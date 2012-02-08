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
from isc.config import config_data
from unittest_fakesession import FakeModuleCCSession

class TestConfigManagerData(unittest.TestCase):
    def setUp(self):
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        self.writable_data_path = os.environ['CONFIG_WR_TESTDATA_PATH']
        self.config_manager_data = ConfigManagerData(self.writable_data_path,
                                                     file_name="b10-config.db")
        self.assert_(self.config_manager_data)

    def test_abs_file(self):
        """
        Test what happens if we give the config manager an absolute path.
        It shouldn't append the data path to it.
        """
        abs_path = self.data_path + os.sep + "b10-config-imaginary.db"
        data = ConfigManagerData(self.data_path, abs_path)
        self.assertEqual(abs_path, data.db_filename)
        self.assertEqual(self.data_path, data.data_path)

    def test_init(self):
        self.assertEqual(self.config_manager_data.data['version'],
                         config_data.BIND10_CONFIG_DATA_VERSION)
        self.assertEqual(self.config_manager_data.data_path,
                         self.writable_data_path)
        self.assertEqual(self.config_manager_data.db_filename,
                         self.writable_data_path + os.sep + "b10-config.db")

    def test_read_from_file(self):
        ConfigManagerData.read_from_file(self.writable_data_path, "b10-config.db")
        self.assertRaises(ConfigManagerDataEmpty,
                          ConfigManagerData.read_from_file,
                          "doesnotexist", "b10-config.db")
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
        cfd1 = ConfigManagerData(self.data_path, file_name="b10-config.db")
        cfd2 = ConfigManagerData(self.data_path, file_name="b10-config.db")
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
        self.cm = ConfigManager(self.writable_data_path,
                                database_filename="b10-config.db",
                                session=self.fake_session)
        self.name = "TestModule"
        self.spec = isc.config.module_spec_from_file(self.data_path + os.sep + "/spec2.spec")

    def test_paths(self):
        """
        Test data_path and database filename is passed trough to
        underlying ConfigManagerData.
        """
        cm = ConfigManager("datapath", "filename", self.fake_session)
        self.assertEqual("datapath" + os.sep + "filename",
                         cm.config.db_filename)
        # It should preserve it while reading
        cm.read_config()
        self.assertEqual("datapath" + os.sep + "filename",
                         cm.config.db_filename)

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
        self.assertEqual(msg, {"running": "ConfigManager"})

    def test_set_module_spec(self):
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        self.assert_(module_spec.get_module_name() not in
                     self.cm.virtual_modules)

    def test_remove_module_spec(self):
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        self.cm.remove_module_spec(module_spec.get_module_name())
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.assert_(module_spec.get_module_name() not in
                     self.cm.virtual_modules)

    def test_add_remove_virtual_module(self):
        module_spec = isc.config.module_spec.module_spec_from_file(
            self.data_path + os.sep + "spec1.spec")
        check_func = lambda: True
        # Make sure it's not in there before
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.assert_(module_spec.get_module_name() not in
                     self.cm.virtual_modules)
        # Add it there
        self.cm.set_virtual_module(module_spec, check_func)
        # Check it's in there
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        self.assertEqual(self.cm.module_specs[module_spec.get_module_name()],
                      module_spec)
        self.assertEqual(self.cm.virtual_modules[module_spec.get_module_name()],
                      check_func)
        # Remove it again
        self.cm.remove_module_spec(module_spec.get_module_name())
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.assert_(module_spec.get_module_name() not in
                     self.cm.virtual_modules)

    def test_get_module_spec(self):
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        module_spec2 = self.cm.get_module_spec(module_spec.get_module_name())
        self.assertEqual(module_spec.get_full_spec(), module_spec2)

        self.assertEqual({}, self.cm.get_module_spec("nosuchmodule"))

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

    def test_get_statistics_spec(self):
        statistics_spec = self.cm.get_statistics_spec()
        self.assertEqual(statistics_spec, {})
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        statistics_spec = self.cm.get_statistics_spec()
        self.assertEqual(statistics_spec, { 'Spec1': None })
        self.cm.remove_module_spec('Spec1')
        module_spec = isc.config.module_spec.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.assert_(module_spec.get_module_name() not in self.cm.module_specs)
        self.cm.set_module_spec(module_spec)
        self.assert_(module_spec.get_module_name() in self.cm.module_specs)
        statistics_spec = self.cm.get_statistics_spec()
        self.assertEqual(statistics_spec['Spec2'], module_spec.get_statistics_spec())
        statistics_spec = self.cm.get_statistics_spec('Spec2')
        self.assertEqual(statistics_spec['Spec2'], module_spec.get_statistics_spec())

    def test_read_config(self):
        self.assertEqual(self.cm.config.data, {'version': config_data.BIND10_CONFIG_DATA_VERSION})
        self.cm.data_path = "/no_such_path"
        self.cm.read_config()
        self.assertEqual(self.cm.config.data, {'version': config_data.BIND10_CONFIG_DATA_VERSION})

    def test_write_config(self):
        # tested in ConfigManagerData tests
        pass

    def _handle_msg_helper(self, msg, expected_answer):
        answer = self.cm.handle_msg(msg)
        self.assertEqual(expected_answer, answer)

    def test_handle_msg_basic_commands(self):
        # Some basic commands, where not much interaction happens, just
        # check the result
        self._handle_msg_helper({},
            { 'result': [ 1, 'Unknown message format: {}']})
        self._handle_msg_helper("",
            { 'result': [ 1, 'Unknown message format: ']})
        self._handle_msg_helper({ "command": [ "badcommand" ] },
            { 'result': [ 1, "Unknown command: badcommand"]})
        self._handle_msg_helper({ "command": [ "get_commands_spec" ] },
                                { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_statistics_spec" ] },
                                { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_module_spec" ] },
                                { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_module_spec",
                                               { "module_name": "Spec2" } ] },
                                { 'result': [ 0, {} ]})
        self._handle_msg_helper({ "command": [ "get_module_spec", 1 ] },
                                {'result': [1, 'Bad get_module_spec command, '+
                                               'argument not a dict']})
        self._handle_msg_helper({ "command": [ "get_module_spec", { } ] },
                                {'result': [1, 'Bad module_name in '+
                                               'get_module_spec command']})
        self._handle_msg_helper({ "command": [ "get_config" ] },
                                { 'result': [ 0, { 'version':
                                    config_data.BIND10_CONFIG_DATA_VERSION }]})
        self._handle_msg_helper({ "command": [ "get_config",
                                    { "module_name": "nosuchmodule" } ] },
                                {'result': [0, { 'version':
                                    config_data.BIND10_CONFIG_DATA_VERSION }]})
        self._handle_msg_helper({ "command": [ "get_config", 1 ] },
                                {'result': [1, 'Bad get_config command, '+
                                               'argument not a dict']})
        self._handle_msg_helper({ "command": [ "get_config", { } ] },
                                {'result': [1, 'Bad module_name in '+
                                               'get_config command']})
        self._handle_msg_helper({ "command": [ "set_config" ] },
                                {'result': [1, 'Wrong number of arguments']})
        self._handle_msg_helper({ "command": [ "set_config", [{}]] },
                                {'result': [0]})

        self.assertEqual(len(self.fake_session.message_queue), 0)

    def test_handle_msg_module_and_stats_commands(self):
        self._handle_msg_helper({ "command":
                                  ["module_spec", self.spec.get_full_spec()]
                                },
                                {'result': [0]})
        # There should be a message on the queue about the 'new' Spec2 module
        # from ConfigManager to Cmdctl, containing its name and full
        # specification
        self.assertEqual(ccsession.create_command(
                            ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE,
                            [ self.spec.get_module_name(),
                              self.spec.get_full_spec()]),
                         self.fake_session.get_message("Cmdctl", None))

        self._handle_msg_helper({ "command": [ "module_spec", { 'foo': 1 } ] },
                                {'result': [1, 'Error in data definition: no '+
                                               'module_name in module_spec']})

        self._handle_msg_helper({ "command": [ "get_module_spec" ] },
                                { 'result': [ 0, { self.spec.get_module_name():
                                                 self.spec.get_full_spec() } ]})
        self._handle_msg_helper({ "command": [ "get_module_spec",
                                               { "module_name" : "Spec2" } ] },
                                { 'result': [ 0, self.spec.get_full_spec() ] })
        self._handle_msg_helper({ "command": [ "get_commands_spec" ] },
                                { 'result': [ 0, { self.spec.get_module_name():
                                              self.spec.get_commands_spec()}]})
        self._handle_msg_helper({ "command": [ "get_statistics_spec" ] },
                                { 'result': [ 0, { self.spec.get_module_name():
                                             self.spec.get_statistics_spec()}]})


    def __test_handle_msg_update_config_helper(self, new_config):
        # Helper function for the common pattern in
        # test_handle_msg_update_config; send 'set config', check for
        # update message, check if config has indeed been updated

        my_ok_answer = { 'result': [ 0 ] }
        # Send the 'ok' that cfgmgr expects back to the fake queue first
        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")

        self._handle_msg_helper({ "command": [ "set_config",
                                               [self.name, new_config] ] },
                                my_ok_answer)

        # The cfgmgr should have eaten the ok message, and sent out an update
        # message
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'config_update', new_config]},
                         self.fake_session.get_message(self.name, None))

        # Config should have been updated
        self.assertEqual(self.cm.config.data, {self.name: new_config,
                            'version': config_data.BIND10_CONFIG_DATA_VERSION})

        # and the queue should now be empty again
        self.assertEqual(len(self.fake_session.message_queue), 0)

    def test_handle_msg_update_config(self):
        # Update the configuration and check results a few times
        # only work the first time
        self.__test_handle_msg_update_config_helper({ "test": 123 })

        self.__test_handle_msg_update_config_helper({ "test": 124 })

        self.__test_handle_msg_update_config_helper({ "test": 125 })

        self.__test_handle_msg_update_config_helper({ "test": 126 })

        # Now send an error result (i.e. config not accepted)
        my_bad_answer = { 'result': [1, "bad config"] }
        self.fake_session.group_sendmsg(my_bad_answer, "ConfigManager")
        self._handle_msg_helper({ "command": [ "set_config",
                                               [self.name, { "test": 127 }] ] },
                                my_bad_answer )
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'config_update', {'test': 127}]},
                         self.fake_session.get_message(self.name, None))
        # Config should not be updated due to the error
        self.cm.read_config()
        self.assertEqual(self.cm.config.data, { self.name: {'test': 126},
                            'version': config_data.BIND10_CONFIG_DATA_VERSION})

        self.assertEqual(len(self.fake_session.message_queue), 0)

        self.fake_session.group_sendmsg(None, 'ConfigManager')
        self._handle_msg_helper({ "command": [ "set_config", [ ] ] },
                                {'result': [1, 'Wrong number of arguments']} )
        self._handle_msg_helper({ "command": [ "set_config",
                                               [ self.name, { "test": 128 }]]},
                                { 'result': [1, 'No answer message '+
                                                'from TestModule']} )

        # This command should leave a message to the TestModule to update its
        # configuration (since the TestModule did not eat it)
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual(
            ccsession.create_command(ccsession.COMMAND_CONFIG_UPDATE,
                                     { "test": 128 }),
            self.fake_session.get_message("TestModule", None))

        # Make sure queue is empty now
        self.assertEqual(len(self.fake_session.message_queue), 0)

        # Shutdown should result in 'ok' answer
        self._handle_msg_helper({ "command":
                                  ["shutdown"]
                                },
                                {'result': [0]})

    def test_stopping_message(self):
        # Update the system by announcing this module
        self._handle_msg_helper({ "command":
                                  ["module_spec", self.spec.get_full_spec()]
                                },
                                {'result': [0]})

        # This causes a update to be sent from the ConfigManager to the CmdCtl
        # channel, containing the new module's name and full specification
        self.assertEqual(ccsession.create_command(
                            ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE,
                            [ self.spec.get_module_name(),
                              self.spec.get_full_spec()]),
                         self.fake_session.get_message("Cmdctl", None))

        # A stopping message should get no response, but should cause another
        # message to be sent, if it is a known module
        self._handle_msg_helper({ "command": [ "stopping",
                                               { "module_name": "Spec2"}] },
                                None)
        self.assertEqual(len(self.fake_session.message_queue), 1)
        self.assertEqual({'command': [ 'module_specification_update',
                                       ['Spec2', None] ] },
                         self.fake_session.get_message("Cmdctl", None))

        # but if the 'stopping' module is either unknown or not running,
        # no followup message should be sent
        self._handle_msg_helper({ "command":
                                  [ "stopping",
                                    { "module_name": "NoSuchModule" } ] },
                                None)
        self.assertEqual(len(self.fake_session.message_queue), 0)

        # If the module does not exist, or is not seen as 'running', the
        # same message should not cause new messages to be sent
        self._handle_msg_helper({ "command": [ "stopping",
                                               { "module_name": "Foo"}] },
                                None)
        self.assertEqual(len(self.fake_session.message_queue), 0)

    def test_set_config_virtual(self):
        """Test that if the module is virtual, we don't send it over the
           message bus, but call the checking function.
           """
        # We run the same three times, with different return values
        def single_test(value, returnFunc, expectedResult):
            # Because closures can't assign to closed-in variables, we pass
            # it trough self
            self.called_with = None
            def check_test(new_data):
                self.called_with = new_data
                return returnFunc()

            # Register our virtual module
            self.cm.set_virtual_module(self.spec, check_test)
            # The fake session will throw now if it tries to read a response.
            # Handy, we don't need to find a complicated way to check for it.
            result = self.cm._handle_set_config_module(self.spec.
                                                       get_module_name(),
                                                       {'item1': value})
            # Check the correct result is passed and our function was called
            # With correct data
            self.assertEqual(self.called_with['item1'], value)
            self.assertEqual(result, {'result': expectedResult})
            if expectedResult[0] == 0:
                # Check it provided the correct notification
                self.assertEqual(len(self.fake_session.message_queue), 1)
                self.assertEqual({'command': [ 'config_update',
                                 {'item1': value}]},
                                 self.fake_session.get_message('Spec2', None))
                # and the queue should now be empty again
                self.assertEqual(len(self.fake_session.message_queue), 0)
            else:
                # It shouldn't send anything on error
                self.assertEqual(len(self.fake_session.message_queue), 0)

        # Success
        single_test(5, lambda: None, [0])
        # Graceful error
        single_test(6, lambda: "Just error", [1, "Just error"])
        # Exception from the checker
        def raiser():
            raise Exception("Just exception")
        single_test(7, raiser, [1, "Exception: Just exception"])

    def test_set_config_all(self):
        my_ok_answer = { 'result': [ 0 ] }

        self.assertEqual({"version": 2}, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value1": 123 }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value1": 123 }
                         }, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value1": 124 }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value1": 124 }
                         }, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value2": True }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value1": 124,
                                    "value2": True
                                  }
                         }, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value3": [ 1, 2, 3 ] }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value1": 124,
                                    "value2": True,
                                    "value3": [ 1, 2, 3 ]
                                  }
                         }, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value2": False }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value1": 124,
                                    "value2": False,
                                    "value3": [ 1, 2, 3 ]
                                  }
                         }, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value1": None }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value2": False,
                                    "value3": [ 1, 2, 3 ]
                                  }
                         }, self.cm.config.data)

        self.fake_session.group_sendmsg(my_ok_answer, "ConfigManager")
        self.cm._handle_set_config_all({"test": { "value3": [ 1 ] }})
        self.assertEqual({"version": config_data.BIND10_CONFIG_DATA_VERSION,
                          "test": { "value2": False,
                                    "value3": [ 1 ]
                                  }
                         }, self.cm.config.data)


    def test_run(self):
        self.fake_session.group_sendmsg({ "command": [ "get_commands_spec" ] }, "ConfigManager")
        self.fake_session.group_sendmsg({ "command": [ "get_statistics_spec" ] }, "ConfigManager")
        self.fake_session.group_sendmsg({ "command": [ "stopping", { "module_name": "FooModule" } ] }, "ConfigManager")
        self.fake_session.group_sendmsg({ "command": [ "shutdown" ] }, "ConfigManager")
        self.assertEqual(len(self.fake_session.message_queue), 4)
        self.cm.run()
        # All commands should have been read out by run()
        # Three of the commands should have been responded to, so the queue
        # should now contain three answers
        self.assertEqual(len(self.fake_session.message_queue), 3)


if __name__ == '__main__':
    if not 'CONFIG_TESTDATA_PATH' in os.environ or not 'CONFIG_WR_TESTDATA_PATH' in os.environ:
        print("You need to set the environment variable CONFIG_TESTDATA_PATH and CONFIG_WR_TESTDATA_PATH to point to the directory containing the test data files")
        exit(1)
    unittest.main()

