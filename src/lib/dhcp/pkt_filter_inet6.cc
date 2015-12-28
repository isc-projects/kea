// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcp/pkt_filter_inet6.h>
#include <util/io/pktinfo_utilities.h>

#include <fcntl.h>
#include <netinet/in.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

PktFilterInet6::PktFilterInet6()
: control_buf_len_(CMSG_SPACE(sizeof(struct in6_pktinfo))),
    control_buf_(new char[control_buf_len_]) {
}

SocketInfo
PktFilterInet6::openSocket(const Iface& iface,
                           const isc::asiolink::IOAddress& addr,
                           const uint16_t port,
                           const bool join_multicast) {
    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port);
    // sin6_scope_id must be set to interface index for link-local addresses.
    // For unspecified addresses we set the scope id to the interface index
    // to handle the case when the IfaceMgr is opening a socket which will
    // join the multicast group. Such socket is bound to in6addr_any.
    if (addr.isV6Multicast() ||
        (addr.isV6LinkLocal() && (addr != IOAddress("::1"))) ||
        (addr == IOAddress("::"))) {
        addr6.sin6_scope_id = if_nametoindex(iface.getName().c_str());
    }

    // Copy the address if it has been specified.
    if (addr != IOAddress("::")) {
        memcpy(&addr6.sin6_addr, &addr.toBytes()[0], sizeof(addr6.sin6_addr));
    }
#ifdef HAVE_SA_LEN
    addr6.sin6_len = sizeof(addr6);
#endif

    // @todo use sockcreator once it becomes available

    // make a socket
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(SocketConfigError, "Failed to create UDP6 socket.");
    }

    // Set the close-on-exec flag.
    if (fcntl(sock, F_SETFD, FD_CLOEXEC) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to set close-on-exec flag"
                  << " on IPv6 socket.");
    }

    // Set SO_REUSEADDR option.
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&flag, sizeof(flag)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Can't set SO_REUSEADDR option on IPv6"
                  " socket.");
    }

#ifdef SO_REUSEPORT
    // Set SO_REUSEPORT has to be set to open multiple sockets and bind to
    // in6addr_any (binding to port). Binding to port is required on some
    // operating systems, e.g. NetBSD and OpenBSD so as the socket can
    // join the socket to multicast group.
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT,
                   (char *)&flag, sizeof(flag)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Can't set SO_REUSEPORT option on IPv6"
                  " socket.");
    }
#endif

    if (bind(sock, (struct sockaddr *)&addr6, sizeof(addr6)) < 0) {
        // Get the error message immediately after the bind because the
        // invocation to close() below would override the errno.
        char* errmsg = strerror(errno);
        close(sock);
        isc_throw(SocketConfigError, "Failed to bind socket " << sock << " to "
                  << addr.toText() << "/port=" << port
                  << ": " << errmsg);
    }
#ifdef IPV6_RECVPKTINFO
    // RFC3542 - a new way
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_RECVPKTINFO,
                   &flag, sizeof(flag)) != 0) {
        close(sock);
        isc_throw(SocketConfigError, "setsockopt: IPV6_RECVPKTINFO failed.");
    }
#else
    // RFC2292 - an old way
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_PKTINFO,
                   &flag, sizeof(flag)) != 0) {
        close(sock);
        isc_throw(SocketConfigError, "setsockopt: IPV6_PKTINFO: failed.");
    }
#endif

    // Join All_DHCP_Relay_Agents_and_Servers multicast group if
    // requested.
    if (join_multicast &&
        !joinMulticast(sock, iface.getName(),
                       std::string(ALL_DHCP_RELAY_AGENTS_AND_SERVERS))) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to join "
                  << ALL_DHCP_RELAY_AGENTS_AND_SERVERS
                  << " multicast group.");
    }

    return (SocketInfo(addr, port, sock));
}

