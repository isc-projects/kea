// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

namespace isc {
namespace dhcp {

/// @brief this template specifies a parameter value
///
/// This template class is used to store configuration parameters, like lifetime or T1.
/// It defines 3 parameters: min, default, and max value. There are 2 constructors:
/// - simple (just one value that sets all parameters)
/// - extended (that sets default value and two thresholds)
/// It will be used with integer types. It provides necessary operators, so
/// it can be assigned to a plain integer or integer assigned to a Triplet.
/// See TripletTest.operator test for details on an easy Triplet usage.
template <class T>
class Triplet {
public:

    /// @brief base type to Triple conversion
    ///
    /// Typically: uint32_t to Triplet assignment. It is very convenient
    /// to be able to simply write Triplet<uint32_t> x = 7;
    Triplet<T> operator=(T other) {
        min_ = other;
        default_ = other;
        max_ = other;
        return *this;
    }

    /// @brief triplet to base type conversion
    ///
    /// Typically: Triplet to uint32_t assignment. It is very convenient
    /// to be able to simply write uint32_t z = x; (where x is a Triplet)
    operator T() const {
        return (default_);
    }

    /// @brief sets a fixed value
    ///
    /// This constructor assigns a fixed (i.e. no range, just a single value)
    /// value.
    Triplet(T value)
        :min_(value), default_(value), max_(value) {
    }

    /// @brief sets the default value and thresholds
    ///
    /// @throw BadValue if min <= def <= max rule is violated
    Triplet(T min, T def, T max)
        :min_(min), default_(def), max_(max) {
        if ( (min_ > def) || (def > max_) ) {
            isc_throw(BadValue, "Invalid triplet values.");
        }
    }

    /// @brief returns a minimum allowed value
    T getMin() const { return min_;}

    /// @brief returns the default value
    T get() const { return default_;}

    /// @brief returns value with a hint
    ///
    /// DHCP protocol treats any values sent by a client as hints.
    /// This is a method that implements that. We can assign any value
    /// from configured range that client asks.
    T get(T hint) const {
        if (hint <= min_) {
            return (min_);
        }

        if (hint >= max_) {
            return (max_);
        }

        return (hint);
    }

    /// @brief returns a maximum allowed value
    T getMax() const { return max_; }

protected:

    /// @brief the minimum value
    T min_;

    /// @brief the default value
    T default_;

    /// @brief the maximum value
    T max_;
};


} // namespace isc::dhcp
} // namespace isc
