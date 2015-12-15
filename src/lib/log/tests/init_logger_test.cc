// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/macros.h>
#include <log/logger_support.h>
#include <log/log_messages.h>

using namespace isc::log;

/// \brief Test InitLogger
///
/// A program used in testing the logger that initializes logging using
/// initLogger(), then outputs several messages at different severities and
/// debug levels.  An external script sets the environment variables and checks
/// that they have the desired effect.

int
main(int, char**) {
    initLogger();
    Logger logger("log");

    LOG_DEBUG(logger, 0, LOG_BAD_DESTINATION).arg("debug-0");
    LOG_DEBUG(logger, 50, LOG_BAD_DESTINATION).arg("debug-50");
    LOG_DEBUG(logger, 99, LOG_BAD_DESTINATION).arg("debug-99");
    LOG_INFO(logger, LOG_BAD_SEVERITY).arg("info");
    LOG_WARN(logger, LOG_BAD_STREAM).arg("warn");
    LOG_ERROR(logger, LOG_DUPLICATE_MESSAGE_ID).arg("error");
    LOG_FATAL(logger, LOG_NO_MESSAGE_ID).arg("fatal");

    return (0);
}
