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
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_lpf.h>
#include <dhcp/protocol_util.h>
#include <exceptions/exceptions.h>
#include <linux/filter.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

namespace {

/// Socket filter program, used to filter out all traffic other
/// then DHCP. In particular, it allows receipt of UDP packets
/// on a specific (customizable) port. It does not allow fragmented
/// packets.
///
/// Socket filter program is platform independent code which is
/// executed on the kernel level when new packet arrives. This concept
/// origins from the Berkeley Packet Filtering supported on BSD systems.
///
/// @todo We may want to extend the filter to receive packets sent
/// to the particular IP address assigned to the interface or
/// broadcast address.
struct sock_filter dhcp_sock_filter [] = {
    // Make sure this is an IP packet...
    BPF_STMT (BPF_LD + BPF_H + BPF_ABS, 12),
    BPF_JUMP (BPF_JMP + BPF_JEQ + BPF_K, ETHERTYPE_IP, 0, 8),

    // Make sure it's a UDP packet...
    BPF_STMT (BPF_LD + BPF_B + BPF_ABS, 23),
    BPF_JUMP (BPF_JMP + BPF_JEQ + BPF_K, IPPROTO_UDP, 0, 6),

    // Make sure this isn't a fragment...
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS, 20),
    BPF_JUMP(BPF_JMP + BPF_JSET + BPF_K, 0x1fff, 4, 0),

    // Get the IP header length...
    BPF_STMT (BPF_LDX + BPF_B + BPF_MSH, 14),

    // Make sure it's to the right port...
    BPF_STMT (BPF_LD + BPF_H + BPF_IND, 16),
    // Use default DHCP server port, but it can be
    // replaced if neccessary.
    BPF_JUMP (BPF_JMP + BPF_JEQ + BPF_K, isc::dhcp::DHCP4_SERVER_PORT, 0, 1),

    // If we passed all the tests, ask for the whole packet.
    BPF_STMT(BPF_RET+BPF_K, (u_int)-1),

    // Otherwise, drop it.
    BPF_STMT(BPF_RET+BPF_K, 0),
};

}

using namespace isc::util;

namespace isc {
namespace dhcp {

int
PktFilterLPF::openSocket(const Iface& iface, const isc::asiolink::IOAddress&,
                         const uint16_t port, const bool,
                         const bool) {

    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        isc_throw(SocketConfigError, "Failed to create raw LPF socket");
    }

    // Create socket filter program. This program will only allow incoming UDP
    // traffic which arrives on the specific (DHCP) port). It will also filter
    // out all fragmented packets.
    struct sock_fprog filter_program;
    memset(&filter_program, 0, sizeof(filter_program));

    filter_program.filter = dhcp_sock_filter;
    filter_program.len = sizeof(dhcp_sock_filter) / sizeof(struct sock_filter);
    // Override the default port value.
    dhcp_sock_filter[8].k = port;
    // Apply the filter.
    if (setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &filter_program,
                   sizeof(filter_program)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to install packet filtering program"
                  << " on the socket " << sock);
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
    // ports from the dummy packet. We should consider doing it
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
    pkt->setLocalHWAddr(dummy_pkt->getLocalHWAddr());
    pkt->setRemoteHWAddr(dummy_pkt->getRemoteHWAddr());

    return (pkt);
}

int
PktFilterLPF::send(const Iface& iface, uint16_t sockfd, const Pkt4Ptr& pkt) {

    OutputBuffer buf(14);

    HWAddrPtr hwaddr(new HWAddr(iface.getMac(), iface.getMacLen(),
                                iface.getHWType()));
    pkt->setLocalHWAddr(hwaddr);


    // Ethernet frame header.
    // Note that we don't validate whether HW addresses in 'pkt'
    // are valid because they are checked by the function called.
    writeEthernetHeader(pkt, buf);

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
        isc_throw(SocketWriteError, "failed to send DHCPv4 packet, errno="
                  << errno << " (check errno.h)");
    }

    return (0);

}


} // end of isc::dhcp namespace
} // end of isc namespace
