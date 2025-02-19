// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/multi_threading_mgr.h>
#include <gtest/gtest.h>
#include <functional>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief Test fixture class for @c NetworkState class.
class NetworkStateTest : public ::testing::Test {
public:

    /// @brief Constructor.
    NetworkStateTest()
        : io_service_(new IOService()) {
        TimerMgr::instance()->unregisterTimers();
        TimerMgr::instance()->setIOService(io_service_);
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    virtual ~NetworkStateTest() {
        // Cancel timers.
        TimerMgr::instance()->unregisterTimers();
        // Make sure IO service will stop when no timers are scheduled.
        io_service_->stopWork();
        // Run outstanding tasks.
        io_service_->run();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief This test verifies the default is enable state.
    void defaultTest();

    /// @brief This test verifies that it is possible to disable and then enable
    /// service using 'user command' origin.
    void disableEnableServiceUsingUserCommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable
    /// service using 'HA local command' origin.
    void disableEnableServiceUsingHALocalCommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable
    /// service using 'HA remote command' origin.
    void disableEnableServiceUsingHARemoteCommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable
    /// service using 'DB connection' origin.
    void disableEnableServiceUsingDBConnectionOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable
    /// service using a combination of origins.
    // 1. Disable using 'user command' origin 2 times (expect disabled state).
    // 2. Disable using 'HA local command' origin 2 times (expect disabled state).
    // 3. Disable using 'HA local command' origin 1 time different id (expect disabled state).
    // 4. Disable using 'HA remote command' origin 2 times (expect disabled state).
    // 5. Disable using 'HA remote command' origin 1 time different id (expect disabled state).
    // 6. Disable using 'DB connection' origin 2 times (expect disabled state).
    // 7. Disable using 'DB connection' origin 1 time different id (expect disabled state).
    // 8. Enable using 'user command' origin 1 time (expect disabled state).
    // 9. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 10. Enable using 'HA local command' origin 1 time different id (expect disabled state).
    // 11. Enable using 'HA remote command' origin 1 time (expect disabled state).
    // 12. Enable using 'HA remote command' origin 1 time different id (expect disabled state).
    // 13. Enable using 'DB connection' origin 1 times (expect disabled state).
    // 14. Enable using 'DB connection' origin 1 time different id (expect disabled state).
    void disableEnableServiceUsingMultipleOriginsTest();

    /// @brief This test verifies that reset works, so that internal state is reset after
    /// all managers are recreated.
    /// 1. Disable using 'user command' origin 3 times (expect disabled state).
    /// 2. Disable using 'HA command' origin 1 time (expect disabled state).
    /// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
    /// 4. Reset using 'user command' origin (expect disabled state).
    /// 5. Enable using 'HA command' origin 1 time (expect disabled state).
    /// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
    /// 7. Disable using 'user command' origin 3 times (expect disabled state).
    /// 8. Reset using 'user command' origin (expect enabled state).
    void resetUsingUserCommandOriginTest();

    /// @brief This test verifies that reset works, so that internal state is reset after
    /// all managers are recreated.
    // 1. Disable using 'user command' origin 1 time (expect disabled state).
    // 2. Disable using 'HA local command' origin 3 times with same id (expect disabled state).
    // 3. Disable using 'DB connection' origin 1 time (expect disabled state).
    // 4. Disable using 'HA remote command' origin 1 time (expect disabled state).
    // 5. Enable using 'HA local command' origin (expect disabled state).
    // 6. Enable using 'user command' origin 1 time (expect disabled state).
    // 7. Enable using 'HA remote command' origin 1 time (expect disabled state).
    // 8. Enable using 'DB connection' origin 1 time (expect enabled state).
    // 9. Disable using 'user command' origin 1 time (expect disabled state).
    // 10. Disable using 'HA local command' origin 3 times with different ids (expect disabled state).
    // 11. Disable using 'DB connection' origin 1 time (expect disabled state).
    // 12. Disable using 'HA remote command' origin 1 time (expect disabled state).
    // 13. Enable using 'user command' origin 1 time (expect disabled state).
    // 14. Enable using 'HA remote command' origin 1 time (expect disabled state).
    // 15. Enable using 'DB connection' origin 1 time (expect disabled state).
    // 16. Enable using 'HA local command' origin 3 times with different ids (expect enabled state).
    // 17. Disable using 'user command' origin 1 time (expect disabled state).
    // 18. Disable using 'HA local command' origin 3 times with different ids (expect disabled state).
    // 19. Disable using 'DB connection' origin 1 time (expect disabled state).
    // 20. Disable using 'HA remote command' origin 1 time (expect disabled state).
    // 21. Enable using 'user command' origin 1 time (expect disabled state).
    // 22. Enable using 'HA remote command' origin 1 time (expect disabled state).
    // 23. Enable using 'DB connection' origin 1 time (expect disabled state).
    // 24. Reset using 'HA local command' origin (expect enabled state).
    // 25. Disable using 'HA local command' origin 3 times (expect disabled state).
    // 26. Enable using 'HA local command' origin (expect enabled state).
    void resetUsingHALocalCommandOriginTest();

    /// @brief This test verifies that reset works, so that internal state is reset after
    /// all managers are recreated.
    // 1. Disable using 'user command' origin 1 time (expect disabled state).
    // 2. Disable using 'HA remote command' origin 3 times with same id (expect disabled state).
    // 3. Disable using 'DB connection' origin 1 time (expect disabled state).
    // 4. Disable using 'HA local command' origin 1 time (expect disabled state).
    // 5. Enable using 'HA remote command' origin (expect disabled state).
    // 6. Enable using 'user command' origin 1 time (expect disabled state).
    // 7. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 8. Enable using 'DB connection' origin 1 time (expect enabled state).
    // 9. Disable using 'user command' origin 1 time (expect disabled state).
    // 10. Disable using 'HA remote command' origin 3 times with different ids (expect disabled state).
    // 11. Disable using 'DB connection' origin 1 time (expect disabled state).
    // 12. Disable using 'HA local command' origin 1 time (expect disabled state).
    // 13. Enable using 'user command' origin 1 time (expect disabled state).
    // 14. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 15. Enable using 'DB connection' origin 1 time (expect disabled state).
    // 16. Enable using 'HA remote command' origin 3 times with different ids (expect enabled state).
    // 17. Disable using 'user command' origin 1 time (expect disabled state).
    // 18. Disable using 'HA remote command' origin 3 times with different ids (expect disabled state).
    // 19. Disable using 'DB connection' origin 1 time (expect disabled state).
    // 20. Disable using 'HA local command' origin 1 time (expect disabled state).
    // 21. Enable using 'user command' origin 1 time (expect disabled state).
    // 22. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 23. Enable using 'DB connection' origin 1 time (expect disabled state).
    // 24. Reset using 'HA remote command' origin (expect enabled state).
    // 25. Disable using 'HA remote command' origin 3 times (expect disabled state).
    // 26. Enable using 'HA remote command' origin (expect enabled state).
    void resetUsingHARemoteCommandOriginTest();

    /// @brief This test verifies that reset works, so that internal state is reset after
    /// all managers are recreated.
    // 1. Disable using 'user command' origin 1 time (expect disabled state).
    // 2. Disable using 'DB connection' origin 3 times with same id (expect disabled state).
    // 3. Disable using 'HA remote command' origin 1 time (expect disabled state).
    // 4. Disable using 'HA local command' origin 1 time (expect disabled state).
    // 5. Enable using 'DB connection' origin (expect disabled state).
    // 6. Enable using 'user command' origin 1 time (expect disabled state).
    // 7. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 8. Enable using 'HA remote command' origin 1 time (expect enabled state).
    // 9. Disable using 'user command' origin 1 time (expect disabled state).
    // 10. Disable using 'DB connection' origin 3 times with different ids (expect disabled state).
    // 11. Disable using 'HA remote command' origin 1 time (expect disabled state).
    // 12. Disable using 'HA local command' origin 1 time (expect disabled state).
    // 13. Enable using 'user command' origin 1 time (expect disabled state).
    // 14. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 15. Enable using 'HA remote command' origin 1 time (expect disabled state).
    // 16. Enable using 'DB connection' origin 3 times with different ids (expect enabled state).
    // 17. Disable using 'user command' origin 1 time (expect disabled state).
    // 18. Disable using 'DB connection' origin 3 times with different ids (expect disabled state).
    // 19. Disable using 'HA remote command' origin 1 time (expect disabled state).
    // 20. Disable using 'HA local command' origin 1 time (expect disabled state).
    // 21. Enable using 'user command' origin 1 time (expect disabled state).
    // 22. Enable using 'HA local command' origin 1 time (expect disabled state).
    // 23. Enable using 'HA remote command' origin 1 time (expect disabled state).
    // 24. Reset using 'DB connection' origin (expect enabled state).
    // 25. Disable using 'DB connection' origin 3 times (expect disabled state).
    // 26. Enable using 'DB connection' origin (expect enabled state).
    void resetUsingDBConnectionOriginTest();

    /// @brief This test verifies that it is possible to setup delayed execution of enableAll
    /// function.
    void delayedEnableServiceTest();

    /// @brief This test verifies that explicitly enabling the service cancels the timer
    /// scheduled for automatically enabling it.
    void earlyEnableServiceTest();

    /// @brief This test verifies that it is possible to call delayedEnableService multiple times
    /// and that it results in only one timer being scheduled.
    void multipleDelayedEnableServiceTest();

    /// @brief This test verifies that it is possible to call delayedEnableService multiple times
    /// from different origins and that it results in each timer being scheduled.
    void multipleDifferentOriginsDelayedEnableServiceTest();

    /// @brief Runs IO service with a timeout.
    ///
    /// @param timeout_ms Timeout for running IO service in milliseconds.
    void runIOService(const long timeout_ms) {
        sleep(timeout_ms/1000);
        io_service_->poll();
    }

    /// @brief Check network state.
    ///
    /// @brief state The network state to check.
    /// @brief user Flag which indicates if user command disabled the state.
    /// @brief local The list of local IDs which disabled the state.
    /// @brief remote The list of remote IDs which disabled the state.
    /// @brief db The list of manager IDs which disabled the state because of a
    /// db connection failure.
    /// @brief global Flag which indicates if the state is disabled.
    void checkNetworkState(const NetworkState& state,
                           bool user,
                           std::vector<uint32_t> local,
                           std::vector<uint32_t> remote,
                           std::vector<uint32_t> db,
                           bool global) {
        std::ostringstream data;
        data << std::boolalpha;
        data << "{ \"disabled-by-db-connection\": [ ";
        bool not_first = false;
        for (auto const value : db) {
            if (not_first) {
                data << ", ";
            }
            data << value;
            not_first = true;
        }
        data << " ], \"disabled-by-local-command\": [ ";
        not_first = false;
        for (auto const value : local) {
            if (not_first) {
                data << ", ";
            }
            data << value;
            not_first = true;
        }
        data << " ], \"disabled-by-remote-command\": [ ";
        not_first = false;
        for (auto const value : remote) {
            if (not_first) {
                data << ", ";
            }
            data << value;
            not_first = true;
        }
        data << " ], \"disabled-by-user\": " << user
             << ", \"globally-disabled\": " << global
             << " }";
        auto const& expected = data.str();
        auto const& actual = state.toElement()->str();
        EXPECT_EQ(expected, actual);
        EXPECT_EQ(!global, state.isServiceEnabled());
    }

    /// @brief IO service used during the tests.
    IOServicePtr io_service_;
};

// This test verifies the default is enable state.
void
NetworkStateTest::defaultTest() {
    NetworkState state;

    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that it is possible to disable and then enable
// service using 'user command' origin.
void
NetworkStateTest::disableEnableServiceUsingUserCommandOriginTest() {
    NetworkState state;

    // Test that enable/disable using 'user command' origin works
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'user command' origin does not use internal counter
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that it is possible to disable and then enable
// service using 'HA local command' origin.
void
NetworkStateTest::disableEnableServiceUsingHALocalCommandOriginTest() {
    NetworkState state;

    // Test that enable/disable using 'HA local command' origin works
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'HA local command' origin does not use internal counter
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'HA local command' origin does consider id
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, false, { 1000, 1001 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 2);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1001, 1002 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, false, { 1002 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND + 2);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that it is possible to disable and then enable
// service using 'HA remote command' origin.
void
NetworkStateTest::disableEnableServiceUsingHARemoteCommandOriginTest() {
    NetworkState state;

    // Test that enable/disable using 'HA remote command' origin works
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'HA remote command' origin does not use internal counter
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'HA remote command' origin does consider id
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, false, {}, { 2000, 2001 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 2);
    checkNetworkState(state, false, {}, { 2000, 2001, 2002 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2001, 2002 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, false, {}, { 2002 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND + 2);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that it is possible to disable and then enable
// service using 'DB connection' origin.
void
NetworkStateTest::disableEnableServiceUsingDBConnectionOriginTest() {
    NetworkState state;

    // Test that enable/disable using 'DB connection' origin works
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'DB connection' origin does not use internal counter
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test that using 'DB connection' origin does consider id
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, false, {}, {}, { 3000, 3001 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 2);
    checkNetworkState(state, false, {}, {}, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3001, 3002 }, true);
    state.enableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, false, {}, {}, { 3002 }, true);
    state.enableService(NetworkState::DB_CONNECTION + 2);
    checkNetworkState(state, false, {}, {}, {}, false);
}

/// @brief This test verifies that it is possible to disable and then enable
/// service using a combination of origins.
// 1. Disable using 'user command' origin 2 times (expect disabled state).
// 2. Disable using 'HA local command' origin 2 times (expect disabled state).
// 3. Disable using 'HA local command' origin 1 time different id (expect disabled state).
// 4. Disable using 'HA remote command' origin 2 times (expect disabled state).
// 5. Disable using 'HA remote command' origin 1 time different id (expect disabled state).
// 6. Disable using 'DB connection' origin 2 times (expect disabled state).
// 7. Disable using 'DB connection' origin 1 time different id (expect disabled state).
// 8. Enable using 'user command' origin 1 time (expect disabled state).
// 9. Enable using 'HA local command' origin 1 time (expect disabled state).
// 10. Enable using 'HA local command' origin 1 time different id (expect disabled state).
// 11. Enable using 'HA remote command' origin 1 time (expect disabled state).
// 12. Enable using 'HA remote command' origin 1 time different id (expect disabled state).
// 13. Enable using 'DB connection' origin 1 times (expect disabled state).
// 14. Enable using 'DB connection' origin 1 time different id (expect disabled state).
void
NetworkStateTest::disableEnableServiceUsingMultipleOriginsTest() {
    NetworkState state;

    // Test that a combination properly affects the state
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, true, { 1000, 1001 }, {}, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000, 1001 }, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000, 1001 }, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, true, { 1000, 1001 }, { 2000, 2001 }, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000, 1001 }, { 2000, 2001 }, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000, 1001 }, { 2000, 2001 }, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, true, { 1000, 1001 }, { 2000, 2001 }, { 3000, 3001 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000, 1001 }, { 2000, 2001 }, { 3000, 3001 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1001 }, { 2000, 2001 }, { 3000, 3001 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, false, {}, { 2000, 2001 }, { 3000, 3001 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2001 }, { 3000, 3001 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, false, {}, {}, { 3000, 3001 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3001 },true);
    state.enableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that reset works, so that internal state is reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 3 times (expect disabled state).
// 2. Disable using 'HA command' origin 1 time (expect disabled state).
// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
// 4. Reset using 'user command' origin (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using 'user command' origin 3 times (expect disabled state).
// 8. Enable using 'user command' origin (expect enabled state).
void
NetworkStateTest::resetUsingUserCommandOriginTest() {
    NetworkState state;

    // Test User COMMAND + HA COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000 }, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test User COMMAND origin only
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that reset works, so that internal state is reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'HA local command' origin 3 times with same id (expect disabled state).
// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
// 4. Disable using 'HA remote command' origin 1 time (expect disabled state).
// 5. Enable using 'HA local command' origin (expect disabled state).
// 6. Enable using 'user command' origin 1 time (expect disabled state).
// 7. Enable using 'HA remote command' origin 1 time (expect disabled state).
// 8. Enable using 'DB connection' origin 1 time (expect enabled state).
// 9. Disable using 'user command' origin 1 time (expect disabled state).
// 10. Disable using 'HA local command' origin 3 times with different ids (expect disabled state).
// 11. Disable using 'DB connection' origin 1 time (expect disabled state).
// 12. Disable using 'HA remote command' origin 1 time (expect disabled state).
// 13. Enable using 'user command' origin 1 time (expect disabled state).
// 14. Enable using 'HA remote command' origin 1 time (expect disabled state).
// 15. Enable using 'DB connection' origin 1 time (expect disabled state).
// 16. Enable using 'HA local command' origin 3 times with different ids (expect enabled state).
// 17. Disable using 'user command' origin 1 time (expect disabled state).
// 18. Disable using 'HA local command' origin 3 times with different ids (expect disabled state).
// 19. Disable using 'DB connection' origin 1 time (expect disabled state).
// 20. Disable using 'HA remote command' origin 1 time (expect disabled state).
// 21. Enable using 'user command' origin 1 time (expect disabled state).
// 22. Enable using 'HA remote command' origin 1 time (expect disabled state).
// 23. Enable using 'DB connection' origin 1 time (expect disabled state).
// 24. Reset using 'HA local command' origin (expect enabled state).
// 25. Disable using 'HA local command' origin 3 times (expect disabled state).
// 26. Enable using 'HA local command' origin (expect enabled state).
void
NetworkStateTest::resetUsingHALocalCommandOriginTest() {
    NetworkState state;

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000 }, {}, { 3000 }, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, true, { 1000, 1001 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 2);
    checkNetworkState(state, true, { 1000, 1001, 1002 }, {}, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000, 1001, 1002 }, {}, { 3000 }, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000, 1001, 1002 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1001, 1002 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, false, { 1002 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND + 2);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 1);
    checkNetworkState(state, true, { 1000, 1001 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND + 2);
    checkNetworkState(state, true, { 1000, 1001, 1002 }, {}, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000, 1001, 1002 }, {}, { 3000 }, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000, 1001, 1002 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, { 1000, 1001, 1002 }, {}, {}, true);
    state.resetForLocalCommands();
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA LOCAL COMMAND origin only
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that reset works, so that internal state is reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'HA remote command' origin 3 times with same id (expect disabled state).
// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
// 4. Disable using 'HA local command' origin 1 time (expect disabled state).
// 5. Enable using 'HA remote command' origin (expect disabled state).
// 6. Enable using 'user command' origin 1 time (expect disabled state).
// 7. Enable using 'HA local command' origin 1 time (expect disabled state).
// 8. Enable using 'DB connection' origin 1 time (expect enabled state).
// 9. Disable using 'user command' origin 1 time (expect disabled state).
// 10. Disable using 'HA remote command' origin 3 times with different ids (expect disabled state).
// 11. Disable using 'DB connection' origin 1 time (expect disabled state).
// 12. Disable using 'HA local command' origin 1 time (expect disabled state).
// 13. Enable using 'user command' origin 1 time (expect disabled state).
// 14. Enable using 'HA local command' origin 1 time (expect disabled state).
// 15. Enable using 'DB connection' origin 1 time (expect disabled state).
// 16. Enable using 'HA remote command' origin 3 times with different ids (expect enabled state).
// 17. Disable using 'user command' origin 1 time (expect disabled state).
// 18. Disable using 'HA remote command' origin 3 times with different ids (expect disabled state).
// 19. Disable using 'DB connection' origin 1 time (expect disabled state).
// 20. Disable using 'HA local command' origin 1 time (expect disabled state).
// 21. Enable using 'user command' origin 1 time (expect disabled state).
// 22. Enable using 'HA local command' origin 1 time (expect disabled state).
// 23. Enable using 'DB connection' origin 1 time (expect disabled state).
// 24. Reset using 'HA remote command' origin (expect enabled state).
// 25. Disable using 'HA remote command' origin 3 times (expect disabled state).
// 26. Enable using 'HA remote command' origin (expect enabled state).
void
NetworkStateTest::resetUsingHARemoteCommandOriginTest() {
    NetworkState state;

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, { 2000 }, { 3000 }, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, { 1000 }, {}, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, {}, { 3000 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, true, {}, { 2000, 2001 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 2);
    checkNetworkState(state, true, {}, { 2000, 2001, 2002 }, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, { 2000, 2001, 2002 }, { 3000 }, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000, 2001, 2002 }, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, { 2000, 2001, 2002 }, { 3000 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, { 2000, 2001, 2002 }, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, { 2000, 2001, 2002 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2001, 2002 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, false, {}, { 2002 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND + 2);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 1);
    checkNetworkState(state, true, {}, { 2000, 2001 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND + 2);
    checkNetworkState(state, true, {}, { 2000, 2001, 2002 }, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, { 2000, 2001, 2002 }, { 3000 }, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000, 2001, 2002 }, { 3000 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, { 2000, 2001, 2002 }, { 3000 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, { 2000, 2001, 2002 }, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, { 2000, 2001, 2002 }, {}, true);
    state.resetForRemoteCommands();
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA REMOTE COMMAND origin only
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);
}

/// @brief This test verifies that reset works, so that internal state is reset after
/// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'DB connection' origin 3 times with same id (expect disabled state).
// 3. Disable using 'HA remote command' origin 1 time (expect disabled state).
// 4. Disable using 'HA local command' origin 1 time (expect disabled state).
// 5. Enable using 'DB connection' origin (expect disabled state).
// 6. Enable using 'user command' origin 1 time (expect disabled state).
// 7. Enable using 'HA local command' origin 1 time (expect disabled state).
// 8. Enable using 'HA remote command' origin 1 time (expect enabled state).
// 9. Disable using 'user command' origin 1 time (expect disabled state).
// 10. Disable using 'DB connection' origin 3 times with different ids (expect disabled state).
// 11. Disable using 'HA remote command' origin 1 time (expect disabled state).
// 12. Disable using 'HA local command' origin 1 time (expect disabled state).
// 13. Enable using 'user command' origin 1 time (expect disabled state).
// 14. Enable using 'HA local command' origin 1 time (expect disabled state).
// 15. Enable using 'HA remote command' origin 1 time (expect disabled state).
// 16. Enable using 'DB connection' origin 3 times with different ids (expect enabled state).
// 17. Disable using 'user command' origin 1 time (expect disabled state).
// 18. Disable using 'DB connection' origin 3 times with different ids (expect disabled state).
// 19. Disable using 'HA remote command' origin 1 time (expect disabled state).
// 20. Disable using 'HA local command' origin 1 time (expect disabled state).
// 21. Enable using 'user command' origin 1 time (expect disabled state).
// 22. Enable using 'HA local command' origin 1 time (expect disabled state).
// 23. Enable using 'HA remote command' origin 1 time (expect disabled state).
// 24. Reset using 'DB connection' origin (expect enabled state).
// 25. Disable using 'DB connection' origin 3 times (expect disabled state).
// 26. Enable using 'DB connection' origin (expect enabled state).
void
NetworkStateTest::resetUsingDBConnectionOriginTest() {
    NetworkState state;

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, { 3000 }, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000 }, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, { 1000 }, { 2000 }, {}, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, { 2000 }, {}, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, {}, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, true, {}, {}, { 3000, 3001 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 2);
    checkNetworkState(state, true, {}, {}, { 3000, 3001, 3002 }, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, { 3000, 3001, 3002 }, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000 }, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, { 2000 }, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3001, 3002 }, true);
    state.enableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, false, {}, {}, { 3002 }, true);
    state.enableService(NetworkState::DB_CONNECTION + 2);
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, true, {}, {}, {}, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, true, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 1);
    checkNetworkState(state, true, {}, {}, { 3000, 3001 }, true);
    state.disableService(NetworkState::DB_CONNECTION + 2);
    checkNetworkState(state, true, {}, {}, { 3000, 3001, 3002 }, true);
    state.disableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, true, {}, { 2000 }, { 3000, 3001, 3002 }, true);
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, true, { 1000 }, { 2000 }, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::USER_COMMAND);
    checkNetworkState(state, false, { 1000 }, { 2000 }, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    checkNetworkState(state, false, {}, { 2000 }, { 3000, 3001, 3002 }, true);
    state.enableService(NetworkState::HA_REMOTE_COMMAND);
    checkNetworkState(state, false, {}, {}, { 3000, 3001, 3002 }, true);
    state.resetForDbConnection();
    checkNetworkState(state, false, {}, {}, {}, false);

    // Test DB CONNECTION origin only
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.disableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, { 3000 }, true);
    state.enableService(NetworkState::DB_CONNECTION);
    checkNetworkState(state, false, {}, {}, {}, false);
}

