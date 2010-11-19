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
# Tests for the messagerenderer part of the pydnspp module
#

import unittest
import os
from pydnspp import *

class NameComparisonTest(unittest.TestCase):
    def setUp(self):
        self.name1 = Name("aaaa.example.com")
        self.name2 = Name("bbbb.example.com")
        self.name3 = Name("cccc.example.com")
        self.name4 = Name("aaaa.example.com")
        self.name5 = Name("something.completely.different")

        self.ncr12 = self.name1.compare(self.name2)
        self.ncr13 = self.name1.compare(self.name3)
        self.ncr23 = self.name2.compare(self.name3)
        self.ncr21 = self.name2.compare(self.name1)
        self.ncr32 = self.name3.compare(self.name2)
        self.ncr31 = self.name3.compare(self.name1)
        self.ncr14 = self.name1.compare(self.name4)
        self.ncr15 = self.name1.compare(self.name5)

    def test_init(self):
        self.assertRaises(NotImplementedError, NameComparisonResult)
        
    def test_get_order(self):
        self.assertEqual(-1, self.ncr12.get_order())
        self.assertEqual(-2, self.ncr13.get_order())
        self.assertEqual(-1, self.ncr23.get_order())
        self.assertEqual(1, self.ncr21.get_order())
        self.assertEqual(1, self.ncr32.get_order())
        self.assertEqual(2, self.ncr31.get_order())
        self.assertEqual(0, self.ncr14.get_order())

    def test_get_common_labels(self):
        self.assertEqual(3, self.ncr12.get_common_labels())
        self.assertEqual(1, self.ncr15.get_common_labels())

    def test_get_relation(self):
        self.assertEqual("COMMONANCESTOR", NameComparisonResult.NameRelation[self.ncr12.get_relation()])
        self.assertEqual("COMMONANCESTOR", NameComparisonResult.NameRelation[self.ncr15.get_relation()])

        superdomain = Name("com")
        relation = superdomain.compare(self.name1)
        self.assertEqual("SUPERDOMAIN", NameComparisonResult.NameRelation[relation.get_relation()])

        subdomain = Name("sub.aaaa.example.com")
        relation = subdomain.compare(self.name1)
        self.assertEqual("SUBDOMAIN", NameComparisonResult.NameRelation[relation.get_relation()])

        same = Name("aaaa.example.com")
        relation = same.compare(self.name1)
        self.assertEqual("EQUAL", NameComparisonResult.NameRelation[relation.get_relation()])

