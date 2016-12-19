// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ctrl_agent_controller.h>
#include <agent/ctrl_agent_process.h>
#include <process/testutils/d_test_stubs.h>
#include <boost/pointer_cast.hpp>

using namespace isc::agent;
using namespace isc::process;

namespace {

/// @brief Valid Control Agent Config used in tests.
/// @todo Use actual config once configuration parsing is implemented.
const char* valid_agent_config = "{ }";

/// @brief test fixture class for testing CtrlAgentController class. This
/// class derives from DControllerTest and wraps CtrlAgentController. Much
/// of the underlying functionality is in the DControllerBase class which
/// has extensive set of unit tests that are independent from the Control
/// Agent.
class CtrlAgentControllerTest : public DControllerTest {
public:

    /// @brief Constructor.
    CtrlAgentControllerTest()
        : DControllerTest(CtrlAgentController::instance) {
    }

};

// Basic Controller instantiation testing.
// Verifies that the controller singleton gets created and that the
// basic derivation from the base class is intact.
TEST_F(CtrlAgentControllerTest, basicInstanceTesting) {
    // Verify the we can the singleton instance can be fetched and that
    // it is the correct type.
    DControllerBasePtr& controller = DControllerTest::getController();
    ASSERT_TRUE(controller);
    ASSERT_NO_THROW(boost::dynamic_pointer_cast<CtrlAgentController>(controller));

    // Verify that controller's app name is correct.
    EXPECT_TRUE(checkAppName(CtrlAgentController::agent_app_name_));

    // Verify that controller's bin name is correct.
    EXPECT_TRUE(checkBinName(CtrlAgentController::agent_bin_name_));

    // Verify that controller's IOService exists.
    EXPECT_TRUE(checkIOService());

    // Verify that the Process does NOT exist.
    EXPECT_FALSE(checkProcess());
}


// Tests basic command line processing.
// Verifies that:
// 1. Standard command line options are supported.
// 2. Invalid options are detected.
TEST_F(CtrlAgentControllerTest, commandLineArgs) {
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-c"),
                     const_cast<char*>(DControllerTest::CFG_TEST_FILE),
                     const_cast<char*>("-d") };
    int argc = 4;

    // Verify that verbose flag is false initially.
    EXPECT_TRUE(checkVerbose(false));

    // Verify that standard options can be parsed without error.
    EXPECT_NO_THROW(parseArgs(argc, argv));

    // Verify that verbose flag is true.
    EXPECT_TRUE(checkVerbose(true));

    // Verify configuration file name is correct.
    EXPECT_TRUE(checkConfigFileName(DControllerTest::CFG_TEST_FILE));

    // Verify that an unknown option is detected.
    char* argv2[] = { const_cast<char*>("progName"),
                      const_cast<char*>("-x") };
    argc = 2;
    EXPECT_THROW(parseArgs(argc, argv2), InvalidUsage);
}

// Tests application process creation and initialization.
// Verifies that the process can be successfully created and initialized.
TEST_F(CtrlAgentControllerTest, initProcessTesting) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());
}

// Tests launch and normal shutdown (stand alone mode).
// This creates an interval timer to generate a normal shutdown and then
// launches with a valid, stand-alone command line and no simulated errors.
TEST_F(CtrlAgentControllerTest, launchNormalShutdown) {
    // Write valid_agent_config and then run launch() for 1000 ms.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 1000, elapsed_time);

    // Give a generous margin to accommodate slower test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() >= 800 &&
                elapsed_time.total_milliseconds() <= 1300);
}

// Tests that the SIGINT triggers a normal shutdown.
TEST_F(CtrlAgentControllerTest, sigintShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGINT, 1);

    // Write valid_agent_config and then run launch() for a maximum
    // of 1000 ms.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 1000, elapsed_time);

    // Signaled shutdown should make our elapsed time much smaller than
    // the maximum run time.  Give generous margin to accommodate slow
    // test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);
}

// Tests that the SIGTERM triggers a normal shutdown.
TEST_F(CtrlAgentControllerTest, sigtermShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGTERM, 1);

    // Write valid_agent_config and then run launch() for a maximum of 1 s.
    time_duration elapsed_time;
    runWithConfig(valid_agent_config, 1000, elapsed_time);

    // Signaled shutdown should make our elapsed time much smaller than
    // the maximum run time.  Give generous margin to accommodate slow
    // test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);
}

}
