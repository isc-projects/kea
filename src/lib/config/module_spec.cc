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

#include "module_spec.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <cerrno>

#include <boost/foreach.hpp>

// todo: add more context to thrown ModuleSpecErrors?

namespace isc {
namespace config {

//
// static functions
//

// todo: is there a direct way to get a std::string from an enum label?
static std::string
getType_string(Element::types type)
{
    switch(type) {
    case Element::integer:
        return std::string("integer");
    case Element::real:
        return std::string("real");
    case Element::boolean:
        return std::string("boolean");
    case Element::string:
        return std::string("string");
    case Element::list:
        return std::string("list");
    case Element::map:
        return std::string("map");
    default:
        return std::string("unknown");
    }
}

static Element::types
getType_value(const std::string& type_name) {
    if (type_name == "integer") {
        return Element::integer;
    } else if (type_name == "real") {
        return Element::real;
    } else if (type_name == "boolean") {
        return Element::boolean;
    } else if (type_name == "string") {
        return Element::string;
    } else if (type_name == "list") {
        return Element::list;
    } else if (type_name == "map") {
        return Element::map;
    } else if (type_name == "any") {
        return Element::any;
    } else {
        throw ModuleSpecError(type_name + " is not a valid type name");
    }
}

static void
check_leaf_item(const ElementPtr& spec, const std::string& name, Element::types type, bool mandatory)
{
    if (spec->contains(name)) {
        if (spec->get(name)->getType() == type) {
            return;
        } else {
            throw ModuleSpecError(name + " not of type " + getType_string(type));
        }
    } else if (mandatory) {
        // todo: want parent item name, and perhaps some info about location
        // in list? or just catch and throw new...
        // or make this part non-throwing and check return value...
        throw ModuleSpecError(name + " missing in " + spec->str());
    }
}

static void check_config_item_list(const ElementPtr& spec);

static void
check_config_item(const ElementPtr& spec) {
    check_leaf_item(spec, "item_name", Element::string, true);
    check_leaf_item(spec, "item_type", Element::string, true);
    check_leaf_item(spec, "item_optional", Element::boolean, true);
    check_leaf_item(spec, "item_default",
                    getType_value(spec->get("item_type")->stringValue()),
                    !spec->get("item_optional")->boolValue()
                   );

    // if list, check the list specification
    if (getType_value(spec->get("item_type")->stringValue()) == Element::list) {
        check_leaf_item(spec, "list_item_spec", Element::map, true);
        check_config_item(spec->get("list_item_spec"));
    }
    // todo: add stuff for type map
    if (getType_value(spec->get("item_type")->stringValue()) == Element::map) {
        check_leaf_item(spec, "map_item_spec", Element::list, true);
        check_config_item_list(spec->get("map_item_spec"));
    }
}

static void
check_config_item_list(const ElementPtr& spec) {
    if (spec->getType() != Element::list) {
        throw ModuleSpecError("config_data is not a list of elements");
    }
    BOOST_FOREACH(ElementPtr item, spec->listValue()) {
        check_config_item(item);
    }
}

static void
check_command(const ElementPtr& spec) {
    check_leaf_item(spec, "command_name", Element::string, true);
    check_leaf_item(spec, "command_args", Element::list, true);
    check_config_item_list(spec->get("command_args"));
}

static void
check_command_list(const ElementPtr& spec) {
    if (spec->getType() != Element::list) {
        throw ModuleSpecError("commands is not a list of elements");
    }
    BOOST_FOREACH(ElementPtr item, spec->listValue()) {
        check_command(item);
    }
}

static void
check_data_specification(const ElementPtr& spec) {
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
static void
check_module_specification(const ElementPtr& def)
{
    check_data_specification(def);
}

//
// Public functions
//

ModuleSpec::ModuleSpec(ElementPtr module_spec_element,
                       const bool check)
                       throw(ModuleSpecError)
                       
{
    module_specification = module_spec_element;
    if (check) {
        check_module_specification(module_specification);
    }
}

const ElementPtr
ModuleSpec::getCommandsSpec() const
{
    if (module_specification->contains("commands")) {
        return module_specification->get("commands");
    } else {
        return ElementPtr();
    }
}

const ElementPtr
ModuleSpec::getConfigSpec() const
{
    if (module_specification->contains("config_data")) {
        return module_specification->get("config_data");
    } else {
        return ElementPtr();
    }
}

const std::string
ModuleSpec::getModuleName() const
{
    return module_specification->get("module_name")->stringValue();
}

const std::string
ModuleSpec::getModuleDescription() const
{
    if (module_specification->contains("module_description")) {
        return module_specification->get("module_description")->stringValue();
    } else {
        return std::string("");
    }
}

bool
ModuleSpec::validate_config(const ElementPtr data, const bool full)
{
    ElementPtr spec = module_specification->find("config_data");
    return validate_spec_list(spec, data, full, ElementPtr());
}

bool
ModuleSpec::validate_config(const ElementPtr data, const bool full, ElementPtr errors)
{
    ElementPtr spec = module_specification->find("config_data");
    return validate_spec_list(spec, data, full, errors);
}

ModuleSpec
moduleSpecFromFile(const std::string& file_name, const bool check)
                   throw(ParseError, ModuleSpecError)
{
    std::ifstream file;

    file.open(file_name.c_str());
    if (!file) {
        std::stringstream errs;
        errs << "Error opening " << file_name << ": " << strerror(errno);
        throw ModuleSpecError(errs.str());
    }

    ElementPtr module_spec_element = Element::fromJSON(file, file_name);
    if (module_spec_element->contains("module_spec")) {
        return ModuleSpec(module_spec_element->get("module_spec"), check);
    } else {
        throw ModuleSpecError("No module_spec in specification");
    }
}

ModuleSpec
moduleSpecFromFile(std::ifstream& in, const bool check)
                   throw(ParseError, ModuleSpecError) {
    ElementPtr module_spec_element = Element::fromJSON(in);
    if (module_spec_element->contains("module_spec")) {
        return ModuleSpec(module_spec_element->get("module_spec"), check);
    } else {
        throw ModuleSpecError("No module_spec in specification");
    }
}


//
// private functions
//

//
// helper functions for validation
//
static bool
check_type(ElementPtr spec, ElementPtr element)
{
    std::string cur_item_type;
    cur_item_type = spec->get("item_type")->stringValue();
    if (cur_item_type == "any") {
        return true;
    }
    switch (element->getType()) {
        case Element::integer:
            return cur_item_type == "integer";
            break;
        case Element::real:
            return cur_item_type == "real";
            break;
        case Element::boolean:
            return cur_item_type == "boolean";
            break;
        case Element::string:
            return cur_item_type == "string";
            break;
        case Element::list:
            return cur_item_type == "list";
            break;
        case Element::map:
            return cur_item_type == "map";
            break;
    }
    return false;
}

bool
ModuleSpec::validate_item(const ElementPtr spec, const ElementPtr data, const bool full, ElementPtr errors) {
    if (!check_type(spec, data)) {
        // we should do some proper error feedback here
        // std::cout << "type mismatch; not " << spec->get("item_type") << ": " << data << std::endl;
        // std::cout << spec << std::endl;
        if (errors) {
            errors->add(Element::create("Type mismatch"));
        }
        return false;
    }
    if (data->getType() == Element::list) {
        ElementPtr list_spec = spec->get("list_item_spec");
        BOOST_FOREACH(ElementPtr list_el, data->listValue()) {
            if (!check_type(list_spec, list_el)) {
                if (errors) {
                    errors->add(Element::create("Type mismatch"));
                }
                return false;
            }
            if (list_spec->get("item_type")->stringValue() == "map") {
                if (!validate_item(list_spec, list_el, full, errors)) {
                    return false;
                }
            }
        }
    }
    if (data->getType() == Element::map) {
        if (!validate_spec_list(spec->get("map_item_spec"), data, full, errors)) {
            return false;
        }
    }
    return true;
}

// spec is a map with item_name etc, data is a map
bool
ModuleSpec::validate_spec(const ElementPtr spec, const ElementPtr data, const bool full, ElementPtr errors) {
    std::string item_name = spec->get("item_name")->stringValue();
    bool optional = spec->get("item_optional")->boolValue();
    ElementPtr data_el;
    data_el = data->get(item_name);
    
    if (data_el) {
        if (!validate_item(spec, data_el, full, errors)) {
            return false;
        }
    } else {
        if (!optional && full) {
            if (errors) {
                errors->add(Element::create("Non-optional value missing"));
            }
            return false;
        }
    }
    return true;
}

// spec is a list of maps, data is a map
bool
ModuleSpec::validate_spec_list(const ElementPtr spec, const ElementPtr data, const bool full, ElementPtr errors) {
    ElementPtr cur_data_el;
    std::string cur_item_name;
    BOOST_FOREACH(ElementPtr cur_spec_el, spec->listValue()) {
        if (!validate_spec(cur_spec_el, data, full, errors)) {
            return false;
        }
    }
    return true;
}

}
}