// This test verifies that it is possible to setup delayed execution of enableAll
// function.
void
NetworkStateTest::delayedEnableServiceTest() {
    NetworkState state;
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::USER_COMMAND);
    state.delayedEnableService(1, NetworkState::USER_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 2 seconds, the service should be enabled.
    runIOService(2000);
    EXPECT_TRUE(state.isServiceEnabled());
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    state.delayedEnableService(1, NetworkState::HA_LOCAL_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 2 seconds, the service should be enabled.
    runIOService(2000);
    EXPECT_TRUE(state.isServiceEnabled());
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_THROW(state.delayedEnableService(1, NetworkState::DB_CONNECTION), BadValue);
}

// This test verifies that explicitly enabling the service cancels the timer
// scheduled for automatically enabling it.
void
NetworkStateTest::earlyEnableServiceTest() {
    NetworkState state;
    // Disable the service.
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    // Schedule enabling the service in 2 seconds.
    state.delayedEnableService(10, NetworkState::USER_COMMAND);
    // Explicitly enable the service.
    state.enableService(NetworkState::USER_COMMAND);
    // The timer should be now canceled and the service should be enabled.
    EXPECT_FALSE(state.isDelayedEnableService());
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to call delayedEnableService multiple times
// and that it results in only one timer being scheduled.
void
NetworkStateTest::multipleDelayedEnableServiceTest() {
    NetworkState state;
    // Disable the service and then schedule enabling it in 5 second.
    state.disableService(NetworkState::USER_COMMAND);
    // Schedule the first timer for 5 seconds.
    state.delayedEnableService(5, NetworkState::USER_COMMAND);
    // When calling it the second time the old timer should be destroyed and
    // the timeout should be set to 2 seconds.
    state.delayedEnableService(2, NetworkState::USER_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 3 seconds, the service should be enabled.
    runIOService(3000);
    EXPECT_TRUE(state.isServiceEnabled());
    // The timer should not be present, even though the first timer was created
    // with 5 seconds interval.
    EXPECT_FALSE(state.isDelayedEnableService());
}

// This test verifies that it is possible to call delayedEnableService multiple times
// from different origins and that it results in each timer being scheduled.
void
NetworkStateTest::multipleDifferentOriginsDelayedEnableServiceTest() {
    NetworkState state;
    // Disable the service and then schedule enabling it in 5 second.
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    // Disable the service and then schedule enabling it in 2 second.
    state.disableService(NetworkState::USER_COMMAND);
    // Schedule the first timer for 5 seconds.
    state.delayedEnableService(5, NetworkState::HA_LOCAL_COMMAND);
    // When calling it the second time the old timer should not be destroyed and
    // the new timeout should be set to 2 seconds.
    state.delayedEnableService(2, NetworkState::USER_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 3 seconds, the service should not be enabled.
    runIOService(3000);
    EXPECT_FALSE(state.isServiceEnabled());
    // The timer should be present, because the first timer was created with 5
    // seconds interval.
    EXPECT_TRUE(state.isDelayedEnableService());
    // After running IO service for 3 seconds, the service should be enabled.
    runIOService(3000);
    EXPECT_TRUE(state.isServiceEnabled());
    // The timer should not be present, because the first timer was created with
    // 5 seconds interval.
    EXPECT_FALSE(state.isDelayedEnableService());
}

// Test invocations.

TEST_F(NetworkStateTest, defaultTest) {
    defaultTest();
}

TEST_F(NetworkStateTest, defaultTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    defaultTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingUserCommandOriginTest) {
    disableEnableServiceUsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingUserCommandOriginTestMultilThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableServiceUsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingHALocalCommandOriginTest) {
    disableEnableServiceUsingHALocalCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingHALocalCommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableServiceUsingHALocalCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingHARemoteCommandOriginTest) {
    disableEnableServiceUsingHARemoteCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingHARemoteCommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableServiceUsingHARemoteCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingDBConnectionOriginTest) {
    disableEnableServiceUsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingDBConnectionOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableServiceUsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingMultipleOriginsTest) {
    disableEnableServiceUsingMultipleOriginsTest();
}

TEST_F(NetworkStateTest, disableEnableServiceUsingMultipleOriginsTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableServiceUsingMultipleOriginsTest();
}

TEST_F(NetworkStateTest, resetUsingUserCommandOriginTest) {
    resetUsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, resetUsingUserCommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    resetUsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, resetUsingDBConnectionOriginTest) {
    resetUsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, resetUsingDBConnectionOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    resetUsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, resetUsingHALocalCommandOriginTest) {
    resetUsingHALocalCommandOriginTest();
}

TEST_F(NetworkStateTest, resetUsingHALocalCommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    resetUsingHALocalCommandOriginTest();
}

TEST_F(NetworkStateTest, resetUsingHARemoteCommandOriginTest) {
    resetUsingHARemoteCommandOriginTest();
}

TEST_F(NetworkStateTest, resetUsingHARemoteCommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    resetUsingHARemoteCommandOriginTest();
}

TEST_F(NetworkStateTest, delayedEnableServiceTest) {
    delayedEnableServiceTest();
}

TEST_F(NetworkStateTest, delayedEnableAllTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    delayedEnableServiceTest();
}

TEST_F(NetworkStateTest, earlyEnableServiceTest) {
    earlyEnableServiceTest();
}

TEST_F(NetworkStateTest, earlyEnableServiceTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    earlyEnableServiceTest();
}

TEST_F(NetworkStateTest, multipleDelayedEnableServiceTest) {
    multipleDelayedEnableServiceTest();
}

TEST_F(NetworkStateTest, multipleDelayedEnableServiceTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    multipleDelayedEnableServiceTest();
}

TEST_F(NetworkStateTest, multipleDifferentOriginsDelayedEnableServiceTest) {
    multipleDifferentOriginsDelayedEnableServiceTest();
}

TEST_F(NetworkStateTest, multipleDifferentOriginsDelayedEnableServiceTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    multipleDifferentOriginsDelayedEnableServiceTest();
}

} // end of anonymous namespace
