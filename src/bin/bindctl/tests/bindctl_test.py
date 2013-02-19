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
import io
import errno
import sys
import socket
import ssl
import http.client
import pwd
import getpass
import re
import json
from optparse import OptionParser
from isc.config.config_data import ConfigData, MultiConfigData
from isc.config.module_spec import ModuleSpec
from isc.testutils.parse_args import TestOptParser, OptsError
from bindctl_main import set_bindctl_options
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
        self.assertRaises(exception_type, cmdparse.BindCmdParser, cmd_line)


    def testCommandWithoutParameter(self):
        cmd_parser = cmdparse.BindCmdParser("zone add")
        assert cmd_parser.module == "zone"
        assert cmd_parser.command == "add"
        self.assertEqual(len(cmd_parser.params), 0)


    def testCommandWithParameters(self):
        lines = {"zone add zone_name = cnnic.cn, file = cnnic.cn.file master=1.1.1.1",
                 "zone add zone_name = \"cnnic.cn\", file ='cnnic.cn.file' master=1.1.1.1  ",
                 "zone add zone_name = 'cnnic.cn\", file ='cnnic.cn.file' master=1.1.1.1, " }

        for cmd_line in lines:
            cmd_parser = cmdparse.BindCmdParser(cmd_line)
            assert cmd_parser.module == "zone"
            assert cmd_parser.command == "add"
            assert cmd_parser.params["zone_name"] == "cnnic.cn"
            assert cmd_parser.params["file"] == "cnnic.cn.file"
            assert cmd_parser.params["master"] == '1.1.1.1'

    def testCommandWithParamters_2(self):
        '''Test whether the parameters in key=value can be parsed properly.'''
        cmd_parser = cmdparse.BindCmdParser('zone cmd name = 1:34::2')
        self.assertEqual(cmd_parser.params['name'], '1:34::2')

        cmd_parser = cmdparse.BindCmdParser('zone cmd name = 1\"\'34**&2'
                                            ' value=44\"\'\"')
        self.assertEqual(cmd_parser.params['name'], '1\"\'34**&2')
        self.assertEqual(cmd_parser.params['value'], '44\"\'\"')

        cmd_parser = cmdparse.BindCmdParser('zone cmd name = 1\"\'34**&2'
                                            ',value=  44\"\'\"')
        self.assertEqual(cmd_parser.params['name'], '1\"\'34**&2')
        self.assertEqual(cmd_parser.params['value'], '44\"\'\"')

        cmd_parser = cmdparse.BindCmdParser('zone cmd name =  1\'34**&2'
                                            'value=44\"\'\" value = '
                                            '\"==============\'')
        self.assertEqual(cmd_parser.params['name'], '1\'34**&2value=44\"\'\"')
        self.assertEqual(cmd_parser.params['value'], '==============')

        cmd_parser = cmdparse.BindCmdParser('zone cmd name =    \"1234, '
                                            '567890 \" value ==&*/')
        self.assertEqual(cmd_parser.params['name'], '1234, 567890 ')
        self.assertEqual(cmd_parser.params['value'], '=&*/')

    def testCommandWithListParam(self):
        cmd_parser = cmdparse.BindCmdParser("zone set zone_name='cnnic.cn', "
                                            "master='1.1.1.1, 2.2.2.2'")
        assert cmd_parser.params["master"] == '1.1.1.1, 2.2.2.2'

    def testCommandWithHelpParam(self):
        cmd_parser = cmdparse.BindCmdParser("zone add help")
        assert cmd_parser.params["help"] == "help"

        cmd_parser = cmdparse.BindCmdParser("zone add help *&)&)*&&$#$^%")
        assert cmd_parser.params["help"] == "help"
        self.assertEqual(len(cmd_parser.params), 1)


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
        zone_file_param = ParamInfo(name = "zone_file",
                                    param_spec = string_spec)
        zone_name = ParamInfo(name = 'zone_name', param_spec = string_spec)
        load_cmd = CommandInfo(name = "load")
        load_cmd.add_param(zone_file_param)
        load_cmd.add_param(zone_name)

        param_master = ParamInfo(name = "master", optional = True,
                                 param_spec = string_spec)
        param_master = ParamInfo(name = "port", optional = True,
                                 param_spec = int_spec)
        param_allow_update = ParamInfo(name = "allow_update",
                                       optional = True,
                                       param_spec = string_spec)
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
        cmd_parser = cmdparse.BindCmdParser(cmd_line)
        self.bindcmd._validate_cmd(cmd_parser)


    def my_assert_raise(self, exception_type, cmd_line):
        cmd_parser = cmdparse.BindCmdParser(cmd_line)
        self.assertRaises(exception_type, self.bindcmd._validate_cmd,
                          cmd_parser)


    def testValidateSuccess(self):
        self.no_assert_raise("zone load zone_file='cn' zone_name='cn'")
        self.no_assert_raise("zone load zone_file='cn', zone_name='cn', ")
        self.no_assert_raise("zone help ")
        self.no_assert_raise("zone load help ")
        self.no_assert_raise("zone help help='dd' ")
        self.no_assert_raise("zone set allow_update='1.1.1.1' zone_name='cn'")
        self.no_assert_raise("zone set zone_name='cn'")
        self.my_assert_raise(isc.cc.data.DataTypeError,
                             "zone set zone_name ='cn', port='cn'")
        self.no_assert_raise("zone reload_all")

    def testCmdUnknownModuleSyntaxError(self):
        self.my_assert_raise(CmdUnknownModuleSyntaxError, "zoned d")
        self.my_assert_raise(CmdUnknownModuleSyntaxError, "dd dd  ")

    def testCmdUnknownCmdSyntaxError(self):
        self.my_assert_raise(CmdUnknownCmdSyntaxError, "zone dd")

    def testCmdMissParamSyntaxError(self):
        self.my_assert_raise(CmdMissParamSyntaxError,
                             "zone load zone_file='cn'")
        self.my_assert_raise(CmdMissParamSyntaxError,
                             "zone load zone_name='cn'")
        self.my_assert_raise(CmdMissParamSyntaxError,
                             "zone set allow_update='1.1.1.1'")
        self.my_assert_raise(CmdMissParamSyntaxError,
                             "zone set ")

    def testCmdUnknownParamSyntaxError(self):
        self.my_assert_raise(CmdUnknownParamSyntaxError,
                             "zone load zone_d='cn'")
        self.my_assert_raise(CmdUnknownParamSyntaxError,
                             "zone reload_all zone_name = 'cn'")
        self.my_assert_raise(CmdUnknownParamSyntaxError,
                             "zone help a b c")

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
        self.random_names = ['1erdfeDDWsd', '3fe', '2009erd',
                             'Fe231', 'tere142', 'rei8WD']
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

