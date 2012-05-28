// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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
#include "util/interprocess_sync.h"
#include "log_test_messages.h"
#include <iostream>

using namespace std;
using namespace isc::log;

class MockLoggingSync : public isc::util::InterprocessSync {
public:
    /// \brief Constructor
    MockLoggingSync(const std::string& component_name) :
        InterprocessSync(component_name)
    {}

protected:
    bool lock() {
        cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: LOCK\n";
        return (true);
    }

    bool tryLock() {
        cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: TRYLOCK\n";
        return (true);
    }

    bool unlock() {
        cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: UNLOCK\n";
        return (true);
    }
};

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
    logger.setInterprocessSync(new MockLoggingSync("log"));

    LOG_INFO(logger, LOG_LOCK_TEST_MESSAGE);

    return (0);
}
