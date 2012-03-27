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

from isc.datasrc.master import *
import unittest

class TestTTL(unittest.TestCase):
    def test_ttl(self):
        self.assertTrue(isttl('3600'))
        self.assertTrue(isttl('1W'))
        self.assertTrue(isttl('1w'))
        self.assertTrue(isttl('2D'))
        self.assertTrue(isttl('2d'))
        self.assertTrue(isttl('30M'))
        self.assertTrue(isttl('30m'))
        self.assertTrue(isttl('10S'))
        self.assertTrue(isttl('10s'))
        self.assertTrue(isttl('2W1D'))
        self.assertFalse(isttl('not a ttl'))
        self.assertFalse(isttl('1X'))

if __name__ == '__main__':
    unittest.main(verbosity=2)
