// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEGAL_LOG_LOG_H
#define LEGAL_LOG_LOG_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <legal_log_messages.h>

namespace isc{
namespace legal_log {

/// @brief Legal Log Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger legal_log_logger;

} // end of namespace legal_log
} // end of namespace isc

#endif // LEGAL_LOG_LOG_H
