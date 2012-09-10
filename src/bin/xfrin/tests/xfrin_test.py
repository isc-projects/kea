# Copyright (C) 2009-2011  Internet Systems Consortium.
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
import re
import shutil
import socket
import sys
import io
from isc.testutils.tsigctx_mock import MockTSIGContext
from isc.testutils.ccsession_mock import MockModuleCCSession
from isc.testutils.rrset_utils import *
from xfrin import *
import xfrin
from isc.xfrin.diff import Diff
import isc.log
# If we use any python library that is basically a wrapper for
# a library we use as well (like sqlite3 in our datasources),
# we must make sure we import ours first; If we have special
# rpath or libtool rules to pick the correct version, python might
# choose the wrong one first, if those rules aren't hit first.
# This would result in missing symbols later.
import sqlite3

#
# Commonly used (mostly constant) test parameters
#
TEST_ZONE_NAME_STR = "example.com."
TEST_ZONE_NAME = Name(TEST_ZONE_NAME_STR)
TEST_RRCLASS = RRClass.IN()
TEST_RRCLASS_STR = 'IN'
TEST_DB_FILE = 'db_file'
TEST_MASTER_IPV4_ADDRESS = '127.0.0.1'
TEST_MASTER_IPV4_ADDRINFO = (socket.AF_INET, socket.SOCK_STREAM,
                             (TEST_MASTER_IPV4_ADDRESS, 53))
TEST_MASTER_IPV6_ADDRESS = '::1'
TEST_MASTER_IPV6_ADDRINFO = (socket.AF_INET6, socket.SOCK_STREAM,
                             (TEST_MASTER_IPV6_ADDRESS, 53))

TESTDATA_SRCDIR = os.getenv("TESTDATASRCDIR")
TESTDATA_OBJDIR = os.getenv("TESTDATAOBJDIR")
# XXX: This should be a non priviledge port that is unlikely to be used.
# If some other process uses this port test will fail.
TEST_MASTER_PORT = '53535'

TSIG_KEY = TSIGKey("example.com:SFuWd/q99SzF8Yzd1QbB9g==")

# SOA intended to be used for the new SOA as a result of transfer.
soa_rdata = Rdata(RRType.SOA(), TEST_RRCLASS,
                  'master.example.com. admin.example.com ' +
                  '1234 3600 1800 2419200 7200')
soa_rrset = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.SOA(), RRTTL(3600))
soa_rrset.add_rdata(soa_rdata)

# SOA intended to be used for the current SOA at the secondary side.
# Note that its serial is smaller than that of soa_rdata.
begin_soa_rdata = Rdata(RRType.SOA(), TEST_RRCLASS,
                        'master.example.com. admin.example.com ' +
                        '1230 3600 1800 2419200 7200')
begin_soa_rrset = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.SOA(), RRTTL(3600))
begin_soa_rrset.add_rdata(begin_soa_rdata)
example_axfr_question = Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.AXFR())
example_soa_question = Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.SOA())
default_questions = [example_axfr_question]
default_answers = [soa_rrset]

def get_fake_time_time():
    '''Returns a temporary replacement function for time.time(), which
       always returns 0.1 more than the previous call. This is to make
       sure these tests do not fail on systems where the time.time()
       function has a high minimal accuracy.
       This fake time.time() is usually set in place of the real one
       where we need testing of get_running_time(). It is done is
       as low a scope as possible, so as not to mess up unit test
       framework time related tests. It must be set before
       XfrinTransferState (or any class that initializes that) is
       initialized.
       And every time it is set up, in must be reset later (again, so
       as not to mess up the framework's concept of time).
    '''
    fake_time = 0.0
    def fake_time_time():
        nonlocal fake_time
        fake_time += 0.1
        return fake_time
    return fake_time_time

def check_diffs(assert_fn, expected, actual):
    '''A helper function checking the differences made in the XFR session.

    This is expected called from some subclass of unittest.TestCase and
    assert_fn is generally expected to be 'self.assertEqual' of that class.

    '''
    assert_fn(len(expected), len(actual))
    for (diffs_exp, diffs_actual) in zip(expected, actual):
        assert_fn(len(diffs_exp), len(diffs_actual))
        for (diff_exp, diff_actual) in zip(diffs_exp, diffs_actual):
            # operation should match
            assert_fn(diff_exp[0], diff_actual[0])
            # The diff as RRset should be equal (for simplicity we assume
            # all RRsets contain exactly one RDATA)
            assert_fn(diff_exp[1].get_name(), diff_actual[1].get_name())
            assert_fn(diff_exp[1].get_type(), diff_actual[1].get_type())
            assert_fn(diff_exp[1].get_class(), diff_actual[1].get_class())
            assert_fn(diff_exp[1].get_rdata_count(),
                      diff_actual[1].get_rdata_count())
            assert_fn(1, diff_exp[1].get_rdata_count())
            assert_fn(diff_exp[1].get_rdata()[0],
                      diff_actual[1].get_rdata()[0])

class XfrinTestException(Exception):
    pass

class XfrinTestTimeoutException(Exception):
    pass

class MockCC(MockModuleCCSession):
    def get_default_value(self, identifier):
        # The returned values should be identical to the spec file
        # XXX: these should be retrieved from the spec file
        # (see MyCCSession of xfrout_test.py.in)
        if identifier == "zones/master_port":
            return TEST_MASTER_PORT
        if identifier == "zones/class":
            return TEST_RRCLASS_STR
        if identifier == "zones/use_ixfr":
            return False

    def remove_remote_config(self, module_name):
        pass

class MockDataSourceClient():
    '''A simple mock data source client.

    This class provides a minimal set of wrappers related the data source
    API that would be used by Diff objects.  For our testing purposes they
    only keep truck of the history of the changes.

    '''
    def __init__(self):
        self.force_fail = False # if True, raise an exception on commit
        self.committed_diffs = []
        self.diffs = []

    def get_class(self):
        '''Mock version of get_class().

        We simply return the commonly used constant RR class.  If and when
        we use this mock for a different RR class we need to adjust it
        accordingly.

        '''
        return TEST_RRCLASS

    def find_zone(self, zone_name):
        '''Mock version of find_zone().

        It returns itself (subsequently acting as a mock ZoneFinder) for
        some test zone names.  For some others it returns either NOTFOUND
        or PARTIALMATCH.

        '''
        if zone_name == TEST_ZONE_NAME or \
                zone_name == Name('no-soa.example') or \
                zone_name == Name('dup-soa.example'):
            return (isc.datasrc.DataSourceClient.SUCCESS, self)
        elif zone_name == Name('no-such-zone.example'):
            return (DataSourceClient.NOTFOUND, None)
        elif zone_name == Name('partial-match-zone.example'):
            return (DataSourceClient.PARTIALMATCH, self)
        raise ValueError('Unexpected input to mock client: bug in test case?')

    def find(self, name, rrtype, options=ZoneFinder.FIND_DEFAULT):
        '''Mock ZoneFinder.find().

        It returns the predefined SOA RRset to queries for SOA of the common
        test zone name.  It also emulates some unusual cases for special
        zone names.

        '''
        if name == TEST_ZONE_NAME and rrtype == RRType.SOA():
            return (ZoneFinder.SUCCESS, begin_soa_rrset, 0)
        if name == Name('no-soa.example'):
            return (ZoneFinder.NXDOMAIN, None, 0)
        if name == Name('dup-soa.example'):
            dup_soa_rrset = RRset(name, TEST_RRCLASS, RRType.SOA(), RRTTL(0))
            dup_soa_rrset.add_rdata(begin_soa_rdata)
            dup_soa_rrset.add_rdata(soa_rdata)
            return (ZoneFinder.SUCCESS, dup_soa_rrset, 0)
        raise ValueError('Unexpected input to mock finder: bug in test case?')

    def get_updater(self, zone_name, replace, journaling=False):
        self._journaling_enabled = journaling
        return self

    def add_rrset(self, rrset):
        self.diffs.append(('add', rrset))

    def delete_rrset(self, rrset):
        self.diffs.append(('delete', rrset))

    def commit(self):
        if self.force_fail:
            raise isc.datasrc.Error('Updater.commit() failed')
        self.committed_diffs.append(self.diffs)
        self.diffs = []

class MockXfrin(Xfrin):
    # This is a class attribute of a callable object that specifies a non
    # default behavior triggered in _cc_check_command().  Specific test methods
    # are expected to explicitly set this attribute before creating a
    # MockXfrin object (when it needs a non default behavior).
    # See the TestMain class.
    check_command_hook = None

    def _cc_setup(self):
        self._tsig_key = None
        self._module_cc = MockCC()
        pass

    def _get_db_file(self):
        pass

    def _cc_check_command(self):
        self._shutdown_event.set()
        if MockXfrin.check_command_hook:
            MockXfrin.check_command_hook()

    def xfrin_start(self, zone_name, rrclass, db_file, master_addrinfo,
                    tsig_key, request_type, check_soa=True):
        # store some of the arguments for verification, then call this
        # method in the superclass
        self.xfrin_started_master_addr = master_addrinfo[2][0]
        self.xfrin_started_master_port = master_addrinfo[2][1]
        self.xfrin_started_request_type = request_type
        return Xfrin.xfrin_start(self, zone_name, rrclass, None,
                                 master_addrinfo, tsig_key,
                                 request_type, check_soa)

class MockXfrinConnection(XfrinConnection):
    def __init__(self, sock_map, zone_name, rrclass, datasrc_client,
                 shutdown_event, master_addr, tsig_key=None):
        super().__init__(sock_map, zone_name, rrclass, MockDataSourceClient(),
                         shutdown_event, master_addr, TEST_DB_FILE)
        self.query_data = b''
        self.reply_data = b''
        self.force_time_out = False
        self.force_close = False
        self.qlen = None
        self.qid = None
        self.response_generator = None

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
        if len(data) == 0:
            raise XfrinTestTimeoutException('Emulated timeout')
        if len(data) < size:
            raise XfrinTestException('cannot get reply data (' + str(size) +
                                     ' bytes)')
        return data

    def send(self, data):
        if self.qlen != None and len(self.query_data) >= self.qlen:
            # This is a new query.  reset the internal state.
            self.qlen = None
            self.qid = None
            self.query_data = b''
        self.query_data += data

        # when the outgoing data is sufficiently large to contain the length
        # and the QID fields (4 octets or more), extract these fields.
        # The length will be reset the internal query data to support multiple
        # queries in a single test.
        # The QID will be used to construct a matching response.
        if len(self.query_data) >= 4 and self.qid == None:
            self.qlen = socket.htons(struct.unpack('H',
                                                   self.query_data[0:2])[0])
            self.qid = socket.htons(struct.unpack('H', self.query_data[2:4])[0])
            # if the response generator method is specified, invoke it now.
            if self.response_generator != None:
                self.response_generator()
        return len(data)

    def create_response_data(self, response=True, auth=True, bad_qid=False,
                             rcode=Rcode.NOERROR(),
                             questions=default_questions,
                             answers=default_answers,
                             authorities=[],
                             tsig_ctx=None):
        resp = Message(Message.RENDER)
        qid = self.qid
        if bad_qid:
            qid += 1
        resp.set_qid(qid)
        resp.set_opcode(Opcode.QUERY())
        resp.set_rcode(rcode)
        if response:
            resp.set_header_flag(Message.HEADERFLAG_QR)
        if auth:
            resp.set_header_flag(Message.HEADERFLAG_AA)
        [resp.add_question(q) for q in questions]
        [resp.add_rrset(Message.SECTION_ANSWER, a) for a in answers]
        [resp.add_rrset(Message.SECTION_AUTHORITY, a) for a in authorities]

        renderer = MessageRenderer()
        if tsig_ctx is not None:
            resp.to_wire(renderer, tsig_ctx)
        else:
            resp.to_wire(renderer)
        reply_data = struct.pack('H', socket.htons(renderer.get_length()))
        reply_data += renderer.get_data()

        return reply_data

class TestXfrinState(unittest.TestCase):
    def setUp(self):
        self.sock_map = {}
        self.conn = MockXfrinConnection(self.sock_map, TEST_ZONE_NAME,
                                        TEST_RRCLASS, None, threading.Event(),
                                        TEST_MASTER_IPV4_ADDRINFO)
        self.conn.init_socket()
        self.begin_soa = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.SOA(),
                               RRTTL(3600))
        self.begin_soa.add_rdata(Rdata(RRType.SOA(), TEST_RRCLASS,
                                       'm. r. 1230 0 0 0 0'))
        self.ns_rrset = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.NS(),
                              RRTTL(3600))
        self.ns_rrset.add_rdata(Rdata(RRType.NS(), TEST_RRCLASS,
                                      'ns.example.com'))
        self.a_rrset = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.A(),
                             RRTTL(3600))
        self.a_rrset.add_rdata(Rdata(RRType.A(), TEST_RRCLASS, '192.0.2.1'))

        self.conn._datasrc_client = MockDataSourceClient()
        self.conn._diff = Diff(self.conn._datasrc_client, TEST_ZONE_NAME)

