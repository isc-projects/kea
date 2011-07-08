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

import unittest
import os
import threading
import io
import time
import imp

import stats
import isc.cc.session
from test_utils import BaseModules, ThreadingServerManager, MyStats, send_command, TIMEOUT_SEC

class TestUtilties(unittest.TestCase):
    items = [
        { 'item_name': 'test_int1',  'item_type': 'integer', 'item_default': 12345      },
        { 'item_name': 'test_real1', 'item_type': 'real',    'item_default': 12345.6789 },
        { 'item_name': 'test_bool1', 'item_type': 'boolean', 'item_default': True       },
        { 'item_name': 'test_str1',  'item_type': 'string',  'item_default': 'ABCD'     },
        { 'item_name': 'test_list1', 'item_type': 'list',    'item_default': [1,2,3],
          'list_item_spec' : [ { 'item_name': 'one',   'item_type': 'integer' },
                               { 'item_name': 'two',   'item_type': 'integer' },
                               { 'item_name': 'three', 'item_type': 'integer' } ] },
        { 'item_name': 'test_map1',  'item_type': 'map',     'item_default': {'a':1,'b':2,'c':3},
          'map_item_spec'  : [ { 'item_name': 'a',   'item_type': 'integer'},
                               { 'item_name': 'b',   'item_type': 'integer'},
                               { 'item_name': 'c', 'item_type': 'integer'} ] },
        { 'item_name': 'test_int2',  'item_type': 'integer' },
        { 'item_name': 'test_real2', 'item_type': 'real'    },
        { 'item_name': 'test_bool2', 'item_type': 'boolean' },
        { 'item_name': 'test_str2',  'item_type': 'string'  },
        { 'item_name': 'test_list2', 'item_type': 'list',
          'list_item_spec' : [ { 'item_name': 'one',   'item_type': 'integer' },
                               { 'item_name': 'two',   'item_type': 'integer' },
                               { 'item_name': 'three', 'item_type': 'integer' } ] },
        { 'item_name': 'test_map2',  'item_type': 'map',
          'map_item_spec'  : [ { 'item_name': 'A', 'item_type': 'integer'},
                               { 'item_name': 'B', 'item_type': 'integer'},
                               { 'item_name': 'C', 'item_type': 'integer'} ] },
        { 'item_name': 'test_none',  'item_type': 'none'    }
        ]

    def test_parse_spec(self):
        self.assertEqual(
            stats.parse_spec(self.items), {
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
                'test_list2' : [0,0,0],
                'test_map2'  : { 'A' : 0, 'B' : 0, 'C' : 0 },
                'test_none'  : None })
        self.assertRaises(TypeError, stats.parse_spec, None)
        self.assertRaises(KeyError, stats.parse_spec, [{'item_name':'Foo'}])

    def test_get_timestamp(self):
        self.assertEqual(stats.get_timestamp(), 1308730448.965706)

    def test_get_datetime(self):
        stats.time = lambda : 1308730448.965706
        stats.gmtime = lambda : (2011, 6, 22, 8, 14, 8, 2, 173, 0)
        self.assertEqual(stats.get_datetime(), '2011-06-22T08:14:08Z')
        self.assertNotEqual(stats.get_datetime(
                (2011, 6, 22, 8, 23, 40, 2, 173, 0)), '2011-06-22T08:14:08Z')

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

    def tearDown(self):
        pass

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
        self.base = BaseModules()
        self.stats = stats.Stats()
        self.assertTrue("B10_FROM_SOURCE" in os.environ)
        self.assertEqual(stats.SPECFILE_LOCATION, \
                             os.environ["B10_FROM_SOURCE"] + os.sep + \
                             "src" + os.sep + "bin" + os.sep + "stats" + \
                             os.sep + "stats.spec")

    def tearDown(self):
        self.base.shutdown()

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
        statsserver = ThreadingServerManager(MyStats)
        stats = statsserver.server
        self.assertFalse(stats.running)
        statsserver.run()
        time.sleep(TIMEOUT_SEC)
        self.assertTrue(stats.running)
        statsserver.shutdown()
        self.assertFalse(stats.running)

    def test_start_with_err(self):
        statsd = stats.Stats()
        statsd.update_statistics_data = lambda x,**y: [1]
        self.assertRaises(stats.StatsError, statsd.start)

    def test_config_handler(self):
        self.assertEqual(self.stats.config_handler({'foo':'bar'}),
                         isc.config.create_answer(0))

    def test_command_handler(self):
        statsserver = ThreadingServerManager(MyStats)
        statsserver.run()
        time.sleep(TIMEOUT_SEC*4)
        self.base.boss.server._started.wait()
        self.assertEqual(
            send_command(
                'show', 'Stats', 
                params={ 'owner' : 'Boss',
                  'name'  : 'boot_time' }),
            (0, '2011-06-22T08:14:08Z'))
        self.assertEqual(
            send_command(
                'set', 'Stats', 
                params={ 'owner' : 'Boss',
                  'data'  : { 'boot_time' : '2012-06-22T18:24:08Z' } }),
            (0, None))
        self.assertEqual(
            send_command(
                'show', 'Stats', 
                params={ 'owner' : 'Boss',
                  'name'  : 'boot_time' }),
            (0, '2012-06-22T18:24:08Z'))
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
        self.assertEqual(value['Boss']['boot_time'], '2012-06-22T18:24:08Z')
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

        statsserver.shutdown()

    def test_update_modules(self):
        self.assertEqual(len(self.stats.modules), 0)
        self.stats.update_modules()
        self.assertTrue('Stats' in self.stats.modules)
        self.assertTrue('Boss' in self.stats.modules)
        self.assertFalse('Dummy' in self.stats.modules)
        my_statistics_data = stats.parse_spec(self.stats.modules['Stats'].get_statistics_spec())
        self.assertTrue('report_time' in my_statistics_data)
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertTrue('last_update_time' in my_statistics_data)
        self.assertTrue('timestamp' in my_statistics_data)
        self.assertTrue('lname' in my_statistics_data)
        self.assertEqual(my_statistics_data['report_time'], "1970-01-01T00:00:00Z")
        self.assertEqual(my_statistics_data['boot_time'], "1970-01-01T00:00:00Z")
        self.assertEqual(my_statistics_data['last_update_time'], "1970-01-01T00:00:00Z")
        self.assertEqual(my_statistics_data['timestamp'], 0.0)
        self.assertEqual(my_statistics_data['lname'], "")
        my_statistics_data = stats.parse_spec(self.stats.modules['Boss'].get_statistics_spec())
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertEqual(my_statistics_data['boot_time'], "1970-01-01T00:00:00Z")

    def test_get_statistics_data(self):
        my_statistics_data = self.stats.get_statistics_data()
        self.assertTrue('Stats' in my_statistics_data)
        self.assertTrue('Boss' in my_statistics_data)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats')
        self.assertTrue('report_time' in my_statistics_data)
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertTrue('last_update_time' in my_statistics_data)
        self.assertTrue('timestamp' in my_statistics_data)
        self.assertTrue('lname' in my_statistics_data)
        self.assertIsNone(self.stats.get_statistics_data(owner='Foo'))
        my_statistics_data = self.stats.get_statistics_data(owner='Stats')
        self.assertTrue('boot_time' in my_statistics_data)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='report_time')
        self.assertEqual(my_statistics_data, "1970-01-01T00:00:00Z")
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='boot_time')
        self.assertEqual(my_statistics_data, "1970-01-01T00:00:00Z")
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='last_update_time')
        self.assertEqual(my_statistics_data, "1970-01-01T00:00:00Z")
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='timestamp')
        self.assertEqual(my_statistics_data, 0.0)
        my_statistics_data = self.stats.get_statistics_data(owner='Stats', name='lname')
        self.assertEqual(my_statistics_data, '')
        self.assertIsNone(self.stats.get_statistics_data(owner='Stats', name='Bar'))
        self.assertIsNone(self.stats.get_statistics_data(owner='Foo', name='Bar'))
        self.assertEqual(self.stats.get_statistics_data(name='Bar'), None)

    def test_update_statistics_data(self):
        self.stats.update_statistics_data(owner='Stats', lname='foo@bar')
        self.assertTrue('Stats' in self.stats.statistics_data)
        my_statistics_data = self.stats.statistics_data['Stats']
        self.assertEqual(my_statistics_data['lname'], 'foo@bar')
        self.stats.update_statistics_data(owner='Stats', last_update_time='2000-01-01T10:10:10Z')
        self.assertTrue('Stats' in self.stats.statistics_data)
        my_statistics_data = self.stats.statistics_data['Stats']
        self.assertEqual(my_statistics_data['last_update_time'], '2000-01-01T10:10:10Z')
        self.assertEqual(self.stats.update_statistics_data(owner='Stats', lname=0.0),
                         ['0.0 should be a string'])
        self.assertEqual(self.stats.update_statistics_data(owner='Dummy', foo='bar'),
                         ['unknown module name'])

    def test_command_status(self):
        self.assertEqual(self.stats.command_status(),
                isc.config.create_answer(
                0, "Stats is up. (PID " + str(os.getpid()) + ")"))
        
    def test_command_shutdown(self):
        self.stats.running = True
        self.assertEqual(self.stats.command_shutdown(),
                         isc.config.create_answer(0))
        self.assertFalse(self.stats.running)
        
    def test_command_show(self):
        self.assertEqual(self.stats.command_show(owner='Foo', name=None),
                         isc.config.create_answer(1, "item name is not specified"))
        self.assertEqual(self.stats.command_show(owner='Foo', name='_bar_'),
                         isc.config.create_answer(
                1, "specified module name and/or item name are incorrect"))
        self.assertEqual(self.stats.command_show(owner='Foo', name='bar'),
                         isc.config.create_answer(
                1, "specified module name and/or item name are incorrect"))
        orig_get_timestamp = stats.get_timestamp
        orig_get_datetime = stats.get_datetime
        stats.get_timestamp = lambda : 1308730448.965706
        stats.get_datetime = lambda : '2011-06-22T08:14:08Z'
        self.assertEqual(stats.get_timestamp(), 1308730448.965706)
        self.assertEqual(stats.get_datetime(), '2011-06-22T08:14:08Z')
        self.assertEqual(self.stats.command_show(owner='Stats', name='report_time'), \
                             isc.config.create_answer(0, '2011-06-22T08:14:08Z'))
        self.assertEqual(self.stats.statistics_data['Stats']['timestamp'], 1308730448.965706)
        self.assertEqual(self.stats.statistics_data['Stats']['boot_time'], '1970-01-01T00:00:00Z')
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
        self.assertEqual(len(schema), 2)
        for item in schema:
            self.assertTrue(len(item) == 6)
            self.assertTrue('item_name' in item)
            self.assertTrue('item_type' in item)
            self.assertTrue('item_optional' in item)
            self.assertTrue('item_default' in item)
            self.assertTrue('item_title' in item)
            self.assertTrue('item_description' in item)

        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_showschema(owner='Stats'))
        self.assertEqual(rcode, 0)
        self.assertFalse('Stats' in value)
        self.assertFalse('Boss' in value)
        self.assertFalse('Auth' in value)
        for item in value:
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
        self.assertFalse('Stats' in value)
        self.assertFalse('Boss' in value)
        self.assertFalse('Auth' in value)
        self.assertTrue(len(value) == 7)
        self.assertTrue('item_name' in value)
        self.assertTrue('item_type' in value)
        self.assertTrue('item_optional' in value)
        self.assertTrue('item_default' in value)
        self.assertTrue('item_title' in value)
        self.assertTrue('item_description' in value)
        self.assertTrue('item_format' in value)
        self.assertEqual(value['item_name'], 'report_time')
        self.assertEqual(value['item_format'], 'date-time')

        self.assertEqual(self.stats.command_showschema(owner='Foo'),
                         isc.config.create_answer(
                1, "specified module name and/or item name are incorrect"))
        self.assertEqual(self.stats.command_showschema(owner='Foo', name='bar'),
                         isc.config.create_answer(
                1, "specified module name and/or item name are incorrect"))
        self.assertEqual(self.stats.command_showschema(owner='Stats', name='bar'),
                         isc.config.create_answer(
                1, "specified module name and/or item name are incorrect"))
        self.assertEqual(self.stats.command_showschema(name='bar'),
                         isc.config.create_answer(
                1, "module name is not specified"))

    def test_command_set(self):
        orig_get_datetime = stats.get_datetime
        stats.get_datetime = lambda : '2011-06-22T06:12:38Z'
        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_set(owner='Boss',
                                   data={ 'boot_time' : '2011-06-22T13:15:04Z' }))
        stats.get_datetime = orig_get_datetime
        self.assertEqual(rcode, 0)
        self.assertTrue(value is None)
        self.assertEqual(self.stats.statistics_data['Boss']['boot_time'],
                         '2011-06-22T13:15:04Z')
        self.assertEqual(self.stats.statistics_data['Stats']['last_update_time'],
                         '2011-06-22T06:12:38Z')
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
                "specified module name and/or statistics data are incorrect:"
                + " No statistics specification"))
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

    def test_osenv(self):
        """
        test for not having environ "B10_FROM_SOURCE"
        """
        if "B10_FROM_SOURCE" in os.environ:
            path = os.environ["B10_FROM_SOURCE"]
            os.environ.pop("B10_FROM_SOURCE")
            imp.reload(stats)
            os.environ["B10_FROM_SOURCE"] = path
            imp.reload(stats)

def test_main():
    unittest.main()

if __name__ == "__main__":
    test_main()
