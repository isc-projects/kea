// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <lease_cmds_log.h>

namespace isc {
namespace lease_cmds {

extern const int LEASE_CMDS_DBG_COMMAND_DATA = isc::log::DBGLVL_COMMAND_DATA;

isc::log::Logger lease_cmds_logger("lease-cmds-hooks");

}
}

