// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/iface_mgr_error_handler.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/pkt_filter_inet6.h>
#include <exceptions/exceptions.h>
#include <util/io/pktinfo_utilities.h>

#include <boost/foreach.hpp>

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
using namespace isc::util;
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
        if (a->get() == addr) {
            addrs_.erase(a);
            return (true);
        }
    }
    return (false);
}

bool Iface::delSocket(const uint16_t sockfd) {
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
     packet_filter_(new PktFilterInet()),
     packet_filter6_(new PktFilterInet6()),
     test_mode_(false)
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
    BOOST_FOREACH(Address a, unicasts_) {
        if (a.get() == addr) {
            isc_throw(BadValue, "Address " << addr
                      << " already defined on the " << name_ << " interface.");
        }
    }
    unicasts_.push_back(OptionalValue<IOAddress>(addr, true));
}

bool
Iface::getAddress4(isc::asiolink::IOAddress& address) const {
    // Iterate over existing addresses assigned to the interface.
    // Try to find the one that is IPv4.
    BOOST_FOREACH(Address addr, getAddresses()) {
        // If address is IPv4, we assign it to the function argument
        // and return true.
        if (addr.get().isV4()) {
            address = addr.get();
            return (true);
        }
    }
    // There is no IPv4 address assigned to this interface.
    return (false);
}

bool
Iface::hasAddress(const isc::asiolink::IOAddress& address) const {
    BOOST_FOREACH(Address addr, getAddresses()) {
        if (address == addr.get()) {
            return (true);
        }
    }
    return (false);
}

void
Iface::addAddress(const isc::asiolink::IOAddress& addr) {
    addrs_.push_back(Address(addr, OptionalValueState(true)));
}

void
Iface::setActive(const IOAddress& address, const bool active) {
    for (AddressCollection::iterator addr_it = addrs_.begin();
         addr_it != addrs_.end(); ++addr_it) {
        if (address == addr_it->get()) {
            addr_it->specify(OptionalValueState(active));
            return;
        }
    }
    isc_throw(BadValue, "specified address " << address << " was not"
              " found on the interface " << getName());
}

void
Iface::setActive(const bool active) {
    for (AddressCollection::iterator addr_it = addrs_.begin();
         addr_it != addrs_.end(); ++addr_it) {
        addr_it->specify(OptionalValueState(active));
    }
}

unsigned int
Iface::countActive4() const {
    uint16_t count = 0;
    BOOST_FOREACH(Address addr, addrs_) {
        if (addr.get().isV4() && addr.isSpecified()) {
            ++count;
        }
    }
    return (count);
}

void IfaceMgr::closeSockets() {
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        iface->closeSockets();
    }
}

