// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file Contains tests that exercise the basic functionality of the
// class RotatingFile.  These tests are independent of the hooks framework.

#include <config.h>

#include <exceptions/exceptions.h>
#include <test_utils.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace legal_log;
using namespace std;

namespace {

/// @brief Tests the RotatingFile constructor.
TEST_F(RotatingFileTest, invalidConstruction) {
    // Verify that a RotatingFile with empty path is rejected.
    ASSERT_THROW_MSG(RotatingFile("", "legal"), BackendStoreError,
                     "path cannot be blank");

    // Verify that a RotatingFile with an empty base name is rejected.
    ASSERT_THROW_MSG(RotatingFile(TEST_DATA_BUILDDIR, ""), BackendStoreError,
                     "file name cannot be blank");

    std::string name = "invalid";

    // Verify that a RotatingFile with an invalid prerotate action is rejected.
    ASSERT_THROW(RotatingFile(TEST_DATA_BUILDDIR, "legal",
                              RotatingFile::TimeUnit::Day, 1, name, ""),
                 BackendStoreError);

    // Verify that a RotatingFile with an invalid postrotate action is rejected.
    ASSERT_THROW(RotatingFile(TEST_DATA_BUILDDIR, "legal",
                              RotatingFile::TimeUnit::Day, 1, "", name),
                 BackendStoreError);

    name = INVALID_FORENSIC_PREROTATE_TEST_SH;

    // Verify that a RotatingFile with a non executable prerotate action is
    // rejected.
    ASSERT_THROW(RotatingFile(TEST_DATA_BUILDDIR, "legal",
                              RotatingFile::TimeUnit::Day, 1, name, ""),
                 BackendStoreError);

    name = INVALID_FORENSIC_POSTROTATE_TEST_SH;

    // Verify that a RotatingFile with a non executable postrotate action is
    // rejected.
    ASSERT_THROW(RotatingFile(TEST_DATA_BUILDDIR, "legal",
                              RotatingFile::TimeUnit::Day, 1, "", name),
                 BackendStoreError);
}

/// @brief Tests #5579 fix.
TEST_F(RotatingFileTest, getYearMonthDay) {
    boost::gregorian::date date(2018,1,1);
    EXPECT_EQ("20180101", RotatingFile::getYearMonthDay(boost::gregorian::to_tm(date)));
}

/// @brief Tests opening and closing RotatingFile
TEST_F(RotatingFileTest, openFile) {
    // Construct the legal file
    ASSERT_NO_THROW(rotating_file_.reset(new TestableRotatingFile(time_)));

    // Check the type is logfile
    EXPECT_EQ("logfile", rotating_file_->getType());

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rotating_file_->isOpen());
    std::string exp_name = genName(today());
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW(rotating_file_->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
}

/// @brief Tests file rotation
TEST_F(RotatingFileTest, rotateFile) {
    // Construct the legal file
    ASSERT_NO_THROW(rotating_file_.reset(new TestableRotatingFile(time_)));

    // Open the file
    ASSERT_NO_THROW(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Use the override to go to tomorrow.
    boost::gregorian::date tomorrow = adjustDay(today(), 1);
    rotating_file_->setNow(boost::gregorian::to_tm(tomorrow));

    // Call rotate
    ASSERT_NO_THROW(rotating_file_->rotate());

    // Verify that we change files
    std::string exp_name = genName(tomorrow);
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());
}

/// @brief Verifies that the timestamp string generator works properly
TEST_F(RotatingFileTest, nowString) {
    // Construct the legal file
    boost::gregorian::date test_day(2016, boost::gregorian::May, 02);
    ASSERT_NO_THROW(rotating_file_.reset(new TestableRotatingFile(boost::gregorian::to_tm(test_day))));

    // Should be the same as "%Y-%m-%d %H:%M:%S.%Q %Z", where %Q is the
    // fractional part of the timestamp (in microseconds).
    rotating_file_->setTimestampFormat("%Y-%m-%d %H:%M:%S.%Q %Z --- %%Q%%%Q%%Q");
    std::string expected_string = "2016-05-02 00:00:00.000.000 " +
        getTimezone(rotating_file_->now().tv_sec) + " --- %Q%000.000%Q";

    std::string now_string;
    ASSERT_NO_THROW(now_string = rotating_file_->getNowString());
    EXPECT_EQ(expected_string, now_string);

    // Try with an alternative format
    ASSERT_NO_THROW(now_string = rotating_file_->getNowString("%d%m%Y"));
    EXPECT_EQ("02052016", now_string);

    // Try with one that's too long. This should throw.
    std::string format("%Y%m%d");
    format += std::string(256, '-');
    ASSERT_THROW(rotating_file_->getNowString(format), BackendStoreError);

    // Try with an alternative format set via a load-time parameter. Use a few
    // of the more obscure strftime format specifiers to verify that it's
    // actually different from the "plain" %Y-%m-%d %M:%M:%S %Z format.
    BackendStore::instance() = rotating_file_;
    data::ElementPtr params = data::Element::createMap();
    params->set("timestamp-format", data::Element::create("%A%t%w %F%%"));
    ASSERT_NO_THROW_LOG(rotating_file_->parseExtraParameters(params));
    ASSERT_NO_THROW_LOG(now_string = rotating_file_->getNowString());
    EXPECT_EQ("Monday\t1 2016-05-02%", now_string);
}

/// @brief Tests writing to a file
TEST_F(RotatingFileTest, writeFile) {
    // Construct the legal file
    ASSERT_NO_THROW(rotating_file_.reset(new TestableRotatingFile(time_)));

    // Open the file
    ASSERT_NO_THROW(rotating_file_->open());

    // Write to the file
    std::string today_now_string = rotating_file_->getNowString();
    std::vector<std::string> today_lines;
    today_lines.push_back("one");
    today_lines.push_back("two");
    for (int i = 0; i < today_lines.size(); i++) {
        ASSERT_NO_THROW(rotating_file_->writeln(today_lines[i], ""));
    }

    // Use the override to go to tomorrow.
    // This should cause the file to rotate during the next
    // write
    boost::gregorian::date tomorrow = adjustDay(today(), 1);
    rotating_file_->setNow(boost::gregorian::to_tm(tomorrow));

    // Write to the file
    std::string tomorrow_now_string = rotating_file_->getNowString();
    std::vector<std::string> tomorrow_lines;
    tomorrow_lines.push_back("three");
    tomorrow_lines.push_back("four");
    for (int i = 0; i < today_lines.size(); i++) {
        ASSERT_NO_THROW(rotating_file_->writeln(tomorrow_lines[i], ""));
    }

    // Close the file to flush writes
    ASSERT_NO_THROW(rotating_file_->close());

    // Make we have the correct content in both files.
    checkFileLines(genName(today()), today_now_string, today_lines);
    checkFileLines(genName(tomorrow), tomorrow_now_string, tomorrow_lines);
}

/// @brief Tests open file when other files are or are not present
TEST_F(RotatingFileTest, useSecondAsTimeUnitOpenFile) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rotating_file_->isOpen());
    std::string exp_name = genName(time_);
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 1 second does reuse old file
    time_ = adjustSecond(time_, 1);
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 5 seconds does not reuse old file
    // (6 seconds since the first file was created)
    time_ = adjustSecond(time_, 5);
    std::string new_exp_name = genName(time_);
    TestableRotatingFilePtr new_file;
    ASSERT_NO_THROW_LOG(new_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file->close());
    EXPECT_FALSE(new_file->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 6 seconds does reuse old file
    TestableRotatingFilePtr same_file_multiple_existing;
    ASSERT_NO_THROW_LOG(same_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->close());
    EXPECT_FALSE(same_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 10 seconds does not reuse old file
    // (16 seconds since the first file was created)
    time_ = adjustSecond(time_, 10);
    new_exp_name = genName(time_);
    TestableRotatingFilePtr new_file_multiple_existing;
    ASSERT_NO_THROW_LOG(new_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->close());
    EXPECT_FALSE(new_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
}

/// @brief Tests file rotation when other files are or are not present
TEST_F(RotatingFileTest, useSecondAsTimeUnitRotateFile) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(time_);

    // Verify that rotating the file after 1 second does not create new file
    time_ = adjustSecond(time_, 1);
    rotating_file_->setNow(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did not change files
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that rotating the file after 5 seconds does create new file
    // (6 seconds since the first file was created)
    time_ = adjustSecond(time_, 5);
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 5 seconds does reuse old file
    // (11 seconds since the first file was created and also 5 seconds since second file was created)
    time_ = adjustSecond(time_, 5);
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that rotating the file after 5 seconds does create new file
    // (10 seconds after the second file was created)
    time_ = adjustSecond(time_, 5);
    same_file->setNow(time_);

    new_exp_name = genName(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(same_file->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
}

/// @brief Tests open file when other files are or are not present
TEST_F(RotatingFileTest, useDayAsTimeUnitOpenFile) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 5)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rotating_file_->isOpen());
    std::string exp_name = genName(today());
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 1 day does reuse old file
    time_ = boost::gregorian::to_tm(adjustDay(today(), 1));
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 5 days does not reuse old file
    // (6 days since the first file was created)
    time_ = boost::gregorian::to_tm(adjustDay(today(), 5));
    std::string new_exp_name = genName(today());
    TestableRotatingFilePtr new_file;
    ASSERT_NO_THROW_LOG(new_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file->close());
    EXPECT_FALSE(new_file->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 6 days does reuse old file
    TestableRotatingFilePtr same_file_multiple_existing;
    ASSERT_NO_THROW_LOG(same_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->close());
    EXPECT_FALSE(same_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 10 days does not reuse old file
    // (16 days since the first file was created)
    time_ = boost::gregorian::to_tm(adjustDay(today(), 10));
    new_exp_name = genName(today());
    TestableRotatingFilePtr new_file_multiple_existing;
    ASSERT_NO_THROW_LOG(new_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->close());
    EXPECT_FALSE(new_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
}

/// @brief Tests file rotation when other files are or are not present
TEST_F(RotatingFileTest, useDayAsTimeUnitRotateFile) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(today());

    // Verify that rotating the file after 1 day does not create new file
    time_ = boost::gregorian::to_tm(adjustDay(today(), 1));
    rotating_file_->setNow(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did not change files
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that rotating the file after 5 days does create new file
    // (6 days since the first file was created)
    time_ = boost::gregorian::to_tm(adjustDay(today(), 5));
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 5 days does reuse old file
    // (11 days since the first file was created and also 5 days since second file was created)
    time_ = boost::gregorian::to_tm(adjustDay(today(), 5));
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Day, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that rotating the file after 5 days does create new file
    // (10 days after the second file was created)
    time_ = boost::gregorian::to_tm(adjustDay(today(), 5));
    same_file->setNow(time_);

    new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(same_file->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
}

/// @brief Tests open file when other files are or are not present
TEST_F(RotatingFileTest, useMonthAsTimeUnitOpenFile) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 5)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rotating_file_->isOpen());
    std::string exp_name = genName(today());
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 1 month does reuse old file
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 1));
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 5 months does not reuse old file
    // (6 months since the first file was created)
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 5));
    std::string new_exp_name = genName(today());
    TestableRotatingFilePtr new_file;
    ASSERT_NO_THROW_LOG(new_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file->close());
    EXPECT_FALSE(new_file->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 6 months does reuse old file
    TestableRotatingFilePtr same_file_multiple_existing;
    ASSERT_NO_THROW_LOG(same_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->close());
    EXPECT_FALSE(same_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 10 months does not reuse old file
    // (16 months since the first file was created)
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 10));
    new_exp_name = genName(today());
    TestableRotatingFilePtr new_file_multiple_existing;
    ASSERT_NO_THROW_LOG(new_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->close());
    EXPECT_FALSE(new_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
}

