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


import unittest
import isc.cc.data
import os
from bindctl import cmdparse
from bindctl import bindcmd
from bindctl.moduleinfo import *
from bindctl.exception import *    
try:
    from collections import OrderedDict
except ImportError:
    from mycollections import OrderedDict

class TestCmdLex(unittest.TestCase):
    
    def my_assert_raise(self, exception_type, cmd_line):
        self.assertRaises(exception_type, cmdparse.BindCmdParse, cmd_line)


    def testCommandWithoutParameter(self):
        cmd = cmdparse.BindCmdParse("zone add")
        assert cmd.module == "zone"
        assert cmd.command == "add"
        self.assertEqual(len(cmd.params), 0)
        
    
    def testCommandWithParameters(self):
        lines = {"zone add zone_name = cnnic.cn, file = cnnic.cn.file master=1.1.1.1",
                 "zone add zone_name = \"cnnic.cn\", file ='cnnic.cn.file' master=1.1.1.1  ",
                 "zone add zone_name = 'cnnic.cn\", file ='cnnic.cn.file' master=1.1.1.1, " }
        
        for cmd_line in lines:
            cmd = cmdparse.BindCmdParse(cmd_line)
            assert cmd.module == "zone"
            assert cmd.command == "add"
            assert cmd.params["zone_name"] == "cnnic.cn"
            assert cmd.params["file"] == "cnnic.cn.file"
            assert cmd.params["master"] == '1.1.1.1'

    def testCommandWithParamters_2(self):
        '''Test whether the parameters in key=value can be parsed properly.'''
        cmd = cmdparse.BindCmdParse('zone cmd name = 1:34::2')
        self.assertEqual(cmd.params['name'], '1:34::2')

        cmd = cmdparse.BindCmdParse('zone cmd name = 1\"\'34**&2 value=44\"\'\"')
        self.assertEqual(cmd.params['name'], '1\"\'34**&2')
        self.assertEqual(cmd.params['value'], '44\"\'\"')

        cmd = cmdparse.BindCmdParse('zone cmd name = 1\"\'34**&2 ,value=  44\"\'\"')
        self.assertEqual(cmd.params['name'], '1\"\'34**&2')
        self.assertEqual(cmd.params['value'], '44\"\'\"')
            
        cmd = cmdparse.BindCmdParse('zone cmd name =  1\'34**&2value=44\"\'\" value = \"==============\'')
        self.assertEqual(cmd.params['name'], '1\'34**&2value=44\"\'\"')
        self.assertEqual(cmd.params['value'], '==============')

        cmd = cmdparse.BindCmdParse('zone cmd name =    \"1234, 567890 \" value ==&*/')
        self.assertEqual(cmd.params['name'], '1234, 567890 ')
        self.assertEqual(cmd.params['value'], '=&*/')
            
    def testCommandWithListParam(self):
        cmd = cmdparse.BindCmdParse("zone set zone_name='cnnic.cn', master='1.1.1.1, 2.2.2.2'")
        assert cmd.params["master"] == '1.1.1.1, 2.2.2.2'            
        
    def testCommandWithHelpParam(self):
        cmd = cmdparse.BindCmdParse("zone add help")
        assert cmd.params["help"] == "help"
        
        cmd = cmdparse.BindCmdParse("zone add help *&)&)*&&$#$^%")
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

