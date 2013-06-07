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
#include <d2/d2_process.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <config.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::config;
using namespace isc::d2;
using namespace boost::posix_time;

namespace {

/// @brief D2Process test fixture class
class D2ProcessTest : public ::testing::Test {
public:

    /// @brief Static instance accessible via test callbacks.
    static DProcessBasePtr process_;

    /// @brief Constructor
    D2ProcessTest() {
        io_service_.reset(new isc::asiolink::IOService());
        process_.reset(new D2Process("TestProcess", io_service_));
    }

    /// @brief Destructor
    ~D2ProcessTest() {
        io_service_.reset();
        process_.reset();
    }

    /// @brief Callback that will invoke shutdown method.
    static void genShutdownCallback() {
        process_->shutdown();
    }

    /// @brief Callback that throws an exception.
    static void genFatalErrorCallback() {
        isc_throw (DProcessBaseError, "simulated fatal error");
    }

    /// @brief IOService for event processing. Fills in for IOService
    /// supplied by management layer.
    IOServicePtr io_service_;
};

// Define the static process instance
DProcessBasePtr D2ProcessTest::process_;


/// @brief Verifies D2Process constructor behavior.
/// 1. Verifies that constructor fails with an invalid IOService
/// 2. Verifies that constructor succeeds with a valid IOService
TEST(D2Process, construction) {
    // Verify that the constructor will fail if given an empty
    // io service.
    IOServicePtr lcl_io_service;
    EXPECT_THROW (D2Process("TestProcess", lcl_io_service), DProcessBaseError);

    // Verify that the constructor succeeds with a valid io_service
    lcl_io_service.reset(new isc::asiolink::IOService());
    ASSERT_NO_THROW (D2Process("TestProcess", lcl_io_service));
}

/// @brief Verifies basic configure method behavior.
/// @TODO This test is simplistic and will need to be augmented as configuration
/// ability is implemented.
TEST_F(D2ProcessTest, configure) {
    // Verify that given a configuration "set", configure returns
    // a successful response.
    int rcode = -1;
    string config = "{ \"test-value\": 1000 } ";
    isc::data::ElementPtr json = isc::data::Element::fromJSON(config);
    isc::data::ConstElementPtr answer = process_->configure(json);
    isc::config::parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);
}

/// @brief Verifies basic command method behavior.
/// @TODO IF the D2Process is extended to support extra commands this testing
/// will need to augmented accordingly.
TEST_F(D2ProcessTest, command) {
    // Verify that the process will process unsupported command and
    // return a failure response.
    int rcode = -1;
    string args = "{ \"arg1\": 77 } ";
    isc::data::ElementPtr json = isc::data::Element::fromJSON(args);
    isc::data::ConstElementPtr answer =
                                    process_->command("bogus_command", json);
    parseAnswer(rcode, answer);
    EXPECT_EQ(COMMAND_INVALID, rcode);
}

/// @brief Verifies that an "external" call to shutdown causes the run method
/// to exit gracefully.
TEST_F(D2ProcessTest, normalShutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // shutdown invocation. (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*io_service_);
    timer.setup(genShutdownCallback, 2 * 1000);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_NO_THROW(process_->run());

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the shutdown was driven
    // by an io_service event and callback.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 1900 &&
                elapsed.total_milliseconds() <= 2100);
}

/// @brief Verifies that an "uncaught" exception thrown during event loop
/// execution is treated as a fatal error.
TEST_F(D2ProcessTest, fatalErrorShutdown) {
    // Use an asiolink IntervalTimer and callback to generate the
    // the exception.  (Note IntervalTimer setup is in milliseconds).
    isc::asiolink::IntervalTimer timer(*io_service_);
    timer.setup(genFatalErrorCallback, 2 * 1000);

    // Record start time, and invoke run().
    ptime start = microsec_clock::universal_time();
    EXPECT_THROW(process_->run(), DProcessBaseError);

    // Record stop time.
    ptime stop = microsec_clock::universal_time();

    // Verify that duration of the run invocation is the same as the
    // timer duration.  This demonstrates that the anomaly occurred
    // during io callback processing.
    time_duration elapsed = stop - start;
    EXPECT_TRUE(elapsed.total_milliseconds() >= 1900 &&
                elapsed.total_milliseconds() <= 2100);
}

} // end of anonymous namespace
