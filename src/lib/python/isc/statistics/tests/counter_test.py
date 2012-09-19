# Copyright (C) 2012  Internet Systems Consortium.
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

'''Tests for isc.statistics.counter'''

import unittest
import threading
from datetime import timedelta
import isc.config
import xfrout
import xfrin

TEST_ZONE_NAME_STR = "example.com."

from isc.statistics import counter

def setup_functor(event, cycle, functor, *args):
    """Waits until the event is started, and then invokes the functor
    by times of the cycle with args."""
    event.wait()
    for i in range(cycle): functor(*args)

def start_functor(number, cycle, functor, *args):
    """Creates the threads of the number and makes them start. Sets
    the event and waits until these threads are finished."""
    threads = []
    event = threading.Event()
    for i in range(number):
        threads.append(threading.Thread(\
                target=setup_functor, \
                    args=(event, cycle, functor,) + args))
    for th in threads: th.start()
    event.set()
    for th in threads: th.join()

class TestCounter(unittest.TestCase):
    def setUp(self):
        self.counter = counter.Counter()
        self._statistics_data = {}
        self._start_time = {}
        self._counter_name = "counter"
        self._timer_name = "seconds"
        self._statistics_spec = [{ "item_name": self._counter_name,
                                   "item_type": "integer",
                                   "item_optional": False,
                                   "item_default": 0 },
                                 { "item_name": self._timer_name,
                                   "item_type": "real",
                                   "item_optional": False,
                                   "item_default": 0.0 }]

    def test_clear_counters(self):
        self.counter._statistics_data = {'counter': 1}
        self.counter.clear_counters()
        self.assertEqual(self.counter._statistics_data,
                         {})

    def test_enablediable(self):
        self.assertFalse(self.counter._disabled)
        self.counter.disable()
        self.assertTrue(self.counter._disabled)
        self.counter.enable()
        self.assertFalse(self.counter._disabled)

    def test_add_counter_normal(self):
        element = {'counter' : 1}
        self.assertEqual(\
            counter._add_counter(element, [], 'counter'), 1)

    def test_add_counter_wrongspec(self):
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          counter._add_counter,
                          {}, [], 'counter')

    def test_add_counter_empty(self):
        self.assertEqual(\
            counter._add_counter(
                {},
                [ { 'item_name' : 'counter',
                    'item_type' : 'integer',
                    'item_default' : 0 } ],
                'counter'), 0)

    def test_add_counter_empty_namedset(self):
        elem = {}
        spec = [ { 'item_name': 'dirs',
                    'item_type': 'named_set',
                    'named_set_item_spec': {
                            'item_name': 'dir',
                            'item_type': 'map',
                            'map_item_spec': [
                                { 'item_name': 'counter1',
                                  'item_type': 'integer',
                                  'item_default': 0 },
                                { 'item_name': 'counter2',
                                  'item_type': 'integer',
                                  'item_default': 0 } ]}
                   }]
        self.assertEqual(\
            counter._add_counter(elem, spec, 'dirs/foo/counter1'), 0)
        self.assertEqual(\
            counter._add_counter(elem, spec, 'dirs/bar/counter2'), 0)

    def test_timer(self):
        t1 = counter._start_timer()
        t2 = t1 - timedelta(seconds=1)
        self.assertEqual((t1 - t2).seconds, 1)
        elem = {}
        spec = [{ 'item_name': 'time',
                  'item_type': 'real',
                  'item_default': 0.0 }]
        counter._stop_timer(t2, elem, spec, 'time')
        self.assertGreater(counter._get_counter(elem,'time'), 1)

    def test_rasing_incrementers(self):
        """ use Thread"""
        number = 3    # number of the threads
        cycle = 10000 # number of counting per thread
        self.counter._statistics_data = self._statistics_data
        self.counter._statistics_spec = self._statistics_spec
        self._start_time = counter._start_timer()
        start_functor(number, cycle, self.counter._incrementer,
                      self._counter_name)
        counter._stop_timer(self._start_time,
                            self._statistics_data,
                            self._statistics_spec,
                            self._timer_name)
        self.assertEqual(
            counter._get_counter(self._statistics_data,
                                 self._counter_name),
            number * cycle)
        self.assertGreater(
            counter._get_counter(self._statistics_data,
                                 self._timer_name), 0)

