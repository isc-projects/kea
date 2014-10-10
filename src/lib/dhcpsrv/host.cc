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
#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

Host::Host(const uint8_t* identifier, const size_t identifier_len,
           const IdentifierType& identifier_type,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname)
    : hw_address_(), duid_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id), ipv4_reservation_(ipv4_reservation),
      hostname_(hostname), dhcp4_client_classes_(), dhcp6_client_classes_() {

    decodeIdentifier(identifier, identifier_len, identifier_type);
}

Host::Host(const std::string& identifier, const std::string& identifier_name,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname)
    : hw_address_(), duid_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id), ipv4_reservation_(ipv4_reservation),
      hostname_(hostname), dhcp4_client_classes_(), dhcp6_client_classes_() {

    decodeIdentifier(identifier, identifier_name);
}

void
Host::decodeIdentifier(const uint8_t* identifier, const size_t len,
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
Host::decodeIdentifier(const std::string& identifier, const std::string& name) {
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


} // end of namespace isc::dhcp
} // end of namespace isc
