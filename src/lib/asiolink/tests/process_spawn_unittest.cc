// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_signal.h>
#include <asiolink/interval_timer.h>
#include <asiolink/process_spawn.h>
#include <gtest/gtest.h>
#include <signal.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include <testutils/gtest_utils.h>

namespace {

using namespace isc;
using namespace isc::asiolink;
using namespace std;
namespace ph = std::placeholders;

/// @brief Test fixture for testing the use of ProcessSpawn with IO service
/// signals.
///
/// This fixture is exercises ProcessSpawn using IO service signaling.
class ProcessSpawnTest : public ::testing::Test {
public:
    /// @brief IOService instance to process IO.
    asiolink::IOServicePtr io_service_;

    /// @brief Single instance of IOService.
    static asiolink::IOServicePtr getIOService() {
        static asiolink::IOServicePtr io_service(new asiolink::IOService());
        return (io_service);
    }

    /// @brief Failsafe timer to ensure test(s) do not hang.
    isc::asiolink::IntervalTimer test_timer_;

    /// @brief Maximum time should be allowed to run.
    int test_time_ms_;

    /// @brief IOSignalSet object.
    IOSignalSetPtr io_signal_set_;

    /// @brief Vector to record the signal values received.
    std::vector<int> processed_signals_;

    /// @brief Constructor.
    ProcessSpawnTest() :
        io_service_(getIOService()), test_timer_(io_service_),
        test_time_ms_(0), io_signal_set_(), processed_signals_() {

        io_signal_set_.reset(new IOSignalSet(io_service_,
                                             std::bind(&ProcessSpawnTest::processSignal,
                                                       this, ph::_1)));
        io_signal_set_->add(SIGCHLD);
    }

    /// @brief Destructor.
    ~ProcessSpawnTest() {
        io_signal_set_->remove(SIGCHLD);
        io_signal_set_.reset();
        // Make sure the cancel handler for the IOSignalSet is called.
        io_service_->restart();
        try {
            io_service_->poll();
        } catch (...) {
        }
    }

    /// @brief Method used as the IOSignalSet handler.
    ///
    /// Records the value of the given signal and checks if the desired
    /// number of signals have been received.  If so, the IOService is
    /// stopped which will cause IOService::run() to exit, returning control
    /// to the test.
    ///
    /// @param signum signal number.
    void processSignal(int signum) {
        // Remember the signal we got.
        processed_signals_.push_back(signum);
    }

    /// @brief Sets the failsafe timer for the test to the given time.
    ///
    /// @param  test_time_ms maximum time in milliseconds the test should
    /// be allowed to run.
    void setTestTime(int test_time_ms) {
        // Fail safe shutdown
        test_time_ms_ = test_time_ms;
        test_timer_.setup(std::bind(&ProcessSpawnTest::testTimerHandler, this),
                          test_time_ms_, asiolink::IntervalTimer::ONE_SHOT);
    }

    /// @brief Failsafe timer expiration handler.
    void testTimerHandler() {
        io_service_->stop();
        FAIL() << "Test Time: " << test_time_ms_ << " expired";
    }
};

// This test verifies that the external application can be ran with
// arguments and that the exit code is gathered.
TEST_F(ProcessSpawnTest, spawnWithArgs) {
    vector<string> args;
    args.push_back("-e");
    args.push_back("64");

    ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);

    // Exit code 64 as requested.
    EXPECT_EQ(64, process.getExitStatus(pid));
}

// This test verifies that the external application can be ran with
// arguments and environment variables that the exit code is gathered.
TEST_F(ProcessSpawnTest, spawnWithArgsAndEnvVars) {
    vector<string> args;
    vector<string> vars;
    args.push_back("-v");
    args.push_back("TEST_VARIABLE_NAME");
    args.push_back("TEST_VARIABLE_VALUE");
    vars.push_back("TEST_VARIABLE_NAME=TEST_VARIABLE_VALUE");

    ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args, vars);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);

    // 56 means successful comparison of env vars.
    EXPECT_EQ(56, process.getExitStatus(pid));
}

// This test verifies that the single ProcessSpawn object can be used
// to start two processes and that their status codes can be gathered.
// It also checks that it is possible to clear the status of the
// process.
TEST_F(ProcessSpawnTest, spawnTwoProcesses) {
    vector<string> args;
    args.push_back("-p");

    ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args);
    pid_t pid1 = 0;
    ASSERT_NO_THROW(pid1 = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);

    pid_t pid2 = 0;
    ASSERT_NO_THROW(pid2 = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(2, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);
    ASSERT_EQ(SIGCHLD, processed_signals_[1]);

    EXPECT_NE(process.getExitStatus(pid1), process.getExitStatus(pid2));

    // Clear the status of the first process. An attempt to get the status
    // for the cleared process should result in exception. But, there should
    // be no exception for the second process.
    process.clearState(pid1);
    EXPECT_THROW(process.getExitStatus(pid1), InvalidOperation);
    EXPECT_NO_THROW(process.getExitStatus(pid2));

    process.clearState(pid2);
    EXPECT_THROW(process.getExitStatus(pid2), InvalidOperation);
}

