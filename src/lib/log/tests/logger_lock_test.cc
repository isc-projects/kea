// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <log/logger_manager.h>
#include <log/log_messages.h>
#include <log/interprocess/interprocess_sync.h>
#include <log/tests/log_test_messages.h>

#include <util/threads/sync.h>
#include <iostream>

using namespace std;
using namespace isc::log;
using isc::util::thread::Mutex;

class MockLoggingSync : public isc::log::interprocess::InterprocessSync {
public:
    /// \brief Constructor
    MockLoggingSync(const std::string& component_name) :
        InterprocessSync(component_name)
    {}

protected:
    virtual bool lock() {
        // We first check if the logger acquired a lock on the
        // LoggerManager mutex.
        try {
            // This lock attempt is non-blocking.
            Mutex::Locker locker(LoggerManager::getMutex(), false);
        } catch (Mutex::Locker::AlreadyLocked&) {
            cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: MUTEXLOCK\n";
        }

        cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: LOCK\n";
        return (true);
    }

    virtual bool tryLock() {
        cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: TRYLOCK\n";
        return (true);
    }

    virtual bool unlock() {
        cout << "FIELD1 FIELD2 LOGGER_LOCK_TEST: UNLOCK\n";
        return (true);
    }
};

/// \brief Test logger lock sequence
///
/// A program used in testing the logger. It verifies that (1) an
/// interprocess sync lock is first acquired by the logger, (2) the
/// message is logged by the logger, and (3) the lock is released in
/// that sequence.
int
main(int, char**) {
    initLogger();
    Logger logger("log");
    logger.setInterprocessSync(new MockLoggingSync("log"));

    LOG_INFO(logger, LOG_LOCK_TEST_MESSAGE);

    return (0);
}
