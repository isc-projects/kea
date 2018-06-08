// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

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

