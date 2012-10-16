// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/mysql_lease_mgr.h>

namespace isc {
namespace dhcp {

MySqlLeaseMgr::MySqlLeaseMgr(const LeaseMgr::ParameterMap& parameters) 
    : LeaseMgr(parameters), major_(0), minor_(0) {
}

MySqlLeaseMgr::~MySqlLeaseMgr() {
}

bool
MySqlLeaseMgr::addLease(Lease4Ptr /* lease */) {
    return (false);
}

bool
MySqlLeaseMgr::addLease(Lease6Ptr /* lease */) {
    return (false);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(isc::asiolink::IOAddress /* addr */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(isc::asiolink::IOAddress /* addr */) const {
    return (Lease4Ptr());
}

Lease4Collection
MySqlLeaseMgr::getLease4(const HWAddr& /* hwaddr */) const {
    return (Lease4Collection());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const HWAddr& /* hwaddr */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease4Collection
MySqlLeaseMgr::getLease4(const ClientId& /* clientid */) const {
    return (Lease4Collection());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const ClientId& /* clientid */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease6Ptr
MySqlLeaseMgr::getLease6(isc::asiolink::IOAddress /* addr */) const {
    return (Lease6Ptr());
}

Lease6Collection
MySqlLeaseMgr::getLease6(const DUID& /* duid */, uint32_t /* iaid */) const {
    return (Lease6Collection());
}

Lease6Ptr
MySqlLeaseMgr::getLease6(const DUID& /* duid */, uint32_t /* iaid */,
                         SubnetID /* subnet_id */) const {
    return (Lease6Ptr());
}

void
MySqlLeaseMgr::updateLease4(Lease4Ptr /* lease4 */) {
}

void
MySqlLeaseMgr::updateLease6(Lease6Ptr /* lease6 */) {
}

bool
MySqlLeaseMgr::deleteLease4(uint32_t /* addr */) {
    return (false);
}

bool
MySqlLeaseMgr::deleteLease6(isc::asiolink::IOAddress /* addr */) {
    return (false);
}

std::string
MySqlLeaseMgr::getName() const {
    return (std::string(""));
}

std::string
MySqlLeaseMgr::getDescription() const {
    return (std::string(""));
}

std::pair<uint32_t, uint32_t>
MySqlLeaseMgr::getVersion() const {
    return (std::make_pair(major_, minor_));
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
