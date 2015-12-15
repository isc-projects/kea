// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/protocol_util.h>
#include <boost/static_assert.hpp>
// in_systm.h is required on some some BSD systems
// complaining that n_time is undefined but used
// in ip.h.
#include <netinet/in_systm.h>
#include <netinet/ip.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

void
decodeEthernetHeader(InputBuffer& buf, Pkt4Ptr& pkt) {
    // The size of the buffer to be parsed must not be lower
    // then the size of the Ethernet frame header.
    if (buf.getLength() - buf.getPosition() < ETHERNET_HEADER_LEN) {
        isc_throw(InvalidPacketHeader, "size of ethernet header in received "
                  << "packet is invalid, expected at least "
                  << ETHERNET_HEADER_LEN << " bytes, received "
                  << buf.getLength() - buf.getPosition() << " bytes");
    }
    // Packet object must not be NULL. We want to output some values
    // to this object.
    if (!pkt) {
        isc_throw(BadValue, "NULL packet object provided when parsing ethernet"
                  " frame header");
    }

    // The size of the single address is always lower then the size of
    // the header that holds this address. Otherwise, it is a programming
    // error that we want to detect in the compilation time.
    BOOST_STATIC_ASSERT(ETHERNET_HEADER_LEN > HWAddr::ETHERNET_HWADDR_LEN);

    // Remember initial position.
    size_t start_pos = buf.getPosition();

    // Read the destination HW address.
    std::vector<uint8_t> dest_addr;
    buf.readVector(dest_addr, HWAddr::ETHERNET_HWADDR_LEN);
    pkt->setLocalHWAddr(HWTYPE_ETHERNET, HWAddr::ETHERNET_HWADDR_LEN, dest_addr);
    // Read the source HW address.
    std::vector<uint8_t> src_addr;
    buf.readVector(src_addr, HWAddr::ETHERNET_HWADDR_LEN);
    pkt->setRemoteHWAddr(HWTYPE_ETHERNET, HWAddr::ETHERNET_HWADDR_LEN, src_addr);
    // Move the buffer read pointer to the end of the Ethernet frame header.
    buf.setPosition(start_pos + ETHERNET_HEADER_LEN);
}

void
decodeIpUdpHeader(InputBuffer& buf, Pkt4Ptr& pkt) {
    // The size of the buffer must be at least equal to the minimal size of
    // the IPv4 packet header plus UDP header length.
    if (buf.getLength() - buf.getPosition() < MIN_IP_HEADER_LEN + UDP_HEADER_LEN) {
        isc_throw(InvalidPacketHeader, "the total size of the IP and UDP headers in "
                  << "received packet is invalid, expected at least "
                  << MIN_IP_HEADER_LEN + UDP_HEADER_LEN
                  << " bytes, received " << buf.getLength() - buf.getPosition()
                  << " bytes");
    }

    // Packet object must not be NULL.
    if (!pkt) {
        isc_throw(BadValue, "NULL packet object provided when parsing IP and UDP"
                  " packet headers");
    }

    BOOST_STATIC_ASSERT(IP_SRC_ADDR_OFFSET < MIN_IP_HEADER_LEN);

    // Remember initial position of the read pointer.
    size_t start_pos = buf.getPosition();

    // Read IP header length (mask most significant bits as they indicate IP version).
    uint8_t ip_len = buf.readUint8() & 0xF;
    // IP length is the number of 4 byte chunks that construct IPv4 header.
    // It must not be lower than 5 because first 20 bytes are fixed.
    if (ip_len < 5) {
        isc_throw(InvalidPacketHeader, "Value of the length of the IP header must not be"
                  << " lower than 5 words. The length of the received header is "
                  << ip_len << ".");
    }

    // Seek to the position of source IP address.
    buf.setPosition(start_pos + IP_SRC_ADDR_OFFSET);
    // Read source address.
    pkt->setRemoteAddr(IOAddress(buf.readUint32()));
    // Read destination address.
    pkt->setLocalAddr(IOAddress(buf.readUint32()));

    // Skip IP header options (if any) to start of the
    // UDP header.
    buf.setPosition(start_pos + ip_len * 4);

    // Read source port from UDP header.
    pkt->setRemotePort(buf.readUint16());
    // Read destination port from UDP header.
    pkt->setLocalPort(buf.readUint16());

    // Set the pointer position to the first byte o the
    // UDP payload (DHCP packet).
    buf.setPosition(start_pos + ip_len * 4 + UDP_HEADER_LEN);
}

