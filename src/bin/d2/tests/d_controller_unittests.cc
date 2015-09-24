// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <cc/command_interpreter.h>
#include <d_test_stubs.h>
#include <d2/spec_config.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <sstream>

using namespace boost::posix_time;

namespace isc {
namespace d2 {

/// @brief Test fixture class for testing DControllerBase class. This class
/// derives from DControllerTest and wraps a DStubController.  DStubController
/// has been constructed to exercise DControllerBase.
class DStubControllerTest : public DControllerTest {
public:
    /// @brief Constructor.
    /// Note the constructor passes in the static DStubController instance
    /// method.
    DStubControllerTest() : DControllerTest (DStubController::instance) {
        controller_ = boost::dynamic_pointer_cast<DStubController>
                                                 (DControllerTest::
                                                  getController());
    }

    DStubControllerPtr controller_;
};

/// @brief Basic Controller instantiation testing.
/// Verfies that the controller singleton gets created and that the
/// basic derivation from the base class is intact.
TEST_F(DStubControllerTest, basicInstanceTesting) {
    // Verify that the singleton exists and it is the correct type.
    DControllerBasePtr& controller = DControllerTest::getController();
    ASSERT_TRUE(controller);
    ASSERT_NO_THROW(boost::dynamic_pointer_cast<DStubController>(controller));

    // Verify that controller's app name is correct.
    EXPECT_TRUE(checkAppName(DStubController::stub_app_name_));

    // Verify that controller's bin name is correct.
    EXPECT_TRUE(checkBinName(DStubController::stub_bin_name_));

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
/// 2. Custom command line options are supported.
/// 3. Invalid options are detected.
/// 4. Extraneous command line information is detected.
TEST_F(DStubControllerTest, commandLineArgs) {

    // Verify that verbose flag is false initially.
    EXPECT_TRUE(checkVerbose(false));

    // Verify that standard options can be parsed without error.
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("cfgName"),
                     const_cast<char*>("-d") };
    int argc = 4;
    EXPECT_NO_THROW(parseArgs(argc, argv));

    // Verify that verbose is true.
    EXPECT_TRUE(checkVerbose(true));

    // Verify configuration file name is correct
    EXPECT_TRUE(checkConfigFileName("cfgName"));

    // Verify that the custom command line option is parsed without error.
    char xopt[3] = "- ";
    xopt[1] =  *DStubController::stub_option_x_;
    char* argv1[] = { const_cast<char*>("progName"), xopt};
    argc = 2;
    EXPECT_NO_THROW (parseArgs(argc, argv1));

    // Verify that an unknown option is detected.
    char* argv2[] = { const_cast<char*>("progName"),
                      const_cast<char*>("-bs") };
    argc = 2;
    EXPECT_THROW (parseArgs(argc, argv2), InvalidUsage);

    // Verify that extraneous information is detected.
    char* argv3[] = { const_cast<char*>("progName"),
                      const_cast<char*>("extra"),
                      const_cast<char*>("information") };
    argc = 3;
    EXPECT_THROW (parseArgs(argc, argv3), InvalidUsage);
}

/// @brief Tests application process creation and initialization.
/// Verifies that:
/// 1. An error during process creation is handled.
/// 2. A NULL returned by process creation is handled.
/// 3. An error during process initialization is handled.
/// 4. Process can be successfully created and initialized.
TEST_F(DStubControllerTest, initProcessTesting) {
    // Verify that a failure during process creation is caught.
    SimFailure::set(SimFailure::ftCreateProcessException);
    EXPECT_THROW(initProcess(), DControllerBaseError);
    EXPECT_FALSE(checkProcess());

    // Verify that a NULL returned by process creation is handled.
    SimFailure::set(SimFailure::ftCreateProcessNull);
    EXPECT_THROW(initProcess(), DControllerBaseError);
    EXPECT_FALSE(checkProcess());

    // Re-create controller, verify that we are starting clean
    resetController();
    EXPECT_FALSE(checkProcess());

    // Verify that an error during process initialization is handled.
    SimFailure::set(SimFailure::ftProcessInit);
    EXPECT_THROW(initProcess(), DProcessBaseError);

    // Re-create controller, verify that we are starting clean
    resetController();
    EXPECT_FALSE(checkProcess());

    // Verify that the application process can created and initialized.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());
}

/// @brief Tests launch handling of invalid command line.
/// This test launches with an invalid command line which should throw
/// an InvalidUsage.
TEST_F(DStubControllerTest, launchInvalidUsage) {
    // Command line to run integrated
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-z") };
    int argc = 2;

    // Launch the controller in integrated mode.
    EXPECT_THROW(launch(argc, argv), InvalidUsage);
}

/// @brief Tests launch handling of failure in application process
/// initialization.  This test launches with a valid command line but with
/// SimFailure set to fail during process creation.  Launch should throw
/// ProcessInitError.
TEST_F(DStubControllerTest, launchProcessInitError) {
    // Command line to run integrated
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-c"),
                     const_cast<char*>(DControllerTest::CFG_TEST_FILE),
                     const_cast<char*>("-d") };
    int argc = 4;

