// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config/command_interpreter.h>
#include <d_test_stubs.h>
#include <d2/bundy_d2_controller.h>
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
class BundyD2ControllerTest : public DControllerTest {
public:
    /// @brief Constructor
    /// Note the constructor passes in the static D2Controller instance
    /// method.
    BundyD2ControllerTest() : DControllerTest(D2Controller::instance) {
    }

};

/// @brief Basic Controller instantiation testing.
/// Verifies that the controller singleton gets created and that the
/// basic derivation from the base class is intact.
TEST_F(BundyD2ControllerTest, basicInstanceTesting) {
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
TEST_F(BundyD2ControllerTest, commandLineArgs) {
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-v") };
    int argc = 2;

    // Verify that verbose flag is false initially.
    EXPECT_TRUE(checkVerbose(false));

    // Verify that standard options can be parsed without error.
    EXPECT_NO_THROW(parseArgs(argc, argv));

    // Verify that verbose flag is now true.
    EXPECT_TRUE(checkVerbose(true));

    // Verify that an unknown option is detected.
    char* argv2[] = { const_cast<char*>("progName"),
                      const_cast<char*>("-x") };
    argc = 2;
    EXPECT_THROW(parseArgs(argc, argv2), InvalidUsage);
}

/// @brief Tests application process creation and initialization.
/// Verifies that the process can be successfully created and initialized.
TEST_F(BundyD2ControllerTest, initProcessTesting) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());
}

/// @brief Configuration update event testing.
/// This really tests just the ability of the handlers to invoke the necessary
/// chain of methods and handle error conditions. Configuration parsing and
/// retrieval should be tested as part of the d2 configuration management
/// implementation.  Note that this testing calls the configuration update event
/// callback, configHandler, directly.
/// This test verifies that:
/// 1. Configuration will be rejected in integrated mode when there is no
/// session established. (This is a very contrived situation).
/// 2. In stand-alone mode a configuration update results in successful
/// status return.
/// 3. That an application process error in configuration updating is handled
/// properly.
TEST_F(BundyD2ControllerTest, configUpdateTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;

    // Initialize the application process.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Create a configuration set using a small, valid D2 configuration.
    isc::data::ElementPtr config_set =
                                isc::data::Element::fromJSON(valid_d2_config);

    // Configuration should be rejected as there is no session.  This is a 
    // pretty contrived situation that shouldn't be possible other than the 
    // handler being called directly (like this does).
    answer = D2Controller::configHandler(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(1, rcode);
}

/// @brief Command execution tests.
/// This really tests just the ability of the handler to invoke the necessary
/// chain of methods and to handle error conditions. Note that this testing
/// calls the command callback, commandHandler, directly.
/// This test verifies that:
/// 1. That an unrecognized command is detected and returns a status of
/// d2::COMMAND_INVALID.
/// 2. Shutdown command is recognized and returns a d2::COMMAND_SUCCESS status.
TEST_F(BundyD2ControllerTest, executeCommandTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;
    isc::data::ElementPtr arg_set;

    // Initialize the application process.
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Verify that an unknown command returns an COMMAND_INVALID response.
    std::string bogus_command("bogus");
    answer = D2Controller::commandHandler(bogus_command, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_INVALID, rcode);

    // Verify that shutdown command returns COMMAND_SUCCESS response.
    //answer = executeCommand(SHUT_DOWN_COMMAND, isc::data::ElementPtr());
    answer = D2Controller::commandHandler(SHUT_DOWN_COMMAND, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);
}

/// @brief Tests launch with a session establishment failure.
/// This test launches with a valid command line for integrated mode and no.
/// Attempting to connect to Bundy should fail, even if Bundy is running
/// UNLESS the test is run as root. Launch should throw SessionStartError.
TEST_F(BundyD2ControllerTest, launchSessionFailure) {
    // Command line to run integrated
    char* argv[] = { (char*)"progName" };
    int argc = 1;

    // Launch the controller in integrated mode.
    EXPECT_THROW(launch(argc, argv), SessionStartError);
}

}; // end of isc::d2 namespace
}; // end of isc namespace
