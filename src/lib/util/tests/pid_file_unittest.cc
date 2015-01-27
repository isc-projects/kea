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

#define TESTNAME "./pid_file.test"

/// @brief Test file writing and deleteion. Start by removing
/// any leftover file. Then write a known PID to the file and
/// attempt to read the file and verify the PID. Next write
/// a second and verify a second PID to verify that an existing
/// file is properly overwritten.

TEST(PIDFileTest, writeAndDelete) {
    PIDFile pid_file(TESTNAME);
    std::ifstream fs;
    int pid(0);

    // Remove any leftovers
    remove(TESTNAME);

    // Write a known process id
    pid_file.write(10);

    // Read the file and comapre the pid
    fs.open(TESTNAME, std::ifstream::in);
    fs >> pid;
    EXPECT_TRUE(fs.good());
    EXPECT_EQ(pid, 10);
    fs.close();

    // Write a second known process id
    pid_file.write(20);

    // And comapre the second pid
    fs.open(TESTNAME, std::ifstream::in);
    fs >> pid;
    EXPECT_TRUE(fs.good());
    EXPECT_EQ(pid, 20);
    fs.close();

    // Delete the file
    pid_file.deleteFile();

    // And verify that it's gone
    fs.open(TESTNAME, std::ifstream::in);
    EXPECT_FALSE(fs.good());
    fs.close();
}

/// @brief Test checking a PID. Write the PID of the current
/// process to the PID file then verify that check indicates
/// the process is running.
TEST(PIDFileTest, pidInUse) {
    PIDFile pid_file(TESTNAME);

    // Write the current PID
    pid_file.write();

    // Check if we think the process is running
    EXPECT_TRUE(pid_file.check());

    // Delete the file
    pid_file.deleteFile();
}

/// @brief Test checking a PID. Write a PID that isn't in use
/// to the PID file and verify that check indicates the process
/// isn't running. The PID may get used between when we select it
/// and write the file and when we check it. To minimize false
/// errors if the first call to check fails we try again with a
/// different range of values and only if both attempts fail do
/// we declare the test to have failed.
TEST(PIDFileTest, pidNotInUse) {
    PIDFile pid_file(TESTNAME);
    int pid;

    // get a pid betwen 10000 and 20000
    for (pid = (random() % 10000) + 10000;
        kill(pid, 0) == 0;
        ++pid)
        ;

    // write it
    pid_file.write(pid);

    // Check to see if we think the process is running
    if (pid_file.check() == false) {
        // Delete the file
        pid_file.deleteFile();
        return;
    }

    // get a pid betwen 40000 and 50000
    for (pid = (random() % 10000) + 40000;
        kill(pid, 0) == 0;
        ++pid)
        ;

    // write it
    pid_file.write(pid);

    // Check to see if we think the process is running
    EXPECT_FALSE(pid_file.check());

    // Delete the file
    pid_file.deleteFile();
}

/// @brief Test checking a PID.  Write garbage to the PID file
/// and verify that check throws an error. In this situation
/// the caller should probably log an error and may decide to
/// continue or not depending on the requirements.
TEST(PIDFileTest, pidGarbage) {
    PIDFile pid_file(TESTNAME);
    std::ofstream fs;

    // Remove any leftovers
    remove(TESTNAME);

    // Open the file and write garbage to it
    fs.open(TESTNAME, std::ofstream::out);
    fs << "text" << std::endl;
    fs.close();

    // Run the check, we expect to find a process "running"
    EXPECT_TRUE(pid_file.check());

    // And clean up the file
    pid_file.deleteFile();

}

} // end of anonymous namespace
