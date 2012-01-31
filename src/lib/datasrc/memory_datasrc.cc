// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <algorithm>
#include <map>
#include <utility>
#include <cctype>
#include <cassert>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/masterload.h>

#include <datasrc/memory_datasrc.h>
#include <datasrc/rbtree.h>
#include <datasrc/logger.h>
#include <datasrc/iterator.h>
#include <datasrc/data_source.h>
#include <datasrc/factory.h>

#include <cc/data.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using boost::scoped_ptr;

namespace isc {
namespace datasrc {

namespace {
// Some type aliases
/*
 * Each domain consists of some RRsets. They will be looked up by the
 * RRType.
 *
 * The use of map is questionable with regard to performance - there'll
 * be usually only few RRsets in the domain, so the log n benefit isn't
 * much and a vector/array might be faster due to its simplicity and
 * continuous memory location. But this is unlikely to be a performance
 * critical place and map has better interface for the lookups, so we use
 * that.
 */
typedef map<RRType, ConstRRsetPtr> Domain;
typedef Domain::value_type DomainPair;
typedef boost::shared_ptr<Domain> DomainPtr;
// The tree stores domains
typedef RBTree<Domain> DomainTree;
typedef RBNode<Domain> DomainNode;

// Separate storage for NSEC3 RRs (and their RRSIGs).  It's an STL map
// from string to the NSEC3 RRset.  The map key is the first label
// (upper cased) of the owner name of the corresponding NSEC3 (i.e., map
// value).  We can use  the standard string comparison (if the comparison
// target is also upper cased) due to the nature of NSEC3 owner names.
typedef map<string, ConstRRsetPtr> NSEC3Map;
typedef NSEC3Map::value_type NSEC3Pair;

// Actual zone data: Essentially a set of zone's RRs.  This is defined as
// a separate structure so that it'll be replaceable on reload.
struct ZoneData {
    ZoneData() : domains_(true) {}

    // The main data (name + RRsets)
    DomainTree domains_;

    // The optional NSEC3 related data
    struct NSEC3Data {
        NSEC3Data(const generic::NSEC3PARAM& nsec3param) :
            hash_(NSEC3Hash::create(nsec3param))
        {}
        NSEC3Data(const generic::NSEC3& nsec3) :
            hash_(NSEC3Hash::create(nsec3))
        {}
        NSEC3Map map_;    // Actual NSEC3 RRs
        const scoped_ptr<NSEC3Hash> hash_; // hash parameter/calculator
    };
    scoped_ptr<NSEC3Data> nsec3_data_; // non NULL only when it's NSEC3 signed
};
}

// Private data and hidden methods of InMemoryZoneFinder
struct InMemoryZoneFinder::InMemoryZoneFinderImpl {
    // Constructor
    InMemoryZoneFinderImpl(const RRClass& zone_class, const Name& origin) :
        zone_class_(zone_class), origin_(origin), origin_data_(NULL),
        zone_data_(new ZoneData)
    {
        // We create the node for origin (it needs to exist anyway in future)
        zone_data_->domains_.insert(origin, &origin_data_);
        DomainPtr origin_domain(new Domain);
        origin_data_->setData(origin_domain);
    }
    static const DomainNode::Flags DOMAINFLAG_WILD = DomainNode::FLAG_USER1;

    // Information about the zone
    RRClass zone_class_;
    Name origin_;
    DomainNode* origin_data_;
    string file_name_;

    // The actual zone data
    scoped_ptr<ZoneData> zone_data_;

    // Add the necessary magic for any wildcard contained in 'name'
    // (including itself) to be found in the zone.
    //
    // In order for wildcard matching to work correctly in find(),
    // we must ensure that a node for the wildcarding level exists in the
    // backend RBTree.
    // E.g. if the wildcard name is "*.sub.example." then we must ensure
    // that "sub.example." exists and is marked as a wildcard level.
    // Note: the "wildcarding level" is for the parent name of the wildcard
    // name (such as "sub.example.").
    //
    // We also perform the same trick for empty wild card names possibly
    // contained in 'name' (e.g., '*.foo.example' in 'bar.*.foo.example').
    void addWildcards(DomainTree& domains, const Name& name) {
        Name wname(name);
        const unsigned int labels(wname.getLabelCount());
        const unsigned int origin_labels(origin_.getLabelCount());
        for (unsigned int l = labels;
             l > origin_labels;
             --l, wname = wname.split(1)) {
            if (wname.isWildcard()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_WILDCARD).
                    arg(name);
                // Ensure a separate level exists for the "wildcarding" name,
                // and mark the node as "wild".
                DomainNode* node;
                DomainTree::Result result(domains.insert(wname.split(1),
                                                         &node));
                assert(result == DomainTree::SUCCESS ||
                       result == DomainTree::ALREADYEXISTS);
                node->setFlag(DOMAINFLAG_WILD);

                // Ensure a separate level exists for the wildcard name.
                // Note: for 'name' itself we do this later anyway, but the
                // overhead should be marginal because wildcard names should
                // be rare.
                result = domains.insert(wname, &node);
                assert(result == DomainTree::SUCCESS ||
                       result == DomainTree::ALREADYEXISTS);
            }
        }
    }

