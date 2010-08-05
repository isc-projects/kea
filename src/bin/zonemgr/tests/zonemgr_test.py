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

'''Tests for the ZoneMgrRefreshInfo and ZoneMgr classes '''


import unittest
import os
import tempfile
from zonemgr import *

ZONE_NAME_CLASS1 = ("sd.cn.", "IN")
ZONE_NAME_CLASS2 = ("tw.cn", "IN")
ZONE_NAME_CLASS3 = ("example.com", "IN")

class ZonemgrTestException(Exception):
    pass

class MySession():
    def __init__(self):
        pass

    def group_sendmsg(self, msg, module_name):
        if module_name not in ("Auth", "Xfrin"):
            raise ZonemgrTestException("module name not exist")

class MyZoneMgrRefreshInfo(ZoneMgrRefreshInfo):
    def __init__(self):
        self._cc = MySession()
        self._db_file = "initdb.file"
        self._zonemgr_refresh_info = { 
         ('sd.cn.', 'IN'): {
         'last_refresh_time': 1280474398.822142,
         'next_refresh_time': 1280481598.822153, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
         'zone_state': 0},
         ('tw.cn', 'IN'): {
         'last_refresh_time': 1280474399.116421, 
         'next_refresh_time': 1280481599.116433, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600', 
         'zone_state': 0}
        } 

