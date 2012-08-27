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
#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

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
    typedef std::vector<isc::asiolink::IOAddress> AddressCollection;

    /// defines callback used when commands are received over control session
    typedef void (*SessionCallback) (void);

    /// maximum MAC address length (Infiniband uses 20 bytes)
    static const unsigned int MAX_MAC_LEN = 20;

    /// @brief Packet reception buffer size
    ///
    /// RFC3315 states that server responses may be
    /// fragmented if they are over MTU. There is no
    /// text whether client's packets may be larger
    /// than 1500. For now, we can assume that
    /// we don't support packets larger than 1500.
    static const uint32_t RCVBUFSIZE = 1500;

    /// Holds information about socket.
    struct SocketInfo {
        uint16_t sockfd_; /// socket descriptor
        isc::asiolink::IOAddress addr_; /// bound address
        uint16_t port_;   /// socket port
        uint16_t family_; /// IPv4 or IPv6

        /// @brief SocketInfo constructor.
        ///
        /// @param sockfd socket descriptor
        /// @param addr an address the socket is bound to
        /// @param port a port the socket is bound to
        SocketInfo(uint16_t sockfd, const isc::asiolink::IOAddress& addr,
                   uint16_t port)
        :sockfd_(sockfd), addr_(addr), port_(port), family_(addr.getFamily()) { }
    };

    /// type that holds a list of socket informations
    typedef std::list<SocketInfo> SocketCollection;

    /// @brief represents a single network interface
    ///
    /// Iface structure represents network interface with all useful
    /// information, like name, interface index, MAC address and
    /// list of assigned addresses
    class Iface {
    public:
        /// @brief Iface constructor.
        ///
        /// Creates Iface object that represents network interface.
        ///
        /// @param name name of the interface
        /// @param ifindex interface index (unique integer identifier)
        Iface(const std::string& name, int ifindex);

        /// @brief Returns full interface name as "ifname/ifindex" string.
        ///
        /// @return string with interface name
        std::string getFullName() const;

        /// @brief Returns link-layer address a plain text.
        ///
        /// @return MAC address as a plain text (string)
        std::string getPlainMac() const;

        /// @brief Sets MAC address of the interface.
        ///
        /// @param mac pointer to MAC address buffer
        /// @param macLen length of mac address
        void setMac(const uint8_t* mac, size_t macLen);

        /// @brief Returns MAC length.
        ///
        /// @return length of MAC address
        size_t getMacLen() const { return mac_len_; }

        /// @brief Returns pointer to MAC address.
        ///
        /// Note: Returned pointer is only valid as long as the interface object
        /// that returned it.
        const uint8_t* getMac() const { return mac_; }

        /// @brief Sets flag_*_ fields based on bitmask value returned by OS
        ///
        /// Note: Implementation of this method is OS-dependent as bits have
        /// different meaning on each OS.
        ///
        /// @param flags bitmask value returned by OS in interface detection
        void setFlags(uint32_t flags);

        /// @brief Returns interface index.
        ///
        /// @return interface index
        uint16_t getIndex() const { return ifindex_; }

        /// @brief Returns interface name.
        ///
        /// @return interface name
        std::string getName() const { return name_; };

        /// @brief Sets up hardware type of the interface.
        ///
        /// @param type hardware type
        void setHWType(uint16_t type ) { hardware_type_ = type; }

        /// @brief Returns hardware type of the interface.
        ///
        /// @return hardware type
        uint16_t getHWType() const { return hardware_type_; }

        /// @brief Returns all interfaces available on an interface.
        ///
        /// Care should be taken to not use this collection after Iface object
        /// ceases to exist. That is easy in most cases as Iface objects are
        /// created by IfaceMgr that is a singleton an is expected to be
        /// available at all time. We may revisit this if we ever decide to
        /// implement dynamic interface detection, but such fancy feature would
        /// mostly be useful for clients with wifi/vpn/virtual interfaces.
        ///
        /// @return collection of addresses
        const AddressCollection& getAddresses() const { return addrs_; }

        /// @brief Adds an address to an interface.
        ///
        /// This only adds an address to collection, it does not physically
        /// configure address on actual network interface.
        ///
        /// @param addr address to be added
        void addAddress(const isc::asiolink::IOAddress& addr) {
            addrs_.push_back(addr);
        }

        /// @brief Deletes an address from an interface.
        ///
        /// This only deletes address from collection, it does not physically
        /// remove address configuration from actual network interface.
        ///
        /// @param addr address to be removed.
        ///
        /// @return true if removal was successful (address was in collection),
        ///         false otherwise
        bool delAddress(const isc::asiolink::IOAddress& addr);

        /// @brief Adds socket descriptor to an interface.
        ///
        /// @param sock SocketInfo structure that describes socket.
        void addSocket(const SocketInfo& sock)
            { sockets_.push_back(sock); }

        /// @brief Closes socket.
        ///
        /// Closes socket and removes corresponding SocketInfo structure
        /// from an interface.
        ///
        /// @param sockfd socket descriptor to be closed/removed.
        /// @return true if there was such socket, false otherwise
        bool delSocket(uint16_t sockfd);

        /// socket used to sending data
        /// TODO: this should be protected
        SocketCollection sockets_;

    protected:
        /// network interface name
        std::string name_;

        /// interface index (a value that uniquely indentifies an interface)
        int ifindex_;

        /// list of assigned addresses
        AddressCollection addrs_;

        /// link-layer address
        uint8_t mac_[MAX_MAC_LEN];

        /// length of link-layer address (usually 6)
        size_t mac_len_;

        /// hardware type
        uint16_t hardware_type_;

    public:
        /// @todo: Make those fields protected once we start supporting more
        /// than just Linux

        /// specifies if selected interface is loopback
        bool flag_loopback_;

        /// specifies if selected interface is up
        bool flag_up_;

        /// flag specifies if selected interface is running
        /// (e.g. cable plugged in, wifi associated)
        bool flag_running_;

        /// flag specifies if selected interface is multicast capable
        bool flag_multicast_;

        /// flag specifies if selected interface is broadcast capable
        bool flag_broadcast_;

        /// interface flags (this value is as is returned by OS,
        /// it may mean different things on different OSes)
        uint32_t flags_;
    };

    // TODO performance improvement: we may change this into
    //      2 maps (ifindex-indexed and name-indexed) and
    //      also hide it (make it public make tests easier for now)

    /// type that holds a list of interfaces
    typedef std::list<Iface> IfaceCollection;

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
    Iface* getIface(int ifindex);

    /// @brief Returns interface with specified interface name
    ///
    /// @param ifname name of searched interface
    ///
    /// @return interface with requested name (or NULL if no such
    ///         interface is present)
    ///
    Iface*
    getIface(const std::string& ifname);

    /// @brief Returns container with all interfaces.
    ///
    /// This reference is only valid as long as IfaceMgr is valid. However,
    /// since IfaceMgr is a singleton and is expected to be destroyed after
    /// main() function completes, you should not worry much about this.
    ///
    /// @return container with all interfaces.
    const IfaceCollection& getIfaces() { return ifaces_; }

    /// @brief Return most suitable socket for transmitting specified IPv6 packet.
    ///
    /// This method takes Pkt6 (see overloaded implementation that takes
    /// Pkt4) and chooses appropriate socket to send it. This method
    /// may throw BadValue if specified packet does not have outbound
    /// interface specified, no such interface exists, or specified
    /// interface does not have any appropriate sockets open.
    ///
    /// @param pkt a packet to be transmitted
    ///
    /// @return a socket descriptor
    uint16_t getSocket(const isc::dhcp::Pkt6& pkt);

    /// @brief Return most suitable socket for transmitting specified IPv6 packet.
    ///
    /// This method takes Pkt4 (see overloaded implementation that takes
    /// Pkt6) and chooses appropriate socket to send it. This method
    /// may throw BadValue if specified packet does not have outbound
    /// interface specified, no such interface exists, or specified
    /// interface does not have any appropriate sockets open.
    ///
    /// @param pkt a packet to be transmitted
    ///
    /// @return a socket descriptor
    uint16_t getSocket(const isc::dhcp::Pkt4& pkt);

    /// debugging method that prints out all available interfaces
    ///
    /// @param out specifies stream to print list of interfaces to
    void
    printIfaces(std::ostream& out = std::cout);

    /// @brief Sends an IPv6 packet.
    ///
    /// Sends an IPv6 packet. All parameters for actual transmission are specified in
    /// Pkt6 structure itself. That includes destination address, src/dst port
    /// and interface over which data will be sent.
    ///
    /// @param pkt packet to be sent
    ///
    /// @return true if sending was successful
    bool send(const Pkt6Ptr& pkt);

    /// @brief Sends an IPv4 packet.
    ///
    /// Sends an IPv4 packet. All parameters for actual transmission are specified
    /// in Pkt4 structure itself. That includes destination address, src/dst
    /// port and interface over which data will be sent.
    ///
    /// @param pkt a packet to be sent
    ///
    /// @return true if sending was successful
    bool send(const Pkt4Ptr& pkt);

    /// @brief Tries to receive IPv6 packet over open IPv6 sockets.
    ///
    /// Attempts to receive a single IPv6 packet of any of the open IPv6 sockets.
    /// If reception is successful and all information about its sender
    /// are obtained, Pkt6 object is created and returned.
    ///
    /// TODO Start using select() and add timeout to be able
    /// to not wait infinitely, but rather do something useful
    /// (e.g. remove expired leases)
    ///
    /// @param timeout specifies timeout (in seconds)
    ///
    /// @return Pkt6 object representing received packet (or NULL)
    Pkt6Ptr receive6(uint32_t timeout);

    /// @brief Tries to receive IPv4 packet over open IPv4 sockets.
    ///
    /// Attempts to receive a single IPv4 packet of any of the open IPv4 sockets.
    /// If reception is successful and all information about its sender
    /// are obtained, Pkt4 object is created and returned.
    ///
    /// @param timeout specifies timeout (in seconds)
    ///
    /// @return Pkt4 object representing received packet (or NULL)
    Pkt4Ptr receive4(uint32_t timeout);

    /// Opens UDP/IP socket and binds it to address, interface and port.
    ///
    /// Specific type of socket (UDP/IPv4 or UDP/IPv6) depends on passed addr
    /// family.
    ///
    /// @param ifname name of the interface
    /// @param addr address to be bound.
    /// @param port UDP port.
    ///
    /// Method will throw if socket creation, socket binding or multicast
    /// join fails.
    ///
    /// @return socket descriptor, if socket creation, binding and multicast
    /// group join were all successful.
    int openSocket(const std::string& ifname,
                   const isc::asiolink::IOAddress& addr,
                   const uint16_t port);

    /// @brief Opens UDP/IP socket and binds it to interface specified.
    ///
    /// This method differs from \ref openSocket in that it does not require
    /// the specification of a local address to which socket will be bound.
    /// Instead, the method searches through the addresses on the specified
    /// interface and selects one that matches the address family.
    ///
    /// @param ifname name of the interface
    /// @param port UDP port
    /// @param family address family (AF_INET or AF_INET6)
    /// @return socket descriptor, if socket creation, binding and multicast
    /// group join were all successful.
    /// @throw isc::Unexpected if failed to create and bind socket.
    /// @throw isc::BadValue if there is no address on specified interface
    /// that belongs to given family.
    int openSocketFromIface(const std::string& ifname,
                            const uint16_t port,
                            const uint8_t family);

    /// @brief Opens UDP/IP socket and binds to address specified
    ///
    /// This methods differs from \ref openSocket in that it does not require
    /// the specification of the interface to which the socket will be bound.
    ///
    /// @param addr address to be bound
    /// @param port UDP port
    /// @return socket descriptor, if socket creation, binding and multicast
    /// group join were all successful.
    /// @throw isc::Unexpected if failed to create and bind socket
    /// @throw isc::BadValue if specified address is not available on
    /// any interface
    int openSocketFromAddress(const isc::asiolink::IOAddress& addr,
                              const uint16_t port);

    /// @brief Opens UDP/IP socket to be used to connect to remote address
    ///
    /// This method identifies the local address to be used to connect to the
    /// remote address specified as argument.  Once the local address is
    /// identified, \ref openSocket is called to open a socket and bind it to
    /// the interface, address and port.
    ///
    /// @param remote_addr remote address to connect to
    /// @param port UDP port
    /// @return socket descriptor, if socket creation, binding and multicast
    /// group join were all successful.
    /// @throw isc::Unexpected if failed to create and bind socket
    int openSocketFromRemoteAddress(const isc::asiolink::IOAddress& remote_addr,
                                    const uint16_t port);


    /// Opens IPv6 sockets on detected interfaces.
    ///
    /// Will throw exception if socket creation fails.
    ///
    /// @param port specifies port number (usually DHCP6_SERVER_PORT)
    ///
    /// @return true if any sockets were open
    bool openSockets6(const uint16_t port = DHCP6_SERVER_PORT);

    /// @brief Closes all open sockets.
    /// Is used in destructor, but also from Dhcpv4_srv and Dhcpv6_srv classes.
    void closeSockets();

    /// Opens IPv4 sockets on detected interfaces.
    /// Will throw exception if socket creation fails.
    ///
    /// @param port specifies port number (usually DHCP4_SERVER_PORT)
    ///
    /// @return true if any sockets were open
    bool openSockets4(const uint16_t port = DHCP4_SERVER_PORT);

    /// @brief returns number of detected interfaces
    ///
    /// @return number of detected interfaces
    uint16_t countIfaces() { return ifaces_.size(); }

    /// @brief Sets session socket and a callback
    ///
    /// Specifies session socket and a callback that will be called
    /// when data will be received over that socket.
    ///
    /// @param socketfd socket descriptor
    /// @param callback callback function
    void set_session_socket(int socketfd, SessionCallback callback) {
        session_socket_ = socketfd;
        session_callback_ = callback;
    }

    /// A value of socket descriptor representing "not specified" state.
    static const int INVALID_SOCKET = -1;

    // don't use private, we need derived classes in tests
