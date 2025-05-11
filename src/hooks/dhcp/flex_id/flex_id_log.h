// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FLEX_ID_LOG_H
#define FLEX_ID_LOG_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <flex_id_messages.h>

namespace isc {
namespace flex_id {

/// @brief Flexible Identifier Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger flex_id_logger;

} // end of namespace flex_id
} // end of namespace isc

#endif // FLEX_ID_LOG_H