    /*
     * Does some checks in context of the data that are already in the zone.
     * Currently checks for forbidden combinations of RRsets in the same
     * domain (CNAME+anything, DNAME+NS).
     *
     * If such condition is found, it throws AddError.
     */
    void contextCheck(const ConstRRsetPtr& rrset,
                      const DomainPtr& domain) const {
        // Ensure CNAME and other type of RR don't coexist for the same
        // owner name.
        if (rrset->getType() == RRType::CNAME()) {
            // TODO: this check will become incorrect when we support DNSSEC
            // (depending on how we support DNSSEC).  We should revisit it
            // at that point.
            if (!domain->empty()) {
                LOG_ERROR(logger, DATASRC_MEM_CNAME_TO_NONEMPTY).
                    arg(rrset->getName());
                isc_throw(AddError, "CNAME can't be added with other data for "
                          << rrset->getName());
            }
        } else if (domain->find(RRType::CNAME()) != domain->end()) {
            LOG_ERROR(logger, DATASRC_MEM_CNAME_COEXIST).arg(rrset->getName());
            isc_throw(AddError, "CNAME and " << rrset->getType() <<
                      " can't coexist for " << rrset->getName());
        }

        /*
         * Similar with DNAME, but it must not coexist only with NS and only in
         * non-apex domains.
         * RFC 2672 section 3 mentions that it is implied from it and RFC 2181
         */
        if (rrset->getName() != origin_ &&
            // Adding DNAME, NS already there
            ((rrset->getType() == RRType::DNAME() &&
            domain->find(RRType::NS()) != domain->end()) ||
            // Adding NS, DNAME already there
            (rrset->getType() == RRType::NS() &&
            domain->find(RRType::DNAME()) != domain->end())))
        {
            LOG_ERROR(logger, DATASRC_MEM_DNAME_NS).arg(rrset->getName());
            isc_throw(AddError, "DNAME can't coexist with NS in non-apex "
                "domain " << rrset->getName());
        }
    }

    // Validate rrset before adding it to the zone.  If something is wrong
    // it throws an exception.  It doesn't modify the zone, and provides
    // the strong exception guarantee.
    void addValidation(const ConstRRsetPtr rrset) {
        if (!rrset) {
            isc_throw(NullRRset, "The rrset provided is NULL");
        }
        if (rrset->getRdataCount() == 0) {
            isc_throw(AddError, "The rrset provided is empty: " <<
                      rrset->getName() << "/" << rrset->getType());
        }
        // Check for singleton RRs. It should probably handled at a different
        // layer in future.
        if ((rrset->getType() == RRType::CNAME() ||
            rrset->getType() == RRType::DNAME()) &&
            rrset->getRdataCount() > 1)
        {
            // XXX: this is not only for CNAME or DNAME. We should generalize
            // this code for all other "singleton RR types" (such as SOA) in a
            // separate task.
            LOG_ERROR(logger, DATASRC_MEM_SINGLETON).arg(rrset->getName()).
                arg(rrset->getType());
            isc_throw(AddError, "multiple RRs of singleton type for "
                      << rrset->getName());
        }
        // NSEC3/NSEC3PARAM is not a "singleton" per protocol, but this
        // implementation doesn't request it be so at the moment.
        if ((rrset->getType() == RRType::NSEC3() ||
             rrset->getType() == RRType::NSEC3PARAM()) &&
            rrset->getRdataCount() > 1) {
            isc_throw(AddError, "Multiple NSEC3/NSEC3PARAM RDATA is given for "
                      << rrset->getName() << " which isn't supported");
        }

        NameComparisonResult compare(origin_.compare(rrset->getName()));
        if (compare.getRelation() != NameComparisonResult::SUPERDOMAIN &&
            compare.getRelation() != NameComparisonResult::EQUAL)
        {
            LOG_ERROR(logger, DATASRC_MEM_OUT_OF_ZONE).arg(rrset->getName()).
                arg(origin_);
            isc_throw(OutOfZone, "The name " << rrset->getName() <<
                " is not contained in zone " << origin_);
        }

        // Some RR types do not really work well with a wildcard.
        // Even though the protocol specifically doesn't completely ban such
        // usage, we refuse to load a zone containing such RR in order to
        // keep the lookup logic simpler and more predictable.
        // See RFC4592 and (for DNAME) draft-ietf-dnsext-rfc2672bis-dname
        // for more technical background.  Note also that BIND 9 refuses
        // NS at a wildcard, so in that sense we simply provide compatible
        // behavior.
        if (rrset->getName().isWildcard()) {
            if (rrset->getType() == RRType::NS()) {
                LOG_ERROR(logger, DATASRC_MEM_WILDCARD_NS).
                    arg(rrset->getName());
                isc_throw(AddError, "Invalid NS owner name (wildcard): " <<
                          rrset->getName());
            }
            if (rrset->getType() == RRType::DNAME()) {
                LOG_ERROR(logger, DATASRC_MEM_WILDCARD_DNAME).
                    arg(rrset->getName());
                isc_throw(AddError, "Invalid DNAME owner name (wildcard): " <<
                          rrset->getName());
            }
        }

        // Owner names of NSEC3 have special format as defined in RFC5155,
        // and cannot be a wildcard name or must be one label longer than
        // the zone origin.  While the RFC doesn't prohibit other forms of
        // names, no sane zone would have such names for NSEC3.
        // BIND 9 also refuses NSEC3 at wildcard.
        if (rrset->getType() == RRType::NSEC3() &&
            (rrset->getName().isWildcard() ||
             rrset->getName().getLabelCount() !=
             origin_.getLabelCount() + 1)) {
            LOG_ERROR(logger, DATASRC_BAD_NSEC3_NAME).
                arg(rrset->getName());
            isc_throw(AddError, "Invalid NSEC3 owner name: " <<
                      rrset->getName());
        }
    }

