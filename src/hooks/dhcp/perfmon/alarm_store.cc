// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <alarm_store.h>
#include <util/multi_threading_mgr.h>

using namespace isc;
using namespace isc::util;

namespace isc {
namespace perfmon {

AlarmStore::AlarmStore(uint16_t family)
    : family_(family),
      alarms_(),
      mutex_(new std::mutex) {
    if (family_ != AF_INET && family_ != AF_INET6) {
        isc_throw(BadValue, "AlarmStore - invalid family "
                            << family_ << ", must be AF_INET or AF_INET6");
    }
}

void
AlarmStore::validateKey(const std::string& label, DurationKeyPtr key) const {
    if (!key) {
        isc_throw(BadValue, "AlarmStore::" << label << " - key is empty");
    }

    if (key->getFamily() != family_) {
        isc_throw(BadValue, "AlarmStore::" << label
                            << " - family mismatch, key is " << (family_ == AF_INET ?
                            "v6, store is v4" : "v4, store is v6"));
    }
}

AlarmPtr
AlarmStore::checkDurationSample(DurationKeyPtr key, const Duration& sample,
                                const Duration& report_interval) {
    validateKey("checkDurationSample", key);

    MultiThreadingLock lock(*mutex_);
    auto& index = alarms_.get<AlarmPrimaryKeyTag>();
    auto alarm_iter = index.find(*key);

    // If we find an alarm then we check the sample.  Alarm::checkSample()
    // does not alter the key so it can be done in-place.
    if (alarm_iter != index.end()) {
        bool should_report = false;
        bool modified = index.modify(alarm_iter,
                                     [sample, report_interval, &should_report](AlarmPtr alarm) {
            should_report = alarm->checkSample(sample, report_interval);
        });

        if (!modified) {
            // Possible but unlikely.
            isc_throw(Unexpected, "AlarmStore::checkDurationSample - modify failed for: " << key->getLabel());
        }

        if (should_report) {
            // Alarm state needs to be reported, return a copy of the alarm.
            return (AlarmPtr(new Alarm(**alarm_iter)));
        }
    }

    // Nothing to alarm.
    return (AlarmPtr());
}

AlarmPtr
AlarmStore::addAlarm(AlarmPtr alarm) {
    MultiThreadingLock lock(*mutex_);
    auto ret = alarms_.insert(alarm);
    if (ret.second == false) {
        isc_throw(DuplicateAlarm, "AlarmStore::addAlarm: alarm already exists for: "
                  << alarm->getLabel());
    }

    // Return a copy of what we inserted.
    return (AlarmPtr(new Alarm(*alarm)));
}

AlarmPtr
AlarmStore::addAlarm(DurationKeyPtr key, const Duration& low_water,
                     const Duration& high_water, bool enabled /* = true */) {
    validateKey("addAlarm", key);

    // Create the alarm instance.
    AlarmPtr alarm;
    try {
        alarm.reset(new Alarm(*key, low_water, high_water, enabled));
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "AlarmStore::addAlarm failed: " << ex.what());
    }

    return (addAlarm(alarm));
}

AlarmPtr
AlarmStore::getAlarm(DurationKeyPtr key) {
    validateKey("getAlarm", key);

    MultiThreadingLock lock(*mutex_);
    const auto& index = alarms_.get<AlarmPrimaryKeyTag>();
    auto alarm_iter = index.find(*key);
    return (alarm_iter == index.end() ? AlarmPtr()
            : AlarmPtr(new Alarm(**alarm_iter)));
}

void
AlarmStore::updateAlarm(AlarmPtr& alarm) {
    validateKey("updateAlarm", alarm);

    MultiThreadingLock lock(*mutex_);
    auto& index = alarms_.get<AlarmPrimaryKeyTag>();
    auto alarm_iter = index.find(*alarm);
    if (alarm_iter == index.end()) {
        isc_throw(InvalidOperation, "AlarmStore::updateAlarm alarm not found: "
                  << alarm->getLabel());
    }

    // Use replace() which only re-indexes if keys change.
    index.replace(alarm_iter, AlarmPtr(new Alarm(*alarm)));
}

void
AlarmStore::deleteAlarm(DurationKeyPtr key) {
    validateKey("deleteAlarm", key);

    MultiThreadingLock lock(*mutex_);
    auto& index = alarms_.get<AlarmPrimaryKeyTag>();
    auto alarm_iter = index.find(*key);
    if (alarm_iter == index.end()) {
        // Not there, just return.
        return;
    }

    // Remove the alarm from the store.
    alarms_.erase(alarm_iter);
}

AlarmCollectionPtr
AlarmStore::getAll() {
    MultiThreadingLock lock(*mutex_);
    const auto& index = alarms_.get<AlarmPrimaryKeyTag>();
    AlarmCollectionPtr collection(new AlarmCollection());
    for (auto const& alarm : index) {
        collection->push_back(AlarmPtr(new Alarm(*alarm)));
    }

    return (collection);
}

void
AlarmStore::clear() {
    MultiThreadingLock lock(*mutex_);
    alarms_.clear();
}

} // end of namespace perfmon
} // end of namespace isc

