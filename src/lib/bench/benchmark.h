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

#ifndef __BENCHMARK_H
#define __BENCHMARK_H 1

#include <sys/time.h>

#include <iostream>
#include <ios>

namespace isc {
namespace bench {

template <typename T>
class BenchMark {
public:
    BenchMark(const int iterations, T& target) :
        iterations_(iterations), sub_iterations_(0), target_(target) {}
    void setUp() {}
    void tearDown() {}
    void run() {
        setUp();

        struct timeval beg, end;
        gettimeofday(&beg, NULL);
        for (int i = 0; i < iterations_; ++i) {
            sub_iterations_ += target_.run();
        }
        gettimeofday(&end, NULL);
        tv_diff_ = tv_subtract(end, beg);

        printResult();
        tearDown();
    }
    void printResult() const {
        std::cout.precision(6);
        std::cout << "Performed " << getIteration() << " iterations in "
                  << std::fixed << getDuration() << "s";
        std::cout.precision(2);
        std::cout << " (" << std::fixed << getIterationPerSecond() << "ips)"
                  << std::endl;
    }
    unsigned int getIteration() const { return (sub_iterations_); }
    double getDuration() const {
        return (tv_diff_.tv_sec +
                static_cast<double>(tv_diff_.tv_usec) / ONE_MILLION);
    }
    double getAverageTime() const {
        return ((tv_diff_.tv_sec +
                 static_cast<double>(tv_diff_.tv_usec) / ONE_MILLION ) /
                sub_iterations_);
    }
    double getIterationPerSecond() const {
        return (sub_iterations_ /
                (tv_diff_.tv_sec +
                 static_cast<double>(tv_diff_.tv_usec) / ONE_MILLION));
    }
private:
    // return t1 - t2
    struct timeval tv_subtract(const struct timeval& t1,
                               const struct timeval& t2)
    {
        struct timeval result;

        result.tv_sec = t1.tv_sec - t2.tv_sec;
        if (t1.tv_usec >= t2.tv_usec) {
            result.tv_usec = t1.tv_usec- t2.tv_usec;
        } else {
            result.tv_usec = ONE_MILLION + t1.tv_usec - t2.tv_usec;
            --result.tv_sec;
        }

        return (result);
    }
private:
    static const int ONE_MILLION = 1000000;
    const unsigned int iterations_;
    unsigned int sub_iterations_;
    T& target_;
    struct timeval tv_diff_;
};

}
}
#endif  // __BENCHMARK_H

// Local Variables: 
// mode: c++
// End: 
