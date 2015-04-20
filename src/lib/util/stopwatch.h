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

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace util {

/// @brief Forward declaration to the @c Stopwatch implementation.
class StopwatchImpl;

/// @brief Utility class to measure code execution times.
///
/// The API of this class is based on the use cases of a stopwatch. It is
/// used to measure time spent executing portions of the code. The typical
/// use case for the @c Stopwatch is to measure the time spent invoking
/// callouts in hooks library. This provides means for diagnosing the
/// server's performance degradations when hooks libraries are in use.
///
/// This class exposes functions like @c start, @c stop and @c reset which
/// behave in the same way as a stopwatch used to measure time for sport
/// activities.
///
/// It is possible to measure the cumulative execution time by invoking
/// @c start and @c stop consecutively. The total measured time will be
/// a sum of durations between the invocations of respective starts and
/// stops.
class Stopwatch {
public:

    /// @brief Constructor.
    ///
    /// @param autostart Indicates if the stopwatch should be initialized to
    /// the "started" state. In this state the stopwatch is measuring the time
    /// since it has been started (object has been constructed in this case.
    /// If the parameter is set to false (default value), the
    /// @c Stopwatch::start must be called to start time measurement.
    Stopwatch(const bool autostart = true);

    /// @brief Destructor.
    ///
    /// Destroys the implementation instance.
    ~Stopwatch();

    /// @brief Starts the stopwatch.
    ///
    /// Sets the stopwatch to the "started" state. In this state the stopwatch
    /// is measuring the duration since @c Stopwatch::start has been invoked.
    ///
    //// This method is no-op if the stopwatch is already in the "stopped"
    /// state.
    void start();

    /// @brief Stops the stopwatch.
    ///
    /// Sets the stopwatch to the "stopped" state. The stopwatch stops the time
    /// measurement and records the duration between the last stopwatch start
    /// and the stop invocation. It also updates the total measured duration,
    /// i.e. the sum of durations between all start/stop invocations. Both
    /// values can be retrieved using @c Stopwatch::getLastDuration and
    /// @c Stopwatch::getTotalDuration respectively, or their variants.
    ///
    /// This method is no-op if the stopwatch is already in the "stopped" state.
    void stop();

    /// @brief Resets the stopwatch.
    ///
    /// It resets the stopwatch to the initial state. In this state, the last
    /// measured duration and the total duration is set to 0. The stopwatch
    /// is set to the "stopped" state.
    void reset();

    /// @brief Retrieves last measured duration.
    ///
    /// If the stopwatch is in the "stopped" state this method retrieves the
    /// duration between the last start and stop. If the stopwatch is in the
    /// "started" state, the retrieved duration is the duration between the
    /// last start of the stopwatch and the current time.
    boost::posix_time::time_duration getLastDuration() const;

    /// @brief Retrieves total measured duration.
    ///
    /// If the stopwatch is in the "stopped" state this method retrieves the
    /// total duration between all starts and stops invoked  during the
    /// lifetime of the object or since the last reset. If the stopwatch is
    /// in the "started" state, the returned is the sum of all durations
    /// between respective starts and stops, and the duration since the
    /// stopwatch has been last started and the current time.
    boost::posix_time::time_duration getTotalDuration() const;

    /// @brief Retrieves the last measured duration in milliseconds.
    long getMilliseconds() const;

    /// @brief Retrieves the total measured duration in milliseconds.
    long getTotalMilliseconds() const;

    /// @brief Retrieves the last measured duration in microseconds.
    long getMicroseconds() const;

    /// @brief Retrieves the total measured duration in microseconds.
    long getTotalMicroseconds() const;

    /// @brief Returns the last measured duration in the format directly
    /// usable in log messages.
    std::string logFormatLastDuration() const;

    /// @brief Returns the total measured duration in the format directly
    /// usable in the log messages.
    std::string logFormatTotalDuration() const;

private:

    /// @brief Pointer to the @c StopwatchImpl.
    StopwatchImpl* impl_;

};

}
}

#endif // STOPWATCH_H

