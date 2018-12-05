// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file dhcp4_log.cc
/// Contains the loggers used by the DHCPv4 server component.

#include <config.h>

#include <dhcp4/dhcp4_log.h>

namespace isc {
namespace dhcp {

extern const int DBG_DHCP4_START = isc::log::DBGLVL_START_SHUT;
extern const int DBG_DHCP4_SHUT = isc::log::DBGLVL_START_SHUT;
extern const int DBG_DHCP4_COMMAND = isc::log::DBGLVL_COMMAND;
extern const int DBG_DHCP4_BASIC = isc::log::DBGLVL_TRACE_BASIC;
extern const int DBG_DHCP4_HOOKS = isc::log::DBGLVL_TRACE_BASIC;
extern const int DBG_DHCP4_BASIC_DATA = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int DBG_DHCP4_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
extern const int DBG_DHCP4_DETAIL_DATA = isc::log::DBGLVL_TRACE_DETAIL_DATA;

const char* DHCP4_ROOT_LOGGER_NAME = "kea-dhcp4";
const char* DHCP4_APP_LOGGER_NAME = "dhcp4";
const char* DHCP4_BAD_PACKET_LOGGER_NAME = "bad-packets";
const char* DHCP4_PACKET_LOGGER_NAME = "packets";
const char* DHCP4_OPTIONS_LOGGER_NAME = "options";
const char* DHCP4_DDNS_LOGGER_NAME = "ddns";
const char* DHCP4_LEASE_LOGGER_NAME = "leases";

isc::log::Logger dhcp4_logger(DHCP4_APP_LOGGER_NAME);
isc::log::Logger bad_packet4_logger(DHCP4_BAD_PACKET_LOGGER_NAME);
isc::log::Logger packet4_logger(DHCP4_PACKET_LOGGER_NAME);
isc::log::Logger options4_logger(DHCP4_OPTIONS_LOGGER_NAME);
isc::log::Logger ddns4_logger(DHCP4_DDNS_LOGGER_NAME);
isc::log::Logger lease4_logger(DHCP4_LEASE_LOGGER_NAME);

} // namespace dhcp
} // namespace isc

