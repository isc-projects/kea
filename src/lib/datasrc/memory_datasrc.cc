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

#include <dns/name.h>
#include <dns/rrclass.h>

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
    result::Result add(const ConstRRsetPtr& rrset) {
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
        switch (domains_.insert(name, &node)) {
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
            return (result::SUCCESS);
        } else {
            // The RRSet of given type was already there
            return (result::EXIST);
        }
    }

    // Implementation of MemoryZone::find
    FindResult find(const Name& name, RRType type) const {
        // Get the node
        DomainNode* node;
        switch (domains_.find(name, &node)) {
            case DomainTree::PARTIALMATCH:
                // Pretend it was not found for now
                // TODO: Implement real delegation
            case DomainTree::NOTFOUND:
                return (FindResult(NXDOMAIN, ConstRRsetPtr()));
            case DomainTree::EXACTMATCH: // This one is OK, handle it
                break;
            default:
                assert(0);
        }
        assert(node);
        assert(!node->isEmpty());

        Domain::const_iterator found(node->getData()->find(type));
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
MemoryZone::find(const Name& name, const RRType& type) const {
    return (impl_->find(name, type));
}

result::Result
MemoryZone::add(const ConstRRsetPtr& rrset) {
    return (impl_->add(rrset));
}

/// Implementation details for \c MemoryDataSrc hidden from the public
/// interface.
///
/// For now, \c MemoryDataSrc only contains a \c ZoneTable object, which
/// consists of (pointers to) \c MemoryZone objects, we may add more
/// member variables later for new features.
struct MemoryDataSrc::MemoryDataSrcImpl {
    ZoneTable zone_table;
};

MemoryDataSrc::MemoryDataSrc() : impl_(new MemoryDataSrcImpl)
{}

MemoryDataSrc::~MemoryDataSrc() {
    delete impl_;
}

result::Result
MemoryDataSrc::addZone(ZonePtr zone) {
    if (!zone) {
        isc_throw(InvalidParameter,
                  "Null pointer is passed to MemoryDataSrc::addZone()");
    }
    return (impl_->zone_table.addZone(zone));
}

MemoryDataSrc::FindResult
MemoryDataSrc::findZone(const isc::dns::Name& name) const {
    return (FindResult(impl_->zone_table.findZone(name).code,
                       impl_->zone_table.findZone(name).zone));
}
} // end of namespace datasrc
} // end of namespace dns
