// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOG_DBGLVLS_H
#define LOG_DBGLVLS_H

/// \file
///
/// When a message is logged with DEBUG severity, the debug level associated
/// with the message is also specified.  This debug level is a number
/// ranging from 0 to 99; the idea is that the higher the debug level, the
/// more detailed the message.
///
/// If debug messages are being logged, the logging system allows them to be
/// filtered by debug level - only messages logged with a level equal to or
/// less than the set debug level will be output.  (For example, if the
/// filter is set to 30, only debug messages logged with levels in the range
/// 0 to 30 will be output; messages logged with levels 31 to 99 will be
/// suppressed.)
///
/// Levels of 30 or below are reserved for debug messages that are most
/// likely to be useful for an administrator. Levels 31 to 99 are for use by
/// someone familiar with the code. "Useful for an administrator" is,
/// admittedly, a subjective term: it is loosely defined as messages helping
/// someone diagnose a problem that they could solve without needing to dive
/// into the code.  So it covers things like start-up steps and configuration
/// messages.
///
/// In practice, this means that levels of 30 and below are most-likely to
/// be used by the top-level programs, and 31 and above by the various
/// libraries.
///
/// This file defines a set of standard debug levels for use across all loggers.
/// In this way users can have some expectation of what will be output when
/// enabling debugging.  Symbols are prefixed DBGLVL so as not to clash with
/// DBG_ symbols in the various modules.

namespace isc {
namespace log {

/// Process startup/shutdown debug messages.  Note that these are _debug_
/// messages, as other messages related to startup and shutdown may be output
/// with another severity.  For example, when the authoritative server starts
/// up, the "server started" message could be output at a severity of INFO.
/// "Server starting" and messages indicating the stages in startup should be
/// debug messages output at this severity.
extern const int DBGLVL_START_SHUT;

/// This debug level is reserved for logging the exchange of messages/commands
/// between processes, including configuration messages.
extern const int DBGLVL_COMMAND;

/// This debug level is reserved for logging the details of packet handling, such
/// as dropping the packet for various reasons.
extern const int DBGLVL_PKT_HANDLING;

/// If the commands have associated data, this level is when they are printed.
/// This includes configuration messages.
extern const int DBGLVL_COMMAND_DATA;

// The following constants are suggested values for common operations.
// Depending on the exact nature of the code, modules may or may not use these
// levels.

/// Trace basic operations.
extern const int DBGLVL_TRACE_BASIC;

/// Trace data associated with the basic operations.
extern const int DBGLVL_TRACE_BASIC_DATA;

/// Trace detailed operations.
extern const int DBGLVL_TRACE_DETAIL;

/// Trace data associated with detailed operations.
extern const int DBGLVL_TRACE_DETAIL_DATA;

}   // log namespace
}   // isc namespace

#endif // LOG_DBGLVLS_H
