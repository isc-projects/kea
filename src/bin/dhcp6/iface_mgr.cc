// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <sstream>
#include <fstream>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <dhcp/dhcp6.h>
#include <dhcp6/iface_mgr.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace isc {

/// IfaceMgr is a singleton implementation
IfaceMgr* IfaceMgr::instance_ = 0;

void
IfaceMgr::instanceCreate() {
    if (instance_) {
        // no need to do anything. Instance is already created.
        // Who called it again anyway? Uh oh. Had to be us, as
        // this is private method.
        return;
    }
    instance_ = new IfaceMgr();
}

IfaceMgr&
IfaceMgr::instance() {
    if (instance_ == 0) {
        instanceCreate();
    }
    return (*instance_);
}

IfaceMgr::Iface::Iface(const std::string& name, int ifindex)
    :name_(name), ifindex_(ifindex), mac_len_(0) {

    memset(mac_, 0, sizeof(mac_));
}

std::string
IfaceMgr::Iface::getFullName() const {
    ostringstream tmp;
    tmp << name_ << "/" << ifindex_;
    return (tmp.str());
}

std::string
IfaceMgr::Iface::getPlainMac() const {
    ostringstream tmp;
    tmp.fill('0');
    tmp << hex;
    for (int i = 0; i < mac_len_; i++) {
        tmp.width(2);
        tmp << mac_[i];
        if (i < mac_len_-1) {
            tmp << ":";
        }
    }
    return (tmp.str());
}

bool IfaceMgr::Iface::delAddress(const isc::asiolink::IOAddress& addr) {
    for (AddressCollection::iterator a = addrs_.begin();
         a!=addrs_.end(); ++a) {
        if (*a==addr) {
            addrs_.erase(a);
            return (true);
        }
    }
    return (false);
}

bool IfaceMgr::Iface::delSocket(uint16_t sockfd) {
    list<SocketInfo>::iterator sock = sockets_.begin();
    while (sock!=sockets_.end()) {
        if (sock->sockfd_ == sockfd) {
            close(sockfd);
            sockets_.erase(sock);
            return (true); //socket found
        }
        ++sock;
    }
    return (false); // socket not found
}

IfaceMgr::IfaceMgr()
    :control_buf_len_(CMSG_SPACE(sizeof(struct in6_pktinfo))),
     control_buf_(new char[control_buf_len_])
{

    cout << "IfaceMgr initialization." << endl;

    try {
        // required for sending/receiving packets
        // let's keep it in front, just in case someone
        // wants to send anything during initialization

        // control_buf_ = boost::scoped_array<char>();

        detectIfaces();

    } catch (const std::exception& ex) {
        cout << "IfaceMgr creation failed:" << ex.what() << endl;

        // TODO Uncomment this (or call LOG_FATAL) once
        // interface detection is implemented. Otherwise
        // it is not possible to run tests in a portable
        // way (see detectIfaces() method).
        // throw ex;
    }
}

IfaceMgr::~IfaceMgr() {
    // control_buf_ is deleted automatically (scoped_ptr)
    control_buf_len_ = 0;
}

void
IfaceMgr::detectIfaces() {
    string ifaceName, linkLocal;

    // TODO do the actual detection. Currently interface detection is faked
    //      by reading a text file.

    cout << "Interface detection is not implemented yet. "
         << "Reading interfaces.txt file instead." << endl;
    cout << "Please use format: interface-name link-local-address" << endl;

    try {
        ifstream interfaces("interfaces.txt");

        if (!interfaces.good()) {
            cout << "Failed to read interfaces.txt file." << endl;
            isc_throw(Unexpected, "Failed to read interfaces.txt");
        }
        interfaces >> ifaceName;
        interfaces >> linkLocal;

        cout << "Detected interface " << ifaceName << "/" << linkLocal << endl;

        Iface iface(ifaceName, if_nametoindex( ifaceName.c_str() ) );
        IOAddress addr(linkLocal);
        iface.addAddress(addr);
        addInterface(iface);
        interfaces.close();
    } catch (const std::exception& ex) {
        // TODO: deallocate whatever memory we used
        // not that important, since this function is going to be
        // thrown away as soon as we get proper interface detection
        // implemented

        // TODO Do LOG_FATAL here
        std::cerr << "Interface detection failed." << std::endl;
        throw ex;
    }
}

