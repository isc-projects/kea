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

import isc.datasrc
import isc.dns

import os
import unittest
import shutil

# Constants and common data used in tests

TESTDATA_PATH = os.environ['TESTDATA_PATH']
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH']

ZONE_FILE = TESTDATA_PATH + '/example.com'

ORIG_DB_FILE = TESTDATA_PATH + '/example.com.sqlite3'
DB_FILE = TESTDATA_WRITE_PATH + '/zoneloadertest.sqlite3'
DB_CLIENT_CONFIG = '{ "database_file": "' + DB_FILE + '"}'

ORIG_SOA_TXT = 'example.com. 3600 IN SOA master.example.com. ' +\
               'admin.example.com. 1234 3600 1800 2419200 7200\n'
NEW_SOA_TXT = 'example.com. 1000 IN SOA a.dns.example.com. ' +\
              'mail.example.com. 1 1 1 1 1\n'


class ZoneLoaderTests(unittest.TestCase):
    def setUp(self):
        self.test_name = isc.dns.Name("example.com")
        self.test_file = ZONE_FILE
        self.client = isc.datasrc.DataSourceClient("sqlite3", DB_CLIENT_CONFIG)
        # Make a fresh copy of the database
        shutil.copy(ORIG_DB_FILE, DB_FILE)

    def test_bad_constructor(self):
        self.assertRaises(TypeError, isc.datasrc.ZoneLoader)
        self.assertRaises(TypeError, isc.datasrc.ZoneLoader, 1)
        self.assertRaises(TypeError, isc.datasrc.ZoneLoader,
                          None, self.test_name, self.test_file)
        self.assertRaises(TypeError, isc.datasrc.ZoneLoader,
                          self.client, None, self.test_file)
        self.assertRaises(TypeError, isc.datasrc.ZoneLoader,
                          self.client, self.test_name, None)
        self.assertRaises(TypeError, isc.datasrc.ZoneLoader,
                          self.client, self.test_name, self.test_file, 1)

    def check_zone_soa(self, soa_txt):
        """
        Check that the given RRset exists and matches the expected string
        """
        result, finder = self.client.find_zone(self.test_name)
        self.assertEqual(self.client.SUCCESS, result)
        result, rrset, _ = finder.find(self.test_name, isc.dns.RRType.SOA())
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(soa_txt, rrset.to_text())

    def test_load_file(self):
        self.check_zone_soa(ORIG_SOA_TXT)

        # Create loader and load the zone
        loader = isc.datasrc.ZoneLoader(self.client, self.test_name, self.test_file)
        loader.load()

        self.check_zone_soa(NEW_SOA_TXT)

    def test_load_incremental(self):
        self.check_zone_soa(ORIG_SOA_TXT)

        # Create loader and load the zone
        loader = isc.datasrc.ZoneLoader(self.client, self.test_name, self.test_file)

        # New zone has 8 RRs
        # After 5, it should return False
        self.assertFalse(loader.load_incremental(5))
        # New zone should not have been loaded yet
        self.check_zone_soa(ORIG_SOA_TXT)

        # After 5 more, it should return True (only having read 3)
        self.assertTrue(loader.load_incremental(5))
        # New zone should now be loaded
        self.check_zone_soa(NEW_SOA_TXT)

        # And after that, it should throw
        self.assertRaises(isc.datasrc.Error, loader.load_incremental, 5)

    def test_bad_file(self):
        self.check_zone_soa(ORIG_SOA_TXT)
        loader = isc.datasrc.ZoneLoader(self.client, self.test_name, "no such file")
        self.assertRaises(isc.datasrc.MasterFileError, loader.load)
        self.check_zone_soa(ORIG_SOA_TXT)

    def test_exception(self):
        # Just check if masterfileerror is subclass of datasrc.Error
        self.assertTrue(issubclass(isc.datasrc.MasterFileError,
                                   isc.datasrc.Error))

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
