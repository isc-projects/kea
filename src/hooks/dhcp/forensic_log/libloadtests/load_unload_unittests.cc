// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the legal log hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().  In order to eliminate
/// potentially indeterminate behavior these tests should NOT be linked
/// against the legal log library (as is done in ../tests).

#include <config.h>

#include <dhcpsrv/testutils/lib_load_test_fixture.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>

#ifdef HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#endif
#ifdef HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#endif

#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <locale>
#include <sys/stat.h>

#include <errno.h>

using namespace std;
using namespace isc;
using namespace hooks;

namespace {

/// @brief Test fixture for testing loading and unloading the legal log library
/// It provides tools for erasing test files, altering date values,
/// generating file names and checking file existence.
class LegalLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    /// over from previous tests
    LegalLibLoadTest() : LibLoadTest(LEGAL_LOG_LIB_SO) {
        reset();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LegalLibLoadTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests
    void reset() {
        std::ostringstream stream;
        stream << "rm " << TEST_DATA_BUILDDIR << "/" << "test-legal"
               << ".*.txt 2>/dev/null";
        int result = ::system(stream.str().c_str());
        if (result != 0) {
            // Ignore the result, because it may well be non-zero value when
            // files to be removed don't exist.
            ;
        }
    }

    /// @brief Checks if the given file exists
    ///
    /// @return true if the file exists, false if it does not
    bool fileExists(const std::string& filename) {
        struct stat statbuf;
        if (stat(filename.c_str(), &statbuf) == 0) {
            return (true);
        }

        int sav_error = errno;
        if (errno == ENOENT) {
            return (false);
        }

        ADD_FAILURE() << "fileExists error - filename: " << filename
                      << " error: " << strerror(sav_error);
        return (false);
    }

    /// @brief Generate a file name based on the given date
    ///
    /// Uses the same formatting as RotatingFile to build file names
    ///
    /// @param day - date to use in the file name
    /// @return - the generated file name
    std::string genName(const boost::gregorian::date& day) {
        boost::gregorian::date::ymd_type ymd = day.year_month_day();
        std::ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "test-legal" << "." << ymd.year
               << std::right << std::setfill('0') << std::setw(2)
               << ymd.month.as_number() << std::setw(2) << ymd.day << ".txt";
        return (stream.str());
    }
};

// Verifies that the load callout, given an unknown type fails to load.
TEST_F(LegalLibLoadTest, invalidType) {
    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("type", data::Element::create("no-such-type"));
    // Still set path and base-name in the case the library loads
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("nobody-should-use-this"));

    // Attempting to Load the library should fail.
    invalidDaemonTest("kea-dhcp4", AF_INET, params);
}

// Verifies that the load callout, given a viable path and base name,
// instantiates and opens the RotatingFile.
// WARNING!!!  Even though the load() function can supply default values
// for both path and base-name, it is ill-advised to conduct such a test as
// one runs the risk of harming a legal file opened with default values
// by a live instance of Kea.
TEST_F(LegalLibLoadTest, validLoad) {

    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("test-legal"));
    params->set("request-parser-format", data::Element::create("'request'"));
    params->set("response-parser-format", data::Element::create("'response'"));
    params->set("timestamp-format", data::Element::create("timestamp"));

    // Grab the current day and make sure the file doesn't already exist.
    boost::gregorian::date today(boost::gregorian::day_clock::local_day());
    std::string expected_filename = genName(today);
    ASSERT_FALSE(fileExists(expected_filename));

    // Load the library.  This should create the expected file name.
    ASSERT_NO_THROW_LOG(addLibrary(LEGAL_LOG_LIB_SO, params));
    ASSERT_NO_THROW_LOG(loadLibraries());

    // In order to avoid the case where this test straddles midnight we'll look
    // for the file using the date we grabbed just before loading the library
    // and if that one doesn't exist, we'll refresh the date and try again. One of
    // the two files must exist otherwise the load failed to open it.
    if (!fileExists(expected_filename)) {
        expected_filename = genName(today);
        EXPECT_TRUE(fileExists(expected_filename));
    }

    // Library should unload with no issue.
    ASSERT_NO_THROW_LOG(unloadLibraries());

    // File should still exist.
    EXPECT_TRUE(fileExists(expected_filename));
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(LegalLibLoadTest, invalidDaemonLoad) {

    // Prepare parameters for the callout parameters library.
    // Even if loads will fail still avoid defaults!
    data::ElementPtr params = data::Element::createMap();
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("test-legal"));

    // V4 is invalid when family is AF_INET6.
    invalidDaemonTest("kea-dhcp4", AF_INET6, params);

    // V6 is invalid when family is AF_INET.
    invalidDaemonTest("kea-dhcp6", AF_INET, params);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, params);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, params);
    invalidDaemonTest("bogus", AF_INET, params);
}

// Verifies that the load callout, given an inaccessible path fails to
// to load.
TEST_F(LegalLibLoadTest, invalidLoad) {
    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    std::string bogus_path(TEST_DATA_BUILDDIR);
    bogus_path += "utter-nonesense-which-doesnt-exist";
    params->set("path", data::Element::create(bogus_path));
    params->set("base-name", data::Element::create("test-legal"));

    // Attempting to Load the library should fail.
    invalidDaemonTest("kea-dhcp6", AF_INET6, params);
}

