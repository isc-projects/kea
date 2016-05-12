// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/host.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <exceptions/exceptions.h>
#include <sstream>

namespace isc {
namespace dhcp {

IPv6Resrv::IPv6Resrv(const Type& type,
                     const asiolink::IOAddress& prefix,
                     const uint8_t prefix_len)
    : type_(type), prefix_(asiolink::IOAddress("::")), prefix_len_(128) {
    // Validate and set the actual values.
    set(type, prefix, prefix_len);
}

void
IPv6Resrv::set(const Type& type, const asiolink::IOAddress& prefix,
               const uint8_t prefix_len) {
    if (!prefix.isV6() || prefix.isV6Multicast()) {
        isc_throw(isc::BadValue, "invalid prefix '" << prefix
                  << "' for new IPv6 reservation");

    } else if (prefix_len > 128) {
        isc_throw(isc::BadValue, "invalid prefix length '"
                  << static_cast<int>(prefix_len)
                  << "' for new IPv6 reservation");

    } else if ((type == TYPE_NA) && (prefix_len != 128)) {
        isc_throw(isc::BadValue, "invalid prefix length '"
                  << static_cast<int>(prefix_len)
                  << "' for reserved IPv6 address, expected 128");
    }

    type_ = type;
    prefix_ = prefix;
    prefix_len_ = prefix_len;
}

std::string
IPv6Resrv::toText() const {
    std::ostringstream s;
    s << prefix_;
    // For PD, append prefix length.
    if (getType() == TYPE_PD) {
        s << "/" << static_cast<int>(prefix_len_);
    }
    return (s.str());
}

bool
IPv6Resrv::operator==(const IPv6Resrv& other) const {
    return (type_ == other.type_ &&
            prefix_ == other.prefix_ &&
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
    : identifier_type_(identifier_type),
      identifier_value_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id),
      ipv4_reservation_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      hostname_(hostname), dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes), host_id_(0),
      cfg_option4_(new CfgOption()), cfg_option6_(new CfgOption()) {

    // Initialize host identifier.
    setIdentifier(identifier, identifier_len, identifier_type);

    if (!ipv4_reservation.isV4Zero()) {
        // Validate and set IPv4 address reservation.
        setIPv4Reservation(ipv4_reservation);
    }
}

Host::Host(const std::string& identifier, const std::string& identifier_name,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname,
           const std::string& dhcp4_client_classes,
           const std::string& dhcp6_client_classes)
    : identifier_type_(IDENT_HWADDR),
      identifier_value_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id),
      ipv4_reservation_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      hostname_(hostname), dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes), host_id_(0),
      cfg_option4_(new CfgOption()), cfg_option6_(new CfgOption()) {

    // Initialize host identifier.
    setIdentifier(identifier, identifier_name);

    if (!ipv4_reservation.isV4Zero()) {
        // Validate and set IPv4 address reservation.
        setIPv4Reservation(ipv4_reservation);
    }
}

const std::vector<uint8_t>&
Host::getIdentifier() const {
    return (identifier_value_);
}

Host::IdentifierType
Host::getIdentifierType() const {
    return (identifier_type_);
}

Host::IdentifierType
Host::getIdentifierType(const std::string& identifier_name) {
    if (identifier_name == "hw-address") {
        return (IDENT_HWADDR);

    } else if (identifier_name == "duid") {
        return (IDENT_DUID);

    } else if (identifier_name == "circuit-id") {
        return (IDENT_CIRCUIT_ID);

    } else {
        isc_throw(isc::BadValue, "invalid client identifier type '"
                  << identifier_name << "'");
    }
}

HWAddrPtr
Host::getHWAddress() const {
    return ((identifier_type_ == IDENT_HWADDR) ?
            HWAddrPtr(new HWAddr(identifier_value_, HTYPE_ETHER)) : HWAddrPtr());
}

DuidPtr
Host::getDuid() const {
    return ((identifier_type_ == IDENT_DUID) ?
            DuidPtr(new DUID(identifier_value_)) : DuidPtr());
}


std::string
Host::getIdentifierAsText() const {
    return (getIdentifierAsText(identifier_type_, &identifier_value_[0],
                                identifier_value_.size()));
}

std::string
Host::getIdentifierAsText(const IdentifierType& type, const uint8_t* value,
                          const size_t length) {
    // Convert identifier into <type>=<value> form.
    std::ostringstream s;
    switch (type) {
    case IDENT_HWADDR:
        s << "hwaddr";
        break;
    case IDENT_DUID:
        s << "duid";
        break;
    case IDENT_CIRCUIT_ID:
        s << "circuit-id";
        break;
    default:
        // This should never happen actually, unless we add new identifier
        // and forget to add a case for it above.
        s << "(invalid-type)";
    }
    std::vector<uint8_t> vec(value, value + length);
    s << "=" << (length > 0 ? util::encode::encodeHex(vec) : "(null)");
    return (s.str());
}

std::string
Host::getIdentifierName(const IdentifierType& type) {
    switch (type) {
    case Host::IDENT_HWADDR:
        return ("hw-address");

    case Host::IDENT_DUID:
        return ("duid");

    case Host::IDENT_CIRCUIT_ID:
        return ("circuit-id");

    default:
        ;
    }
    return ("(unknown)");
}


void
Host::setIdentifier(const uint8_t* identifier, const size_t len,
                    const IdentifierType& type) {
    if (len < 1) {
        isc_throw(BadValue, "invalid client identifier length 0");
    }

    identifier_type_ = type;
    identifier_value_.assign(identifier, identifier + len);
}

