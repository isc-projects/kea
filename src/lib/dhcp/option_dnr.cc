// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option_dnr.h>

namespace isc {
namespace dhcp {

OptionDNR6::OptionDNR6(OptionBufferConstIter begin, OptionBufferConstIter end)
    : Option(V6, D6O_V6_DNR) {
    unpack(begin, end);
}

OptionPtr
OptionDNR6::clone() const {
    return Option::clone();
}

void
OptionDNR6::pack(util::OutputBuffer& buf, bool check) const {
    packHeader(buf, check);

    buf.writeUint16(service_priority_);
    // TBD
}

void
OptionDNR6::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    if (std::distance(begin, end) < getMinimalLength()) {
        isc_throw(OutOfRange, "parsed DHCPv6 Encrypted DNS Option ("
                              << D6O_V6_DNR << ") data truncated to"
                              " size " << std::distance(begin, end));
    }
    setData(begin, end);
    // First two octets of Option data is Service Priority - this is mandatory field.
    service_priority_ = isc::util::readUint16((&*begin), SERVICE_PRIORITY_SIZE);
    begin += sizeof(service_priority_);

    // Next comes two octets of ADN Length plus the ADN data itself (variable length).
    // This is Opaque Data Tuple so let's use this class to retrieve the ADN data.
    OpaqueDataTuple adn_tuple(OpaqueDataTuple::LENGTH_2_BYTES, begin, end);
    adn_length_ = adn_tuple.getLength();
    if (adn_length_ > 0) {
        // Let's try to extract ADN FQDN data
        isc::util::InputBuffer name_buf(&adn_tuple.getData(),
                                        adn_length_);
        try {
            adn_.reset(new isc::dns::Name(name_buf, true));
        } catch (const Exception&) {
            isc_throw(InvalidOptionDNR6DomainName, "failed to parse "
                                                    "fully qualified domain-name from wire format");
        }
    }
    begin += adn_tuple.getTotalLength();

    if (begin == end) {
        // ADN only mode, other fields are not included
        return;
    }
    if (std::distance(begin, end) < ADDR_LENGTH_SIZE) {
        isc_throw(OutOfRange, "truncated DHCPv6 Encrypted DNS Option (" << D6O_V6_DNR << ") - after"
                              " ADN field, there should be at least 2 bytes long Addr Length field");
    }
    addr_length_ = isc::util::readUint16((&*begin), ADDR_LENGTH_SIZE);
    // TBD
}

std::string
OptionDNR6::toText(int indent) const {
    return Option::toText(indent);
}

uint16_t
OptionDNR6::len() const {
    return Option::len();
}

OptionDNR4::OptionDNR4() : Option(V4, DHO_V4_DNR) {
}

OptionDNR4::OptionDNR4(OptionBufferConstIter begin, OptionBufferConstIter end)
    : Option(V4, DHO_V4_DNR) {
    unpack(begin, end);
}

OptionPtr
OptionDNR4::clone() const {
    return Option::clone();
}

void
OptionDNR4::pack(util::OutputBuffer& buf, bool check) const {
    Option::pack(buf, check);
}

void
OptionDNR4::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    Option::unpack(begin, end);
}

std::string
OptionDNR4::toText(int indent) const {
    return Option::toText(indent);
}

uint16_t
OptionDNR4::len() const {
    return Option::len();
}

}  // namespace dhcp
}  // namespace isc
