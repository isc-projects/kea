// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_MGR_FACTORY_H
#define LEASE_MGR_FACTORY_H

#include <database/database_connection.h>
#include <dhcpsrv/tracking_lease_mgr.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>

#include <string>

namespace isc {
namespace dhcp {


/// @brief No lease manager exception
///
/// Thrown if an attempt is made to get a reference to the current lease
/// manager and none is currently available.
class NoLeaseManager : public Exception {
public:
    NoLeaseManager(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Lease Manager Factory
///
/// This class comprises nothing but static methods used to create a lease
/// manager.  It analyzes the database information passed to the creation
/// function and instantiates an appropriate lease manager based on the type
/// requested.
///
/// Strictly speaking these functions could be stand-alone functions.  However,
/// it is convenient to encapsulate them in a class for naming purposes.
///
/// @todo: Will need to develop some form of registration mechanism for
///        user-supplied backends (so that there is no need to modify the code).
class LeaseMgrFactory {
public:
    /// @brief Create an instance of a lease manager.
    ///
    /// Each database backend has its own lease manager type.  This static
    /// method sets the "current" lease manager to be a manager of the
    /// appropriate type.  The actual lease manager is returned by the
    /// "instance" method.
    ///
    /// @note When called, the current lease manager is <b>always</b> destroyed
    ///       and a new one created - even if the parameters are the same.
    ///
    /// dbaccess is a generic way of passing parameters. Parameters are passed
    /// in the "name=value" format, separated by spaces.  The data MUST include
    /// a keyword/value pair of the form "type=dbtype" giving the database
    /// type, e.q. "mysql" or "sqlite3".
    ///
    /// @param dbaccess Database access parameters.  These are in the form of
    ///        "keyword=value" pairs, separated by spaces. They are backend-
    ///        -end specific, although must include the "type" keyword which
    ///        gives the backend in use.
    ///
    /// @throw isc::InvalidParameter dbaccess string does not contain the "type"
    ///        keyword.
    /// @throw isc::dhcp::InvalidType The "type" keyword in dbaccess does not
    ///        identify a supported backend.
    static void create(const std::string& dbaccess);

    /// @brief Destroy lease manager
    ///
    /// Destroys the current lease manager object.  This should have the effect
    /// of closing the database connection.  The method is a no-op if no
    /// lease manager is available.
    static void destroy();

    /// @brief Recreate an instance of a lease manager with optionally
    /// preserving registered callbacks.
    ///
    /// @param dbaccess Database access parameters.  These are in the form of
    ///        "keyword=value" pairs, separated by spaces. They are backend-
    ///        -end specific, although must include the "type" keyword which
    ///        gives the backend in use.
    /// @param preserve_callbacks a boolean flag indicating if all registered
    ///        @c TrackingLeaseMgr callbacks should be copied to the new
    ///        instance.
    static void recreate(const std::string& dbaccess,
                         bool preserve_callbacks = true);

    /// @brief Return current lease manager
    ///
    /// Returns an instance of the "current" lease manager.  An exception
    /// will be thrown if none is available.
    ///
    /// @throw isc::dhcp::NoLeaseManager No lease manager is available: use
    ///        create() to create one before calling this method.
    static TrackingLeaseMgr& instance();

    /// @brief Indicates if the lease manager has been instantiated.
    ///
    /// @return True if the lease manager instance exists, false otherwise.
    static bool haveInstance();

private:
    /// @brief Hold pointer to lease manager
    ///
    /// Holds a pointer to the singleton lease manager.  The singleton
    /// is encapsulated in this method to avoid a "static initialization
    /// fiasco" if defined in an external static variable.
    static boost::scoped_ptr<TrackingLeaseMgr>& getLeaseMgrPtr();

};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // LEASE_MGR_FACTORY_H
