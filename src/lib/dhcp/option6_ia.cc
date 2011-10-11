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

#include "libdhcp.h"
#include "option6_ia.h"
#include "dhcp6.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;

Option6IA::Option6IA(Universe u, unsigned short type, unsigned int iaid)
    :Option(u, type), iaid_(iaid) {

}


Option6IA::Option6IA(Universe u, unsigned short type,
                   boost::shared_array<uint8_t> buf,
                   unsigned int buf_len,
                   unsigned int offset,
                   unsigned int option_len)
    :Option(u, type) {
    unpack(buf, buf_len, offset, option_len);
}

unsigned int
Option6IA::pack(boost::shared_array<uint8_t> buf,
                unsigned int buf_len,
                unsigned int offset) {
    if (offset + len() > buf_len) {
        isc_throw(OutOfRange, "Failed to pack IA option: len=" << len()
                  << ", buffer=" << buf_len << ": too small buffer.");
    }

    uint8_t* ptr = &buf[offset];
    *(uint16_t*)ptr = htons(type_);
    ptr += 2;
    *(uint16_t*)ptr = htons(len() - 4); // len() returns complete option length
    // len field contains length without 4-byte option header
    ptr += 2;

    *(uint32_t*)ptr = htonl(iaid_);
    ptr += 4;

    *(uint32_t*)ptr = htonl(t1_);
    ptr += 4;

    *(uint32_t*)ptr = htonl(t2_);
    ptr += 4;

    offset = LibDHCP::packOptions6(buf, buf_len, offset+16, optionLst_);
    return offset;
}

unsigned int
Option6IA::unpack(boost::shared_array<uint8_t> buf,
                  unsigned int buf_len,
                  unsigned int offset,
                  unsigned int parse_len) {
    if (parse_len<12 || offset+12>buf_len) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }
    iaid_ = ntohl(*(uint32_t*)&buf[offset]);
    offset +=4;
    t1_ = ntohl(*(uint32_t*)&buf[offset]);
    offset +=4;
    t2_ = ntohl(*(uint32_t*)&buf[offset]);
    offset +=4;
    offset = LibDHCP::unpackOptions6(buf, buf_len, offset,
                                     parse_len - 12, optionLst_);

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
        << " " << optionLst_.size() << " sub-options:" << endl;

    for (Option6Lst::const_iterator opt=optionLst_.begin();
         opt!=optionLst_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
    }
    return tmp.str();
}

unsigned short Option6IA::len() {

    unsigned short length = 4/*header*/ + 12 /* option content */; // header

    // length of all suboptions
    for (Option::Option6Lst::iterator it = optionLst_.begin();
         it != optionLst_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}
