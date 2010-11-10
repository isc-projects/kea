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
# Tests for the rcode part of the pydnspp module
#

import unittest
from pydnspp import *

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

        # constructor with a pair of code portions
        self.assertEqual(3, Rcode(Rcode.NXDOMAIN_CODE, 0).get_code())
        self.assertEqual(Rcode.BADVERS_CODE, Rcode(0, 1).get_code())
        self.assertEqual(0xfff, Rcode(0xf, 0xff).get_code())
        self.assertRaises(OverflowError, Rcode, 0x10, 0xff)
        
    def test_constants(self):
        self.assertEqual(Rcode.NOERROR_CODE, Rcode(0).get_code())
        self.assertEqual(Rcode.FORMERR_CODE, Rcode(1).get_code())
        self.assertEqual(Rcode.NOTIMP_CODE, Rcode(4).get_code())
        self.assertEqual(Rcode.REFUSED_CODE, Rcode(5).get_code())
        self.assertEqual(Rcode.RESERVED15_CODE, Rcode(15).get_code())
        self.assertEqual(Rcode.BADVERS_CODE, Rcode(16).get_code())

        self.assertEqual(Rcode.NOERROR_CODE, Rcode.NOERROR().get_code())
        self.assertEqual(Rcode.FORMERR_CODE, Rcode.FORMERR().get_code())
        self.assertEqual(Rcode.NOTIMP_CODE, Rcode.NOTIMP().get_code())
        self.assertEqual(Rcode.REFUSED_CODE, Rcode.REFUSED().get_code())
        self.assertEqual(Rcode.RESERVED15_CODE, Rcode.RESERVED15().get_code())
        self.assertEqual(Rcode.BADVERS_CODE, Rcode.BADVERS().get_code())

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

    def test_get_extended_code(self):
        self.assertEqual(0, Rcode.NOERROR().get_extended_code())
        self.assertEqual(0, Rcode.YXRRSET().get_extended_code())
        self.assertEqual(1, Rcode.BADVERS().get_extended_code())
        self.assertEqual(0xab, Rcode(0xabf).get_extended_code())
        self.assertEqual(0xff, Rcode(0xfff).get_extended_code())

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

if __name__ == '__main__':
    unittest.main()
