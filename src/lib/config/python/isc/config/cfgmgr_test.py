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
# Tests for the configuration manager module
#

import unittest
import os
from isc.config.cfgmgr import *

class TestConfigManagerData(unittest.TestCase):
    def setUp(self):
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        self.config_manager_data = ConfigManagerData(self.data_path)
        self.assert_(self.config_manager_data)

    def test_init(self):
        self.assertEqual(self.config_manager_data.data['version'],
                         ConfigManagerData.CONFIG_VERSION)
        self.assertEqual(self.config_manager_data.data_path,
                         self.data_path)
        self.assertEqual(self.config_manager_data.db_filename,
                         self.data_path + os.sep + "b10-config.db")

    def test_set_data_definition(self):
        pass

    def test_read_from_file(self):
        ConfigManagerData.read_from_file(self.data_path)
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

    def test_write_to_file(self):
        output_file_name = "b10-config-write-test";
        self.config_manager_data.write_to_file(output_file_name)
        new_config = ConfigManagerData(self.data_path, output_file_name)
        self.assertEqual(self.config_manager_data, new_config)

#
# We can probably use a more general version of this
#
class FakeCCSession:
    def __init__(self):
        self.subscriptions = {}
        # each entry is of the form [ channel, instance, message ]
        self.message_queue = []

    def group_subscribe(self, group_name, instance_name = None):
        if not group_name in self.subscriptions:
            self.subscriptions[group_name] = []
        if instance_name:
            self.subscriptions[group_name].append(instance_name)
            

    def has_subscription(self, group_name, instance_name = None):
        if group_name in self.subscriptions:
            if instance_name:
                return instance_name in self.subscriptions[group_name]
            else:
                return True
        else:
            return False

    def group_sendmsg(self, msg, channel, target = None):
        self.message_queue.append([ channel, target, msg ])

    def get_message(self, channel, target = None):
        for qm in self.message_queue:
            if qm[0] == channel and qm[1] == target:
                self.message_queue.remove(qm)
                return qm[2]
        return None
        

class TestConfigManager(unittest.TestCase):

    def setUp(self):
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        self.fake_session = FakeCCSession()
        self.cm = ConfigManager(self.data_path, self.fake_session)
        self.name = "TestModule"
        self.spec = isc.config.data_spec_from_file(self.data_path + os.sep + "/spec2.spec")
    
    def test_init(self):
        self.assert_(self.cm.data_specs == {})
        self.assert_(self.cm.data_path == self.data_path)
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

    def _handle_msg_helper(self, msg, expected_answer):
        answer = self.cm.handle_msg(msg)
        self.assertEqual(expected_answer, answer)

    def test_handle_msg(self):
        self._handle_msg_helper({}, { 'result': [ 1, 'Unknown message format: {}']})
        self._handle_msg_helper("", { 'result': [ 1, 'Unknown message format: ']})
        self._handle_msg_helper({ "command": [ "badcommand" ] }, { 'result': [ 1, "Unknown command: ['badcommand']"]})
        self._handle_msg_helper({ "command": [ "get_commands" ] }, { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_data_spec" ] }, { 'result': [ 0, {} ]})
        #self._handle_msg_helper({ "command": [ "get_data_spec", { "module_name": "nosuchmodule" } ] },
        #                        {'result': [1, 'No specification for module nosuchmodule']})
        self._handle_msg_helper({ "command": [ "get_data_spec", 1 ] },
                                {'result': [1, 'Bad get_data_spec command, argument not a dict']})
        self._handle_msg_helper({ "command": [ "get_data_spec", { } ] },
                                {'result': [1, 'Bad module_name in get_data_spec command']})
        self._handle_msg_helper({ "command": [ "get_config" ] }, { 'result': [ 0, { 'version': 1} ]})
        self._handle_msg_helper({ "command": [ "get_config", { "module_name": "nosuchmodule" } ] },
                                {'result': [0, {}]})
        self._handle_msg_helper({ "command": [ "get_config", 1 ] },
                                {'result': [1, 'Bad get_config command, argument not a dict']})
        self._handle_msg_helper({ "command": [ "get_config", { } ] },
                                {'result': [1, 'Bad module_name in get_config command']})
        self._handle_msg_helper({ "command": [ "set_config" ] },
                                {'result': [1, 'Wrong number of arguments']})
        self._handle_msg_helper({ "command": [ "set_config", {} ] },
                                {'result': [0]})
        self.assertEqual(len(self.fake_session.message_queue), 0)
        self._handle_msg_helper({ "command": [ "set_config", self.name, { "test": 123 } ] },
                                {'result': [0]})
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'config_update': {'test': 123}},
                         self.fake_session.get_message(self.name, None))
        self._handle_msg_helper({ "command": [ "set_config", self.name, { "test": 124 } ] },
                                {'result': [0]})
        #print(self.fake_session.message_queue)
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'config_update': {'test': 124}},
                         self.fake_session.get_message(self.name, None))
        self.assertEqual({'version': 1, 'TestModule': {'test': 124}}, self.cm.config.data)
        self._handle_msg_helper({ "data_specification": 
                                  self.spec.get_definition()
                                },
                                {'result': [0]})
        self._handle_msg_helper({ "data_specification": 
                                  { 'foo': 1 }
                                },
                                {'result': [1, 'Error in data definition: no module_name in data_specification']})
        self._handle_msg_helper({ "command": [ "get_data_spec" ] }, { 'result': [ 0, { self.spec.get_module_name(): self.spec.get_config_spec() } ]})
        self._handle_msg_helper({ "command": [ "get_commands" ] }, { 'result': [ 0, { self.spec.get_module_name(): self.spec.get_commands() } ]})
        # re-add this once we have new way to propagate spec changes (1 instead of the current 2 messages)
        #self.assertEqual(len(self.fake_session.message_queue), 2)
        # the name here is actually wrong (and hardcoded), but needed in the current version
        # TODO: fix that
        #self.assertEqual({'specification_update': [ self.name, self.spec ] },
        #                 self.fake_session.get_message("Cmd-Ctrld", None))
        #self.assertEqual({'commands_update': [ self.name, self.commands ] },
        #                 self.fake_session.get_message("Cmd-Ctrld", None))
        
        

    def test_run(self):
        pass


if __name__ == '__main__':
    if not 'CONFIG_TESTDATA_PATH' in os.environ:
        print("You need to set the environment variable CONFIG_TESTDATA_PATH to point to the directory containing the test data files")
        exit(1)
    unittest.main()