class TestZoneMgrRefreshInfo(unittest.TestCase):
    def setUp(self):
        self.stdout_backup = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.zoneinfo = MyZoneMgrRefreshInfo()

    def test_random_jitter(self):
        max = 100025.120
        jitter = 0
        self.assertEqual(max, self.zoneinfo._random_jitter(max, jitter))
        jitter = max / 4
        self.assertTrue((3 * max / 4) <= self.zoneinfo._random_jitter(max, jitter)) 
        self.assertTrue(self.zoneinfo._random_jitter(max, jitter) <= max) 

    def test_get_current_time(self):
        pass

    def test_set_zone_timer(self):
        max = 3600
        jitter = 900
        time1 = time.time()
        self.zoneinfo._set_zone_timer(ZONE_NAME_CLASS1, 3600, 900)
        time2 = time.time()
        zone_timeout = float(self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"])
        self.assertTrue((3600 - 900) <= (zone_timeout - time1))
        self.assertTrue((zone_timeout - time2) <= 3600)

    def test_set_zone_refresh_timer(self):
        time1 = time.time()
        self.zoneinfo._set_zone_refresh_timer(ZONE_NAME_CLASS1)
        zone_timeout = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue((time1 + 7200 * 3 / 4) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 7200)
        
    def test_set_zone_retry_timer(self):
        time1 = time.time()
        self.zoneinfo._set_zone_retry_timer(ZONE_NAME_CLASS1)
        zone_timeout = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue((time1 + 3600 * 3 / 4) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 3600)

    def test_zone_not_exist(self):
        self.assertFalse(self.zoneinfo._zone_not_exist(ZONE_NAME_CLASS1))
        self.assertFalse(self.zoneinfo._zone_not_exist(ZONE_NAME_CLASS2))
        self.assertTrue(self.zoneinfo._zone_not_exist(ZONE_NAME_CLASS3))

    def test_set_zone_notify_timer(self):
        time1 = time.time()
        self.zoneinfo._set_zone_notify_timer(ZONE_NAME_CLASS1)
        zone_timeout = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"]
        time2 = time.time()
        self.assertTrue(time1 <= zone_timeout)
        self.assertTrue(zone_timeout <= time2)

    def test_zone_is_expired(self):
        current_time = time.time()
        zone_expired_time = 2419200
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["last_refresh_time"] = \
                                                  current_time - zone_expired_time - 1
        self.assertTrue(self.zoneinfo._zone_is_expired(ZONE_NAME_CLASS1))
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["last_refresh_time"] = \
                                                  current_time - zone_expired_time + 1
        self.assertFalse(self.zoneinfo._zone_is_expired(ZONE_NAME_CLASS1))
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"] = ZONE_EXPIRED
        self.assertTrue(self.zoneinfo._zone_is_expired(ZONE_NAME_CLASS1))

    def test_get_zone_soa_rdata(self):
        soa_rdata1  = 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600' 
        soa_rdata2  = 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600' 
        self.assertEqual(soa_rdata1, self.zoneinfo._get_zone_soa_rdata(ZONE_NAME_CLASS1))
        self.assertEqual(soa_rdata2, self.zoneinfo._get_zone_soa_rdata(ZONE_NAME_CLASS2))
         
    def test_zonemgr_reload_zone(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zoneinfo._zonemgr_reload_zone(ZONE_NAME_CLASS1)
        self.assertEqual(soa_rdata, self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_soa_rdata"])

    def test_get_zone_notifier_master(self):
        notify_master = "192.168.1.1"
        self.assertEqual(None, self.zoneinfo._get_zone_notifier_master(ZONE_NAME_CLASS1))
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["notify_master"] = notify_master
        self.assertEqual(notify_master, self.zoneinfo._get_zone_notifier_master(ZONE_NAME_CLASS1))

    def test_set_zone_notifier_master(self):
        notify_master = "192.168.1.1"
        self.zoneinfo._set_zone_notifier_master(ZONE_NAME_CLASS1, notify_master)
        self.assertEqual(self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]\
                                                                ["notify_master"], notify_master)

    def test_clear_zone_notifier_master(self):
        notify_master = "192.168.1.1"
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["notify_master"] = notify_master
        self.zoneinfo._clear_zone_notifier_master(ZONE_NAME_CLASS1)
        self.assertFalse("notify_master" in self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1].keys())
        self.zoneinfo._clear_zone_notifier_master(ZONE_NAME_CLASS2)
        self.assertFalse("notify_master" in self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS2].keys())

    def test_get_zone_state(self):
        self.assertEqual(ZONE_OK, self.zoneinfo._get_zone_state(ZONE_NAME_CLASS2))
        self.assertEqual(ZONE_OK, self.zoneinfo._get_zone_state(ZONE_NAME_CLASS2))

    def test_set_zone_state(self):
        self.zoneinfo._set_zone_state(ZONE_NAME_CLASS1, ZONE_REFRESHING)
        self.zoneinfo._set_zone_state(ZONE_NAME_CLASS2, ZONE_EXPIRED)
        self.assertEqual(ZONE_REFRESHING, \
                self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"])
        self.assertEqual(ZONE_EXPIRED, \
                self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS2]["zone_state"])

    def test_get_zone_refresh_timeout(self):
        current_time = time.time()
        self.assertFalse("refresh_timeout" in self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1].keys())
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["refresh_timeout"] = current_time
        self.assertEqual(current_time, self.zoneinfo._get_zone_refresh_timeout(ZONE_NAME_CLASS1))

    def test_set_zone_refresh_timeout(self):
        current_time = time.time()
        self.zoneinfo._set_zone_refresh_timeout(ZONE_NAME_CLASS1, current_time)
        refresh_time = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["refresh_timeout"]
        self.assertEqual(current_time, refresh_time) 

    def test_get_zone_next_refresh_time(self):
        current_time = time.time()
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"] = current_time
        self.assertEqual(current_time, self.zoneinfo._get_zone_next_refresh_time(ZONE_NAME_CLASS1))

    def test_set_zone_next_refresh_time(self):
        current_time = time.time()
        self.zoneinfo._set_zone_next_refresh_time(ZONE_NAME_CLASS1, current_time)
        next_refresh_time = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"]
        self.assertEqual(current_time, next_refresh_time)

    def test_get_zone_last_refresh_time(self):
        current_time = time.time()
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["last_refresh_time"] = current_time
        self.assertEqual(current_time, self.zoneinfo._get_zone_last_refresh_time(ZONE_NAME_CLASS1))

    def test_set_zone_last_refresh_time(self):
        current_time = time.time()
        self.zoneinfo._set_zone_last_refresh_time(ZONE_NAME_CLASS1, current_time)
        last_refresh_time = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["last_refresh_time"]
        self.assertEqual(current_time, last_refresh_time) 

    def test_send_command(self):
        self.assertRaises(ZonemgrTestException, self.zoneinfo._send_command, "Unknown", "Notify", None)

    def test_zone_mgr_is_empty(self):
        self.assertFalse(self.zoneinfo._zone_mgr_is_empty())
        self.zoneinfo._zonemgr_refresh_info = {} 
        self.assertTrue(self.zoneinfo._zone_mgr_is_empty())

    def test_build_zonemgr_refresh_info(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'

        def get_zones_info(db_file):
            return [("sd.cn.", "IN")] 

        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')

        sqlite3_ds.get_zones_info = get_zones_info
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zoneinfo._zonemgr_refresh_info = {}
        self.zoneinfo._build_zonemgr_refresh_info()
        self.assertEqual(1, len(self.zoneinfo._zonemgr_refresh_info))
        zone_soa_rdata = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata) 
        self.assertEqual(ZONE_OK, self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"])
        self.assertTrue("last_refresh_time" in self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1].keys())
        self.assertTrue("next_refresh_time" in self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1].keys())

    def test_zone_handle_notify(self):
        self.zoneinfo.zone_handle_notify(ZONE_NAME_CLASS1,"127.0.0.1")
        notify_master = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["notify_master"]
        self.assertEqual("127.0.0.1", notify_master) 
        zone_timeout = float(self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"])
        current_time = time.time()
        self.assertTrue(zone_timeout <= current_time)
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_handle_notify,\
                          "org.cn.", "127.0.0.1")
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_handle_notify,\
                          ZONE_NAME_CLASS3, "127.0.0.1")

    def test_zone_refresh_success(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa
        time1 = time.time()
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"] = ZONE_REFRESHING
        self.zoneinfo.zone_refresh_success(ZONE_NAME_CLASS1)
        time2 = time.time()
        zone_soa_rdata = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata) 
        next_refresh_time = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"]
        self.assertTrue((time1 + 3 * 1800 / 4) <= next_refresh_time) 
        self.assertTrue(next_refresh_time <= time2 + 1800)
        self.assertEqual(ZONE_OK, self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"])
        last_refresh_time = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["last_refresh_time"]
        self.assertTrue(time1 <= last_refresh_time)
        self.assertTrue(last_refresh_time <= time2)
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_refresh_success, "org.cn.")
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_refresh_success, ZONE_NAME_CLASS3) 

    def test_zone_refresh_fail(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600' 
        time1 = time.time()
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"] = ZONE_REFRESHING
        self.zoneinfo.zone_refresh_fail(ZONE_NAME_CLASS1)
        time2 = time.time()
        zone_soa_rdata = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_soa_rdata"]
        self.assertEqual(soa_rdata, zone_soa_rdata)
        next_refresh_time = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["next_refresh_time"]
        self.assertTrue((time1 + 3 * 3600 / 4) <= next_refresh_time)
        self.assertTrue(next_refresh_time <= time2 + 3600)
        self.assertEqual(ZONE_OK, self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"])
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_refresh_fail, "org.cn.")
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_refresh_fail, ZONE_NAME_CLASS3) 

    def test_find_need_do_refresh_zone(self):
        time1 = time.time()
        self.zoneinfo._zonemgr_refresh_info = { 
                ("sd.cn.","IN"):{
                    'last_refresh_time': time1,
                    'next_refresh_time': time1 + 7200, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
                    'zone_state': ZONE_OK},
                ("tw.cn","IN"):{
                    'last_refresh_time': time1 - 7200, 
                    'next_refresh_time': time1, 
                    'refresh_timeout': time1 + MAX_TRANSFER_TIMEOUT, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600', 
                    'zone_state': ZONE_REFRESHING}
                }
        zone_need_refresh = self.zoneinfo._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS1, zone_need_refresh)

        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["last_refresh_time"] = time1 - 2419200
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"] = ZONE_EXPIRED
        zone_need_refresh = self.zoneinfo._find_need_do_refresh_zone()
        self.assertEqual(None, zone_need_refresh)

        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"] = ZONE_REFRESHING
        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["notify_master"] = "192.168.0.1"
        zone_need_refresh = self.zoneinfo._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS1, zone_need_refresh)
        self.assertEqual(ZONE_EXPIRED, self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"])

        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS2]["refresh_timeout"] = time1 
        zone_need_refresh = self.zoneinfo._find_need_do_refresh_zone()
        self.assertEqual(ZONE_NAME_CLASS2, zone_need_refresh)

    def test_do_refresh(self):
        time1 = time.time()
        self.zoneinfo._zonemgr_refresh_info = {
                ("sd.cn.", "IN"):{
                    'last_refresh_time': time1 - 7200,
                    'next_refresh_time': time1 - 1, 
                    'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
                    'zone_state': ZONE_OK}
                }
        self.zoneinfo._do_refresh(ZONE_NAME_CLASS1)
        time2 = time.time()
        zone_state = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"]
        self.assertEqual(ZONE_REFRESHING, zone_state)
        refresh_timeout = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["refresh_timeout"] 
        self.assertTrue(time1 + MAX_TRANSFER_TIMEOUT <= refresh_timeout)
        self.assertTrue(time2 + MAX_TRANSFER_TIMEOUT >= refresh_timeout) 

        self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["notify_master"] = "127.0.0.1"
        self.zoneinfo._do_refresh(ZONE_NAME_CLASS1)
        time2 = time.time()
        zone_state = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["zone_state"]
        self.assertEqual(ZONE_REFRESHING, zone_state) 
        refrsh_timeout = self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1]["refresh_timeout"] 
        self.assertTrue(time1 + MAX_TRANSFER_TIMEOUT <= refresh_timeout)
        self.assertTrue(time2 + MAX_TRANSFER_TIMEOUT >= refresh_timeout)
        self.assertFalse("notify_master" in self.zoneinfo._zonemgr_refresh_info[ZONE_NAME_CLASS1].keys())

    def test_shutdown(self):
        pass

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
        self._config_data = {"zone_name" : "org.cn", "zone_class" : "IN", "master" : "127.0.0.1"}

    def _start_zone_refresh_timer(self):
        pass

