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

// $Id$

#include <boost/shared_ptr.hpp>

#include "config.h"

#include "hash_deleter.h"
#include "nsas_entry_compare.h"
#include "nameserver_entry.h"
#include "nameserver_address_store.h"
#include "zone_entry.h"

using namespace isc::dns;
using namespace std;
using namespace boost;

namespace isc {
namespace nsas {

// Constructor.
//
// The LRU lists are set equal to three times the size of the respective
// hash table, on the assumption that three elements is the longest linear
// search we want to do when looking up names in the hash table.
NameserverAddressStore::NameserverAddressStore(uint32_t zonehashsize,
    uint32_t nshashsize) :
    zone_hash_(new NsasEntryCompare<ZoneEntry>, zonehashsize),
    nameserver_hash_(new NsasEntryCompare<NameserverEntry>, nshashsize),
    zone_lru_((3 * zonehashsize), new HashDeleter<ZoneEntry>(zone_hash_)),
    nameserver_lru_((3 * nshashsize), new HashDeleter<NameserverEntry>(
        nameserver_hash_))
{
}

void
NameserverAddressStore::lookup(const std::string& , uint16_t ,
    const AbstractRRset& , const vector<AbstractRRset>& ,
    shared_ptr<AddressRequestCallback> )
{
    // TODO Implement
}

} // namespace nsas
} // namespace isc
