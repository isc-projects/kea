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

#include "dhcp/dhcp6.h"
#include "dhcp6/iface_mgr.h"
#include "exceptions/exceptions.h"

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
IfaceMgr::openSockets() {
    int sock;

    for (IfaceCollection::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {

        AddressCollection addrs = iface->getAddresses();

        for (AddressCollection::iterator addr= addrs.begin();
             addr != addrs.end();
             ++addr) {

            sock = openSocket(iface->getName(), *addr,
                              DHCP6_SERVER_PORT);
            if (sock<0) {
                isc_throw(Unexpected, "Failed to open unicast socket on "
                          << " interface " << iface->getFullName());
            }
            sendsock_ = sock;

            sock = openSocket(iface->getName(),
                              IOAddress(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
                              DHCP6_SERVER_PORT);
            if (sock<0) {
                isc_throw(Unexpected, "Failed to open multicast socket on "
                          << " interface " << iface->getFullName());
                close(sendsock_);
                sendsock_ = 0;
            }
            recvsock_ = sock;
        }
    }
}

void
IfaceMgr::printIfaces(std::ostream& out /*= std::cout*/) {
    for (IfaceCollection::const_iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        out << "Detected interface " << iface->getFullName() << endl;
        out << "  " << iface->getAddresses().size() << " addr(s):" << endl;
        const AddressCollection addrs = iface->getAddresses();

        for (AddressCollection::const_iterator addr = addrs.begin();
             addr != addrs.end();
             ++addr) {
            out << "  " << addr->toText() << endl;
        }
        out << "  mac: " << iface->getPlainMac() << endl;
    }
}

IfaceMgr::Iface*
IfaceMgr::getIface(int ifindex) {
    for (IfaceCollection::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        if (iface->getIndex() == ifindex)
            return (&(*iface));
    }

    return (NULL); // not found
}

IfaceMgr::Iface*
IfaceMgr::getIface(const std::string& ifname) {
    for (IfaceCollection::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        if (iface->getName() == ifname)
            return (&(*iface));
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
    isc_throw(NotImplemented, "Sorry. Try again in 2 weeks");
    cout << iface.getFullName() << addr.toText() << port; // just to disable unused warning
}

uint16_t
IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, int port) {
    struct sockaddr_in6 addr6;

    cout << "Creating socket on " << iface.getFullName()
         << "/port=" << port << endl;

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
        cout << "Failed to create UDP6 socket." << endl;
        return (-1);
    }

    /* Set the REUSEADDR option so that we don't fail to start if
       we're being restarted. */
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&flag, sizeof(flag)) < 0) {
        cout << "Can't set SO_REUSEADDR option on dhcpv6 socket." << endl;
        close(sock);
        return (-1);
    }

    if (bind(sock, (struct sockaddr *)&addr6, sizeof(addr6)) < 0) {
        cout << "Failed to bind socket " << sock << " to " << addr.toText()
             << "/port=" << port << endl;
        close(sock);
        return (-1);
    }
#ifdef IPV6_RECVPKTINFO
    /* RFC3542 - a new way */
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_RECVPKTINFO,
                   &flag, sizeof(flag)) != 0) {
        cout << "setsockopt: IPV6_RECVPKTINFO failed." << endl;
        close(sock);
        return (-1);
    }
#else
    /* RFC2292 - an old way */
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_PKTINFO,
                   &flag, sizeof(flag)) != 0) {
        cout << "setsockopt: IPV6_PKTINFO: failed." << endl;
        close(sock);
        return (-1);
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
            return (-1);
        }
    }

    cout << "Created socket " << sock << " on " << iface.getName() << "/" <<
        addr.toText() << "/port=" << port << endl;

    // TODO: Add socket to iface interface

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
    memset(&control_buf_[0], 0, control_buf_len_);

    /*
     * Initialize our message header structure.
     */
    memset(&m, 0, sizeof(m));

    /*
     * Set the target address we're sending to.
     */
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

    /*
     * Set the data buffer we're sending. (Using this wacky
     * "scatter-gather" stuff... we only have a single chunk
     * of data to send, so we declare a single vector entry.)
     */
    v.iov_base = (char *) &pkt->data_[0];
    v.iov_len = pkt->data_len_;
    m.msg_iov = &v;
    m.msg_iovlen = 1;

    /*
     * Setting the interface is a bit more involved.
     *
     * We have to create a "control message", and set that to
     * define the IPv6 packet information. We could set the
     * source address if we wanted, but we can safely let the
     * kernel decide what that should be.
     */
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

    result = sendmsg(sendsock_, &m, 0);
    if (result < 0) {
        cout << "Send packet failed." << endl;
    }
    cout << "Sent " << result << " bytes." << endl;

    cout << "Sent " << pkt->data_len_ << " bytes over "
         << pkt->iface_ << "/" << pkt->ifindex_ << " interface: "
         << " dst=" << pkt->remote_addr_.toText()
         << ", src=" << pkt->local_addr_.toText()
         << endl;

    return (result);
}

boost::shared_ptr<Pkt4>
IfaceMgr::receive4() {
    // TODO: To be implemented
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

    /*
     * Initialize our message header structure.
     */
    memset(&m, 0, sizeof(m));

    /*
     * Point so we can get the from address.
     */
    m.msg_name = &from;
    m.msg_namelen = sizeof(from);

    /*
     * Set the data buffer we're receiving. (Using this wacky
     * "scatter-gather" stuff... but we that doesn't really make
     * sense for us, so we use a single vector entry.)
     */
    v.iov_base = (void*)&pkt->data_[0];
    v.iov_len = pkt->data_len_;
    m.msg_iov = &v;
    m.msg_iovlen = 1;

    /*
     * Getting the interface is a bit more involved.
     *
     * We set up some space for a "control message". We have
     * previously asked the kernel to give us packet
     * information (when we initialized the interface), so we
     * should get the destination address from that.
     */
    m.msg_control = &control_buf_[0];
    m.msg_controllen = control_buf_len_;

    result = recvmsg(recvsock_, &m, 0);

    if (result >= 0) {
        /*
         * If we did read successfully, then we need to loop
         * through the control messages we received and
         * find the one with our destination address.
         *
         * We also keep a flag to see if we found it. If we
         * didn't, then we consider this to be an error.
         */
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

}
