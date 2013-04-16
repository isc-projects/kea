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

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_lpf.h>
#include <exceptions/exceptions.h>

#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

using namespace isc::util;

namespace isc {
namespace dhcp {

void
PktFilterLPF::assembleEthernetHeader(const Iface& iface,
                                     const Pkt4Ptr& pkt,
                                     util::OutputBuffer& out_buf) {

    std::vector<uint8_t> dest_addr = pkt->getHWAddr()->hwaddr_;
    if (dest_addr.empty()) {
        dest_addr.resize(HWAddr::ETHERNET_HWADDR_LEN);
    }
    out_buf.writeData(&dest_addr[0], dest_addr.size());
    out_buf.writeData(iface.getMac(), iface.getMacLen());

    out_buf.writeUint16(0x0800);
}

void
PktFilterLPF::assembleIpUdpHeader(const Pkt4Ptr& pkt,
                                  util::OutputBuffer& out_buf) {

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
    ip_hdr.ip_sum = checksumFinish(checksum(reinterpret_cast<const char*>(&ip_hdr),
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
PktFilterLPF::checksum(const char* buf, const uint32_t buf_size,
                       uint32_t sum) {

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
PktFilterLPF::checksumFinish(uint16_t sum) {
    return (htons(~sum));
}

int
PktFilterLPF::openSocket(const Iface& iface, const isc::asiolink::IOAddress&,
                         const uint16_t, const bool,
                         const bool) {

    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        isc_throw(SocketConfigError, "Failed to create raw LPF socket");
    }

    struct sockaddr_ll sa;
    memset(&sa, 0, sizeof(sockaddr_ll));
    sa.sll_family = AF_PACKET;
    sa.sll_ifindex = iface.getIndex();

    if (bind(sock, reinterpret_cast<const struct sockaddr*>(&sa),
             sizeof(sa)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to bind LPF socket '" << sock
                  << "' to interface '" << iface.getName() << "'");
    }

    return (sock);

}

Pkt4Ptr
PktFilterLPF::receive(const Iface&, const SocketInfo&) {
    isc_throw(isc::NotImplemented,
              "Linux Packet Filtering is not implemented yet");
}

int
PktFilterLPF::send(const Iface& iface, uint16_t sockfd, const Pkt4Ptr& pkt) {

    OutputBuffer buf(14);

    assembleEthernetHeader(iface, pkt, buf);
    assembleIpUdpHeader(pkt, buf);

    buf.writeData(pkt->getBuffer().getData(), pkt->getBuffer().getLength());

    sockaddr_ll sa;
    sa.sll_family = AF_PACKET;
    sa.sll_ifindex = iface.getIndex();
    sa.sll_protocol = htons(ETH_P_IP);
    sa.sll_halen = 6;

    int result = sendto(sockfd, buf.getData(), buf.getLength(), 0,
                        reinterpret_cast<const struct sockaddr*>(&sa),
                        sizeof(sockaddr_ll));
    if (result < 0) {
        isc_throw(SocketWriteError, "pkt4 send failed");
    }
    
    return (0);
    
}


} // end of isc::dhcp namespace
} // end of isc namespace
