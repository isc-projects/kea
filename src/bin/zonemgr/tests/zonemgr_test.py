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

'''Tests for the ZoneRefreshInfo and ZoneMgr classes '''


import unittest
import os
import tempfile
from zonemgr import *

class ZonemgrTestException(Exception):
    pass

class MySocket():
    def __init__(self, family, type):
        self.family = family
        self.type = type

    def recv(self, len):
        data = struct.pack('s', " ")
        return data

    def send(self, data):
        pass

    def connect(self):
        pass

    def close(self):
        pass

class MySession():
    def __init__(self):
        pass

    def group_sendmsg(self, msg, module_name):
        if module_name not in ("Auth", "Xfrin"):
            raise ZonemgrTestException("module name not exist")

class MyZoneRefreshInfo(ZoneRefreshInfo):
    def __init__(self):
        self._cc = MySession()
        self._sock_file = UNIX_SOCKET_FILE
        self._db_file = "initdb.file"
        self._zone_name_list = ['sd.cn.', 'tw.cn']
        self._zones_refresh_info = [
        {'last_refresh_time': 1280474398.822142,
         'timeout': 1280481598.822153, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
         'zone_state': 0},
        {'last_refresh_time': 1280474399.116421, 
         'timeout': 1280481599.116433, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600', 
         'zone_state': 0}
        ]

