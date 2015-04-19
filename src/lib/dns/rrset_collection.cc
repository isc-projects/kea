// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_DNS_EXPORT

#include <dns/rrset_collection.h>
#include <dns/master_loader_callbacks.h>
#include <dns/master_loader.h>
#include <dns/rrcollator.h>

#include <exceptions/exceptions.h>

#include <boost/bind.hpp>

using namespace isc;

namespace isc {
namespace dns {

void
RRsetCollection::loaderCallback(const std::string&, size_t, const std::string&)
{
     // We just ignore callbacks for errors and warnings.
}

void
RRsetCollection::addRRset(RRsetPtr rrset) {
    const CollectionKey key(rrset->getClass(), rrset->getType(),
                            rrset->getName());
    CollectionMap::const_iterator it = rrsets_.find(key);
    if (it != rrsets_.end()) {
        isc_throw(InvalidParameter,
                  "RRset for " << rrset->getName() << "/" << rrset->getClass()
                  << " with type " << rrset->getType() << " already exists");
    }

    rrsets_.insert(std::pair<CollectionKey, RRsetPtr>(key, rrset));
}

template<typename T>
void
RRsetCollection::constructHelper(T source, const isc::dns::Name& origin,
                                 const isc::dns::RRClass& rrclass)
{
    RRCollator collator(boost::bind(&RRsetCollection::addRRset, this, _1));
    MasterLoaderCallbacks callbacks
        (boost::bind(&RRsetCollection::loaderCallback, this, _1, _2, _3),
         boost::bind(&RRsetCollection::loaderCallback, this, _1, _2, _3));
    MasterLoader loader(source, origin, rrclass, callbacks,
                        collator.getCallback(),
                        MasterLoader::DEFAULT);
    loader.load();
    collator.flush();
}

RRsetCollection::RRsetCollection(const char* filename, const Name& origin,
                                 const RRClass& rrclass)
{
    constructHelper(filename, origin, rrclass);
}

RRsetCollection::RRsetCollection(std::istream& input_stream, const Name& origin,
                                 const RRClass& rrclass)
{
    constructHelper<std::istream&>(input_stream, origin, rrclass);
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

bool
RRsetCollection::removeRRset(const Name& name, const RRClass& rrclass,
                             const RRType& rrtype)
{
    const CollectionKey key(rrclass, rrtype, name);

    CollectionMap::iterator it = rrsets_.find(key);
    if (it == rrsets_.end()) {
        return (false);
    }

    rrsets_.erase(it);
    return (true);
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
