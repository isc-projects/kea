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

#ifndef HOST_DATA_SOURCE_FACTORY_H
#define HOST_DATA_SOURCE_FACTORY_H

#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/database_connection.h>
#include <exceptions/exceptions.h>

#include <string>

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

/// @brief No host data source instance exception
///
/// Thrown if an attempt is made to get a reference to the current
/// host data source instance and none is currently available.
class NoHostDataSourceManager : public Exception {
public:
    NoHostDataSourceManager(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class HostDataSourceFactory {
public:
    /// @brief todo
	///
    static void create(const std::string& dbaccess);

    /// @brief Destroy host data source instance
	///
	/// todo
	static void destroy();

	/// @brief Return current host data source instance
	/// todo
	static BaseHostDataSource& instance();

private:
    /// @brief Hold pointer to host data source instance
    ///
    /// todo
    static boost::scoped_ptr<BaseHostDataSource>& getHostDataSourcePtr();

};


}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
