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

#ifndef IFACE_MGR_H
#define IFACE_MGR_H

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/noncopyable.hpp>
#include "asiolink/io_address.h"
#include "dhcp/pkt6.h"

namespace isc {

namespace dhcp {
/// @brief handles network interfaces, transmission and reception
///
/// IfaceMgr is an interface manager class that detects available network
/// interfaces, configured addresses, link-local addresses, and provides
/// API for using sockets.
///
class IfaceMgr : public boost::noncopyable {
public:
    /// type that defines list of addresses
    typedef std::list<isc::asiolink::IOAddress> Addr6Lst;

    /// maximum MAC address length (Infiniband uses 20 bytes)
    static const unsigned int MAX_MAC_LEN = 20;

    /// @brief represents a single network interface
    ///
    /// Iface structure represents network interface with all useful
    /// information, like name, interface index, MAC address and
    /// list of assigned addresses
    struct Iface {
        /// constructor
        Iface(const std::string& name, int ifindex);

        /// returns full interface name in format ifname/ifindex
        std::string getFullName() const;

        /// returns link-layer address a plain text
        std::string getPlainMac() const;

        /// network interface name
        std::string name_;

        /// interface index (a value that uniquely indentifies an interface)
        int ifindex_;

        /// list of assigned addresses
        Addr6Lst addrs_;

        /// link-layer address
        uint8_t mac_[MAX_MAC_LEN];

        /// length of link-layer address (usually 6)
        int mac_len_;

        /// socket used to sending data
        int sendsock_;

        /// socket used for receiving data
        int recvsock_;
    };

    // TODO performance improvement: we may change this into
    //      2 maps (ifindex-indexed and name-indexed) and
    //      also hide it (make it public make tests easier for now)

    /// type that holds a list of interfaces
    typedef std::list<Iface> IfaceLst;

    /// IfaceMgr is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of interface manager
    static IfaceMgr& instance();

    /// @brief Returns interface with specified interface index
    ///
    /// @param ifindex index of searched interface
    ///
    /// @return interface with requested index (or NULL if no such
    ///         interface is present)
    ///
    Iface*
    getIface(int ifindex);

    /// @brief Returns interface with specified interface name
    ///
    /// @param ifname name of searched interface
    ///
    /// @return interface with requested name (or NULL if no such
    ///         interface is present)
    ///
    Iface*
    getIface(const std::string& ifname);

    /// debugging method that prints out all available interfaces
    ///
    /// @param out specifies stream to print list of interfaces to
    void
    printIfaces(std::ostream& out = std::cout);

    /// @brief Sends a packet.
    ///
    /// Sends a packet. All parameters for actual transmission are specified in
    /// Pkt6 structure itself. That includes destination address, src/dst port
    /// and interface over which data will be sent.
    ///
    /// @param pkt packet to be sent
    ///
    /// @return true if sending was successful
    bool
    send(boost::shared_ptr<Pkt6>& pkt);

    /// @brief Tries to receive packet over open sockets.
    ///
    /// Attempts to receive a single packet of any of the open sockets.
    /// If reception is successful and all information about its sender
    /// are obtained, Pkt6 object is created and returned.
    ///
    /// TODO Start using select() and add timeout to be able
    /// to not wait infinitely, but rather do something useful
    /// (e.g. remove expired leases)
    ///
    /// @return Pkt6 object representing received packet (or NULL)
    boost::shared_ptr<Pkt6> receive();

    // don't use private, we need derived classes in tests
protected:

    /// @brief Protected constructor.
    ///
    /// Protected constructor. This is a singleton class. We don't want
    /// anyone to create instances of IfaceMgr. Use instance() method
    IfaceMgr();

    ~IfaceMgr();

    /// @brief Detects network interfaces.
    ///
    /// This method will eventually detect available interfaces. For now
    /// it offers stub implementation. First interface name and link-local
    /// IPv6 address is read from intefaces.txt file.
    void
    detectIfaces();

    ///
    /// Opens UDP/IPv6 socket and binds it to address, interface and port.
    ///
    /// @param ifname name of the interface
    /// @param addr address to be bound.
    /// @param port UDP port.
    ///
    /// @return socket descriptor, if socket creation, binding and multicast
    /// group join were all successful. -1 otherwise.
    int openSocket(const std::string& ifname,
                   const isc::asiolink::IOAddress& addr,
                   int port);

    // TODO: having 2 maps (ifindex->iface and ifname->iface would)
    //      probably be better for performance reasons

    /// List of available interfaces
    IfaceLst ifaces_;

    /// a pointer to a sole instance of this class (a singleton)
    static IfaceMgr * instance_;

    // TODO: Also keep this interface on Iface once interface detection
    // is implemented. We may need it e.g. to close all sockets on
    // specific interface
    int recvsock_; // TODO: should be fd_set eventually, but we have only
    int sendsock_; // 2 sockets for now. Will do for until next release
    // we can't use the same socket, as receiving socket
    // is bound to multicast address. And we all know what happens
    // to people who try to use multicast as source address.

    /// length of the control_buf_ array
    int control_buf_len_;

    /// control-buffer, used in transmission and reception
    boost::scoped_array<char> control_buf_;

private:
    /// Opens sockets on detected interfaces.
    bool
    openSockets();

    /// creates a single instance of this class (a singleton implementation)
    static void
    instanceCreate();

    /// @brief Joins IPv6 multicast group on a socket.
    ///
    /// Socket must be created and bound to an address. Note that this
    /// address is different than the multicast address. For example DHCPv6
    /// server should bind its socket to link-local address (fe80::1234...)
    /// and later join ff02::1:2 multicast group.
    ///
    /// @param sock socket fd (socket must be bound)
    /// @param ifname interface name (for link-scoped multicast groups)
    /// @param mcast multicast address to join (e.g. "ff02::1:2")
    ///
    /// @return true if multicast join was successful
    ///
    bool
    joinMcast(int sock, const std::string& ifname,
              const std::string& mcast);
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
