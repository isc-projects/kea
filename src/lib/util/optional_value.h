// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <ostream>

namespace isc {
namespace util {

/// @brief Indicate if an @c OptionalValue is is specified or not.
///
/// This is a simple wrapper class which holds a boolean value to indicate
/// if the @c OptionalValue is specified or not. By using this class in the
/// @c OptionalValue class constructor we avoid the ambiguity when the
/// @c OptionalValue encapsulates a bool type.
struct OptionalValueState {

    /// @brief Constructor.
    ///
    /// @param specified A boolean value to be assigned.
    OptionalValueState(const bool specified)
        : specified_(specified) {
    }
    /// @brief A bool value encapsulated by this structure.
    bool specified_;
};

/// @brief Simple class representing an optional value.
///
/// This template class encapsulates a value of any type. An additional flag
/// held by this class indicates if the value is "specified" or "unspecified".
/// For example, a configuration parser for DHCP server may use this class
/// to represent the value of the configuration parameter which may appear
/// in the configuration file, but is not mandatory. The value of the
/// @c OptionalValue may be initialized to "unspecified" initially. When the
/// configuration parser finds that the appropriate parameter exists in the
/// configuration file, the default value can be overridden and the value may
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

    /// @brief Default constructor.
    ///
    /// Note that the type @c T must have a default constructor to use this
    /// constructor.
    OptionalValue()
        : value_(T()), specified_(false) {
    }

    /// @brief Constructor
    ///
    /// Creates optional value. The value defaults to "unspecified".
    ///
    /// @param value Default explicit value.
    /// @param state Specifies bool which determines if the value is initially
    /// specified or not (default is false).
    explicit OptionalValue(const T& value, const OptionalValueState& state =
                           OptionalValueState(false))
        : value_(value), specified_(state.specified_) {
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
        specify(OptionalValueState(true));
    }

    /// @brief Sets the value to "specified" or "unspecified".
    ///
    /// It does not alter the actual value. It only marks it "specified" or
    /// "unspecified".
    /// @param specified boolean that determined if a value is specified or not
    void specify(const OptionalValueState& state) {
        specified_ = state.specified_;
    }

    /// @brief Checks if the value is specified or unspecified.
    ///
    /// @return true if the value is specified, false otherwise.
    bool isSpecified() const {
        return (specified_);
    }

    /// @brief Specifies a new value value and marks it "specified".
    ///
    /// @param value New actual value.
    void operator=(const T& value) {
        specify(value);
    }

    /// @brief Equality operator.
    ///
    /// @param value Actual value to compare to.
    ///
    /// @return true if the value is specified and equals the argument.
    bool operator==(const T& value) const {
        return (specified_ && (value_ == value));
    }

    /// @brief Inequality operator.
    ///
    /// @param value Actual value to compare to.
    ///
    /// @return true if the value is unspecified or unequal.
    bool operator!=(const T& value) const {
        return (!operator==(value));
    }

    /// @brief Type cast operator.
    ///
    /// This operator converts the optional value to the actual value being
    /// encapsulated.
    ///
    /// @return Encapsulated value.
    operator T() const {
        return (value_);
    }

private:
    T value_;         ///< Encapsulated value.
    bool specified_;  ///< Flag which indicates if the value is specified.
};

/// @brief Inserts an optional value to a stream.
///
/// This function overloads the global operator<< to behave as in
/// @c ostream::operator<< but applied to @c OptionalValue objects.
///
/// @param os A @c std::ostream object to which the value is inserted.
/// @param optional_value An @c OptionalValue object to be inserted into
/// a stream.
/// @tparam Type of the value encapsulated by the @c OptionalValue object.
///
/// @return A reference to the stream after insertion.
template<typename T>
std::ostream&
operator<<(std::ostream& os, const OptionalValue<T>& optional_value) {
    os << optional_value.get();
    return (os);
}


} // end of namespace isc::util
} // end of namespace isc

#endif // OPTIONAL_VALUE_H
