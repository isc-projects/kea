// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STAGED_VALUE_H
#define STAGED_VALUE_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {

/// @brief This class implements set/commit mechanism for a single object.
///
/// In some cases it is desired to set value for an object while keeping
/// ability to revert to an original value under certain conditions.
/// This is often desired for objects holding some part of application's
/// configuration. Configuration is usually a multi-step process and
/// may fail on almost any stage. If this happens, the last good
/// configuration should be used. This implies that some of the state
/// of some of the objects needs to be reverted.
///
/// This class implements a mechanism for setting and committing a value.
/// Until the new value has been committed it is possible to revert to
/// an original value.
///
/// @tparam ValueType Type of the value represented by this class.
template<typename ValueType>
class StagedValue : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// Initializes the default value.
    StagedValue()
        : staging_(new ValueType()), current_(new ValueType()),
          modified_(false) {
    }

    /// @brief Retrieves current value.
    ///
    /// If the value hasn't been modified since last commit, reset or
    /// revert operation, a committed value is returned. If the value
    /// has been modified, the modified value is returned.
    const ValueType& getValue() const {
        return (modified_ ? *staging_ : *current_);
    }

    /// @brief Sets new value.
    ///
    /// @param new_value New value to be assigned.
    void setValue(const ValueType& new_value) {
        *staging_ = new_value;
        modified_ = true;
    }

    /// @brief Commits a value.
    void commit() {
        // Only apply changes if any modifications made.
        if (modified_) {
            current_ = staging_;
        }
        revert();
    }

    /// @brief Resets value to defaults.
    void reset() {
        revert();
        current_.reset(new ValueType());
    }

    /// @brief Reverts any modifications since last commit.
    void revert() {
        staging_.reset(new ValueType());
        modified_ = false;
    }

    /// @brief Assignment operator.
    ///
    /// @param value New value to be assigned.
    /// @return Reference to this.
    StagedValue& operator=(const ValueType& value) {
        setValue(value);
        return (*this);
    }

    /// @brief Conversion operator to value type.
    ///
    /// @return Reference to value represented by this object.
    operator const ValueType&() const {
        return (getValue());
    }

private:

    /// @brief Pointer to staging value.
    ///
    /// This value holds any modifications made.
    boost::shared_ptr<ValueType> staging_;

    /// @brief Pointer to committed value.
    ///
    /// This value holds last committed changes.
    boost::shared_ptr<ValueType> current_;

    /// @brief Boolean flag which indicates if any modifications have been
    /// applied since last commit.
    bool modified_;

};

} // namespace isc::util
} // namespace isc

#endif // STAGED_VALUE_H
