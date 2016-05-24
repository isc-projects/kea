// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file Contains tests that exercise the basic functionality of the
// class RotatingFile.  These tests are independent of the hooks framework.

#include <exceptions/exceptions.h>
#include <test_utils.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace isc;
using namespace legal_log;

namespace {

/// @brief Tests the RotatingFile constructor.
TEST_F(RotatingFileTest, invalidConstruction) {
    // Verify that a RotatingFile with empty path is rejected.
    ASSERT_THROW(RotatingFile("", "legal"), RotatingFileError);

    // Verify that a RotatingFile with an empty base name is rejected.
    ASSERT_THROW(RotatingFile(TEST_DATA_BUILDDIR, ""), RotatingFileError);
}

/// @brief Tests opening and closing RotatingFile
TEST_F(RotatingFileTest, openFile) {
    TestableRotatingFilePtr rot_file;

    // Construct the legal file
    ASSERT_NO_THROW(rot_file.reset(new TestableRotatingFile(today_)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rot_file->isOpen());
    std::string exp_name = genName(today_);
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW(rot_file->open());

    // Verify that the name is correct, the physcial file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rot_file->getFileName());
    EXPECT_TRUE(fileExists(rot_file->getFileName()));
    EXPECT_TRUE(rot_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW(rot_file->close());
    EXPECT_FALSE(rot_file->isOpen());
}

/// @brief Tests file rotation
TEST_F(RotatingFileTest, rotateFile) {
    TestableRotatingFilePtr rot_file;

    // Construct the legal file
    ASSERT_NO_THROW(rot_file.reset(new TestableRotatingFile(today_)));

    // Open the file
    ASSERT_NO_THROW(rot_file->open());
    EXPECT_TRUE(fileExists(rot_file->getFileName()));
    EXPECT_TRUE(rot_file->isOpen());

    // Use the override to go to tomorrow.
    boost::gregorian::date tomorrow = adjustDay(today_, 1);
    rot_file->setToday(tomorrow);

    // Call rotate
    ASSERT_NO_THROW(rot_file->rotate());

    // Verify that we change files
    std::string exp_name = genName(tomorrow);
    EXPECT_EQ(exp_name, rot_file->getFileName());
    EXPECT_TRUE(fileExists(rot_file->getFileName()));
    EXPECT_TRUE(rot_file->isOpen());
}

/// @brief Verifies that the timestamp string generator works properly
TEST_F(RotatingFileTest, nowString) {
    TestableRotatingFilePtr rot_file;

    // Construct the legal file
    boost::gregorian::date test_day(2016, boost::gregorian::May, 02);
    ASSERT_NO_THROW(rot_file.reset(new TestableRotatingFile(test_day)));

    // Should be the same as "%Y-%m-%d %H:%M:%S %Z"
    std::string  expected_string = "2016-05-02 00:00:00 " + getTimezone();
    std::string now_string;
    ASSERT_NO_THROW(now_string = rot_file->getNowString());
    EXPECT_EQ(expected_string, now_string);

    // Try with an alternative format
    ASSERT_NO_THROW(now_string = rot_file->getNowString("%d%m%Y"));
    EXPECT_EQ("02052016",  now_string);

    // Try with one that's too long. This should throw.
    char buf[256];
    memset(buf, '-', sizeof(buf));
    std::string format("%Y%m%d");
    format += buf;
    ASSERT_THROW(rot_file->getNowString(format), RotatingFileError);
}

/// @brief Tests writing to a file
TEST_F(RotatingFileTest, writeFile) {
    TestableRotatingFilePtr rot_file;

    // Construct the legal file
    ASSERT_NO_THROW(rot_file.reset(new TestableRotatingFile(today_)));

    // Open the file
    ASSERT_NO_THROW(rot_file->open());

    // Write to the file
    std::string today_now_string = rot_file->getNowString();
    std::vector<std::string> today_lines;
    today_lines.push_back("one");
    today_lines.push_back("two");
    for (int i = 0; i < today_lines.size(); i++) {
        ASSERT_NO_THROW(rot_file->writeln(today_lines[i]));
    }

    // Use the override to go to tomorrow.
    // This should cause the file to rotate during the next
    // write
    boost::gregorian::date tomorrow = adjustDay(today_, 1);
    rot_file->setToday(tomorrow);

    // Write to the file
    std::string tomorrow_now_string = rot_file->getNowString();
    std::vector<std::string> tomorrow_lines;
    tomorrow_lines.push_back("three");
    tomorrow_lines.push_back("four");
    for (int i = 0; i < today_lines.size(); i++) {
        ASSERT_NO_THROW(rot_file->writeln(tomorrow_lines[i]));
    }

    // Close the file to flush writes
    ASSERT_NO_THROW(rot_file->close());

    // Make we have the correct content in both files.
    checkFileLines(genName(today_), today_now_string, today_lines);
    checkFileLines(genName(tomorrow), tomorrow_now_string, tomorrow_lines);
}

// Verifies output of genDurationString()
TEST_F(RotatingFileTest, genDurationString) {
    EXPECT_EQ("0 hrs 0 mins 0 secs", RotatingFile::genDurationString(0));
    EXPECT_EQ("0 hrs 0 mins 1 secs", RotatingFile::genDurationString(1));
    EXPECT_EQ("0 hrs 1 mins 1 secs", RotatingFile::genDurationString(61));
    EXPECT_EQ("1 hrs 1 mins 1 secs", RotatingFile::genDurationString(3661));
    EXPECT_EQ("1 days 0 hrs 0 mins 0 secs",
              RotatingFile::genDurationString(24*60*60));
    EXPECT_EQ("1 days 1 hrs 1 mins 1 secs",
              RotatingFile::genDurationString(24*60*60 + 3661));
    EXPECT_EQ("182 days 17 hrs 21 mins 11 secs",
              RotatingFile::genDurationString(15783671 + 3600));
    EXPECT_EQ("49710 days 6 hrs 28 mins 15 secs",
              RotatingFile::genDurationString(0xFFFFFFFF));
}

} // end of anonymous namespace
