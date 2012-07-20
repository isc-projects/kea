// Copyright (C) 2009-2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <auth/common.h>
#include <auth/spec_config.h>
#include <stdlib.h>

using std::string;

string
getXfroutSocketPath() {
    if (getenv("B10_FROM_BUILD") != NULL) {
        if (getenv("B10_FROM_SOURCE_LOCALSTATEDIR") != NULL) {
            return (string(getenv("B10_FROM_SOURCE_LOCALSTATEDIR")) +
                    "/auth_xfrout_conn");
        } else {
            return (string(getenv("B10_FROM_BUILD")) + "/auth_xfrout_conn");
        }
    } else {
        if (getenv("BIND10_XFROUT_SOCKET_FILE") != NULL) {
            return (getenv("BIND10_XFROUT_SOCKET_FILE"));
        } else {
            return (UNIX_XFROUT_SOCKET_FILE);
        }
    }
}

string
getDDNSSocketPath() {
    if (getenv("B10_FROM_BUILD") != NULL) {
        if (getenv("B10_FROM_SOURCE_LOCALSTATEDIR") != NULL) {
            return (string(getenv("B10_FROM_SOURCE_LOCALSTATEDIR")) +
                    "/ddns_socket");
        } else {
            return (string(getenv("B10_FROM_BUILD")) + "/ddns_socket");
        }
    } else {
        if (getenv("BIND10_DDNS_SOCKET_FILE") != NULL) {
            return (getenv("BIND10_DDNS_SOCKET_FILE"));
        } else {
            return (UNIX_DDNS_SOCKET_FILE);
        }
    }
}

const char* const AUTH_NAME = "b10-auth";
const char* const AUTH_STARTED_NOTIFICATION = "auth_started";
