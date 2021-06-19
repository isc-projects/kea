// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
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
#include <util/multi_threading_mgr.h>

#include <boost/scoped_ptr.hpp>

#include <cstring>
#include <errno.h>
#include <fstream>
#include <functional>
#include <limits>
#include <sstream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#ifndef FD_COPY
#define FD_COPY(orig, copy) \
    do { \
        memmove(copy, orig, sizeof(fd_set)); \
    } while (0)
#endif

using namespace std;
using namespace isc::asiolink;
using namespace isc::util;
using namespace isc::util::io;
using namespace isc::util::io::internal;

namespace isc {
namespace dhcp {

IfaceMgr&
IfaceMgr::instance() {
    return (*instancePtr());
}

const IfaceMgrPtr&
IfaceMgr::instancePtr() {
    static IfaceMgrPtr iface_mgr(new IfaceMgr());
    return (iface_mgr);
}

Iface::Iface(const std::string& name, unsigned int ifindex)
    :name_(name), ifindex_(ifindex), mac_len_(0), hardware_type_(0),
     flag_loopback_(false), flag_up_(false), flag_running_(false),
     flag_multicast_(false), flag_broadcast_(false), flags_(0),
     inactive4_(false), inactive6_(false)
{
    // Sanity checks.
    if (name.empty()) {
        isc_throw(BadValue, "Interface name must not be empty");
    }
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
    // Check that the correct 'family' value has been specified.
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
    if (len > 0) {
        memcpy(mac_, mac, len);
    }
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
    : packet_filter_(new PktFilterInet()),
      packet_filter6_(new PktFilterInet6()),
      test_mode_(false),
      allow_loopback_(false) {

    // Ensure that PQMs have been created to guarantee we have
    // default packet queues in place.
    try {
        packet_queue_mgr4_.reset(new PacketQueueMgr4());
        packet_queue_mgr6_.reset(new PacketQueueMgr6());
    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "Failed to create PacketQueueManagers: " << ex.what());
    }

    try {

        // required for sending/receiving packets
        // let's keep it in front, just in case someone
        // wants to send anything during initialization
        detectIfaces();

    } catch (const std::exception& ex) {
        isc_throw(IfaceDetectError, ex.what());
    }
}

void Iface::addUnicast(const isc::asiolink::IOAddress& addr) {
    for (Address a : unicasts_) {
        if (a.get() == addr) {
            isc_throw(BadValue, "Address " << addr
                      << " already defined on the " << name_ << " interface.");
        }
    }
    unicasts_.push_back(Optional<IOAddress>(addr));
}

bool
Iface::getAddress4(isc::asiolink::IOAddress& address) const {
    // Iterate over existing addresses assigned to the interface.
    // Try to find the one that is IPv4.
    for (Address addr : getAddresses()) {
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
    for (Address addr : getAddresses()) {
        if (address == addr.get()) {
            return (true);
        }
    }
    return (false);
}

void
Iface::addAddress(const isc::asiolink::IOAddress& addr) {
    addrs_.push_back(Address(addr));
}

void
Iface::setActive(const IOAddress& address, const bool active) {
    for (AddressCollection::iterator addr_it = addrs_.begin();
         addr_it != addrs_.end(); ++addr_it) {
        if (address == addr_it->get()) {
            addr_it->unspecified(!active);
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
        addr_it->unspecified(!active);
    }
}

unsigned int
Iface::countActive4() const {
    uint16_t count = 0;
    for (Address addr : addrs_) {
        if (!addr.unspecified() && addr.get().isV4()) {
            ++count;
        }
    }
    return (count);
}

void IfaceMgr::closeSockets() {
    // Clears bound addresses.
    clearBoundAddresses();

    // Stops the receiver thread if there is one.
    stopDHCPReceiver();

    for (IfacePtr iface : ifaces_) {
        iface->closeSockets();
    }
}

void IfaceMgr::stopDHCPReceiver() {
    if (isDHCPReceiverRunning()) {
        dhcp_receiver_->stop();
    }

    dhcp_receiver_.reset();

    if (getPacketQueue4()) {
        getPacketQueue4()->clear();
    }

    if (getPacketQueue6()) {
        getPacketQueue6()->clear();
    }
}

IfaceMgr::~IfaceMgr() {
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
    std::lock_guard<std::mutex> lock(callbacks_mutex_);
    for (SocketCallbackInfo s : callbacks_) {
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
    std::lock_guard<std::mutex> lock(callbacks_mutex_);
    deleteExternalSocketInternal(socketfd);
}

void
IfaceMgr::deleteExternalSocketInternal(int socketfd) {
    for (SocketCallbackInfoContainer::iterator s = callbacks_.begin();
         s != callbacks_.end(); ++s) {
        if (s->socket_ == socketfd) {
            callbacks_.erase(s);
            return;
        }
    }
}

int
IfaceMgr::purgeBadSockets() {
    std::lock_guard<std::mutex> lock(callbacks_mutex_);
    std::vector<int> bad_fds;
    for (SocketCallbackInfo s : callbacks_) {
        errno = 0;
        if (fcntl(s.socket_, F_GETFD) < 0 && (errno == EBADF)) {
            bad_fds.push_back(s.socket_);
        }
    }

    for (auto bad_fd : bad_fds) {
        deleteExternalSocketInternal(bad_fd);
    }

    return (bad_fds.size());
}

void
IfaceMgr::deleteAllExternalSockets() {
    std::lock_guard<std::mutex> lock(callbacks_mutex_);
    callbacks_.clear();
}

void
IfaceMgr::setPacketFilter(const PktFilterPtr& packet_filter) {
    // Do not allow null pointer.
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
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo sock : iface->getSockets()) {
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
    // Fast track for IPv4 using bound addresses.
    if (addr.isV4() && !bound_address_.empty()) {
        return (bound_address_.count(addr.toUint32()) != 0);
    }
    // Iterate over all interfaces and search for open sockets.
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo sock : iface->getSockets()) {
            // Check if the socket address matches the specified address or
            // if address is unspecified (in6addr_any).
            if (sock.addr_ == addr) {
                return (true);
            } else if (sock.addr_.isV6Zero()) {
                // Handle the case that the address is unspecified (any).
                // This happens only with IPv6 so we do not check IPv4.
                // In this case, we should check if the specified address
                // belongs to any of the interfaces.
                for (IfacePtr it : ifaces_) {
                    for (Iface::Address a : it->getAddresses()) {
                        if (addr == a.get()) {
                            return (true);
                        }
                    }
                }
                // The address does not belongs to any interface.
                return (false);
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
    // socket on all interfaces that are up, running and not loopback. As this is
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

    for (IfacePtr iface : ifaces_) {
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
            // Relax the check when the loopback interface was explicitly
            // allowed
            if (iface->flag_loopback_ && !allow_loopback_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "must not open socket on the loopback"
                               " interface " << iface->getName());
                continue;

            }

            if (!iface->flag_up_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " is down");
                continue;
            }

            if (!iface->flag_running_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " is not running");
                continue;
            }

            IOAddress out_address("0.0.0.0");
            if (!iface->getAddress4(out_address)) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " has no usable IPv4 addresses configured");
                continue;
            }
        }

