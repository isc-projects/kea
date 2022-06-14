// Copyright (C) 2012-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/lease.h>
#include <util/pointer_util.h>
#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <sstream>
#include <iostream>


using namespace isc::util;
using namespace isc::data;
using namespace std;

namespace isc {
namespace dhcp {

const uint32_t Lease::STATE_DEFAULT = 0x0;
const uint32_t Lease::STATE_DECLINED = 0x1;
const uint32_t Lease::STATE_EXPIRED_RECLAIMED = 0x2;

std::string
Lease::lifetimeToText(uint32_t lifetime) {
    ostringstream repr;
    if (lifetime == INFINITY_LFT) {
        repr << "infinity";
    } else {
        repr << lifetime;
    }
    return repr.str();
}

Lease::Lease(const isc::asiolink::IOAddress& addr,
             uint32_t valid_lft, SubnetID subnet_id, time_t cltt,
             const bool fqdn_fwd, const bool fqdn_rev,
             const std::string& hostname, const HWAddrPtr& hwaddr)
    : addr_(addr), valid_lft_(valid_lft), current_valid_lft_(valid_lft),
      reuseable_valid_lft_(0),
      cltt_(cltt), current_cltt_(cltt), subnet_id_(subnet_id),
      hostname_(boost::algorithm::to_lower_copy(hostname)), fqdn_fwd_(fqdn_fwd),
      fqdn_rev_(fqdn_rev), hwaddr_(hwaddr), state_(STATE_DEFAULT) {
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

Lease::Type
Lease::textToType(const std::string& text) {
    if (text == "V4") {
        return (TYPE_V4);

    } else  if (text == "IA_NA") {
        return (TYPE_NA);

    } else if (text == "IA_TA") {
        return (TYPE_TA);

    } else if (text == "IA_PD") {
        return (TYPE_PD);
    }

    isc_throw(BadValue, "unsupported lease type " << text);
}

std::string
Lease::basicStatesToText(const uint32_t state) {
    switch (state) {
    case STATE_DEFAULT:
        return ("default");
    case STATE_DECLINED:
        return ("declined");
    case STATE_EXPIRED_RECLAIMED:
        return ("expired-reclaimed");
    default:
        // The default case will be handled further on
        ;
    }
    std::ostringstream s;
    s << "unknown (" << state << ")";
    return s.str();
}

bool
Lease::expired() const {
    return ((valid_lft_ != INFINITY_LFT) && (getExpirationTime() < time(NULL)));
}

bool
Lease::stateExpiredReclaimed() const {
    return (state_ == STATE_EXPIRED_RECLAIMED);
}

bool
Lease::stateDeclined() const {
    return (state_ == STATE_DECLINED);
}

int64_t
Lease::getExpirationTime() const {
    return (static_cast<int64_t>(cltt_) + valid_lft_);
}

bool
Lease::hasIdenticalFqdn(const Lease& other) const {
    return (boost::algorithm::iequals(hostname_, other.hostname_) &&
            fqdn_fwd_ == other.fqdn_fwd_ &&
            fqdn_rev_ == other.fqdn_rev_);
}

void
Lease::fromElementCommon(const LeasePtr& lease, const data::ConstElementPtr& element) {
    if (!element) {
        isc_throw(BadValue, "parsed lease data is null");
    }

    if (element->getType() != Element::map) {
        isc_throw(BadValue, "parsed lease data is not a JSON map");
    }


    if (!lease) {
        isc_throw(Unexpected, "pointer to parsed lease is null");
    }

    // IP address.
    ConstElementPtr ip_address = element->get("ip-address");
    if (!ip_address || (ip_address->getType() != Element::string)) {
        isc_throw(BadValue, "ip-address not present in the parsed lease"
                  " or it is not a string");
    }

    boost::scoped_ptr<asiolink::IOAddress> io_address;
    try {
        io_address.reset(new asiolink::IOAddress(ip_address->stringValue()));

    } catch (const std::exception& ex) {
        isc_throw(BadValue, "invalid IP address " << ip_address->stringValue()
                  << " in the parsed lease");
    }

    lease->addr_ = *io_address;

    // Subnet identifier.
    ConstElementPtr subnet_id = element->get("subnet-id");
    if (!subnet_id || (subnet_id->getType() != Element::integer)) {
        isc_throw(BadValue, "subnet-id not present in the parsed lease"
                  " or it is not a number");
    }

    if (subnet_id->intValue() <= 0) {
        isc_throw(BadValue, "subnet-id " << subnet_id->intValue() << " is not"
                  << " a positive integer");
    } else if (subnet_id->intValue() > numeric_limits<uint32_t>::max()) {
        isc_throw(BadValue, "subnet-id " << subnet_id->intValue() << " is not"
                  << " a 32 bit unsigned integer");
    }

    lease->subnet_id_ = SubnetID(subnet_id->intValue());

    // Hardware address.
    ConstElementPtr hw_address = element->get("hw-address");
    if (hw_address) {
        if (hw_address->getType() != Element::string) {
            isc_throw(BadValue, "hw-address is not a string in the parsed lease");

        }

        try {
            HWAddr parsed_hw_address = HWAddr::fromText(hw_address->stringValue());
            lease->hwaddr_.reset(new HWAddr(parsed_hw_address.hwaddr_, HTYPE_ETHER));

        } catch (const std::exception& ex) {
            isc_throw(BadValue, "invalid hardware address "
                      << hw_address->stringValue() << " in the parsed lease");
        }
    }

    // cltt
    ConstElementPtr cltt = element->get("cltt");
    if (!cltt || (cltt->getType() != Element::integer)) {
        isc_throw(BadValue, "cltt is not present in the parsed lease"
                  " or it is not a number");
    }

    if (cltt->intValue() <= 0) {
        isc_throw(BadValue, "cltt " << cltt->intValue() << " is not a"
                  " positive integer in the parsed lease");
    }

    lease->cltt_ = static_cast<time_t>(cltt->intValue());

    // valid lifetime
    ConstElementPtr valid_lifetime = element->get("valid-lft");
    if (!valid_lifetime || (valid_lifetime->getType() != Element::integer)) {
        isc_throw(BadValue, "valid-lft is not present in the parsed lease"
                  " or it is not a number");
    }

    if (valid_lifetime->intValue() < 0) {
        isc_throw(BadValue, "valid-lft " << valid_lifetime->intValue()
                  << " is negative in the parsed lease");
    }

    lease->valid_lft_ = valid_lifetime->intValue();

    // fqdn-fwd
    ConstElementPtr fqdn_fwd = element->get("fqdn-fwd");
    if (!fqdn_fwd || fqdn_fwd->getType() != Element::boolean) {
        isc_throw(BadValue, "fqdn-fwd is not present in the parsed lease"
                  " or it is not a boolean value");
    }

    lease->fqdn_fwd_ = fqdn_fwd->boolValue();

    // fqdn-fwd
    ConstElementPtr fqdn_rev = element->get("fqdn-rev");
    if (!fqdn_rev || (fqdn_rev->getType() != Element::boolean)) {
        isc_throw(BadValue, "fqdn-rev is not present in the parsed lease"
                  " or it is not a boolean value");
    }

    lease->fqdn_rev_ = fqdn_rev->boolValue();

    // hostname
    ConstElementPtr hostname = element->get("hostname");
    if (!hostname || (hostname->getType() != Element::string)) {
        isc_throw(BadValue, "hostname is not present in the parsed lease"
                  " or it is not a string value");
    }

    lease->hostname_ = hostname->stringValue();
    boost::algorithm::to_lower(lease->hostname_);

    // state
    ConstElementPtr state = element->get("state");
    if (!state || (state->getType() != Element::integer)) {
        isc_throw(BadValue, "state is not present in the parsed lease"
                  " or it is not a number");
    }

    if ((state->intValue() < 0) || (state->intValue() > Lease::STATE_EXPIRED_RECLAIMED)) {
        isc_throw(BadValue, "state " << state->intValue()
                  << " must be in range [0.."
                  << Lease::STATE_EXPIRED_RECLAIMED << "]");
    }

    lease->state_ = state->intValue();

    // user context
    ConstElementPtr ctx = element->get("user-context");
    if (ctx) {
        if (ctx->getType() != Element::map) {
            isc_throw(BadValue, "user context is not a map");
        }
        lease->setContext(ctx);
    }

    lease->updateCurrentExpirationTime();
}

void
Lease::updateCurrentExpirationTime() {
    Lease::syncCurrentExpirationTime(*this, *this);
}

void
Lease::syncCurrentExpirationTime(const Lease& from, Lease& to) {
    to.current_cltt_ = from.cltt_;
    to.current_valid_lft_ = from.valid_lft_;
}

Lease4::Lease4(const Lease4& other)
    : Lease(other.addr_, other.valid_lft_,
            other.subnet_id_, other.cltt_, other.fqdn_fwd_,
            other.fqdn_rev_, other.hostname_, other.hwaddr_) {

    // Copy over fields derived from Lease.
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

    if (other.getContext()) {
        setContext(other.getContext());
    }
}

Lease4::Lease4(const isc::asiolink::IOAddress& address,
               const HWAddrPtr& hw_address,
               const ClientIdPtr& client_id,
               const uint32_t valid_lifetime,
               const time_t cltt,
               const SubnetID subnet_id,
               const bool fqdn_fwd,
               const bool fqdn_rev,
               const std::string& hostname)

    : Lease(address, valid_lifetime, subnet_id, cltt, fqdn_fwd,
            fqdn_rev, hostname, hw_address),
      client_id_(client_id) {
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

void
Lease4::decline(uint32_t probation_period) {
    hwaddr_.reset(new HWAddr());
    client_id_.reset();
    cltt_ = time(NULL);
    hostname_ = string("");
    fqdn_fwd_ = false;
    fqdn_rev_ = false;
    state_ = STATE_DECLINED;
    valid_lft_ = probation_period;
}

Lease4&
Lease4::operator=(const Lease4& other) {
    if (this != &other) {
        addr_ = other.addr_;
        valid_lft_ = other.valid_lft_;
        current_valid_lft_ = other.current_valid_lft_;
        reuseable_valid_lft_ = other.reuseable_valid_lft_;
        cltt_ = other.cltt_;
        current_cltt_ = other.current_cltt_;
        subnet_id_ = other.subnet_id_;
        hostname_ = other.hostname_;
        fqdn_fwd_ = other.fqdn_fwd_;
        fqdn_rev_ = other.fqdn_rev_;
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

        if (other.getContext()) {
            setContext(other.getContext());
        }
    }
    return (*this);
}

isc::data::ElementPtr
Lease4::toElement() const {
    // Prepare the map
    ElementPtr map = Element::createMap();
    contextToElement(map);
    map->set("ip-address", Element::create(addr_.toText()));
    map->set("subnet-id", Element::create(static_cast<long int>(subnet_id_)));
    map->set("hw-address", Element::create(hwaddr_->toText(false)));

    if (client_id_) {
        map->set("client-id", Element::create(client_id_->toText()));
    }

    map->set("cltt", Element::create(cltt_));
    map->set("valid-lft", Element::create(static_cast<long int>(valid_lft_)));

    map->set("fqdn-fwd", Element::create(fqdn_fwd_));
    map->set("fqdn-rev", Element::create(fqdn_rev_));
    map->set("hostname", Element::create(hostname_));

    map->set("state", Element::create(static_cast<int>(state_)));

    return (map);
}

Lease4Ptr
Lease4::fromElement(const ConstElementPtr& element) {
    Lease4Ptr lease(new Lease4());

    // Extract common lease properties into the lease.
    fromElementCommon(boost::dynamic_pointer_cast<Lease>(lease), element);

    // Validate ip-address, which must be an IPv4 address.
    if (!lease->addr_.isV4()) {
        isc_throw(BadValue, "address " << lease->addr_ << " it not an IPv4 address");
    }

    // Make sure the hw-addres is present.
    if (!lease->hwaddr_) {
        isc_throw(BadValue, "hw-address not present in the parsed lease");
    }


    // Client identifier is IPv4 specific.
    ConstElementPtr client_id = element->get("client-id");
    if (client_id) {
        if (client_id->getType() != Element::string) {
            isc_throw(BadValue, "client identifier is not a string in the"
                      " parsed lease");
        }

        try {
            lease->client_id_ = ClientId::fromText(client_id->stringValue());

        } catch (const std::exception& ex) {
            isc_throw(BadValue, "invalid client identifier "
                      << client_id->stringValue() << " in the parsed lease");
        }
    }

    return (lease);
}

Lease6::Lease6(Lease::Type type, const isc::asiolink::IOAddress& addr,
               DuidPtr duid, uint32_t iaid, uint32_t preferred, uint32_t valid,
               SubnetID subnet_id, const HWAddrPtr& hwaddr, uint8_t prefixlen)
    : Lease(addr, valid, subnet_id, 0/*cltt*/, false, false, "", hwaddr),
      type_(type), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
      preferred_lft_(preferred), reuseable_preferred_lft_(0) {
    if (!duid) {
        isc_throw(InvalidOperation, "DUID is mandatory for an IPv6 lease");
    }

    cltt_ = time(NULL);
    current_cltt_ = cltt_;
}

Lease6::Lease6(Lease::Type type, const isc::asiolink::IOAddress& addr,
               DuidPtr duid, uint32_t iaid, uint32_t preferred, uint32_t valid,
               SubnetID subnet_id, const bool fqdn_fwd, const bool fqdn_rev,
               const std::string& hostname, const HWAddrPtr& hwaddr,
               uint8_t prefixlen)
    : Lease(addr, valid, subnet_id, 0/*cltt*/,
            fqdn_fwd, fqdn_rev, hostname, hwaddr),
      type_(type), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
      preferred_lft_(preferred), reuseable_preferred_lft_(0) {
    if (!duid) {
        isc_throw(InvalidOperation, "DUID is mandatory for an IPv6 lease");
    }

    cltt_ = time(NULL);
    current_cltt_ = cltt_;
}

Lease6::Lease6()
    : Lease(isc::asiolink::IOAddress("::"), 0, 0, 0, false, false, "",
            HWAddrPtr()), type_(TYPE_NA), prefixlen_(0), iaid_(0),
            duid_(DuidPtr()), preferred_lft_(0), reuseable_preferred_lft_(0) {
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

void
Lease6::decline(uint32_t probation_period) {
    hwaddr_.reset();
    duid_.reset(new DUID(DUID::EMPTY()));
    preferred_lft_ = 0;
    valid_lft_ = probation_period;
    cltt_ = time(NULL);
    hostname_ = string("");
    fqdn_fwd_ = false;
    fqdn_rev_ = false;
    state_ = Lease::STATE_DECLINED;
}

std::string
Lease6::toText() const {
    ostringstream stream;

    /// @todo: print out DUID
    stream << "Type:          " << typeToText(type_) << "("
           << static_cast<int>(type_) << ")\n"
           << "Address:       " << addr_ << "\n"
           << "Prefix length: " << static_cast<int>(prefixlen_) << "\n"
           << "IAID:          " << iaid_ << "\n"
           << "Pref life:     " << lifetimeToText(preferred_lft_) << "\n"
           << "Valid life:    " << lifetimeToText(valid_lft_) << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "DUID:          " << (duid_?duid_->toText():"(none)") << "\n"
           << "Hardware addr: " << (hwaddr_?hwaddr_->toText(false):"(none)") << "\n"
           << "Subnet ID:     " << subnet_id_ << "\n"
           << "State:         " << statesToText(state_) << "\n";

    if (getContext()) {
        stream << "User context:  " << getContext()->str() << "\n";
    }

    return (stream.str());
}

std::string
Lease4::toText() const {
    ostringstream stream;

    stream << "Address:       " << addr_ << "\n"
           << "Valid life:    " << lifetimeToText(valid_lft_) << "\n"
           << "Cltt:          " << cltt_ << "\n"
           << "Hardware addr: " << (hwaddr_ ? hwaddr_->toText(false) : "(none)") << "\n"
           << "Client id:     " << (client_id_ ? client_id_->toText() : "(none)") << "\n"
           << "Subnet ID:     " << subnet_id_ << "\n"
           << "State:         " << statesToText(state_) << "\n";

    if (getContext()) {
        stream << "User context:  " << getContext()->str() << "\n";
    }

    return (stream.str());
}


bool
Lease4::operator==(const Lease4& other) const {
    return (nullOrEqualValues(hwaddr_, other.hwaddr_) &&
            nullOrEqualValues(client_id_, other.client_id_) &&
            addr_ == other.addr_ &&
            subnet_id_ == other.subnet_id_ &&
            valid_lft_ == other.valid_lft_ &&
            current_valid_lft_ == other.current_valid_lft_ &&
            reuseable_valid_lft_ == other.reuseable_valid_lft_ &&
            cltt_ == other.cltt_ &&
            current_cltt_ == other.current_cltt_ &&
            hostname_ == other.hostname_ &&
            fqdn_fwd_ == other.fqdn_fwd_ &&
            fqdn_rev_ == other.fqdn_rev_ &&
            state_ == other.state_ &&
            nullOrEqualValues(getContext(), other.getContext()));
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
            reuseable_preferred_lft_ == other.reuseable_preferred_lft_ &&
            valid_lft_ == other.valid_lft_ &&
            current_valid_lft_ == other.current_valid_lft_ &&
            reuseable_valid_lft_ == other.reuseable_valid_lft_ &&
            cltt_ == other.cltt_ &&
            current_cltt_ == other.current_cltt_ &&
            subnet_id_ == other.subnet_id_ &&
            hostname_ == other.hostname_ &&
            fqdn_fwd_ == other.fqdn_fwd_ &&
            fqdn_rev_ == other.fqdn_rev_ &&
            state_ == other.state_ &&
            nullOrEqualValues(getContext(), other.getContext()));
}

isc::data::ElementPtr
Lease6::toElement() const {
    // Prepare the map
    ElementPtr map = Element::createMap();
    contextToElement(map);
    map->set("ip-address", Element::create(addr_.toText()));
    map->set("type", Element::create(typeToText(type_)));
    if (type_ == Lease::TYPE_PD) {
        map->set("prefix-len", Element::create(prefixlen_));
    }
    map->set("iaid", Element::create(static_cast<long int>(iaid_)));
    map->set("duid", Element::create(duid_->toText()));
    map->set("subnet-id", Element::create(static_cast<long int>(subnet_id_)));

    map->set("cltt", Element::create(cltt_));
    map->set("preferred-lft", Element::create(static_cast<long int>(preferred_lft_)));
    map->set("valid-lft", Element::create(static_cast<long int>(valid_lft_)));

    map->set("fqdn-fwd", Element::create(fqdn_fwd_));
    map->set("fqdn-rev", Element::create(fqdn_rev_));
    map->set("hostname", Element::create(hostname_));

    if (hwaddr_) {
        map->set("hw-address", Element::create(hwaddr_->toText(false)));
    }

    map->set("state", Element::create(static_cast<long int>(state_)));

    return (map);
}

Lease6Ptr
Lease6::fromElement(const data::ConstElementPtr& element) {
    Lease6Ptr lease(new Lease6());

    // Extract common lease properties into the lease.
    fromElementCommon(boost::dynamic_pointer_cast<Lease>(lease), element);

    // Validate ip-address, which must be an IPv6 address.
    if (!lease->addr_.isV6()) {
        isc_throw(BadValue, "address " << lease->addr_ << " it not an IPv6 address");
    }

    // lease type
    ConstElementPtr lease_type = element->get("type");
    if (!lease_type || (lease_type->getType() != Element::string)) {
        isc_throw(BadValue, "type is not present in the parsed lease"
                  " or it is not a string value");
    }

    lease->type_ = textToType(lease_type->stringValue());

    // prefix length
    ConstElementPtr prefix_len = element->get("prefix-len");
    if (lease->type_ == Lease::TYPE_PD) {
        if (!prefix_len || (prefix_len->getType() != Element::integer)) {
            isc_throw(BadValue, "prefix-len is not present in the parsed lease"
                      " or it is not a number");
        }

        if ((prefix_len->intValue() < 1) || (prefix_len->intValue() > 128)) {
            isc_throw(BadValue, "prefix-len " << prefix_len->intValue()
                      << " must be in range of [1..128]");
        }

        lease->prefixlen_ = static_cast<uint8_t>(prefix_len->intValue());
    }

    // IAID
    ConstElementPtr iaid = element->get("iaid");
    if (!iaid || (iaid->getType() != Element::integer)) {
        isc_throw(BadValue, "iaid is not present in the parsed lease"
                  " or it is not a number");
    }

    if (iaid->intValue() < 0) {
        isc_throw(BadValue, "iaid " << iaid->intValue() << " must not be negative");
    }

    lease->iaid_ = static_cast<uint32_t>(iaid->intValue());

    // DUID
    ConstElementPtr duid = element->get("duid");
    if (!duid || (duid->getType() != Element::string)) {
        isc_throw(BadValue, "duid not present in the parsed lease"
                  " or it is not a string");
    }

    try {
        DUID parsed_duid = DUID::fromText(duid->stringValue());
        lease->duid_.reset(new DUID(parsed_duid.getDuid()));

    } catch (const std::exception& ex) {
        isc_throw(BadValue, "invalid DUID "
                  << duid->stringValue() << " in the parsed lease");
    }

    // preferred lifetime
    ConstElementPtr preferred_lft = element->get("preferred-lft");
    if (!preferred_lft || (preferred_lft->getType() != Element::integer)) {
        isc_throw(BadValue, "preferred-lft is not present in the parsed lease"
                  " or is not a number");
    }

    if (preferred_lft->intValue() < 0) {
        isc_throw(BadValue, "preferred-lft " << preferred_lft->intValue()
                  << " must not be negative");
    }

    lease->preferred_lft_ = static_cast<uint32_t>(preferred_lft->intValue());

    return (lease);
}

std::ostream&
operator<<(std::ostream& os, const Lease& lease) {
    os << lease.toText();
    return (os);
}

} // namespace isc::dhcp
} // namespace isc
