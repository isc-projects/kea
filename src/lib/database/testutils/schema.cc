// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <string>

using namespace std;

namespace isc {
namespace db {
namespace test {

// Connection strings.
// Database: keatest
// Host: localhost
// Username: keatest
// Password: keatest

const char* INVALID_TYPE = "type=unknown";
const char* VALID_NAME = "name=keatest";
const char* INVALID_NAME = "name=invalidname";
const char* VALID_HOST = "host=localhost";
const char* INVALID_HOST = "host=invalidhost";
const char* VALID_USER = "user=keatest";
const char* VALID_READONLY_USER = "user=keatest_readonly";
const char* INVALID_USER = "user=invaliduser";
const char* VALID_PASSWORD = "password=keatest";
const char* INVALID_PASSWORD = "password=invalid";
const char* VALID_TIMEOUT = "connect-timeout=10";
const char* INVALID_TIMEOUT_1 = "connect-timeout=foo";
const char* INVALID_TIMEOUT_2 = "connect-timeout=-17";
const char* VALID_READONLY_DB = "readonly=true";
const char* INVALID_READONLY_DB = "readonly=5";

string connectionString(const char* type, const char* name, const char* host,
                        const char* user, const char* password, const char* timeout,
                        const char* readonly_db = NULL) {
    const string space = " ";
    string result = "";

    if (type != NULL) {
        result += string(type);
    }
    if (name != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(name);
    }

    if (host != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(host);
    }

    if (user != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(user);
    }

    if (password != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(password);
    }

    if (timeout != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(timeout);
    }

    if (readonly_db != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(readonly_db);
    }

    return (result);
}

bool
softWipeEnabled() {
    const char* const wipe_only = getenv("KEA_TEST_DB_WIPE_DATA_ONLY");
    if (wipe_only && (std::string(wipe_only) == std::string("false"))) {
        return (false);
    }

    return (true);
}

};
};
};