        for (Iface::Address addr : iface->getAddresses()) {
            // Skip non-IPv4 addresses and those that weren't selected..
            if (addr.unspecified() || !addr.get().isV4()) {
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

    // If we have open sockets, start the receiver.
    if (count > 0) {
        // Collects bound addresses.
        collectBoundAddresses();

        // Starts the receiver thread (if queueing is enabled).
        startDHCPReceiver(AF_INET);
    }

    return (count > 0);
}

bool
IfaceMgr::openSockets6(const uint16_t port,
                       IfaceMgrErrorMsgCallback error_handler) {
    int count = 0;

    for (IfacePtr iface : ifaces_) {
        if (iface->inactive6_) {
            continue;

        } else {
            // If the interface has been specified in the configuration that
            // it should be used to listen the DHCP traffic we have to check
            // that the interface configuration is valid and that the interface
            // is not a loopback interface. In both cases, we want to report
            // that the socket will not be opened.
            // Relax the check when the loopback interface was explicitly
            // allowed
            if (iface->flag_loopback_ && !allow_loopback_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "must not open socket on the loopback"
                               " interface " << iface->getName());
                continue;

            } else if (!iface->flag_up_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " is down");
                continue;
            } else if (!iface->flag_running_) {
                IFACEMGR_ERROR(SocketConfigError, error_handler,
                               "the interface " << iface->getName()
                               << " is not running");
                continue;
            }

        }

        // Open unicast sockets if there are any unicast addresses defined
        for (Iface::Address addr : iface->getUnicasts()) {

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

        for (Iface::Address addr : iface->getAddresses()) {

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

    // If we have open sockets, start the receiver.
    if (count > 0) {
        // starts the receiver thread (if queueing is enabled).
        startDHCPReceiver(AF_INET6);
    }
    return (count > 0);
}

void
IfaceMgr::startDHCPReceiver(const uint16_t family) {
    if (isDHCPReceiverRunning()) {
        isc_throw(InvalidOperation, "a receiver thread already exists");
    }

    switch (family) {
    case AF_INET:
        // If the queue doesn't exist, packet queing has been configured
        // as disabled. If there is no queue, we do not create a receiver.
        if(!getPacketQueue4()) {
            return;
        }

        dhcp_receiver_.reset(new WatchedThread());
        dhcp_receiver_->start(std::bind(&IfaceMgr::receiveDHCP4Packets, this));
        break;
    case AF_INET6:
        // If the queue doesn't exist, packet queing has been configured
        // as disabled. If there is no queue, we do not create a receiver.
        if(!getPacketQueue6()) {
            return;
        }

        dhcp_receiver_.reset(new WatchedThread());
        dhcp_receiver_->start(std::bind(&IfaceMgr::receiveDHCP6Packets, this));
        break;
    default:
        isc_throw (BadValue, "startDHCPReceiver: invalid family: " << family);
        break;
    }
}

void
IfaceMgr::addInterface(const IfacePtr& iface) {
    for (const IfacePtr& existing : ifaces_) {
        if ((existing->getName() == iface->getName()) ||
            (existing->getIndex() == iface->getIndex())) {
            isc_throw(Unexpected, "Can't add " << iface->getFullName() <<
                      " when " << existing->getFullName() <<
                      " already exists.");
        }
    }
    ifaces_.push_back(iface);
}

void
IfaceMgr::printIfaces(std::ostream& out /*= std::cout*/) {
    for (IfacePtr iface : ifaces_) {
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

        for (Iface::Address addr : addrs) {
            out << "  " << addr.get().toText();
        }
        out << endl;
    }
}

IfacePtr
IfaceCollection::getIface(uint32_t ifindex) {
    return (getIfaceInternal(ifindex, MultiThreadingMgr::instance().getMode()));
}


IfacePtr
IfaceCollection::getIface(const std::string& ifname) {
    return (getIfaceInternal(ifname, MultiThreadingMgr::instance().getMode()));
}

IfacePtr
IfaceCollection::getIfaceInternal(uint32_t ifindex, bool need_lock) {
    if (need_lock) {
        lock_guard<mutex> lock(mutex_);
        if (cache_ && (cache_->getIndex() == ifindex)) {
            return (cache_);
        }
    } else {
        if (cache_ && (cache_->getIndex() == ifindex)) {
            return (cache_);
        }
    }
    const auto& idx = ifaces_container_.get<1>();
    auto it = idx.find(ifindex);
    if (it == idx.end()) {
        return (IfacePtr()); // not found
    }
    if (need_lock) {
        lock_guard<mutex> lock(mutex_);
        cache_ = *it;
        return (cache_);
    } else {
        lock_guard<mutex> lock(mutex_);
        cache_ = *it;
        return (cache_);
    }
}

IfacePtr
IfaceCollection::getIfaceInternal(const std::string& ifname, bool need_lock) {
    if (need_lock) {
        lock_guard<mutex> lock(mutex_);
        if (cache_ && (cache_->getName() == ifname)) {
            return (cache_);
        }
    } else {
        if (cache_ && (cache_->getName() == ifname)) {
            return (cache_);
        }
    }
    const auto& idx = ifaces_container_.get<2>();
    auto it = idx.find(ifname);
    if (it == idx.end()) {
        return (IfacePtr()); // not found
    }
    if (need_lock) {
        lock_guard<mutex> lock(mutex_);
        cache_ = *it;
        return (cache_);
    } else {
        lock_guard<mutex> lock(mutex_);
        cache_ = *it;
        return (cache_);
    }
}

IfacePtr
IfaceMgr::getIface(int ifindex) {
    if ((ifindex < 0) || (ifindex > std::numeric_limits<int32_t>::max())) {
        return (IfacePtr()); // out of range
    }
    return (ifaces_.getIface(ifindex));
}

IfacePtr
IfaceMgr::getIface(const std::string& ifname) {
    if (ifname.empty()) {
        return (IfacePtr()); // empty
    }
    return (ifaces_.getIface(ifname));
}

IfacePtr
IfaceMgr::getIface(const PktPtr& pkt) {
    if (pkt->indexSet()) {
        return (getIface(pkt->getIndex()));
    } else {
        return (getIface(pkt->getIface()));
    }
}

void
IfaceMgr::clearIfaces() {
    ifaces_.clear();
}

void
IfaceMgr::clearBoundAddresses() {
    bound_address_.clear();
}

void
IfaceMgr::collectBoundAddresses() {
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo sock : iface->getSockets()) {
            const IOAddress& addr = sock.addr_;
            if (!addr.isV4()) {
                continue;
            }
            if (bound_address_.count(addr.toUint32()) == 0) {
                bound_address_.insert(addr);
            }
        }
    }
}

void
IfaceMgr::clearUnicasts() {
    for (IfacePtr iface : ifaces_) {
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
    for (IfacePtr iface : ifaces_) {
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
    for (IfacePtr iface : ifaces_) {
        for (Iface::Address a : iface->getAddresses()) {

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
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket sock(io_service);

    boost::system::error_code err_code;
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

        sock.open(boost::asio::ip::udp::v4(), err_code);
        if (err_code) {
            const char* errstr = strerror(errno);
            isc_throw(Unexpected, "failed to open UDPv4 socket, reason:"
                      << errstr);
        }
        sock.set_option(boost::asio::socket_base::broadcast(true), err_code);
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
    boost::asio::ip::udp::socket::endpoint_type local_endpoint =
        sock.local_endpoint();
    boost::asio::ip::address local_address(local_endpoint.address());

    // Close the socket.
    sock.close();

    // Return address of local endpoint.
    return IOAddress(local_address);
}

int
IfaceMgr::openSocket4(Iface& iface, const IOAddress& addr,
                          const uint16_t port, const bool receive_bcast,
                          const bool send_bcast) {

    // Assuming that packet filter is not null, because its modifier checks it.
    SocketInfo info = packet_filter_->openSocket(iface, addr, port,
                                                 receive_bcast, send_bcast);
    iface.addSocket(info);

    return (info.sockfd_);
}

bool
IfaceMgr::send(const Pkt6Ptr& pkt) {
    IfacePtr iface = getIface(pkt);
    if (!iface) {
        isc_throw(BadValue, "Unable to send DHCPv6 message. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    // Assuming that packet filter is not null, because its modifier checks it.
    // The packet filter returns an int but in fact it either returns 0 or throws.
    return (packet_filter6_->send(*iface, getSocket(pkt), pkt) == 0);
}

bool
IfaceMgr::send(const Pkt4Ptr& pkt) {
    IfacePtr iface = getIface(pkt);
    if (!iface) {
        isc_throw(BadValue, "Unable to send DHCPv4 message. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    // Assuming that packet filter is not null, because its modifier checks it.
    // The packet filter returns an int but in fact it either returns 0 or throws.
    return (packet_filter_->send(*iface, getSocket(pkt).sockfd_, pkt) == 0);
}

Pkt4Ptr IfaceMgr::receive4(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    if (isDHCPReceiverRunning()) {
        return (receive4Indirect(timeout_sec, timeout_usec));
    }

    return (receive4Direct(timeout_sec, timeout_usec));
}

Pkt4Ptr IfaceMgr::receive4Indirect(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }

    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    // if there are any callbacks for external sockets registered...
    {
        std::lock_guard<std::mutex> lock(callbacks_mutex_);
        if (!callbacks_.empty()) {
            for (SocketCallbackInfo s : callbacks_) {
                // Add this socket to listening set
                addFDtoSet(s.socket_, maxfd, &sockets);
            }
        }
    }

    // Add Receiver ready watch socket
    addFDtoSet(dhcp_receiver_->getWatchFd(WatchedThread::READY), maxfd, &sockets);

    // Add Receiver error watch socket
    addFDtoSet(dhcp_receiver_->getWatchFd(WatchedThread::ERROR), maxfd, &sockets);

    // Set timeout for our next select() call.  If there are
    // no DHCP packets to read, then we'll wait for a finite
    // amount of time for an IO event.  Otherwise, we'll
    // poll (timeout = 0 secs).  We need to poll, even if
    // DHCP packets are waiting so we don't starve external
    // sockets under heavy DHCP load.
    struct timeval select_timeout;
    if (getPacketQueue4()->empty()) {
        select_timeout.tv_sec = timeout_sec;
        select_timeout.tv_usec = timeout_usec;
    } else {
        select_timeout.tv_sec = 0;
        select_timeout.tv_usec = 0;
    }

    // zero out the errno to be safe
    errno = 0;

    int result = select(maxfd + 1, &sockets, 0, 0, &select_timeout);

    if ((result == 0) && getPacketQueue4()->empty()) {
        // nothing received and timeout has been reached
        return (Pkt4Ptr());
    } else if (result < 0) {
        // In most cases we would like to know whether select() returned
        // an error because of a signal being received  or for some other
        // reason. This is because DHCP servers use signals to trigger
        // certain actions, like reconfiguration or graceful shutdown.
        // By catching a dedicated exception the caller will know if the
        // error returned by the function is due to the reception of the
        // signal or for some other reason.
        if (errno == EINTR) {
            isc_throw(SignalInterruptOnSelect, strerror(errno));
        } else if (errno == EBADF) {
            int cnt = purgeBadSockets();
            isc_throw(SocketReadError,
                      "SELECT interrupted by one invalid sockets, purged "
                       << cnt << " socket descriptors");
        } else {
            isc_throw(SocketReadError, strerror(errno));
        }
    }

    // We only check external sockets if select detected an event.
    if (result > 0) {
        // Check for receiver thread read errors.
        if (dhcp_receiver_->isReady(WatchedThread::ERROR)) {
            string msg = dhcp_receiver_->getLastError();
            dhcp_receiver_->clearReady(WatchedThread::ERROR);
            isc_throw(SocketReadError, msg);
        }

        // Let's find out which external socket has the data
        SocketCallbackInfo ex_sock;
        bool found = false;
        {
            std::lock_guard<std::mutex> lock(callbacks_mutex_);
            for (SocketCallbackInfo s : callbacks_) {
                if (!FD_ISSET(s.socket_, &sockets)) {
                    continue;
                }
                found = true;

                // something received over external socket
                if (s.callback_) {
                    // Note the external socket to call its callback without
                    // the lock taken so it can be deleted.
                    ex_sock = s;
                    break;
                }
            }
        }

        if (ex_sock.callback_) {
            // Calling the external socket's callback provides its service
            // layer access without integrating any specific features
            // in IfaceMgr
            ex_sock.callback_(ex_sock.socket_);
        }
        if (found) {
            return (Pkt4Ptr());
        }
    }

    // If we're here it should only be because there are DHCP packets waiting.
    Pkt4Ptr pkt = getPacketQueue4()->dequeuePacket();
    if (!pkt) {
        dhcp_receiver_->clearReady(WatchedThread::READY);
    }

    return (pkt);
}

Pkt4Ptr IfaceMgr::receive4Direct(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    boost::scoped_ptr<SocketInfo> candidate;
    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    /// @todo: marginal performance optimization. We could create the set once
    /// and then use its copy for select(). Please note that select() modifies
    /// provided set to indicated which sockets have something to read.
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo s : iface->getSockets()) {
            // Only deal with IPv4 addresses.
            if (s.addr_.isV4()) {
                // Add this socket to listening set
                addFDtoSet(s.sockfd_, maxfd, &sockets);
            }
        }
    }

    // if there are any callbacks for external sockets registered...
    {
        std::lock_guard<std::mutex> lock(callbacks_mutex_);
        if (!callbacks_.empty()) {
            for (SocketCallbackInfo s : callbacks_) {
                // Add this socket to listening set
                addFDtoSet(s.socket_, maxfd, &sockets);
            }
        }
    }

    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    // zero out the errno to be safe
    errno = 0;

    int result = select(maxfd + 1, &sockets, 0, 0, &select_timeout);

    if (result == 0) {
        // nothing received and timeout has been reached
        return (Pkt4Ptr()); // null

    } else if (result < 0) {
        // In most cases we would like to know whether select() returned
        // an error because of a signal being received  or for some other
        // reason. This is because DHCP servers use signals to trigger
        // certain actions, like reconfiguration or graceful shutdown.
        // By catching a dedicated exception the caller will know if the
        // error returned by the function is due to the reception of the
        // signal or for some other reason.
        if (errno == EINTR) {
            isc_throw(SignalInterruptOnSelect, strerror(errno));
        } else if (errno == EBADF) {
            int cnt = purgeBadSockets();
            isc_throw(SocketReadError,
                      "SELECT interrupted by one invalid sockets, purged "
                       << cnt << " socket descriptors");
        } else {
            isc_throw(SocketReadError, strerror(errno));
        }
    }

    // Let's find out which socket has the data
    SocketCallbackInfo ex_sock;
    bool found = false;
    {
        std::lock_guard<std::mutex> lock(callbacks_mutex_);
        for (SocketCallbackInfo s : callbacks_) {
            if (!FD_ISSET(s.socket_, &sockets)) {
                continue;
            }
            found = true;

            // something received over external socket
            if (s.callback_) {
                // Note the external socket to call its callback without
                // the lock taken so it can be deleted.
                ex_sock = s;
                break;
            }
        }
    }

    if (ex_sock.callback_) {
        // Calling the external socket's callback provides its service
        // layer access without integrating any specific features
        // in IfaceMgr
        ex_sock.callback_(ex_sock.socket_);
    }
    if (found) {
        return (Pkt4Ptr());
    }

    // Let's find out which interface/socket has the data
    IfacePtr recv_if;
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo s : iface->getSockets()) {
            if (FD_ISSET(s.sockfd_, &sockets)) {
                candidate.reset(new SocketInfo(s));
                break;
            }
        }
        if (candidate) {
            recv_if = iface;
            break;
        }
    }

    if (!candidate || !recv_if) {
        isc_throw(SocketReadError, "received data over unknown socket");
    }

    // Now we have a socket, let's get some data from it!
    // Assuming that packet filter is not null, because its modifier checks it.
    return (packet_filter_->receive(*recv_if, *candidate));
}

Pkt6Ptr
IfaceMgr::receive6(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    if (isDHCPReceiverRunning()) {
        return (receive6Indirect(timeout_sec, timeout_usec));
    }

    return (receive6Direct(timeout_sec, timeout_usec));
}

void
IfaceMgr::addFDtoSet(int fd, int& maxfd, fd_set* sockets) {
    if (!sockets) {
        isc_throw(BadValue, "addFDtoSet: sockets can't be null");
    }

    FD_SET(fd, sockets);
    if (maxfd < fd) {
        maxfd = fd;
    }
}

Pkt6Ptr
IfaceMgr::receive6Direct(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */ ) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }

    boost::scoped_ptr<SocketInfo> candidate;
    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    /// @todo: marginal performance optimization. We could create the set once
    /// and then use its copy for select(). Please note that select() modifies
    /// provided set to indicated which sockets have something to read.
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo s : iface->getSockets()) {
            // Only deal with IPv6 addresses.
            if (s.addr_.isV6()) {
                // Add this socket to listening set
                addFDtoSet(s.sockfd_, maxfd, &sockets);
            }
        }
    }

