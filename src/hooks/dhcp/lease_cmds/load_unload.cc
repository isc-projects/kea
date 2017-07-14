// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>
#include <lease_cmds.h>
#include <lease_cmds_log.h>
#include <string>
#include <hooks/hooks.h>
#include <exceptions/exceptions.h>

using namespace isc::hooks;
using namespace isc::lease_cmds;

boost::shared_ptr<LeaseCmds> instance;

extern "C" {

/// @brief This function is called when the library is loaded.
///
/// This function creates LeaseCmds object that registers
/// additional commands.
///
/// @param handle library handle (ignored)
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& /*handle*/) {

    try {
        instance.reset(new LeaseCmds());
    } catch (const isc::Unexpected& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_INIT_FAILED)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(lease_cmds_logger, LEASE_CMDS_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// This function creates LeaseCmds object that deregisters
/// additional commands.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    try {
        instance.reset();
    } catch (const isc::Unexpected& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_DEINIT_FAILED)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(lease_cmds_logger, LEASE_CMDS_DEINIT_OK);
    return (0);
}

}
