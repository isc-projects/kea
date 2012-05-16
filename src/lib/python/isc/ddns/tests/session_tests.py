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

import isc.log
import unittest
from isc.dns import *
from isc.ddns.session import *
from isc.ddns.zone_config import *

# Some common test parameters
TEST_ZONE_NAME = Name('example.com')
UPDATE_RRTYPE = RRType.SOA()
TEST_RRCLASS = RRClass.IN()
TEST_ZONE_RECORD = Question(TEST_ZONE_NAME, TEST_RRCLASS, UPDATE_RRTYPE)

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
        self.__client_addr = ('192.0.2.1', 53)
        self.__update_msgdata, self.__update_msg = create_update_msg()
        self.__session = UpdateSession(self.__update_msg,
                                       self.__update_msgdata,
                                       self.__client_addr,
                                       ZoneConfig([(Name("example.org"),
                                                    TEST_RRCLASS)]))

    def check_response(self, msg, expected_rcode):
        '''Perform common checks on update resposne message.'''
        self.assertTrue(msg.get_header_flag(Message.HEADERFLAG_QR))
        self.assertEqual(Opcode.UPDATE().to_text(), msg.get_opcode().to_text())
        self.assertEqual(expected_rcode.to_text(), msg.get_rcode().to_text())
        # All sections should be cleared
        self.assertEqual(0, msg.get_rr_count(SECTION_ZONE))
        self.assertEqual(0, msg.get_rr_count(SECTION_PREREQUISITE))
        self.assertEqual(0, msg.get_rr_count(SECTION_UPDATE))
        self.assertEqual(0, msg.get_rr_count(Message.SECTION_ADDITIONAL))

    def test_broken_request(self):
        # Zone section is empty
        msg_data, msg = create_update_msg(zones=[])
        session = UpdateSession(msg, msg_data, None, None)
        result, zname, zclass = session.handle()
        self.assertEqual(UPDATE_ERROR, result)
        self.assertEqual(None, zname)
        self.assertEqual(None, zclass)
        self.check_response(session.get_message(), Rcode.FORMERR())

        # Zone section contains multiple records
        msg_data, msg = create_update_msg(zones=[TEST_ZONE_RECORD,
                                                 TEST_ZONE_RECORD])
        session = UpdateSession(msg, msg_data, None, None)
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.FORMERR())

        # Zone section's type is not SOA
        msg_data, msg = create_update_msg(zones=[Question(TEST_ZONE_NAME,
                                                          TEST_RRCLASS,
                                                          RRType.A())])
        session = UpdateSession(msg, msg_data, None, None)
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.FORMERR())

    def test_update_secondary(self):
        # specified zone is configured as a secondary.  Since this
        # implementation doesn't support update forwarding, the result
        # should be REFUSED.
        sec_zone = Name("example.org")
        msg_data, msg = create_update_msg(zones=[Question(sec_zone,
                                                          TEST_RRCLASS,
                                                          RRType.SOA())])
        session = UpdateSession(msg, msg_data, None,
                                ZoneConfig([(sec_zone, TEST_RRCLASS)]))
        self.assertEqual(UPDATE_ERROR, session.handle()[0])
        self.check_response(session.get_message(), Rcode.REFUSED())

    def test_handle(self):
        result, zname, zclass = self.__session.handle()
        self.assertEqual(UPDATE_SUCCESS, result)
        self.assertNotEqual(UPDATE_ERROR, result)
        self.assertNotEqual(UPDATE_DROP, result)
        self.assertEqual(TEST_ZONE_NAME, zname)
        self.assertEqual(TEST_RRCLASS, zclass)

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
