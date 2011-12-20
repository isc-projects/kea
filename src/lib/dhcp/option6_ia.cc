// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdint.h>
#include <arpa/inet.h>
#include <sstream>
#include "exceptions/exceptions.h"

#include "dhcp/libdhcp++.h"
#include "dhcp/option6_ia.h"
#include "dhcp/dhcp6.h"
#include "util/io_utilities.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

Option6IA::Option6IA(unsigned short type, unsigned int iaid)
    :Option(Option::V6, type), iaid_(iaid) {
}

Option6IA::Option6IA(unsigned short type,
                     const boost::shared_array<uint8_t>& buf,
                     unsigned int buf_len,
                     unsigned int offset,
                     unsigned int option_len)
    :Option(Option::V6, type) {
    unpack(buf, buf_len, offset, option_len);
}

unsigned int
Option6IA::pack(boost::shared_array<uint8_t>& buf,
                unsigned int buf_len,
                unsigned int offset) {
    if (offset + len() > buf_len) {
        isc_throw(OutOfRange, "Failed to pack IA option: len=" << len()
                  << ", buffer=" << buf_len << ": too small buffer.");
    }

    if (len() < 16 ) {
        isc_throw(OutOfRange, "Attempt to build malformed IA option: len="
                  << len() << " is too small (at least 16 is required).");
    }

    uint8_t* ptr = &buf[offset];

    ptr = writeUint16(type_, ptr);
    ptr = writeUint16(len() - OPTION6_HDR_LEN, ptr);
    offset += OPTION6_HDR_LEN;

    ptr = writeUint32(iaid_, ptr);
    ptr = writeUint32(t1_, ptr);
    ptr = writeUint32(t2_, ptr);
    offset += OPTION6_IA_LEN;

    offset = LibDHCP::packOptions6(buf, buf_len, offset, options_);
    return offset;
}

unsigned int
Option6IA::unpack(const boost::shared_array<uint8_t>& buf,
                  unsigned int buf_len,
                  unsigned int offset,
                  unsigned int parse_len) {
    if ( parse_len < OPTION6_IA_LEN || offset + OPTION6_IA_LEN > buf_len) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    iaid_ = readUint32(&buf[offset]);
    offset += sizeof(uint32_t);

    t1_ = readUint32(&buf[offset]);
    offset += sizeof(uint32_t);

    t2_ = readUint32(&buf[offset]);
    offset += sizeof(uint32_t);

    offset = LibDHCP::unpackOptions6(buf, buf_len, offset,
                                     parse_len - OPTION6_IA_LEN, options_);

    return (offset);
}

std::string Option6IA::toText(int indent /* = 0*/) {
    stringstream tmp;

    for (int i=0; i<indent; i++)
        tmp << " ";
    tmp << "type=" << type_;

    switch (type_) {
    case D6O_IA_NA:
        tmp << "(IA_NA)";
        break;
    case D6O_IA_PD:
        tmp << "(IA_PD)";
        break;
    default:
        tmp << "(unknown)";
    }
    tmp << " iaid=" << iaid_ << ", t1=" << t1_ << ", t2=" << t2_
        << " " << options_.size() << " sub-options:" << endl;

    for (OptionCollection::const_iterator opt=options_.begin();
         opt!=options_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
    }
    return tmp.str();
}

uint16_t Option6IA::len() {

    uint16_t length = OPTION6_HDR_LEN /*header (4)*/ +
        OPTION6_IA_LEN  /* option content (12) */;

    // length of all suboptions
    for (Option::OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}
