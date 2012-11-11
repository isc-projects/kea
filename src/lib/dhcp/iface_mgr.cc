// Copyright (C) 2011-2012  Internet Systems Consortium, Inc. ("ISC")
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
#include <sstream>
#include <fstream>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <asio.hpp>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/io_error.h>
#include <util/io/pktinfo_utilities.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::util::io::internal;

namespace isc {
namespace dhcp {

IfaceMgr&
IfaceMgr::instance() {
    static IfaceMgr iface_mgr;
    return (iface_mgr);
}

IfaceMgr::Iface::Iface(const std::string& name, int ifindex)
    :name_(name), ifindex_(ifindex), mac_len_(0), hardware_type_(0),
     flag_loopback_(false), flag_up_(false), flag_running_(false),
     flag_multicast_(false), flag_broadcast_(false), flags_(0)
{
    memset(mac_, 0, sizeof(mac_));
}

void
IfaceMgr::Iface::closeSockets() {
    for (SocketCollection::iterator sock = sockets_.begin();
         sock != sockets_.end(); ++sock) {
        close(sock->sockfd_);
    }
    sockets_.clear();
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
        tmp <<  static_cast<int>(mac_[i]);
        if (i < mac_len_-1) {
            tmp << ":";
        }
    }
    return (tmp.str());
}

void IfaceMgr::Iface::setMac(const uint8_t* mac, size_t len) {
    if (len > IfaceMgr::MAX_MAC_LEN) {
        isc_throw(OutOfRange, "Interface " << getFullName()
                  << " was detected to have link address of length "
                  << len << ", but maximum supported length is "
                  << IfaceMgr::MAX_MAC_LEN);
    }
    mac_len_ = len;
    memcpy(mac_, mac, len);
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
     control_buf_(new char[control_buf_len_]),
     session_socket_(INVALID_SOCKET), session_callback_(NULL)
{

    try {
        // required for sending/receiving packets
        // let's keep it in front, just in case someone
        // wants to send anything during initialization

        // control_buf_ = boost::scoped_array<char>();

        detectIfaces();

    } catch (const std::exception& ex) {
        isc_throw(IfaceDetectError, ex.what());
    }
}

void IfaceMgr::closeSockets() {
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        iface->closeSockets();
    }
}

IfaceMgr::~IfaceMgr() {
    // control_buf_ is deleted automatically (scoped_ptr)
    control_buf_len_ = 0;

    closeSockets();
}

void IfaceMgr::stubDetectIfaces() {
    string ifaceName;
    const string v4addr("127.0.0.1"), v6addr("::1");

    // This is a stub implementation for interface detection. Actual detection
    // is faked by detecting loopback interface (lo or lo0). It will eventually
    // be removed once we have actual implementations for all supported systems.

    if (if_nametoindex("lo") > 0) {
        ifaceName = "lo";
        // this is Linux-like OS
    } else if (if_nametoindex("lo0") > 0) {
        ifaceName = "lo0";
        // this is BSD-like OS
    } else {
        // we give up. What OS is this, anyway? Solaris? Hurd?
        isc_throw(NotImplemented,
                  "Interface detection on this OS is not supported.");
    }

    Iface iface(ifaceName, if_nametoindex(ifaceName.c_str()));
    iface.flag_up_ = true;
    iface.flag_running_ = true;

    // Note that we claim that this is not a loopback. iface_mgr tries to open a
    // socket on all interaces that are up, running and not loopback. As this is
    // the only interface we were able to detect, let's pretend this is a normal
    // interface.
    iface.flag_loopback_ = false;
    iface.flag_multicast_ = true;
    iface.flag_broadcast_ = true;
    iface.setHWType(HWTYPE_ETHERNET);

    iface.addAddress(IOAddress(v4addr));
    iface.addAddress(IOAddress(v6addr));
    addInterface(iface);
}

bool IfaceMgr::openSockets4(const uint16_t port) {
    int sock;
    int count = 0;

    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end();
         ++iface) {

        if (iface->flag_loopback_ ||
            !iface->flag_up_ ||
            !iface->flag_running_) {
            continue;
        }

        AddressCollection addrs = iface->getAddresses();
        for (AddressCollection::iterator addr = addrs.begin();
             addr != addrs.end();
             ++addr) {

            // Skip IPv6 addresses
            if (addr->getFamily() != AF_INET) {
                continue;
            }

            sock = openSocket(iface->getName(), *addr, port);
            if (sock < 0) {
                isc_throw(SocketConfigError, "failed to open unicast socket");
            }

            count++;
        }
    }
    return (count > 0);
}

