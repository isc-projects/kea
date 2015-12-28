// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_iaaddr.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <sstream>

#include <stdint.h>
#include <arpa/inet.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6IAAddr::Option6IAAddr(uint16_t type, const isc::asiolink::IOAddress& addr,
                             uint32_t pref, uint32_t valid)
    :Option(V6, type), addr_(addr), preferred_(pref),
     valid_(valid) {
    setEncapsulatedSpace("dhcp6");
    if (!addr.isV6()) {
        isc_throw(isc::BadValue, addr_ << " is not an IPv6 address");
    }
}

Option6IAAddr::Option6IAAddr(uint32_t type, OptionBuffer::const_iterator begin,
                             OptionBuffer::const_iterator end)
    :Option(V6, type), addr_("::") {
    setEncapsulatedSpace("dhcp6");
    unpack(begin, end);
}

void Option6IAAddr::pack(isc::util::OutputBuffer& buf) {

    buf.writeUint16(type_);

    // len() returns complete option length. len field contains
    // length without 4-byte option header
    buf.writeUint16(len() - getHeaderLen());

    if (!addr_.isV6()) {
        isc_throw(isc::BadValue, addr_ << " is not an IPv6 address");
    }
    buf.writeData(&addr_.toBytes()[0], isc::asiolink::V6ADDRESS_LEN);

    buf.writeUint32(preferred_);
    buf.writeUint32(valid_);

    // parse suboption (there shouldn't be any for IAADDR)
    packOptions(buf);
}

void Option6IAAddr::unpack(OptionBuffer::const_iterator begin,
                      OptionBuffer::const_iterator end) {
    if ( distance(begin, end) < OPTION6_IAADDR_LEN) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    // 16 bytes: IPv6 address
    addr_ = IOAddress::fromBytes(AF_INET6, &(*begin));
    begin += V6ADDRESS_LEN;

    preferred_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);

    valid_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);

    unpackOptions(OptionBuffer(begin, end));
}

std::string Option6IAAddr::toText(int indent) {
    std::stringstream output;
    output << headerToText(indent, "IAADDR") << ": "
           << "address=" << addr_
           << ", preferred-lft=" << preferred_
           << ", valid-lft=" << valid_;

    output << suboptionsToText(indent + 2);
    return (output.str());
}

uint16_t Option6IAAddr::len() {

    uint16_t length = OPTION6_HDR_LEN + OPTION6_IAADDR_LEN;

    // length of all suboptions
    // TODO implement:
    // protected: unsigned short Option::lenHelper(int header_size);
    for (OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}

} // end of namespace isc::dhcp
} // end of namespace isc
