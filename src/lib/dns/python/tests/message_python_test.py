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

#
# Tests for the message part of the pydnspp module
#

import unittest
import os
from pydnspp import *
from testutil import *

# helper functions for tests taken from c++ unittests
if "TESTDATA_PATH" in os.environ:
    testdata_path = os.environ["TESTDATA_PATH"]
else:
    testdata_path = "../tests/testdata"

def factoryFromFile(message, file):
    data = read_wire_data(file)
    message.from_wire(data)
    pass

# we don't have direct comparison for rrsets right now (should we?
# should go in the cpp version first then), so also no direct list
# comparison. Created a helper function
def compare_rrset_list(list1, list2):
    if len(list1) != len(list2):
        return False
    for i in range(0, len(list1)):
        if str(list1[i]) != str(list2[i]):
            return False
    return True

# a complete message taken from cpp tests, for testing towire and totext
def create_message():
    message_render = Message(Message.RENDER)
    message_render.set_qid(0x1035)
    message_render.set_opcode(Opcode.QUERY())
    message_render.set_rcode(Rcode.NOERROR())
    message_render.set_header_flag(Message.HEADERFLAG_QR)
    message_render.set_header_flag(Message.HEADERFLAG_RD)
    message_render.set_header_flag(Message.HEADERFLAG_AA)
    message_render.add_question(Question(Name("test.example.com"),
                                         RRClass("IN"), RRType("A")))
    rrset = RRset(Name("test.example.com"), RRClass("IN"),
                                        RRType("A"), RRTTL(3600))
    rrset.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"))
    rrset.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.2"))
    message_render.add_rrset(Message.SECTION_ANSWER, rrset)
    return message_render

def strip_mutable_tsig_data(data):
    # Unfortunately we cannot easily compare TSIG RR because we can't tweak
    # current time.  As a work around this helper function strips off the time
    # dependent part of TSIG RDATA, i.e., the MAC (assuming HMAC-MD5) and
    # Time Signed.
    return data[0:-32] + data[-26:-22] + data[-6:]

