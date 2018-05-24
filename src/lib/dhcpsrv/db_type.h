// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_TYPE_H
#define DB_TYPE_H

namespace isc {
namespace dhcp {

/// @brief Specifies the database type.
enum class DBType {
    LEASE_DB = 1,
    HOSTS_DB = 2
};

}  // namespace isc
}  // namespace dhcp

#endif
