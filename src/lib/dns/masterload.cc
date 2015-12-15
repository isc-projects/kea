// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

template <typename InputType>
void
loadHelper(InputType input, const Name& origin,
           const RRClass& zone_class, MasterLoadCallback callback)
{
    RRCollator rr_collator(boost::bind(callbackWrapper, _1,
                                       callback, &origin));
    MasterLoader loader(input, origin, zone_class,
                        MasterLoaderCallbacks::getNullCallbacks(),
                        rr_collator.getCallback());
    try {
        loader.load();
    } catch (const MasterLoaderError& ex) {
        isc_throw(MasterLoadError, ex.what());
    }
    rr_collator.flush();
}
}

void
masterLoad(const char* const filename, const Name& origin,
           const RRClass& zone_class, MasterLoadCallback callback)
{
    if ((filename == NULL) || (*filename == '\0')) {
        isc_throw(MasterLoadError, "Name of master file must not be null");
    }

    loadHelper<const char*>(filename, origin, zone_class, callback);
}

void
masterLoad(istream& input, const Name& origin, const RRClass& zone_class,
           MasterLoadCallback callback, const char*)
{
    loadHelper<istream&>(input, origin, zone_class, callback);
}

} // namespace dns
} // namespace isc
