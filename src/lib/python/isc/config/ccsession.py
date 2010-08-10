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
# Client-side functionality for configuration and commands
#
# It keeps a cc-channel session with the configuration manager daemon,
# and handles configuration updates and direct commands

# modeled after ccsession.h/cc 'protocol' changes here need to be
# made there as well
"""Classes and functions for handling configuration and commands

   This module provides the ModuleCCSession and UICCSession classes,
   as well as a set of utility functions to create and parse messages
   related to commands and configuration

   Modules should use the ModuleCCSession class to connect to the
   configuration manager, and receive updates and commands from
   other modules.

   Configuration user interfaces should use the UICCSession to connect
   to b10-cmdctl, and receive and send configuration and commands
   through that to the configuration manager.
"""

from isc.cc import Session
from isc.config.config_data import ConfigData, MultiConfigData, BIND10_CONFIG_DATA_VERSION
import isc

class ModuleCCSessionError(Exception): pass

def parse_answer(msg):
    """Returns a tuple (rcode, value), where value depends on the
       command that was called. If rcode != 0, value is a string
       containing an error message"""
    if type(msg) != dict:
        raise ModuleCCSessionError("Answer message is not a dict: " + str(msg))
    if 'result' not in msg:
        raise ModuleCCSessionError("answer message does not contain 'result' element")
    elif type(msg['result']) != list:
        raise ModuleCCSessionError("wrong result type in answer message")
    elif len(msg['result']) < 1:
        raise ModuleCCSessionError("empty result list in answer message")
    elif type(msg['result'][0]) != int:
        raise ModuleCCSessionError("wrong rcode type in answer message")
    else:
        if len(msg['result']) > 1:
            if (msg['result'][0] != 0 and type(msg['result'][1]) != str):
                raise ModuleCCSessionError("rcode in answer message is non-zero, value is not a string")
            return msg['result'][0], msg['result'][1]
        else:
            return msg['result'][0], None

def create_answer(rcode, arg = None):
    """Creates an answer packet for config&commands. rcode must be an
       integer. If rcode == 0, arg is an optional value that depends
       on what the command or option was. If rcode != 0, arg must be
       a string containing an error message"""
    if type(rcode) != int:
        raise ModuleCCSessionError("rcode in create_answer() must be an integer")
    if rcode != 0 and type(arg) != str:
        raise ModuleCCSessionError("arg in create_answer for rcode != 0 must be a string describing the error")
    if arg != None:
        return { 'result': [ rcode, arg ] }
    else:
        return { 'result': [ rcode ] }

# 'fixed' commands
"""Fixed names for command and configuration messages"""
COMMAND_CONFIG_UPDATE = "config_update"
COMMAND_MODULE_SPECIFICATION_UPDATE = "module_specification_update"

COMMAND_GET_COMMANDS_SPEC = "get_commands_spec"
COMMAND_GET_CONFIG = "get_config"
COMMAND_SET_CONFIG = "set_config"
COMMAND_GET_MODULE_SPEC = "get_module_spec"
COMMAND_MODULE_SPEC = "module_spec"
COMMAND_SHUTDOWN = "shutdown"

def parse_command(msg):
    """Parses what may be a command message. If it looks like one,
       the function returns (command, value) where command is a
       string. If it is not, this function returns None, None"""
    if type(msg) == dict and len(msg.items()) == 1:
        cmd, value = msg.popitem()
        if cmd == "command" and type(value) == list:
            if len(value) == 1 and type(value[0]) == str:
                return value[0], None
            elif len(value) > 1 and type(value[0]) == str:
                return value[0], value[1]
    return None, None

def create_command(command_name, params = None):
    """Creates a module command message with the given command name (as
       specified in the module's specification, and an optional params
       object"""
    # TODO: validate_command with spec
    if type(command_name) != str:
        raise ModuleCCSessionError("command in create_command() not a string")
    cmd = [ command_name ]
    if params:
        cmd.append(params)
    msg = { 'command': cmd }
    return msg

