// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
}

Option6IAAddr::Option6IAAddr(uint32_t type, OptionBuffer::const_iterator begin,
                             OptionBuffer::const_iterator end)
    :Option(V6, type), addr_("::") {
    unpack(begin, end);
}

void Option6IAAddr::pack(isc::util::OutputBuffer& buf) {

    buf.writeUint16(type_);

    // len() returns complete option length. len field contains
    // length without 4-byte option header
    buf.writeUint16(len() - getHeaderLen());


    buf.writeData(addr_.getAddress().to_v6().to_bytes().data(),
                  isc::asiolink::V6ADDRESS_LEN);

    buf.writeUint32(preferred_);
    buf.writeUint32(valid_);

    // parse suboption (there shouldn't be any for IAADDR)
    LibDHCP::packOptions6(buf, options_);
}

void Option6IAAddr::unpack(OptionBuffer::const_iterator begin,
                      OptionBuffer::const_iterator end) {
    if ( distance(begin, end) < OPTION6_IAADDR_LEN) {
        isc_throw(OutOfRange, "Option " << type_ << " truncated");
    }

    // 16 bytes: IPv6 address
    addr_ = IOAddress::fromBytes(AF_INET6, &(*begin));
    begin += V6ADDRESS_LEN;

    preferred_ = readUint32( &(*begin) );
    begin += sizeof(uint32_t);

    valid_ = readUint32( &(*begin) );
    begin += sizeof(uint32_t);
    LibDHCP::unpackOptions6(OptionBuffer(begin, end), options_);
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

} // end of namespace isc::dhcp
} // end of namespace isc
