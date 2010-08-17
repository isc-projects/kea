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

ZONE_NAME_CLASS1_IN = ("sd.cn.", "IN")
ZONE_NAME_CLASS2_CH = ("tw.cn", "CH")
ZONE_NAME_CLASS3_IN = ("example.com", "IN")
ZONE_NAME_CLASS1_CH = ("sd.cn.", "CH")
ZONE_NAME_CLASS2_IN = ("tw.cn", "IN")

class ZonemgrTestException(Exception):
    pass

class MySession():
    def __init__(self):
        pass

    def group_sendmsg(self, msg, module_name):
        if module_name not in ("Auth", "Xfrin"):
            raise ZonemgrTestException("module name not exist")

class MyZonemgrRefresh(ZonemgrRefresh):
    def __init__(self):
        self._cc = MySession()
        self._db_file = "initdb.file"
        self._zonemgr_refresh_info = { 
         ('sd.cn.', 'IN'): {
         'last_refresh_time': 1280474398.822142,
         'next_refresh_time': 1280481598.822153, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
         'zone_state': 0},
         ('tw.cn', 'CH'): {
         'last_refresh_time': 1280474399.116421, 
         'next_refresh_time': 1280481599.116433, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600', 
         'zone_state': 0}
        } 

class TestZonemgrRefresh(unittest.TestCase):
    def setUp(self):
        self.stdout_backup = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.zone_refresh = MyZonemgrRefresh()

    def test_random_jitter(self):
        max = 100025.120
        jitter = 0
        self.assertEqual(max, self.zone_refresh._random_jitter(max, jitter))
        jitter = max / 4
        for i in range (0, 150):
            self.assertTrue((3 * max / 4) <= self.zone_refresh._random_jitter(max, jitter)) 
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
        self.assertTrue((time1 + 7200 * 3 / 4) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 7200)
        
    def test_set_zone_retry_timer(self):
        time1 = time.time()
        self.zone_refresh._set_zone_retry_timer(ZONE_NAME_CLASS1_IN)
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue((time1 + 3600 * 3 / 4) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 3600)

    def test_zone_not_exist(self):
        self.assertFalse(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS1_IN))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS1_CH))
        self.assertFalse(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS2_CH))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS2_IN))
        self.assertTrue(self.zone_refresh._zone_not_exist(ZONE_NAME_CLASS3_IN))

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
        soa_rdata1  = 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600' 
        soa_rdata2  = 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600' 
        self.assertEqual(soa_rdata1, self.zone_refresh._get_zone_soa_rdata(ZONE_NAME_CLASS1_IN))
        self.assertRaises(KeyError, self.zone_refresh._get_zone_soa_rdata, ZONE_NAME_CLASS1_CH)
        self.assertEqual(soa_rdata2, self.zone_refresh._get_zone_soa_rdata(ZONE_NAME_CLASS2_CH))
        self.assertRaises(KeyError, self.zone_refresh._get_zone_soa_rdata, ZONE_NAME_CLASS2_IN)
         
    def test_zonemgr_reload_zone(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zone_refresh.zonemgr_reload_zone(ZONE_NAME_CLASS1_IN)
        self.assertEqual(soa_rdata, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"])

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
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'

        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')

        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zone_refresh._zonemgr_refresh_info = {}
        self.zone_refresh.zonemgr_add_zone(ZONE_NAME_CLASS1_IN)
        self.assertEqual(1, len(self.zone_refresh._zonemgr_refresh_info))
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata) 
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        self.assertTrue("last_refresh_time" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.assertTrue("next_refresh_time" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())

        def get_zone_soa2(zone_name, db_file):
            return None
        sqlite3_ds.get_zone_soa = get_zone_soa2
        self.assertRaises(ZonemgrException, self.zone_refresh.zonemgr_add_zone, \
                                          ZONE_NAME_CLASS1_IN)

    def test_build_zonemgr_refresh_info(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'

        def get_zones_info(db_file):
            return [("sd.cn.", "IN")] 

        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')

        sqlite3_ds.get_zones_info = get_zones_info
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zone_refresh._zonemgr_refresh_info = {}
        self.zone_refresh._build_zonemgr_refresh_info()
        self.assertEqual(1, len(self.zone_refresh._zonemgr_refresh_info))
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata) 
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        self.assertTrue("last_refresh_time" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.assertTrue("next_refresh_time" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())

    def test_zone_handle_notify(self):
        self.zone_refresh.zone_handle_notify(ZONE_NAME_CLASS1_IN,"127.0.0.1")
        notify_master = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["notify_master"]
        self.assertEqual("127.0.0.1", notify_master) 
        zone_timeout = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        current_time = time.time()
        self.assertTrue(zone_timeout <= current_time)
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_handle_notify,\
                          ("org.cn.", "IN"), "127.0.0.1")
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_handle_notify,\
                          ZONE_NAME_CLASS3_IN, "127.0.0.1")

    def test_zone_refresh_success(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_REFRESHING
        self.zone_refresh.zone_refresh_success(ZONE_NAME_CLASS1_IN)
        time2 = time.time()
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata) 
        next_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertTrue((time1 + 3 * 1800 / 4) <= next_refresh_time) 
        self.assertTrue(next_refresh_time <= time2 + 1800)
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        last_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"]
        self.assertTrue(time1 <= last_refresh_time)
        self.assertTrue(last_refresh_time <= time2)
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_success, ("org.cn.", "CH"))
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_success, ZONE_NAME_CLASS3_IN) 

    def test_zone_refresh_fail(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600' 
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_REFRESHING
        self.zone_refresh.zone_refresh_fail(ZONE_NAME_CLASS1_IN)
        time2 = time.time()
        zone_soa_rdata = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata)
        next_refresh_time = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["next_refresh_time"]
        self.assertTrue((time1 + 3 * 3600 / 4) <= next_refresh_time)
        self.assertTrue(next_refresh_time <= time2 + 3600)
        self.assertEqual(ZONE_OK, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_fail, ("org.cn.", "CH"))
        self.assertRaises(ZonemgrException, self.zone_refresh.zone_refresh_fail, ZONE_NAME_CLASS3_IN) 

    def test_find_need_do_refresh_zone(self):
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info = { 
                ("sd.cn.","IN"):{
                    'last_refresh_time': time1,
                    'next_refresh_time': time1 + 7200, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
                    'zone_state': ZONE_OK},
                ("tw.cn","CH"):{
                    'last_refresh_time': time1 - 7200, 
                    'next_refresh_time': time1, 
                    'refresh_timeout': time1 + MAX_TRANSFER_TIMEOUT, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600', 
                    'zone_state': ZONE_REFRESHING}
                }
        zone_need_refresh = self.zone_refresh._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS1_IN, zone_need_refresh)

        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["last_refresh_time"] = time1 - 2419200
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_EXPIRED
        zone_need_refresh = self.zone_refresh._find_need_do_refresh_zone()
        self.assertEqual(None, zone_need_refresh)

        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"] = ZONE_REFRESHING
        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["notify_master"] = "192.168.0.1"
        zone_need_refresh = self.zone_refresh._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS1_IN, zone_need_refresh)
        self.assertEqual(ZONE_EXPIRED, self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"])

        self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS2_CH]["refresh_timeout"] = time1 
        zone_need_refresh = self.zone_refresh._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS2_CH, zone_need_refresh)

    def test_do_refresh(self):
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info = {
                ("sd.cn.", "IN"):{
                    'last_refresh_time': time1 - 7200,
                    'next_refresh_time': time1 - 1, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
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
        Then closing the socket ,the timer will stop, and throw a ZonemgrException."""
        time1 = time.time()
        self.zone_refresh._zonemgr_refresh_info = {
                ("sd.cn.", "IN"):{
                    'last_refresh_time': time1 - 7200,
                    'next_refresh_time': time1 - 1, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
                    'zone_state': ZONE_OK}
                }
        master_socket, slave_socket = socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM)
        self.zone_refresh._socket = master_socket 
        master_socket.close()
        self.assertRaises(ZonemgrException, self.zone_refresh.run_timer)

        self.zone_refresh._socket = slave_socket
        listener = threading.Thread(target = self.zone_refresh.run_timer, args = ())
        listener.setDaemon(True)
        listener.start()
        time.sleep(1)

        zone_state = self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN]["zone_state"]
        self.assertTrue("refresh_timeout" in self.zone_refresh._zonemgr_refresh_info[ZONE_NAME_CLASS1_IN].keys())
        self.assertTrue(zone_state == ZONE_REFRESHING)


    def tearDown(self):
        sys.stdout = self.stdout_backup


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
        self._shutdown_event = threading.Event()
        self._cc = MySession()
        self._module_cc = MyCCSession()
        self._config_data = {"zone_name" : "org.cn", "zone_class" : "CH", "master" : "127.0.0.1"}

    def _start_zone_refresh_timer(self):
        pass

class TestZonemgr(unittest.TestCase):

    def setUp(self):
        self.zonemgr = MyZonemgr()

    def test_config_handler(self):
        config_data1 = {"zone_name" : "sd.cn.", "zone_class" : "CH", "master" : "192.168.1.1"}
        self.zonemgr.config_handler(config_data1)
        self.assertEqual(config_data1, self.zonemgr._config_data)
        config_data2 = {"zone_name" : "sd.cn.", "port" : "53", "master" : "192.168.1.1"}
        self.zonemgr.config_handler(config_data2)
        self.assertEqual(config_data1, self.zonemgr._config_data)

    def test_get_db_file(self):
        self.assertEqual("initdb.file", self.zonemgr.get_db_file())
    
    def test_parse_cmd_params(self):
        params1 = {"zone_name" : "org.cn", "zone_class" : "CH", "master" : "127.0.0.1"}
        answer1 = (("org.cn", "CH"), "127.0.0.1")
        self.assertEqual(answer1, self.zonemgr._parse_cmd_params(params1, ZONE_NOTIFY_COMMAND))
        params2 = {"zone_name" : "org.cn", "zone_class" : "CH"}
        answer2 = ("org.cn", "CH")
        self.assertEqual(answer2, self.zonemgr._parse_cmd_params(params2, ZONE_XFRIN_SUCCESS_COMMAND))
        self.assertRaises(ZonemgrException, self.zonemgr._parse_cmd_params, params2, ZONE_NOTIFY_COMMAND)
        params1 = {"zone_class" : "CH"}
        self.assertRaises(ZonemgrException, self.zonemgr._parse_cmd_params, params2, ZONE_NOTIFY_COMMAND)

    def tearDown(self):
        pass

if __name__== "__main__":
    unittest.main()
