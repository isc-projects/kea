// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <d_test_stubs.h>
#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2/spec_config.h>

#include <boost/pointer_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <sstream>

using namespace boost::posix_time;

namespace isc {
namespace d2 {

/// @brief Test fixture class for testing D2Controller class. This class
/// derives from DControllerTest and wraps a D2Controller.  Much of the
/// underlying functionality is in the DControllerBase class which has an
/// extensive set of unit tests that are independent of DHCP-DDNS.
/// @TODO Currently These tests are relatively light and duplicate some of
/// the testing done on the base class.  These tests are sufficient to ensure
/// that D2Controller properly derives from its base class and to test the
/// logic that is unique to D2Controller. These tests will be augmented and
/// or new tests added as additional functionality evolves.
/// Unlike the stub testing, there is no use of SimFailure to induce error
/// conditions as this is production code.
class D2ControllerTest : public DControllerTest {
public:
    /// @brief Constructor
    /// Note the constructor passes in the static D2Controller instance
    /// method.
    D2ControllerTest() : DControllerTest(D2Controller::instance) {
    }

    /// @brief Fetches the D2Controller's D2Process
    ///
    /// @return A pointer to the process which may be null if it has not yet
    /// been instantiated.
    D2ProcessPtr getD2Process() {
        return (boost::dynamic_pointer_cast<D2Process>(getProcess()));
    }

    /// @brief Fetches the D2Process's D2Configuration manager
    ///
    /// @return A pointer to the manager which may be null if it has not yet
    /// been instantiated.
    D2CfgMgrPtr getD2CfgMgr() {
        D2CfgMgrPtr p;
        if (getD2Process()) {
            p = getD2Process()->getD2CfgMgr();
        }

        return (p);
    }

    /// @brief Fetches the D2Configuration manager's D2CfgContext
    ///
    /// @return A pointer to the context which may be null if it has not yet
    /// been instantiated.
    D2CfgContextPtr getD2CfgContext() {
        D2CfgContextPtr p;
        if (getD2CfgMgr()) {
            p = getD2CfgMgr()->getD2CfgContext();
        }

        return (p);
    }
};

/// @brief Basic Controller instantiation testing.
/// Verifies that the controller singleton gets created and that the
/// basic derivation from the base class is intact.
TEST_F(D2ControllerTest, basicInstanceTesting) {
    // Verify the we can the singleton instance can be fetched and that
    // it is the correct type.
    DControllerBasePtr& controller = DControllerTest::getController();
    ASSERT_TRUE(controller);
    ASSERT_NO_THROW(boost::dynamic_pointer_cast<D2Controller>(controller));

    // Verify that controller's app name is correct.
    EXPECT_TRUE(checkAppName(D2Controller::d2_app_name_));

    // Verify that controller's bin name is correct.
    EXPECT_TRUE(checkBinName(D2Controller::d2_bin_name_));

    // Verify that controller's spec file name is correct.
    EXPECT_TRUE(checkSpecFileName(D2_SPECFILE_LOCATION));

    // Verify that controller's IOService exists.
    EXPECT_TRUE(checkIOService());

    // Verify that the Process does NOT exist.
    EXPECT_FALSE(checkProcess());
}

/// @brief Tests basic command line processing.
/// Verifies that:
/// 1. Standard command line options are supported.
/// 2. Invalid options are detected.
TEST_F(D2ControllerTest, commandLineArgs) {
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

/// @brief Tests application process creation and initialization.
/// Verifies that the process can be successfully created and initialized.
TEST_F(D2ControllerTest, initProcessTesting) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());
}

/// @brief Tests launch and normal shutdown (stand alone mode).
/// This creates an interval timer to generate a normal shutdown and then
/// launches with a valid, stand-alone command line and no simulated errors.
TEST_F(D2ControllerTest, launchNormalShutdown) {
    // Write valid_d2_config and then run launch() for 1000 ms.
    time_duration elapsed_time;
    runWithConfig(valid_d2_config, 1000, elapsed_time);

    // Give a generous margin to accomodate slower test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() >= 800 &&
                elapsed_time.total_milliseconds() <= 1300);
}

