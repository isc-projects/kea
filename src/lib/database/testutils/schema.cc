// Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")
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
const char* VALID_HOST_TCP = "host=127.0.0.1";
const char* INVALID_HOST = "host=invalidhost";
const char* INVALID_PORT_1 = "port=65536";
const char* VALID_USER = "user=keatest";
const char* VALID_READONLY_USER = "user=keatest_readonly";
const char* VALID_SECURE_USER = "user=keatest_secure";
const char* INVALID_USER = "user=invaliduser";
const char* VALID_PASSWORD = "password=keatest";
const char* INVALID_PASSWORD = "password=invalid";
const char* VALID_TIMEOUT = "connect-timeout=10";
const char* INVALID_TIMEOUT_1 = "connect-timeout=foo";
const char* INVALID_TIMEOUT_2 = "connect-timeout=-17";
const char* INVALID_TIMEOUT_3 = "connect-timeout=0";
const char* VALID_READ_TIMEOUT = "read-timeout=11";
const char* VALID_READ_TIMEOUT_ZERO = "read-timeout=0";
const char* INVALID_READ_TIMEOUT_1 = "read-timeout=bar";
const char* VALID_WRITE_TIMEOUT = "write-timeout=12";
const char* VALID_WRITE_TIMEOUT_ZERO = "write-timeout=0";
const char* INVALID_WRITE_TIMEOUT_1 = "write-timeout=baz";
const char* VALID_TCP_USER_TIMEOUT = "tcp-user-timeout=8";
const char* VALID_TCP_USER_TIMEOUT_ZERO = "tcp-user-timeout=0";
const char* INVALID_TCP_USER_TIMEOUT_1 = "-7";
const char* VALID_READONLY_DB = "readonly=true";
const char* INVALID_READONLY_DB = "readonly=5";
const char* VALID_CERT = "cert-file=" TEST_CA_DIR "/kea-client.crt";
const char* VALID_KEY = "key-file=" TEST_CA_DIR "/kea-client.key";
const char* INVALID_KEY = "key-file=" TEST_CA_DIR "/kea-other.key";
const char* VALID_CA = "trust-anchor=" TEST_CA_DIR "/kea-ca.crt";
const char* VALID_CIPHER = "cipher-list=AES";

string connectionString(const char* type, const char* name, const char* host,
                        const char* user, const char* password,
                        const char* timeout, const char* readonly_db,
                        const char* cert_file, const char* key_file,
                        const char* trust_anchor, const char* cipher) {
    const string space = " ";
    string result = "";

    if (type) {
        result += string(type);
    }

    if (name) {
        if (! result.empty()) {
            result += space;
        }
        result += string(name);
    }

    if (host) {
        if (! result.empty()) {
            result += space;
        }
        result += string(host);
    }

    if (user) {
        if (! result.empty()) {
            result += space;
        }
        result += string(user);
    }

    if (password) {
        if (! result.empty()) {
            result += space;
        }
        result += string(password);
    }

    if (timeout) {
        if (! result.empty()) {
            result += space;
        }
        result += string(timeout);
    }

    if (readonly_db) {
        if (! result.empty()) {
            result += space;
        }
        result += string(readonly_db);
    }

    if (cert_file) {
        if (! result.empty()) {
            result += space;
        }
        result += string(cert_file);
    }

    if (key_file) {
        if (! result.empty()) {
            result += space;
        }
        result += string(key_file);
    }

    if (trust_anchor) {
        if (! result.empty()) {
            result += space;
        }
        result += string(trust_anchor);
    }

    if (cipher) {
        if (! result.empty()) {
            result += space;
        }
        result += string(cipher);
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

}
}
}
