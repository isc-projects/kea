// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/daemon.h>
#include <dhcpsrv/logging.h>
#include <log/logger_unittest_support.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;

std::string isc::dhcp::Daemon::getVersion(bool extended) {
    if (extended) {
        return (std::string("EXTENDED"));
    } else {
        return (std::string("BASIC"));
    }
}

namespace {

/// @brief Daemon Test test fixture class
class DaemonTest : public ::testing::Test {
public:
    /// @brief Constructor
    DaemonTest() {
    }

    /// @brief Destructor
    ///
    /// As some of the tests have the side-effect of altering the logging
    /// settings (when configureLogger is called), the logging is reset to
    /// the default after each test completes.
    ~DaemonTest() {
        isc::log::resetUnitTestRootLogger();
    }
};


// Very simple test. Checks whether Daemon can be instantiated and its
// default parameters are sane
TEST_F(DaemonTest, constructor) {
    EXPECT_NO_THROW(Daemon instance1);

    // Check that the verbose mode is not set by default.
    Daemon instance2;
    EXPECT_FALSE(instance2.getVerbose());
}

// Checks that configureLogger method is behaving properly.
// More dedicated tests are availablef for LogConfigParser class.
// See logger_unittest.cc
TEST_F(DaemonTest, parsingConsoleOutput) {
    CfgMgr::instance().setVerbose(false);

    // Storage - parsed configuration will be stored here
    SrvConfigPtr storage(new SrvConfig());

    const char* config_txt =
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"stdout\""
    "            }"
    "        ],"
    "        \"debuglevel\": 99,"
    "        \"severity\": \"DEBUG\""
    "    }"
    "]}";
    ConstElementPtr config = Element::fromJSON(config_txt);

    // Spawn a daemon and tell it to configure logger
    Daemon x;
    EXPECT_NO_THROW(x.configureLogger(config, storage));

    // The parsed configuration should be processed by the daemon and
    // stored in configuration storage.
    ASSERT_EQ(1, storage->getLoggingInfo().size());

    EXPECT_EQ("kea", storage->getLoggingInfo()[0].name_);
    EXPECT_EQ(99, storage->getLoggingInfo()[0].debuglevel_);
    EXPECT_EQ(isc::log::DEBUG, storage->getLoggingInfo()[0].severity_);

    ASSERT_EQ(1, storage->getLoggingInfo()[0].destinations_.size());
    EXPECT_EQ("stdout" , storage->getLoggingInfo()[0].destinations_[0].output_);
}


// More tests will appear here as we develop Daemon class.

};