class ModuleCCSession(ConfigData):
    """This class maintains a connection to the command channel, as
       well as configuration options for modules. The module provides
       a specification file that contains the module name, configuration
       options, and commands. It also gives the ModuleCCSession two callback
       functions, one to call when there is a direct command to the
       module, and one to update the configuration run-time. These
       callbacks are called when 'check_command' is called on the
       ModuleCCSession"""
       
    def __init__(self, spec_file_name, config_handler, command_handler, cc_session = None):
        """Initialize a ModuleCCSession. This does *NOT* send the
           specification and request the configuration yet. Use start()
           for that once the ModuleCCSession has been initialized.
           specfile_name is the path to the specification file
           config_handler and command_handler are callback functions,
           see set_config_handler and set_command_handler for more
           information on their signatures."""
        module_spec = isc.config.module_spec_from_file(spec_file_name)
        ConfigData.__init__(self, module_spec)
        
        self._module_name = module_spec.get_module_name()
        
        self.set_config_handler(config_handler)
        self.set_command_handler(command_handler)

        if not cc_session:
            self._session = Session()
        else:
            self._session = cc_session
        self._session.group_subscribe(self._module_name, "*")

        self._remote_module_configs = {}

    def __del__(self):
        self._session.group_unsubscribe(self._module_name, "*")
        for module_name in self._remote_module_configs:
            self._session.group_unsubscribe(module_name)

    def start(self):
        """Send the specification for this module to the configuration
           manager, and request the current non-default configuration.
           The config_handler will be called with that configuration"""
        self.__send_spec()
        self.__request_config()

    def get_socket(self):
        """Returns the socket from the command channel session. This
           should *only* be used for select() loops to see if there
           is anything on the channel. If that loop is not completely
           time-critical, it is strongly recommended to only use
           check_command(), and not look at the socket at all."""
        return self._session._socket
    
    def close(self):
        """Close the session to the command channel"""
        self._session.close()

    def check_command(self):
        """Check whether there is a command or configuration update
           on the channel. Call the corresponding callback function if
           there is."""
        msg, env = self._session.group_recvmsg(False)
        # should we default to an answer? success-by-default? unhandled error?
        if msg and not 'result' in msg:
            answer = None
            try:
                module_name = env['group']
                cmd, arg = isc.config.ccsession.parse_command(msg)
                if cmd == COMMAND_CONFIG_UPDATE:
                    new_config = arg
                    # If the target channel was not this module
                    # it might be in the remote_module_configs
                    if module_name != self._module_name:
                        if module_name in self._remote_module_configs:
                            # no checking for validity, that's up to the
                            # module itself.
                            newc = self._remote_module_configs[module_name].get_local_config()
                            isc.cc.data.merge(newc, new_config)
                            self._remote_module_configs[module_name].set_local_config(newc)
                            return

                    # ok, so apparently this update is for us.
                    errors = []
                    if not self._config_handler:
                        answer = create_answer(2, self._module_name + " has no config handler")
                    elif not self.get_module_spec().validate_config(False, new_config, errors):
                        answer = create_answer(1, " ".join(errors))
                    else:
                        isc.cc.data.remove_identical(new_config, self.get_local_config())
                        answer = self._config_handler(new_config)
                        rcode, val = parse_answer(answer)
                        if rcode == 0:
                            newc = self.get_local_config()
                            isc.cc.data.merge(newc, new_config)
                            self.set_local_config(newc)
                else:
                    # ignore commands for 'remote' modules
                    if module_name == self._module_name:
                        if self._command_handler:
                            answer = self._command_handler(cmd, arg)
                        else:
                            answer = create_answer(2, self._module_name + " has no command handler")
            except Exception as exc:
                answer = create_answer(1, str(exc))
            if answer:
                self._session.group_reply(env, answer)
    
    def set_config_handler(self, config_handler):
        """Set the config handler for this module. The handler is a
           function that takes the full configuration and handles it.
           It should return an answer created with create_answer()"""
        self._config_handler = config_handler
        # should we run this right now since we've changed the handler?

    def set_command_handler(self, command_handler):
        """Set the command handler for this module. The handler is a
           function that takes a command as defined in the .spec file
           and return an answer created with create_answer()"""
        self._command_handler = command_handler

    def add_remote_config(self, spec_file_name):
        """Gives access to the configuration of a different module.
           These remote module options can at this moment only be
           accessed through get_remote_config_value(). This function
           also subscribes to the channel of the remote module name
           to receive the relevant updates. It is not possible to
           specify your own handler for this right now.
           Returns the name of the module."""
        module_spec = isc.config.module_spec_from_file(spec_file_name)
        module_cfg = ConfigData(module_spec)
        module_name = module_spec.get_module_name()
        self._session.group_subscribe(module_name);

        # Get the current config for that module now
        seq = self._session.group_sendmsg(create_command(COMMAND_GET_CONFIG, { "module_name": module_name }), "ConfigManager")
        answer, env = self._session.group_recvmsg(False, seq)
        if answer:
            rcode, value = parse_answer(answer)
            if rcode == 0:
                if value != None and self.get_module_spec().validate_config(False, value):
                    module_cfg.set_local_config(value);

        # all done, add it
        self._remote_module_configs[module_name] = module_cfg
        return module_name
        
    def remove_remote_config(self, module_name):
        """Removes the remote configuration access for this module"""
        if module_name in self._remote_module_configs:
            self._session.group_unsubscribe(module_name)
            del self._remote_module_configs[module_name]

    def get_remote_config_value(self, module_name, identifier):
        """Returns the current setting for the given identifier at the
           given module. If the module has not been added with
           add_remote_config, a ModuleCCSessionError is raised"""
        if module_name in self._remote_module_configs:
            return self._remote_module_configs[module_name].get_value(identifier)
        else:
            raise ModuleCCSessionError("Remote module " + module_name +
                                       " not found")

    def __send_spec(self):
        """Sends the data specification to the configuration manager"""
        msg = create_command(COMMAND_MODULE_SPEC, self.get_module_spec().get_full_spec())
        seq = self._session.group_sendmsg(msg, "ConfigManager")
        answer, env = self._session.group_recvmsg(False, seq)
        
    def __request_config(self):
        """Asks the configuration manager for the current configuration, and call the config handler if set.
           Raises a ModuleCCSessionError if there is no answer from the configuration manager"""
        seq = self._session.group_sendmsg(create_command(COMMAND_GET_CONFIG, { "module_name": self._module_name }), "ConfigManager")
        answer, env = self._session.group_recvmsg(False, seq)
        if answer:
            rcode, value = parse_answer(answer)
            if rcode == 0:
                if value != None and self.get_module_spec().validate_config(False, value):
                    self.set_local_config(value);
                    if self._config_handler:
                        self._config_handler(value)
            else:
                # log error
                print("[" + self._module_name + "] Error requesting configuration: " + value)
        else:
            raise ModuleCCSessionError("No answer from configuration manager")