/// @brief Tests file rotation when other files are or are not present
TEST_F(RotatingFileTest, useMonthAsTimeUnitRotateFile) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(today());

    // Verify that rotating the file after 1 month does not create new file
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 1));
    rotating_file_->setNow(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did not change files
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that rotating the file after 5 months does create new file
    // (6 months since the first file was created)
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 5));
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 5 months does reuse old file
    // (11 months since the first file was created and also 5 months since second file was created)
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 5));
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Month, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that rotating the file after 5 months does create new file
    // (10 months after the second file was created)
    time_ = boost::gregorian::to_tm(adjustMonth(today(), 5));
    same_file->setNow(time_);

    new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(same_file->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
}

/// @brief Tests open file when other files are or are not present
TEST_F(RotatingFileTest, useYearAsTimeUnitOpenFile) {
    // Go far from 2038.
    time_ = boost::gregorian::to_tm(adjustYear(today(), -20));

    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 5)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rotating_file_->isOpen());
    std::string exp_name = genName(today());
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 1 year does reuse old file
    time_ = boost::gregorian::to_tm(adjustYear(today(), 1));
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 5 years does not reuse old file
    // (6 years since the first file was created)
    time_ = boost::gregorian::to_tm(adjustYear(today(), 5));
    std::string new_exp_name = genName(today());
    TestableRotatingFilePtr new_file;
    ASSERT_NO_THROW_LOG(new_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file->close());
    EXPECT_FALSE(new_file->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 6 years does reuse old file
    TestableRotatingFilePtr same_file_multiple_existing;
    ASSERT_NO_THROW_LOG(same_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file_multiple_existing->close());
    EXPECT_FALSE(same_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 10 years does not reuse old file
    // (16 years since the first file was created)
    time_ = boost::gregorian::to_tm(adjustYear(today(), 10));
    new_exp_name = genName(today());
    TestableRotatingFilePtr new_file_multiple_existing;
    ASSERT_NO_THROW_LOG(new_file_multiple_existing.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file_multiple_existing->getFileName());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file_multiple_existing->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file_multiple_existing->close());
    EXPECT_FALSE(new_file_multiple_existing->isOpen());
    EXPECT_TRUE(fileExists(new_file_multiple_existing->getFileName()));
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
}

