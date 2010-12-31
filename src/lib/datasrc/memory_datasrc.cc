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
        zone_class_(zone_class), origin_(origin)
    {}

    // Information about the zone
    RRClass zone_class_;
    Name origin_;

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
    // The actual zone data
    DomainTree domains_;

    /*
     * Implementation of longer methods. We put them here, because the
     * access is without the impl_-> and it will get inlined anyway.
     */
    // Implementation of MemoryZone::add
    result::Result add(const ConstRRsetPtr& rrset, DomainTree* domains) {
        // Sanitize input
        if (!rrset) {
            isc_throw(NullRRset, "The rrset provided is NULL");
        }
        Name name(rrset->getName());
        NameComparisonResult compare(origin_.compare(name));
        if (compare.getRelation() != NameComparisonResult::SUPERDOMAIN &&
            compare.getRelation() != NameComparisonResult::EQUAL)
        {
            isc_throw(OutOfZone, "The name " << name <<
                " is not contained in zone " << origin_);
        }
        // Get the node
        DomainNode* node;
        switch (domains->insert(name, &node)) {
            // Just check it returns reasonable results
            case DomainTree::SUCCEED:
            case DomainTree::ALREADYEXIST:
                break;
            // Something odd got out
            default:
                assert(0);
        }
        assert(node);

        // Now get the domain
        DomainPtr domain;
        // It didn't exist yet, create it
        if (node->isEmpty()) {
            domain.reset(new Domain);
            node->setData(domain);
        } else { // Get existing one
            domain = node->getData();
        }

        // Try inserting the rrset there
        if (domain->insert(DomainPair(rrset->getType(), rrset)).second) {
            // Ok, we just put it in

            // If this RRset creates a zone cut at this node, mark the node
            // indicating the need for callback in find().
            // TBD: handle DNAME, too
            if (rrset->getType() == RRType::NS() &&
                rrset->getName() != origin_) {
                node->enableCallback();
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
        FindState(FindOptions options) : zonecut_node_(NULL),
                                         options_(options)
        {}
        const DomainNode* zonecut_node_;
        ConstRRsetPtr rrset_;
        const FindOptions options_;
    };

    // A callback called from possible zone cut nodes.  This will be passed
    // from the \c find() method to \c RBTree::find().
    static bool zonecutCallback(const DomainNode& node, FindState* state) {
        // We perform callback check only for the highest zone cut in the
        // rare case of nested zone cuts.
        if (state->zonecut_node_ != NULL) {
            return (false);
        }

        const Domain::const_iterator found(node.getData()->find(RRType::NS()));
        if (found != node.getData()->end()) {
            // BIND 9 checks if this node is not the origin.  But it cannot
            // be the origin because we don't enable the callback at the
            // origin node (see MemoryZoneImpl::add()).  Or should we do a
            // double check for it?
            state->zonecut_node_ = &node;
            state->rrset_ = found->second;

            // Unless glue is allowed the search stops here, so we return
            // false; otherwise return true to continue the search.
            return ((state->options_ & FIND_GLUE_OK) == 0);
        }

        // This case should not happen because we enable callback only
        // when we add an RR searched for above.
        assert(0);
    }

    // Implementation of MemoryZone::find
    FindResult find(const Name& name, RRType type,
                    const FindOptions options) const
    {
        // Get the node
        DomainNode* node(NULL);
        FindState state(options);
        switch (domains_.find(name, &node, zonecutCallback, &state)) {
            case DomainTree::PARTIALMATCH:
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
        assert(!node->isEmpty());

        Domain::const_iterator found;

        // If the node callback is enabled, this may be a zone cut.  If it
        // has a NS RR, we should return a delegation.
        if (node->isCallbackEnabled()) {
            found = node->getData()->find(RRType::NS());
            if (found != node->getData()->end()) {
                return (FindResult(DELEGATION, found->second));
            }
        }

        found = node->getData()->find(type);
        if (found != node->getData()->end()) {
            // Good, it is here
            return (FindResult(SUCCESS, found->second));
        } else {
            /*
             * TODO Look for CNAME and DNAME (it should be OK to do so when
             * the value is not found, as CNAME/DNAME domain should be
             * empty otherwise.)
             */
            return (FindResult(NXRRSET, ConstRRsetPtr()));
        }
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
                 const FindOptions options) const
{
    return (impl_->find(name, type, options));
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
    tmp.swap(impl_->domains_);
    // And let the old data die with tmp
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
