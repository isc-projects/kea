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

    def atest_iterate(self):
        dsc = isc.datasrc.DataSourceClient(READ_ZONE_DB_FILE)

        # for RRSIGS, the TTL's are currently modified. This test should
        # start failing when we fix that.
        rrs = dsc.get_iterator(isc.dns.Name("sql1.example.com."))
        self.assertEqual("sql1.example.com. 3600 IN DNSKEY 256 3 5 AwEAAdYdRhBAEY67R/8G1N5AjGF6asIiNh/pNGeQ8xDQP13JN2lo+sNqWcmpYNhuVqRbLB+mamsU1XcCICSBvAlSmfz/ZUdafX23knArTlALxMmspcfdpqun3Yr3YYnztuj06rV7RqmveYckWvAUXVYMSMQZfJ305fs0dE/xLztL/CzZ\nsql1.example.com. 3600 IN DNSKEY 257 3 5 AwEAAbaKDSa9XEFTsjSYpUTHRotTS9Tz3krfDucugW5UokGQKC26QlyHXlPTZkC+aRFUs/dicJX2kopndLcnlNAPWiKnKtrsFSCnIJDBZIyvcKq+9RXmV3HK3bUdHnQZ88IZWBRmWKfZ6wnzHo53kdYKAemTErkztaX3lRRPLYWpxRcDPEjysXT3Lh0vfL5D+CIO1yKw/q7C+v6+/kYAxc2lfbNE3HpklSuF+dyX4nXxWgzbcFuLz5Bwfq6ZJ9RYe/kNkA0uMWNa1KkGeRh8gg22kgD/KT5hPTnpezUWLvoY5Qc7IB3T0y4n2JIwiF2ZrZYVrWgDjRWAzGsxJiJyjd6w2k0=\n", rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 3600 IN NS dns01.example.com.\nsql1.example.com. 3600 IN NS dns02.example.com.\nsql1.example.com. 3600 IN NS dns03.example.com.\n", rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 7200 IN NSEC www.sql1.example.com. NS SOA RRSIG NSEC DNSKEY\n", rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 3600 IN RRSIG SOA 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. FAKEFAKEFAKEFAKE\nsql1.example.com. 3600 IN RRSIG NS 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. FAKEFAKEFAKEFAKE\nsql1.example.com. 3600 IN RRSIG NSEC 5 3 7200 20100322084536 20100220084536 12447 sql1.example.com. FAKEFAKEFAKEFAKE\nsql1.example.com. 3600 IN RRSIG DNSKEY 5 3 3600 20100322084536 20100220084536 12447 sql1.example.com. FAKEFAKEFAKEFAKE\nsql1.example.com. 3600 IN RRSIG DNSKEY 5 3 3600 20100322084536 20100220084536 33313 sql1.example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        self.assertEqual("sql1.example.com. 3600 IN SOA master.example.com. admin.example.com. 678 3600 1800 2419200 7200\n", rrs.get_next_rrset().to_text())
        self.assertEqual("www.sql1.example.com. 3600 IN A 192.0.2.100\n", rrs.get_next_rrset().to_text())
        self.assertEqual("www.sql1.example.com. 7200 IN NSEC sql1.example.com. A RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("www.sql1.example.com. 3600 IN RRSIG A 5 4 3600 20100322084536 20100220084536 12447 sql1.example.com. FAKEFAKEFAKEFAKE\nwww.sql1.example.com. 3600 IN RRSIG NSEC 5 4 7200 20100322084536 20100220084536 12447 sql1.example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        self.assertEqual(None, rrs.get_next_rrset())
        # TODO should we catch this (iterating past end) and just return None
        # instead of failing?
        self.assertRaises(isc.datasrc.Error, rrs.get_next_rrset)

        rrs = dsc.get_iterator(isc.dns.Name("example.com"))
        self.assertEqual("*.wild.example.com. 3600 IN A 192.0.2.255\n", rrs.get_next_rrset().to_text())
        self.assertEqual("*.wild.example.com. 7200 IN NSEC www.example.com. A RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("*.wild.example.com. 3600 IN RRSIG A 5 3 3600 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\n*.wild.example.com. 3600 IN RRSIG NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-ext.example.com. 3600 IN CNAME www.sql1.example.com.\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-ext.example.com. 7200 IN NSEC cname-int.example.com. CNAME RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-ext.example.com. 3600 IN RRSIG CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\ncname-ext.example.com. 3600 IN RRSIG NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-int.example.com. 3600 IN CNAME www.example.com.\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-int.example.com. 7200 IN NSEC dname.example.com. CNAME RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("cname-int.example.com. 3600 IN RRSIG CNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\ncname-int.example.com. 3600 IN RRSIG NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dname.example.com. 3600 IN DNAME sql1.example.com.\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dname.example.com. 7200 IN NSEC dns01.example.com. DNAME RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dname.example.com. 3600 IN RRSIG DNAME 5 3 3600 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\ndname.example.com. 3600 IN RRSIG NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dns01.example.com. 3600 IN A 192.0.2.1\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dns01.example.com. 7200 IN NSEC dns02.example.com. A RRSIG NSEC\n", rrs.get_next_rrset().to_text())
        self.assertEqual("dns01.example.com. 3600 IN RRSIG A 5 3 3600 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\ndns01.example.com. 3600 IN RRSIG NSEC 5 3 7200 20100322084538 20100220084538 33495 example.com. FAKEFAKEFAKEFAKE\n", rrs.get_next_rrset().to_text())
        # there are more than 80 RRs in this zone... let's just count the rest
        # hmm. this makes me think we might want a real iterator returned from get_iterator()
        rrset = rrs.get_next_rrset()
        count = 0
        while rrset is not None:
            count = count + 1
            rrset = rrs.get_next_rrset()
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
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n", rrset.to_text())

        result, rrset = finder.find(isc.dns.Name("www.sql1.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.DELEGATION, result)
        self.assertEqual("sql1.example.com. 3600 IN NS dns01.example.com.\nsql1.example.com. 3600 IN NS dns02.example.com.\nsql1.example.com. 3600 IN NS dns03.example.com.\n", rrset.to_text())

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
        self.assertEqual("cname-ext.example.com. 3600 IN CNAME www.sql1.example.com.\n", rrset.to_text())

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


    def test_update(self):
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
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n", rrset.to_text())

        rrset_to_delete = rrset;
        # can't delete rrset with associated sig
        rrset_to_delete.remove_rrsig()

        result, rrset = finder.find(isc.dns.Name("doesnotexist.example.com"),
                                    isc.dns.RRType.TXT(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.NXDOMAIN, result)
        self.assertEqual(None, rrset)


        updater = dsc.get_updater(isc.dns.Name("example.com"), True)
        updater.delete_rrset(rrset_to_delete)
        updater.commit()

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

        result, rrset = finder.find(isc.dns.Name("www.example.com"),
                                    isc.dns.RRType.A(),
                                    None,
                                    finder.FIND_DEFAULT)
        self.assertEqual(finder.SUCCESS, result)
        self.assertEqual("www.example.com. 3600 IN A 192.0.2.1\n", rrset.to_text())


if __name__ == "__main__":
    isc.log.init("bind10")
    unittest.main()
