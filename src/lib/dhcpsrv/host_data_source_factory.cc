// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "config.h"

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/hosts_log.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_host_data_source.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <utility>

using namespace std;

namespace isc {
namespace dhcp {


HostDataSourcePtr&
HostDataSourceFactory::getHostDataSourcePtr() {
    static HostDataSourcePtr hostDataSourcePtr;
    return (hostDataSourcePtr);
}

void
HostDataSourceFactory::create(const std::string& dbaccess) {
    const std::string type = "type";

    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters =
            DatabaseConnection::parse(dbaccess);
    std::string redacted =
            DatabaseConnection::redactedAccessString(parameters);

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
        getHostDataSourcePtr().reset(new MySqlHostDataSource(parameters));
        return;
    }
#endif

#ifdef HAVE_PGSQL
    if (parameters[type] == string("postgresql")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_DB).arg(redacted);
        isc_throw(NotImplemented, "Sorry, Postgres backend for host reservations "
                  "is not implemented yet.");
        // Set pgsql data source here, when it will be implemented.
        return;
    }
#endif

    // Get here on no match.
    LOG_ERROR(dhcpsrv_logger, DHCPSRV_UNKNOWN_DB).arg(parameters[type]);
    isc_throw(InvalidType, "Database access parameter 'type' does "
              "not specify a supported database backend");
}

void
HostDataSourceFactory::destroy() {
    // Destroy current host data source instance.  This is a no-op if no host
    // data source is available.
    if (getHostDataSourcePtr()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, HOSTS_CFG_CLOSE_HOST_DATA_SOURCE)
            .arg(getHostDataSourcePtr()->getType());
    }
    getHostDataSourcePtr().reset();
}

#if 0
BaseHostDataSource&
HostDataSourceFactory::instance() {
    BaseHostDataSource* hdsptr = getHostDataSourcePtr().get();
    if (hdsptr == NULL) {
        isc_throw(NoHostDataSourceManager,
                "no current host data source instance is available");
    }
    return (*hdsptr);
}
#endif

}; // namespace dhcp
}; // namespace isc
