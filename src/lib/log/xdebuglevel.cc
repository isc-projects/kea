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
 
#include <cassert>
#include <algorithm>
#include <syslog.h>
#include <string.h>
#include <boost/lexical_cast.hpp>

#include <xdebuglevel.h>
#include <debug_levels.h>
#include <log4cxx/helpers/stringhelper.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

// Storage for the logging level objects corresponding to each debug level

bool XDebugLevel::dbglevels_unset_ = true;
LevelPtr XDebugLevel::dbglevels_[NUM_DEBUG_LEVEL];

// Register the class

IMPLEMENT_LOG4CXX_LEVEL(XDebugLevel)


// Create Extended Debug Level Objects

LevelPtr
XDebugLevel::getExtendedDebug(int level) {

    // Initialize the logging levels corresponding to the possible range of
    // debug if we have not already done so
    if (dbglevels_unset_) {

        // Asserting that the minimum debug level is zero - so corresponds
        // to DEBUG_INT - means that the lowest level is set to main DEBUG
        // level.  This means that the existing logging level object can be
        // used.
        assert(MIN_DEBUG_LEVEL == 0);
        dbglevels_[0] = Level::getDebug();

        // Create the logging level objects for the rest of the debug levels.
        // They are given names of the form DEBUG<debug level> (e.g. DEBUG42).
        // They will all correspond to a syslog level of DEBUG.
        for (int i = 1; i < NUM_DEBUG_LEVEL; ++i) {
            std::string name = std::string("DEBUG") +
                boost::lexical_cast<std::string>(i);
            dbglevels_[i] = new XDebugLevel(
                (XDebugLevel::XDEBUG_MIN_LEVEL_INT - i),
                LOG4CXX_STR(name.c_str()), LOG_DEBUG);
        }
        dbglevels_unset_ = false;
    }

    // Now get the logging level object asked for.  Coerce the debug level to
    // lie in the acceptable range.
    int actual = std::max(MIN_DEBUG_LEVEL, std::min(MAX_DEBUG_LEVEL, level));

    // ... and return a pointer to the appropriate logging level object
    return (dbglevels_[actual - MIN_DEBUG_LEVEL]);
}

// Convert an integer (an absolute logging level number, not a debug level) to a
// logging level object.  If it lies outside the valid range, an object
// corresponding to the minimum debug value is returned.

LevelPtr
XDebugLevel::toLevel(int val) {
    return (toLevel(val, getExtendedDebug(MIN_DEBUG_LEVEL)));
}

LevelPtr
XDebugLevel::toLevel(int val, const LevelPtr& defaultLevel) {

    // Note the reversal of the notion of MIN and MAX - see the header file for
    // details.
    if ((val >= XDEBUG_MAX_LEVEL_INT) && (val <= XDEBUG_MIN_LEVEL_INT)) {
        return (getExtendedDebug(XDEBUG_MIN_LEVEL_INT - val));
    }
    else {
        return (defaultLevel);
    }
}

// Convert string passed to a logging level or return default level.

LevelPtr
XDebugLevel::toLevelLS(const LogString& sArg) {
    return (toLevelLS(sArg, getExtendedDebug(0)));
}

LevelPtr
XDebugLevel::toLevelLS(const LogString& sArg, const LevelPtr& defaultLevel) {
    std::string name = sArg;        // Get to known type
    size_t length = name.size();    // Length of the string

    if (length < 5) {

        // String can't possibly start DEBUG so we don't know what it is.
        return (defaultLevel);
    }
    else {
        if (strncasecmp(name.c_str(), "DEBUG", 5) == 0) {

            // String starts "DEBUG" (or "debug" or any case mixture).  The
            // rest of the string -if any - should be a number.
            if (length == 5) {

                // It is plain "DEBUG".  Take this as level 0.
                return (getExtendedDebug(0));
            }
            else {

                // Try converting the remainder to an integer.  The "5" is
                // the length of the string "DEBUG".  Note that if the number
                // is outside the rangeof debug levels, it is coerced to the
                // nearest limit.  Thus a level of DEBUG509 will end up as
                // if DEBUG99 has been specified.
                try {
                    int level = boost::lexical_cast<int>(name.substr(5));
                    return (getExtendedDebug(level));
                }
                catch ((boost::bad_lexical_cast&) ){
                    return (defaultLevel);
                }
            }
        }
        else {

            // Unknown string - return default.
            return (defaultLevel);
        }
    }
}
