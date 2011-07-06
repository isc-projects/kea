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

import unittest
from isc.acl.dns import *

class RequestACLTest(unittest.TestCase):

    def test_request_loader(self):
        # these shouldn't raise an exception
        load_request_acl('[{"action": "DROP"}]')
        load_request_acl('[{"action": "DROP", "from": "192.0.2.1"}]')

        # Invalid types
        self.assertRaises(TypeError, load_request_acl, 1)
        self.assertRaises(TypeError, load_request_acl, [])

        # Incorrect number of arguments
        self.assertRaises(TypeError, load_request_acl,
                          '[{"action": "DROP"}]', 0)

    def test_bad_acl_syntax(self):
        # this test is derived from loader_test.cc
        self.assertRaises(LoaderError, load_request_acl, '{}');
        self.assertRaises(LoaderError, load_request_acl, '42');
        self.assertRaises(LoaderError, load_request_acl, 'true');
        self.assertRaises(LoaderError, load_request_acl, 'null');
        self.assertRaises(LoaderError, load_request_acl, '"hello"');
        self.assertRaises(LoaderError, load_request_acl, '[42]');
        self.assertRaises(LoaderError, load_request_acl, '["hello"]');
        self.assertRaises(LoaderError, load_request_acl, '[[]]');
        self.assertRaises(LoaderError, load_request_acl, '[true]');
        self.assertRaises(LoaderError, load_request_acl, '[null]');
        self.assertRaises(LoaderError, load_request_acl, '[{}]');

    def test_bad_acl_ipsyntax(self):
        # this test is derived from ip_check_unittest.cc
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "192.0.2.43/-1"}]')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "192.0.2.43//1"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "192.0.2.43/1/"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "/192.0.2.43/1"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "2001:db8::/xxxx"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "2001:db8::/32/s"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "1/"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "/1"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "192.0.2.0/33"')
        self.assertRaises(LoaderError, load_request_acl,
                          '[{"action": "DROP", "from": "::1/129"')

    def test_construct(self):
        RequestACL()

if __name__ == '__main__':
    unittest.main()