    // Launch the controller in stand alone mode.
    SimFailure::set(SimFailure::ftCreateProcessException);
    EXPECT_THROW(launch(argc, argv), ProcessInitError);
}

/// @brief Tests launch and normal shutdown (stand alone mode).
/// This creates an interval timer to generate a normal shutdown and then
/// launches with a valid, command line, with a valid configuration file
///  and no simulated errors.
TEST_F(DStubControllerTest, launchNormalShutdown) {
    // Write the valid, empty, config and then run launch() for 1000 ms
    time_duration elapsed_time;
    ASSERT_NO_THROW(runWithConfig("{}", 2000, elapsed_time));

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    EXPECT_TRUE(elapsed_time.total_milliseconds() >= 1900 &&
                elapsed_time.total_milliseconds() <= 2300);
}

/// @brief Tests launch with an nonexistant configuration file.
TEST_F(DStubControllerTest, nonexistantConfigFile) {
    // command line to run standalone
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("bogus-file"),
                     const_cast<char*>("-d") };
    int argc = 4;

    // Record start time, and invoke launch().
    EXPECT_THROW(launch(argc, argv), ProcessInitError);
}

/// @brief Tests launch with configuration file argument but no file name
TEST_F(DStubControllerTest, missingConfigFileName) {
    // command line to run standalone
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("-d") };
    int argc = 3;

    // Record start time, and invoke launch().
    EXPECT_THROW(launch(argc, argv), ProcessInitError);
}

/// @brief Tests launch with no configuration file argument
TEST_F(DStubControllerTest, missingConfigFileArgument) {
    // command line to run standalone
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-d") };
    int argc = 2;

    // Record start time, and invoke launch().
    EXPECT_THROW(launch(argc, argv), LaunchError);
}

/// @brief Tests launch with an operational error during application execution.
/// This test creates an interval timer to generate a runtime exception during
/// the process event loop. It launches wih a valid, stand-alone command line
/// and no simulated errors.  Launch should throw ProcessRunError.
TEST_F(DStubControllerTest, launchRuntimeError) {
    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*getIOService());
    timer.setup(genFatalErrorCallback, 2000);

    // Write the valid, empty, config and then run launch() for 5000 ms
    time_duration elapsed_time;
    EXPECT_THROW(runWithConfig("{}", 5000, elapsed_time), ProcessRunError);

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    EXPECT_TRUE(elapsed_time.total_milliseconds() >= 1900 &&
                elapsed_time.total_milliseconds() <= 2300);
}

