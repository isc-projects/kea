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

from ISC.CC import Session
import isc

class CCSession:
    def __init__(self, module_name, spec_file_name,
                 config_handler, command_handler):
        self._module_name = module_name
        #self._spec_file_name = spec_file_name
        self.setConfigHandler(config_handler)
        self.setCommandHandler(command_handler)

        self._data_definition = isc.config.DataDefinition(spec_file_name)

        self._session = Session()
        self._session.group_subscribe(module_name, "*")

        self.__sendSpec()
        self.__getFullConfig()

    #do we need getSocket()?

    def checkCommand():
        """Check whether there is a command on the channel.
           Call the command callback function if so"""
        msg, env = self._session.group_recvmsg(False)
        answer = None
        if msg:
            if "config_update" in msg and self._config_handler:
                self._config_handler(msg["config_update"])
                answer = { "result": [ 0 ] }
            if "command" in msg and self._command_handler:
                answer = self._command_handler(msg["command"])
        if answer:
            self._session.group_reply(env, answer)

    
    def setConfigHandler(self, config_handler):
        """Set the config handler for this module. The handler is a
           function that takes the full configuration and handles it.
           It should return either { "result": [ 0 ] } or
           { "result": [ <error_number>, "error message" ] }"""
        self._config_handler = config_handler
        # should we run this right now since we've changed the handler?

    def setCommandHandler(self, command_handler):
        """Set the command handler for this module. The handler is a
           function that takes a command as defined in the .spec file
           and return either { "result": [ 0, (result) ] } or
           { "result": [ <error_number>. "error message" ] }"""
        self._command_handler = command_handler

    def __sendSpec(self):
        """Sends the data specification to the configuration manager"""
        self._session.group_sendmsg(self._data_definition.getDefinition(), "ConfigManager")
        answer, env = self._session.group_recvmsg(False)
        
    def __getFullConfig(self):
        """Asks the configuration manager for the current configuration, and call the config handler if set"""
        self._session.group_sendmsg({ "command": [ "get_config", { "module_name": self._module_name } ] }, "ConfigManager")
        answer, env = self._session.group_recvmsg(False)
        if self._config_handler:
            self._config_handler(answer["result"])
    
