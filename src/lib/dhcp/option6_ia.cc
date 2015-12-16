// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_ia.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <arpa/inet.h>
#include <sstream>
#include <stdint.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option6IA::Option6IA(uint16_t type, uint32_t iaid)
    :Option(Option::V6, type), iaid_(iaid), t1_(0), t2_(0) {

    // IA_TA has different layout than IA_NA and IA_PD. We can't sue this class
    if (type == D6O_IA_TA) {
        isc_throw(BadValue, "Can't use Option6IA for IA_TA as it has "
                  "a different layout");
    }

    setEncapsulatedSpace("dhcp6");
}

Option6IA::Option6IA(uint16_t type, OptionBufferConstIter begin,
                     OptionBufferConstIter end)
    :Option(Option::V6, type) {

    // IA_TA has different layout than IA_NA and IA_PD. We can't use this class
    if (type == D6O_IA_TA) {
        isc_throw(BadValue, "Can't use Option6IA for IA_TA as it has "
                  "a different layout");
    }

    setEncapsulatedSpace("dhcp6");

    unpack(begin, end);
}

void Option6IA::pack(isc::util::OutputBuffer& buf) {
    buf.writeUint16(type_);
    buf.writeUint16(len() - OPTION6_HDR_LEN);
    buf.writeUint32(iaid_);
    buf.writeUint32(t1_);
    buf.writeUint32(t2_);

    packOptions(buf);
}

void Option6IA::unpack(OptionBufferConstIter begin,
                       OptionBufferConstIter end) {
    // IA_NA and IA_PD have 12 bytes content (iaid, t1, t2 fields)
    // followed by 0 or more sub-options.
    if (distance(begin, end) < OPTION6_IA_LEN) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }
    iaid_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);
    t1_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);

    t2_ = readUint32(&(*begin), distance(begin, end));
    begin += sizeof(uint32_t);

    unpackOptions(OptionBuffer(begin, end));
}

std::string Option6IA::toText(int indent) {
    stringstream output;

    switch(getType()) {
    case D6O_IA_NA:
        output << headerToText(indent, "IA_NA");
        break;
    case D6O_IA_PD:
        output << headerToText(indent, "IA_PD");
        break;
    default:
        output << headerToText(indent);
    }

    output << ": iaid=" << iaid_ << ", t1=" << t1_ << ", t2=" << t2_
           << suboptionsToText(indent + 2);

    return (output.str());
}

uint16_t Option6IA::len() {

    uint16_t length = OPTION6_HDR_LEN /*header (4)*/ +
        OPTION6_IA_LEN  /* option content (12) */;

    // length of all suboptions
    for (OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}

} // end of isc::dhcp namespace
} // end of isc namespace