class TestXfrinStateBase(TestXfrinState):
    def setUp(self):
        super().setUp()

    def test_handle_rr_on_base(self):
        # The base version of handle_rr() isn't supposed to be called
        # directly (the argument doesn't matter in this test)
        self.assertRaises(XfrinException, XfrinState().handle_rr, None)

class TestXfrinInitialSOA(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinInitialSOA()

    def test_handle_rr(self):
        # normal case
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinFirstData()),
                         type(self.conn.get_xfrstate()))
        self.assertEqual(1234, self.conn._end_serial.get_value())

    def test_handle_not_soa(self):
        # The given RR is not of SOA
        self.assertRaises(XfrinProtocolError, self.state.handle_rr, self.conn,
                          self.ns_rrset)

    def test_handle_ixfr_uptodate(self):
        self.conn._request_type = RRType.IXFR()
        self.conn._request_serial = isc.dns.Serial(1234) # same as soa_rrset
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinIXFRUptodate()),
                         type(self.conn.get_xfrstate()))

    def test_handle_ixfr_uptodate2(self):
        self.conn._request_type = RRType.IXFR()
        self.conn._request_serial = isc.dns.Serial(1235) # > soa_rrset
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinIXFRUptodate()),
                         type(self.conn.get_xfrstate()))

    def test_handle_ixfr_uptodate3(self):
        # Similar to the previous case, but checking serial number arithmetic
        # comparison
        self.conn._request_type = RRType.IXFR()
        self.conn._request_serial = isc.dns.Serial(0xffffffff)
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinFirstData()),
                         type(self.conn.get_xfrstate()))

    def test_handle_axfr_uptodate(self):
        # "request serial" should matter only for IXFR
        self.conn._request_type = RRType.AXFR()
        self.conn._request_serial = isc.dns.Serial(1234) # same as soa_rrset
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinFirstData()),
                         type(self.conn.get_xfrstate()))

    def test_finish_message(self):
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinFirstData(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinFirstData()
        self.conn._request_type = RRType.IXFR()
        # arbitrary chosen serial < 1234:
        self.conn._request_serial = isc.dns.Serial(1230)
        self.conn._diff = None           # should be replaced in the AXFR case

    def test_handle_ixfr_begin_soa(self):
        self.conn._request_type = RRType.IXFR()
        self.assertFalse(self.state.handle_rr(self.conn, self.begin_soa))
        self.assertEqual(type(XfrinIXFRDeleteSOA()),
                         type(self.conn.get_xfrstate()))

    def test_handle_axfr(self):
        # If the original type is AXFR, other conditions aren't considered,
        # and AXFR processing will continue
        self.conn._request_type = RRType.AXFR()
        self.assertFalse(self.state.handle_rr(self.conn, self.begin_soa))
        self.assertEqual(type(XfrinAXFR()), type(self.conn.get_xfrstate()))

    def test_handle_ixfr_to_axfr(self):
        # Detecting AXFR-compatible IXFR response by seeing a non SOA RR after
        # the initial SOA.  Should switch to AXFR.
        self.assertFalse(self.state.handle_rr(self.conn, self.ns_rrset))
        self.assertEqual(type(XfrinAXFR()), type(self.conn.get_xfrstate()))
        # The Diff for AXFR should be created at this point
        self.assertNotEqual(None, self.conn._diff)

    def test_handle_ixfr_to_axfr_by_different_soa(self):
        # An unusual case: Response contains two consecutive SOA but the
        # serial of the second does not match the requested one.  See
        # the documentation for XfrinFirstData.handle_rr().
        self.assertFalse(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinAXFR()), type(self.conn.get_xfrstate()))
        self.assertNotEqual(None, self.conn._diff)

    def test_finish_message(self):
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinIXFRDeleteSOA(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinIXFRDeleteSOA()
        # In this state a new Diff object is expected to be created.  To
        # confirm it, we nullify it beforehand.
        self.conn._diff = None

    def test_handle_rr(self):
        self.assertTrue(self.state.handle_rr(self.conn, self.begin_soa))
        self.assertEqual(type(XfrinIXFRDelete()),
                         type(self.conn.get_xfrstate()))
        self.assertEqual([('delete', self.begin_soa)],
                         self.conn._diff.get_buffer())

    def test_handle_non_soa(self):
        self.assertRaises(XfrinException, self.state.handle_rr, self.conn,
                          self.ns_rrset)

    def test_finish_message(self):
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinIXFRDelete(TestXfrinState):
    def setUp(self):
        super().setUp()
        # We need record the state in 'conn' to check the case where the
        # state doesn't change.
        XfrinIXFRDelete().set_xfrstate(self.conn, XfrinIXFRDelete())
        self.state = self.conn.get_xfrstate()

    def test_handle_delete_rr(self):
        # Non SOA RRs are simply (goting to be) deleted in this state
        self.assertTrue(self.state.handle_rr(self.conn, self.ns_rrset))
        self.assertEqual([('delete', self.ns_rrset)],
                         self.conn._diff.get_buffer())
        # The state shouldn't change
        self.assertEqual(type(XfrinIXFRDelete()),
                         type(self.conn.get_xfrstate()))

    def test_handle_soa(self):
        # SOA in this state means the beginning of added RRs.  This SOA
        # should also be added in the next state, so handle_rr() should return
        # false.
        self.assertFalse(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual([], self.conn._diff.get_buffer())
        self.assertEqual(1234, self.conn._current_serial.get_value())
        self.assertEqual(type(XfrinIXFRAddSOA()),
                         type(self.conn.get_xfrstate()))

    def test_finish_message(self):
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinIXFRAddSOA(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinIXFRAddSOA()

    def test_handle_rr(self):
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinIXFRAdd()), type(self.conn.get_xfrstate()))
        self.assertEqual([('add', soa_rrset)],
                         self.conn._diff.get_buffer())

    def test_handle_non_soa(self):
        self.assertRaises(XfrinException, self.state.handle_rr, self.conn,
                          self.ns_rrset)

    def test_finish_message(self):
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinIXFRAdd(TestXfrinState):
    def setUp(self):
        super().setUp()
        # We need record the state in 'conn' to check the case where the
        # state doesn't change.
        XfrinIXFRAdd().set_xfrstate(self.conn, XfrinIXFRAdd())
        self.conn._current_serial = isc.dns.Serial(1230)
        self.state = self.conn.get_xfrstate()

    def test_handle_add_rr(self):
        # Non SOA RRs are simply (goting to be) added in this state
        self.assertTrue(self.state.handle_rr(self.conn, self.ns_rrset))
        self.assertEqual([('add', self.ns_rrset)],
                         self.conn._diff.get_buffer())
        # The state shouldn't change
        self.assertEqual(type(XfrinIXFRAdd()), type(self.conn.get_xfrstate()))

    def test_handle_end_soa(self):
        self.conn._end_serial = isc.dns.Serial(1234)
        self.conn._diff.add_data(self.ns_rrset) # put some dummy change
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        self.assertEqual(type(XfrinIXFREnd()), type(self.conn.get_xfrstate()))
        # handle_rr should have caused commit, and the buffer should now be
        # empty.
        self.assertEqual([], self.conn._diff.get_buffer())

    def test_handle_new_delete(self):
        self.conn._end_serial = isc.dns.Serial(1234)
        # SOA RR whose serial is the current one means we are going to a new
        # difference, starting with removing that SOA.
        self.conn._diff.add_data(self.ns_rrset) # put some dummy change
        self.assertFalse(self.state.handle_rr(self.conn, self.begin_soa))
        self.assertEqual([], self.conn._diff.get_buffer())
        self.assertEqual(type(XfrinIXFRDeleteSOA()),
                         type(self.conn.get_xfrstate()))

    def test_handle_new_delete_missing_sig(self):
        self.conn._end_serial = isc.dns.Serial(1234)
        # SOA RR whose serial is the current one means we are going to a new
        # difference, starting with removing that SOA.
        self.conn._diff.add_data(self.ns_rrset) # put some dummy change
        self.conn._tsig_ctx = MockTSIGContext(TSIG_KEY)
        self.conn._tsig_ctx.last_has_signature = lambda: False
        # This would try to finish up. But the TSIG pretends not everything is
        # signed, rejecting it.
        self.assertRaises(xfrin.XfrinProtocolError, self.state.handle_rr,
                          self.conn, self.begin_soa)

    def test_handle_out_of_sync(self):
        # getting SOA with an inconsistent serial.  This is an error.
        self.conn._end_serial = isc.dns.Serial(1235)
        self.assertRaises(XfrinProtocolError, self.state.handle_rr,
                          self.conn, soa_rrset)

    def test_finish_message(self):
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinIXFREnd(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinIXFREnd()

    def test_handle_rr(self):
        self.assertRaises(XfrinProtocolError, self.state.handle_rr, self.conn,
                          self.ns_rrset)

    def test_finish_message(self):
        self.assertFalse(self.state.finish_message(self.conn))

class TestXfrinIXFREndUpToDate(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinIXFRUptodate()

    def test_handle_rr(self):
        self.assertRaises(XfrinProtocolError, self.state.handle_rr, self.conn,
                          self.ns_rrset)

    def test_finish_message(self):
        self.assertRaises(XfrinZoneUptodate, self.state.finish_message,
                          self.conn)

class TestXfrinAXFR(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinAXFR()
        self.conn._end_serial = isc.dns.Serial(1234)

    def test_handle_rr(self):
        """
        Test we can put data inside.
        """
        # Put some data inside
        self.assertTrue(self.state.handle_rr(self.conn, self.a_rrset))
        # This test uses internal Diff structure to check the behaviour of
        # XfrinAXFR. Maybe there could be a cleaner way, but it would be more
        # complicated.
        self.assertEqual([('add', self.a_rrset)], self.conn._diff.get_buffer())
        # This SOA terminates the transfer
        self.assertTrue(self.state.handle_rr(self.conn, soa_rrset))
        # It should have changed the state
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        # At this point, the data haven't been committed yet
        self.assertEqual([('add', self.a_rrset), ('add', soa_rrset)],
                         self.conn._diff.get_buffer())

    def test_handle_rr_mismatch_soa(self):
        """ SOA with inconsistent serial - unexpected, but we accept it.

        """
        self.assertTrue(self.state.handle_rr(self.conn, begin_soa_rrset))
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))

    def test_finish_message(self):
        """
        Check normal end of message.
        """
        # When a message ends, nothing happens usually
        self.assertTrue(self.state.finish_message(self.conn))

class TestXfrinAXFREnd(TestXfrinState):
    def setUp(self):
        super().setUp()
        self.state = XfrinAXFREnd()

    def test_handle_rr(self):
        self.assertRaises(XfrinProtocolError, self.state.handle_rr, self.conn,
                          self.ns_rrset)

    def test_finish_message(self):
        self.conn._diff.add_data(self.a_rrset)
        self.conn._diff.add_data(soa_rrset)
        self.assertFalse(self.state.finish_message(self.conn))

        # The data should have been committed
        self.assertEqual([], self.conn._diff.get_buffer())
        check_diffs(self.assertEqual, [[('add', self.a_rrset),
                                        ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)
        self.assertRaises(ValueError, self.conn._diff.commit)

class TestXfrinConnection(unittest.TestCase):
    '''Convenient parent class for XFR-protocol tests.

    This class provides common setups and helper methods for protocol related
    tests on AXFR and IXFR.

    '''

    def setUp(self):
        if os.path.exists(TEST_DB_FILE):
            os.remove(TEST_DB_FILE)
        self.sock_map = {}
        self.conn = MockXfrinConnection(self.sock_map, TEST_ZONE_NAME,
                                        TEST_RRCLASS, None, threading.Event(),
                                        TEST_MASTER_IPV4_ADDRINFO)
        self.conn.init_socket()
        self.soa_response_params = {
            'questions': [example_soa_question],
            'bad_qid': False,
            'response': True,
            'auth': True,
            'rcode': Rcode.NOERROR(),
            'answers': default_answers,
            'authorities': [],
            'tsig': False,
            'axfr_after_soa': self._create_normal_response_data
            }
        self.axfr_response_params = {
            'question_1st': default_questions,
            'question_2nd': default_questions,
            'answer_1st': [soa_rrset, self._create_ns()],
            'answer_2nd': default_answers,
            'tsig_1st': None,
            'tsig_2nd': None
            }

    def tearDown(self):
        self.conn.close()
        if os.path.exists(TEST_DB_FILE):
            os.remove(TEST_DB_FILE)

    def _create_normal_response_data(self):
        # This helper method creates a simple sequence of DNS messages that
        # forms a valid AXFR transaction.  It consists of two messages: the
        # first one containing SOA, NS, the second containing the trailing SOA.
        question_1st = self.axfr_response_params['question_1st']
        question_2nd = self.axfr_response_params['question_2nd']
        answer_1st = self.axfr_response_params['answer_1st']
        answer_2nd = self.axfr_response_params['answer_2nd']
        tsig_1st = self.axfr_response_params['tsig_1st']
        tsig_2nd = self.axfr_response_params['tsig_2nd']
        self.conn.reply_data = self.conn.create_response_data(
            questions=question_1st, answers=answer_1st,
            tsig_ctx=tsig_1st)
        self.conn.reply_data += \
            self.conn.create_response_data(questions=question_2nd,
                                           answers=answer_2nd,
                                           tsig_ctx=tsig_2nd)

    def _create_soa_response_data(self):
        # This helper method creates a DNS message that is supposed to be
        # used a valid response to SOA queries prior to XFR.
        # If tsig is True, it tries to verify the query with a locally
        # created TSIG context (which may or may not succeed) so that the
        # response will include a TSIG.
        # If axfr_after_soa is True, it resets the response_generator so that
        # a valid XFR messages will follow.

        verify_ctx = None
        if self.soa_response_params['tsig']:
            # xfrin (currently) always uses TCP.  strip off the length field.
            query_data = self.conn.query_data[2:]
            query_message = Message(Message.PARSE)
            query_message.from_wire(query_data)
            verify_ctx = TSIGContext(TSIG_KEY)
            verify_ctx.verify(query_message.get_tsig_record(), query_data)

        self.conn.reply_data = self.conn.create_response_data(
            bad_qid=self.soa_response_params['bad_qid'],
            response=self.soa_response_params['response'],
            auth=self.soa_response_params['auth'],
            rcode=self.soa_response_params['rcode'],
            questions=self.soa_response_params['questions'],
            answers=self.soa_response_params['answers'],
            authorities=self.soa_response_params['authorities'],
            tsig_ctx=verify_ctx)
        if self.soa_response_params['axfr_after_soa'] != None:
            self.conn.response_generator = \
                self.soa_response_params['axfr_after_soa']

    def _create_broken_response_data(self):
        # This helper method creates a bogus "DNS message" that only contains
        # 4 octets of data.  The DNS message parser will raise an exception.
        bogus_data = b'xxxx'
        self.conn.reply_data = struct.pack('H', socket.htons(len(bogus_data)))
        self.conn.reply_data += bogus_data

    def _create_a(self, address):
        rrset = RRset(Name('a.example.com'), TEST_RRCLASS, RRType.A(),
                      RRTTL(3600))
        rrset.add_rdata(Rdata(RRType.A(), TEST_RRCLASS, address))
        return rrset

    def _create_soa(self, serial):
        rrset = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.SOA(),
                      RRTTL(3600))
        rdata_str = 'm. r. ' + serial + ' 3600 1800 2419200 7200'
        rrset.add_rdata(Rdata(RRType.SOA(), TEST_RRCLASS, rdata_str))
        return rrset

    def _create_ns(self, nsname='ns.'+TEST_ZONE_NAME_STR):
        rrset = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.NS(), RRTTL(3600))
        rrset.add_rdata(Rdata(RRType.NS(), TEST_RRCLASS, nsname))
        return rrset

    def _set_test_zone(self, zone_name):
        '''Set the zone name for transfer to the specified one.

        It also make sure that the SOA RR (if exist) is correctly (re)set.

        '''
        self.conn._zone_name = zone_name
        self.conn._zone_soa = self.conn._get_zone_soa()

class TestAXFR(TestXfrinConnection):
    def setUp(self):
        # replace time.time with a steadily increasing fake one
        self.orig_time_time = time.time
        time.time = get_fake_time_time()
        super().setUp()
        XfrinInitialSOA().set_xfrstate(self.conn, XfrinInitialSOA())

    def tearDown(self):
        time.time = self.orig_time_time

    def __create_mock_tsig(self, key, error, has_last_signature=True):
        # This helper function creates a MockTSIGContext for a given key
        # and TSIG error to be used as a result of verify (normally faked
        # one)
        mock_ctx = MockTSIGContext(key)
        mock_ctx.error = error
        if not has_last_signature:
            mock_ctx.last_has_signature = lambda: False
        return mock_ctx

    def __match_exception(self, expected_exception, expected_msg, expression):
        # This helper method is a higher-granularity version of assertRaises().
        # If it's not sufficient to check the exception class (e.g., when
        # the same type of exceptions can be thrown from many places), this
        # method can be used to check it with the exception argument.
        try:
            expression()
        except expected_exception as ex:
            self.assertEqual(str(ex), expected_msg)
        else:
            self.assertFalse('exception is expected, but not raised')

    def test_close(self):
        # we shouldn't be using the global asyncore map.
        self.assertEqual(len(asyncore.socket_map), 0)
        # there should be exactly one entry in our local map
        self.assertEqual(len(self.sock_map), 1)
        # once closing the dispatch the map should become empty
        self.conn.close()
        self.assertEqual(len(self.sock_map), 0)

    def test_init_ip6(self):
        # This test simply creates a new XfrinConnection object with an
        # IPv6 address, tries to bind it to an IPv6 wildcard address/port
        # to confirm an AF_INET6 socket has been created.  A naive application
        # tends to assume it's IPv4 only and hardcode AF_INET.  This test
        # uncovers such a bug.
        c = MockXfrinConnection({}, TEST_ZONE_NAME, TEST_RRCLASS, None,
                                threading.Event(), TEST_MASTER_IPV6_ADDRINFO)
        c.init_socket()
        c.bind(('::', 0))
        c.close()

    def test_init_chclass(self):
        c = MockXfrinConnection({}, TEST_ZONE_NAME, RRClass.CH(), None,
                                threading.Event(), TEST_MASTER_IPV4_ADDRINFO)
        c.init_socket()
        axfrmsg = c._create_query(RRType.AXFR())
        self.assertEqual(axfrmsg.get_question()[0].get_class(),
                         RRClass.CH())
        c.close()

    def test_create_query(self):
        def check_query(expected_qtype, expected_auth):
            '''Helper method to repeat the same pattern of tests'''
            self.assertEqual(Opcode.QUERY(), msg.get_opcode())
            self.assertEqual(Rcode.NOERROR(), msg.get_rcode())
            self.assertEqual(1, msg.get_rr_count(Message.SECTION_QUESTION))
            self.assertEqual(TEST_ZONE_NAME, msg.get_question()[0].get_name())
            self.assertEqual(expected_qtype, msg.get_question()[0].get_type())
            self.assertEqual(0, msg.get_rr_count(Message.SECTION_ANSWER))
            self.assertEqual(0, msg.get_rr_count(Message.SECTION_ADDITIONAL))
            if expected_auth is None:
                self.assertEqual(0,
                                 msg.get_rr_count(Message.SECTION_AUTHORITY))
            else:
                self.assertEqual(1,
                                 msg.get_rr_count(Message.SECTION_AUTHORITY))
                auth_rr = msg.get_section(Message.SECTION_AUTHORITY)[0]
                self.assertEqual(expected_auth.get_name(), auth_rr.get_name())
                self.assertEqual(expected_auth.get_type(), auth_rr.get_type())
                self.assertEqual(expected_auth.get_class(),
                                 auth_rr.get_class())
                # In our test scenario RDATA must be 1
                self.assertEqual(1, expected_auth.get_rdata_count())
                self.assertEqual(1, auth_rr.get_rdata_count())
                self.assertEqual(expected_auth.get_rdata()[0],
                                 auth_rr.get_rdata()[0])

        # Actual tests start here
        # SOA query
        msg = self.conn._create_query(RRType.SOA())
        check_query(RRType.SOA(), None)

        # AXFR query
        msg = self.conn._create_query(RRType.AXFR())
        check_query(RRType.AXFR(), None)

        # IXFR query
        msg = self.conn._create_query(RRType.IXFR())
        check_query(RRType.IXFR(), begin_soa_rrset)
        self.assertEqual(1230, self.conn._request_serial.get_value())

    def test_create_ixfr_query_fail(self):
        # In these cases _create_query() will fail to find a valid SOA RR to
        # insert in the IXFR query, and should raise an exception.

        self._set_test_zone(Name('no-such-zone.example'))
        self.assertRaises(XfrinException, self.conn._create_query,
                          RRType.IXFR())

        self._set_test_zone(Name('partial-match-zone.example'))
        self.assertRaises(XfrinException, self.conn._create_query,
                          RRType.IXFR())

        self._set_test_zone(Name('no-soa.example'))
        self.assertRaises(XfrinException, self.conn._create_query,
                          RRType.IXFR())

        self._set_test_zone(Name('dup-soa.example'))
        self.conn._zone_soa = self.conn._get_zone_soa()
        self.assertRaises(XfrinException, self.conn._create_query,
                          RRType.IXFR())

    def test_send_query(self):
        def message_has_tsig(data):
            # a simple check if the actual data contains a TSIG RR.
            # At our level this simple check should suffice; other detailed
            # tests regarding the TSIG protocol are done in pydnspp.
            msg = Message(Message.PARSE)
            msg.from_wire(data)
            return msg.get_tsig_record() is not None

        # soa request with tsig
        self.conn._tsig_key = TSIG_KEY
        self.conn._send_query(RRType.SOA())
        self.assertTrue(message_has_tsig(self.conn.query_data[2:]))

        # axfr request with tsig
        self.conn._send_query(RRType.AXFR())
        self.assertTrue(message_has_tsig(self.conn.query_data[2:]))

    def test_response_with_invalid_msg(self):
        self.conn.reply_data = b'aaaxxxx'
        self.assertRaises(XfrinTestException,
                          self.conn._handle_xfrin_responses)

    def test_response_with_tsigfail(self):
        self.conn._tsig_key = TSIG_KEY
        # server tsig check fail, return with RCODE 9 (NOTAUTH)
        self.conn._send_query(RRType.SOA())
        self.conn.reply_data = \
            self.conn.create_response_data(rcode=Rcode.NOTAUTH())
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)

    def test_response_without_end_soa(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data()
        # This should result in timeout in the asyncore loop.  We emulate
        # that situation in recv() by emptying the reply data buffer.
        self.assertRaises(XfrinTestTimeoutException,
                          self.conn._handle_xfrin_responses)

    def test_response_bad_qid(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(bad_qid=True)
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)

    def test_response_error_code_bad_sig(self):
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.BAD_SIG)
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
                rcode=Rcode.SERVFAIL())
        # xfrin should check TSIG before other part of incoming message
        # validate log message for XfrinException
        self.__match_exception(XfrinProtocolError,
                               "TSIG verify fail: BADSIG",
                               self.conn._handle_xfrin_responses)

    def test_response_bad_qid_bad_key(self):
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.BAD_KEY)
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(bad_qid=True)
        # xfrin should check TSIG before other part of incoming message
        # validate log message for XfrinException
        self.__match_exception(XfrinProtocolError,
                               "TSIG verify fail: BADKEY",
                               self.conn._handle_xfrin_responses)

    def test_response_non_response(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(response=False)
        self.assertRaises(XfrinException, self.conn._handle_xfrin_responses)

    def test_response_error_code(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
            rcode=Rcode.SERVFAIL())
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)

    def test_response_multi_question(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
            questions=[example_axfr_question, example_axfr_question])
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)

    def test_response_non_response(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(response = False)
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)

    def test_soacheck(self):
        # we need to defer the creation until we know the QID, which is
        # determined in _check_soa_serial(), so we use response_generator.
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn._check_soa_serial(), XFRIN_OK)

    def test_soacheck_with_bad_response(self):
        self.conn.response_generator = self._create_broken_response_data
        self.assertRaises(MessageTooShort, self.conn._check_soa_serial)

    def test_soacheck_badqid(self):
        self.soa_response_params['bad_qid'] = True
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_bad_qid_bad_sig(self):
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.BAD_SIG)
        self.soa_response_params['bad_qid'] = True
        self.conn.response_generator = self._create_soa_response_data
        # xfrin should check TSIG before other part of incoming message
        # validate log message for XfrinException
        self.__match_exception(XfrinProtocolError,
                               "TSIG verify fail: BADSIG",
                               self.conn._check_soa_serial)

    def test_soacheck_non_response(self):
        self.soa_response_params['response'] = False
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_error_code(self):
        self.soa_response_params['rcode'] = Rcode.SERVFAIL()
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_notauth(self):
        self.soa_response_params['auth'] = False
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_uptodate(self):
        # Primary's SOA serial is identical the local serial
        self.soa_response_params['answers'] = [begin_soa_rrset]
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinZoneUptodate, self.conn._check_soa_serial)

    def test_soacheck_uptodate2(self):
        # Primary's SOA serial is "smaller" than the local serial
        self.soa_response_params['answers'] = [create_soa(1229)]
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinZoneUptodate, self.conn._check_soa_serial)

    def test_soacheck_uptodate3(self):
        # Similar to the previous case, but checking the comparison is based
        # on the serial number arithmetic.
        self.soa_response_params['answers'] = [create_soa(0xffffffff)]
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinZoneUptodate, self.conn._check_soa_serial)

    def test_soacheck_newzone(self):
        # Primary's SOA is 'old', but this secondary doesn't know anything
        # about the zone yet, so it should accept it.
        def response_generator():
            # _request_serial is set in _check_soa_serial().  Reset it here.
            self.conn._request_serial = None
            self._create_soa_response_data()
        self.soa_response_params['answers'] = [begin_soa_rrset]
        self.conn.response_generator = response_generator
        self.assertEqual(XFRIN_OK, self.conn._check_soa_serial())

    def test_soacheck_question_empty(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['questions'] = []
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_question_name_mismatch(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['questions'] = [Question(Name('example.org'),
                                                          TEST_RRCLASS,
                                                          RRType.SOA())]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_question_class_mismatch(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['questions'] = [Question(TEST_ZONE_NAME,
                                                          RRClass.CH(),
                                                          RRType.SOA())]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_question_type_mismatch(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['questions'] = [Question(TEST_ZONE_NAME,
                                                          TEST_RRCLASS,
                                                          RRType.AAAA())]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_no_soa(self):
        # The response just doesn't contain SOA without any other indication
        # of errors.
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['answers'] = []
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_soa_name_mismatch(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['answers'] = [create_soa(1234,
                                                          Name('example.org'))]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_soa_class_mismatch(self):
        self.conn.response_generator = self._create_soa_response_data
        soa = RRset(TEST_ZONE_NAME, RRClass.CH(), RRType.SOA(), RRTTL(0))
        soa.add_rdata(Rdata(RRType.SOA(), RRClass.CH(), 'm. r. 1234 0 0 0 0'))
        self.soa_response_params['answers'] = [soa]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_multiple_soa(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['answers'] = [soa_rrset, soa_rrset]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_cname_response(self):
        self.conn.response_generator = self._create_soa_response_data
        # Add SOA to answer, too, to make sure that it that deceives the parser
        self.soa_response_params['answers'] = [soa_rrset, create_cname()]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_referral_response(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['answers'] = []
        self.soa_response_params['authorities'] = [create_ns('ns.example.com')]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_nodata_response(self):
        self.conn.response_generator = self._create_soa_response_data
        self.soa_response_params['answers'] = []
        self.soa_response_params['authorities'] = [soa_rrset]
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_with_tsig(self):
        # Use a mock tsig context emulating a validly signed response
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.NOERROR)
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn._check_soa_serial(), XFRIN_OK)
        self.assertEqual(self.conn._tsig_ctx.get_error(), TSIGError.NOERROR)

    def test_soacheck_with_tsig_notauth(self):
        # emulate a valid error response
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.BAD_SIG)
        self.soa_response_params['rcode'] = Rcode.NOTAUTH()
        self.conn.response_generator = self._create_soa_response_data

        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_with_tsig_noerror_badsig(self):
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.BAD_SIG)

        # emulate a normal response bad verification failure due to BADSIG.
        # According RFC2845, in this case we should ignore it and keep
        # waiting for a valid response until a timeout.  But we immediately
        # treat this as a final failure (just as BIND 9 does).
        self.conn.response_generator = self._create_soa_response_data

        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_with_tsig_unsigned_response(self):
        # we can use a real TSIGContext for this.  the response doesn't
        # contain a TSIG while we sent a signed query.  RFC2845 states
        # we should wait for a valid response in this case, but we treat
        # it as a fatal transaction failure, too.
        self.conn._tsig_key = TSIG_KEY
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_soacheck_with_unexpected_tsig_response(self):
        # we reject unexpected TSIG in responses (following BIND 9's
        # behavior)
        self.soa_response_params['tsig'] = True
        self.conn.response_generator = self._create_soa_response_data
        self.assertRaises(XfrinProtocolError, self.conn._check_soa_serial)

    def test_response_shutdown(self):
        self.conn.response_generator = self._create_normal_response_data
        self.conn._shutdown_event.set()
        self.conn._send_query(RRType.AXFR())
        self.assertRaises(XfrinException, self.conn._handle_xfrin_responses)

    def test_response_timeout(self):
        self.conn.response_generator = self._create_normal_response_data
        self.conn.force_time_out = True
        self.assertRaises(XfrinException, self.conn._handle_xfrin_responses)

    def test_response_remote_close(self):
        self.conn.response_generator = self._create_normal_response_data
        self.conn.force_close = True
        self.assertRaises(XfrinException, self.conn._handle_xfrin_responses)

    def test_response_bad_message(self):
        self.conn.response_generator = self._create_broken_response_data
        self.conn._send_query(RRType.AXFR())
        self.assertRaises(Exception, self.conn._handle_xfrin_responses)

    def test_axfr_response(self):
        # A simple normal case: AXFR consists of SOA, NS, then trailing SOA.
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(RRType.AXFR())
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_response_empty_answer(self):
        '''Test with an empty AXFR answer section.

        This is an unusual response, but there is no reason to reject it.
        The second message is a complete AXFR response, and transfer should
        succeed just like the normal case.

        '''

        self.axfr_response_params['answer_1st'] = []
        self.axfr_response_params['answer_2nd'] = [soa_rrset,
                                                   self._create_ns(),
                                                   soa_rrset]
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(RRType.AXFR())
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_axfr_response_soa_mismatch(self):
        '''AXFR response whose begin/end SOAs are not same.

        What should we do this is moot, for now we accept it, so does BIND 9.

        '''
        ns_rr = self._create_ns()
        a_rr = self._create_a('192.0.2.1')
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                RRType.AXFR())],
            # begin serial=1230, end serial=1234. end will be used.
            answers=[begin_soa_rrset, ns_rr, a_rr, soa_rrset])
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', ns_rr), ('add', a_rr), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_axfr_response_extra(self):
        '''Test with an extra RR after the end of AXFR session.

        The session should be rejected, and nothing should be committed.

        '''
        ns_rr = self._create_ns()
        a_rr = self._create_a('192.0.2.1')
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                RRType.AXFR())],
            answers=[soa_rrset, ns_rr, a_rr, soa_rrset, a_rr])
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        self.assertEqual([], self.conn._datasrc_client.committed_diffs)

    def test_axfr_response_qname_mismatch(self):
        '''AXFR response with a mismatch question name.

        Our implementation accepts that, so does BIND 9.

        '''
        self.axfr_response_params['question_1st'] = \
            [Question(Name('mismatch.example'), TEST_RRCLASS, RRType.AXFR())]
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(RRType.AXFR())
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_axfr_response_qclass_mismatch(self):
        '''AXFR response with a mismatch RR class.

        Our implementation accepts that, so does BIND 9.

        '''
        self.axfr_response_params['question_1st'] = \
            [Question(TEST_ZONE_NAME, RRClass.CH(), RRType.AXFR())]
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(RRType.AXFR())
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_axfr_response_qtype_mismatch(self):
        '''AXFR response with a mismatch RR type.

        Our implementation accepts that, so does BIND 9.

        '''
        # returning IXFR in question to AXFR query
        self.axfr_response_params['question_1st'] = \
            [Question(TEST_ZONE_NAME, RRClass.CH(), RRType.IXFR())]
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(RRType.AXFR())
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_axfr_response_empty_question(self):
        '''AXFR response with an empty question.

        Our implementation accepts that, so does BIND 9.

        '''
        self.axfr_response_params['question_1st'] = []
        self.conn.response_generator = self._create_normal_response_data
        self.conn._send_query(RRType.AXFR())
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_do_xfrin(self):
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)
        self.assertFalse(self.conn._datasrc_client._journaling_enabled)

        self.assertEqual(2, self.conn._transfer_stats.message_count)
        self.assertEqual(2, self.conn._transfer_stats.axfr_rr_count)
        self.assertEqual(0, self.conn._transfer_stats.ixfr_changeset_count)
        self.assertEqual(0, self.conn._transfer_stats.ixfr_deletion_count)
        self.assertEqual(0, self.conn._transfer_stats.ixfr_addition_count)
        self.assertEqual(177, self.conn._transfer_stats.byte_count)
        self.assertGreater(self.conn._transfer_stats.get_running_time(), 0)

    def test_do_xfrin_with_tsig(self):
        # use TSIG with a mock context.  we fake all verify results to
        # emulate successful verification.
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.NOERROR)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_OK)
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('add', self._create_ns()), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_do_xfrin_with_tsig_fail(self):
        # TSIG verify will fail for the first message.  xfrin should fail
        # immediately.
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.BAD_SIG)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)
        self.assertEqual(1, self.conn._tsig_ctx.verify_called)

    def test_do_xfrin_without_last_tsig(self):
        # TSIG verify will succeed, but it will pretend the last message is
        # not signed.
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.NOERROR, False)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)
        self.assertEqual(2, self.conn._tsig_ctx.verify_called)

    def test_do_xfrin_with_tsig_fail_for_second_message(self):
        # Similar to the previous test, but first verify succeeds.  There
        # should be a second verify attempt, which will fail, which should
        # make xfrin fail.
        def fake_tsig_error(ctx):
            if self.conn._tsig_ctx.verify_called == 1:
                return TSIGError.NOERROR
            return TSIGError.BAD_SIG
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, fake_tsig_error)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)
        self.assertEqual(2, self.conn._tsig_ctx.verify_called)

    def test_do_xfrin_with_missing_tsig(self):
        # XFR request sent with TSIG, but the response doesn't have TSIG.
        # xfr should fail.
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, None)
        self.conn._tsig_ctx = MockTSIGContext(TSIG_KEY)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)
        self.assertEqual(1, self.conn._tsig_ctx.verify_called)

    def test_do_xfrin_with_missing_tsig_for_second_message(self):
        # Similar to the previous test, but firt one contains TSIG and verify
        # succeeds (due to fake).  The second message lacks TSIG.
        #
        # Note: this test case is actually not that trivial:  Skipping
        # intermediate TSIG is allowed.  In this case, however, the second
        # message is the last one, which must contain TSIG anyway, so the
        # expected result is correct.  If/when we support skipping
        # intermediate TSIGs, we'll need additional test cases.
        def fake_tsig_error(ctx):
            if self.conn._tsig_ctx.verify_called == 1:
                return TSIGError.NOERROR
            return TSIGError.FORMERR
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, fake_tsig_error)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)
        self.assertEqual(2, self.conn._tsig_ctx.verify_called)

    def test_do_xfrin_with_unexpected_tsig(self):
        # XFR request wasn't signed, but response includes TSIG.  Like BIND 9,
        # we reject that.
        self.axfr_response_params['tsig_1st'] = TSIGContext(TSIG_KEY)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)

    def test_do_xfrin_with_unexpected_tsig_for_second_message(self):
        # similar to the previous test, but the first message is normal.
        # the second one contains an unexpected TSIG.  should be rejected.
        self.axfr_response_params['tsig_2nd'] = TSIGContext(TSIG_KEY)
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)

    def test_do_xfrin_empty_response(self):
        # skipping the creation of response data, so the transfer will fail.
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)

    def test_do_xfrin_bad_response(self):
        self.conn.response_generator = self._create_broken_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)

    def test_do_xfrin_datasrc_error(self):
        # Emulate failure in the data source client on commit.
        self.conn._datasrc_client.force_fail = True
        self.conn.response_generator = self._create_normal_response_data
        self.assertEqual(self.conn.do_xfrin(False), XFRIN_FAIL)

    def test_do_soacheck_and_xfrin(self):
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn.do_xfrin(True), XFRIN_OK)

    def test_do_soacheck_uptodate(self):
        self.soa_response_params['answers'] = [begin_soa_rrset]
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn.do_xfrin(True), XFRIN_OK)

    def test_do_soacheck_protocol_error(self):
        # There are several cases, but at this level it's sufficient to check
        # only one.  We use the case where there's no SOA in the response.
        self.soa_response_params['answers'] = []
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn.do_xfrin(True), XFRIN_FAIL)

    def test_do_soacheck_and_xfrin_with_tsig(self):
        # We are going to have a SOA query/response transaction, followed by
        # AXFR, all TSIG signed.  xfrin should use a new TSIG context for
        # AXFR.  We are not interested in whether verify works correctly in
        # this test, so we simply fake the results (they need to succeed for
        # this test)
        self.conn._tsig_key = TSIG_KEY
        self.conn._tsig_ctx_creator = \
            lambda key: self.__create_mock_tsig(key, TSIGError.NOERROR)
        self.soa_response_params['tsig'] = True
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn.do_xfrin(True), XFRIN_OK)
        # We should've got 3 response messages: 1 SOA and two AXFR, but
        # the context should be replaced for AXFR, so verify() should be
        # called only twice for the latest context.
        self.assertEqual(2, self.conn._tsig_ctx.verify_called)

    def test_do_soacheck_broken_response(self):
        self.conn.response_generator = self._create_broken_response_data
        self.assertEqual(self.conn.do_xfrin(True), XFRIN_FAIL)

    def test_do_soacheck_badqid(self):
        # the QID mismatch would internally trigger a XfrinException exception,
        # and covers part of the code that other tests can't.
        self.soa_response_params['bad_qid'] = True
        self.conn.response_generator = self._create_soa_response_data
        self.assertEqual(self.conn.do_xfrin(True), XFRIN_FAIL)

