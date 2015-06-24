// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/cfg_iface.h>
#include <util/strutil.h>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

const char* CfgIface::ALL_IFACES_KEYWORD = "*";

CfgIface::CfgIface()
    : wildcard_used_(false), socket_type_(SOCKET_RAW) {
}

void
CfgIface::closeSockets() const {
    IfaceMgr::instance().closeSockets();
}

bool
CfgIface::equals(const CfgIface& other) const {
    return (iface_set_ == other.iface_set_ &&
            address_map_ == other.address_map_ &&
            wildcard_used_ == other.wildcard_used_ &&
            socket_type_ == other.socket_type_);
}

bool
CfgIface::multipleAddressesPerInterfaceActive() const {
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();
    BOOST_FOREACH(IfacePtr iface, ifaces) {
        if (iface->countActive4() > 1) {
            return (true);
        }
    }
    return (false);
}

void
CfgIface::openSockets(const uint16_t family, const uint16_t port,
                      const bool use_bcast) const {
    // Close any open sockets because we're going to modify some properties
    // of the IfaceMgr. Those modifications require that sockets are closed.
    closeSockets();
    // If wildcard interface '*' was not specified, set all interfaces to
    // inactive state. We will later enable them selectively using the
    // interface names specified by the user. If wildcard interface was
    // specified, mark all interfaces active. In all cases, mark loopback
    // inactive.
    setState(family, !wildcard_used_, true);
    IfaceMgr& iface_mgr = IfaceMgr::instance();
    // Remove selection of unicast addresses from all interfaces.
    iface_mgr.clearUnicasts();
    // For the DHCPv4 server, if the user has selected that raw sockets
    // should be used, we will try to configure the Interface Manager to
    // support the direct responses to the clients that don't have the
    // IP address. This should effectively turn on the use of raw
    // sockets. However, this may be unsupported on some operating
    // systems, so there is no guarantee.
    if ((family == AF_INET) && (!IfaceMgr::instance().isTestMode())) {
        iface_mgr.setMatchingPacketFilter(socket_type_ == SOCKET_RAW);
        if ((socket_type_ == SOCKET_RAW) &&
            !iface_mgr.isDirectResponseSupported()) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_SOCKET_RAW_UNSUPPORTED);
        }
    }
    // If there is no wildcard interface specified, we will have to iterate
    // over the names specified by the caller and enable them.
    if (!wildcard_used_) {
        for (IfaceSet::const_iterator iface_name = iface_set_.begin();
             iface_name != iface_set_.end(); ++iface_name) {
            IfacePtr iface = IfaceMgr::instance().getIface(*iface_name);
            // This shouldn't really happen because we are checking the
            // names of interfaces when they are being added (use()
            // function). But, if someone has triggered detection of
            // interfaces since then, some interfaces may have disappeared.
            if (iface == NULL) {
                isc_throw(Unexpected,
                          "fail to open socket on interface '"
                          << *iface_name << "' as this interface doesn't"
                          " exist");

            } else if (family == AF_INET) {
                iface->inactive4_ = false;
                setIfaceAddrsState(family, true, *iface);

            } else {
                iface->inactive6_ = false;
            }
        }
    }

    // Select unicast sockets for DHCPv6 or activate specific IPv4 addresses
    // for DHCPv4.
    for (ExplicitAddressMap::const_iterator unicast = address_map_.begin();
         unicast != address_map_.end(); ++unicast) {
        IfacePtr iface = IfaceMgr::instance().getIface(unicast->first);
        if (iface == NULL) {
            isc_throw(Unexpected,
                      "fail to open unicast socket on interface '"
                      << unicast->first << "' as this interface doesn't"
                      " exist");
        }
        if (family == AF_INET6) {
            iface->addUnicast(unicast->second);
            iface->inactive6_ = false;

        } else {
            iface->setActive(unicast->second, true);
            iface->inactive4_ = false;
        }
    }

    // Set the callback which is called when the socket fails to open
    // for some specific interface. This callback will simply log a
    // warning message.
    IfaceMgrErrorMsgCallback error_callback =
        boost::bind(&CfgIface::socketOpenErrorHandler, _1);
    bool sopen;
    if (family == AF_INET) {
        // Use broadcast only if we're using raw sockets. For the UDP sockets,
        // we only handle the relayed (unicast) traffic.
        const bool can_use_bcast = use_bcast && (socket_type_ == SOCKET_RAW);
        // Opening multiple raw sockets handling brodcast traffic on the single
        // interface may lead to processing the same message multiple times.
        // We don't prohibit such configuration because raw sockets can as well
        // handle the relayed traffic. We have to issue a warning, however, to
        // draw administrator's attention.
        if (can_use_bcast && multipleAddressesPerInterfaceActive()) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_MULTIPLE_RAW_SOCKETS_PER_IFACE);
        }
        sopen = IfaceMgr::instance().openSockets4(port, can_use_bcast, error_callback);
    } else {
        // use_bcast is ignored for V6.
        sopen = IfaceMgr::instance().openSockets6(port, error_callback);
    }

    // If no socket were opened, log a warning because the server will
    // not respond to any queries.
    if (!sopen) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_NO_SOCKETS_OPEN);
    }
}

