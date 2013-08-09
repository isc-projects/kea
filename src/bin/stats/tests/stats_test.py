# Copyright (C) 2010-2013  Internet Systems Consortium.
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
import io
import time
import imp
import sys

import stats
import isc.log
from test_utils import MyStats
from isc.config.ccsession import create_answer

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
                               { 'item_name': 'c', 'item_type': 'string'} ] },
        {
          'item_name': 'test_named_set',
          'item_type': 'named_set',
          'item_default': { },
          'named_set_item_spec': {
            'item_name': 'name',
            'item_type': 'map',
            'item_default': { },
            'map_item_spec': [
              {
                'item_name': 'number1',
                'item_type': 'integer'
                },
              {
                'item_name': 'number2',
                'item_type': 'integer'
                }
              ]
            }
          }
        ]

    def setUp(self):
        self.const_timestamp = 1308730448.965706
        self.const_timetuple = (2011, 6, 22, 8, 14, 8, 2, 173, 0)
        self.const_datetime = '2011-06-22T08:14:08Z'
        self.__orig_time = stats.time
        self.__orig_gmtime = stats.gmtime
        stats.time = lambda : self.const_timestamp
        stats.gmtime = lambda : self.const_timetuple

    def tearDown(self):
        stats.time = self.__orig_time
        stats.gmtime = self.__orig_gmtime

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
                'test_map3'  : { 'a' : 'one', 'b' : 'two', 'c' : 'three' },
                'test_named_set' : {} })
        self.assertEqual(stats.get_spec_defaults(None), {})
        self.assertRaises(KeyError, stats.get_spec_defaults, [{'item_name':'Foo'}])

    def test_get_timestamp(self):
        self.assertEqual(stats.get_timestamp(), self.const_timestamp)

    def test_get_datetime(self):
        self.assertEqual(stats.get_datetime(), self.const_datetime)
        self.assertNotEqual(stats.get_datetime(
                (2011, 6, 22, 8, 23, 40, 2, 173, 0)), self.const_datetime)

    def test__accum(self):
        self.assertEqual(stats._accum(None, None), None)
        self.assertEqual(stats._accum(None, "b"), "b")
        self.assertEqual(stats._accum("a", None), "a")
        self.assertEqual(stats._accum(1, 2), 3)
        self.assertEqual(stats._accum(0.5, 0.3), 0.8)
        self.assertEqual(stats._accum(1, 0.3), 1.3)
        self.assertEqual(stats._accum(0.5, 2), 2.5)
        self.assertEqual(stats._accum('aa','bb'), 'bb')
        self.assertEqual(stats._accum('1970-01-01T09:00:00Z','2012-08-09T09:33:31Z'),
                         '2012-08-09T09:33:31Z')
        self.assertEqual(stats._accum(
                [1, 2, 3], [4, 5]), [5, 7, 3])
        self.assertEqual(stats._accum(
                [4, 5], [1, 2, 3]), [5, 7, 3])
        self.assertEqual(stats._accum(
                [1, 2, 3], [None, 5, 6]), [1, 7, 9])
        self.assertEqual(stats._accum(
                [None, 5, 6], [1, 2, 3]), [1, 7, 9])
        self.assertEqual(stats._accum(
                [1, 2, 3], [None, None, None, None]), [1,2,3,None])
        self.assertEqual(stats._accum(
                [[1,2],3],[[],5,6]), [[1,2],8,6])
        self.assertEqual(stats._accum(
                {'one': 1, 'two': 2, 'three': 3},
                {'one': 4, 'two': 5}),
                         {'one': 5, 'two': 7, 'three': 3})
        self.assertEqual(stats._accum(
                {'one': 1, 'two': 2, 'three': 3},
                {'four': 4, 'five': 5}),
                         {'one': 1, 'two': 2, 'three': 3, 'four': 4, 'five': 5})
        self.assertEqual(stats._accum(
                {'one': [1, 2], 'two': [3, None, 5], 'three': [None, 3, None]},
                {'one': [2], 'two': [4, 5], 'three': [None, None, None], 'four': 'FOUR'}),
                         {'one':[3,2], 'two':[7,5,5], 'three':[None,3,None], 'four': 'FOUR'})
        self.assertEqual(stats._accum(
                [ {'one': 1, 'two': 2, 'three': 3}, {'four': 4, 'five': 5, 'six': 6} ],
                [ {}, {'four': 1, 'five': 2, 'six': 3} ]),
                [ {'one': 1, 'two': 2, 'three': 3}, {'four': 5, 'five': 7, 'six': 9} ])

    def test_merge_oldnre(self):
        self.assertEqual(stats.merge_oldnew(1, 2), 2)
        self.assertEqual(stats.merge_oldnew(0.5, 0.3), 0.3)
        self.assertEqual(stats.merge_oldnew('aa','bb'), 'bb')
        self.assertEqual(stats.merge_oldnew(
                [1, 2, 3], [4, 5]), [4, 5, 3])
        self.assertEqual(stats.merge_oldnew(
                [4, 5], [1, 2, 3]), [1, 2, 3])
        self.assertEqual(stats.merge_oldnew(
                [1, 2, 3], [None, 5, 6]), [None, 5, 6])
        self.assertEqual(stats.merge_oldnew(
                [None, 5, 6], [1, 2, 3]), [1, 2, 3])
        self.assertEqual(stats.merge_oldnew(
                [1, 2, 3], [None, None, None, None]), [None, None, None, None])
        self.assertEqual(stats.merge_oldnew(
                [[1,2],3],[[],5,6]), [[1,2],5,6])
        self.assertEqual(stats.merge_oldnew(
                {'one': 1, 'two': 2, 'three': 3},
                {'one': 4, 'two': 5}),
                         {'one': 4, 'two': 5, 'three': 3})
        self.assertEqual(stats.merge_oldnew(
                {'one': 1, 'two': 2, 'three': 3},
                {'four': 4, 'five': 5}),
                         {'one': 1, 'two': 2, 'three': 3, 'four': 4, 'five': 5})
        self.assertEqual(stats.merge_oldnew(
                {'one': [1, 2], 'two': [3, None, 5], 'three': [None, 3, None]},
                {'one': [2], 'two': [4, 5], 'three': [None, None, None], 'four': 'FOUR'}),
                         {'one':[2,2], 'two':[4,5,5], 'three':[None,None,None], 'four': 'FOUR'})
        self.assertEqual(stats.merge_oldnew(
                [ {'one': 1, 'two': 2, 'three': 3}, {'four': 4, 'five': 5, 'six': 6} ],
                [ {}, {'four': 1, 'five': 2, 'six': 3} ]),
                [ {'one': 1, 'two': 2, 'three': 3}, {'four': 1, 'five': 2, 'six': 3} ])

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
        self.const_timestamp = 1308730448.965706
        self.const_datetime = '2011-06-22T08:14:08Z'
        self.const_default_datetime = '1970-01-01T00:00:00Z'
        # Record original module-defined functions in case we replace them
        self.__orig_timestamp = stats.get_timestamp
        self.__orig_get_datetime = stats.get_datetime

    def tearDown(self):
        # restore the stored original function in case we replaced them
        stats.get_timestamp = self.__orig_timestamp
        stats.get_datetime = self.__orig_get_datetime

    def test_init(self):
        self.stats = MyStats()
        self.assertEqual(self.stats.module_name, 'Stats')
        self.assertFalse(self.stats.running)
        self.assertTrue('command_show' in self.stats.callbacks)
        self.assertTrue('command_status' in self.stats.callbacks)
        self.assertTrue('command_shutdown' in self.stats.callbacks)
        self.assertTrue('command_show' in self.stats.callbacks)
        self.assertTrue('command_showschema' in self.stats.callbacks)
        self.assertEqual(self.stats.config['poll-interval'], 60)

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
        self.assertRaises(stats.StatsError, MyStats)
        stats.SPECFILE_LOCATION = orig_spec_location

    def __send_command(self, stats, command_name, params=None):
        '''Emulate a command arriving to stats by directly calling callback'''
        return isc.config.ccsession.parse_answer(
            stats.command_handler(command_name, params))

    def test_start(self):
        # Define a separate exception class so we can be sure that's actually
        # the one raised in __check_start() below
        class CheckException(Exception):
            pass

        def __check_start(tested_stats):
            self.assertTrue(tested_stats.running)
            raise CheckException # terminate the loop

        # start without err
        self.stats = MyStats()
        self.assertFalse(self.stats.running)
        self.stats._check_command = lambda: __check_start(self.stats)
        # We are going to confirm start() will set running to True, avoiding
        # to fall into a loop with the exception trick.
        self.assertRaises(CheckException, self.stats.start)
        self.assertEqual(self.__send_command(self.stats, "status"),
                         (0, "Stats is up. (PID " + str(os.getpid()) + ")"))

    def test_shutdown(self):
        def __check_shutdown(tested_stats):
            self.assertTrue(tested_stats.running)
            self.assertEqual(self.__send_command(tested_stats, "shutdown"),
                             (0, None))
            self.assertFalse(tested_stats.running)
            # override get_interval() so it won't go poll statistics
            tested_stats.get_interval = lambda : 0

        self.stats = MyStats()
        self.stats._check_command = lambda: __check_shutdown(self.stats)
        self.stats.start()
        self.assertTrue(self.stats.mccs.stopped)

    def test_handlers(self):
        """Test command_handler"""

        __stats = MyStats()

        # 'show' command.  We're going to check the expected methods are
        # called in the expected order, and check the resulting response.
        # Details of each method are tested separately.
        call_log = []
        def __steal_method(fn_name, *arg):
            call_log.append((fn_name, arg))
            if fn_name == 'update_stat':
                return False        # "no error"
            if fn_name == 'showschema':
                return isc.config.create_answer(0, 'no error')

        # Fake some methods and attributes for inspection
        __stats.do_polling = lambda: __steal_method('polling')
        __stats.update_statistics_data = \
            lambda x, y, z: __steal_method('update_stat', x, y, z)
        __stats.update_modules = lambda: __steal_method('update_module')
        __stats.mccs.lname = 'test lname'
        __stats.statistics_data = {'Init': {'boot_time': self.const_datetime}}

        # skip initial polling
        stats.get_timestamp = lambda: 0
        __stats._lasttime_poll = 0

        stats.get_datetime = lambda: 42 # make the result predictable

        # now send the command
        self.assertEqual(
            self.__send_command(
                __stats, 'show',
                params={ 'owner' : 'Init', 'name'  : 'boot_time' }),
            (0, {'Init': {'boot_time': self.const_datetime}}))
        # Check if expected methods are called
        self.assertEqual([('update_stat',
                           ('Stats', 'test lname',
                            {'timestamp': 0,
                             'report_time': 42})),
                          ('update_module', ())], call_log)

        # Then update faked timestamp so the initial polling will happen, and
        # confirm that.
        call_log = []
        stats.get_timestamp = lambda: 10
        self.assertEqual(
            self.__send_command(
                __stats, 'show',
                params={ 'owner' : 'Init', 'name'  : 'boot_time' }),
            (0, {'Init': {'boot_time': self.const_datetime}}))
        self.assertEqual([('polling', ()),
                          ('update_stat',
                           ('Stats', 'test lname',
                            {'timestamp': 10,
                             'report_time': 42})),
                          ('update_module', ())], call_log)

        # 'status' command.  We can confirm the behavior without any fake
        self.assertEqual(
            self.__send_command(__stats, 'status'),
            (0, "Stats is up. (PID " + str(os.getpid()) + ")"))

        # 'showschema' command.  update_modules() will be called, which
        # (implicitly) confirms the correct method is called; further details
        # are tested separately.
        call_log = []
        (rcode, value) = self.__send_command(__stats, 'showschema')
        self.assertEqual([('update_module', ())], call_log)

        # Unknown command.  Error should be returned
        self.assertEqual(
            self.__send_command(__stats, '__UNKNOWN__'),
            (1, "Unknown command: '__UNKNOWN__'"))

    def test_update_modules(self):
        """Confirm the behavior of Stats.update_modules().

        It checks whether the expected command is sent to ConfigManager,
        and whether the answer from ConfigManager is handled as expected.

        """

        def __check_rpc_call(command, group):
            self.assertEqual('ConfigManager', group)
            self.assertEqual(command,
                             isc.config.ccsession.COMMAND_GET_STATISTICS_SPEC)
            answer_value = {'Init': [{
                        "item_name": "boot_time",
                        "item_type": "string",
                        "item_optional": False,
                        # Use a different default so we can check it below
                        "item_default": "2013-01-01T00:00:01Z",
                        "item_title": "Boot time",
                        "item_description": "dummy desc",
                        "item_format": "date-time"
                        }]}
            return answer_value

        self.stats = MyStats()
        self.stats.cc_session.rpc_call = __check_rpc_call

        self.stats.update_modules()

        # Stats is always incorporated.  For others, only the ones returned
        # by group_recvmsg() above is available.
        self.assertTrue('Stats' in self.stats.modules)
        self.assertTrue('Init' in self.stats.modules)
        self.assertFalse('Dummy' in self.stats.modules)

        my_statistics_data = stats.get_spec_defaults(
            self.stats.modules['Stats'].get_statistics_spec())
        self.assertTrue('report_time' in my_statistics_data)
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertTrue('last_update_time' in my_statistics_data)
        self.assertTrue('timestamp' in my_statistics_data)
        self.assertTrue('lname' in my_statistics_data)
        self.assertEqual(my_statistics_data['report_time'],
                         self.const_default_datetime)
        self.assertEqual(my_statistics_data['boot_time'],
                         self.const_default_datetime)
        self.assertEqual(my_statistics_data['last_update_time'],
                         self.const_default_datetime)
        self.assertEqual(my_statistics_data['timestamp'], 0.0)
        self.assertEqual(my_statistics_data['lname'], "")
        my_statistics_data = stats.get_spec_defaults(
            self.stats.modules['Init'].get_statistics_spec())
        self.assertTrue('boot_time' in my_statistics_data)
        self.assertEqual(my_statistics_data['boot_time'],
                         "2013-01-01T00:00:01Z")

        # Error case
        def __raise_on_rpc_call(x, y):
            raise isc.config.RPCError(99, 'error')
        orig_parse_answer = stats.isc.config.ccsession.parse_answer
        self.stats.cc_session.rpc_call = __raise_on_rpc_call
        self.assertRaises(stats.StatsError, self.stats.update_modules)

    def test_get_statistics_data(self):
        """Confirm the behavior of Stats.get_statistics_data().

        It should first call update_modules(), and then retrieve the requested
        data from statistics_data.  We confirm this by fake update_modules()
        where we set the expected data in statistics_data.

        """
        self.stats = MyStats()
        def __faked_update_modules():
            self.stats.statistics_data = { \
                'Stats': {
                    'report_time': self.const_default_datetime,
                    'boot_time': None,
                    'last_update_time': None,
                    'timestamp': 0.0,
                    'lname': 'dummy name'
                    },
                'Init': { 'boot_time': None }
                }

        self.stats.update_modules = __faked_update_modules

        my_statistics_data = self.stats.get_statistics_data()
        self.assertTrue('Stats' in my_statistics_data)
        self.assertTrue('Init' in my_statistics_data)
        self.assertTrue('boot_time' in my_statistics_data['Init'])

        my_statistics_data = self.stats.get_statistics_data(owner='Stats')
        self.assertTrue('Stats' in my_statistics_data)
        self.assertTrue('report_time' in my_statistics_data['Stats'])
        self.assertTrue('boot_time' in my_statistics_data['Stats'])
        self.assertTrue('last_update_time' in my_statistics_data['Stats'])
        self.assertTrue('timestamp' in my_statistics_data['Stats'])
        self.assertTrue('lname' in my_statistics_data['Stats'])
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          owner='Foo')

        my_statistics_data = self.stats.get_statistics_data(
            owner='Stats', name='report_time')
        self.assertEqual(my_statistics_data['Stats']['report_time'],
                         self.const_default_datetime)

        my_statistics_data = self.stats.get_statistics_data(
            owner='Stats', name='boot_time')
        self.assertTrue('boot_time' in my_statistics_data['Stats'])

        my_statistics_data = self.stats.get_statistics_data(
            owner='Stats', name='last_update_time')
        self.assertTrue('last_update_time' in my_statistics_data['Stats'])

        my_statistics_data = self.stats.get_statistics_data(
            owner='Stats', name='timestamp')
        self.assertEqual(my_statistics_data['Stats']['timestamp'], 0.0)

        my_statistics_data = self.stats.get_statistics_data(
            owner='Stats', name='lname')
        self.assertTrue(len(my_statistics_data['Stats']['lname']) >0)
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          owner='Stats', name='Bar')
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          owner='Foo', name='Bar')
        self.assertRaises(stats.StatsError, self.stats.get_statistics_data,
                          name='Bar')

    def test_update_statistics_data(self):
        """test for list-type statistics"""
        self.stats = MyStats()
        _test_exp1 = {
              'zonename': 'test1.example',
              'queries.tcp': 5,
              'queries.udp': 4
            }
        _test_exp2 = {
              'zonename': 'test2.example',
              'queries.tcp': 3,
              'queries.udp': 2
            }
        _test_exp3 = {}
        _test_exp4 = {
              'queries.udp': 4
            }
        _test_exp5_1 = {
              'queries.perzone': [
                { },
                {
                  'queries.udp': 9876
                }
              ]
            }
        _test_exp5_2 = {
              'queries.perzone[1]/queries.udp':
                  isc.cc.data.find(_test_exp5_1,
                                   'queries.perzone[1]/queries.udp')
            }
        # Success cases
        self.assertEqual(self.stats.statistics_data['Stats']['lname'],
                         self.stats.cc_session.lname)
        self.stats.update_statistics_data(
            'Stats', self.stats.cc_session.lname,
            {'lname': 'foo@bar'})
        self.assertEqual(self.stats.statistics_data['Stats']['lname'],
                         'foo@bar')
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'queries.perzone': [_test_exp1]}))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['queries.perzone'],\
                             [_test_exp1])
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'queries.perzone': [_test_exp2]}))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['queries.perzone'],\
                             [_test_exp2])
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'queries.perzone': [_test_exp1,_test_exp2]}))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['queries.perzone'],
                         [_test_exp1,_test_exp2])
        # differential update
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'queries.perzone': [_test_exp3,_test_exp4]}))
        _new_data = stats.merge_oldnew(_test_exp2,_test_exp4)
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['queries.perzone'], \
                             [_test_exp1,_new_data])
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', _test_exp5_2))
        _new_data = stats.merge_oldnew(_new_data,
                                       _test_exp5_1['queries.perzone'][1])
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['queries.perzone'], \
                             [_test_exp1,_new_data])
        # Error cases
        self.assertEqual(self.stats.update_statistics_data('Stats', None,
                                                           {'lname': 0.0}),
                         ['0.0 should be a string'])
        self.assertEqual(self.stats.update_statistics_data('Dummy', None,
                                                           {'foo': 'bar'}),
                         ['unknown module name: Dummy'])
        self.assertEqual(self.stats.update_statistics_data(
                'Auth', 'foo1', {'queries.perzone': [None]}), ['None should be a map'])

    def test_update_statistics_data_pt2(self):
        """test for named_set-type statistics"""
        self.stats = MyStats()
        _test_exp1 = \
            { 'test10.example': { 'queries.tcp': 5, 'queries.udp': 4 } }
        _test_exp2 = \
            { 'test20.example': { 'queries.tcp': 3, 'queries.udp': 2 } }
        _test_exp3 = {}
        _test_exp4 = { 'test20.example': { 'queries.udp': 4 } }
        _test_exp5_1 = { 'test10.example': { 'queries.udp': 5432 } }
        _test_exp5_2 ={
              'nds_queries.perzone/test10.example/queries.udp':
                  isc.cc.data.find(_test_exp5_1, 'test10.example/queries.udp')
            }
        _test_exp6 = { 'foo/bar':  'brabra' }
        _test_exp7 = { 'foo[100]': 'bar' }
        # Success cases
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'nds_queries.perzone': _test_exp1}))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],\
                             _test_exp1)
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'nds_queries.perzone': _test_exp2}))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],\
                         dict(_test_exp1,**_test_exp2))
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'nds_queries.perzone':
                                 dict(_test_exp1, **_test_exp2)}))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],
                         dict(_test_exp1, **_test_exp2))
        # differential update
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', {'nds_queries.perzone':
                                 dict(_test_exp3, **_test_exp4)}))
        _new_val = dict(_test_exp1,
                        **stats.merge_oldnew(_test_exp2,_test_exp4))
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],\
                             _new_val)
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo1', _test_exp5_2))
        _new_val = stats.merge_oldnew(_new_val, _test_exp5_1)
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],\
                             _new_val)
        self.assertIsNone(self.stats.update_statistics_data(
            'Auth', 'foo2', _test_exp5_2))
        _new_val = stats.merge_oldnew(_new_val, _test_exp5_1)
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo2']['nds_queries.perzone'],\
                             _test_exp5_1)
        # Error cases
        self.assertEqual(self.stats.update_statistics_data(
                'Auth', 'foo1', {'nds_queries.perzone': None}),
                         ['None should be a map'])
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],\
                             _new_val)
        self.assertEqual(self.stats.update_statistics_data(
                'Auth', 'foo1', _test_exp6), ['unknown item foo'])
        self.assertEqual(self.stats.statistics_data_bymid['Auth']\
                             ['foo1']['nds_queries.perzone'],\
                             _new_val)
        self.assertEqual(self.stats.update_statistics_data(
                'Init', 'bar1', _test_exp7), ["KeyError: 'foo'"])
        self.assertEqual(self.stats.update_statistics_data(
                'Foo', 'foo1', _test_exp6), ['unknown module name: Foo'])

    def test_update_statistics_data_withmid(self):
        self.stats = MyStats()

        # This test relies on existing statistics data at the Stats object.
        # This version of test prepares the data using the do_polling() method;
        # that's a bad practice because a unittest for a method
        # (update_statistics_data) would heavily depend on details of another
        # method (do_polling).  However, there's currently no direct test
        # for do_polling (which is also bad), so we still keep that approach,
        # partly for testing do_polling indirectly.  #2781 should provide
        # direct test for do_polling, with which this test scenario should
        # also be changed to be more stand-alone.

        # We use the knowledge of what kind of messages are sent via
        # do_polling, and return the following faked answer directly.
        self.stats._answers = [
            # Answer for "show_processes"
            (create_answer(0, [[1034, 'b10-auth-1', 'Auth'],
                               [1035, 'b10-auth-2', 'Auth']]),  None),
            # Answers for "getstats".  2 for Auth instances and 1 for Init.
            # we return some bogus values for Init, but the rest of the test
            # doesn't need it, so it's okay.
            (create_answer(0, self.stats._auth_sdata), {'from': 'auth1'}),
            (create_answer(0, self.stats._auth_sdata), {'from': 'auth2'}),
            (create_answer(0, self.stats._auth_sdata), {'from': 'auth3'})
            ]
        # do_polling calls update_modules internally; in our scenario there's
        # no change in modules, so we make it no-op.
        self.stats.update_modules = lambda: None
        # Now call do_polling.
        self.stats.do_polling()

        # samples of query number
        bar1_tcp = 1001
        bar2_tcp = 2001
        bar3_tcp = 1002
        bar3_udp = 1003
        # two auth instances invoked, so we double the pre-set stat values
        sum_qtcp = self.stats._queries_tcp * 2
        sum_qudp = self.stats._queries_udp * 2
        self.stats.update_statistics_data('Auth', "bar1@foo",
                                          {'queries.tcp': bar1_tcp})
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'],
                         bar1_tcp + sum_qtcp)
        self.assertTrue('Auth' in self.stats.statistics_data_bymid)
        self.assertTrue('bar1@foo' in self.stats.statistics_data_bymid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bymid
                        ['Auth']['bar1@foo'])
        self.assertEqual(self.stats.statistics_data_bymid['Auth']['bar1@foo'],
                         {'queries.tcp': bar1_tcp})
        # check consolidation of statistics data even if there is
        # non-existent mid of Auth
        self.stats.update_statistics_data('Auth', "bar2@foo",
                                          {'queries.tcp': bar2_tcp})
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'],
                         bar1_tcp + bar2_tcp + sum_qtcp)
        self.assertTrue('Auth' in self.stats.statistics_data_bymid)
        self.assertTrue('bar1@foo' in self.stats.statistics_data_bymid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bymid['Auth']['bar1@foo'])
        self.assertEqual(self.stats.statistics_data_bymid['Auth']['bar1@foo'],
                         {'queries.tcp': bar1_tcp})
        self.assertEqual(self.stats.statistics_data_bymid['Auth']['bar2@foo'],
                         {'queries.tcp': bar2_tcp})
        # kill running Auth but the statistics data doesn't change
        self.stats.update_statistics_data()
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertTrue('queries.udp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'],
                         bar1_tcp + bar2_tcp + sum_qtcp)
        self.assertEqual(self.stats.statistics_data['Auth']['queries.udp'],
                         sum_qudp)
        self.assertTrue('Auth' in self.stats.statistics_data_bymid)
        # restore statistics data of killed auth
        self.stats.update_statistics_data('Auth',
                                          "bar1@foo",
                                          {'queries.tcp': bar1_tcp})
        # set another mid of Auth
        self.stats.update_statistics_data('Auth',
                                          "bar3@foo",
                                          {'queries.tcp':bar3_tcp,
                                           'queries.udp':bar3_udp})
        self.assertTrue('Auth' in self.stats.statistics_data)
        self.assertTrue('queries.tcp' in self.stats.statistics_data['Auth'])
        self.assertTrue('queries.udp' in self.stats.statistics_data['Auth'])
        self.assertEqual(self.stats.statistics_data['Auth']['queries.tcp'],
                         bar1_tcp + bar2_tcp + bar3_tcp + sum_qtcp)
        self.assertEqual(self.stats.statistics_data['Auth']['queries.udp'],
                         bar3_udp + sum_qudp)
        self.assertTrue('Auth' in self.stats.statistics_data_bymid)
        self.assertTrue('bar1@foo' in self.stats.statistics_data_bymid['Auth'])
        self.assertTrue('bar3@foo' in self.stats.statistics_data_bymid['Auth'])
        self.assertTrue('queries.tcp' in self.stats.statistics_data_bymid['Auth']['bar1@foo'])
        self.assertTrue('queries.udp' in self.stats.statistics_data_bymid['Auth']['bar3@foo'])
        self.assertTrue('queries.udp' in self.stats.statistics_data_bymid['Auth']['bar3@foo'])
        self.assertEqual(self.stats.statistics_data_bymid['Auth']['bar1@foo']['queries.tcp'], bar1_tcp)
        self.assertEqual(self.stats.statistics_data_bymid['Auth']['bar3@foo']['queries.tcp'], bar3_tcp)
        self.assertEqual(self.stats.statistics_data_bymid['Auth']['bar3@foo']['queries.udp'], bar3_udp)

    def test_config(self):
        orig_get_timestamp = stats.get_timestamp
        stats.get_timestamp = lambda : self.const_timestamp
        stat = MyStats()

        # test updating poll-interval
        self.assertEqual(stat.config['poll-interval'], 60)
        self.assertEqual(stat.get_interval(), 60)
        self.assertEqual(stat.next_polltime, self.const_timestamp + 60)
        self.assertEqual(stat.config_handler({'poll-interval': 120}),
                         isc.config.create_answer(0))
        self.assertEqual(stat.config['poll-interval'], 120)
        self.assertEqual(stat.get_interval(), 120)
        self.assertEqual(stat.next_polltime, self.const_timestamp + 120)
        stats.get_timestamp = orig_get_timestamp
        self.assertEqual(stat.config_handler({'poll-interval': "foo"}),
                         isc.config.create_answer(1, 'foo should be an integer'))
        self.assertEqual(stat.config_handler({'poll-interval': -1}),
                         isc.config.create_answer(1, 'Negative integer ignored'))
        # unknown item
        self.assertEqual(
            stat.config_handler({'_UNKNOWN_KEY_': None}),
            isc.config.ccsession.create_answer(
                1, "unknown item _UNKNOWN_KEY_"))
        # test no change if zero interval time
        self.assertEqual(stat.config_handler({'poll-interval': 0}),
                         isc.config.create_answer(0))
        self.assertEqual(stat.config['poll-interval'], 0)

        # see the comment for test_update_statistics_data_withmid.  We abuse
        # do_polling here, too.  With #2781 we should make it more direct.
        stat._answers = [\
            # Answer for "show_processes"
            (create_answer(0, []),  None),
            # Answers for "getstats" for Init (the other one for Auth, but
            # that doesn't matter for this test)
            (create_answer(0, stat._init_sdata), {'from': 'init'}),
            (create_answer(0, stat._init_sdata), {'from': 'init'})
            ]
        stat.update_modules = lambda: None

        self.assertEqual(
            self.__send_command(
                stat, 'show',
                params={ 'owner' : 'Init', 'name'  : 'boot_time' }),
            (0, {'Init': {'boot_time': self.const_datetime}}))

    def test_commands(self):
        self.stats = MyStats()

        # status
        self.assertEqual(self.stats.command_status(),
                isc.config.create_answer(
                0, "Stats is up. (PID " + str(os.getpid()) + ")"))

        # shutdown
        self.stats.running = True
        self.assertEqual(self.stats.command_shutdown(),
                         isc.config.create_answer(0))
        self.assertFalse(self.stats.running)

    def test_command_show_error(self):
        self.stats = MyStats()
        self.assertEqual(self.stats.command_show(owner='Foo', name=None),
                         isc.config.create_answer(
                1,
                "specified arguments are incorrect: owner: Foo, name: None"))
        self.assertEqual(self.stats.command_show(owner='Foo', name='_bar_'),
                         isc.config.create_answer(
                1,
                "specified arguments are incorrect: owner: Foo, name: _bar_"))
        self.assertEqual(self.stats.command_show(owner='Foo', name='bar'),
                         isc.config.create_answer(
                1,
                "specified arguments are incorrect: owner: Foo, name: bar"))

    def test_command_show_auth(self):
        self.stats = MyStats()
        self.stats.update_modules = lambda: None

        # Test data borrowed from test_update_statistics_data_withmid
        self.stats._answers = [
            (create_answer(0, [[1034, 'b10-auth-1', 'Auth'],
                               [1035, 'b10-auth-2', 'Auth']]),  None),
            (create_answer(0, self.stats._auth_sdata), {'from': 'auth1'}),
            (create_answer(0, self.stats._auth_sdata), {'from': 'auth2'}),
            (create_answer(0, self.stats._auth_sdata), {'from': 'auth3'})
            ]

        num_instances = 2
        sum_qtcp = 0
        sum_qudp = 0
        sum_qtcp_perzone1 = 0
        sum_qudp_perzone1 = 0
        sum_qtcp_perzone2 = 4 * num_instances
        sum_qudp_perzone2 = 3 * num_instances
        sum_qtcp_nds_perzone10 = 0
        sum_qudp_nds_perzone10 = 0
        sum_qtcp_nds_perzone20 = 4 * num_instances
        sum_qudp_nds_perzone20 = 3 * num_instances

        self.maxDiff = None
        for a in (0, num_instances):
            sum_qtcp += self.stats._queries_tcp
            sum_qudp += self.stats._queries_udp
            sum_qtcp_perzone1 += self.stats._queries_per_zone[0]['queries.tcp']
            sum_qudp_perzone1 += self.stats._queries_per_zone[0]['queries.udp']
            sum_qtcp_nds_perzone10 += \
                self.stats._nds_queries_per_zone['test10.example']['queries.tcp']
            sum_qudp_nds_perzone10 += \
                self.stats._nds_queries_per_zone['test10.example']['queries.udp']

        self.assertEqual(self.stats.command_show(owner='Auth'),
                         isc.config.create_answer(
                0, {'Auth':{ 'queries.udp': sum_qudp,
                     'queries.tcp': sum_qtcp,
                     'queries.perzone': [{ 'zonename': 'test1.example',
                                           'queries.udp': sum_qudp_perzone1,
                                           'queries.tcp': sum_qtcp_perzone1 },
                                         { 'zonename': 'test2.example',
                                           'queries.udp': sum_qudp_perzone2,
                                           'queries.tcp': sum_qtcp_perzone2 }
                                         ],
                     'nds_queries.perzone': { 'test10.example' : {
                                              'queries.udp': sum_qudp_nds_perzone10,
                                              'queries.tcp': sum_qtcp_nds_perzone10 },
                                              'test20.example' : {
                                              'queries.udp': sum_qudp_nds_perzone20,
                                              'queries.tcp': sum_qtcp_nds_perzone20 }
                             }}}))
        self.assertEqual(self.stats.command_show(owner='Auth', name='queries.udp'),
                         isc.config.create_answer(
                0, {'Auth': {'queries.udp': sum_qudp}}))
        self.assertEqual(self.stats.command_show(owner='Auth', name='queries.perzone'),
                         isc.config.create_answer(
                0, {'Auth': {'queries.perzone': [
                            { 'zonename': 'test1.example',
                              'queries.udp': sum_qudp_perzone1,
                              'queries.tcp': sum_qtcp_perzone1 },
                            { 'zonename': 'test2.example',
                              'queries.udp': sum_qudp_perzone2,
                              'queries.tcp': sum_qtcp_perzone2 }]}}))
        self.assertEqual(self.stats.command_show(owner='Auth', name='nds_queries.perzone'),
                         isc.config.create_answer(
                0, {'Auth': {'nds_queries.perzone': {
                            'test10.example': {
                                'queries.udp': sum_qudp_nds_perzone10,
                                'queries.tcp': sum_qtcp_nds_perzone10 },
                            'test20.example': {
                                'queries.udp': sum_qudp_nds_perzone20,
                                'queries.tcp': sum_qtcp_nds_perzone20 }}}}))

    def test_command_show_stats(self):
        self.stats = MyStats()
        orig_get_datetime = stats.get_datetime
        orig_get_timestamp = stats.get_timestamp
        stats.get_datetime = lambda x=None: self.const_datetime
        stats.get_timestamp = lambda : self.const_timestamp
        self.assertEqual(self.stats.command_show(owner='Stats',
                                                 name='report_time'),
                         isc.config.create_answer(
                0, {'Stats': {'report_time':self.const_datetime}}))
        self.assertEqual(self.stats.command_show(owner='Stats',
                                                 name='timestamp'),
                         isc.config.create_answer(
                0, {'Stats': {'timestamp':self.const_timestamp}}))
        stats.get_datetime = orig_get_datetime
        stats.get_timestamp = orig_get_timestamp
        self.stats.do_polling = lambda : None
        self.stats.modules[self.stats.module_name] = \
            isc.config.module_spec.ModuleSpec(
            { "module_name": self.stats.module_name, "statistics": [] } )
        self.assertRaises(
            stats.StatsError, self.stats.command_show,
            owner=self.stats.module_name, name='bar')

    def test_command_showchema(self):
        self.stats = MyStats()
        (rcode, value) = isc.config.ccsession.parse_answer(
            self.stats.command_showschema())
        self.assertEqual(rcode, 0)
        self.assertEqual(len(value), 3)
        self.assertTrue('Stats' in value)
        self.assertTrue('Init' in value)
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

        schema = value['Init']
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
        self.assertEqual(len(schema), 4)
        for item in schema:
            if item['item_type'] == 'list' or item['item_type'] == 'named_set':
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
        self.assertFalse('Init' in value)
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
        self.assertFalse('Init' in value)
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
                        },
                    {
                        "item_name": "nds_queries.perzone",
                        "item_type": "named_set",
                        "item_optional": False,
                        "item_default": {
                            "test10.example" : {
                                "queries.udp" : 1,
                                "queries.tcp" : 2
                            },
                            "test20.example" : {
                                "queries.udp" : 3,
                                "queries.tcp" : 4
                            }
                        },
                        "item_title": "Queries per zone",
                        "item_description": "Queries per zone",
                        "named_set_item_spec": {
                            "item_name": "zonename",
                            "item_type": "map",
                            "item_optional": False,
                            "item_default": {},
                            "item_title": "Zonename",
                            "item_description": "Zonename",
                            "map_item_spec": [
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
        self.assertEqual(self.stats.command_showschema(owner='Auth', name='nds_queries.perzone'),
                         isc.config.create_answer(
                0, {'Auth':[{
                    "item_name": "nds_queries.perzone",
                    "item_type": "named_set",
                    "item_optional": False,
                    "item_default": {
                        "test10.example" : {
                            "queries.udp" : 1,
                            "queries.tcp" : 2
                        },
                        "test20.example" : {
                            "queries.udp" : 3,
                            "queries.tcp" : 4
                        }
                    },
                    "item_title": "Queries per zone",
                    "item_description": "Queries per zone",
                    "named_set_item_spec": {
                        "item_name": "zonename",
                        "item_type": "map",
                        "item_optional": False,
                        "item_default": {},
                        "item_title": "Zonename",
                        "item_description": "Zonename",
                        "map_item_spec": [
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

    def test_polling_init(self):
        """check statistics data of 'Init'."""

        stat = MyStats()
        # At this point 'stat' is initialized with statistics for Stats,
        # Init and Auth modules.  In this test, we only need to check for Init
        # statistics, while do_polling() can ask for module statistics in an
        # unpredictable order (if hash randomization is enabled, which is
        # the case by default for Python 3.3).  To make it predictable and
        # ensure the prepared answer doesn't cause disruption, we remove the
        # information for the Auth module for this test.
        del stat.statistics_data['Auth']

        stat.update_modules = lambda: None

        stat._answers = [
            # Answer for "show_processes"
            (create_answer(0, []),  None),
            # Answers for "getstats" for Init (type of boot_time is invalid)
            (create_answer(0, {'boot_time': self.const_datetime}),
             {'from': 'init'}),
            ]

        stat.do_polling()
        self.assertEqual(
            stat.statistics_data_bymid['Init']['init'],
            {'boot_time': self.const_datetime})

    def test_polling_consolidate(self):
        """check statistics data of multiple instances of same module."""
        stat = MyStats()
        stat.update_modules = lambda: None

        # Test data borrowed from test_update_statistics_data_withmid
        stat._answers = [
            (create_answer(0, [[1034, 'b10-auth-1', 'Auth'],
                               [1035, 'b10-auth-2', 'Auth']]),  None),
            (create_answer(0, stat._auth_sdata), {'from': 'auth1'}),
            (create_answer(0, stat._auth_sdata), {'from': 'auth2'}),
            (create_answer(0, stat._auth_sdata), {'from': 'auth3'})
            ]

        stat.do_polling()

        # check statistics data of each 'Auth' instances.  expected data
        # for 'nds_queries.perzone' is special as it needs data merge.
        self.assertEqual(2, len(stat.statistics_data_bymid['Auth'].values()))
        for s in stat.statistics_data_bymid['Auth'].values():
            self.assertEqual(
                s, {'queries.perzone': stat._auth_sdata['queries.perzone'],
                    'nds_queries.perzone': stat._nds_queries_per_zone,
                    'queries.tcp': stat._auth_sdata['queries.tcp'],
                    'queries.udp': stat._auth_sdata['queries.udp']})

        # check consolidation of statistics data of the auth instances.
        # it's union of the reported data and the spec default.
        n = len(stat.statistics_data_bymid['Auth'].values())
        self.maxDiff = None
        self.assertEqual(
            stat.statistics_data['Auth'],
            {'queries.perzone': [
                    {'zonename': 'test1.example',
                     'queries.tcp': 5 * n,
                     'queries.udp': 4 * n},
                    {'zonename': 'test2.example',
                     'queries.tcp': 4 * n,
                     'queries.udp': 3 * n},
                    ],
             'nds_queries.perzone': {
                    'test10.example': {
                        'queries.tcp': 5 * n,
                        'queries.udp': 4 * n
                        },
                    'test20.example': {
                        'queries.tcp': 4 * n,
                        'queries.udp': 3 * n
                        },
                    },
             'queries.tcp': 3 * n,
             'queries.udp': 2 * n})

    def test_polling_stats(self):
        """Check statistics data of 'Stats'

        This is actually irrelevant to do_polling(), but provided to
        compatibility of older tests.

        """
        stat = MyStats()
        self.assertEqual(len(stat.statistics_data['Stats']), 5)
        self.assertTrue('boot_time' in stat.statistics_data['Stats'])
        self.assertTrue('last_update_time' in stat.statistics_data['Stats'])
        self.assertTrue('report_time' in stat.statistics_data['Stats'])
        self.assertTrue('timestamp' in stat.statistics_data['Stats'])
        self.assertEqual(stat.statistics_data['Stats']['lname'],
                         stat.mccs._session.lname)

    def test_refresh_statistics_broken_statistics_data(self):
        """Test _refresh_statistics() doesn't incorporate broken statistics data
        """
        stat = MyStats()
        # check default statistics data of 'Init'
        self.assertEqual(
            {'boot_time': self.const_default_datetime},
            stat.statistics_data['Init'])
        last_update_time = stat.statistics_data['Stats']['last_update_time']
        # _refresh_statistics() should ignore the invalid statistics_data(type
        # of boot_time is invalid); default data shouldn't be replaced.
        arg = [('Init', 'lname', {'boot_time': 1})]
        stat._refresh_statistics(arg)
        self.assertEqual(
            {'boot_time': self.const_default_datetime},
            stat.statistics_data['Init'])
        # 'last_update_time' doesn't change
        self.assertEqual(
            last_update_time,
            stat.statistics_data['Stats']['last_update_time'])

class Z_TestOSEnv(unittest.TestCase):
    # Running this test would break logging setting.  To prevent it from
    # affecting other tests we use the same workaround as Z_TestOSEnv in
    # stats-httpd_test.py.
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

if __name__ == "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
