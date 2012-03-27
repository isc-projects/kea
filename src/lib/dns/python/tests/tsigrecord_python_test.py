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

class TSIGRecordTest(unittest.TestCase):
    def setUp(self):
        self.test_name = Name("www.example.com")
        self.test_rdata = TSIG("hmac-md5.sig-alg.reg.int. 1302890362 " + \
                                   "300 16 2tra2tra2tra2tra2tra2g== " + \
                                   "11621 0 0")
        self.test_record = TSIGRecord(self.test_name, self.test_rdata)

    def test_getname(self):
        self.assertEqual(self.test_name, self.test_record.get_name())
        self.assertEqual(1, sys.getrefcount(self.test_record.get_name()))

    def test_get_length(self):
        # see the C++ test for the magic number
        self.assertEqual(85, self.test_record.get_length())

    def test_to_text(self):
        expected_text = "www.example.com. 0 ANY TSIG " + \
            "hmac-md5.sig-alg.reg.int. 1302890362 300 16 " + \
            "2tra2tra2tra2tra2tra2g== 11621 NOERROR 0\n"
        self.assertEqual(expected_text, self.test_record.to_text())
        self.assertEqual(expected_text, str(self.test_record))

if __name__ == '__main__':
    unittest.main(verbosity=2)
