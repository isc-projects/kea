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


class MessageFlagTest(unittest.TestCase):
    def test_init(self):
        self.assertRaises(NotImplementedError, MessageFlag)

    def test_get_bit(self):
        self.assertEqual(0x8000, MessageFlag.QR().get_bit())
        self.assertEqual(0x0400, MessageFlag.AA().get_bit())
        self.assertEqual(0x0200, MessageFlag.TC().get_bit())
        self.assertEqual(0x0100, MessageFlag.RD().get_bit())
        self.assertEqual(0x0080, MessageFlag.RA().get_bit())
        self.assertEqual(0x0020, MessageFlag.AD().get_bit())
        self.assertEqual(0x0010, MessageFlag.CD().get_bit())

class OpcodeTest(unittest.TestCase):
    def test_init(self):
        self.assertRaises(NotImplementedError, Opcode)

    def test_get_code(self):
        self.assertEqual(0, Opcode.QUERY().get_code())
        self.assertEqual(1, Opcode.IQUERY().get_code())
        self.assertEqual(2, Opcode.STATUS().get_code())
        self.assertEqual(3, Opcode.RESERVED3().get_code())
        self.assertEqual(4, Opcode.NOTIFY().get_code())
        self.assertEqual(5, Opcode.UPDATE().get_code())
        self.assertEqual(6, Opcode.RESERVED6().get_code())
        self.assertEqual(7, Opcode.RESERVED7().get_code())
        self.assertEqual(8, Opcode.RESERVED8().get_code())
        self.assertEqual(9, Opcode.RESERVED9().get_code())
        self.assertEqual(10, Opcode.RESERVED10().get_code())
        self.assertEqual(11, Opcode.RESERVED11().get_code())
        self.assertEqual(12, Opcode.RESERVED12().get_code())
        self.assertEqual(13, Opcode.RESERVED13().get_code())
        self.assertEqual(14, Opcode.RESERVED14().get_code())
        self.assertEqual(15, Opcode.RESERVED15().get_code())

    def test_to_text(self):
        self.assertEqual("QUERY", Opcode.QUERY().to_text())
        self.assertEqual("QUERY", str(Opcode.QUERY()))
        self.assertEqual("IQUERY", Opcode.IQUERY().to_text())
        self.assertEqual("STATUS", Opcode.STATUS().to_text())
        self.assertEqual("RESERVED3", Opcode.RESERVED3().to_text())
        self.assertEqual("NOTIFY", Opcode.NOTIFY().to_text())
        self.assertEqual("UPDATE", Opcode.UPDATE().to_text())
        self.assertEqual("RESERVED6", Opcode.RESERVED6().to_text())
        self.assertEqual("RESERVED7", Opcode.RESERVED7().to_text())
        self.assertEqual("RESERVED8", Opcode.RESERVED8().to_text())
        self.assertEqual("RESERVED9", Opcode.RESERVED9().to_text())
        self.assertEqual("RESERVED10", Opcode.RESERVED10().to_text())
        self.assertEqual("RESERVED11", Opcode.RESERVED11().to_text())
        self.assertEqual("RESERVED12", Opcode.RESERVED12().to_text())
        self.assertEqual("RESERVED13", Opcode.RESERVED13().to_text())
        self.assertEqual("RESERVED14", Opcode.RESERVED14().to_text())
        self.assertEqual("RESERVED15", Opcode.RESERVED15().to_text())

    def test_richcmp(self):
        o1 = Opcode.QUERY()
        o2 = Opcode.NOTIFY()
        o3 = Opcode.NOTIFY()
        self.assertTrue(o2 == o3)
        self.assertFalse(o2 != o3)
        self.assertTrue(o1 != o2)
        self.assertFalse(o1 == 1)
        self.assertFalse(o1 == o2)
        # can't use assertRaises here...
        try:
            o1 < o2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            o1 <= o2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            o1 > o2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            o1 >= o2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))

