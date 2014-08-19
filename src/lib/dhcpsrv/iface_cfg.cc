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
#include <dhcpsrv/iface_cfg.h>
#include <util/strutil.h>

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
IfaceCfg::openSockets(const uint16_t /* port */) {
    if (!wildcard_used_) {
        setState(true);
        for (IfaceSet::const_iterator iface_name = iface_set_.begin();
             iface_name != iface_set_.end(); ++iface_name) {
            Iface* iface = IfaceMgr::instance().getIface(*iface_name);
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

    } else {
        setState(false);
    }

    // @todo open sockets here.

}

void
IfaceCfg::setState(const bool inactive) {
    const IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();
    for (IfaceCollection::iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        if (getFamily() == V4) {
            (*iface)->inactive4_ = inactive;
        } else {
            (*iface)->inactive6_ = inactive;
        }
    }
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
    }

    if (name != ALL_IFACES_KEYWORD) {
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
