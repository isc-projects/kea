// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SCHEMA_H
#define SCHEMA_H

#include <config.h>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

extern const char* INVALID_TYPE;
extern const char* VALID_NAME;
extern const char* INVALID_NAME;
extern const char* VALID_HOST;
extern const char* INVALID_HOST;
extern const char* VALID_USER;
extern const char* INVALID_USER;
extern const char* VALID_PASSWORD;
extern const char* INVALID_PASSWORD;
/// @brief Given a combination of strings above, produce a connection string.
///
/// @param type type of the database
/// @param name name of the database to connect to
/// @param host hostname
/// @param user username used to authendicate during connection attempt
/// @param password password used to authendicate during connection attempt
/// @return string containing all specified parameters
std::string connectionString(const char* type, const char* name,
                             const char* host, const char* user,
                             const char* password);
};
};
};

#endif
