# Copyright (C) 2011  Internet Systems Consortium.
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
from isc.datasrc import ZoneFinder, ZoneJournalReader
from isc.dns import *
from isc.testutils.rrset_utils import rrsets_equal
import unittest
import sqlite3
import os
import shutil
import sys
import json

TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep

READ_ZONE_DB_FILE = TESTDATA_PATH + "example.com.sqlite3"
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "rwtest.sqlite3.copied"

READ_ZONE_DB_CONFIG = "{ \"database_file\": \"" + READ_ZONE_DB_FILE + "\" }"
WRITE_ZONE_DB_CONFIG = "{ \"database_file\": \"" + WRITE_ZONE_DB_FILE + "\"}"

def add_rrset(rrset_list, name, rrclass, rrtype, ttl, rdatas):
    rrset_to_add = isc.dns.RRset(name, rrclass, rrtype, ttl)
    if rdatas is not None:
        for rdata in rdatas:
            rrset_to_add.add_rdata(isc.dns.Rdata(rrtype, rrclass, rdata))
    rrset_list.append(rrset_to_add)

# returns true if rrset is in expected_rrsets
# will remove the rrset from expected_rrsets if found
def check_for_rrset(expected_rrsets, rrset):
    for cur_rrset in expected_rrsets[:]:
        if rrsets_equal(cur_rrset, rrset):
            expected_rrsets.remove(cur_rrset)
            return True
    return False

def create_soa(serial):
    soa = RRset(Name('example.org'), RRClass.IN(), RRType.SOA(), RRTTL(3600))
    soa.add_rdata(Rdata(RRType.SOA(), RRClass.IN(),
                        'ns1.example.org. admin.example.org. ' +
                        str(serial) + ' 3600 1800 2419200 7200'))
    return soa

def test_findall_common(self, tested):
    """
    Common part of the find_all test. It tests a find_all method on the passed
    object.
    """
    # Some "failure" responses
    result, rrset, _ = tested.find_all(isc.dns.Name("www.sql1.example.com"),
                                       ZoneFinder.FIND_DEFAULT)
    self.assertEqual(ZoneFinder.DELEGATION, result)
    expected = RRset(Name('sql1.example.com.'), RRClass.IN(), RRType.NS(),
                     RRTTL(3600))
    expected.add_rdata(Rdata(RRType.NS(), RRClass.IN(),
                             'dns01.example.com.'))
    expected.add_rdata(Rdata(RRType.NS(), RRClass.IN(),
                             'dns02.example.com.'))
    expected.add_rdata(Rdata(RRType.NS(), RRClass.IN(),
                             'dns03.example.com.'))
    self.assertTrue(rrsets_equal(expected, rrset))

    result, rrset, _ = tested.find_all(isc.dns.Name("nxdomain.example.com"),
                                       ZoneFinder.FIND_DEFAULT)
    self.assertEqual(ZoneFinder.NXDOMAIN, result)
    self.assertIsNone(None, rrset)

    # A success. It should return the list now.
    # This also tests we can ommit the options parameter
    result, rrsets, _ = tested.find_all(isc.dns.Name("mix.example.com."))
    self.assertEqual(ZoneFinder.SUCCESS, result)
    self.assertEqual(2, len(rrsets))
    rrsets.sort(key=lambda rrset: rrset.get_type().to_text())
    expected = [
        RRset(Name('mix.example.com.'), RRClass.IN(), RRType.A(),
              RRTTL(3600)),
        RRset(Name('mix.example.com.'), RRClass.IN(), RRType.AAAA(),
              RRTTL(3600))
    ]
    expected[0].add_rdata(Rdata(RRType.A(), RRClass.IN(), "192.0.2.1"))
    expected[0].add_rdata(Rdata(RRType.A(), RRClass.IN(), "192.0.2.2"))
    expected[1].add_rdata(Rdata(RRType.AAAA(), RRClass.IN(),
                                "2001:db8::1"))
    expected[1].add_rdata(Rdata(RRType.AAAA(), RRClass.IN(),
                                "2001:db8::2"))
    for (rrset, exp) in zip(rrsets, expected):
        self.assertTrue(rrsets_equal(exp, rrset))

    # Check the reference counts on them. The getrefcount returns one more,
    # as for the reference in its own parameter - see its docs.

    # Two - one for the variable, one for parameter
    self.assertEqual(2, sys.getrefcount(rrsets))
    for rrset in rrsets:
        # 3 - one as the element of list, one for the rrset variable
        # and one for the parameter.
        self.assertEqual(3, sys.getrefcount(rrset))