/// @brief Configuration update event testing.
/// This really tests just the ability of the handlers to invoke the necessary
/// chain of methods and handle error conditions. Configuration parsing and
/// retrieval should be tested as part of the d2 configuration management
/// implementation.
/// This test verifies that:
/// 1. That a valid configuration update results in successful status return.
/// 2. That an application process error in configuration updating is handled
/// properly.
TEST_F(DStubControllerTest, configUpdateTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;

    // Initialize the application process.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Create a configuration set. Content is arbitrary, just needs to be
    // valid JSON.
    std::string config = "{ \"test-value\": 1000 } ";
    isc::data::ElementPtr config_set = isc::data::Element::fromJSON(config);

    // Verify that a valid config gets a successful update result.
    answer = updateConfig(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);

    // Verify that an error in process configure method is handled.
    SimFailure::set(SimFailure::ftProcessConfigure);
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
/// 3. A valid, custom controller command is recognized a d2::COMMAND_SUCCESS
/// status.
/// 4. A valid, custom process command is recognized a d2::COMMAND_SUCCESS
/// status.
/// 5. That a valid controller command that fails returns a d2::COMMAND_ERROR.
/// 6. That a valid process command that fails returns a d2::COMMAND_ERROR.
TEST_F(DStubControllerTest, executeCommandTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;
    isc::data::ElementPtr arg_set;

    // Initialize the application process.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Verify that an unknown command returns an d2::COMMAND_INVALID response.
    std::string bogus_command("bogus");
    answer = executeCommand(bogus_command, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_INVALID, rcode);

    // Verify that shutdown command returns d2::COMMAND_SUCCESS response.
    answer = executeCommand(SHUT_DOWN_COMMAND, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);

    // Verify that a valid custom controller command returns
    // d2::COMMAND_SUCCESS response.
    answer = executeCommand(DStubController::stub_ctl_command_, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);

    // Verify that a valid custom process command returns d2::COMMAND_SUCCESS
    // response.
    answer = executeCommand(DStubProcess::stub_proc_command_, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);

    // Verify that a valid custom controller command that fails returns
    // a d2::COMMAND_ERROR.
    SimFailure::set(SimFailure::ftControllerCommand);
    answer = executeCommand(DStubController::stub_ctl_command_, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_ERROR, rcode);

    // Verify that a valid custom process command that fails returns
    // a d2::COMMAND_ERROR.
    SimFailure::set(SimFailure::ftProcessCommand);
    answer = executeCommand(DStubProcess::stub_proc_command_, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_ERROR, rcode);
}

// Tests that registered signals are caught and handled.
TEST_F(DStubControllerTest, ioSignals) {
    // Tell test controller just to record the signals, don't call the
    // base class signal handler.
    controller_->recordSignalOnly(true);

    // Setup to raise SIGHUP in 10 ms.
    TimedSignal sighup(*getIOService(), SIGHUP, 10);
    TimedSignal sigint(*getIOService(), SIGINT, 100);
    TimedSignal sigterm(*getIOService(), SIGTERM, 200);

    // Write the valid, empty, config and then run launch() for 500 ms
    time_duration elapsed_time;
    runWithConfig("{}", 500, elapsed_time);

    // Verify that we caught the signals as expected.
    std::vector<int>& signals = controller_->getProcessedSignals();
    ASSERT_EQ(3, signals.size());
    EXPECT_EQ(SIGHUP, signals[0]);
    EXPECT_EQ(SIGINT, signals[1]);
    EXPECT_EQ(SIGTERM, signals[2]);
}

// Tests that the original configuration is retained after a SIGHUP triggered
// reconfiguration fails due to invalid config content.
TEST_F(DStubControllerTest, invalidConfigReload) {
    // Schedule to rewrite the configuration file after launch. This way the
    // file is updated after we have done the initial configuration.  The
    // new content is invalid JSON which will cause the config parse to fail.
    scheduleTimedWrite("{ \"string_test\": BOGUS JSON }", 100);

    // Setup to raise SIGHUP in 200 ms.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);

    // Write the config and then run launch() for 500 ms
    // After startup, which will load the initial configuration this enters
    // the process's runIO() loop. We will first rewrite the config file.
    // Next we process the SIGHUP signal which should cause us to reconfigure.
    time_duration elapsed_time;
    runWithConfig("{ \"string_test\": \"first value\" }", 500, elapsed_time);

    // Context is still available post launch. Check to see that our
    // configuration value is still the original value.
    std::string  actual_value = "";
    ASSERT_NO_THROW(getContext()->getParam("string_test", actual_value));
    EXPECT_EQ("first value", actual_value);

    // Verify that we saw the signal.
    std::vector<int>& signals = controller_->getProcessedSignals();
    ASSERT_EQ(1, signals.size());
    EXPECT_EQ(SIGHUP, signals[0]);
}

// Tests that the original configuration is replaced after a SIGHUP triggered
// reconfiguration succeeds.
TEST_F(DStubControllerTest, validConfigReload) {
    // Schedule to rewrite the configuration file after launch. This way the
    // file is updated after we have done the initial configuration.
    scheduleTimedWrite("{ \"string_test\": \"second value\" }", 100);

    // Setup to raise SIGHUP in 200 ms and another at 400 ms.
    TimedSignal sighup(*getIOService(), SIGHUP, 200);
    TimedSignal sighup2(*getIOService(), SIGHUP, 400);

    // Write the config and then run launch() for 800 ms
    time_duration elapsed_time;
    runWithConfig("{ \"string_test\": \"first value\" }", 800, elapsed_time);

    // Context is still available post launch.
    // Check to see that our configuration value is what we expect.
    std::string  actual_value = "";
    ASSERT_NO_THROW(getContext()->getParam("string_test", actual_value));
    EXPECT_EQ("second value", actual_value);

    // Verify that we saw two occurrences of the signal.
    std::vector<int>& signals = controller_->getProcessedSignals();
    ASSERT_EQ(2, signals.size());
    EXPECT_EQ(SIGHUP, signals[0]);
    EXPECT_EQ(SIGHUP, signals[1]);
}

// Tests that the SIGINT triggers a normal shutdown.
TEST_F(DStubControllerTest, sigintShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGINT, 1);

    // Write the config and then run launch() for 1000 ms
    time_duration elapsed_time;
    runWithConfig("{ \"string_test\": \"first value\" }", 1000, elapsed_time);

    // Verify that we saw the signal.
    std::vector<int>& signals = controller_->getProcessedSignals();
    ASSERT_EQ(1, signals.size());
    EXPECT_EQ(SIGINT, signals[0]);

    // Duration should be significantly less than our max run time.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);
}

// Tests that the SIGTERM triggers a normal shutdown.
TEST_F(DStubControllerTest, sigtermShutdown) {
    // Setup to raise SIGHUP in 1 ms.
    TimedSignal sighup(*getIOService(), SIGTERM, 1);

    // Write the config and then run launch() for 1000 ms
    time_duration elapsed_time;
    runWithConfig("{ \"string_test\": \"first value\" }", 1000, elapsed_time);

    // Verify that we saw the signal.
    std::vector<int>& signals = controller_->getProcessedSignals();
    ASSERT_EQ(1, signals.size());
    EXPECT_EQ(SIGTERM, signals[0]);

    // Duration should be significantly less than our max run time.
    EXPECT_TRUE(elapsed_time.total_milliseconds() < 300);
}

}; // end of isc::d2 namespace
}; // end of isc namespace
