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
__version__ = "$Revision$"

#
# Tests for the stats module
#
import os
import sys
import time
import unittest
import imp
from isc.cc.session import Session, SessionError
from isc.config.ccsession import ModuleCCSession, ModuleCCSessionError
import stats
from stats import SessionSubject, CCSessionListener, get_timestamp, get_datetime
from fake_time import _TEST_TIME_SECS, _TEST_TIME_STRF

# setting Constant
if sys.path[0] == '':
    TEST_SPECFILE_LOCATION = "./testdata/stats_test.spec"
else:
    TEST_SPECFILE_LOCATION = sys.path[0] + "/testdata/stats_test.spec"

class TestStats(unittest.TestCase):

    def setUp(self):
        self.session = Session()
        self.subject = SessionSubject(session=self.session, verbose=True)
        self.listener = CCSessionListener(self.subject, verbose=True)
        self.stats_spec = self.listener.cc_session.get_module_spec().get_config_spec()
        self.module_name = self.listener.cc_session.get_module_spec().get_module_name()
        self.stats_data = {
                'report_time' : get_datetime(),
                'bind10.boot_time' : "1970-01-01T00:00:00Z",
                'stats.timestamp' : get_timestamp(),
                'stats.lname' : self.session.lname,
                'auth.queries.tcp': 0,
                'auth.queries.udp': 0,
                "stats.boot_time": get_datetime(),
                "stats.start_time": get_datetime(),
                "stats.last_update_time": get_datetime()
                }
        # check starting
        self.assertFalse(self.subject.running)
        self.subject.start()
        self.assertTrue(self.subject.running)
        self.assertEqual(len(self.session.message_queue), 0)
        self.assertEqual(self.module_name, 'Stats')

    def tearDown(self):
        # check closing
        self.subject.stop()
        self.assertFalse(self.subject.running)
        self.subject.detach(self.listener)
        self.listener.stop()
        self.session.close()

    def test_local_func(self):
        """
        Test for local function
        
        """
        # test for result_ok
        self.assertEqual(type(result_ok()), dict)
        self.assertEqual(result_ok(), {'result': [0]})
        self.assertEqual(result_ok(1), {'result': [1]})
        self.assertEqual(result_ok(0,'OK'), {'result': [0, 'OK']})
        self.assertEqual(result_ok(1,'Not good'), {'result': [1, 'Not good']})
        self.assertEqual(result_ok(None,"It's None"), {'result': [None, "It's None"]})
        self.assertNotEqual(result_ok(), {'RESULT': [0]})

        # test for get_timestamp
        self.assertEqual(get_timestamp(), _TEST_TIME_SECS)

        # test for get_datetime
        self.assertEqual(get_datetime(), _TEST_TIME_STRF)

    def test_show_command(self):
        """
        Test for show command
        
        """
        # test show command without arg
        self.session.group_sendmsg({"command": [ "show", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        # ignore under 0.9 seconds
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test show command with arg
        self.session.group_sendmsg({"command": [ "show", {"stats_item_name": "stats.lname"}]}, "Stats")
        self.assertEqual(len(self.subject.session.message_queue), 1)
        self.subject.check()
        result_data = self.subject.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'stats.lname': self.stats_data['stats.lname']}),
                         result_data)
        self.assertEqual(len(self.subject.session.message_queue), 0)

        # test show command with arg which has wrong name
        self.session.group_sendmsg({"command": [ "show", {"stats_item_name": "stats.dummy"}]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        # ignore under 0.9 seconds
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_set_command(self):
        """
        Test for set command
        
        """
        # test set command
        self.stats_data['auth.queries.udp'] = 54321
        self.assertEqual(self.stats_data['auth.queries.udp'], 54321)
        self.assertEqual(self.stats_data['auth.queries.tcp'], 0)
        self.session.group_sendmsg({ "command": [
                                      "set", {
                                          'stats_data': {'auth.queries.udp': 54321 }
                                      } ] },
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # test show command
        self.session.group_sendmsg({"command": [ "show", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set command 2
        self.stats_data['auth.queries.udp'] = 0
        self.assertEqual(self.stats_data['auth.queries.udp'], 0)
        self.assertEqual(self.stats_data['auth.queries.tcp'], 0)
        self.session.group_sendmsg({ "command": [ "set", {'stats_data': {'auth.queries.udp': 0}} ]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # test show command 2
        self.session.group_sendmsg({"command": [ "show", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set command 3
        self.stats_data['auth.queries.tcp'] = 54322
        self.assertEqual(self.stats_data['auth.queries.udp'], 0)
        self.assertEqual(self.stats_data['auth.queries.tcp'], 54322)
        self.session.group_sendmsg({ "command": [
                                      "set", {
                                          'stats_data': {'auth.queries.tcp': 54322 }
                                      } ] },
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # test show command 3
        self.session.group_sendmsg({"command": [ "show", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_remove_command(self):
        """
        Test for remove command
        
        """
        self.session.group_sendmsg({"command":
                                   [ "remove", {"stats_item_name": 'bind10.boot_time' }]},
                              "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)
        self.assertEqual(self.stats_data.pop('bind10.boot_time'), "1970-01-01T00:00:00Z")
        self.assertFalse('bind10.boot_time' in self.stats_data)

        # test show command with arg
        self.session.group_sendmsg({"command":
                                    [ "show", {"stats_item_name": 'bind10.boot_time'}]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertFalse('bind10.boot_time' in result_data['result'][1])
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_reset_command(self):
        """
        Test for reset command
        
        """
        self.session.group_sendmsg({"command": [ "reset" ] }, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # test show command
        self.session.group_sendmsg({"command": [ "show" ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_status_command(self):
        """
        Test for status command
        
        """
        self.session.group_sendmsg({"command": [ "status" ] }, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(0, "I'm alive."),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

    def test_unknown_command(self):
        """
        Test for unknown command
        
        """
        self.session.group_sendmsg({"command": [ "hoge", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(1, "Unknown command: 'hoge'"),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

    def test_shutdown_command(self):
        """
        Test for shutdown command
        
        """
        self.session.group_sendmsg({"command": [ "shutdown", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.assertTrue(self.subject.running)
        self.subject.check()
        self.assertFalse(self.subject.running)
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)


    def test_some_commands(self):
        """
        Test for some commands in a row
        
        """
        # test set command
        self.stats_data['bind10.boot_time'] = '2010-08-02T14:47:56Z'
        self.assertEqual(self.stats_data['bind10.boot_time'], '2010-08-02T14:47:56Z')
        self.session.group_sendmsg({ "command": [
                                      "set", {
                                          'stats_data': {'bind10.boot_time': '2010-08-02T14:47:56Z' }
                                      }]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check its value
        self.session.group_sendmsg({ "command": [
                                      "show", { 'stats_item_name': 'bind10.boot_time' }
                                     ] }, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'bind10.boot_time': '2010-08-02T14:47:56Z'}),
                         result_data)
        self.assertEqual(result_ok(0, {'bind10.boot_time': self.stats_data['bind10.boot_time']}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set command 2nd
        self.stats_data['auth.queries.udp'] = 98765
        self.assertEqual(self.stats_data['auth.queries.udp'], 98765)
        self.session.group_sendmsg({ "command": [
                                      "set", { 'stats_data': {
                                            'auth.queries.udp':
                                              self.stats_data['auth.queries.udp']
                                            } } 
                                     ] }, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check its value
        self.session.group_sendmsg({"command": [
				      "show", {'stats_item_name': 'auth.queries.udp'}
                                    ] }, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'auth.queries.udp': 98765}),
                         result_data)
        self.assertEqual(result_ok(0, {'auth.queries.udp': self.stats_data['auth.queries.udp']}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set command 3
        self.stats_data['auth.queries.tcp'] = 4321
        self.session.group_sendmsg({"command": [
                                      "set",
                                      {'stats_data': {'auth.queries.tcp': 4321 }} ]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check value
        self.session.group_sendmsg({"command": [ "show", {'stats_item_name': 'auth.queries.tcp'} ]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'auth.queries.tcp': 4321}),
                         result_data)
        self.assertEqual(result_ok(0, {'auth.queries.tcp': self.stats_data['auth.queries.tcp']}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        self.session.group_sendmsg({"command": [ "show", {'stats_item_name': 'auth.queries.udp'} ]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'auth.queries.udp': 98765}),
                         result_data)
        self.assertEqual(result_ok(0, {'auth.queries.udp': self.stats_data['auth.queries.udp']}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set command 4
        self.stats_data['auth.queries.tcp'] = 67890
        self.session.group_sendmsg({"command": [
                                      "set", {'stats_data': {'auth.queries.tcp': 67890 }} ]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # test show command for all values
        self.session.group_sendmsg({"command": [ "show", None ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, self.stats_data), result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_some_commands2(self):
        """
        Test for some commands in a row using list-type value
        
        """
        self.stats_data['listtype'] = [1, 2, 3]
        self.assertEqual(self.stats_data['listtype'], [1, 2, 3])
        self.session.group_sendmsg({ "command": [
                                      "set", {'stats_data': {'listtype': [1, 2, 3] }}
                                      ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check its value
        self.session.group_sendmsg({ "command": [
                                      "show", { 'stats_item_name': 'listtype'}
                                     ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'listtype': [1, 2, 3]}),
                         result_data)
        self.assertEqual(result_ok(0, {'listtype': self.stats_data['listtype']}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set list-type value
        self.assertEqual(self.stats_data['listtype'], [1, 2, 3])
        self.session.group_sendmsg({"command": [
                                      "set", {'stats_data': {'listtype': [3, 2, 1, 0] }}
                                    ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check its value
        self.session.group_sendmsg({ "command": [
                                      "show", { 'stats_item_name': 'listtype' }
                                     ] }, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'listtype': [3, 2, 1, 0]}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_some_commands3(self):
        """
        Test for some commands in a row using dictionary-type value
        
        """
        self.stats_data['dicttype'] = {"a": 1, "b": 2, "c": 3}
        self.assertEqual(self.stats_data['dicttype'], {"a": 1, "b": 2, "c": 3})
        self.session.group_sendmsg({ "command": [
                                      "set", {
                                          'stats_data': {'dicttype': {"a": 1, "b": 2, "c": 3} }
                                      }]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check its value
        self.session.group_sendmsg({ "command": [ "show", { 'stats_item_name': 'dicttype' } ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'dicttype': {"a": 1, "b": 2, "c": 3}}),
                         result_data)
        self.assertEqual(result_ok(0, {'dicttype': self.stats_data['dicttype']}),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

        # test set list-type value
        self.assertEqual(self.stats_data['dicttype'], {"a": 1, "b": 2, "c": 3})
        self.session.group_sendmsg({"command": [
                                      "set", {'stats_data': {'dicttype': {"a": 3, "b": 2, "c": 1, "d": 0} }} ]},
                                   "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))
        self.assertEqual(len(self.session.message_queue), 0)

        # check its value
        self.session.group_sendmsg({ "command": [ "show", { 'stats_item_name': 'dicttype' }]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        result_data = self.session.get_message("Stats", None)
        self.assertEqual(result_ok(0, {'dicttype': {"a": 3, "b": 2, "c": 1, "d": 0} }),
                         result_data)
        self.assertEqual(len(self.session.message_queue), 0)

    def test_config_update(self):
        """
        Test for config update
        
        """
        # test show command without arg
        self.session.group_sendmsg({"command": [ "config_update", {"x-version":999} ]}, "Stats")
        self.assertEqual(len(self.session.message_queue), 1)
        self.subject.check()
        self.assertEqual(result_ok(),
                         self.session.get_message("Stats", None))

class TestStats2(unittest.TestCase):

    def setUp(self):
        self.session = Session(verbose=True)
        self.subject = SessionSubject(session=self.session, verbose=True)
        self.listener = CCSessionListener(self.subject, verbose=True)
        self.module_name = self.listener.cc_session.get_module_spec().get_module_name()
        # check starting
        self.assertFalse(self.subject.running)
        self.subject.start()
        self.assertTrue(self.subject.running)
        self.assertEqual(len(self.session.message_queue), 0)
        self.assertEqual(self.module_name, 'Stats')

    def tearDown(self):
        # check closing
        self.subject.stop()
        self.assertFalse(self.subject.running)
        self.subject.detach(self.listener)
        self.listener.stop()

    def test_specfile(self):
        """
        Test for specfile
        
        """
        if "B10_FROM_BUILD" in os.environ:
            self.assertEqual(stats.SPECFILE_LOCATION,
                             os.environ["B10_FROM_BUILD"] + "/src/bin/stats/stats.spec")
        imp.reload(stats)
        # change path of SPECFILE_LOCATION
        stats.SPECFILE_LOCATION = TEST_SPECFILE_LOCATION
        self.assertEqual(stats.SPECFILE_LOCATION, TEST_SPECFILE_LOCATION)
        self.subject = stats.SessionSubject(session=self.session, verbose=True)
        self.session = self.subject.session
        self.listener = stats.CCSessionListener(self.subject, verbose=True)

        self.assertEqual(self.listener.stats_spec, [])
        self.assertEqual(self.listener.stats_data, {})

        self.assertEqual(self.listener.commands_spec, [
                {
                    "command_name": "status",
                    "command_description": "identify whether stats module is alive or not",
                    "command_args": []
                },
                {
                    "command_name": "the_dummy",
                    "command_description": "this is for testing",
                    "command_args": []
                }])

    def test_func_initialize_data(self):
        """
        Test for initialize_data function 
        
        """
        # prepare for sample data set
        stats_spec = [
            {
                "item_name": "none_sample",
                "item_type": "null",
                "item_default": "None"
            },
            {
                "item_name": "boolean_sample",
                "item_type": "boolean",
                "item_default": True
            },
            {
                "item_name": "string_sample",
                "item_type": "string",
                "item_default": "A something"
            },
            {
                "item_name": "int_sample",
                "item_type": "integer",
                "item_default": 9999999
            },
            {
                "item_name": "real_sample",
                "item_type": "real",
                "item_default": 0.0009
            },
            {
                "item_name": "list_sample",
                "item_type": "list",
                "item_default": [0, 1, 2, 3, 4],
                "list_item_spec": []
            },
            {
                "item_name": "map_sample",
                "item_type": "map",
                "item_default": {'name':'value'},
                "map_item_spec": []
            },
            {
                "item_name": "other_sample",
                "item_type": "__unknown__",
                "item_default": "__unknown__"
            }
        ]
        # data for comparison
        stats_data = {
            'none_sample': None,
            'boolean_sample': True,
            'string_sample': 'A something',
            'int_sample': 9999999,
            'real_sample': 0.0009,
            'list_sample': [0, 1, 2, 3, 4],
            'map_sample': {'name':'value'},
            'other_sample': '__unknown__'
        }
        self.assertEqual(self.listener.initialize_data(stats_spec), stats_data)

    def test_func_main(self):
        # explicitly make failed
        self.session.close()
        stats.main(session=self.session)

    def test_osenv(self):
        """
        test for not having environ "B10_FROM_BUILD"
        """
        if "B10_FROM_BUILD" in os.environ:
            path = os.environ["B10_FROM_BUILD"]
            os.environ.pop("B10_FROM_BUILD")
            imp.reload(stats)
            os.environ["B10_FROM_BUILD"] = path
            imp.reload(stats)

def result_ok(*args):
    if args:
        return { 'result': list(args) }
    else:
        return { 'result': [ 0 ] }

if __name__ == "__main__":
    unittest.main()
