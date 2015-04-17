// Copyright (C) 2012-2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/mysql_connection.h>
#include <exceptions/exceptions.h>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

#include <time.h>


using namespace std;

namespace isc {
namespace dhcp {

Lease6Ptr
LeaseMgr::getLease6(Lease::Type type, const DUID& duid,
                    uint32_t iaid, SubnetID subnet_id) const {
    Lease6Collection col = getLeases6(type, duid, iaid, subnet_id);

    if (col.size() > 1) {
        isc_throw(MultipleRecords, "More than one lease found for type "
                  << static_cast<int>(type) << ", duid "
                  << duid.toText() << ", iaid " << iaid
                  << " and subnet-id " << subnet_id);
    }
    if (col.empty()) {
        return (Lease6Ptr());
    }
    return (*col.begin());
}

std::string
LeaseMgr::getDBVersion() {
    isc_throw(NotImplemented, "LeaseMgr::getDBVersion() called");
}

} // namespace isc::dhcp
} // namespace isc
