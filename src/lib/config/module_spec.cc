// Copyright (C) 2010-2015 Internet Systems Consortium.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config/module_spec.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <cerrno>

#include <boost/foreach.hpp>

// todo: add more context to thrown ModuleSpecErrors?

using namespace isc::data;
using namespace isc::config;

namespace {
//
// Private functions
//

void
check_leaf_item(ConstElementPtr spec, const std::string& name,
                Element::types type, bool mandatory)
{
    if (spec->contains(name)) {
        if (type == Element::any || spec->get(name)->getType() == type) {
            return;
        } else {
            isc_throw(ModuleSpecError,
                      name + " not of type " + Element::typeToName(type));
        }
    } else if (mandatory) {
        // todo: want parent item name, and perhaps some info about location
        // in list? or just catch and throw new...
        // or make this part non-throwing and check return value...
        isc_throw(ModuleSpecError, name + " missing in " + spec->str());
    }
}

void check_config_item_list(ConstElementPtr spec);

void
check_config_item(ConstElementPtr spec) {
    check_leaf_item(spec, "item_name", Element::string, true);
    check_leaf_item(spec, "item_type", Element::string, true);
    check_leaf_item(spec, "item_optional", Element::boolean, true);
    check_leaf_item(spec, "item_default",
                    Element::nameToType(spec->get("item_type")->stringValue()),
                    !spec->get("item_optional")->boolValue()
                   );

    // if list, check the list specification
    if (Element::nameToType(spec->get("item_type")->stringValue()) == Element::list) {
        check_leaf_item(spec, "list_item_spec", Element::map, true);
        check_config_item(spec->get("list_item_spec"));
    }

    if (spec->get("item_type")->stringValue() == "map") {
        check_leaf_item(spec, "map_item_spec", Element::list, true);
        check_config_item_list(spec->get("map_item_spec"));
    } else if (spec->get("item_type")->stringValue() == "named_set") {
        check_leaf_item(spec, "named_set_item_spec", Element::map, true);
        check_config_item(spec->get("named_set_item_spec"));
    }
}

void
check_config_item_list(ConstElementPtr spec) {
    if (spec->getType() != Element::list) {
        isc_throw(ModuleSpecError, "config_data is not a list of elements");
    }
    BOOST_FOREACH(ConstElementPtr item, spec->listValue()) {
        check_config_item(item);
    }
}

// checks whether the given element is a valid statistics specification
// returns false if the specification is bad
bool
check_format(ConstElementPtr value, ConstElementPtr format_name) {
    typedef std::map<std::string, std::string> format_types;
    format_types time_formats;
    // TODO: should be added other format types if necessary
    time_formats.insert(
        format_types::value_type("date-time", "%Y-%m-%dT%H:%M:%SZ") );
    time_formats.insert(
        format_types::value_type("date", "%Y-%m-%d") );
    time_formats.insert(
        format_types::value_type("time", "%H:%M:%S") );
    BOOST_FOREACH (const format_types::value_type& f, time_formats) {
        if (format_name->stringValue() == f.first) {
            struct tm tm;
            std::vector<char> buf(32);
            memset(&tm, 0, sizeof(tm));
            // reverse check
            return (strptime(value->stringValue().c_str(),
                             f.second.c_str(), &tm) != NULL
                    && strftime(&buf[0], buf.size(),
                                f.second.c_str(), &tm) != 0
                    && strncmp(value->stringValue().c_str(),
                               &buf[0], buf.size()) == 0);
        }
    }
    return (false);
}

void check_statistics_item_list(ConstElementPtr spec);

void
check_statistics_item_list(ConstElementPtr spec) {
    if (spec->getType() != Element::list) {
        isc_throw(ModuleSpecError, "statistics is not a list of elements");
    }
    BOOST_FOREACH(ConstElementPtr item, spec->listValue()) {
        check_config_item(item);
        // additional checks for statistics
        check_leaf_item(item, "item_title", Element::string, true);
        check_leaf_item(item, "item_description", Element::string, true);
        check_leaf_item(item, "item_format", Element::string, false);
        // checks name of item_format and validation of item_default
        if (item->contains("item_format")
            && item->contains("item_default")) {
            if(!check_format(item->get("item_default"),
                             item->get("item_format"))) {
                isc_throw(ModuleSpecError,
                    "item_default not valid type of item_format");
            }
        }
    }
}

void
check_command(ConstElementPtr spec) {
    check_leaf_item(spec, "command_name", Element::string, true);
    check_leaf_item(spec, "command_args", Element::list, true);
    check_config_item_list(spec->get("command_args"));
}

void
check_command_list(ConstElementPtr spec) {
    if (spec->getType() != Element::list) {
        isc_throw(ModuleSpecError, "commands is not a list of elements");
    }
    BOOST_FOREACH(ConstElementPtr item, spec->listValue()) {
        check_command(item);
    }
}

void
check_data_specification(ConstElementPtr spec) {
    check_leaf_item(spec, "module_name", Element::string, true);
    check_leaf_item(spec, "module_description", Element::string, false);
    // config_data is not mandatory; module could just define
    // commands and have no config
    if (spec->contains("config_data")) {
        check_config_item_list(spec->get("config_data"));
    }
    if (spec->contains("commands")) {
        check_command_list(spec->get("commands"));
    }
    if (spec->contains("statistics")) {
        check_statistics_item_list(spec->get("statistics"));
    }
}

// checks whether the given element is a valid module specification
// throws a ModuleSpecError if the specification is bad
void
check_module_specification(ConstElementPtr def) {
    try {
        check_data_specification(def);
    } catch (const TypeError& te) {
        isc_throw(ModuleSpecError, te.what());
    }
}
}

