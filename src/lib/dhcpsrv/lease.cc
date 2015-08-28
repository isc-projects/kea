// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/lease.h>
#include <util/pointer_util.h>
#include <sstream>
#include <iostream>

using namespace isc::util;
using namespace std;

namespace isc {
namespace dhcp {

const uint32_t Lease::STATE_DEFAULT = 0x0;
const uint32_t Lease::STATE_DECLINED = 0x1;
const uint32_t Lease::STATE_EXPIRED_RECLAIMED = 0x2;

const unsigned int Lease::BASIC_STATES_NUM = 2;


Lease::Lease(const isc::asiolink::IOAddress& addr, uint32_t t1, uint32_t t2,
             uint32_t valid_lft, SubnetID subnet_id, time_t cltt,
             const bool fqdn_fwd, const bool fqdn_rev,
             const std::string& hostname, const HWAddrPtr& hwaddr)
    :addr_(addr), t1_(t1), t2_(t2), valid_lft_(valid_lft), cltt_(cltt),
     subnet_id_(subnet_id), fixed_(false), hostname_(hostname),
     fqdn_fwd_(fqdn_fwd), fqdn_rev_(fqdn_rev), hwaddr_(hwaddr),
     state_(STATE_DEFAULT) {
}


std::string
Lease::typeToText(Lease::Type type) {
   switch (type) {
   case Lease::TYPE_V4:
       return string("V4");
   case Lease::TYPE_NA:
       return string("IA_NA");
   case Lease::TYPE_TA:
       return string("IA_TA");
   case Lease::TYPE_PD:
       return string("IA_PD");
       break;
   default: {
       stringstream tmp;
       tmp << "unknown (" << type << ")";
       return (tmp.str());
   }
   }
}

std::string
Lease::basicStatesToText(const uint32_t state) {
    // Stream will hold comma separated list of states.
    std::ostringstream s;
    // Iterate over all defined states.
    for (int i = 0; i < BASIC_STATES_NUM; ++i) {
        // Test each bit of the lease state to see if it is set.
        uint32_t single_state = (state & (static_cast<uint32_t>(1) << i));
        // Only proceed if the bit is set.
        if (single_state > 0) {
            // Comma sign is applied only if any state has been found.
            if (static_cast<int>(s.tellp() > 0)) {
                s << ",";
            }
            // Check which bit is set and append state name.
            switch (single_state) {
            case STATE_DECLINED:
                s << "declined";
                break;

            case STATE_EXPIRED_RECLAIMED:
                s << "expired-reclaimed";
                break;

            default:
                // This shouldn't really happen.
                s << "unknown (" << i << ")";
            }
        }
    }

    return (s.tellp() > 0 ? s.str() : "default");
}

bool
Lease::expired() const {
    return (getExpirationTime() < time(NULL));
}

bool
Lease::stateExpiredReclaimed() const {
    return ((state_ & STATE_EXPIRED_RECLAIMED) != 0);
}

int64_t
Lease::getExpirationTime() const {
    return (static_cast<int64_t>(cltt_) + valid_lft_);
}

bool
Lease::hasIdenticalFqdn(const Lease& other) const {
    return (hostname_ == other.hostname_ &&
            fqdn_fwd_ == other.fqdn_fwd_ &&
            fqdn_rev_ == other.fqdn_rev_);
}

Lease4::Lease4(const Lease4& other)
    : Lease(other.addr_, other.t1_, other.t2_, other.valid_lft_,
            other.subnet_id_, other.cltt_, other.fqdn_fwd_,
            other.fqdn_rev_, other.hostname_, other.hwaddr_) {

    // Copy over fields derived from Lease.
    ext_ = other.ext_;
    comments_ = other.comments_;
    fixed_ = other.fixed_;
    state_ = other.state_;

    // Copy the hardware address if it is defined.
    if (other.hwaddr_) {
        hwaddr_.reset(new HWAddr(*other.hwaddr_));
    } else {
        hwaddr_.reset();
    }

    if (other.client_id_) {
        client_id_.reset(new ClientId(other.client_id_->getClientId()));

    } else {
        client_id_.reset();

    }
}

Lease4::Lease4(const isc::asiolink::IOAddress& address,
               const HWAddrPtr& hw_address,
               const ClientIdPtr& client_id,
               const uint32_t valid_lifetime,
               const uint32_t t1,
               const uint32_t t2,
               const time_t cltt,
               const SubnetID subnet_id,
               const bool fqdn_fwd,
               const bool fqdn_rev,
               const std::string& hostname)

