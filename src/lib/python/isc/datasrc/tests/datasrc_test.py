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
import isc.dns
import unittest
import os
import shutil

TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep

READ_ZONE_DB_FILE = TESTDATA_PATH + "example.com.sqlite3"
BROKEN_DB_FILE = TESTDATA_PATH + "brokendb.sqlite3"
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "rwtest.sqlite3.copied"
NEW_DB_FILE = TESTDATA_WRITE_PATH + "new_db.sqlite3"

class DataSrcClient(unittest.TestCase):

    def test_iterate(self):
        dsc = isc.datasrc.DataSourceClient(READ_ZONE_DB_FILE)

        # for RRSIGS, the TTL's are currently modified. This test should
        # start failing when we fix that.
        rrs = dsc.get_iterator(isc.dns.Name("sql1.example.com."))
        self.assertEqual("sql1.example.com. 3600 IN DNSKEY 256 3 5 AwEAAdYdRh" +
                         "BAEY67R/8G1N5AjGF6asIiNh/pNGeQ8xDQP13JN2lo+sNqWcmpY" +
                         "NhuVqRbLB+mamsU1XcCICSBvAlSmfz/ZUdafX23knArTlALxMms" +
                         "pcfdpqun3Yr3YYnztuj06rV7RqmveYckWvAUXVYMSMQZfJ305fs" +
                         "0dE/xLztL/CzZ\nsql1.example.com. 3600 IN DNSKEY 257" +
                         " 3 5 AwEAAbaKDSa9XEFTsjSYpUTHRotTS9Tz3krfDucugW5Uok" +
                         "GQKC26QlyHXlPTZkC+aRFUs/dicJX2kopndLcnlNAPWiKnKtrsF" +
                         "SCnIJDBZIyvcKq+9RXmV3HK3bUdHnQZ88IZWBRmWKfZ6wnzHo53" +
                         "kdYKAemTErkztaX3lRRPLYWpxRcDPEjysXT3Lh0vfL5D+CIO1yK" +
                         "w/q7C+v6+/kYAxc2lfbNE3HpklSuF+dyX4nXxWgzbcFuLz5Bwfq" +
                         "6ZJ9RYe/kNkA0uMWNa1KkGeRh8gg22kgD/KT5hPTnpezUWLvoY5" +
                         "Qc7IB3T0y4n2JIwiF2ZrZYVrWgDjRWAzGsxJiJyjd6w2k0=\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 3600 IN NS dns01.example.com.\nsq" +
                         "l1.example.com. 3600 IN NS dns02.example.com.\nsql1" +
                         ".example.com. 3600 IN NS dns03.example.com.\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 7200 IN NSEC www.sql1.example.com" +
                         ". NS SOA RRSIG NSEC DNSKEY\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 3600 IN RRSIG SOA 5 3 3600 201003" +
                         "22084536 20100220084536 12447 sql1.example.com. FAK" +
                         "EFAKEFAKEFAKE\nsql1.example.com. 3600 IN RRSIG NS 5" +
                         " 3 3600 20100322084536 20100220084536 12447 sql1.ex" +
                         "ample.com. FAKEFAKEFAKEFAKE\nsql1.example.com. 3600" +
                         " IN RRSIG NSEC 5 3 7200 20100322084536 201002200845" +
                         "36 12447 sql1.example.com. FAKEFAKEFAKEFAKE\nsql1.e" +
                         "xample.com. 3600 IN RRSIG DNSKEY 5 3 3600 201003220" +
                         "84536 20100220084536 12447 sql1.example.com. FAKEFA" +
                         "KEFAKEFAKE\nsql1.example.com. 3600 IN RRSIG DNSKEY " +
                         "5 3 3600 20100322084536 20100220084536 33313 sql1.e" +
                         "xample.com. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 3600 IN SOA master.example.com. a" +
                         "dmin.example.com. 678 3600 1800 2419200 7200\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("www.sql1.example.com. 3600 IN A 192.0.2.100\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("www.sql1.example.com. 7200 IN NSEC sql1.example.com" +
                         ". A RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("www.sql1.example.com. 3600 IN RRSIG A 5 4 3600 2010" +
                         "0322084536 20100220084536 12447 sql1.example.com. F" +
                         "AKEFAKEFAKEFAKE\nwww.sql1.example.com. 3600 IN RRSI" +
                         "G NSEC 5 4 7200 20100322084536 20100220084536 12447" +
                         " sql1.example.com. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual(None, rrs.get_next_rrset())
        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        rrs = dsc.get_iterator(isc.dns.Name("example.com"))
        self.assertEqual("*.wild.example.com. 3600 IN A 192.0.2.255\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("*.wild.example.com. 7200 IN NSEC www.example.com. A" +
                         " RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("*.wild.example.com. 3600 IN RRSIG A 5 3 3600 201003" +
                         "22084538 20100220084538 33495 example.com. FAKEFAKE" +
                         "FAKEFAKE\n*.wild.example.com. 3600 IN RRSIG NSEC 5 " +
                         "3 7200 20100322084538 20100220084538 33495 example." +
                         "com. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("cname-ext.example.com. 3600 IN CNAME www.sql1.examp" +
                         "le.com.\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-ext.example.com. 7200 IN NSEC cname-int.examp" +
                         "le.com. CNAME RRSIG NSEC\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("cname-ext.example.com. 3600 IN RRSIG CNAME 5 3 3600" +
                         " 20100322084538 20100220084538 33495 example.com. F" +
                         "AKEFAKEFAKEFAKE\ncname-ext.example.com. 3600 IN RRS" +
                         "IG NSEC 5 3 7200 20100322084538 20100220084538 3349" +
                         "5 example.com. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("cname-int.example.com. 3600 IN CNAME www.example.co" +
                         "m.\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-int.example.com. 7200 IN NSEC dname.example.c" +
                         "om. CNAME RRSIG NSEC\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("cname-int.example.com. 3600 IN RRSIG CNAME 5 3 3600" +
                         " 20100322084538 20100220084538 33495 example.com. F" +
                         "AKEFAKEFAKEFAKE\ncname-int.example.com. 3600 IN RRS" +
                         "IG NSEC 5 3 7200 20100322084538 20100220084538 3349" +
                         "5 example.com. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("dname.example.com. 3600 IN DNAME sql1.example.com.\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("dname.example.com. 7200 IN NSEC dns01.example.com. " +
                         "DNAME RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dname.example.com. 3600 IN RRSIG DNAME 5 3 3600 201" +
                         "00322084538 20100220084538 33495 example.com. FAKEF" +
                         "AKEFAKEFAKE\ndname.example.com. 3600 IN RRSIG NSEC " +
                         "5 3 7200 20100322084538 20100220084538 33495 exampl" +
                         "e.com. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("dns01.example.com. 3600 IN A 192.0.2.1\n",
                         rrs.get_next_rrset().to_text())
        self.assertEqual("dns01.example.com. 7200 IN NSEC dns02.example.com. " +
                         "A RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dns01.example.com. 3600 IN RRSIG A 5 3 3600 2010032" +
                         "2084538 20100220084538 33495 example.com. FAKEFAKEF" +
                         "AKEFAKE\ndns01.example.com. 3600 IN RRSIG NSEC 5 3 " +
                         "7200 20100322084538 20100220084538 33495 example.co" +
                         "m. FAKEFAKEFAKEFAKE\n",
                         rrs.get_next_rrset().to_text())
        # there are more than 80 RRs in this zone... let's just count the rest
        count = 0
        for rrset in rrs:
            count = count + 1
        self.assertEqual(40, count)
        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        self.assertRaises(TypeError, dsc.get_iterator, "asdf")

    def test_find(self):
        dsc = isc.datasrc.DataSourceClient(READ_ZONE_DB_FILE)

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


class DataSrcUpdater(unittest.TestCase):

    def setUp(self):
        # Make a fresh copy of the writable database with all original content
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)

    def test_update_delete_commit(self):
        dsc = isc.datasrc.DataSourceClient(WRITE_ZONE_DB_FILE)

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

    def test_update_delete_abort(self):
        dsc = isc.datasrc.DataSourceClient(WRITE_ZONE_DB_FILE)

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


if __name__ == "__main__":
    isc.log.init("bind10")
    unittest.main()
