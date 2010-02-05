# Copyright (C) 2009  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#
# This class holds the data definition and validates data agains that
# definition. It is the python equivalent of data_def.h
#
import ast

import isc.cc.data

# file objects are passed around as _io.TextIOWrapper objects
# import that so we can check those types

class DataDefinitionError(Exception):
    pass

class DataDefinition:
    def __init__(self, spec_file, check = True):
        if hasattr(spec_file, 'read'):
            self._data_spec = self.__read_data_spec_file(spec_file)
        elif type(spec_file) == str:
            file = open(spec_file)
            self._data_spec = self.__read_data_spec_file(file)
            file.close()
        else:
            raise DataDefinitionError("Not a str or file-like object")

    def validate(self, data, errors = None):
        """Check whether the given piece of data conforms to this
           data definition. If so, it returns True. If not, it will
           return false. If errors is given, and is an array, a string
           describing the error will be appended to it. The current
           version stops as soon as there is one error so this list
           will not be exhaustive."""
        data_def = self.get_definition()
        if 'data_specification' not in data_def:
            if errors:
                errors.append("Data definition has no data_specification element")
            return False
        data_def = data_def['data_specification']
        if 'config_data' not in data_def:
            if errors:
                errors.append("The is no config_data for this specification")
            return False
        errors = []
        return _validate_spec_list(data_def['config_data'], data, errors)

    def __read_data_spec_file(self, file, check = True):
        """Reads the data spec from the given file object.
           If check is True, check whether it is of the correct form.
           If it is not, an DataDefinitionError exception is raised"""
        if not hasattr(file, 'read'):
            raise DataDefinitionError("Not a file-like object:" + str(type(file)))
        str = file.read(-1)
        # TODO catch error here and reraise as a less ugly exception
        data_spec = ast.literal_eval(str)
        if check:
            # TODO
            _check(data_spec)
            pass
        return data_spec

    def get_definition(self):
        return self._data_spec

    def get_module_name(self):
        return self._data_spec["data_specification"]["module_name"]

def _check(data_spec):
    """Checks the full specification. This is a dict that contains the
       element "data_specification", which is in itself a dict that
       must contain at least a "module_name" (string) and optionally
       a "config_data" and a "commands" element, both of which are lists
       of dicts. Raises a DataDefinitionError if there is a problem."""
    if type(data_spec) != dict:
        raise DataDefinitionError("data specification not a dict")
    if "data_specification" not in data_spec:
        raise DataDefinitionError("no data_specification element in specification")
    data_spec = data_spec["data_specification"]
    if "module_name" not in data_spec:
        raise DataDefinitionError("no module_name in data_specification")
    if "config_data" in data_spec:
        _check_config_spec(data_spec["config_data"])
    if "commands" in data_spec:
        _check_command_spec(data_spec["commands"])

def _check_config_spec(config_data):
    # config data is a list of items represented by dicts that contain
    # things like "item_name", depending on the type they can have
    # specific subitems
    """Checks a list that contains the configuration part of the
       specification. Raises a DataDefinitionError if there is a
       problem."""
    if type(config_data) != list:
        raise DataDefinitionError("config_data is not a list of items")
    for config_item in config_data:
        _check_item_spec(config_item)

def _check_command_spec(commands):
    """Checks the list that contains a set of commands. Raises a
       DataDefinitionError is there is an error"""
    if type(commands) != list:
        raise DataDefinitionError("commands is not a list of commands")
    for command in commands:
        if type(command) != dict:
            raise DataDefinitionError("command in commands list is not a dict")
        if "command_name" not in command:
            raise DataDefinitionError("no command_name in command item")
        command_name = command["command_name"]
        if type(command_name) != str:
            raise DataDefinitionError("command_name not a string: " + str(type(command_name)))
        if "command_description" in command:
            if type(command["command_description"]) != str:
                raise DataDefinitionError("command_description not a string in " + command_name)
        if "command_args" in command:
            if type(command["command_args"]) != list:
                raise DataDefinitionError("command_args is not a list in " + command_name)
            for command_arg in command["command_args"]:
                if type(command_arg) != dict:
                    raise DataDefinitionError("command argument not a dict in " + command_name)
                _check_item_spec(command_arg)
        else:
            raise DataDefinitionError("command_args missing in " + command_name)
    pass

