// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/hooks_manager.h>
#include <testutils/gtest_utils.h>
#include <testutils/lib_load_test_fixture.h>

namespace isc {
namespace test {

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::process;
using namespace isc::hooks;

void
LibLoadTest::validDaemonTest(const std::string& daemon_name, uint16_t family,
                             const ElementPtr& params) {
    // Set family and daemon's proc name.
    CfgMgr::instance().setFamily(family);
    process::Daemon::setProcName(daemon_name);

    clearLibraries();

    // Adding the library to the list of libraries should work.
    ASSERT_NO_THROW_LOG(addLibrary(lib_so_name_, params));

    // Should be able to load and unload the library more than once.
    ASSERT_NO_THROW_LOG(loadLibraries());
    ASSERT_NO_THROW_LOG(unloadLibraries());

    ASSERT_NO_THROW_LOG(loadLibraries());
    ASSERT_NO_THROW_LOG(unloadLibraries());
}

void
LibLoadTest::invalidDaemonTest(const std::string& daemon_name, uint16_t family,
                               const ElementPtr& params) {
    // Set family and daemon's proc name.
    CfgMgr::instance().setFamily(family);
    process::Daemon::setProcName(daemon_name);

    clearLibraries();

    // Adding the library to the list of libraries should work.
    ASSERT_NO_THROW_LOG(addLibrary(lib_so_name_, params));

    // Loading the library should fail.
    ASSERT_FALSE(loadLibraries()) << "library: " << lib_so_name_
            << ", should not have loaded for: " << daemon_name;
}

}; // end of isc::test namespace
}; // end of isc namespace