Pkt6Ptr
PktFilterInet6::receive(const SocketInfo& socket_info) {
    // Now we have a socket, let's get some data from it!
    uint8_t buf[IfaceMgr::RCVBUFSIZE];
    memset(&control_buf_[0], 0, control_buf_len_);
    struct sockaddr_in6 from;
    memset(&from, 0, sizeof(from));

    // Initialize our message header structure.
    struct msghdr m;
    memset(&m, 0, sizeof(m));

    // Point so we can get the from address.
    m.msg_name = &from;
    m.msg_namelen = sizeof(from);

    // Set the data buffer we're receiving. (Using this wacky
    // "scatter-gather" stuff... but we that doesn't really make
    // sense for us, so we use a single vector entry.)
    struct iovec v;
    memset(&v, 0, sizeof(v));
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

    struct in6_addr to_addr;
    memset(&to_addr, 0, sizeof(to_addr));

    int ifindex = -1;
    if (result >= 0) {
        struct in6_pktinfo* pktinfo = NULL;


        // If we did read successfully, then we need to loop
        // through the control messages we received and
        // find the one with our destination address.
        //
        // We also keep a flag to see if we found it. If we
        // didn't, then we consider this to be an error.
        bool found_pktinfo = false;
        struct cmsghdr* cmsg = CMSG_FIRSTHDR(&m);
        while (cmsg != NULL) {
            if ((cmsg->cmsg_level == IPPROTO_IPV6) &&
                (cmsg->cmsg_type == IPV6_PKTINFO)) {
                pktinfo = util::io::internal::convertPktInfo6(CMSG_DATA(cmsg));
                to_addr = pktinfo->ipi6_addr;
                ifindex = pktinfo->ipi6_ifindex;
                found_pktinfo = true;
                break;
            }
            cmsg = CMSG_NXTHDR(&m, cmsg);
        }
        if (!found_pktinfo) {
            isc_throw(SocketReadError, "unable to find pktinfo");
        }
    } else {
        isc_throw(SocketReadError, "failed to receive data");
    }

    // Filter out packets sent to global unicast address (not link local and
    // not multicast) if the socket is set to listen multicast traffic and
    // is bound to in6addr_any. The traffic sent to global unicast address is
    // received via dedicated socket.
    IOAddress local_addr = IOAddress::fromBytes(AF_INET6,
                      reinterpret_cast<const uint8_t*>(&to_addr));
    if ((socket_info.addr_ == IOAddress("::")) &&
        !(local_addr.isV6Multicast() || local_addr.isV6LinkLocal())) {
        return (Pkt6Ptr());
    }

    // Let's create a packet.
    Pkt6Ptr pkt;
    try {
        pkt = Pkt6Ptr(new Pkt6(buf, result));
    } catch (const std::exception& ex) {
        isc_throw(SocketReadError, "failed to create new packet");
    }

    pkt->updateTimestamp();

    pkt->setLocalAddr(IOAddress::fromBytes(AF_INET6,
                      reinterpret_cast<const uint8_t*>(&to_addr)));
    pkt->setRemoteAddr(IOAddress::fromBytes(AF_INET6,
                       reinterpret_cast<const uint8_t*>(&from.sin6_addr)));
    pkt->setRemotePort(ntohs(from.sin6_port));
    pkt->setIndex(ifindex);

    IfacePtr received = IfaceMgr::instance().getIface(pkt->getIndex());
    if (received) {
        pkt->setIface(received->getName());
    } else {
        isc_throw(SocketReadError, "received packet over unknown interface"
                  << "(ifindex=" << pkt->getIndex() << ")");
    }

    return (pkt);

}

int
PktFilterInet6::send(const Iface&, uint16_t sockfd, const Pkt6Ptr& pkt) {

    memset(&control_buf_[0], 0, control_buf_len_);

    // Set the target address we're sending to.
    sockaddr_in6 to;
    memset(&to, 0, sizeof(to));
    to.sin6_family = AF_INET6;
    to.sin6_port = htons(pkt->getRemotePort());
    memcpy(&to.sin6_addr,
           &pkt->getRemoteAddr().toBytes()[0],
           16);
    to.sin6_scope_id = pkt->getIndex();

    // Initialize our message header structure.
    struct msghdr m;
    memset(&m, 0, sizeof(m));
    m.msg_name = &to;
    m.msg_namelen = sizeof(to);

    // Set the data buffer we're sending. (Using this wacky
    // "scatter-gather" stuff... we only have a single chunk
    // of data to send, so we declare a single vector entry.)

    // As v structure is a C-style is used for both sending and
    // receiving data, it is shared between sending and receiving
    // (sendmsg and recvmsg). It is also defined in system headers,
    // so we have no control over its definition. To set iov_base
    // (defined as void*) we must use const cast from void *.
    // Otherwise C++ compiler would complain that we are trying
    // to assign const void* to void*.
    struct iovec v;
    memset(&v, 0, sizeof(v));
    v.iov_base = const_cast<void *>(pkt->getBuffer().getData());
    v.iov_len = pkt->getBuffer().getLength();
    m.msg_iov = &v;
    m.msg_iovlen = 1;

    // Setting the interface is a bit more involved.
    //
    // We have to create a "control message", and set that to
    // define the IPv6 packet information. We could set the
    // source address if we wanted, but we can safely let the
    // kernel decide what that should be.
    m.msg_control = &control_buf_[0];
    m.msg_controllen = control_buf_len_;
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&m);

    // FIXME: Code below assumes that cmsg is not NULL, but
    // CMSG_FIRSTHDR() is coded to return NULL as a possibility.  The
    // following assertion should never fail, but if it did and you came
    // here, fix the code. :)
    assert(cmsg != NULL);

    cmsg->cmsg_level = IPPROTO_IPV6;
    cmsg->cmsg_type = IPV6_PKTINFO;
    cmsg->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
    struct in6_pktinfo *pktinfo =
        util::io::internal::convertPktInfo6(CMSG_DATA(cmsg));
    memset(pktinfo, 0, sizeof(struct in6_pktinfo));
    pktinfo->ipi6_ifindex = pkt->getIndex();
    // According to RFC3542, section 20.2, the msg_controllen field
    // may be set using CMSG_SPACE (which includes padding) or
    // using CMSG_LEN. Both forms appear to work fine on Linux, FreeBSD,
    // NetBSD, but OpenBSD appears to have a bug, discussed here:
    // http://www.archivum.info/mailing.openbsd.bugs/2009-02/00017/
    // kernel-6080-msg_controllen-of-IPV6_PKTINFO.html
    // which causes sendmsg to return EINVAL if the CMSG_LEN is
    // used to set the msg_controllen value.
    m.msg_controllen = CMSG_SPACE(sizeof(struct in6_pktinfo));

    pkt->updateTimestamp();

    int result = sendmsg(sockfd, &m, 0);
    if  (result < 0) {
        isc_throw(SocketWriteError, "pkt6 send failed: sendmsg() returned"
                  " with an error: " << strerror(errno));
    }

    return (result);
}


}
}
