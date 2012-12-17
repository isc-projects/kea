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
import sys

# Constants and common data used in tests

TESTDATA_PATH = os.environ['TESTDATA_PATH']
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH']

ZONE_FILE = TESTDATA_PATH + '/example.com'
STATIC_ZONE_FILE = '../../../../datasrc/static.zone'
SOURCE_DB_FILE = TESTDATA_PATH + '/example.com.source.sqlite3'
ORIG_DB_FILE = TESTDATA_PATH + '/example.com.sqlite3'
DB_FILE = TESTDATA_WRITE_PATH + '/zoneloadertest.sqlite3'
DB_CLIENT_CONFIG = '{ "database_file": "' + DB_FILE + '" }'
DB_SOURCE_CLIENT_CONFIG = '{ "database_file": "' + SOURCE_DB_FILE + '" }'

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
        shutil.copyfile(ORIG_DB_FILE, DB_FILE)
        # Some tests set source client; if so, check refcount in
        # tearDown, since most tests don't, set it to None by default.
        self.source_client = None
        self.loader = None
        self.assertEqual(2, sys.getrefcount(self.test_name))
        self.assertEqual(2, sys.getrefcount(self.client))

    def tearDown(self):
        # We can only create 1 loader at a time (it locks the db), and it
        # may not be destroyed immediately if there is an exception in a
        # test. So the tests that do create one should put it in self, and
        # we make sure to invalidate it here.

        # We can also use this to check reference counts; if a loader
        # exists, the client and source client (if any) should have
        # an increased reference count (but the name should not, this
        # is only used in the initializer)
        if self.loader is not None:
            self.assertEqual(2, sys.getrefcount(self.test_name))
            self.assertEqual(3, sys.getrefcount(self.client))
            if (self.source_client is not None):
                self.assertEqual(3, sys.getrefcount(self.source_client))
        self.loader = None

        # Now that the loader has been destroyed, the refcounts
        # of its arguments should be back to their originals
        self.assertEqual(2, sys.getrefcount(self.test_name))
        self.assertEqual(2, sys.getrefcount(self.client))
        if (self.source_client is not None):
            self.assertEqual(2, sys.getrefcount(self.source_client))

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
        Check that the given SOA RR exists and matches the expected string
        """
        result, finder = self.client.find_zone(self.test_name)
        self.assertEqual(self.client.SUCCESS, result)
        result, rrset, _ = finder.find(self.test_name, isc.dns.RRType.SOA())
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(soa_txt, rrset.to_text())

    def check_load(self):
        self.check_zone_soa(ORIG_SOA_TXT)
        self.loader.load()
        self.check_zone_soa(NEW_SOA_TXT)

        # And after that, it should throw
        self.assertRaises(isc.dns.InvalidOperation, self.loader.load)

    def test_load_from_file(self):
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             self.test_file)
        self.check_load()

    def test_load_from_client(self):
        self.source_client = isc.datasrc.DataSourceClient('sqlite3',
                                    DB_SOURCE_CLIENT_CONFIG)
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             self.source_client)
        self.check_load()

    def Xtest_load_from_file_checkrefs(self):
        # A test to see the refcount is increased properly
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             self.test_file)
        # Explicitely delete the objects here, so we trigger bad reference
        # counting (best effort, if there are leaked references for these
        # objects themselves, it still won't fail)
        self.client = None
        self.client = None
        self.test_name = None
        self.test_file = None
        self.loader.load()

    def Xtest_load_from_client_checkrefs(self):
        # A test to see the refcount is increased properly
        source_client = isc.datasrc.DataSourceClient('sqlite3',
                                                     DB_SOURCE_CLIENT_CONFIG)
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             source_client)
        # Explicitely delete the objects here, so we trigger bad reference
        # counting (best effort, if there are leaked references for these
        # objects themselves, it still won't fail)
        self.client = None
        self.test_name = None
        source_client = None
        self.loader.load()

    def check_load_incremental(self):
        # New zone has 8 RRs
        # After 5, it should return False
        self.assertFalse(self.loader.load_incremental(5))
        # New zone should not have been loaded yet
        self.check_zone_soa(ORIG_SOA_TXT)

        # After 5 more, it should return True (only having read 3)
        self.assertTrue(self.loader.load_incremental(5))
        # New zone should now be loaded
        self.check_zone_soa(NEW_SOA_TXT)

        # And after that, it should throw
        self.assertRaises(isc.dns.InvalidOperation,
                          self.loader.load_incremental, 5)

    def test_load_from_file_incremental(self):
        # Create loader and load the zone
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             self.test_file)
        self.check_load_incremental()

    def test_load_from_client_incremental(self):
        self.source_client = isc.datasrc.DataSourceClient('sqlite3',
                                            DB_SOURCE_CLIENT_CONFIG)
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             self.source_client)
        self.check_load_incremental()

    def test_bad_file(self):
        self.check_zone_soa(ORIG_SOA_TXT)
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             'no such file')
        self.assertRaises(isc.datasrc.MasterFileError, self.loader.load)
        self.check_zone_soa(ORIG_SOA_TXT)

    def test_bad_file_incremental(self):
        self.check_zone_soa(ORIG_SOA_TXT)
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             'no such file')
        self.assertRaises(isc.datasrc.MasterFileError,
                          self.loader.load_incremental, 1)
        self.check_zone_soa(ORIG_SOA_TXT)

    def test_no_such_zone_in_target(self):
        self.assertRaises(isc.datasrc.Error, isc.datasrc.ZoneLoader,
                          self.client, isc.dns.Name("unknownzone"),
                          self.test_file)

    def test_no_such_zone_in_source(self):
        # Reuse a zone that exists in target but not in source
        zone_name = isc.dns.Name("sql1.example.com")
        self.source_client = isc.datasrc.DataSourceClient('sqlite3',
                                            DB_SOURCE_CLIENT_CONFIG)

        # make sure the zone exists in the target
        found, _ = self.client.find_zone(zone_name)
        self.assertEqual(self.client.SUCCESS, found)
        # And that it does not in the source
        found, _ = self.source_client.find_zone(zone_name)
        self.assertNotEqual(self.source_client.SUCCESS, found)

        self.assertRaises(isc.datasrc.Error, isc.datasrc.ZoneLoader,
                          self.client, zone_name, self.source_client)

    def test_no_ds_load_support(self):
        # This may change in the future, but atm, the in-mem ds does
        # not support the API the zone loader uses (it has direct load calls)
        inmem_client = isc.datasrc.DataSourceClient('memory',
                                                    '{ "type": "memory" }');
        self.assertRaises(isc.datasrc.NotImplemented,
                          isc.datasrc.ZoneLoader,
                          inmem_client, self.test_name, self.test_file)

    def test_wrong_class_from_file(self):
        # If the file has wrong class, it is not detected until load time
        self.loader = isc.datasrc.ZoneLoader(self.client, self.test_name,
                                             self.test_file + '.ch')
        self.assertRaises(isc.datasrc.MasterFileError, self.loader.load)

    def test_wrong_class_from_client(self):
        # For ds->ds loading, wrong class is detected upon construction
        # Need a bit of the extended setup for CH source client
        clientlist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.CH())
        clientlist.configure('[ { "type": "static", "params": "' +
                             STATIC_ZONE_FILE +'" } ]', False)
        self.source_client, _, _ = clientlist.find(isc.dns.Name("bind."),
                                                   False, False)
        self.assertRaises(isc.dns.InvalidParameter, isc.datasrc.ZoneLoader,
                          self.client, isc.dns.Name("bind."),
                          self.source_client)

    def test_exception(self):
        # Just check if masterfileerror is subclass of datasrc.Error
        self.assertTrue(issubclass(isc.datasrc.MasterFileError,
                                   isc.datasrc.Error))

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
