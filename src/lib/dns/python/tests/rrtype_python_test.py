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

class TestModuleSpec(unittest.TestCase):
    
    rrtype_1 = RRType(1)
    rrtype_0x80 = RRType(0x80);
    rrtype_0x800 = RRType(0x800);
    rrtype_0x8000 = RRType(0x8000);
    rrtype_max = RRType(0xffff);
    wiredata = bytearray(b'\x00\x01\x00\x80\x08\x00\x80\x00\xff\xff');

    def test_from_text(self):
        self.assertEqual("A", RRType("A").to_text())
        self.assertEqual("NS", RRType("NS").to_text());
    
        self.assertEqual("TYPE65535", RRType("TYPE65535").to_text());
    
        self.assertEqual(53, RRType("TYPE00053").get_code());

        self.assertRaises(InvalidRRType, RRType, "TYPE000053");
    
        self.assertRaises(InvalidRRType, RRType, "TYPE");
        self.assertRaises(InvalidRRType, RRType, "TYPE-1");
        self.assertRaises(InvalidRRType, RRType, "TYPExxx");
        self.assertRaises(InvalidRRType, RRType, "TYPE65536");
        self.assertRaises(InvalidRRType, RRType, "TYPE6500x");
        self.assertRaises(InvalidRRType, RRType, "TYPE65000 ");

    def test_case_construct(self):
        self.assertEqual("A", RRType("a").to_text());
        self.assertEqual("NS", RRType("ns").to_text());
        self.assertEqual("TYPE65535", RRType("type65535").to_text());

    def test_to_text(self):
        self.assertEqual("A", RRType(1).to_text());
        self.assertEqual("TYPE65000", RRType(65000).to_text());

    def test_to_wire_buffer(self):
        obuffer = bytearray()
        self.rrtype_1.to_wire(obuffer);
        self.rrtype_0x80.to_wire(obuffer);
        self.rrtype_0x800.to_wire(obuffer);
        self.rrtype_0x8000.to_wire(obuffer);
        self.rrtype_max.to_wire(obuffer);

        self.assertEqual(self.wiredata, obuffer)
        
    def test_to_wire_renderer(self):
        mr = MessageRenderer()
        self.rrtype_1.to_wire(mr);
        self.rrtype_0x80.to_wire(mr);
        self.rrtype_0x800.to_wire(mr);
        self.rrtype_0x8000.to_wire(mr);
        self.rrtype_max.to_wire(mr);

        self.assertEqual(self.wiredata, mr.get_data())

    def test_compare(self):
        self.assertTrue(RRType(1) == RRType("A"));
        #self.assertTrue(RRType(1).equals(RRType("A")));
        self.assertTrue(RRType(0) != RRType("A"));
        #self.assertTrue(RRType(0).nequals(RRType("A")));
    
        self.assertTrue(RRType("A") < RRType("NS"));
        self.assertTrue(RRType(100) < RRType(65535));
        
if __name__ == '__main__':
    unittest.main()
