// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_UTILS_H
#define RADIUS_UTILS_H

#include <dhcp/duid.h>

namespace isc {
namespace radius {

/// @brief Canonize hardware address textual representation.
///
/// FreeRADIUS prefers lowercase with '-' as the separator so
/// translate 0A:0B:01:02:03 into 0a-0b-01-02-03.
///
/// @param hexdump The dump in hexadecimal with ':' separator.
/// @return The argument in canonical format.
std::string canonize(const std::string& hexdump);

/// @brief Pop leading zero in a DHCPv4 client-id.
///
/// flex-id uses client-id with type field (leading byte) set to 0.
///
/// @param client_id Pointer to the client id.
/// @return A vector holding a client identifier without leading zero
/// if exists.
std::vector<uint8_t> pop0(const dhcp::ClientIdPtr& client_id);

/// @brief Pop leading zeros in a DHCPv6 duid.
///
/// flex-id uses duid with type field (leading 2 bytes) set to 0.
///
/// @param duid Pointer to the duid.
std::vector<uint8_t> pop0(const dhcp::DuidPtr& duid);

/// @brief Return printable textual representation of a vector.
///
/// @param content The vector from a client-id or a duid.
/// @return The textual or hexadecimal representation.
std::string toPrintable(const std::vector<uint8_t>& content);

/// @brief Return hexadecimal textual representation of a vector.
///
/// @param content The vector from a client-id or a duid.
/// @return The hexadecimal representation.
std::string toHex(const std::vector<uint8_t>& content);

/// @brief Extract the duid from a RFC 4361 compliant DHCPv4 client ID.
///
/// @param client_id Pointer to the client id.
/// @param extracted a reference to a boolean which is set to true when
///                  a DUID was extracted.
/// @return A vector holding the duid or the client identifier itself.
std::vector<uint8_t> extractDuid(const dhcp::ClientIdPtr& client_id,
                                 bool& extracted);

} // end of namespace isc::radius
} // end of namespace isc

#endif
