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

# file objects are passed around as _io.TextIOWrapper objects
# import that so we can check those types
import _io

class DataDefinitionError(Exception):
    pass

class DataDefinition:
    def __init__(self, spec_file, check = True):
        if type(spec_file) == _io.TextIOWrapper:
            self._data_spec = __read_data_spec_file(spec_file)
        elif type(spec_file) == str:
            file = open(spec_file)
            self._data_spec = self.__readDataSpecFile(file)
            file.close()
        else:
            raise DataDefinitionError("Not a str or file-like object")

    def validate(self, data):
        """Check whether the given piece of data conforms to this
           data definition"""
        # "TODO"
        return True

    def __readDataSpecFile(self, file, check = True):
        """Reads the data spec from the given file object.
           If check is True, check whether it is of the correct form.
           If it is not, an DataDefinitionError exception is raised"""
        if type(file) != _io.TextIOWrapper:
            raise DataDefinitionError("Not a file-like object:" + str(type(file)))
        str = file.read()
        # TODO catch error here and reraise as a less ugly exception
        data_spec = ast.literal_eval(str)
        if check:
            # TODO
            _check(data_spec)
            pass
        return data_spec

    def getDefinition(self):
        return self._data_spec

    def getModuleName(self):
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
        _checkConfigSpec(data_spec["config_data"])
    if "commands" in data_spec:
        _checkCommandSpec(data_spec["commands"])

def _checkConfigSpec(config_data):
    # config data is a list of items represented by dicts that contain
    # things like "item_name", depending on the type they can have
    # specific subitems
    """Checks a list that contains the configuration part of the
       specification. Raises a DataDefinitionError if there is a
       problem."""
    if type(config_data) != list:
        raise DataDefinitionError("config_data is not a list of items")
    for config_item in config_data:
        _checkItemSpec(config_item)

def _checkCommandSpec(commands):
    """Checks the list that contains a set of commands. Raises a
       DataDefinitionError is there is an error"""
    if type(commands) != list:
        raise DataDefinitionError("commands is not a list of commands")
    for command in commands:
        if type(command) != dict:
            raise DataDefinitionError("command in commands list is not a dict")
        if "command_name" not in command:
            raise DataDefitionError("no command_name in command item")
        command_name = command["command_name"]
        if type(command_name) != str:
            raise DataDefinitionError("command_name not a string: " + str(type(command_name)))
        if "command_description" in command:
            if type(command["command_description"]) != str:
                raise DataDefitionError("command_description not a string in " + command_name)
        if "command_args" in command:
            if type(command["command_args"]) != list:
                raise DataDefitionError("command_args is not a list in " + command_name)
            for command_arg in command["command_args"]:
                if type(command_arg) != dict:
                    raise DataDefinitionError("command argument not a dict in " + command_name)
                _checkItemSpec(command_arg)
    pass

def _checkItemSpec(config_item):
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
    if item_type not in ["integer", "real", "boolean", "string", "list", "map"]:
        raise DataDefinitionError("unknown item_type in " + item_name + ": " + item_type)
    if "item_optional" in config_item:
        if type(config_item["item_optional"]) != bool:
            raise DataDefinitionError("item_default in " + item_name + " is not a boolean")
        if not config_item["item_optional"] and "item_default" not in config_item:
            raise DataDefinitionError("no default value for non-optional item " + item_name)
    if "item_default" in config_item:
        item_default = config_item["item_default"]
        if (item_type == "int" and type(item_default) != int) or \
           (item_type == "real" and type(item_default) != double) or \
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
        _checkItemSpec(config_item["list_item_spec"])
    if item_type == "map":
        if "map_item_spec" not in config_item:
            raise DataDefinitionError("no map_item_sepc in map item " + item_name)
        if type(config_item["map_item_spec"]) != list:
            raise DataDefinitionError("map_item_spec in " + item_name + " is not a list")
        for map_item in config_item["map_item_spec"]:
            if type(map_item) != dict:
                raise DataDefinitionError("map_item_spec element is not a dict")
            _checkItemSpec(map_item)

