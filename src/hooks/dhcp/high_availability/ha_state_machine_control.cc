// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <ha_state_machine_control.h>

namespace isc {
namespace ha {

HAStateMachineControl::HAStateMachineControl(const HAConfigPtr& config)
    : config_(config), paused_(false), visited_states_() {
}

void
HAStateMachineControl::notify(const int state) {
    // Always get the configuration to verify that the state identifier is
    // recognized.
    HAConfig::StateConfigPtr state_config = config_->getStateConfig(state);

    // Pause if we should always pause in this state or we should pause once
    // and this is the first time we visit this state.
    bool first_visit = (visited_states_.count(state) == 0);

    // If this is the first time we're in this state, record it.
    if (first_visit) {
        visited_states_.insert(state);
    }

    // Only pause the state machine if it is not paused already.
    if (!amPaused()) {
        if ((state_config->getPausing() == HAConfig::StateConfig::PAUSE_ALWAYS) ||
            ((state_config->getPausing() == HAConfig::StateConfig::PAUSE_ONCE) &&
             first_visit)) {
            paused_ = true;
        }
    }
}

} // end of namespace isc::ha
} // end of namespace isc