class TestIXFRResponse(TestXfrinConnection):
    def setUp(self):
        # replace time.time with a steadily increasing fake one
        self.orig_time_time = time.time
        time.time = get_fake_time_time()

        super().setUp()
        self.conn._query_id = self.conn.qid = 1035
        self.conn._request_serial = isc.dns.Serial(1230)
        self.conn._request_type = RRType.IXFR()
        self.conn._datasrc_client = MockDataSourceClient()
        XfrinInitialSOA().set_xfrstate(self.conn, XfrinInitialSOA())

    def tearDown(self):
        time.time = self.orig_time_time

    def test_ixfr_response(self):
        '''A simplest form of IXFR response.

        It simply updates the zone's SOA one time.

        '''
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, begin_soa_rrset, soa_rrset, soa_rrset])
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinIXFREnd()), type(self.conn.get_xfrstate()))
        self.assertTrue(self.conn._datasrc_client._journaling_enabled)
        self.assertEqual([], self.conn._datasrc_client.diffs)
        check_diffs(self.assertEqual,
                    [[('delete', begin_soa_rrset), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_ixfr_response_multi_sequences(self):
        '''Similar to the previous case, but with multiple diff seqs.

        '''
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset,
                     # removing one A in serial 1230
                     begin_soa_rrset, self._create_a('192.0.2.1'),
                     # adding one A in serial 1231
                     self._create_soa('1231'), self._create_a('192.0.2.2'),
                     # removing one A in serial 1231
                     self._create_soa('1231'), self._create_a('192.0.2.3'),
                     # adding one A in serial 1232
                     self._create_soa('1232'), self._create_a('192.0.2.4'),
                     # removing one A in serial 1232
                     self._create_soa('1232'), self._create_a('192.0.2.5'),
                     # adding one A in serial 1234
                     soa_rrset, self._create_a('192.0.2.6'),
                     soa_rrset])
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinIXFREnd()), type(self.conn.get_xfrstate()))
        self.assertEqual([], self.conn._datasrc_client.diffs)
        check_diffs(self.assertEqual,
                    [[('delete', begin_soa_rrset),
                      ('delete', self._create_a('192.0.2.1')),
                      ('add', self._create_soa('1231')),
                      ('add', self._create_a('192.0.2.2'))],
                     [('delete', self._create_soa('1231')),
                      ('delete', self._create_a('192.0.2.3')),
                      ('add', self._create_soa('1232')),
                      ('add', self._create_a('192.0.2.4'))],
                     [('delete', self._create_soa('1232')),
                      ('delete', self._create_a('192.0.2.5')),
                      ('add', soa_rrset),
                      ('add', self._create_a('192.0.2.6'))]],
                    self.conn._datasrc_client.committed_diffs)

    def test_ixfr_response_multi_messages(self):
        '''Similar to the first case, but RRs span over multiple messages.

        '''
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, begin_soa_rrset, soa_rrset])
        self.conn.reply_data += self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset])
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinIXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('delete', begin_soa_rrset), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_ixfr_response_uptodate(self):
        '''IXFR response indicates the zone is new enough'''
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[begin_soa_rrset])
        self.assertRaises(XfrinZoneUptodate, self.conn._handle_xfrin_responses)
        # no diffs should have been committed
        check_diffs(self.assertEqual,
                    [], self.conn._datasrc_client.committed_diffs)

    def test_ixfr_response_broken(self):
        '''Test with a broken response.

        '''
        # SOA sequence is out-of-sync
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, begin_soa_rrset, soa_rrset,
                     self._create_soa('1235')])
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)
        # no diffs should have been committed
        check_diffs(self.assertEqual,
                    [], self.conn._datasrc_client.committed_diffs)

    def test_ixfr_response_extra(self):
        '''Test with an extra RR after the end of IXFR diff sequences.

        IXFR should be rejected, but complete diff sequences should be
        committed; it's not clear whether it's compliant to the protocol
        specification, but it is how BIND 9 works and we do the same.
        '''
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, begin_soa_rrset, soa_rrset, soa_rrset,
                     self._create_a('192.0.2.1')])
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)
        check_diffs(self.assertEqual,
                    [[('delete', begin_soa_rrset), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_ixfr_response_uptodate_extra(self):
        '''Similar to 'uptodate' test, but with extra bogus data.

        In either case an exception will be raised, but in this case it's
        considered an error.

        '''
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[begin_soa_rrset, soa_rrset])
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)
        # no diffs should have been committed
        check_diffs(self.assertEqual,
                    [], self.conn._datasrc_client.committed_diffs)

    def test_ixfr_to_axfr_response(self):
        '''AXFR-style IXFR response.

        It simply updates the zone's SOA one time.

        '''
        ns_rr = self._create_ns()
        a_rr = self._create_a('192.0.2.1')
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, ns_rr, a_rr, soa_rrset])
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        # In the case AXFR-style IXFR, journaling must have been disabled.
        self.assertFalse(self.conn._datasrc_client._journaling_enabled)
        self.assertEqual([], self.conn._datasrc_client.diffs)
        # The SOA should be added exactly once, and in our implementation
        # it should be added at the end of the sequence.
        check_diffs(self.assertEqual,
                    [[('add', ns_rr), ('add', a_rr), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_ixfr_to_axfr_response_mismatch_soa(self):
        '''AXFR-style IXFR response, but the two SOA are not the same.

        In the current implementation, we accept it and use the second SOA.

        '''
        ns_rr = self._create_ns()
        a_rr = self._create_a('192.0.2.1')
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, ns_rr, a_rr, begin_soa_rrset])
        self.conn._handle_xfrin_responses()
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        self.assertEqual([], self.conn._datasrc_client.diffs)
        check_diffs(self.assertEqual,
                    [[('add', ns_rr), ('add', a_rr),
                      ('add', begin_soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

    def test_ixfr_to_axfr_response_extra(self):
        '''Test with an extra RR after the end of AXFR-style IXFR session.

        The session should be rejected, and nothing should be committed.

        '''
        ns_rr = self._create_ns()
        a_rr = self._create_a('192.0.2.1')
        self.conn.reply_data = self.conn.create_response_data(
            questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, RRType.IXFR())],
            answers=[soa_rrset, ns_rr, a_rr, soa_rrset, a_rr])
        self.assertRaises(XfrinProtocolError,
                          self.conn._handle_xfrin_responses)
        self.assertEqual(type(XfrinAXFREnd()), type(self.conn.get_xfrstate()))
        self.assertEqual([], self.conn._datasrc_client.committed_diffs)

class TestIXFRSession(TestXfrinConnection):
    '''Tests for a full IXFR session (query and response).

    Detailed corner cases should have been covered in test_create_query()
    and TestIXFRResponse, so we'll only check some typical cases to confirm
    the general logic flow.
    '''
    def setUp(self):
        # replace time.time with a steadily increasing fake one
        self.orig_time_time = time.time
        time.time = get_fake_time_time()
        super().setUp()

    def tearDown(self):
        time.time = self.orig_time_time

    def test_do_xfrin(self):
        def create_ixfr_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                    RRType.IXFR())],
                answers=[soa_rrset, begin_soa_rrset, soa_rrset, soa_rrset])
        self.conn.response_generator = create_ixfr_response
        self.assertEqual(XFRIN_OK, self.conn.do_xfrin(False, RRType.IXFR()))

        # Check some details of the IXFR protocol processing
        self.assertEqual(type(XfrinIXFREnd()), type(self.conn.get_xfrstate()))
        check_diffs(self.assertEqual,
                    [[('delete', begin_soa_rrset), ('add', soa_rrset)]],
                    self.conn._datasrc_client.committed_diffs)

        # Check if the query was IXFR.
        qdata = self.conn.query_data[2:]
        qmsg = Message(Message.PARSE)
        qmsg.from_wire(qdata, len(qdata))
        self.assertEqual(1, qmsg.get_rr_count(Message.SECTION_QUESTION))
        self.assertEqual(TEST_ZONE_NAME, qmsg.get_question()[0].get_name())
        self.assertEqual(RRType.IXFR(), qmsg.get_question()[0].get_type())

        self.assertEqual(1, self.conn._transfer_stats.message_count)
        self.assertEqual(0, self.conn._transfer_stats.axfr_rr_count)
        self.assertEqual(1, self.conn._transfer_stats.ixfr_changeset_count)
        self.assertEqual(1, self.conn._transfer_stats.ixfr_deletion_count)
        self.assertEqual(1, self.conn._transfer_stats.ixfr_addition_count)
        self.assertEqual(188, self.conn._transfer_stats.byte_count)
        self.assertGreater(self.conn._transfer_stats.get_running_time(), 0)

    def test_do_xfrin_fail(self):
        '''IXFR fails due to a protocol error.

        '''
        def create_ixfr_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                    RRType.IXFR())],
                answers=[soa_rrset, begin_soa_rrset, soa_rrset,
                         self._create_soa('1235')])
        self.conn.response_generator = create_ixfr_response
        self.assertEqual(XFRIN_FAIL, self.conn.do_xfrin(False, RRType.IXFR()))

    def test_do_xfrin_fail2(self):
        '''IXFR fails due to a bogus DNS message.

        '''
        self._create_broken_response_data()
        self.assertEqual(XFRIN_FAIL, self.conn.do_xfrin(False, RRType.IXFR()))

    def test_do_xfrin_uptodate(self):
        '''IXFR is (gracefully) aborted because serial is not new

        '''
        def create_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                    RRType.IXFR())],
                answers=[begin_soa_rrset])
        self.conn.response_generator = create_response
        self.assertEqual(XFRIN_OK, self.conn.do_xfrin(False, RRType.IXFR()))

        self.assertEqual(1, self.conn._transfer_stats.message_count)
        self.assertEqual(0, self.conn._transfer_stats.axfr_rr_count)
        self.assertEqual(0, self.conn._transfer_stats.ixfr_changeset_count)
        self.assertEqual(0, self.conn._transfer_stats.ixfr_deletion_count)
        self.assertEqual(0, self.conn._transfer_stats.ixfr_addition_count)
        self.assertEqual(80, self.conn._transfer_stats.byte_count)
        self.assertGreater(self.conn._transfer_stats.get_running_time(), 0)

