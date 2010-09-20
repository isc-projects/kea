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

import unittest
import sys
import os
import tempfile
import time
import socket
from isc.datasrc import sqlite3_ds
from isc.notify import notify_out

class TestZoneNotifyInfo(unittest.TestCase):
    def setUp(self):
        self.info = notify_out.ZoneNotifyInfo('cn.', 'IN')

    def test_prepare_finish_notify_out(self):
        self.info.prepare_notify_out()
        self.assertNotEqual(self.info._sock, None)
        self.assertIsNone(self.info._notify_current)

        self.info.finish_notify_out()
        self.assertEqual(self.info._sock, None)

    def test_set_next_notify_target(self):
        self.info.notify_slaves.append(('127.0.0.1', 53))
        self.info.notify_slaves.append(('1.1.1.1', 5353))
        self.info.prepare_notify_out()
        self.assertEqual(self.info.get_current_notify_target(), ('127.0.0.1', 53))

        self.assertEqual('127.0.0.1#53', notify_out.addr_to_str(('127.0.0.1', 53)))
        self.info.set_next_notify_target()
        self.assertEqual(self.info.get_current_notify_target(), ('1.1.1.1', 5353))
        self.info.set_next_notify_target()
        self.assertIsNone(self.info.get_current_notify_target())

        temp_info = notify_out.ZoneNotifyInfo('com.', 'IN')
        temp_info.prepare_notify_out()
        self.assertIsNone(temp_info.get_current_notify_target())