class UIModuleCCSession(MultiConfigData):
    """This class is used in a configuration user interface. It contains
       specific functions for getting, displaying, and sending
       configuration settings through the b10-cmdctl module."""
    def __init__(self, conn):
        """Initialize a UIModuleCCSession. The conn object that is
           passed must have send_GET and send_POST functions"""
        MultiConfigData.__init__(self)
        self._conn = conn
        self.request_specifications()
        self.request_current_config()

    def request_specifications(self):
        """Request the module specifications from b10-cmdctl"""
        # this step should be unnecessary but is the current way cmdctl returns stuff
        # so changes are needed there to make this clean (we need a command to simply get the
        # full specs for everything, including commands etc, not separate gets for that)
        specs = self._conn.send_GET('/module_spec')
        for module in specs.keys():
            self.set_specification(isc.config.ModuleSpec(specs[module]))

    def update_specs_and_config(self):
        self.request_specifications();
        self.request_current_config();

    def request_current_config(self):
        """Requests the current configuration from the configuration
           manager through b10-cmdctl, and stores those as CURRENT"""
        config = self._conn.send_GET('/config_data')
        if 'version' not in config or config['version'] != BIND10_CONFIG_DATA_VERSION:
            raise ModuleCCSessionError("Bad config version")
        self._set_current_config(config)


    def add_value(self, identifier, value_str):
        """Add a value to a configuration list. Raises a DataTypeError
           if the value does not conform to the list_item_spec field
           of the module config data specification"""
        module_spec = self.find_spec_part(identifier)
        if (type(module_spec) != dict or "list_item_spec" not in module_spec):
            raise isc.cc.data.DataNotFoundError(str(identifier) + " is not a list")
        value = isc.cc.data.parse_value_str(value_str)
        cur_list, status = self.get_value(identifier)
        if not cur_list:
            cur_list = []
        if value not in cur_list:
            cur_list.append(value)
        self.set_value(identifier, cur_list)

    def remove_value(self, identifier, value_str):
        """Remove a value from a configuration list. The value string
           must be a string representation of the full item. Raises
           a DataTypeError if the value at the identifier is not a list,
           or if the given value_str does not match the list_item_spec
           """
        module_spec = self.find_spec_part(identifier)
        if (type(module_spec) != dict or "list_item_spec" not in module_spec):
            raise isc.cc.data.DataNotFoundError(str(identifier) + " is not a list")
        value = isc.cc.data.parse_value_str(value_str)
        isc.config.config_data.check_type(module_spec, [value])
        cur_list, status = self.get_value(identifier)
        #if not cur_list:
        #    cur_list = isc.cc.data.find_no_exc(self.config.data, identifier)
        if not cur_list:
            cur_list = []
        if value in cur_list:
            cur_list.remove(value)
        self.set_value(identifier, cur_list)

    def commit(self):
        """Commit all local changes, send them through b10-cmdctl to
           the configuration manager"""
        if self.get_local_changes():
            self._conn.send_POST('/ConfigManager/set_config', [ self.get_local_changes() ])
            # todo: check result
            self.request_current_config()
            self.clear_local_changes()