class NameTest(unittest.TestCase):
    def setUp(self):
        self.name1 = Name("example.com")
        self.name2 = Name(".")
        self.name3 = Name("something.completely.different")
        self.name4 = Name("EXAMPLE.com")
        self.name5 = Name("*.example.com")

    def test_init(self):
        self.assertRaises(EmptyLabel, Name, "example..com")
        self.assertRaises(TooLongLabel, Name, "a"*64 + ".example.com")
        self.assertRaises(BadLabelType, Name, "\[asdf.example.com")
        self.assertRaises(BadEscape, Name, "\\999")
        self.assertRaises(TooLongName, Name, "example."*32 + "com")
        self.assertRaises(IncompleteName, Name, "\\")
        self.assertRaises(TypeError, Name, 1)

        b = bytearray()
        self.name1.to_wire(b)
        self.assertEqual(self.name1, Name(b))
        self.assertEqual(self.name1, Name(b, 0))
        self.assertRaises(InvalidBufferPosition, Name, b, 100)
        b = bytearray()
        b += b'\x07example'*32 + b'\x03com\x00'
        self.assertRaises(DNSMessageFORMERR, Name, b, 0)

    def test_at(self):
        self.assertEqual(7, self.name1.at(0))
        self.assertEqual(101, self.name1.at(1))
        self.assertRaises(IndexError, self.name1.at, 100)
        self.assertRaises(TypeError, self.name1.at, "wrong")

    def test_get_length(self):
        self.assertEqual(13, self.name1.get_length())
        self.assertEqual(1, self.name2.get_length())
        self.assertEqual(32, self.name3.get_length())

    def test_get_labelcount(self):
        self.assertEqual(3, self.name1.get_labelcount())
        self.assertEqual(1, self.name2.get_labelcount())
        self.assertEqual(4, self.name3.get_labelcount())

    def test_to_text(self):
        self.assertEqual("example.com.", self.name1.to_text())
        self.assertEqual(".", self.name2.to_text())
        self.assertEqual(".", str(self.name2))
        self.assertEqual("something.completely.different.", self.name3.to_text())

    def test_to_wire(self):
        b1 = bytearray()
        self.name1.to_wire(b1)
        self.assertEqual(bytearray(b'\x07example\x03com\x00'), b1)
        b2 = bytearray()
        self.name2.to_wire(b2)
        self.assertEqual(bytearray(b'\x00'), b2)

        mr = MessageRenderer()
        self.name1.to_wire(mr)
        self.assertEqual(b'\x07example\x03com\x00', mr.get_data())

        self.assertRaises(TypeError, self.name1.to_wire, "wrong")
        self.assertRaises(TypeError, self.name1.to_wire, 1)

    def test_compare(self):
        # tested in comparison class above
        pass

    def test_equals(self):
        self.assertFalse(self.name1.equals(self.name2))
        self.assertFalse(self.name1.equals(self.name3))
        self.assertTrue(self.name1.equals(self.name4))

    def test_split(self):
        s = self.name1.split(1,1)
        self.assertEqual("com.", s.to_text())
        s = self.name1.split(0,1)
        self.assertEqual("example.", s.to_text())
        s = self.name3.split(1,2)
        self.assertEqual("completely.different.", s.to_text())
        self.assertRaises(TypeError, self.name1.split, "wrong", 1)
        self.assertRaises(TypeError, self.name1.split, 1, "wrong")
        self.assertRaises(IndexError, self.name1.split, 123, 1)
        self.assertRaises(IndexError, self.name1.split, 1, 123)

        s = self.name1.split(1)
        self.assertEqual("com.", s.to_text())
        s = self.name1.split(0)
        self.assertEqual("example.com.", s.to_text())
        self.assertRaises(IndexError, self.name1.split, 123)

    def test_reverse(self):
        self.assertEqual("com.example.", self.name1.reverse().to_text())
        self.assertEqual(".", self.name2.reverse().to_text())

    def test_concatenate(self):
        self.assertEqual("example.com.", self.name1.concatenate(self.name2).to_text())
        self.assertEqual("example.com.example.com.", self.name1.concatenate(self.name1).to_text())
        self.assertRaises(TypeError, self.name1.concatenate, "wrong")
        self.assertRaises(TooLongName, self.name1.concatenate, Name("example."*31))
        

    def test_downcase(self):
        self.assertEqual("EXAMPLE.com.", self.name4.to_text())
        self.name4.downcase()
        self.assertEqual("example.com.", self.name4.to_text())

    def test_is_wildcard(self):
        self.assertFalse(self.name1.is_wildcard())
        self.assertTrue(self.name5.is_wildcard())

    def test_richcmp(self):
        self.assertTrue(self.name1 > self.name2)
        self.assertFalse(self.name1 < self.name2)
        self.assertFalse(self.name2 > self.name1)
        self.assertTrue(self.name2 < self.name1)
        self.assertTrue(self.name1 == self.name4)
        self.assertFalse(self.name1 != self.name4)
        self.assertTrue(self.name1 != self.name2)
        self.assertFalse(self.name1 == self.name2)
        self.assertTrue(self.name1 <= self.name4)
        self.assertTrue(self.name1 >= self.name4)
        self.assertFalse(self.name1 <= self.name2)
        self.assertTrue(self.name4 >= self.name1)
        self.assertTrue(self.name4 <= self.name1)
        self.assertFalse(self.name2 >= self.name1)

if __name__ == '__main__':
    unittest.main()
