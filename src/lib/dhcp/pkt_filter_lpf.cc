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
#include <dhcp/protocol_util.h>
#include <exceptions/exceptions.h>

#include <linux/if_ether.h>
#include <linux/if_packet.h>

using namespace isc::util;

namespace isc {
namespace dhcp {

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
PktFilterLPF::receive(const Iface&, const SocketInfo& socket_info) {
    // @todo: implement this function
    unsigned char buf[1536];
    int data_len = read(socket_info.sockfd_, buf, sizeof(buf));
    if (data_len <= 0) {
        return Pkt4Ptr();
    }

    // Length of the Ethernet, IP and UDP.
    int data_offset = 42;
    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(buf + data_offset,
                                   data_len - data_offset));
    return (pkt);
}

int
PktFilterLPF::send(const Iface& iface, uint16_t sockfd, const Pkt4Ptr& pkt) {

    OutputBuffer buf(14);

    // Ethernet frame header
    std::vector<uint8_t> dest_addr = pkt->getHWAddr()->hwaddr_;
    if (dest_addr.empty()) {
        dest_addr.resize(HWAddr::ETHERNET_HWADDR_LEN);
    }
    writeEthernetHeader(iface.getMac(), &dest_addr[0], buf);

    // IP and UDP header
    writeIpUdpHeader(pkt, buf);

    // DHCPv4 message
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