    // A helper functor to convert the 1st NSEC3 label to all upper-cased
    // characters.  Note: technically there's a subtle issue when char
    // is signed, but in practice the label should consist of all positive
    // character values for a valid NSEC3 hash name (if it's invalid the
    // resulting zone doesn't work correctly anyway).
    struct ToUpper {
        char operator()(char ch) { return (toupper(ch)); }
    };

    result::Result addRRsig(const ConstRRsetPtr sig_rrset, ZoneData& zone_data)
    {
        // Check consistency of the type covered.
        // We know the RRset isn't empty, so the following check is safe.
        RdataIteratorPtr rit = sig_rrset->getRdataIterator();
        const RRType covered = dynamic_cast<const generic::RRSIG&>(
            rit->getCurrent()).typeCovered();
        for (rit->next(); !rit->isLast(); rit->next()) {
            if (dynamic_cast<const generic::RRSIG&>(
                    rit->getCurrent()).typeCovered() != covered) {
                isc_throw(AddError, "RRSIG contains mixed covered types: "
                          << sig_rrset->toText());
            }
        }

        // Find the RRset to be covered; if not found, treat it as an error
        // for now.
        ConstRRsetPtr covered_rrset;
        if (covered != RRType::NSEC3()) {
            DomainNode* node = NULL;
            if (zone_data.domains_.find(sig_rrset->getName(), &node) !=
                DomainTree::EXACTMATCH || node == NULL || !node->getData()) {
                isc_throw(AddError,
                          "RRSIG is being added, but no RR to be covered: "
                          << sig_rrset->getName());
            }
            const Domain::const_iterator it = node->getData()->find(covered);
            if (it != node->getData()->end()) {
                covered_rrset = it->second;
            }
        } else {
            // In case of NSEC3 if something is found it must be NSEC3 RRset
            // under the assumption of our current implementation.
            if (zone_data.nsec3_data_) {
                string fst_label = sig_rrset->getName().split(0, 1).
                    toText(true);
                transform(fst_label.begin(), fst_label.end(),
                          fst_label.begin(), ToUpper());
                NSEC3Map::const_iterator found =
                    zone_data.nsec3_data_->map_.find(fst_label);
                if (found != zone_data.nsec3_data_->map_.end()) {
                    covered_rrset = found->second;
                    assert(covered_rrset->getType() == covered);
                }
            }
        }
        if (!covered_rrset) {
            isc_throw(AddError, "RRSIG is being added, but no RR of "
                      "covered type found: " << sig_rrset->toText());
        }

        // The current implementation doesn't allow an existing RRSIG to be
        // overridden (or updated with additional ones).
        if (covered_rrset->getRRsig()) {
            isc_throw(AddError,
                      "RRSIG is being added to override an existing one: "
                      << sig_rrset->toText());
        }

        // All okay, setting the RRSIG.
        // XXX: we break const-ness of the covered RRsets.  In practice the
        // ownership of these RRsets would have been given to us so it should
        // be safe, but it's still a very bad practice.
        // We'll fix this problem anyway when we update the underlying
        // representation so that it's more space efficient.
        // Note: there's a slight chance of getting an exception.
        // As noted in add(), we give up strong exception guarantee in such
        // cases.
        boost::const_pointer_cast<RRset>(covered_rrset)->addRRsig(sig_rrset);

        return (result::SUCCESS);
    }

    result::Result addNSEC3(const ConstRRsetPtr rrset, ZoneData& zone_data) {
        // We know rrset has exactly one RDATA
        const generic::NSEC3& nsec3_rdata =
            dynamic_cast<const generic::NSEC3&>(
                rrset->getRdataIterator()->getCurrent());

        // If we've not done any NSEC3 setup for the zone, do it know;
        // otherwise check parameter consistency.
        if (!zone_data.nsec3_data_) {
            zone_data.nsec3_data_.reset(new ZoneData::NSEC3Data(nsec3_rdata));
        } else if (!zone_data.nsec3_data_->hash_->match(nsec3_rdata)) {
            isc_throw(AddError, "NSEC3 with inconsistent parameters: " <<
                      rrset->toText());
        }

        string fst_label = rrset->getName().split(0, 1).toText(true);
        transform(fst_label.begin(), fst_label.end(), fst_label.begin(),
                  ToUpper());

        // Our current implementation doesn't allow an existing NSEC3 to be
        // updated/overridden.
        if (zone_data.nsec3_data_->map_.find(fst_label) !=
            zone_data.nsec3_data_->map_.end()) {
            return (result::EXIST);
        }

        zone_data.nsec3_data_->map_.insert(NSEC3Pair(fst_label, rrset));
        return (result::SUCCESS);
    }

