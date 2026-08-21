// Copyright (C) 2017-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FLEX_ID_H
#define FLEX_ID_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <flex_id_messages.h>

namespace isc {
namespace flex_id {

/// @brief Stores expression
///
/// @param v6 Indicates if the expression refers to IPv6 or IPv4 case.
/// @param expr Expression in textual form.
/// @param apply_to_leases Indicates if flexible identifier should be used to
/// replace client supplied client identifier or DUID.
/// @param ignore_iaid Indicates if IAID should be ignored.
/// @param cid_as_rfc4361_duid format v4 id expression results
/// as an RFC4361 embedded duid.  Ignored for v6 packets.
void storeConfiguration(bool v6, const std::string& expr,
                        const bool apply_to_leases,
                        const bool ignore_iaid,
                        const bool cid_as_rfc4361_duid = false);

/// @brief Clears stored configuration.
///
/// This is mostly useful between tests.
void clearConfiguration();

} // end of namespace flex_id
} // end of namespace isc

#endif // FLEX_ID_H
