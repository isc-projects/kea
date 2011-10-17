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
from isc.datasrc import ZoneFinder
import isc.dns
import unittest
import os
import shutil
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

# helper function, we have no direct rrset comparison atm
def rrsets_equal(a, b):
    # no accessor for sigs either (so this only checks name, class, type, ttl,
    # and rdata)
    # also, because of the fake data in rrsigs, if the type is rrsig, the
    # rdata is not checked
    return a.get_name() == b.get_name() and\
           a.get_class() == b.get_class() and\
           a.get_type() == b.get_type() and \
           a.get_ttl() == b.get_ttl() and\
           (a.get_type() == isc.dns.RRType.RRSIG() or
            sorted(a.get_rdata()) == sorted(b.get_rdata()))

# returns true if rrset is in expected_rrsets
# will remove the rrset from expected_rrsets if found
def check_for_rrset(expected_rrsets, rrset):
    for cur_rrset in expected_rrsets[:]:
        if rrsets_equal(cur_rrset, rrset):
            expected_rrsets.remove(cur_rrset)
            return True
    return False

class DataSrcClient(unittest.TestCase):

    def test_constructors(self):
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
        rrs = dsc.get_iterator(isc.dns.Name("sql1.example.com."))

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
                     "5fs0dE/xLztL/CzZ",
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
                    "dns01.example.com.",
                    "dns02.example.com.",
                    "dns03.example.com."
                  ])
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.NSEC(), isc.dns.RRTTL(7200),
                  [
                     "www.sql1.example.com. NS SOA RRSIG NSEC DNSKEY"
                  ])
        # For RRSIGS, we can't add the fake data through the API, so we
        # simply pass no rdata at all (which is skipped by the check later)
        add_rrset(expected_rrset_list, name, rrclass,
                  isc.dns.RRType.RRSIG(), isc.dns.RRTTL(3600), None)
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
                         str([rrset.to_text() for rrset in expected_rrset_list ]
                        ))

        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        rrets = dsc.get_iterator(isc.dns.Name("example.com"))
        # there are more than 80 RRs in this zone... let's just count them
        # (already did a full check of the smaller zone above)
        self.assertEqual(55, len(list(rrets)))
        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        self.assertRaises(TypeError, dsc.get_iterator, "asdf")

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
        self.assertNotEqual(ZoneFinder.DNAME, ZoneFinder.WILDCARD)
        self.assertNotEqual(ZoneFinder.WILDCARD, ZoneFinder.WILDCARD_CNAME)
        self.assertNotEqual(ZoneFinder.WILDCARD_CNAME,
                            ZoneFinder.WILDCARD_NXRRSET)

    def test_find(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)

        result, finder = dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        result, rrset = finder.find(isc.dns.Name("www.sql1.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.DELEGATION, result)
        self.assertEqual("sql1.example.com. 3600 IN NS dns01.example.com.\n" +
                         "sql1.example.com. 3600 IN NS dns02.example.com.\n" +
                         "sql1.example.com. 3600 IN NS dns03.example.com.\n",
                         rrset.to_text())

        result, rrset = finder.find(isc.dns.Name("doesnotexist.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        result, rrset = finder.find(isc.dns.Name("www.some.other.domain"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.TXT(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.NXRRSET, result)
        self.assertEqual(None, rrset)

        result, rrset = finder.find(isc.dns.Name("cname-ext.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.CNAME, result)
        self.assertEqual(
            "cname-ext.example.com. 3600 IN CNAME www.sql1.example.com.\n",
            rrset.to_text())

        result, rrset = finder.find(isc.dns.Name("foo.wild.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.WILDCARD, result)
        self.assertEqual("foo.wild.example.com. 3600 IN A 192.0.2.255\n",
                         rrset.to_text())

        result, rrset = finder.find(isc.dns.Name("foo.wild.example.com"),
                                    isc.dns.RRType.TXT(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.WILDCARD_NXRRSET, result)
        self.assertEqual(None, rrset)

        self.assertRaises(TypeError, finder.find,
                          "foo",
                          isc.dns.RRType.A(),
                          None,
                          finder.FIND_DEFAULT)
        self.assertRaises(TypeError, finder.find,
                          isc.dns.Name("cname-ext.example.com"),
                          "foo",
                          None,
                          finder.FIND_DEFAULT)
        self.assertRaises(TypeError, finder.find,
                          isc.dns.Name("cname-ext.example.com"),
                          isc.dns.RRType.A(),
                          None,
                          "foo")

    def test_find_previous(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", READ_ZONE_DB_CONFIG)

        result, finder = dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)

        prev = finder.find_previous_name(isc.dns.Name("bbb.example.com"))
        self.assertEqual("example.com.", prev.to_text())

        prev = finder.find_previous_name(isc.dns.Name("zzz.example.com"))
        self.assertEqual("www.example.com.", prev.to_text())

        prev = finder.find_previous_name(prev)
        self.assertEqual("*.wild.example.com.", prev.to_text())

        self.assertRaises(isc.datasrc.NotImplemented,
                          finder.find_previous_name,
                          isc.dns.Name("com"))

class DataSrcUpdater(unittest.TestCase):

    def setUp(self):
        # Make a fresh copy of the writable database with all original content
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)

    def test_construct(self):
        # can't construct directly
        self.assertRaises(TypeError, isc.datasrc.ZoneUpdater)

    def test_update_delete_commit(self):

        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)

        # first make sure, through a separate finder, that some record exists
        result, finder = dsc.find_zone(isc.dns.Name("example.com"))
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual(isc.dns.RRClass.IN(), finder.get_class())
        self.assertEqual("example.com.", finder.get_origin().to_text())

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        rrset_to_delete = rrset;

        # can't delete rrset with associated sig. Abuse that to force an
        # exception first, then remove the sig, then delete the record
        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        self.assertRaises(isc.datasrc.Error, updater.delete_rrset,
                          rrset_to_delete)

        rrset_to_delete.remove_rrsig()

        updater.delete_rrset(rrset_to_delete)

        # The record should be gone in the updater, but not in the original
        # finder (since we have not committed)
        result, rrset = updater.find(isc.dns.Name("www.example.com"),
                                     isc.dns.RRType.A(),
                                     None,
                                     finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        updater.commit()
        # second commit should raise exception
        self.assertRaises(isc.datasrc.Error, updater.commit)

        # the record should be gone now in the 'real' finder as well
        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        # now add it again
        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        updater.add_rrset(rrset_to_delete)
        updater.commit()

        # second commit should throw
        self.assertRaises(isc.datasrc.Error, updater.commit)

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
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
        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
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

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

        rrset_to_delete = rrset;

        # can't delete rrset with associated sig. Abuse that to force an
        # exception first, then remove the sig, then delete the record
        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        self.assertRaises(isc.datasrc.Error, updater.delete_rrset,
                          rrset_to_delete)

        rrset_to_delete.remove_rrsig()

        updater.delete_rrset(rrset_to_delete)

        # The record should be gone in the updater, but not in the original
        # finder (since we have not committed)
        result, rrset = updater.find(isc.dns.Name("www.example.com"),
                                     isc.dns.RRType.A(),
                                     None,
                                     finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)

        # destroy the updater, which should make it roll back
        updater = None

        # the record should still be available in the 'real' finder as well
        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n",
                         rrset.to_text())

    def test_update_for_no_zone(self):
        dsc = isc.datasrc.DataSourceClient("sqlite3", WRITE_ZONE_DB_CONFIG)
        self.assertEqual(None,
                         dsc.get_updater(isc.dns.Name("notexistent.example"),
                                         True))

if __name__ == "__main__":
    isc.log.init("bind10")
    unittest.main()