    /*
     * Implementation of longer methods. We put them here, because the
     * access is without the impl_-> and it will get inlined anyway.
     */
    // Implementation of InMemoryZoneFinder::add
    result::Result add(const ConstRRsetPtr& rrset, ZoneData& zone_data) {
        // Sanitize input.  This will cause an exception to be thrown
        // if the input RRset is empty.
        addValidation(rrset);

        // OK, can add the RRset.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_RRSET).
            arg(rrset->getName()).arg(rrset->getType()).arg(origin_);

        if (rrset->getType() == RRType::NSEC3()) {
            return (addNSEC3(rrset, zone_data));
        }

        // RRSIGs are special in various points, so we handle it in a
        // separate dedicated method.
        if (rrset->getType() == RRType::RRSIG()) {
            return (addRRsig(rrset, zone_data));
        }

        // Add wildcards possibly contained in the owner name to the domain
        // tree.
        // Note: this can throw an exception, breaking strong exception
        // guarantee.  (see also the note for contextCheck() below).
        addWildcards(zone_data.domains_, rrset->getName());

        // Get the node
        DomainNode* node;
        DomainTree::Result result = zone_data.domains_.insert(rrset->getName(),
                                                              &node);
        // Just check it returns reasonable results
        assert((result == DomainTree::SUCCESS ||
                result == DomainTree::ALREADYEXISTS) && node!= NULL);

        // Now get the domain
        DomainPtr domain;
        // It didn't exist yet, create it
        if (node->isEmpty()) {
            domain.reset(new Domain);
            node->setData(domain);
        } else { // Get existing one
            domain = node->getData();
        }

        // Checks related to the surrounding data.
        // Note: when the check fails and the exception is thrown, it may
        // break strong exception guarantee.  At the moment we prefer
        // code simplicity and don't bother to introduce complicated
        // recovery code.
        contextCheck(rrset, domain);

        // Try inserting the rrset there
        if (domain->insert(DomainPair(rrset->getType(), rrset)).second) {
            // Ok, we just put it in

            // If this RRset creates a zone cut at this node, mark the node
            // indicating the need for callback in find().
            if (rrset->getType() == RRType::NS() &&
                rrset->getName() != origin_) {
                node->setFlag(DomainNode::FLAG_CALLBACK);
                // If it is DNAME, we have a callback as well here
            } else if (rrset->getType() == RRType::DNAME()) {
                node->setFlag(DomainNode::FLAG_CALLBACK);
            }

            // If we've added NSEC3PARAM at zone origin, set up NSEC3 specific
            // data or check consistency with already set up parameters.
            if (rrset->getType() == RRType::NSEC3PARAM() &&
                rrset->getName() == origin_) {
                // We know rrset has exactly one RDATA
                const generic::NSEC3PARAM& param =
                    dynamic_cast<const generic::NSEC3PARAM&>(
                        rrset->getRdataIterator()->getCurrent());

                if (!zone_data.nsec3_data_) {
                    zone_data.nsec3_data_.reset(
                        new ZoneData::NSEC3Data(param));
                } else if (!zone_data.nsec3_data_->hash_->match(param)) {
                    isc_throw(AddError, "NSEC3PARAM with inconsistent "
                              "parameters: " << rrset->toText());
                }
            }
            return (result::SUCCESS);
        } else {
            // The RRSet of given type was already there
            return (result::EXIST);
        }
    }

    /*
     * Same as above, but it checks the return value and if it already exists,
     * it throws.
     */
    void addFromLoad(const ConstRRsetPtr& set, ZoneData* zone_data) {
        switch (add(set, *zone_data)) {
        case result::EXIST:
            LOG_ERROR(logger, DATASRC_MEM_DUP_RRSET).
                arg(set->getName()).arg(set->getType());
            isc_throw(dns::MasterLoadError, "Duplicate rrset: " <<
                      set->toText());
        case result::SUCCESS:
            return;
        default:
            assert(0);
        }
    }

    // Maintain intermediate data specific to the search context used in
    /// \c find().
    ///
    /// It will be passed to \c zonecutCallback() and record a possible
    /// zone cut node and related RRset (normally NS or DNAME).
    struct FindState {
        FindState(FindOptions options) :
            zonecut_node_(NULL),
            dname_node_(NULL),
            options_(options)
        {}
        const DomainNode* zonecut_node_;
        const DomainNode* dname_node_;
        ConstRRsetPtr rrset_;
        const FindOptions options_;
    };

    // A callback called from possible zone cut nodes and nodes with DNAME.
    // This will be passed from the \c find() method to \c RBTree::find().
    static bool cutCallback(const DomainNode& node, FindState* state) {
        // We need to look for DNAME first, there's allowed case where
        // DNAME and NS coexist in the apex. DNAME is the one to notice,
        // the NS is authoritative, not delegation (corner case explicitly
        // allowed by section 3 of 2672)
        const Domain::const_iterator foundDNAME(node.getData()->find(
            RRType::DNAME()));
        if (foundDNAME != node.getData()->end()) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_MEM_DNAME_ENCOUNTERED);
            state->dname_node_ = &node;
            state->rrset_ = foundDNAME->second;
            // No more processing below the DNAME (RFC 2672, section 3
            // forbids anything to exist below it, so there's no need
            // to actually search for it). This is strictly speaking
            // a different way than described in 4.1 of that RFC,
            // but because of the assumption in section 3, it has the
            // same behaviour.
            return (true);
        }

        // Look for NS
        const Domain::const_iterator foundNS(node.getData()->find(
            RRType::NS()));
        if (foundNS != node.getData()->end()) {
            // We perform callback check only for the highest zone cut in the
            // rare case of nested zone cuts.
            if (state->zonecut_node_ != NULL) {
                return (false);
            }

            LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_MEM_NS_ENCOUNTERED);

            // BIND 9 checks if this node is not the origin.  That's probably
            // because it can support multiple versions for dynamic updates
            // and IXFR, and it's possible that the callback is called at
            // the apex and the DNAME doesn't exist for a particular version.
            // It cannot happen for us (at least for now), so we don't do
            // that check.
            state->zonecut_node_ = &node;
            state->rrset_ = foundNS->second;

