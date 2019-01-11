// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STAMPED_VALUE_H
#define STAMPED_VALUE_H

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

/// @brief This class represents string or signed integer configuration
/// element associated with the modification timestamp.
///
/// Global configuration elements having simple types, e.g. DHCP
/// timers, need to be associatied with modification timestamps.
/// This association is made by deriving from @c StampedElement.
/// Values can be both integers and strings. Because strings are
/// more flexible, configuration elements are always held as strings
/// in the configuration backends. This class reflects a single value
/// held in the database. The value can be converted to an integer or
/// can be returned as a string.
class StampedValue : public StampedElement {
public:

    /// @brief Constructor.
    ///
    /// Creates stamped value from a string.
    ///
    /// @param name Name of the value.
    /// @param value Value to be set.
    StampedValue(const std::string& name, const std::string& value);

    /// @brief Constructor.
    ///
    /// Creates stamped value from the signed integer.
    ///
    /// @param name Name of the value.
    /// @param value Value to be set.
    explicit StampedValue(const std::string& name, const int64_t value);

    /// @brief Convenience function creating shared pointer to the object.
    ///
    /// @param name Name of the value.
    /// @param value String value to be encapsulated by this object.
    static StampedValuePtr create(const std::string& name,
                                  const std::string& value);

    /// @brief Convenience function creating shared Pointer to the object.
    ///
    /// @param name Name of the value.
    /// @param value Integer value to be encapsulated by this object.
    static StampedValuePtr create(const std::string& name,
                                  const int64_t value);

    /// @brief Returns value name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Returns value as string.
    std::string getValue() const {
        return (value_);
    }

    /// @brief Returns value as signed integer.
    ///
    /// @throw BadValue if the value can't be converted to an integer.
    int64_t getSignedIntegerValue() const;

private:

    /// @brief Name of the value.
    std::string name_;

    /// @brief Holds value as a string.
    std::string value_;
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
                StampedElement,
                boost::posix_time::ptime,
                &StampedElement::getModificationTime
            >
        >
    >
> StampedValueCollection;

//@}

} // end of namespace isc::data
} // end of namespace isc

#endif
