// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/basic_auth.h>
#include <util/encode/base64.h>
#include <util/encode/utf8.h>

using namespace isc::util::encode;
using namespace std;

namespace isc {
namespace http {

BasicHttpAuth::BasicHttpAuth(const std::string& user,
                           const std::string& password)
    : user_(user), password_(password) {
    if (user.find(':') != string::npos) {
        isc_throw(BadValue, "user '" << user << "' must not contain a ':'");
    }
    buildSecret();
    buildCredential();
}

BasicHttpAuth::BasicHttpAuth(const std::string& secret) : secret_(secret) {
    if (secret.find(':') == string::npos) {
        isc_throw(BadValue, "secret '" << secret << "' must contain a ':");
    }
    buildCredential();
}

void BasicHttpAuth::buildSecret() {
    secret_ = user_ + ":" + password_;
}

void BasicHttpAuth::buildCredential() {
    credential_ = encodeBase64(encodeUtf8(secret_));
}

} // end of namespace isc::http
} // end of namespace isc