class TestNotifyOut(unittest.TestCase):
    def setUp(self):
        self.old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self._db_file = tempfile.NamedTemporaryFile(delete=False)
        sqlite3_ds.load(self._db_file.name, 'cn.', self._cn_data_reader)
        sqlite3_ds.load(self._db_file.name, 'com.', self._com_data_reader)
        self._notify = notify_out.NotifyOut(self._db_file.name)
        self._notify._notify_infos[('com.', 'IN')] = notify_out.ZoneNotifyInfo('com.', 'IN')
        self._notify._notify_infos[('com.', 'CH')] = notify_out.ZoneNotifyInfo('com.', 'CH')
        self._notify._notify_infos[('cn.', 'IN')] = notify_out.ZoneNotifyInfo('cn.', 'IN')
        self._notify._notify_infos[('org.', 'IN')] = notify_out.ZoneNotifyInfo('org.', 'IN')
        self._notify._notify_infos[('org.', 'CH')] = notify_out.ZoneNotifyInfo('org.', 'CH')
        
        info = self._notify._notify_infos[('cn.', 'IN')]
        info.notify_slaves.append(('127.0.0.1', 53))
        info.notify_slaves.append(('1.1.1.1', 5353))

    def tearDown(self):
        sys.stdout = self.old_stdout
        self._db_file.close()
        os.unlink(self._db_file.name)

    def test_send_notify(self):
        self._notify.send_notify('cn')
        self.assertEqual(self._notify.notify_num, 1)
        self.assertEqual(self._notify._notifying_zones[0], ('cn.','IN'))

        self._notify.send_notify('com')
        self.assertEqual(self._notify.notify_num, 2)
        self.assertEqual(self._notify._notifying_zones[1], ('com.','IN'))

        notify_out._MAX_NOTIFY_NUM = 3
        self._notify.send_notify('com', 'CH')
        self.assertEqual(self._notify.notify_num, 3)
        self.assertEqual(self._notify._notifying_zones[2], ('com.','CH'))
    
        self._notify.send_notify('org.')
        self.assertEqual(self._notify._waiting_zones[0], ('org.', 'IN'))
        self._notify.send_notify('org.')
        self.assertEqual(1, len(self._notify._waiting_zones))

        self._notify.send_notify('org.', 'CH')
        self.assertEqual(2, len(self._notify._waiting_zones))
        self.assertEqual(self._notify._waiting_zones[1], ('org.', 'CH'))

    def test_wait_for_notify_reply(self):
        self._notify.send_notify('cn.')
        self._notify.send_notify('com.')
    
        notify_out._MAX_NOTIFY_NUM = 2
        self._notify.send_notify('org.')
        replied_zones, timeout_zones = self._notify._wait_for_notify_reply()
        self.assertEqual(len(replied_zones), 0)
        self.assertEqual(len(timeout_zones), 2)

        # Now make one socket be readable
        addr = ('localhost', 12340)
        self._notify._notify_infos[('cn.', 'IN')]._sock.bind(addr)
        self._notify._notify_infos[('cn.', 'IN')].notify_timeout = time.time() + 10
        self._notify._notify_infos[('com.', 'IN')].notify_timeout = time.time() + 10
        
        send_fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        #Send some data to socket 12340, to make the target socket be readable
        send_fd.sendto(b'data', addr)
        replied_zones, timeout_zones = self._notify._wait_for_notify_reply()
        self.assertEqual(len(replied_zones), 1)
        self.assertEqual(len(timeout_zones), 1)
        self.assertTrue(('cn.', 'IN') in replied_zones.keys())
        self.assertTrue(('com.', 'IN') in timeout_zones.keys())
        self.assertLess(time.time(), self._notify._notify_infos[('com.', 'IN')].notify_timeout)
    
    def test_notify_next_target(self):
        self._notify.send_notify('cn.')
        self._notify.send_notify('com.')
        notify_out._MAX_NOTIFY_NUM = 2
        self._notify.send_notify('org.')
        self._notify.send_notify('com.', 'CH')

        info = self._notify._notify_infos[('cn.', 'IN')]
        self._notify._notify_next_target(info)
        self.assertEqual(0, info.notify_try_num)
        self.assertEqual(info.get_current_notify_target(), ('1.1.1.1', 5353))
        self.assertEqual(2, self._notify.notify_num)

        self._notify._notify_next_target(info)
        self.assertEqual(0, info.notify_try_num)
        self.assertIsNone(info.get_current_notify_target())
        self.assertEqual(2, self._notify.notify_num)
        self.assertEqual(1, len(self._notify._waiting_zones))

        com_info = self._notify._notify_infos[('com.', 'IN')]
        self._notify._notify_next_target(com_info)
        self.assertEqual(2, self._notify.notify_num)
        self.assertEqual(0, len(self._notify._notifying_zones))
    
    def test_handle_notify_reply(self):
        self.assertEqual(notify_out._BAD_REPLY_PACKET, self._notify._handle_notify_reply(None, b'badmsg'))
        com_info = self._notify._notify_infos[('com.', 'IN')]
        com_info.notify_msg_id = 0X2f18

        # test with right notify reply message
        data = b'\x2f\x18\xa0\x00\x00\x01\x00\x00\x00\x00\x00\x00\x03com\x00\x00\x06\x00\x01'
        self.assertEqual(notify_out._REPLY_OK, self._notify._handle_notify_reply(com_info, data))

        # test with unright query id
        data = b'\x2e\x18\xa0\x00\x00\x01\x00\x00\x00\x00\x00\x00\x03com\x00\x00\x06\x00\x01'
        self.assertEqual(notify_out._BAD_QUERY_ID, self._notify._handle_notify_reply(com_info, data))

        # test with unright query name
        data = b'\x2f\x18\xa0\x00\x00\x01\x00\x00\x00\x00\x00\x00\x02cn\x00\x00\x06\x00\x01'
        self.assertEqual(notify_out._BAD_QUERY_NAME, self._notify._handle_notify_reply(com_info, data))

        # test with unright opcode
        data = b'\x2f\x18\x80\x00\x00\x01\x00\x00\x00\x00\x00\x00\x03com\x00\x00\x06\x00\x01'
        self.assertEqual(notify_out._BAD_OPCODE, self._notify._handle_notify_reply(com_info, data))

        # test with unright qr
        data = b'\x2f\x18\x10\x10\x00\x01\x00\x00\x00\x00\x00\x00\x03com\x00\x00\x06\x00\x01'
        self.assertEqual(notify_out._BAD_QR, self._notify._handle_notify_reply(com_info, data))

    def test_send_notify_message_udp(self):
        com_info = self._notify._notify_infos[('cn.', 'IN')]
        com_info.prepare_notify_out()
        ret = self._notify._send_notify_message_udp(com_info, ('1.1.1.1', 53))
        self.assertTrue(ret)

    def test_zone_notify_handler(self):
        old_send_msg = self._notify._send_notify_message_udp
        def _fake_send_notify_message_udp(va1, va2): 
            pass
        self._notify._send_notify_message_udp = _fake_send_notify_message_udp
        self._notify.send_notify('cn.')
        self._notify.send_notify('com.')
        notify_out._MAX_NOTIFY_NUM = 2
        self._notify.send_notify('org.')

        cn_info = self._notify._notify_infos[('cn.', 'IN')]
        cn_info.prepare_notify_out()

        cn_info.notify_try_num = 2
        self._notify._zone_notify_handler(cn_info, notify_out._EVENT_TIMEOUT)
        self.assertEqual(3, cn_info.notify_try_num)

        time1 = cn_info.notify_timeout
        self._notify._zone_notify_handler(cn_info, notify_out._EVENT_TIMEOUT)
        self.assertEqual(4, cn_info.notify_try_num)
        self.assertGreater(cn_info.notify_timeout, time1 + 2) # bigger than 2 seconds

        cur_tgt = cn_info._notify_current
        cn_info.notify_try_num = notify_out._MAX_NOTIFY_TRY_NUM
        self._notify._zone_notify_handler(cn_info, notify_out._EVENT_NONE)
        self.assertNotEqual(cur_tgt, cn_info._notify_current)

    def _cn_data_reader(self):
        zone_data = [
        ('cn.',         '1000',  'IN',  'SOA', 'a.dns.cn. mail.cn. 1 1 1 1 1'),
        ('cn.',         '1000',  'IN',  'NS',  'a.dns.cn.'),
        ('cn.',         '1000',  'IN',  'NS',  'b.dns.cn.'),
        ('cn.',         '1000',  'IN',  'NS',  'c.dns.cn.'),
        ('a.dns.cn.',   '1000',  'IN',  'A',    '1.1.1.1'),
        ('a.dns.cn.',   '1000',  'IN',  'AAAA', '2:2::2:2'),
        ('b.dns.cn.',   '1000',  'IN',  'A',    '3.3.3.3'),
        ('b.dns.cn.',   '1000',  'IN',  'AAAA', '4:4::4:4'),
        ('b.dns.cn.',   '1000',  'IN',  'AAAA', '5:5::5:5'),
        ('c.dns.cn.',   '1000',  'IN',  'A',    '6.6.6.6'),
        ('c.dns.cn.',   '1000',  'IN',  'A',    '7.7.7.7'),
        ('c.dns.cn.',   '1000',  'IN',  'AAAA', '8:8::8:8')]
        for item in zone_data:
            yield item

    def _com_data_reader(self):
        zone_data = [
        ('com.',         '1000',  'IN',  'SOA', 'a.dns.com. mail.com. 1 1 1 1 1'),
        ('com.',         '1000',  'IN',  'NS',  'a.dns.com.'),
        ('com.',         '1000',  'IN',  'NS',  'b.dns.com.'),
        ('com.',         '1000',  'IN',  'NS',  'c.dns.com.'),
        ('a.dns.com.',   '1000',  'IN',  'A',    '1.1.1.1'),
        ('b.dns.com.',   '1000',  'IN',  'A',    '3.3.3.3'),
        ('b.dns.com.',   '1000',  'IN',  'AAAA', '4:4::4:4'),
        ('b.dns.com.',   '1000',  'IN',  'AAAA', '5:5::5:5')]
        for item in zone_data:
            yield item

    def test_get_notify_slaves_from_ns(self):
        records = self._notify._get_notify_slaves_from_ns('cn.')
        self.assertEqual(6, len(records))
        self.assertEqual('8:8::8:8', records[5])
        self.assertEqual('7.7.7.7', records[4])
        self.assertEqual('6.6.6.6', records[3])
        self.assertEqual('5:5::5:5', records[2])
        self.assertEqual('4:4::4:4', records[1])
        self.assertEqual('3.3.3.3', records[0])

        records = self._notify._get_notify_slaves_from_ns('com.')
        self.assertEqual(3, len(records))
        self.assertEqual('5:5::5:5', records[2])
        self.assertEqual('4:4::4:4', records[1])
        self.assertEqual('3.3.3.3', records[0])
    
    def test_init_notify_out(self):
        self._notify._init_notify_out(self._db_file.name)
        self.assertListEqual([('3.3.3.3', 53), ('4:4::4:4', 53), ('5:5::5:5', 53)], 
                             self._notify._notify_infos[('com.', 'IN')].notify_slaves)
        
    def test_prepare_select_info(self):
        timeout, valid_fds, notifying_zones = self._notify._prepare_select_info()
        self.assertEqual(0, timeout)
        self.assertListEqual([], valid_fds)

        self._notify._notify_infos[('cn.', 'IN')]._sock = 1
        self._notify._notify_infos[('cn.', 'IN')].notify_timeout = time.time() + 5
        timeout, valid_fds, notifying_zones = self._notify._prepare_select_info()
        self.assertGreater(timeout, 0)
        self.assertListEqual([1], valid_fds)

        self._notify._notify_infos[('cn.', 'IN')]._sock = 1
        self._notify._notify_infos[('cn.', 'IN')].notify_timeout = time.time() - 5
        timeout, valid_fds, notifying_zones = self._notify._prepare_select_info()
        self.assertEqual(timeout, 0)
        self.assertListEqual([1], valid_fds)

        self._notify._notify_infos[('com.', 'IN')]._sock = 2
        self._notify._notify_infos[('com.', 'IN')].notify_timeout = time.time() + 5
        timeout, valid_fds, notifying_zones = self._notify._prepare_select_info()
        self.assertEqual(timeout, 0)
        self.assertListEqual([2, 1], valid_fds)

if __name__== "__main__":
    unittest.main()


