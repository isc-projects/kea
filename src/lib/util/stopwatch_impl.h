// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STOPWATCH_IMPL_H
#define STOPWATCH_IMPL_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace util {

/// @brief @c Stopwatch class implementation.
///
/// The @c Stopwatch class uses the plimpl idiom to make it easier to unit
/// test behavior of the @c Stopwatch class without a need to rely on the system
/// clock. The @c StopwatchImpl API allows for overriding the @c getCurrentTime
/// method to return the arbitrary time value as current time to various
/// methods. By setting the current time to arbitrary values the test can expect
/// arbitrary values being returned by the class methods.
///
/// Also, by using the pimpl idiom the @c Stopwatch class hides its implementation
/// details and leaves the header with only the pointer to the @c StopwatchImpl
/// class.
class StopwatchImpl {
public:

    /// @brief Constructor.
    ///
    /// Initializes the internally used timestamps. It also sets the state of
    /// the stopwatch to "stopped".
    StopwatchImpl();

    /// @brief Virtual destructor.
    ///
    /// This destructor is virtual because the @c StopwatchImpl::getCurrentTime
    /// is virtual.
    virtual ~StopwatchImpl();

    /// @brief Starts the stopwatch.
    ///
    /// Sets the stopwatch to the "started" state. It also records the time when
    /// the stopwatch is started. This method is no-op if the stopwatch is
    /// already in the "started" state.
    ///
    /// Also see the @c Stopwatch::start for details.
    void start();

    /// @brief Stop the stopwatch.
    ///
    /// Sets the stopwatch to the "stopped" state. The stop time is recorded and
    /// the cumulative time is updated to include the duration between the most
    /// recent start and stop. This method is no-op if the stopwatch is already
    /// in the "stopped" state.
    ///
    /// Also see the @c Stopwatch::stop for details.
    void stop();

    /// @brief Reset the stopwatch.
    ///
    /// Also see the @c Stopwatch::reset for details.
    void reset();

    /// @brief Retrieves the measured duration.
    ///
    /// Also see the @c Stopwatch::getLastDuration for details.
    boost::posix_time::time_duration getLastDuration() const;

    /// @brief Retrieves the total measured duration.
    ///
    /// Also see the @c Stopwatch::getTotalDuration for details.
    boost::posix_time::time_duration getTotalDuration() const;

    /// @brief Returns the duration in the textual format which can be
    /// directly used in log messages.
    ///
    /// @param duration Duration to be converted to the textual format.
    ///
    /// @return Converted value which can be used to log duration.
    static std::string
    logFormat(const boost::posix_time::time_duration& duration);

protected:

    /// @brief Returns the current time.
    ///
    /// This method is used internally by the @c StopwatchImpl class and
    /// its derivations. This class simply returns the value of
    /// @c boost::posix_time::microsec_clock::univeral_time(), which is
    /// a current timestamp. The derivations may replace it with the
    /// custom implementations. The typical use case is for the unit tests
    /// to customize the behavior of this function to return well known
    /// (deterministic) values. As a result, it is possible to influence
    /// the "measured" values returned by accessors of this class, which
    /// can be compared against some exact values.
    virtual boost::posix_time::ptime getCurrentTime() const;

private:

    /// @brief Holds the state of the stopwatch.
    bool started_;

    /// @brief Holds the timestamp when the stopwatch has been last started.
    boost::posix_time::ptime last_start_;

    /// @brief Holds the timestamp when the stopwatch has been last stopped.
    boost::posix_time::ptime last_stop_;

    /// @brief Holds the total measured time since the stopwatch has been
    /// first started after creation or reset.
    boost::posix_time::time_duration cumulative_time_;

};

}
}

#endif // STOPWATCH_H

