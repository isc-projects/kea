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

   This module provides the ModuleCCSession and UIModuleCCSession
   classes, as well as a set of utility functions to create and parse
   messages related to commands and configuration

   Modules should use the ModuleCCSession class to connect to the
   configuration manager, and receive updates and commands from
   other modules.

   Configuration user interfaces should use the UIModuleCCSession
   to connect to b10-cmdctl, and receive and send configuration and
   commands through that to the configuration manager.
"""

from isc.cc import Session
from isc.config.config_data import ConfigData, MultiConfigData, BIND10_CONFIG_DATA_VERSION
import isc.config.module_spec
import isc
from isc.util.file import path_search
import bind10_config
from isc.log import log_config_update
import json
from isc.log_messages.config_messages import *

logger = isc.log.Logger("config")

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
COMMAND_GET_STATISTICS_SPEC = "get_statistics_spec"
COMMAND_GET_CONFIG = "get_config"
COMMAND_SET_CONFIG = "set_config"
COMMAND_GET_MODULE_SPEC = "get_module_spec"
COMMAND_MODULE_SPEC = "module_spec"
COMMAND_SHUTDOWN = "shutdown"
COMMAND_MODULE_STOPPING = "stopping"

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

def default_logconfig_handler(new_config, config_data):
    errors = []

    if config_data.get_module_spec().validate_config(False, new_config, errors):
        isc.log.log_config_update(json.dumps(new_config),
            json.dumps(config_data.get_module_spec().get_full_spec()))
    else:
        logger.error(CONFIG_LOG_CONFIG_ERRORS, errors)

class ModuleCCSession(ConfigData):
    """This class maintains a connection to the command channel, as
       well as configuration options for modules. The module provides
       a specification file that contains the module name, configuration
       options, and commands. It also gives the ModuleCCSession two callback
       functions, one to call when there is a direct command to the
       module, and one to update the configuration run-time. These
       callbacks are called when 'check_command' is called on the
       ModuleCCSession"""

    def __init__(self, spec_file_name, config_handler, command_handler,
                 cc_session=None, handle_logging_config=True,
                 socket_file = None):
        """Initialize a ModuleCCSession. This does *NOT* send the
           specification and request the configuration yet. Use start()
           for that once the ModuleCCSession has been initialized.

           specfile_name is the path to the specification file.

           config_handler and command_handler are callback functions,
           see set_config_handler and set_command_handler for more
           information on their signatures.

           cc_session can be used to pass in an existing CCSession,
           if it is None, one will be set up. This is mainly intended
           for testing purposes.

           handle_logging_config: if True, the module session will
           automatically handle logging configuration for the module;
           it will read the system-wide Logging configuration and call
           the logger manager to apply it. It will also inform the
           logger manager when the logging configuration gets updated.
           The module does not need to do anything except intializing
           its loggers, and provide log messages. Defaults to true.

           socket_file: If cc_session was none, this optional argument
           specifies which socket file to use to connect to msgq. It
           will be overridden by the environment variable
           MSGQ_SOCKET_FILE. If none, and no environment variable is
           set, it will use the system default.
        """
        module_spec = isc.config.module_spec_from_file(spec_file_name)
        ConfigData.__init__(self, module_spec)

        self._module_name = module_spec.get_module_name()

        self.set_config_handler(config_handler)
        self.set_command_handler(command_handler)

        if not cc_session:
            self._session = Session(socket_file)
        else:
            self._session = cc_session
        self._session.group_subscribe(self._module_name, "*")

        self._remote_module_configs = {}
        self._remote_module_callbacks = {}

        if handle_logging_config:
            self.add_remote_config(path_search('logging.spec', bind10_config.PLUGIN_PATHS),
                                   default_logconfig_handler)

    def __del__(self):
        # If the CC Session obejct has been closed, it returns
        # immediately.
        if self._session._closed: return
        self._session.group_unsubscribe(self._module_name, "*")
        for module_name in self._remote_module_configs:
            self._session.group_unsubscribe(module_name)

    def start(self):
        """Send the specification for this module to the configuration
           manager, and request the current non-default configuration.
           The config_handler will be called with that configuration"""
        self.__send_spec()
        self.__request_config()

    def send_stopping(self):
        """Sends a 'stopping' message to the configuration manager. This
           message is just an FYI, and no response is expected. Any errors
           when sending this message (for instance if the msgq session has
           previously been closed) are logged, but ignored."""
        # create_command could raise an exception as well, but except for
        # out of memory related errors, these should all be programming
        # failures and are not caught
        msg = create_command(COMMAND_MODULE_STOPPING,
                             self.get_module_spec().get_full_spec())
        try:
            self._session.group_sendmsg(msg, "ConfigManager")
        except Exception as se:
            # If the session was previously closed, obvously trying to send
            # a message fails. (TODO: check if session is open so we can
            # error on real problems?)
            logger.error(CONFIG_SESSION_STOPPING_FAILED, se)

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

    def check_command(self, nonblock=True):
        """Check whether there is a command or configuration update on
           the channel. This function does a read on the cc session, and
           returns nothing.
           It calls check_command_without_recvmsg()
           to parse the received message.

           If nonblock is True, it just checks if there's a command
           and does nothing if there isn't. If nonblock is False, it
           waits until it arrives. It temporarily sets timeout to infinity,
           because commands may not come in arbitrary long time."""
        timeout_orig = self._session.get_timeout()
        self._session.set_timeout(0)
        try:
            msg, env = self._session.group_recvmsg(nonblock)
        finally:
            self._session.set_timeout(timeout_orig)
        self.check_command_without_recvmsg(msg, env)

    def check_command_without_recvmsg(self, msg, env):
        """Parse the given message to see if there is a command or a
           configuration update. Calls the corresponding handler
           functions if present. Responds on the channel if the
           handler returns a message."""
        # should we default to an answer? success-by-default? unhandled error?
        if msg is not None and not 'result' in msg:
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
                            if self._remote_module_callbacks[module_name] != None:
                                self._remote_module_callbacks[module_name](new_config,
                                                                           self._remote_module_configs[module_name])
                        # For other modules, we're not supposed to answer
                        return

                    # ok, so apparently this update is for us.
                    errors = []
                    if not self._config_handler:
                        answer = create_answer(2, self._module_name + " has no config handler")
                    elif not self.get_module_spec().validate_config(False, new_config, errors):
                        answer = create_answer(1, ", ".join(errors))
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

    def _add_remote_config_internal(self, module_spec,
                                    config_update_callback=None):
        """The guts of add_remote_config and add_remote_config_by_name"""
        module_cfg = ConfigData(module_spec)
        module_name = module_spec.get_module_name()

        self._session.group_subscribe(module_name)

        # Get the current config for that module now
        seq = self._session.group_sendmsg(create_command(COMMAND_GET_CONFIG, { "module_name": module_name }), "ConfigManager")

        try:
            answer, _ = self._session.group_recvmsg(False, seq)
        except isc.cc.SessionTimeout:
            raise ModuleCCSessionError("No answer from ConfigManager when "
                                       "asking about Remote module " +
                                       module_name)
        call_callback = False
        if answer:
            rcode, value = parse_answer(answer)
            if rcode == 0:
                if value != None:
                    if module_spec.validate_config(False, value):
                        module_cfg.set_local_config(value)
                        call_callback = True
                    else:
                        raise ModuleCCSessionError("Bad config data for " +
                                                   module_name + ": " +
                                                   str(value))
            else:
                raise ModuleCCSessionError("Failure requesting remote " +
                                           "configuration data for " +
                                           module_name)

        # all done, add it
        self._remote_module_configs[module_name] = module_cfg
        self._remote_module_callbacks[module_name] = config_update_callback
        if call_callback and config_update_callback is not None:
            config_update_callback(value, module_cfg)

    def add_remote_config_by_name(self, module_name,
                                  config_update_callback=None):
        """
        This does the same as add_remote_config, but you provide the module name
        instead of the name of the spec file.
        """
        seq = self._session.group_sendmsg(create_command(COMMAND_GET_MODULE_SPEC,
                                                         { "module_name":
                                                         module_name }),
                                          "ConfigManager")
        try:
            answer, env = self._session.group_recvmsg(False, seq)
        except isc.cc.SessionTimeout:
            raise ModuleCCSessionError("No answer from ConfigManager when " +
                                       "asking about for spec of Remote " +
                                       "module " + module_name)
        if answer:
            rcode, value = parse_answer(answer)
            if rcode == 0:
                module_spec = isc.config.module_spec.ModuleSpec(value)
                if module_spec.get_module_name() != module_name:
                    raise ModuleCCSessionError("Module name mismatch: " +
                                               module_name + " and " +
                                               module_spec.get_module_name())
                self._add_remote_config_internal(module_spec,
                                                 config_update_callback)
            else:
                raise ModuleCCSessionError("Error code " + str(rcode) +
                                           "when asking for module spec of " +
                                           module_name)
        else:
            raise ModuleCCSessionError("No answer when asking for module " +
                                       "spec of " + module_name)
        # Just to be consistent with the add_remote_config
        return module_name

    def add_remote_config(self, spec_file_name, config_update_callback=None):
        """Gives access to the configuration of a different module.
           These remote module options can at this moment only be
           accessed through get_remote_config_value(). This function
           also subscribes to the channel of the remote module name
           to receive the relevant updates. It is not possible to
           specify your own handler for this right now, but you can
           specify a callback that is called after the change happened.
           start() must have been called on this CCSession
           prior to the call to this method.
           Returns the name of the module."""
        module_spec = isc.config.module_spec_from_file(spec_file_name)
        self._add_remote_config_internal(module_spec, config_update_callback)
        return module_spec.get_module_name()

    def remove_remote_config(self, module_name):
        """Removes the remote configuration access for this module"""
        if module_name in self._remote_module_configs:
            self._session.group_unsubscribe(module_name)
            del self._remote_module_configs[module_name]
            del self._remote_module_callbacks[module_name]

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
        try:
            answer, env = self._session.group_recvmsg(False, seq)
        except isc.cc.SessionTimeout:
            # TODO: log an error?
            pass

    def __request_config(self):
        """Asks the configuration manager for the current configuration, and call the config handler if set.
           Raises a ModuleCCSessionError if there is no answer from the configuration manager"""
        seq = self._session.group_sendmsg(create_command(COMMAND_GET_CONFIG, { "module_name": self._module_name }), "ConfigManager")
        try:
            answer, env = self._session.group_recvmsg(False, seq)
            if answer:
                rcode, value = parse_answer(answer)
                if rcode == 0:
                    errors = []
                    if value != None:
                        if self.get_module_spec().validate_config(False,
                                                                  value,
                                                                  errors):
                            self.set_local_config(value)
                            if self._config_handler:
                                self._config_handler(value)
                        else:
                            raise ModuleCCSessionError(
                                "Wrong data in configuration: " +
                                " ".join(errors))
                else:
                    logger.error(CONFIG_GET_FAILED, value)
            else:
                raise ModuleCCSessionError("No answer from configuration manager")
        except isc.cc.SessionTimeout:
            raise ModuleCCSessionError("CC Session timeout waiting for configuration manager")


class UIModuleCCSession(MultiConfigData):
    """This class is used in a configuration user interface. It contains
       specific functions for getting, displaying, and sending
       configuration settings through the b10-cmdctl module."""
    def __init__(self, conn):
        """Initialize a UIModuleCCSession. The conn object that is
           passed must have send_GET and send_POST functions"""
        MultiConfigData.__init__(self)
        self._conn = conn
        self.update_specs_and_config()

    def request_specifications(self):
        """Clears the current list of specifications, and requests a new
            list from b10-cmdctl. As other actions may have caused modules
            to be stopped, or new modules to be added, this is expected to
            be run after each interaction (at this moment). It is usually
            also combined with request_current_config(). For that reason,
            we provide update_specs_and_config() which calls both."""
        specs = self._conn.send_GET('/module_spec')
        self.clear_specifications()
        for module in specs.keys():
            self.set_specification(isc.config.ModuleSpec(specs[module]))

    def request_current_config(self):
        """Requests the current configuration from the configuration
           manager through b10-cmdctl, and stores those as CURRENT. This
           does not modify any local changes, it just updates to the current
           state of the server itself."""
        config = self._conn.send_GET('/config_data')
        if 'version' not in config or config['version'] != BIND10_CONFIG_DATA_VERSION:
            raise ModuleCCSessionError("Bad config version")
        self._set_current_config(config)

    def update_specs_and_config(self):
        """Convenience function to both clear and update the known list of
           module specifications, and update the current configuration on
           the server side. There are a few cases where the caller might only
           want to run one of these tasks, but often they are both needed."""
        self.request_specifications()
        self.request_current_config()

    def _add_value_to_list(self, identifier, value, module_spec):
        cur_list, status = self.get_value(identifier)
        if not cur_list:
            cur_list = []

        if value is None and "list_item_spec" in module_spec:
            if "item_default" in module_spec["list_item_spec"]:
                value = module_spec["list_item_spec"]["item_default"]

        if value is None:
            raise isc.cc.data.DataNotFoundError(
                "No value given and no default for " + str(identifier))

        if value not in cur_list:
            cur_list.append(value)
            self.set_value(identifier, cur_list)
        else:
            raise isc.cc.data.DataAlreadyPresentError(str(value) +
                                                      " already in "
                                                      + str(identifier))

    def _add_value_to_named_set(self, identifier, value, item_value):
        if type(value) != str:
            raise isc.cc.data.DataTypeError("Name for named_set " +
                                            identifier +
                                            " must be a string")
        # fail on both None and empty string
        if not value:
            raise isc.cc.data.DataNotFoundError(
                    "Need a name to add a new item to named_set " +
                    str(identifier))
        else:
            cur_map, status = self.get_value(identifier)
            if not cur_map:
                cur_map = {}
            if value not in cur_map:
                cur_map[value] = item_value
                self.set_value(identifier, cur_map)
            else:
                raise isc.cc.data.DataAlreadyPresentError(value +
                                                          " already in " +
                                                          identifier)

    def add_value(self, identifier, value_str = None, set_value_str = None):
        """Add a value to a configuration list. Raises a DataTypeError
           if the value does not conform to the list_item_spec field
           of the module config data specification. If value_str is
           not given, we add the default as specified by the .spec
           file. Raises a DataNotFoundError if the given identifier
           is not specified in the specification as a map or list.
           Raises a DataAlreadyPresentError if the specified element
           already exists."""
        module_spec = self.find_spec_part(identifier)
        if module_spec is None:
            raise isc.cc.data.DataNotFoundError("Unknown item " + str(identifier))

        # for type any, we determine the 'type' by what value is set
        # (which would be either list or dict)
        cur_value, _ = self.get_value(identifier)
        type_any = module_spec['item_type'] == 'any'

        # the specified element must be a list or a named_set
        if 'list_item_spec' in module_spec or\
           (type_any and type(cur_value) == list):
            value = None
            # in lists, we might get the value with spaces, making it
            # the third argument. In that case we interpret both as
            # one big string meant as the value
            if value_str is not None:
                if set_value_str is not None:
                    value_str += set_value_str
                value = isc.cc.data.parse_value_str(value_str)
            self._add_value_to_list(identifier, value, module_spec)
        elif 'named_set_item_spec' in module_spec or\
           (type_any and type(cur_value) == dict):
            item_name = None
            item_value = None
            if value_str is not None:
                item_name = value_str
            if set_value_str is not None:
                item_value = isc.cc.data.parse_value_str(set_value_str)
            else:
                if 'item_default' in module_spec['named_set_item_spec']:
                    item_value = module_spec['named_set_item_spec']['item_default']
            self._add_value_to_named_set(identifier, item_name,
                                         item_value)
        else:
            raise isc.cc.data.DataNotFoundError(str(identifier) + " is not a list or a named set")

    def _remove_value_from_list(self, identifier, value):
        if value is None:
            # we are directly removing a list index
            id, list_indices = isc.cc.data.split_identifier_list_indices(identifier)
            if list_indices is None:
                raise isc.cc.data.DataTypeError("identifier in remove_value() does not contain a list index, and no value to remove")
            else:
                self.set_value(identifier, None)
        else:
            cur_list, status = self.get_value(identifier)
            if not cur_list:
                cur_list = []
            elif value in cur_list:
                cur_list.remove(value)
            self.set_value(identifier, cur_list)

    def _remove_value_from_named_set(self, identifier, value):
        if value is None:
            raise isc.cc.data.DataNotFoundError("Need a name to remove an item from named_set " + str(identifier))
        elif type(value) != str:
            raise isc.cc.data.DataTypeError("Name for named_set " + identifier + " must be a string")
        else:
            cur_map, status = self.get_value(identifier)
            if not cur_map:
                cur_map = {}
            if value in cur_map:
                del cur_map[value]
                self.set_value(identifier, cur_map)
            else:
                raise isc.cc.data.DataNotFoundError(value + " not found in named_set " + str(identifier))

    def remove_value(self, identifier, value_str):
        """Remove a value from a configuration list or named set.
        The value string must be a string representation of the full
        item. Raises a DataTypeError if the value at the identifier
        is not a list, or if the given value_str does not match the
        list_item_spec """
        module_spec = self.find_spec_part(identifier)
        if module_spec is None:
            raise isc.cc.data.DataNotFoundError("Unknown item " + str(identifier))

        value = None
        if value_str is not None:
            value = isc.cc.data.parse_value_str(value_str)

        # for type any, we determine the 'type' by what value is set
        # (which would be either list or dict)
        cur_value, _ = self.get_value(identifier)
        type_any = isc.config.config_data.spec_part_is_any(module_spec)

        # there's two forms of 'remove from list'; the remove-value-from-list
        # form, and the 'remove-by-index' form. We can recognize the second
        # case by value is None
        if 'list_item_spec' in module_spec or\
           (type_any and type(cur_value) == list) or\
           value is None:
            if not type_any and value is not None:
                isc.config.config_data.check_type(module_spec['list_item_spec'], value)
            self._remove_value_from_list(identifier, value)
        elif 'named_set_item_spec' in module_spec or\
           (type_any and type(cur_value) == dict):
            self._remove_value_from_named_set(identifier, value_str)
        else:
            raise isc.cc.data.DataNotFoundError(str(identifier) + " is not a list or a named_set")



    def commit(self):
        """Commit all local changes, send them through b10-cmdctl to
           the configuration manager"""
        if self.get_local_changes():
            response = self._conn.send_POST('/ConfigManager/set_config',
                                            [ self.get_local_changes() ])
            answer = isc.cc.data.parse_value_str(response.read().decode())
            # answer is either an empty dict (on success), or one
            # containing errors
            if answer == {}:
                self.clear_local_changes()
            elif "error" in answer:
                raise ModuleCCSessionError("Error: " + str(answer["error"]) + "\n" + "Configuration not committed")
            else:
                raise ModuleCCSessionError("Unknown format of answer in commit(): " + str(answer))
