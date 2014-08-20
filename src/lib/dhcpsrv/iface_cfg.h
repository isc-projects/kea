// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef IFACE_CFG_H
#define IFACE_CFG_H

#include <asiolink/io_address.h>
#include <map>
#include <set>

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

/// @brief Exception thrown when specified unicast address is not assigned
/// to the interface specified.
class NoSuchAddress : public Exception {
public:
    NoSuchAddress(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Represents selection of interfaces for DHCP server.
///
/// This class manages selection of interfaces on which the DHCP server is
/// listening to queries. The interfaces are selected in the server
/// configuration by their names or by the pairs of interface names and unicast
/// addresses (e.g. eth0/2001:db8:1::1). The latter format is only accepted when
/// IPv6 configuration is in use.
///
/// This class also accepts "wildcard" interface name which, if specified,
/// instructs the server to listen on all available interfaces.
///
/// Once interfaces have been specified the sockets (either IPv4 or IPv6)
/// can be opened by calling @c IfaceCfg::openSockets function.
class IfaceCfg {
public:
    /// @brief Keyword used to enable all interfaces.
    ///
    /// This keyword can be used instead of the interface name to specify
    /// that DHCP server should listen on all interfaces.
    static const char* ALL_IFACES_KEYWORD;

    /// @brief Protocol family: IPv4 or IPv6.
    ///
    /// Depending on the family specified, the IPv4 or IPv6 sockets are
    /// opened.
    enum Family {
        V4, V6
    };

    /// @brief Constructor.
    ///
    /// @param family Protocol family (default is V4).
    IfaceCfg(Family family = V4);

    /// @brief Convenience function which closes all open sockets.
    void closeSockets();

    /// @brief Returns protocol family used by the @c IfaceCfg.
    Family getFamily() const {
        return (family_);
    }

    /// @brief Tries to open sockets on selected interfaces.
    ///
    /// This function opens sockets bound to link-local address as well as
    /// sockets bound to unicast address. See @c IfaceCfg::use function
    /// documentation for details how to specify interfaces and unicast
    /// addresses to bind the sockets to.
    ///
    /// @param port Port number to be used to bind sockets to.
    /// @param use_bcast A boolean flag which indicates if the broadcast
    /// traffic should be received through the socket. This parameter is
    /// ignored for IPv6.
    void openSockets(const uint16_t port, const bool use_bcast = true);

    /// @brief Puts the interface configuration into default state.
    ///
    /// This function removes interface names from the set.
    void reset();

    /// @brief Sets protocol family.
    ///
    /// @param family New family value (V4 or V6).
    void setFamily(Family family) {
        family_ = family;
    }

    /// @brief Select interface to be used to receive DHCP traffic.
    ///
    /// This function controls the selection of the interface on which the
    /// DHCP queries should be received by the server. The interface name
    /// passed as the argument of this function may appear in one of the following
    /// formats:
    /// - interface-name, e.g. eth0
    /// - interface-name/unicast-address, e.g. eth0/2001:db8:1::1 (V6 only)
    ///
    /// Extraneous spaces surrounding the interface name and/or unicast address
    /// are accepted. For example: eth0 / 2001:db8:1::1 will be accepted.
    ///
    /// When only interface name is specified (without an address) it is allowed
    /// to use the "wildcard" interface name (*) which indicates that the server
    /// should open sockets on all interfaces. When IPv6 is in use, the sockets
    /// will be bound to the link local addresses. Wildcard interface names are
    /// not allowed when specifying a unicast address. For example:
    /// */2001:db8:1::1 is not allowed.
    ///
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
    /// @c IfaceCfg::use has been already called for this interface.
    void use(const std::string& iface_name);

private:

    /// @brief Selects or deselects all interfaces.
    ///
    /// This function selects all interfaces to receive DHCP traffic or
    /// deselects all interfaces so as none of them receives a DHCP traffic.
    ///
    /// @param inactive A boolean value which indicates if all interfaces
    /// should be deselected/inactive (true) or selected/active (false).
    void setState(const bool inactive);

    /// @brief Error handler for executed when opening a socket fail.
    ///
    /// A pointer to this function is passed to the @c IfaceMgr::openSockets4
    /// or @c IfaceMgr::openSockets6. These functions call this handler when
    /// they fail to open a socket. The handler logs an error passed in the
    /// parameter.
    ///
    /// @param errmsg Error message being logged by the function.
    void socketOpenErrorHandler(const std::string& errmsg);

    /// @brief Protocol family.
    Family family_;
    /// @brief Represents a set of interface names.
    typedef std::set<std::string> IfaceSet;
    /// @brief A set of interface names specified by the user.
    IfaceSet iface_set_;
    /// @brief A map of interfaces and unicast addresses.
    typedef std::map<std::string, asiolink::IOAddress> UnicastMap;
    /// @brief A map which holds the pairs of interface names and unicast
    /// addresses for which the unicast sockets should be opened.
    ///
    /// This is only used for V6 family.
    UnicastMap unicast_map_;
    /// @brief A booolean value which indicates that the wildcard interface name
    /// has been specified (*).
    bool wildcard_used_;
};

}
}

#endif // IFACE_CFG_H
