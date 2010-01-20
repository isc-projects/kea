import unittest
import command
import bindctl
from moduleinfo import *
from exception import *    
try:
    from collections import OrderedDict
except ImportError:
    from mycollections import OrderedDict

class TestCmdLex(unittest.TestCase):
    
    def my_assert_raise(self, exception_type, cmd_line):
        self.assertRaises(exception_type, command.BindCtlCmd, cmd_line)


    def testCommandWithoutParameter(self):
        cmd = command.BindCtlCmd("zone add")
        assert cmd.module == "zone"
        assert cmd.command == "add"
        self.assertEqual(len(cmd.params), 0)
        
    
    def testCommandWithParameters(self):
        lines = {"zone add zone_name = cnnic.cn, file = cnnic.cn.file master=1.1.1.1",
                 "zone add zone_name = \"cnnic.cn\", file ='cnnic.cn.file' master=1.1.1.1  ",
                 "zone add zone_name = 'cnnic.cn\", file ='cnnic.cn.file' master=1.1.1.1, " }
        
        for cmd_line in lines:
            cmd = command.BindCtlCmd(cmd_line)
            assert cmd.module == "zone"
            assert cmd.command == "add"
            assert cmd.params["zone_name"] == "cnnic.cn"
            assert cmd.params["file"] == "cnnic.cn.file"
            assert cmd.params["master"] == '1.1.1.1'
            
            
    def testCommandWithListParam(self):
            cmd = command.BindCtlCmd("zone set zone_name='cnnic.cn', master='1.1.1.1, 2.2.2.2'")
            assert cmd.params["master"] == '1.1.1.1, 2.2.2.2'            
        
        
    def testCommandWithHelpParam(self):
        cmd = command.BindCtlCmd("zone add help")
        assert cmd.params["help"] == "help"
        
        cmd = command.BindCtlCmd("zone add help *&)&)*&&$#$^%")
        assert cmd.params["help"] == "help"
        self.assertEqual(len(cmd.params), 1)
        

    def testCmdModuleNameFormatError(self):
        self.my_assert_raise(CmdModuleNameFormatError, "zone=good")
        self.my_assert_raise(CmdModuleNameFormatError, "zo/ne")        
        self.my_assert_raise(CmdModuleNameFormatError, "")        
        self.my_assert_raise(CmdModuleNameFormatError, "=zone")
        self.my_assert_raise(CmdModuleNameFormatError, "zone,")        
        
        
    def testCmdMissCommandNameFormatError(self):
        self.my_assert_raise(CmdMissCommandNameFormatError, "zone")
        self.my_assert_raise(CmdMissCommandNameFormatError, "zone ")
        self.my_assert_raise(CmdMissCommandNameFormatError, "help ")
        
             
    def testCmdCommandNameFormatError(self):
        self.my_assert_raise(CmdCommandNameFormatError, "zone =d")
        self.my_assert_raise(CmdCommandNameFormatError, "zone z=d")
        self.my_assert_raise(CmdCommandNameFormatError, "zone z-d ")
        self.my_assert_raise(CmdCommandNameFormatError, "zone zdd/")
        self.my_assert_raise(CmdCommandNameFormatError, "zone zdd/ \"")
        

    def testCmdParamFormatError(self): 
        self.my_assert_raise(CmdParamFormatError, "zone load load")
        self.my_assert_raise(CmdParamFormatError, "zone load load=")
        self.my_assert_raise(CmdParamFormatError, "zone load load==dd")
        self.my_assert_raise(CmdParamFormatError, "zone load , zone_name=dd zone_file=d" )
        self.my_assert_raise(CmdParamFormatError, "zone load zone_name=dd zone_file" )
        self.my_assert_raise(CmdParamFormatError, "zone zdd \"")
        

