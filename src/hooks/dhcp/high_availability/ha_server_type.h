// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_SERVER_TYPE_H
#define HA_SERVER_TYPE_H

namespace isc {
namespace ha {

/// @brief Lists possible server types for which HA service is created.
enum class HAServerType {
    DHCPv4,
    DHCPv6
};

} // end of namespace isc::ha
} // end of namespace isc

#endif // HA_SERVER_TYPE_H