class RcodeTest(unittest.TestCase):
    def test_init(self):
        self.assertRaises(TypeError, Rcode, "wrong")
        self.assertRaises(OverflowError, Rcode, 65536)
        self.assertEqual(Rcode(0).get_code(), 0)
    
        self.assertEqual(0, Rcode(0).get_code())
        self.assertEqual(0xfff, Rcode(0xfff).get_code()) # possible max code
    
        # should fail on attempt of construction with an out of range code
        self.assertRaises(OverflowError, Rcode, 0x1000)
        self.assertRaises(OverflowError, Rcode, 0xffff)

    def test_get_code(self):
        self.assertEqual(0, Rcode.NOERROR().get_code())
        self.assertEqual(1, Rcode.FORMERR().get_code())
        self.assertEqual(2, Rcode.SERVFAIL().get_code())
        self.assertEqual(3, Rcode.NXDOMAIN().get_code())
        self.assertEqual(4, Rcode.NOTIMP().get_code())
        self.assertEqual(5, Rcode.REFUSED().get_code())
        self.assertEqual(6, Rcode.YXDOMAIN().get_code())
        self.assertEqual(7, Rcode.YXRRSET().get_code())
        self.assertEqual(8, Rcode.NXRRSET().get_code())
        self.assertEqual(9, Rcode.NOTAUTH().get_code())
        self.assertEqual(10, Rcode.NOTZONE().get_code())
        self.assertEqual(11, Rcode.RESERVED11().get_code())
        self.assertEqual(12, Rcode.RESERVED12().get_code())
        self.assertEqual(13, Rcode.RESERVED13().get_code())
        self.assertEqual(14, Rcode.RESERVED14().get_code())
        self.assertEqual(15, Rcode.RESERVED15().get_code())
        self.assertEqual(16, Rcode.BADVERS().get_code())

    def test_to_text(self):
        self.assertEqual("NOERROR", Rcode(0).to_text())
        self.assertEqual("NOERROR", str(Rcode(0)))
        self.assertEqual("FORMERR", Rcode(1).to_text())
        self.assertEqual("SERVFAIL", Rcode(2).to_text())
        self.assertEqual("NXDOMAIN", Rcode(3).to_text())
        self.assertEqual("NOTIMP", Rcode(4).to_text())
        self.assertEqual("REFUSED", Rcode(5).to_text())
        self.assertEqual("YXDOMAIN", Rcode(6).to_text())
        self.assertEqual("YXRRSET", Rcode(7).to_text())
        self.assertEqual("NXRRSET", Rcode(8).to_text())
        self.assertEqual("NOTAUTH", Rcode(9).to_text())
        self.assertEqual("NOTZONE", Rcode(10).to_text())
        self.assertEqual("RESERVED11", Rcode(11).to_text())
        self.assertEqual("RESERVED12", Rcode(12).to_text())
        self.assertEqual("RESERVED13", Rcode(13).to_text())
        self.assertEqual("RESERVED14", Rcode(14).to_text())
        self.assertEqual("RESERVED15", Rcode(15).to_text())
        self.assertEqual("BADVERS", Rcode(16).to_text())
        
        self.assertEqual("17", Rcode(Rcode.BADVERS().get_code() + 1).to_text())
        self.assertEqual("4095", Rcode(0xfff).to_text())

    def test_richcmp(self):
        r1 = Rcode.NOERROR()
        r2 = Rcode.FORMERR()
        r3 = Rcode.FORMERR()
        self.assertTrue(r2 == r3)
        self.assertTrue(r1 != r2)
        self.assertFalse(r1 == r2)
        self.assertFalse(r1 != 1)
        # can't use assertRaises here...
        try:
            r1 < r2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            r1 <= r2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            r1 > r2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            r1 >= r2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))

class SectionTest(unittest.TestCase):

    def test_init(self):
        self.assertRaises(NotImplementedError, Section)

    def test_get_code(self):
        self.assertEqual(0, Section.QUESTION().get_code())
        self.assertEqual(1, Section.ANSWER().get_code())
        self.assertEqual(2, Section.AUTHORITY().get_code())
        self.assertEqual(3, Section.ADDITIONAL().get_code())

    def test_richcmp(self):
        s1 = Section.QUESTION()
        s2 = Section.ANSWER()
        s3 = Section.ANSWER()
        self.assertTrue(s2 == s3)
        self.assertTrue(s1 != s2)
        self.assertFalse(s1 == s2)
        self.assertFalse(s1 == 1)
        # can't use assertRaises here...
        try:
            s1 < s2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            s1 <= s2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            s1 > s2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        try:
            s1 >= s2
            self.fail("operation that should have raised an error unexpectedly succeeded")
        except Exception as err:
            self.assertEqual(TypeError, type(err))
        