class TestCmdSyntax(unittest.TestCase):
    
    def _create_bindcmd(self):
        """Create one bindcmd"""
        
        tool = bindcmd.BindCmdInterpreter()        
        string_spec = { 'item_type' : 'string',
                       'item_optional' : False,
                       'item_default' : ''}
        int_spec = { 'item_type' : 'integer',
                       'item_optional' : False,
                       'item_default' : 10}
        zone_file_param = ParamInfo(name = "zone_file", param_spec = string_spec)
        zone_name = ParamInfo(name = 'zone_name', param_spec = string_spec)
        load_cmd = CommandInfo(name = "load")
        load_cmd.add_param(zone_file_param)
        load_cmd.add_param(zone_name)
        
        param_master = ParamInfo(name = "master", optional = True, param_spec = string_spec)                                 
        param_master = ParamInfo(name = "port", optional = True, param_spec = int_spec)                                 
        param_allow_update = ParamInfo(name = "allow_update", optional = True, param_spec = string_spec)                                           
        set_cmd = CommandInfo(name = "set")
        set_cmd.add_param(param_master)
        set_cmd.add_param(param_allow_update)
        set_cmd.add_param(zone_name)
        
        reload_all_cmd = CommandInfo(name = "reload_all")        
        
        zone_module = ModuleInfo(name = "zone")                             
        zone_module.add_command(load_cmd)
        zone_module.add_command(set_cmd)
        zone_module.add_command(reload_all_cmd)
        
        tool.add_module_info(zone_module)
        return tool
        
        
    def setUp(self):
        self.bindcmd = self._create_bindcmd()
        
        
    def no_assert_raise(self, cmd_line):
        cmd = cmdparse.BindCmdParse(cmd_line)
        self.bindcmd._validate_cmd(cmd) 
        
        
    def my_assert_raise(self, exception_type, cmd_line):
        cmd = cmdparse.BindCmdParse(cmd_line)
        self.assertRaises(exception_type, self.bindcmd._validate_cmd, cmd)  
        
        
    def testValidateSuccess(self):
        self.no_assert_raise("zone load zone_file='cn' zone_name='cn'")
        self.no_assert_raise("zone load zone_file='cn', zone_name='cn', ")
        self.no_assert_raise("zone help ")
        self.no_assert_raise("zone load help ")
        self.no_assert_raise("zone help help='dd' ")
        self.no_assert_raise("zone set allow_update='1.1.1.1' zone_name='cn'")
        self.no_assert_raise("zone set zone_name='cn'")
        self.my_assert_raise(isc.cc.data.DataTypeError, "zone set zone_name ='cn', port='cn'")
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
       
class TestModuleInfo(unittest.TestCase):

    def test_get_param_name_by_position(self):
        cmd = CommandInfo('command')
        cmd.add_param(ParamInfo('name'))
        cmd.add_param(ParamInfo('age'))
        cmd.add_param(ParamInfo('data', optional = True))
        cmd.add_param(ParamInfo('sex'))
        self.assertEqual('name', cmd.get_param_name_by_position(0, 2))
        self.assertEqual('age', cmd.get_param_name_by_position(1, 2))
        self.assertEqual('sex', cmd.get_param_name_by_position(2, 3))
        self.assertEqual('data', cmd.get_param_name_by_position(2, 4))
        self.assertEqual('data', cmd.get_param_name_by_position(2, 4))
        
        self.assertRaises(KeyError, cmd.get_param_name_by_position, 4, 4)


    
class TestNameSequence(unittest.TestCase):
    """
    Test if the module/command/parameters is saved in the order creation
    """
    
    def _create_bindcmd(self):
        """Create one bindcmd"""     
        
        self._cmd = CommandInfo(name = "load")
        self.module = ModuleInfo(name = "zone")
        self.tool = bindcmd.BindCmdInterpreter()        
        for random_str in self.random_names:
            self._cmd.add_param(ParamInfo(name = random_str))
            self.module.add_command(CommandInfo(name = random_str))
            self.tool.add_module_info(ModuleInfo(name = random_str))  
        
    def setUp(self):
        self.random_names = ['1erdfeDDWsd', '3fe', '2009erd', 'Fe231', 'tere142', 'rei8WD']
        self._create_bindcmd()
        
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

    def test_apply_cfg_command(self):
        self.tool.location = '/'
        cmd = cmdparse.BindCmdParse("config set identifier=\"foo/bar\" value=\"5\"")
        self.tool.apply_config_cmd(cmd)
    
class FakeBindCmdInterpreter(bindcmd.BindCmdInterpreter):
    def __init__(self):
        pass

class TestBindCmdInterpreter(unittest.TestCase):

    def _create_invalid_csv_file(self, csvfilename):
        import csv
        csvfile = open(csvfilename, 'w')
        writer = csv.writer(csvfile)
        writer.writerow(['name1'])
        writer.writerow(['name2'])
        csvfile.close()

    def test_get_saved_user_info(self):
        cmd = FakeBindCmdInterpreter()
        users = cmd._get_saved_user_info('/notexist', 'cvs_file.cvs')
        self.assertEqual([], users)
        
        csvfilename = 'csv_file.csv'
        self._create_invalid_csv_file(csvfilename)
        users = cmd._get_saved_user_info('./', csvfilename)
        self.assertEqual([], users)
        os.remove(csvfilename)

if __name__== "__main__":
    unittest.main()
    
