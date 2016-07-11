// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::dhcp;

// This set of tests only check the parsing functions of LeaseMgrFactory.
// Tests of the LeaseMgr create/instance/destroy are implicitly carried out
// in the tests for the different concrete lease managers (e.g. MySqlLeaseMgr).

// Currently there are no unit-tests as the sole testable method (parse)
// was moved to its own class (DataSource). All existing unit-tests were
// moved there.

namespace {

}; // end of anonymous namespace
