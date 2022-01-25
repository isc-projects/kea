// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SCHEMA_H
#define SCHEMA_H

#include <config.h>
#include <cstdlib>
#include <string>

namespace isc {
namespace db {
namespace test {

extern const char* INVALID_TYPE;
extern const char* VALID_NAME;
extern const char* INVALID_NAME;
extern const char* VALID_HOST;
extern const char* VALID_HOST_TCP;
extern const char* INVALID_HOST;
extern const char* VALID_USER;
extern const char* VALID_READONLY_USER;
extern const char* VALID_SECURE_USER;
extern const char* INVALID_USER;
extern const char* VALID_PASSWORD;
extern const char* INVALID_PASSWORD;
extern const char* VALID_TIMEOUT;
extern const char* INVALID_TIMEOUT_1;
extern const char* INVALID_TIMEOUT_2;
extern const char* VALID_READONLY_DB;
extern const char* INVALID_READONLY_DB;
extern const char* VALID_CERT;
extern const char* VALID_KEY;
extern const char* INVALID_KEY;
extern const char* VALID_CA;
extern const char* VALID_CIPHER;

/// @brief Given a combination of strings above, produce a connection string.
///
/// @param type type of the database
/// @param name name of the database to connect to
/// @param host hostname
/// @param user username used to authenticate during connection attempt
/// @param password password used to authenticate during connection attempt
/// @param timeout timeout used during connection attempt
/// @param readonly_db specifies if database is read only
/// @param cert_file specifies the client certificate file
/// @param key_file specifies the private key file
/// @param trust_anchor specifies the trust anchor aka cert authority
/// @param cipher specifies the cipher list
/// @return string containing all specified parameters
std::string connectionString(const char* type, const char* name = 0,
                             const char* host = 0, const char* user = 0,
                             const char* password = 0, const char* timeout = 0,
                             const char* readonly_db = 0,
                             const char* cert_file = 0,
                             const char* key_file = 0,
                             const char* trust_anchor = 0,
                             const char* cipher = 0);

/// @brief Determines if  wiping only the data between tests is enabled
///
/// @return true if the environment variable, KEA_TEST_DB_WIPE_DATA_ONLY is
/// defined as "true" or if it is not present.
bool softWipeEnabled();

}
}
}

#endif