# helper functions for tests taken from c++ unittests
if "TESTDATA_PATH" in os.environ:
    testdata_path = os.environ["TESTDATA_PATH"]
else:
    testdata_path = "../tests/testdata"

def read_wire_data(filename):
    data = bytes()
    file = open(testdata_path + os.sep + filename, "r")
    for line in file:
        line = line.strip()
        if line == "" or line.startswith("#"):
            pass
        else:
            cur_data = bytes.fromhex(line)
            data += cur_data

    return data

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
    message_render.set_header_flag(MessageFlag.QR())
    message_render.set_header_flag(MessageFlag.RD())
    message_render.set_header_flag(MessageFlag.AA())
    message_render.add_question(Question(Name("test.example.com"), RRClass("IN"), RRType("A")))
    rrset = RRset(Name("test.example.com"), RRClass("IN"),
                                        RRType("A"), RRTTL(3600))
    rrset.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"))
    rrset.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.2"))
    message_render.add_rrset(Section.ANSWER(), rrset)
    return message_render


class MessageTest(unittest.TestCase):

    def setUp(self):
        self.p = Message(Message.PARSE)
        self.r = Message(Message.RENDER)
        
    def test_init(self):
        self.assertRaises(TypeError, Message, 3)
        self.assertRaises(TypeError, Message, "wrong")

    def test_get_header_flag(self):
        self.assertRaises(TypeError, self.p.get_header_flag, "wrong")
        self.assertFalse(self.p.get_header_flag(MessageFlag.AA()))

    def test_set_clear_header_flag(self):
        self.assertRaises(TypeError, self.r.set_header_flag, "wrong")
        self.assertRaises(TypeError, self.r.clear_header_flag, "wrong")

        self.assertFalse(self.r.get_header_flag(MessageFlag.AA()))
        self.r.set_header_flag(MessageFlag.AA())
        self.assertTrue(self.r.get_header_flag(MessageFlag.AA()))
        self.r.clear_header_flag(MessageFlag.AA())
        self.assertFalse(self.r.get_header_flag(MessageFlag.AA()))

        self.assertRaises(InvalidMessageOperation,
                          self.p.set_header_flag, MessageFlag.AA())
        self.assertRaises(InvalidMessageOperation,
                          self.p.clear_header_flag, MessageFlag.AA())

    def test_set_DNSSEC_supported(self):
        self.assertRaises(TypeError, self.r.set_dnssec_supported, "wrong")

        self.assertFalse(self.r.is_dnssec_supported())
        self.r.set_dnssec_supported(True)
        self.assertTrue(self.r.is_dnssec_supported())
        self.r.set_dnssec_supported(False)
        self.assertFalse(self.r.is_dnssec_supported())

        self.assertRaises(InvalidMessageOperation,
                          self.p.set_dnssec_supported, True)
        self.assertRaises(InvalidMessageOperation,
                          self.p.set_dnssec_supported, False)

    def test_set_udp_size(self):
        self.assertRaises(TypeError, self.r.set_udp_size, "wrong")
        self.assertRaises(InvalidMessageUDPSize, self.r.set_udp_size, 0)
        self.assertRaises(InvalidMessageUDPSize, self.r.set_udp_size, 65536)
        self.assertRaises(InvalidMessageOperation, self.p.set_udp_size, 1024)
        self.r.set_udp_size(2048)
        self.assertEqual(2048, self.r.get_udp_size())

    def test_set_qid(self):
        self.assertRaises(TypeError, self.r.set_qid, "wrong")
        self.assertRaises(InvalidMessageOperation,
                          self.p.set_qid, 123)
        self.r.set_qid(1234)
        self.assertEqual(1234, self.r.get_qid())

    def test_set_rcode(self):
        self.assertRaises(TypeError, self.r.set_rcode, "wrong")

        rcode = Rcode.BADVERS()
        self.r.set_rcode(rcode)
        self.assertEqual(rcode, self.r.get_rcode())

        self.assertRaises(InvalidMessageOperation,
                          self.p.set_rcode, rcode)
        

    def test_set_opcode(self):
        self.assertRaises(TypeError, self.r.set_opcode, "wrong")

        opcode = Opcode.IQUERY()
        self.r.set_opcode(opcode)
        self.assertEqual(opcode, self.r.get_opcode())

        self.assertRaises(InvalidMessageOperation,
                          self.p.set_opcode, opcode)

    def test_get_section(self):
        self.assertRaises(TypeError, self.r.get_section, "wrong")

        rrset = RRset(Name("example.com"), RRClass("IN"), RRType("A"), RRTTL(3600))
        rrset.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"))
        rrset.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.2"))
        section_rrset = [rrset]

        self.assertRaises(InvalidMessageOperation, self.p.add_rrset,
                          Section.ANSWER(), rrset)
        
        self.assertFalse(compare_rrset_list(section_rrset, self.r.get_section(Section.ANSWER())))
        self.assertEqual(0, self.r.get_rr_count(Section.ANSWER()))
        self.r.add_rrset(Section.ANSWER(), rrset)
        self.assertTrue(compare_rrset_list(section_rrset, self.r.get_section(Section.ANSWER())))
        self.assertEqual(2, self.r.get_rr_count(Section.ANSWER()))

        self.assertFalse(compare_rrset_list(section_rrset, self.r.get_section(Section.AUTHORITY())))
        self.assertEqual(0, self.r.get_rr_count(Section.AUTHORITY()))
        self.r.add_rrset(Section.AUTHORITY(), rrset)
        self.assertTrue(compare_rrset_list(section_rrset, self.r.get_section(Section.AUTHORITY())))
        self.assertEqual(2, self.r.get_rr_count(Section.AUTHORITY()))

        self.assertFalse(compare_rrset_list(section_rrset, self.r.get_section(Section.ADDITIONAL())))
        self.assertEqual(0, self.r.get_rr_count(Section.ADDITIONAL()))
        self.r.add_rrset(Section.ADDITIONAL(), rrset)
        self.assertTrue(compare_rrset_list(section_rrset, self.r.get_section(Section.ADDITIONAL())))
        self.assertEqual(2, self.r.get_rr_count(Section.ADDITIONAL()))

    def test_get_rr_count(self):
        self.assertRaises(TypeError, self.r.get_rr_count, "wrong")
        # counts also tested in add_section

    def test_add_question(self):
        self.assertRaises(TypeError, self.r.add_question, "wrong", "wrong")
        q = Question(Name("example.com"), RRClass("IN"), RRType("A"))
        qs = [q]
        self.assertFalse(compare_rrset_list(qs, self.r.get_question()))
        self.assertEqual(0, self.r.get_rr_count(Section.QUESTION()))
        self.r.add_question(q)
        self.assertTrue(compare_rrset_list(qs, self.r.get_question()))
        self.assertEqual(1, self.r.get_rr_count(Section.QUESTION()))

    def test_add_rrset(self):
        self.assertRaises(TypeError, self.r.add_rrset, "wrong")
        # actual addition already tested in get_section

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

    def test_to_text(self):
        message_render = create_message()
        
        msg_str =\
