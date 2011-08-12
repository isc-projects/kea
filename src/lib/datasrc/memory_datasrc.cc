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

#include <map>
#include <cassert>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/masterload.h>

#include <datasrc/memory_datasrc.h>
#include <datasrc/rbtree.h>
#include <datasrc/logger.h>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {

// Private data and hidden methods of InMemoryZoneFinder
struct InMemoryZoneFinder::InMemoryZoneFinderImpl {
    // Constructor
    InMemoryZoneFinderImpl(const RRClass& zone_class, const Name& origin) :
        zone_class_(zone_class), origin_(origin), origin_data_(NULL),
        domains_(true)
    {
        // We create the node for origin (it needs to exist anyway in future)
        domains_.insert(origin, &origin_data_);
        DomainPtr origin_domain(new Domain);
        origin_data_->setData(origin_domain);
    }

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
    static const DomainNode::Flags DOMAINFLAG_WILD = DomainNode::FLAG_USER1;

    // Information about the zone
    RRClass zone_class_;
    Name origin_;
    DomainNode* origin_data_;
    string file_name_;

    // The actual zone data
    DomainTree domains_;

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
        // Check for singleton RRs. It should probably handled at a different
        // in future.
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
    }

    /*
     * Implementation of longer methods. We put them here, because the
     * access is without the impl_-> and it will get inlined anyway.
     */
    // Implementation of InMemoryZoneFinder::add
    result::Result add(const ConstRRsetPtr& rrset, DomainTree* domains) {
        // Sanitize input.  This will cause an exception to be thrown
        // if the input RRset is empty.
        addValidation(rrset);

        // OK, can add the RRset.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_RRSET).
            arg(rrset->getName()).arg(rrset->getType()).arg(origin_);

        // Add wildcards possibly contained in the owner name to the domain
        // tree.
        // Note: this can throw an exception, breaking strong exception
        // guarantee.  (see also the note for contextCheck() below).
        addWildcards(*domains, rrset->getName());

        // Get the node
        DomainNode* node;
        DomainTree::Result result = domains->insert(rrset->getName(), &node);
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
    void addFromLoad(const ConstRRsetPtr& set, DomainTree* domains) {
            switch (add(set, domains)) {
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
                    RRsetList* target, const FindOptions options) const
    {
        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_FIND).arg(name).
            arg(type);
        // Get the node
        DomainNode* node(NULL);
        FindState state(options);
        RBTreeNodeChain<Domain> node_path;
        bool rename(false);
        switch (domains_.find(name, &node, node_path, cutCallback, &state)) {
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
                    DomainTree::Result result(domains_.find(wildcard, &node));
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
        if (node->getFlag(DomainNode::FLAG_CALLBACK) && node != origin_data_) {
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
                target->addRRset(
                    boost::const_pointer_cast<RRset>(prepareRRset(name,
                    found->second, rename)));
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
                 RRsetList* target, const FindOptions options)
{
    return (impl_->find(name, type, target, options));
}

result::Result
InMemoryZoneFinder::add(const ConstRRsetPtr& rrset) {
    return (impl_->add(rrset, &impl_->domains_));
}


void
InMemoryZoneFinder::load(const string& filename) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_LOAD).arg(getOrigin()).
        arg(filename);
    // Load it into a temporary tree
    InMemoryZoneFinderImpl::DomainTree tmp;
    masterLoad(filename.c_str(), getOrigin(), getClass(),
        boost::bind(&InMemoryZoneFinderImpl::addFromLoad, impl_, _1, &tmp));
    // If it went well, put it inside
    impl_->file_name_ = filename;
    tmp.swap(impl_->domains_);
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
    return (FindResult(impl_->zone_table.findZone(name).code,
                       impl_->zone_table.findZone(name).zone));
}
} // end of namespace datasrc
} // end of namespace dns
