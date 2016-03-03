// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <sstream>

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
        HostDataSourceFactory::create(getHostDbAccessString());
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



} // end of isc::dhcp namespace
} // end of isc namespace
