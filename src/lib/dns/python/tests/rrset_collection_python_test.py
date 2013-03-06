# Copyright (C) 2013  Internet Systems Consortium.
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

import os
import unittest
from pydnspp import *

# This should refer to the testdata directory for the C++ tests.
TESTDATA_DIR = os.environ["TESTDATA_PATH"].split(':')[0]

class RRsetCollectionBaseTest(unittest.TestCase):
    def test_init(self):
        # direct instantiation of the base class is prohibited.
        self.assertRaises(TypeError, RRsetCollectionBase)

class RRsetCollectionTest(unittest.TestCase):
    def test_init_fail(self):
        # check various failure cases on construction (other normal cases are
        # covered as part of other tests)

        # bad args
        self.assertRaises(TypeError, RRsetCollection, 1)
        self.assertRaises(TypeError, RRsetCollection, # extra arg
                          b'example. 0 A 192.0.2.1',
                          Name('example'), RRClass.IN, 1)
        self.assertRaises(TypeError, RRsetCollection, # incorrect order
                          b'example. 0 A 192.0.2.1', RRClass.IN,
                          Name('example'))

        # constructor will result in C++ exception.
        self.assertRaises(IscException, RRsetCollection,
                          TESTDATA_DIR + '/no_such_file', Name('example.org'),
                          RRClass.IN)

    def check_find_result(self, rrsets):
        # Commonly used check pattern
        found = rrsets.find(Name('www.example.org'), RRClass.IN, RRType.A)
        self.assertNotEqual(None, found)
        self.assertEqual(Name('www.example.org'), found.get_name())
        self.assertEqual(RRClass.IN, found.get_class())
        self.assertEqual(RRType.A, found.get_type())
        self.assertEqual('192.0.2.1', found.get_rdata()[0].to_text())

    def test_find(self):
        # Checking the underlying find() is called as intended, both for
        # success and failure cases, and with two different constructors.
        rrsets = RRsetCollection(TESTDATA_DIR + '/example.org',
                                 Name('example.org'), RRClass.IN)
        self.check_find_result(rrsets)
        self.assertEqual(None, rrsets.find(Name('example.org'), RRClass.IN,
                                           RRType.A))

        rrsets = RRsetCollection(b'www.example.org. 3600 IN A 192.0.2.1',
                                 Name('example.org'), RRClass.IN)
        self.check_find_result(rrsets)
        self.assertEqual(None, rrsets.find(Name('example.org'), RRClass.IN,
                                           RRType.A))

    def test_find_badargs(self):
        rrsets = RRsetCollection()

        # Check bad arguments: bad types
        self.assertRaises(TypeError, rrsets.find, 1, RRClass.IN, RRType.A)
        self.assertRaises(TypeError, rrsets.find, Name('example'), 1,
                          RRType.A)
        self.assertRaises(TypeError, rrsets.find, Name('example'), 1,
                          RRType.A)
        self.assertRaises(TypeError, rrsets.find, Name('example'),
                          RRClass.IN, 1)
        self.assertRaises(TypeError, rrsets.find, Name('example'), RRType.A,
                          RRClass.IN)

        # Check bad arguments: too many/few arguments
        self.assertRaises(TypeError, rrsets.find, Name('example'),
                          RRClass.IN, RRType.A, 0)
        self.assertRaises(TypeError, rrsets.find, Name('example'),
                          RRClass.IN)

    def test_add_remove_rrset(self):
        name = Name('www.example.org')
        rrclass = RRClass.IN
        rrtype = RRType.A

        # Create a collection with no RRsets
        rrsets = RRsetCollection()
        self.assertEqual(None, rrsets.find(name, rrclass, rrtype))

        # add the record, then it should be found
        rrset = RRset(name, rrclass, rrtype, RRTTL(60))
        rrset.add_rdata(Rdata(rrtype, rrclass, '192.0.2.1'))
        self.assertEqual(None, rrsets.add_rrset(rrset))
        self.check_find_result(rrsets)

        # duplicate add is (at least currently) rejected
        self.assertRaises(ValueError, rrsets.add_rrset, rrset)

        # remove it, then we cannot find it any more.
        self.assertTrue(rrsets.remove_rrset(name, rrclass, rrtype))
        self.assertEqual(None, rrsets.find(name, rrclass, rrtype))

        # duplicate remove (specified RRset doesn't exist) reulsts in False
        self.assertFalse(rrsets.remove_rrset(name, rrclass, rrtype))

        # Checking bad args
        self.assertRaises(TypeError, rrsets.add_rrset, 1)
        self.assertRaises(TypeError, rrsets.add_rrset, rrset, 1)
        self.assertRaises(TypeError, rrsets.add_rrset)

        self.assertRaises(TypeError, rrsets.remove_rrset, 1, rrclass, rrtype)
        self.assertRaises(TypeError, rrsets.remove_rrset, name, 1, rrtype)
        self.assertRaises(TypeError, rrsets.remove_rrset, name, rrclass, 1)
        self.assertRaises(TypeError, rrsets.remove_rrset, name, rrtype,
                          rrclass)
        self.assertRaises(TypeError, rrsets.remove_rrset, name, rrclass)
        self.assertRaises(TypeError, rrsets.remove_rrset, name, rrclass,
                          rrtype, 1)

    def test_empty_class(self):
        # A user defined collection class shouldn't cause disruption.
        class EmptyRRsetCollection(RRsetCollectionBase):
            def __init__(self):
                pass
        rrsets = EmptyRRsetCollection()
        self.assertRaises(TypeError, rrsets.find, Name('www.example.org'),
                          RRClass.IN, RRType.A)

if __name__ == '__main__':
    unittest.main()
