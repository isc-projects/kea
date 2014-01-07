// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_iaprefix.h>
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

Option6IAPrefix::Option6IAPrefix(uint16_t type, const isc::asiolink::IOAddress& prefix,
                                 uint8_t prefix_len, uint32_t pref, uint32_t valid)
    :Option6IAAddr(type, prefix, pref, valid), prefix_len_(prefix_len) {
    setEncapsulatedSpace("dhcp6");
    // Option6IAAddr will check if prefix is IPv6 and will throw if it is not
    if (prefix_len > 128) {
        isc_throw(BadValue, prefix_len << " is not a valid prefix length. "
                  << "Allowed range is 0..128");
    }
}

Option6IAPrefix::Option6IAPrefix(uint32_t type, OptionBuffer::const_iterator begin,
                             OptionBuffer::const_iterator end)
    :Option6IAAddr(type, begin, end) {
    setEncapsulatedSpace("dhcp6");
    unpack(begin, end);
}

void Option6IAPrefix::pack(isc::util::OutputBuffer& buf) {
    if (!addr_.isV6()) {
        isc_throw(isc::BadValue, addr_ << " is not an IPv6 address");
    }

    buf.writeUint16(type_);

    // len() returns complete option length. len field contains
    // length without 4-byte option header
    buf.writeUint16(len() - getHeaderLen());

    buf.writeUint32(preferred_);
    buf.writeUint32(valid_);
    buf.writeUint8(prefix_len_);

    buf.writeData(&addr_.toBytes()[0], isc::asiolink::V6ADDRESS_LEN);

    // store encapsulated options (the only defined so far is PD_EXCLUDE)
    packOptions(buf);
}

void Option6IAPrefix::unpack(OptionBuffer::const_iterator begin,
                      OptionBuffer::const_iterator end) {
    if ( distance(begin, end) < OPTION6_IAPREFIX_LEN) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    preferred_ = readUint32( &(*begin) );
    begin += sizeof(uint32_t);

    valid_ = readUint32( &(*begin) );
    begin += sizeof(uint32_t);

    prefix_len_ = *begin;
    begin += sizeof(uint8_t);

    // 16 bytes: IPv6 address
    addr_ = IOAddress::fromBytes(AF_INET6, &(*begin));
    begin += V6ADDRESS_LEN;

    // unpack encapsulated options (the only defined so far is PD_EXCLUDE)
    unpackOptions(OptionBuffer(begin, end));
}

std::string Option6IAPrefix::toText(int indent /* =0 */) {
    stringstream tmp;
    for (int i=0; i<indent; i++)
        tmp << " ";

    tmp << "type=" << type_ << "(IAPREFIX) prefix=" << addr_.toText() << "/"
        << prefix_len_ << ", preferred-lft=" << preferred_ << ", valid-lft="
        << valid_ << endl;

    for (OptionCollection::const_iterator opt=options_.begin();
         opt!=options_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent + 2);
    }
    return tmp.str();
}

uint16_t Option6IAPrefix::len() {

    uint16_t length = OPTION6_HDR_LEN + OPTION6_IAPREFIX_LEN;

    // length of all suboptions
    for (OptionCollection::const_iterator it = options_.begin();
         it != options_.end(); ++it) {
        length += (*it).second->len();
    }
    return (length);
}

} // end of namespace isc::dhcp
} // end of namespace isc
