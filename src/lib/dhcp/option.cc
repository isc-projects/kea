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
#include "util/io_utilities.h"

#include "dhcp/option.h"
#include "dhcp/libdhcp.h"

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;

Option::Option(Universe u, unsigned short type)
    :universe_(u), type_(type) {

    if ((u == V4) && (type > 255)) {
        isc_throw(BadValue, "Can't create V4 option of type "
                  << type << ", V4 options are in range 0..255");
    }
}

Option::Option(Universe u, unsigned short type,
               const boost::shared_array<uint8_t>& buf,
               unsigned int offset, unsigned int len)
    :universe_(u), type_(type),
     offset_(offset)
{
    if ( (u == V4) && (type > 255)) {
        isc_throw(BadValue, "Can't create V4 option of type "
                  << type << ", V4 options are in range 0..255");
    }

    uint8_t* ptr = &buf[offset];
    data_ = std::vector<uint8_t>(ptr, ptr + len);

    // sanity checks
    // TODO: universe must be in V4 and V6
}

Option::Option(Universe u, unsigned short type, std::vector<uint8_t>& data)
    :universe_(u), type_(type), data_(data) {
    if ( (u == V4) && (data.size() > 255) ) {
        isc_throw(OutOfRange, "DHCPv4 Option " << type_ << " is too big."
                  << "At most 255 bytes are supported.");
        /// TODO Larger options can be stored as separate instances
        /// of DHCPv4 options. Clients MUST concatenate them.
        /// Fortunately, there are no such large options used today.
    }
    if ( (u == V4) && (type > 255) ) {
        isc_throw(OutOfRange, "DHCPv4 Option type " << type_ << " is too big."
                  << "For DHCPv4 allowed type range is 0..255");
    }
}

Option::Option(Universe u, uint16_t type, vector<uint8_t>::const_iterator first,
               vector<uint8_t>::const_iterator last)
    :universe_(u), type_(type) {
    if ( (u == V4) && (type > 255) ) {
        isc_throw(OutOfRange, "DHCPv4 Option type " << type_ << " is too big."
                  << "For DHCPv4 allowed type range is 0..255");
    }
    data_ = std::vector<uint8_t>(first, last);
    if ( (u == V4) && (data_.size() > 255) ) {
        isc_throw(OutOfRange, "DHCPv4 Option " << type_ << " is too big.");
    }
}


unsigned int
Option::pack(boost::shared_array<uint8_t>& buf,
             unsigned int buf_len,
             unsigned int offset) {
    if (universe_ != V6) {
        isc_throw(BadValue, "Failed to pack " << type_ << " option. Do not "
                  << "use this method for options other than DHCPv6.");
    }
    return pack6(buf, buf_len, offset);
}

void
Option::pack4(isc::util::OutputBuffer& buf) {
    switch (universe_) {
    case V4: {
        if (data_.size() > 255) {
            isc_throw(OutOfRange, "DHCPv4 Option " << type_ << " is too big."
                      << "At most 255 bytes are supported.");
            /// TODO Larger options can be stored as separate instances
            /// of DHCPv4 options. Clients MUST concatenate them.
            /// Fortunately, there are no such large options used today.
        }

        buf.writeUint8(type_);
        buf.writeUint8(len() - getHeaderLen());

        buf.writeData(&data_[0], data_.size());

        LibDHCP::packOptions(buf, options_);
        return;
    }
    case V6:
        /// TODO: Do we need a sanity check for option size here?
        buf.writeUint16(type_);
        buf.writeUint16(len() - getHeaderLen());

        LibDHCP::packOptions(buf, options_);
        return;
    default:
        isc_throw(OutOfRange, "Invalid universe type" << universe_);
    }
}

unsigned int
Option::pack6(boost::shared_array<uint8_t>& buf,
             unsigned int buf_len,
             unsigned int offset) {
    if (offset+len() > buf_len) {
        isc_throw(OutOfRange, "Failed to pack v6 option=" <<
                  type_ << ",len=" << len() << ": too small buffer.");
    }

    uint8_t * ptr = &buf[offset];

    ptr = writeUint16(type_, ptr);

    ptr = writeUint16(len() - getHeaderLen(), ptr);

    if (! data_.empty())
        memcpy(ptr, &data_[0], data_.size());

    // end of fixed part of this option
    offset += OPTION6_HDR_LEN + data_.size();

    return LibDHCP::packOptions6(buf, buf_len, offset, options_);
}

