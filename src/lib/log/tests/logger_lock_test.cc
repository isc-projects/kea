// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