bool IfaceMgr::openSockets6(const uint16_t port) {
    int sock;
    int count = 0;

    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end();
         ++iface) {

        if (iface->flag_loopback_ ||
            !iface->flag_up_ ||
            !iface->flag_running_) {
            continue;
        }

        AddressCollection addrs = iface->getAddresses();
        for (AddressCollection::iterator addr = addrs.begin();
             addr != addrs.end();
             ++addr) {

            // skip IPv4 addresses
            if (addr->getFamily() != AF_INET6) {
                continue;
            }

            // Bind link-local addresses only. Otherwise we bind several sockets
            // on interfaces that have several global addresses. For examples
            // with interface with 2 global addresses, we would bind 3 sockets
            // (one for link-local and two for global). That would result in
            // getting each message 3 times.
            if (!addr->getAddress().to_v6().is_link_local()){
                continue;
            }

            sock = openSocket(iface->getName(), *addr, port);
            if (sock < 0) {
                isc_throw(SocketConfigError, "failed to open unicast socket");
            }

            // Binding socket to unicast address and then joining multicast group
            // works well on Mac OS (and possibly other BSDs), but does not work
            // on Linux.
            if ( !joinMulticast(sock, iface->getName(),
                                string(ALL_DHCP_RELAY_AGENTS_AND_SERVERS))) {
                close(sock);
                isc_throw(SocketConfigError, "Failed to join "
                          << ALL_DHCP_RELAY_AGENTS_AND_SERVERS
                          << " multicast group.");
            }

            count++;

            /// @todo: Remove this ifdef once we start supporting BSD systems.
#if defined(OS_LINUX)
            // To receive multicast traffic, Linux requires binding socket to
            // a multicast group. That in turn doesn't work on NetBSD.

            int sock2 = openSocket(iface->getName(),
                                   IOAddress(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
                                   port);
            if (sock2 < 0) {
                isc_throw(SocketConfigError, "Failed to open multicast socket on "
                          << " interface " << iface->getFullName());
                iface->delSocket(sock); // delete previously opened socket
            }
#endif
        }
    }
    return (count > 0);
}