# tine class to fake a UIModuleCCSession, but only the config data
# parts for the next set of tests
class FakeCCSession(MultiConfigData):
    def __init__(self):
        self._local_changes = {}
        self._current_config = {}
        self._specifications = {}
        self.add_foo_spec()

    def add_foo_spec(self):
        spec = { "module_name": "foo",
                 "config_data": [
                 { "item_name": "an_int",
                   "item_type": "integer",
                   "item_optional": False,
                   "item_default": 1
                 },
                 { "item_name": "a_list",
                   "item_type": "list",
                   "item_optional": False,
                   "item_default": [],
                   "list_item_spec":
                   { "item_name": "a_string",
                     "item_type": "string",
                     "item_optional": False,
                     "item_default": "bar"
                   }
                 }
                 ]
               }
        self.set_specification(ModuleSpec(spec))


# fake socket
class FakeSocket():
    def __init__(self):
        self.run = True

    def connect(self, to):
        if not self.run:
            raise socket.error

    def close(self):
        self.run = False

    def send(self, data):
        if not self.run:
            raise socket.error
        return len(data)

    def makefile(self, type):
        return self

    def sendall(self, data):
        if not self.run:
            raise socket.error
        return len(data)


class TestConfigCommands(unittest.TestCase):
    def setUp(self):
        self.tool = bindcmd.BindCmdInterpreter()
        mod_info = ModuleInfo(name = "foo")
        self.tool.add_module_info(mod_info)
        self.tool.config_data = FakeCCSession()
        self.stdout_backup = sys.stdout
        self.printed_messages = []
        self.tool._print = self.store_print

    def test_precmd(self):
        def update_all_modules_info():
            raise socket.error
        def precmd(line):
            self.tool.precmd(line)
        self.tool._update_all_modules_info = update_all_modules_info
        # If line is equals to 'EOF', _update_all_modules_info()
        # shouldn't be called
        precmd('EOF')
        self.assertRaises(socket.error, precmd, 'continue')

    def store_print(self, *args):
        '''Method to override _print in BindCmdInterpreter.
           Instead of printing the values, appends the argument tuple
           to the list in self.printed_messages'''
        self.printed_messages.append(" ".join(map(str, args)))

    def __check_printed_message(self, expected_message, printed_message):
        self.assertIsNotNone(re.match(expected_message, printed_message),
                             "Printed message '" + printed_message +
                             "' does not match '" + expected_message + "'")

    def __check_printed_messages(self, expected_messages):
        '''Helper test function to check the printed messages against a list
           of regexps'''
        self.assertEqual(len(expected_messages), len(self.printed_messages))
        for _ in map(self.__check_printed_message,
                     expected_messages,
                     self.printed_messages):
            pass

    def test_try_login(self):
        # Make sure __try_login raises the correct exception
        # upon failure of either send_POST or the read() on the
        # response

        orig_send_POST = self.tool.send_POST
        expected_printed_messages = []
        try:
            def send_POST_raiseImmediately(self, params):
                raise socket.error("test error")

            self.tool.send_POST = send_POST_raiseImmediately
            self.assertRaises(FailToLogin, self.tool._try_login, "foo", "bar")
            expected_printed_messages.append(
                'Socket error while sending login information:  test error')
            self.__check_printed_messages(expected_printed_messages)

            def create_send_POST_raiseOnRead(exception):
                '''Create a replacement send_POST() method that raises
                   the given exception when read() is called on the value
                   returned from send_POST()'''
                def send_POST_raiseOnRead(self, params):
                    class MyResponse:
                        def read(self):
                            raise exception
                    return MyResponse()
                return send_POST_raiseOnRead

            # basic socket error
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(socket.error("read error"))
            self.assertRaises(FailToLogin, self.tool._try_login, "foo", "bar")
            expected_printed_messages.append(
                'Socket error while sending login information:  read error')
            self.__check_printed_messages(expected_printed_messages)

            # connection reset
            exc = socket.error("connection reset")
            exc.errno = errno.ECONNRESET
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(exc)
            self.assertRaises(FailToLogin, self.tool._try_login, "foo", "bar")
            expected_printed_messages.append(
                'Socket error while sending login information:  '
                'connection reset')
            expected_printed_messages.append(
                'Please check the logs of b10-cmdctl, there may be a '
                'problem accepting SSL connections, such as a permission '
                'problem on the server certificate file.'
            )
            self.__check_printed_messages(expected_printed_messages)

            # 'normal' SSL error
            exc = ssl.SSLError()
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(exc)
            self.assertRaises(FailToLogin, self.tool._try_login, "foo", "bar")
            expected_printed_messages.append(
                'SSL error while sending login information:  .*')
            self.__check_printed_messages(expected_printed_messages)

            # 'EOF' SSL error
            exc = ssl.SSLError()
            exc.errno = ssl.SSL_ERROR_EOF
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(exc)
            self.assertRaises(FailToLogin, self.tool._try_login, "foo", "bar")
            expected_printed_messages.append(
                'SSL error while sending login information: .*')
            expected_printed_messages.append(
                'Please check the logs of b10-cmdctl, there may be a '
                'problem accepting SSL connections, such as a permission '
                'problem on the server certificate file.'
            )
            self.__check_printed_messages(expected_printed_messages)

            # any other exception should be passed through
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(ImportError())
            self.assertRaises(ImportError, self.tool._try_login, "foo", "bar")
            self.__check_printed_messages(expected_printed_messages)

        finally:
            self.tool.send_POST = orig_send_POST

    def test_have_users(self):
        # Make sure __have_users raises the correct exception
        # upon failure of either send_POST or the read() on the
        # response

        orig_send_POST = self.tool.send_POST
        expected_printed_messages = []
        try:
            # Check what happens when cmdctl returns a HTTP server failure
            def send_POST_HTTPFailure(self, params=None):
                '''Replacement send_POST() method that returns a
                HTTP failure code.'''
                class MyResponse:
                    def __init__(self):
                        self.status = http.client.SERVICE_UNAVAILABLE
                    def read(self):
                        return ''
                return MyResponse()

            self.tool.send_POST = send_POST_HTTPFailure
            self.assertRaises(FailToLogin, self.tool._have_users)
            expected_printed_messages.append(
                'Failure in cmdctl when checking if users already exist')
            self.__check_printed_messages(expected_printed_messages)

            # Check what happens when cmdctl returns a result successfully
            def create_send_POST_success(status):
                '''Create a replacement send_POST() method that
                successfully returns status.'''
                def send_POST_success(self, params=None):
                    class MyResponse:
                        def __init__(self):
                            self.status = http.client.OK
                        def read(self):
                            class MyData:
                                def decode(self):
                                    return json.dumps(status)
                            return MyData()
                    return MyResponse()
                return send_POST_success

            # Users exist
            self.tool.send_POST = create_send_POST_success(True)
            self.assertTrue(self.tool._have_users())

            # Users don't exist
            self.tool.send_POST = create_send_POST_success(False)
            self.assertFalse(self.tool._have_users())

            # Check what happens when send_POST() raises an exception
            def send_POST_raiseImmediately(self, params=None):
                raise socket.error("test error")

            self.tool.send_POST = send_POST_raiseImmediately
            self.assertRaises(FailToLogin, self.tool._have_users)
            expected_printed_messages.append(
                'Socket error checking if users exist:  test error')
            self.__check_printed_messages(expected_printed_messages)

            # Check what happens when reading a HTTP response raises an
            # exception
            def create_send_POST_raiseOnRead(exception):
                '''Create a replacement send_POST() method that raises
                   the given exception when read() is called on the value
                   returned from send_POST()'''
                def send_POST_raiseOnRead(self, params=None):
                    class MyResponse:
                        def __init__(self):
                            self.status = http.client.OK
                        def read(self):
                            raise exception
                    return MyResponse()
                return send_POST_raiseOnRead

            # basic socket error
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(socket.error("read error"))
            self.assertRaises(FailToLogin, self.tool._have_users)
            expected_printed_messages.append(
                'Socket error checking if users exist:  read error')
            self.__check_printed_messages(expected_printed_messages)

            # connection reset
            exc = socket.error("connection reset")
            exc.errno = errno.ECONNRESET
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(exc)
            self.assertRaises(FailToLogin, self.tool._have_users)
            expected_printed_messages.append(
                'Socket error checking if users exist:  '
                'connection reset')
            expected_printed_messages.append(
                'Please check the logs of b10-cmdctl, there may be a '
                'problem accepting SSL connections, such as a permission '
                'problem on the server certificate file.'
            )
            self.__check_printed_messages(expected_printed_messages)

            # 'normal' SSL error
            exc = ssl.SSLError()
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(exc)
            self.assertRaises(FailToLogin, self.tool._have_users)
            expected_printed_messages.append(
                'SSL error checking if users exist:  .*')
            self.__check_printed_messages(expected_printed_messages)

            # 'EOF' SSL error
            exc = ssl.SSLError()
            exc.errno = ssl.SSL_ERROR_EOF
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(exc)
            self.assertRaises(FailToLogin, self.tool._have_users)
            expected_printed_messages.append(
                'SSL error checking if users exist: .*')
            expected_printed_messages.append(
                'Please check the logs of b10-cmdctl, there may be a '
                'problem accepting SSL connections, such as a permission '
                'problem on the server certificate file.'
            )
            self.__check_printed_messages(expected_printed_messages)

            # any other exception should be passed through
            self.tool.send_POST =\
                create_send_POST_raiseOnRead(ImportError())
            self.assertRaises(ImportError, self.tool._have_users)
            self.__check_printed_messages(expected_printed_messages)

        finally:
            self.tool.send_POST = orig_send_POST

    def test_run(self):
        def login_to_cmdctl():
            return True
        def cmd_loop():
            self.tool._send_message("/module_spec", None)

        self.tool.login_to_cmdctl = login_to_cmdctl
        # rewrite cmdloop() to avoid interactive mode
        self.tool.cmdloop = cmd_loop

        self.tool.conn.sock = FakeSocket()
        self.tool.conn.sock.close()

        self.assertEqual(1, self.tool.run())

        # First few lines may be some kind of heading, or a warning that
        # Python readline is unavailable, so we do a sub-string check.
        self.assertIn("Failed to send request, the connection is closed",
                      self.printed_messages)
        self.assertEqual(1, len(self.printed_messages))

        # validate log message for http.client.CannotSendRequest
        self.assertEqual(1, self.tool.run())

        # First few lines may be some kind of heading, or a warning that
        # Python readline is unavailable, so we do a sub-string check.
        self.assertIn("Can not send request, the connection is busy",
                      self.printed_messages)
        self.assertEqual(2, len(self.printed_messages))

    def test_apply_cfg_command_int(self):
        self.tool.location = '/'

        self.assertEqual((1, MultiConfigData.DEFAULT),
                         self.tool.config_data.get_value("/foo/an_int"))

        cmd_parser = cmdparse.BindCmdParser('config set identifier='
                                            '"foo/an_int" value="5"')
        self.tool.apply_config_cmd(cmd_parser)
        self.assertEqual((5, MultiConfigData.LOCAL),
                         self.tool.config_data.get_value("/foo/an_int"))

        cmd_parser = cmdparse.BindCmdParser('config unset identifier='
                                            '"foo/an_int"')
        self.tool.apply_config_cmd(cmd_parser)

        self.assertEqual((1, MultiConfigData.DEFAULT),
                         self.tool.config_data.get_value("/foo/an_int"))

        # this should raise a NotFoundError
        cmd_parser = cmdparse.BindCmdParser('config set identifier='
                                            '"foo/bar" value="[]"')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.tool.apply_config_cmd, cmd_parser)

        cmd_parser = cmdparse.BindCmdParser('config unset identifier='
                                            '"foo/bar"')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.tool.apply_config_cmd, cmd_parser)

        # this should raise a TypeError
        cmd_parser = cmdparse.BindCmdParser('config set identifier='
                                            '"foo/an_int" value="[]"')
        self.assertRaises(isc.cc.data.DataTypeError,
                          self.tool.apply_config_cmd, cmd_parser)

    # this is a very specific one for use with a set of list tests
    # to try out the flexibility of the parser (only in the next test)
    def clt(self, full_cmd_string, item_value):
        cmd_parser = cmdparse.BindCmdParser(full_cmd_string)
        self.tool.apply_config_cmd(cmd_parser)
        self.assertEqual(([item_value], MultiConfigData.LOCAL),
                         self.tool.config_data.get_value("/foo/a_list"))

    def test_apply_cfg_command_list(self):
        self.tool.location = '/'

        self.assertEqual(([], MultiConfigData.DEFAULT),
                         self.tool.config_data.get_value("/foo/a_list"))

        self.clt("config set identifier=\"foo/a_list\" value=[\"a\"]", "a")
        self.clt("config set identifier=\"foo/a_list\" value =[\"b\"]", "b")
        self.clt("config set identifier=\"foo/a_list\" value= [\"c\"]", "c")
        self.clt("config set identifier=\"foo/a_list\" value = [\"d\"]", "d")
        self.clt("config set identifier =\"foo/a_list\" value=[\"e\"]", "e")
        self.clt("config set identifier= \"foo/a_list\" value=[\"f\"]", "f")
        self.clt("config set identifier = \"foo/a_list\" value=[\"g\"]", "g")
        self.clt("config set identifier = \"foo/a_list\" value = [\"h\"]", "h")
        self.clt("config set identifier = \"foo/a_list\" value=[\"i\" ]", "i")
        self.clt("config set identifier = \"foo/a_list\" value=[ \"j\"]", "j")
        self.clt("config set identifier = \"foo/a_list\" value=[ \"k\" ]", "k")

        # this should raise a TypeError
        cmd_parser = cmdparse.BindCmdParser('config set identifier='
                                            '"foo/a_list" value="a"')
        self.assertRaises(isc.cc.data.DataTypeError,
                          self.tool.apply_config_cmd, cmd_parser)

        cmd_parser = cmdparse.BindCmdParser('config set identifier='
                                            '"foo/a_list" value=[1]')
        self.assertRaises(isc.cc.data.DataTypeError,
                          self.tool.apply_config_cmd, cmd_parser)

    def tearDown(self):
        sys.stdout = self.stdout_backup

    def test_cmd_has_identifier_param(self):
        module = ModuleInfo(name="test_module")

        cmd = CommandInfo(name="command_with_identifier")
        param = ParamInfo(name=bindcmd.CFGITEM_IDENTIFIER_PARAM)
        cmd.add_param(param)
        module.add_command(cmd)

        cmd = CommandInfo(name="command_without_identifier")
        param = ParamInfo(name="some_argument")
        cmd.add_param(param)
        module.add_command(cmd)

        self.tool.add_module_info(module)

        cmd_parser = cmdparse.BindCmdParser('test_module '
                                            'command_with_identifier')
        self.assertTrue(self.tool._cmd_has_identifier_param(cmd_parser))

        cmd_parser = cmdparse.BindCmdParser('test_module '
                                            'command_without_identifier')
        self.assertFalse(self.tool._cmd_has_identifier_param(cmd_parser))

        cmd_parser = cmdparse.BindCmdParser('badmodule '
                                            'command_without_identifier')
        self.assertFalse(self.tool._cmd_has_identifier_param(cmd_parser))

    def test_get_identifier_startswith(self):
        hints = self.tool._get_identifier_startswith("/")
        self.assertEqual(['foo/an_int', 'foo/a_list'], hints)

        hints = self.tool._get_identifier_startswith("/foo/an")
        self.assertEqual(['foo/an_int'], hints)

        hints = self.tool._get_identifier_startswith("/bar")
        self.assertEqual([], hints)

