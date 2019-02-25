// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <ostream>
#include <string>

namespace isc {
namespace util {

/// @brief A template representing an optional value.
///
/// This template class encapsulates an optional value. The default implementation
/// encapsulates numeric values, but additional specializations are defined
/// as neccessary to support other types od data.
///
/// This class includes a boolean flag which indicates if the encapsulated
/// value is specified or unspecified. For example, a configuration parser
/// for the DHCP server may use this class to represent a value of the
/// configuration parameter which may appear in the configuration file, but
/// is not mandatory. The value of the @c Optional may be initialized to
/// "unspecified" initially. When the configuration parser finds that the
/// particular parameter exists in the configuration file, the default value
/// can be overriden and the value may be marked as "specified". If the
/// parameter is not found, the value remains "unspecified" and the appropriate
/// actions may be taken, e.g. the default value may be used.
///
/// @tparam Type of the encapsulated value.
template<typename T>
class Optional {
public:

    /// @brief Assigns a new value value and marks it "specified".
    ///
    /// @param other new actual value.
    Optional<T>& operator=(T other) {
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

    /// @brief Default constructor.
    ///
    /// Sets the encapsulated value to 0.
    Optional()
        : default_(T(0)), unspecified_(true) {
    }

    /// @brief Constructor
    ///
    /// Creates optional value and marks it as "specified".
    ///
    /// @param value value to be assigned.
    explicit Optional(T value)
        : default_(value), unspecified_(false) {
    }

    /// @brief Retrieves the actual value.
    T get() const {
        return (default_);
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
