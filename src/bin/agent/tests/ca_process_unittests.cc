// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_cfg_mgr.h>
#include <agent/ca_process.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <process/testutils/d_test_stubs.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <functional>

using namespace boost::posix_time;
using namespace isc;
using namespace isc::agent;
using namespace isc::asiolink;
using namespace isc::process;

namespace {

/// @brief CtrlAgentProcess test fixture class.
class CtrlAgentProcessTest : public CtrlAgentProcess, public ::testing::Test  {
public:
    /// @brief Constructor
    CtrlAgentProcessTest() :
        CtrlAgentProcess("agent-test",
                         IOServicePtr(new isc::asiolink::IOService())) {
        CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgMgr()->getCtrlAgentCfgContext();
        ctx->setHttpHost("127.0.0.1");
        ctx->setHttpPort(8081);
    }

    /// @brief Destructor
    virtual ~CtrlAgentProcessTest() {
    }

    /// @brief Callback that will invoke shutdown method.
    void genShutdownCallback() {
        shutdown(isc::data::ConstElementPtr());
    }
};

// Test construction of the CtrlAgentProcess object.
TEST(CtrlAgentProcess, construction) {
    // Verify that the constructor will fail if given an empty
    // io service.
    IOServicePtr lcl_io_service;
    EXPECT_THROW(CtrlAgentProcess("TestProcess", lcl_io_service),
                 DProcessBaseError);

    // Verify that the constructor succeeds with a valid io_service
    lcl_io_service.reset(new IOService());
    ASSERT_NO_THROW(CtrlAgentProcess("TestProcess", lcl_io_service));

    // Verify tha the configuration is accessible after construction.
    CtrlAgentProcess agent_process("TestProcess", lcl_io_service);
    CtrlAgentCfgMgrPtr cfg_mgr = agent_process.getCtrlAgentCfgMgr();
    ASSERT_TRUE(cfg_mgr);
}

// Verifies that en external call to shutdown causes the run method to
// exit gracefully.
TEST_F(CtrlAgentProcessTest, shutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    IntervalTimer timer(*getIoService());
    timer.setup(std::bind(&CtrlAgentProcessTest::genShutdownCallback, this),
                200);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_NO_THROW(run());

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
