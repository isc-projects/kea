// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <sstream>

using namespace std;

namespace isc {
namespace dhcp {

Lease::Lease(const isc::asiolink::IOAddress& addr, uint32_t t1, uint32_t t2,
             uint32_t valid_lft, SubnetID subnet_id, time_t cltt,
             const bool fqdn_fwd, const bool fqdn_rev,
             const std::string& hostname, const HWAddrPtr& hwaddr)
    :addr_(addr), t1_(t1), t2_(t2), valid_lft_(valid_lft), cltt_(cltt),
     subnet_id_(subnet_id), fixed_(false), hostname_(hostname),
     fqdn_fwd_(fqdn_fwd), fqdn_rev_(fqdn_rev), hwaddr_(hwaddr) {
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

bool Lease::expired() const {

    // Let's use int64 to avoid problems with negative/large uint32 values
    int64_t expire_time = cltt_ + valid_lft_;
    return (expire_time < time(NULL));
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
            other.fqdn_rev_, other.hostname_, other.hwaddr_),
            ext_(other.ext_) {

    fixed_ = other.fixed_;
    comments_ = other.comments_;

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
Lease4::matches(const Lease4& other) const {
    if ((client_id_ && !other.client_id_) ||
        (!client_id_ && other.client_id_)) {
        // One lease has client-id, but the other doesn't
        return false;
    }

    if (client_id_ && other.client_id_ &&
        *client_id_ != *other.client_id_) {
        // Different client-ids
        return false;
    }

    // Note that hwaddr_ is now a poiner to the HWAddr structure.
    // We can't simply compare smart pointers, we need to compare the
    // actual objects they point to. If one of the leases had a hardware address
    // and the other doesn't, they clearly don't match.
    if ( (!hwaddr_ && other.hwaddr_) ||
         (hwaddr_ && !other.hwaddr_) ) {
        return (false);
    }

    // The lease is equal if addresses and extensions match and there is
    // either the same hardware address on both or neither have hardware address
    // specified.
    return (addr_ == other.addr_ &&
            ext_ == other.ext_ &&
            (!hwaddr_ ||
             *hwaddr_ == *other.hwaddr_) );
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
           << "Subnet ID:     " << subnet_id_ << "\n";

    return (stream.str());
}

std::string
Lease4::toText() const {
    ostringstream stream;

    /// @todo: print out client-id (if present)
    stream << "Address:       " << addr_ << "\n"
           << "Valid life:    " << valid_lft_ << "\n"
           << "T1:            " << t1_ << "\n"
           << "T2:            " << t2_ << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "Hardware addr: " << (hwaddr_?hwaddr_->toText(false):"(none)") << "\n"
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

    return (matches(other) &&
            subnet_id_ == other.subnet_id_ &&
            t1_ == other.t1_ &&
            t2_ == other.t2_ &&
            valid_lft_ == other.valid_lft_ &&
            cltt_ == other.cltt_ &&
            fixed_ == other.fixed_ &&
            hostname_ == other.hostname_ &&
            fqdn_fwd_ == other.fqdn_fwd_ &&
            fqdn_rev_ == other.fqdn_rev_ &&
            comments_ == other.comments_);
}

bool
Lease6::matches(const Lease6& other) const {

    // One lease has a hardware address, the other doesn't.
    if ( (!hwaddr_ && other.hwaddr_) ||
         (hwaddr_ && !other.hwaddr_) ) {
        return (false);
    }

    // Both leases have hardware address, but they are not equal.
    if (hwaddr_ && (*hwaddr_ != *other.hwaddr_)) {
        return (false);
    }

    return (addr_ == other.addr_ &&
            type_ == other.type_ &&
            prefixlen_ == other.prefixlen_ &&
            iaid_ == other.iaid_ &&
            *duid_ == *other.duid_);
}

bool
Lease6::operator==(const Lease6& other) const {
    return (matches(other) &&
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
            comments_ == other.comments_);
}

std::ostream&
operator<<(std::ostream& os, const Lease& lease) {
    os << lease.toText();
    return (os);
}

} // namespace isc::dhcp
} // namespace isc
