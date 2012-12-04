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

TESTDATA_PATH = os.environ['TESTDATA_PATH']
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH']

ZONE_FILE = TESTDATA_PATH + '/example.com'

DB_FILE = TESTDATA_WRITE_PATH + '/zoneloadertest.sqlite3'
DB_CLIENT_CONFIG = '{ "database_file": "' + DB_FILE + '"}'

class ZoneLoaderTests(unittest.TestCase):
    def setUp(self):
        self.test_name = isc.dns.Name("example.com")
        self.test_file = ZONE_FILE
        self.client = isc.datasrc.DataSourceClient("sqlite3", DB_CLIENT_CONFIG)

    def tearDown(self):
        # Delete the database after each test
        if os.path.exists(DB_FILE):
            os.unlink(DB_FILE)

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

    def test_load_file(self):
        #self.assertRaises(TypeError, isc.datasrc.ZoneLoader());
        result, _ = self.client.find_zone(self.test_name)
        self.assertEqual(self.client.NOTFOUND, result)

        # Create loader and load the zone
        loader = isc.datasrc.ZoneLoader(self.client, self.test_name, self.test_file)
        loader.load()
        # Not really checking content for now, just check the zone exists now
        result, _ = self.client.find_zone(self.test_name)
        self.assertEqual(self.client.SUCCESS, result)

    def test_bad_file(self):
        #self.assertRaises(TypeError, isc.datasrc.ZoneLoader());
        loader = isc.datasrc.ZoneLoader(self.client, self.test_name, "no such file")
        self.assertRaises(isc.datasrc.MasterFileError, loader.load)

    def test_exception(self):
        # Just check if masterfileerror is subclass of datasrc.Error
        self.assertTrue(issubclass(isc.datasrc.MasterFileError,
                                   isc.datasrc.Error))

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
