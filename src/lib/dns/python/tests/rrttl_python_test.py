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
# Tests for the rrttl part of the libdns_python module
#

import unittest
import os
from libdns_python import *

class RdataTest(unittest.TestCase):
    def setUp(self):
        self.t1 = RRTTL(1)
        self.t2 = RRTTL(3600)
        
    def test_init(self):
        self.assertRaises(InvalidRRTTL, RRTTL, "wrong")
        self.assertRaises(TypeError, RRTTL, Exception())
        b = bytearray(1)
        b[0] = 123
        self.assertRaises(TypeError, RRTTL, b)
        self.assertRaises(InvalidRRTTL, RRTTL, "4294967296")
        
    def test_rdata_to_text(self):
        self.assertEqual("1", self.t1.to_text())
        self.assertEqual("3600", self.t2.to_text())

    def test_rdata_to_wire(self):
        b = bytearray()
        self.t1.to_wire(b)
        self.assertEqual(b'\x00\x00\x00\x01', b)
        b = bytearray()
        self.t2.to_wire(b)
        self.assertEqual(b'\x00\x00\x0e\x10', b)

if __name__ == '__main__':
    unittest.main()
