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
"""This module provides the CCSession class, as well as a set of
   utility functions to create and parse messages related to commands
   and configuration"""

from isc.cc import Session
import isc

class CCSessionError(Exception): pass

def parse_answer(msg):
    """Returns a tuple (rcode, value), where value depends on the
       command that was called. If rcode != 0, value is a string
       containing an error message"""
    if 'result' not in msg:
        raise CCSessionError("answer message does not contain 'result' element")
    elif type(msg['result']) != list:
        raise CCSessionError("wrong result type in answer message")
    elif len(msg['result']) < 1:
        raise CCSessionError("empty result list in answer message")
    elif type(msg['result'][0]) != int:
        raise CCSessionError("wrong rcode type in answer message")
    else:
        if len(msg['result']) > 1:
            return msg['result'][0], msg['result'][1]
        else:
            return msg['result'][0], None

def create_answer(rcode, arg = None):
    """Creates an answer packet for config&commands. rcode must be an
       integer. If rcode == 0, arg is an optional value that depends
       on what the command or option was. If rcode != 0, arg must be
       a string containing an error message"""
    if type(rcode) != int:
        raise CCSessionError("rcode in create_answer() must be an integer")
    if rcode != 0 and type(arg) != str:
        raise CCSessionError("arg in create_answer for rcode != 0 must be a string describing the error")
    if arg != None:
        return { 'result': [ rcode, arg ] }
    else:
        return { 'result': [ rcode ] }

class CCSession:
    """This class maintains a connection to the command channel, as
       well as configuration options for modules. The module provides
       a specification file that contains the module name, configuration
       options, and commands. It also gives the CCSession two callback
       functions, one to call when there is a direct command to the
       module, and one to update the configuration run-time. These
       callbacks are called when 'check_command' is called on the
       CCSession"""
       
    def __init__(self, spec_file_name, config_handler, command_handler):
        """Initialize a CCSession. This does *NOT* send the
           specification and request the configuration yet. Use start()
           for that once the CCSession has been initialized.
           specfile_name is the path to the specification file
           config_handler and command_handler are callback functions,
           see set_config_handler and set_command_handler for more
           information on their signatures."""
        data_definition = isc.config.module_spec_from_file(spec_file_name)
        self._config_data = isc.config.config_data.ConfigData(data_definition)
        self._module_name = data_definition.get_module_name()
        
        self.set_config_handler(config_handler)
        self.set_command_handler(command_handler)

        self._session = Session()
        self._session.group_subscribe(self._module_name, "*")

    def start(self):
        """Send the specification for this module to the configuration
           manager, and request the current non-default configuration.
           The config_handler will be called with that configuration"""
        self.__send_spec()
        self.__request_config()

    def get_socket(self):
        """Returns the socket from the command channel session. This can
           be used in select() loops to see if there is anything on the
           channel. This is not strictly necessary as long as
           check_command is called periodically."""
        return self._session._socket
    
    def get_session(self):
        """Returns the command-channel session that is used, so the
           application can use it directly."""
        return self._session

    def set_config(self, new_config):
        """Sets the current or non-default configuration"""
        return self._config_data.set_local_config(new_config)

    def get_config(self):
        """Returns the current or non-default configuration"""
        return self._config_data.get_local_config()

    def get_full_config(self):
        """Returns the current or non-default configuration"""
        return self._config_data.get_full_config()

    def get_module_spec(self):
        return self._config_data.get_module_spec()

    def close(self):
        """Close the session to the command channel"""
        self._session.close()

    def check_command(self):
        """Check whether there is a command or configuration update
           on the channel. Call the corresponding callback function if
           there is."""
        msg, env = self._session.group_recvmsg(False)
        # should we default to an answer? success-by-default? unhandled error?
        if msg:
            answer = None
            try:
                print("[XX] got msg: ")
                print(msg)
                if "config_update" in msg and self._config_handler:
                    answer = self._config_handler(msg["config_update"])
                if "command" in msg and self._command_handler:
                    answer = self._command_handler(msg["command"])
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

    def __send_spec(self):
        """Sends the data specification to the configuration manager"""
        print("[XX] send spec for " + self._module_name + " to ConfigManager")
        self._session.group_sendmsg({ "module_spec": self._config_data.get_module_spec().get_full_spec() }, "ConfigManager")
        answer, env = self._session.group_recvmsg(False)
        print("[XX] got answer from cfgmgr:")
        print(answer)
        
    def __request_config(self):
        """Asks the configuration manager for the current configuration, and call the config handler if set"""
        self._session.group_sendmsg({ "command": [ "get_config", { "module_name": self._module_name } ] }, "ConfigManager")
        answer, env = self._session.group_recvmsg(False)
        rcode, value = parse_answer(answer)
        if rcode == 0:
            if self._config_data.get_module_spec().validate(False, value):
                self._config_data.set_local_config(value);
                if self._config_handler:
                    self._config_handler(value)
        else:
            # log error
            print("Error requesting configuration: " + value)
    
