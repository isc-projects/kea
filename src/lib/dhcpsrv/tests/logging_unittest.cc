// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <config/module_spec.h>
#include <dhcpsrv/logging.h>
#include <gtest/gtest.h>
#include <log/logger_support.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;

namespace {

/// @brief Logging Test Fixture Class
///
/// Trivial class that ensures that the logging is reset to its defaults after
/// each test.  Strictly speaking this only resets the testing root logger (which
/// has the name "kea") but as the only other logger mentioned here ("wombat")
/// is not used elsewhere, that is sufficient.

class LoggingTest : public ::testing::Test {
    public:
        /// @brief Constructor
        LoggingTest() {}

        /// @brief Destructor
        ///
        /// Reset root logger back to defaults.
        ~LoggingTest() {
            isc::log::setDefaultLoggingOutput();
        }
};

// Tests that the spec file is valid.
TEST_F(LoggingTest, basicSpec) {
    std::string specfile = std::string(TEST_DATA_BUILDDIR) + "/../logging.spec";
    ASSERT_NO_THROW(isc::config::moduleSpecFromFile(specfile));
}

// Checks that contructor is able to process specified storage properly
TEST_F(LoggingTest, constructor) {

    SrvConfigPtr null_ptr;
    EXPECT_THROW(LogConfigParser parser(null_ptr), BadValue);

    SrvConfigPtr nonnull(new SrvConfig());

    EXPECT_NO_THROW(LogConfigParser parser(nonnull));
}

// Checks if the LogConfigParser class is able to transform JSON structures
// into Configuration usable by log4cplus. This test checks for output
// configured to stdout on debug level.
TEST_F(LoggingTest, parsingConsoleOutput) {

    const char* config_txt =
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"stdout\","
    "                \"flush\": true"
    "            }"
    "        ],"
    "        \"debuglevel\": 99,"
    "        \"severity\": \"DEBUG\""
    "    }"
    "]}";

    SrvConfigPtr storage(new SrvConfig());

    LogConfigParser parser(storage);

    // We need to parse properly formed JSON and then extract
    // "loggers" element from it. For some reason fromJSON is
    // throwing at opening square bracket
    ConstElementPtr config = Element::fromJSON(config_txt);
    config = config->get("loggers");

    EXPECT_NO_THROW(parser.parseConfiguration(config));

    ASSERT_EQ(1, storage->getLoggingInfo().size());

    EXPECT_EQ("kea", storage->getLoggingInfo()[0].name_);
    EXPECT_EQ(99, storage->getLoggingInfo()[0].debuglevel_);
    EXPECT_EQ(isc::log::DEBUG, storage->getLoggingInfo()[0].severity_);

    ASSERT_EQ(1, storage->getLoggingInfo()[0].destinations_.size());
    EXPECT_EQ("stdout" , storage->getLoggingInfo()[0].destinations_[0].output_);
    EXPECT_TRUE(storage->getLoggingInfo()[0].destinations_[0].flush_);
}

// Checks if the LogConfigParser class is able to transform JSON structures
// into Configuration usable by log4cplus. This test checks for output
// configured to a file on INFO level.
TEST_F(LoggingTest, parsingFile) {

    const char* config_txt =
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"logfile.txt\""
    "            }"
    "        ],"
    "        \"severity\": \"INFO\""
    "    }"
    "]}";

    SrvConfigPtr storage(new SrvConfig());

    LogConfigParser parser(storage);

    // We need to parse properly formed JSON and then extract
    // "loggers" element from it. For some reason fromJSON is
    // throwing at opening square bracket
    ConstElementPtr config = Element::fromJSON(config_txt);
    config = config->get("loggers");

    EXPECT_NO_THROW(parser.parseConfiguration(config));

    ASSERT_EQ(1, storage->getLoggingInfo().size());

    EXPECT_EQ("kea", storage->getLoggingInfo()[0].name_);
    EXPECT_EQ(0, storage->getLoggingInfo()[0].debuglevel_);
    EXPECT_EQ(isc::log::INFO, storage->getLoggingInfo()[0].severity_);

    ASSERT_EQ(1, storage->getLoggingInfo()[0].destinations_.size());
    EXPECT_EQ("logfile.txt" , storage->getLoggingInfo()[0].destinations_[0].output_);
    // Default for immediate flush is true
    EXPECT_TRUE(storage->getLoggingInfo()[0].destinations_[0].flush_);
}

// Checks if the LogConfigParser class is able to transform data structures
// into Configuration usable by log4cplus. This test checks that more than
// one logger can be configured.
TEST_F(LoggingTest, multipleLoggers) {

    const char* config_txt =
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"logfile.txt\","
    "                \"flush\": true"
    "            }"
    "        ],"
    "        \"severity\": \"INFO\""
    "    },"
    "    {"
    "        \"name\": \"wombat\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"logfile2.txt\","
    "                \"flush\": false"
    "            }"
    "        ],"
    "        \"severity\": \"DEBUG\","
    "        \"debuglevel\": 99"
    "    }"
    "]}";

    SrvConfigPtr storage(new SrvConfig());

    LogConfigParser parser(storage);

    // We need to parse properly formed JSON and then extract
    // "loggers" element from it. For some reason fromJSON is
    // throwing at opening square bracket
    ConstElementPtr config = Element::fromJSON(config_txt);
    config = config->get("loggers");

    EXPECT_NO_THROW(parser.parseConfiguration(config));

    ASSERT_EQ(2, storage->getLoggingInfo().size());

    EXPECT_EQ("kea", storage->getLoggingInfo()[0].name_);
    EXPECT_EQ(0, storage->getLoggingInfo()[0].debuglevel_);
    EXPECT_EQ(isc::log::INFO, storage->getLoggingInfo()[0].severity_);
    ASSERT_EQ(1, storage->getLoggingInfo()[0].destinations_.size());
    EXPECT_EQ("logfile.txt" , storage->getLoggingInfo()[0].destinations_[0].output_);
    EXPECT_TRUE(storage->getLoggingInfo()[0].destinations_[0].flush_);

    EXPECT_EQ("wombat", storage->getLoggingInfo()[1].name_);
    EXPECT_EQ(99, storage->getLoggingInfo()[1].debuglevel_);
    EXPECT_EQ(isc::log::DEBUG, storage->getLoggingInfo()[1].severity_);
    ASSERT_EQ(1, storage->getLoggingInfo()[1].destinations_.size());
    EXPECT_EQ("logfile2.txt" , storage->getLoggingInfo()[1].destinations_[0].output_);
    EXPECT_FALSE(storage->getLoggingInfo()[1].destinations_[0].flush_);
}

// Checks if the LogConfigParser class is able to transform data structures
// into Configuration usable by log4cplus. This test checks that more than
// one logging destination can be configured.
TEST_F(LoggingTest, multipleLoggingDestinations) {

    const char* config_txt =
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"logfile.txt\""
    "            },"
    "            {"
    "                \"output\": \"stdout\""
    "            }"
    "        ],"
    "        \"severity\": \"INFO\""
    "    }"
    "]}";

    SrvConfigPtr storage(new SrvConfig());

    LogConfigParser parser(storage);

    // We need to parse properly formed JSON and then extract
    // "loggers" element from it. For some reason fromJSON is
    // throwing at opening square bracket
    ConstElementPtr config = Element::fromJSON(config_txt);
    config = config->get("loggers");

    EXPECT_NO_THROW(parser.parseConfiguration(config));

    ASSERT_EQ(1, storage->getLoggingInfo().size());

    EXPECT_EQ("kea", storage->getLoggingInfo()[0].name_);
    EXPECT_EQ(0, storage->getLoggingInfo()[0].debuglevel_);
    EXPECT_EQ(isc::log::INFO, storage->getLoggingInfo()[0].severity_);
    ASSERT_EQ(2, storage->getLoggingInfo()[0].destinations_.size());
    EXPECT_EQ("logfile.txt" , storage->getLoggingInfo()[0].destinations_[0].output_);
    EXPECT_TRUE(storage->getLoggingInfo()[0].destinations_[0].flush_);
    EXPECT_EQ("stdout" , storage->getLoggingInfo()[0].destinations_[1].output_);
    EXPECT_TRUE(storage->getLoggingInfo()[0].destinations_[1].flush_);
}

/// @todo Add tests for malformed logging configuration

/// @todo There is no easy way to test applyConfiguration() and defaultLogging().
/// To test them, it would require instrumenting log4cplus to actually fake
/// the logging set up. Alternatively, we could develop set of test suites
/// that check each logging destination spearately (e.g. configure log file, then
/// check if the file is indeed created or configure stdout destination, then
/// swap console file descriptors and check that messages are really logged.

};
