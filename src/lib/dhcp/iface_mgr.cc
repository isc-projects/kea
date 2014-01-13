// Copyright (C) 2011-2014 Internet Systems Consortium, Inc. ("ISC")
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

// This must be included before udp_endpoint.h
#include <asio.hpp>

#include <asiolink/io_error.h>
#include <asiolink/udp_endpoint.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/pkt_filter_inet6.h>
#include <exceptions/exceptions.h>
#include <util/io/pktinfo_utilities.h>

#include <cstring>
#include <errno.h>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>

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

Iface::Iface(const std::string& name, int ifindex)
    :name_(name), ifindex_(ifindex), mac_len_(0), hardware_type_(0),
     flag_loopback_(false), flag_up_(false), flag_running_(false),
     flag_multicast_(false), flag_broadcast_(false), flags_(0),
     inactive4_(false), inactive6_(false)
{
    memset(mac_, 0, sizeof(mac_));
}

void
Iface::closeSockets() {
    // Close IPv4 sockets.
    closeSockets(AF_INET);
    // Close IPv6 sockets.
    closeSockets(AF_INET6);
}

void
Iface::closeSockets(const uint16_t family) {
    // Check that the correect 'family' value has been specified.
    // The possible values are AF_INET or AF_INET6. Note that, in
    // the current code they are used to differentiate that the
    // socket is used to transmit IPv4 or IPv6 traffic. However,
    // the actual family types of the sockets may be different,
    // e.g. for LPF we are using raw sockets of AF_PACKET family.
    //
    // @todo Consider replacing the AF_INET and AF_INET6 with some
    // enum which will not be confused with the actual socket type.
    if ((family != AF_INET) && (family != AF_INET6)) {
        isc_throw(BadValue, "Invalid socket family " << family
                  << " specified when requested to close all sockets"
                  << " which belong to this family");
    }
    // Search for the socket of the specific type.
    SocketCollection::iterator sock = sockets_.begin();
    while (sock != sockets_.end()) {
        if (sock->family_ == family) {
            // Close and delete the socket and move to the
            // next one.
            close(sock->sockfd_);
            // Close fallback socket if open.
            if (sock->fallbackfd_ >= 0) {
                close(sock->fallbackfd_);
            }
            sockets_.erase(sock++);

        } else {
            // Different type of socket. Let's move
            // to the next one.
            ++sock;

        }
    }
}

std::string
Iface::getFullName() const {
    ostringstream tmp;
    tmp << name_ << "/" << ifindex_;
    return (tmp.str());
}

