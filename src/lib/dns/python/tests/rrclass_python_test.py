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
# Tests for the rrclass part of the pydnspp module
#

import unittest
import os
from pydnspp import *

class RRClassTest(unittest.TestCase):
    def setUp(self):
        self.c1 = RRClass.IN()
        self.c2 = RRClass.CH()

    def test_init(self):
        self.assertRaises(InvalidRRClass, RRClass, "wrong")
        self.assertRaises(TypeError, RRClass, Exception())
        b = bytearray(1)
        b[0] = 123
        self.assertRaises(TypeError, RRClass, b)
        self.assertRaises(InvalidRRClass, RRClass, 65536)
        self.assertEqual(self.c1, RRClass(1))
        b = bytearray()
        self.c1.to_wire(b)
        self.assertEqual(self.c1, RRClass(b))
        
    def test_rrclass_to_text(self):
        self.assertEqual("IN", self.c1.to_text())
        self.assertEqual("IN", str(self.c1))
        self.assertEqual("CH", self.c2.to_text())

    def test_rrclass_to_wire(self):
        b = bytearray()
        self.c1.to_wire(b)
        self.assertEqual(b'\x00\x01', b)
        b = bytearray()
        self.c2.to_wire(b)
        self.assertEqual(b'\x00\x03', b)

        mr = MessageRenderer()
        self.c1.to_wire(mr)
        self.assertEqual(b'\x00\x01', mr.get_data())

        self.assertRaises(TypeError, self.c1.to_wire, "wrong")

    def test_richcmp(self):
        self.assertTrue(self.c1 != self.c2)
        self.assertTrue(self.c1 < self.c2)
        self.assertTrue(self.c1 <= self.c2)
        self.assertFalse(self.c1 > self.c2)
        self.assertFalse(self.c1 >= self.c2)
        other_rrclass = RRClass("IN")
        self.assertTrue(self.c1 == other_rrclass)

        self.assertFalse(self.c1 == self.c2)
        self.assertFalse(self.c1 > self.c2)
        self.assertFalse(self.c1 >= self.c2)
        self.assertTrue(self.c1 < self.c2)
        self.assertTrue(self.c1 <= self.c2)
        self.assertFalse(self.c1 != other_rrclass)

    def test_statics(self):
        self.assertEqual(RRClass.IN(), RRClass("IN"))
        self.assertEqual(RRClass.CH(), RRClass("CH"))
        self.assertEqual(RRClass.HS(), RRClass("HS"))
        self.assertEqual(254, RRClass.NONE().get_code())
        self.assertEqual(255, RRClass.ANY().get_code())

if __name__ == '__main__':
    unittest.main()
