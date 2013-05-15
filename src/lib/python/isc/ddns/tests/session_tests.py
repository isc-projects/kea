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

import os
import shutil
import isc.log
import unittest
from isc.dns import *
from isc.datasrc import DataSourceClient, ZoneFinder
from isc.ddns.session import *
from isc.ddns.zone_config import *

# Some common test parameters
TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "rwtest.sqlite3.copied"
WRITE_ZONE_DB_CONFIG = "{ \"database_file\": \"" + WRITE_ZONE_DB_FILE + "\"}"

TEST_ZONE_NAME = Name('example.org')
UPDATE_RRTYPE = RRType.SOA
TEST_RRCLASS = RRClass.IN
TEST_ZONE_RECORD = Question(TEST_ZONE_NAME, TEST_RRCLASS, UPDATE_RRTYPE)
TEST_CLIENT6 = ('2001:db8::1', 53, 0, 0)
TEST_CLIENT4 = ('192.0.2.1', 53)
# TSIG key for tests when needed.  The key name is TEST_ZONE_NAME.
TEST_TSIG_KEY = TSIGKey("example.org:SFuWd/q99SzF8Yzd1QbB9g==")

def create_update_msg(zones=[TEST_ZONE_RECORD], prerequisites=[],
                      updates=[], tsig_key=None):
    msg = Message(Message.RENDER)
    msg.set_qid(5353)           # arbitrary chosen
    msg.set_opcode(Opcode.UPDATE)
    msg.set_rcode(Rcode.NOERROR)
    for z in zones:
        msg.add_question(z)
    for p in prerequisites:
        msg.add_rrset(SECTION_PREREQUISITE, p)
    for u in updates:
        msg.add_rrset(SECTION_UPDATE, u)

    renderer = MessageRenderer()
    if tsig_key is not None:
        msg.to_wire(renderer, TSIGContext(tsig_key))
    else:
        msg.to_wire(renderer)

    # re-read the created data in the parse mode
    msg.clear(Message.PARSE)
    msg.from_wire(renderer.get_data(), Message.PRESERVE_ORDER)

    return msg

def add_rdata(rrset, rdata):
    '''
    Helper function for easily adding Rdata fields to RRsets.
    This function assumes the given rdata is of type string or bytes,
    and corresponds to the given rrset
    '''
    rrset.add_rdata(isc.dns.Rdata(rrset.get_type(),
                                  rrset.get_class(),
                                  rdata))

def create_rrset(name, rrclass, rrtype, ttl, rdatas = []):
    '''
    Helper method to easily create RRsets, auto-converts
    name, rrclass, rrtype,  and ttl (if possibly through their
    respective constructors)
    rdatas is a list of rr data strings, or bytestrings, which
    should match the RRType of the rrset to create
    '''
    if type(name) != Name:
        name = Name(name)
    if type(rrclass) != RRClass:
        rrclass = RRClass(rrclass)
    if type(rrtype) != RRType:
        rrtype = RRType(rrtype)
    if type(ttl) != RRTTL:
        ttl = RRTTL(ttl)
    rrset = isc.dns.RRset(name, rrclass, rrtype, ttl)
    for rdata in rdatas:
        add_rdata(rrset, rdata)
    return rrset

class SessionModuleTests(unittest.TestCase):
    '''Tests for module-level functions in the session.py module'''

    def test_foreach_rr_in_rrset(self):
        rrset = create_rrset("www.example.org", TEST_RRCLASS,
                             RRType.A, 3600, [ "192.0.2.1" ])

        l = []
        for rr in foreach_rr(rrset):
            l.append(str(rr))
        self.assertEqual(["www.example.org. 3600 IN A 192.0.2.1\n"], l)

        add_rdata(rrset, "192.0.2.2")
        add_rdata(rrset, "192.0.2.3")

        # but through the generator, there should be several 1-line entries
        l = []
        for rr in foreach_rr(rrset):
            l.append(str(rr))
        self.assertEqual(["www.example.org. 3600 IN A 192.0.2.1\n",
                          "www.example.org. 3600 IN A 192.0.2.2\n",
                          "www.example.org. 3600 IN A 192.0.2.3\n",
                         ], l)

    def test_convert_rrset_class(self):
        # Converting an RRSET to a different class should work
        # if the rdata types can be converted
        rrset = create_rrset("www.example.org", RRClass.NONE, RRType.A,
                             3600, [ b'\xc0\x00\x02\x01', b'\xc0\x00\x02\x02'])

        rrset2 = convert_rrset_class(rrset, RRClass.IN)
        self.assertEqual("www.example.org. 3600 IN A 192.0.2.1\n" +
                         "www.example.org. 3600 IN A 192.0.2.2\n",
                         str(rrset2))

        rrset3 = convert_rrset_class(rrset2, RRClass.NONE)
        self.assertEqual("www.example.org. 3600 NONE A \\# 4 " +
                         "c0000201\nwww.example.org. 3600 NONE " +
                         "A \\# 4 c0000202\n",
                         str(rrset3))

        # depending on what type of bad data is given, a number
        # of different exceptions could be raised (TODO: i recall
        # there was a ticket about making a better hierarchy for
        # dns/parsing related exceptions)
        self.assertRaises(InvalidRdataLength, convert_rrset_class,
                          rrset, RRClass.CH)
        add_rdata(rrset, b'\xc0\x00')
        self.assertRaises(DNSMessageFORMERR, convert_rrset_class,
                          rrset, RRClass.IN)

    def test_collect_rrsets(self):
        '''
        Tests the 'rrset collector' method, which collects rrsets
        with the same name and type
        '''
        collected = []

        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.1" ]))
        # Same name and class, different type
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.TXT, 0, [ "one" ]))
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.2" ]))
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.TXT, 0, [ "two" ]))
        # Same class and type as an existing one, different name
        collect_rrsets(collected, create_rrset("b.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.3" ]))
        # Same name and type as an existing one, different class
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.CH,
                                               RRType.TXT, 0, [ "one" ]))
        collect_rrsets(collected, create_rrset("b.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.4" ]))
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.CH,
                                               RRType.TXT, 0, [ "two" ]))

        strings = [ rrset.to_text() for rrset in collected ]
        # note + vs , in this list
        expected = ['a.example.org. 0 IN A 192.0.2.1\n' +
                    'a.example.org. 0 IN A 192.0.2.2\n',
                    'a.example.org. 0 IN TXT "one"\n' +
                    'a.example.org. 0 IN TXT "two"\n',
                    'b.example.org. 0 IN A 192.0.2.3\n' +
                    'b.example.org. 0 IN A 192.0.2.4\n',
                    'a.example.org. 0 CH TXT "one"\n' +
                    'a.example.org. 0 CH TXT "two"\n']

        self.assertEqual(expected, strings)

