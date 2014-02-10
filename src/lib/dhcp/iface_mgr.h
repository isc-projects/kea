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

#ifndef IFACE_MGR_H
#define IFACE_MGR_H

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter6.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>

#include <list>

namespace isc {

namespace dhcp {


/// @brief IfaceMgr exception thrown thrown when interface detection fails.
class IfaceDetectError : public Exception {
public:
    IfaceDetectError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when it is not allowed to set new Packet Filter.
class PacketFilterChangeDenied : public Exception {
public:
    PacketFilterChangeDenied(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown thrown when socket opening
/// or configuration failed.
class SocketConfigError : public Exception {
public:
    SocketConfigError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown thrown when error occured during
/// reading data from socket.
class SocketReadError : public Exception {
public:
    SocketReadError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown thrown when error occured during
/// sedning data through socket.
class SocketWriteError : public Exception {
public:
    SocketWriteError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// Holds information about socket.
struct SocketInfo {

    isc::asiolink::IOAddress addr_; /// bound address
    uint16_t port_;   /// socket port
    uint16_t family_; /// IPv4 or IPv6

    /// @brief Socket descriptor (a.k.a. primary socket).
    int sockfd_;

    /// @brief Fallback socket descriptor.
    ///
    /// This socket descriptor holds the handle to the fallback socket.
    /// The fallback socket is created when there is a need for the regular
    /// datagram socket to be bound to an IP address and port, besides
    /// primary socket (sockfd_) which is actually used to receive and process
    /// the DHCP messages. The fallback socket (if exists) is always associated
    /// with the primary socket. In particular, the need for the fallback socket
    /// arises when raw socket is a primary one. When primary socket is open,
    /// it is bound to an interface not the address and port. The implications
    /// include the possibility that the other process (e.g. the other instance
    /// of DHCP server) will bind to the same address and port through which the
    /// raw socket receives the DHCP messages.Another implication is that the
    /// kernel, being unaware of the DHCP server operating through the raw
    /// socket, will respond with the ICMP "Destination port unreachable"
    /// messages when DHCP messages are only received through the raw socket.
    /// In order to workaround the issues mentioned here, the fallback socket
    /// should be opened so as/ the kernel is aware that the certain address
    /// and port is in use.
    ///
    /// The fallback description is supposed to be set to a negative value if
    /// the fallback socket is closed (not open).
    int fallbackfd_;

    /// @brief SocketInfo constructor.
    ///
    /// @param addr An address the socket is bound to.
    /// @param port A port the socket is bound to.
    /// @param sockfd Socket descriptor.
    /// @param fallbackfd A descriptor of the fallback socket.
    SocketInfo(const isc::asiolink::IOAddress& addr, const uint16_t port,
               const int sockfd, const int fallbackfd = -1)
        : addr_(addr), port_(port), family_(addr.getFamily()),
          sockfd_(sockfd), fallbackfd_(fallbackfd) { }

};


/// @brief Represents a single network interface
///
/// Iface structure represents network interface with all useful
/// information, like name, interface index, MAC address and
/// list of assigned addresses
class Iface {
public:

    /// Maximum MAC address length (Infiniband uses 20 bytes)
    static const unsigned int MAX_MAC_LEN = 20;

    /// Type that defines list of addresses
    typedef std::vector<isc::asiolink::IOAddress> AddressCollection;

    /// @brief Type that holds a list of socket information.
    ///
    /// @warning The type of the container used here must guarantee
    /// that the iterators do not invalidate when erase() is called.
    /// This is because, the \ref closeSockets function removes
    /// elements selectively by calling erase on the element to be
    /// removed and further iterates through remaining elements.
    ///
    /// @todo: Add SocketCollectionConstIter type
    typedef std::list<SocketInfo> SocketCollection;

    /// @brief Iface constructor.
    ///
    /// Creates Iface object that represents network interface.
    ///
    /// @param name name of the interface
    /// @param ifindex interface index (unique integer identifier)
    Iface(const std::string& name, int ifindex);

    /// @brief Closes all open sockets on interface.
    void closeSockets();

    /// @brief Closes all IPv4 or IPv6 sockets.
    ///
    /// This function closes sockets of the specific 'type' and closes them.
    /// The 'type' of the socket indicates whether it is used to send IPv4
    /// or IPv6 packets. The allowed values of the parameter are AF_INET and
    /// AF_INET6 for IPv4 and IPv6 packets respectively. It is important
    /// to realize that the actual types of sockets may be different than
    /// AF_INET for IPv4 packets. This is because, historically the IfaceMgr
    /// always used AF_INET sockets for IPv4 traffic. This is no longer the
    /// case when the Direct IPv4 traffic must be supported. In order to support
    /// direct traffic, the IfaceMgr operates on raw sockets, e.g. AF_PACKET
    /// family sockets on Linux.
    ///
    /// @todo Replace the AF_INET and AF_INET6 values with an enum
    /// which will not be confused with the actual socket type.
    ///
    /// @param family type of the sockets to be closed (AF_INET or AF_INET6)
    ///
    /// @throw BadValue if family value is different than AF_INET or AF_INET6.
    void closeSockets(const uint16_t family);

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
    /// @note Implementation of this method is OS-dependent as bits have
    /// different meaning on each OS.
    /// We need to make it 64 bits, because Solaris uses 64, not 32 bits.
    ///
    /// @param flags bitmask value returned by OS in interface detection
    void setFlags(uint64_t flags);

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

    /// @brief Returns IPv4 address assigned to the interface.
    ///
    /// This function looks for an IPv4 address assigned to the interface
    /// and returns it through the argument.
    ///
    /// @param [out] address IPv4 address assigned to the interface.
    ///
    /// @return Boolean value which informs whether IPv4 address has been found
    /// for the interface (if true), or not (false).
    bool getAddress4(isc::asiolink::IOAddress& address) const;

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
    void addSocket(const SocketInfo& sock) {
        sockets_.push_back(sock);
    }

    /// @brief Closes socket.
    ///
    /// Closes socket and removes corresponding SocketInfo structure
    /// from an interface.
    ///
    /// @param sockfd socket descriptor to be closed/removed.
    /// @return true if there was such socket, false otherwise
    bool delSocket(uint16_t sockfd);

    /// @brief Returns collection of all sockets added to interface.
    ///
    /// When new socket is created with @ref IfaceMgr::openSocket
    /// it is added to sockets collection on particular interface.
    /// If socket is opened by other means (e.g. function that does
    /// not use @ref IfaceMgr::openSocket) it will not be available
    /// in this collection. Note that functions like
    /// @ref IfaceMgr::openSocketFromIface use
    /// @ref IfaceMgr::openSocket internally.
    /// The returned reference is only valid during the lifetime of
    /// the IfaceMgr object that returned it.
    ///
    /// @return collection of sockets added to interface
    const SocketCollection& getSockets() const { return sockets_; }

    /// @brief Removes any unicast addresses
    ///
    /// Removes any unicast addresses that the server was configured to
    /// listen on
    void clearUnicasts() {
        unicasts_.clear();
    }

    /// @brief Adds unicast the server should listen on
    ///
    /// @throw BadValue if specified address is already defined on interface
    /// @param addr unicast address to listen on
    void addUnicast(const isc::asiolink::IOAddress& addr);

    /// @brief Returns a container of addresses the server should listen on
    ///
    /// @return address collection (may be empty)
    const AddressCollection& getUnicasts() const {
        return unicasts_;
    }

protected:
    /// Socket used to send data.
    SocketCollection sockets_;

    /// Network interface name.
    std::string name_;

    /// Interface index (a value that uniquely indentifies an interface).
    int ifindex_;

    /// List of assigned addresses.
    AddressCollection addrs_;

    /// List of unicast addresses the server should listen on
    AddressCollection unicasts_;

    /// Link-layer address.
    uint8_t mac_[MAX_MAC_LEN];

    /// Length of link-layer address (usually 6).
    size_t mac_len_;

    /// Hardware type.
    uint16_t hardware_type_;

public:
    /// @todo: Make those fields protected once we start supporting more
    /// than just Linux

    /// Specifies if selected interface is loopback.
    bool flag_loopback_;

    /// Specifies if selected interface is up.
    bool flag_up_;

    /// Flag specifies if selected interface is running
    /// (e.g. cable plugged in, wifi associated).
    bool flag_running_;

    /// Flag specifies if selected interface is multicast capable.
    bool flag_multicast_;

    /// Flag specifies if selected interface is broadcast capable.
    bool flag_broadcast_;

    /// Interface flags (this value is as is returned by OS,
    /// it may mean different things on different OSes).
    /// Solaris based os have unsigned long flags field (64 bits).
    /// It is usually 32 bits, though.
    uint64_t flags_;

    /// Indicates that IPv4 sockets should (true) or should not (false)
    /// be opened on this interface.
    bool inactive4_;

    /// Indicates that IPv6 sockets should (true) or should not (false)
    /// be opened on this interface.
    bool inactive6_;
};

/// @brief This type describes the callback function invoked when error occurs
/// in the IfaceMgr.
///
/// @param errmsg An error message.
typedef
boost::function<void(const std::string& errmsg)> IfaceMgrErrorMsgCallback;

/// @brief Handles network interfaces, transmission and reception.
///
/// IfaceMgr is an interface manager class that detects available network
/// interfaces, configured addresses, link-local addresses, and provides
/// API for using sockets.
///
class IfaceMgr : public boost::noncopyable {
public:
    /// Defines callback used when data is received over external sockets.
    typedef boost::function<void ()> SocketCallback;

    /// Keeps callback information for external sockets.
    struct SocketCallbackInfo {
        /// Socket descriptor of the external socket.
        int socket_;

        /// A callback that will be called when data arrives over socket_.
        SocketCallback callback_;
    };

    /// Defines storage container for callbacks for external sockets
    typedef std::list<SocketCallbackInfo> SocketCallbackInfoContainer;

    /// @brief Packet reception buffer size
    ///
    /// RFC3315 states that server responses may be
    /// fragmented if they are over MTU. There is no
    /// text whether client's packets may be larger
    /// than 1500. For now, we can assume that
    /// we don't support packets larger than 1500.
    static const uint32_t RCVBUFSIZE = 1500;

    // TODO performance improvement: we may change this into
    //      2 maps (ifindex-indexed and name-indexed) and
    //      also hide it (make it public make tests easier for now)

    /// Type that holds a list of interfaces.
    typedef std::list<Iface> IfaceCollection;

    /// IfaceMgr is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of interface manager
    static IfaceMgr& instance();

    /// @brief Check if packet be sent directly to the client having no address.
    ///
    /// Checks if IfaceMgr can send DHCPv4 packet to the client
    /// who hasn't got address assigned. If this is not supported
    /// broadcast address should be used to send response to
    /// the client.
    ///
    /// @return true if direct response is supported.
    bool isDirectResponseSupported() const;

    /// @brief Returns interfac specified interface index
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
    Iface* getIface(const std::string& ifname);

    /// @brief Returns container with all interfaces.
    ///
    /// This reference is only valid as long as IfaceMgr is valid. However,
    /// since IfaceMgr is a singleton and is expected to be destroyed after
    /// main() function completes, you should not worry much about this.
    ///
    /// @return container with all interfaces.
    const IfaceCollection& getIfaces() { return (ifaces_); }

    /// @brief Removes detected interfaces.
    ///
    /// This method removes all detected interfaces. This method should be
    /// used by unit tests to supply a custom set of interfaces. For example:
    /// a unit test may create a pool of fake interfaces and use the custom
    /// @c PktFilter class to mimic socket operation on these interfaces.
    void clearIfaces();

    /// @brief Detects network interfaces.
    ///
    /// This method will eventually detect available interfaces. For now
    /// it offers stub implementation. First interface name and link-local
    /// IPv6 address is read from interfaces.txt file.
    void detectIfaces();

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

    /// @brief Return most suitable socket for transmitting specified IPv4 packet.
    ///
    /// This method takes Pkt4 (see overloaded implementation that takes
    /// Pkt6) and chooses appropriate socket to send it. This method
    /// may throw BadValue if specified packet does not have outbound
    /// interface specified, no such interface exists, or specified
    /// interface does not have any appropriate sockets open.
    ///
    /// @param pkt a packet to be transmitted
    ///
    /// @return A structure describing a socket.
    SocketInfo getSocket(const isc::dhcp::Pkt4& pkt);

    /// Debugging method that prints out all available interfaces.
    ///
    /// @param out specifies stream to print list of interfaces to
    void printIfaces(std::ostream& out = std::cout);

    /// @brief Sends an IPv6 packet.
    ///
    /// Sends an IPv6 packet. All parameters for actual transmission are specified in
    /// Pkt6 structure itself. That includes destination address, src/dst port
    /// and interface over which data will be sent.
    ///
    /// @param pkt packet to be sent
    ///
    /// @throw isc::BadValue if invalid interface specified in the packet.
    /// @throw isc::dhcp::SocketWriteError if sendmsg() failed to send packet.
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
    /// @throw isc::BadValue if invalid interface specified in the packet.
    /// @throw isc::dhcp::SocketWriteError if sendmsg() failed to send packet.
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
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @throw isc::BadValue if timeout_usec is greater than one million
    /// @throw isc::dhcp::SocketReadError if error occured when receiving a packet.
    /// @return Pkt6 object representing received packet (or NULL)
    Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// @brief Tries to receive IPv4 packet over open IPv4 sockets.
    ///
    /// Attempts to receive a single IPv4 packet of any of the open IPv4 sockets.
    /// If reception is successful and all information about its sender
    /// are obtained, Pkt4 object is created and returned.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @throw isc::BadValue if timeout_usec is greater than one million
    /// @throw isc::dhcp::SocketReadError if error occured when receiving a packet.
    /// @return Pkt4 object representing received packet (or NULL)
    Pkt4Ptr receive4(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// Opens UDP/IP socket and binds it to address, interface and port.
    ///
    /// Specific type of socket (UDP/IPv4 or UDP/IPv6) depends on passed addr
    /// family.
    ///
    /// @param ifname name of the interface
    /// @param addr address to be bound.
    /// @param port UDP port.
    /// @param receive_bcast configure IPv4 socket to receive broadcast
    /// messages or IPv6 socket to join multicast group.
    /// @param send_bcast configure IPv4 socket to send broadcast messages.
    /// This parameter is ignored for IPv6 sockets.
    ///
    /// Method will throw if socket creation, socket binding or multicast
    /// join fails.
    ///
    /// @return socket descriptor, if socket creation, binding and multicast
    /// group join were all successful.
    int openSocket(const std::string& ifname,
                   const isc::asiolink::IOAddress& addr,
                   const uint16_t port,
                   const bool receive_bcast = false,
                   const bool send_bcast = false);

    /// @brief Opens UDP/IP socket and binds it to interface specified.
    ///
    /// This method differs from \ref openSocket in that it does not require
    /// the specification of a local address to which socket will be bound.
    /// Instead, the method searches through the addresses on the specified
    /// interface and selects one that matches the address family.
    ///
    /// @note This method does not join the socket to the multicast group.
    ///
    /// @param ifname name of the interface
    /// @param port UDP port
    /// @param family address family (AF_INET or AF_INET6)
    /// @return socket descriptor, if socket creation and binding was
    /// successful.
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
    /// @note This method does not join the socket to the multicast group.
    ///
    /// @param addr address to be bound
    /// @param port UDP port
    /// @return socket descriptor, if socket creation and binding was
    /// successful.
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
    /// @note This method does not join the socket to a multicast group.
    ///
    /// @param remote_addr remote address to connect to
    /// @param port UDP port
    /// @return socket descriptor, if socket creation and binding was
    /// successful.
    /// @throw isc::Unexpected if failed to create and bind socket
    int openSocketFromRemoteAddress(const isc::asiolink::IOAddress& remote_addr,
                                    const uint16_t port);


    /// @brief Opens IPv6 sockets on detected interfaces.
    ///
    /// On the systems with multiple interfaces, it is often desired that the
    /// failure to open a socket on a particular interface doesn't cause a
    /// fatal error and sockets should be opened on remaining interfaces.
    /// However, the warning about the failure for the particular socket should
    /// be communicated to the caller. The libdhcp++ is a common library with
    /// no logger associated with it. Most of the functions in this library
    /// communicate errors via exceptions. In case of openSockets6 function
    /// exception must not be thrown if the function is supposed to continue
    /// opening sockets, despite an error. Therefore, if such a behavior is
    /// desired, the error handler function can be passed as a parameter.
    /// This error handler is called (if present) with an error string.
    /// Typically, error handler will simply log an error using an application
    /// logger, but it can do more sophisticated error handling too.
    ///
    /// @todo It is possible that additional parameters will have to be added
    /// to the error handler, e.g. Iface if it was really supposed to do
    /// some more sophisticated error handling.
    ///
    /// If the error handler is not installed (is NULL), the exception is thrown
    /// for each failure (default behavior).
    ///
    /// @warning This function does not check if there has been any sockets
    /// already open by the @c IfaceMgr. Therefore a caller should call
    /// @c IfaceMgr::closeSockets(AF_INET6) before calling this function.
    /// If there are any sockets open, the function may either throw an
    /// exception or invoke an error handler on attempt to bind the new socket
    /// to the same address and port.
    ///
    /// @param port specifies port number (usually DHCP6_SERVER_PORT)
    /// @param error_handler A pointer to an error handler function which is
    /// called by the openSockets6 when it fails to open a socket. This
    /// parameter can be NULL to indicate that the callback should not be used.
    ///
    /// @throw SocketOpenFailure if tried and failed to open socket.
    /// @return true if any sockets were open
    bool openSockets6(const uint16_t port = DHCP6_SERVER_PORT,
                      IfaceMgrErrorMsgCallback error_handler = NULL);

    /// @brief Opens IPv4 sockets on detected interfaces.
    ///
    /// This function attempts to open sockets on all interfaces which have been
    /// detected by @c IfaceMgr and meet the following conditions:
    /// - interface is not a local loopback,
    /// - interface is running (connected),
    /// - interface is up,
    /// - interface is active, e.g. selected from the configuration to be used
    /// to listen DHCPv4 messages,
    /// - interface has an IPv4 address assigned.
    ///
    /// The type of the socket being open depends on the selected Packet Filter
    /// represented by a class derived from @c isc::dhcp::PktFilter abstract
    /// class.
    ///
    /// It is possible to specify whether sockets should be broadcast capable.
    /// In most of the cases, the sockets should support broadcast traffic, e.g.
    /// DHCPv4 server and relay need to listen to broadcast messages sent by
    /// clients. If the socket has to be open on the particular interface, this
    /// interface must have broadcast flag set. If this condition is not met,
    /// the socket will be created in the unicast-only mode. If there are
    /// multiple broadcast-capable interfaces present, they may be all open
    /// in a broadcast mode only if the OS supports SO_BINDTODEVICE (bind socket
    /// to a device) socket option. If this option is not supported, only the
    /// first broadcast-capable socket will be opened in the broadcast mode.
    /// The error will be reported for sockets being opened on other interfaces.
    /// If the socket is bound to a device (interface), the broadcast traffic
    /// sent to this interface will be received on this interface only.
    /// This allows the DHCPv4 server or relay to detect the interface on which
    /// the broadcast message has been received. This interface is later used
    /// to send a response.
    ///
    /// On the systems with multiple interfaces, it is often desired that the
    /// failure to open a socket on a particular interface doesn't cause a
    /// fatal error and sockets should be opened on remaining interfaces.
    /// However, the warning about the failure for the particular socket should
    /// be communicated to the caller. The libdhcp++ is a common library with
    /// no logger associated with it. Most of the functions in this library
    /// communicate errors via exceptions. In case of openSockets4 function
    /// exception must not be thrown if the function is supposed to continue
    /// opening sockets, despite an error. Therefore, if such a behavior is
    /// desired, the error handler function can be passed as a parameter.
    /// This error handler is called (if present) with an error string.
    /// Typically, error handler will simply log an error using an application
    /// logger, but it can do more sophisticated error handling too.
    ///
    /// @todo It is possible that additional parameters will have to be added
    /// to the error handler, e.g. Iface if it was really supposed to do
    /// some more sophisticated error handling.
    ///
    /// If the error handler is not installed (is NULL), the exception is thrown
    /// for each failure (default behavior).
    ///
    /// @warning This function does not check if there has been any sockets
    /// already open by the @c IfaceMgr. Therefore a caller should call
    /// @c IfaceMgr::closeSockets(AF_INET) before calling this function.
    /// If there are any sockets open, the function may either throw an
    /// exception or invoke an error handler on attempt to bind the new socket
    /// to the same address and port.
    ///
    /// @param port specifies port number (usually DHCP4_SERVER_PORT)
    /// @param use_bcast configure sockets to support broadcast messages.
    /// @param error_handler A pointer to an error handler function which is
    /// called by the openSockets4 when it fails to open a socket. This
    /// parameter can be NULL to indicate that the callback should not be used.
    ///
    /// @throw SocketOpenFailure if tried and failed to open socket and callback
    /// function hasn't been specified.
    /// @return true if any sockets were open
    bool openSockets4(const uint16_t port = DHCP4_SERVER_PORT,
                      const bool use_bcast = true,
                      IfaceMgrErrorMsgCallback error_handler = NULL);

    /// @brief Closes all open sockets.
    /// Is used in destructor, but also from Dhcpv4Srv and Dhcpv6Srv classes.
    void closeSockets();

    /// @brief Closes all IPv4 or IPv6 sockets.
    ///
    /// This function closes sockets of the specific 'type' and closes them.
    /// The 'type' of the socket indicates whether it is used to send IPv4
    /// or IPv6 packets. The allowed values of the parameter are AF_INET and
    /// AF_INET6 for IPv4 and IPv6 packets respectively. It is important
    /// to realize that the actual types of sockets may be different than
    /// AF_INET for IPv4 packets. This is because, historically the IfaceMgr
    /// always used AF_INET sockets for IPv4 traffic. This is no longer the
    /// case when the Direct IPv4 traffic must be supported. In order to support
    /// direct traffic, the IfaceMgr operates on raw sockets, e.g. AF_PACKET
    /// family sockets on Linux.
    ///
    /// @todo Replace the AF_INET and AF_INET6 values with an enum
    /// which will not be confused with the actual socket type.
    ///
    /// @param family type of the sockets to be closed (AF_INET or AF_INET6)
    ///
    /// @throw BadValue if family value is different than AF_INET or AF_INET6.
    void closeSockets(const uint16_t family);

    /// @brief Returns number of detected interfaces.
    ///
    /// @return number of detected interfaces
    uint16_t countIfaces() { return ifaces_.size(); }

    /// @brief Adds external socket and a callback
    ///
    /// Specifies external socket and a callback that will be called
    /// when data will be received over that socket.
    ///
    /// @param socketfd socket descriptor
    /// @param callback callback function
    void addExternalSocket(int socketfd, SocketCallback callback);

    /// @brief Deletes external socket

    void deleteExternalSocket(int socketfd);

    /// @brief Set packet filter object to handle sending and receiving DHCPv4
    /// messages.
    ///
    /// Packet filter objects provide means for the @c IfaceMgr to open sockets
    /// for IPv4 packets reception and sending. This function sets custom packet
    /// filter (represented by a class derived from PktFilter) to be used by
    /// @c IfaceMgr. Note that there must be no IPv4 sockets open when this
    /// function is called. Call closeSockets(AF_INET) to close all hanging IPv4
    /// sockets opened by the current packet filter object.
    ///
    /// @param packet_filter A pointer to the new packet filter object to be
    /// used by @c IfaceMgr.
    ///
    /// @throw InvalidPacketFilter if provided packet filter object is NULL.
    /// @throw PacketFilterChangeDenied if there are open IPv4 sockets.
    void setPacketFilter(const PktFilterPtr& packet_filter);

    /// @brief Set packet filter object to handle sending and receving DHCPv6
    /// messages.
    ///
    /// Packet filter objects provide means for the @c IfaceMgr to open sockets
    /// for IPv6 packets reception and sending. This function sets the new
    /// instance of the packet filter which will be used by @c IfaceMgr to send
    /// and receive DHCPv6 messages, until replaced by another packet filter.
    ///
    /// It is required that DHCPv6 messages are send and received using methods
    /// of the same object that was used to open socket. Therefore, it is
    /// required that all IPv6 sockets are closed prior to calling this
    /// function. Call closeSockets(AF_INET6) to close all hanging IPv6 sockets
    /// opened by the current packet filter object.
    ///
    /// @param packet_filter A pointer to the new packet filter object to be
    /// used by @c IfaceMgr.
    ///
    /// @throw isc::dhcp::InvalidPacketFilter if specified object is NULL.
    /// @throw isc::dhcp::PacketFilterChangeDenied if there are open IPv6
    /// sockets.
    void setPacketFilter(const PktFilter6Ptr& packet_filter);

    /// @brief Set Packet Filter object to handle send/receive packets.
    ///
    /// This function sets Packet Filter object to be used by IfaceMgr,
    /// appropriate for the current OS. Setting the argument to 'true'
    /// indicates that function should set a packet filter class
    /// which supports direct responses to clients having no address
    /// assigned yet. Filters picked by this function will vary, depending
    /// on the OS being used. There is no guarantee that there is an
    /// implementation that supports this feature on a particular OS.
    /// If there isn't, the PktFilterInet object will be set. If the
    /// argument is set to 'false', PktFilterInet object instance will
    /// be set as the Packet Filter regrdaless of the OS type.
    ///
    /// @param direct_response_desired specifies whether the Packet Filter
    /// object being set should support direct traffic to the host
    /// not having address assigned.
    void setMatchingPacketFilter(const bool direct_response_desired = false);

    /// @brief Adds an interface to list of known interfaces.
    ///
    /// @param iface reference to Iface object.
    /// @note This function must be public because it has to be callable
    /// from unit tests.
    void addInterface(const Iface& iface) {
        ifaces_.push_back(iface);
    }

    /// @brief Checks if there is at least one socket of the specified family
    /// open.
    ///
    /// @param family A socket family.
    ///
    /// @return true if there is at least one socket open, false otherwise.
    bool hasOpenSocket(const uint16_t family) const;

    /// @brief Checks if there is a socket open and bound to an address.
    ///
    /// This function checks if one of the sockets opened by the IfaceMgr is
    /// bound to the IP address specified as the method parameter.
    ///
    /// @param addr Address of the socket being searched.
    ///
    /// @return true if there is a socket bound to the specified address.
    bool hasOpenSocket(const isc::asiolink::IOAddress& addr) const;

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
    /// @param receive_bcast configure socket to receive broadcast messages
    /// @param send_bcast configure socket to send broadcast messages.
    ///
    /// @return socket descriptor
    int openSocket4(Iface& iface, const isc::asiolink::IOAddress& addr,
                    const uint16_t port, const bool receive_bcast = false,
                    const bool send_bcast = false);

    /// @brief Opens IPv6 socket.
    ///
    /// Please do not use this method directly. Use openSocket instead.
    ///
    /// This method may throw exception if socket creation fails.
    ///
    /// @param iface reference to interface structure.
    /// @param addr an address the created socket should be bound to
    /// @param port a port that created socket should be bound to
    /// @param join_multicast A boolean parameter which indicates whether
    /// socket should join All_DHCP_Relay_Agents_and_servers multicast
    /// group.
    ///
    /// @return socket descriptor
    int openSocket6(Iface& iface, const isc::asiolink::IOAddress& addr,
                    uint16_t port, const bool join_multicast);

    /// @brief Stub implementation of network interface detection.
    ///
    /// This implementations reads a single line from interfaces.txt file
    /// and pretends to detect such interface. First interface name and
    /// link-local IPv6 address or IPv4 address is read from the
    /// interfaces.txt file.
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

    // We can't use the same socket, as receiving socket
    // is bound to multicast address. And we all know what happens
    // to people who try to use multicast as source address.

    /// Length of the control_buf_ array
    size_t control_buf_len_;

    /// Control-buffer, used in transmission and reception.
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

private:
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
    /// @throw isc::Unexpected if unable to identify local address
    isc::asiolink::IOAddress
    getLocalAddress(const isc::asiolink::IOAddress& remote_addr,
                    const uint16_t port);


    /// @brief Open an IPv6 socket with multicast support.
    ///
    /// This function opens socket(s) to allow reception of the DHCPv6 sent
    /// to multicast address. It opens an IPv6 socket, binds it to link-local
    /// address and joins multicast group (on non-Linux systems) or opens two
    /// IPv6 sockets and binds one of them to link-local address and another
    /// one to multicast address (on Linux systems).
    ///
    /// @note This function is intended to be called internally by the
    /// @c IfaceMgr::openSockets6. It is not intended to be called from any
    /// other function.
    ///
    /// @param iface Interface on which socket should be open.
    /// @param addr Link-local address to bind the socket to.
    /// @param port Port number to bind socket to.
    /// @param error_handler Error handler function to be called when an
    /// error occurs during opening a socket, or NULL if exception should
    /// be thrown upon error.
    bool openMulticastSocket(Iface& iface,
                             const isc::asiolink::IOAddress& addr,
                             const uint16_t port,
                             IfaceMgrErrorMsgCallback error_handler = NULL);

    /// Holds instance of a class derived from PktFilter, used by the
    /// IfaceMgr to open sockets and send/receive packets through these
    /// sockets. It is possible to supply custom object using
    /// setPacketFilter method. Various Packet Filters differ mainly by using
    /// different types of sockets, e.g. SOCK_DGRAM,  SOCK_RAW and different
    /// families, e.g. AF_INET, AF_PACKET etc. Another possible type of
    /// Packet Filter is the one used for unit testing, which doesn't
    /// open sockets but rather mimics their behavior (mock object).
    PktFilterPtr packet_filter_;

    /// Holds instance of a class derived from PktFilter6, used by the
    /// IfaceMgr to manage sockets used to send and receive DHCPv6
    /// messages. It is possible to supply a custom object using
    /// setPacketFilter method.
    PktFilter6Ptr packet_filter6_;

    /// @brief Contains list of callbacks for external sockets
    SocketCallbackInfoContainer callbacks_;
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // IFACE_MGR_H
