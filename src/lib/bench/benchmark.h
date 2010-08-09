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

/// \brief Templated micro benchmark framework.
///
/// "Premature optimization is the root of all evil."
/// But programmers are often tempted to focus on performance optimization
/// too early.
/// Likewise, it's not uncommon for an engineer to introduce a minor
/// optimization with a lot of complicated code logic that actually improves
/// performance only marginally.
/// Making benchmark easier will help avoid such common pitfalls.
/// Of course, it also helps when we really need to introduce optimization
/// to identify where is the bottleneck and see how a particular optimization
/// improves the performance.
///
/// The BenchMark class template provides a simple framework for so-called
/// "stopwatch" micro benchmarking.
/// It just encapsulates the common operations for this type of benchmark:
/// repeat a specified operation for a given number of times,
/// record the start and end times of the operations,
/// and provide major accumulated results such as the number of iterations
/// per second.
/// The main goal of this class is to help developers write benchmark test
/// cases with fewer strokes of typing.
///
/// The constructors of a \c BenchMark class is to take the number of
/// iterations (which is referred to as \c niter below)
/// and an object (or reference to it) of the type of the template
/// parameter, \c T.  Class \c T implements the benchmark target code via
/// its \c run() method, whose signature is as follows:
/// \code  unsigned int T::run(); \endcode
///
/// A BenchMark class object, via its own \c run() method, calls \c T::run()
/// for \c niter times.
/// In the simplest form \c T::run() would perform a single operation to
/// be benchmarked and returns 1.
/// In some cases, however, the operation is very lightweight (e.g. performing
/// a binary search on a moderate length of integer vector), and it may be
/// desirable to have an internal iterations within \c T::run() to avoid
/// the overhead of function calls to \c T::run().
/// In that case, \c T::run() would return the number of internal iterations
/// instead of 1.
///
/// The \c BenchMark::run() method records some statistics %data on the
/// benchmarking, including the start and end times and the total number of
/// iterations (which is the sum of the return value of \c T::run(), and,
/// is equal to \c niter in the simplest case where \c T::run() always
/// returns 1).
/// This %data can be retried via other methods of \c BenchMark, but in
/// the primarily intended use case the \c BenchMark object would calls its
/// \c run() method at the end of its construction, and prints summarized
/// statistics to the standard output.
/// This way, the developer can only write a single line of code to perform
/// everything other than the benchmark target code (see the example below).
///
/// \b Example
///
/// Suppose that we want to measure performance of the search (find)
/// operation on STL set objects.  We'd first define the implementation
/// class (to be the template parameter of the \c BenchMark class) as follows:
///
/// \code class SetSearchBenchMark {
/// public:
///    SetSearchBenchMark(const set<int>& data, const vector<int>& keys) :
///        data_(data), keys_(keys)
///    {}
///    unsigned int run() {
///        vector<int>::const_iterator iter;
///        vector<int>::const_iterator end_key = keys_.end();
///        for (iter = keys_.begin(); iter != end_key; ++iter) {
///            data_.find(*iter);
///        }        
///        return (keys_.size());
///    }
///    const set<int>& data_;
///    const vector<int>& keys_;
/// }; \endcode
///
/// In its constructor the \c SetSearchBenchMark class takes a set of
/// integers (\c %data) and a vector of integers (\c keys).  \c %data is
/// the STL set to be searched, and \c keys stores the search keys.
/// The constructor keeps local references to these objects.
///
/// The \c SetSearchBenchMark::run() method, which is called via
/// \c BenchMark::run(), iterates over the key vector, and performs the
/// \c find() method of the set class for each key.
/// (This is only for performance measurement, so the result is ignored).
/// Note that this \c run() method has its own internal iterations.
/// This is because each invocation of \c find() would be pretty lightweight,
/// and the function call overhead may be relatively heavier.
/// Due to the internal iterations, this method returns the number of
/// \c find() calls, which is equal to the size of the key vector.
///
/// Next, we should prepare test %data.  In this simple example, let's assume
/// we use a fixed size: a set of 10,000 integers (from 0 to 9999), and use
/// the same number of search keys randomly chosen from that range:
/// \code
///    set<int> data_set;
///    vector<int> keys;
///    for (int i = 0; i < 10000; ++i) {
///        data_set.insert(i);
///        keys.push_back(rand() % 10000);
///    } \endcode
///
/// Then construct a \c BenchMark<SetSearchBenchMark> object with the
/// test %data:
/// \code
///    BenchMark<SetSearchBenchMark>(100, SetSearchBenchMark(data_set, keys));
/// \endcode
/// Here we specify 100 for the number of iterations, which would cause
/// 1 million search attempts in total.
///
/// That's it.  If we put these in a C++ source file with usual necessary
/// stuff (such as \c %main()), compile it, and run the executable, then
/// we'll see something like this:
///
/// \code Performed 1000000 iterations in 0.180172s (5550251.98ips) \endcode
///
/// It should be obvious what this means (ips stands for "iterations
///  per second").
///
/// A complete example program of this measurement scenario (with some
/// additional test cases and configurable parameters) can be found in
/// example/search_bench.cc.
///
/// \b Customization
///
/// The above simple usage should be sufficient in many benchmark cases,
/// but the \c BenchMark class provides some customization points by
/// specializing some of its (templated) public methods.
/// For example, assume you want to customize the output of benchmark result.
/// It can be done by specializing \c BenchMark::printResult():
/// \code namespace isc {
/// namespace bench {
/// template<>
/// void
/// BenchMark<SetSearchBenchMark>::printResult() const {
///     cout << "Searched for " << target_.keys_.size() << " keys "
///         << getIteration() << " times in " << getDuration() << "s" << endl;
/// }
/// }
/// } \endcode
///
/// Then the Result would be something like this:
///
/// \code Searched for 10000 keys 1000000 times in 0.21s \endcode
///
/// Note that the specialization must be defined in the same namespace as
/// that of the \c BenchMark class, that is, \c isc::bench.
/// It should also be noted that the corresponding \c SetSearchBenchMark
/// object can be accessed (through its public interfaces) via the \c target_
/// member variable of \c BenchMark.
///
/// <b>Future Plans and Compatibility Notes</b>
///
/// Currently, benchmark developers need to write supplemental code that is
/// not directly related to benchmarks (such as \c %main()) by hand.
/// It would be better if we could minimize such development overhead.
/// In future versions we may provide a common \c %main() function and
/// option parsers, thereby allowing the developer to only write the benchmark
/// classes and invoke them, just like what various unit test frameworks do.
///
/// If and when we implement it, some existing benchmark cases may need to be
/// adjusted.
template <typename T>
class BenchMark {
    ///
    /// \name Constructors
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    /// We use the default destructor.
    //@{
private:
    BenchMark(const BenchMark& source);
    BenchMark& operator=(const BenchMark& source);
public:
    /// \bench Constructor for immediate run.
    ///
    /// This is the constructor that is expected to be used normally.
    /// It runs the benchmark within the constructor and prints the result,
    /// thereby making it possible to do everything with a single line of
    /// code (see the above example).
    ///
    /// \param iterations The number of iterations.  The \c run() method will
    /// be called this number of times.
    /// \param target The templated class object that
    /// implements the code to be benchmarked.
    BenchMark(const int iterations, T target) :
        iterations_(iterations), sub_iterations_(0), target_(target)
    {
        initialize(true);
    }