std::string
Iface::getPlainMac() const {
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

void Iface::setMac(const uint8_t* mac, size_t len) {
    if (len > MAX_MAC_LEN) {
        isc_throw(OutOfRange, "Interface " << getFullName()
                  << " was detected to have link address of length "
                  << len << ", but maximum supported length is "
                  << MAX_MAC_LEN);
    }
    mac_len_ = len;
    memcpy(mac_, mac, len);
}

bool Iface::delAddress(const isc::asiolink::IOAddress& addr) {
    for (AddressCollection::iterator a = addrs_.begin();
         a!=addrs_.end(); ++a) {
        if (*a==addr) {
            addrs_.erase(a);
            return (true);
        }
    }
    return (false);
}

bool Iface::delSocket(uint16_t sockfd) {
    list<SocketInfo>::iterator sock = sockets_.begin();
    while (sock!=sockets_.end()) {
        if (sock->sockfd_ == sockfd) {
            close(sockfd);
            // Close fallback socket if open.
            if (sock->fallbackfd_ >= 0) {
                close(sock->fallbackfd_);
            }
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
     session_socket_(INVALID_SOCKET), session_callback_(NULL),
     packet_filter_(new PktFilterInet()),
     packet_filter6_(new PktFilterInet6())
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

void Iface::addUnicast(const isc::asiolink::IOAddress& addr) {
    for (Iface::AddressCollection::const_iterator i = unicasts_.begin();
         i != unicasts_.end(); ++i) {
        if (*i == addr) {
            isc_throw(BadValue, "Address " << addr.toText()
                      << " already defined on the " << name_ << " interface.");
        }
    }
    unicasts_.push_back(addr);
}

void IfaceMgr::closeSockets() {
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        iface->closeSockets();
    }
}

void
IfaceMgr::closeSockets(const uint16_t family) {
    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        iface->closeSockets(family);
    }
}

IfaceMgr::~IfaceMgr() {
    // control_buf_ is deleted automatically (scoped_ptr)
    control_buf_len_ = 0;

    closeSockets();
}

bool
IfaceMgr::isDirectResponseSupported() const {
    return (packet_filter_->isDirectResponseSupported());
}

void
IfaceMgr::setPacketFilter(const PktFilterPtr& packet_filter) {
    // Do not allow NULL pointer.
    if (!packet_filter) {
        isc_throw(InvalidPacketFilter, "NULL packet filter object specified for"
                  " DHCPv4");
    }
    // Different packet filters use different socket types. It does not make
    // sense to allow the change of packet filter when there are IPv4 sockets
    // open because they can't be used by the receive/send functions of the
    // new packet filter. Below, we check that there are no open IPv4 sockets.
    // If we find at least one, we have to fail. However, caller still has a
    // chance to replace the packet filter if he closes sockets explicitly.
    if (hasOpenSocket(AF_INET)) {
        // There is at least one socket open, so we have to fail.
        isc_throw(PacketFilterChangeDenied,
                  "it is not allowed to set new packet"
                  << " filter when there are open IPv4 sockets - need"
                  << " to close them first");
    }
    // Everything is fine, so replace packet filter.
    packet_filter_ = packet_filter;
}

void
IfaceMgr::setPacketFilter(const PktFilter6Ptr& packet_filter) {
    if (!packet_filter) {
        isc_throw(InvalidPacketFilter, "NULL packet filter object specified for"
                  " DHCPv6");
    }

    if (hasOpenSocket(AF_INET6)) {
        // There is at least one socket open, so we have to fail.
        isc_throw(PacketFilterChangeDenied,
                  "it is not allowed to set new packet"
                  << " filter when there are open IPv6 sockets - need"
                  << " to close them first");
    }

    packet_filter6_ = packet_filter;
}

bool
IfaceMgr::hasOpenSocket(const uint16_t family) const {
    // Iterate over all interfaces and search for open sockets.
    for (IfaceCollection::const_iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        const Iface::SocketCollection& sockets = iface->getSockets();
        for (Iface::SocketCollection::const_iterator sock = sockets.begin();
             sock != sockets.end(); ++sock) {
            // Check if the socket matches specified family.
            if (sock->family_ == family) {
                // There is at least one socket open, so return.
                return (true);
            }
        }
    }
    // There are no open sockets found for the specified family.
    return (false);
}

bool
IfaceMgr::hasOpenSocket(const IOAddress& addr) const {
    // Iterate over all interfaces and search for open sockets.
    for (IfaceCollection::const_iterator iface = ifaces_.begin();
         iface != ifaces_.end(); ++iface) {
        const Iface::SocketCollection& sockets = iface->getSockets();
        for (Iface::SocketCollection::const_iterator sock = sockets.begin();
             sock != sockets.end(); ++sock) {
            // Check if the socket address matches the specified address.
            if (sock->addr_ == addr) {
                return (true);
            }
        }
    }
    // There are no open sockets found for the specified family.
    return (false);
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



bool
IfaceMgr::openSockets4(const uint16_t port, const bool use_bcast,
                       IfaceMgrErrorMsgCallback error_handler) {
    int count = 0;

// This option is used to bind sockets to particular interfaces.
// This is currently the only way to discover on which interface
// the broadcast packet has been received. If this option is
// not supported then only one interface should be confugured
// to listen for broadcast traffic.
#ifdef SO_BINDTODEVICE
    const bool bind_to_device = true;
#else
    const bool bind_to_device = false;
#endif

    int bcast_num = 0;

    for (IfaceCollection::iterator iface = ifaces_.begin();
         iface != ifaces_.end();
         ++iface) {

        if (iface->flag_loopback_ ||
            !iface->flag_up_ ||
            !iface->flag_running_ ||
            iface->inactive4_) {
            continue;
        }

        Iface::AddressCollection addrs = iface->getAddresses();
        for (Iface::AddressCollection::iterator addr = addrs.begin();
             addr != addrs.end();
             ++addr) {

            // Skip all but V4 addresses.
            if (!addr->isV4()) {
                continue;
            }

            int sock = -1;
            // If selected interface is broadcast capable set appropriate
            // options on the socket so as it can receive and send broadcast
            // messages.
            if (iface->flag_broadcast_ && use_bcast) {
                // If our OS supports binding socket to a device we can listen
                // for broadcast messages on multiple interfaces. Otherwise we
                // bind to INADDR_ANY address but we can do it only once. Thus,
                // if one socket has been bound we can't do it any further.
                if (!bind_to_device && bcast_num > 0) {
                    handleSocketConfigError("SO_BINDTODEVICE socket option is"
                                            " not supported on this OS;"
                                            " therefore, DHCP server can only"
                                            " listen broadcast traffic on a"
                                            " single interface",
                                            error_handler);
                    continue;

                } else {
                    try {
                        // We haven't open any broadcast sockets yet, so we can
                        // open at least one more.
                        sock = openSocket(iface->getName(), *addr, port,
                                          true, true);
                    } catch (const Exception& ex) {
                        handleSocketConfigError(ex.what(), error_handler);
                        continue;

                    }
                    // Binding socket to an interface is not supported so we
                    // can't open any more broadcast sockets. Increase the
                    // number of open broadcast sockets.
                    if (!bind_to_device) {
                        ++bcast_num;
                    }
                }

            } else {
                try {
                    // Not broadcast capable, do not set broadcast flags.
                    sock = openSocket(iface->getName(), *addr, port,
                                      false, false);
                } catch (const Exception& ex) {
                    handleSocketConfigError(ex.what(), error_handler);
                    continue;
                }

            }
            if (sock < 0) {
                const char* errstr = strerror(errno);
                handleSocketConfigError(std::string("failed to open IPv4 socket,"
                                                    " reason:") + errstr,
                                        error_handler);
            } else {
                ++count;
            }

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
            !iface->flag_running_ ||
            iface->inactive6_) {
            continue;
        }

        // Open unicast sockets if there are any unicast addresses defined
        Iface::AddressCollection unicasts = iface->getUnicasts();
        for (Iface::AddressCollection::iterator addr = unicasts.begin();
             addr != unicasts.end(); ++addr) {

            sock = openSocket(iface->getName(), *addr, port);
            if (sock < 0) {
                const char* errstr = strerror(errno);
                isc_throw(SocketConfigError, "failed to open unicast socket on "
                          << addr->toText() << " on interface " << iface->getName()
                          << ", reason: " << errstr);
            }

            count++;

        }

        Iface::AddressCollection addrs = iface->getAddresses();
        for (Iface::AddressCollection::iterator addr = addrs.begin();
             addr != addrs.end();
             ++addr) {

            // Skip all but V6 addresses.
            if (!addr->isV6()) {
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

            // Open socket and join multicast group only if the interface
            // is multicast-capable.
            // @todo The DHCPv6 requires multicast so we may want to think
            // whether we want to open the socket on a multicast-incapable
            // interface or not. For now, we prefer to be liberal and allow
            // it for some odd use cases which may utilize non-multicast
            // interfaces. Perhaps a warning should be emitted if the
            // interface is not a multicast one.
            sock = openSocket(iface->getName(), *addr, port,
                              iface->flag_multicast_);
            if (sock < 0) {
                const char* errstr = strerror(errno);
                isc_throw(SocketConfigError, "failed to open link-local"
                          " socket on " << addr->toText() << " on interface "
                          << iface->getName() << ", reason: " << errstr);
            }

            count++;

            /// @todo: Remove this ifdef once we start supporting BSD systems.
#if defined(OS_LINUX)
            // To receive multicast traffic, Linux requires binding socket to
            // a multicast group. That in turn doesn't work on NetBSD.
            if (iface->flag_multicast_) {
                int sock2 =
                    openSocket(iface->getName(),
                               IOAddress(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
                               port);
                if (sock2 < 0) {
                    const char* errstr = strerror(errno);
                    isc_throw(SocketConfigError, "Failed to open multicast"
                              " socket on interface " << iface->getFullName()
                              << ", reason:" << errstr);
                    iface->delSocket(sock); // delete previously opened socket
                }
            }
#endif
        }
    }
    return (count > 0);
}

void
IfaceMgr::handleSocketConfigError(const std::string& errmsg,
                                  IfaceMgrErrorMsgCallback handler) {
    // If error handler is installed, we don't want to throw an exception, but
    // rather call this handler.
    if (handler != NULL) {
        handler(errmsg);

    } else {
        isc_throw(SocketConfigError, errmsg);

    }
}

void
IfaceMgr::printIfaces(std::ostream& out /*= std::cout*/) {
    for (IfaceCollection::const_iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {

        const Iface::AddressCollection& addrs = iface->getAddresses();

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

        for (Iface::AddressCollection::const_iterator addr = addrs.begin();
             addr != addrs.end(); ++addr) {
            out << "  " << addr->toText();
        }
        out << endl;
    }
}

Iface*
IfaceMgr::getIface(int ifindex) {
    for (IfaceCollection::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        if (iface->getIndex() == ifindex)
            return (&(*iface));
    }

    return (NULL); // not found
}

Iface*
IfaceMgr::getIface(const std::string& ifname) {
    for (IfaceCollection::iterator iface=ifaces_.begin();
         iface!=ifaces_.end();
         ++iface) {
        if (iface->getName() == ifname)
            return (&(*iface));
    }

    return (NULL); // not found
}

void
IfaceMgr::clearIfaces() {
    ifaces_.clear();
}

int IfaceMgr::openSocket(const std::string& ifname, const IOAddress& addr,
                         const uint16_t port, const bool receive_bcast,
                         const bool send_bcast) {
    Iface* iface = getIface(ifname);
    if (!iface) {
        isc_throw(BadValue, "There is no " << ifname << " interface present.");
    }
    if (addr.isV4()) {
        return openSocket4(*iface, addr, port, receive_bcast, send_bcast);

    } else if (addr.isV6()) {
        return openSocket6(*iface, addr, port, receive_bcast);

    } else {
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
        Iface::AddressCollection addrs = iface->getAddresses();
        Iface::AddressCollection::iterator addr_it = addrs.begin();
        while (addr_it != addrs.end()) {
            if (addr_it->getFamily() == family) {
                // We have interface and address so let's open socket.
                // This may cause isc::Unexpected exception.
                return (openSocket(iface->getName(), *addr_it, port, false));
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

        Iface::AddressCollection addrs = iface->getAddresses();

        for (Iface::AddressCollection::iterator addr_it = addrs.begin();
             addr_it != addrs.end();
             ++addr_it) {

            // Local address must match one of the addresses
            // on detected interfaces. If it does, we have
            // address and interface detected so we can open
            // socket.
            if (*addr_it == addr) {
                // Open socket using local interface, address and port.
                // This may cause isc::Unexpected exception.
                return (openSocket(iface->getName(), *addr_it, port, false));
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
    if (remote_addr.isV4() &&
        (remote_addr == IOAddress(DHCP_IPV4_BROADCAST_ADDRESS))) {
        // Socket has to be open prior to setting the broadcast
        // option. Otherwise set_option will complain about
        // bad file descriptor.

        // @todo: We don't specify interface in any way here. 255.255.255.255
        // We can very easily end up with a socket working on a different
        // interface.
        sock.open(asio::ip::udp::v4(), err_code);
        if (err_code) {
            const char* errstr = strerror(errno);
            isc_throw(Unexpected, "failed to open UDPv4 socket, reason:"
                      << errstr);
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


int
IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, uint16_t port,
                      const bool join_multicast) {
    // Assuming that packet filter is not NULL, because its modifier checks it.
    SocketInfo info = packet_filter6_->openSocket(iface, addr, port,
                                                  join_multicast);
    iface.addSocket(info);

    return (info.sockfd_);
}

int
IfaceMgr::openSocket4(Iface& iface, const IOAddress& addr,
                          const uint16_t port, const bool receive_bcast,
                          const bool send_bcast) {

    // Assuming that packet filter is not NULL, because its modifier checks it.
    SocketInfo info = packet_filter_->openSocket(iface, addr, port,
                                                 receive_bcast, send_bcast);
    iface.addSocket(info);

    return (info.sockfd_);
}

bool
IfaceMgr::send(const Pkt6Ptr& pkt) {
    Iface* iface = getIface(pkt->getIface());
    if (!iface) {
        isc_throw(BadValue, "Unable to send DHCPv6 message. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    // Assuming that packet filter is not NULL, because its modifier checks it.
    return (packet_filter6_->send(*iface, getSocket(*pkt), pkt));
}

bool
IfaceMgr::send(const Pkt4Ptr& pkt) {

    Iface* iface = getIface(pkt->getIface());
    if (!iface) {
        isc_throw(BadValue, "Unable to send DHCPv4 message. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    // Assuming that packet filter is not NULL, because its modifier checks it.
    return (packet_filter_->send(*iface, getSocket(*pkt).sockfd_, pkt));
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

        const Iface::SocketCollection& socket_collection = iface->getSockets();
        for (Iface::SocketCollection::const_iterator s = socket_collection.begin();
             s != socket_collection.end(); ++s) {

            // Only deal with IPv4 addresses.
            if (s->addr_.isV4()) {
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
        const Iface::SocketCollection& socket_collection = iface->getSockets();
        for (Iface::SocketCollection::const_iterator s = socket_collection.begin();
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
    // Assuming that packet filter is not NULL, because its modifier checks it.
    return (packet_filter_->receive(*iface, *candidate));
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
        const Iface::SocketCollection& socket_collection = iface->getSockets();
        for (Iface::SocketCollection::const_iterator s = socket_collection.begin();
             s != socket_collection.end(); ++s) {

            // Only deal with IPv6 addresses.
            if (s->addr_.isV6()) {
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
        const Iface::SocketCollection& socket_collection = iface->getSockets();
        for (Iface::SocketCollection::const_iterator s = socket_collection.begin();
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
    // Assuming that packet filter is not NULL, because its modifier checks it.
    return (packet_filter6_->receive(*candidate));
}

uint16_t IfaceMgr::getSocket(const isc::dhcp::Pkt6& pkt) {
    Iface* iface = getIface(pkt.getIface());
    if (iface == NULL) {
        isc_throw(BadValue, "Tried to find socket for non-existent interface");
    }


    const Iface::SocketCollection& socket_collection = iface->getSockets();

    Iface::SocketCollection::const_iterator candidate = socket_collection.end();

    Iface::SocketCollection::const_iterator s;
    for (s = socket_collection.begin(); s != socket_collection.end(); ++s) {

        // We should not merge those conditions for debugging reasons.

        // V4 sockets are useless for sending v6 packets.
        if (s->family_ != AF_INET6) {
            continue;
        }

        // Sockets bound to multicast address are useless for sending anything.
        if (s->addr_.getAddress().to_v6().is_multicast()) {
            continue;
        }

        if (s->addr_ == pkt.getLocalAddr()) {
            // This socket is bound to the source address. This is perfect
            // match, no need to look any further.
            return (s->sockfd_);
        }

        // If we don't have any other candidate, this one will do
        if (candidate == socket_collection.end()) {
            candidate = s;
        } else {
            // If we want to send something to link-local and the socket is
            // bound to link-local or we want to send to global and the socket
            // is bound to global, then use it as candidate
            if ( (pkt.getRemoteAddr().getAddress().to_v6().is_link_local() &&
                s->addr_.getAddress().to_v6().is_link_local()) ||
                 (!pkt.getRemoteAddr().getAddress().to_v6().is_link_local() &&
                  !s->addr_.getAddress().to_v6().is_link_local()) ) {
                candidate = s;
            }
        }
    }

    if (candidate != socket_collection.end()) {
        return (candidate->sockfd_);
    }

    isc_throw(Unexpected, "Interface " << iface->getFullName()
              << " does not have any suitable IPv6 sockets open.");
}

SocketInfo
IfaceMgr::getSocket(isc::dhcp::Pkt4 const& pkt) {
    Iface* iface = getIface(pkt.getIface());
    if (iface == NULL) {
        isc_throw(BadValue, "Tried to find socket for non-existent interface");
    }

    const Iface::SocketCollection& socket_collection = iface->getSockets();
    Iface::SocketCollection::const_iterator s;
    for (s = socket_collection.begin(); s != socket_collection.end(); ++s) {
        if (s->family_ == AF_INET) {
            return (*s);
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
