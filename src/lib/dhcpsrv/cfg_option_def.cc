// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option_def.h>

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
    // Compareg that sizes are the same. If they hold different number of
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

    // Must not override standard option definition.
    } else if (((option_space == DHCP4_OPTION_SPACE) &&
                LibDHCP::isStandardOption(Option::V4, def->getCode()) &&
                LibDHCP::getOptionDef(Option::V4, def->getCode())) ||
               ((option_space == DHCP6_OPTION_SPACE) &&
                LibDHCP::isStandardOption(Option::V6, def->getCode()) &&
                LibDHCP::getOptionDef(Option::V6, def->getCode()))) {
        isc_throw(BadValue, "unable to override definition of option '"
                  << def->getCode() << "' in standard option space '"
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

} // end of namespace isc::dhcp
} // end of namespace isc