/// @brief Configuration update event testing.
/// This really tests just the ability of the handlers to invoke the necessary
/// chain of methods and handle error conditions. Configuration parsing and
/// retrieval should be tested as part of the d2 configuration management
/// implementation.
/// This test verifies that:
/// 1. A valid configuration yields a successful parse result.
/// 2. That an application process error in configuration updating is handled
/// properly.
TEST_F(D2ControllerTest, configUpdateTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;

    // Initialize the application process.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Create a configuration set using a small, valid D2 configuration.
    isc::data::ElementPtr config_set =
                                isc::data::Element::fromJSON(valid_d2_config);

    // Verify that given a valid config we get a successful update result.
    answer = updateConfig(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);

    // Use an invalid configuration to verify parsing error return.
    std::string config = "{ \"bogus\": 1000 } ";
    config_set = isc::data::Element::fromJSON(config);
    answer = updateConfig(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(1, rcode);
}

/// @brief Command execution tests.
/// This really tests just the ability of the handler to invoke the necessary
/// chain of methods and to handle error conditions.
/// This test verifies that:
/// 1. That an unrecognized command is detected and returns a status of
/// d2::COMMAND_INVALID.
/// 2. Shutdown command is recognized and returns a d2::COMMAND_SUCCESS status.
TEST_F(D2ControllerTest, executeCommandTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;
    isc::data::ElementPtr arg_set;

    // Initialize the application process.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Verify that an unknown command returns an COMMAND_INVALID response.
    std::string bogus_command("bogus");
    answer = executeCommand(bogus_command, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_INVALID, rcode);

    // Verify that shutdown command returns COMMAND_SUCCESS response.
    //answer = executeCommand(SHUT_DOWN_COMMAND, isc::data::ElementPtr());
    answer = executeCommand(SHUT_DOWN_COMMAND, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);
}

// Tests that the original configuration is retained after a SIGHUP triggered
// reconfiguration fails due to invalid config content.
TEST_F(D2ControllerTest, invalidConfigReload) {
    // Schedule to replace the configuration file after launch. This way the
    // file is updated after we have done the initial configuration.
    scheduleTimedWrite("{ \"string_test\": BOGUS JSON }", 100);

    // Setup to raise SIGHUP in 200 ms.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);

    // Write valid_d2_config and then run launch() for a maximum of 500 ms.
    time_duration elapsed_time;
    runWithConfig(valid_d2_config, 500, elapsed_time);

    // Context is still available post launch.
    // Check to see that our configuration matches the original per
    // valid_d2_config (see d_test_stubs.cc)
    D2CfgMgrPtr d2_cfg_mgr = getD2CfgMgr();
    D2ParamsPtr d2_params = d2_cfg_mgr->getD2Params();
    ASSERT_TRUE(d2_params);

    EXPECT_EQ("127.0.0.1", d2_params->getIpAddress().toText());
    EXPECT_EQ(5031, d2_params->getPort());
    EXPECT_TRUE(d2_cfg_mgr->forwardUpdatesEnabled());
    EXPECT_TRUE(d2_cfg_mgr->reverseUpdatesEnabled());

    /// @todo add a way to trap log file and search it
}

// Tests that the original configuration is replaced after a SIGHUP triggered
// reconfiguration succeeds.
TEST_F(D2ControllerTest, validConfigReload) {
    // Define a replacement config.
    const char* second_cfg =
            "{"
            " \"ip-address\": \"192.168.77.1\" , "
            " \"port\": 777 , "
            "\"tsig-keys\": [], "
            "\"forward-ddns\" : {}, "
            "\"reverse-ddns\" : {} "
            "}";

    // Schedule to replace the configuration file after launch. This way the
    // file is updated after we have done the initial configuration.
    scheduleTimedWrite(second_cfg, 100);

    // Setup to raise SIGHUP in 200 ms.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);

    // Write valid_d2_config and then run launch() for a maximum of 500ms.
    time_duration elapsed_time;
    runWithConfig(valid_d2_config, 500, elapsed_time);

    // Context is still available post launch.
    // Check to see that our configuration matches the replacement config.
    D2CfgMgrPtr d2_cfg_mgr = getD2CfgMgr();
    D2ParamsPtr d2_params = d2_cfg_mgr->getD2Params();
    ASSERT_TRUE(d2_params);

    EXPECT_EQ("192.168.77.1", d2_params->getIpAddress().toText());
    EXPECT_EQ(777, d2_params->getPort());
    EXPECT_FALSE(d2_cfg_mgr->forwardUpdatesEnabled());
    EXPECT_FALSE(d2_cfg_mgr->reverseUpdatesEnabled());

    /// @todo add a way to trap log file and search it
}

// Tests that the SIGINT triggers a normal shutdown.
TEST_F(D2ControllerTest, sigintShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGINT, 1);

    // Write valid_d2_config and then run launch() for a maximum of 1000 ms.
    time_duration elapsed_time;
    runWithConfig(valid_d2_config, 1000, elapsed_time);

    // Signaled shutdown should make our elapsed time much smaller than
    // the maximum run time.  Give generous margin to accomodate slow
    // test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);

    /// @todo add a way to trap log file and search it
}

// Tests that the SIGTERM triggers a normal shutdown.
TEST_F(D2ControllerTest, sigtermShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGTERM, 1);

    // Write valid_d2_config and then run launch() for a maximum of 1 s.
    time_duration elapsed_time;
    runWithConfig(valid_d2_config, 1000, elapsed_time);

    // Signaled shutdown should make our elapsed time much smaller than
    // the maximum run time.  Give generous margin to accomodate slow
    // test environs.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);

    /// @todo add a way to trap log file and search it
}

}; // end of isc::d2 namespace
}; // end of isc namespace
