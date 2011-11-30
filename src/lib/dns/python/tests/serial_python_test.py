# Copyright (C) 2011  Internet Systems Consortium.
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
# Tests for the rrttl part of the pydnspp module
#

import unittest
import os
from pydnspp import *

class SerialTest(unittest.TestCase):
    def setUp(self):
        self.one = Serial(1)
        self.one_2 = Serial(1)
        self.two = Serial(2)
        self.date_zero = Serial(1980120100)
        self.date_one = Serial(1980120101)
        self.zero = Serial(0)
        self.highest = Serial(4294967295)
        self.number_low = Serial(12345)
        self.number_medium = Serial(2000000000)
        self.number_high = Serial(4000000000)

    def test_init(self):
        self.assertRaises(ValueError, Serial, -1)
        self.assertRaises(ValueError, Serial, 4294967296)
        self.assertRaises(ValueError, Serial, 4294967297)
        self.assertRaises(ValueError, Serial, 100000000000)

    def test_get_value(self):
        self.assertEqual(1, self.one.get_value())
        self.assertNotEqual(2, self.one_2.get_value())
        self.assertEqual(2, self.two.get_value())
        self.assertEqual(1980120100, self.date_zero.get_value())
        self.assertEqual(1980120101, self.date_one.get_value())
        self.assertEqual(0, self.zero.get_value())
        self.assertEqual(4294967295, self.highest.get_value())
        self.assertEqual(12345, self.number_low.get_value())
        self.assertEqual(2000000000, self.number_medium.get_value())
        self.assertEqual(4000000000, self.number_high.get_value())

    def test_str(self):
        self.assertEqual('1', str(self.one))
        self.assertNotEqual('2', str(self.one_2))
        self.assertEqual('2', str(self.two))
        self.assertEqual('1980120100', str(self.date_zero))
        self.assertEqual('1980120101', str(self.date_one))
        self.assertEqual('0', str(self.zero))
        self.assertEqual('4294967295', str(self.highest))
        self.assertEqual('12345', str(self.number_low))
        self.assertEqual('2000000000', str(self.number_medium))
        self.assertEqual('4000000000', str(self.number_high))

    def test_equals(self):
        self.assertEqual(self.one, self.one)
        self.assertEqual(self.one, self.one_2)
        self.assertNotEqual(self.one, self.two)
        self.assertNotEqual(self.two, self.one)
        self.assertEqual(Serial(12345), self.number_low)
        self.assertNotEqual(Serial(12346), self.number_low)

    def test_compare(self):
        # These should be true/false even without serial arithmetic
        self.assertLessEqual(self.one, self.one)
        self.assertLessEqual(self.one, self.one_2)
        self.assertLess(self.one, self.two)
        self.assertLessEqual(self.one, self.two)
        self.assertGreater(self.two, self.one)
        self.assertGreaterEqual(self.two, self.two)
        self.assertLess(self.one, self.number_low)
        self.assertLess(self.number_low, self.number_medium)
        self.assertLess(self.number_medium, self.number_high)

        # These should 'wrap'
        self.assertGreater(self.zero, self.highest)
        self.assertLess(self.highest, self.one)
        self.assertLess(self.number_high, self.number_low)

    def test_addition(self):
        self.assertEqual(self.two, self.one + self.one)
        self.assertEqual(self.two, self.one + self.one_2)
        self.assertEqual(self.highest, self.highest + self.zero)
        self.assertEqual(self.zero, self.highest + self.one)
        self.assertEqual(self.one, self.highest + self.two)
        self.assertEqual(self.one, self.highest + self.one + self.one)
        self.assertEqual(self.one + 100, self.highest + 102)
        self.assertEqual(100 + self.one, self.highest + 102)
        self.assertEqual(self.zero + 2147483645, self.highest + 2147483646)

        # using lambda so the error doesn't get thrown on initial evaluation
        self.assertRaises(TypeError, lambda: self.zero + "bad")
        self.assertRaises(TypeError, lambda: self.zero + None)
        self.assertRaises(TypeError, lambda: "bad" + self.zero)

if __name__ == '__main__':
    unittest.main()
