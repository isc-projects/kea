# Copyright (C) 2010  Internet Systems Consortium.
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

# $Id$
# This module is a mock-up class of isc.cc.session

__version__ = "$Revision$"

import json
from isc.cc.session import Session

COMMAND_CONFIG_UPDATE = "config_update"

def parse_answer(msg):
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
    file = open(spec_file)
    module_spec = json.loads(file.read())
    return ModuleSpec(module_spec['module_spec'], check)

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

class ConfigData:
    def __init__(self, specification):
        self.specification = specification

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

    def check_command(self):
        msg, env = self._session.group_recvmsg(False)
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
