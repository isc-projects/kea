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
from unittest_fakesession import FakeModuleCCSession

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
        
    def create_session(self, spec_file_name, config_handler = None, command_handler = None, cc_session = None):
        return ModuleCCSession(self.spec_file(spec_file_name), config_handler, command_handler, cc_session)

    def test_init(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertEqual(isc.config.module_spec_from_file(self.spec_file("spec1.spec"))._module_spec, mccs.specification._module_spec)
        self.assertEqual(None, mccs._config_handler)
        self.assertEqual(None, mccs._command_handler)

    def test_start1(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertEqual(len(fake_session.message_queue), 0)
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

    def test_get_socket(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertNotEqual(None, mccs.get_socket())

    def test_get_session(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        self.assertEqual(fake_session, mccs.get_session())

    def test_close(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)
        mccs.close()
        self.assertEqual("closed", fake_session._socket)

    def test_check_command(self):
        fake_session = FakeModuleCCSession()
        mccs = self.create_session("spec1.spec", None, None, fake_session)

        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 0)

        fake_session.group_sendmsg({'result': [ 0 ]}, "Spec1")
        mccs.check_command()
        self.assertEqual(len(fake_session.message_queue), 0)
        
if __name__ == '__main__':
    unittest.main()

