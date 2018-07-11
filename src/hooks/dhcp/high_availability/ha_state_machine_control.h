// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_STATE_MACHINE_CONTROL_H
#define HA_STATE_MACHINE_CONTROL_H

#include <ha_config.h>
#include <boost/shared_ptr.hpp>
#include <set>

namespace isc {
namespace ha {

/// @brief Hold runtime information about HA state machine.
///
/// Currently, the only available runtime information is whether the
/// state machine is paused and if it should paused in certain states
/// upon next transition to these states. Note that the server may be
/// configured to only pause the state machine upon the first transition
/// to the certain states.
///
/// The @c HAService calls @c notify upon transition to the next state.
/// This class determines whether the state machine should be paused
/// in this state based on the provided configuration and the history
/// of already visited states. The @c amPaused method should be later
/// called in the state handlers to check if the state machine is
/// paused or running. In the former case, it should not transition to
/// any other state until the state machine is unpaused.
class HAStateMachineControl {
public:

    /// @brief Constructor.
    ///
    /// @param config HA hooks library configuration.
    explicit HAStateMachineControl(const HAConfigPtr& config);

    /// @brief Receives notification from the HA state handlers about
    /// the current state.
    ///
    /// This method pauses sets a flag to pause the HA state machine if
    /// it should be paused in the given state. It also records that
    /// state as "visited", so as it is possible to determine whether
    /// the state machine should be paused the next time it transitions
    /// to this state.
    ///
    /// @param state current state of the state machine.
    /// @throw BadValue if the state is not recognized.
    void notify(int state);

    /// @brief Informs whether the state machine is paused.
    ///
    /// @return true if the state machine is paused, false otherwise.
    bool amPaused() const {
        return (paused_);
    }

    /// @brief Clears flag indicating that the state machine is paused.
    void unpause();

private:

    /// @brief HA configuration
    HAConfigPtr config_;

    /// @brief Boolean flag indicating if the state machine is paused.
    bool paused_;

    /// @brief Keeps track of visited states.
    std::set<int> visited_states_;
};

/// @brief Shared pointer to the @c HAStateMachineControl.
typedef boost::shared_ptr<HAStateMachineControl> HAStateMachineControlPtr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
