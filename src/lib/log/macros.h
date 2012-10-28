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

#ifndef LOG_MACROS_H
#define LOG_MACROS_H

#include <log/logger.h>
#include <log/log_dbglevels.h>

/// \brief Macro to conveniently test debug output and log it
#define LOG_DEBUG(LOGGER, LEVEL, MESSAGE) \
    if (!(LOGGER).isDebugEnabled((LEVEL))) { \
    } else \
        (LOGGER).debug((LEVEL), (MESSAGE))

/// \brief Macro to conveniently test info output and log it
#define LOG_INFO(LOGGER, MESSAGE) \
    if (!(LOGGER).isInfoEnabled()) { \
    } else \
        (LOGGER).info((MESSAGE))

/// \brief Macro to conveniently test warn output and log it
#define LOG_WARN(LOGGER, MESSAGE) \
    if (!(LOGGER).isWarnEnabled()) { \
    } else \
        (LOGGER).warn((MESSAGE))

/// \brief Macro to conveniently test error output and log it
#define LOG_ERROR(LOGGER, MESSAGE) \
    if (!(LOGGER).isErrorEnabled()) { \
    } else \
        (LOGGER).error((MESSAGE))

/// \brief Macro to conveniently test fatal output and log it
#define LOG_FATAL(LOGGER, MESSAGE) \
    if (!(LOGGER).isFatalEnabled()) { \
    } else \
        (LOGGER).fatal((MESSAGE))

#endif
