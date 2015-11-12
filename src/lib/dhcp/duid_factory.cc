// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/duid_factory.h>
#include <dhcp/iface_mgr.h>
#include <util/io_utilities.h>
#include <util/range_utilities.h>
#include <util/strutil.h>
#include <boost/foreach.hpp>
#include <ctime>
#include <string>
#include <vector>

using namespace isc::util;
using namespace isc::util::str;

namespace {

const size_t MIN_MAC_LEN = 6;

}

namespace isc {
namespace dhcp {

DUIDFactory::DUIDFactory(const std::string& storage_location)
    : storage_location_(trim(storage_location)), duid_() {
}

bool
DUIDFactory::isPersisted() const {
    return (!storage_location_.empty());
}

void
DUIDFactory::createLLT(const uint16_t htype, const uint32_t time_in,
                       const std::vector<uint8_t>& ll_identifier) {
    uint32_t time_out = time_in;
    if (time_out == 0) {
        time_out = static_cast<uint32_t>(time(NULL) - DUID_TIME_EPOCH);
    }

    uint16_t htype_out = htype;
    if (htype_out == 0) {
        htype_out = HTYPE_ETHER;
    }

    std::vector<uint8_t> ll_identifier_out = ll_identifier;
    if (ll_identifier_out.empty()) {
        createLinkLayerId(ll_identifier_out);
    }

    std::vector<uint8_t> duid_out(2 + sizeof(time_out) + sizeof(htype_out));
    writeUint16(DUID::DUID_LLT, &duid_out[0], 2);
    writeUint16(htype_out, &duid_out[2], 2);
    writeUint32(time_out, &duid_out[4], 4);
    duid_out.insert(duid_out.end(), ll_identifier_out.begin(),
                    ll_identifier_out.end());

    duid_.reset(new DUID(duid_out));
}

/*void
DUIDFactory::createEN(const uint32_t enterprise_id,
                          const std::vector<uint8_t>& identifier) {
}*/

/*void
DUIDFactory::createLL(const uint16_t htype, const std::vector<uint8_t>& ll_identifier) {
} */

void
DUIDFactory::createLinkLayerId(std::vector<uint8_t>& identifier) const {
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

    // Let's find suitable interface.
    BOOST_FOREACH(IfacePtr iface, ifaces) {
        // All the following checks could be merged into one multi-condition
        // statement, but let's keep them separated as perhaps one day
        // we will grow knobs to selectively turn them on or off. Also,
        // this code is used only *once* during first start on a new machine
        // and then server-id is stored. (or at least it will be once
        // DUID storage is implemented)

        // I wish there was a this_is_a_real_physical_interface flag...

        // MAC address should be at least 6 bytes. Although there is no such
        // requirement in any RFC, all decent physical interfaces (Ethernet,
        // WiFi, InfiniBand, etc.) have 6 bytes long MAC address. We want to
        // base our DUID on real hardware address, rather than virtual
        // interface that pretends that underlying IP address is its MAC.
        if (iface->getMacLen() < MIN_MAC_LEN) {
            continue;
        }

        // Let's don't use loopback.
        if (iface->flag_loopback_) {
            continue;
        }

        // Let's skip downed interfaces. It is better to use working ones.
        if (!iface->flag_up_) {
            continue;
        }

        // Some interfaces (like lo on Linux) report 6-bytes long
        // MAC address 00:00:00:00:00:00. Let's not use such weird interfaces
        // to generate DUID.
        if (isRangeZero(iface->getMac(), iface->getMac() + iface->getMacLen())) {
            continue;
        }

        identifier.assign(iface->getMac(), iface->getMac() + iface->getMacLen());
    }
}

DuidPtr
DUIDFactory::get() {
    return (duid_);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