void
IfaceMgr::printIfaces(std::ostream& out /*= std::cout*/) {
    for (IfaceCollection::const_iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {

        const AddressCollection& addrs = iface->getAddresses();

        out << "Detected interface " << iface->getFullName()
            << ", hwtype=" << iface->getHWType()
            << ", mac=" << iface->getPlainMac();
        out << ", flags=" << hex << iface->flags_ << dec << "("
            << (iface->flag_loopback_?"LOOPBACK ":"")
            << (iface->flag_up_?"UP ":"")
            << (iface->flag_running_?"RUNNING ":"")
            << (iface->flag_multicast_?"MULTICAST ":"")
            << (iface->flag_broadcast_?"BROADCAST ":"")
            << ")" << endl;
        out << "  " << addrs.size() << " addr(s):";

        for (AddressCollection::const_iterator addr = addrs.begin();
             addr != addrs.end(); ++addr) {
            out << "  " << addr->toText();
        }
        out << endl;
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

int IfaceMgr::openSocket(const std::string& ifname, const IOAddress& addr,
                         const uint16_t port) {
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

int IfaceMgr::openSocketFromIface(const std::string& ifname,
                                  const uint16_t port,
                                  const uint8_t family) {
    // Search for specified interface among detected interfaces.
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end();
         ++iface) {

        if ((iface->getFullName() != ifname) &&
            (iface->getName() != ifname)) {
            continue;
        }

        // Interface is now detected. Search for address on interface
        // that matches address family (v6 or v4).
        AddressCollection addrs = iface->getAddresses();
        AddressCollection::iterator addr_it = addrs.begin();
        while (addr_it != addrs.end()) {
            if (addr_it->getFamily() == family) {
                // We have interface and address so let's open socket.
                // This may cause isc::Unexpected exception.
                return (openSocket(iface->getName(), *addr_it, port));
            }
            ++addr_it;
        }
        // If we are at the end of address collection it means that we found
        // interface but there is no address for family specified.
        if (addr_it == addrs.end()) {
            // Stringify the family value to append it to exception string.
            std::string family_name("AF_INET");
            if (family == AF_INET6) {
                family_name = "AF_INET6";
            }
            // We did not find address on the interface.
            isc_throw(SocketConfigError, "There is no address for interface: "
                      << ifname << ", port: " << port << ", address "
                      " family: " << family_name);
        }
    }
    // If we got here it means that we had not found the specified interface.
    // Otherwise we would have returned from previous exist points.
    isc_throw(BadValue, "There is no " << ifname << " interface present.");
}

int IfaceMgr::openSocketFromAddress(const IOAddress& addr,
                                    const uint16_t port) {
    // Search through detected interfaces and addresses to match
    // local address we got.
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end();
         ++iface) {

        AddressCollection addrs = iface->getAddresses();

        for (AddressCollection::iterator addr_it = addrs.begin();
             addr_it != addrs.end();
             ++addr_it) {

            // Local address must match one of the addresses
            // on detected interfaces. If it does, we have
            // address and interface detected so we can open
            // socket.
            if (*addr_it == addr) {
                // Open socket using local interface, address and port.
                // This may cause isc::Unexpected exception.
                return (openSocket(iface->getName(), *addr_it, port));
            }
        }
    }
    // If we got here it means that we did not find specified address
    // on any available interface.
    isc_throw(BadValue, "There is no such address " << addr.toText());
}

int IfaceMgr::openSocketFromRemoteAddress(const IOAddress& remote_addr,
                                          const uint16_t port) {
    try {
        // Get local address to be used to connect to remote location.
        IOAddress local_address(getLocalAddress(remote_addr, port).getAddress());
        return openSocketFromAddress(local_address, port);
    } catch (const Exception& e) {
        isc_throw(SocketConfigError, e.what());
    }
}

isc::asiolink::IOAddress
IfaceMgr::getLocalAddress(const IOAddress& remote_addr, const uint16_t port) {
    // Create remote endpoint, we will be connecting to it.
    boost::scoped_ptr<const UDPEndpoint>
        remote_endpoint(static_cast<const UDPEndpoint*>
                        (UDPEndpoint::create(IPPROTO_UDP, remote_addr, port)));
    if (!remote_endpoint) {
        isc_throw(Unexpected, "Unable to create remote endpoint");
    }

    // Create socket that will be used to connect to remote endpoint.
    asio::io_service io_service;
    asio::ip::udp::socket sock(io_service);

    asio::error_code err_code;
    // If remote address is broadcast address we have to
    // allow this on the socket.
    if (remote_addr.getAddress().is_v4() &&
        (remote_addr == IOAddress(DHCP_IPV4_BROADCAST_ADDRESS))) {
        // Socket has to be open prior to setting the broadcast
        // option. Otherwise set_option will complain about
        // bad file descriptor.

        // @todo: We don't specify interface in any way here. 255.255.255.255
        // We can very easily end up with a socket working on a different
        // interface.
        sock.open(asio::ip::udp::v4(), err_code);
        if (err_code) {
            isc_throw(Unexpected, "failed to open UDPv4 socket");
        }
        sock.set_option(asio::socket_base::broadcast(true), err_code);
        if (err_code) {
            sock.close();
            isc_throw(Unexpected, "failed to enable broadcast on the socket");
        }
    }

    // Try to connect to remote endpoint and check if attempt is successful.
    sock.connect(remote_endpoint->getASIOEndpoint(), err_code);
    if (err_code) {
        sock.close();
        isc_throw(Unexpected, "failed to connect to remote endpoint.");
    }

    // Once we are connected socket object holds local endpoint.
    asio::ip::udp::socket::endpoint_type local_endpoint =
        sock.local_endpoint();
    asio::ip::address local_address(local_endpoint.address());

    // Close the socket.
    sock.close();

    // Return address of local endpoint.
    return IOAddress(local_address);
}

int IfaceMgr::openSocket4(Iface& iface, const IOAddress& addr, uint16_t port) {

    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(sockaddr));
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);

    addr4.sin_addr.s_addr = htonl(addr);
    //addr4.sin_addr.s_addr = 0; // anyaddr: this will receive 0.0.0.0 => 255.255.255.255 traffic
    // addr4.sin_addr.s_addr = 0xffffffffu; // broadcast address. This will receive 0.0.0.0 => 255.255.255.255 as well

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(SocketConfigError, "Failed to create UDP6 socket.");
    }

    if (bind(sock, (struct sockaddr *)&addr4, sizeof(addr4)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to bind socket " << sock << " to " << addr.toText()
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

    SocketInfo info(sock, addr, port);
    iface.addSocket(info);

    return (sock);
}

int IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, uint16_t port) {

    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port);
    if (addr.toText() != "::1") {
        addr6.sin6_scope_id = if_nametoindex(iface.getName().c_str());
    }

    memcpy(&addr6.sin6_addr,
           addr.getAddress().to_v6().to_bytes().data(),
           sizeof(addr6.sin6_addr));
