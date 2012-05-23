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
import unittest
from isc.dns import *
from isc.datasrc import DataSourceClient
from isc.ddns.zone_config import *

# Some common test parameters
TEST_ZONE_NAME = Name('example.org')
TEST_SECONDARY_ZONE_NAME = Name('example.com')
TEST_RRCLASS = RRClass.IN()

class FakeDataSourceClient:
    '''Faked data source client used in the ZoneConfigTest.

    It emulates isc.datasrc.DataSourceClient, but only has to provide
    the find_zone() interface (and only the first element of the return
    value matters).  By default it returns 'SUCCESS' (exact match) for
    any input.  It can be dynamically customized via the set_find_result()
    method.

    '''
    def __init__(self):
        self.__find_result = DataSourceClient.SUCCESS

    def find_zone(self, zname):
        return (self.__find_result, None)

    def set_find_result(self, result):
        self.__find_result = result

class ZoneConfigTest(unittest.TestCase):
    '''Some basic tests for the ZoneConfig class.'''
    def setUp(self):
        self.__datasrc_client = FakeDataSourceClient()
        self.zconfig = ZoneConfig([(TEST_SECONDARY_ZONE_NAME, TEST_RRCLASS)],
                                  TEST_RRCLASS, self.__datasrc_client)

    def test_find_zone(self):
        # Primay zone case: zone is in the data source, and not in secondaries
        self.assertEqual((ZONE_PRIMARY, self.__datasrc_client),
                         (self.zconfig.find_zone(TEST_ZONE_NAME, TEST_RRCLASS)))

        # Secondary zone case: zone is in the data source and in secondaries.
        self.assertEqual((ZONE_SECONDARY, None),
                         (self.zconfig.find_zone(TEST_SECONDARY_ZONE_NAME,
                                                 TEST_RRCLASS)))

        # 'not found' case: zone not in the data source.
        self.__datasrc_client.set_find_result(DataSourceClient.NOTFOUND)
        self.assertEqual((ZONE_NOTFOUND, None),
                         (self.zconfig.find_zone(Name('example'),
                                                 TEST_RRCLASS)))
        # same for the partial match
        self.__datasrc_client.set_find_result(DataSourceClient.PARTIALMATCH)
        self.assertEqual((ZONE_NOTFOUND, None),
                         (self.zconfig.find_zone(Name('example'),
                                                 TEST_RRCLASS)))
        # a bit unusual case: zone not in the data source, but in secondaries.
        # this is probably a configuration error, but ZoneConfig doesn't do
        # this level check.
        self.__datasrc_client.set_find_result(DataSourceClient.NOTFOUND)
        self.assertEqual((ZONE_NOTFOUND, None),
                         (self.zconfig.find_zone(TEST_ZONE_NAME,
                                                 TEST_RRCLASS)))
        # zone class doesn't match (but zone name matches)
        self.__datasrc_client.set_find_result(DataSourceClient.SUCCESS)
        zconfig = ZoneConfig([(TEST_SECONDARY_ZONE_NAME, TEST_RRCLASS)],
                             RRClass.CH(), self.__datasrc_client)
        self.assertEqual((ZONE_NOTFOUND, None),
                         (zconfig.find_zone(TEST_ZONE_NAME, TEST_RRCLASS)))
        # similar to the previous case, but also in the secondary list
        zconfig = ZoneConfig([(TEST_ZONE_NAME, TEST_RRCLASS)],
                             RRClass.CH(), self.__datasrc_client)
        self.assertEqual((ZONE_NOTFOUND, None),
                         (zconfig.find_zone(TEST_ZONE_NAME, TEST_RRCLASS)))

        # check some basic tests varying the secondary list.
        # empty secondary list doesn't cause any disruption.
        zconfig = ZoneConfig([], TEST_RRCLASS, self.__datasrc_client)
        self.assertEqual((ZONE_PRIMARY, self.__datasrc_client),
                         (self.zconfig.find_zone(TEST_ZONE_NAME, TEST_RRCLASS)))
        # adding some mulitle tuples, including subdomainof the test zone name,
        # and the same zone name but a different class
        zconfig = ZoneConfig([(TEST_SECONDARY_ZONE_NAME, TEST_RRCLASS),
                              (Name('example'), TEST_RRCLASS),
                              (Name('sub.example.org'), TEST_RRCLASS),
                              (TEST_ZONE_NAME, RRClass.CH())],
                             TEST_RRCLASS, self.__datasrc_client)
        self.assertEqual((ZONE_PRIMARY, self.__datasrc_client),
                         (self.zconfig.find_zone(TEST_ZONE_NAME, TEST_RRCLASS)))
        # secondary zone list has a duplicate entry, which is just
        # (effecitivey) ignored
        zconfig = ZoneConfig([(TEST_SECONDARY_ZONE_NAME, TEST_RRCLASS),
                              (TEST_SECONDARY_ZONE_NAME, TEST_RRCLASS)],
                             TEST_RRCLASS, self.__datasrc_client)
        self.assertEqual((ZONE_PRIMARY, self.__datasrc_client),
                         (self.zconfig.find_zone(TEST_ZONE_NAME, TEST_RRCLASS)))

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
