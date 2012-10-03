// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_INT6_H_
#define OPTION_INT6_H_

#include <stdint.h>
#include <limits>
#include <util/io_utilities.h>
#include "dhcp/option.h"

namespace isc {
namespace dhcp {

template<typename T>
class OptionInt6: public Option {

public:
    OptionInt6(uint16_t type, T value)
        : Option(Option::V6, type), value_(value) {
    }

    OptionInt6(uint16_t type, OptionBufferConstIter begin,
               OptionBufferConstIter end)
        : Option(Option::V6, type) {
        unpack(begin, end);
    }

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf buffer (option will be stored here)
    void pack(isc::util::OutputBuffer& buf) {
        if (!std::numeric_limits<T>::is_integer) {
            isc_throw(isc::BadValue, "");
        }
        buf.writeUint16(type_);
        buf.writeUint16(len() - OPTION6_HDR_LEN);
        switch (sizeof(T)) {
        case 1:
            buf.writeUint8(value_);
            break;
        case 2:
            buf.writeUint16(value_);
            break;
        case 4:
            buf.writeUint32(value_);
            break;
        default:
            isc_throw(isc::BadValue, "");
        }
    }

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
        if (distance(begin, end) < sizeof(T)) {
            isc_throw(OutOfRange, "Option " << type_ << " truncated");
        }
        switch (sizeof(T)) {
        case 1:
            value_ = *begin;
            break;
        case 2:
            value_ = isc::util::readUint16( &(*begin) );
            break;
        case 4:
            value_ = isc::util::readUint32( &(*begin) );
            break;
        default:
            isc_throw(isc::BadValue, "");
        }

        LibDHCP::unpackOptions6(OptionBuffer(begin, end), options_);
    }

    void setValue(T value) { value_ = value; }

    T getValue() const { return value_; }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t len() {
        uint16_t length = OPTION6_HDR_LEN + sizeof(T);
        // length of all suboptions
        for (Option::OptionCollection::iterator it = options_.begin();
             it != options_.end();
             ++it) {
            length += (*it).second->len();
        }
        return (length);
    }

private:

    T value_;
};

} // isc::dhcp namespace
} // isc namespace

#endif /* OPTION_IA_H_ */
