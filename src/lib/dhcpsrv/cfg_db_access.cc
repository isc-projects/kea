// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/db_type.h>
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
    if (host_db_access_.empty()) {
        return ("");
    } else {
        return (getAccessString(host_db_access_.front()));
    }
}

std::list<std::string>
CfgDbAccess::getHostDbAccessStringList() const {
    std::list<std::string> ret;
    for (const std::string& dbaccess : host_db_access_) {
        if (!dbaccess.empty()) {
            ret.push_back(getAccessString(dbaccess));
        }
    }
    return (ret);
}

void
CfgDbAccess::createManagers() const {
    // Recreate lease manager.
    LeaseMgrFactory::destroy();
    LeaseMgrFactory::create(getLeaseDbAccessString());

    // Recreate host data source.
    HostMgr::create();
    std::list<std::string> host_db_access_list = getHostDbAccessStringList();
    for (std::string& hds : host_db_access_list) {
        HostMgr::addBackend(hds);
    }

    // Check for a host cache.
    HostMgr::checkCacheBackend(true);
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

} // end of isc::dhcp namespace
} // end of isc namespace