class TestZoneRefreshInfo(unittest.TestCase):
    def setUp(self):
        self.stdout_backup = sys.stdout
        #sys.stdout = open(os.devnull, 'w')
        self.zoneinfo = MyZoneRefreshInfo()

    def test_random_jitter(self):
        max = 100025.120
        jitter = 0
        self.assertEqual(max, self.zoneinfo._random_jitter(max, jitter))
        jitter = max / 4
        self.assertTrue((3 * max / 4) <= self.zoneinfo._random_jitter(max, jitter)) 
        self.assertTrue(self.zoneinfo._random_jitter(max, jitter) <= max) 

    def test_get_current_time(self):
        pass

    def test_set_timer(self):
        max = 3600
        jitter = 900
        time1 = time.time()
        self.zoneinfo._set_timer(0, 3600, 900)
        time2 = time.time()
        zone_timeout = float(self.zoneinfo._zones_refresh_info[0]["timeout"])
        self.assertTrue((3600 - 900) <= (zone_timeout - time1))
        self.assertTrue((zone_timeout - time2) <= 3600)

    def test_set_timer_refresh(self):
        time1 = time.time()
        self.zoneinfo._set_timer_refresh(0)
        zone_timeout = self.zoneinfo._zones_refresh_info[0]["timeout"]
        time2 = time.time()
        self.assertTrue((time1 + 7200 * 3 / 4) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 7200)
        
    def test_set_timer_retry(self):
        time1 = time.time()
        self.zoneinfo._set_timer_retry(0)
        zone_timeout = self.zoneinfo._zones_refresh_info[0]["timeout"]
        time2 = time.time()
        self.assertTrue((time1 + 3600 * 3 / 4) <= zone_timeout)
        self.assertTrue(zone_timeout <= time2 + 3600)

    def test_set_timer_notify(self):
        time1 = time.time()
        self.zoneinfo._set_timer_notify(0)
        zone_timeout = self.zoneinfo._zones_refresh_info[0]["timeout"]
        time2 = time.time()
        self.assertTrue(time1 <= zone_timeout)
        self.assertTrue(zone_timeout <= time2)

    def test_get_zone_index(self):
        self.assertTrue(-1 == self.zoneinfo._get_zone_index("org.cn"))
        self.assertTrue(0 == self.zoneinfo._get_zone_index("sd.cn."))
        self.assertTrue(1 == self.zoneinfo._get_zone_index("tw.cn"))

    def test_zone_is_expired(self):
        current_time = time.time()
        zone_expired_time = 2419200
        self.zoneinfo._zones_refresh_info[0]["last_refresh_time"] = current_time - zone_expired_time - 1
        self.assertTrue(self.zoneinfo._zone_is_expired(0))
        self.zoneinfo._zones_refresh_info[0]["last_refresh_time"] = current_time - zone_expired_time + 1
        self.assertFalse(self.zoneinfo._zone_is_expired(0))
        self.zoneinfo._zones_refresh_info[0]["zone_state"] = ZONE_EXPIRED
        self.assertTrue(self.zoneinfo._zone_is_expired(0))

    def test_get_zone_names(self):
        zone_name_list = ["org.cn"]
        def get_zone_names(db_file):
            return zone_name_list
        sqlite3_ds.get_zone_names = get_zone_names

        self.assertEqual(zone_name_list, self.zoneinfo._get_zone_names())
    
    def test_get_zone_soa_rdata(self):
        soa_rdata1  = 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600' 
        soa_rdata2  = 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600' 
        self.assertEqual(soa_rdata1, self.zoneinfo._get_zone_soa_rdata(0))
        self.assertEqual(soa_rdata2, self.zoneinfo._get_zone_soa_rdata(1))
         
    def test_zonemgr_reload_zone(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zoneinfo._zonemgr_reload_zone(0)
        self.assertEqual(soa_rdata, self.zoneinfo._zones_refresh_info[0]["zone_soa_rdata"])

    def test_get_zone_notifier_master(self):
        notify_master = ["192.168.1.1", 53]
        self.assertEqual(None, self.zoneinfo._get_zone_notifier_master(0))
        self.zoneinfo._zones_refresh_info[0]["notify_master"] = notify_master
        self.assertEqual(notify_master, self.zoneinfo._get_zone_notifier_master(0))

    def test_set_zone_notifier_master(self):
        notify_master = ["192.168.1.1", 53]
        self.zoneinfo._set_zone_notifier_master(0, notify_master)
        self.assertEqual(self.zoneinfo._zones_refresh_info[0]["notify_master"], notify_master)

    def test_clear_zone_notifier_master(self):
        notify_master = ["192.168.1.1", 53]
        self.zoneinfo._zones_refresh_info[0]["notify_master"] = notify_master
        self.zoneinfo._clear_zone_notifier_master(0)
        self.assertFalse("notify_master" in self.zoneinfo._zones_refresh_info[0].keys())
        self.zoneinfo._clear_zone_notifier_master(1)
        self.assertFalse("notify_master" in self.zoneinfo._zones_refresh_info[1].keys())

    def test_get_zone_state(self):
        self.assertEqual(ZONE_OK, self.zoneinfo._get_zone_state(0))
        self.assertEqual(ZONE_OK, self.zoneinfo._get_zone_state(1))

    def test_set_zone_state(self):
        self.zoneinfo._set_zone_state(0, ZONE_REFRESHING)
        self.zoneinfo._set_zone_state(1, ZONE_EXPIRED)
        self.assertEqual(ZONE_REFRESHING, self.zoneinfo._zones_refresh_info[0]["zone_state"])
        self.assertEqual(ZONE_EXPIRED, self.zoneinfo._zones_refresh_info[1]["zone_state"])

    def test_get_zone_refresh_timeout(self):
        current_time = time.time()
        self.assertFalse("fresh_timeout" in self.zoneinfo._zones_refresh_info[0].keys())
        self.zoneinfo._zones_refresh_info[0]["fresh_timeout"] = current_time
        self.assertEqual(current_time, self.zoneinfo._get_zone_refresh_timeout(0))

    def test_set_zone_refresh_timeout(self):
        current_time = time.time()
        self.zoneinfo._set_zone_refresh_timeout(0, current_time)
        self.assertEqual(current_time, self.zoneinfo._zones_refresh_info[0]["fresh_timeout"])

    def test_get_zone_timeout(self):
        current_time = time.time()
        self.zoneinfo._zones_refresh_info[0]["timeout"] = current_time
        self.assertEqual(current_time, self.zoneinfo._get_zone_timeout(0))

    def test_set_zone_timeout(self):
        current_time = time.time()
        self.zoneinfo._set_zone_timeout(0, current_time)
        self.assertEqual(current_time, self.zoneinfo._zones_refresh_info[0]["timeout"])

    def test_get_zone_last_refresh_time(self):
        current_time = time.time()
        self.zoneinfo._zones_refresh_info[0]["last_refresh_time"] = current_time
        self.assertEqual(current_time, self.zoneinfo._get_zone_last_refresh_time(0))

    def test_set_zone_last_refresh_time(self):
        current_time = time.time()
        self.zoneinfo._set_zone_last_refresh_time(0, current_time)
        self.assertEqual(current_time, self.zoneinfo._zones_refresh_info[0]["last_refresh_time"])

    def test_send_command(self):
        self.assertRaises(ZonemgrTestException, self.zoneinfo._send_command, "Unknown", "Notify", None)

    def test_zone_mgr_is_empty(self):
        self.assertFalse(self.zoneinfo._zone_mgr_is_empty())
        self.zoneinfo._zones_refresh_info = []
        self.assertTrue(self.zoneinfo._zone_mgr_is_empty())

    def test_build_zonemgr_refresh_info(self):
        zone_name_list = ["sd.cn."]
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'

        def get_zone_names(db_file):
            return zone_name_list

        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')

        sqlite3_ds.get_zone_names = get_zone_names
        sqlite3_ds.get_zone_soa = get_zone_soa

        self.zoneinfo._zones_refresh_info = []
        self.zoneinfo._build_zonemgr_refresh_info()
        self.assertEqual(1, len(self.zoneinfo._zones_refresh_info))
        self.assertEqual(soa_rdata, self.zoneinfo._zones_refresh_info[0]["zone_soa_rdata"])
        self.assertEqual(ZONE_OK, self.zoneinfo._zones_refresh_info[0]["zone_state"])
        self.assertTrue("last_refresh_time" in self.zoneinfo._zones_refresh_info[0].keys())
        self.assertTrue("timeout" in self.zoneinfo._zones_refresh_info[0].keys())

    def test_zone_handle_notify(self):
        self.zoneinfo.zone_handle_notify("sd.cn.", "127.0.0.1", 53)
        self.assertEqual(["127.0.0.1", 53], self.zoneinfo._zones_refresh_info[0]["notify_master"])
        zone_timeout = float(self.zoneinfo._zones_refresh_info[0]["timeout"])
        current_time = time.time()
        self.assertTrue(zone_timeout <= current_time)
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_handle_notify,
                          "org.cn.", "127.0.0.1", 53)

    def test_zone_refresh_success(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600'
        def get_zone_soa(zone_name, db_file):
            return (1, 2, 'sd.cn.', 'cn.sd.', 21600, 'SOA', None, 
                    'a.dns.cn. root.cnnic.cn. 2009073106 1800 900 2419200 21600')
        sqlite3_ds.get_zone_soa = get_zone_soa
        time1 = time.time()
        self.zoneinfo._zones_refresh_info[0]["zone_state"] = ZONE_REFRESHING
        self.zoneinfo.zone_refresh_success("sd.cn.")
        time2 = time.time()
        self.assertEqual(soa_rdata, self.zoneinfo._zones_refresh_info[0]["zone_soa_rdata"])
        self.assertTrue((time1 + 3 * 1800 / 4) <= self.zoneinfo._zones_refresh_info[0]["timeout"])
        self.assertTrue(self.zoneinfo._zones_refresh_info[0]["timeout"] <= time2 + 1800)
        self.assertEqual(ZONE_OK, self.zoneinfo._zones_refresh_info[0]["zone_state"])
        self.assertTrue(time1 <= self.zoneinfo._zones_refresh_info[0]["last_refresh_time"])
        self.assertTrue(self.zoneinfo._zones_refresh_info[0]["last_refresh_time"] <= time2)
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_refresh_success, "org.cn.")

    def test_zone_refresh_fail(self):
        soa_rdata = 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600' 
        time1 = time.time()
        self.zoneinfo._zones_refresh_info[0]["zone_state"] = ZONE_REFRESHING
        self.zoneinfo.zone_refresh_fail("sd.cn.")
        time2 = time.time()
        self.assertEqual(soa_rdata, self.zoneinfo._zones_refresh_info[0]["zone_soa_rdata"])
        self.assertTrue((time1 + 3 * 3600 / 4) <= self.zoneinfo._zones_refresh_info[0]["timeout"])
        self.assertTrue(self.zoneinfo._zones_refresh_info[0]["timeout"] <= time2 + 3600)
        self.assertEqual(ZONE_OK, self.zoneinfo._zones_refresh_info[0]["zone_state"])
        self.assertRaises(ZonemgrException, self.zoneinfo.zone_refresh_success, "org.cn.")

    def test_find_minimum_timeout_zone(self):
        time1 = time.time()
        self.zoneinfo._zones_refresh_info = [
        {'last_refresh_time': time1,
         'timeout': time1 + 7200, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
         'zone_state': ZONE_OK},
        {'last_refresh_time': time1 - 7200, 
         'timeout': time1, 
         'fresh_timeout': time1 + MAX_TRANSFER_TIMEOUT, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073112 7200 3600 2419200 21600', 
         'zone_state': ZONE_REFRESHING}
        ]
        zone_index = self.zoneinfo._find_minimum_timeout_zone()
        self.assertEqual(0, zone_index)

        self.zoneinfo._zones_refresh_info[0]["last_refresh_time"] = time1 - 2419200
        self.zoneinfo._zones_refresh_info[0]["zone_state"] = ZONE_EXPIRED
        zone_index = self.zoneinfo._find_minimum_timeout_zone()
        self.assertEqual(-1, zone_index)

        self.zoneinfo._zones_refresh_info[0]["zone_state"] = ZONE_REFRESHING
        self.zoneinfo._zones_refresh_info[0]["notify_master"] = ["192.168.0.1", 6363]
        zone_index = self.zoneinfo._find_minimum_timeout_zone()
        self.assertEqual(0, zone_index)
        self.assertEqual(ZONE_EXPIRED, self.zoneinfo._zones_refresh_info[0]["zone_state"])

        self.zoneinfo._zones_refresh_info[1]["fresh_timeout"] = time1 
        zone_index = self.zoneinfo._find_minimum_timeout_zone()
        self.assertEqual(1, zone_index)

    def test_do_refresh(self):
        time1 = time.time()
        self.zoneinfo._zones_refresh_info = [
        {'last_refresh_time': time1 - 7200,
         'timeout': time1 - 1, 
         'zone_soa_rdata': 'a.dns.cn. root.cnnic.cn. 2009073105 7200 3600 2419200 21600', 
         'zone_state': ZONE_OK}
        ]
        self.zoneinfo._do_refresh(0)
        time2 = time.time()
        self.assertEqual(ZONE_REFRESHING, self.zoneinfo._zones_refresh_info[0]["zone_state"])
        self.assertTrue(time1 + MAX_TRANSFER_TIMEOUT <= 
                        self.zoneinfo._zones_refresh_info[0]["fresh_timeout"])
        self.assertTrue(time2 + MAX_TRANSFER_TIMEOUT >= 
                        self.zoneinfo._zones_refresh_info[0]["fresh_timeout"])
        self.zoneinfo._zones_refresh_info[0]["notify_master"] = ["127.0.0.1", 53]
        self.zoneinfo._do_refresh(0)
        time2 = time.time()
        self.assertEqual(ZONE_REFRESHING, self.zoneinfo._zones_refresh_info[0]["zone_state"])
        self.assertTrue(time1 + MAX_TRANSFER_TIMEOUT <= 
                        self.zoneinfo._zones_refresh_info[0]["fresh_timeout"])
        self.assertTrue(time2 + MAX_TRANSFER_TIMEOUT >= 
                        self.zoneinfo._zones_refresh_info[0]["fresh_timeout"])
        self.assertFalse("notify_master" in self.zoneinfo._zones_refresh_info[0].keys())

    def test_connect_server(self):
        self.assertRaises(ZonemgrException, self.zoneinfo._connect_server)

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
        self._conn, addr = (None, None)
        self._shutdown_event = threading.Event()
        self._cc = MySession()
        self._module_cc = MyCCSession()
        self._config_data = {"zone_name" : "org.cn", "master" : "127.0.0.1", "port" : 53}

    def _start_zone_refresh_timer(self):
        pass