void
IfaceMgr::openSockets(uint16_t port) {
    int sock1, sock2;

    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {

        AddressCollection addrs = iface->getAddresses();

        for (AddressCollection::iterator addr = addrs.begin();
             addr != addrs.end();
             ++addr) {

            sock1 = openSocket(iface->getName(), *addr, port);
            if (sock1 < 0) {
                isc_throw(Unexpected, "Failed to open unicast socket on "
                          << " interface " << iface->getFullName());
            }

            if ( !joinMcast(sock1, iface->getName(),
                             string(ALL_DHCP_RELAY_AGENTS_AND_SERVERS) ) ) {
                close(sock1);
                isc_throw(Unexpected, "Failed to join " << ALL_DHCP_RELAY_AGENTS_AND_SERVERS
                          << " multicast group.");
            }

            // this doesn't work too well on NetBSD
            sock2 = openSocket(iface->getName(),
                               IOAddress(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
                               port);
            if (sock2 < 0) {
                isc_throw(Unexpected, "Failed to open multicast socket on "
                          << " interface " << iface->getFullName());
                iface->delSocket(sock1); // delete previously opened socket
            }
        }
    }
}

void
IfaceMgr::printIfaces(std::ostream& out /*= std::cout*/) {
    for (IfaceCollection::const_iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        out << "Detected interface " << iface->getFullName() << endl;
        out << "  " << iface->getAddresses().size() << " addr(s):" << endl;
        const AddressCollection addrs = iface->getAddresses();

        for (AddressCollection::const_iterator addr = addrs.begin();
             addr != addrs.end(); ++addr) {
            out << "  " << addr->toText() << endl;
        }
        out << "  mac: " << iface->getPlainMac() << endl;
    }
}

IfaceMgr::Iface*
IfaceMgr::getIface(int ifindex) {
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        if (iface->getIndex() == ifindex) {
            return (&(*iface));
        }
    }

    return (NULL); // not found
}

IfaceMgr::Iface*
IfaceMgr::getIface(const std::string& ifname) {
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        if (iface->getName() == ifname) {
            return (&(*iface));
        }
    }

    return (NULL); // not found
}

uint16_t
IfaceMgr::openSocket(const std::string& ifname,
                     const IOAddress& addr,
                     int port) {
    Iface* iface = getIface(ifname);
    if (!iface) {
        isc_throw(BadValue, "There is no " << ifname << " interface present.");
    }
    switch (addr.getFamily()) {
    case AF_INET:
        return openSocket4(*iface, addr, port);
    case AF_INET6:
        return openSocket6(*iface, addr, port);
    default:
        isc_throw(BadValue, "Failed to detect family of address: "
                  << addr.toText());
    }
}

uint16_t
IfaceMgr::openSocket4(Iface& iface, const IOAddress& addr, int port) {

    cout << "Creating UDP4 socket on " << iface.getFullName()
         << " " << addr.toText() << "/port=" << port << endl;

    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(sockaddr));
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);
    memcpy(&addr4.sin_addr, addr.getAddress().to_v4().to_bytes().data(),
           sizeof(addr4.sin_addr));

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(Unexpected, "Failed to create UDP6 socket.");
    }

    if (bind(sock, (struct sockaddr *)&addr4, sizeof(addr4)) < 0) {
        close(sock);
        isc_throw(Unexpected, "Failed to bind socket " << sock << " to " << addr.toText()
                  << "/port=" << port);
    }

    // If there is no support for IP_PKTINFO, we are really out of luck.
    // It will be difficult to understand, where this packet came from.
#if defined(IP_PKTINFO)
    int flag = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_PKTINFO, &flag, sizeof(flag)) != 0) {
        close(sock);
        isc_throw(Unexpected, "setsockopt: IP_PKTINFO: failed.");
    }
#endif

    cout << "Created socket " << sock << " on " << iface.getName() << "/" <<
        addr.toText() << "/port=" << port << endl;

    SocketInfo info(sock, addr, port);
    iface.addSocket(info);

    return (sock);
}

uint16_t
IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, int port) {

    cout << "Creating UDP6 socket on " << iface.getFullName()
         << " " << addr.toText() << "/port=" << port << endl;

    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port);
    addr6.sin6_scope_id = if_nametoindex(iface.getName().c_str());

    memcpy(&addr6.sin6_addr,
           addr.getAddress().to_v6().to_bytes().data(),
           sizeof(addr6.sin6_addr));
