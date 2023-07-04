// Copyright (C) 2011-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_UTILITIES_H
#define IO_UTILITIES_H

#include <exceptions/exceptions.h>
#include <cstddef>

namespace isc {
namespace util {

/// \brief Read Unsigned 16-Bit Integer from Buffer
///
/// This is essentially a copy of the isc::util::InputBuffer::readUint16.  It
/// should really be moved into a separate library.
///
/// \param buffer Data buffer at least two bytes long of which the first two
///        bytes are assumed to represent a 16-bit integer in network-byte
///        order.
/// \param length Length of the data buffer.
///
/// \return Value of 16-bit integer
inline uint16_t
readUint16(const void* buffer, size_t length) {
    if (length < sizeof(uint16_t)) {
        isc_throw(isc::OutOfRange,
                  "Length (" << length << ") of buffer is insufficient " <<
                  "to read a uint16_t");
    }

    const uint8_t* byte_buffer = static_cast<const uint8_t*>(buffer);

    uint16_t result = (static_cast<uint16_t>(byte_buffer[0])) << 8;
    result |= static_cast<uint16_t>(byte_buffer[1]);

    return (result);
}

/// \brief Write Unsigned 16-Bit Integer to Buffer
///
/// This is essentially a copy of isc::util::OutputBuffer::writeUint16.  It
/// should really be moved into a separate library.
///
/// \param value 16-bit value to convert
/// \param buffer Data buffer at least two bytes long into which the 16-bit
///        value is written in network-byte order.
/// \param length Length of the data buffer.
///
/// \return pointer to the next byte after stored value
inline uint8_t*
writeUint16(uint16_t value, void* buffer, size_t length) {
    if (length < sizeof(uint16_t)) {
        isc_throw(isc::OutOfRange,
                  "Length (" << length << ") of buffer is insufficient " <<
                  "to write a uint16_t");
    }

    uint8_t* byte_buffer = static_cast<uint8_t*>(buffer);

    byte_buffer[0] = static_cast<uint8_t>((value & 0xff00U) >> 8);
    byte_buffer[1] = static_cast<uint8_t>(value & 0x00ffU);

    return (byte_buffer + sizeof(uint16_t));
}

/// \brief Read Unsigned 32-Bit Integer from Buffer
///
/// \param buffer Data buffer at least four bytes long of which the first four
///        bytes are assumed to represent a 32-bit integer in network-byte
///        order.
/// \param length Length of the data buffer.
///
/// \return Value of 32-bit unsigned integer
inline uint32_t
readUint32(const void* buffer, size_t length) {
    if (length < sizeof(uint32_t)) {
        isc_throw(isc::OutOfRange,
                  "Length (" << length << ") of buffer is insufficient " <<
                  "to read a uint32_t");
    }

    const uint8_t* byte_buffer = static_cast<const uint8_t*>(buffer);

    uint32_t result = (static_cast<uint32_t>(byte_buffer[0])) << 24;
    result |= (static_cast<uint32_t>(byte_buffer[1])) << 16;
    result |= (static_cast<uint32_t>(byte_buffer[2])) << 8;
    result |= (static_cast<uint32_t>(byte_buffer[3]));

    return (result);
}

/// \brief Write Unsigned 32-Bit Integer to Buffer
///
/// \param value 32-bit value to convert
/// \param buffer Data buffer at least four bytes long into which the 32-bit
///        value is written in network-byte order.
/// \param length Length of the data buffer.
///
/// \return pointer to the next byte after stored value
inline uint8_t*
writeUint32(uint32_t value, void* buffer, size_t length) {
    if (length < sizeof(uint32_t)) {
        isc_throw(isc::OutOfRange,
                  "Length (" << length << ") of buffer is insufficient " <<
                  "to write a uint32_t");
    }

    uint8_t* byte_buffer = static_cast<uint8_t*>(buffer);

    byte_buffer[0] = static_cast<uint8_t>((value & 0xff000000U) >> 24);
    byte_buffer[1] = static_cast<uint8_t>((value & 0x00ff0000U) >> 16);
    byte_buffer[2] = static_cast<uint8_t>((value & 0x0000ff00U) >> 8);
    byte_buffer[3] = static_cast<uint8_t>((value & 0x000000ffU));

    return (byte_buffer + sizeof(uint32_t));
}

/// \brief Read Unsigned 64-Bit Integer from Buffer
///
/// \param buffer Data buffer at least four bytes long of which the first four
///        bytes are assumed to represent a 64-bit integer in network-byte
///        order.
/// \param length Length of the data buffer.
///
/// \return Value of 64-bit unsigned integer
inline uint64_t
readUint64(const void* buffer, size_t length) {
    if (length < sizeof(uint64_t)) {
        isc_throw(isc::OutOfRange,
                  "Length (" << length << ") of buffer is insufficient " <<
                  "to read a uint64_t");
    }

    const uint8_t* byte_buffer = static_cast<const uint8_t*>(buffer);

    uint64_t result = (static_cast<uint64_t>(byte_buffer[0])) << 56;
    result |= (static_cast<uint64_t>(byte_buffer[1])) << 48;
    result |= (static_cast<uint64_t>(byte_buffer[2])) << 40;
    result |= (static_cast<uint64_t>(byte_buffer[3])) << 32;
    result |= (static_cast<uint64_t>(byte_buffer[4])) << 24;
    result |= (static_cast<uint64_t>(byte_buffer[5])) << 16;
    result |= (static_cast<uint64_t>(byte_buffer[6])) << 8;
    result |= (static_cast<uint64_t>(byte_buffer[7]));

    return (result);
}

/// \brief Write Unsigned 64-Bit Integer to Buffer
///
/// \param value 64-bit value to convert
/// \param buffer Data buffer at least four bytes long into which the 64-bit
///        value is written in network-byte order.
/// \param length Length of the data buffer.
///
/// \return pointer to the next byte after stored value
inline uint8_t*
writeUint64(uint64_t value, void* buffer, size_t length) {
    if (length < sizeof(uint64_t)) {
        isc_throw(isc::OutOfRange,
                  "Length (" << length << ") of buffer is insufficient " <<
                  "to write a uint64_t");
    }

    uint8_t* byte_buffer = static_cast<uint8_t*>(buffer);

    byte_buffer[0] = static_cast<uint8_t>((value & 0xff00000000000000UL) >> 56);
    byte_buffer[1] = static_cast<uint8_t>((value & 0x00ff000000000000UL) >> 48);
    byte_buffer[2] = static_cast<uint8_t>((value & 0x0000ff0000000000UL) >> 40);
    byte_buffer[3] = static_cast<uint8_t>((value & 0x000000ff00000000UL) >> 32);
    byte_buffer[4] = static_cast<uint8_t>((value & 0x00000000ff000000UL) >> 24);
    byte_buffer[5] = static_cast<uint8_t>((value & 0x0000000000ff0000UL) >> 16);
    byte_buffer[6] = static_cast<uint8_t>((value & 0x000000000000ff00UL) >> 8);
    byte_buffer[7] = static_cast<uint8_t>((value & 0x00000000000000ffUL));

    return (byte_buffer + sizeof(uint64_t));
}

} // namespace util
} // namespace isc

#endif // IO_UTILITIES_H
