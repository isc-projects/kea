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

import unittest
import sys
from pydnspp import *

# A separate exception class raised from some tests to see if it's propagated.
class FakeException(Exception):
    pass

class ZoneCheckerTest(unittest.TestCase):
    def __callback(self, reason, reasons):
        # Issue callback for check_zone().  It simply records the given reason
        # string in the given list.
        reasons.append(reason)

    def test_check(self):
        errors = []
        warns = []

        # A successful case with no warning.
        rrsets = RRsetCollection(b'example.org. 0 SOA . . 0 0 0 0 0\n' +
                                 b'example.org. 0 NS ns.example.org.\n' +
                                 b'ns.example.org. 0 A 192.0.2.1\n',
                                 Name('example.org'), RRClass.IN())
        self.assertTrue(check_zone(Name('example.org'), RRClass.IN(),
                                   rrsets,
                                   (lambda r: self.__callback(r, errors),
                                    lambda r: self.__callback(r, warns))))
        self.assertEqual([], errors)
        self.assertEqual([], warns)

        # Check fails and one additional warning.
        rrsets = RRsetCollection(b'example.org. 0 NS ns.example.org.',
                                 Name('example.org'), RRClass.IN())
        self.assertFalse(check_zone(Name('example.org'), RRClass.IN(), rrsets,
                                    (lambda r: self.__callback(r, errors),
                                     lambda r: self.__callback(r, warns))))
        self.assertEqual(['zone example.org/IN: has 0 SOA records'], errors)
        self.assertEqual(['zone example.org/IN: NS has no address records ' +
                          '(A or AAAA)'], warns)

        # Same RRset collection, suppressing callbacks
        errors = []
        warns = []
        self.assertFalse(check_zone(Name('example.org'), RRClass.IN(), rrsets,
                                    (None, None)))
        self.assertEqual([], errors)
        self.assertEqual([], warns)

    def test_check_badarg(self):
        rrsets = RRsetCollection()
        # Bad types
        self.assertRaises(TypeError, check_zone, 1, RRClass.IN(), rrsets,
                          (None, None))
        self.assertRaises(TypeError, check_zone, Name('example'), 1, rrsets,
                          (None, None))
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          1, (None, None))
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets, 1)

        # Bad callbacks
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets, (None, None, None))
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets, (1, None))
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets, (None, 1))

        # Extra/missing args
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets, (None, None), 1)
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets)
        check_zone(Name('example'), RRClass.IN(), rrsets, (None, None))

    def test_check_callback_fail(self):
        # Let the call raise a Python exception.  It should be propagated to
        # the top level.
        def __bad_callback(reason):
            raise FakeException('error in callback')

        # Using an empty collection, triggering an error callback.
        self.assertRaises(FakeException, check_zone, Name('example.org'),
                          RRClass.IN(), RRsetCollection(),
                          (__bad_callback, None))

        # An unusual case: the callback is expected to return None, but if it
        # returns an actual object it shouldn't cause leak inside the callback.
        class RefChecker:
            pass
        def __callback(reason, checker):
            return checker

        ref_checker = RefChecker()
        orig_refcnt = sys.getrefcount(ref_checker)
        check_zone(Name('example.org'), RRClass.IN(), RRsetCollection(),
                   (lambda r: __callback(r, ref_checker), None))
        self.assertEqual(orig_refcnt, sys.getrefcount(ref_checker))

    def test_check_custom_collection(self):
        # Test if check_zone() works with pure-Python RRsetCollection.

        class FakeRRsetCollection(RRsetCollectionBase):
            # This is the Python-only collection class.  Its find() makes
            # the check pass by default, by returning hardcoded RRsets.
            # If raise_on_find is set to True, find() raises an exception.
            # If find_result is set to something other than 'use_default'
            # (as a string), find() returns that specified value (note that
            # it can be None).

            def __init__(self, raise_on_find=False, find_result='use_default'):
                self.__raise_on_find = raise_on_find
                self.__find_result = find_result

            def find(self, name, rrclass, rrtype):
                if self.__raise_on_find:
                    raise FakeException('find error')
                if self.__find_result is not 'use_default':
                    return self.__find_result
                if rrtype == RRType.SOA():
                    soa = RRset(Name('example'), RRClass.IN(), rrtype,
                                RRTTL(0))
                    soa.add_rdata(Rdata(RRType.SOA(), RRClass.IN(),
                                        '. . 0 0 0 0 0'))
                    return soa
                if rrtype == RRType.NS():
                    ns = RRset(Name('example'), RRClass.IN(), rrtype,
                               RRTTL(0))
                    ns.add_rdata(Rdata(RRType.NS(), RRClass.IN(),
                                       'example.org.'))
                    return ns
                return None

        # A successful case.  Just checking it works in that case.
        rrsets = FakeRRsetCollection()
        self.assertTrue(check_zone(Name('example'), RRClass.IN(), rrsets,
                                   (None, None)))

        # Likewise, normal case but zone check fails.
        rrsets = FakeRRsetCollection(False, None)
        self.assertFalse(check_zone(Name('example'), RRClass.IN(), rrsets,
                                    (None, None)))

        # Our find() returns a bad type of result.
        rrsets = FakeRRsetCollection(False, 1)
        self.assertRaises(TypeError, check_zone, Name('example'), RRClass.IN(),
                          rrsets, (None, None))

        # Our find() returns an empty SOA RRset.  C++ zone checker code
        # throws, which results in IscException.
        rrsets = FakeRRsetCollection(False, RRset(Name('example'),
                                                  RRClass.IN(),
                                                  RRType.SOA(), RRTTL(0)))
        self.assertRaises(IscException, check_zone, Name('example'),
                          RRClass.IN(), rrsets, (None, None))

        # Our find() raises an exception.  That exception is propagated to
        # the top level.
        rrsets = FakeRRsetCollection(True)
        self.assertRaises(FakeException, check_zone, Name('example'),
                          RRClass.IN(), rrsets, (None, None))

if __name__ == '__main__':
    unittest.main()
