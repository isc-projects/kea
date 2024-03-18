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

/// @brief Exception thrown when an attempt was made to add a duplicate duration
/// to the store.
class DuplicateDurationKey : public Exception {
public:
    DuplicateDurationKey(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Tag for index by primary key (DurationKey).
struct DurationKeyTag { };

/// @brief Tag for index by interval start time.
struct IntervalStartTag { };

/// @brief A multi index container holding pointers to durations.
///
/// The durations in the container may be accessed using different indexes:
/// - using the index on DurationKey members, DurationKeyTag
/// - others to follow based on API
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
        >,

        // Specification of the second index starts here.
        // This index sorts durations by current interval start time.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<IntervalStartTag>,
            boost::multi_index::const_mem_fun<MonitoredDuration, Timestamp,
                                              &MonitoredDuration::getCurrentIntervalStart>
        >
    >
> MonitoredDurationContainer;

/// @brief Type for a collection of MonitoredDurationPtrs.
typedef std::vector<MonitoredDurationPtr> MonitoredDurationCollection;

/// @brief Type for a pointer to a collection of MonitoredDurationPtrs.
typedef boost::shared_ptr<MonitoredDurationCollection> MonitoredDurationCollectionPtr;

/// @brief Maintains an in-memory store of durations
///
/// Provides essential CRUD functions for managing a collection of
/// durations.  Additionally there are finders that can return
/// durations by DurationKey (others are TBD)
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

    /// @brief Adds a sample to a duration in-place.
    ///
    /// If the duration exists in the store then the MonitoredDuration::addSample()
    /// is invoked on the in-store duration.  If this returns true, indicating a reportable
    /// condition, then a copy of the in-store duration is returned, otherwise an empty
    /// pointer is returned.
    ///
    /// If the duration does not exist in the store, then one is created and inserted
    /// into the store after adding the sample.  An empty pointer is returned.
    ///
    /// This function does not/must not modify any index keys.
    ///
    /// @param key key value of the duration to which to add.
    /// @param sample duration value to add
    ///
    /// @return A copy of the updated duration if it should be reported, an empty
    /// pointer otherwise.
    MonitoredDurationPtr addDurationSample(DurationKeyPtr key, const Duration& sample);

    /// @brief Creates a new duration and adds it to the store
    ///
    /// @param key key value of the duration to create.
    ///
    /// @return pointer to the newly created duration.
    /// @throw DuplicateDuration if a duration for the given key already exists in
    /// the store.
    MonitoredDurationPtr addDuration(DurationKeyPtr key);

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
    /// @throw InvalidOperation if duration does not exist in the store.
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

    /// @brief Fetches the duration which is due to report next.
    ///
    /// @return pointer to the matching duration or an empty pointer if
    /// not found.
    MonitoredDurationPtr getReportsNext();

    /// @brief Fetches all durations that are overdue to report.
    ///
    /// @param since timestamp to search by. Defaults to current time.
    ///
    /// @return a collection of the matching durations, ordered by current interval
    /// start time.
    MonitoredDurationCollectionPtr getOverdueReports(const Timestamp& since = dhcp::PktEvent::now());

    /// @brief Removes all durations from the store.
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

    /// @brief The length of time over data for a single duration is
    /// accumulated before reporting.
    Duration interval_duration_;

    /// @brief Container instance.
    MonitoredDurationContainer durations_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

typedef boost::shared_ptr<MonitoredDurationStore> MonitoredDurationStorePtr;

} // end of namespace perfmon
} // end of namespace isc

#endif
