// Copyright (C) 2012-2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_lease_mgr.h>
#endif
#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_lease_mgr.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <utility>

using namespace std;

namespace isc {
namespace dhcp {

boost::scoped_ptr<LeaseMgr>&
LeaseMgrFactory::getLeaseMgrPtr() {
    static boost::scoped_ptr<LeaseMgr> leaseMgrPtr;
    return (leaseMgrPtr);
}

void
LeaseMgrFactory::create(const std::string& dbaccess) {
    const std::string type = "type";

    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(dbaccess);
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);

    // Is "type" present?
    if (parameters.find(type) == parameters.end()) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_NOTYPE_DB).arg(dbaccess);
        isc_throw(InvalidParameter, "Database configuration parameters do not "
                  "contain the 'type' keyword");
    }


    // Yes, check what it is.
#ifdef HAVE_MYSQL
    if (parameters[type] == string("mysql")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_DB).arg(redacted);
        getLeaseMgrPtr().reset(new MySqlLeaseMgr(parameters));
        return;
    }
#endif
#ifdef HAVE_PGSQL
    if (parameters[type] == string("postgresql")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_DB).arg(redacted);
        getLeaseMgrPtr().reset(new PgSqlLeaseMgr(parameters));
        return;
    }
#endif
    if (parameters[type] == string("memfile")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_DB).arg(redacted);
        getLeaseMgrPtr().reset(new Memfile_LeaseMgr(parameters));
        return;
    }

    // Get here on no match
    LOG_ERROR(dhcpsrv_logger, DHCPSRV_UNKNOWN_DB).arg(parameters[type]);
    isc_throw(InvalidType, "Database access parameter 'type' does "
              "not specify a supported database backend");
}

void
LeaseMgrFactory::destroy() {
    // Destroy current lease manager.  This is a no-op if no lease manager
    // is available.
    if (getLeaseMgrPtr()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CLOSE_DB)
            .arg(getLeaseMgrPtr()->getType());
    }
    getLeaseMgrPtr().reset();
}

LeaseMgr&
LeaseMgrFactory::instance() {
    LeaseMgr* lmptr = getLeaseMgrPtr().get();
    if (lmptr == NULL) {
        isc_throw(NoLeaseManager, "no current lease manager is available");
    }
    return (*lmptr);
}


}; // namespace dhcp
}; // namespace isc
