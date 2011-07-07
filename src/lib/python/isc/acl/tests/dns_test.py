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
import socket
from isc.acl.acl import LoaderError, Error
from isc.acl.dns import *

def get_sockaddr(address, port):
    '''This is a simple shortcut wrapper for getaddrinfo'''
    ai = socket.getaddrinfo(address, port, 0, 0, 0, socket.AI_NUMERICHOST)[0]
    return ai[4]

class RequestContextTest(unittest.TestCase):

    def test_construct(self):
        # Construct the context from IPv4/IPv6 addresses, check the object
        # by printing it.
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[192.0.2.1]:53001>',
                         RequestContext(('192.0.2.1', 53001)).__str__())
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[2001:db8::1234]:53006>',
                         RequestContext(('2001:db8::1234', 53006,
                                         0, 0)).__str__())

        # Unusual case: port number overflows (this constructor allows that,
        # although it should be rare anyway; the socket address should
        # normally come from the Python socket module.
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[192.0.2.1]:0>',
                         RequestContext(('192.0.2.1', 65536)).__str__())

        # same test using socket.getaddrinfo() to ensure it accepts the sock
        # address representation used in the Python socket module.
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[192.0.2.1]:53001>',
                         RequestContext(get_sockaddr('192.0.2.1',
                                                     53001)).__str__())
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[2001:db8::1234]:53006>',
                         RequestContext(get_sockaddr('2001:db8::1234',
                                                     53006)).__str__())

        #
        # Invalid parameters (in our expected usage this should not happen
        # because the sockaddr would come from the Python socket module, but
        # validation should still be performed correctly)
        #
        # not a tuple
        self.assertRaises(TypeError, RequestContext, 1)
        # invalid number of parameters
        self.assertRaises(TypeError, RequestContext, ('192.0.2.1', 53), 0)
        # tuple is not in the form of sockaddr
        self.assertRaises(TypeError, RequestContext, (0, 53))
        self.assertRaises(TypeError, RequestContext, ('192.0.2.1', 'http'))
        self.assertRaises(TypeError, RequestContext, ('::', 0, 'flow', 0))
        # invalid address
        self.assertRaises(Error, RequestContext, ('example.com', 5300))
        self.assertRaises(Error, RequestContext, ('192.0.2.1.1', 5300))
        self.assertRaises(Error, RequestContext, ('2001:db8:::1', 5300))

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