#ifdef HAVE_SA_LEN
    addr6->sin6_len = sizeof(addr6);
#endif

    // TODO: use sockcreator once it becomes available

    // make a socket
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(Unexpected, "Failed to create UDP6 socket.");
    }

    // Set the REUSEADDR option so that we don't fail to start if
    // we're being restarted.
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&flag, sizeof(flag)) < 0) {
        close(sock);
        isc_throw(Unexpected, "Can't set SO_REUSEADDR option on dhcpv6 socket.");
    }

    if (bind(sock, (struct sockaddr *)&addr6, sizeof(addr6)) < 0) {
        close(sock);
        isc_throw(Unexpected, "Failed to bind socket " << sock << " to " << addr.toText()
                  << "/port=" << port);
    }
#ifdef IPV6_RECVPKTINFO
    // RFC3542 - a new way
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_RECVPKTINFO,
                   &flag, sizeof(flag)) != 0) {
        close(sock);
        isc_throw(Unexpected, "setsockopt: IPV6_RECVPKTINFO failed.");
    }
#else
    // RFC2292 - an old way
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_PKTINFO,
                   &flag, sizeof(flag)) != 0) {
        close(sock);
        isc_throw(Unexpected, "setsockopt: IPV6_PKTINFO: failed.");
    }
#endif

    // multicast stuff
    if (addr.getAddress().to_v6().is_multicast()) {
        // both mcast (ALL_DHCP_RELAY_AGENTS_AND_SERVERS and ALL_DHCP_SERVERS)
        // are link and site-scoped, so there is no sense to join those groups
        // with global addresses.

        if ( !joinMcast( sock, iface.getName(),
                         string(ALL_DHCP_RELAY_AGENTS_AND_SERVERS) ) ) {
            close(sock);
            isc_throw(Unexpected, "Failed to join " << ALL_DHCP_RELAY_AGENTS_AND_SERVERS
                      << " multicast group.");
        }
    }

    cout << "Created socket " << sock << " on " << iface.getName() << "/" <<
        addr.toText() << "/port=" << port << endl;

    SocketInfo info(sock, addr, port);
    iface.addSocket(info);

    return (sock);
}

bool
IfaceMgr::joinMcast(int sock, const std::string& ifname,
const std::string & mcast) {

    struct ipv6_mreq mreq;

    if (inet_pton(AF_INET6, mcast.c_str(),
                  &mreq.ipv6mr_multiaddr) <= 0) {
        cout << "Failed to convert " << ifname
             << " to IPv6 multicast address." << endl;
        return (false);
    }

    mreq.ipv6mr_interface = if_nametoindex(ifname.c_str());
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP,
                   &mreq, sizeof(mreq)) < 0) {
        cout << "Failed to join " << mcast << " multicast group." << endl;
        return (false);
    }

    cout << "Joined multicast " << mcast << " group." << endl;

    return (true);
}

bool
IfaceMgr::send(boost::shared_ptr<Pkt6>& pkt) {
    struct msghdr m;
    struct iovec v;
    int result;
    struct in6_pktinfo *pktinfo;
    struct cmsghdr *cmsg;

    Iface* iface = getIface(pkt->iface_);
    if (!iface) {
        isc_throw(BadValue, "Unable to send Pkt6. Invalid interface ("
                  << pkt->iface_ << ") specified.");
    }

    memset(&control_buf_[0], 0, control_buf_len_);

    // Initialize our message header structure.
    memset(&m, 0, sizeof(m));

    // Set the target address we're sending to.
    sockaddr_in6 to;
    memset(&to, 0, sizeof(to));
    to.sin6_family = AF_INET6;
    to.sin6_port = htons(pkt->remote_port_);
    memcpy(&to.sin6_addr,
           pkt->remote_addr_.getAddress().to_v6().to_bytes().data(),
           16);
    to.sin6_scope_id = pkt->ifindex_;

    m.msg_name = &to;
    m.msg_namelen = sizeof(to);

    // Set the data buffer we're sending. (Using this wacky
    // "scatter-gather" stuff... we only have a single chunk
    // of data to send, so we declare a single vector entry.)
    v.iov_base = (char *) &pkt->data_[0];
    v.iov_len = pkt->data_len_;
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
    cmsg = CMSG_FIRSTHDR(&m);
    cmsg->cmsg_level = IPPROTO_IPV6;
    cmsg->cmsg_type = IPV6_PKTINFO;
    cmsg->cmsg_len = CMSG_LEN(sizeof(*pktinfo));
    pktinfo = (struct in6_pktinfo *)CMSG_DATA(cmsg);
    memset(pktinfo, 0, sizeof(*pktinfo));
    pktinfo->ipi6_ifindex = pkt->ifindex_;
    m.msg_controllen = cmsg->cmsg_len;

    result = sendmsg(getSocket(*pkt), &m, 0);
    if (result < 0) {
        cout << "Send packet failed." << endl;
    }
    cout << "Sent " << pkt->data_len_ << " bytes over socket " << getSocket(*pkt)
         << " on " << iface->getFullName() << " interface: "
         << " dst=" << pkt->remote_addr_.toText()
         << ", src=" << pkt->local_addr_.toText()
         << endl;

    return (result);
}

