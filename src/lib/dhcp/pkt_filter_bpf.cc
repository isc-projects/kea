// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_bpf.h>
#include <dhcp/protocol_util.h>
#include <exceptions/exceptions.h>
#include <algorithm>
#include <net/bpf.h>
#include <netinet/if_ether.h>

namespace {

using namespace isc::dhcp;

/// @brief Maximum number of attempts to open BPF device.
const unsigned int MAX_BPF_OPEN_ATTEMPTS = 100;

/// @brief Length of the header containing the address family for the packet
/// received on local loopback interface.
const unsigned int BPF_LOCAL_LOOPBACK_HEADER_LEN = 4;

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
/// Each instruction is preceded with the comment giving the instruction
/// number within a BPF program, in the following format: #123.
///
/// @todo We may want to extend the filter to receive packets sent
/// to the particular IP address assigned to the interface or
/// broadcast address.
struct bpf_insn ethernet_ip_udp_filter [] = {
    // Make sure this is an IP packet: check the half-word (two bytes)
    // at offset 12 in the packet (the Ethernet packet type).  If it
    // is, advance to the next instruction.  If not, advance 11
    // instructions (which takes execution to the last instruction in
    // the sequence: "drop it").
    // #0
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS, ETHERNET_PACKET_TYPE_OFFSET),
    // #1
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, ETHERTYPE_IP, 0, 11),

    // Make sure it's a UDP packet.  The IP protocol is at offset
    // 9 in the IP header so, adding the Ethernet packet header size
    // of 14 bytes gives an absolute byte offset in the packet of 23.
    // #2
    BPF_STMT(BPF_LD + BPF_B + BPF_ABS,
             ETHERNET_HEADER_LEN + IP_PROTO_TYPE_OFFSET),
    // #3
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, IPPROTO_UDP, 0, 9),

    // Make sure this isn't a fragment by checking that the fragment
    // offset field in the IP header is zero.  This field is the
    // least-significant 13 bits in the bytes at offsets 6 and 7 in
    // the IP header, so the half-word at offset 20 (6 + size of
    // Ethernet header) is loaded and an appropriate mask applied.
    // #4
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS, ETHERNET_HEADER_LEN + IP_FLAGS_OFFSET),
    // #5
    BPF_JUMP(BPF_JMP + BPF_JSET + BPF_K, 0x1fff, 7, 0),

    // Check the packet's destination address. The program will only
    // allow the packets sent to the broadcast address or unicast
    // to the specific address on the interface. By default, this
    // address is set to 0 and must be set to the specific value
    // when the raw socket is created and the program is attached
    // to it. The caller must assign the address to the
    // prog.bf_insns[8].k in the network byte order.
    // #6
    BPF_STMT(BPF_LD + BPF_W + BPF_ABS,
             ETHERNET_HEADER_LEN + IP_DEST_ADDR_OFFSET),
    // If this is a broadcast address, skip the next check.
    // #7
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 0xffffffff, 1, 0),
    // If this is not broadcast address, compare it with the unicast
    // address specified for the interface.
    // #8
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 0x00000000, 0, 4),

    // Get the IP header length.  This is achieved by the following
    // (special) instruction that, given the offset of the start
    // of the IP header (offset 14) loads the IP header length.
    // #9
    BPF_STMT(BPF_LDX + BPF_B + BPF_MSH, ETHERNET_HEADER_LEN),

    // Make sure it's to the right port.  The following instruction
    // adds the previously extracted IP header length to the given
    // offset to locate the correct byte.  The given offset of 16
    // comprises the length of the Ethernet header (14) plus the offset
    // of the UDP destination port (2) within the UDP header.
    // #10
    BPF_STMT(BPF_LD + BPF_H + BPF_IND, ETHERNET_HEADER_LEN + UDP_DEST_PORT),
    // The following instruction tests against the default DHCP server port,
    // but the action port is actually set in PktFilterBPF::openSocket().
    // N.B. The code in that method assumes that this instruction is at
    // offset 11 in the program.  If this is changed, openSocket() must be
    // updated.
    // #11
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, DHCP4_SERVER_PORT, 0, 1),

    // If we passed all the tests, ask for the whole packet.
    // #12
    BPF_STMT(BPF_RET + BPF_K, (u_int)-1),

    // Otherwise, drop it.
    // #13
    BPF_STMT(BPF_RET + BPF_K, 0),
};

