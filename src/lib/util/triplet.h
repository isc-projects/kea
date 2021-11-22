// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TRIPLET_H
#define TRIPLET_H

#include <exceptions/exceptions.h>
#include <util/optional.h>

namespace isc {
namespace util {

/// @brief This template specifies a parameter value
///
/// This template class is used to store configuration parameters, like lifetime
/// or T1. It defines 3 parameters: min, default, and max value. If the
/// particular configuration parameter is not mandatory, it is possible to
/// mark the parameter described by a @c Triplet "unspecified". For example, the
/// T1 and T2 values in DHCPv4 server are optional and may be not specified
/// in the configuration. The @c Triplets describing these parameters will be
/// marked "unspecified". If the server finds that the particular parameter
/// is unspecified it will not include it (e.g. option 58 or 59) in the message
/// to a client.
///
/// There are 3 constructors:
/// - without parameters - marks the parameter "unspecified"
/// - simple (just one value that sets all parameters)
/// - extended (that sets default value and two thresholds)
///
/// It will be used with integer types. It provides necessary operators, so
/// it can be assigned to a plain integer or integer assigned to a Triplet.
/// See TripletTest.operator test for details on an easy Triplet usage.
template <class T>
class Triplet : public util::Optional<T> {
public:

    using util::Optional<T>::get;

    /// @brief Base type to Triplet conversion.
    ///
    /// Typically: uint32_t to Triplet assignment. It is very convenient
    /// to be able to simply write Triplet<uint32_t> x = 7;
    ///
    /// @param other A number to be assigned as min, max and default value.
    Triplet<T>& operator=(T other) {
        min_ = other;
        util::Optional<T>::default_ = other;
        max_ = other;
        // The value is now specified because we just assigned one.
        util::Optional<T>::unspecified_ = false;
        return (*this);
    }

    /// @brief Constructor without parameters.
    ///
    /// Marks value in @c Triplet unspecified.
    Triplet()
        : util::Optional<T>(), min_(0), max_(0) {
    }

    /// @brief Sets a fixed value.
    ///
    /// This constructor assigns a fixed (i.e. no range, just a single value)
    /// value.
    ///
    /// @param value A number to be assigned as min, max and default value.
    Triplet(T value)
        : util::Optional<T>(value), min_(value), max_(value) {
    }

    /// @brief Sets the default value and thresholds
    ///
    /// @throw BadValue if min <= def <= max rule is violated
    Triplet(T min, T def, T max)
        : util::Optional<T>(def), min_(min), max_(max) {
        if ( (min_ > def) || (def > max_) ) {
            isc_throw(BadValue, "Invalid triplet values.");
        }
    }

    /// @brief Returns a minimum allowed value
    T getMin() const { return (min_);}

    /// @brief Returns value with a hint
    ///
    /// DHCP protocol treats any values sent by a client as hints.
    /// This is a method that implements that. We can assign any value
    /// from configured range that client asks.
    ///
    /// @param hint A value being returned when if it is within the range
    /// between min and max value of @c Triplet. If the hint value is lower
    /// than min value, the min value is returned. if the hint is greater
    /// than max value, the max value is returned.
    ///
    /// @return A value adjusted to the hint.
    T get(T hint) const {
        if (hint <= min_) {
            return (min_);
        }

        if (hint >= max_) {
            return (max_);
        }

        return (hint);
    }

    /// @brief Returns a maximum allowed value
    T getMax() const { return (max_); }

private:

    /// @brief the minimum value
    T min_;

    /// @brief the maximum value
    T max_;
};


} // namespace isc::dhcp
} // namespace isc

#endif // TRIPLET_H
