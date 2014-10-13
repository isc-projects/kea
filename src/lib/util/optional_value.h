// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTIONAL_VALUE_H
#define OPTIONAL_VALUE_H

namespace isc {
namespace util {

/// @brief Simple class representing an optional value.
///
/// This template class encapsulates a value of any type. An additional flag
/// held by this class indicates if the value is "specified" or "unspecified".
/// For example, a configuration parser for DHCP server may use this class
/// to represent the value of the configuration parameter which may appear
/// in the configuration file, but is not mandatory. The value of the
/// @c OptionalValue may be initialized to "unspecified" initially. When the
/// configuration parser finds that the appropriate parameter exists in the
/// configuration file, the default value can be overriden and the value may
/// be marked as "specified". If the parameter is not found, the value remains
/// "unspecified" and the appropriate actions may be taken, e.g. the default
/// value may be used.
///
/// This is a generic class and may be used in all cases when there is a need
/// for the additional information to be carried along with the value.
/// Alternative approach is to use a pointer which is only initialized if the
/// actual value needs to be specified, but this may not be feasible in all
/// cases.
///
/// @tparam Type of the encapsulated value.
template<typename T>
class OptionalValue {
public:

    /// @brief Constructor
    ///
    /// Creates optional value. The value defaults to "unspecified".
    ///
    /// @param value Default explicit value.
    /// @param specified Boolean value which determines if the value is
    /// initially specified or not (default is false).
    OptionalValue(const T& value, const bool specified = false)
        : value_(value),
          specified_(specified) {
    }

    /// @brief Retrieves the actual value.
    T get() const {
        return (value_);
    }

    /// @brief Sets the actual value.
    ///
    /// @param value New value.
    void set(const T& value) {
        value_ = value;
    }

    /// @brief Sets the new value and marks it specified.
    ///
    /// @param value New actual value.
    void specify(const T& value) {
        set(value);
        specify(true);
    }

    /// @brief Sets the value to "specified" or "unspecified".
    ///
    /// It does not alter the actual value. It only marks it "specified" or
    /// "unspecified".
    /// @param specified boolean that determined if a value is specified or not
    void specify(const bool specified) {
        specified_ = specified;
    }

    /// @brief Checks if the value is specified or unspecified.
    ///
    /// @return true if the value is specified, false otherwise.
    bool isSpecified() const {
        return (specified_);
    }

private:
    T value_;         ///< Encapsulated value.
    bool specified_;  ///< Flag which indicates if the value is specified.
};

} // end of namespace isc::util
} // end of namespace isc

#endif // OPTIONAL_VALUE_H