    // if there are any callbacks for external sockets registered...
    {
        std::lock_guard<std::mutex> lock(callbacks_mutex_);
        if (!callbacks_.empty()) {
            for (SocketCallbackInfo s : callbacks_) {
                // Add this socket to listening set
                addFDtoSet(s.socket_, maxfd, &sockets);
            }
        }
    }

    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    // zero out the errno to be safe
    errno = 0;

    int result = select(maxfd + 1, &sockets, 0, 0, &select_timeout);

    if (result == 0) {
        // nothing received and timeout has been reached
        return (Pkt6Ptr()); // null

    } else if (result < 0) {
        // In most cases we would like to know whether select() returned
        // an error because of a signal being received  or for some other
        // reason. This is because DHCP servers use signals to trigger
        // certain actions, like reconfiguration or graceful shutdown.
        // By catching a dedicated exception the caller will know if the
        // error returned by the function is due to the reception of the
        // signal or for some other reason.
        if (errno == EINTR) {
            isc_throw(SignalInterruptOnSelect, strerror(errno));
        } else if (errno == EBADF) {
            int cnt = purgeBadSockets();
            isc_throw(SocketReadError,
                      "SELECT interrupted by one invalid sockets, purged "
                       << cnt << " socket descriptors");
        } else {
            isc_throw(SocketReadError, strerror(errno));
        }
    }

