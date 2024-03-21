// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_UTIL_IO_H
#define KEA_UTIL_IO_H

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace isc {
namespace util {

/// \brief Read an unsigned integer from given buffer.
///
/// \tparam uint_t Data type of the unsigned integer.
/// \param buffer Data buffer at least two bytes long of which the first bytes are assumed to
///        represent an unsigned integer in network-byte order.
/// \param length Length of the data buffer.
///
/// \return Value of the integer.
template <typename uint_t>
uint_t
readUint(void const* const buffer, size_t const length) {
    constexpr size_t size(sizeof(uint_t));
    if (length < size) {
        isc_throw(OutOfRange, "Expected buffer to be long enough to read a "
                                  << size << "-byte integer, but got " << length << " byte"
                                  << (length == 1 ? "" : "s") << " instead");
    }

    uint8_t const* const byte_buffer(static_cast<uint8_t const*>(buffer));
    uint_t result(0);

    for (size_t i = 0; i < size; ++i) {
        result |= (static_cast<uint_t>(byte_buffer[i])) << (8 * (size - (i + 1)));
    }

    return (result);
}

/// \brief Write the given unsigned integer to the given buffer.
///
/// \tparam uint_t Data type of the unsigned integer.
/// \param value Value to convert.
/// \param buffer Data buffer at least two bytes long into which the unsigned integer value is
///        written in network-byte order.
/// \param length Length of the data buffer.
///
/// \return pointer to the next byte after stored value
template <typename uint_t>
uint8_t*
writeUint(uint_t const value, void* const buffer, size_t const length) {
    constexpr size_t size(sizeof(uint_t));
    if (length < size) {
        isc_throw(OutOfRange, "Expected buffer to be long enough to write a "
                                  << size << "-byte integer, but got " << length << " byte"
                                  << (length == 1 ? "" : "s") << " instead");
    }

    uint8_t* byte_buffer(static_cast<uint8_t*>(buffer));

    for (size_t i = 0; i < size; ++i) {
        uint8_t const shift_by(8 * (size - (i + 1)));
        byte_buffer[i] = uint8_t((value & (uint_t(0xff) << shift_by)) >> shift_by);
    }

    return (byte_buffer + size);
}

/// \brief uint16_t wrapper over readUint.
inline uint16_t
readUint16(void const* const buffer, size_t const length) {
    return (readUint<uint16_t>(buffer, length));
}

/// \brief uint32_t wrapper over readUint.
inline uint32_t
readUint32(void const* const buffer, size_t const length) {
    return (readUint<uint32_t>(buffer, length));
}

/// \brief uint16_t wrapper over readUint.
inline uint64_t
readUint64(void const* const buffer, size_t const length) {
    return (readUint<uint64_t>(buffer, length));
}

/// \brief uint16_t wrapper over writeUint.
inline uint8_t*
writeUint16(uint16_t const value, void* const buffer, size_t const length) {
    return (writeUint(value, buffer, length));
}

/// \brief uint32_t wrapper over writeUint.
inline uint8_t*
writeUint32(uint32_t const value, void* const buffer, size_t const length) {
    return (writeUint(value, buffer, length));
}

/// \brief uint64_t wrapper over writeUint.
inline uint8_t*
writeUint64(uint64_t const value, void* const buffer, size_t const length) {
    return (writeUint(value, buffer, length));
}

}  // namespace util
}  // namespace isc

#endif  // KEA_UTIL_IO_H