class DataSrcClient(unittest.TestCase):

    def test_(self):
        # can't construct directly
        self.assertRaises(TypeError, isc.datasrc.ZoneIterator)

        self.assertRaises(TypeError, isc.datasrc.DataSourceClient, 1, "{}")
        self.assertRaises(TypeError, isc.datasrc.DataSourceClient, "sqlite3", 1)
        self.assertRaises(isc.datasrc.Error,
                          isc.datasrc.DataSourceClient, "foo", "{}")
        self.assertRaises(isc.datasrc.Error,
                          isc.datasrc.DataSourceClient, "sqlite3", "")
        self.assertRaises(isc.datasrc.Error,
                          isc.datasrc.DataSourceClient, "sqlite3", "{}")
        self.assertRaises(isc.datasrc.Error,
                          isc.datasrc.DataSourceClient, "sqlite3",
                          "{ \"foo\": 1 }")
        self.assertRaises(isc.datasrc.Error,
                          isc.datasrc.DataSourceClient, "memory",
                          "{ \"foo\": 1 }")

    def test_iterate(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)

        # for RRSIGS, the TTL's are currently modified. This test should
        # start failing when we fix that.
        rrs = dsc.get_iterator(isc.dns.Name("sql1.example.com."), True)

        # we do not know the order in which they are returned by the iterator
        # but we do want to check them, so we put all records into one list
        # sort it (doesn't matter which way it is sorted, as long as it is
        # sorted)

        # RRset is (atm) an unorderable type, and within an rrset, the
        # rdatas and rrsigs may also be in random order. In theory the
        # rrsets themselves can be returned in any order.
        #
        # So we create a second list with all rrsets we expect, and for each
        # rrset we get from the iterator, see if it is in that list, and
        # remove it.
        #
        # When the iterator is empty, we check no rrsets are left in the
        # list of expected ones
        expected_rrset_list = []

        name = isc.dns.Name("sql1.example.com")
        rrclass = isc.dns.RRClass.IN()
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.DNSKEY(), isc.dns.RRTTL(3600),
                  [
                     "256 3 5 AwEAAdYdRhBAEY67R/8G1N5AjGF6asIiNh/pNGeQ8xDQP13J"+
                     "N2lo+sNqWcmpYNhuVqRbLB+mamsU1XcCICSBvAlSmfz/ZUdafX23knAr"+
                     "TlALxMmspcfdpqun3Yr3YYnztuj06rV7RqmveYckWvAUXVYMSMQZfJ30"+
                     "5fs0dE/xLztL/CzZ"
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.DNSKEY(), isc.dns.RRTTL(3600),
                  [
                     "257 3 5 AwEAAbaKDSa9XEFTsjSYpUTHRotTS9Tz3krfDucugW5UokGQ"+
                     "KC26QlyHXlPTZkC+aRFUs/dicJX2kopndLcnlNAPWiKnKtrsFSCnIJDB"+
                     "ZIyvcKq+9RXmV3HK3bUdHnQZ88IZWBRmWKfZ6wnzHo53kdYKAemTErkz"+
                     "taX3lRRPLYWpxRcDPEjysXT3Lh0vfL5D+CIO1yKw/q7C+v6+/kYAxc2l"+
                     "fbNE3HpklSuF+dyX4nXxWgzbcFuLz5Bwfq6ZJ9RYe/kNkA0uMWNa1KkG"+
                     "eRh8gg22kgD/KT5hPTnpezUWLvoY5Qc7IB3T0y4n2JIwiF2ZrZYVrWgD"+
                     "jRWAzGsxJiJyjd6w2k0="
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.NS(), isc.dns.RRTTL(3600),
                  [
                    "dns01.example.com."
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.NS(), isc.dns.RRTTL(3600),
                  [
                    "dns02.example.com."
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.NS(), isc.dns.RRTTL(3600),
                  [
                    "dns03.example.com."
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.NSEC(), isc.dns.RRTTL(7200),
                  [
                     "www.sql1.example.com. NS SOA RRSIG NSEC DNSKEY"
                  ])
        # For RRSIGS, we can't add the fake data through the API, so we
        # simply pass no rdata at all (which is skipped by the check later)
        
        # Since we passed separate_rrs = True to get_iterator, we get several
        # sets of RRSIGs, one for each TTL
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(3600), None)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(3600), None)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(3600), None)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(3600), None)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(7200), None)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.SOA(), isc.dns.RRTTL(3600),
                  [
                     "master.example.com. admin.example.com. 678 3600 1800 2419200 7200"
                  ])
        name = isc.dns.Name("www.sql1.example.com.")
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.A(), isc.dns.RRTTL(3600),
                  [
                     "192.0.2.100"
                  ])
        name = isc.dns.Name("www.sql1.example.com.")
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.NSEC(), isc.dns.RRTTL(7200),
                  [
                     "sql1.example.com. A RRSIG NSEC"
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(3600), None)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(7200), None)

        # rrs is an iterator, but also has direct get_next_rrset(), use
        # the latter one here
        rrset_to_check = rrs.get_next_rrset()
        while (rrset_to_check != None):
            self.assertTrue(check_for_rrset(expected_rrset_list,
                                            rrset_to_check),
                            "Unexpected rrset returned by iterator:\n" +
                            rrset_to_check.to_text())
            rrset_to_check = rrs.get_next_rrset()

        # Now check there are none left
        self.assertEqual(0, len(expected_rrset_list),
                         "RRset(s) not returned by iterator: " +
                         str([rrset.get_name().to_text() + '/' +
                              rrset.get_type().to_text() for rrset in
                              expected_rrset_list ]
                        ))

        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        # Without the separate_rrs argument, it should return 55 RRsets
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)
        rrets = dsc.get_iterator(isc.dns.Name("example.com"))
        # there are more than 80 RRs in this zone... let's just count them
        # (already did a full check of the smaller zone above)
        # There are 40 non-RRSIG RRsets and 32 dinstinct RRSIGs.
        self.assertEqual(72, len(list(rrets)))

        # same test, but now with explicit False argument for separate_rrs
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)
        rrets = dsc.get_iterator(isc.dns.Name("example.com"), False)
        # there are more than 80 RRs in this zone... let's just count them
        # (already did a full check of the smaller zone above)
        self.assertEqual(72, len(list(rrets)))

        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)
        rrets = dsc.get_iterator(isc.dns.Name("example.com"), True)
        # there are more than 80 RRs in this zone... let's just count them
        # (already did a full check of the smaller zone above)
        self.assertEqual(84, len(list(rrets)))
        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        self.assertRaises(TypeError, dsc.get_iterator, "asdf")

    def test_iterator_soa(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)
        iterator = dsc.get_iterator(isc.dns.Name("sql1.example.com."))
        expected_soa = isc.dns.RRset(isc.dns.Name("sql1.example.com."),
                                     isc.dns.RRClass.IN(),
                                     isc.dns.RRType.SOA(),
                                     isc.dns.RRTTL(3600))
        expected_soa.add_rdata(isc.dns.Rdata(isc.dns.RRType.SOA(),
                                             isc.dns.RRClass.IN(),
                                             "master.example.com. " +
                                             "admin.example.com. 678 " +
                                             "3600 1800 2419200 7200"))
        self.assertTrue(rrsets_equal(expected_soa, iterator.get_soa()))

    def test_construct(self):
        # can't construct directly
        self.assertRaises(TypeError, isc.datasrc.ZoneFinder)

    def test_findoptions(self):
        '''A simple test to confirm no option is specified by default.

        '''
        self.assertFalse(ZoneFinder.FIND_DEFAULT & ZoneFinder.FIND_GLUE_OK)
        self.assertFalse(ZoneFinder.FIND_DEFAULT & ZoneFinder.FIND_DNSSEC)
        self.assertFalse(ZoneFinder.FIND_DEFAULT & ZoneFinder.NO_WILDCARD)

    def test_findresults(self):
        '''A simple test to confirm result codes are (defined and) different
        for some combinations.

        '''
        self.assertNotEqual(ZoneFinder.SUCCESS, ZoneFinder.DELEGATION)
        self.assertNotEqual(ZoneFinder.DELEGATION, ZoneFinder.NXDOMAIN)
        self.assertNotEqual(ZoneFinder.NXDOMAIN, ZoneFinder.NXRRSET)
        self.assertNotEqual(ZoneFinder.NXRRSET, ZoneFinder.CNAME)
        self.assertNotEqual(ZoneFinder.CNAME, ZoneFinder.DNAME)

    def test_findresultflags(self):
        '''A simple test just confirming the flags are all different.'''
        self.assertNotEqual(ZoneFinder.RESULT_WILDCARD,
                            ZoneFinder.RESULT_NSEC_SIGNED)
        self.assertNotEqual(ZoneFinder.RESULT_NSEC_SIGNED,
                            ZoneFinder.RESULT_NSEC3_SIGNED)
        self.assertNotEqual(ZoneFinder.RESULT_NSEC3_SIGNED,
                            ZoneFinder.RESULT_WILDCARD)

    def test_findall(self):
        """
        A test for the find_all method.
        """
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)
        result, finder = dsc.find_zone(isc.dns.Name("example.com"))

        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())

        test_findall_common(self, finder)

    def test_find(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)

        result, finder = dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())

        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        # Check the optional parameters are optional
        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A())
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        result, rrset, _ = finder.find(isc.dns.Name("www.sql1.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.DELEGATION, result)
        self.assertEqual("sql1.example.com. 3600 IN NS dns01.example.com.\n" +
                         "sql1.example.com. 3600 IN NS dns02.example.com.\n" +
                         "sql1.example.com. 3600 IN NS dns03.example.com.\n",
                         rrset.to_text())

        result, rrset, _ = finder.find(isc.dns.Name("doesnotexist.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)


        self.assertRaises(isc.datasrc.OutOfZone, finder.find,
                          isc.dns.Name("www.some.other.domain"),
                          isc.dns.RRType.A())

        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.TXT(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.NXRRSET, result)
        self.assertEqual(None, rrset)

        result, rrset, _ = finder.find(isc.dns.Name("cname-ext.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.CNAME, result)
        self.assertEqual(
            "cname-ext.example.com. 3600 IN CNAME www.sql1.example.com.\n",
            rrset.to_text())

        result, rrset, flags = \
            finder.find(isc.dns.Name("foo.wild.example.com"),
                        isc.dns.RRType.A(), finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(finder.RESULT_WILDCARD, flags)
        self.assertEqual("foo.wild.example.com. 3600 IN A 192.0.2.255\n",
                         rrset.to_text())

        result, rrset, _ = finder.find(isc.dns.Name("foo.wild.example.com"),
                                       isc.dns.RRType.TXT(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.NXRRSET, result)
        self.assertTrue(finder.RESULT_WILDCARD, flags)
        self.assertEqual(None, rrset)

        self.assertRaises(TypeError, finder.find,
                          "foo",
                          isc.dns.RRType.A(),
                          finder.FIND_DEFAULT)
        self.assertRaises(TypeError, finder.find,
                          isc.dns.Name("cname-ext.example.com"),
                          "foo",
                          finder.FIND_DEFAULT)
        self.assertRaises(TypeError, finder.find,
                          isc.dns.Name("cname-ext.example.com"),
                          isc.dns.RRType.A(),
                          "foo")

class DataSrcUpdater(unittest.TestCase):

    def setUp(self):
        # Make a fresh copy of the writable database with all original content
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)

    def test_findall(self):
        """
        The same test as DataSrcClient.test_findall, but on an updater
        instead of a finder.
        """
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        updater = dsc.get_updater(isc.dns.Name("example.com"), False)

        test_findall_common(self, updater)

    def test_construct(self):
        # can't construct directly
        self.assertRaises(TypeError, isc.datasrc.ZoneUpdater)

    def test_update_finder(self):
        # Check basic behavior of updater's finder
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        updater = dsc.get_updater(isc.dns.Name("example.com"), False)
        result, rrset, _ = updater.find(isc.dns.Name("www.example.com"),
                                        isc.dns.RRType.A(),
                                        ZoneFinder.FIND_DEFAULT)
        self.assertEqual(ZoneFinder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        # Omit optional parameters
        result, rrset, _ = updater.find(isc.dns.Name("www.example.com"),
                                        isc.dns.RRType.A())
        self.assertEqual(ZoneFinder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

    def test_update_delete_commit(self):

        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)

        # first make sure, through a separate finder, that some record exists
        result, finder = dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())

        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        rrset_to_delete = rrset;
        rrset_to_delete.remove_rrsig()

        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        updater.delete_rrset(rrset_to_delete)

        # The record should be gone in the updater, but not in the original
        # finder (since we have not committed)
        result, rrset, _ = updater.find(isc.dns.Name("www.example.com"),
                                        isc.dns.RRType.A(),
                                        finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        updater.commit()
        # second commit should raise exception
        self.assertRaises(isc.datasrc.Error, updater.commit)

        # the record should be gone now in the 'real' finder as well
        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        # now add it again
        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        updater.add_rrset(rrset_to_delete)
        updater.commit()

        # second commit should throw
        self.assertRaises(isc.datasrc.Error, updater.commit)

        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

    def test_two_modules(self):
        # load two modules, and check if they don't interfere
        mem_cfg = { "type": "memory", "class": "IN", "zones": [] };
        dsc_mem = isc.datasrc.DataSourceClient("memory", json.dumps(mem_cfg))
        dsc_sql = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)

        # check if exceptions are working
        self.assertRaises(isc.datasrc.Error, isc.datasrc.DataSourceClient,
                          "memory", "{}")
        self.assertRaises(isc.datasrc.Error, isc.datasrc.DataSourceClient,
                          "sqlite3", "{}")

        # see if a lookup succeeds in sqlite3 ds
        result, finder = dsc_sql.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())
        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        # see if a lookup fails in mem ds
        result, finder = dsc_mem.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.NXDOMAIN, result)


    def test_update_delete_abort(self):
        # we don't do enything with this one, just making sure loading two
        # datasources
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)

        # first make sure, through a separate finder, that some record exists
        result, finder = dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())

        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        rrset_to_delete = rrset;
        rrset_to_delete.remove_rrsig()

        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        updater.delete_rrset(rrset_to_delete)

        # The record should be gone in the updater, but not in the original
        # finder (since we have not committed)
        result, rrset, _ = updater.find(isc.dns.Name("www.example.com"),
                                        isc.dns.RRType.A(),
                                        finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        # destroy the updater, which should make it roll back
        updater = None

        # the record should still be available in the 'real' finder as well
        result, rrset, _ = finder.find(isc.dns.Name("www.example.com"),
                                       isc.dns.RRType.A(),
                                       finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

    def test_update_for_no_zone(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        self.assertEqual(None,
                         dsc.get_updater(isc.dns.Name("notexistent.example"),
                                         True))

    def test_client_reference(self):
        # Temporarily create various objects using factory methods of the
        # client.  The created objects won't be stored anywhere and
        # immediately released.  The creation shouldn't affect the reference
        # to the base client.
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        orig_ref = sys.getrefcount(dsc)

        dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(orig_ref, sys.getrefcount(dsc))

        dsc.get_iterator(isc.dns.Name("example.com."))
        self.assertEqual(orig_ref, sys.getrefcount(dsc))

        dsc.get_updater(isc.dns.Name("example.com"), True)
        self.assertEqual(orig_ref, sys.getrefcount(dsc))

    def test_iterate_over_empty_zone(self):
        # empty the test zone first
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        updater.commit()

        # Check the iterator behavior for the empty zone.
        iterator = dsc.get_iterator(isc.dns.Name("example.com."))
        self.assertEqual(None, iterator.get_soa())
        self.assertEqual(None, iterator.get_next_rrset())

class JournalWrite(unittest.TestCase):
    def setUp(self):
        # Make a fresh copy of the writable database with all original content
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)
        self.dsc = isc.datasrc.DataSourceClient("sqlite3",
                                                WRITE_ZONE_DB_CONFIG)
        self.updater = self.dsc.get_updater(Name("example.com"), False, True)

    def tearDown(self):
        self.dsc = None
        self.updater = None

    def check_journal(self, expected_list):
        # This assumes sqlite3 DB and directly fetches stored data from
        # the DB file.  It should be generalized using ZoneJournalReader
        # once it's supported.
        conn = sqlite3.connect(WRITE_ZONE_DB_FILE)
        cur = conn.cursor()
        cur.execute('SELECT name, rrtype, ttl, rdata FROM diffs ORDER BY id')
        actual_list = cur.fetchall()
        self.assertEqual(len(expected_list), len(actual_list))
        for (expected, actual) in zip(expected_list, actual_list):
            self.assertEqual(expected, actual)
        conn.close()

    def create_a(self, address):
        a_rr = RRset(Name('www.example.org'), RRClass.IN(), RRType.A(),
                     RRTTL(3600))
        a_rr.add_rdata(Rdata(RRType.A(), RRClass.IN(), address))
        return (a_rr)

    def test_journal_write(self):
        # This is a straightforward port of the C++ 'journal' test
        # Note: we add/delete 'out of zone' data (example.org in the
        # example.com zone for convenience.
        self.updater.delete_rrset(create_soa(1234))
        self.updater.delete_rrset(self.create_a('192.0.2.2'))
        self.updater.add_rrset(create_soa(1235))
        self.updater.add_rrset(self.create_a('192.0.2.2'))
        self.updater.commit()

        expected = []
        expected.append(("example.org.", "SOA", 3600,
                         "ns1.example.org. admin.example.org. " +
                         "1234 3600 1800 2419200 7200"))
        expected.append(("www.example.org.", "A", 3600, "192.0.2.2"))
        expected.append(("example.org.", "SOA", 3600,
                         "ns1.example.org. admin.example.org. " +
                         "1235 3600 1800 2419200 7200"))
        expected.append(("www.example.org.", "A", 3600, "192.0.2.2"))
        self.check_journal(expected)

    def test_journal_write_multiple(self):
        # This is a straightforward port of the C++ 'journalMultiple' test
        expected = []
        for i in range(1, 100):
            self.updater.delete_rrset(create_soa(1234 + i - 1))
            expected.append(("example.org.", "SOA", 3600,
                             "ns1.example.org. admin.example.org. " +
                             str(1234 + i - 1) + " 3600 1800 2419200 7200"))
            self.updater.add_rrset(create_soa(1234 + i))
            expected.append(("example.org.", "SOA", 3600,
                             "ns1.example.org. admin.example.org. " +
                             str(1234 + i) + " 3600 1800 2419200 7200"))
        self.updater.commit()
        self.check_journal(expected)

    def test_journal_write_bad_sequence(self):
        # This is a straightforward port of the C++ 'journalBadSequence' test

        # Delete A before SOA
        self.assertRaises(isc.datasrc.Error, self.updater.delete_rrset,
                          self.create_a('192.0.2.1'))
        # Add before delete
        self.updater = self.dsc.get_updater(Name("example.com"), False, True)
        self.assertRaises(isc.datasrc.Error, self.updater.add_rrset,
                          create_soa(1234))
        # Add A before SOA
        self.updater = self.dsc.get_updater(Name("example.com"), False, True)
        self.updater.delete_rrset(create_soa(1234))
        self.assertRaises(isc.datasrc.Error, self.updater.add_rrset,
                          self.create_a('192.0.2.1'))
        # Commit before add
        self.updater = self.dsc.get_updater(Name("example.com"), False, True)
        self.updater.delete_rrset(create_soa(1234))
        self.assertRaises(isc.datasrc.Error, self.updater.commit)
        # Delete two SOAs
        self.updater = self.dsc.get_updater(Name("example.com"), False, True)
        self.updater.delete_rrset(create_soa(1234))
        self.assertRaises(isc.datasrc.Error, self.updater.delete_rrset,
                          create_soa(1235))
        # Add two SOAs
        self.updater = self.dsc.get_updater(Name("example.com"), False, True)
        self.updater.delete_rrset(create_soa(1234))
        self.updater.add_rrset(create_soa(1235))
        self.assertRaises(isc.datasrc.Error, self.updater.add_rrset,
                          create_soa(1236))

    def test_journal_write_onerase(self):
        self.updater = None
        self.assertRaises(isc.datasrc.Error, self.dsc.get_updater,
                          Name("example.com"), True, True)

    def test_journal_write_badparam(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        self.assertRaises(TypeError, dsc.get_updater, 0, False, True)
        self.assertRaises(TypeError, dsc.get_updater, Name('example.com'),
                          False, 0)
        self.assertRaises(TypeError, dsc.get_updater, Name("example.com"),
                          1, True)

class JournalRead(unittest.TestCase):
    def setUp(self):
        # Make a fresh copy of the writable database with all original content
        self.zname = Name('example.com')
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)
        self.dsc = isc.datasrc.DataSourceClient("sqlite3",
                                                WRITE_ZONE_DB_CONFIG)
        self.reader = None

    def tearDown(self):
        # Some tests leave the reader in the middle of sequence, holding
        # the lock.  Since the unittest framework keeps each test object
        # until the end of the entire tests, we need to make sure the reader
        # is released at the end of each test.  The client shouldn't do harm
        # but we clean it up, too, just in case.
        self.dsc = None
        self.reader = None

    def make_simple_diff(self, begin_soa):
        updater = self.dsc.get_updater(self.zname, False, True)
        updater.delete_rrset(begin_soa)
        updater.add_rrset(create_soa(1235))
        updater.commit()

    def test_journal_reader(self):
        # This is a straightforward port of the C++ 'journalReader' test
        self.make_simple_diff(create_soa(1234))
        result, self.reader = self.dsc.get_journal_reader(self.zname, 1234,
                                                          1235)
        self.assertEqual(ZoneJournalReader.SUCCESS, result)
        self.assertNotEqual(None, self.reader)
        rrsets_equal(create_soa(1234), self.reader.get_next_diff())
        rrsets_equal(create_soa(1235), self.reader.get_next_diff())
        self.assertEqual(None, self.reader.get_next_diff())
        self.assertRaises(ValueError, self.reader.get_next_diff)

    def test_journal_reader_with_large_serial(self):
        # similar to the previous one, but use a very large serial to check
        # if the python wrapper code has unexpected integer overflow
        self.make_simple_diff(create_soa(4294967295))
        result, self.reader = self.dsc.get_journal_reader(self.zname,
                                                          4294967295, 1235)
        self.assertNotEqual(None, self.reader)
        # dump to text and compare them in case create_soa happens to have
        # an overflow bug
        self.assertEqual('example.org. 3600 IN SOA ns1.example.org. ' + \
                         'admin.example.org. 4294967295 3600 1800 ' + \
                             '2419200 7200\n',
                         self.reader.get_next_diff().to_text())

    def test_journal_reader_large_journal(self):
        # This is a straightforward port of the C++ 'readLargeJournal' test.
        # In this test we use the ZoneJournalReader object as a Python
        # iterator.
        updater = self.dsc.get_updater(self.zname, False, True)
        expected = []
        for i in range(0, 100):
            rrset = create_soa(1234 + i)
            updater.delete_rrset(rrset)
            expected.append(rrset)

            rrset = create_soa(1234 + i + 1)
            updater.add_rrset(rrset)
            expected.append(rrset)

        updater.commit()
        _, self.reader = self.dsc.get_journal_reader(self.zname, 1234, 1334)
        self.assertNotEqual(None, self.reader)
        i = 0
        for rr in self.reader:
            self.assertNotEqual(len(expected), i)
            rrsets_equal(expected[i], rr)
            i += 1
        self.assertEqual(len(expected), i)

    def test_journal_reader_no_range(self):
        # This is a straightforward port of the C++ 'readJournalForNoRange'
        # test
        self.make_simple_diff(create_soa(1234))
        result, self.reader = self.dsc.get_journal_reader(self.zname, 1200,
                                                          1235)
        self.assertEqual(ZoneJournalReader.NO_SUCH_VERSION, result)
        self.assertEqual(None, self.reader)

    def test_journal_reader_no_zone(self):
        # This is a straightforward port of the C++ 'journalReaderForNXZone'
        # test
        result, self.reader = self.dsc.get_journal_reader(Name('nosuchzone'),
                                                          0, 1)
        self.assertEqual(ZoneJournalReader.NO_SUCH_ZONE, result)
        self.assertEqual(None, self.reader)

    def test_journal_reader_bad_params(self):
        self.assertRaises(TypeError, self.dsc.get_journal_reader,
                          'example.com.', 0, 1)
        self.assertRaises(TypeError, self.dsc.get_journal_reader,
                          self.zname, 'must be int', 1)
        self.assertRaises(TypeError, self.dsc.get_journal_reader,
                          self.zname, 0, 'must be int')

    def test_journal_reader_direct_construct(self):
        # ZoneJournalReader can only be constructed via a factory
        self.assertRaises(TypeError, ZoneJournalReader)

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
