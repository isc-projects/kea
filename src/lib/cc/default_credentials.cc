// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/default_credentials.h>

namespace isc {
namespace data {

const std::unordered_set<std::string>
DefaultCredentials::DEFAULT_CREDENTIALS = {
#ifndef IGNORE_KEA_DEFAULT_CREDENTIALS
#ifndef ALLOW_KEATEST
    "keatest",
#endif
    "1234", "*****"
#endif
#ifdef EXTRA_KEA_DEFAULT_CREDENTIALS
    EXTRA_KEA_DEFAULT_CREDENTIALS
#endif
};

void
DefaultCredentials::check(const std::string& value) {
    if (DEFAULT_CREDENTIALS.count(value)) {
        isc_throw(DefaultCredential,
                  "illegal use of a default value as credential");
    }
}

}  // end of isc::dhcp namespace
}  // end of isc namespace
