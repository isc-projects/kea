# Copyright (C) 2012-2013  Internet Systems Consortium.
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

'''Tests for isc.statistics.counters'''

import unittest
import threading
from datetime import timedelta
import os
import imp
import isc.config

TESTDATA_SRCDIR = os.getenv("TESTDATASRCDIR")

from isc.statistics import counters

def setup_functor(event, cycle, functor, *args):
    """Waits until the event is started, and then invokes the functor
    by times of the cycle with args."""
    event.wait()
    for i in range(cycle): functor(*args)

def start_functor(concurrency, number, functor, *args):
    """Creates the threads of the number and makes them start. Sets
    the event and waits until these threads are finished."""
    threads = []
    event = threading.Event()
    for i in range(concurrency):
        threads.append(threading.Thread(\
                target=setup_functor, \
                    args=(event, number, functor,) + args))
    for th in threads: th.start()
    event.set()
    for th in threads: th.join()

class TestBasicMethods(unittest.TestCase):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec1.spec'

    def setUp(self):
        imp.reload(counters)
        self.counters = counters.Counters(self.TEST_SPECFILE_LOCATION)

    def tearDown(self):
        self.counters.clear_all()

    def test_clear_counters(self):
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counters.get, 'counter')
        self.counters.inc('counter')
        self.assertEqual(self.counters.get('counter'), 1)
        self.counters.clear_all()
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counters.get, 'counter')

    def test_enablediable(self):
        self.assertFalse(self.counters._disabled)
        self.counters.disable()
        self.assertTrue(self.counters._disabled)
        self.counters.enable()
        self.assertFalse(self.counters._disabled)

    def test_add_counter_normal(self):
        element = {'counter' : 1}
        self.assertEqual(\
            counters._add_counter(element, [], 'counter'), 1)

    def test_add_counter_wrongspec(self):
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          counters._add_counter,
                          {}, [], 'counter')

    def test_add_counter_empty(self):
        self.assertEqual(\
            counters._add_counter(
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
            counters._add_counter(elem, spec, 'dirs/foo/counter1'), 0)
        self.assertEqual(\
            counters._add_counter(elem, spec, 'dirs/bar/counter2'), 0)

    def test_timer(self):
        t1 = counters._start_timer()
        t2 = t1 - timedelta(seconds=1)
        self.assertEqual((t1 - t2).seconds, 1)
        elem = {}
        spec = [{ 'item_name': 'time',
                  'item_type': 'real',
                  'item_default': 0.0 }]
        counters._stop_timer(t2, elem, spec, 'time')
        self.assertGreaterEqual(counters._get_counter(elem,'time'), 1.0)

    def test_rasing_incrementers(self):
        """ use Thread"""
        concurrency = 3    # number of the threads
        number = 10000     # number of counting per thread
        counter_name = "counter"
        timer_name = "seconds"
        start_time = counters._start_timer()
        start_functor(concurrency, number, self.counters.inc,
                      counter_name)
        counters._stop_timer(start_time,
                            self.counters._statistics_data,
                            self.counters._statistics_spec,
                            timer_name)
        self.assertEqual(
            counters._get_counter(self.counters._statistics_data,
                                 counter_name),
            concurrency * number)
        self.assertGreaterEqual(
            counters._get_counter(self.counters._statistics_data,
                                 timer_name), 0.0)

    def test_concat(self):
        # only strings
        a = ( 'a','b','c','d' )
        self.assertEqual('a/b/c/d', counters._concat(*a))
        self.assertEqual('aTbTcTd', counters._concat(*a, sep='T'))
        self.assertEqual('a\\b\\c\\d', counters._concat(*a, sep='\\'))
        # mixed with other types
        b = a + (1,)
        self.assertRaises(TypeError, counters._concat, *b)
        b = a + (1.1,)
        self.assertRaises(TypeError, counters._concat, *b)
        b = a + ([],)
        self.assertRaises(TypeError, counters._concat, *b)
        b = a + ({},)
        self.assertRaises(TypeError, counters._concat, *b)

class BaseTestCounters():

    def setUp(self):
        imp.reload(counters)
        self._statistics_data = {}
        self.counters = counters.Counters(self.TEST_SPECFILE_LOCATION)

    def tearDown(self):
        self.counters.clear_all()

    def check_get_statistics(self):
        """Checks no differences between the value returned from
        get_statistics() and locally collected statistics data. Also
        checks the result isn't changed even after the method is
        invoked twice. Finally checks it is valid for the the
        statistics spec."""
        self.assertEqual(self.counters.get_statistics(),
                         self._statistics_data)
        # Idempotency check
        self.assertEqual(self.counters.get_statistics(),
                         self._statistics_data)
        if self.TEST_SPECFILE_LOCATION:
            self.assertTrue(isc.config.module_spec_from_file(
                    self.TEST_SPECFILE_LOCATION).validate_statistics(
                    False, self._statistics_data))
        else:
            self.assertTrue(isc.config.ModuleSpec(
                    {'module_name': 'Foo',
                     'statistics': self.counters._statistics_spec}
                    ).validate_statistics(
                    False, self._statistics_data))

    def test_undefined_item(self):
        # test DataNotFoundError raising when specifying item defined
        # in the specfile
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counters.inc, '__undefined__')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counters.dec, '__undefined__')
        self.counters.start_timer('__undefined__')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counters.stop_timer, '__undefined__')
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.counters.get, '__undefined__')

class TestCounters0(unittest.TestCase, BaseTestCounters):
    TEST_SPECFILE_LOCATION = None
    def setUp(self):
        BaseTestCounters.setUp(self)
    def tearDown(self):
        BaseTestCounters.tearDown(self)

class TestCounters1(unittest.TestCase, BaseTestCounters):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec1.spec'
    def setUp(self):
        BaseTestCounters.setUp(self)
    def tearDown(self):
        BaseTestCounters.tearDown(self)

if __name__== "__main__":
    unittest.main()