/// @brief Tests file rotation when other files are or are not present
TEST_F(RotatingFileTest, useYearAsTimeUnitRotateFile) {
    // Go far from 2038.
    time_ = boost::gregorian::to_tm(adjustYear(today(), -20));

    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 5)));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(today());

    // Verify that rotating the file after 1 year does not create new file
    time_ = boost::gregorian::to_tm(adjustYear(today(), 1));
    rotating_file_->setNow(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did not change files
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that rotating the file after 5 years does create new file
    // (6 years since the first file was created)
    time_ = boost::gregorian::to_tm(adjustYear(today(), 5));
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 5 years does reuse old file
    // (11 years since the first file was created and also 5 years since second file was created)
    time_ = boost::gregorian::to_tm(adjustYear(today(), 5));
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 10)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that rotating the file after 5 years does create new file
    // (10 years after the second file was created)
    time_ = boost::gregorian::to_tm(adjustYear(today(), 5));
    same_file->setNow(time_);

    new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(same_file->rotate());

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
}

/// @brief Tests open file when other files are or are not present when rotation
/// is disabled
TEST_F(RotatingFileTest, useYearAsTimeUnitOpenFileNoRotate) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 0)));

    // Verify that the phsyical file does not yet exist and
    // does not report as open
    EXPECT_FALSE(rotating_file_->isOpen());
    std::string exp_name = genName(today());
    EXPECT_FALSE(fileExists(exp_name));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(rotating_file_->close());
    EXPECT_FALSE(rotating_file_->isOpen());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));

    // Verify that opening the file after 1 second does reuse old file
    time_ = adjustSecond(time_, 1);
    TestableRotatingFilePtr same_file;
    ASSERT_NO_THROW_LOG(same_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 0)));

    // Open the file
    ASSERT_NO_THROW_LOG(same_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(exp_name, same_file->getFileName());
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(same_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(same_file->close());
    EXPECT_FALSE(same_file->isOpen());
    EXPECT_TRUE(fileExists(same_file->getFileName()));

    // Verify that opening the file after 1 day does not reuse old file
    time_ = boost::gregorian::to_tm(adjustDay(today(), 1));
    std::string new_exp_name = genName(today());
    TestableRotatingFilePtr new_file;
    ASSERT_NO_THROW_LOG(new_file.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 0)));

    // Open the file
    ASSERT_NO_THROW_LOG(new_file->open());

    // Verify that the name is correct, the physical file exists, and
    // reports as open
    EXPECT_EQ(new_exp_name, new_file->getFileName());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
    EXPECT_TRUE(new_file->isOpen());

    // Verify that close works
    ASSERT_NO_THROW_LOG(new_file->close());
    EXPECT_FALSE(new_file->isOpen());
    EXPECT_TRUE(fileExists(new_file->getFileName()));
    EXPECT_TRUE(fileExists(same_file->getFileName()));
}

