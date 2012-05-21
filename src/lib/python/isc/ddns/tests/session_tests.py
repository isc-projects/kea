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
from isc.datasrc import DataSourceClient
from isc.ddns.session import *
from isc.ddns.zone_config import *

# Some common test parameters
TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "rwtest.sqlite3.copied"
WRITE_ZONE_DB_CONFIG = "{ \"database_file\": \"" + WRITE_ZONE_DB_FILE + "\"}"

TEST_ZONE_NAME = Name('example.org')
UPDATE_RRTYPE = RRType.SOA()
TEST_RRCLASS = RRClass.IN()
TEST_ZONE_RECORD = Question(TEST_ZONE_NAME, TEST_RRCLASS, UPDATE_RRTYPE)
TEST_CLIENT6 = ('2001:db8::1', 53, 0, 0)
TEST_CLIENT4 = ('192.0.2.1', 53)

def create_update_msg(zones=[TEST_ZONE_RECORD]):
    msg = Message(Message.RENDER)
    msg.set_qid(5353)           # arbitrary chosen
    msg.set_opcode(Opcode.UPDATE())
    msg.set_rcode(Rcode.NOERROR())
    for z in zones:
        msg.add_question(z)

    renderer = MessageRenderer()
    msg.to_wire(renderer)

    # re-read the created data in the parse mode
    msg.clear(Message.PARSE)
    msg.from_wire(renderer.get_data())

    return renderer.get_data(), msg

