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
import errno
from isc.cc import data
from isc.config import ccsession, config_data, module_spec
from isc.util.file import path_search
import bind10_config
import isc.log
from isc.log_messages.cfgmgr_messages import *

logger = isc.log.Logger("cfgmgr")

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

    def __init__(self, data_path, file_name):
        """Initialize the data for the configuration manager, and
           set the version and path for the data store. Initializing
           this does not yet read the database, a call to
           read_from_file is needed for that.

           In case the file_name is absolute, data_path is ignored
           and the directory where the file_name lives is used instead.
           """
        self.data = {}
        self.data['version'] = config_data.BIND10_CONFIG_DATA_VERSION
        if os.path.isabs(file_name):
            self.db_filename = file_name
            self.data_path = os.path.dirname(file_name)
        else:
            self.db_filename = data_path + os.sep + file_name
            self.data_path = data_path

    def read_from_file(data_path, file_name):
        """Read the current configuration found in the file file_name.
           If file_name is absolute, data_path is ignored. Otherwise
           we look for the file_name in data_path directory.

           If the file does not exist, a ConfigManagerDataEmpty exception is
           raised. If there is a parse error, or if the data in the file has
           the wrong version, a ConfigManagerDataReadError is raised. In the
           first case, it is probably safe to log and ignore. In the case of
           the second exception, the best way is probably to report the error
           and stop loading the system.
           """
        config = ConfigManagerData(data_path, file_name)
        logger.info(CFGMGR_CONFIG_FILE, config.db_filename)
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
                    logger.info(CFGMGR_AUTOMATIC_CONFIG_DATABASE_UPDATE, 1, 2)
                    config.data = file_config
                else:
                    if config_data.BIND10_CONFIG_DATA_VERSION > file_config['version']:
                        raise ConfigManagerDataReadError("Cannot load configuration file: version %d no longer supported" % file_config['version'])
                    else:
                        raise ConfigManagerDataReadError("Cannot load configuration file: version %d not yet supported" % file_config['version'])
            else:
                raise ConfigManagerDataReadError("No version information in configuration file " + config.db_filename)
        except IOError as ioe:
            # if IOError is 'no such file or directory', then continue
            # (raise empty), otherwise fail (raise error)
            if ioe.errno == errno.ENOENT:
                raise ConfigManagerDataEmpty("No configuration file found")
            else:
                raise ConfigManagerDataReadError("Can't read configuration file: " + str(ioe))
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
            logger.error(CFGMGR_IOERROR_WHILE_WRITING_CONFIGURATION, ioe)
        except OSError as ose:
            logger.error(CFGMGR_OSERROR_WHILE_WRITING_CONFIGURATION, ose)
        try:
            if filename and os.path.exists(filename):
                os.remove(filename)
        except OSError:
            # Ok if we really can't delete it anymore, leave it
            pass

    def rename_config_file(self, old_file_name=None, new_file_name=None):
        """Renames the given configuration file to the given new file name,
           if it exists. If it does not exist, nothing happens.
           If old_file_name is None (default), the file used in
           read_from_file is used. If new_file_name is None (default), the
           file old_file_name appended with .bak is used. If that file exists
           already, .1 is appended. If that file exists, .2 is appended, etc.
        """
        if old_file_name is None:
            old_file_name = self.db_filename
        if new_file_name is None:
            new_file_name = old_file_name + ".bak"
        if os.path.exists(new_file_name):
            i = 1
            while os.path.exists(new_file_name + "." + str(i)):
                i += 1
            new_file_name = new_file_name + "." + str(i)
        if os.path.exists(old_file_name):
            logger.info(CFGMGR_BACKED_UP_CONFIG_FILE, old_file_name, new_file_name)
            os.rename(old_file_name, new_file_name)

    def __eq__(self, other):
        """Returns True if the data contained is equal. data_path and
           db_filename may be different."""
        if type(other) != type(self):
            return False
        return self.data == other.data