// Verifies that the load callout, given a viable path and base name,
// and logfile type instantiates and opens the RotatingFile.
TEST_F(LegalLibLoadTest, fileValidLoad) {

    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("test-legal"));
    params->set("type", data::Element::create("logfile"));

    // Grab the current day and make sure the file doesn't already exist.
    boost::gregorian::date today(boost::gregorian::day_clock::local_day());
    std::string expected_filename = genName(today);
    ASSERT_FALSE(fileExists(expected_filename));

    // Load the library.  This should create the expected file name.
    ASSERT_NO_THROW_LOG(addLibrary(LEGAL_LOG_LIB_SO, params));
    ASSERT_NO_THROW_LOG(loadLibraries());

    // In order to avoid the case where this test straddles midnight we'll look
    // for the file using the date we grabbed just before loading the library
    // and if that one doesn't exist, we'll refresh the date and try again. One of
    // the two files must exist otherwise the load failed to open it.
    if (!fileExists(expected_filename)) {
        expected_filename = genName(today);
        EXPECT_TRUE(fileExists(expected_filename));
    }

    // Library should unload with no issue.
    ASSERT_NO_THROW_LOG(unloadLibraries());

    // File should still exist.
    EXPECT_TRUE(fileExists(expected_filename));
}

// Verifies that the load callout, given an inaccessible path and logfile
// type fails to to load.
TEST_F(LegalLibLoadTest, fileInvalidLoad) {
    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    std::string bogus_path(TEST_DATA_BUILDDIR);
    bogus_path += "utter-nonesense-which-doesnt-exist";
    params->set("path", data::Element::create(bogus_path));
    params->set("base-name", data::Element::create("test-legal"));
    params->set("type", data::Element::create("logfile"));

    // Attempting to Load the library should fail.
    invalidDaemonTest("kea-dhcp4", AF_INET, params);
}

#ifdef HAVE_PGSQL

/// @brief Test fixture for testing loading and unloading the legal log library
/// using PostgreSQL database backend.
class PgSqlLegalLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    PgSqlLegalLibLoadTest() : LibLoadTest(LEGAL_LOG_LIB_SO) {
        // Ensure we have the proper schema with no transient data.
        isc::db::test::createPgSQLSchema();
    }

    /// @brief Destructor
    virtual ~PgSqlLegalLibLoadTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        isc::db::test::destroyPgSQLSchema();
    }
};

// Verifies that the load callout with correct PostgreSQL setup instantiates.
TEST_F(PgSqlLegalLibLoadTest, PgSqlValidLoad) {

    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("type", data::Element::create("postgresql"));
    params->set("name", data::Element::create("keatest"));
    params->set("user", data::Element::create("keatest"));
    params->set("password", data::Element::create("keatest"));

    // Still set path and base-name in the case the library switches to file
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("nobody-should-use-this"));

    // Load the library. Is there a way to check more than return code?
    validDaemonTest("kea-dhcp4", AF_INET, params);
}

// Verifies that the load callout with incorrect PostgreSQL setup fails.
TEST_F(PgSqlLegalLibLoadTest, PgSqlInvalidLoad) {

    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("type", data::Element::create("postgresql"));
    // name is mandatory
    params->set("user", data::Element::create("keatest"));
    params->set("password", data::Element::create("keatest"));

    // Still set path and base-name in the case the library switches to file
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("nobody-should-use-this"));

    // Attempting to Load the library should fail.
    invalidDaemonTest("kea-dhcp6", AF_INET6, params);
}
#endif

#ifdef HAVE_MYSQL
/// @brief Test fixture for testing loading and unloading the legal log library
/// using MySQL database backend.
class MySqlLegalLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    MySqlLegalLibLoadTest() : LibLoadTest(LEGAL_LOG_LIB_SO){
        // Ensure we have the proper schema with no transient data.
        isc::db::test::createMySQLSchema();
    }

    /// @brief Destructor
    virtual ~MySqlLegalLibLoadTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        isc::db::test::destroyMySQLSchema();
    }
};

// Verifies that the load callout with correct MySQL setup instantiates.
TEST_F(MySqlLegalLibLoadTest, MySqlValidLoad) {

    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("type", data::Element::create("mysql"));
    params->set("name", data::Element::create("keatest"));
    params->set("user", data::Element::create("keatest"));
    params->set("password", data::Element::create("keatest"));

    // Still set path and base-name in the case the library switches to file
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("nobody-should-use-this"));

    // Load the library. Is there a way to check more than return code?
    validDaemonTest("kea-dhcp4", AF_INET, params);
}

// Verifies that the load callout with incorrect MySQL setup fails.
TEST_F(MySqlLegalLibLoadTest, MySqlInvalidLoad) {

    // Prepare parameters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("type", data::Element::create("mysql"));
    // name is mandatory
    params->set("user", data::Element::create("keatest"));
    params->set("password", data::Element::create("keatest"));

    // Still set path and base-name in the case the library switches to file
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("nobody-should-use-this"));

    // Attempting to Load the library should fail.
    invalidDaemonTest("kea-dhcp6", AF_INET6, params);
}
#endif

} // end of anonymous namespace
