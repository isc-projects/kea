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
import os
import copy
import tempfile
import json
from isc.cc import data
from isc.config import ccsession, config_data

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

    def __init__(self, data_path, file_name = "b10-config.db"):
        """Initialize the data for the configuration manager, and
           set the version and path for the data store. Initializing
           this does not yet read the database, a call to
           read_from_file is needed for that."""
        self.data = {}
        self.data['version'] = config_data.BIND10_CONFIG_DATA_VERSION
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
        file = None
        try:
            file = open(config.db_filename, 'r')
            file_config = json.loads(file.read())
            # handle different versions here
            # If possible, we automatically convert to the new
            # scheme and update the configuration
            # If not, we raise an exception
            if 'version' in file_config:
                if file_config['version'] == config_data.BIND10_CONFIG_DATA_VERSION:
                    config.data = file_config
                elif file_config['version'] == 1:
                    # only format change, no other changes necessary
                    file_config['version'] = 2
                    print("[b10-cfgmgr] Updating configuration database version from 1 to 2")
                    config.data = file_config
                else:
                    if config_data.BIND10_CONFIG_DATA_VERSION > file_config['version']:
                        raise ConfigManagerDataReadError("Cannot load configuration file: version %d no longer supported" % file_config['version'])
                    else:
                        raise ConfigManagerDataReadError("Cannot load configuration file: version %d not yet supported" % file_config['version'])
            else:
                raise ConfigManagerDataReadError("No version information in configuration file " + config.db_filename)
        except IOError as ioe:
            raise ConfigManagerDataEmpty("No configuration file found")
        except ValueError:
            raise ConfigManagerDataReadError("Configuration file out of date or corrupt, please update or remove " + config.db_filename)
        finally:
            if file:
                file.close();
        return config
        
    def write_to_file(self, output_file_name = None):
        """Writes the current configuration data to a file. If
           output_file_name is not specified, the file used in
           read_from_file is used."""
        filename = None
        try:
            file = tempfile.NamedTemporaryFile(mode='w',
                                               prefix="b10-config.db.",
                                               dir=self.data_path,
                                               delete=False)
            filename = file.name
            file.write(json.dumps(self.data))
            file.write("\n")
            file.close()
            if output_file_name:
                os.rename(filename, output_file_name)
            else:
                os.rename(filename, self.db_filename)
        except IOError as ioe:
            # TODO: log this (level critical)
            print("[b10-cfgmgr] Unable to write configuration file; configuration not stored: " + str(ioe))
            # TODO: debug option to keep file?
        except OSError as ose:
            # TODO: log this (level critical)
            print("[b10-cfgmgr] Unable to write configuration file; configuration not stored: " + str(ose))
        try:
            if filename and os.path.exists(filename):
                os.remove(filename)
        except OSError:
            # Ok if we really can't delete it anymore, leave it
            pass

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

    def get_module_spec(self, module_name = None):
        """Returns the full ModuleSpec for the module with the given
           module_name. If no module name is given, a dict will
           be returned with 'name': module_spec values. If the
           module name is given, but does not exist, an empty dict
           is returned"""
        if module_name:
            if module_name in self.module_specs:
                return self.module_specs[module_name]
            else:
                # TODO: log error?
                return {}
        else:
            result = {}
            for module in self.module_specs:
                result[module] = self.module_specs[module].get_full_spec()
            return result

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
                    answer = ccsession.create_answer(0, self.get_module_spec(module_name))
                else:
                    answer = ccsession.create_answer(1, "Bad module_name in get_module_spec command")
            else:
                answer = ccsession.create_answer(1, "Bad get_module_spec command, argument not a dict")
        else:
            answer = ccsession.create_answer(0, self.get_module_spec())
        return answer

    def _handle_get_config_dict(self, cmd):
        """Private function that handles the 'get_config' command
           where the command has been checked to be a dict"""
        if 'module_name' in cmd and cmd['module_name'] != '':
            module_name = cmd['module_name']
            try:
                return ccsession.create_answer(0, data.find(self.config.data, module_name))
            except data.DataNotFoundError as dnfe:
                # no data is ok, that means we have nothing that
                # deviates from default values
                return ccsession.create_answer(0, { 'version': config_data.BIND10_CONFIG_DATA_VERSION })
        else:
            return ccsession.create_answer(1, "Bad module_name in get_config command")

    def _handle_get_config(self, cmd):
        """Private function that handles the 'get_config' command"""
        if cmd != None:
            if type(cmd) == dict:
                return self._handle_get_config_dict(cmd)
            else:
                return ccsession.create_answer(1, "Bad get_config command, argument not a dict")
        else:
            return ccsession.create_answer(0, self.config.data)

    def _handle_set_config_module(self, cmd):
        # the answer comes (or does not come) from the relevant module
        # so we need a variable to see if we got it
        answer = None
        # todo: use api (and check the data against the definition?)
        old_data = copy.deepcopy(self.config.data)
        module_name = cmd[0]
        conf_part = data.find_no_exc(self.config.data, module_name)
        if conf_part:
            data.merge(conf_part, cmd[1])
            update_cmd = ccsession.create_command(ccsession.COMMAND_CONFIG_UPDATE,
                                                  conf_part)
            seq = self.cc.group_sendmsg(update_cmd, module_name)
            answer, env = self.cc.group_recvmsg(False, seq)
        else:
            conf_part = data.set(self.config.data, module_name, {})
            data.merge(conf_part[module_name], cmd[1])
            # send out changed info
            update_cmd = ccsession.create_command(ccsession.COMMAND_CONFIG_UPDATE,
                                                  conf_part[module_name])
            seq = self.cc.group_sendmsg(update_cmd, module_name)
            # replace 'our' answer with that of the module
            answer, env = self.cc.group_recvmsg(False, seq)
        if answer:
            rcode, val = ccsession.parse_answer(answer)
            if rcode == 0:
                self.write_config()
            else:
                self.config.data = old_data
        return answer

    def _handle_set_config_all(self, cmd):
        old_data = copy.deepcopy(self.config.data)
        data.merge(self.config.data, cmd[0])
        # send out changed info
        got_error = False
        err_list = []
        for module in self.config.data:
            if module != "version" and \
               (module not in old_data or self.config.data[module] != old_data[module]):
                update_cmd = ccsession.create_command(ccsession.COMMAND_CONFIG_UPDATE,
                                                      self.config.data[module])
                seq = self.cc.group_sendmsg(update_cmd, module)
                answer, env = self.cc.group_recvmsg(False, seq)
                if answer == None:
                    got_error = True
                    err_list.append("No answer message from " + module)
                else:
                    rcode, val = ccsession.parse_answer(answer)
                    if rcode != 0:
                        got_error = True
                        err_list.append(val)
        if not got_error:
            self.write_config()
            return ccsession.create_answer(0)
        else:
            # TODO rollback changes that did get through, should we re-send update?
            self.config.data = old_data
            return ccsession.create_answer(1, " ".join(err_list))

    def _handle_set_config(self, cmd):
        """Private function that handles the 'set_config' command"""
        answer = None
        if cmd == None:
            return ccsession.create_answer(1, "Wrong number of arguments")
        if len(cmd) == 2:
            answer = self._handle_set_config_module(cmd)
        elif len(cmd) == 1:
            answer = self._handle_set_config_all(cmd)
        else:
            answer = ccsession.create_answer(1, "Wrong number of arguments")
        if not answer:
            answer = ccsession.create_answer(1, "No answer message from " + cmd[0])
            
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
        spec_update = ccsession.create_command(ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE,
                                               [ spec.get_module_name(), spec.get_full_spec() ])
        self.cc.group_sendmsg(spec_update, "Cmdctl")
        return ccsession.create_answer(0)

    def handle_msg(self, msg):
        """Handle a command from the cc channel to the configuration manager"""
        answer = {}
        cmd, arg = ccsession.parse_command(msg)
        if cmd:
            if cmd == ccsession.COMMAND_GET_COMMANDS_SPEC:
                answer = ccsession.create_answer(0, self.get_commands_spec())
            elif cmd == ccsession.COMMAND_GET_MODULE_SPEC:
                answer = self._handle_get_module_spec(arg)
            elif cmd == ccsession.COMMAND_GET_CONFIG:
                answer = self._handle_get_config(arg)
            elif cmd == ccsession.COMMAND_SET_CONFIG:
                answer = self._handle_set_config(arg)
            elif cmd == ccsession.COMMAND_SHUTDOWN:
                # TODO: logging
                #print("[b10-cfgmgr] Received shutdown command")
                self.running = False
                answer = ccsession.create_answer(0)
            elif cmd == ccsession.COMMAND_MODULE_SPEC:
                try:
                    answer = self._handle_module_spec(isc.config.ModuleSpec(arg))
                except isc.config.ModuleSpecError as dde:
                    answer = ccsession.create_answer(1, "Error in data definition: " + str(dde))
            else:
                answer = ccsession.create_answer(1, "Unknown command: " + str(cmd))
        else:
            answer = ccsession.create_answer(1, "Unknown message format: " + str(msg))
        return answer
        
    def run(self):
        """Runs the configuration manager."""
        self.running = True
        while (self.running):
            msg, env = self.cc.group_recvmsg(False)
            # ignore 'None' value (current result of timeout)
            # and messages that are answers to questions we did
            # not ask
            if msg is not None and not 'result' in msg:
                answer = self.handle_msg(msg);
                self.cc.group_reply(env, answer)
