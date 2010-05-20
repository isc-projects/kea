# Copyright (C) 2009  Internet Systems Consortium.
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

# $Id$

import unittest
import socket
from xfrin import *

#
# Commonly used (mostly constant) test parameters
#
TEST_ZONE_NAME = "example.com"
TEST_RRCLASS = rr_class.IN()
TEST_DB_FILE = 'db_file'
TEST_MASTER_IPV4_ADDRESS = '127.0.0.1'
TEST_MASTER_IPV6_ADDRESS = '::1'
# XXX: This should be a non priviledge port that is unlikely to be used.
# If some other process uses this port test will fail.
TEST_MASTER_PORT = '53535'

soa_rdata = create_rdata(rr_type.SOA(), TEST_RRCLASS,
                         'master.example.com. admin.example.com ' +
                         '1234 3600 1800 2419200 7200')
soa_rrset = rrset(name(TEST_ZONE_NAME), TEST_RRCLASS, rr_type.SOA(),
                  rr_ttl(3600))
soa_rrset.add_rdata(soa_rdata)
example_question = question(name(TEST_ZONE_NAME), TEST_RRCLASS, rr_type.AXFR())
default_questions = [example_question]
default_answers = [soa_rrset]

class XfrinTestException(Exception):
    pass

# Rewrite the class for unittest.
class MockXfrin(Xfrin):
    def _cc_setup(self):
        pass

class MockXfrinConnection(XfrinConnection):
    def __init__(self, TEST_ZONE_NAME, db_file, shutdown_event, master_addr):
        super().__init__(TEST_ZONE_NAME, db_file, shutdown_event, master_addr)
        self.query_data = b''
        self.reply_data = b''
        self.force_time_out = False
        self.force_close = False
        self.qid = None
        self.response_generator = None

    def _handle_xfrin_response(self):
        for rr in super()._handle_xfrin_response():
            pass

    def _asyncore_loop(self):
        if self.force_close:
            self.handle_close()
        elif not self.force_time_out:
            self.handle_read()

    def connect_to_master(self):
        return True

    def recv(self, size):
        data = self.reply_data[:size]
        self.reply_data = self.reply_data[size:]
        if len(data) < size:
            raise XfrinTestException('cannot get reply data')
        return data

    def send(self, data):
        self.query_data += data
        # when the outgoing data is sufficiently large to contain the QID field
        # (4 octets or more - 16-bit length field + 16-bit QID), extract the
        # value so that we can construct a matching response.
        if len(self.query_data) >= 4 and self.qid == None:
            self.qid = socket.htons(struct.unpack('H', self.query_data[2:4])[0])
            # if the response generator method is specified, invoke it now.
            if self.response_generator != None:
                self.response_generator()
        return len(data)

    def create_response_data(self, response = True, bad_qid = False,
                             rcode = rcode.NOERROR(),
                             questions = default_questions,
                             answers = default_answers):
        resp = message(message_mode.RENDER)
        qid = self.qid
        if bad_qid:
            qid += 1
        resp.set_qid(qid)
        resp.set_opcode(op_code.QUERY())
        resp.set_rcode(rcode)
        if response:
            resp.set_header_flag(message_flag.QR())
        [resp.add_question(q) for q in questions]
        [resp.add_rrset(section.ANSWER(), a) for a in answers]

        obuf = output_buffer(0)
        renderer = message_render(obuf)
        resp.to_wire(renderer)
        reply_data = struct.pack('H', socket.htons(obuf.get_length()))
        reply_data += obuf.get_data()

        return reply_data

