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

#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_rsoo.h>

namespace isc {
namespace dhcp {

CfgRSOO::CfgRSOO()
    : rsoo_options_() {
    rsoo_options_.insert(D6O_ERP_LOCAL_DOMAIN_NAME);
}

void
CfgRSOO::clear() {
    rsoo_options_.clear();
}

bool
CfgRSOO::enabled(const uint16_t code) const {
    return (rsoo_options_.find(code) != rsoo_options_.end());
}

void
CfgRSOO::enable(const uint16_t code) {
    if (rsoo_options_.find(code) == rsoo_options_.end()) {
        // If there's no such code added yet, let's add it
        rsoo_options_.insert(code);
    }
}


}
}