protected:

    /// @brief Protected constructor.
    ///
    /// Protected constructor. This is a singleton class. We don't want
    /// anyone to create instances of IfaceMgr. Use instance() method instead.
    IfaceMgr();

    virtual ~IfaceMgr();

    /// @brief Opens IPv4 socket.
    ///
    /// Please do not use this method directly. Use openSocket instead.
    ///
    /// This method may throw exception if socket creation fails.
    ///
    /// @param iface reference to interface structure.
    /// @param addr an address the created socket should be bound to
    /// @param port a port that created socket should be bound to
    ///
    /// @return socket descriptor
    int openSocket4(Iface& iface, const isc::asiolink::IOAddress& addr, uint16_t port);

    /// @brief Opens IPv6 socket.
    ///
    /// Please do not use this method directly. Use openSocket instead.
    ///
    /// This method may throw exception if socket creation fails.
    ///
    /// @param iface reference to interface structure.
    /// @param addr an address the created socket should be bound to
    /// @param port a port that created socket should be bound to
    ///
    /// @return socket descriptor
    int openSocket6(Iface& iface, const isc::asiolink::IOAddress& addr, uint16_t port);

    /// @brief Adds an interface to list of known interfaces.
    ///
    /// @param iface reference to Iface object.
    void addInterface(const Iface& iface) {
        ifaces_.push_back(iface);
    }

    /// @brief Detects network interfaces.
    ///
    /// This method will eventually detect available interfaces. For now
    /// it offers stub implementation. First interface name and link-local
    /// IPv6 address is read from intefaces.txt file.
    void
    detectIfaces();

    /// @brief Stub implementation of network interface detection.
    ///
    /// This implementations reads a single line from interfaces.txt file
    /// and pretends to detect such interface. First interface name and
    /// link-local IPv6 address or IPv4 address is read from the
    /// intefaces.txt file.
    void
    stubDetectIfaces();

    // TODO: having 2 maps (ifindex->iface and ifname->iface would)
    //      probably be better for performance reasons

    /// List of available interfaces
    IfaceCollection ifaces_;

    // TODO: Also keep this interface on Iface once interface detection
    // is implemented. We may need it e.g. to close all sockets on
    // specific interface
    //int recvsock_; // TODO: should be fd_set eventually, but we have only
    //int sendsock_; // 2 sockets for now. Will do for until next release

    // we can't use the same socket, as receiving socket
    // is bound to multicast address. And we all know what happens
    // to people who try to use multicast as source address.

    /// length of the control_buf_ array
    size_t control_buf_len_;

    /// control-buffer, used in transmission and reception
    boost::scoped_array<char> control_buf_;

    /// @brief A wrapper for OS-specific operations before sending IPv4 packet
    ///
    /// @param m message header (will be later used for sendmsg() call)
    /// @param control_buf buffer to be used during transmission
    /// @param control_buf_len buffer length
    /// @param pkt packet to be sent
    void os_send4(struct msghdr& m, boost::scoped_array<char>& control_buf,
                  size_t control_buf_len, const Pkt4Ptr& pkt);

    /// @brief OS-specific operations during IPv4 packet reception
    ///
    /// @param m message header (was used during recvmsg() call)
    /// @param pkt packet received (some fields will be set here)
    ///
    /// @return true if successful, false otherwise
    bool os_receive4(struct msghdr& m, Pkt4Ptr& pkt);

    /// socket descriptor of the session socket
    int session_socket_;

    /// a callback that will be called when data arrives over session_socket_
    SessionCallback session_callback_;
private:

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
    joinMulticast(int sock, const std::string& ifname,
                  const std::string& mcast);

    /// @brief Identifies local network address to be used to
    /// connect to remote address.
    ///
    /// This method identifies local network address that can be used
    /// to connect to remote address specified.
    /// It first creates socket and makes attempt to connect
    /// to remote location via this socket. If connection
    /// is established successfully, the local address to which
    /// socket is bound is returned.
    ///
    /// @param remote_addr remote address to connect to
    /// @param port port to be used
    /// @return local address to be used to connect to remote address
    /// @throw isc::Unexpected if unable to indentify local address
    isc::asiolink::IOAddress
    getLocalAddress(const isc::asiolink::IOAddress& remote_addr,
                    const uint16_t port);
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
