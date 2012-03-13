# Copyright (C) 2010, 2011  Internet Systems Consortium.
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

"""
In each of these tests we start several virtual components. They are
not the real components, no external processes are started. They are
just simple mock objects running each in its own thread and pretending
to be bind10 modules. This helps testing the stats module in a close
to real environment.
"""

import unittest
import os
import threading
import io
import time
import imp

import stats
import isc.cc.session
from test_utils import BaseModules, ThreadingServerManager, MyStats, SignalHandler, send_command, send_shutdown
from isc.testutils.ccsession_mock import MockModuleCCSession

class TestUtilties(unittest.TestCase):
    items = [
        { 'item_name': 'test_int1',  'item_type': 'integer', 'item_default': 12345      },
        { 'item_name': 'test_real1', 'item_type': 'real',    'item_default': 12345.6789 },
        { 'item_name': 'test_bool1', 'item_type': 'boolean', 'item_default': True       },
        { 'item_name': 'test_str1',  'item_type': 'string',  'item_default': 'ABCD'     },
        { 'item_name': 'test_list1', 'item_type': 'list',    'item_default': [1,2,3],
          'list_item_spec' : { 'item_name': 'number',   'item_type': 'integer' } },
        { 'item_name': 'test_map1',  'item_type': 'map',     'item_default': {'a':1,'b':2,'c':3},
          'map_item_spec'  : [ { 'item_name': 'a',   'item_type': 'integer'},
                               { 'item_name': 'b',   'item_type': 'integer'},
                               { 'item_name': 'c', 'item_type': 'integer'} ] },
        { 'item_name': 'test_int2',  'item_type': 'integer' },
        { 'item_name': 'test_real2', 'item_type': 'real'    },
        { 'item_name': 'test_bool2', 'item_type': 'boolean' },
        { 'item_name': 'test_str2',  'item_type': 'string'  },
        { 'item_name': 'test_list2', 'item_type': 'list',
          'list_item_spec' : { 'item_name': 'number',   'item_type': 'integer' } },
        { 'item_name': 'test_map2',  'item_type': 'map',
          'map_item_spec'  : [ { 'item_name': 'A', 'item_type': 'integer'},
                               { 'item_name': 'B', 'item_type': 'integer'},
                               { 'item_name': 'C', 'item_type': 'integer'} ] },
        { 'item_name': 'test_none',  'item_type': 'none'    },
        { 'item_name': 'test_list3', 'item_type': 'list',    'item_default': ["one","two","three"],
          'list_item_spec' : { 'item_name': 'number', 'item_type': 'string' } },
        { 'item_name': 'test_map3',  'item_type': 'map',     'item_default': {'a':'one','b':'two','c':'three'},
          'map_item_spec'  : [ { 'item_name': 'a', 'item_type': 'string'},
                               { 'item_name': 'b', 'item_type': 'string'},
                               { 'item_name': 'c', 'item_type': 'string'} ] }
        ]

    def setUp(self):
        self.const_timestamp = 1308730448.965706
        self.const_timetuple = (2011, 6, 22, 8, 14, 8, 2, 173, 0)
        self.const_datetime = '2011-06-22T08:14:08Z'
        stats.time = lambda : self.const_timestamp
        stats.gmtime = lambda : self.const_timetuple

    def test_get_spec_defaults(self):
        self.assertEqual(
            stats.get_spec_defaults(self.items), {
                'test_int1'  : 12345              ,
                'test_real1' : 12345.6789         ,
                'test_bool1' : True               ,
                'test_str1'  : 'ABCD'             ,
                'test_list1' : [1,2,3]            ,
                'test_map1'  : {'a':1,'b':2,'c':3},
                'test_int2'  : 0 ,
                'test_real2' : 0.0,
                'test_bool2' : False,
                'test_str2'  : "",
                'test_list2' : [0],
                'test_map2'  : { 'A' : 0, 'B' : 0, 'C' : 0 },
                'test_none'  : None,
                'test_list3' : [ "one", "two", "three" ],
                'test_map3'  : { 'a' : 'one', 'b' : 'two', 'c' : 'three' } })
        self.assertEqual(stats.get_spec_defaults(None), {})
        self.assertRaises(KeyError, stats.get_spec_defaults, [{'item_name':'Foo'}])

    def test_get_timestamp(self):
        self.assertEqual(stats.get_timestamp(), self.const_timestamp)

    def test_get_datetime(self):
        self.assertEqual(stats.get_datetime(), self.const_datetime)
        self.assertNotEqual(stats.get_datetime(
                (2011, 6, 22, 8, 23, 40, 2, 173, 0)), self.const_datetime)

