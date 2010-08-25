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

# $Id$

#
# Tests for the configuration manager module
#

import unittest
import os
from isc.config.cfgmgr import *
from isc.config import config_data
from unittest_fakesession import FakeModuleCCSession

class TestConfigManagerData(unittest.TestCase):
    def setUp(self):
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        self.writable_data_path = os.environ['CONFIG_WR_TESTDATA_PATH']
        self.config_manager_data = ConfigManagerData(self.writable_data_path)
        self.assert_(self.config_manager_data)

    def test_init(self):
        self.assertEqual(self.config_manager_data.data['version'],
                         config_data.BIND10_CONFIG_DATA_VERSION)
        self.assertEqual(self.config_manager_data.data_path,
                         self.writable_data_path)
        self.assertEqual(self.config_manager_data.db_filename,
                         self.writable_data_path + os.sep + "b10-config.db")

    def test_read_from_file(self):
        ConfigManagerData.read_from_file(self.writable_data_path)
        self.assertRaises(ConfigManagerDataEmpty,
                          ConfigManagerData.read_from_file,
                          "doesnotexist")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad1.db")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad2.db")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad3.db")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad4.db")

    def test_write_to_file(self):
        output_file_name = "b10-config-write-test"
        self.config_manager_data.write_to_file(output_file_name)
        new_config = ConfigManagerData(self.data_path, output_file_name)
        self.assertEqual(self.config_manager_data, new_config)
        os.remove(output_file_name)

    def test_equality(self):
        # tests the __eq__ function. Equality is only defined
        # by equality of the .data element. If data_path or db_filename
        # are different, but the contents are the same, it's still
        # considered equal
        cfd1 = ConfigManagerData(self.data_path)
        cfd2 = ConfigManagerData(self.data_path)
        self.assertEqual(cfd1, cfd2)
        cfd2.data_path = "some/unknown/path"
        self.assertEqual(cfd1, cfd2)
        cfd2.db_filename = "bad_file.name"
        self.assertEqual(cfd1, cfd2)
        cfd2.data['test'] = { 'a': [ 1, 2, 3]}
        self.assertNotEqual(cfd1, cfd2)
        

