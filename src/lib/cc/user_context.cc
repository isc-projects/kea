// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/user_context.h>


namespace isc {
namespace data {

void
UserContext::contextToElement(ElementPtr map) const {
    // Set user-context extracting comment
    ConstElementPtr context = getContext();
    if (context) {
        map->set("user-context", context);
    }
}

ElementPtr
UserContext::toElement(ConstElementPtr map) {
    ElementPtr result = isc::data::copy(map);
    return (result);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