    // Let's find out which socket has the data
    SocketCallbackInfo ex_sock;
    bool found = false;
    {
        std::lock_guard<std::mutex> lock(callbacks_mutex_);
        for (SocketCallbackInfo s : callbacks_) {
            if (!FD_ISSET(s.socket_, &sockets)) {
                continue;
            }
            found = true;

            // something received over external socket
            if (s.callback_) {
                // Note the external socket to call its callback without
                // the lock taken so it can be deleted.
                ex_sock = s;
                break;
            }
        }
    }

    if (ex_sock.callback_) {
        // Calling the external socket's callback provides its service
        // layer access without integrating any specific features
        // in IfaceMgr
        ex_sock.callback_(ex_sock.socket_);
    }
    if (found) {
        return (Pkt6Ptr());
    }

    // Let's find out which interface/socket has the data
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo s : iface->getSockets()) {
            if (FD_ISSET(s.sockfd_, &sockets)) {
                candidate.reset(new SocketInfo(s));
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
    // Assuming that packet filter is not null, because its modifier checks it.
    return (packet_filter6_->receive(*candidate));
}

Pkt6Ptr
IfaceMgr::receive6Indirect(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */ ) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }

    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    // if there are any callbacks for external sockets registered...
    {
        std::lock_guard<std::mutex> lock(callbacks_mutex_);
        if (!callbacks_.empty()) {
            for (SocketCallbackInfo s : callbacks_) {
                // Add this socket to listening set
                addFDtoSet(s.socket_, maxfd, &sockets);
            }
        }
    }