    /// \bench Constructor for finer-grained control.
    ///
    /// This constructor takes the third parameter, \c immediate, to control
    /// whether to run the benchmark within the constructor.
    /// It also takes a reference to the templated class object rather than
    /// an object copy, so if the copy overhead isn't acceptable this
    /// constructor must be used.
    ///
    /// \param iterations The number of iterations.  The \c run() method will
    /// be called this number of times.
    /// \param target A reference to the templated class object that
    /// implements the code to be benchmarked.
    /// \param immediate If \c true the benchmark will be performed within
    /// the constructor; otherwise it only does initialization.
    BenchMark(const int iterations, T& target, const bool immediate) :
        iterations_(iterations), sub_iterations_(0), target_(target)
    {
        initialize(immediate);
    }
    //@}

    /// \brief Hook to be called before starting benchmark.
    ///
    /// This method will be called from \c run() before starting the benchmark.
    /// By default it's empty, but can be customized via template
    /// specialization.
    void setUp() {}

    /// \brief Hook to be called after benchmark.
    ///
    /// This method will be called from \c run() when the benchmark completes.
    /// By default it's empty, but can be customized via template
    /// specialization.
    void tearDown() {}

    /// \brief Perform benchmark.
    ///
    /// This method first calls \c setUp().
    /// It then records the current time, calls \c T::run() for the number
    /// of times specified on construction, and records the time on completion.
    /// Finally, it calls \c tearDown().
    void run() {
        setUp();

        struct timeval beg, end;
        gettimeofday(&beg, NULL);
        for (int i = 0; i < iterations_; ++i) {
            sub_iterations_ += target_.run();
        }
        gettimeofday(&end, NULL);
        tv_diff_ = tv_subtract(end, beg);

        tearDown();
    }

