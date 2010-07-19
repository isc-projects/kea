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

"""Module Specifications

   A module specification holds the information about what configuration
   a module can have, and what commands it understands. It provides
   functions to read it from a .spec file, and to validate a given
   set of data against the specification
"""

import json
import sys

import isc.cc.data

# file objects are passed around as _io.TextIOWrapper objects
# import that so we can check those types

class ModuleSpecError(Exception):
    """This exception is raised it the ModuleSpec fails to initialize
       or if there is a failure or parse error reading the specification
       file"""
    pass

def module_spec_from_file(spec_file, check = True):
    """Returns a ModuleSpec object defined by the file at spec_file.
       If check is True, the contents are verified. If there is an error
       in those contents, a ModuleSpecError is raised.
       A ModuleSpecError is also raised if the file cannot be read, or
       if it is not valid JSON."""
    module_spec = None
    try:
        if hasattr(spec_file, 'read'):
            json_str = spec_file.read()
            module_spec = json.loads(json_str)
        elif type(spec_file) == str:
            file = open(spec_file)
            json_str = file.read()
            module_spec = json.loads(json_str)
            file.close()
        else:
            raise ModuleSpecError("spec_file not a str or file-like object")
    except ValueError as ve:
        raise ModuleSpecError("JSON parse error: " + str(ve))
    except IOError as ioe:
        raise ModuleSpecError("JSON read error: " + str(ioe))

    if 'module_spec' not in module_spec:
        raise ModuleSpecError("Data definition has no module_spec element")

    result = ModuleSpec(module_spec['module_spec'], check)
    return result

class ModuleSpec:
    def __init__(self, module_spec, check = True):
        """Initializes a ModuleSpec object from the specification in
           the given module_spec (which must be a dict). If check is
           True, the contents are verified. Raises a ModuleSpec error
           if there is something wrong with the contents of the dict"""
        if type(module_spec) != dict:
            raise ModuleSpecError("module_spec is of type " + str(type(module_spec)) + ", not dict")
        if check:
            _check(module_spec)
        self._module_spec = module_spec

    def validate_config(self, full, data, errors = None):
        """Check whether the given piece of data conforms to this
           data definition. If so, it returns True. If not, it will
           return false. If errors is given, and is an array, a string
           describing the error will be appended to it. The current
           version stops as soon as there is one error so this list
           will not be exhaustive. If 'full' is true, it also errors on
           non-optional missing values. Set this to False if you want to
           validate only a part of a configuration tree (like a list of
           non-default values)"""
        data_def = self.get_config_spec()
        if data_def:
            return _validate_spec_list(data_def, full, data, errors)
        else:
            # no spec, always bad
            if errors != None:
                errors.append("No config_data specification")
            return False

    def validate_command(self, cmd_name, cmd_params, errors = None):
        '''Check whether the given piece of command conforms to this 
        command definition. If so, it reutrns True. If not, it will 
        return False. If errors is given, and is an array, a string
        describing the error will be appended to it. The current version
        stops as soon as there is one error.
           cmd_name is command name to be validated, cmd_params includes 
        command's parameters needs to be validated. cmd_params must 
        be a map, with the format like:
        {param1_name: param1_value, param2_name: param2_value}
        '''
        cmd_spec = self.get_commands_spec()
        if not cmd_spec:
            return False

        for cmd in cmd_spec:
            if cmd['command_name'] != cmd_name:
                continue
            return _validate_spec_list(cmd['command_args'], True, cmd_params, errors)

        return False

    def get_module_name(self):
        """Returns a string containing the name of the module as
           specified by the specification given at __init__()"""
        return self._module_spec['module_name']

    def get_module_description(self):
        """Returns a string containing the description of the module as
           specified by the specification given at __init__().
           Returns an empty string if there is no description.
        """
        if 'module_description' in self._module_spec:
            return self._module_spec['module_description']
        else:
            return ""

    def get_full_spec(self):
        """Returns a dict representation of the full module specification"""
        return self._module_spec

    def get_config_spec(self):
        """Returns a dict representation of the configuration data part
           of the specification, or None if there is none."""
        if 'config_data' in self._module_spec:
            return self._module_spec['config_data']
        else:
            return None
    
    def get_commands_spec(self):
        """Returns a dict representation of the commands part of the
           specification, or None if there is none."""
        if 'commands' in self._module_spec:
            return self._module_spec['commands']
        else:
            return None
    
    def __str__(self):
        """Returns a string representation of the full specification"""
        return self._module_spec.__str__()

def _check(module_spec):
    """Checks the full specification. This is a dict that contains the
       element "module_spec", which is in itself a dict that
       must contain at least a "module_name" (string) and optionally
       a "config_data" and a "commands" element, both of which are lists
       of dicts. Raises a ModuleSpecError if there is a problem."""
    if type(module_spec) != dict:
        raise ModuleSpecError("data specification not a dict")
    if "module_name" not in module_spec:
        raise ModuleSpecError("no module_name in module_spec")
    if "module_description" in module_spec and \
       type(module_spec["module_description"]) != str:
        raise ModuleSpecError("module_description is not a string")
    if "config_data" in module_spec:
        _check_config_spec(module_spec["config_data"])
    if "commands" in module_spec:
        _check_command_spec(module_spec["commands"])

def _check_config_spec(config_data):
    # config data is a list of items represented by dicts that contain
    # things like "item_name", depending on the type they can have
    # specific subitems
    """Checks a list that contains the configuration part of the
       specification. Raises a ModuleSpecError if there is a
       problem."""
    if type(config_data) != list:
        raise ModuleSpecError("config_data is of type " + str(type(config_data)) + ", not a list of items")
    for config_item in config_data:
        _check_item_spec(config_item)

