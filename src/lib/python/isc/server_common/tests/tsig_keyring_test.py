# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

"""
Tests for isc.server_common.tsig_keyring.
"""

import unittest
import isc.log
from isc.server_common.tsig_keyring import *
import isc.dns
from isc.testutils.ccsession_mock import MockModuleCCSession

class Session(MockModuleCCSession):
    """
    A class pretending to be the config session.
    """
    def __init__(self):
        MockModuleCCSession.__init__(self)
        self._name = None
        self._callback = None
        self._remove_name = None
        self._data = None

    def add_remote_config_by_name(self, name, callback):
        self._name = name
        self._callback = callback

    def remove_remote_config(self, name):
        self._remove_name = name

    def get_remote_config_value(self, module, name):
        if module != 'tsig_keys' or name != 'keys':
            raise Exception("Asked for bad data element")
        return (self._data, False)

class TSIGKeyRingTest(unittest.TestCase):
    """
    Tests for the isc.server_common.tsig_keyring module.
    """
    def setUp(self):
        self.__session = Session()
        self.__sha1name = isc.dns.Name('hmac-sha1')

    def tearDown(self):
        deinit_keyring()

    def __do_init(self):
        init_keyring(self.__session)
        # Some initialization happened
        self.assertEqual('tsig_keys', self.__session._name)

    def test_initialization(self):
        """
        Test we can initialize and deintialize the keyring. It also
        tests the interaction with the keyring() function.
        """
        # The keyring function raises until initialized
        self.assertRaises(Unexpected, get_keyring)
        self.__do_init()
        current_keyring = get_keyring()
        self.assertTrue(isinstance(current_keyring, isc.dns.TSIGKeyRing))
        # Another initialization does nothing
        self.__do_init()
        self.assertEqual(current_keyring, get_keyring())
        # When we deinitialize it, it no longer provides the keyring
        deinit_keyring()
        self.assertEqual('tsig_keys', self.__session._remove_name)
        self.__session._remove_name = None
        self.assertRaises(Unexpected, get_keyring)
        # Another deinitialization doesn't change anything
        deinit_keyring()
        self.assertRaises(Unexpected, get_keyring)
        self.assertIsNone(self.__session._remove_name)

    def test_load(self):
        """
        Test it can load the keys from the configuration and reload them
        when the data change.
        """
        # Initial load
        self.__session._data = ['key:MTIzNAo=:hmac-sha1']
        self.__do_init()
        keys = get_keyring()
        self.assertEqual(1, keys.size())
        (rcode, key) = keys.find(isc.dns.Name('key'), self.__sha1name)
        self.assertEqual(isc.dns.TSIGKeyRing.SUCCESS, rcode)
        self.assertEqual(isc.dns.Name('key'), key.get_key_name())
        # There's a change in the configuration
        # (The key has a different name)
        self.__session._data = ['key.example:MTIzNAo=:hmac-sha1']
        self.__session._callback()
        orig_keys = keys
        keys = get_keyring()
        self.assertNotEqual(keys, orig_keys)
        self.assertEqual(1, keys.size())
        # The old key is not here
        (rcode, key) = keys.find(isc.dns.Name('key'), self.__sha1name)
        self.assertEqual(isc.dns.TSIGKeyRing.NOTFOUND, rcode)
        self.assertIsNone(key)
        # But the new one is
        (rcode, key) = keys.find(isc.dns.Name('key.example'), self.__sha1name)
        self.assertEqual(isc.dns.TSIGKeyRing.SUCCESS, rcode)
        self.assertEqual(isc.dns.Name('key.example'), key.get_key_name())

    def test_empty_update(self):
        """
        Test an update that doesn't carry the correct element doesn't change
        anything.
        """
        self.__session._data = ['key:MTIzNAo=:hmac-sha1']
        self.__do_init()
        keys = get_keyring()
        self.__session._data = None
        self.__session._callback()
        self.assertEqual(keys, get_keyring())

    def test_update_bad(self):
        """
        Test it raises on bad updates and doesn't change anything.
        """
        self.__session._data = ['key:MTIzNAo=:hmac-sha1']
        self.__do_init()
        keys = get_keyring()
        # Bad TSIG string
        self.__session._data = ['key:this makes no sense:really']
        self.assertRaises(isc.dns.InvalidParameter, self.__session._callback)
        self.assertEqual(keys, get_keyring())
        # A duplicity
        self.__session._data = ['key:MTIzNAo=:hmac-sha1', 'key:MTIzNAo=:hmac-sha1']
        self.assertRaises(AddError, self.__session._callback)
        self.assertEqual(keys, get_keyring())

if __name__ == "__main__":
    isc.log.init("bind10") # FIXME Should this be needed?
    isc.log.resetUnitTestRootLogger()
    unittest.main()
