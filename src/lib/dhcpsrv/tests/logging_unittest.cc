// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <config/module_spec.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/logging.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <testutils/io_utils.h>

#include <gtest/gtest.h>

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
            wipeFiles();
        }

    /// @brief Generates a log file name suffixed with a rotation number
    /// @param rotation number to the append to the end of the file
    std::string logName(int rotation) {
        std::ostringstream os;
        os << LOG_FILE_NAME << "." << rotation;
        return (os.str());
    }

    /// @brief Removes the base log file name and 1 rotation
    void wipeFiles()  {
        static_cast<void>(remove(LOG_FILE_NAME));
        static_cast<void>(remove(logName(1).c_str()));
    }

    static const char* LOG_FILE_NAME;
};

const char* LoggingTest::LOG_FILE_NAME = "kea.test.log";

// Tests that the spec file is valid.
TEST_F(LoggingTest, basicSpec) {
    std::string specfile = std::string(LOGGING_SPEC_FILE);
    ASSERT_NO_THROW(isc::config::moduleSpecFromFile(specfile));
}

// Checks that the constructor is able to process specified storage properly.
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

// Verifies that log rotation occurs when configured.  We do not
// worry about contents of the log files, only that rotation occurs.
// Such details are tested in lib/log.  This test verifies that
// we can correcty configure logging such that rotation occurs as
// expected.
TEST_F(LoggingTest, logRotate) {
    int rotate_size = 2048;
    std::ostringstream os;
    os <<
        "{ \"loggers\": ["
        "    {"
        "        \"name\": \"kea\","
        "        \"output_options\": ["
        "            {"
        "                \"output\": \""
        << LOG_FILE_NAME << "\","  <<
        "                \"flush\": true,"
        "                \"maxsize\":"
        << rotate_size << "," <<
        "                \"maxver\": 1"
        "            }"
        "        ],"
        "        \"debuglevel\": 99,"
        "        \"severity\": \"DEBUG\""
        "    }"
        "]}";


    // Make sure there aren't any left over.
    wipeFiles();

    // Create our server config container.
    SrvConfigPtr server_cfg(new SrvConfig());

    // LogConfigParser expects a list of loggers, so parse
    // the JSON text and extract the "loggers" element from it
    ConstElementPtr config = Element::fromJSON(os.str());
    config = config->get("loggers");

    // Parse the config and then apply it.
    LogConfigParser parser(server_cfg);
    ASSERT_NO_THROW(parser.parseConfiguration(config));
    ASSERT_NO_THROW(server_cfg->applyLoggingCfg());

    // Make sure we have the initial log file.
    ASSERT_TRUE(isc::test::fileExists(LOG_FILE_NAME));

    // Now generate a log we know will be large enough to force a rotation.
    // We borrow a one argument log message for the test.
    std::string big_arg(rotate_size, 'x');
    isc::log::Logger logger("kea");
    LOG_INFO(logger, DHCPSRV_CFGMGR_ADD_IFACE).arg(big_arg);

    // Make sure we now have a rotation file.
    EXPECT_TRUE(isc::test::fileExists(logName(1).c_str()));

    // Clean up.
    wipeFiles();
}


/// @todo Add tests for malformed logging configuration

/// @todo There is no easy way to test applyConfiguration() and defaultLogging().
/// To test them, it would require instrumenting log4cplus to actually fake
/// the logging set up. Alternatively, we could develop set of test suites
/// that check each logging destination separately (e.g. configure log file, then
/// check if the file is indeed created or configure stdout destination, then
/// swap console file descriptors and check that messages are really logged.

};