namespace isc {
namespace config {
//
// Public functions
//

ModuleSpec::ModuleSpec(ConstElementPtr module_spec_element,
                       const bool check)
                       throw(ModuleSpecError)
                       
{
    module_specification = module_spec_element;
    if (check) {
        check_module_specification(module_specification);
    }
}

ConstElementPtr
ModuleSpec::getCommandsSpec() const {
    if (module_specification->contains("commands")) {
        return (module_specification->get("commands"));
    } else {
        return (ElementPtr());
    }
}

ConstElementPtr
ModuleSpec::getConfigSpec() const {
    if (module_specification->contains("config_data")) {
        return (module_specification->get("config_data"));
    } else {
        return (ElementPtr());
    }
}

ConstElementPtr
ModuleSpec::getStatisticsSpec() const {
    if (module_specification->contains("statistics")) {
        return (module_specification->get("statistics"));
    } else {
        return (ElementPtr());
    }
}

const std::string
ModuleSpec::getModuleName() const {
    return (module_specification->get("module_name")->stringValue());
}

const std::string
ModuleSpec::getModuleDescription() const {
    if (module_specification->contains("module_description")) {
        return (module_specification->get("module_description")->stringValue());
    } else {
        return (std::string(""));
    }
}

bool
ModuleSpec::validateConfig(ConstElementPtr data, const bool full) const {
    ConstElementPtr spec = module_specification->find("config_data");
    return (validateSpecList(spec, data, full, ElementPtr()));
}

bool
ModuleSpec::validateStatistics(ConstElementPtr data, const bool full) const {
    ConstElementPtr spec = module_specification->find("statistics");
    return (validateSpecList(spec, data, full, ElementPtr()));
}

bool
ModuleSpec::validateCommand(const std::string& command,
                             ConstElementPtr args,
                             ElementPtr errors) const
{
    if (args->getType() != Element::map) {
        errors->add(Element::create("args for command " +
                                    command + " is not a map"));
        return (false);
    }

    ConstElementPtr commands_spec = module_specification->find("commands");
    if (!commands_spec) {
        // there are no commands according to the spec.
        errors->add(Element::create("The given module has no commands"));
        return (false);
    }

    BOOST_FOREACH(ConstElementPtr cur_command, commands_spec->listValue()) {
        if (cur_command->get("command_name")->stringValue() == command) {
            return (validateSpecList(cur_command->get("command_args"),
                                       args, true, errors));
        }
    }

    // this command is unknown
    errors->add(Element::create("Unknown command " + command));
    return (false);
}

bool
ModuleSpec::validateConfig(ConstElementPtr data, const bool full,
                            ElementPtr errors) const
{
    ConstElementPtr spec = module_specification->find("config_data");
    return (validateSpecList(spec, data, full, errors));
}

bool
ModuleSpec::validateStatistics(ConstElementPtr data, const bool full,
                               ElementPtr errors) const
{
    ConstElementPtr spec = module_specification->find("statistics");
    return (validateSpecList(spec, data, full, errors));
}

ModuleSpec
moduleSpecFromFile(const std::string& file_name, const bool check)
                   throw(JSONError, ModuleSpecError)
{
    std::ifstream file;

    // zero out the errno to be safe
    errno = 0;

    file.open(file_name.c_str());
    if (!file) {
        std::stringstream errs;
        errs << "Error opening " << file_name << ": " << strerror(errno);
        isc_throw(ModuleSpecError, errs.str());
    }

    ConstElementPtr module_spec_element = Element::fromJSON(file, file_name);
    if (module_spec_element->contains("module_spec")) {
        return (ModuleSpec(module_spec_element->get("module_spec"), check));
    } else {
        isc_throw(ModuleSpecError, "No module_spec in specification");
    }
}

ModuleSpec
moduleSpecFromFile(std::ifstream& in, const bool check)
                   throw(JSONError, ModuleSpecError)
{
    ConstElementPtr module_spec_element = Element::fromJSON(in);
    if (module_spec_element->contains("module_spec")) {
        return (ModuleSpec(module_spec_element->get("module_spec"), check));
    } else {
        isc_throw(ModuleSpecError, "No module_spec in specification");
    }
}


namespace {
//
// private functions
//

//
// helper functions for validation
//
bool
check_type(ConstElementPtr spec, ConstElementPtr element) {
    std::string cur_item_type;
    cur_item_type = spec->get("item_type")->stringValue();
    if (cur_item_type == "any") {
        return (true);
    }
    switch (element->getType()) {
        case Element::integer:
            return (cur_item_type == "integer");
            break;
        case Element::real:
            return (cur_item_type == "real");
            break;
        case Element::boolean:
            return (cur_item_type == "boolean");
            break;
        case Element::string:
            return (cur_item_type == "string");
            break;
        case Element::list:
            return (cur_item_type == "list");
            break;
        case Element::map:
            return (cur_item_type == "map" ||
                    cur_item_type == "named_set");
            break;
    }
    return (false);
}
}

bool
ModuleSpec::validateItem(ConstElementPtr spec, ConstElementPtr data,
                          const bool full, ElementPtr errors) const
{
    if (!check_type(spec, data)) {
        // we should do some proper error feedback here
        // std::cout << "type mismatch; not " << spec->get("item_type") << ": " << data << std::endl;
        // std::cout << spec << std::endl;
        if (errors) {
            errors->add(Element::create("Type mismatch"));
        }
        return (false);
    }
    if (data->getType() == Element::list) {
        ConstElementPtr list_spec = spec->get("list_item_spec");
        BOOST_FOREACH(ConstElementPtr list_el, data->listValue()) {
            if (!check_type(list_spec, list_el)) {
                if (errors) {
                    errors->add(Element::create("Type mismatch"));
                }
                return (false);
            }
            if (list_spec->get("item_type")->stringValue() == "map") {
                if (!validateItem(list_spec, list_el, full, errors)) {
                    return (false);
                }
            }
        }
    }
    if (data->getType() == Element::map) {
        // either a normal 'map' or a 'named set' (determined by which
        // subspecification it has)
        if (spec->contains("map_item_spec")) {
            if (!validateSpecList(spec->get("map_item_spec"), data, full, errors)) {
                return (false);
            }
        } else {
            typedef std::pair<std::string, ConstElementPtr> maptype;

            BOOST_FOREACH(maptype m, data->mapValue()) {
                if (!validateItem(spec->get("named_set_item_spec"), m.second, full, errors)) {
                    return (false);
                }
            }
        }
    }
    if (spec->contains("item_format")) {
        if (!check_format(data, spec->get("item_format"))) {
            if (errors) {
                errors->add(Element::create("Format mismatch"));
            }
            return (false);
        }
    }
    return (true);
}

// spec is a map with item_name etc, data is a map
bool
ModuleSpec::validateSpec(ConstElementPtr spec, ConstElementPtr data,
                          const bool full, ElementPtr errors) const
{
    std::string item_name = spec->get("item_name")->stringValue();
    bool optional = spec->get("item_optional")->boolValue();
    ConstElementPtr data_el;
    data_el = data->get(item_name);
    
    if (data_el) {
        if (!validateItem(spec, data_el, full, errors)) {
            return (false);
        }
    } else {
        if (!optional && full) {
            if (errors) {
                errors->add(Element::create("Non-optional value missing"));
            }
            return (false);
        }
    }
    return (true);
}

// spec is a list of maps, data is a map
bool
ModuleSpec::validateSpecList(ConstElementPtr spec, ConstElementPtr data,
                               const bool full, ElementPtr errors) const
{
    bool validated = true;
    BOOST_FOREACH(ConstElementPtr cur_spec_el, spec->listValue()) {
        if (!validateSpec(cur_spec_el, data, full, errors)) {
            validated = false;
        }
    }

    typedef std::pair<std::string, ConstElementPtr> maptype;
    
    BOOST_FOREACH(maptype m, data->mapValue()) {
        // Ignore 'version' as a config element
        if (m.first.compare("version") != 0) {
            bool found = false;
            BOOST_FOREACH(ConstElementPtr cur_spec_el, spec->listValue()) {
                if (cur_spec_el->get("item_name")->stringValue().compare(m.first) == 0) {
                    found = true;
                }
            }
            if (!found) {
                validated = false;
                if (errors) {
                    errors->add(Element::create("Unknown item " + m.first));
                }
            }
        }
    }

    return (validated);
}

}
}
