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
# Tests for the rdata part of the pydnspp module
#

import unittest
import os
from pydnspp import *

class RdataTest(unittest.TestCase):
    def setUp(self):
        c = RRClass("IN")
        t = RRType("A")
        self.rdata1 = Rdata(t, c, "192.0.2.98")
        self.rdata2 = Rdata(t, c, "192.0.2.99")
        t = RRType("TXT")
        self.rdata3 = Rdata(t, c, "asdfasdfasdf")
        self.rdata4 = Rdata(t, c, "foo")
        
    def test_init(self):
        self.assertRaises(TypeError, Rdata, "wrong", RRClass("IN"), "192.0.2.99")
        self.assertRaises(TypeError, Rdata, RRType("A"), "wrong", "192.0.2.99")
        self.assertRaises(TypeError, Rdata, RRType("A"), RRClass("IN"), 1)

    def test_rdata_to_wire(self):
        b = bytearray()
        self.rdata1.to_wire(b)
        self.assertEqual(b'\xc0\x00\x02b', b)
        b = bytearray()
        self.rdata2.to_wire(b)
        self.assertEqual(b'\xc0\x00\x02c', b)
        b = bytearray()
        self.rdata3.to_wire(b)
        self.assertEqual(b'\x0casdfasdfasdf', b)
        b = bytearray()
        self.rdata4.to_wire(b)
        self.assertEqual(b'\x03foo', b)
        self.assertRaises(TypeError, self.rdata1.to_wire, 1)

        renderer = MessageRenderer()
        self.rdata1.to_wire(renderer)
        self.assertEqual(b'\xc0\x00\x02b', renderer.get_data())

        renderer = MessageRenderer()
        self.rdata3.to_wire(renderer)
        self.assertEqual(b'\x0casdfasdfasdf', renderer.get_data())

    def test_rdata_to_text(self):
        self.assertEqual("192.0.2.98", self.rdata1.to_text())
        self.assertEqual("192.0.2.99", self.rdata2.to_text())
        self.assertEqual("\"asdfasdfasdf\"", self.rdata3.to_text())
        self.assertEqual("\"foo\"", self.rdata4.to_text())
        self.assertEqual("\"foo\"", str(self.rdata4))

    def test_richcmp(self):
        self.assertTrue(self.rdata1 < self.rdata2);
        self.assertTrue(self.rdata1 <= self.rdata2);
        self.assertFalse(self.rdata1 > self.rdata2);
        self.assertFalse(self.rdata1 >= self.rdata2);
        self.assertTrue(self.rdata3 != self.rdata4)
        other_rdata = Rdata(RRType("TXT"), RRClass("IN"), "foo")
        self.assertTrue(self.rdata4 == other_rdata)

        self.assertFalse(self.rdata1 > self.rdata2);
        self.assertFalse(self.rdata1 >= self.rdata2);
        self.assertTrue(self.rdata1 < self.rdata2);
        self.assertTrue(self.rdata1 <= self.rdata2);
        self.assertFalse(self.rdata3 == self.rdata4)
        self.assertFalse(self.rdata4 != other_rdata)
        

if __name__ == '__main__':
    unittest.main()
