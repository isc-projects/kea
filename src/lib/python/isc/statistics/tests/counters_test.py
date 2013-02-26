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
                            self.counters._statistics._data,
                            self.counters._statistics._spec,
                            timer_name)
        self.assertEqual(
            counters._get_counter(self.counters._statistics._data,
                                 counter_name),
            concurrency * number)
        self.assertGreaterEqual(
            counters._get_counter(self.counters._statistics._data,
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
        self._entire_server    = self.counters._entire_server
        self._perzone_prefix   = self.counters._perzone_prefix

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
                     'statistics': self.counters._statistics._spec}
                    ).validate_statistics(
                    False, self._statistics_data))

    def test_perzone_counters(self):
        # for per-zone counters
        for name in self.counters._zones_item_list:
            args = (self._perzone_prefix, TEST_ZONE_NAME_STR, name)
            if name.find('time_to_') == 0:
                self.counters.start_timer(*args)
                self.counters.stop_timer(*args)
                self.assertGreaterEqual(self.counters.get(*args), 0.0)
                sec = self.counters.get(*args)
                for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                    isc.cc.data.set(self._statistics_data,
                                    '%s/%s/%s' % (args[0], zone_str, name), sec)
                # twice exec stopper, then second is not changed
                self.counters.stop_timer(*args)
                self.assertEqual(self.counters.get(*args), sec)
            else:
                self.counters.inc(*args)
                self.assertEqual(self.counters.get(*args), 1)
                # checks disable/enable
                self.counters.disable()
                self.counters.inc(*args)
                self.assertEqual(self.counters.get(*args), 1)
                self.counters.enable()
                self.counters.inc(*args)
                self.assertEqual(self.counters.get(*args), 2)
                for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                    isc.cc.data.set(self._statistics_data,
                                    '%s/%s/%s' % (args[0], zone_str, name), 2)
        self.check_get_statistics()

    def test_xfrrunning_counters(self):
        # for counters of xfer running
        _suffix = 'xfr_running'
        _xfrrunning_names = \
            isc.config.spec_name_list(self.counters._statistics._spec,
                                      "", True)
        for name in _xfrrunning_names:
            if name.find(_suffix) != 1: continue
            args = name.split('/')
            self.counters.inc(*args)
            self.assertEqual(self.counters.get(*args), 1)
            self.counters.dec(*args)
            self.assertEqual(self.counters.get(*args), 0)
            # checks disable/enable
            self.counters.disable()
            self.counters.inc(*args)
            self.assertEqual(self.counters.get(*args), 0)
            self.counters.enable()
            self.counters.inc(*args)
            self.assertEqual(self.counters.get(*args), 1)
            self.counters.disable()
            self.counters.dec(*args)
            self.assertEqual(self.counters.get(*args), 1)
            self.counters.enable()
            self.counters.dec(*args)
            self.assertEqual(self.counters.get(*args), 0)
            self._statistics_data[name] = 0
        self.check_get_statistics()

    def test_socket_counters(self):
        # for ipsocket/unixsocket counters
        _prefix = 'socket/'
        _socket_names = \
            isc.config.spec_name_list(self.counters._statistics._spec,
                                      "", True)
        for name in _socket_names:
            if name.find(_prefix) != 0: continue
            args = name.split('/')
            self.counters.inc(*args)
            self.assertEqual(self.counters.get(*args), 1)
            # checks disable/enable
            self.counters.disable()
            self.counters.inc(*args)
            self.assertEqual(self.counters.get(*args), 1)
            self.counters.enable()
            self.counters.inc(*args)
            self.assertEqual(self.counters.get(*args), 2)
            isc.cc.data.set(
                self._statistics_data, '/'.join(args), 2)
        self.check_get_statistics()

    def test_perzone_zero_counters(self):
        # setting all counters to zero
        for name in self.counters._zones_item_list:
            args = (self._perzone_prefix, TEST_ZONE_NAME_STR, name)
            if name.find('time_to_') == 0:
                zero = 0.0
            else:
                zero = 0
            # set zero
            self.counters._incdec(*args, step=zero)
            for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                isc.cc.data.set(self._statistics_data,
                                '%s/%s/%s' % (args[0], zone_str, name), zero)
        self.check_get_statistics()

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

