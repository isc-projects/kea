// Copyright (C) 2012, 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @file dhcp4_log.cc
/// Contains the loggers used by the DHCPv4 server component.

#include <dhcp4/dhcp4_log.h>

namespace isc {
namespace dhcp {

const char* DHCP4_ROOT_LOGGER_NAME = "kea-dhcp4";
const char* DHCP4_APP_LOGGER_NAME = "dhcp4";
const char* DHCP4_BAD_PACKET_LOGGER_NAME = "bad-packet";
const char* DHCP4_PACKET_LOGGER_NAME = "packet";
const char* DHCP4_OPTIONS_LOGGER_NAME = "options";
const char* DHCP4_HOSTNAME_LOGGER_NAME = "hostname";
const char* DHCP4_LEASE_LOGGER_NAME = "lease";
const char* DHCP4_SRV_HOOKS_LOGGER_NAME = "server-hooks";

isc::log::Logger dhcp4_logger(DHCP4_APP_LOGGER_NAME);
isc::log::Logger bad_packet_logger(DHCP4_BAD_PACKET_LOGGER_NAME);
isc::log::Logger packet_logger(DHCP4_PACKET_LOGGER_NAME);
isc::log::Logger options_logger(DHCP4_OPTIONS_LOGGER_NAME);
isc::log::Logger hostname_logger(DHCP4_HOSTNAME_LOGGER_NAME);
isc::log::Logger lease_logger(DHCP4_LEASE_LOGGER_NAME);
isc::log::Logger srv_hooks_logger(DHCP4_SRV_HOOKS_LOGGER_NAME);

} // namespace dhcp
} // namespace isc

