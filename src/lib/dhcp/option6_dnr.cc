// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option6_dnr.h>
#include <util/io.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6Dnr::Option6Dnr(OptionBufferConstIter begin,
                       OptionBufferConstIter end,
                       bool convenient_notation)
    : Option(V6, D6O_V6_DNR), DnrInstance(V6), convenient_notation_(convenient_notation) {
    unpack(begin, end);
}

OptionPtr
Option6Dnr::clone() const {
    return (cloneInternal<Option6Dnr>());
}

void
Option6Dnr::pack(util::OutputBuffer& buf, bool check) const {
    packHeader(buf, check);

    buf.writeUint16(service_priority_);
    buf.writeUint16(adn_length_);
    packAdn(buf);
    if (adn_only_mode_) {
        return;
    }

    buf.writeUint16(addr_length_);
    packAddresses(buf);
    packSvcParams(buf);
}

void
Option6Dnr::packAddresses(util::OutputBuffer& buf) const {
    for (auto const& address : ip_addresses_) {
        if (!address.isV6()) {
            isc_throw(isc::BadValue, getLogPrefix()
                                         << address.toText() << " is not an IPv6 address");
        }

        buf.writeData(&address.toBytes()[0], V6ADDRESS_LEN);
    }
}

void
Option6Dnr::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    if (convenient_notation_) {
        // parse convenient notation
        std::string config_txt = std::string(begin, end);
        parseDnrInstanceConfigData(config_txt);
    } else {
        if (std::distance(begin, end) < getMinimalLength()) {
            isc_throw(OutOfRange, getLogPrefix()
                                      << "data truncated to size " << std::distance(begin, end));
        }

        setData(begin, end);

        // First two octets of Option data is Service Priority - this is mandatory field.
        unpackServicePriority(begin);

        // Next come two octets of ADN Length plus the ADN data itself (variable length).
        // This is Opaque Data Tuple so let's use this class to retrieve the ADN data.
        unpackAdn(begin, end);

        if (begin == end) {
            // ADN only mode, other fields are not included.
            return;
        }

        adn_only_mode_ = false;

        unpackAddresses(begin, end);

        // SvcParams (variable length) field is last.
        unpackSvcParams(begin, end);
    }
}

std::string
Option6Dnr::toText(int indent) const {
    std::ostringstream stream;
    std::string in(indent, ' ');  // base indentation
    stream << in << "type=" << type_ << "(V6_DNR), "
           << "len=" << (len() - getHeaderLen()) << ", " << getDnrInstanceAsText();
    return (stream.str());
}

uint16_t
Option6Dnr::len() const {
    return (OPTION6_HDR_LEN + dnrInstanceLen());
}

void
Option6Dnr::unpackAddresses(OptionBufferConstIter& begin, OptionBufferConstIter end) {
    if (std::distance(begin, end) < getAddrLengthSize()) {
        isc_throw(OutOfRange, getLogPrefix() << "after"
                                                " ADN field, there should be at least "
                                                "2 bytes long Addr Length field");
    }

    // Next come two octets of Addr Length.
    addr_length_ = isc::util::readUint16(&(*begin), getAddrLengthSize());
    begin += getAddrLengthSize();
    // It MUST be a multiple of 16.
    if ((addr_length_ % V6ADDRESS_LEN) != 0) {
        isc_throw(OutOfRange, getLogPrefix()
                                  << "Addr Len=" << addr_length_ << " is not divisible by 16");
    }

    // As per RFC9463 3.1.8:
    // If additional data is supplied (i.e. not ADN only mode),
    // the option includes at least one valid IP address.
    if (addr_length_ == 0) {
        isc_throw(OutOfRange, getLogPrefix()
                                  << "Addr Len=" << addr_length_
                                  << " but it must contain at least one valid IP address");
    }

    // Check if IPv6 Address(es) field is not truncated.
    if (std::distance(begin, end) < addr_length_) {
        isc_throw(OutOfRange, getLogPrefix() << "Addr Len=" << addr_length_
                                             << " but IPv6 address(es) are truncated to len="
                                             << std::distance(begin, end));
    }

    // Let's unpack the ipv6-address(es).
    auto addr_end = begin + addr_length_;
    while (begin != addr_end) {
        try {
            addIpAddress(IOAddress::fromBytes(AF_INET6, &(*begin)));
        } catch (const Exception& ex) {
            isc_throw(BadValue, getLogPrefix() << "failed to parse IPv6 address"
                                               << " - " << ex.what());
        }

        begin += V6ADDRESS_LEN;
    }
}

}  // namespace dhcp
}  // namespace isc
