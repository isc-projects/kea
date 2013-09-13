// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/lease_mgr.h>
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

Lease::Lease(const isc::asiolink::IOAddress& addr, uint32_t t1, uint32_t t2,
             uint32_t valid_lft, SubnetID subnet_id, time_t cltt,
             const bool fqdn_fwd, const bool fqdn_rev,
             const std::string& hostname)
    :addr_(addr), t1_(t1), t2_(t2), valid_lft_(valid_lft), cltt_(cltt),
     subnet_id_(subnet_id), fixed_(false), hostname_(hostname),
     fqdn_fwd_(fqdn_fwd), fqdn_rev_(fqdn_rev) {
}

Lease4::Lease4(const Lease4& other)
    : Lease(other.addr_, other.t1_, other.t2_, other.valid_lft_,
            other.subnet_id_, other.cltt_, other.fqdn_fwd_,
            other.fqdn_rev_, other.hostname_), ext_(other.ext_),
      hwaddr_(other.hwaddr_) {

    fixed_ = other.fixed_;
    comments_ = other.comments_;

    if (other.client_id_) {
        client_id_.reset(new ClientId(other.client_id_->getClientId()));

    } else {
        client_id_.reset();

    }
}

Lease4&
Lease4::operator=(const Lease4& other) {
    if (this != &other) {
        addr_ = other.addr_;
        t1_ = other.t1_;
        t2_ = other.t2_;
        valid_lft_ = other.valid_lft_;
        cltt_ = other.cltt_;
        subnet_id_ = other.subnet_id_;
        fixed_ = other.fixed_;
        hostname_ = other.hostname_;
        fqdn_fwd_ = other.fqdn_fwd_;
        fqdn_rev_ = other.fqdn_rev_;
        comments_ = other.comments_;
        ext_ = other.ext_;
        hwaddr_ = other.hwaddr_;

        if (other.client_id_) {
            client_id_.reset(new ClientId(other.client_id_->getClientId()));
        } else {
            client_id_.reset();
        }
    }
    return (*this);
}

Lease6::Lease6(LeaseType type, const isc::asiolink::IOAddress& addr,
               DuidPtr duid, uint32_t iaid, uint32_t preferred, uint32_t valid,
               uint32_t t1, uint32_t t2, SubnetID subnet_id, uint8_t prefixlen)
    : Lease(addr, t1, t2, valid, subnet_id, 0/*cltt*/, false, false, ""),
      type_(type), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
      preferred_lft_(preferred) {
    if (!duid) {
        isc_throw(InvalidOperation, "DUID must be specified for a lease");
    }

    cltt_ = time(NULL);
}

Lease6::Lease6(LeaseType type, const isc::asiolink::IOAddress& addr,
               DuidPtr duid, uint32_t iaid, uint32_t preferred, uint32_t valid,
               uint32_t t1, uint32_t t2, SubnetID subnet_id,
               const bool fqdn_fwd, const bool fqdn_rev,
               const std::string& hostname, uint8_t prefixlen)
    : Lease(addr, t1, t2, valid, subnet_id, 0/*cltt*/,
            fqdn_fwd, fqdn_rev, hostname),
      type_(type), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
      preferred_lft_(preferred) {
    if (!duid) {
        isc_throw(InvalidOperation, "DUID must be specified for a lease");
    }

    cltt_ = time(NULL);
}

bool Lease::expired() const {

    // Let's use int64 to avoid problems with negative/large uint32 values
    int64_t expire_time = cltt_ + valid_lft_;
    return (expire_time < time(NULL));
}


std::string LeaseMgr::getParameter(const std::string& name) const {
    ParameterMap::const_iterator param = parameters_.find(name);
    if (param == parameters_.end()) {
        isc_throw(BadValue, "Parameter not found");
    }
    return (param->second);
}

Lease6Ptr
LeaseMgr::getLease6(Lease6::LeaseType type, const DUID& duid,
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
Lease6::toText() const {
    ostringstream stream;

    stream << "Type:          " << static_cast<int>(type_) << " (";
    switch (type_) {
        case Lease6::LEASE_IA_NA:
            stream << "IA_NA)\n";
            break;
        case Lease6::LEASE_IA_TA:
            stream << "IA_TA)\n";
            break;
        case Lease6::LEASE_IA_PD:
            stream << "IA_PD)\n";
            break;
        default:
            stream << "unknown)\n";
    }
    stream << "Address:       " << addr_.toText() << "\n"
           << "Prefix length: " << static_cast<int>(prefixlen_) << "\n"
           << "IAID:          " << iaid_ << "\n"
           << "Pref life:     " << preferred_lft_ << "\n"
           << "Valid life:    " << valid_lft_ << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "Subnet ID:     " << subnet_id_ << "\n";

    return (stream.str());
}

std::string
Lease4::toText() const {
    ostringstream stream;

    stream << "Address:       " << addr_.toText() << "\n"
           << "Valid life:    " << valid_lft_ << "\n"
           << "T1:            " << t1_ << "\n"
           << "T2:            " << t2_ << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "Subnet ID:     " << subnet_id_ << "\n";

    return (stream.str());
}


bool
Lease4::operator==(const Lease4& other) const {
    if ( (client_id_ && !other.client_id_) ||
         (!client_id_ && other.client_id_) ) {
        // One lease has client-id, but the other doesn't
        return false;
    }

    if (client_id_ && other.client_id_ &&
        *client_id_ != *other.client_id_) {
        // Different client-ids
        return false;
    }

    return (
        addr_ == other.addr_ &&
        ext_ == other.ext_ &&
        hwaddr_ == other.hwaddr_ &&
        t1_ == other.t1_ &&
        t2_ == other.t2_ &&
        valid_lft_ == other.valid_lft_ &&
        cltt_ == other.cltt_ &&
        subnet_id_ == other.subnet_id_ &&
        fixed_ == other.fixed_ &&
        hostname_ == other.hostname_ &&
        fqdn_fwd_ == other.fqdn_fwd_ &&
        fqdn_rev_ == other.fqdn_rev_ &&
        comments_ == other.comments_
    );
}

bool
Lease6::operator==(const Lease6& other) const {
    return (
        addr_ == other.addr_ &&
        type_ == other.type_ &&
        prefixlen_ == other.prefixlen_ &&
        iaid_ == other.iaid_ &&
        *duid_ == *other.duid_ &&
        preferred_lft_ == other.preferred_lft_ &&
        valid_lft_ == other.valid_lft_ &&
        t1_ == other.t1_ &&
        t2_ == other.t2_ &&
        cltt_ == other.cltt_ &&
        subnet_id_ == other.subnet_id_ &&
        fixed_ == other.fixed_ &&
        hostname_ == other.hostname_ &&
        fqdn_fwd_ == other.fqdn_fwd_ &&
        fqdn_rev_ == other.fqdn_rev_ &&
        comments_ == other.comments_
    );
}

} // namespace isc::dhcp
} // namespace isc
