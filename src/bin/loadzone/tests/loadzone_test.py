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
from isc.dns import *
import isc.log

TEST_ZONE_NAME = Name('example.org')

class TestLoadZoneRunner(unittest.TestCase):
    def setUp(self):
        # default command line arguments
        self.__args = ['example.org', 'example.zone']
        self.__runner = LoadZoneRunner(self.__args)

    def tearDown(self):
        pass

    def test_init(self):
        '''
        Test the old socket file is removed (if any) and a new socket
        is created when the ddns server is created.
        '''
        self.assertIsNone(self.__runner._zone_class)
        self.assertIsNone(self.__runner._zone_name)

    def test_parse_args(self):
        self.__runner._parse_args()
        self.assertEqual(TEST_ZONE_NAME, self.__runner._zone_name)

    def test_parse_bad_args(self):
        # There must be exactly 2 non-option arguments: zone name and zone file
        self.assertRaises(BadArgument, LoadZoneRunner([])._parse_args)
        self.assertRaises(BadArgument, LoadZoneRunner(['example'])._parse_args)
        self.assertRaises(BadArgument, LoadZoneRunner(self.__args + ['0']).
                          _parse_args)

        # Bad zone name
        self.assertRaises(BadArgument,
                          LoadZoneRunner(['bad..name', 'example.zone']).
                          _parse_args)

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