            // Unless glue is allowed the search stops here, so we return
            // false; otherwise return true to continue the search.
            return ((state->options_ & FIND_GLUE_OK) == 0);
        }

        // This case should not happen because we enable callback only
        // when we add an RR searched for above.
        assert(0);
        // This is here to avoid warning (therefore compilation error)
        // in case assert is turned off. Otherwise we could get "Control
        // reached end of non-void function".
        return (false);
    }

    /*
     * Prepares a rrset to be return as a result.
     *
     * If rename is false, it returns the one provided. If it is true, it
     * creates a new rrset with the same data but with provided name.
     * It is designed for wildcard case, where we create the rrsets
     * dynamically.
     */
    static ConstRRsetPtr prepareRRset(const Name& name, const ConstRRsetPtr&
        rrset, bool rename)
    {
        if (rename) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_MEM_RENAME).
                arg(rrset->getName()).arg(name);
            /*
             * We lose a signature here. But it would be wrong anyway, because
             * the name changed. This might turn out to be unimportant in
             * future, because wildcards will probably be handled somehow
             * by DNSSEC.
             */
            RRsetPtr result(new RRset(name, rrset->getClass(),
                rrset->getType(), rrset->getTTL()));
            for (RdataIteratorPtr i(rrset->getRdataIterator()); !i->isLast();
                i->next()) {
                result->addRdata(i->getCurrent());
            }
            return (result);
        } else {
            return (rrset);
        }
    }

    // Implementation of InMemoryZoneFinder::find
    FindResult find(const Name& name, RRType type,
                    std::vector<ConstRRsetPtr> *target,
                    const FindOptions options) const
    {
        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FIND).arg(name).
            arg(type);
        // Get the node
        DomainNode* node(NULL);
        FindState state(options);
        RBTreeNodeChain<Domain> node_path;
        bool rename(false);
        switch (zone_data_->domains_.find(name, &node, node_path, cutCallback,
                                          &state)) {
            case DomainTree::PARTIALMATCH:
                /*
                 * In fact, we could use a single variable instead of
                 * dname_node_ and zonecut_node_. But then we would need
                 * to distinquish these two cases by something else and
                 * it seemed little more confusing to me when I wrote it.
                 *
                 * Usually at most one of them will be something else than
                 * NULL (it might happen both are NULL, in which case we
                 * consider it NOT FOUND). There's one corner case when
                 * both might be something else than NULL and it is in case
                 * there's a DNAME under a zone cut and we search in
                 * glue OK mode ‒ in that case we don't stop on the domain
                 * with NS and ignore it for the answer, but it gets set
                 * anyway. Then we find the DNAME and we need to act by it,
                 * therefore we first check for DNAME and then for NS. In
                 * all other cases it doesn't matter, as at least one of them
                 * is NULL.
                 */
                if (state.dname_node_ != NULL) {
                    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DNAME_FOUND).
                        arg(state.rrset_->getName());
                    // We were traversing a DNAME node (and wanted to go
                    // lower below it), so return the DNAME
                    return (FindResult(DNAME, prepareRRset(name, state.rrset_,
                        rename)));
                }
                if (state.zonecut_node_ != NULL) {
                    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DELEG_FOUND).
                        arg(state.rrset_->getName());
                    return (FindResult(DELEGATION, prepareRRset(name,
                        state.rrset_, rename)));
                }

                // If the RBTree search stopped at a node for a super domain
                // of the search name, it means the search name exists in
                // the zone but is empty.  Treat it as NXRRSET.
                if (node_path.getLastComparisonResult().getRelation() ==
                    NameComparisonResult::SUPERDOMAIN) {
                    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUPER_STOP).
                        arg(node_path.getAbsoluteName()).arg(name);
                    return (FindResult(NXRRSET, ConstRRsetPtr()));
                }

                /*
                 * No redirection anywhere. Let's try if it is a wildcard.
                 *
                 * The wildcard is checked after the empty non-terminal domain
                 * case above, because if that one triggers, it means we should
                 * not match according to 4.3.3 of RFC 1034 (the query name
                 * is known to exist).
                 */
                if (node->getFlag(DOMAINFLAG_WILD)) {
                    /* Should we cancel this match?
                     *
                     * If we compare with some node and get a common ancestor,
                     * it might mean we are comparing with a non-wildcard node.
                     * In that case, we check which part is common. If we have
                     * something in common that lives below the node we got
                     * (the one above *), then we should cancel the match
                     * according to section 4.3.3 of RFC 1034 (as the name
                     * between the wildcard domain and the query name is known
                     * to exist).
                     *
                     * Because the way the tree stores relative names, we will
                     * have exactly one common label (the ".") in case we have
                     * nothing common under the node we got and we will get
                     * more common labels otherwise (yes, this relies on the
                     * internal RBTree structure, which leaks out through this
                     * little bit).
                     *
                     * If the empty non-terminal node actually exists in the
                     * tree, then this cancellation is not needed, because we
                     * will not get here at all.
                     */
                    if (node_path.getLastComparisonResult().getRelation() ==
                        NameComparisonResult::COMMONANCESTOR && node_path.
                        getLastComparisonResult().getCommonLabels() > 1) {
                        LOG_DEBUG(logger, DBG_TRACE_DATA,
                                     DATASRC_MEM_WILDCARD_CANCEL).arg(name);
                        return (FindResult(NXDOMAIN, ConstRRsetPtr()));
                    }
                    Name wildcard(Name("*").concatenate(
                        node_path.getAbsoluteName()));
                    DomainTree::Result result =
                        zone_data_->domains_.find(wildcard, &node);
                    /*
                     * Otherwise, why would the DOMAINFLAG_WILD be there if
                     * there was no wildcard under it?
                     */
                    assert(result == DomainTree::EXACTMATCH);
                    /*
                     * We have the wildcard node now. Jump below the switch,
                     * where handling of the common (exact-match) case is.
                     *
                     * However, rename it to the searched name.
                     */
                    rename = true;
                    break;
                }

                // fall through
            case DomainTree::NOTFOUND:
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NOT_FOUND).
                    arg(name);
                return (FindResult(NXDOMAIN, ConstRRsetPtr()));
            case DomainTree::EXACTMATCH: // This one is OK, handle it
                break;
            default:
                assert(0);
        }
        assert(node != NULL);

        // If there is an exact match but the node is empty, it's equivalent
        // to NXRRSET.
        if (node->isEmpty()) {
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_DOMAIN_EMPTY).
                arg(name);
            return (FindResult(NXRRSET, ConstRRsetPtr()));
        }

        Domain::const_iterator found;

        // If the node callback is enabled, this may be a zone cut.  If it
        // has a NS RR, we should return a delegation, but not in the apex.
        // There is one exception: the case for DS query, which should always
        // be considered in-zone lookup.
        if (node->getFlag(DomainNode::FLAG_CALLBACK) && node != origin_data_ &&
            type != RRType::DS()) {
            found = node->getData()->find(RRType::NS());
            if (found != node->getData()->end()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA,
                          DATASRC_MEM_EXACT_DELEGATION).arg(name);
                return (FindResult(DELEGATION, prepareRRset(name,
                    found->second, rename)));
            }
        }

        // handle type any query
        if (target != NULL && !node->getData()->empty()) {
            // Empty domain will be handled as NXRRSET by normal processing
            for (found = node->getData()->begin();
                 found != node->getData()->end(); ++found)
            {
                target->push_back(prepareRRset(name, found->second, rename));
            }
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ANY_SUCCESS).
                arg(name);
            return (FindResult(SUCCESS, ConstRRsetPtr()));
        }

        found = node->getData()->find(type);
        if (found != node->getData()->end()) {
            // Good, it is here
            LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_SUCCESS).arg(name).
                arg(type);
            return (FindResult(SUCCESS, prepareRRset(name, found->second,
                rename)));
        } else {
            // Next, try CNAME.
            found = node->getData()->find(RRType::CNAME());
            if (found != node->getData()->end()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_CNAME).arg(name);
                return (FindResult(CNAME, prepareRRset(name, found->second,
                    rename)));
            }
        }
        // No exact match or CNAME.  Return NXRRSET.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_NXRRSET).arg(type).
            arg(name);
        return (FindResult(NXRRSET, ConstRRsetPtr()));
    }
};

