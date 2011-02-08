// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __XDEBUGLEVEL_H
#define __XDEBUGLEVEL_H

#include <syslog.h>
#include <log4cxx/level.h>

#include <dbglevels.h>

namespace log4cxx {

/// \brief Debug Extension to Level Class
///
/// Based on the example given in the log4cxx distribution, this extends the
/// log4cxx Level class to allow 100 debug levels.
///
/// First some terminology, as the use of the term "level" gets confusing.  The
/// code and comments here use the term "level" in two contexts:
///
/// Logging level: The category of messages to log.  By default log4cxx defines
/// the following logging levels: OFF, FATAL, ERROR, WARNING, INFO, DEBUG,
/// TRACE, ALL.  Within the context of BIND-10, OFF, TRACE and ALL are not used
/// and the idea of DEBUG has been extended, as will be seen below.
///
/// Debug level: This is a number that ranges from 0 to 99 and is used by the
/// application to control the detail of debug output.  A value of 0 gives the
/// highest-level debug output; a value of 99 gives the most verbose and most
/// detailed. Debug messages (or whatever debug level) are only ever output
/// when the logging level is set to DEBUG.
///
///
/// With log4cxx, the various logging levels have a numeric value associated
/// with them, such that FATAL > ERROR > WARNING etc.  This suggests that the
/// idea of debug levels can be incorporated into the existing logging level
/// scheme by assigning them appropriate numeric values, i.e.
///
/// WARNING > INFO > DEBUG(0) > DEBUG(2) > ... > DEBUG(99)
///
/// Setting a numeric level of DEBUG enables the basic messages; setting lower
/// numeric levels will enable progressively more messages.  The lowest debug
/// level (0) is chosen such that setting the general DEBUG logging level will
/// automatically select that debug level.
///
/// This sub-class is needed because the log4cxx::Level class does not allow
/// the setting of the numeric value of the current level to something other
/// than the values enumerated in the class.  It creates a set of log4cxx
/// logging levels to correspond to the various debug levels.  These levels have
/// names in the range DEBUG1 to DEBUG99 (the existing Level DEBUG is used for
/// a debug level of 0), although they are not used in BIND-10: instead the
/// BIND-10 Logger class treats the logging levels and debug levels separately
/// and combines them to choose the underlying log4cxx logging level.


/// \brief Debug-Extended Level

class XDebugLevel : public Level {
    DECLARE_LOG4CXX_LEVEL(XDebugLevel)

    /// Array of pointers to logging level objects, one for each debug level.
    /// The pointer corresponding to a debug level of 0 points to the DEBUG
    /// logging level object.
    static LevelPtr dbglevels_[NUM_DEBUG_LEVEL];
    static bool     dbglevels_unset_;

public:

    // Minimum and maximum debug levels.  Note that XDEBUG_MIN_LEVEL_INT is the
    // number corresponding to the minimum debug level - and is actually larger
    // that XDEBUG_MAX_LEVEL_INT, the number corresponding to the maximum debug
    // level.
    enum {
        XDEBUG_MIN_LEVEL_INT = Level::DEBUG_INT - MIN_DEBUG_LEVEL,
        XDEBUG_MAX_LEVEL_INT = Level::DEBUG_INT - MAX_DEBUG_LEVEL
    };

    /// \brief Constructor
    ///
    /// \param level Numeric value of the logging level.
    /// \param name Name given to this logging level.
    /// \param syslogEquivalent The category to be used by syslog when it logs
    /// an event associated with the specified logging level.
    XDebugLevel(int level, const LogString& name, int syslogEquivalent) :
        Level(level, name, syslogEquivalent)
    {}

    /// \brief Create Logging Level Object
    ///
    /// Creates a logging level object corresponding to one of the debug levels.
    ///
    /// \param dbglevel The debug level, which ranges from MIN_DEBUG_LEVEL to
    /// MAX_DEBUG_LEVEL. It is coerced to that range if it lies outside it.
    ///
    /// \return Pointer to the desired logging level object.
    static LevelPtr getExtendedDebug(int dbglevel);

    /// \brief Convert Integer to a Logging Level
    ///
    /// Returns a logging level object corresponding to the given value (which
    /// is an absolute value of a logging level - it is not a debug level).
    /// If the number is invalid, an object of logging level DEBUG (the
    /// minimum debug logging level) is returned.
    ///
    /// \param val Number to convert to a logging level.  This is an absolute
    /// logging level number, not a debug level.
    ///
    /// \return Pointer to the desired logging level object.
    static LevelPtr toLevel(int val);

    /// \brief Convert Integer to a Level
    ///
    /// Returns a logging level object corresponding to the given value (which
    /// is an absolute value of a logging level - it is not a debug level).
    /// If the number is invalid, the given default is returned.
    ///
    /// \param val Number to convert to a logging level.  This is an absolute
    /// logging level number, not a debug level.
    /// \param defaultLevel Logging level to return if value is not recognised.
    ///
    /// \return Pointer to the desired logging level object.
    static LevelPtr toLevel(int val, const LevelPtr& defaultLevel);

    /// \brief Convert String to Logging Level
    ///
    /// Returns a logging level object corresponding to the given name.  If the
    /// name is invalid, an object of logging level DEBUG (the minimum debug
    /// logging level) is returned.
    ///
    /// \param sArg Name of the logging level.
    ///
    /// \return Pointer to the desired logging level object.
    static LevelPtr toLevelLS(const LogString& sArg);

    /// \brief Convert String to Logging Level
    ///
    /// Returns a logging level object corresponding to the given name.  If the
    /// name is invalid, the given default is returned.
    ///
    /// \param sArg name of the level.
    /// \param defaultLevel Logging level to return if name doesn't exist.
    ///
    /// \return Pointer to the desired logging level object.
    static LevelPtr toLevelLS(const LogString& sArg,
        const LevelPtr& defaultLevel);
};

} // namespace log4cxx


#endif // __XDEBUGLEVEL_H
