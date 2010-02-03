
#include "data_def.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <cerrno>

#include <boost/foreach.hpp>

// todo: add more context to thrown DataDefinitionErrors?

using namespace isc::data;

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
    } else {
        throw DataDefinitionError(type_name + " is not a valid type name");
    }
}

static void
check_leaf_item(const ElementPtr& spec, const std::string& name, Element::types type, bool mandatory)
{
    if (spec->contains(name)) {
        if (spec->get(name)->getType() == type) {
            return;
        } else {
            throw DataDefinitionError(name + " not of type " + getType_string(type));
        }
    } else if (mandatory) {
        // todo: want parent item name, and perhaps some info about location
        // in list? or just catch and throw new...
        // or make this part non-throwing and check return value...
        throw DataDefinitionError(name + " missing in " + spec->str());
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

    // if list, check the list definition
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
        std::cout << "[XX] ERROR IN: " << spec << std::endl;
        throw DataDefinitionError("config_data is not a list of elements");
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
        throw DataDefinitionError("commands is not a list of elements");
    }
    BOOST_FOREACH(ElementPtr item, spec->listValue()) {
        check_command(item);
    }
}

static void
check_data_specification(const ElementPtr& spec) {
    check_leaf_item(spec, "module_name", Element::string, true);
    // config_data is not mandatory; module could just define
    // commands and have no config
    if (spec->contains("config_data")) {
        check_config_item_list(spec->get("config_data"));
    }
    if (spec->contains("commands")) {
        check_command_list(spec->get("commands"));
    }
}

// checks whether the given element is a valid data definition
// throws a DataDefinitionError if the specification is bad
static void
check_definition(const ElementPtr& def)
{
    if (!def->contains("data_specification")) {
        throw DataDefinitionError("Data specification does not contain data_specification element");
    } else {
        check_data_specification(def->get("data_specification"));
    }
}

DataDefinition::DataDefinition(const std::string& file_name,
                               const bool check)
                               throw(ParseError, DataDefinitionError) {
    std::ifstream file;

    file.open(file_name.c_str());
    if (!file) {
        std::stringstream errs;
        errs << "Error opening " << file_name << ": " << strerror(errno);
        throw DataDefinitionError(errs.str());
    }

    definition = Element::createFromString(file, file_name);
    if (check) {
        check_definition(definition);
    }
}

DataDefinition::DataDefinition(std::istream& in, const bool check)
                               throw(ParseError, DataDefinitionError) {
    definition = Element::createFromString(in);
    // make sure the whole structure is complete and valid
    if (check) {
        check_definition(definition);
    }
}

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
DataDefinition::validate_item(const ElementPtr spec, const ElementPtr data) {
    std::cout << "Validating type of " << data << std::endl;
    if (!check_type(spec, data)) {
        std::cout << "type mismatch; not " << spec->get("item_type") << ": " << data << std::endl;
        std::cout << spec << std::endl;
        return false;
    }
    if (data->getType() == Element::list) {
        BOOST_FOREACH(ElementPtr list_el, data->listValue()) {
            if (!validate_spec(spec->get("list_item_spec"), list_el)) {
                return false;
            }
        }
    }
    if (data->getType() == Element::map) {
        if (!validate_spec_list(spec->get("map_item_spec"), data)) {
            return false;
        }
    }
    return true;
}

// spec is a map with item_name etc, data is a map
bool
DataDefinition::validate_spec(const ElementPtr spec, const ElementPtr data) {
    std::string item_name = spec->get("item_name")->stringValue();
    bool optional = spec->get("item_optional")->boolValue();
    ElementPtr data_el;
    
    std::cout << "check for item with name " << item_name << std::endl;
    data_el = data->get(item_name);
    if (data_el) {
        if (!validate_item(spec, data_el)) {
            return false;
        }
    } else {
        if (!optional) {
            std::cout << "non-optional value not found" << std::endl;
            return false;
        }
    }
    return true;
}

// spec is a list of maps, data is a map
bool
DataDefinition::validate_spec_list(const ElementPtr spec, const ElementPtr data) {
    ElementPtr cur_data_el;
    std::string cur_item_name;
    BOOST_FOREACH(ElementPtr cur_spec_el, spec->listValue()) {
        if (!validate_spec(cur_spec_el, data)) {
            return false;
        }
    }
    return true;
}

// TODO
// this function does *not* check if the specification is in correct
// form, we should do that in the constructor
bool
DataDefinition::validate(const ElementPtr data) {
    ElementPtr spec = definition->find("data_specification/config_data");
    return validate_spec_list(spec, data);
}