class BaseTestXfrCounter():

    def test_perzone_counters(self):
        # for per-zone counters
        for counter_name in self._zones_item_list:
            if counter_name.find('time_to_') == 0:
                isc.cc.data.set(\
                    self._statistics_data,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  TEST_ZONE_NAME_STR,
                                  counter_name), 0.0)
                continue
            incrementer = self.counter._to_global\
                ['inc_%s' % counter_name]
            getter = self.counter._to_global\
                ['get_%s' % counter_name]
            incrementer(TEST_ZONE_NAME_STR)
            self.assertEqual(getter(TEST_ZONE_NAME_STR), 1)
            # checks disable/enable
            self.counter.disable()
            incrementer(TEST_ZONE_NAME_STR)
            self.assertEqual(getter(TEST_ZONE_NAME_STR), 1)
            self.counter.enable()
            incrementer(TEST_ZONE_NAME_STR)
            self.assertEqual(getter(TEST_ZONE_NAME_STR), 2)
            for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                isc.cc.data.set(\
                    self._statistics_data,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  zone_str,
                                  counter_name), 2)
            # checks other counters
            for counter_name in self._zones_item_list:
                getter = self.counter._to_global\
                    ['get_%s' % counter_name]
                self.assertGreaterEqual(getter(TEST_ZONE_NAME_STR), 0)
        self.check_dump_statistics()

    def test_xfrrunning_counters(self):
        # for counters of xfer running
        for counter_name in self._xfrrunning_names:
            incrementer = self.counter._to_global\
                ['inc_%s' % counter_name]
            getter = self.counter._to_global\
                ['get_%s' % counter_name]
            decrementer = self.counter._to_global\
                ['dec_%s' % counter_name]
            incrementer()
            self.assertEqual(getter(), 1)
            decrementer()
            self.assertEqual(getter(), 0)
            # checks disable/enable
            self.counter.disable()
            incrementer()
            self.assertEqual(getter(), 0)
            self.counter.enable()
            incrementer()
            self.assertEqual(getter(), 1)
            self.counter.disable()
            decrementer()
            self.assertEqual(getter(), 1)
            self.counter.enable()
            decrementer()
            self.assertEqual(getter(), 0)
            self._statistics_data[counter_name] = 0
        self.check_dump_statistics()

    def check_dump_statistics(self):
        """Checks no differences between the value returned from
        dump_statistics() and locally collected statistics data. Also
        checks the result isn't changed even after the method is
        invoked twice. Finally checks it is valid for the the
        statistics spec."""
        self.assertEqual(self.counter.dump_statistics(),
                         self._statistics_data)
        # Idempotency check
        self.assertEqual(self.counter.dump_statistics(),
                         self._statistics_data)
        self.assertTrue(self._module_spec.validate_statistics(
                False, self._statistics_data))

class TestXfroutCounter(unittest.TestCase, BaseTestXfrCounter):

    def setUp(self):
        self._module_spec = isc.config.module_spec_from_file(\
            xfrout.SPECFILE_LOCATION)
        self._statistics_spec = \
            self._module_spec.get_statistics_spec()
        self.counter = \
            counter.XfroutCounter(self._module_spec)
        self._statistics_data = {}
        self._entire_server    = self.counter._entire_server
        self._perzone_prefix   = self.counter._perzone_prefix
        self._xfrrunning_names = self.counter._xfrrunning_names
        self._unixsocket_names = self.counter._unixsocket_names
        self._started = threading.Event()
        self._zones_item_list   = self.counter._zones_item_list

    def test_unixsocket_counters(self):
        # for unixsocket counters
        for counter_name in self._unixsocket_names:
            incrementer = self.counter._to_global\
                ['inc_unixsocket_%s' % counter_name]
            getter = self.counter._to_global\
                ['get_unixsocket_%s' % counter_name]
            incrementer()
            self.assertEqual(getter(), 1)
            # checks disable/enable
            self.counter.disable()
            incrementer()
            self.assertEqual(getter(), 1)
            self.counter.enable()
            incrementer()
            self.assertEqual(getter(), 2)
            isc.cc.data.set(
                self._statistics_data,
                'socket/unixdomain/%s' % counter_name, 2)
        self.check_dump_statistics()

class TestXfrinCounter(unittest.TestCase, BaseTestXfrCounter):

    def setUp(self):
        self._module_spec = isc.config.module_spec_from_file(\
            xfrin.SPECFILE_LOCATION)
        self._statistics_spec = \
            self._module_spec.get_statistics_spec()
        self._statistics_data = {}
        self.counter = \
            counter.XfrinCounter(self._module_spec)
        self._entire_server    = self.counter._entire_server
        self._perzone_prefix   = self.counter._perzone_prefix
        self._xfrrunning_names = self.counter._xfrrunning_names
        self._zones_item_list   = self.counter._zones_item_list
        self._started = threading.Event()

    def test_perzone_timers(self):
        # for timer counters
        for counter_name in self._zones_item_list:
            if counter_name.find('time_to_') == -1:
                isc.cc.data.set(\
                    self._statistics_data,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  TEST_ZONE_NAME_STR,
                                  counter_name), 0)
                continue
            starter = self.counter._to_global\
                ['start_%s' % counter_name]
            stopper = self.counter._to_global\
                ['stop_%s' % counter_name]
            getter = self.counter._to_global\
                ['get_%s' % counter_name]
            starter(TEST_ZONE_NAME_STR)
            stopper(TEST_ZONE_NAME_STR)
            self.assertGreater(getter(TEST_ZONE_NAME_STR), 0)
            sec = getter(TEST_ZONE_NAME_STR)
            for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                isc.cc.data.set(\
                    self._statistics_data,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  zone_str,
                                  counter_name), sec)
            # twice exec stopper, then second is not changed
            stopper(TEST_ZONE_NAME_STR)
            self.assertEqual(getter(TEST_ZONE_NAME_STR), sec)
        self.check_dump_statistics()

if __name__== "__main__":
    unittest.main()
