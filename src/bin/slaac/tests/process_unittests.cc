// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/slaac_cfg_mgr.h>
#include <slaac/slaac_process.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <process/testutils/d_test_stubs.h>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

using namespace boost::posix_time;
using namespace isc;
using namespace isc::slaac;
using namespace isc::asiolink;
using namespace isc::process;

namespace {

/// @brief SlaacProcess test fixture class.
class SlaacProcessTest : public SlaacProcess, public ::testing::Test  {
public:
    /// @brief Constructor
    SlaacProcessTest() :
        SlaacProcess("agent-test",
                         IOServicePtr(new isc::asiolink::IOService())) {
        SlaacConfigPtr ctx = getSlaacCfgMgr()->getSlaacConfig();

        /// @todo: put some defaults here
    }

    /// @brief Destructor
    virtual ~SlaacProcessTest() {
    }

    /// @brief Callback that will invoke shutdown method.
    void genShutdownCallback() {
        shutdown(isc::data::ConstElementPtr());
    }
};

// Test construction of the SlaacProcess object.
TEST(SlaacProcess, construction) {
    // Verify that the constructor will fail if given an empty
    // io service.
    IOServicePtr lcl_io_service;
    EXPECT_THROW(SlaacProcess("TestProcess", lcl_io_service),
                 DProcessBaseError);

    // Verify that the constructor succeeds with a valid io_service
    lcl_io_service.reset(new IOService());
    ASSERT_NO_THROW(SlaacProcess("TestProcess", lcl_io_service));

    // Verify tha the configuration is accessible after construction.
    SlaacProcess agent_process("TestProcess", lcl_io_service);
    SlaacCfgMgrPtr cfg_mgr = agent_process.getSlaacCfgMgr();
    ASSERT_TRUE(cfg_mgr);
}

// Verifies that en external call to shutdown causes the run method to
// exit gracefully.
TEST_F(SlaacProcessTest, shutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    IntervalTimer timer(*getIoService());
    timer.setup(boost::bind(&SlaacProcessTest::genShutdownCallback, this),
                2 * 100);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_NO_THROW(run());

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 190 &&
                elapsed.total_milliseconds() <= 220);
}


}
