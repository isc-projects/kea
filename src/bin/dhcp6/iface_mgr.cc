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
#include <net/if.h>

#include "addr6.h"
#include "dhcp6/iface_mgr.h"
#include "dhcp6/dhcp6.h"

using namespace std;
using namespace isc;

// IfaceMgr is a singleton implementation
IfaceMgr * IfaceMgr::instance_ = 0;

void IfaceMgr::instanceCreate() {
    if (instance_) {
        // XXX: throw exception here
        return;
    }
    instance_ = new IfaceMgr();
}

IfaceMgr& IfaceMgr::instance() {
    if (instance_ == 0)
        instanceCreate();
    return *instance_;
}


IfaceMgr::Iface::Iface()
    : name_(""), ifindex_(0), macLen_(0) {
    memset(mac_, 0, 20);
}

IfaceMgr::Iface::Iface(const std::string name, int ifindex)
    :name_(name), ifindex_(ifindex), macLen_(0) {
    memset(mac_, 0, 20);
}

std::string IfaceMgr::Iface::getFullName() const {
    ostringstream tmp;
    tmp << name_ << "/" << ifindex_;
    return tmp.str();
}

std::string IfaceMgr::Iface::getPlainMac() const {
    ostringstream tmp;
    for (int i=0; i<macLen_; i++) {
        tmp.fill('0');
        tmp.width(2);
        tmp << (hex) << (int) mac_[i];
        if (i<macLen_-1) {
            tmp << ":";
        }
    }
    return tmp.str();
}

IfaceMgr::IfaceMgr() {

    control_buf_len_ = CMSG_SPACE(sizeof(struct in6_pktinfo));
    control_buf_ = (char*) new char[control_buf_len_];

   cout << "IfaceMgr initialization." << endl;

   detectIfaces();

   openSockets();
}

IfaceMgr::~IfaceMgr() {
    if (control_buf_) {
        delete [] control_buf_;
        control_buf_ = 0;
        control_buf_len_ = 0;
    }
}

void IfaceMgr::detectIfaces() {
    string ifaceName, linkLocal;

    // XXX: do the actual detection

    cout << "Interface detection is not implemented yet. "
         << "Reading interfaces.txt file instead." << endl;
    cout << "Please use format: interface-name link-local-address" << endl;

    ifstream interfaces("interfaces.txt");
    interfaces >> ifaceName;
    interfaces >> linkLocal;

    cout << "Detected interface " << ifaceName << "/" << linkLocal << endl;

    Iface iface(ifaceName, if_nametoindex( ifaceName.c_str() ) );
    Addr6 addr(linkLocal.c_str(), true);
    iface.addrs_.push_back(addr);
    ifaces_.push_back(iface);
    interfaces.close();
}

