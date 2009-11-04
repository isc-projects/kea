
#include "data_def.h"

#include <sstream>

#include <boost/foreach.hpp>


using namespace ISC::Data;

DataDefinition::DataDefinition(std::istream& in) throw(ParseError) {
    definition = Element::create_from_string(in);
    // TODO, make sure the whole structure is complete and valid
    if (!definition->contains("data_specification")) {
        throw ParseError("Data specification does not contain data_specification element");
    }
}

//
// helper functions for validation
//
static bool
check_type(ElementPtr spec, ElementPtr element)
{
    std::string cur_item_type;
    cur_item_type = spec->get("item_type")->string_value();
    if (cur_item_type == "any") {
        return true;
    }
    switch (element->get_type()) {
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
    if (data->get_type() == Element::list) {
        BOOST_FOREACH(ElementPtr list_el, data->list_value()) {
            if (!validate_spec(spec->get("list_item_spec"), list_el)) {
                return false;
            }
        }
    }
    if (data->get_type() == Element::map) {
        if (!validate_spec_list(spec->get("map_item_spec"), data)) {
            return false;
        }
    }
    return true;
}

// spec is a map with item_name etc, data is a map
bool
DataDefinition::validate_spec(const ElementPtr spec, const ElementPtr data) {
    std::string item_name = spec->get("item_name")->string_value();
    bool optional = spec->get("item_optional")->bool_value();
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
    bool optional;
    BOOST_FOREACH(ElementPtr cur_spec_el, spec->list_value()) {
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