/// The following structure defines a BPF program to perform packet filtering
/// on local loopback interface. The packets received on this interface do not
/// contain the regular link-layer header, but rather a 4-byte long pseudo
/// header containing the address family. The reminder of the packet contains
/// IP header, UDP header and a DHCP message.
///
/// Each instruction is preceded with the comment giving the instruction
/// number within a BPF program, in the following format: #123.
struct bpf_insn loopback_ip_udp_filter [] = {
    // Make sure this is an IP packet. The pseudo header comprises a 4-byte
    // long value identifying the address family, which should be set to
    // AF_INET. The default value used here (0xFFFFFFFF) must be overriden
    // with htonl(AF_INET) from within the openSocket function.
    // #0
    BPF_STMT(BPF_LD + BPF_W + BPF_ABS, 0),
    // #1
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 0xFFFFFFFF, 0, 11),

    // Make sure it's a UDP packet.  The IP protocol is at offset
    // 9 in the IP header so, adding the pseudo header size 4 bytes
    // gives an absolute byte offset in the packet of 13.
    // #2
    BPF_STMT(BPF_LD + BPF_B + BPF_ABS,
             BPF_LOCAL_LOOPBACK_HEADER_LEN + IP_PROTO_TYPE_OFFSET),
    // #3
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, IPPROTO_UDP, 0, 9),

    // Make sure this isn't a fragment by checking that the fragment
    // offset field in the IP header is zero.  This field is the
    // least-significant 13 bits in the bytes at offsets 6 and 7 in
    // the IP header, so the half-word at offset 10 (6 + size of
    // pseudo header) is loaded and an appropriate mask applied.
    // #4
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS,
             BPF_LOCAL_LOOPBACK_HEADER_LEN + IP_FLAGS_OFFSET),
    // #5
    BPF_JUMP(BPF_JMP + BPF_JSET + BPF_K, 0x1fff, 7, 0),

    // Check the packet's destination address. The program will only
    // allow the packets sent to the broadcast address or unicast
    // to the specific address on the interface. By default, this
    // address is set to 0 and must be set to the specific value
    // when the raw socket is created and the program is attached
    // to it. The caller must assign the address to the
    // prog.bf_insns[8].k in the network byte order.
    // #6
    BPF_STMT(BPF_LD + BPF_W + BPF_ABS,
             BPF_LOCAL_LOOPBACK_HEADER_LEN + IP_DEST_ADDR_OFFSET),
    // If this is a broadcast address, skip the next check.
    // #7
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 0xffffffff, 1, 0),
    // If this is not broadcast address, compare it with the unicast
    // address specified for the interface.
    // #8
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 0x00000000, 0, 4),

    // Get the IP header length.  This is achieved by the following
    // (special) instruction that, given the offset of the start
    // of the IP header (offset 4) loads the IP header length.
    // #9
    BPF_STMT(BPF_LDX + BPF_B + BPF_MSH, BPF_LOCAL_LOOPBACK_HEADER_LEN),

    // Make sure it's to the right port.  The following instruction
    // adds the previously extracted IP header length to the given
    // offset to locate the correct byte.  The given offset of 6
    // comprises the length of the pseudo header (4) plus the offset
    // of the UDP destination port (2) within the UDP header.
    // #10
    BPF_STMT(BPF_LD + BPF_H + BPF_IND,
             BPF_LOCAL_LOOPBACK_HEADER_LEN + UDP_DEST_PORT),
    // The following instruction tests against the default DHCP server port,
    // but the action port is actually set in PktFilterBPF::openSocket().
    // N.B. The code in that method assumes that this instruction is at
    // offset 11 in the program.  If this is changed, openSocket() must be
    // updated.
    // #11
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, DHCP4_SERVER_PORT, 0, 1),

    // If we passed all the tests, ask for the whole packet.
    // #12
    BPF_STMT(BPF_RET + BPF_K, (u_int)-1),

    // Otherwise, drop it.
    // #13
    BPF_STMT(BPF_RET + BPF_K, 0),
};


}

using namespace isc::util;

namespace isc {
namespace dhcp {

SocketInfo
PktFilterBPF::openSocket(Iface& iface,
                         const isc::asiolink::IOAddress& addr,
                         const uint16_t port, const bool,
                         const bool) {

    // Open fallback socket first. If it fails, it will give us an indication
    // that there is another service (perhaps DHCP server) running.
    // The function will throw an exception and effectivelly cease opening
    // the BPF device below.
    int fallback = openFallbackSocket(addr, port);

    // Fallback has opened, so let's open the BPF device that we will be
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
            // If device is busy, try another one.
            if (errno == EBUSY) {
                continue;
            }
            // All other errors are fatal, so close the fallback socket
            // and throw.
            close(fallback);
            isc_throw(SocketConfigError,
                      "Failed to open BPF device " << s.str());
        }
    }

