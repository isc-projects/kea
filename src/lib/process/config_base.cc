// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <process/config_base.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <list>

using namespace isc::log;
using namespace isc::data;

namespace isc {
namespace process {

void
ConfigBase::applyLoggingCfg() const {

    std::list<LoggerSpecification> specs;
    for (LoggingInfoStorage::const_iterator it = logging_info_.begin();
         it != logging_info_.end(); ++it) {
        specs.push_back(it->toSpec());
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
    for (LoggingInfoStorage::const_iterator it = logging_info_.begin();
         it != logging_info_.end(); ++it) {
        other.addLoggingInfo(*it);
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

    // Logging global map (skip if empty)
    if (!logging_info_.empty()) {
        ElementPtr logging = Element::createMap();
        // Set loggers list
        ElementPtr loggers = Element::createList();
        for (LoggingInfoStorage::const_iterator logger =
                 logging_info_.cbegin();
             logger != logging_info_.cend(); ++logger) {
            loggers->add(logger->toElement());
        }
        logging->set("loggers", loggers);
        result->set("Logging", logging);
    }

    // server-tag
    if (!server_tag_.unspecified()) {
        result->set("server-tag", Element::create(server_tag_.get()));
    }

    // We do NOT output ConfigControlInfo here, as it is not a
    // top level element, but rather belongs within the process
    // element.

    return (result);
}

};
};
