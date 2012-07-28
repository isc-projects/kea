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

import datasrc_config_plugin
import unittest

class DatasrcTest(unittest.TestCase):
    def reject(self, config):
        """
        Just a shortcut to check the config is rejected.
        """
        self.assertIsNotNone(datasrc_config_plugin.check({"classes":
                                                         config}))

    def accept(self, config):
        """
        Just a shortcut to check the config is accepted.
        """
        self.assertIsNone(datasrc_config_plugin.check({"classes":
                                                      config}))

    def test_load(self):
        """
        Checks the entry point returns the correct values.
        """
        (spec, check) = datasrc_config_plugin.load()
        # It returns the checking function
        self.assertEqual(check, datasrc_config_plugin.check)
        # The plugin stores it's spec
        self.assertEqual(spec, datasrc_config_plugin.spec)

    def test_empty(self):
        """
        Check an empty input is OK.
        """
        self.accept({})

    def test_invalid_spec(self):
        """
        Check it rejects stuff that is not well-formed according
        to the spec.
        """
        self.reject("test")
        self.reject(13)
        self.reject([])
        self.reject({"IN": {}})
        self.reject({"IN": [{"bad-name": True}]})

    def test_class(self):
        """
        The class is rejected, if it is wrong.
        """
        self.reject({"BAD": []})
        self.reject({"": []})
        # But with a good one, it works
        for c in ["IN", "CH", "HS"]:
            self.accept({c: []})

if __name__ == '__main__':
        unittest.main()
