// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DOCSIS3_OPTION_DEFS_H
#define DOCSIS3_OPTION_DEFS_H

#include <dhcp/std_option_defs.h>
#include <dhcp/option_data_types.h>

namespace isc {
namespace dhcp {

#define VENDOR_ID_CABLE_LABS 4491

#define DOCSIS3_V4_ORO 1
#define DOCSIS3_V4_TFTP_SERVERS 2

/// @brief Definitions of standard DHCPv4 options.
const OptionDefParams DOCSIS3_V4_DEFS[] = {
    { "oro", DOCSIS3_V4_ORO, OPT_UINT8_TYPE, true, NO_RECORD_DEF, "" },
    { "tftp-servers", DOCSIS3_V4_TFTP_SERVERS, OPT_IPV4_ADDRESS_TYPE, true, NO_RECORD_DEF, "" }
};

/// Number of option definitions defined.
const int DOCSIS3_V4_DEFS_SIZE  = sizeof(DOCSIS3_V4_DEFS) / sizeof(OptionDefParams);

/// @todo define remaining docsis3 v6 codes
#define DOCSIS3_V6_ORO 1
#define DOCSIS3_V6_DEVICE_TYPE 2
#define DOCSIS3_V6_VENDOR_NAME 10
#define DOCSIS3_V6_TFTP_SERVERS 32
#define DOCSIS3_V6_CONFIG_FILE 33
#define DOCSIS3_V6_SYSLOG_SERVERS 34
#define DOCSIS3_V6_DEVICE_ID 36
#define DOCSIS3_V6_TIME_SERVERS 37
#define DOCSIS3_V6_TIME_OFFSET 38

// The following DOCSIS3 options are inserted by the CMTS (which acts as
// a relay agent)
#define DOCSIS3_V6_CMTS_CM_MAC 1026

/// @brief Definitions of standard DHCPv6 options.
const OptionDefParams DOCSIS3_V6_DEFS[] = {
    { "oro",            DOCSIS3_V6_ORO, OPT_UINT16_TYPE, true, NO_RECORD_DEF, "" },
    { "device-type",    DOCSIS3_V6_DEVICE_TYPE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "vendor-type",    DOCSIS3_V6_VENDOR_NAME, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "tftp-servers",   DOCSIS3_V6_TFTP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "time-servers",   DOCSIS3_V6_TIME_SERVERS, OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "config-file",    DOCSIS3_V6_CONFIG_FILE, OPT_STRING_TYPE, false, NO_RECORD_DEF, "" },
    { "syslog-servers", DOCSIS3_V6_SYSLOG_SERVERS, OPT_IPV6_ADDRESS_TYPE, true, NO_RECORD_DEF, "" },
    { "device-id",      DOCSIS3_V6_DEVICE_ID, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" },
    { "time-offset",    DOCSIS3_V6_TIME_OFFSET, OPT_INT32_TYPE, false, NO_RECORD_DEF, "" },
    { "cmts-cm-mac",    DOCSIS3_V6_CMTS_CM_MAC, OPT_BINARY_TYPE, false, NO_RECORD_DEF, "" }
    // @todo add definitions for all remaning options.
};

/// Number of option definitions defined.
const int DOCSIS3_V6_DEFS_SIZE  = sizeof(DOCSIS3_V6_DEFS) / sizeof(OptionDefParams);

/// The class as specified in vendor-class option by the devices
extern const char* DOCSIS3_CLASS_EROUTER;
extern const char* DOCSIS3_CLASS_MODEM;

}; // isc::dhcp namespace
}; // isc namespace

#endif // DOCSIS3_OPTION_DEFS_H