class SessionTestBase(unittest.TestCase):
    '''Base class for all sesion related tests.

    It just initializes common test parameters in its setUp() and defines
    some common utility method(s).

    '''
    def setUp(self):
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)
        self._datasrc_client = DataSourceClient("sqlite3",
                                                WRITE_ZONE_DB_CONFIG)
        self._update_msg = create_update_msg()
        self._acl_map = {(TEST_ZONE_NAME, TEST_RRCLASS):
                             REQUEST_LOADER.load([{"action": "ACCEPT"}])}
        self._session = UpdateSession(self._update_msg, TEST_CLIENT4,
                                      ZoneConfig(set(), TEST_RRCLASS,
                                                 self._datasrc_client,
                                                 self._acl_map))
        self._session._get_update_zone()
        self._session._create_diff()

    def tearDown(self):
        # With the Updater created in _get_update_zone, and tests
        # doing all kinds of crazy stuff, one might get database locked
        # errors if it doesn't clean up explicitly after each test
        self._session = None

    def check_response(self, msg, expected_rcode):
        '''Perform common checks on update resposne message.'''
        self.assertTrue(msg.get_header_flag(Message.HEADERFLAG_QR))
        # note: we convert opcode to text it'd be more helpful on failure.
        self.assertEqual(Opcode.UPDATE.to_text(), msg.get_opcode().to_text())
        self.assertEqual(expected_rcode.to_text(), msg.get_rcode().to_text())
        # All sections should be cleared
        self.assertEqual(0, msg.get_rr_count(SECTION_ZONE))
        self.assertEqual(0, msg.get_rr_count(SECTION_PREREQUISITE))
        self.assertEqual(0, msg.get_rr_count(SECTION_UPDATE))
        self.assertEqual(0, msg.get_rr_count(Message.SECTION_ADDITIONAL))

class TestDDNSSOA(unittest.TestCase):
    '''unittest for the DDNS_SOA'''
    def test_update_soa(self):
        '''unittest for update_soa function'''
        soa_update = DDNS_SOA()
        soa_rr = create_rrset("example.org", TEST_RRCLASS,
                              RRType.SOA, 3600, ["ns1.example.org. " +
                              "admin.example.org. " +
                              "1233 3600 1800 2419200 7200"])
        expected_soa_rr = create_rrset("example.org", TEST_RRCLASS,
                                       RRType.SOA, 3600, ["ns1.example.org. "
                                       + "admin.example.org. " +
                                       "1234 3600 1800 2419200 7200"])
        self.assertEqual(soa_update.update_soa(soa_rr).get_rdata()[0].to_text(),
                         expected_soa_rr.get_rdata()[0].to_text())
        max_serial = 2 ** 32 - 1
        soa_rdata = "%d %s"%(max_serial,"3600 1800 2419200 7200")
        soa_rr = create_rrset("example.org", TEST_RRCLASS, RRType.SOA, 3600,
                              ["ns1.example.org. " + "admin.example.org. " +
                              soa_rdata])
        expected_soa_rr = create_rrset("example.org", TEST_RRCLASS,
                                       RRType.SOA, 3600, ["ns1.example.org. "
                                       + "admin.example.org. " +
                                       "1 3600 1800 2419200 7200"])
        self.assertEqual(soa_update.update_soa(soa_rr).get_rdata()[0].to_text(),
                         expected_soa_rr.get_rdata()[0].to_text())

    def test_soa_update_check(self):
        '''unittest for soa_update_check function'''
        small_soa_rr = create_rrset("example.org", TEST_RRCLASS, RRType.SOA,
                                    3600, ["ns1.example.org. " +
                                    "admin.example.org. " +
                                    "1233 3600 1800 2419200 7200"])
        large_soa_rr = create_rrset("example.org", TEST_RRCLASS, RRType.SOA,
                                    3600, ["ns1.example.org. " +
                                    "admin.example.org. " +
                                    "1234 3600 1800 2419200 7200"])
        soa_update = DDNS_SOA()
        # The case of (i1 < i2 and i2 - i1 < 2^(SERIAL_BITS - 1)) in rfc 1982
        self.assertTrue(soa_update.soa_update_check(small_soa_rr,
                                                    large_soa_rr))
        self.assertFalse(soa_update.soa_update_check(large_soa_rr,
                                                     small_soa_rr))
        small_serial = 1235 + 2 ** 31
        soa_rdata = "%d %s"%(small_serial,"3600 1800 2419200 7200")
        small_soa_rr = create_rrset("example.org", TEST_RRCLASS, RRType.SOA,
                                    3600, ["ns1.example.org. " +
                                           "admin.example.org. " +
                                           soa_rdata])
        large_soa_rr = create_rrset("example.org", TEST_RRCLASS, RRType.SOA,
                                    3600, ["ns1.example.org. " +
                                    "admin.example.org. " +
                                    "1234 3600 1800 2419200 7200"])
        # The case of (i1 > i2 and i1 - i2 > 2^(SERIAL_BITS - 1)) in rfc 1982
        self.assertTrue(soa_update.soa_update_check(small_soa_rr,
                                                    large_soa_rr))
        self.assertFalse(soa_update.soa_update_check(large_soa_rr,
                                                     small_soa_rr))