class TestZonemgr(unittest.TestCase):

    def setUp(self):
        self.zonemgr = MyZonemgr()

    def test_config_handler(self):
        config_data = {"zone_name" : "sd.cn.", "master" : "192.168.1.1", "port" : 53}
        self.zonemgr.config_handler(config_data)
        self.assertEqual(config_data, self.zonemgr._config_data)

    def test_get_db_file(self):
        self.assertEqual("initdb.file", self.zonemgr.get_db_file())
    
    def test_sock_file_in_use(self):
        sock_file = tempfile.NamedTemporaryFile(mode='w',
                                                prefix="b10",
                                                delete=True)
        sock_file_name = sock_file.name
        if (os.path.exists(sock_file_name)):
            os.unlink(sock_file_name)
        self.assertFalse(self.zonemgr._sock_file_in_use(sock_file_name))
        self.zonemgr._create_notify_socket(sock_file_name)
        self.assertTrue(self.zonemgr._sock_file_in_use(sock_file_name))
        sock_file.close()

    def test_parse_cmd_params(self):
        params1 = {"zone_name" : "org.cn", "master" : "127.0.0.1", "port" : "53"}
        answer = ("org.cn", "127.0.0.1", "53")
        self.assertEqual(answer, self.zonemgr._parse_cmd_params(params1))
        params2 = {"zone_name" : "org.cn", "master" : "127.0.0.1"}
        self.assertEqual(answer, self.zonemgr._parse_cmd_params(params2))

    def test_remove_unused_sock_file(self):
        sock_file = tempfile.NamedTemporaryFile(mode='w',
                                                prefix="b10",
                                                delete=True)
        sock_file_name = sock_file.name
        self.assertFalse(self.zonemgr._sock_file_in_use(sock_file_name))

    def tearDown(self):
        pass

class TestAddr(unittest.TestCase):

    def test_check_port(self):
        self.assertRaises(ZonemgrException, check_port, "-1")
        self.assertRaises(ZonemgrException, check_port, "65536")
        self.assertRaises(ZonemgrException, check_port, "OK")

    def test_check_addr(self):
        self.assertRaises(ZonemgrException, check_addr, "192.168.256.222")
        self.assertRaises(ZonemgrException, check_addr, "ff:00:00::ge")
        self.assertRaises(ZonemgrException, check_addr, "OK")

if __name__== "__main__":
    unittest.main()
