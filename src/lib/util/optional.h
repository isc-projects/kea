// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <exceptions/exceptions.h>
#include <ostream>
#include <string>

namespace isc {
namespace util {

/// @brief A template representing an optional value.
///
/// This template class encapsulates an optional value. The default implementation
/// encapsulates numeric values, but additional specializations are defined
/// as necessary to support other types od data.
///
/// This class includes a boolean flag which indicates if the encapsulated
/// value is specified or unspecified. For example, a configuration parser
/// for the DHCP server may use this class to represent a value of the
/// configuration parameter which may appear in the configuration file, but
/// is not mandatory. The value of the @c Optional may be initialized to
/// "unspecified" initially. When the configuration parser finds that the
/// particular parameter exists in the configuration file, the default value
/// can be overridden and the value may be marked as "specified". If the
/// parameter is not found, the value remains "unspecified" and the appropriate
/// actions may be taken, e.g. the default value may be used.
///
/// @tparam Type of the encapsulated value.
template<typename T>
class Optional {
public:

    /// @brief Type of the encapsulated value.
    typedef T ValueType;

    /// @brief Assigns a new value value and marks it "specified".
    ///
    /// @tparam A Type of the value to be assigned. Typically this is @c T, but
    /// may also be a type that can be cast to @c T.
    /// @param other new actual value.
    template<typename A>
    Optional<T>& operator=(A other) {
        default_ = other;
        unspecified_ = false;
        return (*this);
    }

    /// @brief Type cast operator.
    ///
    /// This operator converts the optional value to the actual value being
    /// encapsulated.
    ///
    /// @return Encapsulated value.
    operator T() const {
        return (default_);
    }

    /// @brief Equality operator.
    ///
    /// @param other value to be compared.
    bool operator==(const T& other) const {
        return (default_ == other);
    }

    /// @brief Inequality operator.
    ///
    /// @param other value to be compared.
    bool operator!=(const T& other) const {
        return (default_ != other);
    }

    /// @brief Default constructor.
    ///
    /// Sets the encapsulated value to 0 and marks it as "unspecified".
    ///
    /// The caller must ensure that the constructor of the class @c T
    /// creates a valid object when invoked with 0 as an argument.
    /// For example, a @c std::string(0) compiles but will crash at
    /// runtime as 0 is not a valid pointer for the
    /// @c std::string(const char*) constructor. Therefore, the
    /// specialization of the @c Optional template for @c std::string
    /// is provided below. It uses @c std::string default constructor.
    ///
    /// For any other type used with this template which doesn't come
    /// with an appropriate constructor, the caller must create a
    /// template specialization similar to the one provided for
    /// @c std::string below.
    Optional()
        : default_(T(0)), unspecified_(true) {
    }

    /// @brief Constructor
    ///
    /// Sets an explicit value and marks it as "specified".
    ///
    /// @tparam A Type of the value to be assigned. Typically this is @c T, but
    /// may also be a type that can be cast to @c T.
    /// @param value value to be assigned.
    /// @param unspecified initial state. Default is "unspecified".
    template<typename A>
    Optional(A value, const bool unspecified = false)
        : default_(value), unspecified_(unspecified) {
    }

    /// @brief Retrieves the encapsulated value.
    ///
    /// @return the encapsulated value
    T get() const {
        return (default_);
    }

    /// @brief Retrieves the encapsulated value if specified, or the given value
    /// otherwise.
    ///
    /// @param or_value the value it defaults to, if unspecified
    ///
    /// @return the encapsulated value or the default value
    T valueOr(T const& or_value) const {
        if (unspecified_) {
            return or_value;
        }
        return default_;
    }

    /// @brief Modifies the flag that indicates whether the value is specified
    /// or unspecified.
    ///
    /// @param unspecified new value of the flag. If it is @c true, the
    /// value is marked as unspecified, otherwise it is marked as specified.
    void unspecified(bool unspecified) {
        unspecified_ = unspecified;
    }

    /// @brief Checks if the value has been specified or unspecified.
    ///
    /// @return true if the value hasn't been specified, false otherwise.
    bool unspecified() const {
        return (unspecified_);
    }

    /// @brief Checks if the encapsulated value is empty.
    ///
    /// This method can be overloaded in the template specializations that
    /// are dedicated to strings, vectors etc.
    ///
    /// @throw isc::InvalidOperation.
    bool empty() const {
        isc_throw(isc::InvalidOperation, "call to empty() not supported");
    }

protected:
    T default_;         ///< Encapsulated value.
    bool unspecified_;  ///< Flag which indicates if the value is specified.
};

/// @brief Specialization of the default @c Optional constructor for
/// strings.
///
/// It calls default string object constructor.
template<>
inline Optional<std::string>::Optional()
    : default_(), unspecified_(true) {
}

/// @brief Specialization of the @c Optional::empty method for strings.
///
/// @return true if the value is empty, false otherwise.
template<>
inline bool Optional<std::string>::empty() const {
    return (default_.empty());
}

/// @brief Inserts an optional value to a stream.
///
/// This function overloads the global operator<< to behave as in
/// @c ostream::operator<< but applied to @c Optional objects.
///
/// @param os A @c std::ostream object to which the value is inserted.
/// @param optional_value An @c Optional object to be inserted into
/// a stream.
/// @tparam Type of the value encapsulated by the @c Optional object.
///
/// @return A reference to the stream after insertion.
template<typename T>
std::ostream&
operator<<(std::ostream& os, const Optional<T>& optional_value) {
    os << optional_value.get();
    return (os);
}


} // end of namespace isc::util
} // end of namespace isc

#endif // OPTIONAL_VALUE_H
