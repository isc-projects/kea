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

"""This module holds the BindCmdInterpreter class. This provides the
   core functionality for bindctl. It maintains a session with
   b10-cmdctl, holds local configuration and module information, and
   handles command line interface commands"""

import sys
from cmd import Cmd
from bindctl.exception import *
from bindctl.moduleinfo import *
from bindctl.cmdparse import BindCmdParser
from bindctl import command_sets
from xml.dom import minidom
import isc
import isc.cc.data
import http.client
import json
import inspect
import pprint
import ssl, socket
import os, time, random, re
import getpass
from hashlib import sha1
import csv
import pwd
import getpass
import copy

try:
    from collections import OrderedDict
except ImportError:
    from bindctl.mycollections import OrderedDict

# if we have readline support, use that, otherwise use normal stdio
try:
    import readline
    # Only consider spaces as word boundaries; identifiers can contain
    # '/' and '[]', and configuration item names can in theory use any
    # printable  character. See the discussion in tickets #1345 and
    # #2254 for more information.
    readline.set_completer_delims(' ')

    my_readline = readline.get_line_buffer
except ImportError:
    my_readline = sys.stdin.readline

# Used for tab-completion of 'identifiers' (i.e. config values)
# If a command parameter has this name, the tab completion hints
# are derived from config data
IDENTIFIER_PARAM = 'identifier'

CSV_FILE_NAME = 'default_user.csv'
CONFIG_MODULE_NAME = 'config'
CONST_BINDCTL_HELP = """
usage: <module name> <command name> [param1 = value1 [, param2 = value2]]
Type Tab character to get the hint of module/command/parameters.
Type \"help(? h)\" for help on bindctl.
Type \"<module_name> help\" for help on the specific module.
Type \"<module_name> <command_name> help\" for help on the specific command.
\nAvailable module names: """

class ValidatedHTTPSConnection(http.client.HTTPSConnection):
    '''Overrides HTTPSConnection to support certification
    validation. '''
    def __init__(self, host, ca_certs):
        http.client.HTTPSConnection.__init__(self, host)
        self.ca_certs = ca_certs

    def connect(self):
        ''' Overrides the connect() so that we do
        certificate validation. '''
        sock = socket.create_connection((self.host, self.port),
                                        self.timeout)
        if self._tunnel_host:
            self.sock = sock
            self._tunnel()

        req_cert = ssl.CERT_NONE
        if self.ca_certs:
            req_cert = ssl.CERT_REQUIRED
        self.sock = ssl.wrap_socket(sock, self.key_file,
                                    self.cert_file,
                                    cert_reqs=req_cert,
                                    ca_certs=self.ca_certs)

