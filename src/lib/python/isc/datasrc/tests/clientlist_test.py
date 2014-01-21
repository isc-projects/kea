# Copyright (C) 2012-2013  Internet Systems Consortium.
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

import isc.log
import isc.datasrc
import isc.dns
import unittest
import os
import sys

TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
MAPFILE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep + 'test.mapped'

class ClientListTest(unittest.TestCase):
    """
    Test cases for the client lists. Currently, the python wrappers
    contain the ConfigurableClientList only.
    """

    def tearDown(self):
        # The unit test module could keep internal objects alive longer than
        # we expect.  But cached zone finder and cache client cannot stay
        # longer than the originating client list.  So we explicitly clean
        # them up here.  The ordering is important: clist must be destroyed
        # last.
        self.dsrc = None
        self.finder = None

        # If a test created a ZoneWriter with a mapped memory segment,
        # the writer will hold a reference to the client list which will
        # need the mapfile to exist until it's destroyed.  So we'll make
        # sure to destroy the writer (by resetting it) before removing
        # the mapfile below.
        self.__zone_writer = None
        self.clist = None

        if os.path.exists(MAPFILE_PATH):
            os.unlink(MAPFILE_PATH)

    def test_constructors(self):
        """
        Test the constructor. It should accept an RRClass. Check it
        reject invalid inputs.
        """
        isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        isc.datasrc.ConfigurableClientList(isc.dns.RRClass.CH)
        # Not enough arguments
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList)
        # Bad types of arguments
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList, 0)
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList, "IN")
        # Too many arguments
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList,
                         isc.dns.RRClass.IN, isc.dns.RRClass.IN)

    def configure_helper(self):
        self.clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.com": "''' + TESTDATA_PATH + '''example.com"
            },
            "cache-enable": true
        }]''', True)

    def test_configure(self):
        """
        Test we can configure the client list. This tests if the valid
        ones are accepted and invalid rejected. We check the changes
        have effect.
        """
        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        # This should be NOP now
        self.clist.configure("[]", True)
        # Check the zone is not there yet
        dsrc, finder, exact = self.clist.find(isc.dns.Name("example.com"))
        self.assertIsNone(dsrc)
        self.assertIsNone(finder)
        self.assertFalse(exact)
        # We can use this type, as it is not loaded dynamically.
        self.configure_helper()
        # Check the zone is there now. Proper tests of find are in other
        # test methods.
        self.dsrc, self.finder, exact = \
            self.clist.find(isc.dns.Name("example.com"))
        self.assertIsNotNone(self.dsrc)
        self.assertTrue(isinstance(self.dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(self.finder)
        self.assertTrue(isinstance(self.finder, isc.datasrc.ZoneFinder))
        self.assertTrue(exact)
        self.assertRaises(isc.datasrc.Error, self.clist.configure,
                          '"bad type"', True)
        self.assertRaises(isc.datasrc.Error, self.clist.configure, '''[{
            bad JSON,
        }]''', True)
        self.assertRaises(TypeError, self.clist.configure, [], True)
        self.assertRaises(TypeError, self.clist.configure, "[]")
        self.assertRaises(TypeError, self.clist.configure, "[]", "true")

    def find_helper(self):
        dsrc, finder, exact = self.clist.find(isc.dns.Name("sub.example.com"))
        self.assertIsNotNone(dsrc)
        self.assertTrue(isinstance(dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(finder)
        self.assertTrue(isinstance(finder, isc.datasrc.ZoneFinder))
        # Check the finder holds a reference to the data source
        # Note that one reference is kept in the parameter list
        # of getrefcount
        self.assertEqual(3, sys.getrefcount(dsrc))
        finder = None
        self.assertEqual(2, sys.getrefcount(dsrc))
        # We check an exact match in test_configure already
        self.assertFalse(exact)
        self.dsrc, self.finder, exact = \
            self.clist.find(isc.dns.Name("sub.example.com"), False)
        self.assertIsNotNone(self.dsrc)
        self.assertTrue(isinstance(self.dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(self.finder)
        self.assertTrue(isinstance(self.finder, isc.datasrc.ZoneFinder))
        self.assertFalse(exact)
        self.dsrc, self.finder, exact = \
            self.clist.find(isc.dns.Name("sub.example.com"), True)
        self.assertIsNone(self.dsrc)
        self.assertIsNone(self.finder)
        self.assertFalse(exact)
        self.dsrc, self.finder, exact = \
            self.clist.find(isc.dns.Name("sub.example.com"), False, False)
        self.assertIsNotNone(self.dsrc)
        self.assertTrue(isinstance(self.dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(self.finder)
        self.assertTrue(isinstance(self.finder, isc.datasrc.ZoneFinder))
        self.assertFalse(exact)
        self.dsrc, self.finder, exact = \
            self.clist.find(isc.dns.Name("sub.example.com"), True, False)
        self.assertIsNone(self.dsrc)
        self.assertIsNone(self.finder)
        self.assertFalse(exact)
        # Some invalid inputs
        self.assertRaises(TypeError, self.clist.find, "example.com")
        self.assertRaises(TypeError, self.clist.find)

    def test_get_zone_table_accessor(self):
        """
        Test that we can get the zone table accessor and, thereby,
        the zone table iterator.
        """
        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)

        # null configuration
        self.clist.configure("[]", True)
        self.assertIsNone(self.clist.get_zone_table_accessor(None, True))

        # empty configuration
        self.clist.configure('''[{
            "type": "MasterFiles",
            "params": {},
            "cache-enable": true
        }]''', True)
        # bogus datasrc
        self.assertIsNone(self.clist.get_zone_table_accessor("bogus", True))
        # first datasrc - empty zone table
        table = self.clist.get_zone_table_accessor(None, True)
        self.assertIsNotNone(table)
        iterator = iter(table)
        self.assertIsNotNone(iterator)
        self.assertEqual(0, len(list(iterator)))

        # normal configuration
        self.configure_helper()
        # !use_cache => NotImplemented
        self.assertRaises(isc.datasrc.Error,
                          self.clist.get_zone_table_accessor, None, False)
        # bogus datasrc
        self.assertIsNone(self.clist.get_zone_table_accessor("bogus", True))

        # first datasrc
        table = self.clist.get_zone_table_accessor(None, True)
        self.assertIsNotNone(table)
        zonelist = list(table)
        self.assertEqual(1, len(zonelist))
        self.assertEqual(zonelist[0][1], isc.dns.Name("example.com"))

        # named datasrc
        table = self.clist.get_zone_table_accessor("MasterFiles", True)
        self.assertEqual(zonelist, list(table))

        # longer zone list for non-trivial iteration
        self.clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.org": "''' + TESTDATA_PATH + '''example.org.zone",
                "example.com": "''' + TESTDATA_PATH + '''example.com.zone",
                "example.net": "''' + TESTDATA_PATH + '''example.net.zone",
                "example.biz": "''' + TESTDATA_PATH + '''example.biz.zone",
                "example.edu": "''' + TESTDATA_PATH + '''example.edu.zone"
            },
            "cache-enable": true
        }]''', True)
        zonelist = list(self.clist.get_zone_table_accessor(None, True))
        self.assertEqual(5, len(zonelist))
        self.assertTrue((0, isc.dns.Name("example.net.")) in zonelist)

        # ensure the iterator returns exactly and only the zones we expect
        zonelist = [
            isc.dns.Name("example.org"),
            isc.dns.Name("example.com"),
            isc.dns.Name("example.net"),
            isc.dns.Name("example.biz"),
            isc.dns.Name("example.edu")]
        table = self.clist.get_zone_table_accessor("MasterFiles", True)
        for index, zone in table:
            self.assertTrue(zone in zonelist)
            zonelist.remove(zone)
        self.assertEqual(0, len(zonelist))

    def test_find(self):
        """
        Test the find accepts the right arguments, some of them can be omitted,
        etc.
        """
        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.configure_helper()
        self.find_helper()

    @unittest.skipIf(os.environ['HAVE_SHARED_MEMORY'] != 'yes',
                     'shared memory is not available')
    def test_find_mapped(self):
        """
        Test find on a mapped segment.
        """
        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.com": "''' + TESTDATA_PATH + '''example.com"
            },
            "cache-enable": true,
            "cache-type": "mapped"
        }]''', True)

        map_params = '{"mapped-file": "' + MAPFILE_PATH + '"}'
        self.clist.reset_memory_segment("MasterFiles",
                                        isc.datasrc.ConfigurableClientList.CREATE,
                                        map_params)
        result, self.__zone_writer = \
            self.clist.get_cached_zone_writer(isc.dns.Name("example.com"),
                                              False)
        self.assertEqual(isc.datasrc.ConfigurableClientList.CACHE_STATUS_ZONE_SUCCESS,
                         result)
        err_msg = self.__zone_writer.load()
        self.assertIsNone(err_msg)
        self.__zone_writer.install()
        self.__zone_writer.cleanup()

        self.clist.reset_memory_segment("MasterFiles",
                                        isc.datasrc.ConfigurableClientList.READ_ONLY,
                                        map_params)
        result, self.__zone_writer = \
            self.clist.get_cached_zone_writer(isc.dns.Name("example.com"),
                                              False)
        self.assertEqual(isc.datasrc.ConfigurableClientList.CACHE_STATUS_CACHE_NOT_WRITABLE,
                         result)

        # The segment is still in READ_ONLY mode.
        self.find_helper()

    def test_zone_writer_load_twice(self):
        """
        Test that the zone writer throws when load() is called more than
        once.
        """

        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.configure_helper()

        result, self.__zone_writer = \
            self.clist.get_cached_zone_writer(isc.dns.Name("example.com"),
                                              False)
        self.assertEqual(isc.datasrc.ConfigurableClientList.CACHE_STATUS_ZONE_SUCCESS,
                         result)
        err_msg = self.__zone_writer.load()
        self.assertIsNone(err_msg)
        self.assertRaises(isc.datasrc.Error, self.__zone_writer.load)
        self.__zone_writer.cleanup()

    def test_zone_writer_load_without_raise(self):
        """
        Test that the zone writer does not throw when asked not to.
        """

        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.com": "''' + TESTDATA_PATH + '''example.com-broken.zone"
            },
            "cache-enable": true
        }]''', True)

        result, self.__zone_writer = \
            self.clist.get_cached_zone_writer(isc.dns.Name("example.com"),
                                              True)
        self.assertEqual(isc.datasrc.ConfigurableClientList.CACHE_STATUS_ZONE_SUCCESS,
                         result)
        err_msg = self.__zone_writer.load()
        self.assertIsNotNone(err_msg)
        self.assertTrue('Errors found when validating zone' in err_msg)
        self.__zone_writer.cleanup()

    def test_zone_writer_install_without_load(self):
        """
        Test that the zone writer throws when install() is called
        without calling load() first.
        """

        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.configure_helper()

        result, self.__zone_writer = \
            self.clist.get_cached_zone_writer(isc.dns.Name("example.com"),
                                              False)
        self.assertEqual(isc.datasrc.ConfigurableClientList.CACHE_STATUS_ZONE_SUCCESS,
                         result)
        self.assertRaises(isc.datasrc.Error, self.__zone_writer.install)
        self.__zone_writer.cleanup()

    def test_get_status(self):
        """
        Test getting status of various data sources.
        """

        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)

        status = self.clist.get_status()
        self.assertIsNotNone(status)
        self.assertTrue(isinstance(status, list))
        self.assertEqual(0, len(status))

        self.configure_helper()

        status = self.clist.get_status()
        self.assertIsNotNone(status)
        self.assertTrue(isinstance(status, list))
        self.assertEqual(1, len(status))
        self.assertTrue(isinstance(status[0], tuple))
        self.assertTupleEqual(('MasterFiles', 'local',
                               isc.datasrc.ConfigurableClientList.SEGMENT_INUSE),
                              status[0])

    @unittest.skipIf(os.environ['HAVE_SHARED_MEMORY'] != 'yes',
                     'shared memory is not available')
    def test_get_status_unused(self):
        """
        Test getting status when segment type is mapped, but the cache
        is disabled.
        """

        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.clist.configure('''[{
            "type": "sqlite3",
            "params": {
                "database_file": "''' + TESTDATA_PATH + '''example.com.sqlite3"
            },
            "cache-zones" : ["example.com"],
            "cache-type": "mapped",
            "cache-enable": false
        }]''', True)

        status = self.clist.get_status()
        self.assertIsNotNone(status)
        self.assertTrue(isinstance(status, list))
        self.assertEqual(1, len(status))
        self.assertTrue(isinstance(status[0], tuple))
        self.assertTupleEqual(('sqlite3', None,
                               isc.datasrc.ConfigurableClientList.SEGMENT_UNUSED),
                              status[0])

    @unittest.skipIf(os.environ['HAVE_SHARED_MEMORY'] != 'yes',
                     'shared memory is not available')
    def test_get_status_waiting(self):
        """
        Test getting status when segment type is mapped and it has not
        been reset yet.
        """

        self.clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN)
        self.clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.com": "''' + TESTDATA_PATH + '''example.com"
            },
            "cache-enable": true,
            "cache-type": "mapped"
        }]''', True)

        status = self.clist.get_status()
        self.assertIsNotNone(status)
        self.assertTrue(isinstance(status, list))
        self.assertEqual(1, len(status))
        self.assertTrue(isinstance(status[0], tuple))
        self.assertTupleEqual(('MasterFiles', 'mapped',
                               isc.datasrc.ConfigurableClientList.SEGMENT_WAITING),
                              status[0])

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