// This test verifies that the external application can be ran without
// arguments and that the exit code is gathered.
TEST_F(ProcessSpawnTest, spawnNoArgs) {
    ProcessSpawn process(io_service_, TEST_SCRIPT_SH);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);

    // 32 means no args.
    EXPECT_EQ(32, process.getExitStatus(pid));

    ASSERT_NO_THROW(pid = process.spawn(true));

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(2, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);
    ASSERT_EQ(SIGCHLD, processed_signals_[1]);

    EXPECT_THROW(process.getExitStatus(pid), InvalidOperation);
}

// This test verifies that the EXIT_FAILURE code is returned when
// application can't be executed.
TEST_F(ProcessSpawnTest, invalidExecutable) {
    std::string expected = "File not found: foo";
    ASSERT_THROW_MSG(ProcessSpawn process(io_service_, "foo"),
                     ProcessSpawnError, expected);

    std::string name = INVALID_TEST_SCRIPT_SH;

    expected = "File not executable: ";
    expected += name;
    ASSERT_THROW_MSG(ProcessSpawn process(io_service_, name),
                     ProcessSpawnError, expected);
}

// This test verifies that the full command line for the process is
// returned.
TEST_F(ProcessSpawnTest, getCommandLine) {
    {
        // Case 1: arguments present.
        ProcessArgs args;
        args.push_back("-x");
        args.push_back("-y");
        args.push_back("foo");
        args.push_back("bar");
        ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args);
        std::string expected = TEST_SCRIPT_SH;
        expected += " -x -y foo bar";
        EXPECT_EQ(expected, process.getCommandLine());
    }

    {
        // Case 2: no arguments.
        ProcessSpawn process(io_service_, TEST_SCRIPT_SH);
        EXPECT_EQ(TEST_SCRIPT_SH, process.getCommandLine());
    }
}

// This test verifies that it is possible to check if the process is
// running.
TEST_F(ProcessSpawnTest, isRunning) {
    // Run the process which sleeps for 10 seconds, so as we have
    // enough time to check if it is running.
    vector<string> args;
    args.push_back("-s");
    args.push_back("10");

    ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    EXPECT_TRUE(process.isRunning(pid));

    // Kill the process.
    ASSERT_EQ(0, kill(pid, SIGKILL));

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);
}

// This test verifies inheritance of environment.
TEST_F(ProcessSpawnTest, inheritEnv) {
    // Run the process which sleeps for 10 seconds, so as we have
    // enough time to check if it is running.
    vector<string> args{"-v", "VAR", "value"};

    ProcessEnvVars vars{"VAR=value"};

    ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args, vars,
                         /* inherit_env = */ true);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);

    // 56 means successful comparison of env vars.
    EXPECT_EQ(56, process.getExitStatus(pid));
}

// This test verifies inheritance of environment when a variable is inherited
// from parent. It assumes PATH is set.
TEST_F(ProcessSpawnTest, inheritEnvWithParentVar) {
    // Run the process which sleeps for 10 seconds, so as we have
    // enough time to check if it is running.
    vector<string> args{"-v", "PATH", "value"};

    ProcessEnvVars vars{"VAR=value"};

    ProcessSpawn process(io_service_, TEST_SCRIPT_SH, args, vars,
                         /* inherit_env = */ true);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // Set test fail safe.
    setTestTime(1000);

    // SIGCHLD signal.
    io_service_->runOne();

    // waitForProcess handler.
    // ProcessSpawnTest::processSignal handler.
    io_service_->runOne();

    // Poll to be sure.
    io_service_->poll();

    ASSERT_EQ(1, processed_signals_.size());
    ASSERT_EQ(SIGCHLD, processed_signals_[0]);

    // 34 means failed comparison of env vars.
    EXPECT_EQ(34, process.getExitStatus(pid));
}

// This test verifies that the external application can be ran synchronously
// with arguments and that the exit code is gathered.
TEST_F(ProcessSpawnTest, spawnWithArgsSync) {
    vector<string> args;
    args.push_back("-e");
    args.push_back("64");

    ProcessSpawn process(TEST_SCRIPT_SH, args);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // Exit code 64 as requested.
    EXPECT_EQ(64, process.getExitStatus(pid));
}

