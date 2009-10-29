try:
    from collections import OrderedDict
except ImportError:
    from mycollections import OrderedDict

# Define value type
STRING_TYPE = "string"
LIST_TYPE = "list"
INT_TYPE = "int"

MODULE_NODE_NAME = 'module'
COMMAND_NODE_NAME = 'command'
PARAM_NODE_NAME = 'param'


class ParamInfo:
    """The parameter of one command
    each command parameter have four attributes, 
    parameter name, parameter type, parameter value, and parameter description
    """
    def __init__(self, name, desc = '', type = STRING_TYPE, 
                 optional = False, value = '', default_value = ''):
        self.name = name
        self.type = type
        self.value = value
        self.default_value = default_value                           
        self.desc = desc
        self.is_optional = optional
    
    def __str__(self):        
        return str("\t%s <type: %s> \t(%s)" % (self.name, self.type, self.desc))

    def write_xml(xmldoc, name, value):
        node = xmldoc.createElement(PARAM_NODE_NAME)
        node.setAttribute('name', name)
        node.setAttribute('value', value)                             
        return node                                              

class CommandInfo:
    """One command which provide by one bind10 module, it has zero or 
    more parameters
    """

    def __init__(self, name, desc = "", need_inst_param = True):
        self.name = name
        # Wether command needs parameter "instance_name" 
        self.need_inst_param = need_inst_param 
        self.desc = desc
        self.params = OrderedDict()        
        # Set default parameter "help"
        self.add_param(ParamInfo("help", 
                                  desc = "Get help for command",
                                  optional = True))
                
    def __str__(self):
        return str("%s \t(%s)" % (self.name, self.desc))
        

    def add_param(self, paraminfo):
        self.params[paraminfo.name] = paraminfo
        

    def has_param_with_name(self, param_name):
        return param_name in self.params
        

    def get_param_with_name(self, param_name):
        return self.params[param_name]
        

    def get_params(self):
        return list(self.params.values())
        

    def get_param_names(self):
        return list(self.params.keys())
        
        
    def get_mandatory_param_names(self):
        all_names = self.params.keys()
        return [name for name in all_names 
                if not self.params[name].is_optional]        
        
        
    def need_instance_param(self):
        return self.need_inst_param

    
    def write_xml(self, xmldoc, command_name):
        node = xmldoc.createElement(COMMAND_NODE_NAME)
        node.setAttribute('name', command_name)
        return node 
        

    def command_help(self, inst_name, inst_type, inst_desc):
        print("Command ", self)
        print("\t\thelp (Get help for command)")
                
        params = self.params.copy()
        del params["help"]

        if len(params) == 0:
            print("\tNo parameters for the command")
            return
        
        print("\n\tMandatory parameters:")
        mandatory_infos = []
        for info in params.values():            
            if not info.is_optional:
                print("\t", info)
                mandatory_infos.append(info)

        optional_infos = [info for info in params.values() 
                          if info not in mandatory_infos]
        if len(optional_infos) > 0:
            print("\n\tOptional parameters:")      
            for info in optional_infos:
                    print("\t", info)


class ModuleInfo:
    """Define the information of one module, include module name, 
    module supporting commands, instance name and the value type of instance name
    """    
    
    def __init__(self, name, inst_name = "", inst_type = STRING_TYPE, 
                 inst_desc = "", desc = ""):
        self.name = name
        self.inst_name = inst_name
        self.inst_type = inst_type
        self.inst_desc = inst_desc
        self.desc = desc
        self.commands = OrderedDict()         
        self.add_command(CommandInfo(name = "help", 
                                     desc = "Get help for module",
                                     need_inst_param = False))
        
    def __str__(self):
        return str("%s \t%s" % (self.name, self.desc))
        
    def add_command(self, command_info):        
        self.commands[command_info.name] = command_info
        if command_info.need_instance_param():
            command_info.add_param(ParamInfo(name = self.inst_name, 
                                             type = self.inst_type,
                                             desc = self.inst_desc))

        
    def has_command_with_name(self, command_name):
        return command_name in self.commands
        

    def get_command_with_name(self, command_name):
        return self.commands[command_name]
        
        
    def get_commands(self):
        return list(self.commands.values())
        
    
    def get_command_names(self):
        return list(self.commands.keys())
        
    
    def get_instance_param_name(self):
        return self.inst_name
        
        
    def get_instance_param_type(self):
        return self.inst_type
        

    def module_help(self):
        print("Module ", self, "\nAvailable commands:")
        for k in self.commands.keys():
            print("\t", self.commands[k])
            
            
    def command_help(self, command):
        self.commands[command].command_help(self.inst_name, 
                                            self.inst_type,
                                            self.inst_desc)
    
    def write_xml(self, xmldoc, module_name):
        node = xmldoc.createElement(MODULE_NODE_NAME)
        node.setAttribute('name', module_name)
        return node
    

