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
#include <dhcpsrv/iface_cfg.h>
#include <util/strutil.h>
#include <boost/bind.hpp>

namespace isc {
namespace dhcp {

const char* IfaceCfg::ALL_IFACES_KEYWORD = "*";

IfaceCfg::IfaceCfg(Family family)
    : family_(family),
      wildcard_used_(false) {
}

void
IfaceCfg::closeSockets() {
    IfaceMgr::instance().closeSockets();
}

void
IfaceCfg::openSockets(const uint16_t port, const bool use_bcast) {
    // If wildcard interface '*' was not specified, set all interfaces to
    // inactive state. We will later enable them selectively using the
    // interface names specified by the user. If wildcard interface was
    // specified, mark all interfaces active.
    setState(!wildcard_used_);
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

    // Set the callback which is called when the socket fails to open
    // for some specific interface. This callback will simply log a
    // warning message.
    IfaceMgrErrorMsgCallback error_callback =
        boost::bind(&IfaceCfg::socketOpenErrorHandler, this, _1);
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
IfaceCfg::reset() {
    wildcard_used_ = false;
    iface_set_.clear();
}

void
IfaceCfg::setState(const bool inactive) {
    IfaceMgr::IfaceCollection ifaces = IfaceMgr::instance().getIfaces();
    for (IfaceMgr::IfaceCollection::iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        Iface* iface_ptr = IfaceMgr::instance().getIface(iface->getName());
        if (getFamily() == V4) {
            iface_ptr->inactive4_ = inactive;
        } else {
            iface_ptr->inactive6_ = inactive;
        }
    }
}

void
IfaceCfg::socketOpenErrorHandler(const std::string& errmsg) {
    LOG_WARN(dhcpsrv_logger, DHCPSRV_OPEN_SOCKET_FAIL).arg(errmsg);
}

void
IfaceCfg::use(const std::string& iface_name) {
    // In theory the configuration parser should strip extraneous spaces but
    // since this is a common library it may be better to make sure that it
    // is really the case.
    std::string name = util::str::trim(iface_name);
    if (name.empty()) {
        isc_throw(InvalidIfaceName,
                  "empty interface name used in configuration");

    } else if (name != ALL_IFACES_KEYWORD) {
        if (IfaceMgr::instance().getIface(name) == NULL) {
            isc_throw(NoSuchIface, "interface '" << name
                      << "' doesn't exist in the system");
        }

        std::pair<IfaceSet::iterator, bool> res = iface_set_.insert(name);
        if (!res.second) {
            isc_throw(DuplicateIfaceName, "interface '" << name
                      << "' has already been specified");
        }

    } else if (wildcard_used_) {
        isc_throw(DuplicateIfaceName, "the wildcard interface '"
                  << ALL_IFACES_KEYWORD << "' can only be specified once");

    } else {
        wildcard_used_ = true;

    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