void
IfaceMgr::closeSockets(const uint16_t family) {
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
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
IfaceMgr::addExternalSocket(int socketfd, SocketCallback callback) {
    if (socketfd < 0) {
        isc_throw(BadValue, "Attempted to install callback for invalid socket "
                  << socketfd);
    }
    BOOST_FOREACH(SocketCallbackInfo s, callbacks_) {
        // There's such a socket description there already.
        // Update the callback and we're done
        if (s.socket_ == socketfd) {
            s.callback_ = callback;
            return;
        }
    }

    // Add a new entry to the callbacks vector
    SocketCallbackInfo x;
    x.socket_ = socketfd;
    x.callback_ = callback;
    callbacks_.push_back(x);
}

void
IfaceMgr::deleteExternalSocket(int socketfd) {
    for (SocketCallbackInfoContainer::iterator s = callbacks_.begin();
         s != callbacks_.end(); ++s) {
        if (s->socket_ == socketfd) {
            callbacks_.erase(s);
            return;
        }
    }
}

void
IfaceMgr::deleteAllExternalSockets() {
    callbacks_.clear();
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
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        BOOST_FOREACH(SocketInfo sock, iface->getSockets()) {
            // Check if the socket matches specified family.
            if (sock.family_ == family) {
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
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        BOOST_FOREACH(SocketInfo sock, iface->getSockets()) {
            // Check if the socket address matches the specified address or
            // if address is unspecified (in6addr_any).
            if (sock.addr_ == addr) {
                return (true);

            } else if (sock.addr_ == IOAddress("::")) {
                // Handle the case that the address is unspecified (any).
                // In this case, we should check if the specified address
                // belongs to any of the interfaces.
                BOOST_FOREACH(Iface::Address a, iface->getAddresses()) {
                    if (addr == a.get()) {
                        return (true);
                    }
                }
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

    IfacePtr iface(new Iface(ifaceName, if_nametoindex(ifaceName.c_str())));
    iface->flag_up_ = true;
    iface->flag_running_ = true;

    // Note that we claim that this is not a loopback. iface_mgr tries to open a
    // socket on all interaces that are up, running and not loopback. As this is
    // the only interface we were able to detect, let's pretend this is a normal
    // interface.
    iface->flag_loopback_ = false;
    iface->flag_multicast_ = true;
    iface->flag_broadcast_ = true;
    iface->setHWType(HWTYPE_ETHERNET);

    iface->addAddress(IOAddress(v4addr));
    iface->addAddress(IOAddress(v6addr));
    addInterface(iface);
}

bool
IfaceMgr::openSockets4(const uint16_t port, const bool use_bcast,
                       IfaceMgrErrorMsgCallback error_handler) {
    int count = 0;
    int bcast_num = 0;

    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        // If the interface is inactive, there is nothing to do. Simply
        // proceed to the next detected interface.
        if (iface->inactive4_) {
            continue;

        } else {
            // If the interface has been specified in the configuration that
            // it should be used to listen the DHCP traffic we have to check
            // that the interface configuration is valid and that the interface
            // is not a loopback interface. In both cases, we want to report
            // that the socket will not be opened.
            if (iface->flag_loopback_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "must not open socket on the loopback"
                               " interface " << iface->getName());
                continue;

            }

            IOAddress out_address("0.0.0.0");
            if (!iface->flag_up_ || !iface->flag_running_ ||
                !iface->getAddress4(out_address)) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " is down or has no usable IPv4"
                               " addresses configured");
                continue;
            }
        }

        BOOST_FOREACH(Iface::Address addr, iface->getAddresses()) {
            // Skip non-IPv4 addresses and those that weren't selected..
            if (!addr.get().isV4() || !addr.isSpecified()) {
                continue;
            }

            // If selected interface is broadcast capable set appropriate
            // options on the socket so as it can receive and send broadcast
            // messages.
            if (iface->flag_broadcast_ && use_bcast) {
                // The DHCP server must have means to determine which interface
                // the broadcast packets are coming from. This is achieved by
                // binding a socket to the device (interface) and specialized
                // packet filters (e.g. BPF and LPF) implement this mechanism.
                // If the PktFilterInet (generic one) is used, the socket is
                // bound to INADDR_ANY which effectively binds the socket to
                // all addresses on all interfaces. So, only one of those can
                // be opened. Currently, the direct response support is
                // provided by the PktFilterLPF and PktFilterBPF, so by checking
                // the support for direct response we actually determine that
                // one of those objects is in use. For all other objects we
                // assume that binding to the device is not supported and we
                // cease opening sockets and display the appropriate message.
                if (!isDirectResponseSupported() && bcast_num > 0) {
                    IFACEMGR_ERROR(SocketConfigError, error_handler,
                                   "Binding socket to an interface is not"
                                   " supported on this OS; therefore only"
                                   " one socket listening to broadcast traffic"
                                   " can be opened. Sockets will not be opened"
                                   " on remaining interfaces");
                    continue;

                } else {
                    try {
                        // We haven't open any broadcast sockets yet, so we can
                        // open at least one more.
                        openSocket(iface->getName(), addr.get(), port, true, true);
                    } catch (const Exception& ex) {
                        IFACEMGR_ERROR(SocketConfigError, error_handler,
                                       "failed to open socket on interface "
                                       << iface->getName() << ", reason: "
                                       << ex.what());
                        continue;

                    }
                    // Binding socket to an interface is not supported so we
                    // can't open any more broadcast sockets. Increase the
                    // number of open broadcast sockets.
                    ++bcast_num;
                }

            } else {
                try {
                    // Not broadcast capable, do not set broadcast flags.
                    openSocket(iface->getName(), addr.get(), port, false, false);
                } catch (const Exception& ex) {
                    IFACEMGR_ERROR(SocketConfigError, error_handler,
                                   "failed to open socket on interface "
                                   << iface->getName() << ", reason: "
                                   << ex.what());
                    continue;
                }

            }
            ++count;

        }
    }
    return (count > 0);
}

bool
IfaceMgr::openSockets6(const uint16_t port,
                       IfaceMgrErrorMsgCallback error_handler) {
    int count = 0;

    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        if (iface->inactive6_) {
            continue;

        } else {
            // If the interface has been specified in the configuration that
            // it should be used to listen the DHCP traffic we have to check
            // that the interface configuration is valid and that the interface
            // is not a loopback interface. In both cases, we want to report
            // that the socket will not be opened.
            if (iface->flag_loopback_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "must not open socket on the loopback"
                               " interface " << iface->getName());
                continue;

            } else if (!iface->flag_up_ || !iface->flag_running_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " is down or has no usable IPv6"
                               " addresses configured");
                continue;
            }

        }

        // Open unicast sockets if there are any unicast addresses defined
        BOOST_FOREACH(Iface::Address addr, iface->getUnicasts()) {

            try {
                openSocket(iface->getName(), addr, port);
            } catch (const Exception& ex) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "Failed to open unicast socket on  interface "
                               << iface->getName() << ", reason: "
                               << ex.what());
                continue;
            }

            count++;

        }

        BOOST_FOREACH(Iface::Address addr, iface->getAddresses()) {

            // Skip all but V6 addresses.
            if (!addr.get().isV6()) {
                continue;
            }

            // Bind link-local addresses only. Otherwise we bind several sockets
            // on interfaces that have several global addresses. For examples
            // with interface with 2 global addresses, we would bind 3 sockets
            // (one for link-local and two for global). That would result in
            // getting each message 3 times.
            if (!addr.get().isV6LinkLocal()){
                continue;
            }

            // Run OS-specific function to open a socket capable of receiving
            // packets sent to All_DHCP_Relay_Agents_and_Servers multicast
            // address.
            if (openMulticastSocket(*iface, addr, port, error_handler)) {
                ++count;
            }

        }
    }
    return (count > 0);
}

