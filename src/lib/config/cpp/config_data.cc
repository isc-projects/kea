// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include "config_data.h"

#include <boost/foreach.hpp>

#include <string>
#include <iostream>

using namespace isc::data;

namespace isc {
namespace config {

static ElementPtr
find_spec_part(ElementPtr spec, const std::string& identifier)
{
    //std::cout << "[XX] find_spec_part for " << identifier << std::endl;
    if (!spec) { return ElementPtr(); }
    //std::cout << "in: " << std::endl << spec << std::endl;
    ElementPtr spec_part = spec;
    if (identifier == "") {
        dns_throw(DataNotFoundError, "Empty identifier");
    }
    std::string id = identifier;
    size_t sep = id.find('/');
    while(sep != std::string::npos) {
        std::string part = id.substr(0, sep);
        //std::cout << "[XX] id part: " << part << std::endl;
        if (spec_part->getType() == Element::list) {
            bool found = false;
            BOOST_FOREACH(ElementPtr list_el, spec_part->listValue()) {
                if (list_el->getType() == Element::map &&
                    list_el->contains("item_name") &&
                    list_el->get("item_name")->stringValue() == part) {
                    spec_part = list_el;
                    found = true;
                }
            }
            if (!found) {
                dns_throw(DataNotFoundError, identifier);
            }
        }
        id = id.substr(sep + 1);
        sep = id.find("/");
    }
    if (id != "" && id != "/") {
        if (spec_part->getType() == Element::list) {
            bool found = false;
            BOOST_FOREACH(ElementPtr list_el, spec_part->listValue()) {
                if (list_el->getType() == Element::map &&
                    list_el->contains("item_name") &&
                    list_el->get("item_name")->stringValue() == id) {
                    spec_part = list_el;
                    found = true;
                }
            }
            if (!found) {
                dns_throw(DataNotFoundError, identifier);
            }
        } else if (spec_part->getType() == Element::map) {
            if (spec_part->contains("map_item_spec")) {
                bool found = false;
                BOOST_FOREACH(ElementPtr list_el, spec_part->get("map_item_spec")->listValue()) {
                    if (list_el->getType() == Element::map &&
                        list_el->contains("item_name") &&
                        list_el->get("item_name")->stringValue() == id) {
                        spec_part = list_el;
                        found = true;
                    }
                }
                if (!found) {
                    dns_throw(DataNotFoundError, identifier);
                }
            } else {
                dns_throw(DataNotFoundError, identifier);
            }
        }
    }
    //std::cout << "[XX] found spec part: " << std::endl << spec_part << std::endl;
    return spec_part;
}

static void
spec_name_list(ElementPtr result, ElementPtr spec_part, std::string prefix, bool recurse = false)
{
    if (spec_part->getType() == Element::list) {
        BOOST_FOREACH(ElementPtr list_el, spec_part->listValue()) {
            if (list_el->getType() == Element::map &&
                list_el->contains("item_name")) {
                std::string new_prefix = prefix;
                if (prefix != "") { new_prefix += "/"; }
                new_prefix += list_el->get("item_name")->stringValue();
                if (recurse && list_el->get("item_type")->stringValue() == "map") {
                    spec_name_list(result, list_el->get("map_item_spec"), new_prefix, recurse);
                } else {
                    if (list_el->get("item_type")->stringValue() == "map" ||
                        list_el->get("item_type")->stringValue() == "list"
                    ) {
                        new_prefix += "/";
                    }
                    result->add(Element::create(new_prefix));
                }
            }
        }
    } else if (spec_part->getType() == Element::map && spec_part->contains("map_item_spec")) {
        spec_name_list(result, spec_part->get("map_item_spec"), prefix, recurse);
    }
}

ElementPtr
ConfigData::getValue(const std::string& identifier)
{
    bool fake;
    return getValue(fake, identifier);
}

ElementPtr
ConfigData::getValue(bool& is_default, const std::string& identifier)
{
    ElementPtr value = _config->find(identifier);
    if (value) {
        is_default = false;
    } else {
        ElementPtr spec_part = find_spec_part(_module_spec.getConfigSpec(), identifier);
        if (spec_part->contains("item_default")) {
            value = spec_part->get("item_default");
            is_default = true;
        } else {
            is_default = false;
            value = ElementPtr();
        }
    }
    return value;
}

/// Returns an ElementPtr pointing to a ListElement containing
/// StringElements with the names of the options at the given
/// identifier. If recurse is true, maps will be expanded as well
ElementPtr
ConfigData::getItemList(const std::string& identifier, bool recurse)
{
    ElementPtr result = Element::createFromString("[]");
    ElementPtr spec_part = getModuleSpec().getConfigSpec();
    if (identifier != "" && identifier != "/") {
        spec_part = find_spec_part(spec_part, identifier);
    }
    spec_name_list(result, spec_part, identifier, recurse);
    return result;
}

/// Returns an ElementPtr containing a MapElement with identifier->value
/// pairs.
ElementPtr
ConfigData::getFullConfig()
{
    ElementPtr result = Element::createFromString("{}");
    ElementPtr items = getItemList("", true);
    BOOST_FOREACH(ElementPtr item, items->listValue()) {
        result->set(item->stringValue(), getValue(item->stringValue()));
    }
    return result;
}

}
}
