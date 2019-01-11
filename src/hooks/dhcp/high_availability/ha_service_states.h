// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_SERVICE_STATES_H
#define HA_SERVICE_STATES_H

#include <util/state_model.h>
#include <string>

namespace isc {
namespace ha {

/// Backup state.
const int HA_BACKUP_ST = util::StateModel::SM_DERIVED_STATE_MIN + 1;

/// Hot standby state.
const int HA_HOT_STANDBY_ST = util::StateModel::SM_DERIVED_STATE_MIN + 2;

/// Load balancing state.
const int HA_LOAD_BALANCING_ST = util::StateModel::SM_DERIVED_STATE_MIN + 3;

/// Partner down state.
const int HA_PARTNER_DOWN_ST = util::StateModel::SM_DERIVED_STATE_MIN + 4;

/// Server ready state, i.e. synchronized database, can enable DHCP service.
const int HA_READY_ST = util::StateModel::SM_DERIVED_STATE_MIN + 5;

/// Synchronizing database state.
const int HA_SYNCING_ST = util::StateModel::SM_DERIVED_STATE_MIN + 6;

/// HA service terminated state.
const int HA_TERMINATED_ST = util::StateModel::SM_DERIVED_STATE_MIN + 7;

/// Server waiting state, i.e. waiting for another server to be ready.
const int HA_WAITING_ST = util::StateModel::SM_DERIVED_STATE_MIN + 8;

/// Special state indicating that this server is unable to communicate with
/// the partner.
const int HA_UNAVAILABLE_ST = util::StateModel::SM_DERIVED_STATE_MIN + 1000;

/// @brief Returns state name.
///
/// @param state state identifier for which name should be returned.
///
/// @throw BadValue if the state identifier is unsupported.
std::string stateToString(int state);

/// @brief Returns state for a given name.
///
/// @param state_name name of the state to be returned.
///
/// @throw BadValue if the state name is unsupported.
int stringToState(const std::string& state_name);

} // end of namespace isc::ha
} // end of namespace isc

#endif
