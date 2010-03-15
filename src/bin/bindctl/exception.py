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


class BindCtlException(Exception):
    """Abstract base class shared by all bindctl exceptions"""
    def __str__(self):
        return "Big tool has problem"

# Begin define Format exception

class CmdFormatError(BindCtlException):
    """Command is malformed"""
    def __str__(self):
        return "Command is malformed"

        
class CmdModuleNameFormatError(CmdFormatError):
    """module name format error"""

    def __str__(self):
        return "Module name format error: the charater of name can only be '0-9a-zA-Z_'" 
                      
                
class CmdCommandNameFormatError(CmdFormatError):
    """command name format error"""
    
    def __init__(self, module):
        self.module = module        
        
    def __str__(self):
        return "Command name format error: the charater of name can only be '0-9a-zA-Z_'"      
        
        
class CmdMissCommandNameFormatError(CmdFormatError):
    """Module name isn't finished"""
    
    def __init__(self, module):
        self.module = module
        
    def __str__(self):
        return "command name is missed"   


class CmdParamFormatError(CmdFormatError):
    """Command is malformed which parameter isn't key value pair"""
    
    def __init__(self, module, command):        
        self.module = module
        self.command = command        

    def __str__(self):
        return  "Parameter format error, it should like 'key = value'"         
        
# Begin define the exception for syntax

class CmdSyntaxError(BindCtlException):
    """Command line has syntax error"""
    
    def __str__(self):
        return "Command line has syntax error"


class CmdUnknownModuleSyntaxError(CmdSyntaxError):
    """Command is unknown"""
    def __init__(self, module):
        self.module = module

    def __str__(self):
        return str("Unknown module '%s'" % self.module)
        

class CmdUnknownCmdSyntaxError(CmdSyntaxError):
    """Command is unknown"""
    def __init__(self, module, command):
        self.module = module
        self.command = command

    def __str__(self):
        return str("Unknown command '%s' to module '%s'" % 
                    (self.command, self.module))
                    

class CmdUnknownParamSyntaxError(CmdSyntaxError):
    """The parameter of command is unknown"""
    def __init__(self, module, command, param):
        self.module = module
        self.command = command
        self.param = param

    def __str__(self):
        return str("Unknown parameter '%s' to command '%s' of module '%s'" %
                   (self.param, self.command, self.module))
                   

class CmdMissParamSyntaxError(CmdSyntaxError):
    """The parameter of one command is missed"""
    def __init__(self, module, command, param):
        self.module = module
        self.command = command
        self.param = param

    def __str__(self):
        return str("Parameter '%s' is missed for command '%s' of module '%s'" % 
                   (self.param, self.command, self.module))
                   
   
