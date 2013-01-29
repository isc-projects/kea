// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/rrset_collection_base.h>
#include <datasrc/zone_loader.h>
#include <datasrc/zone_finder.h>
#include <exceptions/exceptions.h>

using namespace isc;
using namespace isc::dns;

namespace isc {
namespace datasrc {

ConstRRsetPtr
isc::datasrc::RRsetCollectionBase::find(const isc::dns::Name& name,
                                        const isc::dns::RRClass& rrclass,
                                        const isc::dns::RRType& rrtype) const
{
    if (isDisabled()) {
        isc_throw(RRsetCollectionError, "This RRsetCollection is disabled.");
    }

    if (rrclass != rrclass_) {
        // We could throw an exception here, but RRsetCollection is
        // expected to support an arbitrary collection of RRsets, and it
        // can be queried just as arbitrarily. So we just return nothing
        // here.
        return (ConstRRsetPtr());
    }

    ZoneFinder& finder = updater_.getFinder();
    try {
        ZoneFinderContextPtr result =
            finder.find(name, rrtype,
                        ZoneFinder::NO_WILDCARD | ZoneFinder::FIND_GLUE_OK);
        // We return the result rrset only if the result code is
        // SUCCESS. We return empty if CNAME, DNAME, DELEGATION,
        // etc. are returned by the ZoneFinder.
        //
        // Note that in the case that the queried type itself is CNAME
        // or DNAME, then the finder will return SUCCESS.
        if (result->code == ZoneFinder::SUCCESS) {
            return (result->rrset);
        } else {
            return (ConstRRsetPtr());
        }
    } catch (const OutOfZone&) {
        // As RRsetCollection is an arbitrary set of RRsets, in case the
        // searched name is out of zone, we return nothing instead of
        // propagating the exception.
        return (ConstRRsetPtr());
    } catch (const DataSourceError& e) {
        isc_throw(RRsetCollectionError,
                  "ZoneFinder threw a DataSourceError: "
                      << e.getMessage().c_str());
    }
}

} // end of namespace datasrc
} // end of namespace isc
