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
import os
import imp
import isc.config

TEST_ZONE_NAME_STR = "example.com."
TESTDATA_SRCDIR = os.getenv("TESTDATASRCDIR")

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

class TestBasicMethods(unittest.TestCase):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec1.spec'

    def setUp(self):
        self.counter = counter.Counter(self.TEST_SPECFILE_LOCATION)

    def tearDown(self):
        self.counter.clear_counters()

    def test_clear_counters(self):
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counter.get, 'counter')
        self.counter.inc('counter')
        self.assertEqual(self.counter.get('counter'), 1)
        self.counter.clear_counters()
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counter.get, 'counter')

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
        statistics_data = {}
        counter_name = "counter"
        timer_name = "seconds"
        statistics_spec = \
            isc.config.module_spec_from_file(self.TEST_SPECFILE_LOCATION)\
            .get_statistics_spec()
        self.counter._statistics_data = statistics_data
        self.counter._statistics_spec = statistics_spec
        start_time = counter._start_timer()
        start_functor(number, cycle, self.counter._incrementer,
                      counter_name)
        counter._stop_timer(start_time,
                            statistics_data,
                            statistics_spec,
                            timer_name)
        self.assertEqual(
            counter._get_counter(statistics_data,
                                 counter_name),
            number * cycle)
        self.assertGreater(
            counter._get_counter(statistics_data,
                                 timer_name), 0)

class BaseTestCounter():

    def setUp(self):
        self._statistics_data = {}
        self.counter = counter.Counter(self.TEST_SPECFILE_LOCATION)
        self._entire_server    = self.counter._entire_server
        self._perzone_prefix   = self.counter._perzone_prefix

    def tearDown(self):
        self.counter.clear_counters()

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
        if self.TEST_SPECFILE_LOCATION:
            self.assertTrue(isc.config.module_spec_from_file(
                    self.TEST_SPECFILE_LOCATION).validate_statistics(
                    False, self._statistics_data))
        else:
            self.assertTrue(isc.config.ModuleSpec(
                    {'module_name': 'Foo',
                     'statistics': self.counter._statistics._spec}
                    ).validate_statistics(
                    False, self._statistics_data))

    def test_perzone_counters(self):
        # for per-zone counters
        for name in self.counter._zones_item_list:
            args = (self._perzone_prefix, TEST_ZONE_NAME_STR, name)
            if name.find('time_to_') == 0:
                self.counter.start(*args)
                self.counter.stop(*args)
                self.assertGreater(self.counter.get(*args), 0)
                sec = self.counter.get(*args)
                for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                    isc.cc.data.set(self._statistics_data,
                                    '%s/%s/%s' % (args[0], zone_str, name), sec)
                # twice exec stopper, then second is not changed
                self.counter.stop(*args)
                self.assertEqual(self.counter.get(*args), sec)
            else:
                self.counter.inc(*args)
                self.assertEqual(self.counter.get(*args), 1)
                # checks disable/enable
                self.counter.disable()
                self.counter.inc(*args)
                self.assertEqual(self.counter.get(*args), 1)
                self.counter.enable()
                self.counter.inc(*args)
                self.assertEqual(self.counter.get(*args), 2)
                for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                    isc.cc.data.set(self._statistics_data,
                                    '%s/%s/%s' % (args[0], zone_str, name), 2)
        self.check_dump_statistics()

    def test_xfrrunning_counters(self):
        # for counters of xfer running
        _suffix = 'xfr_running'
        _xfrrunning_names = \
            isc.config.spec_name_list(self.counter._statistics._spec,
                                      "", True)
        for name in _xfrrunning_names:
            if name.find(_suffix) != 1: continue
            args = name.split('/')
            self.counter.inc(*args)
            self.assertEqual(self.counter.get(*args), 1)
            self.counter.dec(*args)
            self.assertEqual(self.counter.get(*args), 0)
            # checks disable/enable
            self.counter.disable()
            self.counter.inc(*args)
            self.assertEqual(self.counter.get(*args), 0)
            self.counter.enable()
            self.counter.inc(*args)
            self.assertEqual(self.counter.get(*args), 1)
            self.counter.disable()
            self.counter.dec(*args)
            self.assertEqual(self.counter.get(*args), 1)
            self.counter.enable()
            self.counter.dec(*args)
            self.assertEqual(self.counter.get(*args), 0)
            self._statistics_data[name] = 0
        self.check_dump_statistics()

    def test_socket_counters(self):
        # for ipsocket/unixsocket counters
        _prefix = 'socket/'
        _socket_names = \
            isc.config.spec_name_list(self.counter._statistics._spec,
                                      "", True)
        for name in _socket_names:
            if name.find(_prefix) != 0: continue
            args = name.split('/')
            self.counter.inc(*args)
            self.assertEqual(self.counter.get(*args), 1)
            # checks disable/enable
            self.counter.disable()
            self.counter.inc(*args)
            self.assertEqual(self.counter.get(*args), 1)
            self.counter.enable()
            self.counter.inc(*args)
            self.assertEqual(self.counter.get(*args), 2)
            isc.cc.data.set(
                self._statistics_data, '/'.join(args), 2)
        self.check_dump_statistics()

    def test_undefined_item(self):
        # test DataNotFoundError raising when specifying item defined
        # in the specfile
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counter.inc, '__undefined__')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counter.dec, '__undefined__')
        self.counter.start('__undefined__')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counter.stop, '__undefined__')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counter.get, '__undefined__')

class TestCounter0(unittest.TestCase, BaseTestCounter):
    TEST_SPECFILE_LOCATION = None
    def setUp(self):
        BaseTestCounter.setUp(self)
    def tearDown(self):
        BaseTestCounter.tearDown(self)

class TestCounter1(unittest.TestCase, BaseTestCounter):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec1.spec'
    def setUp(self):
        BaseTestCounter.setUp(self)
    def tearDown(self):
        BaseTestCounter.tearDown(self)

class TestCounter2(unittest.TestCase, BaseTestCounter):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec2.spec'
    def setUp(self):
        BaseTestCounter.setUp(self)
    def tearDown(self):
        BaseTestCounter.tearDown(self)

class TestCounter3(unittest.TestCase, BaseTestCounter):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec3.spec'
    def setUp(self):
        BaseTestCounter.setUp(self)
    def tearDown(self):
        BaseTestCounter.tearDown(self)

if __name__== "__main__":
    unittest.main()
