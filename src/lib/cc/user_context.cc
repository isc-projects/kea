// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/user_context.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

void
UserContext::contextToElement(ElementPtr map) const {
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

ElementPtr
UserContext::toElement(ConstElementPtr map) {
    ElementPtr result = isc::data::copy(map);
    // Protect against argument not map
    if (result->getType() != Element::map) {
        return (result);
    }
    ConstElementPtr ctx = result->get("user-context");
    // Protect against user context not map
    if (!ctx || (ctx->getType() != Element::map)) {
        return (result);
    }
    // Extract comment
    if (ctx->contains("comment")) {
        ElementPtr ctx_copy = isc::data::copy(ctx);
        result->set("comment", ctx_copy->get("comment"));
        ctx_copy->remove("comment");
        result->remove("user-context");
        if (ctx_copy->size() > 0) {
            result->set("user-context", ctx_copy);
        }
    }
    return (result);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
