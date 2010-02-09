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

#
# This is the main class for the b10-cfgmgr daemon
#

import isc
import signal
import ast
import pprint
import os
from isc.cc import data

class ConfigManagerDataReadError(Exception):
    pass

class ConfigManagerDataEmpty(Exception):
    pass

class ConfigManagerData:
    CONFIG_VERSION = 1

    def __init__(self, data_path, file_name = "b10-config.db"):
        """Initialize the data for the configuration manager, and
           set the version and path for the data store. Initializing
           this does not yet read the database, a call to
           read_from_file is needed for that."""
        self.data = {}
        self.data['version'] = ConfigManagerData.CONFIG_VERSION
        self.data_path = data_path
        self.db_filename = data_path + os.sep + file_name

    def set_data_definition(self, module_name, module_data_definition):
        """Set the data definition for the given module name."""
        #self.zones[module_name] = module_data_definition
        self.data_definitions[module_name] = module_data_definition

    def read_from_file(data_path, file_name = "b10-config.db"):
        """Read the current configuration found in the file at
           data_path. If the file does not exist, a
           ConfigManagerDataEmpty exception is raised. If there is a
           parse error, or if the data in the file has the wrong
           version, a ConfigManagerDataReadError is raised. In the first
           case, it is probably safe to log and ignore. In the case of
           the second exception, the best way is probably to report the
           error and stop loading the system."""
        config = ConfigManagerData(data_path, file_name)
        try:
            file = open(config.db_filename, 'r')
            file_config = ast.literal_eval(file.read())
            if 'version' in file_config and \
                file_config['version'] == ConfigManagerData.CONFIG_VERSION:
                config.data = file_config
            else:
                # We can put in a migration path here for old data
                raise ConfigManagerDataReadError("[bind-cfgd] Old version of data found")
            file.close()
        except IOError as ioe:
            raise ConfigManagerDataEmpty("No config file found")
        except:
            raise ConfigManagerDataReadError("Config file unreadable")

        return config
        
    def write_to_file(self, output_file_name = None):
        """Writes the current configuration data to a file. If
           output_file_name is not specified, the file used in
           read_from_file is used."""
        try:
            tmp_filename = self.db_filename + ".tmp"
            file = open(tmp_filename, 'w');
            pp = pprint.PrettyPrinter(indent=4)
            s = pp.pformat(self.data)
            file.write(s)
            file.write("\n")
            file.close()
            os.rename(tmp_filename, self.db_filename)
        except IOError as ioe:
            print("Unable to write config file; configuration not stored")

    def __eq__(self, other):
        """Returns True if the data contained is equal. data_path and
           db_filename may be different."""
        if type(other) != type(self):
            return False
        return self.data == other.data