    // Set the close-on-exec flag.
    if (fcntl(sock, F_SETFD, FD_CLOEXEC) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Failed to set close-on-exec flag"
                  << " on BPF device with interface " << iface.getName());
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
        isc_throw(SocketConfigError, "Invalid BPF version: "
                  << ver.bv_major << "." << ver.bv_minor
                  << " Expected at least version:"
                  << BPF_MAJOR_VERSION << "."
                  << BPF_MINOR_VERSION);
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

    if (buf_len < sizeof(bpf_hdr)) {
        isc_throw(SocketConfigError, "read buffer length returned by the"
                  " kernel for the BPF device associated with the interface"
                  << iface.getName() << " is lower than the BPF header"
                  " length: this condition is impossible unless the"
                  " operating system is really broken!");
    }

    // Set the filter program so as we only get packets we are interested in.
    struct bpf_program prog;
    memset(&prog, 0, sizeof(bpf_program));
    if (iface.flag_loopback_) {
        prog.bf_insns = loopback_ip_udp_filter;
        prog.bf_len = sizeof(loopback_ip_udp_filter) / sizeof(struct bpf_insn);
        // The address family is AF_INET. It can't be hardcoded in the BPF program
        // because we need to make the host to network order conversion using htonl
        // and conversion can't be done within the BPF program structure as it
        // doesn't work on some systems.
        prog.bf_insns[1].k = htonl(AF_INET);

    } else {
        prog.bf_insns = ethernet_ip_udp_filter;
        prog.bf_len = sizeof(ethernet_ip_udp_filter) / sizeof(struct bpf_insn);
    }

    // Configure the BPF program to receive unicast packets sent to the
    // specified address. The program will also allow packets sent to the
    // 255.255.255.255 broadcast address.
    prog.bf_insns[8].k = static_cast<uint32_t>(addr);

    // Configure the BPF program to receive packets on the specified port.
    prog.bf_insns[11].k = port;

    // Actually set the filter program for the device.
    if (ioctl(sock, BIOCSETF, &prog) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Failed to install BPF filter"
                  " program");
    }

    // Configure the BPF device to use the immediate mode. This ensures
    // that the read function returns immediatelly, instead of waiting
    // for the kernel to fill up the buffer, which would likely cause
    // read hangs.
    int flag = 1;
    if (ioctl(sock, BIOCIMMEDIATE, &flag) < 0) {
        close(fallback);
        close(sock);
        isc_throw(SocketConfigError, "Failed to set promiscious mode for"
                  " BPF device");
    }

    // Everything is ok, allocate the read buffer and return the socket
    // (BPF device descriptor) to the caller.
    try {
        iface.resizeReadBuffer(buf_len);

    } catch (...) {
        close(fallback);
        close(sock);
        throw;
    }
    return (SocketInfo(addr, port, sock, fallback));
}