bool IfaceMgr::openSockets() {
    int sock;

    for (IfaceLst::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {


        for (Addr6Lst::iterator addr=iface->addrs_.begin();
             addr!=iface->addrs_.end();
             ++addr) {

            sock = openSocket(iface->name_, *addr,
                              DHCP6_SERVER_PORT, false);
            if (sock<0) {
                cout << "Failed to open unicast socket." << endl;
                return false;
            }
            sendsock_ = sock;

            sock = openSocket(iface->name_,
                              Addr6(ALL_DHCP_RELAY_AGENTS_AND_SERVERS, true),
                              DHCP6_SERVER_PORT, true);
            if (sock<0) {
                cout << "Failed to open multicast socket." << endl;
                return false;
            }
            recvsock_ = sock;
        }
    }

    return true;
}

void IfaceMgr::printIfaces() {
    for (IfaceLst::const_iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        cout << "Detected interface " << iface->getFullName() << endl;
        cout << "  " << iface->addrs_.size() << " addr(s):" << endl;
        for (Addr6Lst::const_iterator addr=iface->addrs_.begin();
             addr != iface->addrs_.end();
             ++addr) {
            cout << "  " << *addr << endl;
        }
        cout << "  mac: " << iface->getPlainMac() << endl;
    }
}

IfaceMgr::Iface* IfaceMgr::getIface(int ifindex) {
    for (IfaceLst::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        if (iface->ifindex_ == ifindex)
            return &(*iface);
    }

    return 0; // not found
}

IfaceMgr::Iface* IfaceMgr::getIface(const std::string &ifname) {
    for (IfaceLst::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        if (iface->name_ == ifname)
            return &(*iface);
    }

    return 0; // not found
}

int IfaceMgr::openSocket(const std::string &ifname,
                         const Addr6 &addr,
                         int port,
                         bool mcast) {
    struct sockaddr_storage name;
    int name_len;
    struct sockaddr_in6 *addr6;

    cout << "Creating socket on " << ifname << "/" << addr << "/port=" 
         << port << endl;

    memset(&name, 0, sizeof(name));
    addr6 = (struct sockaddr_in6 *)&name;
    addr6->sin6_family = AF_INET6;
    addr6->sin6_port = htons(port);
    addr6->sin6_scope_id = if_nametoindex(ifname.c_str());
    memcpy(&addr6->sin6_addr,
           addr.get(),
           sizeof(addr6->sin6_addr));
#ifdef HAVE_SA_LEN
    addr6->sin6_len = sizeof(*addr6);
#endif
    name_len = sizeof(*addr6);

    // XXX: use sockcreator once it becomes available

    // make a socket
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0) {
        cout << "Failed to create UDP6 socket." << endl;
        return -1;
    }

    /* Set the REUSEADDR option so that we don't fail to start if
       we're being restarted. */
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&flag, sizeof(flag)) < 0) {
        cout << "Can't set SO_REUSEADDR option on dhcpv6 socket." << endl;
        return -1;
    }

    if (bind(sock, (struct sockaddr *)&name, name_len) < 0) {
        cout << "Failed to bind socket " << sock << " to " << addr.getPlain()
             << "/port=" << port << endl;
        return -1;
    }

#ifdef IPV6_RECVPKTINFO
    /* RFC3542 - a new way */
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_RECVPKTINFO,
                   &flag, sizeof(flag)) != 0) {
        cout << "setsockopt: IPV6_RECVPKTINFO failed." << endl;
        return -1;
    }
#else
    /* RFC2292 - an old way */
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_PKTINFO,
                   &flag, sizeof(flag)) != 0) {
        cout << "setsockopt: IPV6_PKTINFO: failed." << endl;
        return -1;
    }
#endif

    // multicast stuff

    if (mcast /*addr.multicast()*/) {
        // both mcast (ALL_DHCP_RELAY_AGENTS_AND_SERVERS and ALL_DHCP_SERVERS)
        // are link and site-scoped, so there is no sense to join those them
        // with global addressed.

        if ( !joinMcast( sock, ifname, 
                         string(ALL_DHCP_RELAY_AGENTS_AND_SERVERS) ) ) {
            close(sock);
            return -1;
        }
    }

    cout << "Created socket " << sock << " on " << ifname << "/" << addr 
         << "/port=" << port << endl;

    return sock;
}