class ConfigManager:
    """Creates a configuration manager. The data_path is the path
       to the directory containing the b10-config.db file.
       If session is set, this will be used as the communication
       channel session. If not, a new session will be created.
       The ability to specify a custom session is for testing purposes
       and should not be needed for normal usage."""
    def __init__(self, data_path, session = None):
        self.commands = {}
        self.data_definitions = {}
        self.data_path = data_path
        self.config = ConfigManagerData(data_path)
        if session:
            self.cc = session
        else:
            self.cc = isc.cc.Session()
        self.cc.group_subscribe("ConfigManager")
        self.cc.group_subscribe("Boss", "ConfigManager")
        self.running = False

    def notify_boss(self):
        """Notifies the Boss module that the Config Manager is running"""
        self.cc.group_sendmsg({"running": "configmanager"}, "Boss")

    def set_config(self, module_name, data_specification):
        """Set the data specification for the given module"""
        self.data_definitions[module_name] = data_specification
        
    def remove_config(self, module_name):
        """Remove the data specification for the given module"""
        self.data_definitions[module_name]

    def set_commands(self, module_name, commands):
        """Set the command list for the given module"""
        self.commands[module_name] = commands

    def remove_commands(self, module_name):
        """Remove the command list for the given module"""
        del self.commands[module_name]

    def read_config(self):
        """Read the current configuration from the b10-config.db file
           at the path specificied at init()"""
        try:
            self.config = ConfigManagerData.read_from_file(self.data_path)
        except ConfigManagerDataEmpty:
            # ok, just start with an empty config
            self.config = ConfigManagerData(self.data_path)
        
    def write_config(self):
        """Write the current configuration to the b10-config.db file
           at the path specificied at init()"""
        self.config.write_to_file()

    def _handle_get_data_spec(self, cmd):
        answer = {}
        if len(cmd) > 1:
            if type(cmd[1]) == dict:
                if 'module_name' in cmd[1] and cmd[1]['module_name'] != '':
                    module_name = cmd[1]['module_name']
                    try:
                        answer["result"] = [0, self.data_definitions[module_name]]
                    except KeyError as ke:
                        answer["result"] = [1, "No specification for module " + module_name]
                else:
                    answer["result"] = [1, "Bad module_name in get_data_spec command"]
            else:
                answer["result"] = [1, "Bad get_data_spec command, argument not a dict"]
        else:
            answer["result"] = [0, self.data_definitions]
        return answer

    def _handle_get_config(self, cmd):
        answer = {}
        if len(cmd) > 1:
            if type(cmd[1]) == dict:
                if 'module_name' in cmd[1] and cmd[1]['module_name'] != '':
                    module_name = cmd[1]['module_name']
                    try:
                        answer["result"] = [0, data.find(self.config.data, module_name) ]
                    except data.DataNotFoundError as dnfe:
                        # no data is ok, that means we have nothing that
                        # deviates from default values
                        answer["result"] = [0, {} ]
                else:
                    answer["result"] = [1, "Bad module_name in get_config command"]
            else:
                answer["result"] = [1, "Bad get_config command, argument not a dict"]
        else:
            answer["result"] = [0, self.config.data]
        return answer

    def _handle_set_config(self, cmd):
        answer = {}
        if len(cmd) == 3:
            # todo: use api (and check the data against the definition?)
            module_name = cmd[1]
            conf_part = data.find_no_exc(self.config.data, module_name)
            if conf_part:
                data.merge(conf_part, cmd[2])
                self.cc.group_sendmsg({ "config_update": conf_part }, module_name)
            else:
                conf_part = data.set(self.config.data, module_name, {})
                data.merge(conf_part[module_name], cmd[2])
                # send out changed info
                self.cc.group_sendmsg({ "config_update": conf_part[module_name] }, module_name)
            self.write_config()
            answer["result"] = [ 0 ]
        elif len(cmd) == 2:
            # todo: use api (and check the data against the definition?)
            data.merge(self.config.data, cmd[1])
            # send out changed info
            for module in self.config.data:
                if module != "version":
                    self.cc.group_sendmsg({ "config_update": self.config.data[module] }, module)
            self.write_config()
            answer["result"] = [ 0 ]
        else:
            answer["result"] = [ 1, "Wrong number of arguments" ]
        return answer

    def _handle_data_specification(self, spec):
        # todo: validate? (no direct access to spec as
        # todo: use DataDefinition class
        # todo: error checking (like keyerrors)
        answer = {}
        if "config_data" in spec:
            self.set_config(spec["module_name"], spec["config_data"])
            self.cc.group_sendmsg({ "specification_update": [ spec["module_name"], spec["config_data"] ] }, "Cmd-Ctrld")
        if "commands" in spec:
            self.set_commands(spec["module_name"], spec["commands"])
            self.cc.group_sendmsg({ "commands_update": [ spec["module_name"], spec["commands"] ] }, "Cmd-Ctrld")
        answer["result"] = [ 0 ]
        return answer

    def handle_msg(self, msg):
        """Handle a direct command"""
        answer = {}
        if "command" in msg:
            cmd = msg["command"]
            try:
                if cmd[0] == "get_commands":
                    answer["result"] = [ 0, self.commands ]

                elif cmd[0] == "get_data_spec":
                    answer = self._handle_get_data_spec(cmd)
                elif cmd[0] == "get_config":
                    answer = self._handle_get_config(cmd)
                elif cmd[0] == "set_config":
                    answer = self._handle_set_config(cmd)
                elif cmd[0] == "shutdown":
                    print("[bind-cfgd] Received shutdown command")
                    self.running = False
                    answer["result"] = [ 0 ]
                else:
                    answer["result"] = [ 1, "Unknown command: " + str(cmd) ]
            except IndexError as ie:
                answer["result"] = [ 1, "Missing argument in command: " + str(ie) ]
                raise ie
        elif "data_specification" in msg:
            answer = self._handle_data_specification(msg["data_specification"])
        elif 'result' in msg:
            # this seems wrong, might start pingpong
            answer['result'] = [0]
        else:
            answer["result"] = [ 1, "Unknown message format: " + str(msg) ]
        return answer
        
    def run(self):
        self.running = True
        while (self.running):
            msg, env = self.cc.group_recvmsg(False)
            if msg:
                answer = self.handle_msg(msg);
                self.cc.group_reply(env, answer)
            else:
                self.running = False

cm = None

def signal_handler(signal, frame):
    global cm
    if cm:
        cm.running = False