class TestXfrinConnection(unittest.TestCase):
    def setUp(self):
        if os.path.exists(TEST_DB_FILE):
            os.remove(TEST_DB_FILE)
        self.conn = MockXfrinConnection('example.com.', TEST_DB_FILE,
                                        threading.Event(),
                                        TEST_MASTER_IPV4_ADDRESS)

    def tearDown(self):
        self.conn.close()
        if os.path.exists(TEST_DB_FILE):
            os.remove(TEST_DB_FILE)

    def test_init_ip6(self):
        # This test simply creates a new XfrinConnection object with an
        # IPv6 address, tries to bind it to an IPv6 wildcard address/port
        # to confirm an AF_INET6 socket has been created.  A naive application
        # tends to assume it's IPv4 only and hardcode AF_INET.  This test
        # uncovers such a bug.
        c = MockXfrinConnection('example.com.', TEST_DB_FILE,
                                threading.Event(),
                                TEST_MASTER_IPV6_ADDRESS)
        #This test currently fails.  Fix the code, then enable it
        #c.bind(('::', 0))
        c.close()

    def test_response_with_invalid_msg(self):
        self.conn.reply_data = b'aaaxxxx'
        self.assertRaises(XfrinTestException, self.conn._handle_xfrin_response)

    def test_response_without_end_soa(self):
        self.conn._send_query(rr_type.AXFR())
        self.conn.reply_data = self.conn.create_response_data()
        self.assertRaises(XfrinTestException, self.conn._handle_xfrin_response)

    def test_response_bad_qid(self):
        self.conn._send_query(rr_type.AXFR())
        self.conn.reply_data = self.conn.create_response_data(bad_qid = True)
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_non_response(self):
        self.conn._send_query(rr_type.AXFR())
        self.conn.reply_data = self.conn.create_response_data(response = False)
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_error_code(self):
        self.conn._send_query(rr_type.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
            rcode = rcode.SERVFAIL())
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_multi_question(self):
        self.conn._send_query(rr_type.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
            questions=[example_question, example_question])
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_empty_answer(self):
        self.conn._send_query(rr_type.AXFR())
        self.conn.reply_data = self.conn.create_response_data(answers=[])
        # Should an empty answer trigger an exception?  Even though it's very
        # unusual it's not necessarily invalid.  Need to revisit.
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_shutdown(self):
        self.conn.response_generator = self._create_normal_response_data
        self.conn._shutdown_event.set()
        self.conn._send_query(rr_type.AXFR())
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_timeout(self):
        self.conn.response_generator = self._create_normal_response_data
        self.conn.force_time_out = True
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_remote_close(self):
        self.conn.response_generator = self._create_normal_response_data
        self.conn.force_close = True
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response_bad_message(self):
        self.conn.response_generator = self._create_broken_response_data
        self.conn._send_query(rr_type.AXFR())
        self.assertRaises(Exception, self.conn._handle_xfrin_response)

    def test_response(self):
        # normal case.  should silently succeed.
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(rr_type.AXFR())
        self.conn._handle_xfrin_response()

    def test_do_xfrin(self):
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)

    def test_do_xfrin_empty_response(self):
        # skipping the creation of response data, so the transfer will fail.
        # (but do_xfrin() always return OK.)
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)

    def test_do_xfrin_empty_response(self):
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)

    def test_do_xfrin_bad_response(self):
        self.conn.response_generator = self._create_broken_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)

    def test_do_xfrin_dberror(self):
        # DB file is under a non existent directory, so its creation will fail,
        # which will make the transfer fail.
        self.conn._db_file = "not_existent/" + TEST_DB_FILE
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)

# This test currently doesn't work due to bug.  Fix it and then enable the test.
#     def test_do_xfrin_with_soacheck(self):
#         self.conn.response_generator = self._create_normal_response_data
#         self.assertEqual(self.conn.do_xfrin(True), XFRIN_OK)

#     def test_do_xfrin_with_soacheck_bad_response(self):
#         self.conn.response_generator = self._create_broken_response_data
#         self.assertEqual(self.conn.do_xfrin(True), XFRIN_OK)

    def _create_normal_response_data(self):
        # This helper method creates a simple sequence of DNS messages that
        # forms a valid XFR transaction.  It consists of two messages, each
        # containing just a single SOA RR.
        self.conn.reply_data = self.conn.create_response_data()
        self.conn.reply_data += self.conn.create_response_data()

    def _create_broken_response_data(self):
        # This helper method creates a bogus "DNS message" that only contains
        # 4 octets of data.  The DNS message parser will raise an exception.
        bogus_data = b'xxxx'
        self.conn.reply_data = struct.pack('H', socket.htons(len(bogus_data)))
        self.conn.reply_data += bogus_data