bool IfaceMgr::joinMcast(int sock, const std::string& ifname,
                         const std::string & mcast) {

    struct ipv6_mreq mreq;

        if (inet_pton(AF_INET6, mcast.c_str(),
                      &mreq.ipv6mr_multiaddr) <= 0) {
            cout << "Failed to convert " << ifname
                 << " to IPv6 multicast address." << endl;
            return false;
        }

        mreq.ipv6mr_interface = if_nametoindex(ifname.c_str());
        if (setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP,
                       &mreq, sizeof(mreq)) < 0) {
            cout << "Failed to join " << mcast << " multicast group." << endl;
            return false;
        }

        cout << "Joined multicast " << mcast << " group." << endl;

        return true;
    }

    bool IfaceMgr::send(Pkt6 &pkt) {
        struct msghdr m;
        struct iovec v;
        int result;
        struct in6_pktinfo *pktinfo;
        struct cmsghdr *cmsg;
        memset(control_buf_, 0, control_buf_len_);

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
        to.sin6_port = htons(pkt.remotePort);
        memcpy(&to.sin6_addr, pkt.remoteAddr.get(), 16);
        to.sin6_scope_id = pkt.ifindex;

        m.msg_name = &to;
        m.msg_namelen = sizeof(to);

        /*
         * Set the data buffer we're sending. (Using this wacky
         * "scatter-gather" stuff... we only have a single chunk
         * of data to send, so we declare a single vector entry.)
         */
        v.iov_base = (char *) pkt.data_;
        v.iov_len = pkt.dataLen_;
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
        m.msg_control = control_buf_;
        m.msg_controllen = control_buf_len_;
        cmsg = CMSG_FIRSTHDR(&m);
        cmsg->cmsg_level = IPPROTO_IPV6;
        cmsg->cmsg_type = IPV6_PKTINFO;
        cmsg->cmsg_len = CMSG_LEN(sizeof(*pktinfo));
        pktinfo = (struct in6_pktinfo *)CMSG_DATA(cmsg);
        memset(pktinfo, 0, sizeof(*pktinfo));
        pktinfo->ipi6_ifindex = pkt.ifindex;
        m.msg_controllen = cmsg->cmsg_len;

        result = sendmsg(sendsock_, &m, 0);
        if (result < 0) {
            cout << "Send packet failed." << endl;
        }
        cout << "Sent " << result << " bytes." << endl;

        cout << "Sent " << pkt.dataLen_ << " bytes over "
             << pkt.iface << "/" << pkt.ifindex << " interface: "
             << " dst=" << pkt.remoteAddr << ", src=" << pkt.localAddr
             << endl;

        return result;
    }

    Pkt6 * IfaceMgr::receive() {
        struct msghdr m;
        struct iovec v;
        int result;
        struct cmsghdr *cmsg;
        struct in6_pktinfo *pktinfo;
        int found_pktinfo;
        struct sockaddr_in6 from;
        struct in6_addr to_addr;

        Pkt6 * pkt = new Pkt6(1500);

        memset(control_buf_, 0, control_buf_len_);

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
        v.iov_base = pkt->data_;
        v.iov_len = pkt->dataLen_;
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
        m.msg_control = control_buf_;
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
            found_pktinfo = 0;
            cmsg = CMSG_FIRSTHDR(&m);
            while (cmsg != NULL) {
                if ((cmsg->cmsg_level == IPPROTO_IPV6) &&
                    (cmsg->cmsg_type == IPV6_PKTINFO)) {
                    pktinfo = (struct in6_pktinfo *)CMSG_DATA(cmsg);
                    to_addr = pktinfo->ipi6_addr;
                    pkt->ifindex = pktinfo->ipi6_ifindex;
                    found_pktinfo = 1;
                }
                cmsg = CMSG_NXTHDR(&m, cmsg);
            }
            if (!found_pktinfo) {
                cout << "Unable to find pktinfo" << endl;
                delete pkt;
                return 0;
            }
        } else {
            cout << "Failed to receive data." << endl;

            delete pkt;
            return 0;
        }

        pkt->localAddr = Addr6(&to_addr);
        pkt->remoteAddr = Addr6(&from);
        pkt->remotePort = ntohs(from.sin6_port);

        Iface * received = getIface(pkt->ifindex);
        if (received) {
            pkt->iface = received->name_;
        }

        pkt->dataLen_ = result;

        cout << "Received " << pkt->dataLen_ << " bytes over "
             << pkt->iface << "/" << pkt->ifindex << " interface: "
             << " src=" << pkt->remoteAddr << ", dst=" << pkt->localAddr
             << endl;

        return pkt;

    }
