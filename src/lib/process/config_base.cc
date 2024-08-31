// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/logger_specification.h>
#include <process/config_base.h>

#include <list>

using namespace isc::log;
using namespace isc::data;

namespace isc {
namespace process {

void
ConfigBase::applyLoggingCfg() const {
    std::list<LoggerSpecification> specs;
    for (LoggingInfo const& logging_info : logging_info_) {
        if (logging_info.name_ == getRootLoggerName()) {
            // Root logger has to be processed first if we expect child loggers
            // to inherit configuration from it.
            specs.push_front(logging_info.toSpec());
        } else {
            specs.push_back(logging_info.toSpec());
        }
    }
    LoggerManager manager;
    manager.process(specs.begin(), specs.end());
}

bool
ConfigBase::equals(const ConfigBase& other) const {
    // If number of loggers is different, then configurations aren't equal.
    if (logging_info_.size() != other.logging_info_.size()) {
        return (false);
    }
    // Pass through all loggers and try to find the match for each of them
    // with the loggers from the other configuration. The order doesn't
    // matter so we can't simply compare the vectors.
    for (LoggingInfoStorage::const_iterator this_it =
             logging_info_.begin(); this_it != logging_info_.end();
         ++this_it) {
        bool match = false;
        for (LoggingInfoStorage::const_iterator other_it =
                 other.logging_info_.begin();
             other_it != other.logging_info_.end(); ++other_it) {
            if (this_it->equals(*other_it)) {
                match = true;
                break;
            }
        }
        // No match found for the particular logger so return false.
        if (!match) {
            return (false);
        }
    }

    // Check config control info for equality.
    if ((config_ctl_info_ && !other.config_ctl_info_) ||
        (!config_ctl_info_ && other.config_ctl_info_) ||
        ((config_ctl_info_ && other.config_ctl_info_) &&
         (!config_ctl_info_->equals(*(other.config_ctl_info_))))) {
        return (false);
    }

    return (true);
}

void
ConfigBase::copy(ConfigBase& other) const {
    // We will entirely replace loggers in the new configuration.
    other.logging_info_.clear();
    for (auto const& it : logging_info_) {
        other.addLoggingInfo(it);
    }

    // Clone the config control info
    if (config_ctl_info_) {
        other.config_ctl_info_.reset(new ConfigControlInfo(*config_ctl_info_));
    } else {
        other.config_ctl_info_.reset();
    }

    // Clone server tag.
    other.server_tag_ = server_tag_;
}

void
ConfigBase::merge(ConfigBase& other) {
    // Merge logging info.
    if (!other.logging_info_.empty()) {
        logging_info_ = other.logging_info_;
    }

    // Merge the config control info
    if (other.config_ctl_info_) {
        if (config_ctl_info_) {
            config_ctl_info_->merge(*other.config_ctl_info_);
        } else {
            config_ctl_info_ = other.config_ctl_info_;
        }
    }

    // Merge server tag.
    if (!other.server_tag_.unspecified()) {
        server_tag_ = other.server_tag_.get();
    }
}

ElementPtr
ConfigBase::toElement() const {
    ElementPtr result = Element::createMap();

    // Was in the Logging global map.
    if (!logging_info_.empty()) {
        // Set loggers list
        ElementPtr loggers = Element::createList();
        for (LoggingInfoStorage::const_iterator logger =
                 logging_info_.cbegin();
             logger != logging_info_.cend(); ++logger) {
            loggers->add(logger->toElement());
        }
        result->set("loggers", loggers);
    }

    // server-tag
    if (!server_tag_.unspecified()) {
        result->set("server-tag", Element::create(server_tag_.get()));
    }

    return (result);
}

}  // namespace process
}  // namespace isc
