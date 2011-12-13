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

'''Tests for the ZonemgrRefresh and Zonemgr classes '''


import unittest
import os
import tempfile
from zonemgr import *

ZONE_NAME_CLASS1_IN = ("example.net.", "IN")
ZONE_NAME_CLASS1_CH = ("example.net.", "CH")
ZONE_NAME_CLASS2_IN = ("example.org.", "IN")
ZONE_NAME_CLASS2_CH = ("example.org.", "CH")
ZONE_NAME_CLASS3_IN = ("example.com.", "IN")
ZONE_NAME_CLASS3_CH = ("example.com.", "CH")

MAX_TRANSFER_TIMEOUT = 14400
LOWERBOUND_REFRESH = 10
LOWERBOUND_RETRY = 5
REFRESH_JITTER = 0.10
RELOAD_JITTER = 0.75

class ZonemgrTestException(Exception):
    pass

class MySession():
    def __init__(self):
        pass

    def group_sendmsg(self, msg, module_name):
        if module_name not in ("Auth", "Xfrin"):
            raise ZonemgrTestException("module name not exist")

    def group_recvmsg(self, nonblock, seq):
        return None, None

class FakeConfig:
    def __init__(self):
        self.zone_list = []
        self.set_zone_list_from_name_classes([ZONE_NAME_CLASS1_IN,
                                              ZONE_NAME_CLASS2_CH])

    def set_zone_list_from_name_classes(self, zones):
        self.zone_list = map(lambda nc: {"name": nc[0], "class": nc[1]}, zones)

    def get(self, name):
        if name == 'lowerbound_refresh':
            return LOWERBOUND_REFRESH
        elif name == 'lowerbound_retry':
            return LOWERBOUND_RETRY
        elif name == 'max_transfer_timeout':
            return MAX_TRANSFER_TIMEOUT
        elif name == 'refresh_jitter':
            return REFRESH_JITTER
        elif name == 'reload_jitter':
            return RELOAD_JITTER
        elif name == 'secondary_zones':
            return self.zone_list
        else:
            raise ValueError('Uknown config option')

class FakeCCSession:
    def __init__(self):
        self.config = FakeConfig()

    def get_full_config(self):
        return {'lowerbound_refresh': LOWERBOUND_REFRESH,
                'lowerbound_retry': LOWERBOUND_RETRY,
                'max_transfer_timeout': MAX_TRANSFER_TIMEOUT,
                'refresh_jitter': REFRESH_JITTER,
                'reload_jitter': RELOAD_JITTER,
                'secondary_zones': [] }

    def get_default_value(self, identifier):
        return "IN"


class MyZonemgrRefresh(ZonemgrRefresh):
    def __init__(self):
        self._master_socket, self._slave_socket = socket.socketpair()
        self._zonemgr_refresh_info = {}
        self._lowerbound_refresh = 10
        self._lowerbound_retry = 5
        self._reload_jitter = 0.75
        self._refresh_jitter = 0.25

        def get_zone_soa(zone_name, db_file):
            if zone_name == 'example.net.':
                return (1, 2, 'example.net.', 'example.net.sd.', 21600, 'SOA', None,
                        'a.example.net. root.example.net. 2009073106 7200 3600 2419200 21600')
            elif zone_name == 'example.org.':
                return (1, 2, 'example.org.', 'example.org.sd.', 21600, 'SOA', None,
                        'a.example.org. root.example.org. 2009073112 7200 3600 2419200 21600')
            else:
                return None
        sqlite3_ds.get_zone_soa = get_zone_soa

        ZonemgrRefresh.__init__(self, MySession(), "initdb.file",
                                self._slave_socket, FakeCCSession())
        current_time = time.time()
        self._zonemgr_refresh_info = {
         ('example.net.', 'IN'): {
         'last_refresh_time': current_time,
         'next_refresh_time': current_time + 6500,
         'zone_soa_rdata': 'a.example.net. root.example.net. 2009073105 7200 3600 2419200 21600',
         'zone_state': 0},
         ('example.org.', 'CH'): {
         'last_refresh_time': current_time,
         'next_refresh_time': current_time + 6900,
         'zone_soa_rdata': 'a.example.org. root.example.org. 2009073112 7200 3600 2419200 21600',
         'zone_state': 0}
        }