/// @brief Tests file rotation when other files are or are not present when
/// rotation is disabled
TEST_F(RotatingFileTest, useYearAsTimeUnitRotateFileNoRotate) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Year, 0)));

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(today());

    time_ = adjustSecond(time_, 1);
    rotating_file_->setNow(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did not change files
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    time_ = boost::gregorian::to_tm(adjustYear(today(), 1));
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(today());

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());

    // Verify that we did not change files
    EXPECT_EQ(exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_FALSE(fileExists(new_exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());
}

/// @brief Tests file rotation with prerotate action
TEST_F(RotatingFileTest, prerotateActions) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5,
                                                                  FORENSIC_PREROTATE_TEST_SH, "")));

    BackendStore::instance() = rotating_file_;

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(time_);

    time_ = adjustSecond(time_, 5);
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());
    waitForFile(exp_name);
    waitForFile(new_exp_name);
    getIOService()->poll();

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    exp_name += "-prerotate-completed";
    new_exp_name += "-postrotate-completed";
    waitForFile(exp_name);
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_FALSE(fileExists(new_exp_name));

    ::remove(exp_name.c_str());
    ::remove(new_exp_name.c_str());
}

/// @brief Tests file rotation with postrotate action
TEST_F(RotatingFileTest, postrotateActions) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5,
                                                                  "", FORENSIC_POSTROTATE_TEST_SH)));

    BackendStore::instance() = rotating_file_;

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(time_);

    time_ = adjustSecond(time_, 5);
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());
    waitForFile(exp_name);
    waitForFile(new_exp_name);
    getIOService()->poll();

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    exp_name += "-prerotate-completed";
    new_exp_name += "-postrotate-completed";
    waitForFile(new_exp_name);
    EXPECT_FALSE(fileExists(exp_name));
    EXPECT_TRUE(fileExists(new_exp_name));

    ::remove(exp_name.c_str());
    ::remove(new_exp_name.c_str());
}

