// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file Contains tests that exercise the basic functionality of the
// class RotatingFile.  These tests are independent of the hooks framework.

#include <config.h>

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <testutils/gtest_utils.h>
#include <dhcpsrv/legal_log_mgr_factory.h>
#include <dhcpsrv/legal_log_db_log.h>
#include <hooks/hooks_parser.h>
#include <legal_log_log.h>
#include <rotating_file.h>
#include <util/filesystem.h>
#include <testutils/env_var_wrapper.h>
#include <testutils/log_utils.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace isc;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::legal_log;
using namespace isc::test;
using namespace isc::dhcp::test;
using namespace isc::util::file;
using namespace std;

namespace {

const DbLogger::MessageMap legal_log_db_message_map = {
};

DbLogger legal_log_db_logger(legal_log_logger, legal_log_db_message_map);

/// @brief Test fixture
class LegalLogMgrTest : public LogContentTest {
public:
    /// @brief Constructor.
    LegalLogMgrTest() : legal_log_dir_env_var_("KEA_LEGAL_LOG_DIR") {
        HookLibraryScriptsChecker::getHookScriptsPath(true, TEST_DATA_BUILDDIR);
    }

    /// @brief Destructor.
    virtual ~LegalLogMgrTest() = default;

    /// @brief Called before each test.
    virtual void SetUp() override {
        setLogTestPath();
        // Clean up from past tests.
        LegalLogMgrFactory::delAllBackends();
    }

    /// @brief Called after each test.
    virtual void TearDown() override {
        // Clean up from past tests.
        LegalLogMgrFactory::delAllBackends();
        reset();
        resetLogPath();
    }

    /// @brief Removes files that may be left over from previous tests
    void reset() {
        PathChecker::enableEnforcement(true);
        std::ostringstream stream;
        stream << "rm " << TEST_DATA_BUILDDIR << "/" << "*-legal"
               << ".*.txt 2>/dev/null";
        int result = ::system(stream.str().c_str());
        if (result != 0) {
            // Ignore the result, because it may well be non-zero value when
            // files to be removed don't exist.
            ;
        }
    }

    /// @brief Sets the log path for log files.
    /// @param custom_path path to use as the log file path.
    void setLogTestPath(const std::string explicit_path = "") {
        LegalLogMgr::getLogPath(true, (!explicit_path.empty() ?
                                      explicit_path : TEST_DATA_BUILDDIR));
    }

    /// @brief Resets the log path to LEGAL_LOG_DIR.
    void resetLogPath() {
        LegalLogMgr::getLogPath(true);
    }

    /// @brief Initializer.
    RotatingFileInit init_;

    /// @brief RAII wrapper for KEA_LEGAL_LOG_DIR env variable.
    EnvVarWrapper legal_log_dir_env_var_;
};

// Verifies output of genDurationString()
TEST_F(LegalLogMgrTest, genDurationString) {
    EXPECT_EQ("0 hrs 0 mins 0 secs", LegalLogMgr::genDurationString(0));
    EXPECT_EQ("0 hrs 0 mins 1 secs", LegalLogMgr::genDurationString(1));
    EXPECT_EQ("0 hrs 1 mins 1 secs", LegalLogMgr::genDurationString(61));
    EXPECT_EQ("1 hrs 1 mins 1 secs", LegalLogMgr::genDurationString(3661));
    EXPECT_EQ("1 days 0 hrs 0 mins 0 secs",
              LegalLogMgr::genDurationString(24*60*60));
    EXPECT_EQ("1 days 1 hrs 1 mins 1 secs",
              LegalLogMgr::genDurationString(24*60*60 + 3661));
    EXPECT_EQ("182 days 17 hrs 21 mins 11 secs",
              LegalLogMgr::genDurationString(15783671 + 3600));
    EXPECT_EQ("infinite duration",
              LegalLogMgr::genDurationString(0xFFFFFFFF));
}

// Verifies the LegalLogDbLogger class works as expected
TEST_F(LegalLogMgrTest, legalLogDbLogger) {
    EXPECT_EQ(1, db_logger_stack.size());

    // Open a block
    {
        EXPECT_EQ(1, db_logger_stack.size());

        // Push local logger
        LegalLogDbLogger pushed(legal_log_db_logger);

        // Check now we have a second logger
        EXPECT_EQ(2, db_logger_stack.size());
    }

    // Logger was popped when existing the block
    EXPECT_EQ(1, db_logger_stack.size());

    // Open a try block to check it works with it
    try {
        EXPECT_EQ(1, db_logger_stack.size());
        LegalLogDbLogger pushed(legal_log_db_logger);
        EXPECT_EQ(2, db_logger_stack.size());
    } catch (const std::exception&) {
        ADD_FAILURE() << "no exception was raised";
    }
    EXPECT_EQ(1, db_logger_stack.size());

    // Another check with an exception now
    try {
        EXPECT_EQ(1, db_logger_stack.size());
        LegalLogDbLogger pushed(legal_log_db_logger);
        EXPECT_EQ(2, db_logger_stack.size());
        isc_throw(Unexpected, "for testing");
        ADD_FAILURE() << "an exception was raised";
    } catch (const std::exception&) {
        // The handler is outside the block
        EXPECT_EQ(1, db_logger_stack.size());
    }
    ASSERT_EQ(1, db_logger_stack.size());
}

// Verifies that vectorDump handles empty content (for static analyzers)
TEST_F(LegalLogMgrTest, emptyVectorDump) {
    std::vector<uint8_t> bytes;
    EXPECT_TRUE(LegalLogMgr::vectorDump(bytes).empty());
    EXPECT_TRUE(LegalLogMgr::vectorHexDump(bytes).empty());
}

// Verify path validation
TEST_F(LegalLogMgrTest, pathValidation) {
    isc::db::DatabaseConnection::ParameterMap map;
    EXPECT_NO_THROW(LegalLogMgr::parseConfig(ConstElementPtr(), map));
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(map));
    EXPECT_TRUE(LegalLogMgrFactory::instance());

