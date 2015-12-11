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
    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters =
            DatabaseConnection::parse(dbaccess);

    // Get the databaase type and open the corresponding database
    DatabaseConnection::ParameterMap::iterator it = parameters.find("type");
    if (it == parameters.end()) {
        isc_throw(InvalidParameter, "Host database configuration does not "
                  "contain the 'type' keyword");
    }

    std::string db_type = it->second;

#ifdef HAVE_MYSQL
    if (db_type == "mysql") {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        getHostDataSourcePtr().reset(new MySqlHostDataSource(parameters));
        return;
    }
#endif

#ifdef HAVE_PGSQL
    if (db_type == "postgresql") {
        isc_throw(NotImplemented, "Sorry, PostgreSQL backend for host reservations "
                  "is not implemented yet.");
    }
#endif

    // Get here on no match.
    isc_throw(InvalidType, "Hosts database access parameter 'type': " <<
                           db_type << " is invalid");
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
