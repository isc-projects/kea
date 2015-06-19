// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/pkt_filter_inet.h>
#include <errno.h>
#include <cstring>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

PktFilterInet::PktFilterInet()
    : control_buf_len_(CMSG_SPACE(sizeof(struct in6_pktinfo))),
      control_buf_(new char[control_buf_len_])
{
}

SocketInfo
PktFilterInet::openSocket(Iface& iface,
                          const isc::asiolink::IOAddress& addr,
                          const uint16_t port,
                          const bool receive_bcast,
                          const bool send_bcast) {

    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(sockaddr));
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);

    // If we are to receive broadcast messages we have to bind
    // to "ANY" address.
    if (receive_bcast && iface.flag_broadcast_) {
        addr4.sin_addr.s_addr = INADDR_ANY;
    } else {
        addr4.sin_addr.s_addr = htonl(addr);
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(SocketConfigError, "Failed to create UDP6 socket.");
    }

#ifdef SO_BINDTODEVICE
    if (receive_bcast && iface.flag_broadcast_) {
        // Bind to device so as we receive traffic on a specific interface.
        if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, iface.getName().c_str(),
                       iface.getName().length() + 1) < 0) {
            close(sock);
            isc_throw(SocketConfigError, "Failed to set SO_BINDTODEVICE option"
                      << " on socket " << sock);
        }
    }
#endif

    if (send_bcast && iface.flag_broadcast_) {
        // Enable sending to broadcast address.
        int flag = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) < 0) {
            close(sock);
            isc_throw(SocketConfigError, "Failed to set SO_BROADCAST option"
                      << " on socket " << sock);
        }
    }

    if (bind(sock, (struct sockaddr *)&addr4, sizeof(addr4)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to bind socket " << sock
                  << " to " << addr
                  << "/port=" << port);
    }

    // if there is no support for IP_PKTINFO, we are really out of luck
    // it will be difficult to undersand, where this packet came from
#if defined(IP_PKTINFO)
    int flag = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_PKTINFO, &flag, sizeof(flag)) != 0) {
        close(sock);
        isc_throw(SocketConfigError, "setsockopt: IP_PKTINFO: failed.");
    }
#endif

    SocketInfo sock_desc(addr, port, sock);
    return (sock_desc);

}

Pkt4Ptr
PktFilterInet::receive(Iface& iface, const SocketInfo& socket_info) {
    struct sockaddr_in from_addr;
    uint8_t buf[IfaceMgr::RCVBUFSIZE];

    memset(&control_buf_[0], 0, control_buf_len_);
    memset(&from_addr, 0, sizeof(from_addr));

    // Initialize our message header structure.
    struct msghdr m;
    memset(&m, 0, sizeof(m));

    // Point so we can get the from address.
    m.msg_name = &from_addr;
    m.msg_namelen = sizeof(from_addr);

    struct iovec v;
    v.iov_base = static_cast<void*>(buf);
    v.iov_len = IfaceMgr::RCVBUFSIZE;
    m.msg_iov = &v;
    m.msg_iovlen = 1;

    // Getting the interface is a bit more involved.
    //
    // We set up some space for a "control message". We have
    // previously asked the kernel to give us packet
    // information (when we initialized the interface), so we
    // should get the destination address from that.
    m.msg_control = &control_buf_[0];
    m.msg_controllen = control_buf_len_;

    int result = recvmsg(socket_info.sockfd_, &m, 0);
    if (result < 0) {
        isc_throw(SocketReadError, "failed to receive UDP4 data");
    }

    // We have all data let's create Pkt4 object.
    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(buf, result));

    pkt->updateTimestamp();

    unsigned int ifindex = iface.getIndex();

    IOAddress from(htonl(from_addr.sin_addr.s_addr));
    uint16_t from_port = htons(from_addr.sin_port);

    // Set receiving interface based on information, which socket was used to
    // receive data. OS-specific info (see os_receive4()) may be more reliable,
    // so this value may be overwritten.
    pkt->setIndex(ifindex);
    pkt->setIface(iface.getName());
    pkt->setRemoteAddr(from);
    pkt->setRemotePort(from_port);
    pkt->setLocalPort(socket_info.port_);