    : Lease(address, t1, t2, valid_lifetime, subnet_id, cltt, fqdn_fwd,
            fqdn_rev, hostname, hw_address),
      ext_(0), client_id_(client_id) {
}

std::string
Lease4::statesToText(const uint32_t state) {
    return (Lease::basicStatesToText(state));
}

const std::vector<uint8_t>&
Lease4::getClientIdVector() const {
    if(!client_id_) {
        static std::vector<uint8_t> empty_vec;
        return (empty_vec);
    }

    return (client_id_->getClientId());
}

const std::vector<uint8_t>&
Lease::getHWAddrVector() const {
    if (!hwaddr_) {
        static std::vector<uint8_t> empty_vec;
        return (empty_vec);
    }
    return (hwaddr_->hwaddr_);
}

bool
Lease4::belongsToClient(const HWAddrPtr& hw_address,
                        const ClientIdPtr& client_id) const {
    // If client id matches, lease matches.
    if (equalValues(client_id, client_id_)) {
        return (true);

    } else if (!client_id || !client_id_) {
        // If client id is unspecified, use HW address.
        if (equalValues(hw_address, hwaddr_)) {
            return (true);
        }
    }

    return (false);
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
        state_ = other.state_;

        // Copy the hardware address if it is defined.
        if (other.hwaddr_) {
            hwaddr_.reset(new HWAddr(*other.hwaddr_));
        } else {
            hwaddr_.reset();
        }

        if (other.client_id_) {
            client_id_.reset(new ClientId(other.client_id_->getClientId()));
        } else {
            client_id_.reset();
        }
    }
    return (*this);
}

Lease6::Lease6(Type type, const isc::asiolink::IOAddress& addr,
               DuidPtr duid, uint32_t iaid, uint32_t preferred, uint32_t valid,
               uint32_t t1, uint32_t t2, SubnetID subnet_id,
               const HWAddrPtr& hwaddr, uint8_t prefixlen)
    : Lease(addr, t1, t2, valid, subnet_id, 0/*cltt*/, false, false, "", hwaddr),
      type_(type), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
      preferred_lft_(preferred) {
    if (!duid) {
        isc_throw(InvalidOperation, "DUID is mandatory for an IPv6 lease");
    }

    cltt_ = time(NULL);
}

Lease6::Lease6(Type type, const isc::asiolink::IOAddress& addr,
               DuidPtr duid, uint32_t iaid, uint32_t preferred, uint32_t valid,
               uint32_t t1, uint32_t t2, SubnetID subnet_id,
               const bool fqdn_fwd, const bool fqdn_rev,
               const std::string& hostname, const HWAddrPtr& hwaddr,
               uint8_t prefixlen)
    : Lease(addr, t1, t2, valid, subnet_id, 0/*cltt*/,
            fqdn_fwd, fqdn_rev, hostname, hwaddr),
      type_(type), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
      preferred_lft_(preferred) {
    if (!duid) {
        isc_throw(InvalidOperation, "DUID is mandatory for an IPv6 lease");
    }

    cltt_ = time(NULL);
}

Lease6::Lease6()
    : Lease(isc::asiolink::IOAddress("::"), 0, 0, 0, 0, 0, false, false, "",
            HWAddrPtr()), type_(TYPE_NA), prefixlen_(0), iaid_(0),
            duid_(DuidPtr()), preferred_lft_(0) {
}

std::string
Lease6::statesToText(const uint32_t state) {
    return (Lease::basicStatesToText(state));
}

const std::vector<uint8_t>&
Lease6::getDuidVector() const {
    if (!duid_) {
        static std::vector<uint8_t> empty_vec;
        return (empty_vec);
    }

    return (duid_->getDuid());
}

std::string
Lease6::toText() const {
    ostringstream stream;

    /// @todo: print out DUID
    stream << "Type:          " << typeToText(type_) << "("
           << static_cast<int>(type_) << ")\n";
    stream << "Address:       " << addr_ << "\n"
           << "Prefix length: " << static_cast<int>(prefixlen_) << "\n"
           << "IAID:          " << iaid_ << "\n"
           << "Pref life:     " << preferred_lft_ << "\n"
           << "Valid life:    " << valid_lft_ << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "Hardware addr: " << (hwaddr_?hwaddr_->toText(false):"(none)") << "\n"
           << "Subnet ID:     " << subnet_id_ << "\n"
           << "State:         " << statesToText(state_) << "\n";

    return (stream.str());
}

std::string
Lease4::toText() const {
    ostringstream stream;

    stream << "Address:       " << addr_ << "\n"
           << "Valid life:    " << valid_lft_ << "\n"
           << "T1:            " << t1_ << "\n"
           << "T2:            " << t2_ << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "Hardware addr: " << (hwaddr_ ? hwaddr_->toText(false) : "(none)") << "\n"
           << "Client id:     " << (client_id_ ? client_id_->toText() : "(none)") << "\n"
           << "Subnet ID:     " << subnet_id_ << "\n"
           << "State:         " << statesToText(state_) << "\n";

    return (stream.str());
}


bool
Lease4::operator==(const Lease4& other) const {
    return (nullOrEqualValues(hwaddr_, other.hwaddr_) &&
            nullOrEqualValues(client_id_, other.client_id_) &&
            addr_ == other.addr_ &&
            ext_ == other.ext_ &&
            subnet_id_ == other.subnet_id_ &&
            t1_ == other.t1_ &&
            t2_ == other.t2_ &&
            valid_lft_ == other.valid_lft_ &&
            cltt_ == other.cltt_ &&
            fixed_ == other.fixed_ &&
            hostname_ == other.hostname_ &&
            fqdn_fwd_ == other.fqdn_fwd_ &&
            fqdn_rev_ == other.fqdn_rev_ &&
            comments_ == other.comments_ &&
            state_ == other.state_);
}

bool
Lease6::operator==(const Lease6& other) const {
    return (nullOrEqualValues(duid_, other.duid_) &&
            nullOrEqualValues(hwaddr_, other.hwaddr_) &&
            addr_ == other.addr_ &&
            type_ == other.type_ &&
            prefixlen_ == other.prefixlen_ &&
            iaid_ == other.iaid_ &&
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
            comments_ == other.comments_ &&
            state_ == other.state_);
}

std::ostream&
operator<<(std::ostream& os, const Lease& lease) {
    os << lease.toText();
    return (os);
}

} // namespace isc::dhcp
} // namespace isc
