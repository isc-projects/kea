// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