""";; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 4149
;; flags: qr aa rd ; QUESTION: 1, ANSWER: 2, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;test.example.com. IN A

;; ANSWER SECTION:
test.example.com. 3600 IN A 192.0.2.1
test.example.com. 3600 IN A 192.0.2.2
"""
        self.assertEqual(msg_str, message_render.to_text())
        self.assertEqual(msg_str, str(message_render))

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
        self.assertTrue(message_parse.get_header_flag(MessageFlag.QR()))
        self.assertTrue(message_parse.get_header_flag(MessageFlag.RD()))
        self.assertTrue(message_parse.get_header_flag(MessageFlag.AA()))
    
        #QuestionPtr q = *message_parse.beginQuestion()
        q = message_parse.get_question()[0]
        self.assertEqual(test_name, q.get_name())
        self.assertEqual(RRType("A"), q.get_type())
        self.assertEqual(RRClass("IN"), q.get_class())
        self.assertEqual(1, message_parse.get_rr_count(Section.QUESTION()))
        self.assertEqual(2, message_parse.get_rr_count(Section.ANSWER()))
        self.assertEqual(0, message_parse.get_rr_count(Section.AUTHORITY()))
        self.assertEqual(0, message_parse.get_rr_count(Section.ADDITIONAL()))
    
        #RRsetPtr rrset = *message_parse.beginSection(Section.ANSWER())
        rrset = message_parse.get_section(Section.ANSWER())[0]
        self.assertEqual(test_name, rrset.get_name())
        self.assertEqual(RRType("A"), rrset.get_type())
        self.assertEqual(RRClass("IN"), rrset.get_class())
        ## TTL should be 3600, even though that of the 2nd RR is 7200
        self.assertEqual(RRTTL(3600), rrset.get_ttl())
        rdata = rrset.get_rdata();
        self.assertEqual("192.0.2.1", rdata[0].to_text())
        self.assertEqual("192.0.2.2", rdata[1].to_text())
        self.assertEqual(2, len(rdata))

    def test_GetEDNS0DOBit(self):
        message_parse = Message(Message.PARSE)
        ## Without EDNS0, DNSSEC is considered to be unsupported.
        factoryFromFile(message_parse, "message_fromWire1")
        self.assertFalse(message_parse.is_dnssec_supported())
    
        ## If DO bit is on, DNSSEC is considered to be supported.
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire2")
        self.assertTrue(message_parse.is_dnssec_supported())
    
        ## If DO bit is off, DNSSEC is considered to be unsupported.
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire3")
        self.assertFalse(message_parse.is_dnssec_supported())
    
    def test_SetEDNS0DOBit(self):
        # By default, it's false, and we can enable/disable it.
        message_parse = Message(Message.PARSE)
        message_render = Message(Message.RENDER)
        self.assertFalse(message_render.is_dnssec_supported())
        message_render.set_dnssec_supported(True)
        self.assertTrue(message_render.is_dnssec_supported())
        message_render.set_dnssec_supported(False)
        self.assertFalse(message_render.is_dnssec_supported())
    
        ## A message in the parse mode doesn't allow this flag to be set.
        self.assertRaises(InvalidMessageOperation,
                          message_parse.set_dnssec_supported,
                          True)
        ## Once converted to the render mode, it works as above
        message_parse.make_response()
        self.assertFalse(message_parse.is_dnssec_supported())
        message_parse.set_dnssec_supported(True)
        self.assertTrue(message_parse.is_dnssec_supported())
        message_parse.set_dnssec_supported(False)
        self.assertFalse(message_parse.is_dnssec_supported())
    
    def test_GetEDNS0UDPSize(self):
        # Without EDNS0, the default max UDP size is used.
        message_parse = Message(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire1")
        self.assertEqual(Message.DEFAULT_MAX_UDPSIZE, message_parse.get_udp_size())
    
        ## If the size specified in EDNS0 > default max, use it.
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire2")
        self.assertEqual(4096, message_parse.get_udp_size())
    
        ## If the size specified in EDNS0 < default max, keep using the default.
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire8")
        self.assertEqual(Message.DEFAULT_MAX_UDPSIZE, message_parse.get_udp_size())
    
    def test_SetEDNS0UDPSize(self):
        # The default size if unspecified
        message_render = Message(Message.RENDER)
        message_parse = Message(Message.PARSE)
        self.assertEqual(Message.DEFAULT_MAX_UDPSIZE, message_render.get_udp_size())
        # A common buffer size with EDNS, should succeed
        message_render.set_udp_size(4096)
        self.assertEqual(4096, message_render.get_udp_size())
        # Unusual large value, but accepted
        message_render.set_udp_size(0xffff)
        self.assertEqual(0xffff, message_render.get_udp_size())
        # Too small is value is rejected
        self.assertRaises(InvalidMessageUDPSize, message_render.set_udp_size, 511)
    
        # A message in the parse mode doesn't allow the set operation.
        self.assertRaises(InvalidMessageOperation, message_parse.set_udp_size, 4096)
        ## Once converted to the render mode, it works as above.
        message_parse.make_response()
        message_parse.set_udp_size(4096)
        self.assertEqual(4096, message_parse.get_udp_size())
        message_parse.set_udp_size(0xffff)
        self.assertEqual(0xffff, message_parse.get_udp_size())
        self.assertRaises(InvalidMessageUDPSize, message_parse.set_udp_size, 511)
    
    def test_EDNS0ExtCode(self):
        # Extended Rcode = BADVERS
        message_parse = Message(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire10")
        self.assertEqual(Rcode.BADVERS(), message_parse.get_rcode())
    
        # Maximum extended Rcode
        message_parse.clear(Message.PARSE)
        factoryFromFile(message_parse, "message_fromWire11")
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