class SessionTest(SessionTestBase):
    '''Basic session tests'''

    def test_handle(self):
        '''Basic update case'''
        result, zname, zclass = self._session.handle()
        self.assertEqual(UPDATE_SUCCESS, result)
        self.assertEqual(TEST_ZONE_NAME, zname)
        self.assertEqual(TEST_RRCLASS, zclass)

        # Just checking these are different from the success code.
        self.assertNotEqual(UPDATE_ERROR, result)
        self.assertNotEqual(UPDATE_DROP, result)

    def test_broken_request(self):
        # Zone section is empty
        msg = create_update_msg(zones=[])
        session = UpdateSession(msg, TEST_CLIENT6, None)
        result, zname, zclass = session.handle()
        self.assertEqual(UPDATE_ERROR, result)
        self.assertEqual(None, zname)
        self.assertEqual(None, zclass)
        self.check_response(session.get_message(), Rcode.FORMERR)

        # Zone section contains multiple records
        msg = create_update_msg(zones=[TEST_ZONE_RECORD, TEST_ZONE_RECORD])
        session = UpdateSession(msg, TEST_CLIENT4, None)
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.FORMERR)

        # Zone section's type is not SOA
        msg = create_update_msg(zones=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                                RRType.A)])
        session = UpdateSession(msg, TEST_CLIENT4, None)
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.FORMERR)

    def test_update_secondary(self):
        # specified zone is configured as a secondary.  Since this
        # implementation doesn't support update forwarding, the result
        # should be NOTIMP.
        msg = create_update_msg(zones=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                                RRType.SOA)])
        session = UpdateSession(msg, TEST_CLIENT4,
                                ZoneConfig({(TEST_ZONE_NAME, TEST_RRCLASS)},
                                           TEST_RRCLASS, self._datasrc_client))
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.NOTIMP)

    def check_notauth(self, zname, zclass=TEST_RRCLASS):
        '''Common test sequence for the 'notauth' test'''
        msg = create_update_msg(zones=[Question(zname, zclass, RRType.SOA)])
        session = UpdateSession(msg, TEST_CLIENT4,
                                ZoneConfig({(TEST_ZONE_NAME, TEST_RRCLASS)},
                                           TEST_RRCLASS, self._datasrc_client))
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.NOTAUTH)

    def test_update_notauth(self):
        '''Update attempt for non authoritative zones'''
        # zone name doesn't match
        self.check_notauth(Name('example.com'))
        # zone name is a subdomain of the actual authoritative zone
        # (match must be exact)
        self.check_notauth(Name('sub.example.org'))
        # zone class doesn't match
        self.check_notauth(Name('example.org'), RRClass.CH)

    def test_update_datasrc_error(self):
        # if the data source client raises an exception, it should result in
        # a SERVFAIL.
        class BadDataSourceClient:
            def find_zone(self, name):
                raise isc.datasrc.Error('faked exception')
        msg = create_update_msg(zones=[Question(TEST_ZONE_NAME, TEST_RRCLASS,
                                                RRType.SOA)])
        session = UpdateSession(msg, TEST_CLIENT4,
                                ZoneConfig({(TEST_ZONE_NAME, TEST_RRCLASS)},
                                           TEST_RRCLASS,
                                           BadDataSourceClient()))
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.SERVFAIL)

    def test_foreach_rr_in_rrset(self):
        rrset = create_rrset("www.example.org", TEST_RRCLASS,
                             RRType.A, 3600, [ "192.0.2.1" ])

        l = []
        for rr in foreach_rr(rrset):
            l.append(str(rr))
        self.assertEqual(["www.example.org. 3600 IN A 192.0.2.1\n"], l)

        add_rdata(rrset, "192.0.2.2")
        add_rdata(rrset, "192.0.2.3")

        # but through the generator, there should be several 1-line entries
        l = []
        for rr in foreach_rr(rrset):
            l.append(str(rr))
        self.assertEqual(["www.example.org. 3600 IN A 192.0.2.1\n",
                          "www.example.org. 3600 IN A 192.0.2.2\n",
                          "www.example.org. 3600 IN A 192.0.2.3\n",
                         ], l)

    def test_convert_rrset_class(self):
        # Converting an RRSET to a different class should work
        # if the rdata types can be converted
        rrset = create_rrset("www.example.org", RRClass.NONE, RRType.A,
                             3600, [ b'\xc0\x00\x02\x01', b'\xc0\x00\x02\x02'])

        rrset2 = convert_rrset_class(rrset, RRClass.IN)
        self.assertEqual("www.example.org. 3600 IN A 192.0.2.1\n" +
                         "www.example.org. 3600 IN A 192.0.2.2\n",
                         str(rrset2))

        rrset3 = convert_rrset_class(rrset2, RRClass.NONE)
        self.assertEqual("www.example.org. 3600 NONE A \\# 4 " +
                         "c0000201\nwww.example.org. 3600 NONE " +
                         "A \\# 4 c0000202\n",
                         str(rrset3))

        # depending on what type of bad data is given, a number
        # of different exceptions could be raised (TODO: i recall
        # there was a ticket about making a better hierarchy for
        # dns/parsing related exceptions)
        self.assertRaises(InvalidRdataLength, convert_rrset_class,
                          rrset, RRClass.CH)
        add_rdata(rrset, b'\xc0\x00')
        self.assertRaises(DNSMessageFORMERR, convert_rrset_class,
                          rrset, RRClass.IN)

    def test_collect_rrsets(self):
        '''
        Tests the 'rrset collector' method, which collects rrsets
        with the same name and type
        '''
        collected = []

        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.1" ]))
        # Same name and class, different type
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.TXT, 0, [ "one" ]))
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.2" ]))
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.IN,
                                               RRType.TXT, 0, [ "two" ]))
        # Same class and type as an existing one, different name
        collect_rrsets(collected, create_rrset("b.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.3" ]))
        # Same name and type as an existing one, different class
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.CH,
                                               RRType.TXT, 0, [ "one" ]))
        collect_rrsets(collected, create_rrset("b.example.org", RRClass.IN,
                                               RRType.A, 0, [ "192.0.2.4" ]))
        collect_rrsets(collected, create_rrset("a.example.org", RRClass.CH,
                                               RRType.TXT, 0, [ "two" ]))

        strings = [ rrset.to_text() for rrset in collected ]
        # note + vs , in this list
        expected = ['a.example.org. 0 IN A 192.0.2.1\n' +
                    'a.example.org. 0 IN A 192.0.2.2\n',
                    'a.example.org. 0 IN TXT "one"\n' +
                    'a.example.org. 0 IN TXT "two"\n',
                    'b.example.org. 0 IN A 192.0.2.3\n' +
                    'b.example.org. 0 IN A 192.0.2.4\n',
                    'a.example.org. 0 CH TXT "one"\n' +
                    'a.example.org. 0 CH TXT "two"\n']

        self.assertEqual(expected, strings)

    def __prereq_helper(self, method, expected, rrset):
        '''Calls the given method with self._datasrc_client
           and the given rrset, and compares the return value.
           Function does not do much but makes the code look nicer'''
        self.assertEqual(expected, method(rrset))

    def __check_prerequisite_exists_combined(self, method, rrclass, expected):
        '''shared code for the checks for the very similar (but reversed
           in behaviour) methods __prereq_rrset_exists and
           __prereq_rrset_does_not_exist.
           For rrset_exists, rrclass should be ANY, for rrset_does_not_exist,
           it should be NONE.
        '''
        # Basic existence checks
        # www.example.org should have an A, but not an MX
        rrset = create_rrset("www.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, expected, rrset)
        rrset = create_rrset("www.example.org", rrclass, RRType.MX, 0)
        self.__prereq_helper(method, not expected, rrset)

        # example.org should have an MX, but not an A
        rrset = create_rrset("example.org", rrclass, RRType.MX, 0)
        self.__prereq_helper(method, expected, rrset)
        rrset = create_rrset("example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, not expected, rrset)

        # Also check the case where the name does not even exist
        rrset = create_rrset("doesnotexist.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, not expected, rrset)

        # Wildcard expansion should not be applied, but literal matches
        # should work
        rrset = create_rrset("foo.wildcard.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, not expected, rrset)

        rrset = create_rrset("*.wildcard.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, expected, rrset)

        # Likewise, CNAME directly should match, but what it points to should
        # not
        rrset = create_rrset("cname.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, not expected, rrset)

        rrset = create_rrset("cname.example.org", rrclass, RRType.CNAME, 0)
        self.__prereq_helper(method, expected, rrset)

        # And also make sure a delegation (itself) is not treated as existing
        # data
        rrset = create_rrset("foo.sub.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, not expected, rrset)
        # But the delegation data itself should match
        rrset = create_rrset("sub.example.org", rrclass, RRType.NS, 0)
        self.__prereq_helper(method, expected, rrset)
        # As should glue
        rrset = create_rrset("ns.sub.example.org", rrclass, RRType.A, 0)
        self.__prereq_helper(method, expected, rrset)

    def test_check_prerequisite_exists(self):
        method = self._session._UpdateSession__prereq_rrset_exists
        self.__check_prerequisite_exists_combined(method,
                                                  RRClass.ANY,
                                                  True)

    def test_check_prerequisite_does_not_exist(self):
        method = self._session._UpdateSession__prereq_rrset_does_not_exist
        self.__check_prerequisite_exists_combined(method,
                                                  RRClass.NONE,
                                                  False)

    def test_check_prerequisite_exists_value(self):
        method = self._session._UpdateSession__prereq_rrset_exists_value

        rrset = create_rrset("www.example.org", RRClass.IN, RRType.A, 0)
        # empty one should not match
        self.__prereq_helper(method, False, rrset)

        # When the rdata is added, it should match
        add_rdata(rrset, "192.0.2.1")
        self.__prereq_helper(method, True, rrset)

        # But adding more should not
        add_rdata(rrset, "192.0.2.2")
        self.__prereq_helper(method, False, rrset)

        # Also test one with more than one RR
        rrset = create_rrset("example.org", RRClass.IN, RRType.NS, 0)
        self.__prereq_helper(method, False, rrset)
        add_rdata(rrset, "ns1.example.org.")
        self.__prereq_helper(method, False, rrset)
        add_rdata(rrset, "ns2.example.org.")
        self.__prereq_helper(method, False, rrset)
        add_rdata(rrset, "ns3.example.org.")
        self.__prereq_helper(method, True, rrset)
        add_rdata(rrset, "ns4.example.org.")
        self.__prereq_helper(method, False, rrset)

        # Repeat that, but try a different order of Rdata addition
        rrset = create_rrset("example.org", RRClass.IN, RRType.NS, 0)
        self.__prereq_helper(method, False, rrset)
        add_rdata(rrset, "ns3.example.org.")
        self.__prereq_helper(method, False, rrset)
        add_rdata(rrset, "ns2.example.org.")
        self.__prereq_helper(method, False, rrset)
        add_rdata(rrset, "ns1.example.org.")
        self.__prereq_helper(method, True, rrset)
        add_rdata(rrset, "ns4.example.org.")
        self.__prereq_helper(method, False, rrset)

        # and test one where the name does not even exist
        rrset = create_rrset("doesnotexist.example.org", RRClass.IN,
                             RRType.A, 0, [ "192.0.2.1" ])
        self.__prereq_helper(method, False, rrset)

    def __check_prerequisite_name_in_use_combined(self, method, rrclass,
                                                  expected):
        '''shared code for the checks for the very similar (but reversed
           in behaviour) methods __prereq_name_in_use and
           __prereq_name_not_in_use
        '''
        rrset = create_rrset("example.org", rrclass, RRType.ANY, 0)
        self.__prereq_helper(method, expected, rrset)

        rrset = create_rrset("www.example.org", rrclass, RRType.ANY, 0)
        self.__prereq_helper(method, expected, rrset)

        rrset = create_rrset("doesnotexist.example.org", rrclass,
                             RRType.ANY, 0)
        self.__prereq_helper(method, not expected, rrset)

        rrset = create_rrset("belowdelegation.sub.example.org", rrclass,
                             RRType.ANY, 0)
        self.__prereq_helper(method, not expected, rrset)

        rrset = create_rrset("foo.wildcard.example.org", rrclass,
                             RRType.ANY, 0)
        self.__prereq_helper(method, not expected, rrset)

        # empty nonterminal should not match
        rrset = create_rrset("nonterminal.example.org", rrclass,
                             RRType.ANY, 0)
        self.__prereq_helper(method, not expected, rrset)
        rrset = create_rrset("empty.nonterminal.example.org", rrclass,
                             RRType.ANY, 0)
        self.__prereq_helper(method, expected, rrset)

    def test_check_prerequisite_name_in_use(self):
        method = self._session._UpdateSession__prereq_name_in_use
        self.__check_prerequisite_name_in_use_combined(method,
                                                       RRClass.ANY,
                                                       True)

    def test_check_prerequisite_name_not_in_use(self):
        method = self._session._UpdateSession__prereq_name_not_in_use
        self.__check_prerequisite_name_in_use_combined(method,
                                                       RRClass.NONE,
                                                       False)

    def check_prerequisite_result(self, expected, prerequisites):
        '''Helper method for checking the result of a prerequisite check;
           creates an update session, and fills it with the list of rrsets
           from 'prerequisites'. Then checks if __check_prerequisites()
           returns the Rcode specified in 'expected'.'''
        msg = create_update_msg([TEST_ZONE_RECORD], prerequisites)
        zconfig = ZoneConfig(set(), TEST_RRCLASS, self._datasrc_client,
                             self._acl_map)
        session = UpdateSession(msg, TEST_CLIENT4, zconfig)
        session._get_update_zone()
        session._create_diff()
        # compare the to_text output of the rcodes (nicer error messages)
        # This call itself should also be done by handle(),
        # but just for better failures, it is first called on its own
        self.assertEqual(expected.to_text(),
            session._UpdateSession__check_prerequisites().to_text())
        # Now see if handle finds the same result
        (result, _, _) = session.handle()
        self.assertEqual(expected.to_text(),
                         session._UpdateSession__message.get_rcode().to_text())
        # And that the result looks right
        if expected == Rcode.NOERROR:
            self.assertEqual(UPDATE_SUCCESS, result)
        else:
            self.assertEqual(UPDATE_ERROR, result)

    def check_prescan_result(self, expected, updates, expected_soa = None):
        '''Helper method for checking the result of a prerequisite check;
           creates an update session, and fills it with the list of rrsets
           from 'updates'. Then checks if __do_prescan()
           returns the Rcode specified in 'expected'.'''
        msg = create_update_msg([TEST_ZONE_RECORD], [], updates)
        zconfig = ZoneConfig(set(), TEST_RRCLASS, self._datasrc_client,
                             self._acl_map)
        session = UpdateSession(msg, TEST_CLIENT4, zconfig)
        session._get_update_zone()
        session._create_diff()
        # compare the to_text output of the rcodes (nicer error messages)
        # This call itself should also be done by handle(),
        # but just for better failures, it is first called on its own
        self.assertEqual(expected.to_text(),
            session._UpdateSession__do_prescan().to_text())
        # If there is an expected soa, check it
        self.assertEqual(str(expected_soa),
                         str(session._UpdateSession__added_soa))

    def check_full_handle_result(self, expected, updates, prerequisites=[]):
        '''Helper method for checking the result of a full handle;
           creates an update session, and fills it with the list of rrsets
           from 'updates'. Then checks if __handle()
           results in a response with rcode 'expected'.'''
        msg = create_update_msg([TEST_ZONE_RECORD], prerequisites, updates)
        zconfig = ZoneConfig(set(), TEST_RRCLASS, self._datasrc_client,
                             self._acl_map)
        session = UpdateSession(msg, TEST_CLIENT4, zconfig)

        # Now see if handle finds the same result
        (result, _, _) = session.handle()
        self.assertEqual(expected.to_text(),
                         session._UpdateSession__message.get_rcode().to_text())
        # And that the result looks right
        if expected == Rcode.NOERROR:
            self.assertEqual(UPDATE_SUCCESS, result)
        else:
            self.assertEqual(UPDATE_ERROR, result)

    def test_check_prerequisites(self):
        # This test checks if the actual prerequisite-type-specific
        # methods are called.
        # It does test all types of prerequisites, but it does not test
        # every possible result for those types (those are tested above,
        # in the specific prerequisite type tests)

        # Let's first define a number of prereq's that should succeed
        rrset_exists_yes = create_rrset("example.org", RRClass.ANY,
                                        RRType.SOA, 0)

        rrset_exists_value_yes = create_rrset("www.example.org", RRClass.IN,
                                              RRType.A, 0, [ "192.0.2.1" ])

        rrset_does_not_exist_yes = create_rrset("foo.example.org",
                                                RRClass.NONE, RRType.SOA,
                                                0)

        name_in_use_yes = create_rrset("www.example.org", RRClass.ANY,
                                       RRType.ANY, 0)

        name_not_in_use_yes = create_rrset("foo.example.org", RRClass.NONE,
                                           RRType.ANY, 0)

        rrset_exists_value_1 = create_rrset("example.org", RRClass.IN,
                                            RRType.NS, 0, ["ns1.example.org."])
        rrset_exists_value_2 = create_rrset("example.org", RRClass.IN,
                                            RRType.NS, 0, ["ns2.example.org."])
        rrset_exists_value_3 = create_rrset("example.org", RRClass.IN,
                                            RRType.NS, 0, ["ns3.example.org."])

        # and a number that should not
        rrset_exists_no = create_rrset("foo.example.org", RRClass.ANY,
                                       RRType.SOA, 0)

        rrset_exists_value_no = create_rrset("www.example.org", RRClass.IN,
                                             RRType.A, 0, [ "192.0.2.2" ])

        rrset_does_not_exist_no = create_rrset("example.org", RRClass.NONE,
                                               RRType.SOA, 0)

        name_in_use_no = create_rrset("foo.example.org", RRClass.ANY,
                                      RRType.ANY, 0)

        name_not_in_use_no = create_rrset("www.example.org", RRClass.NONE,
                                          RRType.ANY, 0)
        # check 'no' result codes
        self.check_prerequisite_result(Rcode.NXRRSET,
                                       [ rrset_exists_no ])
        self.check_prerequisite_result(Rcode.NXRRSET,
                                       [ rrset_exists_value_no ])
        self.check_prerequisite_result(Rcode.YXRRSET,
                                       [ rrset_does_not_exist_no ])
        self.check_prerequisite_result(Rcode.NXDOMAIN,
                                       [ name_in_use_no ])
        self.check_prerequisite_result(Rcode.YXDOMAIN,
                                       [ name_not_in_use_no ])

        # the 'yes' codes should result in ok
        # individually
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ rrset_exists_yes ] )
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ rrset_exists_value_yes ])
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ rrset_does_not_exist_yes ])
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ name_in_use_yes ])
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ name_not_in_use_yes ])
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ rrset_exists_value_1,
                                         rrset_exists_value_2,
                                         rrset_exists_value_3])

        # and together
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ rrset_exists_yes,
                                         rrset_exists_value_yes,
                                         rrset_does_not_exist_yes,
                                         name_in_use_yes,
                                         name_not_in_use_yes,
                                         rrset_exists_value_1,
                                         rrset_exists_value_2,
                                         rrset_exists_value_3])

        # try out a permutation, note that one rrset is split up,
        # and the order of the RRs should not matter
        self.check_prerequisite_result(Rcode.NOERROR,
                                       [ rrset_exists_value_3,
                                         rrset_exists_yes,
                                         rrset_exists_value_2,
                                         name_in_use_yes,
                                         rrset_exists_value_1])

        # Should fail on the first error, even if most of the
        # prerequisites are ok
        self.check_prerequisite_result(Rcode.NXDOMAIN,
                                       [ rrset_exists_value_3,
                                         rrset_exists_yes,
                                         rrset_exists_value_2,
                                         name_in_use_yes,
                                         name_in_use_no,
                                         rrset_exists_value_1])

    def test_prerequisite_notzone(self):
        rrset = create_rrset("some.other.zone.", RRClass.ANY, RRType.SOA, 0)
        self.check_prerequisite_result(Rcode.NOTZONE, [ rrset ])

    def test_prerequisites_formerr(self):
        # test for form errors in the prerequisite section

        # Class ANY, non-zero TTL
        rrset = create_rrset("example.org", RRClass.ANY, RRType.SOA, 1)
        self.check_prerequisite_result(Rcode.FORMERR, [ rrset ])

        # Class ANY, but with rdata
        rrset = create_rrset("example.org", RRClass.ANY, RRType.A, 0,
                             [ b'\x00\x00\x00\x00' ])
        self.check_prerequisite_result(Rcode.FORMERR, [ rrset ])

        # Class NONE, non-zero TTL
        rrset = create_rrset("example.org", RRClass.NONE, RRType.SOA, 1)
        self.check_prerequisite_result(Rcode.FORMERR, [ rrset ])

        # Class NONE, but with rdata
        rrset = create_rrset("example.org", RRClass.NONE, RRType.A, 0,
                             [ b'\x00\x00\x00\x00' ])
        self.check_prerequisite_result(Rcode.FORMERR, [ rrset ])

        # Matching class and type, but non-zero TTL
        rrset = create_rrset("www.example.org", RRClass.IN, RRType.A, 1,
                             [ "192.0.2.1" ])
        self.check_prerequisite_result(Rcode.FORMERR, [ rrset ])

        # Completely different class
        rrset = create_rrset("example.org", RRClass.CH, RRType.TXT, 0,
                             [ "foo" ])
        self.check_prerequisite_result(Rcode.FORMERR, [ rrset ])

    def __prereq_helper(self, method, expected, rrset):
        '''Calls the given method with self._datasrc_client
           and the given rrset, and compares the return value.
           Function does not do much but makes the code look nicer'''
        self.assertEqual(expected, method(rrset))

    def __initialize_update_rrsets(self):
        '''Prepare a number of RRsets to be used in several update tests
           The rrsets are stored in self'''
        orig_a_rrset = create_rrset("www.example.org", TEST_RRCLASS,
                                    RRType.A, 3600, [ "192.0.2.1" ])
        self.orig_a_rrset = orig_a_rrset

        rrset_update_a = create_rrset("www.example.org", TEST_RRCLASS,
                                      RRType.A, 3600,
                                      [ "192.0.2.2", "192.0.2.3" ])
        self.rrset_update_a = rrset_update_a

        rrset_update_soa = create_rrset("example.org", TEST_RRCLASS,
                                        RRType.SOA, 3600,
                                        [ "ns1.example.org. " +
                                          "admin.example.org. " +
                                          "1233 3600 1800 2419200 7200" ])
        self.rrset_update_soa = rrset_update_soa

        rrset_update_soa_del = create_rrset("example.org", RRClass.NONE,
                                            RRType.SOA, 0,
                                            [ "ns1.example.org. " +
                                              "admin.example.org. " +
                                              "1233 3600 1800 2419200 7200" ])
        self.rrset_update_soa_del = rrset_update_soa_del

        rrset_update_soa2 = create_rrset("example.org", TEST_RRCLASS,
                                         RRType.SOA, 3600,
                                         [ "ns1.example.org. " +
                                           "admin.example.org. " +
                                           "4000 3600 1800 2419200 7200" ])
        self.rrset_update_soa2 = rrset_update_soa2

        rrset_update_del_name = create_rrset("www.example.org", RRClass.ANY,
                                             RRType.ANY, 0)
        self.rrset_update_del_name = rrset_update_del_name

        rrset_update_del_name_apex = create_rrset("example.org", RRClass.ANY,
                                                  RRType.ANY, 0)
        self.rrset_update_del_name_apex = rrset_update_del_name_apex

        rrset_update_del_rrset = create_rrset("www.example.org", RRClass.ANY,
                                              RRType.A, 0)
        self.rrset_update_del_rrset = rrset_update_del_rrset

        rrset_update_del_mx_apex = create_rrset("example.org", RRClass.ANY,
                                                RRType.MX, 0)
        self.rrset_update_del_mx_apex = rrset_update_del_mx_apex

        rrset_update_del_soa_apex = create_rrset("example.org", RRClass.ANY,
                                                 RRType.SOA, 0)
        self.rrset_update_del_soa_apex = rrset_update_del_soa_apex

        rrset_update_del_ns_apex = create_rrset("example.org", RRClass.ANY,
                                                RRType.NS, 0)
        self.rrset_update_del_ns_apex = rrset_update_del_ns_apex

        rrset_update_del_rrset_part = create_rrset("www.example.org",
                                                   RRClass.NONE, RRType.A,
                                                   0,
                                                   [ b'\xc0\x00\x02\x02',
                                                     b'\xc0\x00\x02\x03' ])
        self.rrset_update_del_rrset_part = rrset_update_del_rrset_part

        rrset_update_del_rrset_ns = create_rrset("example.org", RRClass.NONE,
                                        RRType.NS, 0,
                                        [ b'\x03ns1\x07example\x03org\x00',
                                          b'\x03ns2\x07example\x03org\x00',
                                          b'\x03ns3\x07example\x03org\x00' ])
        self.rrset_update_del_rrset_ns = rrset_update_del_rrset_ns

        rrset_update_del_rrset_mx = create_rrset("example.org", RRClass.NONE,
                                RRType.MX, 0,
                                [ b'\x00\x0a\x04mail\x07example\x03org\x00' ])
        self.rrset_update_del_rrset_mx = rrset_update_del_rrset_mx

    def test_acl_before_prereq(self):
        name_in_use_no = create_rrset("foo.example.org", RRClass.ANY,
                                      RRType.ANY, 0)

        # Test a prerequisite that would fail
        self.check_full_handle_result(Rcode.NXDOMAIN, [], [ name_in_use_no ])

        # Change ACL so that it would be denied
        self._acl_map = {(TEST_ZONE_NAME, TEST_RRCLASS):
                             REQUEST_LOADER.load([{"action": "REJECT"}])}

        # The prerequisite should now not be reached; it should fail on the
        # ACL
        self.check_full_handle_result(Rcode.REFUSED, [], [ name_in_use_no ])

    def test_prescan(self):
        '''Test whether the prescan succeeds on data that is ok, and whether
           if notices the SOA if present'''
        # prepare a set of correct update statements
        self.__initialize_update_rrsets()

        self.check_prescan_result(Rcode.NOERROR, [ self.rrset_update_a ])

        # check if soa is noticed
        self.check_prescan_result(Rcode.NOERROR, [ self.rrset_update_soa ],
                                  self.rrset_update_soa)

        # Other types of succesful prechecks
        self.check_prescan_result(Rcode.NOERROR, [ self.rrset_update_soa2 ],
                                  self.rrset_update_soa2)
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_del_name ])
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_del_name_apex ])
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_del_rrset ])
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_del_mx_apex ])
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_del_rrset_part ])

        # and check a few permutations of the above
        # all of them (with one of the soas)
        self.check_prescan_result(Rcode.NOERROR,
                                  [
                                    self.rrset_update_a,
                                    self.rrset_update_soa,
                                    self.rrset_update_del_name,
                                    self.rrset_update_del_name_apex,
                                    self.rrset_update_del_rrset,
                                    self.rrset_update_del_mx_apex,
                                    self.rrset_update_del_rrset_part
                                  ],
                                  self.rrset_update_soa)

        # Two soas. Should we reject or simply use the last?
        # (RFC is not really explicit on this, but between the lines I read
        # use the last)
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_soa,
                                    self.rrset_update_soa2 ],
                                    self.rrset_update_soa2)
        self.check_prescan_result(Rcode.NOERROR,
                                  [ self.rrset_update_soa2,
                                    self.rrset_update_soa ],
                                  self.rrset_update_soa)

        self.check_prescan_result(Rcode.NOERROR,
                                  [
                                    self.rrset_update_del_mx_apex,
                                    self.rrset_update_del_name,
                                    self.rrset_update_del_name_apex,
                                    self.rrset_update_del_rrset_part,
                                    self.rrset_update_a,
                                    self.rrset_update_del_rrset,
                                    self.rrset_update_soa
                                  ],
                                  self.rrset_update_soa)

    def test_prescan_failures(self):
        '''Test whether prescan fails on bad data'''
        # out of zone data
        rrset = create_rrset("different.zone", RRClass.ANY, RRType.TXT, 0)
        self.check_prescan_result(Rcode.NOTZONE, [ rrset ])

        # forbidden type, zone class
        rrset = create_rrset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.ANY, 0,
                             [ b'\x00' ])
        self.check_prescan_result(Rcode.FORMERR, [ rrset ])

        # non-zero TTL, class ANY
        rrset = create_rrset(TEST_ZONE_NAME, RRClass.ANY, RRType.TXT, 1)
        self.check_prescan_result(Rcode.FORMERR, [ rrset ])

        # non-zero Rdata, class ANY
        rrset = create_rrset(TEST_ZONE_NAME, RRClass.ANY, RRType.TXT, 0,
                             [ "foo" ])
        self.check_prescan_result(Rcode.FORMERR, [ rrset ])

        # forbidden type, class ANY
        rrset = create_rrset(TEST_ZONE_NAME, RRClass.ANY, RRType.AXFR, 0,
                             [ b'\x00' ])
        self.check_prescan_result(Rcode.FORMERR, [ rrset ])

        # non-zero TTL, class NONE
        rrset = create_rrset(TEST_ZONE_NAME, RRClass.NONE, RRType.TXT, 1)
        self.check_prescan_result(Rcode.FORMERR, [ rrset ])

        # forbidden type, class NONE
        rrset = create_rrset(TEST_ZONE_NAME, RRClass.NONE, RRType.AXFR, 0,
                             [ b'\x00' ])
        self.check_prescan_result(Rcode.FORMERR, [ rrset ])

    def __check_inzone_data(self, expected_result, name, rrtype,
                            expected_rrset = None):
        '''Does a find on TEST_ZONE for the given rrset's name and type,
           then checks if the result matches the expected result.
           If so, and if expected_rrset is given, they are compared as
           well.'''
        _, finder = self._datasrc_client.find_zone(TEST_ZONE_NAME)
        result, found_rrset, _ = finder.find(name, rrtype,
                                             finder.NO_WILDCARD |
                                             finder.FIND_GLUE_OK)
        self.assertEqual(expected_result, result)
        # Sigh. Need rrsets.compare() again.
        # To be sure, compare name, class, type, and ttl
        if expected_rrset is not None:
            self.assertEqual(expected_rrset.get_name(), found_rrset.get_name())
            self.assertEqual(expected_rrset.get_class(), found_rrset.get_class())
            self.assertEqual(expected_rrset.get_type(), found_rrset.get_type())
            self.assertEqual(expected_rrset.get_ttl().to_text(),
                             found_rrset.get_ttl().to_text())
            expected_rdata =\
                [ rdata.to_text() for rdata in expected_rrset.get_rdata() ]
            found_rdata =\
                [ rdata.to_text() for rdata in found_rrset.get_rdata() ]
            expected_rdata.sort()
            found_rdata.sort()
            self.assertEqual(expected_rdata, found_rdata)

    def test_update_add_delete_rrset(self):
        '''
        Tests a sequence of related add and delete updates. Some other
        cases are tested by later tests.
        '''
        self.__initialize_update_rrsets()

        # initially, the www should only contain one rr
        # (set to self.orig_a_rrset)

        # during this test, we will extend it at some point
        extended_a_rrset = create_rrset("www.example.org", TEST_RRCLASS,
                                        RRType.A, 3600,
                                        [ "192.0.2.1",
                                          "192.0.2.2",
                                          "192.0.2.3" ])

        # Sanity check, make sure original data is really there before updates
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.orig_a_rrset)

        # Add two rrs
        self.check_full_handle_result(Rcode.NOERROR, [ self.rrset_update_a ])

        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 extended_a_rrset)

        # Adding the same RRsets should not make a difference.
        self.check_full_handle_result(Rcode.NOERROR, [ self.rrset_update_a ])

        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 extended_a_rrset)

        # Now delete those two, and we should end up with the original RRset
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_rrset_part ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.orig_a_rrset)

        # 'Deleting' them again should make no difference
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_rrset_part ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.orig_a_rrset)

        # But deleting the entire rrset, independent of its contents, should
        # work
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)

        # Check that if we update the SOA, it is updated to our value
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_soa2 ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.SOA,
                                 self.rrset_update_soa2)

    def test_glue_deletions(self):
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("sub.example.org."),
                                 RRType.NS)
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("ns.sub.example.org."),
                                 RRType.A)

        # See that we can delete glue
        rrset_delete_glue = create_rrset("ns.sub.example.org.",
                                         RRClass.ANY,
                                         RRType.A,
                                         0)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ rrset_delete_glue ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("sub.example.org."),
                                 RRType.NS)
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("ns.sub.example.org."),
                                 RRType.A)

        # Check that we don't accidentally delete a delegation if we
        # try to delete non-existent glue
        rrset_delete_nonexistent_glue = create_rrset("foo.sub.example.org.",
                                                     RRClass.ANY,
                                                     RRType.A,
                                                     0)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ rrset_delete_nonexistent_glue ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("sub.example.org."),
                                 RRType.NS)

    def test_update_add_new_data(self):
        '''
        This tests adds data where none is present
        '''
        # Add data at a completely new name
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("new.example.org"),
                                 RRType.A)
        rrset = create_rrset("new.example.org", TEST_RRCLASS, RRType.A,
                             3600, [ "192.0.2.1", "192.0.2.2" ])
        self.check_full_handle_result(Rcode.NOERROR, [ rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("new.example.org"),
                                 RRType.A,
                                 rrset)

        # Also try a name where data is present, but none of this
        # specific type
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXRRSET,
                                 isc.dns.Name("new.example.org"),
                                 RRType.TXT)
        rrset = create_rrset("new.example.org", TEST_RRCLASS, RRType.TXT,
                             3600, [ "foo" ])
        self.check_full_handle_result(Rcode.NOERROR, [ rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("new.example.org"),
                                 RRType.TXT,
                                 rrset)

    def test_update_add_new_data_interspersed(self):
        '''
        This tests adds data where none is present, similar to
        test_update_add_new_data, but this time the second RRset
        is put into the record between the two RRs of the first
        RRset.
        '''
        # Add data at a completely new name
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("new_a.example.org"),
                                 RRType.A)
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("new_txt.example.org"),
                                 RRType.TXT)

        rrset1 = create_rrset("new_a.example.org", TEST_RRCLASS, RRType.A,
                              3600, [ "192.0.2.1" ])

        rrset2 = create_rrset("new_txt.example.org", TEST_RRCLASS, RRType.TXT,
                              3600, [ "foo" ])

        rrset3 = create_rrset("new_a.example.org", TEST_RRCLASS, RRType.A,
                              3600, [ "192.0.2.2" ])

        self.check_full_handle_result(Rcode.NOERROR,
                                      [ rrset1, rrset2, rrset3 ])

        # The update should have merged rrset1 and rrset3
        rrset_merged = create_rrset("new_a.example.org", TEST_RRCLASS,
                                    RRType.A, 3600,
                                    [ "192.0.2.1", "192.0.2.2" ])

        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("new_a.example.org"),
                                 RRType.A,
                                 rrset_merged)

        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("new_txt.example.org"),
                                 RRType.TXT,
                                 rrset2)

    def test_update_delete_name(self):
        '''
        Tests whether deletion of every RR for a name works
        '''
        self.__initialize_update_rrsets()

        # First check it is there
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)

        # Delete the entire name
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_name ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)

        # Should still be gone after pointless second delete
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_name ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)

    def test_update_apex_special_cases(self):
        '''
        Tests a few special cases when deleting data from the apex
        '''
        self.__initialize_update_rrsets()

        # the original SOA
        orig_soa_rrset = create_rrset("example.org", TEST_RRCLASS,
                                      RRType.SOA, 3600,
                                      [ "ns1.example.org. " +
                                        "admin.example.org. " +
                                        "1234 3600 1800 2419200 7200" ])
        # At some point, the SOA SERIAL will be auto-incremented
        incremented_soa_rrset_01 = create_rrset("example.org", TEST_RRCLASS,
                RRType.SOA, 3600, ["ns1.example.org. " +
                                     "admin.example.org. " +
                                     "1235 3600 1800 2419200 7200" ])
        incremented_soa_rrset_02 = create_rrset("example.org", TEST_RRCLASS,
                RRType.SOA, 3600, ["ns1.example.org. " +
                                     "admin.example.org. " +
                                     "1236 3600 1800 2419200 7200" ])

        # We will delete some of the NS records
        orig_ns_rrset = create_rrset("example.org", TEST_RRCLASS,
                                      RRType.NS, 3600,
                                      [ "ns1.example.org.",
                                        "ns2.example.org.",
                                        "ns3.example.org." ])

        # Sanity check, make sure original data is really there before updates
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.NS,
                                 orig_ns_rrset)
        # We will delete the MX record later in this test, so let's make
        # sure that it exists (we do not care about its value)
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.MX)

        # Check that we cannot delete the SOA record by direct deletion
        # both by name+type and by full rrset
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_soa_apex,
                                        self.rrset_update_soa_del ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.SOA,
                                 incremented_soa_rrset_01)

        # If we delete everything at the apex, the SOA and NS rrsets should be
        # untouched (but serial will be incremented)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_name_apex ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.SOA,
                                 incremented_soa_rrset_02)
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.NS,
                                 orig_ns_rrset)
        # but the MX should be gone
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXRRSET,
                                 isc.dns.Name("example.org"),
                                 RRType.MX)

        # Deleting the NS rrset by name and type only, it should also be left
        # untouched
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_ns_apex ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.NS,
                                 orig_ns_rrset)

    def test_update_apex_special_case_ns_rrset(self):
        # If we delete the NS at the apex specifically, it should still
        # keep one record
        self.__initialize_update_rrsets()
        # When we are done, we should have a reduced NS rrset
        short_ns_rrset = create_rrset("example.org", TEST_RRCLASS,
                                      RRType.NS, 3600,
                                      [ "ns3.example.org." ])
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_rrset_ns ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.NS,
                                 short_ns_rrset)

    def test_update_apex_special_case_ns_rrset2(self):
        # If we add new NS records, then delete all existing ones, it
        # should not keep any
        self.__initialize_update_rrsets()
        new_ns = create_rrset("example.org", TEST_RRCLASS, RRType.NS, 3600,
                              [ "newns1.example.org.", "newns2.example.org." ])

        self.check_full_handle_result(Rcode.NOERROR,
                                      [ new_ns,
                                        self.rrset_update_del_rrset_ns ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.NS,
                                 new_ns)

    def test_update_delete_normal_rrset_at_apex(self):
        '''
        Tests a number of 'normal rrset' deletes at the apex
        '''

        # MX should simply be deleted
        self.__initialize_update_rrsets()
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("example.org"),
                                 RRType.MX)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_rrset_mx ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXRRSET,
                                 isc.dns.Name("example.org"),
                                 RRType.MX)

    def test_update_add_then_delete_rrset(self):
        # If we add data, then delete the whole rrset, added data should
        # be gone as well
        self.__initialize_update_rrsets()
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_a,
                                        self.rrset_update_del_rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)

    def test_update_add_then_delete_name(self):
        # If we add data, then delete the entire name, added data should
        # be gone as well
        self.__initialize_update_rrsets()
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_a,
                                        self.rrset_update_del_name ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.NXDOMAIN,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)

    def test_update_delete_then_add_rrset(self):
        # If we delete an entire rrset, then add something there again,
        # the addition should be done
        self.__initialize_update_rrsets()
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_rrset,
                                        self.rrset_update_a ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.rrset_update_a)

    def test_update_delete_then_add_rrset(self):
        # If we delete an entire name, then add something there again,
        # the addition should be done
        self.__initialize_update_rrsets()
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A)
        self.check_full_handle_result(Rcode.NOERROR,
                                      [ self.rrset_update_del_name,
                                        self.rrset_update_a ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.rrset_update_a)

    def test_update_cname_special_cases(self):
        self.__initialize_update_rrsets()

        # Sanity check
        orig_cname_rrset = create_rrset("cname.example.org", TEST_RRCLASS,
                                        RRType.CNAME, 3600,
                                        [ "www.example.org." ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.CNAME,
                                 isc.dns.Name("cname.example.org"),
                                 RRType.A,
                                 orig_cname_rrset)

        # If we try to add data where a cname is preset
        rrset = create_rrset("cname.example.org", TEST_RRCLASS, RRType.A,
                             3600, [ "192.0.2.1" ])

        self.check_full_handle_result(Rcode.NOERROR, [ rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.CNAME,
                                 isc.dns.Name("cname.example.org"),
                                 RRType.A,
                                 orig_cname_rrset)

        # But updating the cname itself should work
        new_cname_rrset = create_rrset("cname.example.org", TEST_RRCLASS,
                                       RRType.CNAME, 3600,
                                       [ "mail.example.org." ])
        self.check_full_handle_result(Rcode.NOERROR, [ new_cname_rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.CNAME,
                                 isc.dns.Name("cname.example.org"),
                                 RRType.A,
                                 new_cname_rrset)

        self.__initialize_update_rrsets()

        # Likewise, adding a cname where other data is
        # present should do nothing either
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.orig_a_rrset)
        new_cname_rrset = create_rrset("www.example.org", TEST_RRCLASS,
                                       RRType.CNAME, 3600,
                                       [ "mail.example.org." ])
        self.check_full_handle_result(Rcode.NOERROR, [ new_cname_rrset ])
        self.__check_inzone_data(isc.datasrc.ZoneFinder.SUCCESS,
                                 isc.dns.Name("www.example.org"),
                                 RRType.A,
                                 self.orig_a_rrset)

    def test_update_bad_class(self):
        rrset = create_rrset("example.org.", RRClass.CH, RRType.TXT, 0,
                             [ "foo" ])
        self.check_full_handle_result(Rcode.FORMERR, [ rrset ])

    def test_uncaught_exception(self):
        def my_exc():
            raise Exception("foo")
        self._session._UpdateSession__update_soa = my_exc
        self.assertEqual(Rcode.SERVFAIL.to_text(),
                         self._session._UpdateSession__do_update().to_text())

class SessionACLTest(SessionTestBase):
    '''ACL related tests for update session.'''
    def test_update_acl_check(self):
        '''Test for various ACL checks.

        Note that accepted cases are covered in the basic tests.

        '''
        # create a separate session, with default (empty) ACL map.
        session = UpdateSession(self._update_msg,
                                TEST_CLIENT4, ZoneConfig(set(), TEST_RRCLASS,
                                                         self._datasrc_client))
        # then the request should be rejected.
        self.assertEqual((UPDATE_ERROR, None, None), session.handle())

        # recreate the request message, and test with an ACL that would result
        # in 'DROP'.  get_message() should return None.
        msg = create_update_msg()
        acl_map = {(TEST_ZONE_NAME, TEST_RRCLASS):
                       REQUEST_LOADER.load([{"action": "DROP", "from":
                                                 TEST_CLIENT4[0]}])}
        session = UpdateSession(msg, TEST_CLIENT4,
                                ZoneConfig([], TEST_RRCLASS,
                                           self._datasrc_client, acl_map))
        self.assertEqual((UPDATE_DROP, None, None), session.handle())
        self.assertEqual(None, session.get_message())

    def test_update_tsigacl_check(self):
        '''Test for various ACL checks using TSIG.'''
        # This ACL will accept requests from TEST_CLIENT4 (any port) *and*
        # has TSIG signed by TEST_ZONE_NAME; all others will be rejected.
        acl_map = {(TEST_ZONE_NAME, TEST_RRCLASS):
                       REQUEST_LOADER.load([{"action": "ACCEPT",
                                             "from": TEST_CLIENT4[0],
                                             "key": TEST_ZONE_NAME.to_text()}])}

        # If the message doesn't contain TSIG, it doesn't match the ACCEPT
        # ACL entry, and the request should be rejected.
        session = UpdateSession(self._update_msg,
                                TEST_CLIENT4, ZoneConfig(set(), TEST_RRCLASS,
                                                         self._datasrc_client,
                                                         acl_map))
        self.assertEqual((UPDATE_ERROR, None, None), session.handle())
        self.check_response(session.get_message(), Rcode.REFUSED)

        # If the message contains TSIG, it should match the ACCEPT
        # ACL entry, and the request should be granted.
        session = UpdateSession(create_update_msg(tsig_key=TEST_TSIG_KEY),
                                TEST_CLIENT4, ZoneConfig(set(), TEST_RRCLASS,
                                                         self._datasrc_client,
                                                         acl_map))
        self.assertEqual((UPDATE_SUCCESS, TEST_ZONE_NAME, TEST_RRCLASS),
                         session.handle())

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
