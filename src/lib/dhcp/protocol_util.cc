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

#include <protocol_util.h>

#include <netinet/ip.h>
#include <netinet/udp.h>

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

    struct ip ip_hdr;
    memset(&ip_hdr, 0, sizeof(ip_hdr));
    ip_hdr.ip_hl = (ip_hdr.ip_hl | 5) & 0xF;
    ip_hdr.ip_v = (ip_hdr.ip_v | 4) & 0xF;
    ip_hdr.ip_tos = IPTOS_LOWDELAY;
    ip_hdr.ip_len = htons(sizeof(ip) + sizeof(udphdr) +
                          pkt->getBuffer().getLength());
    ip_hdr.ip_id = 0;
    ip_hdr.ip_off = 0;
    ip_hdr.ip_ttl = 128;
    ip_hdr.ip_p = IPPROTO_UDP;
    ip_hdr.ip_src.s_addr = htonl(pkt->getLocalAddr());
    ip_hdr.ip_dst.s_addr = htonl(pkt->getRemoteAddr());
    ip_hdr.ip_sum =
        wrapChecksum(calculateChecksum(reinterpret_cast<const char*>(&ip_hdr),
                                       sizeof(ip_hdr)));

    out_buf.writeData(static_cast<void*>(&ip_hdr), sizeof(ip_hdr));

    struct udphdr udp_hdr;
    memset(&udp_hdr, 0, sizeof(udp_hdr));
    udp_hdr.source = htons(pkt->getLocalPort());
    udp_hdr.dest = htons(pkt->getRemotePort());
    udp_hdr.len = htons(sizeof(udp_hdr) + pkt->getBuffer().getLength());
    udp_hdr.check = 0;

    out_buf.writeData(static_cast<void*>(&udp_hdr), sizeof(udp_hdr));

}

uint16_t
calculateChecksum(const char* buf, const uint32_t buf_size, uint32_t sum) {
    uint32_t i;
    for (i = 0; i < (buf_size & ~1U); i += 2) {
        uint16_t chunk = buf[i] << 8 | buf[i+1];
        sum += chunk;
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }

    if (i < buf_size) {
        sum += buf[i] << 8;
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }

    return (sum);

}

uint16_t
wrapChecksum(uint16_t sum) {
    return (htons(~sum));
}

}
}
