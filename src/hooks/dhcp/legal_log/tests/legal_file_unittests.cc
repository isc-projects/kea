// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <legal_file.h>

#include <gtest/gtest.h>

#include "boost/date_time/posix_time/posix_time.hpp"
#include <locale>
#include <sys/stat.h>

using namespace std;
using namespace isc;
using namespace legal_log;

namespace {

/// @brief Derivation of LegalFile which provides an overridden date mechanism
/// This class overrides LegalFile::today() with an implementation that returns
/// fixed value, rather than based on the actual system time.  This simplifies
/// testing file rotation.
class TestableLegalFile : public LegalFile {
public:
    /// @brief Constructor
    ///
    /// Create a LegalFile for the given file name without opening the file.
    /// @param today - The date with which to override LegalFile::today()
    ///
    /// @throw LegalFileError if given file name is empty.
    TestableLegalFile(boost::gregorian::date today)
        : LegalFile(TEST_DATA_BUILDDIR, "legal"), today_(today) {
    }

    /// @brief Destructor.
    ////
    /// The destructor does call the close method.
    virtual ~TestableLegalFile() {};

    /// @brief Overrides LegalFile::today()
    /// @return value of member variable today_
    virtual boost::gregorian::date today() {
        return (today_);
    }

    /// @brief Overrides LegalFile::now()
    /// @return
    virtual time_t now() {
        struct tm now_tm = boost::gregorian::to_tm(today_);
        return (mktime(&now_tm));
    }

    /// @brief Sets the override date value
    /// @param - new value for the override date
    void setToday(boost::gregorian::date day) {
        today_ = day;
    }
    /// @brief Override date value
    boost::gregorian::date today_;
};

/// @brief Test fixture for testing LegalFile.
/// It provides tools for erasing test files, altering date values,
/// generating file names, checking file existance and content.
class LegalFileTest : public ::testing::Test {
public:
    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    /// over from previous tests
    LegalFileTest() : today_(boost::gregorian::day_clock::local_day()) {
        wipeFiles();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LegalFileTest() {
        wipeFiles();
    }

    /// @brief Removes files that may be left over from previous tests
    void wipeFiles() {
        ::remove((genName(today_)).c_str());
        ::remove((genName(adjustDay(today_, 1))).c_str());
    }

    /// @brief Returns a new date by adding given days to a given date
    /// @param org_day - date to adjust
    /// @param days - the number of days to add (may be negative)
    /// @return - the new date
    boost::gregorian::date adjustDay(const boost::gregorian::date& org_day,
                                       int days) {
        boost::gregorian::date_duration dd(days);
        return (org_day + dd);
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
    /// Uses the same formatting as LegalFile to build file names
    ///
    /// @param day - date to use in the file name
    /// @return - the generated file name
    std::string genName(const boost::gregorian::date& day)  {
        boost::gregorian::date::ymd_type ymd = day.year_month_day();
        std::ostringstream stream;
        stream << TEST_DATA_BUILDDIR << "/" << "legal" << "." << ymd.year
               << std::right << std::setfill('0') << std::setw(2)
               << ymd.month.as_number()
               << ymd.day << ".txt";
        return(stream.str());
    }

    /// @brief Check a file's contents against an expected set of lines
    ///
    /// Passes if the given file's content matches. Fails otherwise.
    ///
    /// @param file_name - name of the file to read
    /// @param expected_lines - a vector of the lines expected to be found
    /// in the file (entries DO NOT include EOL)
    void checkFileLines(const std::string& file_name,
                        const std::string& now_string,
                        const std::vector<std::string>& expected_lines) {
        std::ifstream is;
        is.open(file_name);
        ASSERT_TRUE(is.good()) << "Could not open file: " << file_name;

        int i = 0;
        while (!is.eof()) {
            char buf[128];

            is.getline(buf, sizeof(buf));
            if (is.gcount() > 0) {
                ASSERT_TRUE(i < expected_lines.size())
                        << "Too many entries in file: " << file_name;

                std::string cmp_line = now_string + " " + expected_lines[i];
                ASSERT_EQ(cmp_line, buf)
                        << "line mismatch in: " << file_name
                        << " at line:" << i;

                ++i;
            }
        }

        ASSERT_EQ(i, expected_lines.size())
                    << "Not enough entries in file: " << file_name;
    }

    /// @brief Returns the current timezone abbreviate as a string
    std::string getTimezone()  {
        char buffer[16];
        time_t curtime;
        time(&curtime);
        struct tm* timeinfo;
        timeinfo = localtime(&curtime);

        strftime(buffer, sizeof(buffer), "%Z", timeinfo);
        return (std::string(buffer));
    }

    /// @brief The current date
    boost::gregorian::date today_;
};

/// @brief Defines a pointer to a TestableLegalFile
typedef boost::shared_ptr<TestableLegalFile> TestableLegalFilePtr;

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
