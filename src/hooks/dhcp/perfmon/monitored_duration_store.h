// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MONITORED_DURATION_STORE_H
#define MONITORED_DURATION_STORE_H

#include <exceptions/exceptions.h>
#include <monitored_duration.h>

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
class DuplicateDurationKey : public Exception {
public:
    DuplicateDurationKey(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Tag for index by primary key (DurationKey).
struct DurationKeyTag { };

/// @brief A multi index container holding pointers to MonitoredDurations.
///
/// The durations in the container may be accessed using different indexes:
/// - using the full key index
///   <TBD>
///
/// Indexes can be accessed using the index number (from 0 to n) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to Lease6 objects.
    MonitoredDurationPtr,
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts using DurationKey::operators
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<DurationKeyTag>,
            boost::multi_index::identity<DurationKey>
        >
        /// @todo more indexes start here...
#if 0
        /// @todo toss this ... did this before I figured out how to use
        /// DurationKey::operator<
        ,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<KeyTag>,
            boost::multi_index::composite_key<
                MonitoredDuration,
                // The query packet type
                boost::multi_index::const_mem_fun<DurationKey, uint8_t,
                                                  &DurationKey::getQueryType>,
                // The response packet type
                boost::multi_index::const_mem_fun<DurationKey, uint8_t,
                                                  &DurationKey::getResponseType>,
                // The start event label
                boost::multi_index::const_mem_fun<DurationKey, std::string,
                                                  &DurationKey::getStartEventLabel>,
                // The end event label
                boost::multi_index::const_mem_fun<DurationKey, std::string,
                                                  &DurationKey::getEndEventLabel>,
                // The subnet id
                boost::multi_index::const_mem_fun<DurationKey, dhcp::SubnetID,
                                                  &DurationKey::getSubnetId>
            >
        >
#endif
    >
> MonitoredDurationContainer;

/// @brief Type for a collection of MonitoredDurationPtrs.
typedef std::vector<MonitoredDurationPtr> MonitoredDurationCollection;

/// @brief Type for a pointer to a collection of MonitoredDurationPtrs.
typedef boost::shared_ptr<MonitoredDurationCollection> MonitoredDurationCollectionPtr;

/// @brief Maintains an in-memory store of MonitoredDurations
///
/// Provides essential CRUD functions for managing a collection of
/// MonitoredDurations.  Additionally there are finders that can return
/// durations by DurationKey  <TBD>
/// All finders return copies of the durations found, rather than the
/// stored duration itself.
class MonitoredDurationStore {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    /// @param interval_duration the interval duration
    explicit MonitoredDurationStore(uint16_t family, const Duration& interval_duration);

    /// @brief Destructor
    ~MonitoredDurationStore() = default;

    /// @brief Creates a new MonitoredDuration and adds it to the store
    ///
    /// @param key key value of the duration to create.
    /// @param sample An initial sample to add to the duration if not zero.
    ///
    /// @return pointer to the newly created duration.
    /// @throw DuplicateDuration if a duration for the given key already exists in
    /// the store.
    MonitoredDurationPtr addDuration(DurationKeyPtr key, const Duration& sample
                                                         = DurationDataInterval::ZERO_DURATION());

    /// @brief Fetches a duration from the store for a given key.
    ///
    /// @param key key value of the duration to fetch.
    ///
    /// @return Pointer the desired duration or an empty pointer.
    MonitoredDurationPtr getDuration(DurationKeyPtr key);

    /// @brief Updates a duration in the store.
    ///
    /// The duration is assumed to already exist in the store.
    ///
    /// @param duration duration to update.
    ///
    /// @throw InvalidOperation if MonitoredDuration does not exist in the store.
    void updateDuration(MonitoredDurationPtr& duration);

    /// @brief Removes the duration from the store.
    ///
    /// If the duration does not exist in the store, it simply returns.
    ///
    /// @param key key value of the duration to delete.
    void deleteDuration(DurationKeyPtr key);

    /// @brief Fetches all of the durations (in order by target)
    ///
    /// @return a collection of all durations in the store.
    MonitoredDurationCollectionPtr getAll();

    /// @brief Removes all durations from the store.
    void clear();

    /// @brief Get protocol family
    ///
    /// @return uint16_t containing the family (AF_INET or AF_INET6)
    uint16_t getFamily() {
        return (family_);
    }

private:
    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief The length of time over data for a single MonitoredDuration is
    /// accumulated before reporting.
    Duration interval_duration_;

    /// @brief Container instance.
    MonitoredDurationContainer durations_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

typedef boost::shared_ptr<MonitoredDurationStore> MonitoredDurationStorePtr;

} // end of namespace ping_check
} // end of namespace isc

#endif
