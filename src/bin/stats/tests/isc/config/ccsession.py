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

# This module is a mock-up class of isc.cc.session

import json
import os
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
        self._module_spec = module_spec

    def get_config_spec(self):
        return self._module_spec['config_data']

    def get_commands_spec(self):
        return self._module_spec['commands']

    def get_module_name(self):
        return self._module_spec['module_name']

class ModuleCCSessionError(Exception):
    pass

class DataNotFoundError(Exception):
    pass

class ConfigData:
    def __init__(self, specification):
        self.specification = specification

    def get_value(self, identifier):
        """Returns a tuple where the first item is the value at the
           given identifier, and the second item is a bool which is
           true if the value is an unset default. Raises an
           DataNotFoundError if the identifier is bad"""
        def _get_value(config_map):
                if 'item_default' in config_map:
                    return config_map['item_default'], False
                elif 'item_type' in config_map:
                    if config_map['item_type'] == 'boolean':
                        return bool(), True
                    elif config_map['item_type'] == 'string':
                        return str(), True
                    elif config_map['item_type'] in set(['number', 'integer']):
                        return int(), True
                    elif config_map['item_type'] in set(['float', 'double', 'real']):
                        return float(), True
                    elif config_map['item_type'] in set(['list', 'array']):
                        return [ _get_value(conf)
                                 for conf in spec['list_item_spec'] ], True
                    elif config_map['item_type'] in set(['map', 'object']):
                        return dict(
                            [ (conf['item_name'], _get_value(conf))
                              for conf in config_map['map_item_spec'] ]), True
                return None, True
        for config_map in self.get_module_spec().get_config_spec():
            if config_map['item_name'] == identifier:
                return _get_value(config_map)
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

