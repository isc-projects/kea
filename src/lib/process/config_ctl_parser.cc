// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/dhcp_config_error.h>
#include <process/config_ctl_parser.h>
#include <database/dbaccess_parser.h>
#include <cstdint>
#include <string>

using namespace isc;
using namespace isc::data;

namespace isc {
namespace process {

ConfigControlInfoPtr
ConfigControlParser::parse(const data::ConstElementPtr& config_control) {
    ConfigControlInfoPtr ctl_info(new ConfigControlInfo());

    try {
        if (config_control->contains("config-databases")) {

            auto elem = config_control->get("config-databases");
            if (elem->getType() != Element::list) {
                isc_throw (ConfigError, "config-databases must be a list ("
                           << elem->getPosition() << ")");
            }

            const std::vector<data::ElementPtr>& db_list = elem->listValue();
            for (auto db = db_list.cbegin(); db != db_list.end(); ++db) {
                db::DbAccessParser parser;
                std::string access_string;
                parser.parse(access_string, *db);
                /// @todo do we still need access_string for this at all?
                /// can't we just use params directly and get rid of the
                /// string now that DatabaseConnection::toElement(map) exists?
                ctl_info->addConfigDatabase(access_string);
            }
        }

        if (config_control->contains("config-fetch-wait-time")) {
            auto config_fetch_wait_time = getInteger(config_control,
                                                     "config-fetch-wait-time",
                                                     0, 65535);
            ctl_info->setConfigFetchWaitTime(static_cast<uint16_t>(config_fetch_wait_time));
        }

    } catch (const isc::ConfigError&) {
        // Position was already added
        throw;
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what() << " ("
                  << config_control->getPosition() << ")");
    }

    return (ctl_info);
}

} // end of namespace isc::process
} // end of namespace isc

