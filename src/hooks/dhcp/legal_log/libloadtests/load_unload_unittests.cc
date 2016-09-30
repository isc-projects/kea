// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which excercise the load and unload
/// functions in the legal log hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().  In order to eliminate
/// potentially indeterminate behavior these tests should NOT be linked
/// against the legal log library (as is done in ../tests).

#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <locale>
#include <sys/stat.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace hooks;

namespace {

/// @brief Test fixture for testing loading and unloading the legal log library
/// It provides tools for erasing test files, altering date values,
/// generating file names and checking file existance.
class LegalLibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    /// over from previous tests
    LegalLibLoadTest() {
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
        stream << "rm " << TEST_DATA_BUILDDIR << "/" << "test-legal" << ".*.txt 2>/dev/null";
        int result = ::system(stream.str().c_str());
        if (result != 0) {
            // Ignore the result, because it may well be non-zero value when
            // files to be removed don't exist.
            ;
        }
        HooksManager::unloadLibraries();
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
    std::string genName(const boost::gregorian::date& day)  {
        boost::gregorian::date::ymd_type ymd = day.year_month_day();
        std::ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "test-legal" << "." << ymd.year
               << std::right << std::setfill('0') << std::setw(2)
               << ymd.month.as_number()
               << ymd.day << ".txt";
        return(stream.str());
    }
};

// Verifies that the load callout, given a viable path and base name,
// instantiates and opens the RotatingFile.
// WARNING!!!  Even though the load() function can supply default values
// for both path and base-name, it is ill-advised to conduct such a test as
// one runs the risk of harming a legal file opened with default values
// by a live instance of Kea.
TEST_F(LegalLibLoadTest, validLoad) {

    // Prepare paramters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    params->set("path", data::Element::create(TEST_DATA_BUILDDIR));
    params->set("base-name", data::Element::create("test-legal"));

    HookLibsCollection libraries;
    libraries.push_back(make_pair(LEGAL_LOG_LIB_SO, params));

    // Grag the current day and make sure the file doesn't already exist.
    boost::gregorian::date today(boost::gregorian::day_clock::local_day());
    std::string expected_filename = genName(today);
    ASSERT_FALSE(fileExists(expected_filename));

    // Load the library.  This should create the expected file name.
    EXPECT_TRUE(HooksManager::loadLibraries(libraries));

    // In order to avoid the case where this test straddles midnight we'll look
    // for the file using the date we grabbed just before loading the library
    // and if that one doesn't exist, we'll refresh the date and try again. One of
    // the two files must exist otherwise the load failed to open it.
    if (!fileExists(expected_filename)) {
        std::string expected_filename = genName(today);
        EXPECT_TRUE(fileExists(expected_filename));
    }

    // Library should unload with no issue.
    EXPECT_NO_THROW(HooksManager::unloadLibraries());

    // File should still exist.
    EXPECT_TRUE(fileExists(expected_filename));
}

// Verifies that the load callout, given an inaccessible path fails to
// to load.
TEST_F(LegalLibLoadTest, invalidLoad) {
    // Prepare paramters for the callout parameters library.
    data::ElementPtr params = data::Element::createMap();
    std::string bogus_path(TEST_DATA_BUILDDIR);
    bogus_path +=  "utter-nonesense-which-doesnt-exist";
    params->set("path", data::Element::create(bogus_path));
    params->set("base-name", data::Element::create("test-legal"));

    HookLibsCollection libraries;
    libraries.push_back(make_pair(LEGAL_LOG_LIB_SO, params));

    // Attemptng to Load the library should fail.
    EXPECT_FALSE(HooksManager::loadLibraries(libraries));
}


} // end of anonymous namespace
