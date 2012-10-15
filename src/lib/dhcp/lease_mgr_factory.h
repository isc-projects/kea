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

#include <string>
#include <dhcp/lease_mgr.h>


namespace isc {
namespace dhcp {

/// @brief Lease Manager Factory
///
/// This class comprises nothing but static methods used to create a lease
/// manager.  It analyzes the database information passed to the creation
/// function and instantiates an appropriate lease manager based on the type
/// requested.
///
/// Strictly speaking these functions could be stand-alone functions.  However,
/// it is convenient to encapsulate them in a class for naming purposes.
class LeaseMgrFactory {
public:
    /// @brief Create an instance of a lease manager.
    ///
    /// Each database backend has its own lease manager type.  This static
    /// method returns a lease manager of the appropriate type, based on the
    /// the data in the input argument.
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
    /// @return Implementation of lease manager for the specified database.
    static LeaseMgrPtr create(const std::string& dbconfig);

    /// @brief Parse Database Parameters
    ///
    /// Parses the string of "keyword=value" pairs and separates them
    /// out into the map.
    ///
    /// @param dbconfig Database configuration string
    ///
    /// @return std::map<>std::string, std::string> Map of keyword/value pairs.
    static LeaseMgr::ParameterMap parse(const std::string& dbconfig);
};

}; // end of isc::dhcp namespace

}; // end of isc namespace
