// Copyright (C) 2012-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_INT_H
#define OPTION_INT_H

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_space.h>
#include <util/io_utilities.h>

#include <stdint.h>
#include <sstream>

namespace isc {
namespace dhcp {

template<typename T>
class OptionInt;

/// @defgroup option_int_defs Typedefs for OptionInt class.
///
/// @brief Classes that represent options comprising an integer.
///
/// @{
typedef OptionInt<uint8_t> OptionUint8;
typedef boost::shared_ptr<OptionUint8> OptionUint8Ptr;
typedef OptionInt<uint16_t> OptionUint16;
typedef boost::shared_ptr<OptionUint16> OptionUint16Ptr;
typedef OptionInt<uint32_t> OptionUint32;
typedef boost::shared_ptr<OptionUint32> OptionUint32Ptr;
/// @}

/// This template class represents DHCP option with single value.
/// This value is of integer type and can be any of the following:
/// - uint8_t,
/// - uint16_t,
/// - uint32_t,
/// - int8_t,
/// - int16_t,
/// - int32_t.
///
/// @tparam T data field type (see above).
template<typename T>
class OptionInt: public Option {
private:

    /// @brief Pointer to the option object for a specified type T.
    typedef boost::shared_ptr<OptionInt<T> > OptionIntTypePtr;

public:
    /// @brief Constructor.
    ///
    /// @param u universe (V4 or V6)
    /// @param type option type.
    /// @param value option value.
    ///
    /// @throw isc::dhcp::InvalidDataType if data field type provided
    /// as template parameter is not a supported integer type.
    /// @todo Extend constructor to set encapsulated option space name.
    OptionInt(Option::Universe u, uint16_t type, T value)
        : Option(u, type), value_(value) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
        setEncapsulatedSpace(u == Option::V4 ? DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE);
    }

    /// @brief Constructor.
    ///
    /// This constructor creates option from a buffer. This constructor
    /// may throw exception if \ref unpack function throws during buffer
    /// parsing.
    ///
    /// @param u universe (V4 or V6)
    /// @param type option type.
    /// @param begin iterator to first byte of option data.
    /// @param end iterator to end of option data (first byte after option end).
    ///
    /// @throw isc::OutOfRange if provided buffer is shorter than data size.
    /// @throw isc::dhcp::InvalidDataType if data field type provided
    /// as template parameter is not a supported integer type.
    /// @todo Extend constructor to set encapsulated option space name.
    OptionInt(Option::Universe u, uint16_t type, OptionBufferConstIter begin,
               OptionBufferConstIter end)
        : Option(u, type) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
        setEncapsulatedSpace(u == Option::V4 ? DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE);
        unpack(begin, end);
    }

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const {
        return (cloneInternal<OptionInt<T> >());
    }

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param [out] buf buffer (option will be stored here)
    /// @param check if set to false, allows options larger than 255 for v4
    ///
    /// @throw isc::dhcp::InvalidDataType if size of a data field type is not
    /// equal to 1, 2 or 4 bytes. The data type is not checked in this function
    /// because it is checked in a constructor.
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const {
        // Pack option header.
        packHeader(buf, check);
        // Depending on the data type length we use different utility functions
        // writeUint16 or writeUint32 which write the data in the network byte
        // order to the provided buffer. The same functions can be safely used
        // for either unsigned or signed integers so there is not need to create
        // special cases for intX_t types.
        switch (OptionDataTypeTraits<T>::len) {
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
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
        packOptions(buf, check);
    }

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw isc::OutOfRange if provided buffer is shorter than data size.
    /// @throw isc::dhcp::InvalidDataType if size of a data field type is not
    /// equal to 1, 2 or 4 bytes. The data type is not checked in this function
    /// because it is checked in a constructor.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
        if (distance(begin, end) < sizeof(T)) {
            isc_throw(OutOfRange, "OptionInt " << getType() << " truncated");
        }
        // @todo consider what to do if buffer is longer than data type.

        // Depending on the data type length we use different utility functions
        // readUint16 or readUint32 which read the data laid in the network byte
        // order from the provided buffer. The same functions can be safely used
        // for either unsigned or signed integers so there is not need to create
        // special cases for intX_t types.
        int data_size_len = OptionDataTypeTraits<T>::len;
        switch (data_size_len) {
        case 1:
            value_ = *begin;
            break;
        case 2:
            value_ = isc::util::readUint16(&(*begin),
                                           std::distance(begin, end));
            break;
        case 4:
            value_ = isc::util::readUint32(&(*begin),
                                           std::distance(begin, end));
            break;
        default:
            isc_throw(dhcp::InvalidDataType, "non-integer type");
        }
        // Use local variable to set a new value for this iterator.
        // When using OptionDataTypeTraits<T>::len directly some versions
        // of clang complain about unresolved reference to
        // OptionDataTypeTraits structure during linking.
        begin += data_size_len;
        unpackOptions(OptionBuffer(begin, end));
    }

    /// @brief Set option value.
    ///
    /// @param value new option value.
    void setValue(T value) { value_ = value; }

    /// @brief Return option value.
    ///
    /// @return option value.
    T getValue() const { return value_; }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t len() const {
        // Calculate the length of the header.
        uint16_t length = (getUniverse() == Option::V4) ? OPTION4_HDR_LEN : OPTION6_HDR_LEN;
        // The data length is equal to size of T.
        length += sizeof(T);;
        // length of all suboptions
        for (OptionCollection::const_iterator it = options_.begin();
             it != options_.end();
             ++it) {
            length += (*it).second->len();
        }
        return (length);
    }

    /// @brief Returns option carrying an integer value in the textual
    /// format.
    ///
    /// The returned value also includes the suboptions if present.
    ///
    /// @param indent Number of spaces to be inserted before the text.
    virtual std::string toText(int indent = 0) const {
        std::stringstream output;
        output << headerToText(indent) << ": ";

        // For 1 byte long data types we need to cast to the integer
        // because they are usually implemented as "char" types, in
        // which case the character rather than number would be printed.
        if (OptionDataTypeTraits<T>::len == 1) {
            output << static_cast<int>(getValue());
        } else {
            output << getValue();
        }

        // Append data type name.
        output << " ("
               << OptionDataTypeUtil::getDataTypeName(OptionDataTypeTraits<T>::type)
               << ")";

        // Append suboptions.
        output << suboptionsToText(indent + 2);

        return (output.str());
    }

private:

    T value_;  ///< Value conveyed by the option.
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_INT_H
