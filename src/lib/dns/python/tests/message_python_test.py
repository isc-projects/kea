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

import sys
import unittest
import os
from pydnspp import *
from testutil import *
from pyunittests_util import fix_current_time

# helper functions for tests taken from c++ unittests
if "TESTDATA_PATH" in os.environ:
    testdata_path = os.environ["TESTDATA_PATH"]
else:
    testdata_path = "../tests/testdata"

def factoryFromFile(message, file, parse_options=Message.PARSE_DEFAULT):
    data = read_wire_data(file)
    message.from_wire(data, parse_options)
    return data

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

# These are used for TSIG + TC tests
LONG_TXT1 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde";

LONG_TXT2 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456";

LONG_TXT3 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef01";

LONG_TXT4 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0";

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

class MessageTest(unittest.TestCase):

    def setUp(self):
        # make sure we don't use faked time unless explicitly do so in tests
        fix_current_time(None)

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

    def tearDown(self):
        # reset any faked current time setting (it would affect other tests)
        fix_current_time(None)

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

        # 0 passed as flag should raise
        self.assertRaises(InvalidParameter, self.r.get_header_flag, 0)
        # unused bit
        self.assertRaises(InvalidParameter, self.r.get_header_flag, 0x80000000)

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

        # We always make a new deep copy in get_section(), so the reference
        # count of the returned list and its each item should be 1; otherwise
        # they would leak.
        self.assertEqual(1, sys.getrefcount(self.r.get_section(
                    Message.SECTION_ANSWER)))
        self.assertEqual(1, sys.getrefcount(self.r.get_section(
                    Message.SECTION_ANSWER)[0]))

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

    def test_add_and_get_question(self):
        self.assertRaises(TypeError, self.r.add_question, "wrong", "wrong")
        q = Question(Name("example.com"), RRClass("IN"), RRType("A"))
        qs = [q]
        self.assertFalse(compare_rrset_list(qs, self.r.get_question()))
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_QUESTION))
        self.r.add_question(q)
        self.assertTrue(compare_rrset_list(qs, self.r.get_question()))
        self.assertEqual(1, self.r.get_rr_count(Message.SECTION_QUESTION))

        # We always make a new deep copy in get_section(), so the reference
        # count of the returned list and its each item should be 1; otherwise
        # they would leak.
        self.assertEqual(1, sys.getrefcount(self.r.get_question()))
        self.assertEqual(1, sys.getrefcount(self.r.get_question()[0]))

        # Message.add_question() called in non-RENDER mode should assert
        self.r.clear(Message.PARSE)
        self.assertRaises(InvalidMessageOperation, self.r.add_question, q)

    def test_make_response(self):
        # Message.make_response() called in non-PARSE mode should assert
        self.r.clear(Message.RENDER)
        self.assertRaises(InvalidMessageOperation, self.r.make_response)

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

    def test_clear_question_section(self):
        self.r.add_question(Question(Name("www.example.com"), RRClass.IN(),
                                     RRType.A()))
        self.assertEqual(1, self.r.get_rr_count(Message.SECTION_QUESTION))
        self.r.clear_section(Message.SECTION_QUESTION)
        self.assertEqual(0, self.r.get_rr_count(Message.SECTION_QUESTION))
        self.assertEqual(0, len(self.r.get_question()))

    def test_clear_section(self):
        for section in [Message.SECTION_ANSWER, Message.SECTION_AUTHORITY,
                        Message.SECTION_ADDITIONAL]:
            self.r.add_rrset(section, self.rrset_a)
            self.assertEqual(2, self.r.get_rr_count(section))
            self.r.clear_section(section)
            self.assertEqual(0, self.r.get_rr_count(section))

        self.assertRaises(InvalidMessageOperation, self.p.clear_section,
                          Message.SECTION_ANSWER)
        self.assertRaises(OverflowError, self.r.clear_section,
                          self.bogus_section)

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

    def __common_tsigmessage_setup(self, flags=[Message.HEADERFLAG_RD],
                                   rrtype=RRType("A"), answer_data=None):
        self.r.set_opcode(Opcode.QUERY())
        self.r.set_rcode(Rcode.NOERROR())
        for flag in flags:
            self.r.set_header_flag(flag)
        if answer_data is not None:
            rrset = RRset(Name("www.example.com"), RRClass("IN"),
                          rrtype, RRTTL(86400))
            for rdata in answer_data:
                rrset.add_rdata(Rdata(rrtype, RRClass("IN"), rdata))
            self.r.add_rrset(Message.SECTION_ANSWER, rrset)
        self.r.add_question(Question(Name("www.example.com"),
                                     RRClass("IN"), rrtype))

    def __common_tsig_checks(self, expected_file):
        renderer = MessageRenderer()
        self.r.to_wire(renderer, self.tsig_ctx)
        self.assertEqual(read_wire_data(expected_file), renderer.get_data())

    def test_to_wire_with_tsig(self):
        fix_current_time(0x4da8877a)
        self.r.set_qid(0x2d65)
        self.__common_tsigmessage_setup()
        self.__common_tsig_checks("message_toWire2.wire")

    def test_to_wire_with_edns_tsig(self):
        fix_current_time(0x4db60d1f)
        self.r.set_qid(0x6cd)
        self.__common_tsigmessage_setup()
        edns = EDNS()
        edns.set_udp_size(4096)
        self.r.set_edns(edns)
        self.__common_tsig_checks("message_toWire3.wire")

    def test_to_wire_tsig_truncation(self):
        fix_current_time(0x4e179212)
        data = factoryFromFile(self.p, "message_fromWire17.wire")
        self.assertEqual(TSIGError.NOERROR,
                         self.tsig_ctx.verify(self.p.get_tsig_record(), data))
        self.r.set_qid(0x22c2)
        self.__common_tsigmessage_setup([Message.HEADERFLAG_QR,
                                         Message.HEADERFLAG_AA,
                                         Message.HEADERFLAG_RD],
                                        RRType("TXT"),
                                        [LONG_TXT1, LONG_TXT2])
        self.__common_tsig_checks("message_toWire4.wire")

    def test_to_wire_tsig_truncation2(self):
        fix_current_time(0x4e179212)
        data = factoryFromFile(self.p, "message_fromWire17.wire")
        self.assertEqual(TSIGError.NOERROR,
                         self.tsig_ctx.verify(self.p.get_tsig_record(), data))
        self.r.set_qid(0x22c2)
        self.__common_tsigmessage_setup([Message.HEADERFLAG_QR,
                                         Message.HEADERFLAG_AA,
                                         Message.HEADERFLAG_RD],
                                        RRType("TXT"),
                                        [LONG_TXT1, LONG_TXT3])
        self.__common_tsig_checks("message_toWire4.wire")

    def test_to_wire_tsig_truncation3(self):
        self.r.set_opcode(Opcode.QUERY())
        self.r.set_rcode(Rcode.NOERROR())
        for i in range(1, 68):
            self.r.add_question(Question(Name("www.example.com"),
                                         RRClass("IN"), RRType(i)))
        renderer = MessageRenderer()
        self.r.to_wire(renderer, self.tsig_ctx)

        self.p.from_wire(renderer.get_data())
        self.assertTrue(self.p.get_header_flag(Message.HEADERFLAG_TC))
        self.assertEqual(66, self.p.get_rr_count(Message.SECTION_QUESTION))
        self.assertNotEqual(None, self.p.get_tsig_record())

    def test_to_wire_tsig_no_truncation(self):
        fix_current_time(0x4e17b38d)
        data = factoryFromFile(self.p, "message_fromWire18.wire")
        self.assertEqual(TSIGError.NOERROR,
                         self.tsig_ctx.verify(self.p.get_tsig_record(), data))
        self.r.set_qid(0xd6e2)
        self.__common_tsigmessage_setup([Message.HEADERFLAG_QR,
                                         Message.HEADERFLAG_AA,
                                         Message.HEADERFLAG_RD],
                                        RRType("TXT"),
                                        [LONG_TXT1, LONG_TXT4])
        self.__common_tsig_checks("message_toWire5.wire")

    def test_to_wire_tsig_length_errors(self):
        renderer = MessageRenderer()
        renderer.set_length_limit(84) # 84 = expected TSIG length - 1
        self.__common_tsigmessage_setup()
        self.assertRaises(TSIGContextError,
                          self.r.to_wire, renderer, self.tsig_ctx)

        renderer.clear()
        self.r.clear(Message.RENDER)
        renderer.set_length_limit(86) # 86 = expected TSIG length + 1
        self.__common_tsigmessage_setup()
        self.assertRaises(TSIGContextError,
                          self.r.to_wire, renderer, self.tsig_ctx)

        # skip the last test of the corresponding C++ test: it requires
        # subclassing MessageRenderer, which is (currently) not possible
        # for python.  In any case, it's very unlikely to happen in practice.

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

    def test_from_wire_short_buffer(self):
        data = read_wire_data("message_fromWire22.wire")
        self.assertRaises(DNSMessageFORMERR, self.p.from_wire, data[:-1])

    def test_from_wire_combind_rrs(self):
        factoryFromFile(self.p, "message_fromWire19.wire")
        rrset = self.p.get_section(Message.SECTION_ANSWER)[0]
        self.assertEqual(RRType("A"), rrset.get_type())
        self.assertEqual(2, len(rrset.get_rdata()))

        rrset = self.p.get_section(Message.SECTION_ANSWER)[1]
        self.assertEqual(RRType("AAAA"), rrset.get_type())
        self.assertEqual(1, len(rrset.get_rdata()))

    def check_preserve_rrs(self, message, section):
        rrset = message.get_section(section)[0]
        self.assertEqual(RRType("A"), rrset.get_type())
        rdata = rrset.get_rdata()
        self.assertEqual(1, len(rdata))
        self.assertEqual('192.0.2.1', rdata[0].to_text())

        rrset = message.get_section(section)[1]
        self.assertEqual(RRType("AAAA"), rrset.get_type())
        rdata = rrset.get_rdata()
        self.assertEqual(1, len(rdata))
        self.assertEqual('2001:db8::1', rdata[0].to_text())

        rrset = message.get_section(section)[2]
        self.assertEqual(RRType("A"), rrset.get_type())
        rdata = rrset.get_rdata()
        self.assertEqual(1, len(rdata))
        self.assertEqual('192.0.2.2', rdata[0].to_text())

    def test_from_wire_preserve_answer(self):
        factoryFromFile(self.p, "message_fromWire19.wire",
                        Message.PRESERVE_ORDER)
        self.check_preserve_rrs(self.p, Message.SECTION_ANSWER)

    def test_from_wire_preserve_authority(self):
        factoryFromFile(self.p, "message_fromWire20.wire",
                        Message.PRESERVE_ORDER)
        self.check_preserve_rrs(self.p, Message.SECTION_AUTHORITY)

    def test_from_wire_preserve_additional(self):
        factoryFromFile(self.p, "message_fromWire21.wire",
                        Message.PRESERVE_ORDER)
        self.check_preserve_rrs(self.p, Message.SECTION_ADDITIONAL)

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

    def test_from_wire_with_tsig(self):
        # Initially there should be no TSIG
        self.assertEqual(None, self.p.get_tsig_record())

        # getTSIGRecord() is only valid in the parse mode.
        self.assertRaises(InvalidMessageOperation, self.r.get_tsig_record)

        factoryFromFile(self.p, "message_toWire2.wire")
        tsig_rr = self.p.get_tsig_record()
        self.assertEqual(Name("www.example.com"), tsig_rr.get_name())
        self.assertEqual(85, tsig_rr.get_length())
        self.assertEqual(TSIGKey.HMACMD5_NAME,
                         tsig_rr.get_rdata().get_algorithm())

        # If we clear the message for reuse, the recorded TSIG will be cleared.
        self.p.clear(Message.PARSE)
        self.assertEqual(None, self.p.get_tsig_record())

    def test_from_wire_with_tsigcompressed(self):
        # Mostly same as fromWireWithTSIG, but the TSIG owner name is
        # compressed.
        factoryFromFile(self.p, "message_fromWire12.wire");
        tsig_rr = self.p.get_tsig_record()
        self.assertEqual(Name("www.example.com"), tsig_rr.get_name())
        # len(www.example.com) = 17, but when fully compressed, the length is
        # 2 bytes.  So the length of the record should be 15 bytes shorter.
        self.assertEqual(70, tsig_rr.get_length())

    def test_from_wire_with_badtsig(self):
        # Multiple TSIG RRs
        self.assertRaises(DNSMessageFORMERR, factoryFromFile,
                          self.p, "message_fromWire13.wire")
        self.p.clear(Message.PARSE)

        # TSIG in the answer section (must be in additional)
        self.assertRaises(DNSMessageFORMERR, factoryFromFile,
                          self.p, "message_fromWire14.wire")
        self.p.clear(Message.PARSE)

        # TSIG is not the last record.
        self.assertRaises(DNSMessageFORMERR, factoryFromFile,
                          self.p, "message_fromWire15.wire")
        self.p.clear(Message.PARSE)

        # Unexpected RR Class (this will fail in constructing TSIGRecord)
        self.assertRaises(DNSMessageFORMERR, factoryFromFile,
                          self.p, "message_fromWire16.wire")

if __name__ == '__main__':
    unittest.main()
