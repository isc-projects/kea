// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ELEMENT_VALUE_H
#define ELEMENT_VALUE_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <string>

namespace isc {
namespace data {

/// @brief Template class for converting a value encapsulated in the
/// @c Element object into a simple type.
///
/// The @c Element object provides a set of accessors to retrieve
/// values of different types it encapsulates. These methods
/// however can't be always used in template methods and classes.
///
/// Consider a template function which returns a value of a type
/// specified as template argument. In order to convert a value
/// held in the @c Element object it would have to conditionally
/// call this object's accessors to return the value of the
/// appropriate type. This would however fail to compile because
/// the compiler would check for all possible value types returned
/// by the @c Element accessors and report an error for those that
/// don't cast to the returned type.
///
/// This class provides a mechanism to extract the value of the
/// appropriate type from the @c Element object within the
/// template function. It comes with a number of class specializations
/// for various data types to be returned. The default implementation
/// calls @c Element::intValue and casts it to the returned type.
/// There are class specializations for @c double, @c bool and
/// @c string.
///
/// @tparam T Type of the value to be extracted.
template<typename T>
class ElementValue {
public:

    /// @brief Function operator extracting an @c Element value as
    /// integer.
    ///
    /// @param el Element holding a value to be extracted.
    T operator()(ConstElementPtr el) const {
        return (static_cast<T>(el->intValue()));
    }
};

/// @brief The @c ElementValue specialization for double.
template<>
class ElementValue<double> {
public:

    /// @brief Function operator extracting an @c Element value as
    /// double.
    ///
    /// @param el Element holding a value to be extracted.
    double operator()(ConstElementPtr el) const {
        return (el->doubleValue());
    }
};

/// @brief The @c ElementValue specialization for boolean.
template<>
class ElementValue<bool> {
public:

    /// @brief Function operator extracting an @c Element value as
    /// boolean.
    ///
    /// @param el Element holding a value to be extracted.
    bool operator()(ConstElementPtr el) const {
        return (el->boolValue());
    }

};

/// @brief The @c ElementValue specialization for string.
template<>
class ElementValue<std::string> {
public:

    /// @brief Function operator extracting an @c Element value as
    /// string.
    ///
    /// @param el Element holding a value to be extracted.
    std::string operator()(ConstElementPtr el) const {
        return (el->stringValue());
    }
};

/// @brief The @c ElementValue specialization for IOAddress.
template<>
class ElementValue<asiolink::IOAddress> {
public:

    /// @brief Function operator extracting an @c Element value as
    /// IOAddress.
    ///
    /// @note This does NOT support empty string value.
    ///
    /// @param el Element holding a value to be extracted.
    asiolink::IOAddress operator()(ConstElementPtr el) const {
        return (asiolink::IOAddress(el->stringValue()));
    }
};

} // end of namespace isc::data
} // end of namespace isc

#endif // ELEMENT_VALUE_H