Pkt4Ptr
PktFilterBPF::receive(Iface& iface, const SocketInfo& socket_info) {
    // When using BPF, the read buffer must be allocated for the interface.
    // If it is not allocated, it is a programmatic error.
    if (iface.getReadBufferSize() == 0) {
        isc_throw(SocketConfigError, "socket read buffer empty"
                  " for the interface: " << iface.getName());
    }

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
        datalen = recv(socket_info.fallbackfd_, iface.getReadBuffer(),
                       iface.getReadBufferSize(), 0);
    } while (datalen > 0);

    datalen = read(socket_info.sockfd_, iface.getReadBuffer(),
                   iface.getReadBufferSize());
    // If negative value is returned by read(), it indicates that an
    // error occured. If returned value is 0, no data was read from the
    // socket. In both cases something has gone wrong, because we expect
    // that a chunk of data is there. We signal the lack of data by
    // returing an empty packet.
    if (datalen <= 0) {
        return Pkt4Ptr();
    }
    datalen = BPF_WORDALIGN(datalen);

    // Holds BPF header.
    struct bpf_hdr bpfh;

    /// @todo BPF may occasionally append more than one packet in a
    /// single read. Our current libdhcp++ API is oriented towards receiving
    /// one packet at the time so we just pick first usable packet here
    /// and drop other packets. In the future the additional packets should
    /// be queued and processed. For now, we just iterate over the packets
    /// in the buffer and pick the first usable one.
    int offset = 0;
    while (offset < datalen) {
        // Check if the BPF header fits in the reminder of the buffer.
        // If it doesn't something is really wrong.
        if (datalen - offset < sizeof(bpf_hdr)) {
            isc_throw(SocketReadError, "packet received over the BPF device on"
                      " interface " << iface.getName() << " has a truncated "
                      " BPF header");
        }

        // Copy the BPF header.
        memcpy(static_cast<void*>(&bpfh),
               static_cast<void*>(iface.getReadBuffer()),
               sizeof(bpfh));

        // Check if the captured data fit into the reminder of the buffer.
        // Again, something is really wrong here if it doesn't fit.
        if (offset + bpfh.bh_hdrlen + bpfh.bh_caplen > datalen) {
            isc_throw(SocketReadError, "packet received from the BPF device"
                      << " attached to interface " << iface.getName()
                      << " is truncated");
        }

        // Check if the whole packet has been captured.
        if (bpfh.bh_caplen != bpfh.bh_datalen) {
            // Not whole packet captured, proceed to next received packet.
            offset = BPF_WORDALIGN(offset + bpfh.bh_hdrlen + bpfh.bh_caplen);
            continue;
        }

        // All checks passed, let's use the packet at the offset found.
        // Typically it will be at offset 0.
        break;
    };

    // No parsable packet found, so return.
    if (offset >= datalen) {
        return (Pkt4Ptr());
    }

    // Skip the BPF header and create the buffer holding a frame.
    InputBuffer buf(iface.getReadBuffer() + offset + bpfh.bh_hdrlen,
                    datalen - bpfh.bh_hdrlen - offset);


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

    // On local loopback interface the ethernet header is not present.
    // Instead, there is a 4-byte long pseudo header containing the
    // address family in the host byte order.
    if (iface.flag_loopback_) {
        if (buf.getLength() < BPF_LOCAL_LOOPBACK_HEADER_LEN) {
            isc_throw(SocketReadError, "packet received on local loopback"
                      " interface " << iface.getName() << " doesn't contain"
                      " the pseudo header with the address family type");
        }
        // Advance to the position of the IP header. We don't check the
        // contents of the pseudo header because the BPF filter should have
        // filtered out the packets with address family other than AF_INET.
        buf.setPosition(BPF_LOCAL_LOOPBACK_HEADER_LEN);

        // Since we don't decode the real link-layer header we need to
        // supply the hardware address ourselves.
        dummy_pkt->setLocalHWAddr(HWAddrPtr(new HWAddr()));
        dummy_pkt->setRemoteHWAddr(HWAddrPtr(new HWAddr()));

    } else {
        // If we are on the interface other than local loopback, assume
        // the ethernet header. For now we don't support any other data
        // link layer.
        decodeEthernetHeader(buf, dummy_pkt);
    }

    // Decode IP/UDP headers.
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
PktFilterBPF::send(const Iface& iface, uint16_t sockfd, const Pkt4Ptr& pkt) {

    OutputBuffer buf(14);

    // Some interfaces may have no HW address - e.g. loopback interface.
    // For these interfaces the HW address length is 0. If this is the case,
    // then we will rely on the functions which construct the IP/UDP headers
    // to provide a default HW address. Otherwise, create the HW address
    // object using the HW address of the interface.
    if (iface.getMacLen() > 0) {
        HWAddrPtr hwaddr(new HWAddr(iface.getMac(), iface.getMacLen(),
                                    iface.getHWType()));
        pkt->setLocalHWAddr(hwaddr);
    }

    /// Loopback interface requires special treatment. It doesn't
    /// use the ethernet header but rather a 4-bytes long pseudo header
    /// holding an address family type (see bpf.c in OS sources).
    if (iface.flag_loopback_) {
        writeAFPseudoHeader(AF_INET, buf);

    } else {
        // Ethernet frame header.
        // Note that we don't validate whether HW addresses in 'pkt'
        // are valid because they are validated by the function called.
        writeEthernetHeader(pkt, buf);
    }

    // IP and UDP header
    writeIpUdpHeader(pkt, buf);

    // DHCPv4 message
    buf.writeData(pkt->getBuffer().getData(), pkt->getBuffer().getLength());

    int result = write(sockfd, buf.getData(), buf.getLength());
    if (result < 0) {
        isc_throw(SocketWriteError, "failed to send DHCPv4 packet: "
                  << strerror(errno));
    }

    return (0);
}

void
PktFilterBPF::writeAFPseudoHeader(const uint32_t address_family,
                                  util::OutputBuffer& out_buf) {
    // Copy address family to the temporary buffer and preserve the
    // bytes order.
    uint8_t af_buf[4];
    memcpy(static_cast<void*>(af_buf),
           static_cast<const void*>(&address_family),
           sizeof(af_buf));
    // Write the data into the buffer.
    out_buf.writeData(af_buf, sizeof(af_buf));
}

} // end of isc::dhcp namespace
} // end of isc namespace