bool
IfaceMgr::send(boost::shared_ptr<Pkt4>& )
{
    /// TODO: Implement this (ticket #1240)
    isc_throw(Unexpected, "Pkt4 send not implemented yet.");
}


boost::shared_ptr<Pkt4>
IfaceMgr::receive4() {
    isc_throw(Unexpected, "Pkt4 reception not implemented yet.");

    // TODO: To be implemented (ticket #1239)
    return (boost::shared_ptr<Pkt4>()); // NULL
}

boost::shared_ptr<Pkt6>
IfaceMgr::receive6() {
    struct msghdr m;
    struct iovec v;
    int result;
    struct cmsghdr* cmsg;
    struct in6_pktinfo* pktinfo;
    struct sockaddr_in6 from;
    struct in6_addr to_addr;
    boost::shared_ptr<Pkt6> pkt;
    char addr_str[INET6_ADDRSTRLEN];

    try {
        // RFC3315 states that server responses may be
        // fragmented if they are over MTU. There is no
        // text whether client's packets may be larger
        // than 1500. Nevertheless to be on the safe side
        // we use larger buffer. This buffer limit is checked
        // during reception (see iov_len below), so we are
        // safe
        pkt = boost::shared_ptr<Pkt6>(new Pkt6(65536));
    } catch (const std::exception& ex) {
        cout << "Failed to create new packet." << endl;
        return (boost::shared_ptr<Pkt6>()); // NULL
    }

    memset(&control_buf_[0], 0, control_buf_len_);

    memset(&from, 0, sizeof(from));
    memset(&to_addr, 0, sizeof(to_addr));

    // Initialize our message header structure.
    memset(&m, 0, sizeof(m));

    // Point so we can get the from address.
    m.msg_name = &from;
    m.msg_namelen = sizeof(from);

    // Set the data buffer we're receiving. (Using this wacky
    // "scatter-gather" stuff... but we that doesn't really make
    // sense for us, so we use a single vector entry.)
    v.iov_base = (void*)&pkt->data_[0];
    v.iov_len = pkt->data_len_;
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

    /// TODO: Need to move to select() and pool over
    /// all available sockets. For now, we just take the
    /// first interface and use first socket from it.
    IfaceCollection::const_iterator iface = ifaces_.begin();
    if (iface == ifaces_.end()) {
        isc_throw(Unexpected, "No interfaces detected. Can't receive anything.");
    }
    SocketCollection::const_iterator s = iface->sockets_.begin();
    const SocketInfo* candidate = 0;
    while (s != iface->sockets_.end()) {
        if (s->addr_.getAddress().to_v6().is_multicast()) {
            candidate = &(*s);
            break;
        }
        if (!candidate) {
            candidate = &(*s); // it's not multicast, but it's better than none
        }
        ++s;
    }
    if (!candidate) {
        isc_throw(Unexpected, "Interface " << iface->getFullName()
                  << " does not have any sockets open.");
    }

    cout << "Trying to receive over socket " << candidate->sockfd_ << " bound to "
         << candidate->addr_.toText() << "/port=" << candidate->port_ << " on "
         << iface->getFullName() << endl;
    result = recvmsg(candidate->sockfd_, &m, 0);

    if (result >= 0) {
        // If we did read successfully, then we need to loop
        // through the control messages we received and
        // find the one with our destination address.
        //
        // We also keep a flag to see if we found it. If we
        // didn't, then we consider this to be an error.
        int found_pktinfo = 0;
        cmsg = CMSG_FIRSTHDR(&m);
        while (cmsg != NULL) {
            if ((cmsg->cmsg_level == IPPROTO_IPV6) &&
                (cmsg->cmsg_type == IPV6_PKTINFO)) {
                pktinfo = (struct in6_pktinfo*)CMSG_DATA(cmsg);
                to_addr = pktinfo->ipi6_addr;
                pkt->ifindex_ = pktinfo->ipi6_ifindex;
                found_pktinfo = 1;
            }
            cmsg = CMSG_NXTHDR(&m, cmsg);
        }
        if (!found_pktinfo) {
            cout << "Unable to find pktinfo" << endl;
            return (boost::shared_ptr<Pkt6>()); // NULL
        }
    } else {
        cout << "Failed to receive data." << endl;
        return (boost::shared_ptr<Pkt6>()); // NULL
    }

    // That's ugly.
    // TODO add IOAddress constructor that will take struct in6_addr*
    // TODO: there's from_bytes() method added in IOAddress. Use it!
    inet_ntop(AF_INET6, &to_addr, addr_str,INET6_ADDRSTRLEN);
    pkt->local_addr_ = IOAddress(string(addr_str));

    // TODO: there's from_bytes() method added in IOAddress. Use it!
    inet_ntop(AF_INET6, &from.sin6_addr, addr_str, INET6_ADDRSTRLEN);
    pkt->remote_addr_ = IOAddress(string(addr_str));

    pkt->remote_port_ = ntohs(from.sin6_port);

    Iface* received = getIface(pkt->ifindex_);
    if (received) {
        pkt->iface_ = received->getName();
    } else {
        cout << "Received packet over unknown interface (ifindex="
             << pkt->ifindex_ << ")." << endl;
        return (boost::shared_ptr<Pkt6>()); // NULL
    }

    pkt->data_len_ = result;

    // TODO Move this to LOG_DEBUG
    cout << "Received " << pkt->data_len_ << " bytes over "
         << pkt->iface_ << "/" << pkt->ifindex_ << " interface: "
         << " src=" << pkt->remote_addr_.toText()
         << ", dst=" << pkt->local_addr_.toText()
         << endl;

    return (pkt);
}

