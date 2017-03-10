// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <vector>

using namespace isc::data;

namespace isc {
namespace dhcp {

CfgDbAccess::CfgDbAccess()
    : appended_parameters_(), lease_db_access_("type=memfile"),
      host_db_access_() {
}

std::string
CfgDbAccess::getLeaseDbAccessString() const {
    return (getAccessString(lease_db_access_));
}


std::string
CfgDbAccess::getHostDbAccessString() const {
    return (getAccessString(host_db_access_));
}


void
CfgDbAccess::createManagers() const {
    // Recreate lease manager.
    LeaseMgrFactory::destroy();
    LeaseMgrFactory::create(getLeaseDbAccessString());

    // Recreate host data source.
    HostDataSourceFactory::destroy();
    if (!host_db_access_.empty()) {
        HostMgr::create(getHostDbAccessString());
    }
}

std::string 
CfgDbAccess::getAccessString(const std::string& access_string) const {
    std::ostringstream s;
    s << access_string;
    // Only append additional parameters if any parameters are specified
    // in a configuration. For host database, no parameters mean that
    // database access is disabled and thus we don't want to append any
    // parameters.
    if ((s.tellp() != std::streampos(0)) && (!appended_parameters_.empty())) {
        s << " " << appended_parameters_;
    }

    return (s.str());
}

ElementPtr
CfgDbAccess::toElementDbAccessString(const std::string& dbaccess) {
    ElementPtr result = Element::createMap();
    // Code from DatabaseConnection::parse
    if (dbaccess.empty()) {
        return (result);
    }
    std::vector<std::string> tokens;
    boost::split(tokens, dbaccess, boost::is_any_of(std::string("\t ")));
    BOOST_FOREACH(std::string token, tokens) {
        size_t pos = token.find("=");
        if (pos != std::string::npos) {
            std::string keyword = token.substr(0, pos);
            std::string value = token.substr(pos + 1);
            if ((keyword == "lfc-interval") ||
                (keyword == "connect-timeout") ||
                (keyword == "port")) {
                // integer parameters
                int64_t int_value;
                try {
                    int_value = boost::lexical_cast<int64_t>(value);
                    result->set(keyword, Element::create(int_value));
                } catch (...) {
                    isc_throw(ToElementError, "invalid DB access "
                              << "integer parameter: "
                              << keyword << "=" << value);
                }
            } else if ((keyword == "persist") ||
                       (keyword == "readonly")) {
                if (value == "true") {
                    result->set(keyword, Element::create(true));
                } else if (value == "false") {
                    result->set(keyword, Element::create(false));
                } else {
                    isc_throw(ToElementError, "invalid DB access "
                              << "boolean parameter: "
                              << keyword << "=" << value);
                }
            } else if ((keyword == "type") ||
                       (keyword == "user") ||
                       (keyword == "password") ||
                       (keyword == "host") ||
                       (keyword == "name") ||
                       (keyword == "contact_points") ||
                       (keyword == "keyspace")) {
                result->set(keyword, Element::create(value));
            } else {
                isc_throw(ToElementError, "unknown DB access parameter: "
                          << keyword << "=" << value);
            }
        } else {
            isc_throw(ToElementError, "Cannot unparse " << token
                      << ", expected format is name=value");
        }
    }
    return (result);
}

} // end of isc::dhcp namespace
} // end of isc namespace
