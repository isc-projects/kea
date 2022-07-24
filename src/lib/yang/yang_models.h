// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_YANG_MODELS_H
#define ISC_YANG_MODELS_H 1

#include <string>

namespace isc {
namespace yang {

/// This model is being developed at DHC working group in IETF.
/// For details, see draft-ietf-dhc-dhcpv6-yang Internet Draft.
/// It is a generic model that is somewhat applicable to Kea.
static const std::string IETF_DHCPV6_SERVER = "ietf-dhcpv6-server";

/// This model is being developed by ISC and is dedicated to Kea.
static const std::string KEA_DHCP4_SERVER = "kea-dhcp4-server";

/// This model is being developed by ISC and is dedicated to Kea.
static const std::string KEA_DHCP6_SERVER = "kea-dhcp6-server";

/// This model is currently in prototype phase. It will be developed
/// by ISC in the near future.
static const std::string KEA_DHCP_DDNS = "kea-dhcp-ddns";

/// This model is currently in prototype phase. It will be developed
/// by ISC in the near future.
static const std::string KEA_CTRL_AGENT = "kea-ctrl-agent";

}  // end of namespace isc::yang
}  // end of namespace isc

#endif // ISC_YANG_MODELS_H