def _check_command_spec(commands):
    """Checks the list that contains a set of commands. Raises a
       ModuleSpecError is there is an error"""
    if type(commands) != list:
        raise ModuleSpecError("commands is not a list of commands")
    for command in commands:
        if type(command) != dict:
            raise ModuleSpecError("command in commands list is not a dict")
        if "command_name" not in command:
            raise ModuleSpecError("no command_name in command item")
        command_name = command["command_name"]
        if type(command_name) != str:
            raise ModuleSpecError("command_name not a string: " + str(type(command_name)))
        if "command_description" in command:
            if type(command["command_description"]) != str:
                raise ModuleSpecError("command_description not a string in " + command_name)
        if "command_args" in command:
            if type(command["command_args"]) != list:
                raise ModuleSpecError("command_args is not a list in " + command_name)
            for command_arg in command["command_args"]:
                if type(command_arg) != dict:
                    raise ModuleSpecError("command argument not a dict in " + command_name)
                _check_item_spec(command_arg)
        else:
            raise ModuleSpecError("command_args missing in " + command_name)
    pass

def _check_item_spec(config_item):
    """Checks the dict that defines one config item
       (i.e. containing "item_name", "item_type", etc.
       Raises a ModuleSpecError if there is an error"""
    if type(config_item) != dict:
        raise ModuleSpecError("item spec not a dict")
    if "item_name" not in config_item:
        raise ModuleSpecError("no item_name in config item")
    if type(config_item["item_name"]) != str:
        raise ModuleSpecError("item_name is not a string: " + str(config_item["item_name"]))
    item_name = config_item["item_name"]
    if "item_type" not in config_item:
        raise ModuleSpecError("no item_type in config item")
    item_type = config_item["item_type"]
    if type(item_type) != str:
        raise ModuleSpecError("item_type in " + item_name + " is not a string: " + str(type(item_type)))
    if item_type not in ["integer", "real", "boolean", "string", "list", "map", "any"]:
        raise ModuleSpecError("unknown item_type in " + item_name + ": " + item_type)
    if "item_optional" in config_item:
        if type(config_item["item_optional"]) != bool:
            raise ModuleSpecError("item_default in " + item_name + " is not a boolean")
        if not config_item["item_optional"] and "item_default" not in config_item:
            raise ModuleSpecError("no default value for non-optional item " + item_name)
    else:
        raise ModuleSpecError("item_optional not in item " + item_name)
    if "item_default" in config_item:
        item_default = config_item["item_default"]
        if (item_type == "integer" and type(item_default) != int) or \
           (item_type == "real" and type(item_default) != float) or \
           (item_type == "boolean" and type(item_default) != bool) or \
           (item_type == "string" and type(item_default) != str) or \
           (item_type == "list" and type(item_default) != list) or \
           (item_type == "map" and type(item_default) != dict):
            raise ModuleSpecError("Wrong type for item_default in " + item_name)
    # TODO: once we have check_type, run the item default through that with the list|map_item_spec
    if item_type == "list":
        if "list_item_spec" not in config_item:
            raise ModuleSpecError("no list_item_spec in list item " + item_name)
        if type(config_item["list_item_spec"]) != dict:
            raise ModuleSpecError("list_item_spec in " + item_name + " is not a dict")
        _check_item_spec(config_item["list_item_spec"])
    if item_type == "map":
        if "map_item_spec" not in config_item:
            raise ModuleSpecError("no map_item_sepc in map item " + item_name)
        if type(config_item["map_item_spec"]) != list:
            raise ModuleSpecError("map_item_spec in " + item_name + " is not a list")
        for map_item in config_item["map_item_spec"]:
            if type(map_item) != dict:
                raise ModuleSpecError("map_item_spec element is not a dict")
            _check_item_spec(map_item)


def _validate_type(spec, value, errors):
    """Returns true if the value is of the correct type given the
       specification"""
    data_type = spec['item_type']
    if data_type == "integer" and type(value) != int:
        if errors != None:
            errors.append(str(value) + " should be an integer")
        return False
    elif data_type == "real" and type(value) != float:
        if errors != None:
            errors.append(str(value) + " should be a real")
        return False
    elif data_type == "boolean" and type(value) != bool:
        if errors != None:
            errors.append(str(value) + " should be a boolean")
        return False
    elif data_type == "string" and type(value) != str:
        if errors != None:
            errors.append(str(value) + " should be a string")
        return False
    elif data_type == "list" and type(value) != list:
        if errors != None:
            errors.append(str(value) + " should be a list")
        return False
    elif data_type == "map" and type(value) != dict:
        if errors != None:
            errors.append(str(value) + " should be a map")
        return False
    else:
        return True

def _validate_item(spec, full, data, errors):
    if not _validate_type(spec, data, errors):
        return False
    elif type(data) == list:
        list_spec = spec['list_item_spec']
        for data_el in data:
            if not _validate_type(list_spec, data_el, errors):
                return False
            if list_spec['item_type'] == "map":
                if not _validate_item(list_spec, full, data_el, errors):
                    return False
    elif type(data) == dict:
        if not _validate_spec_list(spec['map_item_spec'], full, data, errors):
            return False
    return True

def _validate_spec(spec, full, data, errors):
    item_name = spec['item_name']
    item_optional = spec['item_optional']

    if item_name in data:
        return _validate_item(spec, full, data[item_name], errors)
    elif full and not item_optional:
        if errors != None:
            errors.append("non-optional item " + item_name + " missing")
        return False
    else:
        return True

def _validate_spec_list(module_spec, full, data, errors):
    for spec_item in module_spec:
        if not _validate_spec(spec_item, full, data, errors):
            return False
    return True
