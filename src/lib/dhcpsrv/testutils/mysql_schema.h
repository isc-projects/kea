// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
