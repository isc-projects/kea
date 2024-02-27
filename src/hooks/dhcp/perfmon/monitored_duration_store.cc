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
using namespace isc::util;

namespace isc {
namespace perfmon {

MonitoredDurationStore::MonitoredDurationStore(uint16_t family,
                                               const Duration& interval_duration)
    : family_(family),
      interval_duration_(interval_duration),
      durations_(),
      mutex_(new std::mutex) {
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
MonitoredDurationStore::addDuration(DurationKeyPtr key,
                                    const Duration& sample /* = ZERO_DURATION()*/) {
    validateKey("addDuration", key);

    // Create the duration instance.
    MonitoredDurationPtr mond;
    try {
        mond.reset(new MonitoredDuration(*key, interval_duration_));
        // Add the first sample if provided.
        if (sample > DurationDataInterval::ZERO_DURATION()) {
            mond->addSample(sample);
        }
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

    // Use replace() to re-index durations.
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
    for (auto duration_iter = index.begin(); duration_iter != index.end(); ++duration_iter) {
        collection->push_back(MonitoredDurationPtr(new MonitoredDuration(**duration_iter)));
    }

    return (collection);
}

void
MonitoredDurationStore::clear() {
    MultiThreadingLock lock(*mutex_);
    durations_.clear();
}

} // end of namespace perfmon
} // end of namespace isc

