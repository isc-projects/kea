// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <log/macros.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <log/log_messages.h>
#include <log/interprocess/interprocess_sync.h>
#include <log/tests/log_test_messages.h>

#include <mutex>
#include <iostream>

#include <boost/noncopyable.hpp>

using namespace std;
using namespace isc::log;

/// \brief RAII safe mutex checker.
class CheckMutex : boost::noncopyable {
public:
    /// \brief Exception thrown when the mutex is already locked.
    struct AlreadyLocked : public isc::InvalidParameter {
        AlreadyLocked(const char* file, size_t line, const char* what) :
            isc::InvalidParameter(file, line, what)
        {}
    };

    /// \brief Constructor.
    ///
    /// \throw AlreadyLocked if the mutex is already locked.
    CheckMutex(mutex& mutex) : mutex_(mutex) {
        if (!mutex.try_lock()) {
            isc_throw(AlreadyLocked, "The mutex is already locked");
        }
    }

    /// \brief Destructor.
    ///
    /// Unlocks the mutex.
    ~CheckMutex() {
        mutex_.unlock();
    }

private:
    mutex& mutex_;
};

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
            CheckMutex check(LoggerManager::getMutex());
        } catch (const CheckMutex::AlreadyLocked&) {
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
