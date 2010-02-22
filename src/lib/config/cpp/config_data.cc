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

ElementPtr
find_spec_part(ElementPtr spec, const std::string& identifier)
{
    //std::cout << "[XX] find_spec_part" << std::endl;
    if (!spec) { return ElementPtr(); }
    //std::cout << "in: " << spec << std::endl;
    ElementPtr spec_part = spec;
    if (identifier == "") {
        //std::cout << "[XX] empty id" << std::endl;
        return ElementPtr();
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
                    spec_part = list_el->get("item_name");
                    found = true;
                }
            }
            if (!found) {
                // raise exception?
                return ElementPtr();
            }
        } else if (spec_part->getType() == Element::map) {
            if (spec_part->contains("map_item_spec")) {
                bool found = false;
                BOOST_FOREACH(ElementPtr list_el, spec_part->get("map_item_spec")->listValue()) {
                    if (list_el->getType() == Element::map &&
                        list_el->contains("item_name") &&
                        list_el->get("item_name")->stringValue() == part) {
                        spec_part = list_el->get("item_name");
                        found = true;
                    }
                }
                if (!found) {
                    // raise exception?
                    return ElementPtr();
                }
            }
        }
        id = id.substr(sep + 1);
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
                // raise exception?
                return ElementPtr();
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
                    // raise exception?
                    return ElementPtr();
                }
            }
        }
    }
    return spec_part;
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
    if (!value) {
        ElementPtr spec_part = find_spec_part(_module_spec.getConfigSpec(), identifier);
        if (spec_part) {
            value = spec_part->get("item_default");
            is_default = true;
        } else {
            // we should raise an error here
            dns_throw(DataNotFoundError, "identifier not found");
        }
    } else {
        is_default = false;
    }
    return value;
}

void
spec_name_list(ElementPtr result, ElementPtr spec_part, std::string prefix, bool recurse = false)
{
    if (spec_part->getType() == Element::list) {
        BOOST_FOREACH(ElementPtr list_el, spec_part->listValue()) {
            if (list_el->getType() == Element::map &&
                list_el->contains("item_name")) {
                    result->add(Element::create(prefix + "/" + list_el->get("item_name")->stringValue()));
            }
        }
    } else if (spec_part->getType() == Element::map &&
               spec_part->contains("map_item_spec")
    ) {
        if (recurse) {
            spec_name_list(result, spec_part->get("map_item_spec"), prefix + "/" + spec_part->get("item_name")->stringValue(), recurse);
        } else {
            result->add(Element::create(prefix + "/" + spec_part->get("item_name")->stringValue()));
        }
    }
}

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

ElementPtr
ConfigData::getFullConfig()
{
    return ElementPtr();
}

}
}
