// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @file dhcp6_log.cc
/// Contains the loggers used by the DHCPv6 server component.

#include <dhcp6/dhcp6_log.h>

namespace isc {
namespace dhcp {

const char* DHCP6_ROOT_LOGGER_NAME = "kea-dhcp6";
const char* DHCP6_APP_LOGGER_NAME = "dhcp6";
const char* DHCP6_BAD_PACKET_LOGGER_NAME = "bad-packets";
const char* DHCP6_PACKET_LOGGER_NAME = "packets";
const char* DHCP6_OPTIONS_LOGGER_NAME = "options";
const char* DHCP6_DDNS_LOGGER_NAME = "ddns";
const char* DHCP6_LEASE_LOGGER_NAME = "leases";

isc::log::Logger dhcp6_logger(DHCP6_APP_LOGGER_NAME);
isc::log::Logger bad_packet_logger(DHCP6_BAD_PACKET_LOGGER_NAME);
isc::log::Logger packet_logger(DHCP6_PACKET_LOGGER_NAME);
isc::log::Logger options_logger(DHCP6_OPTIONS_LOGGER_NAME);
isc::log::Logger ddns_logger(DHCP6_DDNS_LOGGER_NAME);
isc::log::Logger lease_logger(DHCP6_LEASE_LOGGER_NAME);

} // namespace dhcp
} // namespace isc