// In the future the OS-specific code may be abstracted to a different
// file but for now we keep it here because there is no code yet, which
// is specific to non-Linux systems.
#if defined (IP_PKTINFO) && defined (OS_LINUX)
    struct cmsghdr* cmsg;
    struct in_pktinfo* pktinfo;
    struct in_addr to_addr;

    memset(&to_addr, 0, sizeof(to_addr));

    cmsg = CMSG_FIRSTHDR(&m);
    while (cmsg != NULL) {
        if ((cmsg->cmsg_level == IPPROTO_IP) &&
            (cmsg->cmsg_type == IP_PKTINFO)) {
            pktinfo = (struct in_pktinfo*)CMSG_DATA(cmsg);

            pkt->setIndex(pktinfo->ipi_ifindex);
            pkt->setLocalAddr(IOAddress(htonl(pktinfo->ipi_addr.s_addr)));
            break;

            // This field is useful, when we are bound to unicast
            // address e.g. 192.0.2.1 and the packet was sent to
            // broadcast. This will return broadcast address, not
            // the address we are bound to.

            // XXX: Perhaps we should uncomment this:
            // to_addr = pktinfo->ipi_spec_dst;
        }
        cmsg = CMSG_NXTHDR(&m, cmsg);
    }
#endif

    return (pkt);
}

int
PktFilterInet::send(const Iface&, uint16_t sockfd,
                    const Pkt4Ptr& pkt) {
    memset(&control_buf_[0], 0, control_buf_len_);

    // Set the target address we're sending to.
    sockaddr_in to;
    memset(&to, 0, sizeof(to));
    to.sin_family = AF_INET;
    to.sin_port = htons(pkt->getRemotePort());
    to.sin_addr.s_addr = htonl(pkt->getRemoteAddr());

    struct msghdr m;
    // Initialize our message header structure.
    memset(&m, 0, sizeof(m));
    m.msg_name = &to;
    m.msg_namelen = sizeof(to);

    // Set the data buffer we're sending. (Using this wacky
    // "scatter-gather" stuff... we only have a single chunk
    // of data to send, so we declare a single vector entry.)
    struct iovec v;
    memset(&v, 0, sizeof(v));
    // iov_base field is of void * type. We use it for packet
    // transmission, so this buffer will not be modified.
    v.iov_base = const_cast<void *>(pkt->getBuffer().getData());
    v.iov_len = pkt->getBuffer().getLength();
    m.msg_iov = &v;
    m.msg_iovlen = 1;

// In the future the OS-specific code may be abstracted to a different
// file but for now we keep it here because there is no code yet, which
// is specific to non-Linux systems.
#if defined (IP_PKTINFO) && defined (OS_LINUX)
    // Setting the interface is a bit more involved.
    //
    // We have to create a "control message", and set that to
    // define the IPv4 packet information. We set the source address
    // to handle correctly interfaces with multiple addresses.
    m.msg_control = &control_buf_[0];
    m.msg_controllen = control_buf_len_;
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&m);
    cmsg->cmsg_level = IPPROTO_IP;
    cmsg->cmsg_type = IP_PKTINFO;
    cmsg->cmsg_len = CMSG_LEN(sizeof(struct in_pktinfo));
    struct in_pktinfo* pktinfo =(struct in_pktinfo *)CMSG_DATA(cmsg);
    memset(pktinfo, 0, sizeof(struct in_pktinfo));
    pktinfo->ipi_ifindex = pkt->getIndex();
    pktinfo->ipi_spec_dst.s_addr = htonl(pkt->getLocalAddr()); // set the source IP address
    m.msg_controllen = CMSG_SPACE(sizeof(struct in_pktinfo));
#endif

    pkt->updateTimestamp();

    int result = sendmsg(sockfd, &m, 0);
    if (result < 0) {
        isc_throw(SocketWriteError, "pkt4 send failed: sendmsg() returned "
                  " with an error: " << strerror(errno));
    }

    return (result);
}



} // end of isc::dhcp namespace
} // end of isc namespace
