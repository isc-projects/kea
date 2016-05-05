// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file Contains tests that exercise the basic functionality of the
// class LegalFile.  These tests are independent of the hooks framework.

#include <exceptions/exceptions.h>
#include <test_utils.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace isc;
using namespace legal_log;

namespace {

/// @brief Tests the LegalFile constructor.
TEST_F(LegalFileTest, invalidConstruction) {
    // Verify that a LegalFile with empty path is rejected.
    ASSERT_THROW(LegalFile("", "legal"), LegalFileError);

    // Verify that a LegalFile with an empty base name is rejected.
    ASSERT_THROW(LegalFile("TEST_DATA_BUILDDIR", ""), LegalFileError);
}

/// @brief Tests opening and closing LegalFile
TEST_F(LegalFileTest, openFile) {
    TestableLegalFilePtr legal_file;

    // Construct the legal file
    ASSERT_NO_THROW(legal_file.reset(new TestableLegalFile(today_)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(legal_file->isOpen());
    std::string exp_name = genName(today_);
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW(legal_file->open());

    // Verify that the name is correct, the physcial file exists, and
    // reports as open
    EXPECT_EQ(exp_name, legal_file->getFileName());
    EXPECT_TRUE(fileExists(legal_file->getFileName()));
    EXPECT_TRUE(legal_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW(legal_file->close());
    EXPECT_FALSE(legal_file->isOpen());
}

/// @brief Tests file rotation
TEST_F(LegalFileTest, rotateFile) {
    TestableLegalFilePtr legal_file;

    // Construct the legal file
    ASSERT_NO_THROW(legal_file.reset(new TestableLegalFile(today_)));

    // Open the file
    ASSERT_NO_THROW(legal_file->open());
    EXPECT_TRUE(fileExists(legal_file->getFileName()));
    EXPECT_TRUE(legal_file->isOpen());

    // Use the override to go to tomorrow.
    boost::gregorian::date tomorrow = adjustDay(today_, 1);
    legal_file->setToday(tomorrow);

    // Call rotate
    ASSERT_NO_THROW(legal_file->rotate());

    // Verify that we change files
    std::string exp_name = genName(tomorrow);
    EXPECT_EQ(exp_name, legal_file->getFileName());
    EXPECT_TRUE(fileExists(legal_file->getFileName()));
    EXPECT_TRUE(legal_file->isOpen());
}

/// @brief Verifies that the timestamp string generator works properly
TEST_F(LegalFileTest, nowString) {
    TestableLegalFilePtr legal_file;

    // Construct the legal file
    boost::gregorian::date test_day(2016, boost::gregorian::May, 02);
    ASSERT_NO_THROW(legal_file.reset(new TestableLegalFile(test_day)));

    // Should be the same as "%Y-%m-%d %H:%M:%S %Z"
    std::string  expected_string = "2016-05-02 00:00:00 " + getTimezone();
    std::string now_string;
    ASSERT_NO_THROW(now_string = legal_file->getNowString());
    EXPECT_EQ(expected_string, now_string);

    // Try with an alternative format
    ASSERT_NO_THROW(now_string = legal_file->getNowString("%d%m%Y"));
    EXPECT_EQ("02052016",  now_string);

    // Try with one that's too long. This should throw.
    char buf[256];
    memset(buf, '-', sizeof(buf));
    std::string format("%Y%m%d");
    format += buf;
    ASSERT_THROW(legal_file->getNowString(format), LegalFileError);
}

/// @brief Tests writing to a file
TEST_F(LegalFileTest, writeFile) {
    TestableLegalFilePtr legal_file;

    // Construct the legal file
    ASSERT_NO_THROW(legal_file.reset(new TestableLegalFile(today_)));

    // Open the file
    ASSERT_NO_THROW(legal_file->open());

    // Write to the file
    std::string today_now_string = legal_file->getNowString();
    std::vector<std::string> today_lines;
    today_lines.push_back("one");
    today_lines.push_back("two");
    for (int i = 0; i < today_lines.size(); i++) {
        ASSERT_NO_THROW(legal_file->writeln(today_lines[i]));
    }

    // Use the override to go to tomorrow.
    // This should cause the file to rotate during the next
    // write
    boost::gregorian::date tomorrow = adjustDay(today_, 1);
    legal_file->setToday(tomorrow);

    // Write to the file
    std::string tomorrow_now_string = legal_file->getNowString();
    std::vector<std::string> tomorrow_lines;
    tomorrow_lines.push_back("three");
    tomorrow_lines.push_back("four");
    for (int i = 0; i < today_lines.size(); i++) {
        ASSERT_NO_THROW(legal_file->writeln(tomorrow_lines[i]));
    }

    // Close the file to flush writes
    ASSERT_NO_THROW(legal_file->close());

    // Make we have the correct content in both files.
    checkFileLines(genName(today_), today_now_string, today_lines);
    checkFileLines(genName(tomorrow), tomorrow_now_string, tomorrow_lines);
}

// Verifies output of genDurationString()
TEST_F(LegalFileTest, genDurationString) {
    EXPECT_EQ("0 hrs 0 min 0 secs", LegalFile::genDurationString(0));
    EXPECT_EQ("0 hrs 0 min 1 secs", LegalFile::genDurationString(1));
    EXPECT_EQ("0 hrs 1 min 1 secs", LegalFile::genDurationString(61));
    EXPECT_EQ("1 hrs 1 min 1 secs", LegalFile::genDurationString(3661));
    EXPECT_EQ("1 day 0 hrs 0 min 0 secs",
              LegalFile::genDurationString(24*60*60));
    EXPECT_EQ("1 day 1 hrs 1 min 1 secs",
              LegalFile::genDurationString(24*60*60 + 3661));
    EXPECT_EQ("182 days 17 hrs 21 min 11 secs",
              LegalFile::genDurationString(15783671 + 3600));
    EXPECT_EQ("49710 days 6 hrs 28 min 15 secs",
              LegalFile::genDurationString(0xFFFFFFFF));
}

} // end of anonymous namespace