void
CfgIface::reset() {
    wildcard_used_ = false;
    iface_set_.clear();
    address_map_.clear();
    useSocketType(AF_INET, SOCKET_RAW);
}

void
CfgIface::setState(const uint16_t family, const bool inactive,
                   const bool loopback_inactive) const {
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();
    BOOST_FOREACH(IfacePtr iface, ifaces) {
        bool iface_inactive = iface->flag_loopback_ ? loopback_inactive : inactive;
        if (family == AF_INET) {
            iface->inactive4_ = iface_inactive;
        } else {
            iface->inactive6_ = iface_inactive;
        }

        // Activate/deactivate all addresses.
        setIfaceAddrsState(family, !inactive, *iface);
    }
}

void
CfgIface::setIfaceAddrsState(const uint16_t family, const bool active,
                             Iface& iface) const {
    // Activate/deactivate all addresses.
    BOOST_FOREACH(Iface::Address addr, iface.getAddresses()) {
        if (addr.get().getFamily() == family) {
            iface.setActive(addr.get(), active);
        }
    }
}

void
CfgIface::socketOpenErrorHandler(const std::string& errmsg) {
    LOG_WARN(dhcpsrv_logger, DHCPSRV_OPEN_SOCKET_FAIL).arg(errmsg);
}

std::string
CfgIface::socketTypeToText() const {
    switch (socket_type_) {
    case SOCKET_RAW:
        return ("raw");

    case SOCKET_UDP:
        return ("udp");

    default:
        ;
    }

    isc_throw(Unexpected, "unsupported socket type " << socket_type_);
}

CfgIface::SocketType
CfgIface::textToSocketType(const std::string& socket_type_name) const {
    if (socket_type_name == "udp") {
        return (SOCKET_UDP);

    } else if (socket_type_name == "raw") {
        return (SOCKET_RAW);

    } else {
        isc_throw(InvalidSocketType, "unsupported socket type '"
                  << socket_type_name << "'");
    }
}