void
writeEthernetHeader(const Pkt4Ptr& pkt, OutputBuffer& out_buf) {
    // Set destination HW address.
    HWAddrPtr remote_addr = pkt->getRemoteHWAddr();
    if (remote_addr) {
        if (remote_addr->hwaddr_.size() == HWAddr::ETHERNET_HWADDR_LEN) {
            out_buf.writeData(&remote_addr->hwaddr_[0],
                              HWAddr::ETHERNET_HWADDR_LEN);
        } else {
            isc_throw(BadValue, "invalid size of the remote HW address "
                      << remote_addr->hwaddr_.size() << " when constructing"
                      << " an ethernet frame header; expected size is"
                      << " " << HWAddr::ETHERNET_HWADDR_LEN);
        }
    } else {
        // HW address has not been specified. This is possible when receiving
        // packet through a logical interface (e.g. lo). In such cases, we
        // don't want to fail but rather provide a default HW address, which
        // consists of zeros.
        out_buf.writeData(&std::vector<uint8_t>(HWAddr::ETHERNET_HWADDR_LEN)[0],
                          HWAddr::ETHERNET_HWADDR_LEN);
    }

    // Set source HW address.
    HWAddrPtr local_addr = pkt->getLocalHWAddr();
    if (local_addr) {
        if (local_addr->hwaddr_.size() == HWAddr::ETHERNET_HWADDR_LEN) {
            out_buf.writeData(&local_addr->hwaddr_[0],
                              HWAddr::ETHERNET_HWADDR_LEN);
        } else {
            isc_throw(BadValue, "invalid size of the local HW address "
                      << local_addr->hwaddr_.size() << " when constructing"
                      << " an ethernet frame header; expected size is"
                      << " " << HWAddr::ETHERNET_HWADDR_LEN);
        }
    } else {
        // Provide default HW address.
        out_buf.writeData(&std::vector<uint8_t>(HWAddr::ETHERNET_HWADDR_LEN)[0],
                          HWAddr::ETHERNET_HWADDR_LEN);
    }

    // Type IP.
    out_buf.writeUint16(ETHERNET_TYPE_IP);
}

void
writeIpUdpHeader(const Pkt4Ptr& pkt, util::OutputBuffer& out_buf) {

    out_buf.writeUint8(0x45); // IP version 4, IP header length 5
    out_buf.writeUint8(IPTOS_LOWDELAY); // DSCP and ECN
    out_buf.writeUint16(28 + pkt->getBuffer().getLength()); // Total length.
    out_buf.writeUint16(0); // Identification
    out_buf.writeUint16(0x4000); // Disable fragmentation.
    out_buf.writeUint8(128); // TTL
    out_buf.writeUint8(IPPROTO_UDP); // Protocol UDP.
    out_buf.writeUint16(0); // Temporarily set checksum to 0.
    out_buf.writeUint32(pkt->getLocalAddr()); // Source address.
    out_buf.writeUint32(pkt->getRemoteAddr()); // Destination address.

    // Calculate pseudo header checksum. It will be necessary to compute
    // UDP checksum.
    // Get the UDP length. This includes udp header's and data length.
    uint32_t udp_len = 8 + pkt->getBuffer().getLength();
    // The magic number "8" indicates the offset where the source address
    // is stored in the buffer. This offset is counted here from the
    // current tail of the buffer. Starting from this offset we calculate
    // the checksum using 8 following bytes of data. This will include
    // 4 bytes of source address and 4 bytes of destination address.
    // The IPPROTO_UDP and udp_len are also added up to the checksum.
    uint16_t pseudo_hdr_checksum =
        calcChecksum(static_cast<const uint8_t*>(out_buf.getData()) + out_buf.getLength() - 8,
                     8, IPPROTO_UDP + udp_len);

    // Calculate IP header checksum.
    uint16_t ip_checksum = ~calcChecksum(static_cast<const uint8_t*>(out_buf.getData())
                                         + out_buf.getLength() - 20, 20);
    // Write checksum in the IP header. The offset of the checksum is 10 bytes
    // back from the tail of the current buffer.
    out_buf.writeUint16At(ip_checksum, out_buf.getLength() - 10);

    // Start UDP header.
    out_buf.writeUint16(pkt->getLocalPort()); // Source port.
    out_buf.writeUint16(pkt->getRemotePort()); // Destination port.
    out_buf.writeUint16(udp_len); // Length of the header and data.

    // Checksum is calculated from the contents of UDP header, data and pseudo ip header.
    // The magic number "6" indicates that the UDP header starts at offset 6 from the
    // tail of the current buffer. These 6 bytes contain source and destination port
    // as well as the length of the header.
    uint16_t udp_checksum =
        ~calcChecksum(static_cast<const uint8_t*>(out_buf.getData()) + out_buf.getLength() - 6, 6,
                      calcChecksum(static_cast<const uint8_t*>(pkt->getBuffer().getData()),
                                   pkt->getBuffer().getLength(),
                                   pseudo_hdr_checksum));
    // Write UDP checksum.
    out_buf.writeUint16(udp_checksum);
}

uint16_t
calcChecksum(const uint8_t* buf, const uint32_t buf_size, uint32_t sum) {
    uint32_t i;
    for (i = 0; i < (buf_size & ~1U); i += 2) {
        uint16_t chunk = buf[i] << 8 | buf[i + 1];
        sum += chunk;
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }
    // If one byte has left, we also need to add it to the checksum.
    if (i < buf_size) {
        sum += buf[i] << 8;
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }

    return (sum);

}

}
}
