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

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {

// Private data and hidden methods of MemoryZone
struct MemoryZone::MemoryZoneImpl {
    // Constructor
    MemoryZoneImpl(const RRClass& zone_class, const Name& origin) :
        zone_class_(zone_class), origin_(origin), origin_data_(NULL)
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
    typedef RBTree<Domain, true> DomainTree;
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
                // Ensure a separate level exists for the wildcard name.
                // Note: for 'name' itself we do this later anyway, but the
                // overhead should be marginal because wildcard names should
                // be rare.
                DomainNode* node;
                DomainTree::Result result(domains.insert(wname.split(1),
                                                         &node));
                assert(result == DomainTree::SUCCESS ||
                       result == DomainTree::ALREADYEXISTS);

                // Ensure a separate level exists for the "wildcarding" name,
                // and mark the node as "wild".
                result = domains.insert(wname, &node);
                assert(result == DomainTree::SUCCESS ||
                       result == DomainTree::ALREADYEXISTS);
                node->setFlag(DOMAINFLAG_WILD);
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
            // XXX: this check will become incorrect when we support DNSSEC
            // (depending on how we support DNSSEC).  We should revisit it
            // at that point.
            if (!domain->empty()) {
                isc_throw(AddError, "CNAME can't be added with other data for "
                          << rrset->getName());
            }
        } else if (domain->find(RRType::CNAME()) != domain->end()) {
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
            isc_throw(AddError, "multiple RRs of singleton type for "
                      << rrset->getName());
        }

        NameComparisonResult compare(origin_.compare(rrset->getName()));
        if (compare.getRelation() != NameComparisonResult::SUPERDOMAIN &&
            compare.getRelation() != NameComparisonResult::EQUAL)
        {
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
                isc_throw(AddError, "Invalid NS owner name (wildcard): " <<
                          rrset->getName());
            }
            if (rrset->getType() == RRType::DNAME()) {
                isc_throw(AddError, "Invalid DNAME owner name (wildcard): " <<
                          rrset->getName());
            }
        }
    }

    /*
     * Implementation of longer methods. We put them here, because the
     * access is without the impl_-> and it will get inlined anyway.
     */
    // Implementation of MemoryZone::add
    result::Result add(const ConstRRsetPtr& rrset, DomainTree* domains) {
        // Sanitize input
        addValidation(rrset);

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


    // Implementation of MemoryZone::find
    FindResult find(const Name& name, RRType type,
                    RRsetList* target, const FindOptions options) const
    {
        // Get the node
        DomainNode* node(NULL);
        FindState state(options);
        switch (domains_.find(name, &node, cutCallback, &state)) {
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
                    // We were traversing a DNAME node (and wanted to go
                    // lower below it), so return the DNAME
                    return (FindResult(DNAME, state.rrset_));
                }
                if (state.zonecut_node_ != NULL) {
                    return (FindResult(DELEGATION, state.rrset_));
                }
                // TODO: we should also cover empty non-terminal cases, which
                // will require non trivial code and is deferred for later
                // development.  For now, we regard any partial match that
                // didn't hit a zone cut as "not found".
            case DomainTree::NOTFOUND:
                return (FindResult(NXDOMAIN, ConstRRsetPtr()));
            case DomainTree::EXACTMATCH: // This one is OK, handle it
                break;
            default:
                assert(0);
        }
        assert(node);

        // If there is an exact match but the node is empty, it's equivalent
        // to NXRRSET.
        if (node->isEmpty()) {
            return (FindResult(NXRRSET, ConstRRsetPtr()));
        }

        Domain::const_iterator found;

        // If the node callback is enabled, this may be a zone cut.  If it
        // has a NS RR, we should return a delegation, but not in the apex.
        if (node->getFlag(DomainNode::FLAG_CALLBACK) && node != origin_data_) {
            found = node->getData()->find(RRType::NS());
            if (found != node->getData()->end()) {
                return (FindResult(DELEGATION, found->second));
            }
        }

        // handle type any query
        if (target != NULL && !node->getData()->empty()) {
            // Empty domain will be handled as NXRRSET by normal processing
            for (found = node->getData()->begin();
                 found != node->getData()->end(); found++)
            {
                target->addRRset(
                    boost::const_pointer_cast<RRset>(found->second));
            }
            return (FindResult(SUCCESS, ConstRRsetPtr()));
        }

        found = node->getData()->find(type);
        if (found != node->getData()->end()) {
            // Good, it is here
            return (FindResult(SUCCESS, found->second));
        } else {
            // Next, try CNAME.
            found = node->getData()->find(RRType::CNAME());
            if (found != node->getData()->end()) {
                return (FindResult(CNAME, found->second));
            }
        }
        // No exact match or CNAME.  Return NXRRSET.
        return (FindResult(NXRRSET, ConstRRsetPtr()));
    }
};

MemoryZone::MemoryZone(const RRClass& zone_class, const Name& origin) :
    impl_(new MemoryZoneImpl(zone_class, origin))
{
}

MemoryZone::~MemoryZone() {
    delete impl_;
}

const Name&
MemoryZone::getOrigin() const {
    return (impl_->origin_);
}

const RRClass&
MemoryZone::getClass() const {
    return (impl_->zone_class_);
}

Zone::FindResult
MemoryZone::find(const Name& name, const RRType& type,
                 RRsetList* target, const FindOptions options) const
{
    return (impl_->find(name, type, target, options));
}

result::Result
MemoryZone::add(const ConstRRsetPtr& rrset) {
    return (impl_->add(rrset, &impl_->domains_));
}


void
MemoryZone::load(const string& filename) {
    // Load it into a temporary tree
    MemoryZoneImpl::DomainTree tmp;
    masterLoad(filename.c_str(), getOrigin(), getClass(),
        boost::bind(&MemoryZoneImpl::addFromLoad, impl_, _1, &tmp));
    // If it went well, put it inside
    impl_->file_name_ = filename;
    tmp.swap(impl_->domains_);
    // And let the old data die with tmp
}

void
MemoryZone::swap(MemoryZone& zone) {
    std::swap(impl_, zone.impl_);
}

const string
MemoryZone::getFileName() const {
    return (impl_->file_name_);
}

/// Implementation details for \c MemoryDataSrc hidden from the public
/// interface.
///
/// For now, \c MemoryDataSrc only contains a \c ZoneTable object, which
/// consists of (pointers to) \c MemoryZone objects, we may add more
/// member variables later for new features.
class MemoryDataSrc::MemoryDataSrcImpl {
public:
    MemoryDataSrcImpl() : zone_count(0) {}
    unsigned int zone_count;
    ZoneTable zone_table;
};

MemoryDataSrc::MemoryDataSrc() : impl_(new MemoryDataSrcImpl)
{}

MemoryDataSrc::~MemoryDataSrc() {
    delete impl_;
}

unsigned int
MemoryDataSrc::getZoneCount() const {
    return (impl_->zone_count);
}

result::Result
MemoryDataSrc::addZone(ZonePtr zone) {
    if (!zone) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to MemoryDataSrc::addZone()");
    }

    const result::Result result = impl_->zone_table.addZone(zone);
    if (result == result::SUCCESS) {
        ++impl_->zone_count;
    }
    return (result);
}

MemoryDataSrc::FindResult
MemoryDataSrc::findZone(const isc::dns::Name& name) const {
    return (FindResult(impl_->zone_table.findZone(name).code,
                       impl_->zone_table.findZone(name).zone));
}
} // end of namespace datasrc
} // end of namespace dns
