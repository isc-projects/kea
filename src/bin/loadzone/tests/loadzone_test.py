# Copyright (C) 2012  Internet Systems Consortium.
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

'''Tests for the loadzone module'''

import unittest
from loadzone import *
import isc.log

class TestLoadZoneRunner(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_dummy(self):
        '''
        Test the old socket file is removed (if any) and a new socket
        is created when the ddns server is created.
        '''
        runner = LoadZoneRunner(['-h', 'example.org', 'example.zone'])

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
