// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LEASE_MGR_FACTORY_H
#define LEASE_MGR_FACTORY_H

#include <string>
#include <dhcp/lease_mgr.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

/// @brief Invalid type exception
///
/// Thrown when the factory doesn't recognise the type of the backend.
class InvalidType : public Exception {
public:
    InvalidType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

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
/// @TODO: Will need to develop some form of registration mechanism for
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
    /// Note: when called, the current lease manager is *always* destroyed
    /// and a new one created - even if the parameters are the same.
    ///
    /// dbconfig is a generic way of passing parameters. Parameters are passed
    /// in the "name=value" format, separated by spaces.  The data MUST include
    /// a keyword/value pair of the form "type=dbtype" giving the database
    /// type, e.q. "mysql" or "sqlite3".
    ///
    /// @param dbconfig Database configuration parameters.  These are in
    ///        the form of "keyword=value" pairs, separated by spaces. These
    ///        are back-end specific, although must include the "type" keyword
    ///        which gives the backend in use.
    ///
    /// @throw isc::InvalidParameter dbconfig string does not contain the "type"
    ///        keyword.
    /// @throw isc::dhcp::InvalidType The "type" keyword in dbconfig does not
    ///        identify a supported backend.
    static void create(const std::string& dbconfig);

    /// @brief Destroy lease manager
    ///
    /// Destroys the current lease manager object.  This should have the effect
    /// of closing the database connection.  The method is a no-op if no
    /// lease manager is available.
    static void destroy();

    /// @brief Return Current Lease Manager
    ///
    /// Returns an instance of the "current" lease manager.  An exception
    /// will be thrown if none is available.
    ///
    /// @throw isc::dhcp::NoLeaseManager No lease manager is available: use
    ///        create() to create one before calling this method.
    static LeaseMgr& instance();

    /// @brief Parse Database Parameters
    ///
    /// Parses the string of "keyword=value" pairs and separates them
    /// out into the map.
    ///
    /// @param dbconfig Database configuration string
    ///
    /// @return std::map<>std::string, std::string> Map of keyword/value pairs.
    static LeaseMgr::ParameterMap parse(const std::string& dbconfig);

private:
    /// @brief Hold pointer to lease manager
    ///
    /// Holds a pointer to the singleton lease manager.  The singleton
    /// is encapsulated in this method to avoid a "static initialization
    /// fiasco" if defined in an external static variable.
    static boost::scoped_ptr<LeaseMgr>& getLeaseMgrPtr();

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // LEASE_MGR_FACTORY_H
