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

#include <dns/rrset.h>
#include "local_zone_data.h"
#include "cache_entry_key.h"
#include "rrset_copy.h"
#include "logger.h"

using namespace std;
using namespace isc::dns;

namespace isc {
namespace cache {

typedef pair<std::string, RRsetPtr> RRsetMapPair;
typedef map<std::string, RRsetPtr>::iterator RRsetMapIterator;

isc::dns::RRsetPtr
LocalZoneData::lookup(const isc::dns::Name& name,
                      const isc::dns::RRType& type)
{
    string key = genCacheEntryName(name, type);
    RRsetMapIterator iter = rrsets_map_.find(key);
    if (iter == rrsets_map_.end()) {
        LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_LOCALZONE_UNKNOWN).arg(key);
        return (RRsetPtr());
    } else {
        LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_LOCALZONE_FOUND).arg(key);
        return (iter->second);
    }
}

void
LocalZoneData::update(const isc::dns::AbstractRRset& rrset) {
    //TODO Do we really need to recreate the rrset again?
    string key = genCacheEntryName(rrset.getName(), rrset.getType());
    LOG_DEBUG(logger, DBG_TRACE_DATA, CACHE_LOCALZONE_UPDATE).arg(key);
    RRset* rrset_copy = new RRset(rrset.getName(), rrset.getClass(),
                                  rrset.getType(), rrset.getTTL());

    rrsetCopy(rrset, *rrset_copy);
    RRsetPtr rrset_ptr(rrset_copy);
    rrsets_map_[key] = rrset_ptr;
}

} // namespace cache
} // namespace isc

