// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/rrset_collection.h>
#include <dns/master_loader_callbacks.h>
#include <dns/master_loader.h>

#include <boost/bind.hpp>

namespace isc {
namespace dns {

void
RRsetCollection::loaderCallback(const std::string&, size_t, const std::string&)
{
     // We just ignore callbacks for errors and warnings.
}

void
RRsetCollection::addRRset(const Name& name, const RRClass& rrclass,
                          const RRType& rrtype, const RRTTL& rrttl,
                          const rdata::RdataPtr& data)
{
    RRsetPtr rrset(new BasicRRset(name, rrclass, rrtype, rrttl));
    rrset->addRdata(data);
    addRRset(rrset);
}

void
RRsetCollection::addRRset(RRsetPtr rrset) {
    const CollectionKey key(rrset->getClass(), rrset->getType(),
                            rrset->getName());
    rrsets_.insert(std::pair<CollectionKey, RRsetPtr>(key, rrset));
}

RRsetCollection::RRsetCollection(const char* filename, const Name& origin,
                                 const RRClass& rrclass)
{
    MasterLoaderCallbacks callbacks
        (boost::bind(&RRsetCollection::loaderCallback, this, _1, _2, _3),
         boost::bind(&RRsetCollection::loaderCallback, this, _1, _2, _3));
    MasterLoader loader(filename, origin, rrclass, callbacks,
                        boost::bind(&RRsetCollection::addRRset,
                                    this, _1, _2, _3, _4, _5),
                        MasterLoader::DEFAULT);
    loader.load();
}

const AbstractRRset*
RRsetCollection::find(const Name& name, const RRType& rrtype,
                      const RRClass& rrclass) const {
    const CollectionKey key(rrclass, rrtype, name);
    CollectionMap::const_iterator it = rrsets_.find(key);
    if (it != rrsets_.end()) {
        return (&(*it->second));
    }
    return (NULL);
}

RRsetPtr
RRsetCollection::find(const Name& name, const RRClass& rrclass,
                      const RRType& rrtype) {
    const CollectionKey key(rrclass, rrtype, name);
    CollectionMap::iterator it = rrsets_.find(key);
    if (it != rrsets_.end()) {
        return (it->second);
    }
    return (RRsetPtr());
}

ConstRRsetPtr
RRsetCollection::find(const Name& name, const RRClass& rrclass,
                      const RRType& rrtype) const
{
    const CollectionKey key(rrclass, rrtype, name);
    CollectionMap::const_iterator it = rrsets_.find(key);
    if (it != rrsets_.end()) {
        return (it->second);
    }
    return (ConstRRsetPtr());
}

void
RRsetCollection::removeRRset(const Name& name, const RRClass& rrclass,
                             const RRType& rrtype)
{
    const CollectionKey key(rrclass, rrtype, name);
    rrsets_.erase(key);
}

RRsetCollectionBase::IterPtr
RRsetCollection::getBeginning() {
    CollectionMap::iterator it = rrsets_.begin();
    return (RRsetCollectionBase::IterPtr(new DnsIter(it)));
}

RRsetCollectionBase::IterPtr
RRsetCollection::getEnd() {
    CollectionMap::iterator it = rrsets_.end();
    return (RRsetCollectionBase::IterPtr(new DnsIter(it)));
}

} // end of namespace dns
} // end of namespace isc
