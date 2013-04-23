// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PROTOCOL_UTIL_H
#define PROTOCOL_UTIL_H

#include <dhcp/pkt4.h>
#include <util/buffer.h>

#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Writes ethernet frame header into a buffer.
///
/// @param src_hw_addr source HW address.
/// @param dst_hw_addr destination HW address.
/// @param [out] out_buf buffer where a header is written.
void writeEthernetHeader(const uint8_t* src_hw_addr,
                         const uint8_t* dest_hw_addr,
                         util::OutputBuffer& out_buf);

/// @brief Writes both IP and UDP header into output buffer
///
/// This utility function assembles IP and UDP packet headers for the
/// provided DHCPv4 message. The source and destination addreses and
/// ports stored in the Pkt4 object are copied as source and destination
/// addresses and ports into IP/UDP headers.
///
/// @param pkt DHCPv4 packet to be sent in IP packet
/// @param [out] out_buf buffer where an IP header is written
void writeIpUdpHeader(const Pkt4Ptr& pkt, util::OutputBuffer& out_buf);

/// @brief Calculates checksum for provided buffer
///
/// This function returns the sum of 16-bit values from the provided
/// buffer. If the third parameter is specified, it indicates the
/// initial checksum value. This parameter can be a result of
/// calcChecksum function's invocation on different data buffer.
/// The IP or UDP checksum value is a complement of the result returned
/// by this function. However, this function does not compute complement
/// of the summed values. It must be calculated outside of this function
/// before writing the value to the packet buffer.
///
/// @param buf buffer for which the checksum is calculated.
/// @param buf_size size of the buffer for which checksum is calculated.
/// @param sum initial checksum value, other values will be added to it.
///
/// @return calculated checksum.
uint16_t calcChecksum(const uint8_t* buf, const uint32_t buf_size,
                      uint32_t sum = 0);

}
}
#endif // PROTOCOL_UTIL_H
