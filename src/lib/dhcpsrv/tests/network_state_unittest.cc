// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
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

namespace  {

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

    /// @brief This test verifies that it is possible to disable and then enable DHCPv4
    /// service using 'user command' origin.
    void disableEnableService4UsingUserCommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv4
    /// service using 'HA command' origin.
    void disableEnableService4UsingHACommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv4
    /// service using 'DB connection' origin.
    void disableEnableService4UsingDBConnectionOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv4
    /// service using a combination of origins.
    /// 1. Disable using 'user command' origin 2 times (expect disabled state).
    /// 2. Disable using 'HA command' origin 2 times (expect disabled state).
    /// 3. Disable using 'DB connection' origin 2 times (expect disabled state).
    /// 4. Enable using 'user command' origin 1 time (expect disabled state).
    /// 5. Enable using 'HA command' origin 1 time (expect disabled state).
    /// 6. Enable using 'DB connection' origin 2 times (expect enabled state).
    void disableEnableService4UsingMultipleOriginsTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv6
    /// service using 'user command' origin.
    void disableEnableService6UsingUserCommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv6
    /// service using 'HA command' origin.
    void disableEnableService6UsingHACommandOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv6
    /// service using 'DB connection' origin.
    void disableEnableService6UsingDBConnectionOriginTest();

    /// @brief This test verifies that it is possible to disable and then enable DHCPv6
    /// service using a combination of origins.
    /// 1. Disable using 'user command' origin 2 times (expect disabled state).
    /// 2. Disable using 'HA command' origin 2 times (expect disabled state).
    /// 3. Disable using 'DB connection' origin 2 times (expect disabled state).
    /// 4. Enable using 'user command' origin 1 time (expect disabled state).
    /// 5. Enable using 'HA command' origin 1 time (expect disabled state).
    /// 6. Enable using 'DB connection' origin 2 times (expect enabled state).
    void disableEnableService6UsingMultipleOriginsTest();

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
    /// 1. Disable using 'user command' origin 1 time (expect disabled state).
    /// 2. Disable using 'HA command' origin 3 times (expect disabled state).
    /// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
    /// 4. Reset using 'HA command' origin (expect disabled state).
    /// 5. Enable using 'user command' origin 1 time (expect disabled state).
    /// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
    /// 7. Disable using 'HA command' origin 3 times (expect disabled state).
    /// 8. Reset using 'HA command' origin (expect enabled state).
    void resetUsingHACommandOriginTest();

    /// @brief This test verifies that reset works, so that internal state is reset after
    /// all managers are recreated.
    /// 1. Disable using 'user command' origin 1 time (expect disabled state).
    /// 2. Disable using 'HA command' origin 1 time (expect disabled state).
    /// 3. Disable using 'DB connection' origin 3 time (expect disabled state).
    /// 4. Reset using 'DB connection' origin (expect disabled state).
    /// 5. Enable using 'user command' origin 1 time (expect disabled state).
    /// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
    /// 7. Disable using 'DB connection' origin 3 times (expect disabled state).
    /// 8. Reset using 'DB connection' origin (expect enabled state).
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

    /// @brief IO service used during the tests.
    IOServicePtr io_service_;
};