class TestZonemgr(unittest.TestCase):

    def setUp(self):
        self.zonemgr = MyZonemgr()

    def test_config_handler(self):
        config_data1 = {"zone_name" : "sd.cn.", "zone_class" : "IN", "master" : "192.168.1.1"}
        self.zonemgr.config_handler(config_data1)
        self.assertEqual(config_data1, self.zonemgr._config_data)
        config_data2 = {"zone_name" : "sd.cn.", "port" : "53", "master" : "192.168.1.1"}
        self.zonemgr.config_handler(config_data2)
        self.assertEqual(config_data1, self.zonemgr._config_data)

    def test_get_db_file(self):
        self.assertEqual("initdb.file", self.zonemgr.get_db_file())
    
    def test_parse_cmd_params(self):
        params1 = {"zone_name" : "org.cn", "zone_class" : "IN", "master" : "127.0.0.1"}
        answer1 = ("org.cn", "IN", "127.0.0.1")
        self.assertEqual(answer1, self.zonemgr._parse_cmd_params(params1, ZONE_NOTIFY_COMMAND))
        params2 = {"zone_name" : "org.cn", "zone_class" : "IN"}
        answer2 = ("org.cn", "IN")
        self.assertEqual(answer2, self.zonemgr._parse_cmd_params(params2, ZONE_XFRIN_SUCCESS_COMMAND))
        self.assertRaises(ZonemgrException, self.zonemgr._parse_cmd_params, params2, ZONE_NOTIFY_COMMAND)
        params1 = {"zone_class" : "IN"}
        self.assertRaises(ZonemgrException, self.zonemgr._parse_cmd_params, params2, ZONE_NOTIFY_COMMAND)

    def tearDown(self):
        pass

if __name__== "__main__":
    unittest.main()
