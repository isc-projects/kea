// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

/// Defines the logger used by the top-level component of kea-dhcp-ddns.

#include <d2/d2_log.h>

namespace isc {
namespace d2 {

/// @brief Defines the logger used within D2.
isc::log::Logger dctl_logger("dhcpddns");
isc::log::Logger dhcp_to_d2_logger("dhcp-to-d2");
isc::log::Logger d2_to_dns_logger("d2-to-dns");

} // namespace d2
} // namespace isc

