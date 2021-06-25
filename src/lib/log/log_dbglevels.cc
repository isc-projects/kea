// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

namespace isc {
namespace log {

/// This is given a value of 0 as that is the level selected if debugging is
/// enabled without giving a level.
extern const int DBGLVL_START_SHUT = 0;
extern const int DBGLVL_COMMAND = 10;
extern const int DBGLVL_PKT_HANDLING = 15;
extern const int DBGLVL_COMMAND_DATA = 20;

extern const int DBGLVL_TRACE_BASIC = 40;
extern const int DBGLVL_TRACE_BASIC_DATA = 45;
extern const int DBGLVL_TRACE_DETAIL = 50;
extern const int DBGLVL_TRACE_DETAIL_DATA = 55;

}
}
