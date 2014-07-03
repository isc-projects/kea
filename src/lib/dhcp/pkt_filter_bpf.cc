// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/pkt_filter_bpf.h>
#include <dhcp/protocol_util.h>
#include <exceptions/exceptions.h>
#include <algorithm>
#include <net/bpf.h>
#include <net/ethernet.h>

namespace {

using namespace isc::dhcp;

/// @brief Maximum number of attempts to open BPF device.
const unsigned int MAX_BPF_OPEN_ATTEMPTS = 100;

/// The following structure defines a Berkely Packet Filter program to perform
/// packet filtering. The program operates on Ethernet packets.  To help with
/// interpretation of the program, for the types of Ethernet packets we are
/// interested in, the header layout is:
///
///   6 bytes  Destination Ethernet Address
///   6 bytes  Source Ethernet Address
///   2 bytes  Ethernet packet type
///
///  20 bytes  Fixed part of IP header
///  variable  Variable part of IP header
///
///   2 bytes  UDP Source port
///   2 bytes  UDP destination port
///   4 bytes  Rest of UDP header
///
/// @todo We may want to extend the filter to receive packets sent
/// to the particular IP address assigned to the interface or
/// broadcast address.
struct bpf_insn dhcp_sock_filter [] = {
    // Make sure this is an IP packet: check the half-word (two bytes)
    // at offset 12 in the packet (the Ethernet packet type).  If it
    // is, advance to the next instruction.  If not, advance 8
    // instructions (which takes execution to the last instruction in
    // the sequence: "drop it").
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS, ETHERNET_PACKET_TYPE_OFFSET),
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, ETHERTYPE_IP, 0, 8),

    // Make sure it's a UDP packet.  The IP protocol is at offset
    // 9 in the IP header so, adding the Ethernet packet header size
    // of 14 bytes gives an absolute byte offset in the packet of 23.
    BPF_STMT(BPF_LD + BPF_B + BPF_ABS, ETHERNET_HEADER_LEN + IP_PROTO_TYPE_OFFSET),
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, IPPROTO_UDP, 0, 6),

    // Make sure this isn't a fragment by checking that the fragment
    // offset field in the IP header is zero.  This field is the
    // least-significant 13 bits in the bytes at offsets 6 and 7 in
    // the IP header, so the half-word at offset 20 (6 + size of
    // Ethernet header) is loaded and an appropriate mask applied.
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS, ETHERNET_HEADER_LEN + IP_FLAGS_OFFSET),
    BPF_JUMP(BPF_JMP + BPF_JSET + BPF_K, 0x1fff, 4, 0),

    // Get the IP header length.  This is achieved by the following
    // (special) instruction that, given the offset of the start
    // of the IP header (offset 14) loads the IP header length.
    BPF_STMT(BPF_LDX + BPF_B + BPF_MSH, ETHERNET_HEADER_LEN),

    // Make sure it's to the right port.  The following instruction
    // adds the previously extracted IP header length to the given
    // offset to locate the correct byte.  The given offset of 16
    // comprises the length of the Ethernet header (14) plus the offset
    // of the UDP destination port (2) within the UDP header.
    BPF_STMT(BPF_LD + BPF_H + BPF_IND, ETHERNET_HEADER_LEN + UDP_DEST_PORT),
    // The following instruction tests against the default DHCP server port,
    // but the action port is actually set in PktFilterBPF::openSocket().
    // N.B. The code in that method assumes that this instruction is at
    // offset 8 in the program.  If this is changed, openSocket() must be
    // updated.
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, DHCP4_SERVER_PORT, 0, 1),

    // If we passed all the tests, ask for the whole packet.
    BPF_STMT(BPF_RET + BPF_K, (u_int)-1),

    // Otherwise, drop it.
    BPF_STMT(BPF_RET + BPF_K, 0),
};

}

using namespace isc::util;

namespace isc {
namespace dhcp {

SocketInfo
PktFilterBPF::openSocket(const Iface& iface,
                         const isc::asiolink::IOAddress& addr,
                         const uint16_t port, const bool,
                         const bool) {

    // Open fallback socket first. If it fails, it will give us an indication
    // that there is another service (perhaps DHCP server) running.
    // The function will throw an exception and effectivelly cease opening
    // the BPF device below.
    int fallback = openFallbackSocket(addr, port);

    // Fallback has opened so, let's open the BPF device that we will be
    // using for receiving and sending packets. The BPF device is opened
    // by opening a file /dev/bpf%d where %d is a number. There may be
    // devices already open so we will try them one by one and open the
    // one that is not busy.
    int sock = -1;
    for (unsigned int bpf_dev = 0;
         bpf_dev < MAX_BPF_OPEN_ATTEMPTS && (sock < 0);
         ++bpf_dev) {
        std::ostringstream s;
        s << "/dev/bpf" << bpf_dev;
        sock = open(s.str().c_str(), O_RDWR, 0);
        if (sock < 0) {
            // If device busy, try another one.
            if (errno == EBUSY) {
                continue;
            }
            // All other errors are fatal, so close the fallback socket
            // and throw.
            close(fallback);
            isc_throw(SocketConfigError, "Failed to open BPF device " << s);
        }
    }

    // The BPF device is now open. Now it needs to be configured.

    // Associate the device with the interface name.
    struct ifreq iface_data;
    memset(&iface_data, 0, sizeof(iface_data));
    std::strncpy(iface_data.ifr_name, iface.getName().c_str(),
                 std::min(static_cast<int>(IFNAMSIZ),
                          static_cast<int>(iface.getName().length())));
    if (ioctl(sock, BIOCSETIF, &iface_data) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Failed to associate BPF device "
                  " with interface " << iface.getName());
    }