/// @brief Tests file rotation with prerotate and postrotate actions
TEST_F(RotatingFileTest, prerotateAndPostrotateActions) {
    // Construct the legal file
    ASSERT_NO_THROW_LOG(rotating_file_.reset(new TestableRotatingFile(time_, RotatingFile::TimeUnit::Second, 5,
                                                                  FORENSIC_PREROTATE_TEST_SH,
                                                                  FORENSIC_POSTROTATE_TEST_SH)));

    BackendStore::instance() = rotating_file_;

    // Open the file
    ASSERT_NO_THROW_LOG(rotating_file_->open());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(rotating_file_->isOpen());

    std::string exp_name = genName(time_);

    time_ = adjustSecond(time_, 5);
    rotating_file_->setNow(time_);

    std::string new_exp_name = genName(time_);

    // Call rotate
    ASSERT_NO_THROW_LOG(rotating_file_->rotate());
    waitForFile(exp_name);
    waitForFile(new_exp_name);
    getIOService()->poll();

    // Verify that we did change files
    EXPECT_EQ(new_exp_name, rotating_file_->getFileName());
    EXPECT_TRUE(fileExists(rotating_file_->getFileName()));
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(rotating_file_->isOpen());

    exp_name += "-prerotate-completed";
    new_exp_name += "-postrotate-completed";
    waitForFile(exp_name);
    waitForFile(new_exp_name);
    EXPECT_TRUE(fileExists(exp_name));
    EXPECT_TRUE(fileExists(new_exp_name));

    ::remove(exp_name.c_str());
    ::remove(new_exp_name.c_str());
}

} // end of anonymous namespace
