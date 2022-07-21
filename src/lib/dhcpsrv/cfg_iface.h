// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_IFACE_H
#define CFG_IFACE_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <util/reconnect_ctl.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
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
/// The DHCPv4 configuration doesn't accept the simultaneous use of the
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
class CfgIface : public isc::data::UserContext, public isc::data::CfgToElement {
public:

    /// @brief Socket type used by the DHCPv4 server.
    enum SocketType  {
        /// Raw socket, used for direct DHCPv4 traffic.
        SOCKET_RAW,
        /// Datagram socket, i.e. IP/UDP socket.
        SOCKET_UDP
    };

    /// @brief Indicates how outbound interface is selected for relayed traffic.
    enum OutboundIface {
        /// Server sends responses over the same interface on which queries are
        /// received.
        SAME_AS_INBOUND,
        /// Server uses routing to determine the right interface to send response.
        USE_ROUTING
    };

    /// @brief Keyword used to enable all interfaces.
    ///
    /// This keyword can be used instead of the interface name to specify
    /// that DHCP server should listen on all interfaces.
    static const char* ALL_IFACES_KEYWORD;

    /// @brief Constructor.
    CfgIface();

    /// @brief Convenience function which closes all open sockets.
    /// It stops the receiver thread too.
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
    /// This function starts the family receiver.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param port Port number to be used to bind sockets to.
    /// @param use_bcast A boolean flag which indicates if the broadcast
    /// traffic should be received through the socket. This parameter is
    /// ignored for IPv6.
    void openSockets(const uint16_t family, const uint16_t port,
                     const bool use_bcast = true);

    /// @brief Puts the interface configuration into default state.
    ///
    /// This function removes interface names from the set.
    void reset();

    /// @brief Select interface to be used to receive DHCP traffic.
    ///
    /// @ref CfgIface for a detail explanation of the interface name argument.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param iface_name Explicit interface name, a wildcard name (*) of
    /// the interface(s) or the pair of interface/unicast-address to be used
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

    /// @brief Returns DHCP socket type used by the server.
    SocketType getSocketType() const {
        return (socket_type_);
    }

    /// @brief Returns the socket type in the textual format.
    std::string socketTypeToText() const;

    /// @brief Sets outbound interface selection mode.
    ///
    /// @param outbound_iface New outbound interface selection mode setting.
    void setOutboundIface(const OutboundIface& outbound_iface);

    /// @brief Returns outbound interface selection mode.
    ///
    /// @return Outbound interface selection mode.
    OutboundIface getOutboundIface() const;

    /// @brief Returns outbound interface selection mode as string.
    ///
    /// @return text representation of the outbound interface selection mode.
    std::string outboundTypeToText() const;

    /// @brief Converts text to outbound interface selection mode.
    ///
    /// @param txt either 'same-as-inbound' or 'use-routing'
    /// @return Outbound interface selection mode.
    static OutboundIface textToOutboundIface(const std::string& txt);

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

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Set the re-detect flag
    ///
    /// @param re_detect the new value of the flag
    void setReDetect(bool re_detect) {
        re_detect_ = re_detect;
    }

    /// @brief Set flag that Kea must successfully bind all socket services on init.
    ///
    /// @param require_all true if all sockets must be bound, false otherwise.
    void setServiceSocketsRequireAll(bool require_all) {
        service_socket_require_all_ = require_all;
    }

    /// @brief Indicates that Kea must successfully bind all socket services on init.
    ///
    /// @return true if all sockets must be bound, false otherwise.
    bool getServiceSocketsRequireAll() const {
        return (service_socket_require_all_);
    }

    /// @brief Set the socket service binding retry interval between attempts.
    ///
    /// @param interval Milliseconds between attempts.
    void setServiceSocketsRetryWaitTime(uint32_t interval) {
        service_sockets_retry_wait_time_ = interval;
    }

    /// @brief Indicates the socket service binding retry interval between attempts.
    ///
    /// @return Milliseconds between attempts.
    uint32_t getServiceSocketsRetryWaitTime() const {
        return (service_sockets_retry_wait_time_);
    }

    /// @brief Set a maximum number of service sockets bind attempts.
    ///
    /// @param max_retries Number of attempts. The value 0 disables retries.
    void setServiceSocketsMaxRetries(uint32_t max_retries) {
        service_sockets_max_retries_ = max_retries;
    }

