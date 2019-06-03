// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/server_tag.h>
#include <exceptions/exceptions.h>
#include <util/strutil.h>

namespace isc {
namespace data {

std::string ServerTag::ALL = "all";

ServerTag::ServerTag()
    : tag_(ALL) {
}

ServerTag::ServerTag(const std::string& tag)
    : tag_(util::str::trim(tag)) {
    if (tag_.empty()) {
        isc_throw(BadValue, "server-tag must not be empty");

    } else if (tag_.length() > 256) {
        isc_throw(BadValue, "server-tag must not be longer than 256 characters");
    }
}

bool
ServerTag::amAll() const {
    return (tag_ == ALL);
}

} // end of namespace isc::data
} // end of namespace isc
