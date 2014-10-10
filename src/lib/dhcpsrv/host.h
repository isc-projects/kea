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

#ifndef HOST_H
#define HOST_H

#include <asiolink/io_address.h>
#include <dhcp/classify.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/subnet_id.h>
#include <list>
#include <map>
#include <string>
#include <utility>

namespace isc {
namespace dhcp {

class IPv6Resrv {
public:

    enum Type {
        TYPE_NA,
        TYPE_PD
    };

    IPv6Resrv(const asiolink::IOAddress& address,
              const uint8_t prefix_len = 128)
        : address_(address), prefix_len_(prefix_len) {
    }

    const asiolink::IOAddress& getAddress() const {
        return (address_);
    }

    uint8_t getPrefixLen() const {
        return (prefix_len_);
    }

    Type getType() const {
        return (prefix_len_ == 128 ? TYPE_NA : TYPE_PD);
    }

    void set(const asiolink::IOAddress& address, const uint8_t prefix_len) {
        address_ = address;
        prefix_len_ = prefix_len;
    }

private:
    asiolink::IOAddress address_;
    uint8_t prefix_len_;

};

/// @brief Collection of IPv6 reservations for the host.
typedef std::multimap<IPv6Resrv::Type, IPv6Resrv> IPv6ResrvCollection;
typedef IPv6ResrvCollection::iterator IPv6ResrvIterator;
typedef std::pair<IPv6ResrvIterator, IPv6ResrvIterator> IPv6ResrvRange;

class Host {
public:

    enum IdentifierType {
        IDENT_HWADDR,
        IDENT_DUID
    };

    Host(const uint8_t* identifier, const size_t identifier_len,
         const IdentifierType& identifier_type,
         const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
         const asiolink::IOAddress& ipv4_reservation,
         const std::string& hostname = "");

    Host(const std::string& identifier, const std::string& identifier_name,
         const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
         const asiolink::IOAddress& ipv4_reservation,
         const std::string& hostname = "");

    void addReservation(const IPv6Resrv& reservation);

    void setIdentifier(const uint8_t* identifier, const size_t identifier_len,
                       const IdentifierType& identifier_type);

    void setIdentifier(const std::string& identifier, const std::string& name);

    HWAddrPtr getHWAddress() const {
        return (hw_address_);
    }

    DuidPtr getDuid() const {
        return (duid_);
    }

    SubnetID getIPv4SubnetID() const {
        return (ipv4_subnet_id_);
    }

    SubnetID getIPv6SubnetID() const {
        return (ipv6_subnet_id_);
    }

    const asiolink::IOAddress& getIPv4Reservation() const {
        return (ipv4_reservation_);
    }

    IPv6ResrvRange getIPv6Reservations(const IPv6Resrv& type) const;

    const std::string& getHostname() const {
        return (hostname_);
    }

    const ClientClasses& getClientClasses4() const {
        return (dhcp4_client_classes_);
    }

    const ClientClasses& getClientClasses6() const {
        return (dhcp6_client_classes_);
    }

private:

    void decodeIdentifier(const uint8_t* identifier, const size_t len,
                          const IdentifierType& type);

    void decodeIdentifier(const std::string& identifier,
                          const std::string& name);

    HWAddrPtr hw_address_;
    DuidPtr duid_;
    SubnetID ipv4_subnet_id_;
    SubnetID ipv6_subnet_id_;
    asiolink::IOAddress ipv4_reservation_;
    IPv6ResrvCollection ipv6_reservations_;
    std::string hostname_;
    ClientClasses dhcp4_client_classes_;
    ClientClasses dhcp6_client_classes_;
};

}
}

#endif // HOST_H
