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

'''Tests for the XfroutSession and UnixSockServer classes '''


import unittest
import os
from isc.cc.session import *
from pydnspp import *
from xfrout import *

# our fake socket, where we can read and insert messages
class MySocket():
    def __init__(self, family, type):
        self.family = family
        self.type = type
        self.sendqueue = bytearray()

    def connect(self, to):
        pass

    def close(self):
        pass

    def send(self, data):
        self.sendqueue.extend(data);
        return len(data)

    def readsent(self):
        result = self.sendqueue[:]
        del self.sendqueue[:]
        return result
    
    def read_msg(self):
        sent_data = self.readsent()
        get_msg = Message(Message.PARSE)
        get_msg.from_wire(bytes(sent_data[2:]))
        return get_msg
    
    def clear_send(self):
        del self.sendqueue[:]

# We subclass the Session class we're testing here, only
# to override the __init__() method, which wants a socket,
class MyXfroutSession(XfroutSession):
    def handle(self):
        pass
    
class Dbserver:
    def __init__(self):
        self._shutdown_event = threading.Event()
    def get_db_file(self):
        return None
    def decrease_transfers_counter(self):
        pass

class TestXfroutSession(unittest.TestCase):
    def getmsg(self):
        msg = Message(Message.PARSE)
        msg.from_wire(self.mdata)
        return msg

    def setUp(self):
        request = MySocket(socket.AF_INET,socket.SOCK_STREAM)
        self.log = isc.log.NSLogger('xfrout', '',  severity = 'critical', log_to_console = False )
        self.xfrsess = MyXfroutSession(request, None, None, self.log)
        self.xfrsess.server = Dbserver()
        self.mdata = bytes(b'\xd6=\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x07example\x03com\x00\x00\xfc\x00\x01')
        self.sock = MySocket(socket.AF_INET,socket.SOCK_STREAM)
        self.soa_record = (4, 3, 'example.com.', 'com.example.', 3600, 'SOA', None, 'master.example.com. admin.example.com. 1234 3600 1800 2419200 7200')

    def test_parse_query_message(self):
        [get_rcode, get_msg] = self.xfrsess._parse_query_message(self.mdata)
        self.assertEqual(get_rcode.to_text(), "NOERROR")

    def test_get_query_zone_name(self):
        msg = self.getmsg()
        self.assertEqual(self.xfrsess._get_query_zone_name(msg), "example.com.")
  
    def test_send_data(self):
        self.xfrsess._send_data(self.sock, self.mdata)
        senddata = self.sock.readsent()
        self.assertEqual(senddata, self.mdata)

    def test_reply_xfrout_query_with_error_rcode(self):
        msg = self.getmsg()
        self.xfrsess._reply_query_with_error_rcode(msg, self.sock, Rcode(3))
        get_msg = self.sock.read_msg()
        self.assertEqual(get_msg.get_rcode().to_text(), "NXDOMAIN") 
     
    def test_clear_message(self):
        msg = self.getmsg()
        qid = msg.get_qid()
        opcode = msg.get_opcode()
        rcode = msg.get_rcode()

        self.xfrsess._clear_message(msg)
        self.assertEqual(msg.get_qid(), qid)
        self.assertEqual(msg.get_opcode(), opcode)
        self.assertEqual(msg.get_rcode(), rcode)
        self.assertTrue(msg.get_header_flag(MessageFlag.AA()))

    def test_reply_query_with_format_error(self):
         
        msg = self.getmsg()
        self.xfrsess._reply_query_with_format_error(msg, self.sock)
        get_msg = self.sock.read_msg()
        self.assertEqual(get_msg.get_rcode().to_text(), "FORMERR")

    def test_create_rrset_from_db_record(self):
        rrset = self.xfrsess._create_rrset_from_db_record(self.soa_record)
        self.assertEqual(rrset.get_name().to_text(), "example.com.")
        self.assertEqual(rrset.get_class(), RRClass("IN"))
        self.assertEqual(rrset.get_type().to_text(), "SOA")
        rdata = rrset.get_rdata()
        self.assertEqual(rdata[0].to_text(), self.soa_record[7])

    def test_send_message_with_last_soa(self):
        rrset_soa = self.xfrsess._create_rrset_from_db_record(self.soa_record)

        msg = self.getmsg()
        msg.make_response()
        self.xfrsess._send_message_with_last_soa(msg, self.sock, rrset_soa)
        get_msg = self.sock.read_msg()

        self.assertEqual(get_msg.get_rr_count(Section.QUESTION()), 1)
        self.assertEqual(get_msg.get_rr_count(Section.ANSWER()), 1)
        self.assertEqual(get_msg.get_rr_count(Section.AUTHORITY()), 0)

        #answer_rrset_iter = section_iter(get_msg, section.ANSWER())
        answer = get_msg.get_section(Section.ANSWER())[0]#answer_rrset_iter.get_rrset()
        self.assertEqual(answer.get_name().to_text(), "example.com.")
        self.assertEqual(answer.get_class(), RRClass("IN"))
        self.assertEqual(answer.get_type().to_text(), "SOA")
        rdata = answer.get_rdata()
        self.assertEqual(rdata[0].to_text(), self.soa_record[7])

    def test_get_message_len(self):
        msg = self.getmsg()
        msg.make_response()  
        self.assertEqual(self.xfrsess._get_message_len(msg), 29)

    def test_zone_is_empty(self):
        global sqlite3_ds
        def mydb1(zone, file):
            return True
        sqlite3_ds.get_zone_soa = mydb1
        self.assertEqual(self.xfrsess._zone_is_empty(""), False)
        def mydb2(zone, file):
            return False
        sqlite3_ds.get_zone_soa = mydb2
        self.assertEqual(self.xfrsess._zone_is_empty(""), True)

    def test_zone_exist(self):
        global sqlite3_ds
        def zone_soa(zone, file):
            return zone
        sqlite3_ds.get_zone_soa = zone_soa
        self.assertEqual(self.xfrsess._zone_exist(True), True)
        self.assertEqual(self.xfrsess._zone_exist(False), False)
    
    def test_check_xfrout_available(self):
        def zone_exist(zone):
            return zone
        self.xfrsess._zone_exist = zone_exist
        self.xfrsess._zone_is_empty = zone_exist
        self.assertEqual(self.xfrsess._check_xfrout_available(False).to_text(), "NOTAUTH")
        self.assertEqual(self.xfrsess._check_xfrout_available(True).to_text(), "SERVFAIL")

        def zone_empty(zone):
            return not zone
        self.xfrsess._zone_is_empty = zone_empty
        def false_func():
            return False
        self.xfrsess.server.increase_transfers_counter = false_func
        self.assertEqual(self.xfrsess._check_xfrout_available(True).to_text(), "REFUSED")
        def true_func():
            return True
        self.xfrsess.server.increase_transfers_counter = true_func
        self.assertEqual(self.xfrsess._check_xfrout_available(True).to_text(), "NOERROR")

    def test_dns_xfrout_start_formerror(self):
        # formerror
        self.xfrsess.dns_xfrout_start(self.sock, b"\xd6=\x00\x00\x00\x01\x00")
        sent_data = self.sock.readsent()
        self.assertEqual(len(sent_data), 0)
    
    def default(self, param):
        return "example.com"

    def test_dns_xfrout_start_notauth(self):
        self.xfrsess._get_query_zone_name = self.default
        def notauth(formpara):
            return Rcode.NOTAUTH()
        self.xfrsess._check_xfrout_available = notauth
        self.xfrsess.dns_xfrout_start(self.sock, self.mdata)
        get_msg = self.sock.read_msg()
        self.assertEqual(get_msg.get_rcode().to_text(), "NOTAUTH")
    
    def test_dns_xfrout_start_noerror(self):
        self.xfrsess._get_query_zone_name = self.default
        def noerror(form):
            return Rcode.NOERROR() 
        self.xfrsess._check_xfrout_available = noerror
        
        def myreply(msg, sock, zonename):
            self.sock.send(b"success")
        
        self.xfrsess._reply_xfrout_query = myreply
        self.xfrsess.dns_xfrout_start(self.sock, self.mdata)
        self.assertEqual(self.sock.readsent(), b"success")
    
    def test_reply_xfrout_query_noerror(self):
        global sqlite3_ds
        def get_zone_soa(zonename, file):
            return self.soa_record

        def get_zone_datas(zone, file):
            return [self.soa_record]

        sqlite3_ds.get_zone_soa = get_zone_soa
        sqlite3_ds.get_zone_datas = get_zone_datas
        self.xfrsess._reply_xfrout_query(self.getmsg(), self.sock, "example.com.")
        reply_msg = self.sock.read_msg()
        self.assertEqual(reply_msg.get_rr_count(Section.ANSWER()), 2)

