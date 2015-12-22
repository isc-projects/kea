// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_IFACE_H
#define CFG_IFACE_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <boost/shared_ptr.hpp>
#include <map>
#include <set>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when duplicated interface names specified.
class DuplicateIfaceName : public Exception {
public:
    DuplicateIfaceName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when specified interface name is invalid.
class InvalidIfaceName : public Exception {
public:
    InvalidIfaceName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when specified interface doesn't exist in a system.
class NoSuchIface : public Exception {
public:
    NoSuchIface(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when duplicated address specified.
class DuplicateAddress : public Exception {
public:
    DuplicateAddress(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when specified unicast address is not assigned
/// to the interface specified.
class NoSuchAddress : public Exception {
public:
    NoSuchAddress(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when invalid socket type has been specified
/// for the given family.
class InvalidSocketType : public Exception {
public:
    InvalidSocketType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Represents selection of interfaces for DHCP server.
///
/// This class manages selection of interfaces on which the DHCP server is
/// listening to queries. The interfaces are selected in the server
/// configuration by their names or by the pairs of interface names and
/// addresses, e.g. eth0/2001:db8:1::1 (DHCPv6) or e.g. eth0/192.168.8.1
/// (DHCPv4).
///
/// This class also accepts "wildcard" interface name which, if specified,
/// instructs the server to listen on all available interfaces.
///
/// Once interfaces have been specified the sockets (either IPv4 or IPv6)
/// can be opened by calling @c CfgIface::openSockets function. Kea
/// offers configuration parameters to control the types of sockets to be
/// opened by the DHCPv4 server. In small deployments it is requires that
/// the server can handle messages from the directly connected clients
/// which don't have an address yet. Unicasting the response to such
/// client is possible by the use of raw sockets. In larger deployments
/// it is often the case that whole traffic is received via relays, and
/// in such case the use of UDP sockets is preferred. The type of the
/// sockets to be opened is specified using one of the
/// @c CfgIface::useSocketType method variants. The @c CfgIface::SocketType
/// enumeration specifies the possible values.
///
/// @warning This class makes use of the AF_INET and AF_INET6 family literals,
/// but it doesn't verify that the address family value passed as @c uint16_t
/// parameter is equal to one of them. It is a callers responsibility to
/// guarantee that the address family value is correct.
///
/// The interface name is passed as an argument of the @ref CfgIface::use
/// function which controls the selection of the interface on which the
/// DHCP queries should be received by the server. The interface name
/// passed as the argument of this function may appear in one of the following
/// formats:
/// - interface-name, e.g. eth0
/// - interface-name/address, e.g. eth0/2001:db8:1::1 or eth0/192.168.8.1
///
/// Extraneous spaces surrounding the interface name and/or address
/// are accepted. For example: eth0 / 2001:db8:1::1 will be accepted.
///
/// When only interface name is specified (without an address) it is allowed
/// to use the "wildcard" interface name (*) which indicates that the server
/// should open sockets on all interfaces. When IPv6 is in use, the sockets
/// will be bound to the link local addresses. Wildcard interface names are
/// not allowed when specifying a unicast address. For example:
/// */2001:db8:1::1 is not allowed.
///
/// The DHCPv6 configuration accepts simultaneous use of the "interface-name"
/// and "interface-name/address" tuple for the same interface, e.g.
/// "eth0", "eth0/2001:db8:1::1" specifies that the server should open a
/// socket and bind to link local address as well as open a socket bound to
/// the specified unicast address.
///
/// The DHCPv4 configuration doesn't accept the simulatenous use of the
/// "interface-name" and the "interface-name/address" tuple for the
/// given interface. When the "interface-name" is specified it implies
/// that the sockets will be opened on for all addresses configured on
/// this interface. If the tuple of "interface-name/address" is specified
/// there will be only one socket opened and bound to the specified address.
/// This socket will be configured to listen to the broadcast messages
/// reaching the interface as well as unicast messages sent to the address
/// to which it is bound. It is allowed to select multiple addresses on the
/// particular interface explicitly, e.g. "eth0/192.168.8.1",
/// "eth0/192.168.8.2".
class CfgIface {
public:

    /// @brief Socket type used by the DHCPv4 server.
    enum SocketType  {
        /// Raw socket, used for direct DHCPv4 traffic.
        SOCKET_RAW,
        /// Datagram socket, i.e. IP/UDP socket.
        SOCKET_UDP
    };

    /// @brief Keyword used to enable all interfaces.
    ///
    /// This keyword can be used instead of the interface name to specify
    /// that DHCP server should listen on all interfaces.
    static const char* ALL_IFACES_KEYWORD;

    /// @brief Constructor.
    CfgIface();

    /// @brief Convenience function which closes all open sockets.
    void closeSockets() const;

    /// @brief Compares two @c CfgIface objects for equality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool equals(const CfgIface& other) const;

    /// @brief Tries to open sockets on selected interfaces.
    ///
    /// This function opens sockets bound to link-local address as well as
    /// sockets bound to unicast address. See @c CfgIface::use function
    /// documentation for details how to specify interfaces and unicast
    /// addresses to bind the sockets to.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param port Port number to be used to bind sockets to.
    /// @param use_bcast A boolean flag which indicates if the broadcast
    /// traffic should be received through the socket. This parameter is
    /// ignored for IPv6.
    void openSockets(const uint16_t family, const uint16_t port,
                     const bool use_bcast = true) const;

    /// @brief Puts the interface configuration into default state.
    ///
    /// This function removes interface names from the set.
    void reset();

    /// @brief Select interface to be used to receive DHCP traffic.
    ///
    /// @ref CfgIface for a detail explaination of the interface name argument.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param iface_name Explicit interface name, a wildcard name (*) of
    /// the interface(s) or the pair of iterface/unicast-address to be used
    /// to receive DHCP traffic.
    ///
    /// @throw InvalidIfaceName If the interface name is incorrect, e.g. empty.
    /// @throw NoSuchIface If the specified interface is not present.
    /// @throw NoSuchAddress If the specified unicast address is not assigned
    /// to the interface.
    /// @throw DuplicateIfaceName If the interface is already selected, i.e.
    /// @throw IOError when specified unicast address is invalid.
    /// @c CfgIface::use has been already called for this interface.
    void use(const uint16_t family, const std::string& iface_name);

    /// @brief Sets the specified socket type to be used by the server.
    ///
    /// Supported socket types for DHCPv4 are:
    /// - @c SOCKET_RAW
    /// - @c SOCKET_UDP
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param socket_type Socket type.
    ///
    /// @throw InvalidSocketType if the unsupported socket type has been
    /// specified for the address family. Currently, the socket type
    /// can only be selected for the AF_INET family.
    void useSocketType(const uint16_t family, const SocketType& socket_type);

    /// @brief Sets the specified socket type specified in textual format.
    ///
    /// The following names of the socket types are currently supported, and
    /// can be passed in the @c socket_type parameter:
    /// - raw - for raw sockets,
    /// - udp - for the IP/UDP datagram sockets,
    ///
    /// @param family Address family (AF_INET or AF_INET6)
    /// @param socket_type_name Socket type in the textual format.
    ///
    /// @throw InvalidSocketType if the unsupported socket type has been
    /// specified for the address family. Currently, the socket type
    /// can only be selected for the AF_INET family.
    void useSocketType(const uint16_t family,
                       const std::string& socket_type_name);

    /// @brief Returns the socket type in the textual format.
    std::string socketTypeToText() const;

    /// @brief Converts the socket type in the textual format to the type
    /// represented by the @c SocketType.
    ///
    /// @throw InvalidSocketType if the specified value of the @c socket_type_name
    /// is invalid.
    SocketType textToSocketType(const std::string& socket_type_name) const;

    /// @brief Equality operator.
    ///
    /// @param other Object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool operator==(const CfgIface& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other Object to be compared with this object.
    ///
    /// @return true if objects are not equal, false otherwise.
    bool operator!=(const CfgIface& other) const {
        return (!equals(other));
    }

private:

    /// @brief Checks if multiple IPv4 addresses has been activated on any
    /// interface.
    ///
    /// This method is useful to check if the current configuration uses
    /// multiple IPv4 addresses on any interface. This is important when
    /// using raw sockets to recieve messages from the clients because
    /// each packet may be received multiple times when it is sent from
    /// a directly connected client. If this is the case, a warning must
    /// be logged.
    ///
    /// @return true if multiple addresses are activated on any interface,
    /// false otherwise.
    bool multipleAddressesPerInterfaceActive() const;

    /// @brief Selects or deselects interfaces.
    ///
    /// This function selects all interfaces to receive DHCP traffic or
    /// deselects all interfaces so as none of them receives a DHCP traffic.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param inactive A boolean value which indicates if all interfaces
    /// (except loopback) should be selected or deselected.
    /// @param loopback_inactive A boolean value which indicates if loopback
    /// interface should be selected or deselected.
    /// should be deselected/inactive (true) or selected/active (false).
    void setState(const uint16_t family, const bool inactive,
                  const bool loopback_inactive) const;

    /// @brief Selects or deselects addresses on the interface.
    ///
    /// This function selects all address on the interface to receive DHCP
    /// traffic or deselects all addresses so as none of them receives the
    /// DHCP traffic.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param active A boolean value which indicates if all addresses should
    /// be active (if true), or inactive (if false).
    /// @param iface An interface on which addresses are selected/deselected.
    void setIfaceAddrsState(const uint16_t family, const bool active,
                            Iface& iface) const;

    /// @brief Error handler for executed when opening a socket fail.
    ///
    /// A pointer to this function is passed to the @c IfaceMgr::openSockets4
    /// or @c IfaceMgr::openSockets6. These functions call this handler when
    /// they fail to open a socket. The handler logs an error passed in the
    /// parameter.
    ///
    /// @param errmsg Error message being logged by the function.
    static void socketOpenErrorHandler(const std::string& errmsg);

    /// @brief Represents a set of interface names.
    typedef std::set<std::string> IfaceSet;

    /// @brief A set of interface names specified by the user.
    IfaceSet iface_set_;

    /// @brief A map of interfaces and addresses to which the server
    /// should bind sockets.
    typedef std::multimap<std::string, asiolink::IOAddress> ExplicitAddressMap;

    /// @brief A map which holds the pairs of interface names and addresses
    /// for which the sockets should be opened.
    ExplicitAddressMap address_map_;

    /// @brief A booolean value which indicates that the wildcard interface name
    /// has been specified (*).
    bool wildcard_used_;

    /// @brief A type of the sockets used by the DHCP server.
    SocketType socket_type_;
};

/// @brief A pointer to the @c CfgIface .
typedef boost::shared_ptr<CfgIface> CfgIfacePtr;

/// @brief A pointer to the const @c CfgIface.
typedef boost::shared_ptr<const CfgIface> ConstCfgIfacePtr;

}
}

#endif // CFG_IFACE_H
