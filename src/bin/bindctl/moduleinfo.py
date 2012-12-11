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

"""This module holds classes representing modules, commands and
   parameters for use in bindctl"""

import textwrap

try:
    from collections import OrderedDict
except ImportError:
    from bindctl.mycollections import OrderedDict

# Define value type
STRING_TYPE = "string"
LIST_TYPE = "list"
INT_TYPE = "int"

MODULE_NODE_NAME = 'module'
COMMAND_NODE_NAME = 'command'
PARAM_NODE_NAME = 'param'

# this is used to align the descriptions in help output
CONST_BINDCTL_HELP_INDENT_WIDTH=12


class ParamInfo:
    """One parameter of one command.
    Each command parameter has five attributes:
    parameter name, parameter type, parameter value,
    parameter description and paramter's spec(got from
    module spec file). 
    """
    def __init__(self, name, desc = '', type = STRING_TYPE, 
                 optional = False, value = '', default_value = '', 
                 param_spec = None):
        self.name = name
        self.type = type
        self.value = value
        self.default_value = default_value                           
        self.desc = desc
        self.is_optional = optional
        self.param_spec = param_spec
    
    def __str__(self):        
        return str("\t%s <type: %s> \t(%s)" % (self.name, self.type, self.desc))

    def get_basic_info(self):
        if self.is_optional:
            opt_str = "optional"
        else:
            opt_str = "mandatory"
        return "%s (%s, %s)" % (self.name, self.type, opt_str)

    def get_desc(self):
        return self.desc

class CommandInfo:
    """One command which is provided by one bind10 module, it has zero
       or more parameters
    """

    def __init__(self, name, desc = ""):
        self.name = name
        self.desc = desc
        self.params = OrderedDict()        
        # Set default parameter "help"
        self.add_param(ParamInfo("help", 
                                  desc = "Get help for command.",
                                  optional = True))
                
    def __str__(self):
        return str("%s \t(%s)" % (self.name, self.desc))

    def get_name(self):
        return self.name

    def get_desc(self):
        return self.desc;
    
    def add_param(self, paraminfo):
        """Add a ParamInfo object to this CommandInfo"""
        self.params[paraminfo.name] = paraminfo
        

    def has_param_with_name(self, param_name):
        """Returns true if the parameter with param_name exists"""
        return param_name in self.params
        

    def get_param_with_name(self, param_name):
        """Returns the ParamInfo with the given name. Raises a
           KeyError if it doesn't exist"""
        return self.params[param_name]
        

    def get_params(self):
        """Returns a list of all ParamInfo objects for this CommandInfo"""
        return list(self.params.values())
        

    def get_param_names(self):
        """Returns a list of the names of all parameters for this command"""
        return list(self.params.keys())
        
        
    def get_mandatory_param_names(self):
        """Returns a list of the names of all mandatory parameters for
           this command"""
        all_names = self.params.keys()
        return [name for name in all_names 
                if not self.params[name].is_optional]        
        
    def get_param_name_by_position(self, pos, param_count):
        """
        Find a proper parameter name for the position 'pos':
        If param_count is equal to the count of mandatory parameters of command,
        and there is some optional parameter, find the first mandatory parameter 
        from the position 'pos' to the end. Else, return the name on position pos.
        (This function will be changed if bindctl command line syntax is changed
        in the future. )
        """
        if type(pos) != int:
            raise KeyError(str(pos) + " is not an integer")

        else:
            params = self.params.copy()
            del params['help']
            count = len(params)
            if (pos >= count):
                raise KeyError(str(pos) + " out of range")

            mandatory_count = len(self.get_mandatory_param_names())
            param_names = list(params.keys())
            if (param_count == mandatory_count) and (param_count < count):
                while pos < count:
                    if not params[param_names[pos]].is_optional:
                        return param_names[pos]
                    pos += 1
                
                raise KeyError(str(pos) + "parameters have error")
            else:
                return param_names[pos]


    def command_help(self):
        """Prints the help info for this command to stdout"""
        print("Command ", self)
        print("\t\thelp (Get help for command)")

        params = self.params.copy()
        del params["help"]

        if len(params) == 0:
            print("This command has no parameters")
            return

        print("Parameters:")
        for info in params.values():
            print("    %s" % info.get_basic_info())
            description = info.get_desc()
            if description != "":
                print(textwrap.fill(description,
                      initial_indent="        ",
                      subsequent_indent="        ",
                      width=70))

class ModuleInfo:
    """Define the information of one module, include module name, 
    module supporting commands.
    """    
    
    def __init__(self, name, desc = ""):
        self.name = name
        self.desc = desc
        self.commands = OrderedDict()         
        self.add_command(CommandInfo(name = "help", 
                                     desc = "Get help for module."))
        
    def __str__(self):
        return str("%s \t%s" % (self.name, self.desc))

    def get_name(self):
        return self.name

    def get_desc(self):
        return self.desc

    def add_command(self, command_info):
        """Add a CommandInfo to this ModuleInfo."""
        self.commands[command_info.name] = command_info
        
    def has_command_with_name(self, command_name):
        """Returns true if this module has a command with the given name."""
        return command_name in self.commands
        
    def get_command_with_name(self, command_name):
        """Returns the CommandInfo for the command with the given name.
           Raises a KeyError if not found"""
        return self.commands[command_name]
        
    def get_commands(self):
        """Returns a list of all CommandInfo objects for this module."""
        return list(self.commands.values())
        
    def get_command_names(self):
        """Returns a list of the names of all commands for this module."""
        return list(self.commands.keys())

    def module_help(self):
        """Prints the help info for this module to stdout"""
        print("Module " + str(self))
        print("Available commands:")
        for k in self.commands.values():
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
            
    def command_help(self, command):
        """Prints the help info for the command with the given name.
           Raises KeyError if not found"""
        self.commands[command].command_help()    

