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
# Tests for the rrtype part of the pydnspp module
#

import unittest
import os
from pydnspp import *

class TestModuleSpec(unittest.TestCase):
    
    def setUp(self):
        self.test_name = Name("test.example.com")
        self.test_domain = Name("example.com")
        self.test_nsname = Name("ns.example.com")
        self.rrset_a = RRset(self.test_name, RRClass("IN"), RRType("A"), RRTTL(3600))
        self.rrset_a_empty = RRset(self.test_name, RRClass("IN"), RRType("A"), RRTTL(3600))
        self.rrset_ns = RRset(self.test_domain, RRClass("IN"), RRType("NS"), RRTTL(86400))
        self.rrset_ch_txt = RRset(self.test_domain, RRClass("CH"), RRType("TXT"), RRTTL(0))
        self.MAX_RDATA_COUNT = 100
        self.rrset_a.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"));
        self.rrset_a.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.2"));

    def test_init(self):
        self.assertRaises(TypeError, RRset)

    def test_get_rdata_count(self):
        for i in range(0, self.MAX_RDATA_COUNT):
            self.assertEqual(i, self.rrset_a_empty.get_rdata_count())
            self.rrset_a_empty.add_rdata(Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"))

    def test_get_name(self):
        self.assertEqual(self.test_name, self.rrset_a.get_name())
        self.assertEqual(self.test_domain, self.rrset_ns.get_name())

    def test_get_class(self):
        self.assertEqual(RRClass("IN"), self.rrset_a.get_class());
        self.assertEqual(RRClass("CH"), self.rrset_ch_txt.get_class());

    def test_get_type(self):
        self.assertEqual(RRType("A"), self.rrset_a.get_type());
        self.assertEqual(RRType("NS"), self.rrset_ns.get_type());
        self.assertEqual(RRType("TXT"), self.rrset_ch_txt.get_type());

    def test_get_ttl(self):
        self.assertEqual(RRTTL(3600), self.rrset_a.get_ttl());
        self.assertEqual(RRTTL(86400), self.rrset_ns.get_ttl());
        self.assertEqual(RRTTL(0), self.rrset_ch_txt.get_ttl());

    def test_set_ttl(self):
        self.rrset_a.set_ttl(RRTTL(86400));
        self.assertEqual(RRTTL(86400), self.rrset_a.get_ttl());
        self.rrset_a.set_ttl(RRTTL(0));
        self.assertEqual(RRTTL(0), self.rrset_a.get_ttl());
        self.assertRaises(TypeError, self.rrset_a.set_ttl, 1)

    def test_set_name(self):
        self.rrset_a.set_name(self.test_nsname);
        self.assertEqual(self.test_nsname, self.rrset_a.get_name());
        self.assertRaises(TypeError, self.rrset_a.set_name, 1)

    def test_add_rdata(self):
        # no iterator to read out yet (TODO: add addition test once implemented)

        self.assertRaises(TypeError, self.rrset_a.add_rdata, Rdata(RRType("NS"), RRClass("IN"), "test.name"))
        pass

    def test_to_text(self):
        self.assertEqual("test.example.com. 3600 IN A 192.0.2.1\n"
                         "test.example.com. 3600 IN A 192.0.2.2\n",
                         self.rrset_a.to_text());
        self.assertEqual("test.example.com. 3600 IN A 192.0.2.1\n"
                         "test.example.com. 3600 IN A 192.0.2.2\n",
                         str(self.rrset_a));

        self.assertRaises(EmptyRRset, self.rrset_a_empty.to_text)

    def test_to_wire_buffer(self):
        exp_buffer = bytearray(b'\x04test\x07example\x03com\x00\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\x00\x02\x01\x04test\x07example\x03com\x00\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\x00\x02\x02')
        buffer = bytearray()
        self.rrset_a.to_wire(buffer)
        self.assertEqual(exp_buffer, buffer)

        self.assertRaises(EmptyRRset, self.rrset_a_empty.to_wire, buffer);
        self.assertRaises(TypeError, self.rrset_a.to_wire, 1)

    def test_to_wire_renderer(self):
        exp_buffer = bytearray(b'\x04test\x07example\x03com\x00\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\x00\x02\x01\xc0\x00\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\x00\x02\x02')
        mr = MessageRenderer()
        self.rrset_a.to_wire(mr)
        self.assertEqual(exp_buffer, mr.get_data())

    def test_get_rdata(self):
        rdata = [ Rdata(RRType("A"), RRClass("IN"), "192.0.2.1"),
                  Rdata(RRType("A"), RRClass("IN"), "192.0.2.2")
                ]
        self.assertEqual(rdata, self.rrset_a.get_rdata())
        self.assertEqual([], self.rrset_a_empty.get_rdata())
        
if __name__ == '__main__':
    unittest.main()