    // Add Receiver ready watch socket
    addFDtoSet(dhcp_receiver_->getWatchFd(WatchedThread::READY), maxfd, &sockets);

    // Add Receiver error watch socket
    addFDtoSet(dhcp_receiver_->getWatchFd(WatchedThread::ERROR), maxfd, &sockets);

    // Set timeout for our next select() call.  If there are
    // no DHCP packets to read, then we'll wait for a finite
    // amount of time for an IO event.  Otherwise, we'll
    // poll (timeout = 0 secs).  We need to poll, even if
    // DHCP packets are waiting so we don't starve external
    // sockets under heavy DHCP load.
    struct timeval select_timeout;
    if (getPacketQueue6()->empty()) {
        select_timeout.tv_sec = timeout_sec;
        select_timeout.tv_usec = timeout_usec;
    } else {
        select_timeout.tv_sec = 0;
        select_timeout.tv_usec = 0;
    }

    // zero out the errno to be safe
    errno = 0;

    int result = select(maxfd + 1, &sockets, 0, 0, &select_timeout);

    if ((result == 0) && getPacketQueue6()->empty()) {
        // nothing received and timeout has been reached
        return (Pkt6Ptr());
    } else if (result < 0) {
        // In most cases we would like to know whether select() returned
        // an error because of a signal being received  or for some other
        // reason. This is because DHCP servers use signals to trigger
        // certain actions, like reconfiguration or graceful shutdown.
        // By catching a dedicated exception the caller will know if the
        // error returned by the function is due to the reception of the
        // signal or for some other reason.
        if (errno == EINTR) {
            isc_throw(SignalInterruptOnSelect, strerror(errno));
        } else if (errno == EBADF) {
            int cnt = purgeBadSockets();
            isc_throw(SocketReadError,
                      "SELECT interrupted by one invalid sockets, purged "
                       << cnt << " socket descriptors");
        } else {
            isc_throw(SocketReadError, strerror(errno));
        }
    }