void
Host::setIdentifier(const std::string& identifier, const std::string& name) {
    // Empty identifier is not allowed.
    if (identifier.empty()) {
        isc_throw(isc::BadValue, "empty host identifier used");
    }

    // Set identifier type.
    identifier_type_ = getIdentifierType(name);

    // Idetifier value can either be specified as string of hexadecimal
    // digits or a string in quotes. The latter is copied to a vector excluding
    // quote characters.

    // Try to convert the values in quotes into a vector of ASCII codes.
    // If the identifier lacks opening and closing quote, this will return
    // an empty value, in which case we'll try to decode it as a string of
    // hexadecimal digits.
    try {
        std::vector<uint8_t> binary = util::str::quotedStringToBinary(identifier);
        if (binary.empty()) {
            util::str::decodeFormattedHexString(identifier, binary);
        }
        // Successfully decoded the identifier, so let's use it.
        identifier_value_.swap(binary);

    } catch (...) {
        // The string doesn't match any known pattern, so we have to
        // report an error at this point.
        isc_throw(isc::BadValue, "invalid host identifier value '"
                      << identifier << "'");
    }
}

void
Host::setIPv4Reservation(const asiolink::IOAddress& address) {
    if (!address.isV4()) {
        isc_throw(isc::BadValue, "address '" << address << "' is not a valid"
                  " IPv4 address");
    } else if (address.isV4Zero() || address.isV4Bcast()) {
        isc_throw(isc::BadValue, "must not make reservation for the '"
                  << address << "' address");
    }
    ipv4_reservation_ = address;
}

void
Host::removeIPv4Reservation() {
    ipv4_reservation_ = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
}

void
Host::addReservation(const IPv6Resrv& reservation) {
    // Check if it is not duplicating existing reservation.
    if (hasReservation(reservation)) {
        isc_throw(isc::InvalidOperation, "failed on attempt to add a duplicated"
                  " host reservation for " << reservation.toText());
    }
    // Add it.
    ipv6_reservations_.insert(IPv6ResrvTuple(reservation.getType(),
                                             reservation));
}

IPv6ResrvRange
Host::getIPv6Reservations(const IPv6Resrv::Type& type) const {
    return (ipv6_reservations_.equal_range(type));
}

IPv6ResrvRange
Host::getIPv6Reservations() const {
    return (IPv6ResrvRange(ipv6_reservations_.begin(),
                           ipv6_reservations_.end()));
}

bool
Host::hasIPv6Reservation() const {
    return (!ipv6_reservations_.empty());
}

bool
Host::hasReservation(const IPv6Resrv& reservation) const {
    IPv6ResrvRange reservations = getIPv6Reservations(reservation.getType());
    if (std::distance(reservations.first, reservations.second) > 0) {
        for (IPv6ResrvIterator it = reservations.first;
             it != reservations.second; ++it) {
            if (it->second == reservation) {
                return (true);
            }
        }
    }

    // No matching reservations found.
    return (false);
}

void
Host::addClientClass4(const std::string& class_name) {
    addClientClassInternal(dhcp4_client_classes_, class_name);
}

void
Host::addClientClass6(const std::string& class_name) {
    addClientClassInternal(dhcp6_client_classes_, class_name);
}

void
Host::addClientClassInternal(ClientClasses& classes,
                             const std::string& class_name) {
    std::string trimmed = util::str::trim(class_name);
    if (!trimmed.empty()) {
        classes.insert(ClientClass(trimmed));
    }
}

std::string
Host::toText() const {
    std::ostringstream s;

    // Add HW address or DUID.
    s << getIdentifierAsText();

    // Add IPv4 subnet id if exists (non-zero).
    if (ipv4_subnet_id_) {
        s << " ipv4_subnet_id=" << ipv4_subnet_id_;
    }

    // Add IPv6 subnet id if exists (non-zero).
    if (ipv6_subnet_id_) {
        s << " ipv6_subnet_id=" << ipv6_subnet_id_;
    }

    // Add hostname.
    s << " hostname=" << (hostname_.empty() ? "(empty)" : hostname_);

    // Add IPv4 reservation.
    s << " ipv4_reservation=" << (ipv4_reservation_.isV4Zero() ? "(no)" :
                                  ipv4_reservation_.toText());

    if (ipv6_reservations_.empty()) {
        s << " ipv6_reservations=(none)";

    } else {
        // Add all IPv6 reservations.
        for (IPv6ResrvIterator resrv = ipv6_reservations_.begin();
             resrv != ipv6_reservations_.end(); ++resrv) {
            s << " ipv6_reservation"
              << std::distance(ipv6_reservations_.begin(), resrv)
              << "=" << resrv->second.toText();
        }
    }

    // Add DHCPv4 client classes.
    for (ClientClasses::const_iterator cclass = dhcp4_client_classes_.begin();
         cclass != dhcp4_client_classes_.end(); ++cclass) {
        s << " dhcp4_class"
          << std::distance(dhcp4_client_classes_.begin(), cclass)
          << "=" << *cclass;
    }

    // Add DHCPv6 client classes.
    for (ClientClasses::const_iterator cclass = dhcp6_client_classes_.begin();
         cclass != dhcp6_client_classes_.end(); ++cclass) {
        s << " dhcp6_class"
          << std::distance(dhcp6_client_classes_.begin(), cclass)
          << "=" << *cclass;
    }

    return (s.str());
}

} // end of namespace isc::dhcp
} // end of namespace isc