class TestXFRSessionWithSQLite3(TestXfrinConnection):
    '''Tests for XFR sessions using an SQLite3 DB.

    These are provided mainly to confirm the implementation actually works
    in an environment closer to actual operational environments.  So we
    only check a few common cases; other details are tested using mock
    data sources.

    '''
    def setUp(self):
        self.sqlite3db_src = TESTDATA_SRCDIR + '/example.com.sqlite3'
        self.sqlite3db_obj = TESTDATA_OBJDIR + '/example.com.sqlite3.copy'
        self.empty_sqlite3db_obj = TESTDATA_OBJDIR + '/empty.sqlite3'
        self.sqlite3db_cfg = "{ \"database_file\": \"" +\
                             self.sqlite3db_obj + "\"}"
        # replace time.time with a steadily increasing fake one
        self.orig_time_time = time.time
        time.time = get_fake_time_time()
        super().setUp()
        if os.path.exists(self.sqlite3db_obj):
            os.unlink(self.sqlite3db_obj)
        if os.path.exists(self.empty_sqlite3db_obj):
            os.unlink(self.empty_sqlite3db_obj)
        shutil.copyfile(self.sqlite3db_src, self.sqlite3db_obj)
        self.conn._datasrc_client = DataSourceClient("sqlite3",
                                                     self.sqlite3db_cfg)

    def tearDown(self):
        if os.path.exists(self.sqlite3db_obj):
            os.unlink(self.sqlite3db_obj)
        if os.path.exists(self.empty_sqlite3db_obj):
            os.unlink(self.empty_sqlite3db_obj)
        time.time = self.orig_time_time

    def get_zone_serial(self):
        result, finder = self.conn._datasrc_client.find_zone(TEST_ZONE_NAME)
        self.assertEqual(DataSourceClient.SUCCESS, result)
        result, soa, _ = finder.find(TEST_ZONE_NAME, RRType.SOA())
        self.assertEqual(ZoneFinder.SUCCESS, result)
        self.assertEqual(1, soa.get_rdata_count())
        return get_soa_serial(soa.get_rdata()[0])

    def record_exist(self, name, type):
        result, finder = self.conn._datasrc_client.find_zone(TEST_ZONE_NAME)
        self.assertEqual(DataSourceClient.SUCCESS, result)
        result, soa, _ = finder.find(name, type)
        return result == ZoneFinder.SUCCESS

    def test_do_ixfrin_sqlite3(self):
        def create_ixfr_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                    RRType.IXFR())],
                answers=[soa_rrset, begin_soa_rrset, soa_rrset, soa_rrset])
        self.conn.response_generator = create_ixfr_response

        # Confirm xfrin succeeds and SOA is updated
        self.assertEqual(1230, self.get_zone_serial().get_value())
        self.assertEqual(XFRIN_OK, self.conn.do_xfrin(False, RRType.IXFR()))
        self.assertEqual(1234, self.get_zone_serial().get_value())

        # Also confirm the corresponding diffs are stored in the diffs table
        conn = sqlite3.connect(self.sqlite3db_obj)
        cur = conn.cursor()
        cur.execute('SELECT name, rrtype, ttl, rdata FROM diffs ORDER BY id')
        soa_rdata_base = 'master.example.com. admin.example.com. ' + \
            'SERIAL 3600 1800 2419200 7200'
        self.assertEqual(cur.fetchall(),
                         [(TEST_ZONE_NAME_STR, 'SOA', 3600,
                           re.sub('SERIAL', str(1230), soa_rdata_base)),
                          (TEST_ZONE_NAME_STR, 'SOA', 3600,
                           re.sub('SERIAL', str(1234), soa_rdata_base))])
        conn.close()

    def test_do_ixfrin_sqlite3_fail(self):
        '''Similar to the previous test, but xfrin fails due to error.

        Check the DB is not changed.

        '''
        def create_ixfr_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                    RRType.IXFR())],
                answers=[soa_rrset, begin_soa_rrset, soa_rrset,
                         self._create_soa('1235')])
        self.conn.response_generator = create_ixfr_response

        self.assertEqual(1230, self.get_zone_serial().get_value())
        self.assertEqual(XFRIN_FAIL, self.conn.do_xfrin(False, RRType.IXFR()))
        self.assertEqual(1230, self.get_zone_serial().get_value())

    def test_do_ixfrin_nozone_sqlite3(self):
        self._set_test_zone(Name('nosuchzone.example'))
        self.assertEqual(XFRIN_FAIL, self.conn.do_xfrin(False, RRType.IXFR()))
        # This should fail even before starting state transition
        self.assertEqual(None, self.conn.get_xfrstate())

    def axfr_check(self, type):
        '''Common checks for AXFR and AXFR-style IXFR

        '''
        def create_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, type)],
                answers=[soa_rrset, self._create_ns(), soa_rrset])
        self.conn.response_generator = create_response

        # Confirm xfrin succeeds and SOA is updated, A RR is deleted.
        self.assertEqual(1230, self.get_zone_serial().get_value())
        self.assertTrue(self.record_exist(Name('dns01.example.com'),
                                          RRType.A()))
        self.assertEqual(XFRIN_OK, self.conn.do_xfrin(False, type))
        self.assertEqual(1234, self.get_zone_serial().get_value())
        self.assertFalse(self.record_exist(Name('dns01.example.com'),
                                           RRType.A()))

    def test_do_ixfrin_axfr_sqlite3(self):
        '''AXFR-style IXFR.

        '''
        self.axfr_check(RRType.IXFR())

    def test_do_axfrin_sqlite3(self):
        '''AXFR.

        '''
        self.axfr_check(RRType.AXFR())

    def axfr_failure_check(self, type):
        '''Similar to the previous two tests, but xfrin fails due to error.

        Check the DB is not changed.

        '''
        def create_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS, type)],
                answers=[soa_rrset, self._create_ns(), soa_rrset, soa_rrset])
        self.conn.response_generator = create_response

        self.assertEqual(1230, self.get_zone_serial().get_value())
        self.assertTrue(self.record_exist(Name('dns01.example.com'),
                                          RRType.A()))
        self.assertEqual(XFRIN_FAIL, self.conn.do_xfrin(False, type))
        self.assertEqual(1230, self.get_zone_serial().get_value())
        self.assertTrue(self.record_exist(Name('dns01.example.com'),
                                          RRType.A()))

    def test_do_xfrin_axfr_sqlite3_fail(self):
        '''Failure case for AXFR-style IXFR.

        '''
        self.axfr_failure_check(RRType.IXFR())

    def test_do_axfrin_sqlite3_fail(self):
        '''Failure case for AXFR.

        '''
        self.axfr_failure_check(RRType.AXFR())

    def test_do_axfrin_nozone_sqlite3(self):
        '''AXFR test with an empty SQLite3 DB file, thus no target zone there.

        For now, we provide backward compatible behavior: xfrin will create
        the zone (after even setting up the entire schema) in the zone.
        Note: a future version of this test will make it fail.

        '''
        self.conn._db_file = self.empty_sqlite3db_obj
        self.conn._datasrc_client = DataSourceClient(
            "sqlite3",
            "{ \"database_file\": \"" + self.empty_sqlite3db_obj + "\"}")
        def create_response():
            self.conn.reply_data = self.conn.create_response_data(
                questions=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                    RRType.AXFR())],
                answers=[soa_rrset, self._create_ns(), soa_rrset])
        self.conn.response_generator = create_response
        self._set_test_zone(Name('example.com'))
        self.assertEqual(XFRIN_OK, self.conn.do_xfrin(False, RRType.AXFR()))
        self.assertEqual(type(XfrinAXFREnd()),
                         type(self.conn.get_xfrstate()))
        self.assertEqual(1234, self.get_zone_serial().get_value())
        self.assertFalse(self.record_exist(Name('dns01.example.com'),
                                           RRType.A()))

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

