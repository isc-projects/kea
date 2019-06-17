// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STAMPED_VALUE_H
#define STAMPED_VALUE_H

#include <cc/data.h>
#include <cc/stamped_element.h>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <string>

namespace isc {
namespace data {

class StampedValue;

/// @brief Pointer to the stamped value.
typedef boost::shared_ptr<StampedValue> StampedValuePtr;

/// @brief This class represents a named configuration parameter,
/// e.g. global parameter of the DHCP server.
///
/// Global configuration elements having simple types, e.g. DHCP
/// timers, need to be associatied with modification timestamps.
/// This association is made by deriving from @c StampedElement.
/// The values can be strings, integers, booleans or real numbers.
///
/// Because the strings are more flexible, configuration elements
/// are always held as strings in the configuration backends. This
/// class reflects a single value held in the database. The value
/// can be return in its orginal type or can be returned as a
/// string. Also the null values are allowed.
class StampedValue : public StampedElement {
public:

    /// @brief Constructor creating a null value.
    ///
    /// @param name Name of the value.
    StampedValue(const std::string& name);

    /// @brief Constructor creating a value from the @c Element.
    ///
    /// @param name Name of the value.
    /// @param value Value encapsulated in the @c Element object.
    ///
    /// @throw BadValue if the value is null.
    /// @throw TypeError if the value is neither a string, integer,
    /// bool nor real.
    StampedValue(const std::string& name, const ElementPtr& value);

    /// @brief Constructor creating a string value.
    ///
    /// Creates stamped value from a string.
    ///
    /// @param name Name of the value.
    /// @param value Value to be set.
    StampedValue(const std::string& name, const std::string& value);

    /// @brief Factory function creating a null value.
    ///
    /// @param name Name of the value.
    static StampedValuePtr create(const std::string& name);

    /// @brief Factory function creating a value from the @c Element.
    ///
    /// @param name Name of the value.
    /// @param value Value encapsulated in the @c Element object.
    ///
    /// @throw BadValue if the value is null.
    /// @throw TypeError if the value is neither a string, integer,
    /// bool nor real.
    static StampedValuePtr create(const std::string& name,
                                  const ElementPtr& value);

    /// @brief Factory function creating a string value.
    ///
    /// Creates stamped value from a string.
    ///
    /// @param name Name of the value.
    /// @param value Value to be set.
    static StampedValuePtr create(const std::string& name,
                                  const std::string& value);

    /// @brief Factory function which attempts to convert provided
    /// string value to a given type.
    ///
    /// This factory function is useful in cases when the value is
    /// read as a string from a database. The string value has to
    /// be converted to the appropriate data type. The type is also
    /// known from the database.
    ///
    /// @param name Name of the value.
    /// @param value Value given as string to be converted.
    /// @param type Type of the value to convert to.
    static StampedValuePtr create(const std::string& name,
                                  const std::string& value,
                                  Element::types type);

    /// @brief Returns a type of the value.
    ///
    /// @return Type of the value as integer. It can be compared
    /// with the @c Element::getType() output.
    /// @throw InvalidOperation if the value is null.
    int getType() const;

    /// @brief Returns value name.
    ///
    /// @return Value name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Returns value as string.
    ///
    /// It is allowed to call this function for all supported data
    /// types. They are converted to a string. For example, a real
    /// number of 1.4 will be returned as "1.4". The boolean true
    /// value will be returned as "1" etc.
    ///
    /// @return Stored value as string.
    /// @throw InvalidOperation if the value is null.
    std::string getValue() const;

    /// @brief Checks if the value is null.
    ///
    /// @return true if the value is null, false otherwise.
    bool amNull() const {
        return (!value_);
    }

    /// @brief Returns value as signed integer.
    ///
    /// @return Stored value as a signed integer.
    /// @throw TypeError if the value is not of @c Element::integer
    /// type.
    int64_t getIntegerValue() const;

    /// @brief Returns value as a boolean.
    ///
    /// @return Stored value as a boolean.
    /// @throw TypeError if the value is not of @c Element::boolean
    /// type.
    bool getBoolValue() const;

    /// @brief Returns value as a real number.
    ///
    /// @return Stored value as a real number.
    /// @throw TypeError if the value is not of @c Element::real
    /// type.
    double getDoubleValue() const;

    /// @brief Returns the value as @c Element.
    ConstElementPtr getElementValue() const {
        return (value_);
    }

private:

    /// @brief Checks if the values passed to the constructors
    /// were correct.
    ///
    /// This is called from the constructors.
    ///
    /// @throw BadValue if the value is null.
    /// @throw TypeError if the value type is neither a string,
    /// integer, boolean nor real.
    void validateConstruct() const;

    /// @brief Checks if the value is accessed correctly.
    ///
    /// This is called from the accessors of this class.
    ///
    /// @param type Type of the value expected by the accessor
    /// function.
    ///
    /// @throw InvalidOperation if the accessed value is null.
    /// @throw TypeError if the expected type is not a string
    /// and it doesn't match the value type.
    void validateAccess(Element::types type) const;

    /// @brief Name of the value.
    std::string name_;

    /// @brief Stored value.
    ElementPtr value_;
};

/// @name Definition of the multi index container for @c StampedValue.
///
//@{

/// @brief Tag for the index for access by value name.
struct StampedValueNameIndexTag { };

/// @brief Tag for the index for access by modification time.
struct StampedValueModificationTimeIndexTag { };

/// @brief Multi index container for @c StampedValue.
typedef boost::multi_index_container<
    StampedValuePtr,
    boost::multi_index::indexed_by<
        // Index used to access value by name.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<StampedValueNameIndexTag>,
            boost::multi_index::const_mem_fun<
                StampedValue,
                std::string,
                &StampedValue::getName
            >
        >,

        // Index used to access value by modification time.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<StampedValueModificationTimeIndexTag>,
            boost::multi_index::const_mem_fun<
                BaseStampedElement,
                boost::posix_time::ptime,
                &BaseStampedElement::getModificationTime
            >
        >
    >
> StampedValueCollection;

//@}

} // end of namespace isc::data
} // end of namespace isc

#endif
