// Copyright (C) 2011-2012,2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/io_address.h>
#include <dhcp/option4_addrlst.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <iomanip>
#include <sstream>

#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::util;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

Option4AddrLst::Option4AddrLst(uint8_t type)
    :Option(V4, type) {
}

Option4AddrLst::Option4AddrLst(uint8_t type, const AddressContainer& addrs)
    :Option(V4, type) {
    setAddresses(addrs);
    // don't set addrs_ directly. setAddresses() will do additional checks.
}


Option4AddrLst::Option4AddrLst(uint8_t type, OptionBufferConstIter first,
                               OptionBufferConstIter last)
    :Option(V4, type) {
    if ( (distance(first, last) % V4ADDRESS_LEN) ) {
        isc_throw(OutOfRange, "DHCPv4 Option4AddrLst " << type_
                  << " has invalid length=" << distance(first, last)
                  << ", must be divisible by 4.");
    }

    while (first != last) {
        const uint8_t* ptr = &(*first);
        addAddress(IOAddress(readUint32(ptr, distance(first, last))));
        first += V4ADDRESS_LEN;
    }
}

Option4AddrLst::Option4AddrLst(uint8_t type, const IOAddress& addr)
    :Option(V4, type) {
    setAddress(addr);
}

void
Option4AddrLst::pack(isc::util::OutputBuffer& buf) {

    if (addrs_.size() * V4ADDRESS_LEN > 255) {
        isc_throw(OutOfRange, "DHCPv4 Option4AddrLst " << type_ << " is too big."
                  << "At most 255 bytes are supported.");
        /// TODO Larger options can be stored as separate instances
        /// of DHCPv4 options. Clients MUST concatenate them.
        /// Fortunately, there are no such large options used today.
    }

    buf.writeUint8(type_);
    buf.writeUint8(len() - getHeaderLen());

    AddressContainer::const_iterator addr = addrs_.begin();

    while (addr != addrs_.end()) {
        buf.writeUint32(*addr);
        ++addr;
    }
}

void Option4AddrLst::setAddress(const isc::asiolink::IOAddress& addr) {
    if (!addr.isV4()) {
        isc_throw(BadValue, "Can't store non-IPv4 address in "
                  << "Option4AddrLst option");
    }
    addrs_.clear();
    addAddress(addr);
}

void Option4AddrLst::setAddresses(const AddressContainer& addrs) {

    // Do not copy it as a whole. addAddress() does sanity checks.
    // i.e. throw if someone tries to set IPv6 address.
    addrs_.clear();
    for (AddressContainer::const_iterator addr = addrs.begin();
         addr != addrs.end(); ++addr) {
        addAddress(*addr);
    }
}


void Option4AddrLst::addAddress(const isc::asiolink::IOAddress& addr) {
    if (!addr.isV4()) {
        isc_throw(BadValue, "Can't store non-IPv4 address in "
                  << "Option4AddrLst option");
    }
    addrs_.push_back(addr);
}

uint16_t Option4AddrLst::len() {

    // Returns length of the complete option (option header + data length)
    return (getHeaderLen() + addrs_.size() * V4ADDRESS_LEN);
}

std::string Option4AddrLst::toText(int indent) {
    std::stringstream output;
    output << headerToText(indent) << ":";

    for (AddressContainer::const_iterator addr = addrs_.begin();
         addr != addrs_.end(); ++addr) {
        output << " " << (*addr);
    }

    return (output.str());
}

} // end of isc::dhcp namespace
} // end of isc namespace
