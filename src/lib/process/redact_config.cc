// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <process/redact_config.h>

using namespace isc::data;
using namespace std;

namespace isc {
namespace process {

ConstElementPtr
redactConfig(ConstElementPtr elem, bool& redacted, const set<string>& follow) {
    // From isc::data::copy.
    if (!elem) {
        isc_throw(BadValue, "redactConfig got a null pointer");
    }

    // Redact lists.
    if (elem->getType() == Element::list) {
        ElementPtr result = ElementPtr(new ListElement());
        for (auto item : elem->listValue()) {
            // add wants a ElementPtr so use a shallow copy.
            ElementPtr copy =
                data::copy(redactConfig(item, redacted, follow), 0);
            result->add(copy);
        }
        if (redacted) {
            return (result);
        }
        return (elem);
    }

    // Redact maps.
    if (elem->getType() == Element::map) {
        ElementPtr result = ElementPtr(new MapElement());
        for (auto kv : elem->mapValue()) {
            auto key = kv.first;
            auto value = kv.second;

            if ((key == "password") || (key == "secret")) {
                // Handle passwords.
                redacted = true;
                result->set(key, Element::create(std::string("*****")));
            } else if (key == "user-context") {
                // Skip user contexts.
                result->set(key, value);
            } else if (follow.empty() || follow.count(key)) {
                // Handle this subtree where are passwords or secrets.
                result->set(key, redactConfig(value, redacted, follow));
            } else {
                // Not follow: no passwords and secrets in this subtree.
                result->set(key, value);
            }
        }
        if (redacted) {
            return (result);
        }
        return (elem);
    }

    // Handle other element types.
    return (elem);
}

} // namespace process
} // namespace isc
