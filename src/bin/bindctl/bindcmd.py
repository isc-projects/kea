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

import sys
import readline
from cmd import Cmd
from exception import *
from moduleinfo import *
from cmdparse import BindCmdParse
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
import ast

try:
    from collections import OrderedDict
except ImportError:
    from mycollections import OrderedDict


CONST_BINDCTL_HELP = """BindCtl, verstion 0.1
usage: <module name> <command name> [param1 = value1 [, param2 = value2]]
Type Tab character to get the hint of module/command/paramters.
Type \"help(? h)\" for help on bindctl.
Type \"<module_name> help\" for help on the specific module.
Type \"<module_name> <command_name> help\" for help on the specific command.
\nAvailable module names: """

CONST_COMMAND_NODE = "command"

class BindCmdInterpreter(Cmd):
    """simple bindctl example."""    

    def __init__(self, server_port = 'localhost:8080'):
        Cmd.__init__(self)
        self.location = ""
        self.prompt_end = '> '
        self.prompt = self.prompt_end
        self.ruler = '-'
        self.modules = OrderedDict()
        self.add_module_info(ModuleInfo("help", desc = "Get help for bindctl"))
        self.server_port = server_port
        self.connect_to_cmd_ctrld()
        self.session_id = self._get_session_id()

    def connect_to_cmd_ctrld(self):
        try:
            self.conn = http.client.HTTPSConnection(self.server_port, cert_file='bindctl.pem')
        except  Exception as e:
            print(e)
            print("can't connect to %s, please make sure cmd-ctrld is running" % self.server_port)

    def _get_session_id(self):
        rand = os.urandom(16)
        now = time.time()
        ip = socket.gethostbyname(socket.gethostname())
        session_id = sha1(("%s%s%s" %(rand, now, ip)).encode())
        session_id = session_id.hexdigest()
        return session_id
    
    def run(self):
        try:
            ret = self.login()
            if not ret:
                return False

            # Get all module information from cmd-ctrld
            self.config_data = isc.config.UIConfigData(self)
            self.update_commands()
            self.cmdloop()
        except KeyboardInterrupt:
            return True

    def login(self):
        csvfile = None
        bsuccess = False
        try:
            csvfile = open('default_user.csv')
            users = csv.reader(csvfile)
            for row in users:
                if (len(row) < 2):
                    continue

                param = {'username': row[0], 'password' : row[1]}
                response = self.send_POST('/login', param)
                data = response.read().decode()
                if response.status == http.client.OK:
                    print(data + ' login as ' + row[0] )
                    bsuccess = True
                    break
        except IOError as e:
            pass
        except Exception as e:
            print(e)
        finally:
            if csvfile:
                csvfile.close()
            if bsuccess:
                return True

        count = 0
        csvfile = None
        print("[TEMP MESSAGE]: username :root  password :bind10")
        while count < 3:
            count = count + 1
            username = input("Username:")
            passwd = getpass.getpass()
            param = {'username': username, 'password' : passwd}
            response = self.send_POST('/login', param)
            data = response.read().decode()
            print(data)
            
            if response.status == http.client.OK:
                csvfile = open('default_user.csv', 'w')
                writer = csv.writer(csvfile)
                writer.writerow([username, passwd])
                bsuccess = True
                break

            if count == 3:
                print("Too many authentication failures")
                break

        if csvfile:
            csvfile.close()
        return bsuccess

    def update_commands(self):
        cmd_spec = self.send_GET('/command_spec')
        if (len(cmd_spec) == 0):
            print('can\'t get any command specification')
        for module_name in cmd_spec.keys():
            if cmd_spec[module_name]:
                self.prepare_module_commands(module_name, cmd_spec[module_name])

    def send_GET(self, url, body = None):
        headers = {"cookie" : self.session_id}
        self.conn.request('GET', url, body, headers)
        res = self.conn.getresponse()
        reply_msg = res.read()
        if reply_msg:
           return json.loads(reply_msg.decode())
        else:
            return None
       

    def send_POST(self, url, post_param = None): 
        '''
        Format: /module_name/command_name
        parameters of command is encoded as a map
        '''
        param = None
        if (len(post_param) != 0):
            param = json.dumps(post_param)

        headers = {"cookie" : self.session_id}
        self.conn.request('POST', url, param, headers)
        return self.conn.getresponse()
        

    def postcmd(self, stop, line):
        self.prompt = self.location + self.prompt_end
        return stop

    def prepare_module_commands(self, module_name, module_commands):
        module = ModuleInfo(name = module_name,
                            desc = "same here")
        for command in module_commands:
            cmd = CommandInfo(name = command["command_name"],
                              desc = command["command_description"],
                              need_inst_param = False)
            for arg in command["command_args"]:
                param = ParamInfo(name = arg["item_name"],
                                  type = arg["item_type"],
                                  optional = bool(arg["item_optional"]))
                if ("item_default" in arg):
                    param.default = arg["item_default"]
                cmd.add_param(param)
            module.add_command(cmd)
        self.add_module_info(module)

    def validate_cmd(self, cmd):
        if not cmd.module in self.modules:
            raise CmdUnknownModuleSyntaxError(cmd.module)
        
        module_info = self.modules[cmd.module]
        if not module_info.has_command_with_name(cmd.command):
            raise CmdUnknownCmdSyntaxError(cmd.module, cmd.command)

        command_info = module_info.get_command_with_name(cmd.command)
        manda_params = command_info.get_mandatory_param_names()
        all_params = command_info.get_param_names()
        
        # If help is inputed, don't do further paramters validation.
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
            index = 0
            param_count = len(params)
            for name in params:
                # either the name of the parameter must be known, or
                # the 'name' must be an integer (ie. the position of
                # an unnamed argument
                if type(name) == int:
                    # lump all extraneous arguments together as one big final one
                    # todo: check if last param type is a string?
                    if (param_count > 2):
                        while (param_count > len(command_info.params) - 1):
                            params[param_count - 2] += params[param_count - 1]
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
                        param_name = command_info.get_param_name_by_position(name+1, index, param_count)
                        cmd.params[param_name] = cmd.params[name]
                        del cmd.params[name]
                        
                elif not name in all_params:
                    raise CmdUnknownParamSyntaxError(cmd.module, cmd.command, name)
            param_nr = 0
            for name in manda_params:
                if not name in params and not param_nr in params:
                    raise CmdMissParamSyntaxError(cmd.module, cmd.command, name)
                
                param_nr += 1
                param_nr += 1

    def _handle_cmd(self, cmd):
        #to do, consist xml package and send to bind10
        if cmd.command == "help" or ("help" in cmd.params.keys()):
            self._handle_help(cmd)
        elif cmd.module == "config":
            self.apply_config_cmd(cmd)
        else:
            self.apply_cmd(cmd)

    def add_module_info(self, module_info):        
        self.modules[module_info.name] = module_info
        
    def get_module_names(self):
        return list(self.modules.keys())

    #override methods in cmd
    def default(self, line):
        self._parse_cmd(line)

    def emptyline(self):
        pass

    def do_help(self, name):
        print(CONST_BINDCTL_HELP)
        for k in self.modules.keys():
            print("\t", self.modules[k])
                
    
    def onecmd(self, line):
        if line == 'EOF' or line.lower() == "quit":
            self.conn.close()
            return True
            
        if line == 'h':
            line = 'help'
        
        Cmd.onecmd(self, line)
                    
    def complete(self, text, state):
        if 0 == state:
            text = text.strip()
            hints = []
            cur_line = readline.get_line_buffer()            
            try:
                cmd = BindCmdParse(cur_line)
                if not cmd.params and text:
                    hints = self._get_command_startswith(cmd.module, text)
                else:                       
                    hints = self._get_param_startswith(cmd.module, cmd.command,
                                                       text)
                    if cmd.module == "config":
                        # grm text has been stripped of slashes...
                        my_text = self.location + "/" + cur_line.rpartition(" ")[2]
                        list = self.config_data.get_config_item_list(my_text.rpartition("/")[0])
                        hints.extend([val for val in list if val.startswith(text)])
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
            #self._append_space_to_hint()

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
            cmd = BindCmdParse(line)
            self.validate_cmd(cmd)
            self._handle_cmd(cmd)
        except BindCtlException as e:
            print("Error! ", e)
            self._print_correct_usage(e)
            
            
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
        identifier = self.location
        try:
            if 'identifier' in cmd.params:
                if not identifier.endswith("/"):
                    identifier += "/"
                if cmd.params['identifier'].startswith("/"):
                    identifier = cmd.params['identifier']
                else:
                    identifier += cmd.params['identifier']
            if cmd.command == "show":
                values = self.config_data.get_value_maps(identifier)
                for value_map in values:
                    line = value_map['name']
                    if value_map['type'] in [ 'module', 'map', 'list' ]:
                        line += "/"
                    else:
                        line += ":\t" + str(value_map['value'])
                    line += "\t" + value_map['type']
                    line += "\t"
                    if value_map['default']:
                        line += "(default)"
                    if value_map['modified']:
                        line += "(modified)"
                    print(line)
            elif cmd.command == "add":
                self.config_data.add_value(identifier, cmd.params['value'])
            elif cmd.command == "remove":
                self.config_data.remove_value(identifier, cmd.params['value'])
            elif cmd.command == "set":
                if 'identifier' not in cmd.params:
                    print("Error: missing identifier or value")
                else:
                    parsed_value = None
                    try:
                        parsed_value = ast.literal_eval(cmd.params['value'])
                    except Exception as exc:
                        # ok could be an unquoted string, interpret as such
                        parsed_value = cmd.params['value']
                    self.config_data.set_value(identifier, parsed_value)
            elif cmd.command == "unset":
                self.config_data.unset(identifier)
            elif cmd.command == "revert":
                self.config_data.revert()
            elif cmd.command == "commit":
                self.config_data.commit()
            elif cmd.command == "diff":
                print(self.config_data.get_local_changes());
            elif cmd.command == "go":
                self.go(identifier)
        except isc.cc.data.DataTypeError as dte:
            print("Error: " + str(dte))
        except isc.cc.data.DataNotFoundError as dnfe:
            print("Error: " + identifier + " not found")
        except KeyError as ke:
            print("Error: missing " + str(ke))
            raise ke

    def go(self, identifier):
        # just to see if it exists
        self.config_data.get_value(identifier)
        # some sanitizing
        identifier = identifier.replace("//", "/")
        if not identifier.startswith("/"):
            identifier = "/" + identifier
        if identifier.endswith("/"):
            identifier = identifier[:-1]
        self.location = identifier

    def apply_cmd(self, cmd):
        url = '/' + cmd.module + '/' + cmd.command
        cmd_params = None
        if (len(cmd.params) != 0):
            cmd_params = json.dumps(cmd.params)

        print("send the message to cmd-ctrld")        
        reply = self.send_POST(url, cmd.params)
        data = reply.read().decode()
        print("received reply:", data)