    // We only check external sockets if select detected an event.
    if (result > 0) {
        // Check for receiver thread read errors.
        if (dhcp_receiver_->isReady(WatchedThread::ERROR)) {
            string msg = dhcp_receiver_->getLastError();
            dhcp_receiver_->clearReady(WatchedThread::ERROR);
            isc_throw(SocketReadError, msg);
        }

        // Let's find out which external socket has the data
        SocketCallbackInfo ex_sock;
        bool found = false;
        {
            std::lock_guard<std::mutex> lock(callbacks_mutex_);
            for (SocketCallbackInfo s : callbacks_) {
                if (!FD_ISSET(s.socket_, &sockets)) {
                    continue;
                }
                found = true;

                // something received over external socket
                if (s.callback_) {
                    // Note the external socket to call its callback without
                    // the lock taken so it can be deleted.
                    ex_sock = s;
                    break;
                }
            }
        }

        if (ex_sock.callback_) {
            // Calling the external socket's callback provides its service
            // layer access without integrating any specific features
            // in IfaceMgr
            ex_sock.callback_(ex_sock.socket_);
        }
        if (found) {
            return (Pkt6Ptr());
        }
    }

    // If we're here it should only be because there are DHCP packets waiting.
    Pkt6Ptr pkt = getPacketQueue6()->dequeuePacket();
    if (!pkt) {
        dhcp_receiver_->clearReady(WatchedThread::READY);
    }