// This test verifies that the external application can be ran synchronously
// with arguments and environment variables that the exit code is gathered.
TEST_F(ProcessSpawnTest, spawnWithArgsAndEnvVarsSync) {
    vector<string> args;
    vector<string> vars;
    args.push_back("-v");
    args.push_back("TEST_VARIABLE_NAME");
    args.push_back("TEST_VARIABLE_VALUE");
    vars.push_back("TEST_VARIABLE_NAME=TEST_VARIABLE_VALUE");

    ProcessSpawn process(TEST_SCRIPT_SH, args, vars);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // 56 means successful comparison of env vars.
    EXPECT_EQ(56, process.getExitStatus(pid));
}

// This test verifies that the single ProcessSpawn object can be used
// to start two processes synchronously and that their status codes can be
// gathered. It also checks that it is possible to clear the status of the
// process.
TEST_F(ProcessSpawnTest, spawnTwoProcessesSync) {
    vector<string> args;
    args.push_back("-p");

    ProcessSpawn process(TEST_SCRIPT_SH, args);
    pid_t pid1 = 0;
    ASSERT_NO_THROW(pid1 = process.spawn());

    pid_t pid2 = 0;
    ASSERT_NO_THROW(pid2 = process.spawn());

    EXPECT_NE(process.getExitStatus(pid1), process.getExitStatus(pid2));

    // Clear the status of the first process. An attempt to get the status
    // for the cleared process should result in exception. But, there should
    // be no exception for the second process.
    process.clearState(pid1);
    EXPECT_THROW(process.getExitStatus(pid1), InvalidOperation);
    EXPECT_NO_THROW(process.getExitStatus(pid2));

    process.clearState(pid2);
    EXPECT_THROW(process.getExitStatus(pid2), InvalidOperation);
}

// This test verifies that the external application can be ran synchronously
// without arguments and that the exit code is gathered.
TEST_F(ProcessSpawnTest, spawnNoArgsSync) {
    ProcessSpawn process(TEST_SCRIPT_SH);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // 32 means no args.
    EXPECT_EQ(32, process.getExitStatus(pid));

    ASSERT_NO_THROW(pid = process.spawn(true));

    EXPECT_THROW(process.getExitStatus(pid), InvalidOperation);
}

// This test verifies that the EXIT_FAILURE code is returned when
// application can't be executed synchronously.
TEST_F(ProcessSpawnTest, invalidExecutableSync) {
    std::string expected = "File not found: foo";
    ASSERT_THROW_MSG(ProcessSpawn process("foo"),
                     ProcessSpawnError, expected);

    std::string name = INVALID_TEST_SCRIPT_SH;

    expected = "File not executable: ";
    expected += name;
    ASSERT_THROW_MSG(ProcessSpawn process(name),
                     ProcessSpawnError, expected);
}

// This test verifies that the full command line for the synchronous process is
// returned.
TEST_F(ProcessSpawnTest, getCommandLineSync) {
    {
        // Case 1: arguments present.
        ProcessArgs args;
        args.push_back("-x");
        args.push_back("-y");
        args.push_back("foo");
        args.push_back("bar");
        ProcessSpawn process(TEST_SCRIPT_SH, args);
        std::string expected = TEST_SCRIPT_SH;
        expected += " -x -y foo bar";
        EXPECT_EQ(expected, process.getCommandLine());
    }

    {
        // Case 2: no arguments.
        ProcessSpawn process(TEST_SCRIPT_SH);
        EXPECT_EQ(TEST_SCRIPT_SH, process.getCommandLine());
    }
}

// This test verifies that the synchronous process reports as not running after
// it was spawned.
TEST_F(ProcessSpawnTest, isRunningSync) {
    ProcessSpawn process(TEST_SCRIPT_SH);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    EXPECT_FALSE(process.isRunning(pid));
}

// This test verifies inheritance of environment in a synchronous context.
TEST_F(ProcessSpawnTest, inheritEnvSync) {
    // Run the process which sleeps for 10 seconds, so as we have
    // enough time to check if it is running.
    vector<string> args{"-v", "VAR", "value"};

    ProcessEnvVars vars{"VAR=value"};

    ProcessSpawn process(TEST_SCRIPT_SH, args, vars,
                         /* inherit_env = */ true);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // 56 means successful comparison of env vars.
    EXPECT_EQ(56, process.getExitStatus(pid));
}

// This test verifies inheritance of environment when a variable is inherited
// from parent in a synchronous context. It assumes PATH is set.
TEST_F(ProcessSpawnTest, inheritEnvWithParentVarSync) {
    // Run the process which sleeps for 10 seconds, so as we have
    // enough time to check if it is running.
    vector<string> args{"-v", "PATH", "value"};

    ProcessEnvVars vars{"VAR=value"};

    ProcessSpawn process(TEST_SCRIPT_SH, args, vars,
                         /* inherit_env = */ true);
    pid_t pid = 0;
    ASSERT_NO_THROW(pid = process.spawn());

    // 34 means failed comparison of env vars.
    EXPECT_EQ(34, process.getExitStatus(pid));
}

} // end of anonymous namespace
