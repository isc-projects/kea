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

#include <config/config_data.h>

#include <boost/foreach.hpp>

#include <string>
#include <iostream>

using namespace isc::data;

namespace isc {
namespace config {

//
// Return a part of a specification, as identified by the
// '/'-separated identifier.
// If it cannot be found, a DataNotFound error is thrown.
//
// Recursively goes through the Element. If it is a List,
// we search it contents to have 'items' (i.e. contain item_name)
// If it is a map, we search through the list contained in its
// 'map_item_spec' value. This code assumes the data has been
// validated and conforms to the specification.
static ConstElementPtr
find_spec_part(ConstElementPtr spec, const std::string& identifier) {
    //std::cout << "[XX] find_spec_part for " << identifier << std::endl;
    if (!spec) {
        isc_throw(DataNotFoundError, "Empty specification");
    }
    //std::cout << "in: " << std::endl << spec << std::endl;
    ConstElementPtr spec_part = spec;
    if (identifier == "") {
        isc_throw(DataNotFoundError, "Empty identifier");
    }
    std::string id = identifier;
    size_t sep = id.find('/');
    while(sep != std::string::npos) {
        std::string part = id.substr(0, sep);
        //std::cout << "[XX] id part: " << part << std::endl;
        if (spec_part->getType() == Element::list) {
            bool found = false;
            BOOST_FOREACH(ConstElementPtr list_el, spec_part->listValue()) {
                if (list_el->getType() == Element::map &&
                    list_el->contains("item_name") &&
                    list_el->get("item_name")->stringValue() == part) {
                    spec_part = list_el;
                    found = true;
                }
            }
            if (!found) {
                isc_throw(DataNotFoundError, identifier);
            }
        }
        id = id.substr(sep + 1);
        sep = id.find("/");
    }
    if (id != "" && id != "/") {
        if (spec_part->getType() == Element::list) {
            bool found = false;
            BOOST_FOREACH(ConstElementPtr list_el, spec_part->listValue()) {
                if (list_el->getType() == Element::map &&
                    list_el->contains("item_name") &&
                    list_el->get("item_name")->stringValue() == id) {
                    spec_part = list_el;
                    found = true;
                }
            }
            if (!found) {
                isc_throw(DataNotFoundError, identifier);
            }
        } else if (spec_part->getType() == Element::map) {
            if (spec_part->contains("map_item_spec")) {
                bool found = false;
                BOOST_FOREACH(ConstElementPtr list_el,
                              spec_part->get("map_item_spec")->listValue()) {
                    if (list_el->getType() == Element::map &&
                        list_el->contains("item_name") &&
                        list_el->get("item_name")->stringValue() == id) {
                        spec_part = list_el;
                        found = true;
                    }
                }
                if (!found) {
                    isc_throw(DataNotFoundError, identifier);
                }
            } else {
                isc_throw(DataNotFoundError, identifier);
            }
        }
    }
    //std::cout << "[XX] found spec part: " << std::endl << spec_part << std::endl;
    return (spec_part);
}

//
// Adds the names of the items in the given specification part.
// If recurse is true, maps will also have their children added.
// Result must be a ListElement
//
static void
spec_name_list(ElementPtr result, ConstElementPtr spec_part,
               const std::string& prefix, bool recurse = false)
{
    if (spec_part->getType() == Element::list) {
        BOOST_FOREACH(ConstElementPtr list_el, spec_part->listValue()) {
            if (list_el->getType() == Element::map &&
                list_el->contains("item_name")) {
                std::string new_prefix = prefix;
                if (prefix != "") {
                    new_prefix += "/";
                }
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
    } else if (spec_part->getType() == Element::map &&
               spec_part->contains("map_item_spec")) {
        spec_name_list(result, spec_part->get("map_item_spec"), prefix,
                       recurse);
    }
}

ConstElementPtr
ConfigData::getValue(const std::string& identifier) const {
    // 'fake' is set, but dropped by this function and
    // serves no further purpose.
    bool fake;
    return (getValue(fake, identifier));
}

ConstElementPtr
ConfigData::getValue(bool& is_default, const std::string& identifier) const {
    ConstElementPtr value = _config->find(identifier);
    if (value) {
        is_default = false;
    } else {
        ConstElementPtr spec_part =
            find_spec_part(_module_spec.getConfigSpec(), identifier);
        if (spec_part->contains("item_default")) {
            value = spec_part->get("item_default");
            is_default = true;
        } else {
            is_default = false;
            value = ElementPtr();
        }
    }
    return (value);
}

/// Returns an ElementPtr pointing to a ListElement containing
/// StringElements with the names of the options at the given
/// identifier. If recurse is true, maps will be expanded as well
ConstElementPtr
ConfigData::getItemList(const std::string& identifier, bool recurse) const {
    ElementPtr result = Element::createList();
    ConstElementPtr spec_part = getModuleSpec().getConfigSpec();
    if (identifier != "" && identifier != "/") {
        spec_part = find_spec_part(spec_part, identifier);
    }
    spec_name_list(result, spec_part, identifier, recurse);
    return (result);
}

/// Returns an ElementPtr containing a MapElement with identifier->value
/// pairs.
ConstElementPtr
ConfigData::getFullConfig() const {
    ElementPtr result = Element::createMap();
    ConstElementPtr items = getItemList("", true);
    BOOST_FOREACH(ConstElementPtr item, items->listValue()) {
        result->set(item->stringValue(), getValue(item->stringValue()));
    }
    return (result);
}

}
}