class SessionTest(unittest.TestCase):
    '''Session tests'''
    def setUp(self):
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)
        self.__datasrc_client = DataSourceClient("sqlite3",
                                                 WRITE_ZONE_DB_CONFIG)
        self.__update_msgdata, self.__update_msg = create_update_msg()
        self.__session = UpdateSession(self.__update_msg,
                                       self.__update_msgdata, TEST_CLIENT4,
                                       ZoneConfig([], TEST_RRCLASS,
                                                  self.__datasrc_client))

    def check_response(self, msg, expected_rcode):
        '''Perform common checks on update resposne message.'''
        self.assertTrue(msg.get_header_flag(Message.HEADERFLAG_QR))
        # note: we convert opcode to text it'd be more helpful on failure.
        self.assertEqual(Opcode.UPDATE().to_text(), msg.get_opcode().to_text())
        self.assertEqual(expected_rcode.to_text(), msg.get_rcode().to_text())
        # All sections should be cleared
        self.assertEqual(0, msg.get_rr_count(SECTION_ZONE))
        self.assertEqual(0, msg.get_rr_count(SECTION_PREREQUISITE))
        self.assertEqual(0, msg.get_rr_count(SECTION_UPDATE))
        self.assertEqual(0, msg.get_rr_count(Message.SECTION_ADDITIONAL))

    def test_handle(self):
        '''Basic update case'''
        result, zname, zclass = self.__session.handle()
        self.assertEqual(UPDATE_SUCCESS, result)
        self.assertEqual(TEST_ZONE_NAME, zname)
        self.assertEqual(TEST_RRCLASS, zclass)

        # Just checking these are different from the success code.
        self.assertNotEqual(UPDATE_ERROR, result)
        self.assertNotEqual(UPDATE_DROP, result)

    def test_broken_request(self):
        # Zone section is empty
        msg_data, msg = create_update_msg(zones=[])
        session = UpdateSession(msg, msg_data, TEST_CLIENT6, None)
        result, zname, zclass = session.handle()
        self.assertEqual(UPDATE_ERROR, result)
        self.assertEqual(None, zname)
        self.assertEqual(None, zclass)
        self.check_response(session.get_message(), Rcode.FORMERR())

        # Zone section contains multiple records
        msg_data, msg = create_update_msg(zones=[TEST_ZONE_RECORD,
                                                 TEST_ZONE_RECORD])
        session = UpdateSession(msg, msg_data, TEST_CLIENT4, None)
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.FORMERR())

        # Zone section's type is not SOA
        msg_data, msg = create_update_msg(zones=[Question(TEST_ZONE_NAME,
                                                          TEST_RRCLASS,
                                                          RRType.A())])
        session = UpdateSession(msg, msg_data, TEST_CLIENT4, None)
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.FORMERR())

    def test_update_secondary(self):
        # specified zone is configured as a secondary.  Since this
        # implementation doesn't support update forwarding, the result
        # should be NOTIMP.
        msg_data, msg = create_update_msg(zones=[Question(TEST_ZONE_NAME,
                                                          TEST_RRCLASS,
                                                          RRType.SOA())])
        session = UpdateSession(msg, msg_data, TEST_CLIENT4,
                                ZoneConfig([(TEST_ZONE_NAME, TEST_RRCLASS)],
                                           TEST_RRCLASS,
                                           self.__datasrc_client))
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.NOTIMP())

    def check_notauth(self, zname, zclass=TEST_RRCLASS):
        '''Common test sequence for the 'notauth' test'''
        msg_data, msg = create_update_msg(zones=[Question(zname, zclass,
                                                          RRType.SOA())])
        session = UpdateSession(msg, msg_data, TEST_CLIENT4,
                                ZoneConfig([(TEST_ZONE_NAME, TEST_RRCLASS)],
                                           TEST_RRCLASS,
                                           self.__datasrc_client))
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.NOTAUTH())

    def test_update_notauth(self):
        '''Update attempt for non authoritative zones'''
        # zone name doesn't match
        self.check_notauth(Name('example.com'))
        # zone name is a subdomain of the actual authoritative zone
        # (match must be exact)
        self.check_notauth(Name('sub.example.org'))
        # zone class doesn't match
        self.check_notauth(Name('example.org'), RRClass.CH())

    def __check_prerequisite_exists(self, expected, client, rrset):
        '''helper method for test_check_prerequisite_exists. This function
           does nothing but call __check_prerequisite_exists, and checks
           the result value.
           expected is either True or False.
           (since the check_prerequisite is a 'private' method, and calling
           it is a bit ugly, this helper method helps keeping the actual
           test code cleaner).
        '''
        self.assertEqual(expected,
            self.__session._UpdateSession__check_prerequisite_rrset_exists(
                            client, rrset))

    def __check_prerequisite_exists_value(self, expected, client, rrset):
        '''Similar to __check_prerequisite_exists(), but for checking
           the result of __check_prerequisite_rrset_exists_value().
        '''
        self.assertEqual(expected,
            self.__session.
                 _UpdateSession__check_prerequisite_rrset_exists_value(client,
                                                                       rrset))

    def __check_prerequisite_does_not_exist(self, expected, client, rrset):
        '''Similar to __check_prerequisite_exists(), but for checking
           the result of __check_prerequisite_rrset_does_not_exist().
        '''
        self.assertEqual(expected,
            self.__session.
                _UpdateSession__check_prerequisite_rrset_does_not_exist(client,
                                                                        rrset))

    def test_check_prerequisite_exists(self):
        # Basic existence checks
        # www.example.org should have an A, but not an MX
        rrset = isc.dns.RRset(isc.dns.Name("www.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(True, self.__datasrc_client, rrset)
        rrset = isc.dns.RRset(isc.dns.Name("www.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.MX(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(False, self.__datasrc_client, rrset)

        # example.org should have an MX, but not an A
        rrset = isc.dns.RRset(isc.dns.Name("example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.MX(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(True, self.__datasrc_client, rrset)
        rrset = isc.dns.RRset(isc.dns.Name("example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(False, self.__datasrc_client, rrset)

        # Wildcard expansion should not be applied, but literal matches
        # should work
        rrset = isc.dns.RRset(isc.dns.Name("foo.wildcard.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(False, self.__datasrc_client, rrset)

        rrset = isc.dns.RRset(isc.dns.Name("*.wildcard.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(True, self.__datasrc_client, rrset)

        # Likewise, CNAME directly should match, but what it points to should not
        rrset = isc.dns.RRset(isc.dns.Name("cname.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(False, self.__datasrc_client, rrset)

        rrset = isc.dns.RRset(isc.dns.Name("cname.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.CNAME(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(True, self.__datasrc_client, rrset)

        # And also make sure a delegation (itself) is not treated as existing data
        rrset = isc.dns.RRset(isc.dns.Name("foo.sub.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(False, self.__datasrc_client, rrset)
        # But the delegation data itself should match
        rrset = isc.dns.RRset(isc.dns.Name("sub.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.NS(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(True, self.__datasrc_client, rrset)
        # As should glue
        rrset = isc.dns.RRset(isc.dns.Name("ns.sub.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists(True, self.__datasrc_client, rrset)

    def test_check_prerequisite_exists_value(self):
        rrset = isc.dns.RRset(isc.dns.Name("www.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        # empty one should not match
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)

        # When the rdata is added, it should match
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.A(),
                                      isc.dns.RRClass.IN(),
                                      "192.0.2.1"))
        self.__check_prerequisite_exists_value(True, self.__datasrc_client,
                                               rrset)

        # But adding more should not
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.A(),
                                      isc.dns.RRClass.IN(),
                                      "192.0.2.2"))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)

        # Also test one with more than one RR
        rrset = isc.dns.RRset(isc.dns.Name("example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.NS(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns1.example.org."))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns2.example.org."))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns3.example.org."))
        self.__check_prerequisite_exists_value(True, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns4.example.org."))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)

        # Repeat that, but try a different order of Rdata addition
        rrset = isc.dns.RRset(isc.dns.Name("example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.NS(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns3.example.org."))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns2.example.org."))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns1.example.org."))
        self.__check_prerequisite_exists_value(True, self.__datasrc_client,
                                               rrset)
        rrset.add_rdata(isc.dns.Rdata(isc.dns.RRType.NS(),
                                      isc.dns.RRClass.IN(),
                                      "ns4.example.org."))
        self.__check_prerequisite_exists_value(False, self.__datasrc_client,
                                               rrset)

    def test_check_prerequisite_does_not_exist(self):
        # This is essentially the same as test_check_prerequisite_exists(),
        # but with the opposite resulting values
        # www.example.org should have an A, but not an MX
        rrset = isc.dns.RRset(isc.dns.Name("www.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(False, self.__datasrc_client, rrset)
        rrset = isc.dns.RRset(isc.dns.Name("www.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.MX(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(True, self.__datasrc_client, rrset)

        # example.org should have an MX, but not an A
        rrset = isc.dns.RRset(isc.dns.Name("example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.MX(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(False, self.__datasrc_client, rrset)
        rrset = isc.dns.RRset(isc.dns.Name("example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(True, self.__datasrc_client, rrset)

        # Wildcard expansion should not be applied, but literal matches
        # should work
        rrset = isc.dns.RRset(isc.dns.Name("foo.wildcard.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(True, self.__datasrc_client, rrset)

        rrset = isc.dns.RRset(isc.dns.Name("*.wildcard.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(False, self.__datasrc_client, rrset)

        # Likewise, CNAME directly should match, but what it points to should not
        rrset = isc.dns.RRset(isc.dns.Name("cname.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(True, self.__datasrc_client, rrset)

        rrset = isc.dns.RRset(isc.dns.Name("cname.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.CNAME(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(False, self.__datasrc_client, rrset)

        # And also make sure a delegation (itself) is not treated as existing data
        rrset = isc.dns.RRset(isc.dns.Name("foo.sub.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(True, self.__datasrc_client, rrset)
        # But the delegation data itself should match
        rrset = isc.dns.RRset(isc.dns.Name("sub.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.NS(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(False, self.__datasrc_client, rrset)
        # As should glue
        rrset = isc.dns.RRset(isc.dns.Name("ns.sub.example.org"),
                              isc.dns.RRClass.IN(), isc.dns.RRType.A(),
                              isc.dns.RRTTL(0))
        self.__check_prerequisite_does_not_exist(False, self.__datasrc_client, rrset)

    def test_check_prerequisite_name_in_use(self):
        pass

    def test_check_prerequisite_name_not_in_use(self):
        pass

    def test_check_prerequisites(self):
        pass

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
