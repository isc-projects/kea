// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <ha_state_machine_control.h>
#include <ha_test.h>
#include <gtest/gtest.h>

using namespace isc::ha;
using namespace isc::ha::test;

namespace {

class HAStateMachineControlTest : public HATest {
public:

    /// @brief Constructor.
    HAStateMachineControlTest()
        : HATest() {
    }

};

// This test verifies that pausing HA state machine works as expected.
TEST_F(HAStateMachineControlTest, pause) {
    HAConfigPtr config = createValidConfiguration();

    // Always pause in the waiting state and pause on first transition to
    // the ready state. Do not pause for other states.
    config->getStateMachineConfig()->getStateConfig(HA_WAITING_ST)->setPausing("always");
    config->getStateMachineConfig()->getStateConfig(HA_READY_ST)->setPausing("once");

    // Initially we shouldn't be paused.
    HAStateMachineControl control(config);
    EXPECT_FALSE(control.amPaused());

    // Should not pause in load-balancing state.
    EXPECT_NO_THROW(control.notify(HA_LOAD_BALANCING_ST));
    EXPECT_FALSE(control.amPaused());

    // Should always pause in waiting state.
    EXPECT_NO_THROW(control.notify(HA_WAITING_ST));
    EXPECT_TRUE(control.amPaused());

    control.unpause();
    EXPECT_FALSE(control.amPaused());

    // Should pause once in the ready state.
    EXPECT_NO_THROW(control.notify(HA_READY_ST));
    EXPECT_TRUE(control.amPaused());

    control.unpause();
    EXPECT_FALSE(control.amPaused());

    // Do not pause the second time in the ready state.
    EXPECT_NO_THROW(control.notify(HA_READY_ST));
    EXPECT_FALSE(control.amPaused());

    // Never pause in the load-balancing state.
    EXPECT_NO_THROW(control.notify(HA_LOAD_BALANCING_ST));
    EXPECT_FALSE(control.amPaused());

    // Always pause in the waiting state.
    EXPECT_NO_THROW(control.notify(HA_WAITING_ST));
    EXPECT_TRUE(control.amPaused());
}

}