#ifdef HAVE_SA_LEN
    addr6.sin6_len = sizeof(addr6);
#endif

    // TODO: use sockcreator once it becomes available

    // make a socket
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(SocketConfigError, "Failed to create UDP6 socket.");
    }

    // Set the REUSEADDR option so that we don't fail to start if
    // we're being restarted.
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&flag, sizeof(flag)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Can't set SO_REUSEADDR option on dhcpv6 socket.");
    }

    if (bind(sock, (struct sockaddr *)&addr6, sizeof(addr6)) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to bind socket " << sock << " to " << addr.toText()
                  << "/port=" << port);
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

    // multicast stuff
    if (addr.getAddress().to_v6().is_multicast()) {
        // both mcast (ALL_DHCP_RELAY_AGENTS_AND_SERVERS and ALL_DHCP_SERVERS)
        // are link and site-scoped, so there is no sense to join those groups
        // with global addresses.

        if ( !joinMulticast( sock, iface.getName(),
                         string(ALL_DHCP_RELAY_AGENTS_AND_SERVERS) ) ) {
            close(sock);
            isc_throw(SocketConfigError, "Failed to join " << ALL_DHCP_RELAY_AGENTS_AND_SERVERS
                      << " multicast group.");
        }
    }

    SocketInfo info(sock, addr, port);
    iface.addSocket(info);

    return (sock);
}

bool
IfaceMgr::joinMulticast(int sock, const std::string& ifname,
const std::string & mcast) {

    struct ipv6_mreq mreq;

    if (inet_pton(AF_INET6, mcast.c_str(),
                  &mreq.ipv6mr_multiaddr) <= 0) {
        return (false);
    }

    mreq.ipv6mr_interface = if_nametoindex(ifname.c_str());
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP,
                   &mreq, sizeof(mreq)) < 0) {
        return (false);
    }

    return (true);
}