class FakeBindCmdInterpreter(bindcmd.BindCmdInterpreter):
    def __init__(self):
        pass

class TestBindCmdInterpreter(unittest.TestCase):

    def setUp(self):
        self.old_stdout = sys.stdout

    def tearDown(self):
        sys.stdout = self.old_stdout

    def _create_invalid_csv_file(self, csvfilename):
        import csv
        csvfile = open(csvfilename, 'w')
        writer = csv.writer(csvfile)
        writer.writerow(['name1'])
        writer.writerow(['name2'])
        csvfile.close()

    def test_csv_file_dir(self):
        # Checking default value
        home_dir = pwd.getpwnam(getpass.getuser()).pw_dir
        self.assertEqual(home_dir + os.sep + '.bind10' + os.sep,
                         bindcmd.BindCmdInterpreter().csv_file_dir)

        new_csv_dir = '/something/different/'
        custom_cmd = bindcmd.BindCmdInterpreter(csv_file_dir=new_csv_dir)
        self.assertEqual(new_csv_dir, custom_cmd.csv_file_dir)

    def test_get_saved_user_info(self):
        with open(os.devnull, 'w') as f:
            sys.stdout = f
            cmd = bindcmd.BindCmdInterpreter()
            users = cmd._get_saved_user_info('/notexist', 'csv_file.csv')
            self.assertEqual([], users)

            csvfilename = 'csv_file.csv'
            self._create_invalid_csv_file(csvfilename)
            users = cmd._get_saved_user_info('./', csvfilename)
            self.assertEqual([], users)
            os.remove(csvfilename)

class TestCommandLineOptions(unittest.TestCase):
    def setUp(self):
        self.parser = TestOptParser()
        set_bindctl_options(self.parser)

    def test_csv_file_dir(self):
        # by default the option is "undefined"
        (options, _) = self.parser.parse_args([])
        self.assertEqual(None, options.csv_file_dir)

        # specify the option, valid case.
        (options, _) = self.parser.parse_args(['--csv-file-dir', 'some_dir'])
        self.assertEqual('some_dir', options.csv_file_dir)

        # missing option arg; should trigger parser error.
        self.assertRaises(OptsError, self.parser.parse_args,
                          ['--csv-file-dir'])

if __name__== "__main__":
    unittest.main()

