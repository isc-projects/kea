// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <protocol_util.h>
#include <netinet/ip.h>

namespace isc {
namespace dhcp {

void
writeEthernetHeader(const uint8_t* src_hw_addr, const uint8_t* dest_hw_addr,
                    util::OutputBuffer& out_buf) {
    // Write destination and source address.
    out_buf.writeData(dest_hw_addr, HWAddr::ETHERNET_HWADDR_LEN);
    out_buf.writeData(src_hw_addr, HWAddr::ETHERNET_HWADDR_LEN);
    // Type IP.
    out_buf.writeUint16(0x0800);
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
        uint16_t chunk = buf[i] << 8 | buf[i+1];
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
