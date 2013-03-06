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

#ifndef OPTION_INT_ARRAY_H
#define OPTION_INT_ARRAY_H

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_data_types.h>
#include <util/io_utilities.h>

#include <stdint.h>

namespace isc {
namespace dhcp {

/// Forward declaration of OptionIntArray.
template<typename T>
class OptionIntArray;

/// @defgroup option_int_array_defs Typedefs for OptionIntArray class.
///
/// @brief Classes that represent options comprising array of integers.
///
/// @{
typedef OptionIntArray<uint8_t> OptionUint8Array;
typedef boost::shared_ptr<OptionUint8Array> OptionUint8ArrayPtr;
typedef OptionIntArray<uint16_t> OptionUint16Array;
typedef boost::shared_ptr<OptionUint16Array> OptionUint16ArrayPtr;
typedef OptionIntArray<uint32_t> OptionUint32Array;
typedef boost::shared_ptr<OptionUint32Array> OptionUint32ArrayPtr;
/// @}

/// This template class represents DHCP (v4 or v6) option with an
/// array of integer values. The type of the elements in the array
/// can be any of the following:
/// - uint8_t,
/// - uint16_t,
/// - uint32_t,
/// - int8_t,
/// - int16_t,
/// - int32_t.
///
/// @warning Since this option may convey variable number of integer
/// values, sub-options are should not be added in this option as
/// there is no way to distinguish them from other data. The API will
/// allow addition of sub-options but they will be ignored during
/// packing and unpacking option data.
///
/// @param T data field type (see above).
template<typename T>
class OptionIntArray: public Option {

public:

    /// @brief Constructor.
    ///
    /// Creates option with empty values vector.
    ///
    /// @param u universe (V4 or V6).
    /// @param type option type.
    ///
    /// @throw isc::dhcp::InvalidDataType if data field type provided
    /// as template parameter is not a supported integer type.
    OptionIntArray(const Option::Universe u, const uint16_t type)
        : Option(u, type),
          values_(0) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
    }

    /// @brief Constructor.
    ///
    /// @param u universe (V4 or V6).
    /// @param type option type.
    /// @param buf buffer with option data (must not be empty).
    ///
    /// @throw isc::OutOfRange if provided buffer is empty or its length
    /// is not multiple of size of the data type in bytes.
    /// @throw isc::dhcp::InvalidDataType if data field type provided
    /// as template parameter is not a supported integer type.
    OptionIntArray(const Option::Universe u, const uint16_t type,
                   const OptionBuffer& buf)
        : Option(u, type) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
        unpack(buf.begin(), buf.end());
    }

    /// @brief Constructor.
    ///
    /// This constructor creates option from a buffer. This constructor
    /// may throw exception if \ref unpack function throws during buffer
    /// parsing.
    ///
    /// @param u universe (V4 or V6).
    /// @param type option type.
    /// @param begin iterator to first byte of option data.
    /// @param end iterator to end of option data (first byte after option end).
    ///
    /// @throw isc::OutOfRange if provided buffer is empty or its length
    /// is not multiple of size of the data type in bytes.
    /// @throw isc::dhcp::InvalidDataType if data field type provided
    /// as template parameter is not a supported integer type.
    OptionIntArray(const Option::Universe u, const uint16_t type,
                   OptionBufferConstIter begin, OptionBufferConstIter end)
        : Option(u, type) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
        unpack(begin, end);
    }

    /// @brief Adds a new value to the array.
    ///
    /// @param value a value being added.
    void addValue(const T value) {
        values_.push_back(value);
    }

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param [out] buf buffer (option will be stored here)
    ///
    /// @throw isc::dhcp::InvalidDataType if size of a data fields type is not
    /// equal to 1, 2 or 4 bytes. The data type is not checked in this function
    /// because it is checked in a constructor.
    void pack(isc::util::OutputBuffer& buf) {
        // Pack option header.
        packHeader(buf);
        // Pack option data.
        for (int i = 0; i < values_.size(); ++i) {
            // Depending on the data type length we use different utility functions
            // writeUint16 or writeUint32 which write the data in the network byte
            // order to the provided buffer. The same functions can be safely used
            // for either unsigned or signed integers so there is not need to create
            // special cases for intX_t types.
            switch (OptionDataTypeTraits<T>::len) {
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
                isc_throw(dhcp::InvalidDataType, "non-integer type");
            }
        }
        // We don't pack sub-options here because we have array-type option.
        // We don't allow sub-options in array-type options as there is no
        // way to distinguish them from the data fields on option reception.
    }

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw isc::dhcp::InvalidDataType if size of a data fields type is not
    /// equal to 1, 2 or 4 bytes. The data type is not checked in this function
    /// because it is checked in a constructor.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
        if (distance(begin, end) == 0) {
            isc_throw(OutOfRange, "option " << getType() << " empty");
        }
        if (distance(begin, end) % sizeof(T) != 0) {
            isc_throw(OutOfRange, "option " << getType() << " truncated");
        }
        // @todo consider what to do if buffer is longer than data type.

        values_.clear();
        while (begin != end) {
            // Depending on the data type length we use different utility functions
            // readUint16 or readUint32 which read the data laid in the network byte
            // order from the provided buffer. The same functions can be safely used
            // for either unsigned or signed integers so there is not need to create
            // special cases for intX_t types.
            int data_size_len = OptionDataTypeTraits<T>::len;
            switch (data_size_len) {
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
                isc_throw(dhcp::InvalidDataType, "non-integer type");
            }
            // Use local variable to set a new value for this iterator.
            // When using OptionDataTypeTraits<T>::len directly some versions
            // of clang complain about unresolved reference to
            // OptionDataTypeTraits structure during linking.
            begin += data_size_len;
        }
        // We do not unpack sub-options here because we have array-type option.
        // Such option have variable number of data fields, thus there is no
        // way to assess where sub-options start.
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
        uint16_t length = (getUniverse() == Option::V4) ? OPTION4_HDR_LEN : OPTION6_HDR_LEN;
        length += values_.size() * sizeof(T);
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

#endif // OPTION_INT_ARRAY_H
