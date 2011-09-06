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

#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sstream>
#include <iomanip>
#include <boost/shared_array.hpp>
#include "exceptions/exceptions.h"

#include "option.h"
#include "libdhcp.h"

using namespace std;
using namespace isc::dhcp;

Option::Option(Universe u, unsigned short type)
    :universe_(u), type_(type), data_len_(0) {


}

Option::Option(Universe u, unsigned short type, boost::shared_array<char> buf,
               unsigned int offset, unsigned int len)
    :universe_(u), type_(type), data_(buf),
     data_len_(len), offset_(offset)
      {

    // sanity checks
    // TODO: universe must be in V4 and V6
}

unsigned int
Option::pack(boost::shared_array<char> buf,
             unsigned int buf_len,
             unsigned int offset) {
    switch (universe_) {
    case V4:
        return pack4(buf, buf_len, offset);
    case V6:
        return pack6(buf, buf_len, offset);
    default:
        isc_throw(BadValue, "Unknown universe defined for Option " << type_);
    }
}


unsigned int
Option::pack4(boost::shared_array<char> buf,
             unsigned int buf_len,
             unsigned int offset) {
    if ( offset+len() > buf_len ) {
        isc_throw(OutOfRange, "Failed to pack v4 option=" <<
                  type_ << ",len=" << data_len_ << ": too small buffer.");
    }
    char *ptr = &buf[offset];
    ptr[0] = type_;
    ptr[1] = data_len_;
    ptr += 2;
    memcpy(ptr, &data_[0], data_len_+4);

    return offset + len();
}

unsigned int
Option::pack6(boost::shared_array<char> buf,
             unsigned int buf_len,
             unsigned int offset) {
    if ( offset+len() > buf_len ) {
        isc_throw(OutOfRange, "Failed to pack v6 option=" <<
                  type_ << ",len=" << len() << ": too small buffer.");
    }

    int length = len() - getHeaderLen();

    char * ptr = &buf[offset];
    *(uint16_t*)ptr = htons(type_);
    ptr += 2;
    *(uint16_t*)ptr = htons(length);
    ptr += 2;
    if (data_len_)
        memcpy(ptr, &data_[offset_], data_len_);

    offset += 4 + data_len_; // end of this option

    return LibDHCP::packOptions6(buf, buf_len, offset, optionLst_);
}

unsigned int
Option::unpack(boost::shared_array<char> buf,
               unsigned int buf_len,
               unsigned int offset,
               unsigned int parse_len) {
    switch (universe_) {
    case V4:
        return unpack4(buf, buf_len, offset, parse_len);
    case V6:
        return unpack6(buf, buf_len, offset, parse_len);
    default:
        isc_throw(BadValue, "Unknown universe defined for Option " << type_);
    }

    return 0; // should not happen
}

unsigned int
Option::unpack4(boost::shared_array<char>,
                unsigned int ,
                unsigned int ,
                unsigned int ) {
    isc_throw(Unexpected, "IPv4 support not implemented yet.");
    return 0;
}

unsigned int
Option::unpack6(boost::shared_array<char> buf,
                unsigned int buf_len,
                unsigned int offset,
                unsigned int parse_len) {

    if (buf_len < offset+parse_len) {
        isc_throw(OutOfRange, "Failed to unpack DHCPv6 option len="
                  << parse_len << " offset=" << offset
                  << " from buffer (length=" << buf_len
                  << "): too small buffer.");
    }

    data_ = buf;
    offset_ = offset;
    data_len_ = buf_len;

    return LibDHCP::unpackOptions6(buf, buf_len, offset, parse_len,
                                   optionLst_);
}

unsigned short Option::len() {
    int length = getHeaderLen() + data_len_;

    for (Option::Option6Lst::iterator it = optionLst_.begin();
         it != optionLst_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
}

bool Option::valid() {
    // total length of buffer is not stored. shared_array is not very useful.
    // we should either add buf_len field or better replace shared_array
    // with shared_ptr to array
    if (universe_ != V4 &&
        universe_ != V6) {
        return (false);
    }

    return (true);
}

void
isc::dhcp::Option::addOption(boost::shared_ptr<isc::dhcp::Option> opt) {
    optionLst_.insert(pair<int, boost::shared_ptr<Option> >(opt->getType(),
                                                            opt));

}

std::string Option::toText(int indent /* =0 */ ) {
    std::stringstream tmp;

    for (int i=0; i<indent; i++)
        tmp << " ";

    tmp << "type=" << type_ << ", len=" << data_len_ << ":";

    for (unsigned int i=0; i<data_len_; i++) {
        if (i) {
            tmp << ":";
        }
        tmp << setfill('0') << setw(2) << hex
            << (unsigned short)(unsigned char)data_[offset_+i];
    }
    return tmp.str();
}

unsigned short
Option::getType() {
    return type_;
}

char*
Option::getData() {
    if (data_len_) {
        return (&data_[offset_]);
    } else {
        return (NULL);
    }
}

unsigned short
Option::getHeaderLen() {
    switch (universe_) {
    case V4:
        return 2; // header length for v4
    case V6:
        return 4; // header length for v6
    }
    return 0; // should not happen
}


Option::~Option() {

}
