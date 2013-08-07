# Copyright (C) 2013  Internet Systems Consortium.
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

'''Tests for isc.statistics.dns'''

import unittest
import os
import imp
import isc.config
import counters_test

TEST_ZONE_NAME_STR = "example.com."
TEST_ZONE_CLASS_STR = "IN"
TESTDATA_SRCDIR = os.getenv("TESTDATASRCDIR")

from isc.statistics import dns

class BaseTestCounters(counters_test.BaseTestCounters):

    def setUp(self):
        imp.reload(dns)
        self._statistics_data = {}
        self.counters = dns.Counters(self.TEST_SPECFILE_LOCATION)
        self._entire_server    = self.counters._entire_server
        self._perzone_prefix   = self.counters._perzone_prefix

    def test_perzone_counters(self):
        # for per-zone counters
        for name in self.counters._zones_item_list:
            args = (self._perzone_prefix, TEST_ZONE_CLASS_STR,
                    TEST_ZONE_NAME_STR, name)
            if name.find('last_') == 0 and name.endswith('_duration'):
                self.counters.start_timer(*args)
                self.counters.stop_timer(*args)
                self.assertGreaterEqual(self.counters.get(*args), 0.0)
                sec = self.counters.get(*args)
                for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                    isc.cc.data.set(self._statistics_data,
                                    '%s/%s/%s/%s' % (args[0], args[1],
                                                     zone_str, name), sec)
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
                                    '%s/%s/%s/%s' % (args[0], args[1],
                                                     zone_str, name), 2)
        self.check_get_statistics()

    def test_xfrrunning_counters(self):
        # for counters of xfer running
        _suffix = 'xfr_running'
        _xfrrunning_names = \
            isc.config.spec_name_list(self.counters._statistics_spec,
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
            isc.config.spec_name_list(self.counters._statistics_spec,
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
            args = (self._perzone_prefix, TEST_ZONE_CLASS_STR,
                    TEST_ZONE_NAME_STR, name)
            if name.find('last_') == 0 and name.endswith('_duration'):
                zero = 0.0
            else:
                zero = 0
            # set zero
            self.counters._incdec(*args, step=zero)
            for zone_str in (self._entire_server, TEST_ZONE_NAME_STR):
                isc.cc.data.set(self._statistics_data,
                                '%s/%s/%s/%s' % (args[0], args[1],
                                                 zone_str, name), zero)
        self.check_get_statistics()


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
        imp.reload(dns)
    def setUp(self):
        BaseTestCounters.setUp(self)
    def tearDown(self):
        BaseTestCounters.tearDown(self)

class BaseDummyModule():
    """A base dummy class"""
    TEST_SPECFILE_LOCATION = TESTDATA_SRCDIR + os.sep + 'test_spec2.spec'
    def __init__(self):
        self.counters = dns.Counters(self.TEST_SPECFILE_LOCATION)

    def get_counters(self):
        return self.counters.get_statistics()

    def clear_counters(self):
        self.counters.clear_all()

class DummyNotifyOut(BaseDummyModule):
    """A dummy class equivalent to notify.notify_out.NotifyOut"""
    def __init__(self):
        self.counters = dns.Counters()

    def inc_counters(self):
        """increments counters"""
        self.counters.inc('zones', TEST_ZONE_CLASS_STR,
                          TEST_ZONE_NAME_STR, 'notifyoutv4')
        self.counters.inc('zones', TEST_ZONE_CLASS_STR,
                          TEST_ZONE_NAME_STR, 'notifyoutv6')

class DummyXfroutSession(BaseDummyModule):
    """A dummy class equivalent to XfroutSession in b10-xfrout"""
    def inc_counters(self):
        """increments counters"""
        self.counters.inc('zones', TEST_ZONE_CLASS_STR,
                          TEST_ZONE_NAME_STR, 'xfrreqdone')
        self.counters.inc('zones', TEST_ZONE_CLASS_STR,
                          TEST_ZONE_NAME_STR, 'xfrrej')
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
        imp.reload(dns)
        self.notifier = DummyNotifyOut()
        self.notifier.inc_counters()

    def tearDown(self):
        self.notifier.clear_counters()

    def test_counters(self):
        self.assertEqual(
            {'zones': {TEST_ZONE_CLASS_STR: { '_SERVER_':
                           {'notifyoutv4': 1, 'notifyoutv6': 1},
                                              TEST_ZONE_NAME_STR:
                           {'notifyoutv4': 1, 'notifyoutv6': 1}}}},
            self.notifier.get_counters())

class TestDummyXfroutServer(unittest.TestCase):
    """Tests counters are incremented or decremented in which the same
    spec file is multiply loaded in each child class"""
    def setUp(self):
        imp.reload(dns)
        self.xfrout_server = DummyXfroutServer()
        self.xfrout_server.inc_counters()

    def tearDown(self):
        self.xfrout_server.clear_counters()

    def test_counters(self):
        self.assertEqual(
            {'axfr_running': 0, 'ixfr_running': 0,
             'socket': {'unixdomain': {'open': 1, 'close': 1}},
             'zones': {TEST_ZONE_CLASS_STR: {
                        '_SERVER_': {'notifyoutv4': 1,
                                    'notifyoutv6': 1,
                                    'xfrrej': 1, 'xfrreqdone': 1},
                        TEST_ZONE_NAME_STR: {'notifyoutv4': 1,
                                        'notifyoutv6': 1,
                                        'xfrrej': 1,
                                        'xfrreqdone': 1}}}},
            self.xfrout_server.get_counters())

if __name__== "__main__":
    unittest.main()
