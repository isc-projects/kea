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

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <iomanip>
#include <sstream>

#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

OptionPtr
Option::factory(Option::Universe u,
        uint16_t type,
        const OptionBuffer& buf) {
    return(LibDHCP::optionFactory(u, type, buf));
}


Option::Option(Universe u, uint16_t type)
    :universe_(u), type_(type) {

    // END option (type 255 is forbidden as well)
    if ((u == V4) && ((type == 0) || (type > 254))) {
        isc_throw(BadValue, "Can't create V4 option of type "
                  << type << ", V4 options are in range 1..254");
    }
}

Option::Option(Universe u, uint16_t type, const OptionBuffer& data)
    :universe_(u), type_(type), data_(data) {
    check();
}

Option::Option(Universe u, uint16_t type, OptionBufferConstIter first,
               OptionBufferConstIter last)
    :universe_(u), type_(type), data_(OptionBuffer(first,last)) {
    check();
}

void
Option::check() {
    if ( (universe_ != V4) && (universe_ != V6) ) {
        isc_throw(BadValue, "Invalid universe type specified. "
                  << "Only V4 and V6 are allowed.");
    }

    if (universe_ == V4) {

        if (type_ > 255) {
            isc_throw(OutOfRange, "DHCPv4 Option type " << type_ << " is too big. "
                      << "For DHCPv4 allowed type range is 0..255");
        } else if (data_.size() > 255) {
            isc_throw(OutOfRange, "DHCPv4 Option " << type_ << " is too big.");
            /// TODO Larger options can be stored as separate instances
            /// of DHCPv4 options. Clients MUST concatenate them.
            /// Fortunately, there are no such large options used today.
        }
    }

    // no need to check anything for DHCPv6. It allows full range (0-64k) of
    // both types and data size.
}

void Option::pack(isc::util::OutputBuffer& buf) {
    switch (universe_) {
    case V6:
        return (pack6(buf));

    case V4:
        return (pack4(buf));

    default:
        isc_throw(BadValue, "Failed to pack " << type_ << " option as the "
                  << "universe type is unknown.");
    }
}

void
Option::pack4(isc::util::OutputBuffer& buf) {
    if (universe_ == V4) {
        if (len() > 255) {
            isc_throw(OutOfRange, "DHCPv4 Option " << type_ << " is too big. "
                      << "At most 255 bytes are supported.");
            /// TODO Larger options can be stored as separate instances
            /// of DHCPv4 options. Clients MUST concatenate them.
            /// Fortunately, there are no such large options used today.
        }

        buf.writeUint8(type_);
        buf.writeUint8(len() - getHeaderLen());
        if (!data_.empty()) {
            buf.writeData(&data_[0], data_.size());
        }

        packOptions(buf);

    } else {
        isc_throw(BadValue, "Invalid universe type " << universe_);
    }

    return;
}

void Option::pack6(isc::util::OutputBuffer& buf) {
    if (universe_ == V6) {
        buf.writeUint16(type_);
        buf.writeUint16(len() - getHeaderLen());
        if (!data_.empty()) {
            buf.writeData(&data_[0], data_.size());
        }

        packOptions(buf);
    } else {
        isc_throw(BadValue, "Invalid universe type " << universe_);
    }
    return;
}

void
Option::packOptions(isc::util::OutputBuffer& buf) {
    switch (universe_) {
    case V4:
        LibDHCP::packOptions(buf, options_);
        return;
    case V6:
        LibDHCP::packOptions6(buf, options_);
        return;
    default:
        isc_throw(isc::BadValue, "Invalid universe type " << universe_);
    }
}

void Option::unpack(OptionBufferConstIter begin,
                    OptionBufferConstIter end) {
    data_ = OptionBuffer(begin, end);
}

void
Option::unpackOptions(const OptionBuffer& buf) {
    switch (universe_) {
    case V4:
        LibDHCP::unpackOptions4(buf, options_);
        return;
    case V6:
        LibDHCP::unpackOptions6(buf, options_);
        return;
    default:
        isc_throw(isc::BadValue, "Invalid universe type " << universe_);
    }
}

uint16_t Option::len() {
    // Returns length of the complete option (data length + DHCPv4/DHCPv6
    // option header)

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

OptionPtr Option::getOption(uint16_t opt_type) {
    isc::dhcp::Option::OptionCollection::const_iterator x =
        options_.find(opt_type);
    if ( x != options_.end() ) {
        return (*x).second;
    }
    return OptionPtr(); // NULL
}

bool Option::delOption(uint16_t opt_type) {
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

uint16_t
Option::getHeaderLen() {
    switch (universe_) {
    case V4:
        return OPTION4_HDR_LEN; // header length for v4
    case V6:
        return OPTION6_HDR_LEN; // header length for v6
    }
    return 0; // should not happen
}

void Option::addOption(OptionPtr opt) {
    if (universe_ == V4) {
        // check for uniqueness (DHCPv4 options must be unique)
        if (getOption(opt->getType())) {
            isc_throw(BadValue, "Option " << opt->getType()
                      << " already present in this message.");
        }
    }
    options_.insert(make_pair(opt->getType(), opt));
}

uint8_t Option::getUint8() {
    if (data_.size() < sizeof(uint8_t) ) {
        isc_throw(OutOfRange, "Attempt to read uint8 from option " << type_
                  << " that has size " << data_.size());
    }
    return (data_[0]);
}

uint16_t Option::getUint16() {
    if (data_.size() < sizeof(uint16_t) ) {
        isc_throw(OutOfRange, "Attempt to read uint16 from option " << type_
                  << " that has size " << data_.size());
    }

    return ( readUint16(&data_[0]) );
}

uint32_t Option::getUint32() {
    if (data_.size() < sizeof(uint32_t) ) {
        isc_throw(OutOfRange, "Attempt to read uint32 from option " << type_
                  << " that has size " << data_.size());
    }
    return ( readUint32(&data_[0]) );
}

void Option::setUint8(uint8_t value) {
  data_.resize(1);
  data_[0] = value;
}

void Option::setUint16(uint16_t value) {
  data_.resize(2);
  writeUint16(value, &data_[0]);
}

void Option::setUint32(uint32_t value) {
  data_.resize(4);
  writeUint32(value, &data_[0]);
}

void Option::setData(const OptionBufferConstIter first,
                     const OptionBufferConstIter last) {
    // We will copy entire option buffer, so we have to resize data_.
    data_.resize(std::distance(first, last));
    std::copy(first, last, data_.begin());
}


Option::~Option() {

}

} // end of isc::dhcp namespace
} // end of isc namespace
