// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <process/config_ctl_info.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace process {

void
ConfigDbInfo::setAccessString(const std::string& access_str) {
    access_str_ = access_str;
    access_params_.clear();
    access_params_ = db::DatabaseConnection::parse(access_str_);
}

bool
ConfigDbInfo::equals(const ConfigDbInfo& other) const {
    return (access_params_ == other.access_params_);
}

isc::data::ElementPtr
ConfigDbInfo::toElement() const {
    return (isc::db::DatabaseConnection::toElementDbAccessString(access_str_));
}

bool
ConfigDbInfo::getParameterValue(const std::string& name, std::string& value) const {
    auto param = access_params_.find(name);
    if (param == access_params_.end()) {
        return(false);
    }

    value = param->second;
    return(true);
}

//********* ConfiControlInfo ************//

ConfigControlInfo::ConfigControlInfo(const ConfigControlInfo& other)
    : config_fetch_wait_time_(other.config_fetch_wait_time_) {
    for (auto db : other.db_infos_) {
        addConfigDatabase(db.getAccessString());
    }
}

void
ConfigControlInfo::addConfigDatabase(const std::string& access_str) {
    ConfigDbInfo new_db;
    new_db.setAccessString(access_str);

    for (auto db : db_infos_) {
        if (new_db == db) {
            // we have a duplicate!
            isc_throw(BadValue, "database with access parameters: "
                      << access_str << " already exists");
        }
    }

    db_infos_.push_back(new_db);
}

const ConfigDbInfo&
ConfigControlInfo::findConfigDb(const std::string& param_name,
                                const std::string& param_value) {
    for (ConfigDbInfoList::iterator db = db_infos_.begin();
         db != db_infos_.end(); ++db) {
        std::string db_value;
        if (db->getParameterValue(param_name, db_value) &&
            (param_value == db_value)) {
                return (*db);
            }
    }

    return (EMPTY_DB());
}

const ConfigDbInfo&
ConfigControlInfo::EMPTY_DB() {
    static ConfigDbInfo empty;
    return (empty);
}

void
ConfigControlInfo::clear() {
    db_infos_.clear();
    config_fetch_wait_time_ = Optional<uint16_t>(30, true);
}

void
ConfigControlInfo::merge(const ConfigControlInfo& other) {
    if (!other.db_infos_.empty()) {
        db_infos_ = other.db_infos_;
    }
}

ElementPtr
ConfigControlInfo::toElement() const {
    ElementPtr result = Element::createMap();
    ElementPtr db_list = Element::createList();
    for (auto db_info : db_infos_) {
        db_list->add(db_info.toElement());
    }

    result->set("config-databases", db_list);

    if (!config_fetch_wait_time_.unspecified()) {
        result->set("config-fetch-wait-time",
                    Element::create(static_cast<int>(config_fetch_wait_time_)));
    }

    return(result);
}

bool
ConfigControlInfo::equals(const ConfigControlInfo& other) const {
   return ((db_infos_ == other.db_infos_) &&
           (config_fetch_wait_time_ == other.config_fetch_wait_time_));
}

} // end of namespace isc::process
} // end of namespace isc
