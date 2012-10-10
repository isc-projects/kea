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

#ifndef OPTION6_INT_ARRAY_H_
#define OPTION6_INT_ARRAY_H_

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_data_types.h>
#include <util/io_utilities.h>

#include <stdint.h>
#include <limits>

namespace isc {
namespace dhcp {

/// This template class represents DHCPv6 option with array of
/// integer values. The type of the elements in the array can be
/// any of the following:
/// - uint8_t,
/// - uint16_t,
/// - uint32_t,
/// - int8_t,
/// - int16_t,
/// - int32_t.
///
/// @param T data field type (see above).
template<typename T>
class Option6IntArray: public Option {

public:

    /// @brief Constructor.
    ///
    /// Creates option with empty values vector.
    ///
    /// @param type option type.
    Option6IntArray(uint16_t type)
        : Option(Option::V6, type),
          values_(0) {
        if (!OptionDataTypes<T>::valid) {
            isc_throw(dhcp::InvalidDataType, "non-numeric type");
        }
    }

    /// @brief Constructor.
    ///
    /// @param type option type.
    /// @param buf buffer with option data.
    Option6IntArray(uint16_t type, const OptionBuffer& buf)
        : Option(Option::V6, type) {
        if (!OptionDataTypes<T>::valid) {
            isc_throw(dhcp::InvalidDataType, "non-numeric type");
        }
        unpack(buf.begin(), buf.end());
    }

    /// @brief Constructor.
    ///
    /// This constructor creates option from a buffer. This construtor
    /// may throw exception if \ref unpack function throws during buffer
    /// parsing.
    ///
    /// @param type option type.
    /// @param begin iterator to first byte of option data.
    /// @param end iterator to end of option data (first byte after option end).
    ///
    /// @todo mention here what it throws.
    Option6IntArray(uint16_t type, OptionBufferConstIter begin,
                    OptionBufferConstIter end)
        : Option(Option::V6, type) {
        if (!OptionDataTypes<T>::valid) {
            isc_throw(dhcp::InvalidDataType, "non-numeric type");
        }
        unpack(begin, end);
    }

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param [out] buf buffer (option will be stored here)
    ///
    /// @throw isc::BadValue if invalid option type has been provided.
    void pack(isc::util::OutputBuffer& buf) {
        buf.writeUint16(type_);
        buf.writeUint16(len() - OPTION6_HDR_LEN);
        for (int i = 0; i < values_.size(); ++i) {
            switch (OptionDataTypes<T>::len) {
            case 1:
                buf.writeUint8(values_[i]);
                break;
            case 2:
                buf.writeUint16(values_[i]);
                break;
            case 4:
                buf.writeUint32(values_[i]);
                break;
            default:
                isc_throw(dhcp::InvalidDataType, "non-numeric type");
            }
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
        if (distance(begin, end) % sizeof(T) != 0) {
            isc_throw(OutOfRange, "Option " << type_ << " truncated");
        }
        values_.clear();
        while (begin != end) {
            switch (OptionDataTypes<T>::len) {
            case 1:
                values_.push_back(*begin);
                break;
            case 2:
                values_.push_back(isc::util::readUint16(&(*begin)));
                break;
            case 4:
                values_.push_back(isc::util::readUint32(&(*begin)));
                break;
            default:
                isc_throw(dhcp::InvalidDataType, "non-numeric type");
            }
            begin += sizeof(T);
        }
    }

    /// @brief Return collection of option values.
    ///
    /// @return collection of values.
    const std::vector<T>& getValues() const { return (values_); }

    /// @brief Set option values.
    ///
    /// @param values collection of values to be set for option.
    void setValues(const std::vector<T>& values) { values_ = values; }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t len() {
        uint16_t length = OPTION6_HDR_LEN + values_.size() * sizeof(T);
        // length of all suboptions
        for (Option::OptionCollection::iterator it = options_.begin();
             it != options_.end();
             ++it) {
            length += (*it).second->len();
        }
        return (length);
    }

private:

    std::vector<T> values_;
};

} // isc::dhcp namespace
} // isc namespace

#endif /* OPTION6_INT_ARRAY_H_ */