    // Default path should be OK.
    ElementPtr params = Element::createMap();
    params->set("base-name", Element::create("name"));
    ASSERT_NO_THROW_LOG(LegalLogMgr::parseFile(params, map));

    // Valid path should be OK.
    params = Element::createMap();
    params->set("path", Element::create(LegalLogMgr::getLogPath()));
    ASSERT_NO_THROW_LOG(LegalLogMgr::parseFile(params, map));

    // Invalid path should NOT be OK.
    params = Element::createMap();
    params->set("path", Element::create("/tmp"));
    std::ostringstream os;
    os << "invalid path specified: '/tmp', supported path is '"
       << LegalLogMgr::getLogPath() << "'";
    ASSERT_THROW_MSG(LegalLogMgr::parseFile(params, map), SecurityError, os.str());
}

// Verify env variable path override.
TEST_F(LegalLogMgrTest, pathEnvVarOverride) {
    legal_log_dir_env_var_.setValue("/tmp");
    resetLogPath();
    isc::db::DatabaseConnection::ParameterMap map;
    EXPECT_NO_THROW(LegalLogMgr::parseConfig(ConstElementPtr(), map));
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(map));
    EXPECT_TRUE(LegalLogMgrFactory::instance());

    // Default path should be OK.
    ElementPtr params = Element::createMap();
    params->set("base-name", Element::create("name"));
    ASSERT_NO_THROW_LOG(LegalLogMgr::parseFile(params, map));

    // Valid path should be OK.
    params = Element::createMap();
    params->set("path", Element::create("/tmp"));
    ASSERT_NO_THROW_LOG(LegalLogMgr::parseFile(params, map));

    // Invalid path should NOT be OK.
    params = Element::createMap();
    params->set("path", Element::create("/bogus"));
    std::ostringstream os;
    os << "invalid path specified: '/bogus', supported path is '"
       << LegalLogMgr::getLogPath() << "'";
    ASSERT_THROW_MSG(LegalLogMgr::parseFile(params, map), SecurityError, os.str());
}

// Verify path validation when security is disabled.
TEST_F(LegalLogMgrTest, pathValidationSecurityDisabled) {
    PathChecker::enableEnforcement(false);
    isc::db::DatabaseConnection::ParameterMap map;
    EXPECT_NO_THROW(LegalLogMgr::parseConfig(ConstElementPtr(), map));
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(map));
    EXPECT_TRUE(LegalLogMgrFactory::instance());

    // Invalid path should be OK but we should get warning.
    ElementPtr params = Element::createMap();
    params->set("path", Element::create("/tmp"));
    ASSERT_NO_THROW_LOG(LegalLogMgr::parseFile(params, map));

    std::ostringstream os;
    os << "LEGAL_LOG_PATH_SECURITY_WARNING Forensic log path specified is NOT SECURE:"
       << " invalid path specified: '/tmp', supported path is '"
       << LegalLogMgr::getLogPath() << "'";

    EXPECT_EQ(1, countFile(os.str()));
}

