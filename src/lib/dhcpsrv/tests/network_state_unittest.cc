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
        : io_service_(new IOService()),
          test_timer_(*io_service_) {
        TimerMgr::instance()->unregisterTimers();
        TimerMgr::instance()->setIOService(io_service_);
    }

    /// @brief Destructor.
    virtual ~NetworkStateTest() {
        // Cancel timers.
        TimerMgr::instance()->unregisterTimers();
        test_timer_.cancel();
        // Make sure IO service will stop when no timers are scheduled.
        io_service_->stopWork();
        // Run outstanding tasks.
        io_service_->run();
    }

    /// @brief Test timer callback stopping IO service.
    void testTimerCallback() {
        TimerMgr::instance()->unregisterTimers();
        io_service_->stop();
    }

    /// @brief Runs IO service with a timeout.
    ///
    /// @param timeout_ms Timeout for running IO service in milliseconds.
    void runIOService(const long timeout_ms) {
        test_timer_.setup(std::bind(&NetworkStateTest::testTimerCallback,
                                    this),
                          timeout_ms,
                          IntervalTimer::ONE_SHOT);
        io_service_->run();
    }

    /// @brief IO service used during the tests.
    IOServicePtr io_service_;

    /// @brief Timeout detecting timer.
    IntervalTimer test_timer_;
};