InMemoryZoneFinder::InMemoryZoneFinder(const RRClass& zone_class, const Name& origin) :
    impl_(new InMemoryZoneFinderImpl(zone_class, origin))
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_CREATE).arg(origin).
        arg(zone_class);
}

InMemoryZoneFinder::~InMemoryZoneFinder() {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_DESTROY).arg(getOrigin()).
        arg(getClass());
    delete impl_;
}

Name
InMemoryZoneFinder::getOrigin() const {
    return (impl_->origin_);
}

RRClass
InMemoryZoneFinder::getClass() const {
    return (impl_->zone_class_);
}

ZoneFinder::FindResult
InMemoryZoneFinder::find(const Name& name, const RRType& type,
                 const FindOptions options)
{
    return (impl_->find(name, type, NULL, options));
}

ZoneFinder::FindResult
InMemoryZoneFinder::findAll(const Name& name,
                            std::vector<ConstRRsetPtr>& target,
                            const FindOptions options)
{
    return (impl_->find(name, RRType::ANY(), &target, options));
}

ZoneFinder::FindNSEC3Result
InMemoryZoneFinder::findNSEC3(const Name&, bool) {
    isc_throw(NotImplemented, "findNSEC3 is not yet implemented for in memory "
              "data source");
}

ZoneFinder::FindNSEC3Result
InMemoryZoneFinder::findNSEC3Tmp(const Name& name, bool recursive) {
    if (!impl_->zone_data_->nsec3_data_) {
        isc_throw(Unexpected, "findNSEC3 is called for non NSEC3 zone");
    }
    if (recursive) {
        isc_throw(Unexpected, "recursive mode isn't expected in tests");
    }

    // A temporary workaround for testing: convert the original name to
    // NSEC3-hashed name using hardcoded mapping.
    string hname_text;
    if (name == Name("example.org")) {
        hname_text = "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
    } else if (name == Name("www.example.org")) {
        hname_text = "2S9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
    } else if (name == Name("xxx.example.org")) {
        hname_text = "Q09MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
    } else if (name == Name("yyy.example.org")) {
        hname_text = "0A9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
    } else {
        isc_throw(Unexpected, "unexpected name for NSEC3 test: " << name);
    }

    // Below we assume the map is not empty for simplicity.
    NSEC3Map::const_iterator found =
        impl_->zone_data_->nsec3_data_->map_.lower_bound(hname_text);
    if (found != impl_->zone_data_->nsec3_data_->map_.end() &&
        found->first == hname_text) {
        // exact match
        return (FindNSEC3Result(true, 2, found->second, ConstRRsetPtr()));
    } else if (found == impl_->zone_data_->nsec3_data_->map_.end() ||
               found == impl_->zone_data_->nsec3_data_->map_.begin()) {
        // the search key is "smaller" than the smallest or "larger" than
        // largest.  In either case "previous" is the largest one.
        return (FindNSEC3Result(false, 2,
                                impl_->zone_data_->nsec3_data_->map_.
                                rbegin()->second, ConstRRsetPtr()));
    } else {
        // Otherwise, H(found_domain-1) < given_hash < H(found_domain)
        // The covering proof is the first one.
        return (FindNSEC3Result(false, 2, (--found)->second, ConstRRsetPtr()));
    }

    // We should have covered all cases.
    isc_throw(Unexpected, "Impossible NSEC3 search result for " << name);
}

result::Result
InMemoryZoneFinder::add(const ConstRRsetPtr& rrset) {
    return (impl_->add(rrset, *impl_->zone_data_));
}