class TestCallback(unittest.TestCase):
    def setUp(self):
        self.dummy_func = lambda *x, **y : (x, y)
        self.dummy_args = (1,2,3)
        self.dummy_kwargs = {'a':1,'b':2,'c':3}
        self.cback1 = stats.Callback(
            command=self.dummy_func,
            args=self.dummy_args,
            kwargs=self.dummy_kwargs
            )
        self.cback2 = stats.Callback(
            args=self.dummy_args,
            kwargs=self.dummy_kwargs
            )
        self.cback3 = stats.Callback(
            command=self.dummy_func,
            kwargs=self.dummy_kwargs
            )
        self.cback4 = stats.Callback(
            command=self.dummy_func,
            args=self.dummy_args
            )

    def test_init(self):
        self.assertEqual((self.cback1.command, self.cback1.args, self.cback1.kwargs),
                         (self.dummy_func, self.dummy_args, self.dummy_kwargs))
        self.assertEqual((self.cback2.command, self.cback2.args, self.cback2.kwargs),
                         (None, self.dummy_args, self.dummy_kwargs))
        self.assertEqual((self.cback3.command, self.cback3.args, self.cback3.kwargs),
                         (self.dummy_func, (), self.dummy_kwargs))
        self.assertEqual((self.cback4.command, self.cback4.args, self.cback4.kwargs),
                         (self.dummy_func, self.dummy_args, {}))

    def test_call(self):
        self.assertEqual(self.cback1(), (self.dummy_args, self.dummy_kwargs))
        self.assertEqual(self.cback1(100, 200), ((100, 200), self.dummy_kwargs))
        self.assertEqual(self.cback1(a=100, b=200), (self.dummy_args, {'a':100, 'b':200}))
        self.assertEqual(self.cback2(), None)
        self.assertEqual(self.cback3(), ((), self.dummy_kwargs))
        self.assertEqual(self.cback3(100, 200), ((100, 200), self.dummy_kwargs))
        self.assertEqual(self.cback3(a=100, b=200), ((), {'a':100, 'b':200}))
        self.assertEqual(self.cback4(), (self.dummy_args, {}))
        self.assertEqual(self.cback4(100, 200), ((100, 200), {}))
        self.assertEqual(self.cback4(a=100, b=200), (self.dummy_args, {'a':100, 'b':200}))