unsigned int
Option::unpack(const boost::shared_array<uint8_t>& buf,
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
Option::unpack4(const boost::shared_array<uint8_t>&,
                unsigned int ,
                unsigned int ,
                unsigned int ) {
    isc_throw(Unexpected, "IPv4 support not implemented yet.");
    return 0;
}

unsigned int
Option::unpack6(const boost::shared_array<uint8_t>& buf,
                unsigned int buf_len,
                unsigned int offset,
                unsigned int parse_len) {

    if (buf_len < offset+parse_len) {
        isc_throw(OutOfRange, "Failed to unpack DHCPv6 option len="
                  << parse_len << " offset=" << offset
                  << " from buffer (length=" << buf_len
                  << "): too small buffer.");
    }

    uint8_t* ptr = &buf[offset];
    data_ = std::vector<uint8_t>(ptr, ptr + parse_len);

    offset_ = offset;

    return (offset+parse_len);

    //return LibDHCP::unpackOptions6(buf, buf_len, offset, parse_len,
    //                               options_);
}

/// Returns length of the complete option (data length + DHCPv4/DHCPv6
/// option header)
unsigned short
Option::len() {

    // length of the whole option is header and data stored in this option...
    int length = getHeaderLen() + data_.size();

    // ... and sum of lengths of all suboptions
    for (Option::OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    // note that this is not equal to lenght field. This value denotes
    // number of bytes required to store this option. length option should
    // contain (len()-getHeaderLen()) value.
    return (length);
}

bool
Option::valid() {
    if (universe_ != V4 &&
        universe_ != V6) {
        return (false);
    }

    return (true);
}

boost::shared_ptr<isc::dhcp::Option>
Option::getOption(unsigned short opt_type) {
    isc::dhcp::Option::OptionCollection::const_iterator x =
        options_.find(opt_type);
    if ( x != options_.end() ) {
        return (*x).second;
    }
    return boost::shared_ptr<isc::dhcp::Option>(); // NULL
}

bool
Option::delOption(unsigned short opt_type) {
    isc::dhcp::Option::OptionCollection::iterator x = options_.find(opt_type);
    if ( x != options_.end() ) {
        options_.erase(x);
        return true; // delete successful
    }
    return (false); // option not found, can't delete
}


std::string Option::toText(int indent /* =0 */ ) {
    std::stringstream tmp;

    for (int i = 0; i < indent; i++)
        tmp << " ";

    tmp << "type=" << type_ << ", len=" << len()-getHeaderLen() << ": ";

    for (unsigned int i = 0; i < data_.size(); i++) {
        if (i) {
            tmp << ":";
        }
        tmp << setfill('0') << setw(2) << hex
            << static_cast<unsigned short>(data_[i]);
    }

    // print suboptions
    for (OptionCollection::const_iterator opt = options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << (*opt).second->toText(indent+2);
    }
    return tmp.str();
}

unsigned short
Option::getType() {
    return type_;
}

const std::vector<uint8_t>&
Option::getData() {
    return (data_);
}

unsigned short
Option::getHeaderLen() {
    switch (universe_) {
    case V4:
        return OPTION4_HDR_LEN; // header length for v4
    case V6:
        return OPTION6_HDR_LEN; // header length for v6
    }
    return 0; // should not happen
}

void
Option::addOption(boost::shared_ptr<Option> opt) {
    if (universe_ == V4) {
        // check for uniqueness (DHCPv4 options must be unique)
        if (getOption(opt->getType())) {
            isc_throw(BadValue, "Option " << opt->getType()
                      << " already present in this message.");
        }
    }
    options_.insert(pair<int, boost::shared_ptr<Option> >(opt->getType(), opt));
}

Option::~Option() {

}
