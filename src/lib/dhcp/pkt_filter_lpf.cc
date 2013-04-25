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
PktFilterLPF::receive(const Iface& iface, const SocketInfo& socket_info) {
    // @todo: implement this function
    uint8_t raw_buf[IfaceMgr::RCVBUFSIZE];
    int data_len = read(socket_info.sockfd_, raw_buf, sizeof(raw_buf));
    if (data_len <= 0) {
        return Pkt4Ptr();
    }

    InputBuffer buf(raw_buf, data_len);

    // @todo: This is awkward way to solve the chicken and egg problem
    // whereby we don't know the offset where DHCP data start in the
    // received buffer when we create the packet object. The dummy
    // object is created so as we can pass it to the functions which
    // decode IP stack and find actual offset of the DHCP packet.
    // Once we find the offset we can create another Pkt4 object from
    // the reminder of the input buffer and set the IP addresses and
    // ports from the dummy packet. We should consider making this
    // in some more elegant way.
    Pkt4Ptr dummy_pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 0));

    // Decode ethernet, ip and udp headers.
    decodeEthernetHeader(buf, dummy_pkt);
    decodeIpUdpHeader(buf, dummy_pkt);

    // Read the DHCP data.
    std::vector<uint8_t> dhcp_buf;
    buf.readVector(dhcp_buf, buf.getLength() - buf.getPosition());

    // Decode DHCP data into the Pkt4 object.
    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(&dhcp_buf[0], dhcp_buf.size()));

    // Set the appropriate packet members using data collected from
    // the decoded headers.
    pkt->setIndex(iface.getIndex());
    pkt->setIface(iface.getName());
    pkt->setLocalAddr(dummy_pkt->getLocalAddr());
    pkt->setRemoteAddr(dummy_pkt->getRemoteAddr());
    pkt->setLocalPort(dummy_pkt->getLocalPort());
    pkt->setRemotePort(dummy_pkt->getRemotePort());

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

    // It is likely that the local address in pkt object is set to
    // broadcast address. This is the case if server received the
    // client's packet on broadcast address. Therefore, we need to
    // correct it here and assign the actual source address.
    if (pkt->getLocalAddr().toText() == "255.255.255.255") {
        const Iface::SocketCollection& sockets = iface.getSockets();
        for (Iface::SocketCollection::const_iterator it = sockets.begin();
             it != sockets.end(); ++it) {
            if (sockfd == it->sockfd_) {
                pkt->setLocalAddr(it->addr_);
            }
        }
    }

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
