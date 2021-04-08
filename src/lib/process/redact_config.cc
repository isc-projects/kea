// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <process/redact_config.h>

using namespace isc::data;
using namespace std;

namespace isc {
namespace process {

ConstElementPtr
redactConfig(ConstElementPtr const& element,
             list<string> const& json_path) {
    if (!element) {
        isc_throw(BadValue, "redactConfig got a null pointer");
    }

    ElementPtr result;
    if (element->getType() == Element::list) {
        // Redact lists.
        result = Element::createList();
        for (ConstElementPtr const& item : element->listValue()) {
            // add wants an ElementPtr so use a shallow copy.
            // We could hypothetically filter lists through JSON paths, but we
            // would have to dig inside the list's children to see if we have a
            // match. So we always copy because it's faster.
            result->add(data::copy(redactConfig(item, json_path), 0));
        }
    } else if (element->getType() == Element::map) {
        // Redact maps.
        result = Element::createMap();
        for (auto kv : element->mapValue()) {
            std::string const& key(kv.first);
            ConstElementPtr const& value(kv.second);

            if ((key == "password") || (key == "secret")) {
                // Handle passwords.
                result->set(key, Element::create(string("*****")));
            } else if (key == "user-context") {
                // Skip user contexts.
                result->set(key, value);
            } else if (json_path.empty()) {
                // Passwords or secrets expected in this subtree.
                result->set(key, isc::data::copy(
                                     redactConfig(value, json_path)));
            } else if (key == json_path.front()) {
                // Passwords or secrets expected in this subtree.
                auto it(json_path.begin());
                std::advance(it, 1);
                list<string> new_json_path(it, json_path.end());
                result->set(key, isc::data::copy(
                                     redactConfig(value, new_json_path)));
            } else {
                // No passwords or secrets expected in this subtree.
                result->set(key, value);
            }
        }
    } else {
        return element;
    }

    return result;
}

} // namespace process
} // namespace isc