void
CfgIface::use(const uint16_t family, const std::string& iface_name) {
    // The interface name specified may have two formats:
    // - "interface-name", e.g. eth0
    // - "interface-name/address", e.g. eth0/10.0.0.1 or eth/2001:db8:1::1
    // The latter format is used to open unicast socket on the specified
    // interface. Here we are detecting which format was used and we strip
    // all extraneous spaces.
    size_t pos = iface_name.find("/");
    std::string name;
    std::string addr_str;
    // There is no unicast address so the whole string is an interface name.
    if (pos == std::string::npos) {
        name = util::str::trim(iface_name);
        if (name.empty()) {
            isc_throw(InvalidIfaceName,
                      "empty interface name used in configuration");

        } else if (name != ALL_IFACES_KEYWORD) {
            if (IfaceMgr::instance().getIface(name) == NULL) {
                isc_throw(NoSuchIface, "interface '" << name
                          << "' doesn't exist in the system");
            }

        } else if (wildcard_used_) {
            isc_throw(DuplicateIfaceName, "the wildcard interface '"
                      << ALL_IFACES_KEYWORD << "' can only be specified once");

        } else {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_ALL_IFACES_ACTIVE);
            wildcard_used_ = true;

        }

    } else {
        // The interface name includes the address on which the socket should
        // be opened, and we need to split interface name and the address to
        // two variables.
        name = util::str::trim(iface_name.substr(0, pos));
        addr_str = util::str::trim(iface_name.substr(pos + 1));

        // Interface name must not be empty.
        if (name.empty()) {
            isc_throw(InvalidIfaceName,
                      "empty interface name specified in the"
                      " interface configuration");

        }
        // An address following the interface name must not be empty.
        if (addr_str.empty()) {
            isc_throw(InvalidIfaceName,
                      "empty address specified in the interface"
                      << " configuration");

        }

        // Interface name must not be the wildcard name.
        if (name == ALL_IFACES_KEYWORD) {
            isc_throw(InvalidIfaceName,
                      "wildcard interface name '" << ALL_IFACES_KEYWORD
                      << "' must not be used in conjunction with an"
                      " address");

        }

        // Interface must exist.
        IfacePtr iface = IfaceMgr::instance().getIface(name);
        if (!iface) {
            isc_throw(NoSuchIface, "interface '" << name
                      << "' doesn't exist in the system");

        }

        // Convert address string. This may throw an exception if the address
        // is invalid.
        IOAddress addr(addr_str);

        // Validate V6 address.
        if (family == AF_INET6) {
            // Check that the address is a valid unicast address.
            if (!addr.isV6() || addr.isV6Multicast()) {
                isc_throw(InvalidIfaceName, "address '" << addr << "' is not"
                          " a valid IPv6 unicast address");
            }

            // There are valid cases where link local address can be specified to
            // receive unicast traffic, e.g. sent by relay agent.
            if (addr.isV6LinkLocal()) {
                LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_UNICAST_LINK_LOCAL)
                    .arg(addr.toText()).arg(name);
            }

        } else {
            if (!addr.isV4()) {
                isc_throw(InvalidIfaceName, "address '" << addr << "' is not"
                          " a valid IPv4 address");
            }
        }

        // Interface must have this address assigned.
        if (!iface->hasAddress(addr)) {
            isc_throw(NoSuchAddress,
                      "interface '" << name << "' doesn't have address '"
                      << addr << "' assigned");
        }

        // For the IPv4, if the interface name was specified (instead of the interface-
        // address tuple) all addresses are already activated. Adding an explicit address
        // for the interface should result in error.
        if ((family == AF_INET) && (iface_set_.find(iface->getName()) != iface_set_.end())) {
            isc_throw(DuplicateIfaceName, "interface '" << iface->getName()
                      << "' has already been selected");
        }

        // Check if the address hasn't been selected already.
        std::pair<const std::string, IOAddress> iface_address_tuple(name, addr);
        if (std::find(address_map_.begin(), address_map_.end(),
                      iface_address_tuple) != address_map_.end()) {
            isc_throw(DuplicateAddress, "must not select address '"
                      << addr << "' for interface '" << name << "' "
                      "because this address is already selected");
        }

        if (family == AF_INET6) {
            LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_USE_UNICAST)
                .arg(addr.toText()).arg(name);

        } else {
            LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_USE_ADDRESS)
                .arg(addr.toText()).arg(name);
        }
        address_map_.insert(std::pair<std::string, IOAddress>(name, addr));
    }

    // If interface name was explicitly specified without an address, we will
    // insert the interface name to the set of enabled interfaces.
    if ((name != ALL_IFACES_KEYWORD) && addr_str.empty()) {
        // An interface has been selected or an IPv4 address on this interface
        // has been selected it is not allowed to select the whole interface.
        if ((iface_set_.find(name) != iface_set_.end()) ||
            ((family == AF_INET) && address_map_.count(name) > 0)) {
            isc_throw(DuplicateIfaceName, "interface '" << name
                      << "' has already been specified");
        }

        // Log that we're listening on the specific interface and that the
        // address is not explicitly specified.
        if (addr_str.empty()) {
            LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_ADD_IFACE).arg(name);
        }
        iface_set_.insert(name);
    }
}

void
CfgIface::useSocketType(const uint16_t family,
                        const SocketType& socket_type) {
    if (family != AF_INET) {
        isc_throw(InvalidSocketType, "socket type must not be specified for"
                  " the DHCPv6 server");
    }
    socket_type_ = socket_type;
    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_SOCKET_TYPE_SELECT)
        .arg(socketTypeToText());
}

void
CfgIface::useSocketType(const uint16_t family,
                        const std::string& socket_type_name) {
    useSocketType(family, textToSocketType(socket_type_name));
}

} // end of isc::dhcp namespace
} // end of isc namespace
