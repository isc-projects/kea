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

#
# Tests for the rrtype part of the libdns_python module
#

import unittest
import os
from libdns_python import *

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

class MessageTest(unittest.TestCase):
    
    def test_RcodeConstruct(self):
        # normal cases
        self.assertEqual(0, Rcode(0).get_code())
        self.assertEqual(0xfff, Rcode(0xfff).get_code()) # possible max code
    
        # should fail on attempt of construction with an out of range code
        self.assertRaises(OverflowError, Rcode, 0x1000)
        self.assertRaises(OverflowError, Rcode, 0xffff)
    
    def test_RcodeToText(self):
        self.assertEqual("NOERROR", Rcode.NOERROR().to_text())
        self.assertEqual("BADVERS", Rcode.BADVERS().to_text())
        self.assertEqual("17", Rcode(Rcode.BADVERS().get_code() + 1).to_text())
        self.assertEqual("4095", Rcode(0xfff).to_text())
    
    
    def test_fromWire(self):
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
        message_parse = Message(PARSE)
        ## Without EDNS0, DNSSEC is considered to be unsupported.
        factoryFromFile(message_parse, "message_fromWire1")
        self.assertFalse(message_parse.is_dnssec_supported())
    
        ## If DO bit is on, DNSSEC is considered to be supported.
        message_parse.clear(PARSE)
        factoryFromFile(message_parse, "message_fromWire2")
        self.assertTrue(message_parse.is_dnssec_supported())
    
        ## If DO bit is off, DNSSEC is considered to be unsupported.
        message_parse.clear(PARSE)
        factoryFromFile(message_parse, "message_fromWire3")
        self.assertFalse(message_parse.is_dnssec_supported())
    
    def test_SetEDNS0DOBit(self):
        # By default, it's false, and we can enable/disable it.
        message_parse = Message(PARSE)
        message_render = Message(RENDER)
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
        message_parse = Message(PARSE)
        factoryFromFile(message_parse, "message_fromWire1")
        self.assertEqual(DEFAULT_MAX_UDPSIZE, message_parse.get_udp_size())
    
        ## If the size specified in EDNS0 > default max, use it.
        message_parse.clear(PARSE)
        factoryFromFile(message_parse, "message_fromWire2")
        self.assertEqual(4096, message_parse.get_udp_size())
    
        ## If the size specified in EDNS0 < default max, keep using the default.
        message_parse.clear(PARSE)
        factoryFromFile(message_parse, "message_fromWire8")
        self.assertEqual(DEFAULT_MAX_UDPSIZE, message_parse.get_udp_size())
    
    def test_SetEDNS0UDPSize(self):
        # The default size if unspecified
        message_render = Message(RENDER)
        message_parse = Message(PARSE)
        self.assertEqual(DEFAULT_MAX_UDPSIZE, message_render.get_udp_size())
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
        message_parse = Message(PARSE)
        factoryFromFile(message_parse, "message_fromWire10")
        self.assertEqual(Rcode.BADVERS(), message_parse.get_rcode())
    
        # Maximum extended Rcode
        message_parse.clear(PARSE)
        factoryFromFile(message_parse, "message_fromWire11")
        self.assertEqual(0xfff, message_parse.get_rcode().get_code())
    
    def test_BadEDNS0(self):
        message_parse = Message(PARSE)
        # OPT RR in the answer section
        self.assertRaises(DNSMessageFORMERR,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire4")

        # multiple OPT RRs (in the additional section)
        message_parse.clear(PARSE)
        self.assertRaises(DNSMessageFORMERR,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire5")

        ## OPT RR of a non root name
        message_parse.clear(PARSE)
        self.assertRaises(DNSMessageFORMERR,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire6")
                          
        # Compressed owner name of OPT RR points to a root name.
        # Not necessarily bogus, but very unusual and mostly pathological.
        # We accept it, but is it okay?
        message_parse.clear(PARSE)
        factoryFromFile(message_parse, "message_fromWire7")

        # Unsupported Version
        message_parse.clear(PARSE)
        self.assertRaises(DNSMessageBADVERS,
                          factoryFromFile,
                          message_parse,
                          "message_fromWire9")
    
    def test_toWire(self):
        message_render = Message(RENDER)
        message_render.set_qid(0x1035)
        message_render.set_opcode(Opcode.QUERY())
        message_render.set_rcode(Rcode.NOERROR())
        message_render.set_header_flag(MessageFlag.QR())
        message_render.set_header_flag(MessageFlag.RD())
        message_render.set_header_flag(MessageFlag.AA())
        #message_render.addQuestion(Question(Name("test.example.com"), RRClass.IN(),
                                            #RRType.A()))
        rrset = RRset(Name("test.example.com"), RRClass("IN"),
                                            RRType("A"), RRTTL(3600))
        #rrset.add_rdata(in.A("192.0.2.1"))
        #rrset.addRdata(in.A("192.0.2.2"))
        #message_render.addRRset(Section.ANSWER(), rrset)
    
        #self.assertEqual(1, message_render.get_rr_count(Section.QUESTION()))
        #self.assertEqual(2, message_render.get_rr_count(Section.ANSWER()))
        self.assertEqual(0, message_render.get_rr_count(Section.AUTHORITY()))
        self.assertEqual(0, message_render.get_rr_count(Section.ADDITIONAL()))

        renderer = MessageRenderer()
        message_render.to_wire(renderer)
        #vector<unsigned char> data;
        #UnitTestUtil.readWireData("testdata/message_toWire1", data)
        #EXPECT_PRED_FORMAT4(UnitTestUtil.matchWireData, obuffer.getData(),
                            #obuffer.getLength(), &data[0], data.size())

if __name__ == '__main__':
    unittest.main()