class TestXfrinProcess(unittest.TestCase):
    def setUp(self):
        self.unlocked = False
        self.conn_closed = False
        self.do_raise_on_close = False
        self.do_raise_on_connect = False
        self.do_raise_on_publish = False
        self.master = (socket.AF_INET, socket.SOCK_STREAM,
                       (TEST_MASTER_IPV4_ADDRESS, TEST_MASTER_PORT))

    def tearDown(self):
        # whatever happens the lock acquired in xfrin_recorder.increment
        # must always be released.  We checked the condition for all test
        # cases.
        self.assertTrue(self.unlocked)

        # Same for the connection
        self.assertTrue(self.conn_closed)

    def increment(self, zone_name):
        '''Fake method of xfrin_recorder.increment.

        '''
        self.unlocked = False

    def decrement(self, zone_name):
        '''Fake method of xfrin_recorder.decrement.

        '''
        self.unlocked = True

    def publish_xfrin_news(self, zone_name, rrclass, ret):
        '''Fake method of serve.publish_xfrin_news

        '''
        if self.do_raise_on_publish:
            raise XfrinTestException('Emulated exception in publish')

    def connect_to_master(self, conn):
        self.sock_fd = conn.fileno()
        if self.do_raise_on_connect:
            raise XfrinTestException('Emulated exception in connect')
        return True

    def conn_close(self, conn):
        self.conn_closed = True
        XfrinConnection.close(conn)
        if self.do_raise_on_close:
            raise XfrinTestException('Emulated exception in connect')

    def create_xfrinconn(self, sock_map, zone_name, rrclass, datasrc_client,
                         shutdown_event, master_addrinfo, tsig_key):
        conn = MockXfrinConnection(sock_map, zone_name, rrclass,
                                   datasrc_client, shutdown_event,
                                   master_addrinfo, tsig_key)

        # An awkward check that would specifically identify an old bug
        # where initialziation of XfrinConnection._tsig_ctx_creator caused
        # self reference and subsequently led to reference leak.
        orig_ref = sys.getrefcount(conn)
        conn._tsig_ctx_creator = None
        self.assertEqual(orig_ref, sys.getrefcount(conn))

        # Replace some methods for connect with our internal ones for the
        # convenience of tests
        conn.connect_to_master = lambda : self.connect_to_master(conn)
        conn.do_xfrin = lambda x, y : XFRIN_OK
        conn.close = lambda : self.conn_close(conn)

        return conn

    def test_process_xfrin_normal(self):
        # Normal, successful case.  We only check that things are cleaned up
        # at the tearDown time.
        process_xfrin(self, self, TEST_ZONE_NAME, TEST_RRCLASS, None, None,
                      self.master,  False, None, RRType.AXFR(),
                      self.create_xfrinconn)

    def test_process_xfrin_exception_on_connect(self):
        # connect_to_master() will raise an exception.  Things must still be
        # cleaned up.
        self.do_raise_on_connect = True
        process_xfrin(self, self, TEST_ZONE_NAME, TEST_RRCLASS, None, None,
                      self.master,  False, None, RRType.AXFR(),
                      self.create_xfrinconn)

    def test_process_xfrin_exception_on_close(self):
        # connect() will result in exception, and even the cleanup close()
        # will fail with an exception.  This should be quite likely a bug,
        # but we deal with that case.
        self.do_raise_on_connect = True
        self.do_raise_on_close = True
        process_xfrin(self, self, TEST_ZONE_NAME, TEST_RRCLASS, None, None,
                      self.master,  False, None, RRType.AXFR(),
                      self.create_xfrinconn)

    def test_process_xfrin_exception_on_publish(self):
        # xfr succeeds but notifying the zonemgr fails with exception.
        # everything must still be cleaned up.
        self.do_raise_on_publish = True
        process_xfrin(self, self, TEST_ZONE_NAME, TEST_RRCLASS, None, None,
                      self.master,  False, None, RRType.AXFR(),
                      self.create_xfrinconn)

