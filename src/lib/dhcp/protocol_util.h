// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PROTOCOL_UTIL_H
#define PROTOCOL_UTIL_H

#include <dhcp/pkt4.h>
#include <util/buffer.h>

#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when error occurred during parsing packet's headers.
///
/// This exception is thrown when parsing link, Internet or Transport layer
/// header has failed.
class InvalidPacketHeader : public Exception {
public:
    InvalidPacketHeader(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// Size of the Ethernet frame header.
static const size_t ETHERNET_HEADER_LEN = 14;
/// Offset of the 2-byte word in the Ethernet packet which
/// holds the type of the protocol it encapsulates.
static const size_t ETHERNET_PACKET_TYPE_OFFSET = 12;
/// This value is held in the Ethertype field of Ethernet frame
/// and indicates that an IP packet is encapsulated with this
/// frame. In the standard headers, there is an ETHERTYPE_IP,
/// constant which serves the same purpose. However, it is more
/// convenient to have our constant because we avoid
/// inclusion of additional headers, which have different names
/// and locations on different OSes.
static const uint16_t ETHERNET_TYPE_IP = 0x0800;

/// Minimal IPv4 header length.
static const size_t MIN_IP_HEADER_LEN = 20;
/// Offset in the IP header where the flags field starts.
static const size_t IP_FLAGS_OFFSET = 6;
/// Offset of the byte in IP header which holds the type
/// of the protocol it encapsulates.
static const size_t IP_PROTO_TYPE_OFFSET = 9;
/// Offset of source address in the IPv4 header.
static const size_t IP_SRC_ADDR_OFFSET = 12;
/// Offset of destination address in the IPv4 header.
static const size_t IP_DEST_ADDR_OFFSET = 16;

/// UDP header length.
static const size_t UDP_HEADER_LEN = 8;
/// Offset within UDP header where destination port is held.
static const size_t UDP_DEST_PORT = 2;

/// @brief Decode the Ethernet header.
///
/// This function reads Ethernet frame header from the provided
/// buffer at the current read position. The source HW address
/// is read from the header and assigned as client address in
/// the pkt object. The buffer read pointer is set to the end
/// of the Ethernet frame header if read was successful.
///
/// @warning This function does not check that the provided 'pkt'
/// pointer is valid. Caller must make sure that pointer is
/// allocated.
///
/// @param buf input buffer holding header to be parsed.
/// @param [out] pkt packet object receiving HW source address read from header.
///
/// @throw InvalidPacketHeader if packet header is truncated
/// @throw BadValue if pkt object is NULL.
void decodeEthernetHeader(util::InputBuffer& buf, Pkt4Ptr& pkt);

/// @brief Decode IP and UDP header.
///
/// This function reads IP and UDP headers from the provided buffer
/// at the current read position. The source and destination IP
/// addresses and ports and read from these headers and stored in
/// the appropriate members of the pkt object.
///
/// @warning This function does not check that the provided 'pkt'
/// pointer is valid. Caller must make sure that pointer is
/// allocated.
///
/// @param buf input buffer holding headers to be parsed.
/// @param [out] pkt packet object where IP addresses and ports
/// are stored.
///
/// @throw InvalidPacketHeader if packet header is truncated
/// @throw BadValue if pkt object is NULL.
void decodeIpUdpHeader(util::InputBuffer& buf, Pkt4Ptr& pkt);

/// @brief Writes ethernet frame header into a buffer.
///
/// @warning This function does not check that the provided 'pkt'
/// pointer is valid. Caller must make sure that pointer is
/// allocated.
///
/// @param pkt packet object holding source and destination HW address.
/// @param [out] out_buf buffer where a header is written.
void writeEthernetHeader(const Pkt4Ptr& pkt,
                         util::OutputBuffer& out_buf);

/// @brief Writes both IP and UDP header into output buffer
///
/// This utility function assembles IP and UDP packet headers for the
/// provided DHCPv4 message. The source and destination addresses and
/// ports stored in the pkt object are copied as source and destination
/// addresses and ports into IP/UDP headers.
///
/// @warning This function does not check that the provided 'pkt'
/// pointer is valid. Caller must make sure that pointer is
/// allocated.
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
/// The IP header checksum calculation algorithm has been defined in
/// <a href="https://tools.ietf.org/html/rfc791#page-14">RFC 791</a>
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
