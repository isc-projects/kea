// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <unistd.h>             // for usleep

#include <bench/benchmark.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::bench;

namespace {
// Our "benchmark" simply sleeps for a short period, and reports a faked
// number of iterations.
class TestBenchMark {
public:
    TestBenchMark(const int sub_iterations, const int sleep_time) :
        sub_iterations_(sub_iterations), sleep_time_(sleep_time),
        setup_completed_(false), teardown_completed_(false)
    {}
    unsigned int run() {
        usleep(sleep_time_);
        return (sub_iterations_);
    }
    const int sub_iterations_;
    const int sleep_time_;
    bool setup_completed_;
    bool teardown_completed_;
};
}

namespace isc {
namespace bench {
template <>
void
BenchMark<TestBenchMark>::setUp() {
    target_.setup_completed_ = true;
};

template <>
void
BenchMark<TestBenchMark>::tearDown() {
    target_.teardown_completed_ = true;
};

// XXX: some compilers cannot find class static constants used in
// EXPECT_xxx macros, for which we need an explicit definition.
template <typename T>
const int BenchMark<T>::TIME_FAILURE;
}
}

namespace {
TEST(BenchMarkTest, run) {
    // use some uncommon iterations for testing purpose:
    const int sub_iterations = 23;
    const int sleep_time = 50000; // will sleep for 50ms
    // we cannot expect particular accuracy on the measured duration, so
    // we'll include some conservative margin (25%) and perform range
    // comparison below.
    const int duration_margin = 12500; // 12.5ms
    const int ONE_MILLION = 1000000;

    // Prerequisite check: since the tests in this case may depend on subtle
    // timing, it may result in false positives.  There are reportedly systems
    // where usleep() doesn't work as this test expects.  So we check the
    // conditions before the tests, and if it fails skip the tests at the
    // risk of overlooking possible bugs.
    struct timeval check_begin, check_end;
    gettimeofday(&check_begin, NULL);
    usleep(sleep_time);
    gettimeofday(&check_end, NULL);
    check_end.tv_sec -= check_begin.tv_sec;
    if (check_end.tv_usec >= check_begin.tv_usec) {
        check_end.tv_usec = check_end.tv_usec - check_begin.tv_usec;
    } else {
        check_end.tv_usec = ONE_MILLION + check_begin.tv_usec -
            check_end.tv_usec;
        --check_end.tv_sec;
    }
    if (check_end.tv_sec != 0 ||
        sleep_time - duration_margin > check_end.tv_usec ||
        sleep_time + duration_margin < check_end.tv_usec) {
        cerr << "Prerequisite check failed.  skipping test" << endl;
        return;
    }

    TestBenchMark test_bench(sub_iterations, sleep_time);
    BenchMark<TestBenchMark> bench(1, test_bench, false);
    // Check pre-test conditions.
    EXPECT_FALSE(test_bench.setup_completed_);
    EXPECT_FALSE(test_bench.teardown_completed_);

    bench.run();

    // Check if specialized setup and teardown were performed.
    EXPECT_TRUE(test_bench.setup_completed_);
    EXPECT_TRUE(test_bench.teardown_completed_);

    // Check accuracy of the measured statistics.
    EXPECT_EQ(sub_iterations, bench.getIteration());
    EXPECT_LT(sleep_time - duration_margin, bench.getDuration() * ONE_MILLION);
    EXPECT_GT(sleep_time + duration_margin, bench.getDuration() * ONE_MILLION);
    EXPECT_LT((sleep_time - duration_margin) /
              static_cast<double>(sub_iterations),
              bench.getAverageTime() * ONE_MILLION);
    EXPECT_GT((sleep_time + duration_margin) /
              static_cast<double>(sub_iterations),
              bench.getAverageTime() * ONE_MILLION);
    EXPECT_LT(static_cast<double>(sub_iterations) /
              (sleep_time + duration_margin),
              bench.getIterationPerSecond() / ONE_MILLION);
    EXPECT_GT(static_cast<double>(sub_iterations) /
              (sleep_time - duration_margin),
              bench.getIterationPerSecond() / ONE_MILLION);
}

TEST(BenchMarkTest, runWithNoIteration) {
    // we'll lie on the number of iteration (0).  it will result in
    // meaningless result, but at least it shouldn't crash.
    TestBenchMark test_bench(0, 0);
    BenchMark<TestBenchMark> bench(1, test_bench, false);
    bench.run();
    EXPECT_EQ(0, bench.getIteration());
    // Since the reported iteration is 0, naive calculation of the average
    // time would cause a division by 0 failure.
    EXPECT_EQ(bench.TIME_FAILURE, bench.getAverageTime());
}
}
