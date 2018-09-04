// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

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
        test_timer_.setup(boost::bind(&NetworkStateTest::testTimerCallback, this), timeout_ms,
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

// This test verifies that it is possible to disable and then enable DHCPv4 service.
TEST_F(NetworkStateTest, disableEnableService4) {
    NetworkState state(NetworkState::DHCPv4);
    state.disableService();
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService();
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to disable and then enable DHCPv6 service.
TEST_F(NetworkStateTest, disableEnableService6) {
    NetworkState state(NetworkState::DHCPv6);
    state.disableService();
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService();
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that enableAll() enables the service. This test will be extended
// in the future to verify that it also enables disabled scopes.
TEST_F(NetworkStateTest, enableAll) {
    NetworkState state(NetworkState::DHCPv4);
    state.disableService();
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableAll();
    EXPECT_TRUE(state.isServiceEnabled());
}

// This test verifies that it is possible to setup delayed execution of enableAll
// function.
TEST_F(NetworkStateTest, delayedEnableAll) {
    NetworkState state(NetworkState::DHCPv4);
    // Disable the service and then schedule enabling it in 1 second.
    state.disableService();
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
    state.disableService();
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
    state.disableService();
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
