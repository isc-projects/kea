// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_service_states.h>

namespace isc {
namespace ha {

std::string stateToString(int state) {
    switch (state) {
    case HA_BACKUP_ST:
        return ("backup");
    case HA_COMMUNICATION_RECOVERY_ST:
        return ("communication-recovery");
    case HA_HOT_STANDBY_ST:
        return ("hot-standby");
    case HA_LOAD_BALANCING_ST:
        return ("load-balancing");
    case HA_IN_MAINTENANCE_ST:
        return ("in-maintenance");
    case HA_PARTNER_DOWN_ST:
        return ("partner-down");
    case HA_PARTNER_IN_MAINTENANCE_ST:
        return ("partner-in-maintenance");
    case HA_PASSIVE_BACKUP_ST:
        return ("passive-backup");
    case HA_READY_ST:
        return ("ready");
    case HA_SYNCING_ST:
        return ("syncing");
    case HA_TERMINATED_ST:
        return ("terminated");
    case HA_WAITING_ST:
        return ("waiting");
    case HA_UNAVAILABLE_ST:
        return ("unavailable");
    default:
        ;
    }

    isc_throw(BadValue, "unknown state identifier " << state);
}

int stringToState(const std::string& state_name) {
    if (state_name == "backup") {
        return (HA_BACKUP_ST);

    } else if (state_name == "communication-recovery") {
        return (HA_COMMUNICATION_RECOVERY_ST);

    } else if (state_name == "hot-standby") {
        return (HA_HOT_STANDBY_ST);

    } else if (state_name == "load-balancing") {
        return (HA_LOAD_BALANCING_ST);

    } else if (state_name == "in-maintenance") {
        return (HA_IN_MAINTENANCE_ST);

    } else if (state_name == "partner-down") {
        return (HA_PARTNER_DOWN_ST);

    } else if (state_name == "partner-in-maintenance") {
        return (HA_PARTNER_IN_MAINTENANCE_ST);

    } else if (state_name == "passive-backup") {
        return (HA_PASSIVE_BACKUP_ST);

    } else if (state_name == "ready") {
        return (HA_READY_ST);

    } else if (state_name == "syncing") {
        return (HA_SYNCING_ST);

    } else if (state_name == "terminated") {
        return (HA_TERMINATED_ST);

    } else if (state_name == "waiting") {
        return (HA_WAITING_ST);

    } else if (state_name == "unavailable") {
        return (HA_UNAVAILABLE_ST);
    }

    isc_throw(BadValue, "unknown state " << state_name);
}

} // end of namespace isc::ha 
} // end of namespace isc
