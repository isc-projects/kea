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

    /// @brief This test verifies that enableAll() enables the service. This test will be
    /// extended in the future to verify that it also enables disabled scopes.
    void enableAllTest();

    /// @brief This test verifies that it is possible to setup delayed execution of enableAll
    /// function.
    void delayedEnableAllTest();

    /// @brief This test verifies that explicitly enabling the service cancels the timer
    /// scheduled for automatically enabling it.
    void earlyEnableAllTest();

    /// @brief This test verifies that it is possible to call delayedEnableAll multiple times
    /// and that it results in only one timer being scheduled.
    void multipleDelayedEnableAllTest();

    /// @brief This test verifies that it is possible to call delayedEnableAll multiple times
    /// from different origins and that it results in each timer being scheduled.
    void multipleDifferentOriginsDelayedEnableAllTest();

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
void
NetworkStateTest::disableEnableService4UsingHACommandOriginTest() {
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
// service using 'DB connection' origin.
void
NetworkStateTest::disableEnableService4UsingDBConnectionOriginTest() {
    NetworkState state(NetworkState::DHCPv4);

    // Test that enable/disable using 'DB connection' origin works
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'DB connection' origin uses internal counter
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
// 3. Disable using 'DB connection' origin 2 times (expect disabled state).
// 4. Enable using 'user command' origin 1 time (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 2 times (expect enabled state).
void
NetworkStateTest::disableEnableService4UsingMultipleOriginsTest() {
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
void
NetworkStateTest::disableEnableService6UsingUserCommandOriginTest() {
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
void
NetworkStateTest::disableEnableService6UsingHACommandOriginTest() {
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
// service using 'DB connection' origin.
void
NetworkStateTest::disableEnableService6UsingDBConnectionOriginTest() {
    NetworkState state(NetworkState::DHCPv6);

    // Test that enable/disable using 'DB connection' origin works
    state.disableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_FALSE(state.isServiceEnabled());
    state.enableService(NetworkState::Origin::DB_CONNECTION);
    EXPECT_TRUE(state.isServiceEnabled());

    // Test that using 'DB connection' origin uses internal counter
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
// 3. Disable using 'DB connection' origin 2 times (expect disabled state).
// 4. Enable using 'user command' origin 1 time (expect disabled state).
// 5. Enable using 'HA command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 2 times (expect enabled state).
void
NetworkStateTest::disableEnableService6UsingMultipleOriginsTest() {
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
// 3. Disable using 'DB connection' origin 1 time (expect disabled state).
// 4. Reset using 'HA command' origin (expect disabled state).
// 5. Enable using 'user command' origin 1 time (expect disabled state).
// 6. Enable using 'DB connection' origin 1 time (expect enabled state).
// 7. Disable using 'HA command' origin 3 times (expect disabled state).
// 8. Reset using 'HA command' origin (expect enabled state).
void
NetworkStateTest::resetUsingHACommandOriginTest() {
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
void
NetworkStateTest::enableAllTest() {
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
void
NetworkStateTest::delayedEnableAllTest() {
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
void
NetworkStateTest::earlyEnableAllTest() {
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
void
NetworkStateTest::multipleDelayedEnableAllTest() {
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
void
NetworkStateTest::multipleDifferentOriginsDelayedEnableAllTest() {
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

TEST_F(NetworkStateTest, enableAllTest) {
    enableAllTest();
}

TEST_F(NetworkStateTest, enableAllTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    enableAllTest();
}

TEST_F(NetworkStateTest, delayedEnableAllTest) {
    delayedEnableAllTest();
}

TEST_F(NetworkStateTest, delayedEnableAllTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    delayedEnableAllTest();
}

TEST_F(NetworkStateTest, earlyEnableAllTest) {
    earlyEnableAllTest();
}

TEST_F(NetworkStateTest, earlyEnableAllTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    earlyEnableAllTest();
}

TEST_F(NetworkStateTest, multipleDelayedEnableAllTest) {
    multipleDelayedEnableAllTest();
}

TEST_F(NetworkStateTest, multipleDelayedEnableAllTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    multipleDelayedEnableAllTest();
}

TEST_F(NetworkStateTest, multipleDifferentOriginsDelayedEnableAllTest) {
    multipleDifferentOriginsDelayedEnableAllTest();
}

TEST_F(NetworkStateTest, multipleDifferentOriginsDelayedEnableAllTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    multipleDifferentOriginsDelayedEnableAllTest();
}

} // end of anonymous namespace