void
InMemoryZoneFinder::load(const string& filename) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_LOAD).arg(getOrigin()).
        arg(filename);
    // Load it into temporary zone data
    scoped_ptr<ZoneData> tmp(new ZoneData);
    masterLoad(filename.c_str(), getOrigin(), getClass(),
               boost::bind(&InMemoryZoneFinderImpl::addFromLoad, impl_,
                           _1, tmp.get()));
    // If it went well, put it inside
    impl_->file_name_ = filename;
    tmp.swap(impl_->zone_data_);
    // And let the old data die with tmp
}

void
InMemoryZoneFinder::swap(InMemoryZoneFinder& zone_finder) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_SWAP).arg(getOrigin()).
        arg(zone_finder.getOrigin());
    std::swap(impl_, zone_finder.impl_);
}

const string
InMemoryZoneFinder::getFileName() const {
    return (impl_->file_name_);
}

isc::dns::Name
InMemoryZoneFinder::findPreviousName(const isc::dns::Name&) const {
    isc_throw(NotImplemented, "InMemory data source doesn't support DNSSEC "
              "yet, can't find previous name");
}

/// Implementation details for \c InMemoryClient hidden from the public
/// interface.
///
/// For now, \c InMemoryClient only contains a \c ZoneTable object, which
/// consists of (pointers to) \c InMemoryZoneFinder objects, we may add more
/// member variables later for new features.
class InMemoryClient::InMemoryClientImpl {
public:
    InMemoryClientImpl() : zone_count(0) {}
    unsigned int zone_count;
    ZoneTable zone_table;
};

InMemoryClient::InMemoryClient() : impl_(new InMemoryClientImpl)
{}

InMemoryClient::~InMemoryClient() {
    delete impl_;
}

unsigned int
InMemoryClient::getZoneCount() const {
    return (impl_->zone_count);
}

result::Result
InMemoryClient::addZone(ZoneFinderPtr zone_finder) {
    if (!zone_finder) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to InMemoryClient::addZone()");
    }

    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_ADD_ZONE).
        arg(zone_finder->getOrigin()).arg(zone_finder->getClass().toText());

    const result::Result result = impl_->zone_table.addZone(zone_finder);
    if (result == result::SUCCESS) {
        ++impl_->zone_count;
    }
    return (result);
}

InMemoryClient::FindResult
InMemoryClient::findZone(const isc::dns::Name& name) const {
    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_FIND_ZONE).arg(name);
    ZoneTable::FindResult result(impl_->zone_table.findZone(name));
    return (FindResult(result.code, result.zone));
}

namespace {

class MemoryIterator : public ZoneIterator {
private:
    RBTreeNodeChain<Domain> chain_;
    Domain::const_iterator dom_iterator_;
    const DomainTree& tree_;
    const DomainNode* node_;
    // Only used when separate_rrs_ is true
    RdataIteratorPtr rdata_iterator_;
    bool separate_rrs_;
    bool ready_;
public:
    MemoryIterator(const DomainTree& tree, const Name& origin, bool separate_rrs) :
        tree_(tree),
        separate_rrs_(separate_rrs),
        ready_(true)
    {
        // Find the first node (origin) and preserve the node chain for future
        // searches
        DomainTree::Result result(tree_.find<void*>(origin, &node_, chain_,
                                                    NULL, NULL));
        // It can't happen that the origin is not in there
        if (result != DomainTree::EXACTMATCH) {
            isc_throw(Unexpected,
                      "In-memory zone corrupted, missing origin node");
        }
        // Initialize the iterator if there's somewhere to point to
        if (node_ != NULL && node_->getData() != DomainPtr()) {
            dom_iterator_ = node_->getData()->begin();
            if (separate_rrs_ && dom_iterator_ != node_->getData()->end()) {
                rdata_iterator_ = dom_iterator_->second->getRdataIterator();
            }
        }
    }

    virtual ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            isc_throw(Unexpected, "Iterating past the zone end");
        }
        /*
         * This cycle finds the first nonempty node with yet unused RRset.
         * If it is NULL, we run out of nodes. If it is empty, it doesn't
         * contain any RRsets. If we are at the end, just get to next one.
         */
        while (node_ != NULL && (node_->getData() == DomainPtr() ||
                                 dom_iterator_ == node_->getData()->end())) {
            node_ = tree_.nextNode(chain_);
            // If there's a node, initialize the iterator and check next time
            // if the map is empty or not
            if (node_ != NULL && node_->getData() != NULL) {
                dom_iterator_ = node_->getData()->begin();
                // New RRset, so get a new rdata iterator
                if (separate_rrs_) {
                    rdata_iterator_ = dom_iterator_->second->getRdataIterator();
                }
            }
        }
        if (node_ == NULL) {
            // That's all, folks
            ready_ = false;
            return (ConstRRsetPtr());
        }

        if (separate_rrs_) {
            // For separate rrs, reconstruct a new RRset with just the
            // 'current' rdata
            RRsetPtr result(new RRset(dom_iterator_->second->getName(),
                                      dom_iterator_->second->getClass(),
                                      dom_iterator_->second->getType(),
                                      dom_iterator_->second->getTTL()));
            result->addRdata(rdata_iterator_->getCurrent());
            rdata_iterator_->next();
            if (rdata_iterator_->isLast()) {
                // all used up, next.
                ++dom_iterator_;
                // New RRset, so get a new rdata iterator, but only if this
                // was not the final RRset in the chain
                if (dom_iterator_ != node_->getData()->end()) {
                    rdata_iterator_ = dom_iterator_->second->getRdataIterator();
                }
            }
            return (result);
        } else {
            // The iterator points to the next yet unused RRset now
            ConstRRsetPtr result(dom_iterator_->second);

            // This one is used, move it to the next time for next call
            ++dom_iterator_;

            return (result);
        }
    }

    virtual ConstRRsetPtr getSOA() const {
        isc_throw(NotImplemented, "Not imelemented");
    }
};

} // End of anonymous namespace

