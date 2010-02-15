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

from isc.cc import Session
import isc

class CCSessionError(Exception): pass

def parse_answer(msg):
    """Returns a type (rcode, value), where value depends on the command
       that was called. If rcode != 0, value is a string containing
       an error message"""
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
    if arg:
        return { 'result': [ rcode, arg ] }
    else:
        return { 'result': [ 0 ] }

class CCSession:
    def __init__(self, spec_file_name, config_handler, command_handler):
        data_definition = isc.config.data_spec_from_file(spec_file_name)
        self._config_data = isc.config.config_data.ConfigData(data_definition)
        self._module_name = data_definition.get_module_name()
        
        self.set_config_handler(config_handler)
        self.set_command_handler(command_handler)

        self._session = Session()
        self._session.group_subscribe(self._module_name, "*")

    def start(self):
        print("[XX] SEND SPEC AND REQ CONFIG")
        self.__send_spec()
        self.__request_config()

    def get_socket(self):
        """Returns the socket from the command channel session"""
        return self._session._socket
    
    def get_session(self):
        """Returns the command-channel session that is used, so the
           application can use it directly"""
        return self._session

    def set_config(self, new_config):
        return self._config_data.set_local_config(new_config)

    def get_config(self):
        return self._config_data.get_local_config()

    def get_config_data(self):
        return self._config_data

    def close(self):
        self._session.close()

    def check_command(self):
        """Check whether there is a command on the channel.
           Call the command callback function if so"""
        msg, env = self._session.group_recvmsg(False)
        # should we default to an answer? success-by-default? unhandled error?
        answer = None
        try:
            if msg:
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
        self._session.group_sendmsg({ "data_specification": self._config_data.get_specification().get_definition() }, "ConfigManager")
        answer, env = self._session.group_recvmsg(False)
        print("[XX] got answer from cfgmgr:")
        print(answer)
        
    def __request_config(self):
        """Asks the configuration manager for the current configuration, and call the config handler if set"""
        self._session.group_sendmsg({ "command": [ "get_config", { "module_name": self._module_name } ] }, "ConfigManager")
        answer, env = self._session.group_recvmsg(False)
        rcode, value = parse_answer(answer)
        if rcode == 0:
            if self._config_data.get_specification().validate(False, value):
                self._config_data.set_local_config(value);
                if self._config_handler:
                    self._config_handler(value)
        else:
            # log error
            print("Error requesting configuration: " + value)
    
