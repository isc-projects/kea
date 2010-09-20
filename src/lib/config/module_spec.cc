// Copyright (C) 2010  Internet Systems Consortium.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
// DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
// INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
// FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
// NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
// WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include <config/module_spec.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <cerrno>

#include <boost/foreach.hpp>

// todo: add more context to thrown ModuleSpecErrors?

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
        if (spec->get(name)->getType() == type) {
            return;
        } else {
            throw ModuleSpecError(name + " not of type " + Element::typeToName(type));
        }
    } else if (mandatory) {
        // todo: want parent item name, and perhaps some info about location
        // in list? or just catch and throw new...
        // or make this part non-throwing and check return value...
        throw ModuleSpecError(name + " missing in " + spec->str());
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
    // todo: add stuff for type map
    if (Element::nameToType(spec->get("item_type")->stringValue()) == Element::map) {
        check_leaf_item(spec, "map_item_spec", Element::list, true);
        check_config_item_list(spec->get("map_item_spec"));
    }
}

void
check_config_item_list(ConstElementPtr spec) {
    if (spec->getType() != Element::list) {
        throw ModuleSpecError("config_data is not a list of elements");
    }
    BOOST_FOREACH(ConstElementPtr item, spec->listValue()) {
        check_config_item(item);
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
        throw ModuleSpecError("commands is not a list of elements");
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
}

// checks whether the given element is a valid module specification
// throws a ModuleSpecError if the specification is bad
void
check_module_specification(ConstElementPtr def) {
    try {
        check_data_specification(def);
    } catch (TypeError te) {
        throw ModuleSpecError(te.what());
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
ModuleSpec::validate_config(ConstElementPtr data, const bool full) const {
    ConstElementPtr spec = module_specification->find("config_data");
    return (validate_spec_list(spec, data, full, ElementPtr()));
}

bool
ModuleSpec::validate_config(ConstElementPtr data, const bool full,
                            ElementPtr errors) const
{
    ConstElementPtr spec = module_specification->find("config_data");
    return (validate_spec_list(spec, data, full, errors));
}

ModuleSpec
moduleSpecFromFile(const std::string& file_name, const bool check)
                   throw(JSONError, ModuleSpecError)
{
    std::ifstream file;

    file.open(file_name.c_str());
    if (!file) {
        std::stringstream errs;
        errs << "Error opening " << file_name << ": " << strerror(errno);
        throw ModuleSpecError(errs.str());
    }

    ConstElementPtr module_spec_element = Element::fromJSON(file, file_name);
    if (module_spec_element->contains("module_spec")) {
        return (ModuleSpec(module_spec_element->get("module_spec"), check));
    } else {
        throw ModuleSpecError("No module_spec in specification");
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
        throw ModuleSpecError("No module_spec in specification");
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
            return (cur_item_type == "map");
            break;
    }
    return (false);
}
}

bool
ModuleSpec::validate_item(ConstElementPtr spec, ConstElementPtr data,
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
                if (!validate_item(list_spec, list_el, full, errors)) {
                    return (false);
                }
            }
        }
    }
    if (data->getType() == Element::map) {
        if (!validate_spec_list(spec->get("map_item_spec"), data, full, errors)) {
            return (false);
        }
    }
    return (true);
}

// spec is a map with item_name etc, data is a map
bool
ModuleSpec::validate_spec(ConstElementPtr spec, ConstElementPtr data,
                          const bool full, ElementPtr errors) const
{
    std::string item_name = spec->get("item_name")->stringValue();
    bool optional = spec->get("item_optional")->boolValue();
    ConstElementPtr data_el;
    data_el = data->get(item_name);
    
    if (data_el) {
        if (!validate_item(spec, data_el, full, errors)) {
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
ModuleSpec::validate_spec_list(ConstElementPtr spec, ConstElementPtr data,
                               const bool full, ElementPtr errors) const
{
    std::string cur_item_name;
    BOOST_FOREACH(ConstElementPtr cur_spec_el, spec->listValue()) {
        if (!validate_spec(cur_spec_el, data, full, errors)) {
            return (false);
        }
    }
    return (true);
}

}
}