class TestCounters2(unittest.TestCase, BaseTestCounters):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec2.spec'
    def setUp(self):
        BaseTestCounters.setUp(self)
    def tearDown(self):
        BaseTestCounters.tearDown(self)

class TestCounters3(unittest.TestCase, BaseTestCounters):
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec3.spec'
    @classmethod
    def setUpClass(cls):
        imp.reload(counters)
    def setUp(self):
        BaseTestCounters.setUp(self)
    def tearDown(self):
        BaseTestCounters.tearDown(self)

class BaseDummyModule():
    """A base dummy class"""
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec2.spec'
    def __init__(self):
        self.counters = counters.Counters(self.TEST_SPECFILE_LOCATION)

    def get_counters(self):
        return self.counters.get_statistics()

    def clear_counters(self):
        self.counters.clear_all()

class DummyNotifyOut(BaseDummyModule):
    """A dummy class equivalent to notify.notify_out.NotifyOut"""
    def __init__(self):
        self.counters = counters.Counters()

    def inc_counters(self):
        """increments counters"""
        self.counters.inc('zones', TEST_ZONE_NAME_STR, 'notifyoutv4')
        self.counters.inc('zones', TEST_ZONE_NAME_STR, 'notifyoutv6')

class DummyXfroutSession(BaseDummyModule):
    """A dummy class equivalent to XfroutSession in b10-xfrout"""
    def inc_counters(self):
        """increments counters"""
        self.counters.inc('zones', TEST_ZONE_NAME_STR, 'xfrreqdone')
        self.counters.inc('zones', TEST_ZONE_NAME_STR, 'xfrrej')
        self.counters.inc('axfr_running')
        self.counters.inc('ixfr_running')
        self.counters.dec('axfr_running')
        self.counters.dec('ixfr_running')

class DummyUnixSockServer(BaseDummyModule):
    """A dummy class equivalent to UnixSockServer in b10-xfrout"""
    def inc_counters(self):
        """increments counters"""
        self.counters.inc('socket', 'unixdomain', 'open')
        self.counters.inc('socket', 'unixdomain', 'close')

class DummyXfroutServer(BaseDummyModule):
    """A dummy class equivalent to XfroutServer in b10-xfrout"""
    def __init__(self):
        super().__init__()
        self.xfrout_sess = DummyXfroutSession()
        self.unix_socket_server = DummyUnixSockServer()
        self.notifier = DummyNotifyOut()

    def inc_counters(self):
        self.xfrout_sess.inc_counters()
        self.unix_socket_server.inc_counters()
        self.notifier.inc_counters()

class TestDummyNotifyOut(unittest.TestCase):
    """Tests counters are incremented in which the spec file is not
    loaded"""
    def setUp(self):
        imp.reload(counters)
        self.notifier = DummyNotifyOut()
        self.notifier.inc_counters()

    def tearDown(self):
        self.notifier.clear_counters()

    def test_counters(self):
        self.assertEqual(
            {'zones': {'_SERVER_': {'notifyoutv4': 1, 'notifyoutv6': 1},
                       TEST_ZONE_NAME_STR: {'notifyoutv4': 1, 'notifyoutv6': 1}}},
            self.notifier.get_counters())

class TestDummyXfroutServer(unittest.TestCase):
    """Tests counters are incremented or decremented in which the same
    spec file is multiply loaded in each child class"""
    def setUp(self):
        imp.reload(counters)
        self.xfrout_server = DummyXfroutServer()
        self.xfrout_server.inc_counters()

    def tearDown(self):
        self.xfrout_server.clear_counters()

    def test_counters(self):
        self.assertEqual(
            {'axfr_running': 0, 'ixfr_running': 0,
             'socket': {'unixdomain': {'open': 1, 'close': 1}},
             'zones': {'_SERVER_': {'notifyoutv4': 1,
                                    'notifyoutv6': 1,
                                    'xfrrej': 1, 'xfrreqdone': 1},
                       TEST_ZONE_NAME_STR: {'notifyoutv4': 1,
                                        'notifyoutv6': 1,
                                        'xfrrej': 1,
                                        'xfrreqdone': 1}}},
            self.xfrout_server.get_counters())

if __name__== "__main__":
    unittest.main()
