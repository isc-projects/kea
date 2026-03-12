// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <process/redact_config.h>

#include <boost/algorithm/string.hpp>

using namespace isc;
using namespace isc::data;
using namespace std;

namespace {

template <typename ElementPtrType>
ElementPtrType
    redact(ElementPtrType const& element, list<string> json_path,
           string obscure, unsigned level) {
    if (!element) {
        isc_throw(BadValue, "redact() got a null pointer");
    }
    if (level == 0) {
        isc_throw(BadValue, "redact() elements nested too deeply");
    }

    string const next_key(json_path.empty() ? string() : json_path.front());
    ElementPtr result;
    if (element->getType() == Element::list) {
        // If we are looking for a list...
        if (next_key == "*" || next_key == "[]") {
            // But if we are looking specifically for a list...
            if (next_key == "[]") {
                // Then advance in the path.
                json_path.pop_front();
            }
            // Then redact all children.
            result = Element::createList();
            for (ElementPtr const& child : element->listValue()) {
                result->add(redact(child, json_path, obscure, level - 1));
            }
            return (result);
        }
    } else if (element->getType() == Element::map) {
        // If we are looking for anything or if we have reached the end of a
        /// path...
        if (next_key == "*" || json_path.empty()) {
            // Then iterate through all the children.
            result = Element::createMap();
            for (auto const& kv : element->mapValue()) {
                std::string const& key(kv.first);
                ConstElementPtr const& value(kv.second);

                if (boost::algorithm::ends_with(key, "password") ||
                    boost::algorithm::ends_with(key, "secret")) {
                    // Sensitive data
                    result->set(key, Element::create(obscure));
                } else if (key == "user-context") {
                    // Skip user contexts.
                    result->set(key, value);
                } else {
                    if (json_path.empty()) {
                        // End of path means no sensitive data expected in this
                        // subtree, so we stop here.
                        result->set(key, value);
                    } else {
                        // We are looking for anything '*' so redact further.
                        result->set(key, redact(value, json_path, obscure,
                                                level - 1));
                    }
                }
            }
            return (result);
        } else {
            ConstElementPtr child(element->get(next_key));
            if (child) {
                result = isc::data::copy(element, 1U);
                json_path.pop_front();
                result->set(next_key,
                            redact(child, json_path, obscure, level - 1));
                return (result);
            }
        }
    }

    return (element);
}

}  // namespace

namespace isc {
namespace process {

ConstElementPtr
redactConfig(ConstElementPtr const& element, list<string> const& json_path,
             string obscure, unsigned max_nesting_depth) {
    return (redact(element, json_path, obscure, max_nesting_depth));
}

}  // namespace process
}  // namespace isc
