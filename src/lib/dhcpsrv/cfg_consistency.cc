// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfg_consistency.h>
#include <cc/data.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

isc::data::ElementPtr CfgConsistency::toElement() const {
    ElementPtr m(new MapElement());
    ElementPtr l(new StringElement(sanityCheckToText(getLeaseSanityCheck())));
    m->set("lease-checks", l);
    ElementPtr x(new StringElement(sanityCheckToText(getExtendedInfoSanityCheck())));
    m->set("extended-info-checks", x);

    return (m);
}

std::string CfgConsistency::sanityCheckToText(LeaseSanity check_type) {
    switch (check_type) {
    case LEASE_CHECK_NONE:
        return ("none");
    case LEASE_CHECK_WARN:
        return ("warn");
    case LEASE_CHECK_FIX:
        return ("fix");
    case LEASE_CHECK_FIX_DEL:
        return ("fix-del");
    case LEASE_CHECK_DEL:
        return ("del");
    default:
        return ("unknown");
    }
}

std::string CfgConsistency::sanityCheckToText(ExtendedInfoSanity check_type) {
    switch (check_type) {
    case EXTENDED_INFO_CHECK_NONE:
        return ("none");
    case EXTENDED_INFO_CHECK_FIX:
        return ("fix");
    case EXTENDED_INFO_CHECK_STRICT:
        return ("strict");
    case EXTENDED_INFO_CHECK_PEDANTIC:
        return ("pedantic");
    default:
        return ("unknown");
    }
}

}
}