class TestCmdSyntax(unittest.TestCase):
    
    def _create_bindctl(self):
        """Create one bindctl"""
        
        tool = bindctl.BindCtl()        
        zone_file_param = ParamInfo(name = "zone_file")
        load_cmd = CommandInfo(name = "load")
        load_cmd.add_param(zone_file_param)
        
        param_master = ParamInfo(name = "master", optional = True)                                 
        param_allow_update = ParamInfo(name = "allow_update", optional = True)                                           
        set_cmd = CommandInfo(name = "set")
        set_cmd.add_param(param_master)
        set_cmd.add_param(param_allow_update)
        
        reload_all_cmd = CommandInfo(name = "reload_all", need_inst_param = False)        
        
        zone_module = ModuleInfo(name = "zone", inst_name = "zone_name")                             
        zone_module.add_command(load_cmd)
        zone_module.add_command(set_cmd)
        zone_module.add_command(reload_all_cmd)
        
        tool.add_module_info(zone_module)
        return tool
        
        
    def setUp(self):
        self.bindctl = self._create_bindctl()
        
        
    def no_assert_raise(self, cmd_line):
        cmd = command.BindCtlCmd(cmd_line)
        self.bindctl.validate_cmd(cmd) 
        
        
    def my_assert_raise(self, exception_type, cmd_line):
        cmd = command.BindCtlCmd(cmd_line)
        self.assertRaises(exception_type, self.bindctl.validate_cmd, cmd)  
        
        
    def testValidateSuccess(self):
        self.no_assert_raise("zone load zone_file='cn' zone_name='cn'")
        self.no_assert_raise("zone load zone_file='cn', zone_name='cn', ")
        self.no_assert_raise("zone help ")
        self.no_assert_raise("zone load help ")
        self.no_assert_raise("zone help help='dd' ")
        self.no_assert_raise("zone set allow_update='1.1.1.1' zone_name='cn'")
        self.no_assert_raise("zone set zone_name='cn'")
        self.no_assert_raise("zone reload_all")        
        
    
    def testCmdUnknownModuleSyntaxError(self):
        self.my_assert_raise(CmdUnknownModuleSyntaxError, "zoned d")
        self.my_assert_raise(CmdUnknownModuleSyntaxError, "dd dd  ")
        
              
    def testCmdUnknownCmdSyntaxError(self):
        self.my_assert_raise(CmdUnknownCmdSyntaxError, "zone dd")
        
    def testCmdMissParamSyntaxError(self):
        self.my_assert_raise(CmdMissParamSyntaxError, "zone load zone_file='cn'")
        self.my_assert_raise(CmdMissParamSyntaxError, "zone load zone_name='cn'")
        self.my_assert_raise(CmdMissParamSyntaxError, "zone set allow_update='1.1.1.1'")
        self.my_assert_raise(CmdMissParamSyntaxError, "zone set ")
        
    def testCmdUnknownParamSyntaxError(self):
        self.my_assert_raise(CmdUnknownParamSyntaxError, "zone load zone_d='cn'")
        self.my_assert_raise(CmdUnknownParamSyntaxError, "zone reload_all zone_name = 'cn'")  
        
    
class TestNameSequence(unittest.TestCase):
    """
    Test if the module/command/parameters is saved in the order creation
    """
    
    def _create_bindctl(self):
        """Create one bindctl"""     
        
        self._cmd = CommandInfo(name = "load")
        self.module = ModuleInfo(name = "zone")
        self.tool = bindctl.BindCtl()        
        for random_str in self.random_names:
            self._cmd.add_param(ParamInfo(name = random_str))
            self.module.add_command(CommandInfo(name = random_str))
            self.tool.add_module_info(ModuleInfo(name = random_str))  
        
    def setUp(self):
        self.random_names = ['1erdfeDDWsd', '3fe', '2009erd', 'Fe231', 'tere142', 'rei8WD']
        self._create_bindctl()
        
    def testSequence(self):        
        param_names = self._cmd.get_param_names()
        cmd_names = self.module.get_command_names()
        module_names = self.tool.get_module_names()
        
        i = 0
        while i < len(self.random_names):
            assert self.random_names[i] == param_names[i+1]
            assert self.random_names[i] == cmd_names[i+1]
            assert self.random_names[i] == module_names[i+1]
            i = i + 1
        
    
if __name__== "__main__":
    unittest.main()
    