    /// \brief Print the benchmark result.
    ///
    /// This method prints the benchmark result in a common style to the
    /// standard out.  The result contains the number of total iterations,
    /// the duration of the test, and the number of iterations per second
    /// calculated from the previous two parameters.
    ///
    /// A call to this method is only meaningful after the completion of
    /// \c run().  The behavior is undefined in other cases.
    void printResult() const {
        std::cout.precision(6);
        std::cout << "Performed " << getIteration() << " iterations in "
                  << std::fixed << getDuration() << "s";
        std::cout.precision(2);
        std::cout << " (" << std::fixed << getIterationPerSecond() << "ips)"
                  << std::endl;
    }

    /// \brief Return the number of iterations.
    ///
    /// It returns the total iterations of benchmark, which is the sum
    /// of the return value of \c T::run() over all calls to it
    /// (note that it may not equal to the number of calls to \c T::run(),
    /// which was specified on construction of this class).
    ///
    /// A call to this method is only meaningful after the completion of
    /// \c run().  The behavior is undefined in other cases.
    unsigned int getIteration() const { return (sub_iterations_); }

    /// \brief Return the duration of benchmark in seconds.
    ///
    /// The highest possible precision of this value is microseconds.
    ///
    /// A call to this method is only meaningful after the completion of
    /// \c run().  The behavior is undefined in other cases.
    double getDuration() const {
        return (tv_diff_.tv_sec +
                static_cast<double>(tv_diff_.tv_usec) / ONE_MILLION);
    }

    /// \brief Return the average duration per iteration in seconds.
    ///
    /// The highest possible precision of this value is microseconds.
    /// The iteration is the sum of the return value of \c T::run() over
    /// all calls to it (note that it may not equal to the number of calls
    /// to \c T::run()).
    ///
    /// If it cannot calculate the average, it returns \c TIME_FAILURE.
    ///
    /// A call to this method is only meaningful after the completion of
    /// \c run().  The behavior is undefined in other cases.
    double getAverageTime() const {
        if (sub_iterations_ == 0) {
            return (TIME_FAILURE);
        }
        return ((tv_diff_.tv_sec +
                 static_cast<double>(tv_diff_.tv_usec) / ONE_MILLION ) /
                sub_iterations_);
    }

    /// \brief Return the number of possible iterations per second based on
    /// the benchmark result.
    ///
    /// If it cannot calculate that number (e.g. because the duration is
    /// too small) it returns \c ITERATION_FAILURE.
    /// A call to this method is only meaningful after the completion of
    /// \c run().  The behavior is undefined in other cases.
    double getIterationPerSecond() const {
        const double duration_usec = tv_diff_.tv_sec +
            static_cast<double>(tv_diff_.tv_usec) / ONE_MILLION;
        if (duration_usec == 0) {
            return (ITERATION_FAILURE);
        }
        return (sub_iterations_ / duration_usec);
    }
public:
    /// \brief A constant that indicates a failure in \c getAverageTime().
    ///
    /// This constant be used as double but is defined as int so that it can
    /// be initialized within the class definition.  Type conversion will be
    /// performed implicitly.
    static const int TIME_FAILURE = -1;

    /// \brief A constant that indicates a failure in
    /// \c getIterationPerSecond().
    ///
    /// This constant be used as double but is defined as int so that it can
    /// be initialized within the class definition.  Type conversion will be
    /// performed implicitly.
    static const int ITERATION_FAILURE = -1;
private:
    void initialize(const bool immediate) {
        if (immediate) {
            run();
            printResult();
        }
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
