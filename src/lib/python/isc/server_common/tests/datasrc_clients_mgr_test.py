# Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
from isc.server_common.datasrc_clients_mgr import *
from isc.dns import *
import unittest
import isc.config
import os

DATASRC_SPECFILE = os.environ["B10_FROM_BUILD"] + \
    "/src/bin/cfgmgr/plugins/datasrc.spec"
DEFAULT_CONFIG = \
    isc.config.ConfigData(isc.config.module_spec_from_file(DATASRC_SPECFILE)).\
    get_full_config()

class DataSrcClientsMgrTest(unittest.TestCase):
    def setUp(self):
        # We construct the manager with enabling in-memory cache for easier
        # tests.  There should be no risk of inter-thread issues in the tests.
        self.__mgr = DataSrcClientsMgr(use_cache=True)

    def test_init(self):
        """Check some initial state.

        Initially there's no client list available, but get_client_list
        doesn't cause disruption.
        """
        self.assertIsNone(self.__mgr.get_client_list(RRClass.IN))
        self.assertIsNone(self.__mgr.get_client_list(RRClass.CH))

    def test_reconfigure(self):
        """Check configuration behavior.

        First try the default configuration, and replace it with something
        else.
        """

        # There should be at least in-memory only data for the static
        # bind/CH zone. (We don't assume the existence of SQLite3 datasrc,
        # so it'll still work if and when we make the default DB-independent).
        self.__mgr.reconfigure(DEFAULT_CONFIG)
        clist = self.__mgr.get_client_list(RRClass.CH)
        self.assertIsNotNone(clist)
        self.assertTrue(clist.find(Name('bind'), True, False)[2])

        # Reconfigure it with a simple new config: the list for CH will be
        # gone, and and an empty list for IN will be installed.
        self.__mgr.reconfigure({"classes": {"IN": []}})
        self.assertIsNone(self.__mgr.get_client_list(RRClass.CH))
        self.assertIsNotNone(self.__mgr.get_client_list(RRClass.IN))

    def test_reconfigure_error(self):
        """Check reconfigure failure preserves the old config."""
        # Configure it with the default
        self.__mgr.reconfigure(DEFAULT_CONFIG)
        self.assertIsNotNone(self.__mgr.get_client_list(RRClass.CH))

        # Then try invalid configuration
        self.assertRaises(ConfigError, self.__mgr.reconfigure, 42)
        self.assertIsNotNone(self.__mgr.get_client_list(RRClass.CH))

        # Another type of invalid configuration: exception would come from
        # the C++ wrapper.
        self.assertRaises(ConfigError,
                          self.__mgr.reconfigure, {"classes": {"IN": 42}})
        self.assertIsNotNone(self.__mgr.get_client_list(RRClass.CH))

    def test_reconfig_while_using_old(self):
        """Check datasrc client and finder can work even after list is gone."""
        self.__mgr.reconfigure(DEFAULT_CONFIG)
        clist = self.__mgr.get_client_list(RRClass.CH)
        self.__mgr.reconfigure({"classes": {"IN": []}})

        datasrc_client, finder, exact = clist.find(Name('bind'))
        self.assertTrue(exact)

        # Reset the client list
        clist = None

        # Both finder and datasrc client should still work without causing
        # disruption.  We shouldn't have to inspect too much details of the
        # returned values.
        result, rrset, _ = finder.find(Name('bind'), RRType.SOA)
        self.assertEqual(Name('bind'), rrset.get_name())
        self.assertEqual(RRType.SOA, rrset.get_type())
        self.assertEqual(RRClass.CH, rrset.get_class())
        self.assertEqual(RRTTL(0), rrset.get_ttl())

        # iterator should produce some non empty set of RRsets
        rrsets = datasrc_client.get_iterator(Name('bind'))
        self.assertNotEqual(0, len(list(rrsets)))

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
