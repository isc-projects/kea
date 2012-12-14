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
from isc.datasrc import *
import isc.log
import os
import shutil

# Some common test parameters
TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
LOCAL_TESTDATA_PATH = os.environ['LOCAL_TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
NEW_ZONE_TXT_FILE = LOCAL_TESTDATA_PATH + "example.org.zone"
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "rwtest.sqlite3.copied"
TEST_ZONE_NAME = Name('example.org')
DATASRC_CONFIG = '{"database_file": "' + WRITE_ZONE_DB_FILE + '"}'

# before/after SOAs: different in mname and serial
ORIG_SOA_TXT = 'example.org. 3600 IN SOA ns1.example.org. ' +\
    'admin.example.org. 1234 3600 1800 2419200 7200\n'
NEW_SOA_TXT = 'example.org. 3600 IN SOA ns.example.org. ' +\
    'admin.example.org. 1235 3600 1800 2419200 7200\n'

class TestLoadZoneRunner(unittest.TestCase):
    def setUp(self):
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)

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

    def check_zone_soa(self, soa_txt):
        "Check that the given SOA RR exists and matches the expected string"

        client = DataSourceClient('sqlite3', DATASRC_CONFIG)
        result, finder = client.find_zone(TEST_ZONE_NAME)
        self.assertEqual(client.SUCCESS, result)
        result, rrset, _ = finder.find(TEST_ZONE_NAME, RRType.SOA())
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(soa_txt, rrset.to_text())

    def test_load_update(self):
        '''successful case to loading new contents to an existing zone.'''
        self.__runner._zone_class = RRClass.IN()
        self.__runner._zone_name = TEST_ZONE_NAME
        self.__runner._zone_file = NEW_ZONE_TXT_FILE
        self.__runner._datasrc_type = 'sqlite3'
        self.__runner._datasrc_config = DATASRC_CONFIG
        self.check_zone_soa(ORIG_SOA_TXT)
        self.__runner._do_load()
        self.check_zone_soa(NEW_SOA_TXT)

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
