// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
