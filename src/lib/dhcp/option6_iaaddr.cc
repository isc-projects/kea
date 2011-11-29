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
#include "util/io_utilities.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

Option6IAAddr::Option6IAAddr(unsigned short type,
                             const isc::asiolink::IOAddress& addr,
                             unsigned int pref, unsigned int valid)
    :Option(V6, type), addr_(addr), preferred_(pref),
     valid_(valid) {
}

Option6IAAddr::Option6IAAddr(unsigned short type,
                             boost::shared_array<uint8_t> buf,
                             unsigned int buf_len, unsigned int offset,
                             unsigned int option_len)
    :Option(V6, type), addr_("::") {
    unpack(buf, buf_len, offset, option_len);
}

unsigned int
Option6IAAddr::pack(boost::shared_array<uint8_t>& buf,
                    unsigned int buf_len,
                    unsigned int offset) {
    if (len() > buf_len) {
        isc_throw(OutOfRange, "Failed to pack IA option: len=" << len()
                  << ", buffer=" << buf_len << ": too small buffer.");
    }

    uint8_t* ptr = &buf[offset];

    ptr = writeUint16(type_, ptr);

    // len() returns complete option length. len field contains
    // length without 4-byte option header
    ptr = writeUint16(len() - OPTION6_HDR_LEN, ptr);
    offset += OPTION6_HDR_LEN;

    memcpy(ptr, addr_.getAddress().to_v6().to_bytes().data(), 16);
    ptr += V6ADDRESS_LEN;

    ptr = writeUint32(preferred_, ptr);

    ptr = writeUint32(valid_, ptr);
    offset += OPTION6_IAADDR_LEN;

    // parse suboption (there shouldn't be any)
    offset = LibDHCP::packOptions6(buf, buf_len, offset, options_);
    return offset;
}

unsigned int
Option6IAAddr::unpack(const boost::shared_array<uint8_t>& buf,
                  unsigned int buf_len,
                  unsigned int offset,
                  unsigned int parse_len) {
    if ( parse_len < OPTION6_IAADDR_LEN || offset + OPTION6_IAADDR_LEN > buf_len) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    // 16 bytes: IPv6 address
    addr_ = IOAddress::from_bytes(AF_INET6, &buf[offset]);
    offset += V6ADDRESS_LEN;

    preferred_ = readUint32(&buf[offset]);
    offset += sizeof(uint32_t);

    valid_ = readUint32(&buf[offset]);
    offset += sizeof(uint32_t);
    offset = LibDHCP::unpackOptions6(buf, buf_len, offset,
                                     parse_len - 24, options_);

    return offset;
}

std::string Option6IAAddr::toText(int indent /* =0 */) {
    stringstream tmp;
    for (int i=0; i<indent; i++)
        tmp << " ";

    tmp << "type=" << type_ << "(IAADDR) addr=" << addr_.toText()
        << ", preferred-lft=" << preferred_  << ", valid-lft="
        << valid_ << endl;

    for (OptionCollection::const_iterator opt=options_.begin();
         opt!=options_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
    }
    return tmp.str();
}

uint16_t Option6IAAddr::len() {

    uint16_t length = OPTION6_HDR_LEN + OPTION6_IAADDR_LEN;

    // length of all suboptions
    // TODO implement:
    // protected: unsigned short Option::lenHelper(int header_size);
    for (Option::OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}