void
IfaceMgr::printIfaces(std::ostream& out /*= std::cout*/) {
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
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

        BOOST_FOREACH(Iface::Address addr, addrs) {
            out << "  " << addr.get().toText();
        }
        out << endl;
    }
}

IfacePtr
IfaceMgr::getIface(int ifindex) {
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        if (iface->getIndex() == ifindex)
            return (iface);
    }

    return (IfacePtr()); // not found
}

IfacePtr
IfaceMgr::getIface(const std::string& ifname) {
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        if (iface->getName() == ifname)
            return (iface);
    }

    return (IfacePtr()); // not found
}

void
IfaceMgr::clearIfaces() {
    ifaces_.clear();
}

void
IfaceMgr::clearUnicasts() {
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        iface->clearUnicasts();
    }
}

int IfaceMgr::openSocket(const std::string& ifname, const IOAddress& addr,
                         const uint16_t port, const bool receive_bcast,
                         const bool send_bcast) {
    IfacePtr iface = getIface(ifname);
    if (!iface) {
        isc_throw(BadValue, "There is no " << ifname << " interface present.");
    }
    if (addr.isV4()) {
        return openSocket4(*iface, addr, port, receive_bcast, send_bcast);

    } else if (addr.isV6()) {
        return openSocket6(*iface, addr, port, receive_bcast);

    } else {
        isc_throw(BadValue, "Failed to detect family of address: "
                  << addr);
    }
}