// Verify that parsing extra parameters for rotate file works
TEST_F(LegalLogMgrTest, parseExtraRotatingFileParameters) {
    isc::db::DatabaseConnection::ParameterMap map;
    EXPECT_NO_THROW(LegalLogMgr::parseConfig(ConstElementPtr(), map));
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(map));
    EXPECT_TRUE(LegalLogMgrFactory::instance());
    RotatingFile& rotating_file = dynamic_cast<RotatingFile&>(*LegalLogMgrFactory::instance());

    ElementPtr params = Element::createMap();
    params->set("path", Element::create(LegalLogMgr::getLogPath()));
    params->set("base-name", Element::create("name"));

    params->set("time-unit", Element::create(0));
    EXPECT_THROW(LegalLogMgr::parseFile(params, map), TypeError);

    params->set("time-unit", Element::create("nothing"));
    EXPECT_NO_THROW(LegalLogMgr::parseFile(params, map));
    EXPECT_THROW(rotating_file.apply(map), BadValue);

    params->set("time-unit", Element::create("second"));
    params->set("count", Element::create(""));
    EXPECT_THROW(LegalLogMgr::parseFile(params, map), TypeError);

    params->set("time-unit", Element::create("day"));
    params->set("count", Element::create(-1));
    EXPECT_THROW(LegalLogMgr::parseFile(params, map), OutOfRange);

    params->set("time-unit", Element::create("month"));
    params->set("count", Element::create(static_cast<int64_t>(1) << 32));
    EXPECT_THROW(LegalLogMgr::parseFile(params, map), OutOfRange);

    params->set("time-unit", Element::create("year"));
    params->set("count", Element::create(1));
    params->set("prerotate", Element::create(FORENSIC_PREROTATE_TEST_SH));
    params->set("postrotate", Element::create(FORENSIC_POSTROTATE_TEST_SH));
    EXPECT_NO_THROW(LegalLogMgr::parseFile(params, map));
    EXPECT_NO_THROW(rotating_file.apply(map));
}

// Verify that parsing extra parameters works
TEST_F(LegalLogMgrTest, parseExtraParameters) {
    db::DatabaseConnection::ParameterMap map;
    map["base-name"] = "name";
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new RotatingFile(map)));
    ElementPtr params = Element::createMap();
    params->set("request-parser-format", Element::create("'request'"));
    params->set("response-parser-format", Element::create("'response'"));
    params->set("timestamp-format", Element::create("timestamp"));

    map.clear();
    map["type"] = "logfile";
    map["path"] = TEST_DATA_BUILDDIR;
    EXPECT_NO_THROW(LegalLogMgr::parseExtraParameters(params, map));
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(map));
    EXPECT_TRUE(LegalLogMgrFactory::instance());

    auto request_format = LegalLogMgrFactory::instance()->getRequestFormatExpression();
    EXPECT_TRUE(request_format);

    auto response_format = LegalLogMgrFactory::instance()->getResponseFormatExpression();
    EXPECT_TRUE(response_format);

    EXPECT_NE(request_format, response_format);

    auto timestamp_format = LegalLogMgrFactory::instance()->getTimestampFormat();
    EXPECT_EQ(timestamp_format, "timestamp");
}

TEST_F(LegalLogMgrTest, fileNoParameters) {
    db::DatabaseConnection::ParameterMap map;
    EXPECT_NO_THROW(LegalLogMgr::parseFile(ConstElementPtr(), map));
    ASSERT_NO_THROW(LegalLogMgrFactory::instance().reset(new RotatingFile(map)));
    ASSERT_NO_THROW(LegalLogMgrFactory::instance()->open());
    RotatingFile& rotating_file = dynamic_cast<RotatingFile&>(*LegalLogMgrFactory::instance());
    map.clear();
    rotating_file.apply(map);
    EXPECT_EQ(rotating_file.getPath(), LegalLogMgr::getLogPath());
    EXPECT_EQ(rotating_file.getBaseName(), "kea-legal");
}

TEST_F(LegalLogMgrTest, databaseNoParameters) {
    db::DatabaseConnection::ParameterMap map;
    EXPECT_THROW(LegalLogMgr::parseDatabase(ConstElementPtr(), map), BadValue);
}

TEST_F(LegalLogMgrTest, wrongDatabaseType) {
    db::DatabaseConnection::ParameterMap map;
    ElementPtr parameters = Element::createMap();
    parameters->set("type", Element::create(""));
    EXPECT_NO_THROW(LegalLogMgr::parseDatabase(parameters, map));
    EXPECT_THROW_MSG(LegalLogMgrFactory::addBackend(map), InvalidType,
                     "The type of the forensic log backend: '' is not supported");
    EXPECT_FALSE(LegalLogMgrFactory::instance());

    parameters->set("type", Element::create("awesomesql"));
    EXPECT_NO_THROW(LegalLogMgr::parseDatabase(parameters, map));
    EXPECT_THROW_MSG(LegalLogMgrFactory::addBackend(map), InvalidType,
                     "The type of the forensic log backend: 'awesomesql' is not supported");
}

TEST_F(LegalLogMgrTest, syslogNoParameters) {
    db::DatabaseConnection::ParameterMap map;
    EXPECT_THROW(LegalLogMgr::parseSyslog(ConstElementPtr(), map), BadValue);
}

} // end of anonymous namespace