def _check_item_spec(config_item):
    """Checks the dict that defines one config item
       (i.e. containing "item_name", "item_type", etc.
       Raises a DataDefinitionError if there is an error"""
    if type(config_item) != dict:
        raise DataDefinitionError("item spec not a dict")
    if "item_name" not in config_item:
        raise DataDefinitionError("no item_name in config item")
    if type(config_item["item_name"]) != str:
        raise DataDefinitionError("item_name is not a string: " + str(config_item["item_name"]))
    item_name = config_item["item_name"]
    if "item_type" not in config_item:
        raise DataDefinitionError("no item_type in config item")
    item_type = config_item["item_type"]
    if type(item_type) != str:
        raise DataDefinitionError("item_type in " + item_name + " is not a string: " + str(type(item_type)))
    if item_type not in ["integer", "real", "boolean", "string", "list", "map", "any"]:
        raise DataDefinitionError("unknown item_type in " + item_name + ": " + item_type)
    if "item_optional" in config_item:
        if type(config_item["item_optional"]) != bool:
            raise DataDefinitionError("item_default in " + item_name + " is not a boolean")
        if not config_item["item_optional"] and "item_default" not in config_item:
            raise DataDefinitionError("no default value for non-optional item " + item_name)
    else:
        raise DataDefinitionError("item_optional not in item " + item_name)
    if "item_default" in config_item:
        item_default = config_item["item_default"]
        if (item_type == "integer" and type(item_default) != int) or \
           (item_type == "real" and type(item_default) != float) or \
           (item_type == "boolean" and type(item_default) != bool) or \
           (item_type == "string" and type(item_default) != str) or \
           (item_type == "list" and type(item_default) != list) or \
           (item_type == "map" and type(item_default) != dict):
            raise DataDefinitionError("Wrong type for item_default in " + item_name)
    # TODO: once we have check_type, run the item default through that with the list|map_item_spec
    if item_type == "list":
        if "list_item_spec" not in config_item:
            raise DataDefinitionError("no list_item_spec in list item " + item_name)
        if type(config_item["list_item_spec"]) != dict:
            raise DataDefinitionError("list_item_spec in " + item_name + " is not a dict")
        _check_item_spec(config_item["list_item_spec"])
    if item_type == "map":
        if "map_item_spec" not in config_item:
            raise DataDefinitionError("no map_item_sepc in map item " + item_name)
        if type(config_item["map_item_spec"]) != list:
            raise DataDefinitionError("map_item_spec in " + item_name + " is not a list")
        for map_item in config_item["map_item_spec"]:
            if type(map_item) != dict:
                raise DataDefinitionError("map_item_spec element is not a dict")
            _check_item_spec(map_item)


def _validate_type(spec, value, errors):
    """Returns true if the value is of the correct type given the
       specification"""
    data_type = spec['item_type']
    if data_type == "integer" and type(value) != int:
        if errors:
            errors.append(str(value) + " should be an integer")
        return False
    elif data_type == "real" and type(value) != float:
        if errors:
            errors.append(str(value) + " should be a real")
        return False
    elif data_type == "boolean" and type(value) != bool:
        if errors:
            errors.append(str(value) + " should be a boolean")
        return False
    elif data_type == "string" and type(value) != str:
        if errors:
            errors.append(str(value) + " should be a string")
        return False
    elif data_type == "list" and type(value) != list:
        if errors:
            errors.append(str(value) + " should be a list, not a " + str(value.__class__.__name__))
        return False
    elif data_type == "map" and type(value) != dict:
        if errors:
            errors.append(str(value) + " should be a map")
        return False
    else:
        return True

def _validate_item(spec, data, errors):
    if not _validate_type(spec, data, errors):
        return False
    elif type(data) == list:
        list_spec = spec['list_item_spec']
        for data_el in data:
            if not _validate_type(list_spec, data_el, errors):
                return False
            if list_spec['item_type'] == "map":
                if not _validate_item(list_spec, data_el, errors):
                    return False
    elif type(data) == dict:
        if not _validate_spec_list(spec['map_item_spec'], data, errors):
            return False
    return True

def _validate_spec(spec, data, errors):
    item_name = spec['item_name']
    item_optional = spec['item_optional']

    if item_name in data:
        return _validate_item(spec, data[item_name], errors)
    elif not item_optional:
        if errors:
            errors.append("non-optional item " + item_name + " missing")
        return False
    else:
        return True

def _validate_spec_list(data_spec, data, errors):
    for spec_item in data_spec:
        if not _validate_spec(spec_item, data, errors):
            return False
    return True
