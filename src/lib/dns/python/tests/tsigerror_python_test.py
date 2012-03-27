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

import unittest
import sys
from pydnspp import *

class TSIGErrorTest(unittest.TestCase):
    def test_from_code(self):
        self.assertEqual(0, TSIGError(0).get_code())
        self.assertEqual(18, TSIGError(18).get_code())
        self.assertEqual(65535, TSIGError(65535).get_code())
        self.assertRaises(ValueError, TSIGError, 65536)
        self.assertRaises(ValueError, TSIGError, -1)
        self.assertRaises(TypeError, TSIGError, "not yet supported")

    def test_from_rcode(self):
        # We use RCODE for code values from 0-15.
        self.assertEqual(0, TSIGError(Rcode.NOERROR()).get_code())
        self.assertEqual(15, TSIGError(Rcode(15)).get_code())

        # From error code 16 TSIG errors define a separate space, so passing
        # corresponding RCODE for such code values should be prohibited.
        self.assertRaises(ValueError, TSIGError, Rcode(16))

    def test_constants(self):
        # We'll only test arbitrarily chosen subsets of the codes.
        # This class is quite simple, so it should be suffice.
        self.assertEqual(TSIGError.BAD_SIG_CODE, TSIGError(16).get_code())
        self.assertEqual(TSIGError.BAD_KEY_CODE, TSIGError(17).get_code())
        self.assertEqual(TSIGError.BAD_TIME_CODE, TSIGError(18).get_code())

        self.assertEqual(0, TSIGError.NOERROR.get_code())
        self.assertEqual(9, TSIGError.NOTAUTH.get_code())
        self.assertEqual(14, TSIGError.RESERVED14.get_code())
        self.assertEqual(TSIGError.BAD_SIG_CODE, TSIGError.BAD_SIG.get_code())
        self.assertEqual(TSIGError.BAD_KEY_CODE, TSIGError.BAD_KEY.get_code())
        self.assertEqual(TSIGError.BAD_TIME_CODE, TSIGError.BAD_TIME.get_code())

    def test_equal(self):
        self.assertTrue(TSIGError.NOERROR == TSIGError(Rcode.NOERROR()))
        self.assertTrue(TSIGError(Rcode.NOERROR()) == TSIGError.NOERROR)

        self.assertTrue(TSIGError.BAD_SIG == TSIGError(16))
        self.assertTrue(TSIGError(16) == TSIGError.BAD_SIG)

    def test_nequal(self):
        self.assertTrue(TSIGError.BAD_KEY != TSIGError(Rcode.NOERROR()))
        self.assertTrue(TSIGError(Rcode.NOERROR()) != TSIGError.BAD_KEY)

    def test_to_text(self):
        # TSIGError derived from the standard Rcode
        self.assertEqual("NOERROR", TSIGError(Rcode.NOERROR()).to_text())

        # Well known TSIG errors
        self.assertEqual("BADSIG", TSIGError.BAD_SIG.to_text())
        self.assertEqual("BADKEY", TSIGError.BAD_KEY.to_text())
        self.assertEqual("BADTIME", TSIGError.BAD_TIME.to_text())

        # Unknown (or not yet supported) codes.  Simply converted as numeric.
        self.assertEqual("19", TSIGError(19).to_text());
        self.assertEqual("65535", TSIGError(65535).to_text());

        # also check str() works same way
        self.assertEqual("NOERROR", str(TSIGError(Rcode.NOERROR())))
        self.assertEqual("BADSIG", str(TSIGError.BAD_SIG))

    def test_to_rcode(self):
        # TSIGError derived from the standard Rcode
        self.assertEqual(Rcode.NOERROR(), TSIGError(Rcode.NOERROR()).to_rcode())

        # Well known TSIG errors
        self.assertEqual(Rcode.NOTAUTH(), TSIGError.BAD_SIG.to_rcode())
        self.assertEqual(Rcode.NOTAUTH(), TSIGError.BAD_KEY.to_rcode())
        self.assertEqual(Rcode.NOTAUTH(), TSIGError.BAD_TIME.to_rcode())

        # Unknown (or not yet supported) codes are treated as SERVFAIL.
        self.assertEqual(Rcode.SERVFAIL(), TSIGError(19).to_rcode())
        self.assertEqual(Rcode.SERVFAIL(), TSIGError(65535).to_rcode())

        # Check there's no redundant refcount (which would cause leak)
        self.assertEqual(1, sys.getrefcount(TSIGError.BAD_SIG.to_rcode()))

if __name__ == '__main__':
    unittest.main(verbosity=2)
