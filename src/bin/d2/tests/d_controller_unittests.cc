// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <config/ccsession.h>
#include <d_test_stubs.h>
#include <d2/spec_config.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <config.h>
#include <sstream>

using namespace boost::posix_time;

namespace isc {
namespace d2 {

/// @brief basic instantiation  
// @TODO This test is simplistic and will need to be augmented
TEST_F(DStubControllerTest, basicInstanceTesting) {
    DControllerBasePtr& controller = DControllerTest::getController();
    ASSERT_TRUE(controller);
    EXPECT_TRUE(checkName(D2_MODULE_NAME));
    EXPECT_TRUE(checkSpecFileName(D2_SPECFILE_LOCATION));
    EXPECT_TRUE(checkIOService());

    // Process should NOT exist yet
    EXPECT_FALSE(checkProcess());
}

/// @TODO brief Verifies command line processing. 
TEST_F(DStubControllerTest, commandLineArgs) {
    char* argv[] = { (char*)"progName", (char*)"-s", (char*)"-v" };
    int argc = 3;

    EXPECT_TRUE(checkStandAlone(false));
    EXPECT_TRUE(checkVerbose(false));

    EXPECT_NO_THROW(parseArgs(argc, argv));

    EXPECT_TRUE(checkStandAlone(true));
    EXPECT_TRUE(checkVerbose(true));

    char* argv1[] = { (char*)"progName", (char*)"-x" };
    argc = 2;
    EXPECT_NO_THROW (parseArgs(argc, argv1));

    char* argv2[] = { (char*)"progName", (char*)"-bs" };
    argc = 2;
    EXPECT_THROW (parseArgs(argc, argv2), InvalidUsage);
}

/// @TODO brief initProcess testing. 
TEST_F(DStubControllerTest, initProcessTesting) {

    SimFailure::set(SimFailure::ftCreateProcessException);
    EXPECT_THROW(initProcess(), DControllerBaseError);
    EXPECT_FALSE(checkProcess());

    SimFailure::set(SimFailure::ftCreateProcessNull);
    EXPECT_THROW(initProcess(), DControllerBaseError);
    EXPECT_FALSE(checkProcess());

    resetController();
    SimFailure::set(SimFailure::ftProcessInit);
    EXPECT_THROW(initProcess(), DProcessBaseError);

    resetController();
    EXPECT_FALSE(checkProcess());

    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());
}

/// @TODO brief establishSession failure testing. 
/// Testing with BIND10 is out of scope for unit tests 
TEST_F(DStubControllerTest, sessionFailureTesting) {
    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    EXPECT_THROW(establishSession(), std::exception);
}

/// @TODO brief test launch 
TEST_F(DStubControllerTest, launchDirectShutdown) {
    // command line to run standalone 
    char* argv[] = { (char*)"progName", (char*)"-s", (char*)"-v" };
    int argc = 3;

    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*getIOService());
    timer.setup(genShutdownCallback, 2 * 1000);

    // Record start time, and invoke launch().
    ptime start = microsec_clock::universal_time();
    int rcode = launch(argc, argv);

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify normal shutdown status.
    EXPECT_EQ(EXIT_SUCCESS, rcode);

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 1900 &&
                elapsed.total_milliseconds() <= 2100);
}

/// @TODO brief test launch 
TEST_F(DStubControllerTest, launchRuntimeError) {
    // command line to run standalone 
    char* argv[] = { (char*)"progName", (char*)"-s", (char*)"-v" };
    int argc = 3;

    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*getIOService());
    timer.setup(genFatalErrorCallback, 2 * 1000);

    // Record start time, and invoke launch().
    ptime start = microsec_clock::universal_time();
    int rcode = launch(argc, argv);

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify normal shutdown status.
    EXPECT_EQ(EXIT_SUCCESS, rcode);

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 1900 &&
                elapsed.total_milliseconds() <= 2100);
}

/// @TODO brief test configUpateTests 
/// This really tests just the ability of the handlers to invoke the necessary
/// chain, and error conditions. Configuration parsing and retrieval should be
/// tested as part of the d2 configuration management implementation.   
TEST_F(DStubControllerTest, configUpdateTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;

    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Create a configuration set. Content is arbitrary, just needs to be 
    // valid JSON.
    std::string config = "{ \"test-value\": 1000 } ";
    isc::data::ElementPtr config_set = isc::data::Element::fromJSON(config);

    // We are not stand-alone, so configuration should be rejected as there is
    // no session.  This is a pretty contrived situation that shouldn't be 
    // possible other than the handler being called directly (like this does).
    answer = DControllerBase::configHandler(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(1, rcode);

    // Verify that in stand alone we get a successful update result.
    setStandAlone(true);
    answer = DControllerBase::configHandler(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);

    // Verify that an error in process configure method is handled.
    SimFailure::set(SimFailure::ftProcessConfigure);
    answer = DControllerBase::configHandler(config_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(1, rcode);

}

TEST_F(DStubControllerTest, executeCommandTests) {
    int rcode = -1;
    isc::data::ConstElementPtr answer;
    isc::data::ElementPtr arg_set;

    ASSERT_NO_THROW(initProcess());
    EXPECT_TRUE(checkProcess());

    // Verify that shutdown command returns CommandSuccess response.
    answer = DControllerBase::commandHandler(SHUT_DOWN_COMMAND, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);

    // Verify that a valid custom controller command returns CommandSuccess
    // response.
    answer = DControllerBase::commandHandler(DStubController::
                                             custom_ctl_command_, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);

    // Verify that an unknown command returns an InvalidCommand response.
    std::string bogus_command("bogus");
    answer = DControllerBase::commandHandler(bogus_command, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_INVALID, rcode);

    // Verify that a valid custom process command returns CommandSuccess
    // response.
    answer = DControllerBase::commandHandler(DStubProcess::
                                             custom_process_command_, arg_set);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_SUCCESS, rcode);
}

}; // end of isc::d2 namespace
}; // end of isc namespace
