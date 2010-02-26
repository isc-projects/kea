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

"""This is the BIND 10 configuration manager, run by b10-cfgmgr.

   It stores the system configuration, and sends updates of the
   configuration to the modules that need them.
"""

import isc
import signal
import ast
import pprint
import os
from isc.cc import data

class ConfigManagerDataReadError(Exception):
    """This exception is thrown when there is an error while reading
       the current configuration on startup."""
    pass

class ConfigManagerDataEmpty(Exception):
    """This exception is thrown when the currently stored configuration
       is not found, or appears empty."""
    pass

class ConfigManagerData:
    """This class hold the actual configuration information, and
       reads it from and writes it to persistent storage"""

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
                raise ConfigManagerDataReadError("[b10-cfgmgr] Old version of data found")
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
            if output_file_name:
                os.rename(tmp_filename, output_file_name)
            else:
                os.rename(tmp_filename, self.db_filename)
        except IOError as ioe:
            # TODO: log this (level critical)
            print("[b10-cfgmgr] Unable to write config file; configuration not stored: " + str(ioe))
        except OSError as ose:
            # TODO: log this (level critical)
            print("[b10-cfgmgr] Unable to write config file; configuration not stored: " + str(ose))

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
        """Initialize the configuration manager. The data_path string
           is the path to the directory where the configuration is
           stored (in <data_path>/b10-config.db). Session is an optional
           cc-channel session. If this is not given, a new one is
           created"""
        self.data_path = data_path
        self.module_specs = {}
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

    def set_module_spec(self, spec):
        """Adds a ModuleSpec"""
        self.module_specs[spec.get_module_name()] = spec

    def remove_module_spec(self, module_name):
        """Removes the full ModuleSpec for the given module_name.
           Does nothing if the module was not present."""
        if module_name in self.module_specs:
            del self.module_specs[module_name]

    def get_module_spec(self, module_name):
        """Returns the full ModuleSpec for the module with the given
           module_name"""
        if module_name in self.module_specs:
            return self.module_specs[module_name]

    def get_config_spec(self, name = None):
        """Returns a dict containing 'module_name': config_spec for
           all modules. If name is specified, only that module will
           be included"""
        config_data = {}
        if name:
            if name in self.module_specs:
                config_data[name] = self.module_specs[name].get_config_spec()
        else:
            for module_name in self.module_specs.keys():
                config_data[module_name] = self.module_specs[module_name].get_config_spec()
        return config_data

    def get_commands_spec(self, name = None):
        """Returns a dict containing 'module_name': commands_spec for
           all modules. If name is specified, only that module will
           be included"""
        commands = {}
        if name:
            if name in self.module_specs:
                commands[name] = self.module_specs[name].get_commands_spec()
        else:
            for module_name in self.module_specs.keys():
                commands[module_name] = self.module_specs[module_name].get_commands_spec()
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

    def _handle_get_module_spec(self, cmd):
        """Private function that handles the 'get_module_spec' command"""
        answer = {}
        if cmd != None:
            if type(cmd) == dict:
                if 'module_name' in cmd and cmd['module_name'] != '':
                    module_name = cmd['module_name']
                    answer = isc.config.ccsession.create_answer(0, self.get_config_spec(module_name))
                else:
                    answer = isc.config.ccsession.create_answer(1, "Bad module_name in get_module_spec command")
            else:
                answer = isc.config.ccsession.create_answer(1, "Bad get_module_spec command, argument not a dict")
        else:
            answer = isc.config.ccsession.create_answer(0, self.get_config_spec())
        return answer

    def _handle_get_config(self, cmd):
        """Private function that handles the 'get_config' command"""
        answer = {}
        if cmd != None:
            if type(cmd) == dict:
                if 'module_name' in cmd and cmd['module_name'] != '':
                    module_name = cmd['module_name']
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
        """Private function that handles the 'set_config' command"""
        answer = None
        if cmd == None:
            return isc.config.ccsession.create_answer(1, "Wrong number of arguments")
        if len(cmd) == 2:
            # todo: use api (and check the data against the definition?)
            module_name = cmd[0]
            conf_part = data.find_no_exc(self.config.data, module_name)
            if conf_part:
                data.merge(conf_part, cmd[1])
                update_cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, conf_part)
                self.cc.group_sendmsg(update_cmd, module_name)
                answer, env = self.cc.group_recvmsg(False)
            else:
                conf_part = data.set(self.config.data, module_name, {})
                data.merge(conf_part[module_name], cmd[1])
                # send out changed info
                update_cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, conf_part[module_name])
                self.cc.group_sendmsg(update_cmd, module_name)
                # replace 'our' answer with that of the module
                answer, env = self.cc.group_recvmsg(False)
            if answer:
                rcode, val = isc.config.ccsession.parse_answer(answer)
                if rcode == 0:
                    self.write_config()
        elif len(cmd) == 1:
            # todo: use api (and check the data against the definition?)
            old_data = self.config.data.copy()
            data.merge(self.config.data, cmd[0])
            # send out changed info
            got_error = False
            err_list = []
            for module in self.config.data:
                if module != "version":
                    update_cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, self.config.data[module])
                    self.cc.group_sendmsg(update_cmd, module)
                    answer, env = self.cc.group_recvmsg(False)
                    if answer == None:
                        got_error = True
                        err_list.append("No answer message from " + module)
                    else:
                        rcode, val = isc.config.ccsession.parse_answer(answer)
                        if rcode != 0:
                            got_error = True
                            err_list.append(val)
            if not got_error:
                self.write_config()
                answer = isc.config.ccsession.create_answer(0)
            else:
                # TODO rollback changes that did get through, should we re-send update?
                self.config.data = old_data
                answer = isc.config.ccsession.create_answer(1, " ".join(err_list))
        else:
            print(cmd)
            answer = isc.config.ccsession.create_answer(1, "Wrong number of arguments")
        if not answer:
            answer = isc.config.ccsession.create_answer(1, "No answer message from " + cmd[0])
            
        return answer

    def _handle_module_spec(self, spec):
        """Private function that handles the 'module_spec' command"""
        # todo: validate? (no direct access to spec as
        # todo: use ModuleSpec class
        # todo: error checking (like keyerrors)
        answer = {}
        self.set_module_spec(spec)
        
        # We should make one general 'spec update for module' that
        # passes both specification and commands at once
        spec_update = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_SPECIFICATION_UPDATE,
                                                          [ spec.get_module_name(), spec.get_config_spec() ])
        self.cc.group_sendmsg(spec_update, "Cmd-Ctrld")
        cmds_update = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_COMMANDS_UPDATE,
                                                          [ spec.get_module_name(), spec.get_commands_spec() ])
        self.cc.group_sendmsg(cmds_update, "Cmd-Ctrld")
        answer = isc.config.ccsession.create_answer(0)
        return answer

    def handle_msg(self, msg):
        """Handle a command from the cc channel to the configuration manager"""
        answer = {}
        cmd, arg = isc.config.ccsession.parse_command(msg)
        if cmd:
            if cmd == isc.config.ccsession.COMMAND_GET_COMMANDS_SPEC:
                answer = isc.config.ccsession.create_answer(0, self.get_commands_spec())
            elif cmd == isc.config.ccsession.COMMAND_GET_MODULE_SPEC:
                answer = self._handle_get_module_spec(arg)
            elif cmd == isc.config.ccsession.COMMAND_GET_CONFIG:
                answer = self._handle_get_config(arg)
            elif cmd == isc.config.ccsession.COMMAND_SET_CONFIG:
                answer = self._handle_set_config(arg)
            elif cmd == "shutdown":
                # TODO: logging
                print("[b10-cfgmgr] Received shutdown command")
                self.running = False
                answer = isc.config.ccsession.create_answer(0)
            elif cmd == isc.config.ccsession.COMMAND_MODULE_SPEC:
                try:
                    answer = self._handle_module_spec(isc.config.ModuleSpec(arg))
                except isc.config.ModuleSpecError as dde:
                    answer = isc.config.ccsession.create_answer(1, "Error in data definition: " + str(dde))
            else:
                answer = isc.config.ccsession.create_answer(1, "Unknown command: " + str(cmd))
        else:
            answer = isc.config.ccsession.create_answer(1, "Unknown message format: " + str(msg))
        return answer
        
    def run(self):
        """Runs the configuration manager."""
        self.running = True
        while (self.running):
            msg, env = self.cc.group_recvmsg(False)
            if msg and not 'result' in msg:
                answer = self.handle_msg(msg);
                self.cc.group_reply(env, answer)
            else:
                self.running = False
