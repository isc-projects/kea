// Copyright (C) 2012, 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef TRIPLET_H
#define TRIPLET_H

#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

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
class Triplet {
public:

    /// @brief Base type to Triplet conversion.
    ///
    /// Typically: uint32_t to Triplet assignment. It is very convenient
    /// to be able to simply write Triplet<uint32_t> x = 7;
    ///
    /// @param other A number to be assigned as min, max and default value.
    Triplet<T>& operator=(T other) {
        min_ = other;
        default_ = other;
        max_ = other;
        // The value is now specified because we just assigned one.
        unspecified_ = false;
        return (*this);
    }

    /// @brief Triplet to base type conversion
    ///
    /// Typically: Triplet to uint32_t assignment. It is very convenient
    /// to be able to simply write uint32_t z = x; (where x is a Triplet)
    operator T() const {
        return (default_);
    }

    /// @brief Constructor without parameters.
    ///
    /// Marks value in @c Triplet unspecified.
    Triplet()
        : min_(0), default_(0), max_(0),
          unspecified_(true) {
    }

    /// @brief Sets a fixed value.
    ///
    /// This constructor assigns a fixed (i.e. no range, just a single value)
    /// value.
    ///
    /// @param value A number to be assigned as min, max and default value.
    // cppcheck-suppress noExplicitConstructor
    Triplet(T value)
        : min_(value), default_(value), max_(value),
          unspecified_(false) {
    }

    /// @brief Sets the default value and thresholds
    ///
    /// @throw BadValue if min <= def <= max rule is violated
    Triplet(T min, T def, T max)
        : min_(min), default_(def), max_(max),
          unspecified_(false) {
        if ( (min_ > def) || (def > max_) ) {
            isc_throw(BadValue, "Invalid triplet values.");
        }
    }

    /// @brief Returns a minimum allowed value
    T getMin() const { return (min_);}

    /// @brief Returns the default value
    T get() const { return (default_); }

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

    /// @brief Check if the value has been specified.
    ///
    /// @return true if the value hasn't been specified, or false otherwise.
    bool unspecified() const {
        return (unspecified_);
    }

private:

    /// @brief the minimum value
    T min_;

    /// @brief the default value
    T default_;

    /// @brief the maximum value
    T max_;

    /// @brief Indicates whether the value is unspecified.
    bool unspecified_;
};


} // namespace isc::dhcp
} // namespace isc

#endif // TRIPLET_H
