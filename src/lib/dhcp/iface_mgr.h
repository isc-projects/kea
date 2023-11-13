// Copyright (C) 2011-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IFACE_MGR_H
#define IFACE_MGR_H

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/packet_queue_mgr4.h>
#include <dhcp/packet_queue_mgr6.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter6.h>
#include <util/optional.h>
#include <util/watch_socket.h>
#include <util/watched_thread.h>

#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>

#include <functional>
#include <list>
#include <vector>
#include <mutex>

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

/// @brief Exception thrown when a call to select is interrupted by a signal.
class SignalInterruptOnSelect : public Exception {
public:
    SignalInterruptOnSelect(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown thrown when socket opening
/// or configuration failed.
class SocketConfigError : public Exception {
public:
    SocketConfigError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown thrown when error occurred during
/// reading data from socket.
class SocketReadError : public Exception {
public:
    SocketReadError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown thrown when error occurred during
/// sending data through socket.
class SocketWriteError : public Exception {
public:
    SocketWriteError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown when there is no suitable interface.
class IfaceNotFound : public Exception {
public:
    IfaceNotFound(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief IfaceMgr exception thrown when there is no suitable socket found.
class SocketNotFound : public Exception {
public:
    SocketNotFound(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Represents a single network interface
///
/// Iface structure represents network interface with all useful
/// information, like name, interface index, MAC address and
/// list of assigned addresses
///
/// This class also holds the pointer to the socket read buffer.
/// Functions reading from the socket may utilize this buffer to store the
/// data being read from the socket. The advantage of using the
/// pre-allocated buffer is that the buffer is allocated only once, rather
/// than on every read. In addition, some OS specific code (e.g. BPF)
/// may require use of fixed-size buffers. The size of such a buffer is
/// returned by the OS kernel when the socket is opened. Hence, it is
/// convenient to allocate the buffer when the socket is being opened and
/// utilize it throughout the lifetime of the socket.
///
/// In order to avoid potentially expensive copies of the @c Iface objects
/// holding pre-allocated buffers and multiple containers, this class is
/// noncopyable.
class Iface : public boost::noncopyable {
public:

    /// Maximum MAC address length (Infiniband uses 20 bytes)
    static const unsigned int MAX_MAC_LEN = 20;

    /// @brief Address type.
    typedef util::Optional<asiolink::IOAddress> Address;

    /// Type that defines list of addresses
    typedef std::list<Address> AddressCollection;

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

    /// @brief Type definition for a list of error messages
    using ErrorBuffer = std::vector<std::string>;

    /// @brief Iface constructor.
    ///
    /// Creates Iface object that represents network interface.
    ///
    /// @param name name of the interface
    /// @param ifindex interface index (unique integer identifier)
    /// @throw BadValue when name is empty.
    Iface(const std::string& name, unsigned int ifindex);

    /// @brief Destructor.
    ~Iface() { }

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
    unsigned int getIndex() const { return ifindex_; }

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

    /// @brief Returns all addresses available on an interface.
    ///
    /// The returned addresses are encapsulated in the @c util::Optional
    /// class to be able to selectively flag some of the addresses as active
    /// (when optional value is specified) or inactive (when optional value
    /// is specified). If the address is marked as active, the
    /// @c IfaceMgr::openSockets4 method will open socket and bind to this
    /// address. Otherwise, it will not bind any socket to this address.
    /// This is useful when an interface has multiple IPv4 addresses assigned.
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

    /// @brief Check if the interface has the specified address assigned.
    ///
    /// @param address Address to be checked.
    /// @return true if address is assigned to the interface, false otherwise.
    bool hasAddress(const isc::asiolink::IOAddress& address) const;

    /// @brief Adds an address to an interface.
    ///
    /// This only adds an address to collection, it does not physically
    /// configure address on actual network interface.
    ///
    /// @param addr address to be added
    void addAddress(const isc::asiolink::IOAddress& addr);

    /// @brief Activates or deactivates address for the interface.
    ///
    /// This method marks a specified address on the interface active or
    /// inactive. If the address is marked inactive, the
    /// @c IfaceMgr::openSockets4 method will NOT open socket for this address.
    ///
    /// @param address An address which should be activated, deactivated.
    /// @param active A boolean flag which indicates that the specified address
    /// should be active (if true) or inactive (if false).
    ///
    /// @throw BadValue if specified address doesn't exist for the interface.
    void setActive(const isc::asiolink::IOAddress& address, const bool active);

    /// @brief Activates or deactivates all addresses for the interface.
    ///
    /// This method marks all addresses on the interface active or inactive.
    /// If the address is marked inactive, the @c IfaceMgr::openSockets4
    /// method will NOT open socket for this address.
    ///
    /// @param active A boolean flag which indicates that the addresses
    /// should be active (if true) or inactive (if false).
    void setActive(const bool active);

    /// @brief Returns a number of activated IPv4 addresses on the interface.
    unsigned int countActive4() const;

    /// @brief Deletes an address from an interface.
    ///
    /// This only deletes address from collection, it does not physically
    /// remove address configuration from actual network interface.
    ///
    /// @param addr address to be removed.
    ///
    /// @return true if removal was successful (address was in collection),
    /// false otherwise
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

    /// @brief Returns the pointer to the buffer used for data reading.
    ///
    /// The returned pointer is only valid during the lifetime of the
    /// object which returns it or until the buffer is resized.
    /// This function is meant to be used with socket API to gather
    /// data from the socket.
    ///
    /// @return Pointer to the first element of the read buffer or
    /// NULL if the buffer is empty.
    uint8_t* getReadBuffer() {
        if (read_buffer_.empty()) {
            return (0);
        }
        return (&read_buffer_[0]);
    }

    /// @brief Returns the current size of the socket read buffer.
    size_t getReadBufferSize() const {
        return (read_buffer_.size());
    }

    /// @brief Reallocates the socket read buffer.
    ///
    /// @param new_size New size of the buffer.
    void resizeReadBuffer(const size_t new_size) {
        read_buffer_.resize(new_size);
    }

    /// @brief Add an error to the list of messages.
    ///
    /// @param message the error message
    void addError(std::string const& message);

    /// @brief Clears all errors.
    void clearErrors();

    /// @brief Get the consistent list of error messages.
    ///
    /// @return the list of messages
    ErrorBuffer const& getErrors() const;

protected:
    /// Socket used to send data.
    SocketCollection sockets_;

    /// Network interface name.
    std::string name_;

    /// Interface index (a value that uniquely identifies an interface).
    unsigned int ifindex_;

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

private:

    /// @brief The buffer holding the data read from the socket.
    ///
    /// See @c Iface manager description for details.
    std::vector<uint8_t> read_buffer_;

    /// @brief List of errors that occurred since the last attempt to open sockets
    ///
    /// This list needs to always have a consistent view of the errors. They should all belong to
    /// the same session of socket opening i.e. the same call to openSockets[46]. This is currently
    /// ensured by openSockets[46] and all the places where these errors are being used i.e. the
    /// status-get handler, being sequential.
    ErrorBuffer errors_;
};

/// @brief Type definition for the pointer to an @c Iface object.
typedef boost::shared_ptr<Iface> IfacePtr;

/// @brief Collection of pointers to network interfaces.
class IfaceCollection {
public:

    /// @brief Multi index container for network interfaces.
    ///
    /// This container allows to search for a network interfaces using
    /// three indexes:
    ///  - sequenced: used to access elements in the order they have
    /// been added to the container.
    ///  - interface index: used to access an interface using its index.
    ///  - interface name: used to access an interface using its name.
    /// Note that indexes and names are unique.
    typedef boost::multi_index_container<
        // Container comprises elements of IfacePtr type.
        IfacePtr,
        // Here we start enumerating various indexes.
        boost::multi_index::indexed_by<
            // Sequenced index allows accessing elements in the same way
            // as elements in std::list. Sequenced is the index #0.
            boost::multi_index::sequenced<>,
            // Start definition of index #1.
            boost::multi_index::hashed_unique<
                // Use the interface index as the key.
                boost::multi_index::const_mem_fun<
                    Iface, unsigned int, &Iface::getIndex
                >
            >,
            // Start definition of index #2.
            boost::multi_index::hashed_unique<
                // Use the interface name as the key.
                boost::multi_index::const_mem_fun<
                    Iface, std::string, &Iface::getName
                >
            >
        >
    > IfaceContainer;

    /// @brief Begin iterator.
    ///
    /// @return The container sequence begin iterator.
    IfaceContainer::const_iterator begin() const {
        return (ifaces_container_.begin());
    }

    /// @brief End iterator.
    ///
    /// @return The container sequence end iterator.
    IfaceContainer::const_iterator end() const {
        return (ifaces_container_.end());
    }

    /// @brief Empty predicate.
    ///
    /// @return If the container is empty true else false.
    bool empty() const {
        return (ifaces_container_.empty());
    }

    /// @brief Return the number of interfaces.
    ///
    /// @return The container size.
    size_t size() const {
        return (ifaces_container_.size());
    }

    /// @brief Clear the collection.
    void clear() {
        cache_.reset();
        ifaces_container_.clear();
    }

    /// @brief Adds an interface to the collection.
    ///
    /// The interface is added at the end of sequence.
    ///
    /// @param iface reference to Iface object.
    void push_back(const IfacePtr& iface) {
        ifaces_container_.push_back(iface);
    }

    /// @brief Lookup by interface index.
    ///
    /// @param ifindex The index of the interface to find.
    /// @return The interface with the index or null.
    IfacePtr getIface(const unsigned int ifindex);

    /// @brief Lookup by interface name.
    ///
    /// @param ifname The name of the interface to find.
    /// @return The interface with the name or null.
    IfacePtr getIface(const std::string& ifname);

private:
    /// @brief Lookup by interface index.
    ///
    /// @param ifindex The index of the interface to find.
    /// @param need_lock True when the cache operation needs to hold the mutex.
    /// @return The interface with the index or null.
    IfacePtr getIfaceInternal(const unsigned int ifindex, const bool need_lock);

    /// @brief Lookup by interface name.
    ///
    /// The mutex must be held when called from a packet processing thread.
    ///
    /// @param ifname The name of the interface to find.
    /// @param need_lock True when the cache operation needs to hold the mutex.
    /// @return The interface with the name or null.
    IfacePtr getIfaceInternal(const std::string& ifname, const bool need_lock);

    /// @brief The mutex for protecting the cache from concurrent
    /// access from packet processing threads.
    std::mutex mutex_;

    /// @brief The last interface returned by a lookup method.
    ///
    /// A lookup method first tries the cache: if it matches the cache is
    /// returned without an expensive lookup in the container. If it does
    /// not match and a value is found in the container the cache is
    /// updated with this value.
    /// The cache should perform well when active interfaces are a small
    /// subset of the whole interface set, or when consecutive packets
    /// come from the same interface.
    IfacePtr cache_;

    /// @brief The container.
    IfaceContainer ifaces_container_;
};

/// @brief Type definition for the unordered set of IPv4 bound addresses.
///
/// In order to make @c hasOpenSocket with an IPv4 address faster bound
/// addresses should be collected after calling @c CfgIface::openSockets.
typedef boost::multi_index_container<
    /// Container comprises elements of asiolink::IOAddress type.
    asiolink::IOAddress,
    // Here we start enumerating the only index.
    boost::multi_index::indexed_by<
        // Start definition of index #0.
        boost::multi_index::hashed_unique<
            // Use the address in its network order integer form as the key.
            boost::multi_index::const_mem_fun<
                asiolink::IOAddress, uint32_t, &asiolink::IOAddress::toUint32
            >
        >
    >
> BoundAddresses;

/// @brief Forward declaration to the @c IfaceMgr.
class IfaceMgr;

/// @brief Type definition for the pointer to the @c IfaceMgr.
typedef boost::shared_ptr<IfaceMgr> IfaceMgrPtr;

/// @brief This type describes the callback function invoked when error occurs
/// in the IfaceMgr.
///
/// @param errmsg An error message.
typedef
std::function<void(const std::string& errmsg)> IfaceMgrErrorMsgCallback;

/// @brief Handles network interfaces, transmission and reception.
///
/// IfaceMgr is an interface manager class that detects available network
/// interfaces, configured addresses, link-local addresses, and provides
/// API for using sockets.
///
class IfaceMgr : public boost::noncopyable {
public:
    /// @brief Defines callback used when data is received over external sockets.
    ///
    /// @param fd socket descriptor of the ready socket
    typedef std::function<void (int fd)> SocketCallback;

    /// @brief Defines callback used when detecting interfaces.
    ///
    /// @param update_only Only add interfaces that do not exist and update
    /// existing interfaces.
    ///
    /// @return true if callback exited with no issue and @ref detectIfaces
    /// should continue with specific system calls, false otherwise.
    typedef std::function<bool (bool)> DetectCallback;

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
    /// RFC 8415 states that server responses may be
    /// fragmented if they are over MTU. There is no
    /// text whether client's packets may be larger
    /// than 1500. For now, we can assume that
    /// we don't support packets larger than 1500.
    static const uint32_t RCVBUFSIZE = 1500;

    /// IfaceMgr is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of interface manager
    static IfaceMgr& instance();

    /// @brief Returns pointer to the sole instance of the interface manager.
    ///
    /// This method returns the pointer to the instance of the interface manager
    /// which can be held in singleton objects that depend on it. This will
    /// eliminate issues with the static deinitialization fiasco between this
    /// object and dependent singleton objects.
    ///
    /// The @c IfaceMgr::instance method should be considered deprecated.
    ///
    /// @return Shared pointer to the @c IfaceMgr instance.
    static const IfaceMgrPtr& instancePtr();

    /// @brief Destructor.
    ///
    /// Closes open sockets.
    virtual ~IfaceMgr();

    /// @brief Sets or clears the test mode for @c IfaceMgr.
    ///
    /// Various unit test may set this flag to true, to indicate that the
    /// @c IfaceMgr is in the test mode. There are places in the code that
    /// modify the behavior depending if the @c IfaceMgr is in the test
    /// mode or not.
    ///
    /// @param test_mode A flag which indicates that the @c IfaceMgr is in the
    /// test mode (if true), or not (if false).
    void setTestMode(const bool test_mode) {
        test_mode_ = test_mode;
    }

    /// @brief Checks if the @c IfaceMgr is in the test mode.
    ///
    /// @return true if the @c IfaceMgr is in the test mode, false otherwise.
    bool isTestMode() const {
        return (test_mode_);
    }

    /// @brief Allows or disallows the loopback interface
    ///
    /// By default the loopback interface is not considered when opening
    /// sockets. This flag provides a way to relax this constraint.
    ///
    void setAllowLoopBack(const bool allow_loopback) {
        allow_loopback_ = allow_loopback;
    }

    /// @brief Check if packet be sent directly to the client having no address.
    ///
    /// Checks if IfaceMgr can send DHCPv4 packet to the client
    /// who hasn't got address assigned. If this is not supported
    /// broadcast address should be used to send response to
    /// the client.
    ///
    /// @return true if direct response is supported.
    bool isDirectResponseSupported() const;

    /// @brief Returns interface specified interface index
    ///
    /// @param ifindex index of searched interface
    ///
    /// @return interface with requested index (or null if no such
    ///         interface is present)
    ///
    IfacePtr getIface(const unsigned int ifindex);

    /// @brief Returns interface with specified interface name
    ///
    /// @param ifname name of searched interface
    ///
    /// @return interface with requested name (or null if no such
    ///         interface is present)
    IfacePtr getIface(const std::string& ifname);

    /// @brief Returns interface with specified packet
    ///
    /// @note When the interface index is set (@c Pkt::indexSet
    ///       returns true) it is searched for, if it is not set
    ///       the name instead is searched for.
    ///
    /// @param pkt packet with interface index and name
    ///
    /// @return interface with packet interface index or name
    ///         (or null if no such interface is present)
    IfacePtr getIface(const PktPtr& pkt);

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

    /// @brief Set a callback to perform operations before executing specific
    /// system calls.
    ///
    /// @param cb The callback used before executing specific system calls.
    void setDetectCallback(const DetectCallback& cb) {
        detect_callback_ = cb;
    }

    /// @brief Check if the specific system calls used to detect interfaces
    /// should be executed.
    ///
    /// @param update_only Only add interfaces that do not exist and update
    /// existing interfaces.
    ///
    /// @return true if the specific system calls should be executed, false
    /// otherwise causing the @ref detectIfaces to return immediately.
    bool checkDetectIfaces(bool update_only);

    /// @brief Detects network interfaces.
    ///
    /// If the @ref detect_callback_ returns true, the specific system calls are
    /// executed, otherwise the @ref detectIfaces will return immediately.
    ///
    /// @param update_only Only add interfaces that do not exist and update
    /// existing interfaces.
    void detectIfaces(bool update_only = false);

    /// @brief Clears unicast addresses on all interfaces.
    void clearUnicasts();

    /// @brief Clears the addresses all sockets are bound to.
    void clearBoundAddresses();

    /// @brief Collect the addresses all sockets are bound to.
    void collectBoundAddresses();

    /// @brief Return most suitable socket for transmitting specified IPv6 packet.
    ///
    /// This method takes Pkt6Ptr (see overloaded implementation that takes
    /// Pkt4Ptr) and chooses appropriate socket to send it. This method
    /// may throw if specified packet does not have outbound interface specified,
    /// no such interface exists, or specified interface does not have any
    /// appropriate sockets open.
    ///
    /// @param pkt a packet to be transmitted
    ///
    /// @return a socket descriptor
    /// @throw SocketNotFound If no suitable socket found.
    /// @throw IfaceNotFound If interface is not set for the packet.
    uint16_t getSocket(const isc::dhcp::Pkt6Ptr& pkt);

    /// @brief Return most suitable socket for transmitting specified IPv4 packet.
    ///
    /// This method uses the local address assigned to the packet and tries
    /// to match it with addresses to which sockets are bound for the particular
    /// interface. If the match is not found, the method returns the first IPv4
    /// socket found for the particular interface. In case, there are no IPv4
    /// sockets assigned to the interface the exception is thrown.
    ///
    /// @param pkt A packet to be transmitted. It must hold a local address and
    /// a valid pointer to the interface.
    ///
    /// @return A structure describing a socket.
    /// @throw SocketNotFound if no suitable socket found.
    SocketInfo getSocket(const isc::dhcp::Pkt4Ptr& pkt);

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

    /// @brief Receive IPv4 packets or data from external sockets
    ///
    /// Wrapper around calls to either @c receive4Direct or @c
    /// receive4Indirect.  The former is called when packet queueing is
    /// disabled, the latter when it is enabled.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @return Pkt4 object representing received packet (or null)
    Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// @brief Receive IPv4 packets or data from external sockets
    ///
    /// Wrapper around calls to either @c receive4Direct or @c
    /// receive4Indirect.  The former is called when packet queueing is
    /// disabled, the latter when it is enabled.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @return Pkt4 object representing received packet (or null)
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
    /// This method opens sockets only on interfaces which have the
    /// @c inactive6_ field set to false (are active). If the interface is active
    /// but it is not running, it is down, or is a loopback interface when
    /// loopback is not allowed, an error is reported.
    ///
    /// If sockets were successfully opened, it calls @ startDHCPReceiver to
    /// start the receiver thread (if packet queueing is enabled).
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
    /// If the error handler is not installed (is null), the exception is thrown
    /// for each failure (default behavior).
    ///
    /// @warning This function does not check if there has been any sockets
    /// already open by the @c IfaceMgr. Therefore a caller should call
    /// @c IfaceMgr::closeSockets() before calling this function.
    /// If there are any sockets open, the function may either throw an
    /// exception or invoke an error handler on attempt to bind the new socket
    /// to the same address and port.
    ///
    /// @param port specifies port number (usually DHCP6_SERVER_PORT)
    /// @param error_handler a pointer to an error handler function which is
    /// called by the openSockets6 when it fails to open a socket. This
    /// parameter can be null to indicate that the callback should not be used.
    /// @param skip_opened skip the addresses that already have the opened port
    ///
    /// @throw SocketOpenFailure if tried and failed to open socket.
    /// @return true if any sockets were open
    bool openSockets6(const uint16_t port = DHCP6_SERVER_PORT,
                      IfaceMgrErrorMsgCallback error_handler = 0,
                      const bool skip_opened = false);

    /// @brief Opens IPv4 sockets on detected interfaces.
    ///
    /// This method opens sockets only on interfaces which have the
    /// @c inactive4_ field set to false (are active). If the interface is active
    /// but it is not running, it is down, or is a loopback interface when
    /// loopback is not allowed, an error is reported.
    ///
    /// The type of the socket being open depends on the selected Packet Filter
    /// represented by a class derived from @c isc::dhcp::PktFilter abstract
    /// class.
    ///
    /// If sockets were successfully opened, it calls @ startDHCPReceiver to
    /// start the receiver thread (if packet queueing is enabled).
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
    /// If the error handler is not installed (is null), the exception is thrown
    /// for each failure (default behavior).
    ///
    /// @warning This function does not check if there has been any sockets
    /// already open by the @c IfaceMgr. Therefore a caller should call
    /// @c IfaceMgr::closeSockets() before calling this function.
    /// If there are any sockets open, the function may either throw an
    /// exception or invoke an error handler on attempt to bind the new socket
    /// to the same address and port.
    ///
    /// @param port specifies port number (usually DHCP4_SERVER_PORT)
    /// @param use_bcast configure sockets to support broadcast messages.
    /// @param error_handler a pointer to an error handler function which is
    /// called by the openSockets4 when it fails to open a socket. This
    /// parameter can be null to indicate that the callback should not be used.
    /// @param skip_opened skip the addresses that already have the opened port
    ///
    /// @throw SocketOpenFailure if tried and failed to open socket and callback
    /// function hasn't been specified.
    /// @return true if any sockets were open
    bool openSockets4(const uint16_t port = DHCP4_SERVER_PORT,
                      const bool use_bcast = true,
                      IfaceMgrErrorMsgCallback error_handler = 0,
                      const bool skip_opened = false);

    /// @brief Closes all open sockets.
    ///
    /// It calls @c stopDHCPReceiver to stop the receiver thread and then
    /// it closes all open interface sockets.
    ///
    /// Is used in destructor, but also from Dhcpv4Srv and Dhcpv6Srv classes.
    void closeSockets();

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
    ///
    /// @param socketfd socket descriptor
    void deleteExternalSocket(int socketfd);

    /// @brief Scans registered socket set and removes any that are invalid.
    ///
    /// Walks the list of registered external sockets and tests each for
    /// validity.  If any are found to be invalid they are removed. This is
    /// primarily a self-defense mechanism against hook libs or other users
    /// of external sockets that may leave a closed socket registered by
    /// mistake.
    ///
    /// @return A count of the sockets purged.
    int purgeBadSockets();

    /// @brief Deletes all external sockets.
    void deleteAllExternalSockets();

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
    /// @param packet_filter a pointer to the new packet filter object to be
    /// used by @c IfaceMgr.
    ///
    /// @throw InvalidPacketFilter if provided packet filter object is null.
    /// @throw PacketFilterChangeDenied if there are open IPv4 sockets.
    void setPacketFilter(const PktFilterPtr& packet_filter);

    /// @brief Set packet filter object to handle sending and receiving DHCPv6
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
    /// @param packet_filter a pointer to the new packet filter object to be
    /// used by @c IfaceMgr.
    ///
    /// @throw isc::dhcp::InvalidPacketFilter if specified object is null.
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
    /// be set as the Packet Filter regardless of the OS type.
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
    /// @throw Unexpected when name or index already exists.
    void addInterface(const IfacePtr& iface);

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
    /// bound to the IP address specified as the method parameter. If the
    /// socket is bound to the port (and address is unspecified), the
    /// method will check if the address passed in the argument is configured
    /// on an interface.
    /// Note: On BSD and Solaris the socket is opened for "::" address instead
    /// of the link-local address or the "ff02::1:2" address. If there are
    /// multiple interfaces joining the multicast group, this function matches
    /// the "::" address bound by any interface, not necessary the one with the
    /// specified link-local address and returns true.
    ///
    /// @param addr Address of the socket being searched.
    ///
    /// @return true if there is a socket bound to the specified address.
    bool hasOpenSocket(const isc::asiolink::IOAddress& addr) const;

    /// @brief Fetches the DHCPv4 packet queue manager
    ///
    /// @return pointer to the packet queue mgr
    PacketQueueMgr4Ptr getPacketQueueMgr4() {
        return (packet_queue_mgr4_);
    }

    /// @brief Fetches the DHCPv4 receiver packet queue.
    ///
    /// Incoming packets are read by the receiver thread and
    /// added to this queue. @c receive4() dequeues and
    /// returns them.
    /// @return pointer to the packet queue
    PacketQueue4Ptr getPacketQueue4() {
        return (packet_queue_mgr4_->getPacketQueue());
    }

    /// @brief Fetches the DHCPv6 packet queue manager
    ///
    /// @return pointer to the packet queue mgr
    PacketQueueMgr6Ptr getPacketQueueMgr6() {
        return (packet_queue_mgr6_);
    }

    /// @brief Fetches the DHCPv6 receiver packet queue.
    ///
    /// Incoming packets are read by the receiver thread and
    /// added to this queue. @c receive6() dequeues and
    /// returns them.
    /// @return pointer to the packet queue
    PacketQueue6Ptr getPacketQueue6() {
        return (packet_queue_mgr6_->getPacketQueue());
    }

    /// @brief Starts DHCP packet receiver.
    ///
    /// Starts the DHCP packet receiver thread for the given.
    /// protocol, AF_NET or AF_INET6, if the packet queue
    /// exists, otherwise it simply returns.
    ///
    /// @param family indicates which receiver to start,
    /// (AF_INET or AF_INET6)
    ///
    /// @throw Unexpected if the thread already exists.
    void startDHCPReceiver(const uint16_t family);

    /// @brief Stops the DHCP packet receiver.
    ///
    /// If the thread exists, it is stopped, deleted, and
    /// the packet queue is flushed.
    void stopDHCPReceiver();

    /// @brief Returns true if there is a receiver exists and its
    /// thread is currently running.
    bool isDHCPReceiverRunning() const {
        return (dhcp_receiver_ != 0 && dhcp_receiver_->isRunning());
    }

    /// @brief Configures DHCP packet queue
    ///
    /// If the given configuration enables packet queueing, then the
    /// appropriate queue is created. Otherwise, the existing queue is
    /// destroyed. If the receiver thread is running when this function
    /// is invoked, it will throw.
    ///
    /// @param family indicates which receiver to start,
    /// (AF_INET or AF_INET6)
    /// @param queue_control configuration containing "dhcp-queue-control"
    /// content
    /// @return true if packet queueing has been enabled, false otherwise
    /// @throw InvalidOperation if the receiver thread is currently running.
    bool configureDHCPPacketQueue(const uint16_t family,
                                  data::ConstElementPtr queue_control);

    /// @brief Convenience method for adding an descriptor to a set
    ///
    /// @param fd descriptor to add
    /// @param[out] maxfd maximum fd value in the set.  If the new fd is
    /// larger than it's current value, it will be updated to new fd value
    /// @param sockets pointer to the set of sockets
    /// @throw BadValue if sockets is null
    static void addFDtoSet(int fd, int& maxfd, fd_set* sockets);

    // don't use private, we need derived classes in tests
protected:

    /// @brief Protected constructor.
    ///
    /// Protected constructor. This is a singleton class. We don't want
    /// anyone to create instances of IfaceMgr. Use instance() method instead.
    IfaceMgr();

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

    /// @brief Receive IPv4 packets directly or data from external sockets.
    ///
    /// Attempts to receive a single DHCPv4 message over any of the open
    /// IPv4 sockets. If reception is successful and all information about
    /// its sender is obtained, an Pkt4 object is created and returned.
    ///
    /// This method also checks if data arrived over registered external socket.
    /// This data may be of a different protocol family than AF_INET.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @throw isc::BadValue if timeout_usec is greater than one million
    /// @throw isc::dhcp::SocketReadError if error occurred when receiving a
    /// packet.
    /// @throw isc::dhcp::SignalInterruptOnSelect when a call to select() is
    /// interrupted by a signal.
    ///
    /// @return Pkt4 object representing received packet (or null)
    Pkt4Ptr receive4Direct(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// @brief Receive IPv4 packets indirectly or data from external sockets.
    ///
    /// Attempts to receive a single DHCPv4 message from the packet queue.
    /// The queue is populated by the receiver thread.  If a packet is waiting
    /// in the queue, a Pkt4 returned.
    ///
    /// This method also checks if data arrived over registered external socket.
    /// This data may be of a different protocol family than AF_INET.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @throw isc::BadValue if timeout_usec is greater than one million
    /// @throw isc::dhcp::SocketReadError if error occurred when receiving a
    /// packet.
    /// @throw isc::dhcp::SignalInterruptOnSelect when a call to select() is
    /// interrupted by a signal.
    ///
    /// @return Pkt4 object representing received packet (or null)
    Pkt4Ptr receive4Indirect(uint32_t timeout_sec, uint32_t timeout_usec = 0);

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

    /// @brief Receive IPv6 packets directly or data from external sockets.
    ///
    /// Attempts to receive a single DHCPv6 message over any of the open
    /// IPv6 sockets. If reception is successful and all information about
    /// its sender is obtained, an Pkt6 object is created and returned.
    ///
    /// This method also checks if data arrived over registered external socket.
    /// This data may be of a different protocol family than AF_INET.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @throw isc::BadValue if timeout_usec is greater than one million
    /// @throw isc::dhcp::SocketReadError if error occurred when receiving a
    /// packet.
    /// @throw isc::dhcp::SignalInterruptOnSelect when a call to select() is
    /// interrupted by a signal.
    ///
    /// @return Pkt6 object representing received packet (or null)
    Pkt6Ptr receive6Direct(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// @brief Receive IPv6 packets indirectly or data from external sockets.
    ///
    /// Attempts to receive a single DHCPv6 message from the packet queue.
    /// The queue is populated by the receiver thread.  If a packet is waiting
    /// in the queue, a Pkt6 returned.
    ///
    /// This method also checks if data arrived over registered external socket.
    /// This data may be of a different protocol family than AF_INET.
    ///
    /// @param timeout_sec specifies integral part of the timeout (in seconds)
    /// @param timeout_usec specifies fractional part of the timeout
    /// (in microseconds)
    ///
    /// @throw isc::BadValue if timeout_usec is greater than one million
    /// @throw isc::dhcp::SocketReadError if error occurred when receiving a
    /// packet.
    /// @throw isc::dhcp::SignalInterruptOnSelect when a call to select() is
    /// interrupted by a signal.
    ///
    /// @return Pkt6 object representing received packet (or null)
    Pkt6Ptr receive6Indirect(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// @brief List of available interfaces
    IfaceCollection ifaces_;

    /// @brief Unordered set of IPv4 bound addresses.
    BoundAddresses bound_address_;

    // TODO: Also keep this interface on Iface once interface detection
    // is implemented. We may need it e.g. to close all sockets on
    // specific interface
    //int recvsock_; // TODO: should be fd_set eventually, but we have only
    //int sendsock_; // 2 sockets for now. Will do for until next release

    // We can't use the same socket, as receiving socket
    // is bound to multicast address. And we all know what happens
    // to people who try to use multicast as source address.

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
    /// This function opens a socket capable of receiving messages sent to
    /// the All_DHCP_Relay_Agents_and_Servers (ff02::1:2) multicast address.
    /// The socket is bound to the in6addr_any address and the IPV6_JOIN_GROUP
    /// option is set to point to the ff02::1:2 multicast address.
    ///
    /// @note This function is intended to be called internally by the
    /// @c IfaceMgr::openSockets6. It is not intended to be called from any
    /// other function.
    ///
    /// @param iface Interface on which socket should be open.
    /// @param addr Link-local address to bind the socket to.
    /// @param port Port number to bind socket to.
    /// @param error_handler Error handler function to be called when an
    /// error occurs during opening a socket, or null if exception should
    /// be thrown upon error.
    bool openMulticastSocket(Iface& iface,
                             const isc::asiolink::IOAddress& addr,
                             const uint16_t port,
                             IfaceMgrErrorMsgCallback error_handler = 0);

    /// @brief DHCPv4 receiver method.
    ///
    /// Loops forever reading DHCPv4 packets from the interface sockets
    /// and adds them to the packet queue.  It monitors the "terminate"
    /// watch socket, and exits if it is marked ready.  This is method
    /// is used as the worker function in the thread created by @c
    /// startDHCP4Receiver().  It currently uses select() to monitor
    /// socket readiness.  If the select errors out (other than EINTR),
    /// it marks the "error" watch socket as ready.
    void receiveDHCP4Packets();

    /// @brief Receives a single DHCPv4 packet from an interface socket
    ///
    /// Called by @c receiveDHPC4Packets when a socket fd is flagged as
    /// ready. It uses the DHCPv4 packet filter to receive a single packet
    /// from the given interface socket, adds it to the packet queue, and
    /// marks the "receive" watch socket ready. If an error occurs during
    /// the read, the "error" watch socket is marked ready.
    ///
    /// @param iface interface
    /// @param socket_info structure holding socket information
    void receiveDHCP4Packet(Iface& iface, const SocketInfo& socket_info);

    /// @brief DHCPv6 receiver method.
    ///
    /// Loops forever reading DHCPv6 packets from the interface sockets
    /// and adds them to the packet queue.  It monitors the "terminate"
    /// watch socket, and exits if it is marked ready.  This is method
    /// is used as the worker function in the thread created by @c
    /// startDHCP6Receiver().  It currently uses select() to monitor
    /// socket readiness.  If the select errors out (other than EINTR),
    /// it marks the "error" watch socket as ready.
    void receiveDHCP6Packets();

    /// @brief Receives a single DHCPv6 packet from an interface socket
    ///
    /// Called by @c receiveDHPC6Packets when a socket fd is flagged as
    /// ready. It uses the DHCPv6 packet filter to receive a single packet
    /// from the given interface socket, adds it to the packet queue, and
    /// marks the "receive" watch socket ready. If an error occurs during
    /// the read, the "error" watch socket is marked ready.
    ///
    /// @param socket_info structure holding socket information
    void receiveDHCP6Packet(const SocketInfo& socket_info);

    /// @brief Deletes external socket with the callbacks_mutex_ taken
    ///
    /// @param socketfd socket descriptor
    void deleteExternalSocketInternal(int socketfd);

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

    /// @brief Mutex to protect callbacks_ against concurrent access
    std::mutex callbacks_mutex_;

    /// @brief Indicates if the IfaceMgr is in the test mode.
    bool test_mode_;

    /// @brief Detect callback used to perform actions before system dependent
    /// function calls.
    ///
    /// If the @ref detect_callback_ returns true, the specific system calls are
    /// executed, otherwise the @ref detectIfaces will return immediately.
    DetectCallback detect_callback_;

    /// @brief Allows to use loopback
    bool allow_loopback_;

    /// @brief Manager for DHCPv4 packet implementations and queues
    PacketQueueMgr4Ptr packet_queue_mgr4_;

    /// @brief Manager for DHCPv6 packet implementations and queues
    PacketQueueMgr6Ptr packet_queue_mgr6_;

    /// @brief DHCP packet receiver.
    isc::util::WatchedThreadPtr dhcp_receiver_;
};

}  // namespace isc::dhcp
}  // namespace isc

#endif // IFACE_MGR_H