class MyCCSession():
    def __init__(self):
        pass

    def get_remote_config_value(self, module_name, identifier):
        if module_name == "Auth" and identifier == "database_file":
            return "initdb.file", False
        else:
            return "unknown", False
    

class MyUnixSockServer(UnixSockServer):
    def __init__(self):
        self._lock = threading.Lock()
        self._transfers_counter = 0
        self._shutdown_event = threading.Event()
        self._max_transfers_out = 10
        self._cc = MyCCSession()
        self._log = isc.log.NSLogger('xfrout', '', severity = 'critical', log_to_console = False )

class TestUnixSockServer(unittest.TestCase):
    def setUp(self):
        self.unix = MyUnixSockServer()
     
    def test_updata_config_data(self):
        self.unix.update_config_data({'transfers_out':10 })
        self.assertEqual(self.unix._max_transfers_out, 10)

    def test_get_db_file(self):
        self.assertEqual(self.unix.get_db_file(), "initdb.file")

    def test_increase_transfers_counter(self):
        self.unix._max_transfers_out = 10
        count = self.unix._transfers_counter
        self.assertEqual(self.unix.increase_transfers_counter(), True)
        self.assertEqual(count + 1, self.unix._transfers_counter)

        self.unix._max_transfers_out = 0
        count = self.unix._transfers_counter
        self.assertEqual(self.unix.increase_transfers_counter(), False)
        self.assertEqual(count, self.unix._transfers_counter)
 
    def test_decrease_transfers_counter(self):
        count = self.unix._transfers_counter
        self.unix.decrease_transfers_counter()
        self.assertEqual(count - 1, self.unix._transfers_counter)

    def _remove_file(self, sock_file):
        try:
            os.remove(sock_file)
        except OSError:
            pass
 
    def test_sock_file_in_use_file_exist(self):
        sock_file = 'temp.sock.file'
        self._remove_file(sock_file)
        self.assertFalse(self.unix._sock_file_in_use(sock_file))
        self.assertFalse(os.path.exists(sock_file))

    def test_sock_file_in_use_file_not_exist(self):
        self.assertFalse(self.unix._sock_file_in_use('temp.sock.file'))

    def _start_unix_sock_server(self, sock_file):
        serv = ThreadingUnixStreamServer(sock_file, BaseRequestHandler)
        serv_thread = threading.Thread(target=serv.serve_forever)
        serv_thread.setDaemon(True)
        serv_thread.start()

    def test_sock_file_in_use(self):
        sock_file = 'temp.sock.file'
        self._remove_file(sock_file)
        self.assertFalse(self.unix._sock_file_in_use(sock_file))
        self._start_unix_sock_server(sock_file)

        old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.assertTrue(self.unix._sock_file_in_use(sock_file))
        sys.stdout = old_stdout

    def test_remove_unused_sock_file_in_use(self):
        sock_file = 'temp.sock.file'
        self._remove_file(sock_file)
        self.assertFalse(self.unix._sock_file_in_use(sock_file))
        self._start_unix_sock_server(sock_file)
        old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        try:
            self.unix._remove_unused_sock_file(sock_file)
        except SystemExit:
            pass
        else:
            # This should never happen
            self.assertTrue(False)

        sys.stdout = old_stdout

    def test_remove_unused_sock_file_dir(self):
        import tempfile
        dir_name = tempfile.mkdtemp()
        old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        try:
            self.unix._remove_unused_sock_file(dir_name)
        except SystemExit:
            pass
        else:
            # This should never happen
            self.assertTrue(False)

        sys.stdout = old_stdout
        os.rmdir(dir_name)

if __name__== "__main__":
    unittest.main()
