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
        # remove these and use self.data_specs
        #self.commands = {}
        self.data_definitions = {}

        self.data_path = data_path
        self.data_specs = {}
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

    def set_data_spec(self, spec):
        #data_def = isc.config.DataDefinition(spec)
        self.data_specs[spec.get_module_name()] = spec

    def get_data_spec(self, module_name):
        if module_name in self.data_specs:
            return self.data_specs[module_name]

    def get_config_data(self, name = None):
        """Returns a dict containing 'module_name': config_data for
           all modules. If name is specified, only that module will
           be included"""
        config_data = {}
        if name:
            if name in self.data_specs:
                config_data[name] = self.data_specs[name].get_data
        else:
            for module_name in self.data_specs.keys():
                config_data[module_name] = self.data_specs[module_name].get_config_data()
        return config_data

    def get_commands(self, name = None):
        """Returns a dict containing 'module_name': commands_dict for
           all modules. If name is specified, only that module will
           be included"""
        commands = {}
        if name:
            if name in self.data_specs:
                commands[name] = self.data_specs[name].get_commands
        else:
            for module_name in self.data_specs.keys():
                commands[module_name] = self.data_specs[module_name].get_commands()
        return commands

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
                    answer = isc.config.ccsession.create_answer(0, self.get_config_data(module_name))
                else:
                    answer = isc.config.ccsession.create_answer(1, "Bad module_name in get_data_spec command")
            else:
                answer = isc.config.ccsession.create_answer(1, "Bad get_data_spec command, argument not a dict")
        else:
            answer = isc.config.ccsession.create_answer(0, self.get_config_data())
        return answer

    def _handle_get_config(self, cmd):
        answer = {}
        if len(cmd) > 1:
            if type(cmd[1]) == dict:
                if 'module_name' in cmd[1] and cmd[1]['module_name'] != '':
                    module_name = cmd[1]['module_name']
                    try:
                        answer = isc.config.ccsession.create_answer(0, data.find(self.config.data, module_name))
                    except data.DataNotFoundError as dnfe:
                        # no data is ok, that means we have nothing that
                        # deviates from default values
                        answer = isc.config.ccsession.create_answer(0, {})
                else:
                    answer = isc.config.ccsession.create_answer(1, "Bad module_name in get_config command")
            else:
                answer = isc.config.ccsession.create_answer(1, "Bad get_config command, argument not a dict")
        else:
            answer = isc.config.ccsession.create_answer(0, self.config.data)
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
                answer, env = self.cc.group_recvmsg(False)
            else:
                conf_part = data.set(self.config.data, module_name, {})
                data.merge(conf_part[module_name], cmd[2])
                # send out changed info
                self.cc.group_sendmsg({ "config_update": conf_part[module_name] }, module_name)
                # replace 'our' answer with that of the module
                answer, env = selc.cc.group_recvmsg(False)
                print("[XX] module responded with")
                print(answer)
            rcode, val = isc.config.ccsession.parse_answer(answer)
            if rcode == 0:
                self.write_config()
        elif len(cmd) == 2:
            # todo: use api (and check the data against the definition?)
            data.merge(self.config.data, cmd[1])
            # send out changed info
            got_error = False
            for module in self.config.data:
                if module != "version":
                    self.cc.group_sendmsg({ "config_update": self.config.data[module] }, module)
                    answer, env = self.cc.group_recvmsg(False)
                    print("[XX] one module responded with")
                    print(answer)
                    rcode, val = isc.config.ccsession.parse_answer(answer)
                    if rcode != 0:
                        got_error = True
            if not got_error:
                self.write_config()
            # TODO rollback changes that did get through?
            # feed back *all* errors?
        else:
            answer = isc.config.ccsession.create_answer(1, "Wrong number of arguments")
        return answer

    def _handle_data_specification(self, spec):
        # todo: validate? (no direct access to spec as
        # todo: use DataDefinition class
        # todo: error checking (like keyerrors)
        answer = {}
        self.set_data_spec(spec)
        print("[XX] cfgmgr add spec:")
        print(spec)
        
        # We should make one general 'spec update for module' that
        # passes both specification and commands at once
        self.cc.group_sendmsg({ "specification_update": [ spec.get_module_name(), spec.get_config_data() ] }, "Cmd-Ctrld")
        self.cc.group_sendmsg({ "commands_update": [ spec.get_module_name(), spec.get_commands() ] }, "Cmd-Ctrld")
        answer = isc.config.ccsession.create_answer(0)
        return answer

    def handle_msg(self, msg):
        """Handle a direct command"""
        answer = {}
        if "command" in msg:
            cmd = msg["command"]
            try:
                if cmd[0] == "get_commands":
                    answer = isc.config.ccsession.create_answer(0, self.get_commands())
                elif cmd[0] == "get_data_spec":
                    answer = self._handle_get_data_spec(cmd)
                elif cmd[0] == "get_config":
                    answer = self._handle_get_config(cmd)
                elif cmd[0] == "set_config":
                    answer = self._handle_set_config(cmd)
                elif cmd[0] == "shutdown":
                    print("[bind-cfgd] Received shutdown command")
                    self.running = False
                    answer = isc.config.ccsession.create_answer(0)
                else:
                    answer = isc.config.ccsession.create_answer(1, "Unknown command: " + str(cmd))
            except IndexError as ie:
                answer = isc.config.ccsession.create_answer(1, "Missing argument in command: " + str(ie))
                raise ie
        elif "data_specification" in msg:
            try:
                answer = self._handle_data_specification(isc.config.DataDefinition(msg["data_specification"]))
            except isc.config.DataDefinitionError as dde:
                answer = isc.config.ccsession.create_answer(1, "Error in data definition: " + str(dde))
        elif 'result' in msg:
            # this seems wrong, might start pingpong
            answer = isc.config.ccsession.create_answer(0)
        else:
            answer = isc.config.ccsession.create_answer(1, "Unknown message format: " + str(msg))
        return answer
        
    def run(self):
        self.running = True
        while (self.running):
            msg, env = self.cc.group_recvmsg(False)
            if msg:
                answer = self.handle_msg(msg);
                print("[XX] CFGMGR Sending answer to UI:")
                print(answer)
                print("For command")
                print(msg)
                self.cc.group_reply(env, answer)
            else:
                self.running = False

cm = None

def signal_handler(signal, frame):
    global cm
    if cm:
        cm.running = False
