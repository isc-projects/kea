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

class TSIGRdataTest(unittest.TestCase):
    VALID_TEXT1 = "hmac-md5.sig-alg.reg.int. 1286779327 300 0 16020 BADKEY 0"
    def test_from_string(self):
        tsig = TSIG(self.VALID_TEXT1)
        self.assertEqual(Name("hmac-md5.sig-alg.reg.int"),
                         tsig.get_algorithm())
        # check there's no leak in creating the name object:
        self.assertEqual(1, sys.getrefcount(tsig.get_algorithm()))

if __name__ == '__main__':
    unittest.main()
