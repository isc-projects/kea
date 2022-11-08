// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <netconf/netconf_cfg_mgr.h>
#include <netconf/netconf_process.h>
#include <process/testutils/d_test_stubs.h>
#include <testutils/gtest_utils.h>

#include <functional>

using namespace isc;
using namespace isc::netconf;
using namespace isc::asiolink;
using namespace isc::process;

namespace {

/// @brief NetconfProcess test fixture class.
class NetconfProcessTest : public NetconfProcess, public ::testing::Test  {
public:
    /// @brief Constructor
    NetconfProcessTest() :
        NetconfProcess("netconf-test",
                       IOServicePtr(new isc::asiolink::IOService())) {
        NetconfConfigPtr ctx = getNetconfCfgMgr()->getNetconfConfig();
    }

    /// @brief Callback that will invoke shutdown method.
    void genShutdownCallback() {
        shutdown(isc::data::ElementPtr());
    }
};  // NetconfProcessTest

// Test construction of the NetconfProcess object.
TEST(NetconfProcess, construction) {
    // Verify that the constructor will fail if given an empty
    // io service.
    IOServicePtr lcl_io_service;
    EXPECT_THROW_MSG(NetconfProcess("TestProcess", lcl_io_service), DProcessBaseError,
                     "IO Service cannot be null");

    // Verify that the constructor succeeds with a valid io_service
    lcl_io_service.reset(new IOService());
    ASSERT_NO_THROW_LOG(NetconfProcess("TestProcess", lcl_io_service));

    // Verify tha the configuration is accessible after construction.
    NetconfProcess netconf_process("TestProcess", lcl_io_service);
    NetconfCfgMgrPtr cfg_mgr = netconf_process.getNetconfCfgMgr();
    ASSERT_TRUE(cfg_mgr);
}

// Verifies that en external call to shutdown causes the run method to
// exit gracefully.
TEST_F(NetconfProcessTest, shutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    IntervalTimer timer(*getIoService());
    timer.setup(std::bind(&NetconfProcessTest::genShutdownCallback, this),
                200);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_NO_THROW_LOG(run());

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 100 &&
                elapsed.total_milliseconds() <= 400);
}

}
