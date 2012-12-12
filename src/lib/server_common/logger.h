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

#ifndef SERVER_COMMON_LOGGER_H
#define SERVER_COMMON_LOGGER_H

#include <log/macros.h>
#include <server_common/server_common_messages.h>

/// \file server_common/logger.h
/// \brief Server Common library global logger
///
/// This holds the logger for the server common library. It is a private header
/// and should not be included in any publicly used header, only in local
/// cc files.

namespace isc {
namespace server_common {

/// \brief The logger for this library
extern isc::log::Logger logger;

/// \brief Trace basic operations
const int DBG_TRACE_BASIC = DBGLVL_TRACE_BASIC;

/// \brief Print also values used
const int DBG_TRACE_VALUES = DBGLVL_TRACE_BASIC_DATA;

}
}

#endif
