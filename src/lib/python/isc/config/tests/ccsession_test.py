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

#
# Tests for the ConfigData and MultiConfigData classes
#

import unittest
import os
from isc.config.ccsession import *
from isc.config.config_data import BIND10_CONFIG_DATA_VERSION
from unittest_fakesession import FakeModuleCCSession, WouldBlockForever
import bind10_config
import isc.log

class TestHelperFunctions(unittest.TestCase):
    def test_parse_answer(self):
        self.assertRaises(ModuleCCSessionError, parse_answer, 1)
        self.assertRaises(ModuleCCSessionError, parse_answer, { 'just a dict': 1 })
        self.assertRaises(ModuleCCSessionError, parse_answer, { 'result': 1 })
        self.assertRaises(ModuleCCSessionError, parse_answer, { 'result': [] })
        self.assertRaises(ModuleCCSessionError, parse_answer, { 'result': [ 'not_an_rcode' ] })
        self.assertRaises(ModuleCCSessionError, parse_answer, { 'result': [ 1, 2 ] })

        rcode, val = parse_answer({ 'result': [ 0 ] })
        self.assertEqual(0, rcode)
        self.assertEqual(None, val)
        rcode, val = parse_answer({ 'result': [ 0, "something" ] })
        self.assertEqual(0, rcode)
        self.assertEqual("something", val)
        rcode, val = parse_answer({ 'result': [ 1, "some error" ] })
        self.assertEqual(1, rcode)
        self.assertEqual("some error", val)

    def test_create_answer(self):
        self.assertRaises(ModuleCCSessionError, create_answer, 'not_an_int')
        self.assertRaises(ModuleCCSessionError, create_answer, 1, 2)
        self.assertRaises(ModuleCCSessionError, create_answer, 1)
        self.assertEqual({ 'result': [ 0 ] }, create_answer(0))
        self.assertEqual({ 'result': [ 1, 'something bad' ] }, create_answer(1, 'something bad'))
        self.assertEqual({ 'result': [ 0, 'something good' ] }, create_answer(0, 'something good'))
        self.assertEqual({ 'result': [ 0, ['some', 'list' ] ] }, create_answer(0, ['some', 'list']))
        self.assertEqual({ 'result': [ 0, {'some': 'map' } ] }, create_answer(0, {'some': 'map'}))

    def test_parse_command(self):
        cmd, arg = parse_command(1)
        self.assertEqual(None, cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({})
        self.assertEqual(None, cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({ 'not a command': 1})
        self.assertEqual(None, cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({ 'command': 1})
        self.assertEqual(None, cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({ 'command': []})
        self.assertEqual(None, cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({ 'command': [ 1 ]})
        self.assertEqual(None, cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({ 'command': [ 'command' ]})
        self.assertEqual('command', cmd)
        self.assertEqual(None, arg)

        cmd, arg = parse_command({ 'command': [ 'command', 1 ]})
        self.assertEqual('command', cmd)
        self.assertEqual(1, arg)

        cmd, arg = parse_command({ 'command': [ 'command', ['some', 'argument', 'list'] ]})
        self.assertEqual('command', cmd)
        self.assertEqual(['some', 'argument', 'list'], arg)

    def test_create_command(self):
        self.assertRaises(ModuleCCSessionError, create_command, 1)
        self.assertEqual({'command': [ 'my_command' ]}, create_command('my_command'))
        self.assertEqual({'command': [ 'my_command', 1 ]}, create_command('my_command', 1))
        self.assertEqual({'command': [ 'my_command', [ 'some', 'list' ] ]}, create_command('my_command', [ 'some', 'list' ]))
        self.assertEqual({'command': [ 'my_command', { 'some': 'map' } ]}, create_command('my_command', { 'some': 'map' }))

class TestModuleCCSession(unittest.TestCase):
    def setUp(self):
        if 'CONFIG_TESTDATA_PATH' in os.environ:
            self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        else:
            self.data_path = "../../../testdata"

    def spec_file(self, file):
        return self.data_path + os.sep + file

    def create_session(self, spec_file_name, config_handler = None,
                       command_handler = None, cc_session = None):
        return ModuleCCSession(self.spec_file(spec_file_name),
                               config_handler, command_handler,
                               cc_session, False)

    def test_init(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertEqual(isc.config.module_spec_from_file(self.spec_file("spec1.spec"))._module_spec, mccs.specification._module_spec)
        self.assertEqual(None, mccs._config_handler)
        self.assertEqual(None, mccs._command_handler)

    def test_start1(self):
        fake_session = FakeModuleCCSession()
        self.assertFalse("Spec1" in fake_session.subscriptions)
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertTrue("Spec1" in fake_session.subscriptions)

        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg(None, 'Spec1')
        fake_session.group_sendmsg(None, 'Spec1')
        self.assertRaises(ModuleCCSessionError, mccs.start)
        self.assertEqual(len(fake_session.message_queue), 2)
        self.assertEqual({'command': ['module_spec', {'module_name': 'Spec1'}]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec1'}]},
                         fake_session.get_message('ConfigManager', None))

        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec1")
        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec1")
        mccs.start()
        self.assertEqual(len(fake_session.message_queue), 2)

        self.assertEqual({'command': ['module_spec', {'module_name': 'Spec1'}]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec1'}]},
                         fake_session.get_message('ConfigManager', None))

        mccs = None
        self.assertFalse("Spec1" in fake_session.subscriptions)

    def test_start2(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg(None, 'Spec2')
        fake_session.group_sendmsg(None, 'Spec2')
        self.assertRaises(ModuleCCSessionError, mccs.start)
        self.assertEqual(len(fake_session.message_queue), 2)
        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec2")
        fake_session.group_sendmsg({'result': [ 0, {} ]}, "Spec2")
        mccs.start()
        self.assertEqual(len(fake_session.message_queue), 2)

        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

    def test_start3(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg(None, 'Spec2')
        fake_session.group_sendmsg(None, 'Spec2')
        self.assertRaises(ModuleCCSessionError, mccs.start)
        self.assertEqual(len(fake_session.message_queue), 2)
        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec2")
        fake_session.group_sendmsg({'result': [ 0, {} ]}, "Spec2")
        mccs.start()
        self.assertEqual(len(fake_session.message_queue), 2)

        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

    def test_start4(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg(None, 'Spec2')
        fake_session.group_sendmsg(None, 'Spec2')
        self.assertRaises(ModuleCCSessionError, mccs.start)
        self.assertEqual(len(fake_session.message_queue), 2)
        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec2")
        fake_session.group_sendmsg({'result': [ 1, "just an error" ]}, "Spec2")
        mccs.start()
        self.assertEqual(len(fake_session.message_queue), 2)

        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

    def test_start5(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg(None, 'Spec2')
        fake_session.group_sendmsg(None, 'Spec2')
        self.assertRaises(ModuleCCSessionError, mccs.start)
        self.assertEqual(len(fake_session.message_queue), 2)
        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

        self.assertEqual(len(fake_session.message_queue), 0)
        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec2")
        fake_session.group_sendmsg({'result': [ 0, {"Wrong": True} ]}, "Spec2")
        self.assertRaises(ModuleCCSessionError, mccs.start)
        self.assertEqual(len(fake_session.message_queue), 2)

        self.assertEqual({'command': ['module_spec', mccs.specification._module_spec]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))

    def test_stop(self):
        fake_session = FakeModuleCCSession()
        self.assertFalse("Spec1" in fake_session.subscriptions)
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertTrue("Spec1" in fake_session.subscriptions)

        self.assertEqual(len(fake_session.message_queue), 0)
        mccs.send_stopping()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'command': ['stopping', {'module_name': 'Spec1'}]},
                         fake_session.get_message('ConfigManager', None))

    def test_get_socket(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertNotEqual(None, mccs.get_socket())

    def test_get_session(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertEqual(fake_session, mccs._session)

    def test_close(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.close()
        self.assertEqual(None, fake_session._socket)

    def test_del_opened(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.__del__() # with opened fake_session

    def test_del_closed(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        fake_session.close()
        mccs.__del__() # with closed fake_session

    def my_config_handler_ok(self, new_config):
        return isc.config.ccsession.create_answer(0)

    def my_config_handler_err(self, new_config):
        return isc.config.ccsession.create_answer(1, "just an error")

    def my_config_handler_exc(self, new_config):
        raise Exception("just an exception")

    def my_command_handler_ok(self, command, args):
        return isc.config.ccsession.create_answer(0)

    def my_command_handler_no_answer(self, command, args):
        pass

    def test_check_command1(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)

        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 0)

        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec1")
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 0)

        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'Spec1': 'a' })

        fake_session.group_sendmsg(cmd, 'Spec1')
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [2, 'Spec1 has no config handler']},
                         fake_session.get_message('Spec1', None))

    def test_check_command2(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'Spec1': 'a' })
        fake_session.group_sendmsg(cmd, 'Spec1')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [1, 'No config_data specification']},
                         fake_session.get_message('Spec1', None))

    def test_check_command3(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'item1': 2 })
        fake_session.group_sendmsg(cmd, 'Spec2')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [0]},
                         fake_session.get_message('Spec2', None))

    def test_check_command4(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_err)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'item1': 'aaa' })
        fake_session.group_sendmsg(cmd, 'Spec2')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [1, 'aaa should be an integer']},
                         fake_session.get_message('Spec2', None))

    def test_check_command5(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_exc)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'item1': 'aaa' })
        fake_session.group_sendmsg(cmd, 'Spec2')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [1, 'aaa should be an integer']},
                         fake_session.get_message('Spec2', None))

    def test_check_command6(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command("print_message", "just a message")
        fake_session.group_sendmsg(cmd, 'Spec2')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [2, 'Spec2 has no command handler']},
                         fake_session.get_message('Spec2', None))

    """Many check_command tests look too similar, this is common body."""
    def common_check_command_check(self, cmd_handler,
            cmd_check=lambda mccs, _: mccs.check_command()):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_command_handler(cmd_handler)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command("print_message", "just a message")
        fake_session.group_sendmsg(cmd, 'Spec2')
        self.assertEqual(len(fake_session.message_queue), 1)
        cmd_check(mccs, fake_session)
        return fake_session

    def test_check_command7(self):
        fake_session = self.common_check_command_check(
            self.my_command_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [0]},
                         fake_session.get_message('Spec2', None))

    def test_check_command8(self):
        fake_session = self.common_check_command_check(
            self.my_command_handler_no_answer)
        self.assertEqual(len(fake_session.message_queue), 0)

    def test_check_command_block(self):
        """See if the message gets there even in blocking mode."""
        fake_session = self.common_check_command_check(
            self.my_command_handler_ok,
            lambda mccs, _: mccs.check_command(False))
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [0]},
                         fake_session.get_message('Spec2', None))

    def test_check_command_block_timeout(self):
        """Check it works if session has timeout and it sets it back."""
        def cmd_check(mccs, session):
            session.set_timeout(1)
            mccs.check_command(False)
        fake_session = self.common_check_command_check(
            self.my_command_handler_ok, cmd_check)
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [0]},
                         fake_session.get_message('Spec2', None))
        self.assertEqual(fake_session.get_timeout(), 1)

    def test_check_command_blocks_forever(self):
        """Check it would wait forever checking a command."""
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_command_handler(self.my_command_handler_ok)
        self.assertRaises(WouldBlockForever, lambda: mccs.check_command(False))

    def test_check_command_blocks_forever_timeout(self):
        """Like above, but it should wait forever even with timeout here."""
        fake_session = FakeModuleCCSession()
        fake_session.set_timeout(1)
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_command_handler(self.my_command_handler_ok)
        self.assertRaises(WouldBlockForever, lambda: mccs.check_command(False))

    def test_check_command_without_recvmsg1(self):
        "copied from test_check_command2"
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'Spec1': 'abcd' })
        env = { 'group': 'Spec1', 'from':None };
        mccs.check_command_without_recvmsg(cmd, env)
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [1, 'No config_data specification']},
                         fake_session.get_message('Spec1', None))

    def test_check_command_without_recvmsg2(self):
        "copied from test_check_command3"
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'item1': 2 })
        self.assertEqual(len(fake_session.message_queue), 0)
        env = { 'group':'Spec2', 'from':None }
        mccs.check_command_without_recvmsg(cmd, env)
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [0]},
                          fake_session.get_message('Spec2', None))

    def test_check_command_without_recvmsg3(self):
        "copied from test_check_command7"
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_command_handler(self.my_command_handler_ok)
        self.assertEqual(len(fake_session.message_queue), 0)
        cmd = isc.config.ccsession.create_command("print_message", "just a message")
        env = { 'group':'Spec2', 'from':None }
        self.assertEqual(len(fake_session.message_queue), 0)
        mccs.check_command_without_recvmsg(cmd, env)
        self.assertEqual({'result': [0]},
                         fake_session.get_message('Spec2', None))

    def test_check_command_block_timeout(self):
        """Check it works if session has timeout and it sets it back."""
        def cmd_check(mccs, session):
            session.set_timeout(1)
            mccs.check_command(False)
        fake_session = self.common_check_command_check(
            self.my_command_handler_ok, cmd_check)
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [0]},
                         fake_session.get_message('Spec2', None))
        self.assertEqual(fake_session.get_timeout(), 1)

    def test_check_command_blocks_forever(self):
        """Check it would wait forever checking a command."""
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_command_handler(self.my_command_handler_ok)
        self.assertRaises(WouldBlockForever, lambda: mccs.check_command(False))

    def test_check_command_blocks_forever_timeout(self):
        """Like above, but it should wait forever even with timeout here."""
        fake_session = FakeModuleCCSession()
        fake_session.set_timeout(1)
        mccs = self.create_session("spec2.spec", None, None, fake_session)
        mccs.set_command_handler(self.my_command_handler_ok)
        self.assertRaises(WouldBlockForever, lambda: mccs.check_command(False))

    # Now there's a group of tests testing both add_remote_config and
    # add_remote_config_by_name. Since they are almost the same (they differ
    # just in the parameter and that the second one asks one more question over
    # the bus), the actual test code is shared.
    #
    # These three functions are helper functions to easy up the writing of them.
    # To write a test, there need to be 3 functions. First, the function that
    # does the actual test. It looks like:
    # def _internal_test(self, function_lambda, param, fill_other_messages):
    #
    # The function_lambda provides the tested function if called on the
    # ccsession. The param is the parameter to pass to the function (either
    # the module name or the spec file name. The fill_other_messages fills
    # needed messages (the answer containing the module spec in case of add by
    # name, no messages in the case of adding by spec file) into the fake bus.
    # So, the code would look like:
    #
    # * Create the fake session and tested ccsession object
    # * function = function_lambda(ccsession object)
    # * fill_other_messages(fake session)
    # * Fill in answer to the get_module_config command
    # * Test by calling function(param)
    #
    # Then you need two wrappers that do launch the tests. There are helpers
    # for that, so you can just call:
    # def test_by_spec(self)
    #     self._common_remote_module_test(self._internal_test)
    # def test_by_name(self)
    #     self._common_remote_module_by_name_test(self._internal_test)
    def _common_remote_module_test(self, internal_test):
        internal_test(lambda ccs: ccs.add_remote_config,
                      self.spec_file("spec2.spec"),
                      lambda session: None)

    def _prepare_spec_message(self, session, spec_name):
        # It could have been one command, but the line would be way too long
        # to even split it
        spec_file = self.spec_file(spec_name)
        spec = isc.config.module_spec_from_file(spec_file)
        session.group_sendmsg({'result': [0, spec.get_full_spec()]}, "Spec1")

    def _common_remote_module_by_name_test(self, internal_test):
        internal_test(lambda ccs: ccs.add_remote_config_by_name, "Spec2",
                      lambda session: self._prepare_spec_message(session,
                                                                 "spec2.spec"))

    def _internal_remote_module(self, function_lambda, parameter,
                                fill_other_messages):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.remove_remote_config("Spec2")
        function = function_lambda(mccs)

        self.assertRaises(ModuleCCSessionError, mccs.get_remote_config_value, "Spec2", "item1")

        self.assertFalse("Spec2" in fake_session.subscriptions)
        fill_other_messages(fake_session)
        fake_session.group_sendmsg(None, 'Spec2')
        rmodname = function(parameter)
        self.assertTrue("Spec2" in fake_session.subscriptions)
        self.assertEqual("Spec2", rmodname)
        self.assertRaises(isc.cc.data.DataNotFoundError, mccs.get_remote_config_value, rmodname, "asdf")
        value, default = mccs.get_remote_config_value(rmodname, "item1")
        self.assertEqual(1, value)
        self.assertEqual(True, default)

        mccs.remove_remote_config(rmodname)
        self.assertFalse("Spec2" in fake_session.subscriptions)
        self.assertRaises(ModuleCCSessionError, mccs.get_remote_config_value, "Spec2", "item1")

        # test if unsubscription is also sent when object is deleted
        fill_other_messages(fake_session)
        fake_session.group_sendmsg({'result' : [0]}, 'Spec2')
        rmodname = function(parameter)
        self.assertTrue("Spec2" in fake_session.subscriptions)
        mccs = None
        function = None
        self.assertFalse("Spec2" in fake_session.subscriptions)

    def test_remote_module(self):
        """
        Test we can add a remote config and get the configuration.
        Remote module specified by the spec file name.
        """
        self._common_remote_module_test(self._internal_remote_module)

    def test_remote_module_by_name(self):
        """
        Test we can add a remote config and get the configuration.
        Remote module specified its name.
        """
        self._common_remote_module_by_name_test(self._internal_remote_module)

    def _internal_remote_module_with_custom_config(self, function_lambda,
                                                   parameter,
                                                   fill_other_messages):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        function = function_lambda(mccs)
        # override the default config value for "item1". add_remote_config[_by_name]()
        # should incorporate the overridden value, and we should be able to
        # get it via get_remote_config_value().
        fill_other_messages(fake_session)
        fake_session.group_sendmsg({'result': [0, {"item1": 10}]}, 'Spec2')
        rmodname = function(parameter)
        value, default = mccs.get_remote_config_value(rmodname, "item1")
        self.assertEqual(10, value)
        self.assertEqual(False, default)

    def test_remote_module_with_custom_config(self):
        """
        Test the config of module will load non-default values on
        initialization.
        Remote module specified by the spec file name.
        """
        self._common_remote_module_test(
            self._internal_remote_module_with_custom_config)

    def test_remote_module_by_name_with_custom_config(self):
        """
        Test the config of module will load non-default values on
        initialization.
        Remote module its name.
        """
        self._common_remote_module_by_name_test(
            self._internal_remote_module_with_custom_config)

    def _internal_ignore_command_remote_module(self, function_lambda, param,
                                               fill_other_messages):
        # Create a Spec1 module and subscribe to remote config for Spec2
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.set_command_handler(self.my_command_handler_ok)
        function = function_lambda(mccs)
        fill_other_messages(fake_session)
        fake_session.group_sendmsg(None, 'Spec2')
        rmodname = function(param)

        # remove the commands from queue
        while len(fake_session.message_queue) > 0:
            fake_session.get_message("ConfigManager")

        # check if the command for the module itself is received
        cmd = isc.config.ccsession.create_command("just_some_command", { 'foo': 'a' })
        fake_session.group_sendmsg(cmd, 'Spec1')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 1)
        self.assertEqual({'result': [ 0 ]},
                         fake_session.get_message('Spec1', None))

        # check if the command for the other module is ignored
        cmd = isc.config.ccsession.create_command("just_some_command", { 'foo': 'a' })
        fake_session.group_sendmsg(cmd, 'Spec2')
        self.assertEqual(len(fake_session.message_queue), 1)
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 0)

    def test_ignore_commant_remote_module(self):
        """
        Test that commands for remote modules aren't handled.
        Remote module specified by the spec file name.
        """
        self._common_remote_module_test(
            self._internal_ignore_command_remote_module)

    def test_ignore_commant_remote_module_by_name(self):
        """
        Test that commands for remote modules aren't handled.
        Remote module specified by its name.
        """
        self._common_remote_module_by_name_test(
            self._internal_ignore_command_remote_module)

    def _internal_check_command_without_recvmsg_remote_module(self,
                                                              function_lambda,
                                                              param,
                                                              fill_other_messages):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        function = function_lambda(mccs)
        self.assertEqual(len(fake_session.message_queue), 0)

        fill_other_messages(fake_session)
        fake_session.group_sendmsg(None, 'Spec2')
        rmodname = function(param)
        if (len(fake_session.message_queue) == 2):
            self.assertEqual({'command': ['get_module_spec',
                                          {'module_name': 'Spec2'}]},
                             fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual(len(fake_session.message_queue), 0)

        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'Spec2': { 'item1': 2 }})
        env = { 'group':'Spec2', 'from':None }
        self.assertEqual(len(fake_session.message_queue), 0)
        mccs.check_command_without_recvmsg(cmd, env)
        self.assertEqual(len(fake_session.message_queue), 0)

    def test_check_command_without_recvmsg_remote_module(self):
        """
        Test updates on remote module.
        The remote module is specified by the spec file name.
        """
        self._common_remote_module_test(
            self._internal_check_command_without_recvmsg_remote_module)

    def test_check_command_without_recvmsg_remote_module_by_name(self):
        """
        Test updates on remote module.
        The remote module is specified by its name.
        """
        self._common_remote_module_by_name_test(
            self._internal_check_command_without_recvmsg_remote_module)

    def _internal_check_command_without_recvmsg_remote_module2(self,
                                                               function_lambda,
                                                               param,
                                                               fill_other_messages):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        function = function_lambda(mccs)
        self.assertEqual(len(fake_session.message_queue), 0)

        fill_other_messages(fake_session)
        fake_session.group_sendmsg(None, 'Spec2')
        rmodname = function(param)
        if (len(fake_session.message_queue) == 2):
            self.assertEqual({'command': ['get_module_spec',
                                          {'module_name': 'Spec2'}]},
                             fake_session.get_message('ConfigManager', None))
        self.assertEqual({'command': ['get_config', {'module_name': 'Spec2'}]},
                         fake_session.get_message('ConfigManager', None))
        self.assertEqual(len(fake_session.message_queue), 0)

        cmd = isc.config.ccsession.create_command(isc.config.ccsession.COMMAND_CONFIG_UPDATE, { 'Spec3': { 'item1': 2 }})
        env = { 'group':'Spec3', 'from':None }
        self.assertEqual(len(fake_session.message_queue), 0)
        mccs.check_command_without_recvmsg(cmd, env)
        self.assertEqual(len(fake_session.message_queue), 0)

    def test_check_command_without_recvmsg_remote_module2(self):
        """
        Test updates on remote module.
        The remote module is specified by the spec file name.
        """
        self._common_remote_module_test(
            self._internal_check_command_without_recvmsg_remote_module2)

    def test_check_command_without_recvmsg_remote_module_by_name2(self):
        """
        Test updates on remote module.
        The remote module is specified by its name.
        """
        self._common_remote_module_by_name_test(
            self._internal_check_command_without_recvmsg_remote_module2)

    def _internal_remote_module_bad_config(self, function_lambda, parameter,
                                           fill_other_messages):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        function = function_lambda(mccs)
        # Provide wrong config data. It should be rejected.
        fill_other_messages(fake_session)
        fake_session.group_sendmsg({'result': [0, {"bad_item": -1}]}, 'Spec2')
        self.assertRaises(isc.config.ModuleCCSessionError,
                          function, parameter)

    def test_remote_module_bad_config(self):
        """
        Test the remote module rejects bad config data.
        """
        self._common_remote_module_test(
            self._internal_remote_module_bad_config)

    def test_remote_module_by_name_bad_config(self):
        """
        Test the remote module rejects bad config data.
        """
        self._common_remote_module_by_name_test(
            self._internal_remote_module_bad_config)

    def _internal_remote_module_error_response(self, function_lambda,
                                               parameter, fill_other_messages):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        function = function_lambda(mccs)
        # Provide wrong config data. It should be rejected.
        fill_other_messages(fake_session)
        fake_session.group_sendmsg({'result': [1, "An error, and I mean it!"]},
                                   'Spec2')
        self.assertRaises(isc.config.ModuleCCSessionError,
                          function, parameter)

    def test_remote_module_bad_config(self):
        """
        Test the remote module complains if there's an error response."
        """
        self._common_remote_module_test(
            self._internal_remote_module_error_response)

    def test_remote_module_by_name_bad_config(self):
        """
        Test the remote module complains if there's an error response."
        """
        self._common_remote_module_by_name_test(
            self._internal_remote_module_error_response)

    def test_remote_module_bad_config(self):
        """
        Test the remote module rejects bad config data.
        """
        self._common_remote_module_by_name_test(
            self._internal_remote_module_bad_config)

    def test_module_name_mismatch(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.set_config_handler(self.my_config_handler_ok)
        self._prepare_spec_message(fake_session, 'spec1.spec')
        self.assertRaises(isc.config.ModuleCCSessionError,
                          mccs.add_remote_config_by_name, "Spec2")

    def test_logconfig_handler(self):
        # test whether default_logconfig_handler reacts nicely to
        # bad data. We assume the actual logger output is tested
        # elsewhere
        self.assertRaises(TypeError, default_logconfig_handler);
        self.assertRaises(TypeError, default_logconfig_handler, 1);

        spec = isc.config.module_spec_from_file(
            path_search('logging.spec', bind10_config.PLUGIN_PATHS))
        config_data = ConfigData(spec)

        self.assertRaises(TypeError, default_logconfig_handler, 1, config_data)

        default_logconfig_handler({}, config_data)

        # Wrong data should not raise, but simply not be accepted
        # This would log a lot of errors, so we may want to suppress that later
        default_logconfig_handler({ "bad_data": "indeed" }, config_data)
        default_logconfig_handler({ "bad_data": 1}, config_data)
        default_logconfig_handler({ "bad_data": 1123 }, config_data)
        default_logconfig_handler({ "bad_data": True }, config_data)
        default_logconfig_handler({ "bad_data": False }, config_data)
        default_logconfig_handler({ "bad_data": 1.1 }, config_data)
        default_logconfig_handler({ "bad_data": [] }, config_data)
        default_logconfig_handler({ "bad_data": [[],[],[[1, 3, False, "foo" ]]] },
                                  config_data)
        default_logconfig_handler({ "bad_data": [ 1, 2, { "b": { "c": "d" } } ] },
                                  config_data)

        # Try a correct config
        log_conf = {"loggers":
                       [{"name": "b10-xfrout", "output_options":
                           [{"output": "/tmp/bind10.log",
                                       "destination": "file",
                                       "flush": True}]}]}
        default_logconfig_handler(log_conf, config_data)

class fakeData:
    def decode(self):
        return "{}";

class fakeAnswer:
    def read(self):
        return fakeData();

class fakeUIConn():
    def __init__(self):
        self.get_answers = {}
        self.post_answers = {}

    def set_get_answer(self, name, answer):
        self.get_answers[name] = answer

    def set_post_answer(self, name, answer):
        self.post_answers[name] = answer

    def send_GET(self, name, arg = None):
        if name in self.get_answers:
            return self.get_answers[name]
        else:
            return {}

    def send_POST(self, name, arg = None):
        if name in self.post_answers:
            return self.post_answers[name]
        else:
            return fakeAnswer()


class TestUIModuleCCSession(unittest.TestCase):
    def setUp(self):
        if 'CONFIG_TESTDATA_PATH' in os.environ:
            self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        else:
            self.data_path = "../../../testdata"

    def spec_file(self, file):
        return self.data_path + os.sep + file

    def create_uccs(self, fake_conn, specfile="spec2.spec"):
        module_spec = isc.config.module_spec_from_file(self.spec_file(specfile))
        fake_conn.set_get_answer('/module_spec', { module_spec.get_module_name(): module_spec.get_full_spec()})
        fake_conn.set_get_answer('/config_data', { 'version': BIND10_CONFIG_DATA_VERSION })
        return UIModuleCCSession(fake_conn)

    def create_uccs_named_set(self, fake_conn):
        module_spec = isc.config.module_spec_from_file(self.spec_file("spec32.spec"))
        fake_conn.set_get_answer('/module_spec', { module_spec.get_module_name(): module_spec.get_full_spec()})
        fake_conn.set_get_answer('/config_data', { 'version': BIND10_CONFIG_DATA_VERSION })
        return UIModuleCCSession(fake_conn)

    def create_uccs_listtest(self, fake_conn):
        module_spec = isc.config.module_spec_from_file(self.spec_file("spec39.spec"))
        fake_conn.set_get_answer('/module_spec', { module_spec.get_module_name(): module_spec.get_full_spec()})
        fake_conn.set_get_answer('/config_data', { 'version': BIND10_CONFIG_DATA_VERSION })
        return UIModuleCCSession(fake_conn)

    def test_init(self):
        fake_conn = fakeUIConn()
        fake_conn.set_get_answer('/module_spec', {})
        fake_conn.set_get_answer('/config_data', { 'version': BIND10_CONFIG_DATA_VERSION })
        uccs = UIModuleCCSession(fake_conn)
        self.assertEqual({}, uccs._specifications)
        self.assertEqual({ 'version': BIND10_CONFIG_DATA_VERSION}, uccs._current_config)

        module_spec = isc.config.module_spec_from_file(self.spec_file("spec2.spec"))
        fake_conn.set_get_answer('/module_spec', { module_spec.get_module_name(): module_spec.get_full_spec()})
        fake_conn.set_get_answer('/config_data', { 'version': BIND10_CONFIG_DATA_VERSION })
        uccs = UIModuleCCSession(fake_conn)
        self.assertEqual(module_spec._module_spec, uccs._specifications['Spec2']._module_spec)

        fake_conn.set_get_answer('/config_data', { 'version': 123123 })
        self.assertRaises(ModuleCCSessionError, UIModuleCCSession, fake_conn)

    def test_request_specifications(self):
        module_spec1 = isc.config.module_spec_from_file(
                          self.spec_file("spec1.spec"))
        module_spec_dict1 = { "module_spec": module_spec1.get_full_spec() }
        module_spec2 = isc.config.module_spec_from_file(
                          self.spec_file("spec2.spec"))
        module_spec_dict2 = { "module_spec": module_spec2.get_full_spec() }

        fake_conn = fakeUIConn()
        # Set the first one in the answer
        fake_conn.set_get_answer('/module_spec', module_spec_dict1)
        fake_conn.set_get_answer('/config_data',
                                 { 'version': BIND10_CONFIG_DATA_VERSION })
        uccs = UIModuleCCSession(fake_conn)

        # We should now have the first one, but not the second.
        self.assertTrue("Spec1" in uccs._specifications)
        self.assertEqual(module_spec1.get_full_spec(),
                         uccs._specifications["Spec1"].get_full_spec())
        self.assertFalse("Spec2" in uccs._specifications)

        # Now set an answer where only the second one is present
        fake_conn.set_get_answer('/module_spec', module_spec_dict2)

        uccs.request_specifications()

        # Now Spec1 should have been removed, and spec2 should be there
        self.assertFalse("Spec1" in uccs._specifications)
        self.assertTrue("Spec2" in uccs._specifications)
        self.assertEqual(module_spec2.get_full_spec(),
                         uccs._specifications["Spec2"].get_full_spec())

    def test_add_remove_value(self):
        fake_conn = fakeUIConn()
        uccs = self.create_uccs(fake_conn)

        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.add_value, 1, "a")
        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.add_value, "no_such_item", "a")
        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.add_value, "Spec2/item1", "a")
        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.remove_value, 1, "a")
        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.remove_value, "no_such_item", "a")
        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.remove_value, "Spec2/item1", "a")

        self.assertEqual({}, uccs._local_changes)
        uccs.add_value("Spec2/item5", "foo")
        self.assertEqual({'Spec2': {'item5': ['a', 'b', 'foo']}}, uccs._local_changes)
        uccs.remove_value("Spec2/item5", "foo")
        self.assertEqual({'Spec2': {'item5': ['a', 'b']}}, uccs._local_changes)
        uccs._local_changes = {'Spec2': {'item5': []}}
        uccs.remove_value("Spec2/item5", "foo")
        uccs.add_value("Spec2/item5", "foo")
        self.assertEqual({'Spec2': {'item5': ['foo']}}, uccs._local_changes)
        self.assertRaises(isc.cc.data.DataAlreadyPresentError,
                          uccs.add_value, "Spec2/item5", "foo")
        self.assertEqual({'Spec2': {'item5': ['foo']}}, uccs._local_changes)
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          uccs.remove_value, "Spec2/item5[123]", None)
        uccs.remove_value("Spec2/item5[0]", None)
        self.assertEqual({'Spec2': {'item5': []}}, uccs._local_changes)
        uccs.add_value("Spec2/item5", None);
        self.assertEqual({'Spec2': {'item5': ['']}}, uccs._local_changes)
        # Intending to empty a list element, but forget specifying the index.
        self.assertRaises(isc.cc.data.DataTypeError,
                          uccs.remove_value, "Spec2/item5", None)

    # Test adding and removing values for type = any
    def test_add_remove_value_any(self):
        fake_conn = fakeUIConn()
        uccs = self.create_uccs(fake_conn, "spec40.spec")

        # Test item set of basic types
        items = [ 1234, "foo", True, False ]
        items_as_str = [ '1234', 'foo', 'true', 'false' ]

        def test_fails():
            self.assertRaises(isc.cc.data.DataNotFoundError, uccs.add_value, "Spec40/item1", "foo")
            self.assertRaises(isc.cc.data.DataNotFoundError, uccs.add_value, "Spec40/item1", "foo", "bar")
            self.assertRaises(isc.cc.data.DataNotFoundError, uccs.remove_value, "Spec40/item1", "foo")
            self.assertRaises(isc.cc.data.DataTypeError, uccs.remove_value, "Spec40/item1[0]", None)

        # A few helper functions to perform a number of tests
        # (to repeat the same test for nested data)
        def check_list(identifier):
            for item in items_as_str:
                uccs.add_value(identifier, item)
            self.assertEqual((items, 1), uccs.get_value(identifier))

            # Removing from list should work in both ways
            uccs.remove_value(identifier, "foo")
            uccs.remove_value(identifier + "[1]", None)
            self.assertEqual(([1234, False], 1), uccs.get_value(identifier))

            # As should item indexing
            self.assertEqual((1234, 1), uccs.get_value(identifier + "[0]"))
            self.assertEqual((False, 1), uccs.get_value(identifier + "[1]"))

        def check_named_set(identifier):
            for item in items_as_str:
                # use string version as key as well
                uccs.add_value(identifier, item, item)

            self.assertEqual((1234, 1), uccs.get_value(identifier + "/1234"))
            self.assertEqual((True, 1), uccs.get_value(identifier + "/true"))

            for item in items_as_str:
                # use string version as key as well
                uccs.remove_value(identifier, item)


        # should fail when set to value of primitive type
        for item in items:
            uccs.set_value("Spec40/item1", item)
            test_fails()

        # When set to list, add and remove should work, and its elements
        # should be considered of type 'any' themselves.
        uccs.set_value("Spec40/item1", [])
        check_list("Spec40/item1")

        # When set to dict, it should have the behaviour of a named set
        uccs.set_value("Spec40/item1", {})
        check_named_set("Spec40/item1")

        # And, or course, we may need nesting.
        uccs.set_value("Spec40/item1", { "foo": {}, "bar": [] })
        check_named_set("Spec40/item1/foo")
        check_list("Spec40/item1/bar")
        uccs.set_value("Spec40/item1", [ {}, [] ] )
        check_named_set("Spec40/item1[0]")
        check_list("Spec40/item1[1]")
        uccs.set_value("Spec40/item1", [[[[[[]]]]]] )
        check_list("Spec40/item1[0][0][0][0][0]")
        uccs.set_value("Spec40/item1", { 'a': { 'a': { 'a': {} } } } )
        check_named_set("Spec40/item1/a/a/a")

    def test_add_dup_value(self):
        fake_conn = fakeUIConn()
        uccs = self.create_uccs_listtest(fake_conn)

        uccs.add_value("Spec39/list")
        self.assertRaises(isc.cc.data.DataAlreadyPresentError, uccs.add_value,
                          "Spec39/list")

    def test_add_remove_value_named_set(self):
        fake_conn = fakeUIConn()
        uccs = self.create_uccs_named_set(fake_conn)
        value, status = uccs.get_value("/Spec32/named_set_item")
        self.assertEqual({'a': 1, 'b': 2}, value)

        # make sure that removing from default actually removes it
        uccs.remove_value("/Spec32/named_set_item", "a")
        value, status = uccs.get_value("/Spec32/named_set_item")
        self.assertEqual({'b': 2}, value)
        self.assertEqual(uccs.LOCAL, status)

        # ok, put it back now
        uccs.add_value("/Spec32/named_set_item", "a")
        uccs.set_value("/Spec32/named_set_item/a", 1)

        uccs.add_value("/Spec32/named_set_item", "foo")
        value, status = uccs.get_value("/Spec32/named_set_item")
        self.assertEqual({'a': 1, 'b': 2, 'foo': 3}, value)

        uccs.remove_value("/Spec32/named_set_item", "a")
        uccs.remove_value("/Spec32/named_set_item", "foo")
        value, status = uccs.get_value("/Spec32/named_set_item")
        self.assertEqual({'b': 2}, value)

        uccs.set_value("/Spec32/named_set_item/c", 5)
        value, status = uccs.get_value("/Spec32/named_set_item")
        self.assertEqual({"b": 2, "c": 5}, value)

        self.assertRaises(isc.cc.data.DataNotFoundError,
                          uccs.set_value,
                          "/Spec32/named_set_item/no_such_item/a",
                          4)
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          uccs.remove_value, "/Spec32/named_set_item",
                          "no_such_item")
        self.assertRaises(isc.cc.data.DataAlreadyPresentError,
                          uccs.add_value, "/Spec32/named_set_item", "c")

    def test_set_value_named_set(self):
        fake_conn = fakeUIConn()
        uccs = self.create_uccs_named_set(fake_conn)
        value, status = uccs.get_value("/Spec32/named_set_item2")
        self.assertEqual({}, value)
        self.assertEqual(status, uccs.DEFAULT)

        # Try setting a value that is optional but has no default
        uccs.add_value("/Spec32/named_set_item2", "new1")
        uccs.set_value("/Spec32/named_set_item2/new1/first", 3)
        # Different method to add a new element
        uccs.set_value("/Spec32/named_set_item2/new2", { "second": 4 })

        value, status = uccs.get_value("/Spec32/named_set_item2")
        self.assertEqual({ "new1": {"first": 3 }, "new2": {"second": 4}},
                         value)
        self.assertEqual(status, uccs.LOCAL)

        uccs.set_value("/Spec32/named_set_item2/new1/second", "foo")

        value, status = uccs.get_value("/Spec32/named_set_item2")
        self.assertEqual({ "new1": {"first": 3, "second": "foo" },
                           "new2": {"second": 4}},
                         value)
        self.assertEqual(status, uccs.LOCAL)

        # make sure using a bad name still fails
        self.assertRaises(isc.cc.data.DataNotFoundError, uccs.set_value,
                          "/Spec32/named_set_item2/doesnotexist/first", 3)



    def test_commit(self):
        fake_conn = fakeUIConn()
        uccs = self.create_uccs(fake_conn)
        uccs.commit()
        uccs._local_changes = {'Spec2': {'item5': [ 'a' ]}}
        uccs.commit()

if __name__ == '__main__':
    isc.log.init("bind10")
    unittest.main()

