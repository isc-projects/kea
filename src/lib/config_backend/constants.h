// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_BACKEND_CONSTANTS_H
#define CONFIG_BACKEND_CONSTANTS_H

namespace isc {
namespace cb {

/// @name Constants specifying output buffer lengths.
///
/// Config backends create buffers of these sizes to store
/// fetched variable length data in them.
///
//@{
constexpr unsigned long SUBNET_PREFIX_BUF_LENGTH = 32;

constexpr unsigned long DHCP4O6_INTERFACE_BUF_LENGTH = 128;

constexpr unsigned long DHCP4O6_INTERFACE_ID_BUF_LENGTH = 128;

constexpr unsigned long DHCP4O6_SUBNET_BUF_LENGTH = 64;

constexpr unsigned long BOOT_FILE_NAME_BUF_LENGTH = 512;

constexpr unsigned long CLIENT_CLASS_BUF_LENGTH = 128;

constexpr unsigned long INTERFACE_BUF_LENGTH = 128;

constexpr unsigned long RELAY_BUF_LENGTH = 65536;

constexpr unsigned long REQUIRE_CLIENT_CLASSES_BUF_LENGTH = 65536;

constexpr unsigned long SERVER_HOSTNAME_BUF_LENGTH = 512;

constexpr unsigned long SHARED_NETWORK_NAME_BUF_LENGTH = 128;

constexpr unsigned long USER_CONTEXT_BUF_LENGTH = 65536;

constexpr unsigned long OPTION_VALUE_BUF_LENGTH = 65536;

constexpr unsigned long FORMATTED_OPTION_VALUE_BUF_LENGTH = 8192;

constexpr unsigned long OPTION_SPACE_BUF_LENGTH = 128;

constexpr unsigned long OPTION_NAME_BUF_LENGTH = 128;

constexpr unsigned long OPTION_ENCAPSULATE_BUF_LENGTH = 128;

constexpr unsigned long OPTION_RECORD_TYPES_BUF_LENGTH = 512;

constexpr unsigned long GLOBAL_PARAMETER_NAME_BUF_LENGTH = 128;

constexpr unsigned long GLOBAL_PARAMETER_VALUE_BUF_LENGTH = 65536;

//*}

} // end of namespace isc::cb
} // end of namespace isc

#endif
