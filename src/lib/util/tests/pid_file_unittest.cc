// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <util/pid_file.h>
#include <gtest/gtest.h>
#include <signal.h>

namespace {
using namespace isc::util;

#define TESTNAME "pid_file.test"
#define TESTNAME2 "pid_file.test.2"

class PIDFileTest : public ::testing::Test {
public:
    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    static std::string absolutePath(const std::string& filename);

    /// @brief Generate a random number for use as a PID
    ///
    /// @param start - the start of the range we want the PID in
    /// @param range - the size of the range for our PID
    ///
    /// @return returns a random value between start and start + range
    int randomizePID(const uint32_t start, const uint32_t range) {
        int pid;

        for (pid = (random() % range) + start;
             kill(pid, 0) == 0;
             ++pid)
            ;

        return (pid);
    }

protected:
    /// @brief Removes any old test files before the test
    virtual void SetUp() {
        removeTestFile();
    }

    /// @brief Removes any remaining test files after the test
    virtual void TearDown() {
        removeTestFile();
    }

private:
    /// @brief Removes any remaining test files
    void removeTestFile() const {
        remove(TESTNAME);
    }

};

std::string
PIDFileTest::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << filename;

    std::cerr << s.str() << std::endl;
    return (s.str());
}

/// @brief Test file writing and deletion. Start by removing
/// any leftover file. Then write a known PID to the file and
/// attempt to read the file and verify the PID. Next write
/// a second and verify a second PID to verify that an existing
/// file is properly overwritten.

TEST_F(PIDFileTest, writeAndDelete) {
    PIDFile pid_file(absolutePath(TESTNAME));
    std::ifstream fs;
    int pid(0);

    // Write a known process id
    pid_file.write(10);

    // Read the file and compare the pid
    fs.open(absolutePath(TESTNAME), std::ifstream::in);
    fs >> pid;
    EXPECT_TRUE(fs.good());
    EXPECT_EQ(pid, 10);
    fs.close();

    // Write a second known process id
    pid_file.write(20);

    // And comapre the second pid
    fs.open(absolutePath(TESTNAME), std::ifstream::in);
    fs >> pid;
    EXPECT_TRUE(fs.good());
    EXPECT_EQ(pid, 20);
    fs.close();

    // Delete the file
    pid_file.deleteFile();

    // And verify that it's gone
    fs.open(absolutePath(TESTNAME), std::ifstream::in);
    EXPECT_FALSE(fs.good());
    fs.close();
}

/// @brief Test checking a PID. Write the PID of the current
/// process to the PID file then verify that check indicates
/// the process is running.
TEST_F(PIDFileTest, pidInUse) {
    PIDFile pid_file(absolutePath(TESTNAME));

    // Write the current PID
    pid_file.write();

    // Check if we think the process is running
    EXPECT_TRUE(pid_file.check());
}

/// @brief Test checking a PID. Write a PID that isn't in use
/// to the PID file and verify that check indicates the process
/// isn't running. The PID may get used between when we select it
/// and write the file and when we check it. To minimize false
/// errors if the first call to check fails we try again with a
/// different range of values and only if both attempts fail do
/// we declare the test to have failed.
TEST_F(PIDFileTest, pidNotInUse) {
    PIDFile pid_file(absolutePath(TESTNAME));
    int pid;

    // get a pid betwen 10000 and 20000
    pid = randomizePID(10000, 10000);

    // write it
    pid_file.write(pid);

    // Check to see if we think the process is running
    if (!pid_file.check()) {
        return;
    }

    // get a pid betwen 40000 and 50000
    pid = randomizePID(10000, 40000);

    // write it
    pid_file.write(pid);

    // Check to see if we think the process is running
    EXPECT_FALSE(pid_file.check());
}

/// @brief Test checking a PID.  Write garbage to the PID file
/// and verify that check throws an error. In this situation
/// the caller should probably log an error and may decide to
/// continue or not depending on the requirements.
TEST_F(PIDFileTest, pidGarbage) {
    PIDFile pid_file(absolutePath(TESTNAME));
    std::ofstream fs;

    // Open the file and write garbage to it
    fs.open(absolutePath(TESTNAME), std::ofstream::out);
    fs << "text" << std::endl;
    fs.close();

    // Run the check, we expect to get an execption
    EXPECT_THROW(pid_file.check(), PIDCantReadPID);
}

/// @brief Test failing to write a file.
TEST_F(PIDFileTest, pidWriteFail) {
    PIDFile pid_file(absolutePath(TESTNAME2));

    EXPECT_THROW(pid_file.write(10), PIDFileError);
}

} // end of anonymous namespace
