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
import unittest
import json
sys.path.extend(os.environ["B10_TEST_PLUGIN_DIR"].split(':'))
import isc.log

import datasrc_config_plugin

class DatasrcTest(unittest.TestCase):
    def reject(self, config):
        """
        Just a shortcut to check the config is rejected.
        """
        old = json.dumps(config)
        self.assertIsNotNone(datasrc_config_plugin.check({"classes":
                                                         config}))
        # There's some data mangling inside the plugin. Check it does
        # not propagate out, as it could change the real configuration.
        self.assertEqual(old, json.dumps(config))

    def accept(self, config):
        """
        Just a shortcut to check the config is accepted.
        """
        old = json.dumps(config)
        self.assertIsNone(datasrc_config_plugin.check({"classes":
                                                      config}))
        # There's some data mangling inside the plugin. Check it does
        # not propagate out, as it could change the real configuration.
        self.assertEqual(old, json.dumps(config))

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

    def test_mem_ok(self):
        """
        Test we accept an in-memory data source. It doesn't really matter
        which one it is. We just want to make sure we accept something
        and this one does not need any kind of path mangling to find
        plugins.
        """
        self.accept({"IN": [{
            "type": "MasterFiles",
            "cache-enable": True,
            "params": {}
        }]})

    def test_dstype_bad(self):
        """
        The configuration is correct by the spec, but it would be rejected
        by the client list. Check we reject it.
        """
        self.reject({"IN": [{
            "type": "No such type"
        }]})

    def test_invalid_mem_params(self):
        """
        The client list skips in-memory sources. So we check it locally that
        invalid things are rejected.
        """
        # The 'params' key is mandatory for MasterFiles
        self.reject({"IN": [{
            "type": "MasterFiles",
            "cache-enable": True
        }]})
        # The cache must be enabled
        self.reject({"IN": [{
            "type": "MasterFiles",
            "cache-enable": False,
            "params": {}
        }]})
        self.reject({"IN": [{
            "type": "MasterFiles",
            "params": {}
        }]})
        # Bad params type
        self.reject({"IN": [{
            "type": "MasterFiles",
            "cache-enable": True,
            "params": []
        }]})
        # Bad name
        self.reject({"IN": [{
            "type": "MasterFiles",
            "cache-enable": True,
            "params": {
                "example....org.": '/file/does/not/exist'
            }
        }]})

    def test_no_such_file_mem(self):
        """
        We also check the existance of master files. Not the actual content,
        though.
        """
        self.reject({"IN": [{
            "type": "MasterFiles",
            "cache-enable": True,
            "params": {
                "example.org.": '/file/does/not/exist'
            }
        }]})

if __name__ == '__main__':
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