class TestConfigManager(unittest.TestCase):

    def setUp(self):
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        self.writable_data_path = os.environ['CONFIG_WR_TESTDATA_PATH']
        self.fake_session = FakeModuleCCSession()
        self.cm = ConfigManager(self.writable_data_path, self.fake_session)
        self.name = "TestModule"
        self.spec = isc.config.module_spec_from_file(self.data_path + os.sep + "/spec2.spec")
    
    def test_init(self):
        self.assert_(self.cm.module_specs == {})
        self.assert_(self.cm.data_path == self.writable_data_path)
        self.assert_(self.cm.config != None)
        self.assert_(self.fake_session.has_subscription("ConfigManager"))
        self.assert_(self.fake_session.has_subscription("Boss", "ConfigManager"))
        self.assertFalse(self.cm.running)

    def test_notify_boss(self):
        self.cm.notify_boss()
        msg = self.fake_session.get_message("Boss", None)
        self.assert_(msg)
        # this one is actually wrong, but 'current status quo'
        self.assertEqual(msg, {"running": "configmanager"})

    def test_set_module_spec(self):
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)

    def test_remove_module_spec(self):
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        self.cm.remove_module_spec(module_spec.get_module_name())
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)

    def test_get_module_spec(self):
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        module_spec2 = self.cm.get_module_spec(module_spec.get_module_name())
        self.assertEqual(module_spec, module_spec2)

    def test_get_config_spec(self):
        config_spec = self.cm.get_config_spec()
        self.assertEqual(config_spec, {})
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        config_spec = self.cm.get_config_spec()
        self.assertEqual(config_spec, { 'Spec1': None })
        self.cm.remove_module_spec('Spec1')
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        config_spec = self.cm.get_config_spec()
        self.assertEqual(config_spec['Spec2'], module_spec.get_config_spec())
        config_spec = self.cm.get_config_spec('Spec2')
        self.assertEqual(config_spec['Spec2'], module_spec.get_config_spec())
        
    
    def test_get_commands_spec(self):
        commands_spec = self.cm.get_commands_spec()
        self.assertEqual(commands_spec, {})
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        commands_spec = self.cm.get_commands_spec()
        self.assertEqual(commands_spec, { 'Spec1': None })
        self.cm.remove_module_spec('Spec1')
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        commands_spec = self.cm.get_commands_spec()
        self.assertEqual(commands_spec['Spec2'], module_spec.get_commands_spec())
        commands_spec = self.cm.get_commands_spec('Spec2')
        self.assertEqual(commands_spec['Spec2'], module_spec.get_commands_spec())

    def test_read_config(self):
        self.assertEqual(self.cm.config.data, {'version': config_data.BIND10_CONFIG_DATA_VERSION})
        self.cm.read_config()
        # due to what get written, the value here is what the last set_config command in test_handle_msg does
        self.assertEqual(self.cm.config.data, {'TestModule': {'test': 125}, 'version': config_data.BIND10_CONFIG_DATA_VERSION})
        self.cm.data_path = "/no_such_path"
        self.cm.read_config()
        self.assertEqual(self.cm.config.data, {'version': config_data.BIND10_CONFIG_DATA_VERSION})

    def test_write_config(self):
        # tested in ConfigManagerData tests
        pass
    
    def _handle_msg_helper(self, msg, expected_answer):
        answer = self.cm.handle_msg(msg)
        self.assertEqual(expected_answer, answer)

    def test_handle_msg(self):
        self._handle_msg_helper({}, { 'result': [ 1, 'Unknown message format: {}']})
        self._handle_msg_helper("", { 'result': [ 1, 'Unknown message format: ']})
        self._handle_msg_helper({ "command": [ "badcommand" ] }, { 'result': [ 1, "Unknown command: badcommand"]})
        self._handle_msg_helper({ "command": [ "get_commands_spec" ] }, { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_module_spec" ] }, { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_module_spec", { "module_name": "Spec2" } ] }, { 'result': [ 0, {} ]})
        #self._handle_msg_helper({ "command": [ "get_module_spec", { "module_name": "nosuchmodule" } ] },
        #                        {'result': [1, 'No specification for module nosuchmodule']})
        self._handle_msg_helper({ "command": [ "get_module_spec", 1 ] },
                                {'result': [1, 'Bad get_module_spec command, argument not a dict']})
        self._handle_msg_helper({ "command": [ "get_module_spec", { } ] },
                                {'result': [1, 'Bad module_name in get_module_spec command']})
        self._handle_msg_helper({ "command": [ "get_config" ] }, { 'result': [ 0, { 'version': config_data.BIND10_CONFIG_DATA_VERSION } ]})
        self._handle_msg_helper({ "command": [ "get_config", { "module_name": "nosuchmodule" } ] },
                                {'result': [0, { 'version': config_data.BIND10_CONFIG_DATA_VERSION }]})
        self._handle_msg_helper({ "command": [ "get_config", 1 ] },
                                {'result': [1, 'Bad get_config command, argument not a dict']})
        self._handle_msg_helper({ "command": [ "get_config", { } ] },
                                {'result': [1, 'Bad module_name in get_config command']})
        self._handle_msg_helper({ "command": [ "set_config" ] },
                                {'result': [1, 'Wrong number of arguments']})
        self._handle_msg_helper({ "command": [ "set_config", [{}]] },
                                {'result': [0]})
        self.assertEqual(len(self.fake_session.message_queue), 0)

        # the targets of some of these tests expect specific answers, put
        # those in our fake msgq first.
        my_ok_answer = { 'result': [ 0 ] }


        # Send the 'ok' that cfgmgr expects back to the fake queue first
        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        # then send the command
        self._handle_msg_helper({ "command": [ "set_config", [self.name, { "test": 123 }] ] },
                                my_ok_answer)
        # The cfgmgr should have eaten the ok message, and sent out an update again
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'config_update', {'test': 123}]},
                         self.fake_session.get_message(self.name, None))
        # and the queue should now be empty again
        self.assertEqual(len(self.fake_session.message_queue), 0)

        # below are variations of the theme above
        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self._handle_msg_helper({ "command": [ "set_config", [self.name, { "test": 124 }] ] },
                                my_ok_answer)
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'config_update', {'test': 124}]},
                         self.fake_session.get_message(self.name, None))
        self.assertEqual(len(self.fake_session.message_queue), 0)


        # This is the last 'succes' one, the value set here is what test_read_config expects
        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self._handle_msg_helper({ "command": [ "set_config", [ { self.name: { "test": 125 } }] ] },
                                my_ok_answer )
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'config_update', {'test': 125}]},
                         self.fake_session.get_message(self.name, None))
        self.assertEqual(len(self.fake_session.message_queue), 0)

        my_bad_answer = { 'result': [1, "bad_answer"] }
        self.fake_session.group_sendmsg(my_bad_answer, "ConfigManager")
        self._handle_msg_helper({ "command": [ "set_config", [ self.name, { "test": 125 }] ] },
                                my_bad_answer )
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'config_update', {'test': 125}]},
                         self.fake_session.get_message(self.name, None))
        self.assertEqual(len(self.fake_session.message_queue), 0)

        self._handle_msg_helper({ "command": [ "set_config", [ ] ] },
                                {'result': [1, 'Wrong number of arguments']} )
        self._handle_msg_helper({ "command": [ "set_config", [ self.name, { "test": 125 }] ] },
                                { 'result': [1, 'No answer message from TestModule']} )

        #self.assertEqual(len(self.fake_session.message_queue), 1)
        #self.assertEqual({'config_update': {'test': 124}},
        #                 self.fake_session.get_message(self.name, None))
        #self.assertEqual({'version': 1, 'TestModule': {'test': 124}}, self.cm.config.data)
        #
        self._handle_msg_helper({ "command": 
                                  ["module_spec", self.spec.get_full_spec()]
                                },
                                {'result': [0]})
        self._handle_msg_helper({ "command": [ "module_spec", { 'foo': 1 } ] },
                                {'result': [1, 'Error in data definition: no module_name in module_spec']})
        self._handle_msg_helper({ "command": [ "get_module_spec" ] }, { 'result': [ 0, { self.spec.get_module_name(): self.spec.get_full_spec() } ]})
        self._handle_msg_helper({ "command": [ "get_commands_spec" ] }, { 'result': [ 0, { self.spec.get_module_name(): self.spec.get_commands_spec() } ]})
        # re-add this once we have new way to propagate spec changes (1 instead of the current 2 messages)
        #self.assertEqual(len(self.fake_session.message_queue), 2)
        # the name here is actually wrong (and hardcoded), but needed in the current version
        # TODO: fix that
        #self.assertEqual({'specification_update': [ self.name, self.spec ] },
        #                 self.fake_session.get_message("Cmdctl", None))
        #self.assertEqual({'commands_update': [ self.name, self.commands ] },
        #                 self.fake_session.get_message("Cmdctl", None))

        self._handle_msg_helper({ "command": 
                                  ["shutdown"]
                                },
                                {'result': [0]})

    def test_run(self):
        self.fake_session.group_sendmsg({ "command": [ "get_commands_spec" ] }, "ConfigManager")
        self.fake_session.group_sendmsg({ "command": [ "shutdown" ] }, "ConfigManager")
        self.cm.run()
        pass


if __name__ == '__main__':
    if not 'CONFIG_TESTDATA_PATH' in os.environ or not 'CONFIG_WR_TESTDATA_PATH' in os.environ:
        print("You need to set the environment variable CONFIG_TESTDATA_PATH and CONFIG_WR_TESTDATA_PATH to point to the directory containing the test data files")
        exit(1)
    unittest.main()

