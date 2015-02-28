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

#include <util/process_spawn.h>
#include <gtest/gtest.h>
#include <signal.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

namespace {

using namespace isc;
using namespace isc::util;

/// @brief Returns a location of the test script.
///
/// The test script is no-op and it returns the exit code equal to
/// the argument passed to it.
///
/// @return Absolute location of the test script.
std::string getApp() {
    std::ostringstream s;
    s << TEST_DATA_TOPBUILDDIR << "/src/lib/util/tests/process_spawn_app.sh";
    return (s.str());
}

/// @brief Waits for the specified process to finish.
///
/// @param process An object which started the process.
/// @param pid ID of the spawned process.
/// @param timeout Timeout in seconds.
///
/// @return true if the process ended, false otherwise
bool waitForProcess(const ProcessSpawn& process, const pid_t pid,
                    const uint8_t timeout) {
    uint32_t iterations = 0;
    const uint32_t iterations_max = timeout * 1000;
    while (process.isRunning(pid) && (iterations < iterations_max)) {
        usleep(1000);
        ++iterations;
    }
    return (iterations < iterations_max);
}

// This test verifies that the external application can be ran with
// arguments and that the exit code is gathered.
TEST(ProcessSpawn, spawnWithArgs) {
    std::vector<std::string> args;
    args.push_back("-e");
    args.push_back("64");
    ProcessSpawn process(getApp(), args);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    ASSERT_TRUE(waitForProcess(process, pid, 2));

    EXPECT_EQ(64, process.getExitStatus(pid));
}

// This test verifies that the single ProcessSpawn object can be used
// to start two processes and that their status codes can be gathered.
// It also checks that it is possible to clear the status of the
// process.
TEST(ProcessSpawn, spawnTwoProcesses) {
    std::vector<std::string> args;
    args.push_back("-p");
    ProcessSpawn process(getApp(), args);
    pid_t pid1 = 0;
    ASSERT_NO_THROW(pid1 = process.spawn());
    ASSERT_TRUE(waitForProcess(process, pid1, 2));

    pid_t pid2 = 0;
    ASSERT_NO_THROW(pid2 = process.spawn());
    ASSERT_TRUE(waitForProcess(process, pid2, 2));

    EXPECT_NE(process.getExitStatus(pid1), process.getExitStatus(pid2));

    // Clear the status of the first process. An attempt to get the status
    // for the cleared process should result in exception. But, there should
    // be no exception for the second process.
    process.clearStatus(pid1);
    EXPECT_THROW(process.getExitStatus(pid1), InvalidOperation);
    EXPECT_NO_THROW(process.getExitStatus(pid2));

    process.clearStatus(pid2);
    EXPECT_THROW(process.getExitStatus(pid2), InvalidOperation);
}

// This test verifies that the external application can be ran without
// arguments and that the exit code is gathered.
TEST(ProcessSpawn, spawnNoArgs) {
    std::vector<std::string> args;
    ProcessSpawn process(getApp());
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    ASSERT_TRUE(waitForProcess(process, pid, 2));

    EXPECT_EQ(32, process.getExitStatus(pid));
}


// This test verifies that the EXIT_FAILURE code is returned when
// application can't be executed.
TEST(ProcessSpawn, invalidExecutable) {
    ProcessSpawn process("foo");
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    ASSERT_TRUE(waitForProcess(process, pid, 2));

    EXPECT_EQ(EXIT_FAILURE, process.getExitStatus(pid));
}

// This test verifies that the full command line for the process is
// returned.
TEST(ProcessSpawn, getCommandLine) {
    // Note that cases below are enclosed in separate scopes to make
    // sure that the ProcessSpawn object is destroyed before a new
    // object is created. Current implementation doesn't allow for
    // having two ProcessSpawn objects simultaneously as they will
    // both try to allocate a signal handler for SIGCHLD.
    {
        // Case 1: arguments present.
        ProcessArgs args;
        args.push_back("-x");
        args.push_back("-y");
        args.push_back("foo");
        args.push_back("bar");
        ProcessSpawn process("myapp", args);
        EXPECT_EQ("myapp -x -y foo bar", process.getCommandLine());
    }

    {
        // Case 2: no arguments.
        ProcessSpawn process("myapp");
        EXPECT_EQ("myapp", process.getCommandLine());
    }
}

// This test verifies that it is possible to check if the process is
// running.
TEST(ProcessSpawn, isRunning) {
    // Run the process which sleeps for 10 seconds, so as we have
    // enough time to check if it is running.
    std::vector<std::string> args;
    args.push_back("-s");
    args.push_back("10");
    ProcessSpawn process(getApp(), args);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());
    EXPECT_TRUE(process.isRunning(pid));

    // Kill the process.
    ASSERT_EQ(0, kill(pid, SIGKILL));
    // And make sure if died.
    ASSERT_TRUE(waitForProcess(process, pid, 2));
}

} // end of anonymous namespace
