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

#include <datasrc/zone_loader.h>

#include <datasrc/client.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>
#include <datasrc/zone.h>

#include <dns/rrset.h>

using isc::dns::Name;
using isc::dns::ConstRRsetPtr;

namespace isc {
namespace datasrc {

ZoneLoader::ZoneLoader(DataSourceClient& destination, const Name& zone_name,
                       DataSourceClient& source) :
    // Separate the RRsets as that is possibly faster (the data source doesn't
    // have to aggregate them) and also because our limit semantics.
    iterator_(source.getIterator(zone_name, true)),
    updater_(destination.getUpdater(zone_name, true, false))
{
    // The getIterator should never return NULL. So we check it.
    // Or should we throw instead?
    assert(iterator_ != ZoneIteratorPtr());
    // In case the zone doesn't exist in the destination, throw
    if (updater_ == ZoneUpdaterPtr()) {
        isc_throw(DataSourceError, "Zone " << zone_name << " not found in "
                  "destination data source, can't fill it with data");
    }
}

namespace {

// Copy up to limit RRsets from source to destination
bool
copyRRsets(const ZoneUpdaterPtr& destination, const ZoneIteratorPtr& source,
           size_t limit)
{
    size_t loaded = 0;
    while (loaded < limit) {
        const ConstRRsetPtr rrset(source->getNextRRset());
        if (rrset == ConstRRsetPtr()) {
            // Done loading, no more RRsets in the input.
            return (true);
        } else {
            destination->addRRset(*rrset);
        }
        ++loaded;
    }
    return (false); // Not yet, there may be more
}

}

bool
ZoneLoader::loadIncremental(size_t limit) {
    if (iterator_ != ZoneIteratorPtr()) {
        if (copyRRsets(updater_, iterator_, limit)) {
            updater_->commit();
            return (true);
        } else {
            return (false);
        }
    } else {
        isc_throw(isc::NotImplemented, "The master file way is not ready yet");
    }
}

}
}