class TestXfrin(unittest.TestCase):
    def setUp(self):
        # redirect output
        self.stderr_backup = sys.stderr
        sys.stderr = open(os.devnull, 'w')
        self.xfr = MockXfrin()
        self.args = {}
        self.args['zone_name'] = TEST_ZONE_NAME_STR
        self.args['class'] = TEST_RRCLASS_STR
        self.args['port'] = TEST_MASTER_PORT
        self.args['master'] = TEST_MASTER_IPV4_ADDRESS
        self.args['db_file'] = TEST_DB_FILE
        self.args['tsig_key'] = ''

    def tearDown(self):
        self.assertFalse(self.xfr._module_cc.stopped);
        self.xfr.shutdown()
        self.assertTrue(self.xfr._module_cc.stopped);
        sys.stderr.close()
        sys.stderr = self.stderr_backup

    def _do_parse_zone_name_class(self):
        return self.xfr._parse_zone_name_and_class(self.args)

    def _do_parse_master_port(self):
        name, rrclass = self._do_parse_zone_name_class()
        return self.xfr._parse_master_and_port(self.args, name, rrclass)

    def test_parse_cmd_params(self):
        name, rrclass = self._do_parse_zone_name_class()
        master_addrinfo = self._do_parse_master_port()
        db_file = self.args.get('db_file')
        self.assertEqual(master_addrinfo[2][1], int(TEST_MASTER_PORT))
        self.assertEqual(name, TEST_ZONE_NAME)
        self.assertEqual(rrclass, TEST_RRCLASS)
        self.assertEqual(master_addrinfo[2][0], TEST_MASTER_IPV4_ADDRESS)
        self.assertEqual(db_file, TEST_DB_FILE)

    def test_parse_cmd_params_default_port(self):
        del self.args['port']
        master_addrinfo = self._do_parse_master_port()
        self.assertEqual(master_addrinfo[2][1], 53)

    def test_parse_cmd_params_ip6master(self):
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS
        master_addrinfo = self._do_parse_master_port()
        self.assertEqual(master_addrinfo[2][0], TEST_MASTER_IPV6_ADDRESS)

    def test_parse_cmd_params_chclass(self):
        self.args['zone_class'] = 'CH'
        self.assertEqual(self._do_parse_zone_name_class()[1], RRClass.CH())

    def test_parse_cmd_params_bogusclass(self):
        self.args['zone_class'] = 'XXX'
        self.assertRaises(XfrinZoneInfoException, self._do_parse_zone_name_class)

    def test_parse_cmd_params_nozone(self):
        # zone name is mandatory.
        del self.args['zone_name']
        self.assertRaises(XfrinException, self._do_parse_zone_name_class)

    def test_parse_cmd_params_nomaster(self):
        # master address is mandatory.
        del self.args['master']
        self.assertRaises(XfrinException, self._do_parse_master_port)

    def test_parse_cmd_params_bad_ip4(self):
        self.args['master'] = '3.3.3.3.3'
        self.assertRaises(XfrinException, self._do_parse_master_port)

    def test_parse_cmd_params_bad_ip6(self):
        self.args['master'] = '1::1::1'
        self.assertRaises(XfrinException, self._do_parse_master_port)

    def test_parse_cmd_params_bad_port(self):
        self.args['port'] = '-1'
        self.assertRaises(XfrinException, self._do_parse_master_port)

        self.args['port'] = '65536'
        self.assertRaises(XfrinException, self._do_parse_master_port)

        self.args['port'] = 'http'
        self.assertRaises(XfrinException, self._do_parse_master_port)

    def test_command_handler_shutdown(self):
        self.assertEqual(self.xfr.command_handler("shutdown",
                                                  None)['result'][0], 0)
        # shutdown command doesn't expect an argument, but accepts it if any.
        self.assertEqual(self.xfr.command_handler("shutdown",
                                                  "unused")['result'][0], 0)

    def test_command_handler_retransfer(self):
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 0)
        self.assertEqual(self.args['master'], self.xfr.xfrin_started_master_addr)
        self.assertEqual(int(self.args['port']), self.xfr.xfrin_started_master_port)
        # By default we use AXFR (for now)
        self.assertEqual(RRType.AXFR(), self.xfr.xfrin_started_request_type)

    def test_command_handler_retransfer_short_command1(self):
        # try it when only specifying the zone name (of unknown zone)
        # this should fail because master address is not specified.
        short_args = {}
        short_args['zone_name'] = TEST_ZONE_NAME_STR
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  short_args)['result'][0], 1)

    def test_command_handler_retransfer_short_command2(self):
        # try it when only specifying the zone name (of known zone)
        short_args = {}
        short_args['zone_name'] = TEST_ZONE_NAME_STR

        zones = { 'zones': [
                  { 'name': TEST_ZONE_NAME_STR,
                    'master_addr': TEST_MASTER_IPV4_ADDRESS,
                    'master_port': TEST_MASTER_PORT
                  }
                ]}
        self.xfr.config_handler(zones)
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  short_args)['result'][0], 0)
        self.assertEqual(TEST_MASTER_IPV4_ADDRESS,
                         self.xfr.xfrin_started_master_addr)
        self.assertEqual(int(TEST_MASTER_PORT),
                         self.xfr.xfrin_started_master_port)

    def test_command_handler_retransfer_short_command3(self):
        # try it when only specifying the zone name (of known zone)
        short_args = {}
        # test it without the trailing root dot
        short_args['zone_name'] = TEST_ZONE_NAME_STR[:-1]

        zones = { 'zones': [
                  { 'name': TEST_ZONE_NAME_STR,
                    'master_addr': TEST_MASTER_IPV4_ADDRESS,
                    'master_port': TEST_MASTER_PORT
                  }
                ]}
        self.xfr.config_handler(zones)
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  short_args)['result'][0], 0)
        self.assertEqual(TEST_MASTER_IPV4_ADDRESS,
                         self.xfr.xfrin_started_master_addr)
        self.assertEqual(int(TEST_MASTER_PORT),
                         self.xfr.xfrin_started_master_port)

    def test_command_handler_retransfer_short_command4(self):
        # try it when only specifying the zone name (of known zone, with
        # different case)
        short_args = {}

        # swap the case of the zone name in our command
        short_args['zone_name'] = TEST_ZONE_NAME_STR.swapcase()

        zones = { 'zones': [
                  { 'name': TEST_ZONE_NAME_STR,
                    'master_addr': TEST_MASTER_IPV4_ADDRESS,
                    'master_port': TEST_MASTER_PORT
                  }
                ]}
        self.xfr.config_handler(zones)
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  short_args)['result'][0], 0)
        self.assertEqual(TEST_MASTER_IPV4_ADDRESS,
                         self.xfr.xfrin_started_master_addr)
        self.assertEqual(int(TEST_MASTER_PORT),
                         self.xfr.xfrin_started_master_port)

    def test_command_handler_retransfer_badcommand(self):
        self.args['master'] = 'invalid'
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)

    def test_command_handler_retransfer_quota(self):
        self.args['master'] = TEST_MASTER_IPV4_ADDRESS

        for i in range(self.xfr._max_transfers_in - 1):
            self.xfr.recorder.increment(Name(str(i) + TEST_ZONE_NAME_STR))
        # there can be one more outstanding transfer.
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 0)
        # make sure the # xfrs would excceed the quota
        self.xfr.recorder.increment(Name(str(self.xfr._max_transfers_in) + TEST_ZONE_NAME_STR))
        # this one should fail
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)

    def test_command_handler_retransfer_inprogress(self):
        self.xfr.recorder.increment(TEST_ZONE_NAME)
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)

    def test_command_handler_retransfer_nomodule(self):
        dns_module = sys.modules['pydnspp'] # this must exist
        del sys.modules['pydnspp']
        self.assertEqual(self.xfr.command_handler("retransfer",
                                                  self.args)['result'][0], 1)
        # sys.modules is global, so we must recover it
        sys.modules['pydnspp'] = dns_module

    def test_command_handler_refresh(self):
        # at this level, refresh is no different than retransfer.
        # just confirm the successful case with a different family of address.
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS
        self.assertEqual(self.xfr.command_handler("refresh",
                                                  self.args)['result'][0], 0)
        self.assertEqual(TEST_MASTER_IPV6_ADDRESS,
                         self.xfr.xfrin_started_master_addr)
        self.assertEqual(int(TEST_MASTER_PORT),
                         self.xfr.xfrin_started_master_port)
        # By default we use AXFR (for now)
        self.assertEqual(RRType.AXFR(), self.xfr.xfrin_started_request_type)

    def test_command_handler_notify(self):
        # at this level, refresh is no different than retransfer.
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS
        # ...but the zone is unknown so this would return an error
        self.assertEqual(self.xfr.command_handler("notify",
                                                  self.args)['result'][0], 1)

    def test_command_handler_notify_known_zone_bad_addr(self):
        # try it with a known zone
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS

        # but use a different address in the actual command
        zones = { 'zones': [
                  { 'name': TEST_ZONE_NAME_STR,
                    'master_addr': TEST_MASTER_IPV4_ADDRESS,
                    'master_port': TEST_MASTER_PORT
                  }
                ]}
        self.xfr.config_handler(zones)
        # the command should now fail
        self.assertEqual(self.xfr.command_handler("notify",
                                                  self.args)['result'][0], 1)

        # also try a different port in the actual command
        zones = { 'zones': [
                  { 'name': TEST_ZONE_NAME_STR,
                    'master_addr': TEST_MASTER_IPV6_ADDRESS,
                    'master_port': str(int(TEST_MASTER_PORT) + 1)
                  }
                ]}
        self.xfr.config_handler(zones)
        # the command should now fail
        self.assertEqual(self.xfr.command_handler("notify",
                                                  self.args)['result'][0], 1)


    def test_command_handler_notify_known_zone(self):
        # try it with a known zone
        self.args['master'] = TEST_MASTER_IPV6_ADDRESS

        # with a zone configuration that has a matching master address.
        zones = { 'zones': [
                  { 'name': TEST_ZONE_NAME_STR,
                    'master_addr': TEST_MASTER_IPV6_ADDRESS,
                    'master_port': TEST_MASTER_PORT
                  }
                ]}
        self.xfr.config_handler(zones)
        self.assertEqual(self.xfr.command_handler("notify",
                                                  self.args)['result'][0], 0)

    def test_command_handler_unknown(self):
        self.assertEqual(self.xfr.command_handler("xxx", None)['result'][0], 1)

    def test_command_handler_transfers_in(self):
        self.assertEqual(self.xfr.config_handler({})['result'][0], 0)
        self.assertEqual(self.xfr.config_handler({'transfers_in': 3})['result'][0], 0)
        self.assertEqual(self.xfr._max_transfers_in, 3)

    def _check_zones_config(self, config_given):
        if 'transfers_in' in config_given:
            self.assertEqual(config_given['transfers_in'],
                             self.xfr._max_transfers_in)
        for zone_config in config_given['zones']:
            zone_name = zone_config['name']
            zone_info = self.xfr._get_zone_info(Name(zone_name), RRClass.IN())
            self.assertEqual(str(zone_info.master_addr), zone_config['master_addr'])
            self.assertEqual(zone_info.master_port, zone_config['master_port'])
            if 'tsig_key' in zone_config:
                self.assertEqual(zone_info.tsig_key.to_text(), TSIGKey(zone_config['tsig_key']).to_text())
            else:
                self.assertIsNone(zone_info.tsig_key)
            if 'use_ixfr' in zone_config and\
               zone_config.get('use_ixfr'):
                self.assertTrue(zone_info.use_ixfr)
            else:
                # if not set, should default to False
                self.assertFalse(zone_info.use_ixfr)

    def test_config_handler_zones(self):
        # This test passes a number of good and bad configs, and checks whether
        # the values are reflected in the structure that will dictate the
        # actual behaviour. It also checks if bad values are correctly
        # handled
        config1 = { 'transfers_in': 3,
                   'zones': [
                   { 'name': 'test.example.',
                    'master_addr': '192.0.2.1',
                    'master_port': 53,
                    'use_ixfr': False
                   }
                 ]}
        self.assertEqual(self.xfr.config_handler(config1)['result'][0], 0)
        self._check_zones_config(config1)

        config2 = { 'transfers_in': 4,
                   'zones': [
                   { 'name': 'test.example.',
                    'master_addr': '192.0.2.2',
                    'master_port': 53,
                    'tsig_key': "example.com:SFuWd/q99SzF8Yzd1QbB9g==",
                    'use_ixfr': True
                   }
                 ]}
        self.assertEqual(self.xfr.config_handler(config2)['result'][0], 0)
        self._check_zones_config(config2)

        # test that configuring the zone multiple times fails
        zones = { 'transfers_in': 5,
                  'zones': [
                  { 'name': 'test.example.',
                    'master_addr': '192.0.2.1',
                    'master_port': 53
                  },
                  { 'name': 'test.example.',
                    'master_addr': '192.0.2.2',
                    'master_port': 53
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'name': 'test.example.',
                    'master_addr': '192.0.2.3',
                    'master_port': 53,
                    'class': 'BADCLASS'
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'master_addr': '192.0.2.4',
                    'master_port': 53
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'name': 'bad..zone.',
                    'master_addr': '192.0.2.5',
                    'master_port': 53
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'name': '',
                    'master_addr': '192.0.2.6',
                    'master_port': 53
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'name': 'test.example',
                    'master_addr': 'badaddress',
                    'master_port': 53
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'name': 'test.example',
                    'master_addr': '192.0.2.7',
                    'master_port': 'bad_port'
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        zones = { 'zones': [
                  { 'name': 'test.example',
                    'master_addr': '192.0.2.7',
                    'master_port': 53,
                    # using a bad TSIG key spec
                    'tsig_key': "bad..example.com:SFuWd/q99SzF8Yzd1QbB9g=="
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

        # let's also add a zone that is correct too, and make sure
        # that the new config is not partially taken
        zones = { 'zones': [
                  { 'name': 'test.example.',
                    'master_addr': '192.0.2.8',
                    'master_port': 53
                  },
                  { 'name': 'test2.example.',
                    'master_addr': '192.0.2.9',
                    'master_port': 53,
                    'tsig_key': 'badkey'
                  }
                ]}
        self.assertEqual(self.xfr.config_handler(zones)['result'][0], 1)
        # since this has failed, we should still have the previous config
        self._check_zones_config(config2)

    def test_config_handler_zones_default(self):
        # Checking it some default config values apply.  Using a separate
        # test case for a fresh xfr object.
        config = { 'zones': [
                   { 'name': 'test.example.',
                    'master_addr': '192.0.2.1',
                    'master_port': 53,
                   }
                 ]}
        self.assertEqual(self.xfr.config_handler(config)['result'][0], 0)
        self._check_zones_config(config)

    def common_ixfr_setup(self, xfr_mode, use_ixfr):
        # This helper method explicitly sets up a zone configuration with
        # use_ixfr, and invokes either retransfer or refresh.
        # Shared by some of the following test cases.
        config = {'zones': [
                {'name': 'example.com.',
                 'master_addr': '192.0.2.1',
                 'use_ixfr': use_ixfr}]}
        self.assertEqual(self.xfr.config_handler(config)['result'][0], 0)
        self.assertEqual(self.xfr.command_handler(xfr_mode,
                                                  self.args)['result'][0], 0)

    def test_command_handler_retransfer_ixfr_enabled(self):
        # If IXFR is explicitly enabled in config, IXFR will be used
        self.common_ixfr_setup('retransfer', True)
        self.assertEqual(RRType.IXFR(), self.xfr.xfrin_started_request_type)

    def test_command_handler_refresh_ixfr_enabled(self):
        # Same for refresh
        self.common_ixfr_setup('refresh', True)
        self.assertEqual(RRType.IXFR(), self.xfr.xfrin_started_request_type)

    def test_command_handler_retransfer_ixfr_disabled(self):
        # Similar to the previous case, but explicitly disabled.  AXFR should
        # be used.
        self.common_ixfr_setup('retransfer', False)
        self.assertEqual(RRType.AXFR(), self.xfr.xfrin_started_request_type)

    def test_command_handler_refresh_ixfr_disabled(self):
        # Same for refresh
        self.common_ixfr_setup('refresh', False)
        self.assertEqual(RRType.AXFR(), self.xfr.xfrin_started_request_type)

class TestXfrinMemoryZones(unittest.TestCase):
    def setUp(self):
        self.xfr = MockXfrin()
        # Configuration snippet containing 2 memory datasources,
        # one for IN and one for CH. Both contain a zone 'example.com'
        # the IN ds also contains a zone example2.com, and a zone example3.com,
        # which is of file type 'text' (and hence, should be ignored)
        self.config = { 'datasources': [
                          { 'type': 'memory',
                            'class': 'IN',
                            'zones': [
                              { 'origin': 'example.com',
                                'filetype': 'sqlite3' },
                              { 'origin': 'EXAMPLE2.com.',
                                'filetype': 'sqlite3' },
                              { 'origin': 'example3.com',
                                'filetype': 'text' }
                            ]
                          },
                          { 'type': 'memory',
                            'class': 'ch',
                            'zones': [
                              { 'origin': 'example.com',
                                'filetype': 'sqlite3' }
                            ]
                          }
                      ] }

    def test_updates(self):
        self.assertFalse(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example.com", "CH"))

        # add them all
        self.xfr._set_memory_zones(self.config, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example.com", "CH"))

        # Remove the CH data source from the self.config snippet, and update
        del self.config['datasources'][1]
        self.xfr._set_memory_zones(self.config, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example.com", "CH"))

        # Remove example2.com from the datasource, and update
        del self.config['datasources'][0]['zones'][1]
        self.xfr._set_memory_zones(self.config, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example.com", "CH"))

        # If 'datasources' is not in the self.config update list (i.e. its
        # self.config has not changed), no difference should be found
        self.xfr._set_memory_zones({}, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example.com", "CH"))

        # If datasources list becomes empty, everything should be removed
        self.config['datasources'][0]['zones'] = []
        self.xfr._set_memory_zones(self.config, None)
        self.assertFalse(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example.com", "CH"))

    def test_normalization(self):
        self.xfr._set_memory_zones(self.config, None)
        # make sure it is case insensitive, root-dot-insensitive,
        # and supports CLASSXXX notation
        self.assertTrue(self.xfr._is_memory_zone("EXAMPLE.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example.com", "in"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com.", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example.com", "CLASS3"))

    def test_bad_name(self):
        # First set it to some config
        self.xfr._set_memory_zones(self.config, None)

        # Error checking; bad owner name should result in no changes
        self.config['datasources'][1]['zones'][0]['origin'] = ".."
        self.xfr._set_memory_zones(self.config, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example.com", "CH"))

    def test_bad_class(self):
        # First set it to some config
        self.xfr._set_memory_zones(self.config, None)

        # Error checking; bad owner name should result in no changes
        self.config['datasources'][1]['class'] = "Foo"
        self.xfr._set_memory_zones(self.config, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example.com", "CH"))

    def test_no_filetype(self):
        # omitting the filetype should leave that zone out, but not
        # the rest
        del self.config['datasources'][1]['zones'][0]['filetype']
        self.xfr._set_memory_zones(self.config, None)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example.com", "CH"))

    def test_class_filetype(self):
        # omitting the class should have it default to what is in the
        # specfile for Auth.
        AuthConfigData = isc.config.config_data.ConfigData(
            isc.config.module_spec_from_file(xfrin.AUTH_SPECFILE_LOCATION))
        del self.config['datasources'][0]['class']
        self.xfr._set_memory_zones(self.config, AuthConfigData)
        self.assertTrue(self.xfr._is_memory_zone("example.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example2.com", "IN"))
        self.assertFalse(self.xfr._is_memory_zone("example3.com", "IN"))
        self.assertTrue(self.xfr._is_memory_zone("example.com", "CH"))

def raise_interrupt():
    raise KeyboardInterrupt()

def raise_ccerror():
    raise isc.cc.session.SessionError('test error')

def raise_exception():
    raise Exception('test exception')

class TestMain(unittest.TestCase):
    def setUp(self):
        MockXfrin.check_command_hook = None

    def tearDown(self):
        MockXfrin.check_command_hook = None

    def test_startup(self):
        main(MockXfrin, False)

    def test_startup_interrupt(self):
        MockXfrin.check_command_hook = raise_interrupt
        main(MockXfrin, False)

    def test_startup_ccerror(self):
        MockXfrin.check_command_hook = raise_ccerror
        main(MockXfrin, False)

    def test_startup_generalerror(self):
        MockXfrin.check_command_hook = raise_exception
        main(MockXfrin, False)

class TestXfrinProcessMockCC:
    def __init__(self):
        self.config = []

class TestXfrinProcessMockCCSession:
    def __init__(self):
        self.send_called = False
        self.send_called_correctly = False
        self.recv_called = False
        self.recv_called_correctly = False

    def group_sendmsg(self, msg, module):
        self.send_called = True
        if module == 'Auth' and msg['command'][0] == 'loadzone':
            self.send_called_correctly = True
            seq = "random-e068c2de26d760f20cf10afc4b87ef0f"
        else:
            seq = None

        return seq

    def group_recvmsg(self, message, seq):
        self.recv_called = True
        if message == False and seq == "random-e068c2de26d760f20cf10afc4b87ef0f":
            self.recv_called_correctly = True
        # return values are ignored
        return (None, None)

class TestXfrinProcess(unittest.TestCase):
    """
    Some tests for the xfrin_process function. This replaces the
    XfrinConnection class with itself, so we can emulate whatever behavior we
    might want.

    Currently only tests for retry if IXFR fails.
    """
    def setUp(self):
        """
        Backs up the original class implementation so it can be restored
        and places our own version in place of the constructor.

        Also sets up several internal variables to watch what happens.
        """
        self._module_cc = TestXfrinProcessMockCC()
        self._send_cc_session = TestXfrinProcessMockCCSession()
        # This will hold a "log" of what transfers were attempted.
        self.__transfers = []
        # This will "log" if failures or successes happened.
        self.__published = []
        # How many connections were created.
        self.__created_connections = 0

    def __get_connection(self, *args):
        """
        Provides a "connection". To mock the connection and see what it is
        asked to do, we pretend to be the connection.
        """
        self.__created_connections += 1
        return self

    def connect_to_master(self):
        """
        Part of pretending to be the connection. It pretends it connected
        correctly every time.
        """
        return True

    def do_xfrin(self, check_soa, request_type):
        """
        Part of pretending to be the connection. It looks what answer should
        be answered now and logs what request happened.
        """
        self.__transfers.append(request_type)
        ret = self.__rets[0]
        self.__rets = self.__rets[1:]
        return ret

    def zone_str(self):
        """
        Part of pretending to be the connection. It provides the logging name
        of zone.
        """
        return "example.org/IN"

    def publish_xfrin_news(self, zone_name, rrclass, ret):
        """
        Part of pretending to be the server as well. This just logs the
        success/failure of the previous operation.
        """
        if ret == XFRIN_OK:
            xfrin._do_auth_loadzone(self, zone_name, rrclass)

        self.__published.append(ret)

    def close(self):
        """
        Part of pretending to be the connection.
        """
        pass

    def init_socket(self):
        """
        Part of pretending to be the connection.
        """
        pass

    def __do_test(self, rets, transfers, request_type):
        """
        Do the actual test. The request type, prepared sucesses/failures
        and expected sequence of transfers is passed to specify what test
        should happen.
        """
        self.__rets = rets
        published = rets[-1]
        xfrin.process_xfrin(self, XfrinRecorder(), Name("example.org."),
                            RRClass.IN(), None, None, None, True, None,
                            request_type, self.__get_connection)
        self.assertEqual([], self.__rets)
        self.assertEqual(transfers, self.__transfers)
        # Create a connection for each attempt
        self.assertEqual(len(transfers), self.__created_connections)
        self.assertEqual([published], self.__published)

    def test_ixfr_ok(self):
        """
        Everything OK the first time, over IXFR.
        """
        self.__do_test([XFRIN_OK], [RRType.IXFR()], RRType.IXFR())
        # Check there was loadzone command
        self.assertTrue(self._send_cc_session.send_called)
        self.assertTrue(self._send_cc_session.send_called_correctly)
        self.assertTrue(self._send_cc_session.recv_called)
        self.assertTrue(self._send_cc_session.recv_called_correctly)

    def test_axfr_ok(self):
        """
        Everything OK the first time, over AXFR.
        """
        self.__do_test([XFRIN_OK], [RRType.AXFR()], RRType.AXFR())

    def test_axfr_fail(self):
        """
        The transfer failed over AXFR. Should not be retried (we don't expect
        to fail on AXFR, but succeed on IXFR and we didn't use IXFR in the first
        place for some reason.
        """
        self.__do_test([XFRIN_FAIL], [RRType.AXFR()], RRType.AXFR())

    def test_ixfr_fallback(self):
        """
        The transfer fails over IXFR, but suceeds over AXFR. It should fall back
        to it and say everything is OK.
        """
        self.__do_test([XFRIN_FAIL, XFRIN_OK], [RRType.IXFR(), RRType.AXFR()],
                       RRType.IXFR())

    def test_ixfr_fail(self):
        """
        The transfer fails both over IXFR and AXFR. It should report failure
        (only once) and should try both before giving up.
        """
        self.__do_test([XFRIN_FAIL, XFRIN_FAIL],
                       [RRType.IXFR(), RRType.AXFR()], RRType.IXFR())

    def test_send_loadzone(self):
        """
        Check the loadzone command is sent after successful transfer.
        """
        self.__do_test([XFRIN_OK], [RRType.IXFR()], RRType.IXFR())
        self.assertTrue(self._send_cc_session.send_called)
        self.assertTrue(self._send_cc_session.send_called_correctly)
        self.assertTrue(self._send_cc_session.recv_called)
        self.assertTrue(self._send_cc_session.recv_called_correctly)

class TestFormatting(unittest.TestCase):
    # If the formatting functions are moved to a more general library
    # (ticket #1379), these tests should be moved with them.
    def test_format_zone_str(self):
        self.assertEqual("example.com/IN",
                         format_zone_str(isc.dns.Name("example.com"),
                         isc.dns.RRClass("IN")))
        self.assertEqual("example.com/CH",
                         format_zone_str(isc.dns.Name("example.com"),
                         isc.dns.RRClass("CH")))
        self.assertEqual("example.org/IN",
                         format_zone_str(isc.dns.Name("example.org"),
                         isc.dns.RRClass("IN")))

    def test_format_addrinfo(self):
        # This test may need to be updated if the input type is changed,
        # right now it is a nested tuple:
        # (family, sockettype, (address, port))
        # of which sockettype is ignored
        self.assertEqual("192.0.2.1:53",
                         format_addrinfo((socket.AF_INET, socket.SOCK_STREAM,
                                          ("192.0.2.1", 53))))
        self.assertEqual("192.0.2.2:53",
                         format_addrinfo((socket.AF_INET, socket.SOCK_STREAM,
                                          ("192.0.2.2", 53))))
        self.assertEqual("192.0.2.1:54",
                         format_addrinfo((socket.AF_INET, socket.SOCK_STREAM,
                                          ("192.0.2.1", 54))))
        self.assertEqual("[2001:db8::1]:53",
                         format_addrinfo((socket.AF_INET6, socket.SOCK_STREAM,
                                          ("2001:db8::1", 53))))
        self.assertEqual("[2001:db8::2]:53",
                         format_addrinfo((socket.AF_INET6, socket.SOCK_STREAM,
                                          ("2001:db8::2", 53))))
        self.assertEqual("[2001:db8::1]:54",
                         format_addrinfo((socket.AF_INET6, socket.SOCK_STREAM,
                                          ("2001:db8::1", 54))))
        self.assertEqual("/some/file",
                         format_addrinfo((socket.AF_UNIX, socket.SOCK_STREAM,
                                          "/some/file")))
        # second element of passed tuple should be ignored
        self.assertEqual("192.0.2.1:53",
                         format_addrinfo((socket.AF_INET, None,
                                          ("192.0.2.1", 53))))
        self.assertEqual("192.0.2.1:53",
                         format_addrinfo((socket.AF_INET, "Just some string",
                                          ("192.0.2.1", 53))))
        self.assertRaises(TypeError, format_addrinfo, 1)
        self.assertRaises(TypeError, format_addrinfo,
                                     (socket.AF_INET, "asdf"))
        self.assertRaises(TypeError, format_addrinfo,
                                     (socket.AF_INET, "asdf", ()))

class TestXfrinTransferStats(unittest.TestCase):
    def setUp(self):
        # replace time.time with a steadily increasing fake one
        self.orig_time_time = time.time
        time.time = get_fake_time_time()
        self.stats = XfrinTransferStats()

    def tearDown(self):
        time.time = self.orig_time_time

    def zero_check(self):
        # Checks whether all counters are zero
        self.assertEqual(0, self.stats.message_count)
        self.assertEqual(0, self.stats.axfr_rr_count)
        self.assertEqual(0, self.stats.byte_count)
        self.assertEqual(0, self.stats.ixfr_changeset_count)
        self.assertEqual(0, self.stats.ixfr_deletion_count)
        self.assertEqual(0, self.stats.ixfr_addition_count)

    def test_init(self):
        self.zero_check()
        self.assertIsNone(self.stats._end_time)

    def test_get_running_time(self):
        self.assertIsNone(self.stats._end_time)
        runtime = self.stats.get_running_time()
        self.assertIsNotNone(self.stats._end_time)
        self.assertGreater(runtime, 0)
        # make sure a second get does not change anything
        runtime2 = self.stats.get_running_time()
        self.assertEqual(runtime, runtime2)
        # And that no counters have been modified
        self.zero_check()

    def test_bytes_per_second(self):
        zbps = self.stats.get_bytes_per_second()
        self.assertEqual(0, zbps)

        self.stats._start_time = 1
        self.stats._end_time = 2
        self.stats.byte_count += 4
        zbps = self.stats.get_bytes_per_second()
        self.assertEqual(4, zbps)

        self.stats._start_time = float(1)
        self.stats._end_time = float(11)
        self.assertEqual(10, self.stats.get_running_time())
        self.stats.byte_count = 1234
        zbps = self.stats.get_bytes_per_second()
        self.assertEqual(123.4, zbps)

        # if for some reason the runtime is 0, depending
        # on whether bytes have actually been seen, bps is either
        # 0 or 'infinite'
        self.stats._end_time = self.stats._start_time
        zbps = self.stats.get_bytes_per_second()
        self.assertEqual(float("inf"), zbps)

        self.stats.byte_count = 0
        zbps = self.stats.get_bytes_per_second()
        self.assertEqual(0, zbps)

if __name__== "__main__":
    try:
        isc.log.resetUnitTestRootLogger()
        unittest.main()
    except KeyboardInterrupt as e:
        print(e)
