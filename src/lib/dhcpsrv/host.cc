// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/host.h>
#include <util/strutil.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

IPv6Resrv::IPv6Resrv(const asiolink::IOAddress& prefix,
                     const uint8_t prefix_len)
    : prefix_(asiolink::IOAddress("::")), prefix_len_(128) {
    // Validate and set the actual values.
    set(prefix, prefix_len);
}

void
IPv6Resrv::set(const asiolink::IOAddress& prefix, const uint8_t prefix_len) {
    if (!prefix.isV6() || prefix.isV6Multicast()) {
        isc_throw(isc::BadValue, "invalid prefix '" << prefix
                  << " for new IPv6 reservation");

    } else if (prefix_len > 128) {
        isc_throw(isc::BadValue, "invalid prefix length '"
                  << static_cast<int>(prefix_len)
                  << "' for new IPv6 reservation");
    }

    prefix_ = prefix;
    prefix_len_ = prefix_len;
}

bool
IPv6Resrv::operator==(const IPv6Resrv& other) const {
    return (prefix_ == other.prefix_ &&
            prefix_len_ == other.prefix_len_);
}

bool
IPv6Resrv::operator!=(const IPv6Resrv& other) const {
    return (!operator==(other));
}

Host::Host(const uint8_t* identifier, const size_t identifier_len,
           const IdentifierType& identifier_type,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname,
           const std::string& dhcp4_client_classes,
           const std::string& dhcp6_client_classes)
    : hw_address_(), duid_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id), ipv4_reservation_(ipv4_reservation),
       hostname_(hostname), dhcp4_client_classes_(dhcp4_client_classes),
       dhcp6_client_classes_(dhcp6_client_classes) {

    // Initialize HWAddr or DUID
    setIdentifier(identifier, identifier_len, identifier_type);
}

Host::Host(const std::string& identifier, const std::string& identifier_name,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname,
           const std::string& dhcp4_client_classes,
           const std::string& dhcp6_client_classes)
    : hw_address_(), duid_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id), ipv4_reservation_(ipv4_reservation),
      hostname_(hostname), dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes) {

    // Initialize HWAddr or DUID
    setIdentifier(identifier, identifier_name);
}

const std::vector<uint8_t>&
Host::getIdentifier() const {
    if (hw_address_) {
        return (hw_address_->hwaddr_);

    } else if (duid_) {
        return (duid_->getDuid());

    }
    static std::vector<uint8_t> empty_vector;
    return (empty_vector);
}

Host::IdentifierType
Host::getIdentifierType() const {
    if (hw_address_) {
        return (IDENT_HWADDR);
    }
    return (IDENT_DUID);
}

void
Host::setIdentifier(const uint8_t* identifier, const size_t len,
                    const IdentifierType& type) {
    switch (type) {
    case IDENT_HWADDR:
        hw_address_ = HWAddrPtr(new HWAddr(identifier, len, HTYPE_ETHER));
        duid_.reset();
        break;
    case IDENT_DUID:
        duid_ = DuidPtr(new DUID(identifier, len));
        hw_address_.reset();
        break;
    default:
        isc_throw(isc::BadValue, "invalid client identifier type '"
                  << static_cast<int>(type) << "' when creating host "
                  " instance");
    }
}

void
Host::setIdentifier(const std::string& identifier, const std::string& name) {
    if (name == "hw-address") {
        hw_address_ = HWAddrPtr(new HWAddr(HWAddr::fromText(identifier)));
        duid_.reset();
    } else if (name == "duid") {
        duid_ = DuidPtr(new DUID(DUID::fromText(identifier)));
        hw_address_.reset();
    } else {
        isc_throw(isc::BadValue, "invalid client identifier type '"
                  << name << "' when creating host instance");
    }
}

void
Host::addReservation(const IPv6Resrv& reservation) {
    ipv6_reservations_.insert(IPv6ResrvTuple(reservation.getType(),
                                             reservation));
}

IPv6ResrvRange
Host::getIPv6Reservations(const IPv6Resrv::Type& type) const {
    return (ipv6_reservations_.equal_range(type));
}

void
Host::addClientClassInternal(ClientClasses& classes,
                             const std::string& class_name) {
    std::string trimmed = util::str::trim(class_name);
    if (!class_name.empty()) {
        classes.insert(ClientClass(class_name));
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