    return (pkt);
}

void
IfaceMgr::receiveDHCP4Packets() {
    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    // Add terminate watch socket.
    addFDtoSet(dhcp_receiver_->getWatchFd(WatchedThread::TERMINATE), maxfd, &sockets);

    // Add Interface sockets.
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo s : iface->getSockets()) {
            // Only deal with IPv4 addresses.
            if (s.addr_.isV4()) {
                // Add this socket to listening set.
                addFDtoSet(s.sockfd_, maxfd, &sockets);
            }
        }
    }

    for (;;) {
        // Check the watch socket.
        if (dhcp_receiver_->shouldTerminate()) {
            return;
        }

        fd_set rd_set;
        FD_COPY(&sockets, &rd_set);

        // zero out the errno to be safe.
        errno = 0;

        // Select with null timeouts to wait indefinitely an event
        int result = select(maxfd + 1, &rd_set, 0, 0, 0);

        // Re-check the watch socket.
        if (dhcp_receiver_->shouldTerminate()) {
            return;
        }

        if (result == 0) {
            // nothing received?
            continue;

        } else if (result < 0) {
            // This thread should not get signals?
            if (errno != EINTR) {
                // Signal the error to receive4.
                dhcp_receiver_->setError(strerror(errno));
                // We need to sleep in case of the error condition to
                // prevent the thread from tight looping when result
                // gets negative.
                sleep(1);
            }
            continue;
        }

        // Let's find out which interface/socket has data.
        for (IfacePtr iface : ifaces_) {
            for (SocketInfo s : iface->getSockets()) {
                if (FD_ISSET(s.sockfd_, &sockets)) {
                    receiveDHCP4Packet(*iface, s);
                    // Can take time so check one more time the watch socket.
                    if (dhcp_receiver_->shouldTerminate()) {
                        return;
                    }
                }
            }
        }
    }

}

void
IfaceMgr::receiveDHCP6Packets() {
    fd_set sockets;
    int maxfd = 0;

    FD_ZERO(&sockets);

    // Add terminate watch socket.
    addFDtoSet(dhcp_receiver_->getWatchFd(WatchedThread::TERMINATE), maxfd, &sockets);

    // Add Interface sockets.
    for (IfacePtr iface : ifaces_) {
        for (SocketInfo s : iface->getSockets()) {
            // Only deal with IPv6 addresses.
            if (s.addr_.isV6()) {
                // Add this socket to listening set.
                addFDtoSet(s.sockfd_ , maxfd, &sockets);
            }
        }
    }

    for (;;) {
        // Check the watch socket.
        if (dhcp_receiver_->shouldTerminate()) {
            return;
        }

        fd_set rd_set;
        FD_COPY(&sockets, &rd_set);

        // zero out the errno to be safe.
        errno = 0;

        // Note we wait until something happen.
        int result = select(maxfd + 1, &rd_set, 0, 0, 0);

        // Re-check the watch socket.
        if (dhcp_receiver_->shouldTerminate()) {
            return;
        }

        if (result == 0) {
            // nothing received?
            continue;
        } else if (result < 0) {
            // This thread should not get signals?
            if (errno != EINTR) {
                // Signal the error to receive6.
                dhcp_receiver_->setError(strerror(errno));
                // We need to sleep in case of the error condition to
                // prevent the thread from tight looping when result
                // gets negative.
                sleep(1);
            }
            continue;
        }

        // Let's find out which interface/socket has data.
        for (IfacePtr iface : ifaces_) {
            for (SocketInfo s : iface->getSockets()) {
                if (FD_ISSET(s.sockfd_, &sockets)) {
                    receiveDHCP6Packet(s);
                    // Can take time so check one more time the watch socket.
                    if (dhcp_receiver_->shouldTerminate()) {
                        return;
                    }
                }
            }
        }
    }
}

