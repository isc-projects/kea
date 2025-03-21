// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
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
void storeConfiguration(bool v6, const std::string& expr,
                        const bool apply_to_leases,
                        const bool ignore_iaid);

/// @brief Clears stored configuration.
///
/// This is mostly useful between tests.
void clearConfiguration();

} // end of namespace flex_id
} // end of namespace isc

#endif // FLEX_ID_H
