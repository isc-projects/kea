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

import isc.log
import isc.datasrc
import isc.dns
import unittest
import os
import sys

TESTDATA_PATH = os.environ['GLOBAL_TESTDATA_PATH'] + os.sep

class ClientListTest(unittest.TestCase):
    """
    Test cases for the client lists. Currently, the python wrappers
    contain the ConfigurableClientList only.
    """

    def test_constructors(self):
        """
        Test the constructor. It should accept an RRClass. Check it
        reject invalid inputs.
        """
        isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN())
        isc.datasrc.ConfigurableClientList(isc.dns.RRClass.CH())
        # Not enough arguments
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList)
        # Bad types of arguments
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList, 0)
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList, "IN")
        # Too many arguments
        self.assertRaises(TypeError, isc.datasrc.ConfigurableClientList,
                         isc.dns.RRClass.IN(), isc.dns.RRClass.IN())

    def test_configure(self):
        """
        Test we can configure the client list. This tests if the valid
        ones are acceptend and invalid rejected. We check the changes
        have effect.
        """
        clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN())
        # This should be NOP now
        clist.configure("[]", True)
        # Check the zone is not there yet
        dsrc, finder, exact = clist.find(isc.dns.Name("example.org"))
        self.assertIsNone(dsrc)
        self.assertIsNone(finder)
        self.assertFalse(exact)
        # We can use this type, as it is not loaded dynamically.
        clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.org": "''' + TESTDATA_PATH + '''example.org.zone"
            },
            "cache-enable": true
        }]''', True)
        # Check the zone is there now. Proper tests of find are in other
        # test methods.
        dsrc, finder, exact = clist.find(isc.dns.Name("example.org"))
        self.assertIsNotNone(dsrc)
        self.assertTrue(isinstance(dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(finder)
        self.assertTrue(isinstance(finder, isc.datasrc.ZoneFinder))
        self.assertTrue(exact)
        self.assertRaises(isc.datasrc.Error, clist.configure, '"bad type"',
                          True)
        self.assertRaises(isc.datasrc.Error, clist.configure, '''[{
            "type": "bad type"
        }]''', True)
        self.assertRaises(isc.datasrc.Error, clist.configure, '''[{
            bad JSON,
        }]''', True)
        self.assertRaises(TypeError, clist.configure, [], True)
        self.assertRaises(TypeError, clist.configure, "[]")
        self.assertRaises(TypeError, clist.configure, "[]", "true")

    def test_find(self):
        """
        Test the find accepts the right arguments, some of them can be omitted,
        etc.
        """
        clist = isc.datasrc.ConfigurableClientList(isc.dns.RRClass.IN())
        clist.configure('''[{
            "type": "MasterFiles",
            "params": {
                "example.org": "''' + TESTDATA_PATH + '''example.org.zone"
            },
            "cache-enable": true
        }]''', True)
        dsrc, finder, exact = clist.find(isc.dns.Name("sub.example.org"))
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
        dsrc, finder, exact = clist.find(isc.dns.Name("sub.example.org"),
                                         False)
        self.assertIsNotNone(dsrc)
        self.assertTrue(isinstance(dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(finder)
        self.assertTrue(isinstance(finder, isc.datasrc.ZoneFinder))
        self.assertFalse(exact)
        dsrc, finder, exact = clist.find(isc.dns.Name("sub.example.org"),
                                         True)
        self.assertIsNone(dsrc)
        self.assertIsNone(finder)
        self.assertFalse(exact)
        dsrc, finder, exact = clist.find(isc.dns.Name("sub.example.org"),
                                         False, False)
        self.assertIsNotNone(dsrc)
        self.assertTrue(isinstance(dsrc, isc.datasrc.DataSourceClient))
        self.assertIsNotNone(finder)
        self.assertTrue(isinstance(finder, isc.datasrc.ZoneFinder))
        self.assertFalse(exact)
        dsrc, finder, exact = clist.find(isc.dns.Name("sub.example.org"),
                                         True, False)
        self.assertIsNone(dsrc)
        self.assertIsNone(finder)
        self.assertFalse(exact)
        # Some invalid inputs
        self.assertRaises(TypeError, clist.find, "example.org")
        self.assertRaises(TypeError, clist.find)

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