class TestXfrinRecorder(unittest.TestCase):
    def setUp(self):
        self.recorder = XfrinRecorder()

    def test_increment(self):
        self.assertEqual(self.recorder.count(), 0)
        self.recorder.increment(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.count(), 1)
        # duplicate "increment" should probably be rejected.  but it's not
        # checked at this moment
        self.recorder.increment(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.count(), 2)

    def test_decrement(self):
        self.assertEqual(self.recorder.count(), 0)
        self.recorder.increment(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.count(), 1)
        self.recorder.decrement(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.count(), 0)

    def test_decrement_from_empty(self):
        self.assertEqual(self.recorder.count(), 0)
        self.recorder.decrement(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.count(), 0)

    def test_inprogress(self):
        self.assertEqual(self.recorder.count(), 0)
        self.recorder.increment(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.xfrin_in_progress(TEST_ZONE_NAME), True)
        self.recorder.decrement(TEST_ZONE_NAME)
        self.assertEqual(self.recorder.xfrin_in_progress(TEST_ZONE_NAME), False)

class TestXfrin(unittest.TestCase):
    args = {}

    def setUp(self):
        self.xfr = MockXfrin()
        self.args['zone_name'] = TEST_ZONE_NAME
        self.args['port'] = TEST_MASTER_PORT
        self.args['master'] = TEST_MASTER_IPV4_ADDRESS
        self.args['db_file'] = TEST_DB_FILE

    def tearDown(self):
        self.xfr.shutdown()

    def _do_parse(self):
        return self.xfr._parse_cmd_params(self.args)

    def test_parse_cmd_params(self):
        name, master, port, db_file = self._do_parse()
        self.assertEqual(port, int(TEST_MASTER_PORT))
        self.assertEqual(name, TEST_ZONE_NAME)
        self.assertEqual(master, TEST_MASTER_IPV4_ADDRESS)
        self.assertEqual(db_file, TEST_DB_FILE)

    def test_parse_cmd_params_default_port(self):
        del self.args['port']
        self.assertEqual(self._do_parse()[2], 53)

    def test_parse_cmd_params_ip6master(self):
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS
        self.assertEqual(self._do_parse()[1], TEST_MASTER_IPV6_ADDRESS)

    def test_parse_cmd_params_nozone(self):
        # zone name is mandatory.
        del self.args['zone_name']
        self.assertRaises(XfrinException, self._do_parse)

    def test_parse_cmd_params_nomaster(self):
        # master address is mandatory.
        del self.args['master']
        self.assertRaises(XfrinException, self._do_parse)

    def test_parse_cmd_params_bad_ip4(self):
        self.args['master'] = '3.3.3'
        self.assertRaises(XfrinException, self._do_parse)

    def test_parse_cmd_params_bad_ip6(self):
        self.args['master'] = '1::1::1'
        self.assertRaises(XfrinException, self._do_parse)

    def test_parse_cmd_params_bad_port(self):
        self.args['port'] = '-1'
        self.assertRaises(XfrinException, self._do_parse)

        self.args['port'] = '65536'
        self.assertRaises(XfrinException, self._do_parse)

    def test_command_handler_shutdown(self):
        self.assertEqual(self.xfr.command_handler("shutdown",
                                                  None)['result'][0], 0)
        # shutdown command doesn't expect an argument, but accepts it if any.
        self.assertEqual(self.xfr.command_handler("shutdown",
                                                  "unused")['result'][0], 0)

        self.assertEqual(self.xfr.command_handler("Shutdown",
                                                  "unused")['result'][0], 0)

    def test_command_handler_retransfer(self):
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 0)

    def test_command_handler_retransfer_badcommand(self):
        self.args['master'] = 'invalid'
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)

    def test_command_handler_retransfer_quota(self):
        for i in range(self.xfr._max_transfers_in - 1):
            self.xfr.recorder.increment(str(i) + TEST_ZONE_NAME)
        # there can be one more outstanding transfer.
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 0)
        # make sure the # xfrs would excceed the quota
        self.xfr.recorder.increment(str(self.xfr._max_transfers_in) + TEST_ZONE_NAME)
        # this one should fail
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)

    def test_command_handler_retransfer_inprogress(self):
        self.xfr.recorder.increment(TEST_ZONE_NAME)
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)

    def test_command_handler_retransfer_nomodule(self):
        dns_module = sys.modules['bind10_dns'] # this must exist
        del sys.modules['bind10_dns']
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)
        # sys.modules is global, so we must recover it
        sys.modules['bind10_dns'] = dns_module

    def test_command_handler_refresh(self):
        # at this level, refresh is no different than retransfer.
        # just confirm the successful case with a different family of address.
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS
        self.assertEqual(self.xfr.command_handler("refresh",
                                                  self.args)['result'][0], 0)

if __name__== "__main__":
    try:
        unittest.main()
    except KeyboardInterrupt as e:
        print(e)