void
IfaceMgr::receiveDHCP4Packet(Iface& iface, const SocketInfo& socket_info) {
    int len;

    int result = ioctl(socket_info.sockfd_, FIONREAD, &len);
    if (result < 0) {
        // Signal the error to receive4.
        dhcp_receiver_->setError(strerror(errno));
        return;
    }
    if (len == 0) {
        // Nothing to read.
        return;
    }

    Pkt4Ptr pkt;

    try {
        pkt = packet_filter_->receive(iface, socket_info);
    } catch (const std::exception& ex) {
        dhcp_receiver_->setError(strerror(errno));
    } catch (...) {
        dhcp_receiver_->setError("packet filter receive() failed");
    }

    if (pkt) {
        getPacketQueue4()->enqueuePacket(pkt, socket_info);
        dhcp_receiver_->markReady(WatchedThread::READY);
    }
}

void
IfaceMgr::receiveDHCP6Packet(const SocketInfo& socket_info) {
    int len;

    int result = ioctl(socket_info.sockfd_, FIONREAD, &len);
    if (result < 0) {
        // Signal the error to receive6.
        dhcp_receiver_->setError(strerror(errno));
        return;
    }
    if (len == 0) {
        // Nothing to read.
        return;
    }

    Pkt6Ptr pkt;

    try {
        pkt = packet_filter6_->receive(socket_info);
    } catch (const std::exception& ex) {
        dhcp_receiver_->setError(ex.what());
    } catch (...) {
        dhcp_receiver_->setError("packet filter receive() failed");
    }

    if (pkt) {
        getPacketQueue6()->enqueuePacket(pkt, socket_info);
        dhcp_receiver_->markReady(WatchedThread::READY);
    }
}

uint16_t
IfaceMgr::getSocket(const isc::dhcp::Pkt6Ptr& pkt) {
    IfacePtr iface = getIface(pkt);
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

        if (s->addr_ == pkt->getLocalAddr()) {
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
            if ( (pkt->getRemoteAddr().isV6LinkLocal() &&
                s->addr_.isV6LinkLocal()) ||
                 (!pkt->getRemoteAddr().isV6LinkLocal() &&
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
IfaceMgr::getSocket(const isc::dhcp::Pkt4Ptr& pkt) {
    IfacePtr iface = getIface(pkt);
    if (!iface) {
        isc_throw(IfaceNotFound, "Tried to find socket for non-existent interface");
    }

    const Iface::SocketCollection& socket_collection = iface->getSockets();
    // A candidate being an end of the iterator marks that it is a beginning of
    // the socket search and that the candidate needs to be set to the first
    // socket found.
    Iface::SocketCollection::const_iterator candidate = socket_collection.end();
    Iface::SocketCollection::const_iterator s;
    for (s = socket_collection.begin(); s != socket_collection.end(); ++s) {
        if (s->family_ == AF_INET) {
            if (s->addr_ == pkt->getLocalAddr()) {
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

bool
IfaceMgr::configureDHCPPacketQueue(uint16_t family, data::ConstElementPtr queue_control) {
    if (isDHCPReceiverRunning()) {
        isc_throw(InvalidOperation, "Cannot reconfigure queueing"
                                    " while DHCP receiver thread is running");
    }

    bool enable_queue = false;
    if (queue_control) {
        try {
            enable_queue = data::SimpleParser::getBoolean(queue_control, "enable-queue");
        } catch (...) {
            // @todo - for now swallow not found errors.
            // if not present we assume default
        }
    }

    if (enable_queue) {
        // Try to create the queue as configured.
        if (family == AF_INET) {
            packet_queue_mgr4_->createPacketQueue(queue_control);
        } else {
            packet_queue_mgr6_->createPacketQueue(queue_control);
        }
    } else {
        // Destroy the current queue (if one), this inherently disables threading.
        if (family == AF_INET) {
            packet_queue_mgr4_->destroyPacketQueue();
        } else {
            packet_queue_mgr6_->destroyPacketQueue();
        }
    }

    return(enable_queue);
}

} // end of namespace isc::dhcp
} // end of namespace isc