ZoneIteratorPtr
InMemoryClient::getIterator(const Name& name, bool separate_rrs) const {
    ZoneTable::FindResult result(impl_->zone_table.findZone(name));
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + name.toText());
    }

    const InMemoryZoneFinder*
        zone(dynamic_cast<const InMemoryZoneFinder*>(result.zone.get()));
    if (zone == NULL) {
        /*
         * TODO: This can happen only during some of the tests and only as
         * a temporary solution. This should be fixed by #1159 and then
         * this cast and check shouldn't be necessary. We don't have
         * test for handling a "can not happen" condition.
         */
        isc_throw(Unexpected, "The zone at " + name.toText() +
                  " is not InMemoryZoneFinder");
    }
    return (ZoneIteratorPtr(new MemoryIterator(
                                zone->impl_->zone_data_->domains_, name,
                                separate_rrs)));
}

ZoneUpdaterPtr
InMemoryClient::getUpdater(const isc::dns::Name&, bool, bool) const {
    isc_throw(isc::NotImplemented, "Update attempt on in memory data source");
}

pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
InMemoryClient::getJournalReader(const isc::dns::Name&, uint32_t,
                                 uint32_t) const
{
    isc_throw(isc::NotImplemented, "Journaling isn't supported for "
              "in memory data source");
}

namespace {
// convencience function to add an error message to a list of those
// (TODO: move functions like these to some util lib?)
void
addError(ElementPtr errors, const std::string& error) {
    if (errors != ElementPtr() && errors->getType() == Element::list) {
        errors->add(Element::create(error));
    }
}

/// Check if the given element exists in the map, and if it is a string
bool
checkConfigElementString(ConstElementPtr config, const std::string& name,
                         ElementPtr errors)
{
    if (!config->contains(name)) {
        addError(errors,
                 "Config for memory backend does not contain a '"
                 +name+
                 "' value");
        return false;
    } else if (!config->get(name) ||
               config->get(name)->getType() != Element::string) {
        addError(errors, "value of " + name +
                 " in memory backend config is not a string");
        return false;
    } else {
        return true;
    }
}

bool
checkZoneConfig(ConstElementPtr config, ElementPtr errors) {
    bool result = true;
    if (!config || config->getType() != Element::map) {
        addError(errors, "Elements in memory backend's zone list must be maps");
        result = false;
    } else {
        if (!checkConfigElementString(config, "origin", errors)) {
            result = false;
        }
        if (!checkConfigElementString(config, "file", errors)) {
            result = false;
        }
        // we could add some existence/readabilty/parsability checks here
        // if we want
    }
    return result;
}

bool
checkConfig(ConstElementPtr config, ElementPtr errors) {
    /* Specific configuration is under discussion, right now this accepts
     * the 'old' configuration, see [TODO]
     * So for memory datasource, we get a structure like this:
     * { "type": string ("memory"),
     *   "class": string ("IN"/"CH"/etc),
     *   "zones": list
     * }
     * Zones list is a list of maps:
     * { "origin": string,
     *     "file": string
     * }
     *
     * At this moment we cannot be completely sure of the contents of the
     * structure, so we have to do some more extensive tests than should
     * strictly be necessary (e.g. existence and type of elements)
     */
    bool result = true;

    if (!config || config->getType() != Element::map) {
        addError(errors, "Base config for memory backend must be a map");
        result = false;
    } else {
        if (!checkConfigElementString(config, "type", errors)) {
            result = false;
        } else {
            if (config->get("type")->stringValue() != "memory") {
                addError(errors,
                         "Config for memory backend is not of type \"memory\"");
                result = false;
            }
        }
        if (!checkConfigElementString(config, "class", errors)) {
            result = false;
        } else {
            try {
                RRClass rrc(config->get("class")->stringValue());
            } catch (const isc::Exception& rrce) {
                addError(errors,
                         "Error parsing class config for memory backend: " +
                         std::string(rrce.what()));
                result = false;
            }
        }
        if (!config->contains("zones")) {
            addError(errors, "No 'zones' element in memory backend config");
            result = false;
        } else if (!config->get("zones") ||
                   config->get("zones")->getType() != Element::list) {
            addError(errors, "'zones' element in memory backend config is not a list");
            result = false;
        } else {
            BOOST_FOREACH(ConstElementPtr zone_config,
                          config->get("zones")->listValue()) {
                if (!checkZoneConfig(zone_config, errors)) {
                    result = false;
                }
            }
        }
    }

    return (result);
    return true;
}

} // end anonymous namespace

DataSourceClient *
createInstance(isc::data::ConstElementPtr config, std::string& error) {
    ElementPtr errors(Element::createList());
    if (!checkConfig(config, errors)) {
        error = "Configuration error: " + errors->str();
        return (NULL);
    }
    try {
        return (new InMemoryClient());
    } catch (const std::exception& exc) {
        error = std::string("Error creating memory datasource: ") + exc.what();
        return (NULL);
    } catch (...) {
        error = std::string("Error creating memory datasource, "
                            "unknown exception");
        return (NULL);
    }
}

void destroyInstance(DataSourceClient* instance) {
    delete instance;
}


} // end of namespace datasrc
} // end of namespace isc
