// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <log/log_formatter.h>

#include <cassert>

#ifdef ENABLE_LOGGER_CHECKS
#include <iostream>
#endif

using namespace std;
using namespace boost;

namespace isc {
namespace log {

void
replacePlaceholder(string* message, const string& arg,
                   const unsigned placeholder)
{
    const string mark("%" + lexical_cast<string>(placeholder));
    size_t pos(message->find(mark));
    if (pos != string::npos) {
        do {
            message->replace(pos, mark.size(), arg);
            pos = message->find(mark, pos + arg.size());
        } while (pos != string::npos);
    }
#ifdef ENABLE_LOGGER_CHECKS
    else {
        // We're missing the placeholder, so throw an exception
        isc_throw(MismatchedPlaceholders,
                  "Missing logger placeholder in message: " << *message);
    }
#else
    else {
        // We're missing the placeholder, so add some complain
        message->append(" @@Missing placeholder " + mark + " for '" + arg + "'@@");
    }
#endif /* ENABLE_LOGGER_CHECKS */
}

void
checkExcessPlaceholders(string* message, unsigned int placeholder) {
    const string mark("%" + lexical_cast<string>(placeholder));
    const size_t pos(message->find(mark));
    if (pos != string::npos) {
        // Excess placeholders were found.  If we enable the harsh check,
        // abort it.  Note: ideally we'd like to throw MismatchedPlaceholders,
        // but we can't at least for now because this function is called from
        // the Formatter's destructor.
#ifdef ENABLE_LOGGER_CHECKS
        // Also, make sure we print the message so we can identify which
        // identifier has the problem.
        cerr << "Message " << *message << endl;
        assert("Excess logger placeholders still exist in message" == NULL);
#else
        message->append(" @@Excess logger placeholders still exist@@");
#endif /* ENABLE_LOGGER_CHECKS */
    }
}

}
}
