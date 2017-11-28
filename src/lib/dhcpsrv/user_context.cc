// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/user_context.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

void
UserContext::contextToElement(ElementPtr map) const{
    // Set user-context extracting comment
    ConstElementPtr context = getContext();
    if (!isNull(context)) {
        if ((context->getType() == Element::map) &&
            context->contains("comment")) {
            ElementPtr copied = isc::data::copy(context);
            map->set("comment", copied->get("comment"));
            copied->remove("comment");
            if (copied->size() > 0) {
                map->set("user-context", copied);
            }
        } else {
            map->set("user-context", context);
        }
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