uint16_t
IfaceMgr::getSocket(isc::dhcp::Pkt6 const& pkt) {
    Iface* iface = getIface(pkt.iface_);
    if (!iface) {
        isc_throw(BadValue, "Tried to find socket for non-existent interface "
                  << pkt.iface_);
    }

    SocketCollection::const_iterator s;
    for (s = iface->sockets_.begin(); s != iface->sockets_.end(); ++s) {
        if (s->family_ != AF_INET6) {
            // don't use IPv4 sockets
            continue;
        }
        if (s->addr_.getAddress().to_v6().is_multicast()) {
            // don't use IPv6 sockets bound to multicast address
            continue;
        }
        /// TODO: Add more checks here later. If remote address is
        /// not link-local, we can't use link local bound socket
        /// to send data.

        return (s->sockfd_);
    }

    isc_throw(Unexpected, "Interface " << iface->getFullName()
              << " does not have any suitable IPv6 sockets open.");
}

uint16_t
IfaceMgr::getSocket(isc::dhcp::Pkt4 const& pkt) {
    Iface* iface = getIface(pkt.getIface());
    if (!iface) {
        isc_throw(BadValue, "Tried to find socket for non-existent interface "
                  << pkt.getIface());
    }

    SocketCollection::const_iterator s;
    for (s = iface->sockets_.begin(); s != iface->sockets_.end(); ++s) {
        if (s->family_ != AF_INET) {
            // don't use IPv4 sockets
            continue;
        }
        /// TODO: Add more checks here later. If remote address is
        /// not link-local, we can't use link local bound socket
        /// to send data.

        return (s->sockfd_);
    }

    isc_throw(Unexpected, "Interface " << iface->getFullName()
              << " does not have any suitable IPv4 sockets open.");
}



}
