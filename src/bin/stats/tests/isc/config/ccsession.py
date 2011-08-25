# Copyright (C) 2010,2011  Internet Systems Consortium.
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

"""
A mock-up module of isc.cc.session

*** NOTE ***
It is only for testing stats_httpd module and not reusable for
external module.
"""

import json
import os
import time
from isc.cc.session import Session

COMMAND_CONFIG_UPDATE = "config_update"

def parse_answer(msg):
    assert 'result' in msg
    try:
        return msg['result'][0], msg['result'][1]
    except IndexError:
        return msg['result'][0], None

def create_answer(rcode, arg = None):
    if arg is None:
        return { 'result': [ rcode ] }
    else:
        return { 'result': [ rcode, arg ] }

def parse_command(msg):
    assert 'command' in msg
    try:
        return msg['command'][0], msg['command'][1]
    except IndexError:
        return msg['command'][0], None

def create_command(command_name, params = None):
    if params is None:
        return {"command": [command_name]}
    else:
        return {"command": [command_name, params]}

def module_spec_from_file(spec_file, check = True):
    try:
        file = open(spec_file)
        json_str = file.read()
        module_spec = json.loads(json_str)
        file.close()
        return ModuleSpec(module_spec['module_spec'], check)
    except IOError as ioe:
        raise ModuleSpecError("JSON read error: " + str(ioe))
    except ValueError as ve:
        raise ModuleSpecError("JSON parse error: " + str(ve))
    except KeyError as err:
        raise ModuleSpecError("Data definition has no module_spec element")

class ModuleSpecError(Exception):
    pass

class ModuleSpec:
    def __init__(self, module_spec, check = True):
        # check only confi_data for testing
        if check and "config_data" in module_spec:
            _check_config_spec(module_spec["config_data"])
        self._module_spec = module_spec

    def get_config_spec(self):
        return self._module_spec['config_data']

    def get_commands_spec(self):
        return self._module_spec['commands']

    def get_module_name(self):
        return self._module_spec['module_name']

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
    if 'item_format' in config_item and 'item_default' in config_item:
        item_format = config_item["item_format"]
        item_default = config_item["item_default"]
        if not _check_format(item_default, item_format):
            raise ModuleSpecError(
                "Wrong format for " + str(item_default) + " in " + str(item_name))

def _check_format(value, format_name):
    """Check if specified value and format are correct. Return True if
       is is correct."""
    # TODO: should be added other format types if necessary
    time_formats = { 'date-time' : "%Y-%m-%dT%H:%M:%SZ",
                     'date'      : "%Y-%m-%d",
                     'time'      : "%H:%M:%S" }
    for fmt in time_formats:
        if format_name == fmt:
            try:
                time.strptime(value, time_formats[fmt])
                return True
            except (ValueError, TypeError):
                break
    return False

class ModuleCCSessionError(Exception):
    pass

class DataNotFoundError(Exception):
    pass

class ConfigData:
    def __init__(self, specification):
        self.specification = specification

    def get_value(self, identifier):
        """Returns a tuple where the first item is the value at the
           given identifier, and the second item is absolutely False
           even if the value is an unset default or not. Raises an
           DataNotFoundError if the identifier is not found in the
           specification file.
           *** NOTE ***
           There are some differences from the original method. This
           method never handles local settings like the original
           method. But these different behaviors aren't so big issues
           for a mock-up method of stats_httpd because stats_httpd
           calls this method at only first."""
        for config_map in self.get_module_spec().get_config_spec():
            if config_map['item_name'] == identifier:
                if 'item_default' in config_map:
                    return config_map['item_default'], False
        raise DataNotFoundError("item_name %s is not found in the specfile" % identifier)

    def get_module_spec(self):
        return self.specification

class ModuleCCSession(ConfigData):
    def __init__(self, spec_file_name, config_handler, command_handler, cc_session = None):
        module_spec = module_spec_from_file(spec_file_name)
        ConfigData.__init__(self, module_spec)
        self._module_name = module_spec.get_module_name()
        self.set_config_handler(config_handler)
        self.set_command_handler(command_handler)
        if not cc_session:
            self._session = Session(verbose=True)
        else:
            self._session = cc_session

    def start(self):
        pass

    def close(self):
        self._session.close()

    def check_command(self, nonblock=True):
        msg, env = self._session.group_recvmsg(nonblock)
        if not msg or 'result' in msg:
            return
        cmd, arg = parse_command(msg)
        answer = None
        if cmd == COMMAND_CONFIG_UPDATE and self._config_handler:
            answer = self._config_handler(arg)
        elif env['group'] == self._module_name and self._command_handler:
            answer = self._command_handler(cmd, arg)
        if answer:
            self._session.group_reply(env, answer)

    def set_config_handler(self, config_handler):
        self._config_handler = config_handler
        # should we run this right now since we've changed the handler?

    def set_command_handler(self, command_handler):
        self._command_handler = command_handler

    def get_module_spec(self):
        return self.specification

    def get_socket(self):
        return self._session._socket

