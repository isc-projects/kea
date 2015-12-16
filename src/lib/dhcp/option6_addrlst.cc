// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <sstream>

#include <arpa/inet.h>
#include <stdint.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6AddrLst::Option6AddrLst(uint16_t type, const AddressContainer& addrs)
    :Option(V6, type), addrs_(addrs) {
}

Option6AddrLst::Option6AddrLst(uint16_t type, const isc::asiolink::IOAddress& addr)
    :Option(V6, type), addrs_(1,addr) {
}

Option6AddrLst::Option6AddrLst(uint16_t type, OptionBufferConstIter begin,
                               OptionBufferConstIter end)
    :Option(V6, type) {
    unpack(begin, end);
}

void
Option6AddrLst::setAddress(const isc::asiolink::IOAddress& addr) {
    if (!addr.isV6()) {
        isc_throw(BadValue, "Can't store non-IPv6 address in Option6AddrLst option");
    }

    addrs_.clear();
    addrs_.push_back(addr);
}

void
Option6AddrLst::setAddresses(const AddressContainer& addrs) {
    addrs_ = addrs;
}

void Option6AddrLst::pack(isc::util::OutputBuffer& buf) {

    buf.writeUint16(type_);

    // len() returns complete option length.
    // len field contains length without 4-byte option header
    buf.writeUint16(len() - getHeaderLen());

    for (AddressContainer::const_iterator addr=addrs_.begin();
         addr!=addrs_.end(); ++addr) {
        if (!addr->isV6()) {
            isc_throw(isc::BadValue, addr->toText()
                      << " is not an IPv6 address");
        }
        // If an address is IPv6 address it should have assumed
        // length of V6ADDRESS_LEN.
        buf.writeData(&addr->toBytes()[0], V6ADDRESS_LEN);
    }
}

void Option6AddrLst::unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end) {
    if ((distance(begin, end) % V6ADDRESS_LEN) != 0) {
        isc_throw(OutOfRange, "Option " << type_
                  << " malformed: len=" << distance(begin, end)
                  << " is not divisible by 16.");
    }
    while (begin != end) {
        addrs_.push_back(IOAddress::fromBytes(AF_INET6, &(*begin)));
        begin += V6ADDRESS_LEN;
    }
}

std::string Option6AddrLst::toText(int indent) {
    stringstream output;
    output << headerToText(indent) << ":";

    for (AddressContainer::const_iterator addr = addrs_.begin();
         addr != addrs_.end(); ++addr) {
        output << " " << *addr;
    }
    return (output.str());
}

uint16_t Option6AddrLst::len() {
    return (OPTION6_HDR_LEN + addrs_.size() * V6ADDRESS_LEN);
}

} // end of namespace isc::dhcp
} // end of namespace isc