    /// @brief Indicates the maximum number of service sockets bind attempts.
    ///
    /// @return Number of attempts.
    uint32_t getServiceSocketsMaxRetries() const {
        return (service_sockets_max_retries_);
    }

    /// @brief Get the reconnect controller.
    ///
    /// @return the reconnect controller
    util::ReconnectCtlPtr getReconnectCtl() const {
        return (reconnect_ctl_);
    }

    /// @brief Represents a callback invoked if all retries of the
    /// opening sockets fail.
    typedef std::function<void(util::ReconnectCtlPtr)> OpenSocketsFailedCallback;

    /// @brief Optional callback function to invoke if all retries of the
    /// opening sockets fail.
    static OpenSocketsFailedCallback open_sockets_failed_callback_;

private:

    /// @brief Checks if multiple IPv4 addresses has been activated on any
    /// interface.
    ///
    /// This method is useful to check if the current configuration uses
    /// multiple IPv4 addresses on any interface. This is important when
    /// using raw sockets to receive messages from the clients because
    /// each packet may be received multiple times when it is sent from
    /// a directly connected client. If this is the case, a warning must
    /// be logged.
    ///
    /// @return true if multiple addresses are activated on any interface,
    /// false otherwise.
    static bool multipleAddressesPerInterfaceActive();

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

    /// @brief Calls a family-specific function to open sockets.
    ///
    /// It is a static function for a safe call from a CfgIface instance or a
    /// timer handler.
    ///
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param port Port number to be used to bind sockets to.
    /// @param can_use_bcast A boolean flag which indicates if the broadcast
    /// traffic should be received through the socket and the raw sockets are
    /// used. For the UDP sockets, we only handle the relayed (unicast)
    /// traffic. This parameter is ignored for IPv6.
    /// @param skip_opened Omits the already opened sockets (doesn't try to
    /// re-bind).
    /// @return Pair of boolean flags. The first boolean is true if at least
    /// one socket is successfully opened, and the second is true if no errors
    /// occur.
    static std::pair<bool, bool> openSocketsForFamily(const uint16_t family,
                                                      const uint16_t port,
                                                      const bool can_use_bcast,
                                                      const bool skip_opened);

    /// @brief Creates a ReconnectCtl based on the configuration's
    /// retry parameters.
    ///
    /// @return The reconnect control created using the configuration
    /// parameters.
    util::ReconnectCtlPtr makeReconnectCtl() const;

    /// Calls the @c CfgIface::openSocketsForFamily function and retry it if
    /// socket opening fails.
    ///
    /// @param reconnect_ctl Used to manage socket reconnection.
    /// @param family Address family (AF_INET or AF_INET6).
    /// @param port Port number to be used to bind sockets to.
    /// @param can_use_bcast A boolean flag which indicates if the broadcast
    /// traffic should be received through the socket and the raw sockets are
    /// used. For the UDP sockets, we only handle the relayed (unicast)
    /// traffic. This parameter is ignored for IPv6.
    ///
    /// @return True if at least one socket opened successfully.
    static bool openSocketsWithRetry(util::ReconnectCtlPtr reconnect_ctl,
                                     const uint16_t family, const uint16_t port,
                                     const bool can_use_bcast);

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

    /// @brief A boolean value which indicates that the wildcard interface name
    /// has been specified (*).
    bool wildcard_used_;

    /// @brief A type of the sockets used by the DHCP server.
    SocketType socket_type_;

    /// @brief A boolean value which reflects current re-detect setting
    bool re_detect_;

    /// @brief A boolean value indicates that Kea must successfully bind all socket services on init
    bool service_socket_require_all_;

    /// @brief An interval between attempts to retry the socket service binding.
    uint32_t service_sockets_retry_wait_time_;

    /// @brief A maximum number of attempts to bind the service sockets.
    uint32_t service_sockets_max_retries_;

    /// @brief Indicates how outbound interface is selected for relayed traffic.
    OutboundIface outbound_iface_;

    /// @brief Used to manage socket reconnection.
    util::ReconnectCtlPtr reconnect_ctl_;
};

/// @brief A pointer to the @c CfgIface .
typedef boost::shared_ptr<CfgIface> CfgIfacePtr;

/// @brief A pointer to the const @c CfgIface.
typedef boost::shared_ptr<const CfgIface> ConstCfgIfacePtr;

}
}

#endif // CFG_IFACE_H