class ConfigManager:
    """Creates a configuration manager. The data_path is the path
       to the directory containing the configuraton file,
       database_filename points to the configuration file.
       If session is set, this will be used as the communication
       channel session. If not, a new session will be created.
       The ability to specify a custom session is for testing purposes
       and should not be needed for normal usage."""
    def __init__(self, data_path, database_filename, session=None,
                 clear_config=False):
        """Initialize the configuration manager. The data_path string
           is the path to the directory where the configuration is
           stored (in <data_path>/<database_filename> or in
           <database_filename>, if it is absolute). The database_filename
           is the config file to load. Session is an optional
           cc-channel session. If this is not given, a new one is
           created. If clear_config is True, the configuration file is
           renamed and a new one is created."""
        self.data_path = data_path
        self.database_filename = database_filename
        self.module_specs = {}
        # Virtual modules are the ones which have no process running. The
        # checking of validity is done by functions presented here instead
        # of some other process
        self.virtual_modules = {}
        self.config = ConfigManagerData(data_path, database_filename)
        if clear_config:
            self.config.rename_config_file()
        if session:
            self.cc = session
        else:
            self.cc = isc.cc.Session()
        self.cc.group_subscribe("ConfigManager")
        self.cc.group_subscribe("Boss", "ConfigManager")
        self.running = False
        # As a core module, CfgMgr is different than other modules,
        # as it does not use a ModuleCCSession, and hence needs
        # to handle logging config on its own
        self.log_config_data = config_data.ConfigData(
            isc.config.module_spec_from_file(
                path_search('logging.spec',
                bind10_config.PLUGIN_PATHS)))
        # store the logging 'module' name for easier reference
        self.log_module_name = self.log_config_data.get_module_spec().get_module_name()

    def check_logging_config(self, config):
        if self.log_module_name in config:
            ccsession.default_logconfig_handler(config[self.log_module_name],
                                                self.log_config_data)
        else:
            ccsession.default_logconfig_handler({}, self.log_config_data)

    def notify_boss(self):
        """Notifies the Boss module that the Config Manager is running"""
        self.cc.group_sendmsg({"running": "ConfigManager"}, "Boss")

    def set_module_spec(self, spec):
        """Adds a ModuleSpec"""
        self.module_specs[spec.get_module_name()] = spec

    def set_virtual_module(self, spec, check_func):
        """Adds a virtual module with its spec and checking function."""
        self.module_specs[spec.get_module_name()] = spec
        self.virtual_modules[spec.get_module_name()] = check_func

    def remove_module_spec(self, module_name):
        """Removes the full ModuleSpec for the given module_name.
           Also removes the virtual module check function if it
           was present.
           Does nothing if the module was not present."""
        if module_name in self.module_specs:
            del self.module_specs[module_name]
        if module_name in self.virtual_modules:
            del self.virtual_modules[module_name]

    def get_module_spec(self, module_name = None):
        """Returns the full ModuleSpec for the module with the given
           module_name. If no module name is given, a dict will
           be returned with 'name': module_spec values. If the
           module name is given, but does not exist, an empty dict
           is returned"""
        if module_name:
            if module_name in self.module_specs:
                return self.module_specs[module_name].get_full_spec()
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

    def get_statistics_spec(self, name = None):
        """Returns a dict containing 'module_name': statistics_spec for
           all modules. If name is specified, only that module will
           be included"""
        statistics = {}
        if name:
            if name in self.module_specs:
                statistics[name] = self.module_specs[name].get_statistics_spec()
        else:
            for module_name in self.module_specs.keys():
                statistics[module_name] = self.module_specs[module_name].get_statistics_spec()
        return statistics

    def read_config(self):
        """Read the current configuration from the file specificied at init()"""
        try:
            self.config = ConfigManagerData.read_from_file(self.data_path,
                                                           self.\
                                                           database_filename)
        except ConfigManagerDataEmpty:
            # ok, just start with an empty config
            self.config = ConfigManagerData(self.data_path,
                                            self.database_filename)
        self.check_logging_config(self.config.data);

    def write_config(self):
        """Write the current configuration to the file specificied at init()"""
        self.config.write_to_file()

    def __handle_get_module_spec(self, cmd):
        """Private function that handles the 'get_module_spec' command"""
        answer = {}
        if cmd != None:
            if type(cmd) == dict:
                if 'module_name' in cmd and cmd['module_name'] != '':
                    module_name = cmd['module_name']
                    spec = self.get_module_spec(cmd['module_name'])
                    if type(spec) != type({}):
                        # this is a ModuleSpec object.  Extract the
                        # internal spec.
                        spec = spec.get_full_spec()
                    answer = ccsession.create_answer(0, spec)
                else:
                    answer = ccsession.create_answer(1, "Bad module_name in get_module_spec command")
            else:
                answer = ccsession.create_answer(1, "Bad get_module_spec command, argument not a dict")
        else:
            answer = ccsession.create_answer(0, self.get_module_spec())
        return answer

    def __handle_get_config_dict(self, cmd):
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

    def __handle_get_config(self, cmd):
        """Private function that handles the 'get_config' command"""
        if cmd != None:
            if type(cmd) == dict:
                return self.__handle_get_config_dict(cmd)
            else:
                return ccsession.create_answer(1, "Bad get_config command, argument not a dict")
        else:
            return ccsession.create_answer(0, self.config.data)

    def __handle_set_config_module(self, module_name, cmd):
        # the answer comes (or does not come) from the relevant module
        # so we need a variable to see if we got it
        answer = None
        # todo: use api (and check the data against the definition?)
        old_data = copy.deepcopy(self.config.data)
        conf_part = data.find_no_exc(self.config.data, module_name)
        update_cmd = None
        use_part = None
        if conf_part:
            data.merge(conf_part, cmd)
            use_part = conf_part
        else:
            conf_part = data.set(self.config.data, module_name, {})
            data.merge(conf_part[module_name], cmd)
            use_part = conf_part[module_name]

        # The command to send
        update_cmd = ccsession.create_command(ccsession.COMMAND_CONFIG_UPDATE,
                                              use_part)

        # TODO: This design might need some revisiting. We might want some
        # polymorphism instead of branching. But it just might turn out it
        # will get solved by itself when we move everything to virtual modules
        # (which is possible solution to the offline configuration problem)
        # or when we solve the incorect behaviour here when a config is
        # rejected (spying modules don't know it was rejected and some modules
        # might have been commited already).
        if module_name in self.virtual_modules:
            # The module is virtual, so call it to get the answer
            try:
                error = self.virtual_modules[module_name](use_part)
                if error is None:
                    answer = ccsession.create_answer(0)
                    # OK, it is successful, send the notify, but don't wait
                    # for answer
                    seq = self.cc.group_sendmsg(update_cmd, module_name)
                else:
                    answer = ccsession.create_answer(1, error)
            # Make sure just a validating plugin don't kill the whole manager
            except Exception as excp:
                # Provide answer
                answer = ccsession.create_answer(1, "Exception: " + str(excp))
        else:
            # Real module, send it over the wire to it
            # send out changed info and wait for answer
            seq = self.cc.group_sendmsg(update_cmd, module_name)
            try:
                # replace 'our' answer with that of the module
                answer, env = self.cc.group_recvmsg(False, seq)
            except isc.cc.SessionTimeout:
                answer = ccsession.create_answer(1, "Timeout waiting for answer from " + module_name)
            except isc.cc.SessionError as se:
                logger.error(CFGMGR_BAD_UPDATE_RESPONSE_FROM_MODULE, module_name, se)
                answer = ccsession.create_answer(1, "Unable to parse response from " + module_name + ": " + str(se))
        if answer:
            rcode, val = ccsession.parse_answer(answer)
            if rcode == 0:
                self.write_config()
            else:
                self.config.data = old_data
        return answer

    def __handle_set_config_all(self, cmd):
        old_data = copy.deepcopy(self.config.data)
        got_error = False
        err_list = []
        # The format of the command is a dict with module->newconfig
        # sets, so we simply call set_config_module for each of those
        for module in cmd:
            if module != "version":
                answer = self.__handle_set_config_module(module, cmd[module])
                if answer == None:
                    got_error = True
                    err_list.append("No answer message from " + module)
                else:
                    rcode, val = ccsession.parse_answer(answer)
                    if rcode != 0:
                        got_error = True
                        err_list.append(val)
        if not got_error:
            # if Logging config is in there, update our config as well
            self.check_logging_config(cmd);
            self.write_config()
            return ccsession.create_answer(0)
        else:
            # TODO rollback changes that did get through, should we re-send update?
            self.config.data = old_data
            return ccsession.create_answer(1, " ".join(err_list))

    def __handle_set_config(self, cmd):
        """Private function that handles the 'set_config' command"""
        answer = None

        if cmd == None:
            return ccsession.create_answer(1, "Wrong number of arguments")
        if len(cmd) == 2:
            answer = self.__handle_set_config_module(cmd[0], cmd[1])
        elif len(cmd) == 1:
            answer = self.__handle_set_config_all(cmd[0])
        else:
            answer = ccsession.create_answer(1, "Wrong number of arguments")
        if not answer:
            answer = ccsession.create_answer(1, "No answer message from " + cmd[0])

        return answer

    def __handle_module_spec(self, spec):
        """Private function that handles the 'module_spec' command"""
        # todo: validate? (no direct access to spec as
        # todo: use ModuleSpec class
        # todo: error checking (like keyerrors)
        answer = {}
        self.set_module_spec(spec)
        self._send_module_spec_to_cmdctl(spec.get_module_name(),
                                         spec.get_full_spec())
        return ccsession.create_answer(0)

    def __handle_module_stopping(self, arg):
        """Private function that handles a 'stopping' command;
           The argument is of the form { 'module_name': <name> }.
           If the module is known, it is removed from the known list,
           and a message is sent to the Cmdctl channel to remove it as well.
           If it is unknown, the message is ignored."""
        if arg['module_name'] in self.module_specs:
            del self.module_specs[arg['module_name']]
            self._send_module_spec_to_cmdctl(arg['module_name'], None)
        # This command is not expected to be answered
        return None

    def _send_module_spec_to_cmdctl(self, module_name, spec):
        """Sends the given module spec for the given module name to Cmdctl.
           Parameters:
           module_name: A string with the name of the module
           spec: dict containing full module specification, as returned by
                 ModuleSpec.get_full_spec(). This argument may also be None,
                 in which case it signals Cmdctl to remove said module from
                 its list.
           No response from Cmdctl is expected."""
        spec_update = ccsession.create_command(ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE,
                                               [ module_name, spec ])
        self.cc.group_sendmsg(spec_update, "Cmdctl")

    def handle_msg(self, msg):
        """Handle a command from the cc channel to the configuration manager"""
        answer = {}
        cmd, arg = ccsession.parse_command(msg)
        if cmd:
            if cmd == ccsession.COMMAND_GET_COMMANDS_SPEC:
                answer = ccsession.create_answer(0, self.get_commands_spec())
            elif cmd == ccsession.COMMAND_GET_STATISTICS_SPEC:
                answer = ccsession.create_answer(0, self.get_statistics_spec())
            elif cmd == ccsession.COMMAND_GET_MODULE_SPEC:
                answer = self.__handle_get_module_spec(arg)
            elif cmd == ccsession.COMMAND_GET_CONFIG:
                answer = self.__handle_get_config(arg)
            elif cmd == ccsession.COMMAND_SET_CONFIG:
                answer = self.__handle_set_config(arg)
            elif cmd == ccsession.COMMAND_MODULE_STOPPING:
                answer = self.__handle_module_stopping(arg)
            elif cmd == ccsession.COMMAND_SHUTDOWN:
                self.running = False
                answer = ccsession.create_answer(0)
            elif cmd == ccsession.COMMAND_MODULE_SPEC:
                try:
                    answer = self.__handle_module_spec(isc.config.ModuleSpec(arg))
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
            # we just wait eternally for any command here, so disable
            # timeouts for this specific recv
            self.cc.set_timeout(0)
            msg, env = self.cc.group_recvmsg(False)
            # and set it back to whatever we default to
            self.cc.set_timeout(isc.cc.Session.MSGQ_DEFAULT_TIMEOUT)
            # ignore 'None' value (even though they should not occur)
            # and messages that are answers to questions we did
            # not ask
            if msg is not None and not 'result' in msg:
                answer = self.handle_msg(msg);
                # Only respond if there actually is something to respond with
                if answer is not None:
                    self.cc.group_reply(env, answer)
