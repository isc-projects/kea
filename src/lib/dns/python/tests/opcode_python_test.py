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
# Tests for the opcode part of the pydnspp module
#

import unittest
from pydnspp import *

class OpcodeTest(unittest.TestCase):
    def test_init(self):
        self.assertRaises(TypeError, Opcode, "wrong")
        self.assertEqual(Rcode(0).get_code(), 0)
        self.assertEqual(Rcode(Opcode.RESERVED15_CODE).get_code(), 15)
        self.assertRaises(OverflowError, Opcode, 16)

    def test_constants(self):
        self.assertEqual(Opcode.QUERY_CODE, Opcode(0).get_code())
        self.assertEqual(Opcode.IQUERY_CODE, Opcode(1).get_code())
        self.assertEqual(Opcode.NOTIFY_CODE, Opcode(4).get_code())
        self.assertEqual(Opcode.UPDATE_CODE, Opcode(5).get_code())
        self.assertEqual(Opcode.RESERVED15_CODE, Opcode(15).get_code())

        self.assertEqual(Opcode.QUERY_CODE, Opcode.QUERY().get_code())
        self.assertEqual(Opcode.IQUERY_CODE, Opcode.IQUERY().get_code())
        self.assertEqual(Opcode.NOTIFY_CODE, Opcode.NOTIFY().get_code())
        self.assertEqual(Opcode.UPDATE_CODE, Opcode.UPDATE().get_code())
        self.assertEqual(Opcode.RESERVED15_CODE, Opcode.RESERVED15().get_code())

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

if __name__ == '__main__':
    unittest.main()
