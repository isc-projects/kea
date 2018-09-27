// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/dhcp_config_error.h>
#include <config/config_ctl_parser.h>
#include <database/dbaccess_parser.h>
#include <string>

using namespace isc;
using namespace isc::data;

namespace isc {
namespace config {

ConfigControlInfoPtr
ConfigControlParser::parse(const data::ConstElementPtr& config_control) {
    ConfigControlInfoPtr ctl_info(new ConfigControlInfo()); 

    try {
        if (config_control->contains("config-databases")) {
            const std::vector<data::ElementPtr>& db_list =
                config_control->get("config-databases")->listValue();

            for (auto db = db_list.cbegin(); db != db_list.end(); ++db) {
                db::DbAccessParser parser;
                std::string access_string;
                parser.parse(access_string, *db);
                // @todo do we still need access_string for this at all?
                // can't we just use params directly and get rid of the
                // string now that DatabaseConnection::toElement(map) exists?
                ctl_info->addConfigDatabase(access_string);
            }
        }

#if 0
        // @todo, should it have user_context and what about comment?
        ConstElementPtr user_context = shared_network_data->get("user-context");
        if (user_context) {
            shared_network->setContext(user_context);
        }
#endif

    } catch (const isc::ConfigError&) {
        // Position was already added
        throw;
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what() << " ("
                  << config_control->getPosition() << ")");
    }

    return (ctl_info);
}

} // end of namespace isc::config
} // end of namespace isc