class MessageTest(unittest.TestCase):

    def setUp(self):
        self.p = Message(Message.PARSE)
        self.r = Message(Message.RENDER)

        self.rrset_a = RRset(Name("example.com"), RRClass("IN"), RRType("A"),
                             RRTTL(3600))
        self.rrset_a.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"))
        self.rrset_a.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.2"))

        self.rrset_aaaa = RRset(Name("example.com"), RRClass("IN"),
                                RRType("AAAA"), RRTTL(3600))
        self.rrset_aaaa.add_rdata(Rdata(RRType("AAAA"), RRClass("IN"),
                                        "2001:db8::134"))

        self.bogus_section = Message.SECTION_ADDITIONAL + 1
        self.bogus_below_section = Message.SECTION_QUESTION - 1
        self.tsig_key = TSIGKey("www.example.com:SFuWd/q99SzF8Yzd1QbB9g==")
        self.tsig_ctx = TSIGContext(self.tsig_key)

    def test_init(self):
        self.assertRaises(TypeError, Message, -1)
        self.assertRaises(TypeError, Message, 3)
        self.assertRaises(TypeError, Message, "wrong")

    def test_header_flag(self): # set and get methods
        self.assertRaises(TypeError, self.p.get_header_flag, "wrong")
        self.assertRaises(TypeError, self.r.set_header_flag, "wrong")

        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_QR))
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_AA))
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_TC))
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_RD))
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_RA))
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_AD))
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_CD))

        self.r.set_header_flag(Message.HEADERFLAG_QR)
        self.assertTrue(self.r.get_header_flag(Message.HEADERFLAG_QR))

        self.r.set_header_flag(Message.HEADERFLAG_AA, True)
        self.assertTrue(self.r.get_header_flag(Message.HEADERFLAG_AA))

        self.r.set_header_flag(Message.HEADERFLAG_AA, False)
        self.assertFalse(self.r.get_header_flag(Message.HEADERFLAG_AA))

        self.assertRaises(InvalidParameter, self.r.set_header_flag, 0)
        self.assertRaises(InvalidParameter, self.r.set_header_flag, 0x7000)
        self.assertRaises(InvalidParameter, self.r.set_header_flag, 0x0800)
        self.assertRaises(InvalidMessageOperation,
                          self.p.set_header_flag, Message.HEADERFLAG_AA)

        # Range check.  We need to do this at the binding level, so we need
        # explicit tests for it.
        self.assertRaises(ValueError, self.r.set_header_flag, 0x10000)
        self.assertRaises(ValueError, self.r.set_header_flag, -1)

    def test_set_qid(self):
        self.assertRaises(TypeError, self.r.set_qid, "wrong")
        self.assertRaises(InvalidMessageOperation,
                          self.p.set_qid, 123)
        self.r.set_qid(1234)
        self.assertEqual(1234, self.r.get_qid())
        # Range check.  We need to do this at the binding level, so we need
        # explicit tests for it.
        self.r.set_qid(0)
        self.assertEqual(0, self.r.get_qid())
        self.r.set_qid(0xffff)
        self.assertEqual(0xffff, self.r.get_qid())
        self.assertRaises(ValueError, self.r.set_qid, -1)
        self.assertRaises(ValueError, self.r.set_qid, 0x10000)

    def test_set_rcode(self):
        self.assertRaises(TypeError, self.r.set_rcode, "wrong")

        rcode = Rcode.BADVERS()
        self.r.set_rcode(rcode)
        self.assertEqual(rcode, self.r.get_rcode())

        self.assertRaises(InvalidMessageOperation,
                          self.p.set_rcode, rcode)

        self.assertRaises(InvalidMessageOperation, self.p.get_rcode)

    def test_set_opcode(self):
        self.assertRaises(TypeError, self.r.set_opcode, "wrong")

        opcode = Opcode.IQUERY()
        self.r.set_opcode(opcode)
        self.assertEqual(opcode, self.r.get_opcode())

        self.assertRaises(InvalidMessageOperation,
                          self.p.set_opcode, opcode)

        self.assertRaises(InvalidMessageOperation, self.p.get_opcode)

    def test_get_edns(self):
        self.assertEqual(None, self.p.get_edns())

        message_parse = Message(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire10.wire")
        edns = message_parse.get_edns()
        self.assertEqual(0, edns.get_version())
        self.assertEqual(4096, edns.get_udp_size())
        self.assertTrue(edns.get_dnssec_awareness())

    def test_set_edns(self):
        self.assertRaises(InvalidMessageOperation, self.p.set_edns, EDNS())

        edns = EDNS()
        edns.set_udp_size(1024)
        self.r.set_edns(edns)
        self.assertEqual(1024, self.r.get_edns().get_udp_size())

    def test_get_rr_count(self):
        # counts also tested in add_section
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_QUESTION))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_ANSWER))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_AUTHORITY))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_ADDITIONAL))

        self.r.add_question(Question(Name("example.com"), RRClass("IN"),
                                     RRType("A")))
        self.assertEqual(1, self.r.get_rr_count(Message.SECTION_QUESTION))

        self.r.add_rrset(Message.SECTION_ANSWER, self.rrset_a)
        self.assertEqual(2, self.r.get_rr_count(Message.SECTION_ANSWER))

        factoryFromFile(self.p, "message_fromWire11.wire")
        self.assertEqual(1, self.r.get_rr_count(Message.SECTION_QUESTION))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_ADDITIONAL))

        self.assertRaises(OverflowError, self.r.get_rr_count,
                          self.bogus_section)
        self.assertRaises(TypeError, self.r.get_rr_count, "wrong")

    def test_get_section(self):
        self.assertRaises(TypeError, self.r.get_section, "wrong")

        section_rrset = [self.rrset_a]

        self.assertRaises(InvalidMessageOperation, self.p.add_rrset,
                          Message.SECTION_ANSWER, self.rrset_a)

        self.assertFalse(compare_rrset_list(section_rrset, self.r.get_section(Message.SECTION_ANSWER)))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_ANSWER))
        self.r.add_rrset(Message.SECTION_ANSWER, self.rrset_a)
        self.assertTrue(compare_rrset_list(section_rrset, self.r.get_section(Message.SECTION_ANSWER)))
        self.assertEqual(2, self.r.get_rr_count(Message.SECTION_ANSWER))

        self.assertFalse(compare_rrset_list(section_rrset, self.r.get_section(Message.SECTION_AUTHORITY)))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_AUTHORITY))
        self.r.add_rrset(Message.SECTION_AUTHORITY, self.rrset_a)
        self.assertTrue(compare_rrset_list(section_rrset, self.r.get_section(Message.SECTION_AUTHORITY)))
        self.assertEqual(2, self.r.get_rr_count(Message.SECTION_AUTHORITY))

        self.assertFalse(compare_rrset_list(section_rrset, self.r.get_section(Message.SECTION_ADDITIONAL)))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_ADDITIONAL))
        self.r.add_rrset(Message.SECTION_ADDITIONAL, self.rrset_a)
        self.assertTrue(compare_rrset_list(section_rrset, self.r.get_section(Message.SECTION_ADDITIONAL)))
        self.assertEqual(2, self.r.get_rr_count(Message.SECTION_ADDITIONAL))

    def test_add_question(self):
        self.assertRaises(TypeError, self.r.add_question, "wrong", "wrong")
        q = Question(Name("example.com"), RRClass("IN"), RRType("A"))
        qs = [q]
        self.assertFalse(compare_rrset_list(qs, self.r.get_question()))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_QUESTION))
        self.r.add_question(q)
        self.assertTrue(compare_rrset_list(qs, self.r.get_question()))
        self.assertEqual(1, self.r.get_rr_count(Message.SECTION_QUESTION))

    def test_add_rrset(self):
        self.assertRaises(TypeError, self.r.add_rrset, "wrong")
        self.assertRaises(TypeError, self.r.add_rrset)

        # we can currently only test the no-sign case.
        self.r.add_rrset(Message.SECTION_ANSWER, self.rrset_a)
        self.assertEqual(2, self.r.get_rr_count(Message.SECTION_ANSWER))

    def test_bad_add_rrset(self):
        self.assertRaises(InvalidMessageOperation, self.p.add_rrset,
                          Message.SECTION_ANSWER, self.rrset_a)
        self.assertRaises(OverflowError, self.r.add_rrset,
                          self.bogus_section, self.rrset_a)
        self.assertRaises(OverflowError, self.r.add_rrset,
                          self.bogus_below_section, self.rrset_a)

    def test_clear(self):
        self.assertEqual(None, self.r.clear(Message.PARSE))
        self.assertEqual(None, self.r.clear(Message.RENDER))
        self.assertRaises(TypeError, self.r.clear, "wrong")
        self.assertRaises(TypeError, self.r.clear, 3)

    def test_to_wire(self):
        self.assertRaises(TypeError, self.r.to_wire, 1)
        self.assertRaises(InvalidMessageOperation,
                          self.p.to_wire, MessageRenderer())

        message_render = create_message()
        renderer = MessageRenderer()
        message_render.to_wire(renderer)
        self.assertEqual(b'\x105\x85\x00\x00\x01\x00\x02\x00\x00\x00\x00\x04test\x07example\x03com\x00\x00\x01\x00\x01\xc0\x0c\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\x00\x02\x01\xc0\x0c\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\x00\x02\x02',
                         renderer.get_data())

    def test_to_wire_without_opcode(self):
        self.r.set_rcode(Rcode.NOERROR())
        self.assertRaises(InvalidMessageOperation, self.r.to_wire,
                          MessageRenderer())

    def test_to_wire_without_rcode(self):
        self.r.set_opcode(Opcode.QUERY())
        self.assertRaises(InvalidMessageOperation, self.r.to_wire,
                          MessageRenderer())

    def __common_tsigquery_setup(self):
        self.r.set_opcode(Opcode.QUERY())
        self.r.set_rcode(Rcode.NOERROR())
        self.r.set_header_flag(Message.HEADERFLAG_RD)
        self.r.add_question(Question(Name("www.example.com"),
                                     RRClass("IN"), RRType("A")))

    def __common_tsig_checks(self, expected_file):
        renderer = MessageRenderer()
        self.r.to_wire(renderer, self.tsig_ctx)
        actual_wire = strip_mutable_tsig_data(renderer.get_data())
        expected_wire = strip_mutable_tsig_data(read_wire_data(expected_file))
        self.assertEqual(expected_wire, actual_wire)

    def test_to_wire_with_tsig(self):
        self.r.set_qid(0x2d65)
        self.__common_tsigquery_setup()
        self.__common_tsig_checks("message_toWire2.wire")

    def test_to_wire_with_edns_tsig(self):
        self.r.set_qid(0x6cd)
        self.__common_tsigquery_setup()
        edns = EDNS()
        edns.set_udp_size(4096)
        self.r.set_edns(edns)
        self.__common_tsig_checks("message_toWire3.wire")

    def test_to_text(self):
        message_render = create_message()
        
        msg_str =\
