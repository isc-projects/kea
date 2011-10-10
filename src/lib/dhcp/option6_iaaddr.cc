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

#include "dhcp/libdhcp.h"
#include "dhcp/option6_iaaddr.h"
#include "dhcp/dhcp6.h"
#include "asiolink/io_address.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

Option6IAAddr::Option6IAAddr(unsigned short type,
                             isc::asiolink::IOAddress addr,
                             unsigned int pref,
                             unsigned int valid)
    :Option(V6, type), addr_(addr), preferred_(pref),
     valid_(valid) {
}

Option6IAAddr::Option6IAAddr(unsigned short type,
                             boost::shared_array<char> buf,
                             unsigned int buf_len,
                             unsigned int offset,
                             unsigned int option_len)
    :Option(V6, type), addr_(IOAddress("::")) {
    unpack(buf, buf_len, offset, option_len);
}

unsigned int
Option6IAAddr::pack(boost::shared_array<char> buf,
                    unsigned int buf_len,
                    unsigned int offset) {
    if (len() > buf_len) {
        isc_throw(OutOfRange, "Failed to pack IA option: len=" << len()
                  << ", buffer=" << buf_len << ": too small buffer.");
    }

    *(uint16_t*)&buf[offset] = htons(type_);
    offset += 2;
    *(uint16_t*)&buf[offset] = htons(len()-4); // len() returns complete option
    // length. len field contains length without 4-byte option header
    offset += 2;

    memcpy(&buf[offset], addr_.getAddress().to_v6().to_bytes().data(), 16);
    offset += 16;

    *(uint32_t*)&buf[offset] = htonl(preferred_);
    offset += 4;
    *(uint32_t*)&buf[offset] = htonl(valid_);
    offset += 4;

    // parse suboption (there shouldn't be any)
    offset = LibDHCP::packOptions6(buf, buf_len, offset, optionLst_);
    return offset;
}

unsigned int
Option6IAAddr::unpack(boost::shared_array<char> buf,
                  unsigned int buf_len,
                  unsigned int offset,
                  unsigned int parse_len) {
    if (parse_len<24 || offset+24>buf_len) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    // 16 bytes: IPv6 address
    /// TODO Implement fromBytes() method in IOAddress
    char addr_str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &buf[offset], addr_str,INET6_ADDRSTRLEN);
    addr_ = IOAddress(string(addr_str));
    offset += 16;

    preferred_ = ntohl(*(uint32_t*)&buf[offset]);
    offset +=4;

    valid_ = ntohl(*(uint32_t*)&buf[offset]);
    offset +=4;
    offset = LibDHCP::unpackOptions6(buf, buf_len, offset,
                                     parse_len - 24, optionLst_);

    return offset;
}

std::string Option6IAAddr::toText(int indent /* =0 */) {
    stringstream tmp;
    for (int i=0; i<indent; i++)
        tmp << " ";

    tmp << "type=" << type_ << "(IAADDR) addr=" << addr_.toText()
        << ", preferred-lft=" << preferred_  << ", valid-lft="
        << valid_ << endl;

    for (Option6Lst::const_iterator opt=optionLst_.begin();
         opt!=optionLst_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
    }
    return tmp.str();
}

unsigned short Option6IAAddr::len() {

    unsigned short length = 4/*header*/ + 24 /* content */; // header

    // length of all suboptions
    // TODO implement:
    // protected: unsigned short Option::lenHelper(int header_size);

    for (Option::Option6Lst::iterator it = optionLst_.begin();
         it != optionLst_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}
