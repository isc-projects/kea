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
    :universe_(u), type_(type) {


}

Option::Option(Universe u, unsigned short type, boost::shared_array<char> buf,
               unsigned int offset, unsigned int len)
    :universe_(u), type_(type), data_(buf),
     offset_(offset),
     len_(len) {

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
                  type_ << ",len=" << len_ << ": too small buffer.");
    }
    char *ptr = &buf[offset];
    ptr[0] = type_;
    ptr[1] = len_;
    ptr += 2;
    memcpy(ptr, &data_[0], len_);

    return offset + len();
}

unsigned int
Option::pack6(boost::shared_array<char> buf,
             unsigned int buf_len,
             unsigned int offset) {
    if ( offset+len() > buf_len ) {
        isc_throw(OutOfRange, "Failed to pack v6 option=" <<
                  type_ << ",len=" << len_ << ": too small buffer.");
    }
    char * ptr = &buf[offset];
    *(uint16_t*)ptr = htons(type_);
    ptr += 2;
    *(uint16_t*)ptr = htons(len_);
    ptr += 2;
    memcpy(ptr, &data_[0], len_);

    return offset + len();
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
/**
 * Parses buffer and creates collection of Option objects.
 *
 * @param buf pointer to buffer
 * @param buf_len length of buf
 * @param offset offset, where start parsing option
 * @param parse_len how many bytes should be parsed
 *
 * @return offset after last parsed option
 */
unsigned int
Option::unpack6(boost::shared_array<char> buf,
                unsigned int buf_len,
                unsigned int offset,
                unsigned int parse_len) {

    if (buf_len < offset+parse_len) {
        isc_throw(OutOfRange, "Failed to unpack DHCPv6 option len="
                  << parse_len << " offset=" << offset << " from buffer (length="
                  << buf_len << "): too small buffer.");
    }

    data_ = buf;
    offset_ = offset;
    len_ = buf_len;

    return LibDHCP::unpackOptions6(buf, buf_len, offset, parse_len,
                                   optionLst_);
}

unsigned short Option::len() {
    switch (universe_) {
    case V4:
        return len_ + 2; // DHCPv4 option header length: 2 bytes
    case V6:
        return len_ + 4; // DHCPv6 option header length: 4 bytes
    default:
        isc_throw(BadValue, "Unknown universe defined for Option " << type_);
    }

    return 0; // should not happen
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

/**
 * Converts generic option to string.
 *
 * @return string that represents option.
 */
std::string Option::toText() {
    std::stringstream tmp;
    tmp << type_ << "(len=" << len_ << "):";

    for (unsigned int i=0; i<len_; i++) {
        if (i) {
            tmp << ":";
        }
        tmp << setfill('0') << setw(2) << hex << (unsigned short)(unsigned char)data_[offset_+i];
    }
    return tmp.str();
}

unsigned short
Option::getType() {
    return type_;
}

Option::~Option() {

}