""";; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 4149
;; flags: qr aa rd; QUERY: 1, ANSWER: 2, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;test.example.com. IN A

;; ANSWER SECTION:
test.example.com. 3600 IN A 192.0.2.1
test.example.com. 3600 IN A 192.0.2.2
"""
        self.assertEqual(msg_str, message_render.to_text())
        self.assertEqual(msg_str, str(message_render))

    def test_to_text_without_opcode(self):
        self.r.set_rcode(Rcode.NOERROR())
        self.assertRaises(InvalidMessageOperation, self.r.to_text)

    def test_to_text_without_rcode(self):
        self.r.set_opcode(Opcode.QUERY())
        self.assertRaises(InvalidMessageOperation, self.r.to_text)

    def test_from_wire(self):
        self.assertRaises(TypeError, self.r.from_wire, 1)
        self.assertRaises(InvalidMessageOperation,
                          Message.from_wire, self.r, bytes())
        self.assertRaises(MessageTooShort,
                          Message.from_wire, self.p, bytes())

        test_name = Name("test.example.com");
        
        message_parse = Message(0)
        factoryFromFile(message_parse, "message_fromWire1")
        self.assertEqual(0x1035, message_parse.get_qid())
        self.assertEqual(Opcode.QUERY(), message_parse.get_opcode())
        self.assertEqual(Rcode.NOERROR(), message_parse.get_rcode())
        self.assertTrue(message_parse.get_header_flag(Message.HEADERFLAG_QR))
        self.assertTrue(message_parse.get_header_flag(Message.HEADERFLAG_RD))
        self.assertTrue(message_parse.get_header_flag(Message.HEADERFLAG_AA))
    
        #QuestionPtr q = *message_parse.beginQuestion()
        q = message_parse.get_question()[0]
        self.assertEqual(test_name, q.get_name())
        self.assertEqual(RRType("A"), q.get_type())
        self.assertEqual(RRClass("IN"), q.get_class())
        self.assertEqual(1, message_parse.get_rr_count(Message.SECTION_QUESTION))
        self.assertEqual(2, message_parse.get_rr_count(Message.SECTION_ANSWER))
        self.assertEqual(0, message_parse.get_rr_count(Message.SECTION_AUTHORITY))
        self.assertEqual(0, message_parse.get_rr_count(Message.SECTION_ADDITIONAL))
    
        #RRsetPtr rrset = *message_parse.beginSection(Message.SECTION_ANSWER)
        rrset = message_parse.get_section(Message.SECTION_ANSWER)[0]
        self.assertEqual(test_name, rrset.get_name())
        self.assertEqual(RRType("A"), rrset.get_type())
        self.assertEqual(RRClass("IN"), rrset.get_class())
        ## TTL should be 3600, even though that of the 2nd RR is 7200
        self.assertEqual(RRTTL(3600), rrset.get_ttl())
        rdata = rrset.get_rdata();
        self.assertEqual("192.0.2.1", rdata[0].to_text())
        self.assertEqual("192.0.2.2", rdata[1].to_text())
        self.assertEqual(2, len(rdata))

    def test_EDNS0ExtCode(self):
        # Extended Rcode = BADVERS
        message_parse = Message(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire10.wire")
        self.assertEqual(Rcode.BADVERS(), message_parse.get_rcode())
    
        # Maximum extended Rcode
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire11.wire")
        self.assertEqual(0xfff, message_parse.get_rcode().get_code())
    
    def test_BadEDNS0(self):
        message_parse = Message(Message.PARSE)
        # OPT RR in the answer section
        self.assertRaises(DNSMessageFORMERR,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire4")

        # multiple OPT RRs (in the additional section)
        message_parse.clear(Message.PARSE)
        self.assertRaises(DNSMessageFORMERR,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire5")

        ## OPT RR of a non root name
        message_parse.clear(Message.PARSE)
        self.assertRaises(DNSMessageFORMERR,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire6")
                          
        # Compressed owner name of OPT RR points to a root name.
        # Not necessarily bogus, but very unusual and mostly pathological.
        # We accept it, but is it okay?
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire7")

        # Unsupported Version
        message_parse.clear(Message.PARSE)
        self.assertRaises(DNSMessageBADVERS,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire9")
    

if __name__ == '__main__':
    unittest.main()
