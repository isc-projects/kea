// Copyright (C) 2013,2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef USER_CHK_LOG_H
#define USER_CHK_LOG_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <user_chk_messages.h>

namespace user_chk {

/// @brief User Check Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger user_chk_logger;

} // end of namespace user_chk

#endif // USER_CHK_LOG_H
