// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option_def.h>
#include <sstream>

using namespace isc::data;

namespace isc {
namespace dhcp {

void
CfgOptionDef::copyTo(CfgOptionDef& new_config) const {
    // Remove any existing option definitions from the destination.
    new_config.option_definitions_.clearItems();
    const std::list<std::string>& names =
        option_definitions_.getOptionSpaceNames();
    for (std::list<std::string>::const_iterator name = names.begin();
         name != names.end(); ++name) {
        OptionDefContainerPtr defs = getAll(*name);
        for (OptionDefContainer::const_iterator def = defs->begin();
             def != defs->end(); ++def) {
            OptionDefinitionPtr new_def =
                OptionDefinitionPtr(new OptionDefinition(**def));
            new_config.add(new_def, *name);
        }
    }
}

bool
CfgOptionDef::equals(const CfgOptionDef& other) const {
    // Get our option space names.
    const std::list<std::string>& names = option_definitions_.getOptionSpaceNames();
    // Get option space names held by the other object.
    const std::list<std::string>&
        other_names = other.option_definitions_.getOptionSpaceNames();
    // Compare that sizes are the same. If they hold different number of
    // option space names the objects are not equal.
    if (names.size() != other_names.size()) {
        return (false);
    }
    // Iterate over all option space names and get the definitions for each
    // of them.
    for (std::list<std::string>::const_iterator name = names.begin();
         name != names.end(); ++name) {
        // Get all definitions.
        OptionDefContainerPtr defs = getAll(*name);
        OptionDefContainerPtr other_defs = other.getAll(*name);
        // Compare sizes. If they hold different number of definitions,
        // they are unequal.
        if (defs->size() != defs->size()) {
            return (false);
        }
        // For each option definition, try to find one in the other object.
        for (OptionDefContainer::const_iterator def = defs->begin();
             def != defs->end(); ++def) {
            OptionDefinitionPtr
                other_def = other.get(*name, (*def)->getCode());
            // Actually compare them.
            if (!other_def || (*other_def != **def)) {
                return (false);
            }
        }
    }

    // All checks passed.
    return (true);
}

void
CfgOptionDef::add(const OptionDefinitionPtr& def,
                  const std::string& option_space) {
    if (!OptionSpace::validateName(option_space)) {
        isc_throw(BadValue, "invalid option space name '"
                  << option_space << "'");

    // Option definition being added must be a valid pointer.
    } else if (!def) {
        isc_throw(MalformedOptionDefinition,
                  "option definition must not be NULL");
    // Must not duplicate an option definition.
    } else if (get(option_space, def->getCode())) {
        isc_throw(DuplicateOptionDefinition, "option definition with code '"
                  << def->getCode() << "' already exists in option"
                  " space '" << option_space << "'");
    } else if (get(option_space, def->getName())) {
        isc_throw(DuplicateOptionDefinition, "option definition with name '"
                  << def->getName() << "' already exists in option"
                  " space '" << option_space << "'");

    // Must not override standard option definition.
    } else if (LibDHCP::getOptionDef(option_space, def->getCode())) {
        isc_throw(BadValue, "unable to override definition of option '"
                  << def->getCode() << "' in standard option space '"
                  << option_space << "'");
    } else if (LibDHCP::getOptionDef(option_space, def->getName())) {
        isc_throw(BadValue, "unable to override definition of option '"
                  << def->getName() << "' in standard option space '"
                  << option_space << "'");
    }
    // Add the definition.
    option_definitions_.addItem(def, option_space);
}

OptionDefContainerPtr
CfgOptionDef::getAll(const std::string& option_space) const {
    /// @todo Does option space require any validation here?
    return (option_definitions_.getItems(option_space));
}

OptionDefinitionPtr
CfgOptionDef::get(const std::string& option_space,
                  const uint16_t option_code) const {
    // Get the pointer to collection of the option definitions that belong
    // to the particular option space.
    OptionDefContainerPtr defs = getAll(option_space);
    // If there are any option definitions for this option space, get the
    // one that has the specified option code.
    if (defs && !defs->empty()) {
        const OptionDefContainerTypeIndex& idx = defs->get<1>();
        const OptionDefContainerTypeRange& range = idx.equal_range(option_code);
        // If there is more than one definition matching the option code,
        // return the first one. In fact, it shouldn't happen that we have
        // more than one because we check for duplicates when we add them.
        if (std::distance(range.first, range.second) > 0) {
            return (*range.first);
        }
    }
    // Nothing found. Return NULL pointer.
    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
CfgOptionDef::get(const std::string& option_space,
                  const std::string& option_name) const {
    // Get the pointer to collection of the option definitions that belong
    // to the particular option space.
    OptionDefContainerPtr defs = getAll(option_space);
    // If there are any option definitions for this option space, get the
    // one that has the specified option name.
    if (defs && !defs->empty()) {
        const OptionDefContainerNameIndex& idx = defs->get<2>();
        const OptionDefContainerNameRange& range = idx.equal_range(option_name);
        // If there is more than one definition matching the option name,
        // return the first one. In fact, it shouldn't happen that we have
        // more than one because we check for duplicates when we add them.
        if (std::distance(range.first, range.second) > 0) {
            return (*range.first);
        }
    }
    // Nothing found. Return NULL pointer.
    return (OptionDefinitionPtr());
}

uint64_t
CfgOptionDef::del(const uint64_t id) {
    return (option_definitions_.deleteItems(id));
}

ElementPtr
CfgOptionDef::toElement() const {
    return (toElementWithMetadata(false));
}

ElementPtr
CfgOptionDef::toElementWithMetadata(const bool include_metadata) const {
    // option-defs value is a list of maps
    ElementPtr result = Element::createList();
    // Iterate through the container by names and definitions
    const std::list<std::string>& names =
        option_definitions_.getOptionSpaceNames();
    for (std::list<std::string>::const_iterator name = names.begin();
         name != names.end(); ++name) {
        OptionDefContainerPtr defs = getAll(*name);
        for (OptionDefContainer::const_iterator def = defs->begin();
             def != defs->end(); ++def) {
            // Get and fill the map for this definition
            ElementPtr map = Element::createMap();
            // Set user context
            (*def)->contextToElement(map);
            // Set space from parent iterator
            map->set("space", Element::create(*name));
            // Set required items: name, code and type
            map->set("name", Element::create((*def)->getName()));
            map->set("code", Element::create((*def)->getCode()));
            std::string data_type =
                OptionDataTypeUtil::getDataTypeName((*def)->getType());
            map->set("type", Element::create(data_type));
            // Set the array type
            bool array_type = (*def)->getArrayType();
            map->set("array", Element::create(array_type));
            // Set the encapsulate space
            std::string encapsulates = (*def)->getEncapsulatedSpace();
            map->set("encapsulate", Element::create(encapsulates));
            // Set the record field types
            OptionDefinition::RecordFieldsCollection fields =
                (*def)->getRecordFields();
            if (!fields.empty()) {
                std::ostringstream oss;
                for (OptionDefinition::RecordFieldsCollection::const_iterator
                         field = fields.begin();
                     field != fields.end(); ++field) {
                    if (field != fields.begin()) {
                        oss << ", ";
                    }
                    oss << OptionDataTypeUtil::getDataTypeName(*field);
                }
                map->set("record-types", Element::create(oss.str()));
            } else {
                map->set("record-types", Element::create(std::string()));
            }

            // Include metadata if requested.
            if (include_metadata) {
                map->set("metadata", (*def)->getMetadata());
            }

            // Push on the list
            result->add(map);
        }
    }
    return (result);
}

void
CfgOptionDef::merge(CfgOptionDef& other) {
    // The definitions in "other" are presumed to be valid and
    // not in conflict with standard definitions.
    if (other.getContainer().getOptionSpaceNames().empty()) {
        // Nothing to merge, don't waste cycles.
        return;
    }

    // Iterate over this config's definitions in each space.
    // If either a definition's name or code already exist in
    // that space in "other", skip it.  Otherwise, add it to "other".
    for (auto space : option_definitions_.getOptionSpaceNames()) {
        for (auto my_def : *(getAll(space))) {
            if ((other.get(space, my_def->getName())) ||
                (other.get(space, my_def->getCode()))) {
                // Already in "other" so skip it.
                continue;
            }

            // Not in "other" so add it.
            other.add(my_def, space);
        }
    }

    // Replace the current definitions with the merged set.
    other.copyTo(*this);
}

} // end of namespace isc::dhcp
} // end of namespace isc
