// Copyright (C) 2011-2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SERIAL_H
#define SERIAL_H 1

#include <stdint.h>
#include <iostream>

namespace isc {
namespace dns {

/// The maximum difference between two serial numbers. If the (plain uint32_t)
/// difference between two serials is greater than this number, the smaller one
/// is considered greater.
const uint32_t MAX_SERIAL_INCREMENT = 2147483647;

/// Maximum value a serial can have, used in + operator.
const uint64_t MAX_SERIAL_VALUE = 4294967296ull;

/// \brief This class defines DNS serial numbers and serial arithmetic.
///
/// DNS Serial number are in essence unsigned 32-bits numbers, with one
/// catch; they should be compared using sequence space arithmetic.
/// So given that they are 32-bits; as soon as the difference between two
/// serial numbers is greater than 2147483647 (2^31 - 1), the lower number
/// (in plain comparison) is considered the higher one.
///
/// In order to do this as transparently as possible, these numbers are
/// stored in the Serial class, which overrides the basic comparison operators.
///
/// In this specific context, these operations are called 'serial number
/// arithmetic', and they are defined in RFC 1982.
///
/// \note RFC 1982 defines everything based on the value SERIAL_BITS. Since
/// the serial number has a fixed length of 32 bits, the values we use are
/// hard-coded, and not computed based on variable bit lengths.
class Serial {
public:
    /// \brief Constructor with value
    ///
    /// \param value The uint32_t value of the serial
    explicit Serial(uint32_t value) : value_(value) {}

    /// \brief Copy constructor
    Serial(const Serial& other) : value_(other.getValue()) {}

    /// \brief Direct assignment from other Serial
    ///
    /// \param other The Serial to assign the value from
    Serial& operator=(const Serial& other) {
        value_ = other.getValue();
        return (*this);
    }

    /// \brief Direct assignment from value
    ///
    /// \param value the uint32_t value to assign
    void operator=(uint32_t value) { value_ = value; }

    /// \brief Returns the uint32_t representation of this serial value
    ///
    /// \return The uint32_t value of this Serial
    uint32_t getValue() const { return (value_); }

    /// \brief Returns true if the serial values are equal
    ///
    /// \return True if the values are equal
    bool operator==(const Serial& other) const;

    /// \brief Returns true if the serial values are not equal
    ///
    /// \return True if the values are not equal
    bool operator!=(const Serial& other) const;

    /// \brief Returns true if the serial value of this serial is smaller than
    /// the other, according to serial arithmetic as described in RFC 1982
    ///
    /// \param other The Serial to compare to
    ///
    /// \return True if this is smaller than the given value
    bool operator<(const Serial& other) const;

    /// \brief Returns true if the serial value of this serial is equal to or
    /// smaller than the other, according to serial arithmetic as described
    /// in RFC 1982
    ///
    /// \param other The Serial to compare to
    ///
    /// \return True if this is smaller than or equal to the given value
    bool operator<=(const Serial& other) const;

    /// \brief Returns true if the serial value of this serial is greater than
    /// the other, according to serial arithmetic as described in RFC 1982
    ///
    /// \param other The Serial to compare to
    ///
    /// \return True if this is greater than the given value
    bool operator>(const Serial& other) const;

    /// \brief Returns true if the serial value of this serial is equal to or
    /// greater than the other, according to serial arithmetic as described in
    /// RFC 1982
    ///
    /// \param other The Serial to compare to
    ///
    /// \return True if this is greater than or equal to the given value
    bool operator>=(const Serial& other) const;

    /// \brief Adds the given value to the serial number. If this would make
    /// the number greater than 2^32-1, it is 'wrapped'.
    /// \note According to the specification, an addition greater than
    /// MAX_SERIAL_INCREMENT is undefined. We do NOT catch this error (so as not
    /// to raise exceptions), but this behaviour remains undefined.
    ///
    /// \param other The Serial to add
    ///
    /// \return The result of the addition
    Serial operator+(const Serial& other) const;

    /// \brief Adds the given value to the serial number. If this would make
    /// the number greater than 2^32-1, it is 'wrapped'.
    ///
    /// \note According to the specification, an addition greater than
    /// MAX_SERIAL_INCREMENT is undefined. We do NOT catch this error (so as not
    /// to raise exceptions), but this behaviour remains undefined.
    ///
    /// \param other_val The uint32_t value to add
    ///
    /// \return The result of the addition
    Serial operator+(uint32_t other_val) const;

private:
    uint32_t value_;
};

/// \brief Helper operator for output streams, writes the value to the stream
///
/// \param os The ostream to write to
/// \param serial The Serial to write
/// \return the output stream
std::ostream& operator<<(std::ostream& os, const Serial& serial);

} // end namespace dns
} // end namespace isc

#endif // SERIAL_H
