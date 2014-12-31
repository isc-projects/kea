// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfg_mac_source.h>
#include <exceptions/exceptions.h>
#include <dhcp/hwaddr.h>

namespace isc {
namespace dhcp {

CfgMACSource::CfgMACSource() {

    // By default, use any hardware source that is available.
    mac_sources_.push_back(HWAddr::HWADDR_SOURCE_ANY);
}

uint32_t CfgMACSource::MACSourceFromText(const std::string& name) {

    struct {
        const char * name;
        uint32_t type;
    } sources[] = {
        { "any", HWAddr::HWADDR_SOURCE_ANY },
        { "raw", HWAddr::HWADDR_SOURCE_RAW },
        { "duid", HWAddr::HWADDR_SOURCE_DUID },
        { "ipv6-link-local", HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL },
        { "client-link-addr-option", HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION },
        { "rfc6939", HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION },
        { "remote-id", HWAddr::HWADDR_SOURCE_REMOTE_ID },
        { "rfc4649", HWAddr::HWADDR_SOURCE_REMOTE_ID },
        { "subscriber-id", HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID },
        { "rfc4580", HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID },
        { "docsis-cmts", HWAddr::HWADDR_SOURCE_DOCSIS_CMTS },
        { "docsis-modem", HWAddr::HWADDR_SOURCE_DOCSIS_MODEM }
    };

    for (int i=0; i < sizeof(sources)/sizeof(sources[0]); ++i) {
        if (name.compare(sources[i].name) == 0) {
            return (sources[i].type);
        }
    }

    isc_throw(BadValue, "Can't convert '" << name << "' to any known MAC source.");
}


};
};
