// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ALARM_STORE_H
#define ALARM_STORE_H

#include <exceptions/exceptions.h>
#include <alarm.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>

namespace isc {
namespace perfmon {

/// @brief Exception thrown when an attempt was made to add a duplicate key
/// to either the duration or alarm stores.
class DuplicateAlarm : public Exception {
public:
    DuplicateAlarm(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Tag for index by primary key (DurationKey).
struct AlarmPrimaryKeyTag { };

/// @brief A multi index container holding pointers to alarms.
///
/// The alarms in the container may be accessed using different indexes:
/// - using the index on DurationKey members, AlarmPrimaryKeyTag
/// - others to follow based on API
///
/// Indexes can be accessed using the index number (from 0 to n) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to Lease6 objects.
    AlarmPtr,
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts using DurationKey::operators
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<AlarmPrimaryKeyTag>,
            boost::multi_index::identity<DurationKey>
        >
    >
> AlarmContainer;

/// @brief Type for a collection of AlarmPtrs.
typedef std::vector<AlarmPtr> AlarmCollection;

/// @brief Type for a pointer to a collection of AlarmPtrs.
typedef boost::shared_ptr<AlarmCollection> AlarmCollectionPtr;

/// @brief Maintains an in-memory store of alarms
///
/// Provides essential CRUD functions for managing a collection of
/// alarms.  Additionally there are finders that can return
/// durations by DurationKey (others are TBD).
/// All finders return copies of the durations found, rather than the
/// stored duration itself.
class AlarmStore {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    explicit AlarmStore(uint16_t family);

    /// @brief Destructor
    ~AlarmStore() = default;

    /// @brief Checks a sample against an alarm.
    ///
    /// If the alarm exists in the store for the duration key, then Alarm::checkSample()
    /// is invoked on the in-store alarm.  If this returns true, indicating an alarm
    /// state change, then a copy of the in-store alarm is returned, otherwise an empty
    /// pointer is returned.
    ///
    /// If no alarm exists in the store, then it simply returns an empty pointer.
    ///
    /// This function does not/must not modify any index keys.
    ///
    /// @param key key value of the alarm to check.
    /// @param sample duration value to check.
    /// @param report_interval amount of time that must elapse between high
    /// water reports.
    ///
    /// @return A copy of the updated alarm if it should be reported, an empty
    /// pointer otherwise.
    AlarmPtr checkDurationSample(DurationKeyPtr key, const Duration& sample,
                                 const Duration& report_interval);

    /// @brief Creates a new alarm and adds it to the store
    ///
    /// @param key key value of the alarm to create.
    /// @param low_water threshold below which the average duration must fall to clear the alarm
    /// @param high_water threshold above which the average duration must rise to trigger the alarm.
    /// @param enabled true sets state to CLEAR, otherwise DISABLED, defaults to true.
    ///
    /// @return pointer to the newly created alarm.
    /// @throw DuplicateAlarm if a duration for the given key already exists in
    /// the store.
    AlarmPtr addAlarm(DurationKeyPtr key, const Duration& low_water,
                      const Duration& high_water, bool enabled = true);

    /// @brief Adds an alarm to the store.
    ///
    /// @return pointer to a copy of the alarm added.
    AlarmPtr addAlarm(AlarmPtr alarm);

    /// @brief Fetches a duration from the store for a given key.
    ///
    /// @param key key value of the alarm to fetch.
    ///
    /// @return Pointer the desired alarm or an empty pointer.
    AlarmPtr getAlarm(DurationKeyPtr key);

    /// @brief Updates an alarm in the store.
    ///
    /// The alarm is assumed to already exist in the store.
    ///
    /// @param alarm alarm to update.
    ///
    /// @throw InvalidOperation if the alarm does not exist in the store.
    void updateAlarm(AlarmPtr& alarm);

    /// @brief Removes the alarm from the store.
    ///
    /// If the alarm does not exist in the store, it simply returns.
    ///
    /// @param key key value of the alarm to delete.
    void deleteAlarm(DurationKeyPtr key);

    /// @brief Fetches all of the alarms (in order by target)
    ///
    /// @return a collection of all alarms in the store.
    AlarmCollectionPtr getAll();

    /// @brief Removes all alarms from the store.
    void clear();

    /// @brief Get protocol family
    ///
    /// @return uint16_t containing the family (AF_INET or AF_INET6)
    uint16_t getFamily() {
        return (family_);
    }

private:
    /// @brief Convenience method to verify a key is valid for an operation.
    ///
    /// @param label description of where the check is being made, appears in exception text.
    /// @param key key to validate.
    ///
    /// @throw BadValue if the key is either empty or its family does not
    /// match the store.
    void validateKey(const std::string& label, DurationKeyPtr key) const;

    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief Container instance.
    AlarmContainer alarms_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

typedef boost::shared_ptr<AlarmStore> AlarmStorePtr;

} // end of namespace perfmon
} // end of namespace isc

#endif
