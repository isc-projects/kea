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
#include <gtest/gtest.h>
#include <functional>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace  {

/// @brief Test fixture class for @c NetworkState class.
class NetworkStateTest : public ::testing::Test {
public:

    /// @brief Constructor.
    NetworkStateTest()
        : io_service_(new IOService()) {
        TimerMgr::instance()->unregisterTimers();
        TimerMgr::instance()->setIOService(io_service_);
    }

    /// @brief Destructor.
    virtual ~NetworkStateTest() {
        // Cancel timers.
        TimerMgr::instance()->unregisterTimers();
        // Make sure IO service will stop when no timers are scheduled.
        io_service_->stopWork();
        // Run outstanding tasks.
        io_service_->run();
    }

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
TEST_F(NetworkStateTest, default) {
    NetworkState state4(NetworkState::DHCPv4);
    EXPECT_TRUE(state4.isServiceEnabled());
    NetworkState state6(NetworkState::DHCPv6);
    EXPECT_TRUE(state6.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using 'user command' origin.
TEST_F(NetworkStateTest, disableEnableService4UsingUserCommandOrigin) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'user command' origin works
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'user command' origin does not use internal counter
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using 'HA command' origin.
TEST_F(NetworkStateTest, disableEnableService4UsingHACommandOrigin) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'HA command' origin works
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'HA command' origin does not use internal counter
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using using 'DB connection' origin.
TEST_F(NetworkStateTest, disableEnableService4UsingDBConnectionOrigin) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'DB connection' origin works
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using using 'DB connection' origin uses internal counter
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using a combination of origins.
// 1. Disable using 'user command' origin 2 times (expect disabled state).
// 2. Disable using 'HA command' origin 2 times (expect disabled state).
// 3. Disable using using 'DB connection' origin 2 times (expect disabled state).
// 4. Enable using 'user command' origin 1 time (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using using 'DB connection' origin 2 times (expect enabled state).
TEST_F(NetworkStateTest, disableEnableService4UsingMultipleOrigins) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that a combination properly affects the state
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using 'user command' origin.
TEST_F(NetworkStateTest, disableEnableService6UsingUserCommandOrigin) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using 'user command' origin works
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'user command' origin does not use internal counter
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using 'HA command' origin.
TEST_F(NetworkStateTest, disableEnableService6UsingHACommandOrigin) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using 'HA command' origin works
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'HA command' origin does not use internal counter
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using using 'DB connection' origin.
TEST_F(NetworkStateTest, disableEnableService6UsingDBConnectionOrigin) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using using 'DB connection' origin works
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using using 'DB connection' origin uses internal counter
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using a combination of origins.
// 1. Disable using 'user command' origin 2 times (expect disabled state).
// 2. Disable using 'HA command' origin 2 times (expect disabled state).
// 3. Disable using using 'DB connection' origin 2 times (expect disabled state).
// 4. Enable using 'user command' origin 1 time (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using using 'DB connection' origin 2 times (expect enabled state).
TEST_F(NetworkStateTest, disableEnableService6UsingMultipleOrigins) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that a combination properly affects the state
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that reset works, so that internal state is reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 3 times (expect disabled state).
// 2. Disable using 'HA command' origin 1 time (expect disabled state).
// 3. Disable using using 'DB connection' origin 1 time (expect disabled state).
// 4. Reset using 'user command' origin (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using 'user command' origin 3 times (expect disabled state).
// 8. Reset using 'user command' origin (expect enabled state).
TEST_F(NetworkStateTest, resetUsingUserCommandOrigin) {
    NetworkState state(NetworkState::DHCPv4);

    // Test User COMMAND + HA COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.reset(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test User COMMAND origin only
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.reset(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that reset works, so that internal state is reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'HA command' origin 3 times (expect disabled state).
// 3. Disable using using 'DB connection' origin 1 time (expect disabled state).
// 4. Reset using 'HA command' origin (expect disabled state).
// 5. Enable using 'user command' origin 1 time (expect disabled state).
// 6. Enable using using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using 'HA command' origin 3 times (expect disabled state).
// 8. Reset using 'HA command' origin (expect enabled state).
TEST_F(NetworkStateTest, resetUsingHACommandOrigin) {
    NetworkState state(NetworkState::DHCPv4);

    // Test HA COMMAND + User COMMAND + DB CONNECTION origins
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.reset(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test HA COMMAND origin only
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.reset(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that reset works, so that internal state is  reset after
// all managers are recreated.
// 1. Disable using 'user command' origin 1 time (expect disabled state).
// 2. Disable using 'HA command' origin 1 time (expect disabled state).
// 3. Disable using using 'DB connection' origin 3 time (expect disabled state).
// 4. Reset using using 'DB connection' origin (expect disabled state).
// 5. Enable using 'user command' origin 1 time (expect disabled state).
// 6. Enable using using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using using 'DB connection' origin 3 times (expect disabled state).
// 8. Reset using using 'DB connection' origin (expect enabled state).
TEST_F(NetworkStateTest, resetUsingDBConnectionOrigin) {
    NetworkState state(NetworkState::DHCPv4);

    // Test DB CONNECTION + User COMMAND + HA COMMAND origins
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.reset(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test DB CONNECTION origin only
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.reset(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that enableAll() enables the service. This test will be
// extended in the future to verify that it also enables disabled scopes.
TEST_F(NetworkStateTest, enableAll) {
    NetworkState state(NetworkState::DHCPv4);
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableAll(NetworkState::Origin::USER_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableAll(NetworkState::Origin::HA_COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableAll(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to setup delayed execution of enableAll
// function.
TEST_F(NetworkStateTest, delayedEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::Origin::USER_COMMAND);
    state.delayedEnableAll(1, NetworkState::Origin::USER_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 2 seconds, the service should be enabled.
    runIOService(2000);
    EXPECT_TRUE(state.isServiceEnabled());
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::Origin::HA_COMMAND);
    state.delayedEnableAll(1, NetworkState::Origin::HA_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 2 seconds, the service should be enabled.
    runIOService(2000);
    EXPECT_TRUE(state.isServiceEnabled());
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_THROW(state.delayedEnableAll(1, NetworkState::Origin::DB_CONNECTION), BadValue);
}

// This test verifies that explicitly enabling the service cancels the timer
// scheduled for automatically enabling it.
TEST_F(NetworkStateTest, earlyEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service.
    state.disableService(NetworkState::Origin::USER_COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    // Schedule enabling the service in 2 seconds.
    state.delayedEnableAll(2, NetworkState::Origin::USER_COMMAND);
    // Explicitly enable the service.
    state.enableAll(NetworkState::Origin::USER_COMMAND);
    // The timer should be now canceled and the service should be enabled.
    EXPECT_FALSE(state.isDelayedEnableAll());
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to call delayedEnableAll multiple times
// and that it results in only one timer being scheduled.
TEST_F(NetworkStateTest, multipleDelayedEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service and then schedule enabling it in 5 second.
    state.disableService(NetworkState::Origin::USER_COMMAND);
    // Schedule the first timer for 5 seconds.
    state.delayedEnableAll(5, NetworkState::Origin::USER_COMMAND);
    // When calling it the second time the old timer should be destroyed and
    // the timeout should be set to 2 seconds.
    state.delayedEnableAll(2, NetworkState::Origin::USER_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 3 seconds, the service should be enabled.
    runIOService(3000);
    EXPECT_TRUE(state.isServiceEnabled());
    // The timer should not be present, even though the first timer was created
    // with 5 seconds interval.
    EXPECT_FALSE(state.isDelayedEnableAll());
}

// This test verifies that it is possible to call delayedEnableAll multiple times
// from different origins and that it results in each timer being scheduled.
TEST_F(NetworkStateTest, multipleDifferentOriginsDelayedEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service and then schedule enabling it in 5 second.
    state.disableService(NetworkState::Origin::HA_COMMAND);
    // Disable the service and then schedule enabling it in 2 second.
    state.disableService(NetworkState::Origin::USER_COMMAND);
    // Schedule the first timer for 5 seconds.
    state.delayedEnableAll(5, NetworkState::Origin::HA_COMMAND);
    // When calling it the second time the old timer should not be destroyed and
    // the new timeout should be set to 2 seconds.
    state.delayedEnableAll(2, NetworkState::Origin::USER_COMMAND);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 3 seconds, the service should not be enabled.
    runIOService(3000);
    EXPECT_FALSE(state.isServiceEnabled());
    // The timer should be present, because the first timer was created with 5
    // seconds interval.
    EXPECT_TRUE(state.isDelayedEnableAll());
    // After running IO service for 3 seconds, the service should be enabled.
    runIOService(3000);
    EXPECT_TRUE(state.isServiceEnabled());
    // The timer should not be present, because the first timer was created with
    // 5 seconds interval.
    EXPECT_FALSE(state.isDelayedEnableAll());
}

} // end of anonymous namespace