// This test verifies the default is enable state.
TEST_F(NetworkStateTest, default) {
    NetworkState state4(NetworkState::DHCPv4);
    EXPECT_TRUE(state4.isServiceEnabled());
    NetworkState state6(NetworkState::DHCPv6);
    EXPECT_TRUE(state6.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using origin type command.
TEST_F(NetworkStateTest, disableEnableService4UsingOriginTypeCommand) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using origin type command works
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using origin type command does not use internal counter
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using origin type HA.
TEST_F(NetworkStateTest, disableEnableService4UsingOriginTypeHA) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using origin type HA works
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using origin type HA does not use internal counter
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using origin type connection.
TEST_F(NetworkStateTest, disableEnableService4UsingOriginTypeConnection) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable origin type connection works
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using origin type connection uses internal counter
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv4
// service using a combination of origin types.
// 1. Disable using origin type command 2 times (expect disabled state).
// 2. Disable using origin type HA 2 times (expect disabled state).
// 3. Disable using origin type connection 2 times (expect disabled state).
// 4. Enable using origin type command 1 time (expect disabled state).
// 5. Enable using origin type HA 1 time (expect disabled state).
// 6. Enable using origin type connection 2 times (expect enabled state).
TEST_F(NetworkStateTest, disableEnableService4UsingMultipleOriginTypes) {
    NetworkState state(NetworkState::DHCPv4);

    // Test that a combination properly affects the state
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using origin type command.
TEST_F(NetworkStateTest, disableEnableService6UsingOriginCommand) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using origin type command works
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using origin type command does not use internal counter
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using origin type HA.
TEST_F(NetworkStateTest, disableEnableService6UsingOriginTypeHA) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using origin type HA works
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using origin type HA does not use internal counter
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using origin type connection.
TEST_F(NetworkStateTest, disableEnableService6UsingOriginTypeConnection) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using origin type connection works
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using origin type connection uses internal counter
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6
// service using a combination of origin types.
// 1. Disable using origin type command 2 times (expect disabled state).
// 2. Disable using origin type HA 2 times (expect disabled state).
// 3. Disable using origin type connection 2 times (expect disabled state).
// 4. Enable using origin type command 1 time (expect disabled state).
// 5. Enable using origin type HA 1 time (expect disabled state).
// 6. Enable using origin type connection 2 times (expect enabled state).
TEST_F(NetworkStateTest, disableEnableService6UsingMultipleOriginTypes) {
    NetworkState state(NetworkState::DHCPv6);

    // Test that a combination properly affects the state
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that resetInternalState works, so that internal state is
// reset after all managers are recreated.
// 1. Disable using origin type command 3 times (expect disabled state).
// 2. Disable using origin type HA 1 time (expect disabled state).
// 3. Disable using origin type connection 1 time (expect disabled state).
// 4. Reset using origin type command (expect disabled state).
// 5. Enable using origin type HA 1 time (expect disabled state).
// 6. Enable using origin type connection 1 time (expect enabled state).
// 7. Disable using origin type command 3 times (expect disabled state).
// 8. Reset using origin type command (expect enabled state).
TEST_F(NetworkStateTest, resetInternalStateUsingOriginTypeCommand) {
    NetworkState state(NetworkState::DHCPv4);

    // Test COMMAND + HA + CONNECTION types
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetInternalState(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test COMMAND type only
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetInternalState(NetworkState::Origin::COMMAND);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that resetInternalState works, so that internal state is
// reset after all managers are recreated.
// 1. Disable using origin type command 1 time (expect disabled state).
// 2. Disable using origin type HA 3 times (expect disabled state).
// 3. Disable using origin type connection 1 time (expect disabled state).
// 4. Reset using origin type HA (expect disabled state).
// 5. Enable using origin type command 1 time (expect disabled state).
// 6. Enable using origin type connection 1 time (expect enabled state).
// 7. Disable using origin type HA 3 times (expect disabled state).
// 8. Reset using origin type HA (expect enabled state).
TEST_F(NetworkStateTest, resetInternalStateUsingOriginTypeHA) {
    NetworkState state(NetworkState::DHCPv4);

    // Test HA + COMMAND + CONNECTION types
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetInternalState(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test HA type only
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetInternalState(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that resetInternalState works, so that internal state is
// reset after all managers are recreated.
// 1. Disable using origin type command 1 time (expect disabled state).
// 2. Disable using origin type HA a time (expect disabled state).
// 3. Disable using origin type connection 3 time (expect disabled state).
// 4. Reset using origin type connection (expect disabled state).
// 5. Enable using origin type command 1 time (expect disabled state).
// 6. Enable using origin type connection 1 time (expect enabled state).
// 7. Disable using origin type connection 3 times (expect disabled state).
// 8. Reset using origin type connection (expect enabled state).
TEST_F(NetworkStateTest, resetInternalStateUsingOriginTypeConnection) {
    NetworkState state(NetworkState::DHCPv4);

    // Test CONNECTION + COMMAND + HA types
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::HA);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetInternalState(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::HA);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test CONNECTION type only
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.disableService(NetworkState::Origin::CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.resetInternalState(NetworkState::Origin::CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that enableAll() enables the service. This test will be extended
// in the future to verify that it also enables disabled scopes.
TEST_F(NetworkStateTest, enableAll) {
    NetworkState state(NetworkState::DHCPv4);
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableAll();
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to setup delayed execution of enableAll
// function.
TEST_F(NetworkStateTest, delayedEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::Origin::COMMAND);
    state.delayedEnableAll(1);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 2 seconds, the service should be enabled.
    runIOService(2000);
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that explicitly enabling the service cancels the timer
// scheduled for automatically enabling it.
TEST_F(NetworkStateTest, earlyEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service.
    state.disableService(NetworkState::Origin::COMMAND);
    EXPECT_FALSE(state.isServiceEnabled());
    // Schedule enabling the service in 2 seconds.
    state.delayedEnableAll(2);
    // Explicitly enable the service.
    state.enableAll();
    // The timer should be now canceled and the service should be enabled.
    EXPECT_FALSE(state.isDelayedEnableAll());
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to call delayedEnableAll multiple times
// and that it results in only one timer being scheduled.
TEST_F(NetworkStateTest, multipleDelayedEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService(NetworkState::Origin::COMMAND);
    // Schedule the first timer for 5 seconds.
    state.delayedEnableAll(5);
    // When calling it the second time the old timer should be destroyed and
    // the timeout should be set to 2 seconds.
    state.delayedEnableAll(2);
    // Initially the service should be still disabled.
    EXPECT_FALSE(state.isServiceEnabled());
    // After running IO service for 3 seconds, the service should be enabled.
    runIOService(3000);
    EXPECT_TRUE(state.isServiceEnabled());
    // The timer should not be present, even though the first timer was created
    // with 5 seconds interval.
    EXPECT_FALSE(state.isDelayedEnableAll());
}

} // end of anonymous namespace