    // Get the BPF version supported by the kernel. Every application
    // must check this version against the current version in use.
    struct bpf_version ver;
    if (ioctl(sock, BIOCVERSION, &ver) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Failed to obtain the BPF version"
                  " number from the kernel");
    }
    // Major BPF version must match and the minor version that the kernel
    // runs must be at least the current version in use.
    if ((ver.bv_major != BPF_MAJOR_VERSION) ||
        (ver.bv_minor < BPF_MINOR_VERSION)) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Invalid BPF version");
    }

    // Get the size of the read buffer for this device. We will need to
    // allocate the buffer of this size for packet reads.
    unsigned int buf_len = 0;
    if (ioctl(sock, BIOCGBLEN, &buf_len) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Unable to obtain the required"
                  " buffer legth for reads from BPF device");
    }

    // Configure the BPF program to receive packets on the specified port.
    dhcp_sock_filter[8].k = port;

    // Set the filter program so as we only get packets we are interested in.
    struct bpf_program prog;
    prog.bf_insns = dhcp_sock_filter;
    prog.bf_len = sizeof(dhcp_sock_filter) / sizeof(struct bpf_insn);
    if (ioctl(sock, BIOCSETF, &prog) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Failed to install BPF filter"
                  " program");
    }

    // Everything is ok, return the socket (BPF device descriptor) to
    // the caller.
    return (SocketInfo(addr, port, sock, fallback));
}

Pkt4Ptr
PktFilterBPF::receive(const Iface&/* iface */, const SocketInfo& /*socket_info*/) {
  return (Pkt4Ptr());
  /*    uint8_t raw_buf[IfaceMgr::RCVBUFSIZE];
    // First let's get some data from the fallback socket. The data will be
    // discarded but we don't want the socket buffer to bloat. We get the
    // packets from the socket in loop but most of the time the loop will
    // end after receiving one packet. The call to recv returns immediately
    // when there is no data left on the socket because the socket is
    // non-blocking.
    // @todo In the normal conditions, both the primary socket and the fallback
    // socket are in sync as they are set to receive packets on the same
    // address and port. The reception of packets on the fallback socket
    // shouldn't cause significant lags in packet reception. If we find in the
    // future that it does, the sort of threshold could be set for the maximum
    // bytes received on the fallback socket in a single round. Further
    // optimizations would include an asynchronous read from the fallback socket
    // when the DHCP server is idle.
    int datalen;
    do {
        datalen = recv(socket_info.fallbackfd_, raw_buf, sizeof(raw_buf), 0);
    } while (datalen > 0);

    // Now that we finished getting data from the fallback socket, we
    // have to get the data from the raw socket too.
    int data_len = read(socket_info.sockfd_, raw_buf, sizeof(raw_buf));
    // If negative value is returned by read(), it indicates that an
    // error occured. If returned value is 0, no data was read from the
    // socket. In both cases something has gone wrong, because we expect
    // that a chunk of data is there. We signal the lack of data by
    // returing an empty packet.
    if (data_len <= 0) {
        return Pkt4Ptr();
    }

    InputBuffer buf(raw_buf, data_len);

    // @todo: This is awkward way to solve the chicken and egg problem
    // whereby we don't know the offset where DHCP data start in the
    // received buffer when we create the packet object. In general case,
    // the IP header has variable length. The information about its length
    // is stored in one of its fields. Therefore, we have to decode the
    // packet to get the offset of the DHCP data. The dummy object is
    // created so as we can pass it to the functions which decode IP stack
    // and find actual offset of the DHCP data.
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

    return (pkt); */
}

int
PktFilterBPF::send(const Iface& /*iface*/, uint16_t /*sockfd*/, const Pkt4Ptr& /*pkt*/) {

  return 0;

  /*    OutputBuffer buf(14);

    // Some interfaces may have no HW address - e.g. loopback interface.
    // For these interfaces the HW address length is 0. If this is the case,
    // then we will rely on the functions which construct the IP/UDP headers
    // to provide a default HW addres. Otherwise, create the HW address
    // object using the HW address of the interface.
    if (iface.getMacLen() > 0) {
        HWAddrPtr hwaddr(new HWAddr(iface.getMac(), iface.getMacLen(),
                                    iface.getHWType()));
        pkt->setLocalHWAddr(hwaddr);
    }


    // Ethernet frame header.
    // Note that we don't validate whether HW addresses in 'pkt'
    // are valid because they are checked by the function called.
    writeEthernetHeader(pkt, buf);

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
  */
}


} // end of isc::dhcp namespace
} // end of isc namespace