class BindCmdInterpreter(Cmd):
    """simple bindctl example."""

    def __init__(self, server_port='localhost:8080', pem_file=None,
                 csv_file_dir=None):
        Cmd.__init__(self)
        self.location = ""
        self.prompt_end = '> '
        if sys.stdin.isatty():
            self.prompt = self.prompt_end
        else:
            self.prompt = ""
        self.ruler = '-'
        self.modules = OrderedDict()
        self.add_module_info(ModuleInfo("help", desc = "Get help for bindctl."))
        self.server_port = server_port
        self.conn = ValidatedHTTPSConnection(self.server_port,
                                             ca_certs=pem_file)
        self.session_id = self._get_session_id()
        self.config_data = None
        if csv_file_dir is not None:
            self.csv_file_dir = csv_file_dir
        else:
            self.csv_file_dir = pwd.getpwnam(getpass.getuser()).pw_dir + \
                os.sep + '.bind10' + os.sep

    def _get_session_id(self):
        '''Generate one session id for the connection. '''
        rand = os.urandom(16)
        now = time.time()
        session_id = sha1(("%s%s%s" %(rand, now,
                                      socket.gethostname())).encode())
        digest = session_id.hexdigest()
        return digest

    def run(self):
        '''Parse commands from user and send them to cmdctl. '''
        try:
            if not self.login_to_cmdctl():
                return 1

            self.cmdloop()
            print('\nExit from bindctl')
            return 0
        except FailToLogin as err:
            # error already printed when this was raised, ignoring
            return 1
        except KeyboardInterrupt:
            print('\nExit from bindctl')
            return 0
        except socket.error as err:
            print('Failed to send request, the connection is closed')
            return 1
        except http.client.CannotSendRequest:
            print('Can not send request, the connection is busy')
            return 1

    def _get_saved_user_info(self, dir, file_name):
        ''' Read all the available username and password pairs saved in
        file(path is "dir + file_name"), Return value is one list of elements
        ['name', 'password'], If get information failed, empty list will be
        returned.'''
        if (not dir) or (not os.path.exists(dir)):
            return []

        try:
            csvfile = None
            users = []
            csvfile = open(dir + file_name)
            users_info = csv.reader(csvfile)
            for row in users_info:
                users.append([row[0], row[1]])
        except (IOError, IndexError) as err:
            print("Error reading saved username and password from %s%s: %s" % (dir, file_name, err))
        finally:
            if csvfile:
                csvfile.close()
            return users

    def _save_user_info(self, username, passwd, dir, file_name):
        ''' Save username and password in file "dir + file_name"
        If it's saved properly, return True, or else return False. '''
        try:
            if not os.path.exists(dir):
                os.mkdir(dir, 0o700)

            csvfilepath = dir + file_name
            csvfile = open(csvfilepath, 'w')
            os.chmod(csvfilepath, 0o600)
            writer = csv.writer(csvfile)
            writer.writerow([username, passwd])
            csvfile.close()
        except IOError as err:
            print("Error saving user information:", err)
            print("user info file name: %s%s" % (dir, file_name))
            return False

        return True

    def login_to_cmdctl(self):
        '''Login to cmdctl with the username and password inputted
        from user. After the login is sucessful, the username and
        password will be saved in 'default_user.csv', when run the next
        time, username and password saved in 'default_user.csv' will be
        used first.
        '''
        users = self._get_saved_user_info(self.csv_file_dir, CSV_FILE_NAME)
        for row in users:
            param = {'username': row[0], 'password' : row[1]}
            try:
                response = self.send_POST('/login', param)
                data = response.read().decode()
            except socket.error as err:
                print("Socket error while sending login information:", err)
                raise FailToLogin()

            if response.status == http.client.OK:
                # Is interactive?
                if sys.stdin.isatty():
                    print(data + ' login as ' + row[0])
                return True

        count = 0
        print("[TEMP MESSAGE]: username :root  password :bind10")
        while True:
            count = count + 1
            if count > 3:
                print("Too many authentication failures")
                return False

            username = input("Username:")
            passwd = getpass.getpass()
            param = {'username': username, 'password' : passwd}
            try:
                response = self.send_POST('/login', param)
                data = response.read().decode()
                print(data)
            except socket.error as err:
                print("Socket error while sending login information:", err)
                raise FailToLogin()

            if response.status == http.client.OK:
                self._save_user_info(username, passwd, self.csv_file_dir,
                                     CSV_FILE_NAME)
                return True

    def _update_commands(self):
        '''Update the commands of all modules. '''
        for module_name in self.config_data.get_config_item_list():
            self._prepare_module_commands(self.config_data.get_module_spec(module_name))

    def _send_message(self, url, body):
        headers = {"cookie" : self.session_id}
        self.conn.request('GET', url, body, headers)
        res = self.conn.getresponse()
        return res.status, res.read()

    def send_GET(self, url, body = None):
        '''Send GET request to cmdctl, session id is send with the name
        'cookie' in header.
        '''
        status, reply_msg = self._send_message(url, body)
        if status == http.client.UNAUTHORIZED:
            if self.login_to_cmdctl():
                # successful, so try send again
                status, reply_msg = self._send_message(url, body)

        if reply_msg:
            return json.loads(reply_msg.decode())
        else:
            return {}


    def send_POST(self, url, post_param = None):
        '''Send POST request to cmdctl, session id is send with the name
        'cookie' in header.
        Format: /module_name/command_name
        parameters of command is encoded as a map
        '''
        param = None
        if (len(post_param) != 0):
            param = json.dumps(post_param)

        headers = {"cookie" : self.session_id}
        self.conn.request('POST', url, param, headers)
        return self.conn.getresponse()

    def _update_all_modules_info(self):
        ''' Get all modules' information from cmdctl, including
        specification file and configuration data. This function
        should be called before interpreting command line or complete-key
        is entered. This may not be the best way to keep bindctl
        and cmdctl share same modules information, but it works.'''
        if self.config_data is not None:
            self.config_data.update_specs_and_config()
        else:
            self.config_data = isc.config.UIModuleCCSession(self)
        self._update_commands()

    def precmd(self, line):
        if line != 'EOF':
            self._update_all_modules_info()
        return line

    def postcmd(self, stop, line):
        '''Update the prompt after every command, but only if we
           have a tty as output'''
        if sys.stdin.isatty():
            self.prompt = self.location + self.prompt_end
        return stop

    def _prepare_module_commands(self, module_spec):
        '''Prepare the module commands'''
        module = ModuleInfo(name = module_spec.get_module_name(),
                            desc = module_spec.get_module_description())
        for command in module_spec.get_commands_spec():
            cmd = CommandInfo(name = command["command_name"],
                              desc = command["command_description"])
            for arg in command["command_args"]:
                param = ParamInfo(name = arg["item_name"],
                                  type = arg["item_type"],
                                  optional = bool(arg["item_optional"]),
                                  param_spec = arg)
                if ("item_default" in arg):
                    param.default = arg["item_default"]
                if ("item_description" in arg):
                    param.desc = arg["item_description"]
                cmd.add_param(param)
            module.add_command(cmd)
        self.add_module_info(module)

    def _validate_cmd(self, cmd):
        '''validate the parameters and merge some parameters together,
        merge algorithm is based on the command line syntax, later, if
        a better command line syntax come out, this function should be
        updated first.
        '''
        if not cmd.module in self.modules:
            raise CmdUnknownModuleSyntaxError(cmd.module)

        module_info = self.modules[cmd.module]
        if not module_info.has_command_with_name(cmd.command):
            raise CmdUnknownCmdSyntaxError(cmd.module, cmd.command)

        command_info = module_info.get_command_with_name(cmd.command)
        manda_params = command_info.get_mandatory_param_names()
        all_params = command_info.get_param_names()

        # If help is entered, don't do further parameter validation.
        for val in cmd.params.keys():
            if val == "help":
                return

        params = cmd.params.copy()
        if not params and manda_params:
            raise CmdMissParamSyntaxError(cmd.module, cmd.command, manda_params[0])
        elif params and not all_params:
            raise CmdUnknownParamSyntaxError(cmd.module, cmd.command,
                                             list(params.keys())[0])
        elif params:
            param_name = None
            param_count = len(params)
            for name in params:
                # either the name of the parameter must be known, or
                # the 'name' must be an integer (ie. the position of
                # an unnamed argument
                if type(name) == int:
                    # lump all extraneous arguments together as one big final one
                    # todo: check if last param type is a string?
                    while (param_count > 2 and
                           param_count > len(command_info.params) - 1):
                        params[param_count - 2] += " " + params[param_count - 1]
                        del(params[param_count - 1])
                        param_count = len(params)
                        cmd.params = params.copy()

                    # (-1, help is always in the all_params list)
                    if name >= len(all_params) - 1:
                        # add to last known param
                        if param_name:
                            cmd.params[param_name] += cmd.params[name]
                        else:
                            raise CmdUnknownParamSyntaxError(cmd.module, cmd.command, cmd.params[name])
                    else:
                        # replace the numbered items by named items
                        param_name = command_info.get_param_name_by_position(name, param_count)
                        cmd.params[param_name] = cmd.params[name]
                        del cmd.params[name]

                elif not name in all_params:
                    raise CmdUnknownParamSyntaxError(cmd.module, cmd.command, name)

            param_nr = 0
            for name in manda_params:
                if not name in params and not param_nr in params:
                    raise CmdMissParamSyntaxError(cmd.module, cmd.command, name)
                param_nr += 1

        # Convert parameter value according parameter spec file.
        # Ignore check for commands belongs to module 'config' or 'execute
        if cmd.module != CONFIG_MODULE_NAME and\
           cmd.module != command_sets.EXECUTE_MODULE_NAME:
            for param_name in cmd.params:
                param_spec = command_info.get_param_with_name(param_name).param_spec
                try:
                    cmd.params[param_name] = isc.config.config_data.convert_type(param_spec, cmd.params[param_name])
                except isc.cc.data.DataTypeError as e:
                    raise isc.cc.data.DataTypeError('Invalid parameter value for \"%s\", the type should be \"%s\" \n'
                                                     % (param_name, param_spec['item_type']) + str(e))

    def _handle_cmd(self, cmd):
        '''Handle a command entered by the user'''
        if cmd.command == "help" or ("help" in cmd.params.keys()):
            self._handle_help(cmd)
        elif cmd.module == CONFIG_MODULE_NAME:
            self.apply_config_cmd(cmd)
        elif cmd.module == command_sets.EXECUTE_MODULE_NAME:
            self.apply_execute_cmd(cmd)
        else:
            self.apply_cmd(cmd)

    def add_module_info(self, module_info):
        '''Add the information about one module'''
        self.modules[module_info.name] = module_info

    def get_module_names(self):
        '''Return the names of all known modules'''
        return list(self.modules.keys())

    #override methods in cmd
    def default(self, line):
        self._parse_cmd(line)

    def emptyline(self):
        pass

    def do_help(self, name):
        print(CONST_BINDCTL_HELP)
        for k in self.modules.values():
            n = k.get_name()
            if len(n) >= CONST_BINDCTL_HELP_INDENT_WIDTH:
                print("    %s" % n)
                print(textwrap.fill(k.get_desc(),
                      initial_indent="            ",
                      subsequent_indent="    " +
                      " " * CONST_BINDCTL_HELP_INDENT_WIDTH,
                      width=70))
            else:
                print(textwrap.fill("%s%s%s" %
                    (k.get_name(),
                     " "*(CONST_BINDCTL_HELP_INDENT_WIDTH - len(k.get_name())),
                     k.get_desc()),
                    initial_indent="    ",
                    subsequent_indent="    " +
                    " " * CONST_BINDCTL_HELP_INDENT_WIDTH,
                    width=70))

    def onecmd(self, line):
        if line == 'EOF' or line.lower() == "quit":
            self.conn.close()
            return True

        if line == 'h':
            line = 'help'

        Cmd.onecmd(self, line)

    def _get_identifier_startswith(self, id_text):
        """Return the tab-completion hints for identifiers starting with
           id_text.

           Parameters:
           id_text (string): the currently entered identifier part, which
           is to be completed.
        """
        # Strip starting "/" from id_text
        if id_text.startswith('/'):
            id_text = id_text[1:]
        # Get all items from the given module (up to the first /)
        list = self.config_data.get_config_item_list(
                        id_text.rpartition("/")[0], recurse=True)
        # filter out all possibilities that don't match currently entered
        # text part
        hints = [val for val in list if val.startswith(id_text)]
        return hints

    def _cmd_has_identifier_param(self, cmd):
        """
        Returns True if the given (parsed) command is known and has a
        parameter which points to a config data identifier

        Parameters:
        cmd (cmdparse.BindCmdParser): command context, including given params

        """
        if cmd.module not in self.modules:
            return False
        command = self.modules[cmd.module].get_command_with_name(cmd.command)
        return command.has_param_with_name(IDENTIFIER_PARAM)

    def complete(self, text, state):
        """
        Returns tab-completion hints. See the python documentation of the
        readline and Cmd modules for more information.

        The first time this is called (within one 'completer' action), it
        has state 0, and a list of possible completions is made. This list
        is stored; complete() will then be called with increasing values of
        state, until it returns None. For each call it returns the state'th
        element of the hints it collected in the first call.

        The hints list contents depend on which part of the full command
        line; if no module is given yet, it will list all modules. If a
        module is given, but no command, it will complete with module
        commands. If both have been given, it will create the hints based on
        the command parameters.

        If module and command have already been specified, and the command
        has a parameter 'identifier', the configuration data is used to
        create the hints list.

        Parameters:
        text (string): The text entered so far in the 'current' part of
                       the command (module, command, parameters)
        state (int): state used in the readline tab-completion logic;
                     0 on first call, increasing by one until there are
                     no (more) hints to return.

        Returns the string value of the hints list with index 'state',
        or None if no (more) hints are available.
        """
        if 0 == state:
            self._update_all_modules_info()
            text = text.strip()
            hints = []
            cur_line = my_readline()
            try:
                cmd = BindCmdParser(cur_line)
                if not cmd.params and text:
                    hints = self._get_command_startswith(cmd.module, text)
                elif self._cmd_has_identifier_param(cmd):
                    # For tab-completion of identifiers, replace hardcoded
                    # hints with hints derived from the config data
                    hints = self._get_identifier_startswith(text)
                else:
                    hints = self._get_param_startswith(cmd.module, cmd.command,
                                                       text)

            except CmdModuleNameFormatError:
                if not text:
                    hints = self.get_module_names()

            except CmdMissCommandNameFormatError as e:
                if not text.strip(): # command name is empty
                    hints = self.modules[e.module].get_command_names()
                else:
                    hints = self._get_module_startswith(text)

            except CmdCommandNameFormatError as e:
                if e.module in self.modules:
                    hints = self._get_command_startswith(e.module, text)

            except CmdParamFormatError as e:
                hints = self._get_param_startswith(e.module, e.command, text)

            except BindCtlException:
                hints = []

            self.hint = hints

        if state < len(self.hint):
            return self.hint[state]
        else:
            return None


    def _get_module_startswith(self, text):
        return [module
                for module in self.modules
                if module.startswith(text)]


    def _get_command_startswith(self, module, text):
        if module in self.modules:
            return [command
                    for command in self.modules[module].get_command_names()
                    if command.startswith(text)]

        return []


    def _get_param_startswith(self, module, command, text):
        if module in self.modules:
            module_info = self.modules[module]
            if command in module_info.get_command_names():
                cmd_info = module_info.get_command_with_name(command)
                params = cmd_info.get_param_names()
                hint = []
                if text:
                    hint = [val for val in params if val.startswith(text)]
                else:
                    hint = list(params)

                if len(hint) == 1 and hint[0] != "help":
                    hint[0] = hint[0] + " ="

                return hint

        return []

    def _parse_cmd(self, line):
        try:
            cmd = BindCmdParser(line)
            self._validate_cmd(cmd)
            self._handle_cmd(cmd)
        except (IOError, http.client.HTTPException) as err:
            print('Error: ', err)
        except BindCtlException as err:
            print("Error! ", err)
            self._print_correct_usage(err)
        except isc.cc.data.DataTypeError as err:
            print("Error! ", err)
        except isc.cc.data.DataTypeError as dte:
            print("Error: " + str(dte))
        except isc.cc.data.DataNotFoundError as dnfe:
            print("Error: " + str(dnfe))
        except isc.cc.data.DataAlreadyPresentError as dape:
            print("Error: " + str(dape))
        except KeyError as ke:
            print("Error: missing " + str(ke))

    def _print_correct_usage(self, ept):
        if isinstance(ept, CmdUnknownModuleSyntaxError):
            self.do_help(None)

        elif isinstance(ept, CmdUnknownCmdSyntaxError):
            self.modules[ept.module].module_help()

        elif isinstance(ept, CmdMissParamSyntaxError) or \
             isinstance(ept, CmdUnknownParamSyntaxError):
             self.modules[ept.module].command_help(ept.command)


    def _append_space_to_hint(self):
        """Append one space at the end of complete hint."""
        self.hint = [(val + " ") for val in self.hint]


    def _handle_help(self, cmd):
        if cmd.command == "help":
            self.modules[cmd.module].module_help()
        else:
            self.modules[cmd.module].command_help(cmd.command)


    def apply_config_cmd(self, cmd):
        '''Handles a configuration command.
           Raises a DataTypeError if a wrong value is set.
           Raises a DataNotFoundError if a wrong identifier is used.
           Raises a KeyError if the command was not complete
        '''
        identifier = self.location
        if 'identifier' in cmd.params:
            if not identifier.endswith("/"):
                identifier += "/"
            if cmd.params['identifier'].startswith("/"):
                identifier = cmd.params['identifier']
            else:
                if cmd.params['identifier'].startswith('['):
                    identifier = identifier[:-1]
                identifier += cmd.params['identifier']

            # Check if the module is known; for unknown modules
            # we currently deny setting preferences, as we have
            # no way yet to determine if they are ok.
            module_name = identifier.split('/')[1]
            if module_name != "" and (self.config_data is None or \
               not self.config_data.have_specification(module_name)):
                print("Error: Module '" + module_name + "' unknown or not running")
                return

        if cmd.command == "show":
            # check if we have the 'all' argument
            show_all = False
            if 'argument' in cmd.params:
                if cmd.params['argument'] == 'all':
                    show_all = True
                elif 'identifier' not in cmd.params:
                    # no 'all', no identifier, assume this is the
                    #identifier
                    identifier += cmd.params['argument']
                else:
                    print("Error: unknown argument " + cmd.params['argument'] + ", or multiple identifiers given")
                    return
            values = self.config_data.get_value_maps(identifier, show_all)
            for value_map in values:
                line = value_map['name']
                if value_map['type'] in [ 'module', 'map' ]:
                    line += "/"
                elif value_map['type'] == 'list' \
                     and value_map['value'] != []:
                    # do not print content of non-empty lists if
                    # we have more data to show
                    line += "/"
                else:
                    # if type is named_set, don't print value if None
                    # (it is either {} meaning empty, or None, meaning
                    # there actually is data, but not to be shown with
                    # the current command
                    if value_map['type'] == 'named_set' and\
                       value_map['value'] is None:
                        line += "/\t"
                    else:
                        line += "\t" + json.dumps(value_map['value'])
                line += "\t" + value_map['type']
                line += "\t"
                if value_map['default']:
                    line += "(default)"
                if value_map['modified']:
                    line += "(modified)"
                print(line)
        elif cmd.command == "show_json":
            if identifier == "":
                print("Need at least the module to show the configuration in JSON format")
            else:
                data, default = self.config_data.get_value(identifier)
                print(json.dumps(data))
        elif cmd.command == "add":
            self.config_data.add_value(identifier,
                                       cmd.params.get('value_or_name'),
                                       cmd.params.get('value_for_set'))
        elif cmd.command == "remove":
            if 'value' in cmd.params:
                self.config_data.remove_value(identifier, cmd.params['value'])
            else:
                self.config_data.remove_value(identifier, None)
        elif cmd.command == "set":
            if 'identifier' not in cmd.params:
                print("Error: missing identifier or value")
            else:
                parsed_value = None
                try:
                    parsed_value = json.loads(cmd.params['value'])
                except Exception as exc:
                    # ok could be an unquoted string, interpret as such
                    parsed_value = cmd.params['value']
                self.config_data.set_value(identifier, parsed_value)
        elif cmd.command == "unset":
            self.config_data.unset(identifier)
        elif cmd.command == "revert":
            self.config_data.clear_local_changes()
        elif cmd.command == "commit":
            try:
                self.config_data.commit()
            except isc.config.ModuleCCSessionError as mcse:
                print(str(mcse))
        elif cmd.command == "diff":
            print(self.config_data.get_local_changes())
        elif cmd.command == "go":
            self.go(identifier)

    def go(self, identifier):
        '''Handles the config go command, change the 'current' location
           within the configuration tree. '..' will be interpreted as
           'up one level'.'''
        id_parts = isc.cc.data.split_identifier(identifier)

        new_location = ""
        for id_part in id_parts:
            if (id_part == ".."):
                # go 'up' one level
                new_location, a, b = new_location.rpartition("/")
            else:
                new_location += "/" + id_part
        # check if exists, if not, revert and error
        v,d = self.config_data.get_value(new_location)
        if v is None:
            print("Error: " + identifier + " not found")
            return

        self.location = new_location

    def apply_execute_cmd(self, command):
        '''Handles the 'execute' command, which executes a number of
           (preset) statements. The command set to execute is either
           read from a file (e.g. 'execute file <file>'.) or one
           of the sets as defined in command_sets.py'''
        if command.command == 'file':
            try:
                with open(command.params['filename']) as command_file:
                    commands = command_file.readlines()
            except IOError as ioe:
                print("Error: " + str(ioe))
                return
        elif command_sets.has_command_set(command.command):
            commands = command_sets.get_commands(command.command)
        else:
            # Should not be reachable; parser should've caught this
            raise Exception("Unknown execute command type " + command.command)

        # We have our set of commands now, depending on whether 'show' was
        # specified, show or execute them
        if 'show' in command.params and command.params['show'] == 'show':
            self.__show_execute_commands(commands)
        else:
            self.__apply_execute_commands(commands)

    def __show_execute_commands(self, commands):
        '''Prints the command list without executing them'''
        for line in commands:
            print(line.strip())

    def __apply_execute_commands(self, commands):
        '''Applies the configuration commands from the given iterator.
           This is the method that catches, comments, echo statements, and
           other directives. All commands not filtered by this method are
           interpreted as if they are directly entered in an active session.
           Lines starting with any of the following characters are not
           passed directly:
           # - These are comments
           ! - These are directives
               !echo: print the rest of the line
               !verbose on/off: print the commands themselves too
               Unknown directives are ignored (with a warning)
           The execution is stopped if there are any errors.
        '''
        verbose = False
        try:
            for line in commands:
                line = line.strip()
                if verbose:
                    print(line)
                if line.startswith('#') or len(line) == 0:
                    continue
                elif line.startswith('!'):
                    if re.match('^!echo ', line, re.I) and len(line) > 6:
                        print(line[6:])
                    elif re.match('^!verbose\s+on\s*$', line, re.I):
                        verbose = True
                    elif re.match('^!verbose\s+off$', line, re.I):
                        verbose = False
                    else:
                        print("Warning: ignoring unknown directive: " + line)
                else:
                    cmd = BindCmdParser(line)
                    self._validate_cmd(cmd)
                    self._handle_cmd(cmd)
        except (isc.config.ModuleCCSessionError,
                IOError, http.client.HTTPException,
                BindCtlException, isc.cc.data.DataTypeError,
                isc.cc.data.DataNotFoundError,
                isc.cc.data.DataAlreadyPresentError,
                KeyError) as err:
            print('Error: ', err)
            print()
            print('Depending on the contents of the script, and which')
            print('commands it has called, there can be committed and')
            print('local changes. It is advised to check your settings,')
            print('and revert local changes with "config revert".')

    def apply_cmd(self, cmd):
        '''Handles a general module command'''
        url = '/' + cmd.module + '/' + cmd.command
        cmd_params = None
        if (len(cmd.params) != 0):
            cmd_params = json.dumps(cmd.params)

        reply = self.send_POST(url, cmd.params)
        data = reply.read().decode()
        # The reply is a string containing JSON data,
        # parse it, then prettyprint
        if data != "" and data != "{}":
            print(json.dumps(json.loads(data), sort_keys=True, indent=4))


