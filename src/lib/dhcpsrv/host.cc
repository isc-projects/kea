// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/host.h>
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
    : hw_address_(), duid_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id),
      ipv4_reservation_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      hostname_(hostname),
      dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes),
      credential_(""), tmp_state_(new TmpState) {

    // Initialize HWAddr or DUID
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
    : hw_address_(), duid_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id),
      ipv4_reservation_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      hostname_(hostname),
      dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes),
      credential_(""), tmp_state_(new TmpState) {

    // Initialize HWAddr or DUID
    setIdentifier(identifier, identifier_name);

    if (!ipv4_reservation.isV4Zero()) {
        // Validate and set IPv4 address reservation.
        setIPv4Reservation(ipv4_reservation);
    }
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

std::string
Host::getIdentifierAsText() const {
    std::string txt;
    if (hw_address_) {
        txt = "hwaddr=" + hw_address_->toText(false);
    } else {
        txt = "duid=";
        if (duid_) {
            txt += duid_->toText();
        } else {
            txt += "(none)";
        }
    }

    return (txt);

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

    // Add credential
    if (!credential_.empty()) {
        s << " credential=" << credential_;
    }

    // Add state (TODO)

    return (s.str());
}

} // end of namespace isc::dhcp
} // end of namespace isc