class TestZonemgrRefresh(unittest.TestCase):
    def setUp(self):
        self.stderr_backup = sys.stderr
        sys.stderr = open(os.devnull, 'w')
        self.zone_refresh = MyZonemgrRefresh()
        self.cc_session = FakeCCSession()

    def test_random_jitter(self):
        max = 100025.120
        jitter = 0
        self.assertEqual(max, self.zone_refresh._random_jitter(max, jitter))
        jitter = 0.3 * max
        for i in range (0, 150):
            self.assertTrue((max - jitter) <= self.zone_refresh._random_jitter(max, jitter))
            self.assertTrue(self.zone_refresh._random_jitter(max, jitter) <= max)
            i += 1;

    def test_get_current_time(self):
        pass

    def test_set_zone_timer(self):
        max = 3600
        jitter = 900
        time1 = time.time()
        self.zone_refresh._set_zone_timer(ZONE_NAME_CLASS1_IN, 3600, 900)
        time2 = time.time()
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertTrue((3600 - 900) <= (zone_timeout - time1))
        self.assertTrue((zone_timeout - time2) <= 3600)

    def test_set_zone_refresh_timer(self):
        time1 = time.time()
        self.zone_refresh._set_zone_refresh_timer(ZONE_NAME_CLASS1_IN)
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue((time1 + 7200 * (1 - self.zone_refresh._refresh_jitter)) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 7200)

    def test_set_zone_retry_timer(self):
        time1 = time.time()
        self.zone_refresh._set_zone_retry_timer(ZONE_NAME_CLASS1_IN)
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue((time1 + 3600 * (1 - self.zone_refresh._refresh_jitter)) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 3600)

        # No soa rdata
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"] = None
        time3 = time.time()
        self.zone_refresh._set_zone_retry_timer(ZONE_NAME_CLASS1_IN)
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        time4 = time.time()
        self.assertTrue((time3 + self.zone_refresh._lowerbound_retry * (1 - self.zone_refresh._refresh_jitter))
                         <= zone_timeout)
        self.assertTrue(zone_timeout <= time4 + self.zone_refresh._lowerbound_retry)

    def test_zone_not_exist(self):
        self.assertFalse(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS1_IN))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS1_CH))
        self.assertFalse(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS2_CH))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS2_IN))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS3_IN))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS3_CH))

    def test_set_zone_notify_timer(self):
        time1 = time.time()
        self.zone_refresh._set_zone_notify_timer(ZONE_NAME_CLASS1_IN)
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue(time1 <= zone_timeout)
        self.assertTrue(zone_timeout <= time2)

    def test_zone_is_expired(self):
        current_time = time.time()
        zone_expired_time = 2419200
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"] = \
                                                  current_time - zone_expired_time - 1
        self.assertTrue(self.zone_refresh._zone_is_expired(ZONE_NAME_CLASS1_IN))
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"] = \
                                                  current_time - zone_expired_time + 1
        self.assertFalse(self.zone_refresh._zone_is_expired(ZONE_NAME_CLASS1_IN))
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_EXPIRED
        self.assertTrue(self.zone_refresh._zone_is_expired(ZONE_NAME_CLASS1_IN))

    def test_get_zone_soa_rdata(self):
        soa_rdata1  = 'a.example.net. root.example.net. 2009073105 7200 3600 2419200 21600'
        soa_rdata2  = 'a.example.org. root.example.org. 2009073112 7200 3600 2419200 21600'
        self.assertEqual(soa_rdata1, self.zone_refresh._get_zone_soa_rdata(ZONE_NAME_CLASS1_IN))
        self.assertRaises(KeyError, self.zone_refresh._get_zone_soa_rdata, ZONE_NAME_CLASS1_CH)
        self.assertEqual(soa_rdata2, self.zone_refresh._get_zone_soa_rdata(ZONE_NAME_CLASS2_CH))
        self.assertRaises(KeyError, self.zone_refresh._get_zone_soa_rdata, ZONE_NAME_CLASS2_IN)

    def test_zonemgr_reload_zone(self):
        soa_rdata = 'a.example.net. root.example.net. 2009073106 1800 900 2419200 21600'
        # We need to restore this not to harm other tests
        old_get_zone_soa = sqlite3_ds.get_zone_soa
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'example.net.', 'example.net.sd.', 21600, 'SOA', None,
                    'a.example.net. root.example.net. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zone_refresh.zonemgr_reload_zone(ZONE_NAME_CLASS1_IN)
        self.assertEqual(soa_rdata, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"])
        sqlite3_ds.get_zone_soa = old_get_zone_soa

    def test_get_zone_notifier_master(self):
        notify_master = "192.168.1.1"
        self.assertEqual(None, self.zone_refresh._get_zone_notifier_master(ZONE_NAME_CLASS1_IN))
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["notify_master"] = notify_master
        self.assertEqual(notify_master, self.zone_refresh._get_zone_notifier_master(ZONE_NAME_CLASS1_IN))

    def test_set_zone_notifier_master(self):
        notify_master = "192.168.1.1"
        self.zone_refresh._set_zone_notifier_master(ZONE_NAME_CLASS1_IN, notify_master)
        self.assertEqual(self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]\
                                                                ["notify_master"], notify_master)

    def test_clear_zone_notifier_master(self):
        notify_master = "192.168.1.1"
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["notify_master"] = notify_master
        self.zone_refresh._clear_zone_notifier_master(ZONE_NAME_CLASS1_IN)
        self.assertFalse("notify_master" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.zone_refresh._clear_zone_notifier_master(ZONE_NAME_CLASS2_CH)
        self.assertFalse("notify_master" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS2_CH].keys())

    def test_get_zone_state(self):
        self.assertEqual(ZONE_OK, self.zone_refresh._get_zone_state(ZONE_NAME_CLASS1_IN))
        self.assertEqual(ZONE_OK, self.zone_refresh._get_zone_state(ZONE_NAME_CLASS2_CH))

    def test_set_zone_state(self):
        self.zone_refresh._set_zone_state(ZONE_NAME_CLASS1_IN, ZONE_REFRESHING)
        self.zone_refresh._set_zone_state(ZONE_NAME_CLASS2_CH, ZONE_EXPIRED)
        self.assertEqual(ZONE_REFRESHING, \
                self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        self.assertEqual(ZONE_EXPIRED, \
                self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS2_CH]["zone_state"])

    def test_get_zone_refresh_timeout(self):
        current_time = time.time()
        self.assertFalse("refresh_timeout" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["refresh_timeout"] = current_time
        self.assertEqual(current_time, self.zone_refresh._get_zone_refresh_timeout(ZONE_NAME_CLASS1_IN))

    def test_set_zone_refresh_timeout(self):
        current_time = time.time()
        self.zone_refresh._set_zone_refresh_timeout(ZONE_NAME_CLASS1_IN, current_time)
        refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["refresh_timeout"]
        self.assertEqual(current_time, refresh_time)

    def test_get_zone_next_refresh_time(self):
        current_time = time.time()
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"] = current_time
        self.assertEqual(current_time, self.zone_refresh._get_zone_next_refresh_time(ZONE_NAME_CLASS1_IN))

    def test_set_zone_next_refresh_time(self):
        current_time = time.time()
        self.zone_refresh._set_zone_next_refresh_time(ZONE_NAME_CLASS1_IN, current_time)
        next_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertEqual(current_time, next_refresh_time)

    def test_get_zone_last_refresh_time(self):
        current_time = time.time()
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"] = current_time
        self.assertEqual(current_time, self.zone_refresh._get_zone_last_refresh_time(ZONE_NAME_CLASS1_IN))

    def test_set_zone_last_refresh_time(self):
        current_time = time.time()
        self.zone_refresh._set_zone_last_refresh_time(ZONE_NAME_CLASS1_IN, current_time)
        last_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"]
        self.assertEqual(current_time, last_refresh_time)

    def test_send_command(self):
        self.assertRaises(ZonemgrTestException, self.zone_refresh._send_command, "Unknown", "Notify", None)

    def test_zone_mgr_is_empty(self):
        self.assertFalse(self.zone_refresh._zone_mgr_is_empty())
        self.zone_refresh._zonemgr_refresh_info = {}
        self.assertTrue(self.zone_refresh._zone_mgr_is_empty())

    def test_zonemgr_add_zone(self):
        soa_rdata = 'a.example.net. root.example.net. 2009073106 1800 900 2419200 21600'
        # This needs to be restored. The following test actually failed if we left
        # this unclean
        old_get_zone_soa = sqlite3_ds.get_zone_soa
        time1 = time.time()

        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'example.net.', 'example.net.sd.', 21600, 'SOA', None,
                    'a.example.net. root.example.net. 2009073106 1800 900 2419200 21600')

        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zone_refresh._zonemgr_refresh_info = {}
        self.zone_refresh.zonemgr_add_zone(ZONE_NAME_CLASS1_IN)
        self.assertEqual(1, len(self.zone_refresh._zonemgr_refresh_info))
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata)
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        self.assertTrue("last_refresh_time" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.assertTrue("next_refresh_time" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        time2 = time.time()
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertTrue((time1 + 900 * (1 - self.zone_refresh._reload_jitter)) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 900)

        def get_zone_soa2(zone_name, db_file):
            return None
        sqlite3_ds.get_zone_soa = get_zone_soa2
        self.zone_refresh.zonemgr_add_zone(ZONE_NAME_CLASS2_IN)
        self.assertTrue(self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS2_IN]["zone_soa_rdata"] is None)
        sqlite3_ds.get_zone_soa = old_get_zone_soa

    def test_zone_handle_notify(self):
        self.zone_refresh.zone_handle_notify(ZONE_NAME_CLASS1_IN,"127.0.0.1")
        notify_master = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["notify_master"]
        self.assertEqual("127.0.0.1", notify_master)
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        current_time = time.time()
        self.assertTrue(zone_timeout <= current_time)
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_handle_notify,\
                          ZONE_NAME_CLASS3_CH, "127.0.0.1")
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_handle_notify,\
                          ZONE_NAME_CLASS3_IN, "127.0.0.1")

    def test_zone_refresh_success(self):
        soa_rdata = 'a.example.net. root.example.net. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'example.net.', 'example.net.sd.', 21600, 'SOA', None,
                    'a.example.net. root.example.net. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_REFRESHING
        self.zone_refresh.zone_refresh_success(ZONE_NAME_CLASS1_IN)
        time2 = time.time()
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata)
        next_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertTrue((time1 + 1800 * (1 - self.zone_refresh._refresh_jitter)) <= next_refresh_time)
        self.assertTrue(next_refresh_time <= time2 + 1800)
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        last_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"]
        self.assertTrue(time1 <= last_refresh_time)
        self.assertTrue(last_refresh_time <= time2)
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_success, ("example.test.", "CH"))
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_success, ZONE_NAME_CLASS3_IN)

    def test_zone_refresh_fail(self):
        soa_rdata = 'a.example.net. root.example.net. 2009073105 7200 3600 2419200 21600'
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_REFRESHING
        self.zone_refresh.zone_refresh_fail(ZONE_NAME_CLASS1_IN)
        time2 = time.time()
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata)
        next_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertTrue(((time1 + 3600 * (1 - self.zone_refresh._refresh_jitter))) <= next_refresh_time)
        self.assertTrue(next_refresh_time <= time2 + 3600)
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])

        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"] = time1 - 2419200
        self.zone_refresh.zone_refresh_fail(ZONE_NAME_CLASS1_IN)
        self.assertEqual(ZONE_EXPIRED, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])

        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_fail, ZONE_NAME_CLASS3_CH)
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_fail, ZONE_NAME_CLASS3_IN)

        old_get_zone_soa = sqlite3_ds.get_zone_soa
        def get_zone_soa(zone_name, db_file):
            return None
        sqlite3_ds.get_zone_soa = get_zone_soa
        self.zone_refresh.zone_refresh_fail(ZONE_NAME_CLASS1_IN)
        self.assertEqual(self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"],
                         ZONE_EXPIRED)
        sqlite3_ds.get_zone_soa = old_get_zone_soa

    def test_find_need_do_refresh_zone(self):
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info = {
                ("example.net.","IN"):{
                    'last_refresh_time': time1,
                    'next_refresh_time': time1 + 7200,
                    'zone_soa_rdata': 'a.example.net. root.example.net. 2009073105 7200 3600 2419200 21600',
                    'zone_state': ZONE_OK},
                ("example.org.","CH"):{
                    'last_refresh_time': time1 - 7200,
                    'next_refresh_time': time1,
                    'refresh_timeout': time1 + MAX_TRANSFER_TIMEOUT,
                    'zone_soa_rdata': 'a.example.org. root.example.org. 2009073112 7200 3600 2419200 21600',
                    'zone_state': ZONE_REFRESHING}
                }
        zone_need_refresh = self.zone_refresh._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS1_IN, zone_need_refresh)

        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS2_CH]["refresh_timeout"] = time1
        zone_need_refresh = self.zone_refresh._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS2_CH, zone_need_refresh)

    def test_do_refresh(self):
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info = {
                ("example.net.", "IN"):{
                    'last_refresh_time': time1 - 7200,
                    'next_refresh_time': time1 - 1,
                    'zone_soa_rdata': 'a.example.net. root.example.net. 2009073105 7200 3600 2419200 21600',
                    'zone_state': ZONE_OK}
                }
        self.zone_refresh._do_refresh(ZONE_NAME_CLASS1_IN)
        time2 = time.time()
        zone_state = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"]
        self.assertEqual(ZONE_REFRESHING, zone_state)
        refresh_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["refresh_timeout"]
        self.assertTrue(time1 + MAX_TRANSFER_TIMEOUT <= refresh_timeout)
        self.assertTrue(time2 + MAX_TRANSFER_TIMEOUT >= refresh_timeout)

        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["notify_master"] = "127.0.0.1"
        self.zone_refresh._do_refresh(ZONE_NAME_CLASS1_IN)
        time2 = time.time()
        zone_state = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"]
        self.assertEqual(ZONE_REFRESHING, zone_state)
        refresh_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["refresh_timeout"]
        self.assertTrue(time1 + MAX_TRANSFER_TIMEOUT <= refresh_timeout)
        self.assertTrue(time2 + MAX_TRANSFER_TIMEOUT >= refresh_timeout)
        self.assertFalse("notify_master" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())

    def test_run_timer(self):
        """This case will run timer in daemon thread.
        The zone's next_refresh_time is less than now, so zonemgr will do zone refresh
        immediately. The zone's state will become "refreshing".
        """
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info = {
                ("example.net.", "IN"):{
                    'last_refresh_time': time1 - 7200,
                    'next_refresh_time': time1 - 1,
                    'zone_soa_rdata': 'a.example.net. root.example.net. 2009073105 7200 3600 2419200 21600',
                    'zone_state': ZONE_OK}
                }
        self.zone_refresh._check_sock = self.zone_refresh._master_socket
        listener = self.zone_refresh.run_timer(daemon=True)
        # Shut down the timer thread
        self.zone_refresh.shutdown()
        # After running timer, the zone's state should become "refreshing".
        zone_state = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"]
        self.assertTrue("refresh_timeout" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.assertTrue(zone_state == ZONE_REFRESHING)

    def test_update_config_data(self):
        # make sure it doesn't fail if we only provide secondary zones
        config_data = {
                    "secondary_zones": [ { "name": "example.net.",
                                           "class": "IN" } ]
                }
        self.zone_refresh.update_config_data(config_data, self.cc_session)
        self.assertTrue(("example.net.", "IN") in
                        self.zone_refresh._zonemgr_refresh_info)

        # make sure it does fail if we don't provide a name
        config_data = {
                    "secondary_zones": [ { "class": "IN" } ]
                }
        self.assertRaises(ZonemgrException,
                          self.zone_refresh.update_config_data,
                          config_data, self.cc_session)

        # But not if we don't provide a class
        config_data = {
                    "secondary_zones": [ { "name": "example.net." } ]
                }
        self.zone_refresh.update_config_data(config_data, self.cc_session)
        self.assertTrue(("example.net.", "IN") in
                        self.zone_refresh._zonemgr_refresh_info)

        # update all values
        config_data = {
                    "lowerbound_refresh" : 60,
                    "lowerbound_retry" : 30,
                    "max_transfer_timeout" : 19800,
                    "refresh_jitter" : 0.25,
                    "reload_jitter" : 0.75,
                    "secondary_zones": []
                }
        self.zone_refresh.update_config_data(config_data, self.cc_session)
        self.assertEqual(60, self.zone_refresh._lowerbound_refresh)
        self.assertEqual(30, self.zone_refresh._lowerbound_retry)
        self.assertEqual(19800, self.zone_refresh._max_transfer_timeout)
        self.assertEqual(0.25, self.zone_refresh._refresh_jitter)
        self.assertEqual(0.75, self.zone_refresh._reload_jitter)

        # make sure they are not reset when we only update one
        config_data = {
                    "reload_jitter" : 0.35,
                }
        self.zone_refresh.update_config_data(config_data, self.cc_session)
        self.assertEqual(60, self.zone_refresh._lowerbound_refresh)
        self.assertEqual(30, self.zone_refresh._lowerbound_retry)
        self.assertEqual(19800, self.zone_refresh._max_transfer_timeout)
        self.assertEqual(0.25, self.zone_refresh._refresh_jitter)
        self.assertEqual(0.35, self.zone_refresh._reload_jitter)

        # and make sure we restore the previous config if something
        # goes wrong
        config_data = {
                    "lowerbound_refresh" : 61,
                    "lowerbound_retry" : 31,
                    "max_transfer_timeout" : 19801,
                    "refresh_jitter" : 0.21,
                    "reload_jitter" : 0.71,
                    "secondary_zones": [ { "name": "doesnotexist",
                                           "class": "IN" } ]
                }
        self.zone_refresh.update_config_data(config_data, self.cc_session)
        name_class = ("doesnotexist.", "IN")
        self.assertTrue(self.zone_refresh._zonemgr_refresh_info[name_class]["zone_soa_rdata"]
                        is None)
        # The other configs should be updated successfully
        self.assertEqual(61, self.zone_refresh._lowerbound_refresh)
        self.assertEqual(31, self.zone_refresh._lowerbound_retry)
        self.assertEqual(19801, self.zone_refresh._max_transfer_timeout)
        self.assertEqual(0.21, self.zone_refresh._refresh_jitter)
        self.assertEqual(0.71, self.zone_refresh._reload_jitter)

        # Make sure we accept 0 as a value
        config_data = {
                    "lowerbound_refresh" : 60,
                    "lowerbound_retry" : 30,
                    "max_transfer_timeout" : 19800,
                    "refresh_jitter" : 0,
                    "reload_jitter" : 0.75,
                    "secondary_zones": []
                }
        self.zone_refresh.update_config_data(config_data, self.cc_session)
        self.assertEqual(60, self.zone_refresh._lowerbound_refresh)
        self.assertEqual(30, self.zone_refresh._lowerbound_retry)
        self.assertEqual(19800, self.zone_refresh._max_transfer_timeout)
        self.assertEqual(0, self.zone_refresh._refresh_jitter)
        self.assertEqual(0.75, self.zone_refresh._reload_jitter)

    def test_shutdown(self):
        self.zone_refresh._check_sock = self.zone_refresh._master_socket
        listener = self.zone_refresh.run_timer()
        self.assertTrue(listener.is_alive())
        # Shut down the timer thread
        self.zone_refresh.shutdown()
        self.assertFalse(listener.is_alive())

    def test_secondary_zones(self):
        """Test that we can modify the list of secondary zones"""
        config = FakeConfig()
        config.zone_list = []
        # First, remove everything
        self.zone_refresh.update_config_data(config, self.cc_session)
        self.assertEqual(self.zone_refresh._zonemgr_refresh_info, {})
        # Put something in
        config.set_zone_list_from_name_classes([ZONE_NAME_CLASS1_IN])
        self.zone_refresh.update_config_data(config, self.cc_session)
        self.assertTrue(("example.net.", "IN") in
                        self.zone_refresh._zonemgr_refresh_info)
        # This one does not exist
        config.set_zone_list_from_name_classes(["example.net", "CH"])
        self.zone_refresh.update_config_data(config, self.cc_session)
        self.assertFalse(("example.net.", "CH") in
                        self.zone_refresh._zonemgr_refresh_info)
        # Simply skip loading soa for the zone, the other configs should be updated successful
        self.assertFalse(("example.net.", "IN") in
                        self.zone_refresh._zonemgr_refresh_info)
        # Make sure it works even when we "accidentally" forget the final dot
        config.set_zone_list_from_name_classes([("example.net", "IN")])
        self.zone_refresh.update_config_data(config, self.cc_session)
        self.assertTrue(("example.net.", "IN") in
                        self.zone_refresh._zonemgr_refresh_info)

    def tearDown(self):
        sys.stderr= self.stderr_backup


class MyCCSession():
    def __init__(self):
        pass

    def get_remote_config_value(self, module_name, identifier):
        if module_name == "Auth" and identifier == "database_file":
            return "initdb.file", False
        else:
            return "unknown", False


class MyZonemgr(Zonemgr):

    def __init__(self):
        self._db_file = "initdb.file"
        self._zone_refresh = None
        self._shutdown_event = threading.Event()
        self._cc = MySession()
        self._module_cc = MyCCSession()
        self._config_data = {
                    "lowerbound_refresh" : 10,
                    "lowerbound_retry" : 5,
                    "max_transfer_timeout" : 14400,
                    "refresh_jitter" : 0.1,
                    "reload_jitter" : 0.75,
                    "secondary_zones": []
                    }

    def _start_zone_refresh_timer(self):
        pass

class TestZonemgr(unittest.TestCase):

    def setUp(self):
        self.zonemgr = MyZonemgr()

    def test_config_handler(self):
        config_data1 = {
                    "lowerbound_refresh" : 60,
                    "lowerbound_retry" : 30,
                    "max_transfer_timeout" : 14400,
                    "refresh_jitter" : 0.1,
                    "reload_jitter" : 0.75,
                    "secondary_zones": []
                    }
        self.assertEqual(self.zonemgr.config_handler(config_data1),
                         {"result": [0]})
        self.assertEqual(config_data1, self.zonemgr._config_data)
        config_data2 = {"zone_name" : "example.net.", "port" : "53", "master" : "192.168.1.1"}
        self.zonemgr.config_handler(config_data2)
        self.assertEqual(config_data1, self.zonemgr._config_data)
        # jitter should not be bigger than half of the original value
        config_data3 = {"refresh_jitter" : 0.7}
        self.zonemgr.config_handler(config_data3)
        self.assertEqual(0.5, self.zonemgr._config_data.get("refresh_jitter"))
        # The zone doesn't exist in database, simply skip loading soa for it and log an warning
        self.zonemgr._zone_refresh = ZonemgrRefresh(None, "initdb.file", None,
                                                    FakeCCSession())
        config_data1["secondary_zones"] = [{"name": "nonexistent.example",
                                            "class": "IN"}]
        self.assertEqual(self.zonemgr.config_handler(config_data1),
                         {"result": [0]})
        # other configs should be updated successfully
        name_class = ("nonexistent.example.", "IN")
        self.assertTrue(self.zonemgr._zone_refresh._zonemgr_refresh_info[name_class]["zone_soa_rdata"]
                        is None)
        self.assertEqual(0.1, self.zonemgr._config_data.get("refresh_jitter"))

    def test_get_db_file(self):
        self.assertEqual("initdb.file", self.zonemgr.get_db_file())

    def test_parse_cmd_params(self):
        params1 = {"zone_name" : "example.com.", "zone_class" : "CH", "master" : "127.0.0.1"}
        answer1 = (ZONE_NAME_CLASS3_CH, "127.0.0.1")
        self.assertEqual(answer1, self.zonemgr._parse_cmd_params(params1, ZONE_NOTIFY_COMMAND))
        params2 = {"zone_name" : "example.com.", "zone_class" : "IN"}
        answer2 = ZONE_NAME_CLASS3_IN
        self.assertEqual(answer2, self.zonemgr._parse_cmd_params(params2, ZONE_XFRIN_SUCCESS_COMMAND))
        self.assertRaises(ZonemgrException, self.zonemgr._parse_cmd_params, params2, ZONE_NOTIFY_COMMAND)
        params1 = {"zone_class" : "CH"}
        self.assertRaises(ZonemgrException, self.zonemgr._parse_cmd_params, params2, ZONE_NOTIFY_COMMAND)

    def test_config_data_check(self):
        # jitter should not be bigger than half of the original value
        config_data2 = {"refresh_jitter" : 0.2}
        config_data3 = {"refresh_jitter" : 0.6}
        self.zonemgr._config_data_check(config_data2)
        self.assertEqual(0.2, config_data2.get("refresh_jitter"))
        self.zonemgr._config_data_check(config_data3)
        self.assertEqual(0.5, config_data3.get("refresh_jitter"))

    def tearDown(self):
        pass

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
