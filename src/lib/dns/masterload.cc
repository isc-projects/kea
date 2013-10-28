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

#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cerrno>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/master_loader.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/rrcollator.h>

using namespace std;
using namespace boost;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
namespace {
void
callbackWrapper(const RRsetPtr& rrset, MasterLoadCallback callback,
                const Name* origin)
{
    // Origin related validation:
    //  - reject out-of-zone data
    //  - reject SOA whose owner is not at the top of zone
    const NameComparisonResult cmp_result =
        rrset->getName().compare(*origin);
    if (cmp_result.getRelation() != NameComparisonResult::EQUAL &&
        cmp_result.getRelation() != NameComparisonResult::SUBDOMAIN) {
        isc_throw(MasterLoadError, "Out-of-zone data for " << *origin
                  << "/" << rrset->getClass() << ": " << rrset->getName());
    }
    if (rrset->getType() == RRType::SOA() &&
        cmp_result.getRelation() != NameComparisonResult::EQUAL) {
        isc_throw(MasterLoadError, "SOA not at top of zone: "
                  << *rrset);
    }

    callback(rrset);
}
}

void
masterLoad(const char* const filename, const Name& origin,
           const RRClass& zone_class, MasterLoadCallback callback)
{
    if ((filename == NULL) || (*filename == '\0')) {
        isc_throw(MasterLoadError, "Name of master file must not be null");
    }

    RRCollator rr_collator(boost::bind(callbackWrapper, _1, callback, &origin));
    MasterLoader loader(filename, origin, zone_class,
                        MasterLoaderCallbacks::getNullCallbacks(),
                        rr_collator.getCallback());
    try {
        loader.load();
    } catch (const MasterLoaderError& ex) {
        isc_throw(MasterLoadError, ex.what());
    }
    rr_collator.flush();
}

void
masterLoad(istream& input, const Name& origin, const RRClass& zone_class,
           MasterLoadCallback callback, const char* source)
{
    RRCollator rr_collator(boost::bind(callbackWrapper, _1, callback, &origin));
    MasterLoader loader(input, origin, zone_class,
                        MasterLoaderCallbacks::getNullCallbacks(),
                        rr_collator.getCallback());
    if (source == NULL) {
        source = "<unknown>";
    }
    try {
        loader.load();
    } catch (const MasterLoaderError& ex) {
        isc_throw(MasterLoadError, ex.what());
    }
    rr_collator.flush();
}

} // namespace dns
} // namespace isc