// This test verifies the default is enable state.
void
NetworkStateTest::defaultTest() {
    NetworkState state4(NetworkState::DHCPv4);
    EXPECT_TRUE(state4.isServiceEnabled());
    NetworkState state6(NetworkState::DHCPv6);
    EXPECT_TRUE(state6.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using 'user command' origin.
void
NetworkStateTest::disableEnableService4UsingUserCommandOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'user command' origin works
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'user command' origin does not use internal counter
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using 'HA command' origin.
void
NetworkStateTest::disableEnableService4UsingHACommandOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'HA command' origin works
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'HA command' origin does not use internal counter
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using 'DB connection' origin.
void
NetworkStateTest::disableEnableService4UsingDBConnectionOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'DB connection' origin works
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'DB connection' origin uses internal counter
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using a combination of origins.
// 1. Disable using 'user command' origin 2 times (expect disabled state).
// 2. Disable using 'HA command' origin 2 times (expect disabled state).
// 3. Disable using 'DB connection' origin 2 times (expect disabled state).
// 4. Enable using 'user command' origin 1 time (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 2 times (expect enabled state).
void
NetworkStateTest::disableEnableService4UsingMultipleOriginsTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test that a combination properly affects the state
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using 'user command' origin.
void
NetworkStateTest::disableEnableService6UsingUserCommandOriginTest() {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using 'user command' origin works
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'user command' origin does not use internal counter
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using 'HA command' origin.
void
NetworkStateTest::disableEnableService6UsingHACommandOriginTest() {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using 'HA command' origin works
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'HA command' origin does not use internal counter
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using 'DB connection' origin.
void
NetworkStateTest::disableEnableService6UsingDBConnectionOriginTest() {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using 'DB connection' origin works
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'DB connection' origin uses internal counter
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using a combination of origins.
// 1. Disable using 'user command' origin 2 times (expect disabled state).
// 2. Disable using 'HA command' origin 2 times (expect disabled state).
// 3. Disable using 'DB connection' origin 2 times (expect disabled state).
// 4. Enable using 'user command' origin 1 time (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 2 times (expect enabled state).
void
NetworkStateTest::disableEnableService6UsingMultipleOriginsTest() {
    NetworkState state(NetworkState::DHCPv6);

    // Test that a combination properly affects the state
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
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
// 8. Reset using 'user command' origin (expect enabled state).
void
NetworkStateTest::resetUsingUserCommandOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test User COMMAND + HA COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test User COMMAND origin only
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that reset works, so that internal state is reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'HA command' origin 3 times (expect disabled state).
// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
// 4. Enable using 'HA command' origin (expect disabled state).
// 5. Enable using 'user command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using 'HA command' origin 3 times (expect disabled state).
// 8. Enable using 'HA command' origin (expect enabled state).
void
NetworkStateTest::resetUsingHACommandOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test HA COMMAND origin only
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that reset works, so that internal state is  reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'HA command' origin 1 time (expect disabled state).
// 3. Disable using 'DB connection' origin 3 time (expect disabled state).
// 4. Reset using 'DB connection' origin (expect disabled state).
// 5. Enable using 'user command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using 'DB connection' origin 3 times (expect disabled state).
// 8. Reset using 'DB connection' origin (expect enabled state).
void
NetworkStateTest::resetUsingDBConnectionOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test DB CONNECTION + User COMMAND + HA COMMAND origins
    state.disableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetForDbConnection();
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test DB CONNECTION origin only
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetForDbConnection();
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to setup delayed execution of enableAll
// function.
void
NetworkStateTest::delayedEnableServiceTest() {
    NetworkState state(NetworkState::DHCPv4);
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
    NetworkState state(NetworkState::DHCPv4);
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
    NetworkState state(NetworkState::DHCPv4);
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
    NetworkState state(NetworkState::DHCPv4);
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

TEST_F(NetworkStateTest, disableEnableService4UsingUserCommandOriginTest) {
    disableEnableService4UsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingUserCommandOriginTestMultilThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService4UsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingHACommandOriginTest) {
    disableEnableService4UsingHACommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingHACommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService4UsingHACommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingDBConnectionOriginTest) {
    disableEnableService4UsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingDBConnectionOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService4UsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingMultipleOriginsTest) {
    disableEnableService4UsingMultipleOriginsTest();
}

TEST_F(NetworkStateTest, disableEnableService4UsingMultipleOriginsTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService4UsingMultipleOriginsTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingUserCommandOriginTest) {
    disableEnableService6UsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingUserCommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService6UsingUserCommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingHACommandOriginTest) {
    disableEnableService6UsingHACommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingHACommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService6UsingHACommandOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingDBConnectionOriginTest) {
    disableEnableService6UsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingDBConnectionOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService6UsingDBConnectionOriginTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingMultipleOriginsTest) {
    disableEnableService6UsingMultipleOriginsTest();
}

TEST_F(NetworkStateTest, disableEnableService6UsingMultipleOriginsTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    disableEnableService6UsingMultipleOriginsTest();
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

TEST_F(NetworkStateTest, resetUsingHACommandOriginTest) {
    resetUsingHACommandOriginTest();
}

TEST_F(NetworkStateTest, resetUsingHACommandOriginTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    resetUsingHACommandOriginTest();
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
