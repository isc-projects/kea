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

# Make sure we can load the module, put it into path
import sys
import os
sys.path.extend(os.environ["B10_TEST_PLUGIN_DIR"].split(':'))

import tsig_keys
import unittest
import isc.config.module_spec

class TSigKeysTest(unittest.TestCase):
    def test_load(self):
        """
        Checks the entry point returns the correct values.
        """
        (spec, check) = tsig_keys.load()
        # It returns the checking function
        self.assertEqual(check, tsig_keys.check)
        # The plugin stores it's spec
        self.assertEqual(spec, tsig_keys.spec)

    def test_spec(self):
        """
        Checks the spec is looking sane (doesn't do really deep check here).
        """
        spec = tsig_keys.spec
        # In python, we don't generally check the type of something, because
        # of the duck typing.
        # But this is unittest, so we check it does what we intend and
        # supplying that's behaving the same but is different is not our
        # intention
        self.assertTrue(isinstance(spec, isc.config.module_spec.ModuleSpec))
        # Correct name
        self.assertEqual("tsig_keys", spec.get_module_name())
        # There are no commands, nobody would handle them anyway
        self.assertEqual([], spec.get_commands_spec())
        # There's some nonempty configuration
        self.assertNotEqual({}, spec.get_config_spec())

    def test_missing_keys(self):
        """
        Test that missing keys doesn't kill us. There are just no keys there.
        """
        self.assertEqual(None, tsig_keys.check({}))

    def test_data_empty(self):
        """Check we accept valid config with empty set of tsig keys."""
        self.assertEqual(None, tsig_keys.check({'keys': []}))

    def test_keys_valid(self):
        """
        Check we accept some valid keys (we don't check all the algorithms,
        that's the job of isc.dns.TSIGKey).
        """
        self.assertEqual(None, tsig_keys.check({'keys':
            ['testkey:QklORCAxMCBpcyBjb29sCg==',
             'test.key:QklORCAxMCBpcyBjb29sCg==:hmac-sha1']}))

    def test_keys_same_name(self):
        """
        Test we reject when we have multiple keys with the same name.
        """
        self.assertEqual("Multiple TSIG keys with name 'test.key.'",
                         tsig_keys.check({'keys':
                                         ['test.key:QklORCAxMCBpcyBjb29sCg==',
                                          'test.key:b3RoZXIK']}))

    def test_invalid_key(self):
        """
        Test we reject invalid key.
        """
        self.assertEqual("TSIG: Invalid TSIG key string: invalid.key",
                         tsig_keys.check({'keys': ['invalid.key']}))
        self.assertEqual(
            "TSIG: Unexpected end of input in BASE decoder",
            tsig_keys.check({'keys': ['invalid.key:123']}))

    def test_bad_format(self):
        """
        Test we fail on bad format. We don't really care much how here, though,
        as this should not get in trough config manager anyway.
        """
        self.assertNotEqual(None, tsig_keys.check({'bad_name': {}}))
        self.assertNotEqual(None, tsig_keys.check({'keys': 'not_list'}))
        self.assertNotEqual(None, tsig_keys.check({'keys': 42}))
        self.assertNotEqual(None, tsig_keys.check({'keys': {}}))

if __name__ == '__main__':
        unittest.main()
