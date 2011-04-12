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

#ifndef __IO_UTILITIES_H
#define __IO_UTILITIES_H

#include <cstddef>

namespace isc {
namespace util {
namespace io {

/// \brief Read Unsigned 16-Bit Integer from Buffer
///
/// This is essentially a copy of the isc::util::InputBuffer::readUint16.  It
/// should really be moved into a separate library.
///
/// \param buffer Data buffer at least two bytes long of which the first two
///        bytes are assumed to represent a 16-bit integer in network-byte
///        order.
///
/// \return Value of 16-bit integer
inline uint16_t
readUint16(const void* buffer) {
    const uint8_t* byte_buffer = static_cast<const uint8_t*>(buffer);

    uint16_t result = (static_cast<uint16_t>(byte_buffer[0])) << 8;
    result |= static_cast<uint16_t>(byte_buffer[1]);

    return (result);
}

/// \brief Write Unisgned 16-Bit Integer to Buffer
///
/// This is essentially a copy of isc::util::OutputBuffer::writeUint16.  It
/// should really be moved into a separate library.
///
/// \param value 16-bit value to convert
/// \param buffer Data buffer at least two bytes long into which the 16-bit
///        value is written in network-byte order.

inline void
writeUint16(uint16_t value, void* buffer) {
    uint8_t* byte_buffer = static_cast<uint8_t*>(buffer);

    byte_buffer[0] = static_cast<uint8_t>((value & 0xff00U) >> 8);
    byte_buffer[1] = static_cast<uint8_t>(value & 0x00ffU);
}

} // namespace io
} // namespace util
} // namespace isc

#endif // __ASIOLINK_UTILITIES_H
