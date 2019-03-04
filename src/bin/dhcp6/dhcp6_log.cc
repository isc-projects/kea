// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file dhcp6_log.cc
/// Contains the loggers used by the DHCPv6 server component.

#include <config.h>

#include <dhcp6/dhcp6_log.h>

namespace isc {
namespace dhcp {

extern const int DBG_DHCP6_START = isc::log::DBGLVL_START_SHUT;
extern const int DBG_DHCP6_SHUT = isc::log::DBGLVL_START_SHUT;
extern const int DBG_DHCP6_COMMAND = isc::log::DBGLVL_COMMAND;
extern const int DBG_DHCP6_BASIC = isc::log::DBGLVL_TRACE_BASIC;
extern const int DBG_DHCP6_HOOKS = isc::log::DBGLVL_TRACE_BASIC;
extern const int DBG_DHCP6_BASIC_DATA = isc::log::DBGLVL_TRACE_BASIC_DATA;
extern const int DBG_DHCP6_DETAIL = isc::log::DBGLVL_TRACE_DETAIL;
extern const int DBG_DHCP6_DETAIL_DATA = isc::log::DBGLVL_TRACE_DETAIL_DATA;

const char* DHCP6_ROOT_LOGGER_NAME = "kea-dhcp6";
const char* DHCP6_APP_LOGGER_NAME = "dhcp6";
const char* DHCP6_BAD_PACKET_LOGGER_NAME = "bad-packets";
const char* DHCP6_PACKET_LOGGER_NAME = "packets";
const char* DHCP6_OPTIONS_LOGGER_NAME = "options";
const char* DHCP6_DDNS_LOGGER_NAME = "ddns";
const char* DHCP6_LEASE_LOGGER_NAME = "leases";

isc::log::Logger dhcp6_logger(DHCP6_APP_LOGGER_NAME);
isc::log::Logger bad_packet6_logger(DHCP6_BAD_PACKET_LOGGER_NAME);
isc::log::Logger packet6_logger(DHCP6_PACKET_LOGGER_NAME);
isc::log::Logger options6_logger(DHCP6_OPTIONS_LOGGER_NAME);
isc::log::Logger ddns6_logger(DHCP6_DDNS_LOGGER_NAME);
isc::log::Logger lease6_logger(DHCP6_LEASE_LOGGER_NAME);

} // namespace dhcp
} // namespace isc