int IfaceMgr::openSocketFromIface(const std::string& ifname,
                                  const uint16_t port,
                                  const uint8_t family) {
    // Search for specified interface among detected interfaces.
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        if ((iface->getFullName() != ifname) &&
            (iface->getName() != ifname)) {
            continue;
        }

        // Interface is now detected. Search for address on interface
        // that matches address family (v6 or v4).
        Iface::AddressCollection addrs = iface->getAddresses();
        Iface::AddressCollection::iterator addr_it = addrs.begin();
        while (addr_it != addrs.end()) {
            if (addr_it->get().getFamily() == family) {
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
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        BOOST_FOREACH(Iface::Address a, iface->getAddresses()) {

            // Local address must match one of the addresses
            // on detected interfaces. If it does, we have
            // address and interface detected so we can open
            // socket.
            if (a.get() == addr) {
                // Open socket using local interface, address and port.
                // This may cause isc::Unexpected exception.
                return (openSocket(iface->getName(), a, port, false));
            }
        }
    }
    // If we got here it means that we did not find specified address
    // on any available interface.
    isc_throw(BadValue, "There is no such address " << addr);
}

int IfaceMgr::openSocketFromRemoteAddress(const IOAddress& remote_addr,
                                          const uint16_t port) {
    try {
        // Get local address to be used to connect to remote location.
        IOAddress local_address(getLocalAddress(remote_addr, port));
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

        // zero out the errno to be safe
        errno = 0;

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
    IfacePtr iface = getIface(pkt->getIface());
    if (!iface) {
        isc_throw(BadValue, "Unable to send DHCPv6 message. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    // Assuming that packet filter is not NULL, because its modifier checks it.
    return (packet_filter6_->send(*iface, getSocket(*pkt), pkt));
}

bool
IfaceMgr::send(const Pkt4Ptr& pkt) {

    IfacePtr iface = getIface(pkt->getIface());
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
    IfacePtr iface;
    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    /// @todo: marginal performance optimization. We could create the set once
    /// and then use its copy for select(). Please note that select() modifies
    /// provided set to indicated which sockets have something to read.
    BOOST_FOREACH(iface, ifaces_) {
        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {

            // Only deal with IPv4 addresses.
            if (s.addr_.isV4()) {

                // Add this socket to listening set
                FD_SET(s.sockfd_, &sockets);
                if (maxfd < s.sockfd_) {
                    maxfd = s.sockfd_;
                }
            }
        }
    }

    // if there are any callbacks for external sockets registered...
    if (!callbacks_.empty()) {
        BOOST_FOREACH(SocketCallbackInfo s, callbacks_) {
            FD_SET(s.socket_, &sockets);
            if (maxfd < s.socket_) {
                maxfd = s.socket_;
            }
        }
    }

    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    // zero out the errno to be safe
    errno = 0;

    int result = select(maxfd + 1, &sockets, NULL, NULL, &select_timeout);

    if (result == 0) {
        // nothing received and timeout has been reached
        return (Pkt4Ptr()); // NULL

    } else if (result < 0) {
        // In most cases we would like to know whether select() returned
        // an error because of a signal being received  or for some other
        // reasaon. This is because DHCP servers use signals to trigger
        // certain actions, like reconfiguration or graceful shutdown.
        // By catching a dedicated exception the caller will know if the
        // error returned by the function is due to the reception of the
        // signal or for some other reason.
        if (errno == EINTR) {
            isc_throw(SignalInterruptOnSelect, strerror(errno));
        } else {
            isc_throw(SocketReadError, strerror(errno));
        }
    }

    // Let's find out which socket has the data
    BOOST_FOREACH(SocketCallbackInfo s, callbacks_) {
        if (!FD_ISSET(s.socket_, &sockets)) {
            continue;
        }

        // something received over external socket

        // Calling the external socket's callback provides its service
        // layer access without integrating any specific features
        // in IfaceMgr
        if (s.callback_) {
            s.callback_();
        }

        return (Pkt4Ptr());
    }

    // Let's find out which interface/socket has the data
    BOOST_FOREACH(iface, ifaces_) {
        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {
            if (FD_ISSET(s.sockfd_, &sockets)) {
                candidate = &(s);
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

    FD_ZERO(&sockets);

    /// @todo: marginal performance optimization. We could create the set once
    /// and then use its copy for select(). Please note that select() modifies
    /// provided set to indicated which sockets have something to read.
    BOOST_FOREACH(IfacePtr iface, ifaces_) {

        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {
            // Only deal with IPv6 addresses.
            if (s.addr_.isV6()) {

                // Add this socket to listening set
                FD_SET(s.sockfd_, &sockets);
                if (maxfd < s.sockfd_) {
                    maxfd = s.sockfd_;
                }
            }
        }
    }

    // if there are any callbacks for external sockets registered...
    if (!callbacks_.empty()) {
        BOOST_FOREACH(SocketCallbackInfo s, callbacks_) {
            // Add it to the set as well
            FD_SET(s.socket_, &sockets);
            if (maxfd < s.socket_) {
                maxfd = s.socket_;
            }
        }
    }

    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    // zero out the errno to be safe
    errno = 0;

    int result = select(maxfd + 1, &sockets, NULL, NULL, &select_timeout);

    if (result == 0) {
        // nothing received and timeout has been reached
        return (Pkt6Ptr()); // NULL

    } else if (result < 0) {
        // In most cases we would like to know whether select() returned
        // an error because of a signal being received  or for some other
        // reasaon. This is because DHCP servers use signals to trigger
        // certain actions, like reconfiguration or graceful shutdown.
        // By catching a dedicated exception the caller will know if the
        // error returned by the function is due to the reception of the
        // signal or for some other reason.
        if (errno == EINTR) {
            isc_throw(SignalInterruptOnSelect, strerror(errno));
        } else {
            isc_throw(SocketReadError, strerror(errno));
        }
    }

    // Let's find out which socket has the data
    BOOST_FOREACH(SocketCallbackInfo s, callbacks_) {
        if (!FD_ISSET(s.socket_, &sockets)) {
            continue;
        }

        // something received over external socket

        // Calling the external socket's callback provides its service
        // layer access without integrating any specific features
        // in IfaceMgr
        if (s.callback_) {
            s.callback_();
        }

        return (Pkt6Ptr());
    }

    // Let's find out which interface/socket has the data
    BOOST_FOREACH(IfacePtr iface, ifaces_) {
        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {
            if (FD_ISSET(s.sockfd_, &sockets)) {
                candidate = &(s);
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
    IfacePtr iface = getIface(pkt.getIface());
    if (!iface) {
        isc_throw(IfaceNotFound, "Tried to find socket for non-existent interface");
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
        if (s->addr_.isV6Multicast()) {
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
            if ( (pkt.getRemoteAddr().isV6LinkLocal() &&
                s->addr_.isV6LinkLocal()) ||
                 (!pkt.getRemoteAddr().isV6LinkLocal() &&
                  !s->addr_.isV6LinkLocal()) ) {
                candidate = s;
            }
        }
    }

    if (candidate != socket_collection.end()) {
        return (candidate->sockfd_);
    }

    isc_throw(SocketNotFound, "Interface " << iface->getFullName()
              << " does not have any suitable IPv6 sockets open.");
}

SocketInfo
IfaceMgr::getSocket(isc::dhcp::Pkt4 const& pkt) {
    IfacePtr iface = getIface(pkt.getIface());
    if (iface == NULL) {
        isc_throw(IfaceNotFound, "Tried to find socket for non-existent interface");
    }

    const Iface::SocketCollection& socket_collection = iface->getSockets();
    // A candidate being an end of the iterator marks that it is a begining of
    // the socket search and that the candidate needs to be set to the first
    // socket found.
    Iface::SocketCollection::const_iterator candidate = socket_collection.end();
    Iface::SocketCollection::const_iterator s;
    for (s = socket_collection.begin(); s != socket_collection.end(); ++s) {
        if (s->family_ == AF_INET) {
            if (s->addr_ == pkt.getLocalAddr()) {
                return (*s);
            }

            if (candidate == socket_collection.end()) {
                candidate = s;
            }
        }
    }

    if (candidate == socket_collection.end()) {
        isc_throw(SocketNotFound, "Interface " << iface->getFullName()
                  << " does not have any suitable IPv4 sockets open.");
    }

    return (*candidate);
}

} // end of namespace isc::dhcp
} // end of namespace isc