class TestStats(unittest.TestCase):
    def setUp(self):
        # set the signal handler for deadlock
        self.sig_handler = SignalHandler(self.fail)
        self.base = BaseModules()
        self.stats = stats.Stats()
        self.const_timestamp = 1308730448.965706
        self.const_datetime = '2011-06-22T08:14:08Z'
        self.const_default_datetime = '1970-01-01T00:00:00Z'

    def tearDown(self):
        self.base.shutdown()
        # reset the signal handler
        self.sig_handler.reset()

    def test_init(self):
        self.assertEqual(self.stats.module_name, 'Stats')
        self.assertFalse(self.stats.running)
        self.assertTrue('command_show' in self.stats.callbacks)
        self.assertTrue('command_status' in self.stats.callbacks)
        self.assertTrue('command_shutdown' in self.stats.callbacks)
        self.assertTrue('command_show' in self.stats.callbacks)
        self.assertTrue('command_showschema' in self.stats.callbacks)
        self.assertTrue('command_set' in self.stats.callbacks)

    def test_init_undefcmd(self):
        spec_str = """\
{
  "module_spec": {
    "module_name": "Stats",
    "module_description": "Stats daemon",
    "config_data": [],
    "commands": [
      {
        "command_name": "_undef_command_",
        "command_description": "a undefined command in stats",
        "command_args": []
      }
    ],
    "statistics": []
  }
}
"""
        orig_spec_location = stats.SPECFILE_LOCATION
        stats.SPECFILE_LOCATION = io.StringIO(spec_str)
        self.assertRaises(stats.StatsError, stats.Stats)
        stats.SPECFILE_LOCATION = orig_spec_location

    def test_start(self):
        # start without err
        self.stats_server = ThreadingServerManager(MyStats)
        self.stats = self.stats_server.server
        self.assertFalse(self.stats.running)
        self.stats_server.run()
        self.assertEqual(send_command("status", "Stats"),
                (0, "Stats is up. (PID " + str(os.getpid()) + ")"))
        self.assertTrue(self.stats.running)
        # Due to a race-condition related to the threads used in these
        # tests, use of the mock session and the stopped check (see
        # below), are temporarily disabled
        # See ticket #1668
        # Override moduleCCSession so we can check if send_stopping is called
        #self.stats.mccs = MockModuleCCSession()
        self.assertEqual(send_shutdown("Stats"), (0, None))
        self.assertFalse(self.stats.running)
        # Call server.shutdown with argument True so the thread.join() call
        # blocks and we are sure the main loop has finished (and set
        # mccs.stopped)
        self.stats_server.shutdown(True)
        # Also temporarily disabled for #1668, see above
        #self.assertTrue(self.stats.mccs.stopped)

        # start with err
        self.stats = stats.Stats()
        self.stats.update_statistics_data = lambda x,**y: ['an error']
        self.assertRaises(stats.StatsError, self.stats.start)

    def test_handlers(self):
        self.stats_server = ThreadingServerManager(MyStats)
        self.stats = self.stats_server.server
        self.stats_server.run()
        # config_handler
        self.assertEqual(self.stats.config_handler({'foo':'bar'}),
                         isc.config.create_answer(0))

        # command_handler
        self.base.boss.server._started.wait()
        self.base.boss.server._started.clear()
        self.assertEqual(
            send_command(
                'show', 'Stats',
                params={ 'owner' : 'Boss',
                  'name'  : 'boot_time' }),
            (0, {'Boss': {'boot_time': self.const_datetime}}))
        self.assertEqual(
            send_command(
                'set', 'Stats',
                params={ 'owner' : 'Boss',
                  'data'  : { 'boot_time' : self.const_datetime } }),
            (0, None))
        self.assertEqual(
            send_command(
                'show', 'Stats',
                params={ 'owner' : 'Boss',
                  'name'  : 'boot_time' }),
            (0, {'Boss': {'boot_time': self.const_datetime}}))
        self.assertEqual(
            send_command('status', 'Stats'),
            (0, "Stats is up. (PID " + str(os.getpid()) + ")"))

        (rcode, value) = send_command('show', 'Stats')
        self.assertEqual(rcode, 0)
        self.assertEqual(len(value), 3)
        self.assertTrue('Boss' in value)
        self.assertTrue('Stats' in value)
        self.assertTrue('Auth' in value)
        self.assertEqual(len(value['Stats']), 5)
        self.assertEqual(len(value['Boss']), 1)
        self.assertTrue('boot_time' in value['Boss'])
        self.assertEqual(value['Boss']['boot_time'], self.const_datetime)
        self.assertTrue('report_time' in value['Stats'])
        self.assertTrue('boot_time' in value['Stats'])
        self.assertTrue('last_update_time' in value['Stats'])
        self.assertTrue('timestamp' in value['Stats'])
        self.assertTrue('lname' in value['Stats'])
        (rcode, value) = send_command('showschema', 'Stats')
        self.assertEqual(rcode, 0)
        self.assertEqual(len(value), 3)
        self.assertTrue('Boss' in value)
        self.assertTrue('Stats' in value)
        self.assertTrue('Auth' in value)
        self.assertEqual(len(value['Stats']), 5)
        self.assertEqual(len(value['Boss']), 1)
        for item in value['Boss']:
            self.assertTrue(len(item) == 7)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)
            self.assertTrue('item_format' in item)
        for item in value['Stats']:
            self.assertTrue(len(item) == 6 or len(item) == 7)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)
            if len(item) == 7:
                self.assertTrue('item_format' in item)

        self.assertEqual(
            send_command('__UNKNOWN__', 'Stats'),
            (1, "Unknown command: '__UNKNOWN__'"))

        self.stats_server.shutdown()

    def test_update_modules(self):
        self.assertEqual(len(self.stats.modules), 0)
        self.stats.update_modules()
        self.assertTrue('Stats' in self.stats.modules)
        self.assertTrue('Boss' in self.stats.modules)
        self.assertFalse('Dummy' in self.stats.modules)
        my_statistics_data = stats.get_spec_defaults(self.stats.modules['Stats'].get_statistics_spec())
        self.assertTrue('report_time' in my_statistics_data)
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertTrue('last_update_time' in my_statistics_data)
        self.assertTrue('timestamp' in my_statistics_data)
        self.assertTrue('lname' in my_statistics_data)
        self.assertEqual(my_statistics_data['report_time'], self.const_default_datetime)
        self.assertEqual(my_statistics_data['boot_time'], self.const_default_datetime)
        self.assertEqual(my_statistics_data['last_update_time'], self.const_default_datetime)
        self.assertEqual(my_statistics_data['timestamp'], 0.0)
        self.assertEqual(my_statistics_data['lname'], "")
        my_statistics_data = stats.get_spec_defaults(self.stats.modules['Boss'].get_statistics_spec())
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertEqual(my_statistics_data['boot_time'], self.const_default_datetime)
        orig_parse_answer = stats.isc.config.ccsession.parse_answer
        stats.isc.config.ccsession.parse_answer = lambda x: (99, 'error')
        self.assertRaises(stats.StatsError, self.stats.update_modules)
        stats.isc.config.ccsession.parse_answer = orig_parse_answer

    def test_get_statistics_data(self):
        my_statistics_data = self.stats.get_statistics_data()
        self.assertTrue('Stats' in my_statistics_data)
        self.assertTrue('Boss' in my_statistics_data)
        self.assertTrue('boot_time' in my_statistics_data['Boss'])
        my_statistics_data = self.stats.get_statistics_data(owner='Stats')
        self.assertTrue('Stats' in my_statistics_data)
        self.assertTrue('report_time' in my_statistics_data['Stats'])
        self.assertTrue('boot_time' in my_statistics_data['Stats'])
        self.assertTrue('last_update_time' in my_statistics_data['Stats'])
        self.assertTrue('timestamp' in my_statistics_data['Stats'])
        self.assertTrue('lname' in my_statistics_data['Stats'])
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data, owner='Foo')
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='report_time')
        self.assertEqual(my_statistics_data['Stats']['report_time'], self.const_default_datetime)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='boot_time')
        self.assertEqual(my_statistics_data['Stats']['boot_time'], self.const_default_datetime)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='last_update_time')
        self.assertEqual(my_statistics_data['Stats']['last_update_time'], self.const_default_datetime)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='timestamp')
        self.assertEqual(my_statistics_data['Stats']['timestamp'], 0.0)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='lname')
        self.assertEqual(my_statistics_data, {'Stats': {'lname':''}})
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          owner='Stats', name='Bar')
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          owner='Foo', name='Bar')
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          name='Bar')

    def test_update_statistics_data(self):
        self.stats.update_statistics_data(owner='Stats', lname='foo@bar')
        self.assertTrue('Stats' in self.stats.statistics_data)
        my_statistics_data = self.stats.statistics_data['Stats']
        self.assertEqual(my_statistics_data['lname'], 'foo@bar')
        self.stats.update_statistics_data(owner='Stats', last_update_time=self.const_datetime)
        self.assertTrue('Stats' in self.stats.statistics_data)
        my_statistics_data = self.stats.statistics_data['Stats']
        self.assertEqual(my_statistics_data['last_update_time'], self.const_datetime)
        self.assertEqual(self.stats.update_statistics_data(owner='Stats', lname=0.0),
                         ['0.0 should be a string'])
        self.assertEqual(self.stats.update_statistics_data(owner='Dummy', foo='bar'),
                         ['unknown module name: Dummy'])

    def test_update_modules_withpid(self):
        # one pid of Auth
        self.stats.update_statistics_data(owner='Auth',
                                          pid=9999,
                                          **{'queries.tcp':1001})
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'], 1001)
        self.assertTrue('Auth' in self.stats.statistics_data_bypid)
        self.assertTrue(9999 in self.stats.statistics_data_bypid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bypid['Auth'][9999])
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9999]['queries.tcp'], 1001)
        self.assertEqual(self.stats.statistics_data_bypid,
                         {'Auth': {9999: {'queries.tcp': 1001}}})
        # another pid of Auth
        self.stats.update_statistics_data(owner='Auth',
                                          pid=9998,
                                          **{'queries.tcp':1002,
                                             'queries.udp':1003})
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertTrue('queries.udp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'], 2003)
        self.assertEqual(self.stats.statistics_data['Auth']['queries.udp'], 1003)
        self.assertTrue('Auth' in self.stats.statistics_data_bypid)
        self.assertTrue(9999 in self.stats.statistics_data_bypid['Auth'])
        self.assertTrue(9998 in self.stats.statistics_data_bypid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bypid['Auth'][9999])
        self.assertTrue('queries.udp' in self.stats.statistics_data_bypid['Auth'][9998])
        self.assertTrue('queries.udp' in self.stats.statistics_data_bypid['Auth'][9998])
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9999]['queries.tcp'], 1001)
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9998]['queries.tcp'], 1002)
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9998]['queries.udp'], 1003)

    def test_commands(self):
        # status
        self.assertEqual(self.stats.command_status(),
                isc.config.create_answer(
                0, "Stats is up. (PID " + str(os.getpid()) + ")"))

        # shutdown
        self.stats.running = True
        self.assertEqual(self.stats.command_shutdown(),
                         isc.config.create_answer(0))
        self.assertFalse(self.stats.running)

    def test_command_show(self):
        self.assertEqual(self.stats.command_show(owner='Foo', name=None),
                         isc.config.create_answer(
                1, "specified arguments are incorrect: owner: Foo, name: None"))
        self.assertEqual(self.stats.command_show(owner='Foo', name='_bar_'),
                         isc.config.create_answer(
                1, "specified arguments are incorrect: owner: Foo, name: _bar_"))
        self.assertEqual(self.stats.command_show(owner='Foo', name='bar'),
                         isc.config.create_answer(
                1, "specified arguments are incorrect: owner: Foo, name: bar"))
        self.assertEqual(self.stats.command_show(owner='Auth'),
                         isc.config.create_answer(
                0, {'Auth':{ 'queries.udp': 0,
                     'queries.tcp': 0,
                     'queries.perzone': [{ 'zonename': 'test1.example',
                                           'queries.udp': 1,
                                           'queries.tcp': 2 },
                                         { 'zonename': 'test2.example',
                                           'queries.udp': 3,
                                           'queries.tcp': 4 }] }}))
        self.assertEqual(self.stats.command_show(owner='Auth', name='queries.udp'),
                         isc.config.create_answer(
                0, {'Auth': {'queries.udp':0}}))
        self.assertEqual(self.stats.command_show(owner='Auth', name='queries.perzone'),
                         isc.config.create_answer(
                0, {'Auth': {'queries.perzone': [{ 'zonename': 'test1.example',
                      'queries.udp': 1,
                      'queries.tcp': 2 },
                    { 'zonename': 'test2.example',
                      'queries.udp': 3,
                      'queries.tcp': 4 }]}}))
        orig_get_timestamp = stats.get_timestamp
        orig_get_datetime = stats.get_datetime
        stats.get_timestamp = lambda : self.const_timestamp
        stats.get_datetime = lambda : self.const_datetime
        self.assertEqual(stats.get_timestamp(), self.const_timestamp)
        self.assertEqual(stats.get_datetime(), self.const_datetime)
        self.assertEqual(self.stats.command_show(owner='Stats', name='report_time'), \
                             isc.config.create_answer(0, {'Stats': {'report_time':self.const_datetime}}))
        self.assertEqual(self.stats.statistics_data['Stats']['timestamp'], self.const_timestamp)
        self.assertEqual(self.stats.statistics_data['Stats']['boot_time'], self.const_default_datetime)
        stats.get_timestamp = orig_get_timestamp
        stats.get_datetime = orig_get_datetime
        self.stats.mccs.specification = isc.config.module_spec.ModuleSpec(
            { "module_name": self.stats.module_name,
              "statistics": [] } )
        self.assertRaises(
            stats.StatsError, self.stats.command_show, owner='Foo', name='bar')

    def test_command_showchema(self):
        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_showschema())
        self.assertEqual(rcode, 0)
        self.assertEqual(len(value), 3)
        self.assertTrue('Stats' in value)
        self.assertTrue('Boss' in value)
        self.assertTrue('Auth' in value)
        self.assertFalse('__Dummy__' in value)
        schema = value['Stats']
        self.assertEqual(len(schema), 5)
        for item in schema:
            self.assertTrue(len(item) == 6 or len(item) == 7)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)
            if len(item) == 7:
                self.assertTrue('item_format' in item)

        schema = value['Boss']
        self.assertEqual(len(schema), 1)
        for item in schema:
            self.assertTrue(len(item) == 7)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)
            self.assertTrue('item_format' in item)

        schema = value['Auth']
        self.assertEqual(len(schema), 3)
        for item in schema:
            if item['item_type'] == 'list':
                self.assertEqual(len(item), 7)
            else:
                self.assertEqual(len(item), 6)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)

        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_showschema(owner='Stats'))
        self.assertEqual(rcode, 0)
        self.assertTrue('Stats' in value)
        self.assertFalse('Boss' in value)
        self.assertFalse('Auth' in value)
        for item in value['Stats']:
            self.assertTrue(len(item) == 6 or len(item) == 7)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)
            if len(item) == 7:
                self.assertTrue('item_format' in item)

        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_showschema(owner='Stats', name='report_time'))
        self.assertEqual(rcode, 0)
        self.assertTrue('Stats' in value)
        self.assertFalse('Boss' in value)
        self.assertFalse('Auth' in value)
        self.assertEqual(len(value['Stats'][0]), 7)
        self.assertTrue('item_name' in value['Stats'][0])
        self.assertTrue('item_type' in value['Stats'][0])
        self.assertTrue('item_optional' in value['Stats'][0])
        self.assertTrue('item_default' in value['Stats'][0])
        self.assertTrue('item_title' in value['Stats'][0])
        self.assertTrue('item_description' in value['Stats'][0])
        self.assertTrue('item_format' in value['Stats'][0])
        self.assertEqual(value['Stats'][0]['item_name'], 'report_time')
        self.assertEqual(value['Stats'][0]['item_format'], 'date-time')

        self.assertEqual(self.stats.command_showschema(owner='Foo'),
                         isc.config.create_answer(
                1, "specified arguments are incorrect: owner: Foo, name: None"))
        self.assertEqual(self.stats.command_showschema(owner='Foo', name='bar'),
                         isc.config.create_answer(
                1, "specified arguments are incorrect: owner: Foo, name: bar"))
        self.assertEqual(self.stats.command_showschema(owner='Auth'),
                         isc.config.create_answer(
                0, {'Auth': [{
                        "item_default": 0,
                        "item_description": "A number of total query counts which all auth servers receive over TCP since they started initially",
                        "item_name": "queries.tcp",
                        "item_optional": False,
                        "item_title": "Queries TCP",
                        "item_type": "integer"
                        },
                    {
                        "item_default": 0,
                        "item_description": "A number of total query counts which all auth servers receive over UDP since they started initially",
                        "item_name": "queries.udp",
                        "item_optional": False,
                        "item_title": "Queries UDP",
                        "item_type": "integer"
                        },
                    {
                        "item_name": "queries.perzone",
                        "item_type": "list",
                        "item_optional": False,
                        "item_default": [
                            {
                                "zonename" : "test1.example",
                                "queries.udp" : 1,
                                "queries.tcp" : 2
                                },
                            {
                                "zonename" : "test2.example",
                                "queries.udp" : 3,
                                "queries.tcp" : 4
                                }
                        ],
                        "item_title": "Queries per zone",
                        "item_description": "Queries per zone",
                        "list_item_spec": {
                            "item_name": "zones",
                            "item_type": "map",
                            "item_optional": False,
                            "item_default": {},
                            "map_item_spec": [
                                {
                                    "item_name": "zonename",
                                    "item_type": "string",
                                    "item_optional": False,
                                    "item_default": "",
                                    "item_title": "Zonename",
                                    "item_description": "Zonename"
                                    },
                                {
                                    "item_name": "queries.udp",
                                    "item_type": "integer",
                                    "item_optional": False,
                                    "item_default": 0,
                                    "item_title": "Queries UDP per zone",
                                    "item_description": "A number of UDP query counts per zone"
                                    },
                                {
                                    "item_name": "queries.tcp",
                                    "item_type": "integer",
                                    "item_optional": False,
                                    "item_default": 0,
                                    "item_title": "Queries TCP per zone",
                                    "item_description": "A number of TCP query counts per zone"
                                    }
                                ]
                            }
                        }]}))
        self.assertEqual(self.stats.command_showschema(owner='Auth', name='queries.tcp'),
                         isc.config.create_answer(
                0, {'Auth': [{
                    "item_default": 0,
                    "item_description": "A number of total query counts which all auth servers receive over TCP since they started initially",
                    "item_name": "queries.tcp",
                    "item_optional": False,
                    "item_title": "Queries TCP",
                    "item_type": "integer"
                    }]}))
        self.assertEqual(self.stats.command_showschema(owner='Auth', name='queries.perzone'),
                         isc.config.create_answer(
                0, {'Auth':[{
                    "item_name": "queries.perzone",
                    "item_type": "list",
                    "item_optional": False,
                    "item_default": [
                        {
                            "zonename" : "test1.example",
                            "queries.udp" : 1,
                            "queries.tcp" : 2
                            },
                        {
                            "zonename" : "test2.example",
                            "queries.udp" : 3,
                            "queries.tcp" : 4
                            }
                    ],
                    "item_title": "Queries per zone",
                    "item_description": "Queries per zone",
                    "list_item_spec": {
                        "item_name": "zones",
                        "item_type": "map",
                        "item_optional": False,
                        "item_default": {},
                        "map_item_spec": [
                            {
                                "item_name": "zonename",
                                "item_type": "string",
                                "item_optional": False,
                                "item_default": "",
                                "item_title": "Zonename",
                                "item_description": "Zonename"
                                },
                            {
                                "item_name": "queries.udp",
                                "item_type": "integer",
                                "item_optional": False,
                                "item_default": 0,
                                "item_title": "Queries UDP per zone",
                                "item_description": "A number of UDP query counts per zone"
                                },
                            {
                                "item_name": "queries.tcp",
                                "item_type": "integer",
                                "item_optional": False,
                                "item_default": 0,
                                "item_title": "Queries TCP per zone",
                                "item_description": "A number of TCP query counts per zone"
                                }
                            ]
                        }
                    }]}))

        self.assertEqual(self.stats.command_showschema(owner='Stats', name='bar'),
                         isc.config.create_answer(
                1, "specified arguments are incorrect: owner: Stats, name: bar"))
        self.assertEqual(self.stats.command_showschema(name='bar'),
                         isc.config.create_answer(
                1, "module name is not specified"))

    def test_command_set(self):
        orig_get_datetime = stats.get_datetime
        stats.get_datetime = lambda : self.const_datetime
        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_set(owner='Boss',
                                   data={ 'boot_time' : self.const_datetime }))
        stats.get_datetime = orig_get_datetime
        self.assertEqual(rcode, 0)
        self.assertTrue(value is None)
        self.assertEqual(self.stats.statistics_data['Boss']['boot_time'],
                         self.const_datetime)
        self.assertEqual(self.stats.statistics_data['Stats']['last_update_time'],
                         self.const_datetime)
        self.assertEqual(self.stats.command_set(owner='Stats',
                                                data={ 'lname' : 'foo@bar' }),
                         isc.config.create_answer(0, None))
        self.stats.statistics_data['Stats'] = {}
        self.stats.mccs.specification = isc.config.module_spec.ModuleSpec(
            { "module_name": self.stats.module_name,
              "statistics": [] } )
        self.assertEqual(self.stats.command_set(owner='Stats',
                                                data={ 'lname' : '_foo_@_bar_' }),
                         isc.config.create_answer(
                1,
                "errors while setting statistics data: unknown item lname"))
        self.stats.statistics_data['Stats'] = {}
        self.stats.mccs.specification = isc.config.module_spec.ModuleSpec(
            { "module_name": self.stats.module_name } )
        self.assertEqual(self.stats.command_set(owner='Stats',
                                                data={ 'lname' : '_foo_@_bar_' }),
                         isc.config.create_answer(
                1,
                "errors while setting statistics data: No statistics specification"))
        self.stats.statistics_data['Stats'] = {}
        self.stats.mccs.specification = isc.config.module_spec.ModuleSpec(
            { "module_name": self.stats.module_name,
              "statistics": [
                    {
                        "item_name": "dummy",
                        "item_type": "string",
                        "item_optional": False,
                        "item_default": "",
                        "item_title": "Local Name",
                        "item_description": "brabra"
                        } ] } )
        self.assertRaises(stats.StatsError,
                          self.stats.command_set, owner='Stats', data={ 'dummy' : '_xxxx_yyyy_zzz_' })

    def test_command_set_withpid(self):
        # one pid of Auth
        retval = isc.config.ccsession.parse_answer(
            self.stats.command_set(owner='Auth',
                                   pid=9997,
                                   data={ 'queries.tcp' : 1001 }))
        self.assertEqual(retval, (0,None))
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'], 1001)
        self.assertTrue('Stats' in self.stats.statistics_data)
        self.assertTrue('last_update_time' in self.stats.statistics_data['Stats'])
        self.assertTrue('Auth' in self.stats.statistics_data_bypid)
        self.assertTrue(9997 in self.stats.statistics_data_bypid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bypid['Auth'][9997])
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9997]['queries.tcp'], 1001)
        # another pid of Auth
        retval = isc.config.ccsession.parse_answer(
            self.stats.command_set(owner='Auth',
                                   pid=9996,
                                   data={ 'queries.tcp' : 1002,
                                          'queries.udp' : 1003,}))
        self.assertEqual(retval, (0,None))
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertTrue('queries.udp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'], 2003)
        self.assertEqual(self.stats.statistics_data['Auth']['queries.udp'], 1003)
        self.assertTrue('Auth' in self.stats.statistics_data_bypid)
        self.assertTrue(9997 in self.stats.statistics_data_bypid['Auth'])
        self.assertTrue(9996 in self.stats.statistics_data_bypid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bypid['Auth'][9997])
        self.assertTrue('queries.udp' in self.stats.statistics_data_bypid['Auth'][9996])
        self.assertTrue('queries.udp' in self.stats.statistics_data_bypid['Auth'][9996])
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9997]['queries.tcp'], 1001)
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9996]['queries.tcp'], 1002)
        self.assertEqual(self.stats.statistics_data_bypid['Auth'][9996]['queries.udp'], 1003)

class TestOSEnv(unittest.TestCase):
    def test_osenv(self):
        """
        test for the environ variable "B10_FROM_SOURCE"
        "B10_FROM_SOURCE" is set in Makefile
        """
        # test case having B10_FROM_SOURCE
        self.assertTrue("B10_FROM_SOURCE" in os.environ)
        self.assertEqual(stats.SPECFILE_LOCATION, \
                             os.environ["B10_FROM_SOURCE"] + os.sep + \
                             "src" + os.sep + "bin" + os.sep + "stats" + \
                             os.sep + "stats.spec")
        # test case not having B10_FROM_SOURCE
        path = os.environ["B10_FROM_SOURCE"]
        os.environ.pop("B10_FROM_SOURCE")
        self.assertFalse("B10_FROM_SOURCE" in os.environ)
        # import stats again
        imp.reload(stats)
        # revert the changes
        os.environ["B10_FROM_SOURCE"] = path
        imp.reload(stats)

def test_main():
    unittest.main()

if __name__ == "__main__":
    test_main()
