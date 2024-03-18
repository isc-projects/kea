// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <monitored_duration_store.h>
#include <util/multi_threading_mgr.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;
using namespace boost::posix_time;

namespace isc {
namespace perfmon {

MonitoredDurationStore::MonitoredDurationStore(uint16_t family,
                                               const Duration& interval_duration)
    : family_(family),
      interval_duration_(interval_duration),
      durations_(),
      mutex_(new std::mutex) {
    if (family != AF_INET && family_ != AF_INET6) {
        isc_throw(BadValue, "MonitoredDurationStore - invalid family "
                            << family_ << ", must be AF_INET or AF_INET6");
    }

    if (interval_duration_ <= DurationDataInterval::ZERO_DURATION()) {
        isc_throw(BadValue, "MonitoredDurationStore - invalid interval_duration "
                            << interval_duration_ << ", must be greater than zero");
    }
}

void
MonitoredDurationStore::validateKey(const std::string& label, DurationKeyPtr key) const {
    if (!key) {
        isc_throw(BadValue, "MonitoredDurationStore::" << label << " - key is empty");
    }

    if (key->getFamily() != family_) {
        isc_throw(BadValue, "MonitoredDurationStore::" << label
                            << " - family mismatch, key is " << (family_ == AF_INET ?
                            "v6, store is v4" : "v4, store is v6"));
    }
}

MonitoredDurationPtr
MonitoredDurationStore::addDurationSample(DurationKeyPtr key, const Duration& sample) {
    validateKey("addDurationSample", key);

    MultiThreadingLock lock(*mutex_);
    auto& index = durations_.get<DurationKeyTag>();
    auto duration_iter = index.find(*key);
    if (duration_iter != index.end()) {
        bool should_report = false;
        // Modify updates in place and only re-indexes if keys change.
        bool modified = index.modify(duration_iter,
                                     [sample, &should_report](MonitoredDurationPtr mond) {
            should_report = mond->addSample(sample);
        });

        if (!modified) {
            // Possible but unlikely.
            isc_throw(Unexpected,
                      "MonitoredDurationStore::addDurationSample - modify failed for: "
                      << key->getLabel());
        }

        // If it's time to report return a copy otherwise an empty pointer.
        return (should_report ? MonitoredDurationPtr(new MonitoredDuration(**duration_iter))
                              : MonitoredDurationPtr());
    }

    // It doesn't exist, add it.
    MonitoredDurationPtr mond(new MonitoredDuration(*key, interval_duration_));
    static_cast<void>(mond->addSample(sample));
    auto ret = durations_.insert(mond);
    if (ret.second == false) {
        // Shouldn't be possible.
        isc_throw(DuplicateDurationKey,
                  "MonitoredDurationStore::addDurationSample: duration already exists for: "
                  << key->getLabel());
    }

    // Nothing to report.
    return (MonitoredDurationPtr());
}

MonitoredDurationPtr
MonitoredDurationStore::addDuration(DurationKeyPtr key) {
    validateKey("addDuration", key);

    // Create the duration instance.
    MonitoredDurationPtr mond;
    try {
        mond.reset(new MonitoredDuration(*key, interval_duration_));
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "MonitoredDurationStore::addDuration failed: " << ex.what());
    }

    // Now lock and insert the new duration.
    {
        MultiThreadingLock lock(*mutex_);
        auto ret = durations_.insert(mond);
        if (ret.second == false) {
            isc_throw(DuplicateDurationKey,
                      "MonitoredDurationStore::addDuration: duration already exists for: "
                      << key->getLabel());
        }
    }

    // Return a copy of what we inserted.
    return (MonitoredDurationPtr(new MonitoredDuration(*mond)));
}


MonitoredDurationPtr
MonitoredDurationStore::getDuration(DurationKeyPtr key) {
    validateKey("getDuration", key);

    MultiThreadingLock lock(*mutex_);
    const auto& index = durations_.get<DurationKeyTag>();
    auto duration_iter = index.find(*key);
    return (duration_iter == index.end() ? MonitoredDurationPtr()
                                         : MonitoredDurationPtr(new MonitoredDuration(**duration_iter)));
}

void
MonitoredDurationStore::updateDuration(MonitoredDurationPtr& duration) {
    validateKey("updateDuration", duration);

    MultiThreadingLock lock(*mutex_);
    auto& index = durations_.get<DurationKeyTag>();
    auto duration_iter = index.find(*duration);
    if (duration_iter == index.end()) {
        isc_throw(InvalidOperation, "MonitoredDurationStore::updateDuration duration not found: "
                  << duration->getLabel());
    }

    // Use replace() which only re-indexes if keys change.
    index.replace(duration_iter, MonitoredDurationPtr(new MonitoredDuration(*duration)));
}

void
MonitoredDurationStore::deleteDuration(DurationKeyPtr key) {
    validateKey("deleteDuration", key);

    MultiThreadingLock lock(*mutex_);
    auto& index = durations_.get<DurationKeyTag>();
    auto duration_iter = index.find(*key);
    if (duration_iter == index.end()) {
        // Not there, just return.
        return;
    }

    // Remove the duration from the store.
    durations_.erase(duration_iter);
}

MonitoredDurationCollectionPtr
MonitoredDurationStore::getAll() {
    MultiThreadingLock lock(*mutex_);
    const auto& index = durations_.get<DurationKeyTag>();
    MonitoredDurationCollectionPtr collection(new MonitoredDurationCollection());
    for (auto const& mond : index) {
        collection->push_back(MonitoredDurationPtr(new MonitoredDuration(*mond)));
    }

    return (collection);
}

void
MonitoredDurationStore::clear() {
    MultiThreadingLock lock(*mutex_);
    durations_.clear();
}

MonitoredDurationPtr
MonitoredDurationStore::getReportsNext() {
    MultiThreadingLock lock(*mutex_);
    const auto& index = durations_.get<IntervalStartTag>();
    // We want to find the oldest interval that is less than interval_duration in the past.
    auto duration_iter = index.lower_bound(dhcp::PktEvent::now() - interval_duration_);
    return (duration_iter == index.end() ? MonitoredDurationPtr()
                                         : MonitoredDurationPtr(new MonitoredDuration(**duration_iter)));
}

MonitoredDurationCollectionPtr
MonitoredDurationStore::getOverdueReports(const Timestamp& since /* = PktEvent::now() */) {
    MultiThreadingLock lock(*mutex_);
    // We use a lower bound of MIN + 1us to avoid dormant durations
    static Timestamp lower_limit_time(PktEvent::MIN_TIME() + microseconds(1));

    // We want to find anything since the start of time who's start time
    // is more than interval_duration_ in the past.
    const auto& index = durations_.get<IntervalStartTag>();
    auto lower_limit = index.lower_bound(lower_limit_time);
    auto upper_limit = index.upper_bound(since - interval_duration_);

    MonitoredDurationCollectionPtr collection(new MonitoredDurationCollection());
    for (auto duration_iter = lower_limit; duration_iter != upper_limit; ++duration_iter) {
        collection->push_back(MonitoredDurationPtr(new MonitoredDuration(**duration_iter)));
    }

    return (collection);
}

} // end of namespace perfmon
} // end of namespace isc

