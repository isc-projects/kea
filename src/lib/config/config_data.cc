// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config/config_data.h>

#include <boost/foreach.hpp>

#include <string>
#include <iostream>

using namespace isc::data;

namespace {

// Returns the '_spec' part of a list or map specification (recursively,
// i.e. if it is a list of lists or maps, will return the spec of the
// inner-most list or map).
//
// \param spec_part the list or map specification (part)
// \return the value of spec_part's "list_item_spec" or "map_item_spec",
//         or the original spec_part, if it is not a MapElement or does
//         not contain "list_item_spec" or "map_item_spec"
ConstElementPtr findListOrMapSubSpec(ConstElementPtr spec_part) {
    while (spec_part->getType() == Element::map &&
           (spec_part->contains("list_item_spec") ||
            spec_part->contains("map_item_spec"))) {
        if (spec_part->contains("list_item_spec")) {
            spec_part = spec_part->get("list_item_spec");
        } else {
            spec_part = spec_part->get("map_item_spec");
        }
    }
    return spec_part;
}

// Returns a specific Element in a given specification ListElement
//
// \exception DataNotFoundError if the given identifier does not
// point to an existing element. Since we are dealing with the
// specification here, and not the config data itself, this should
// not happen, and is a code bug.
//
// \param spec_part ListElement to find the element in
// \param id_part the name of the element to find (must match the value
//                "item_name" in the list item
// \param id_full the full identifier id_part is a part of, this is
//                used to better report any errors
ConstElementPtr findItemInSpecList(ConstElementPtr spec_part,
                                   const std::string& id_part,
                                   const std::string& id_full)
{
    bool found = false;
    BOOST_FOREACH(ConstElementPtr list_el, spec_part->listValue()) {
        if (list_el->getType() == Element::map &&
            list_el->contains("item_name") &&
            list_el->get("item_name")->stringValue() == id_part) {
            spec_part = list_el;
            found = true;
        }
    }
    if (!found) {
        isc_throw(isc::config::DataNotFoundError,
                  id_part + " in " + id_full + " not found");
    }
    return (spec_part);
}

} // anonymous namespace

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
    if (!spec) {
        isc_throw(DataNotFoundError, "Empty specification");
    }

    ConstElementPtr spec_part = spec;
    if (identifier == "") {
        isc_throw(DataNotFoundError, "Empty identifier");
    }
    std::string id = identifier;
    size_t sep = id.find('/');
    while(sep != std::string::npos) {
        std::string part = id.substr(0, sep);

        if (spec_part->getType() == Element::list) {
            spec_part = findItemInSpecList(spec_part, part, identifier);
        } else {
            isc_throw(DataNotFoundError,
                      "Not a list of spec items: " + spec_part->str());
        }
        id = id.substr(sep + 1);
        sep = id.find("/");

        // As long as we are not in the 'final' element as specified
        // by the identifier, we want to automatically traverse list
        // and map specifications
        if (id != "" && id != "/") {
            spec_part = findListOrMapSubSpec(spec_part);
        }
    }
    if (id != "" && id != "/") {
        if (spec_part->getType() == Element::list) {
            spec_part = findItemInSpecList(spec_part, id, identifier);
        } else if (spec_part->getType() == Element::map) {
            if (spec_part->contains("map_item_spec")) {
                spec_part = findItemInSpecList(
                                spec_part->get("map_item_spec"),
                                id, identifier);
            } else {
                // Either we already have the element we are looking
                // for, or we are trying to reach something that does
                // not exist (i.e. the code does not match the spec)
                if (!spec_part->contains("item_name") ||
                    spec_part->get("item_name")->stringValue() != id) {
                    isc_throw(DataNotFoundError, "Element above " + id +
                                                 " in " + identifier +
                                                 " is not a map: " + spec_part->str());
                }
            }
        }
    }
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

ConstElementPtr
ConfigData::getDefaultValue(const std::string& identifier) const {
    ConstElementPtr spec_part =
        find_spec_part(_module_spec.getConfigSpec(), identifier);
    if (spec_part->contains("item_default")) {
        return spec_part->get("item_default");
    } else {
        isc_throw(DataNotFoundError, "No default for " + identifier);
    }
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
    ConstElementPtr items = getItemList("", false);
    BOOST_FOREACH(ConstElementPtr item, items->listValue()) {
        result->set(item->stringValue(), getValue(item->stringValue()));
    }
    return (result);
}

}
}
