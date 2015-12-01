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

#ifndef TEST_MYSQL_SCHEMA_H
#define TEST_MYSQL_SCHEMA_H

#include <config.h>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

extern const char* VALID_TYPE;
extern const char* INVALID_TYPE;
extern const char* VALID_NAME;
extern const char* INVALID_NAME;
extern const char* VALID_HOST;
extern const char* INVALID_HOST;
extern const char* VALID_USER;
extern const char* INVALID_USER;
extern const char* VALID_PASSWORD;
extern const char* INVALID_PASSWORD;

/// @brief Create the Schema
///
/// Creates all the tables in what is assumed to be an empty database.
///
/// There is no error checking in this code: if it fails, one of the tests
/// will fall over.
void createMySQLSchema();

/// @brief Clear everything from the database
///
/// There is no error checking in this code: if something fails, one of the
/// tests will (should) fall over.
void destroyMySQLSchema();

/// Return valid connection string
///
/// @return valid MySQL connection string.
std::string validMySQLConnectionString();

/// @brief Given a combination of strings above, produce a connection string.
///
/// @param type type of the database
/// @param name name of the database to connect to
/// @param host hostname
/// @param user username used to authendicate during connection attempt
/// @param password password used to authendicate during connection attempt
/// @return string containing all specified parameters
std::string connectionString(const char* type, const char* name, const char* host,
                             const char* user, const char* password);
};
};
};

#endif