bool
IfaceMgr::send(const Pkt6Ptr& pkt) {
    int result;

    Iface* iface = getIface(pkt->getIface());
    if (!iface) {
        isc_throw(BadValue, "Unable to send Pkt6. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    memset(&control_buf_[0], 0, control_buf_len_);


    // Set the target address we're sending to.
    sockaddr_in6 to;
    memset(&to, 0, sizeof(to));
    to.sin6_family = AF_INET6;
    to.sin6_port = htons(pkt->getRemotePort());
    memcpy(&to.sin6_addr,
           pkt->getRemoteAddr().getAddress().to_v6().to_bytes().data(),
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
    struct in6_pktinfo *pktinfo = convertPktInfo6(CMSG_DATA(cmsg));
    memset(pktinfo, 0, sizeof(struct in6_pktinfo));
    pktinfo->ipi6_ifindex = pkt->getIndex();
    m.msg_controllen = cmsg->cmsg_len;

    pkt->updateTimestamp();

    result = sendmsg(getSocket(*pkt), &m, 0);
    if (result < 0) {
        isc_throw(SocketWriteError, "Pkt6 send failed: sendmsg() returned " << result);
    }

    return (result);
}

bool
IfaceMgr::send(const Pkt4Ptr& pkt)
{
    Iface* iface = getIface(pkt->getIface());
    if (!iface) {
        isc_throw(BadValue, "Unable to send Pkt4. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

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

    // call OS-specific routines (like setting interface index)
    os_send4(m, control_buf_, control_buf_len_, pkt);

    pkt->updateTimestamp();

    int result = sendmsg(getSocket(*pkt), &m, 0);
    if (result < 0) {
        isc_throw(SocketWriteError, "pkt4 send failed");
    }

    return (result);
}


boost::shared_ptr<Pkt4>
IfaceMgr::receive4(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    const SocketInfo* candidate = 0;
    IfaceCollection::const_iterator iface;
    fd_set sockets;
    int maxfd = 0;
    stringstream names;

    FD_ZERO(&sockets);

    /// @todo: marginal performance optimization. We could create the set once
    /// and then use its copy for select(). Please note that select() modifies
    /// provided set to indicated which sockets have something to read.
    for (iface = ifaces_.begin(); iface != ifaces_.end(); ++iface) {

        const SocketCollection& socket_collection = iface->getSockets();
        for (SocketCollection::const_iterator s = socket_collection.begin();
             s != socket_collection.end(); ++s) {

            // Only deal with IPv4 addresses.
            if (s->addr_.getFamily() == AF_INET) {
                names << s->sockfd_ << "(" << iface->getName() << ") ";

                // Add this socket to listening set
                FD_SET(s->sockfd_, &sockets);
                if (maxfd < s->sockfd_) {
                    maxfd = s->sockfd_;
                }
            }
        }
    }

    // if there is session socket registered...
    if (session_socket_ != INVALID_SOCKET) {
        // at it to the set as well
        FD_SET(session_socket_, &sockets);
        if (maxfd < session_socket_)
            maxfd = session_socket_;
        names << session_socket_ << "(session)";
    }

    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    int result = select(maxfd + 1, &sockets, NULL, NULL, &select_timeout);

    if (result == 0) {
        // nothing received and timeout has been reached
        return (Pkt4Ptr()); // NULL
    } else if (result < 0) {
        isc_throw(SocketReadError, strerror(errno));
    }

    // Let's find out which socket has the data
    if ((session_socket_ != INVALID_SOCKET) && (FD_ISSET(session_socket_, &sockets))) {
        // something received over session socket
        if (session_callback_) {
            // in theory we could call io_service.run_one() here, instead of
            // implementing callback mechanism, but that would introduce
            // asiolink dependency to libdhcp++ and that is something we want
            // to avoid (see CPE market and out long term plans for minimalistic
            // implementations.
            session_callback_();
        }

        return (Pkt4Ptr()); // NULL
    }

    // Let's find out which interface/socket has the data
    for (iface = ifaces_.begin(); iface != ifaces_.end(); ++iface) {
        const SocketCollection& socket_collection = iface->getSockets();
        for (SocketCollection::const_iterator s = socket_collection.begin();
             s != socket_collection.end(); ++s) {
            if (FD_ISSET(s->sockfd_, &sockets)) {
                candidate = &(*s);
                break;
            }
        }
        if (candidate) {
            break;
        }
    }

    if (!candidate) {
        isc_throw(SocketReadError, "received data over unknown socket");
    }

    // Now we have a socket, let's get some data from it!
    struct sockaddr_in from_addr;
    uint8_t buf[RCVBUFSIZE];

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
    v.iov_len = RCVBUFSIZE;
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

    result = recvmsg(candidate->sockfd_, &m, 0);
    if (result < 0) {
        isc_throw(SocketReadError, "failed to receive UDP4 data");
    }

    // We have all data let's create Pkt4 object.
    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(buf, result));

    pkt->updateTimestamp();

    unsigned int ifindex = iface->getIndex();

    IOAddress from(htonl(from_addr.sin_addr.s_addr));
    uint16_t from_port = htons(from_addr.sin_port);

    // Set receiving interface based on information, which socket was used to
    // receive data. OS-specific info (see os_receive4()) may be more reliable,
    // so this value may be overwritten.
    pkt->setIndex(ifindex);
    pkt->setIface(iface->getName());
    pkt->setRemoteAddr(from);
    pkt->setRemotePort(from_port);
    pkt->setLocalPort(candidate->port_);

    if (!os_receive4(m, pkt)) {
        isc_throw(SocketReadError, "unable to find pktinfo");
    }

    return (pkt);
}

Pkt6Ptr IfaceMgr::receive6(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */ ) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }

    const SocketInfo* candidate = 0;
    fd_set sockets;
    int maxfd = 0;
    stringstream names;

    FD_ZERO(&sockets);

    /// @todo: marginal performance optimization. We could create the set once
    /// and then use its copy for select(). Please note that select() modifies
    /// provided set to indicated which sockets have something to read.
    IfaceCollection::const_iterator iface;
    for (iface = ifaces_.begin(); iface != ifaces_.end(); ++iface) {
        const SocketCollection& socket_collection = iface->getSockets();
        for (SocketCollection::const_iterator s = socket_collection.begin();
             s != socket_collection.end(); ++s) {

            // Only deal with IPv4 addresses.
            if (s->addr_.getFamily() == AF_INET6) {
                names << s->sockfd_ << "(" << iface->getName() << ") ";

                // Add this socket to listening set
                FD_SET(s->sockfd_, &sockets);
                if (maxfd < s->sockfd_) {
                    maxfd = s->sockfd_;
                }
            }
        }
    }

    // if there is session socket registered...
    if (session_socket_ != INVALID_SOCKET) {
        // at it to the set as well
        FD_SET(session_socket_, &sockets);
        if (maxfd < session_socket_)
            maxfd = session_socket_;
        names << session_socket_ << "(session)";
    }

    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    int result = select(maxfd + 1, &sockets, NULL, NULL, &select_timeout);

    if (result == 0) {
        // nothing received and timeout has been reached
        return (Pkt6Ptr()); // NULL
    } else if (result < 0) {
        isc_throw(SocketReadError, strerror(errno));
    }

    // Let's find out which socket has the data
    if ((session_socket_ != INVALID_SOCKET) && (FD_ISSET(session_socket_, &sockets))) {
        // something received over session socket
        if (session_callback_) {
            // in theory we could call io_service.run_one() here, instead of
            // implementing callback mechanism, but that would introduce
            // asiolink dependency to libdhcp++ and that is something we want
            // to avoid (see CPE market and out long term plans for minimalistic
            // implementations.
            session_callback_();
        }

        return (Pkt6Ptr()); // NULL
    }

    // Let's find out which interface/socket has the data
    for (iface = ifaces_.begin(); iface != ifaces_.end(); ++iface) {
        const SocketCollection& socket_collection = iface->getSockets();
        for (SocketCollection::const_iterator s = socket_collection.begin();
             s != socket_collection.end(); ++s) {
            if (FD_ISSET(s->sockfd_, &sockets)) {
                candidate = &(*s);
                break;
            }
        }
        if (candidate) {
            break;
        }
    }

    if (!candidate) {
        isc_throw(SocketReadError, "received data over unknown socket");
    }

    // Now we have a socket, let's get some data from it!
    uint8_t buf[RCVBUFSIZE];
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
    v.iov_len = RCVBUFSIZE;
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

    result = recvmsg(candidate->sockfd_, &m, 0);

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
                pktinfo = convertPktInfo6(CMSG_DATA(cmsg));
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

    // Let's create a packet.
    Pkt6Ptr pkt;
    try {
        pkt = Pkt6Ptr(new Pkt6(buf, result));
    } catch (const std::exception& ex) {
        isc_throw(SocketReadError, "failed to create new packet");
    }

    pkt->updateTimestamp();

    pkt->setLocalAddr(IOAddress::from_bytes(AF_INET6,
                      reinterpret_cast<const uint8_t*>(&to_addr)));
    pkt->setRemoteAddr(IOAddress::from_bytes(AF_INET6,
                       reinterpret_cast<const uint8_t*>(&from.sin6_addr)));
    pkt->setRemotePort(ntohs(from.sin6_port));
    pkt->setIndex(ifindex);

    Iface* received = getIface(pkt->getIndex());
    if (received) {
        pkt->setIface(received->getName());
    } else {
        isc_throw(SocketReadError, "received packet over unknown interface"
                  << "(ifindex=" << pkt->getIndex() << ")");
    }

    return (pkt);
}

uint16_t IfaceMgr::getSocket(const isc::dhcp::Pkt6& pkt) {
    Iface* iface = getIface(pkt.getIface());
    if (iface == NULL) {
        isc_throw(BadValue, "Tried to find socket for non-existent interface "
                  << pkt.getIface());
    }

    const SocketCollection& socket_collection = iface->getSockets();
    SocketCollection::const_iterator s;
    for (s = socket_collection.begin(); s != socket_collection.end(); ++s) {
        if ((s->family_ == AF_INET6) &&
            (!s->addr_.getAddress().to_v6().is_multicast())) {
            return (s->sockfd_);
        }
        /// @todo: Add more checks here later. If remote address is
        /// not link-local, we can't use link local bound socket
        /// to send data.
    }

    isc_throw(Unexpected, "Interface " << iface->getFullName()
              << " does not have any suitable IPv6 sockets open.");
}

uint16_t IfaceMgr::getSocket(isc::dhcp::Pkt4 const& pkt) {
    Iface* iface = getIface(pkt.getIface());
    if (iface == NULL) {
        isc_throw(BadValue, "Tried to find socket for non-existent interface "
                  << pkt.getIface());
    }

    const SocketCollection& socket_collection = iface->getSockets();
    SocketCollection::const_iterator s;
    for (s = socket_collection.begin(); s != socket_collection.end(); ++s) {
        if (s->family_ == AF_INET) {
            return (s->sockfd_);
        }
        /// TODO: Add more checks here later. If remote address is
        /// not link-local, we can't use link local bound socket
        /// to send data.
    }

    isc_throw(Unexpected, "Interface " << iface->getFullName()
              << " does not have any suitable IPv4 sockets open.");
}

} // end of namespace isc::dhcp
} // end of namespace isc
