// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <boost/noncopyable.hpp>
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
class Stopwatch : boost::noncopyable {
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
    //// This method is no-op if the stopwatch is already in the "started"
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
    long getLastMilliseconds() const;

    /// @brief Retrieves the total measured duration in milliseconds.
    long getTotalMilliseconds() const;

    /// @brief Retrieves the last measured duration in microseconds.
    long getLastMicroseconds() const;

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

