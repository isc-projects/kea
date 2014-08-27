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

#include <dhcp/iface_mgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/cfg_iface.h>
#include <util/strutil.h>
#include <boost/bind.hpp>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

const char* CfgIface::ALL_IFACES_KEYWORD = "*";

CfgIface::CfgIface(Family family)
    : family_(family),
      wildcard_used_(false) {
}

void
CfgIface::closeSockets() {
    IfaceMgr::instance().closeSockets();
}

void
CfgIface::openSockets(const uint16_t port, const bool use_bcast) {
    // If wildcard interface '*' was not specified, set all interfaces to
    // inactive state. We will later enable them selectively using the
    // interface names specified by the user. If wildcard interface was
    // specified, mark all interfaces active. In all cases, mark loopback
    // inactive.
    setState(!wildcard_used_, true);
    // Remove selection of unicast addresses from all interfaces.
    IfaceMgr::instance().clearUnicasts();
    // If there is no wildcard interface specified, we will have to iterate
    // over the names specified by the caller and enable them.
    if (!wildcard_used_) {
        for (IfaceSet::const_iterator iface_name = iface_set_.begin();
             iface_name != iface_set_.end(); ++iface_name) {
            Iface* iface = IfaceMgr::instance().getIface(*iface_name);
            // This shouldn't really happen because we are checking the
            // names of interfaces when they are being added (use()
            // function). But, if someone has triggered detection of
            // interfaces since then, some interfaces may have disappeared.
            if (iface == NULL) {
                isc_throw(Unexpected,
                          "fail to open socket on interface '"
                          << *iface_name << "' as this interface doesn't"
                          " exist");

            } else if (getFamily() == V4) {
                iface->inactive4_ = false;

            } else {
                iface->inactive6_ = false;
            }
        }
    }

    // Select unicast sockets. It works only for V6. Ignore for V4.
    if (getFamily() == V6) {
        for (UnicastMap::const_iterator unicast = unicast_map_.begin();
             unicast != unicast_map_.end(); ++unicast) {
            Iface* iface = IfaceMgr::instance().getIface(unicast->first);
            if (iface == NULL) {
                isc_throw(Unexpected,
                          "fail to open unicast socket on interface '"
                          << unicast->first << "' as this interface doesn't"
                          " exist");
            }
            iface->addUnicast(unicast->second);
            iface->inactive6_ = false;
        }
    }

    // Before opening any sockets, close existing ones.
    closeSockets();

    // Set the callback which is called when the socket fails to open
    // for some specific interface. This callback will simply log a
    // warning message.
    IfaceMgrErrorMsgCallback error_callback =
        boost::bind(&CfgIface::socketOpenErrorHandler, _1);
    bool sopen;
    if (getFamily() == V4) {
        sopen = IfaceMgr::instance().openSockets4(port, use_bcast,
                                                  error_callback);
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
}

void
CfgIface::setState(const bool inactive, const bool loopback_inactive) {
    IfaceMgr::IfaceCollection ifaces = IfaceMgr::instance().getIfaces();
    for (IfaceMgr::IfaceCollection::iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        Iface* iface_ptr = IfaceMgr::instance().getIface(iface->getName());
        if (getFamily() == V4) {
            iface_ptr->inactive4_ = iface_ptr->flag_loopback_ ?
                loopback_inactive : inactive;
        } else {
            iface_ptr->inactive6_ = iface_ptr->flag_loopback_ ?
                loopback_inactive : inactive;
        }
    }
}

void
CfgIface::socketOpenErrorHandler(const std::string& errmsg) {
    LOG_WARN(dhcpsrv_logger, DHCPSRV_OPEN_SOCKET_FAIL).arg(errmsg);
}

void
CfgIface::use(const std::string& iface_name) {
    // The interface name specified may have two formats, e.g.:
    // - eth0
    // - eth0/2001:db8:1::1.
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

        } if (name != ALL_IFACES_KEYWORD) {
            if (IfaceMgr::instance().getIface(name) == NULL) {
                isc_throw(NoSuchIface, "interface '" << name
                          << "' doesn't exist in the system");
            }

            // If interface has already been specified.
            if (iface_set_.find(name) != iface_set_.end()) {
                isc_throw(DuplicateIfaceName, "interface '" << name
                          << "' has already been specified");

            }

            // All ok, add interface.
            LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_ADD_IFACE)
                .arg(name);
            iface_set_.insert(name);

        } else if (wildcard_used_) {
            isc_throw(DuplicateIfaceName, "the wildcard interface '"
                      << ALL_IFACES_KEYWORD << "' can only be specified once");

        } else {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_ALL_IFACES_ACTIVE);
            wildcard_used_ = true;

        }

    } else if (getFamily() == V4) {
        isc_throw(InvalidIfaceName, "unicast addresses in the format of: "
                  "iface-name/unicast-addr_stress can only be specified for"
                  " IPv6 addr_stress family");

    } else {
        // The interface name includes the unicast addr_stress, so we split
        // interface name and the unicast addr_stress to two variables.
        name = util::str::trim(iface_name.substr(0, pos));
        addr_str = util::str::trim(iface_name.substr(pos + 1));

        // Interface name must not be empty.
        if (name.empty()) {
            isc_throw(InvalidIfaceName,
                      "empty interface name specified in the"
                      " interface configuration");

        }
        // Unicast addr_stress following the interface name must not be empty.
        if (addr_str.empty()) {
            isc_throw(InvalidIfaceName,
                      "empty unicast addr_stress specified in the interface"
                      << " configuration");

        }

        // Interface name must not be the wildcard name.
        if (name == ALL_IFACES_KEYWORD) {
            isc_throw(InvalidIfaceName,
                      "wildcard interface name '" << ALL_IFACES_KEYWORD
                      << "' must not be used in conjunction with a"
                      " unicast addr_stress");

        }

        // Interface must exist.
        Iface* iface = IfaceMgr::instance().getIface(name);
        if (iface == NULL) {
            isc_throw(NoSuchIface, "interface '" << name
                      << "' doesn't exist in the system");

        }

        // Convert address string. This may throw an exception if the address
        // is invalid.
        IOAddress addr(addr_str);

        // Check that the address is a valid unicast address.
        if (!addr.isV6() || addr.isV6LinkLocal() || addr.isV6Multicast()) {
            isc_throw(InvalidIfaceName, "address '" << addr << "' is not"
                      " a valid IPv6 unicast address");
        }

        // There are valid cases where link local address can be specified to
        // receive unicast traffic, e.g. sent by relay agent.
        if (addr.isV6LinkLocal()) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_UNICAST_LINK_LOCAL)
                .arg(addr.toText()).arg(name);
        }

        // Interface must have this address assigned.
        if (!iface->hasAddress(addr)) {
            isc_throw(NoSuchAddress,
                      "interface '" << name << "' doesn't have address '"
                      << addr << "' assigned");
        }

        // Insert address and the interface to the collection of unicast
        // addresses.
        if (unicast_map_.find(name) != unicast_map_.end()) {
            isc_throw(DuplicateIfaceName, "must not specify unicast address '"
                      << addr << "' for interface '" << name << "' "
                      "because other unicast address has already been"
                      " specified for this interface");
        }
        LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_ADD_UNICAST)
            .arg(addr.toText()).arg(name);
        unicast_map_.insert(std::pair<std::string, IOAddress>(name, addr));
    }

}

} // end of isc::dhcp namespace
} // end of isc namespace
