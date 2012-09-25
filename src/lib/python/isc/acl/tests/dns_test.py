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
from pydnspp import *
from isc.acl.acl import LoaderError, Error, ACCEPT, REJECT, DROP
from isc.acl.dns import *

def get_sockaddr(address, port):
    '''This is a simple shortcut wrapper for getaddrinfo'''
    ai = socket.getaddrinfo(address, port, 0, socket.SOCK_DGRAM,
                            socket.IPPROTO_UDP, socket.AI_NUMERICHOST)[0]
    return ai[4]

def get_acl(prefix):
    '''This is a simple shortcut for creating an ACL containing single rule
    that accepts addresses for the given IP prefix (and reject any others
    by default)
    '''
    return REQUEST_LOADER.load('[{"action": "ACCEPT", "from": "' + \
                                   prefix + '"}]')

def get_acl_json(prefix):
    '''Same as get_acl, but this function passes a Python representation of
    JSON to the loader, not a string.'''
    json = [{"action": "ACCEPT"}]
    json[0]["from"] = prefix
    return REQUEST_LOADER.load(json)

# The following two are similar to the previous two, but use a TSIG key name
# instead of IP prefix.
def get_tsig_acl(key):
    return REQUEST_LOADER.load('[{"action": "ACCEPT", "key": "' + \
                                   key + '"}]')

def get_tsig_acl_json(key):
    json = [{"action": "ACCEPT"}]
    json[0]["key"] = key
    return REQUEST_LOADER.load(json)

# commonly used TSIG RDATA.  For the purpose of ACL checks only the key name
# matters; other parrameters are simply borrowed from some other tests, which
# can be anything for the purpose of the tests here.
TSIG_RDATA = TSIG("hmac-md5.sig-alg.reg.int. 1302890362 " + \
                      "300 16 2tra2tra2tra2tra2tra2g== " + \
                      "11621 0 0")

def get_context(address, key_name=None):
    '''This is a simple shortcut wrapper for creating a RequestContext
    object with a given IP address and optionally TSIG key  name.
    Port number doesn't matter in the test (as of the initial implementation),
    so it's fixed for simplicity.
    If key_name is not None, it internally creates a (faked) TSIG record
    and constructs a context with that key.  Note that only the key name
    matters for the purpose of ACL checks.
    '''
    tsig_record = None
    if key_name is not None:
        tsig_record = TSIGRecord(Name(key_name), TSIG_RDATA)
    return RequestContext(get_sockaddr(address, 53000), tsig_record)

# These are commonly used RequestContext object
CONTEXT4 = get_context('192.0.2.1')
CONTEXT6 = get_context('2001:db8::1')

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

        # Construct the context from IP address and a TSIG record.
        tsig_record = TSIGRecord(Name("key.example.com"), TSIG_RDATA)
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[192.0.2.1]:53001, ' + \
                             'key=key.example.com.>',
                         RequestContext(('192.0.2.1', 53001),
                                        tsig_record).__str__())

        # same with IPv6 address, just in case.
        self.assertEqual('<isc.acl.dns.RequestContext object, ' + \
                             'remote_addr=[2001:db8::1234]:53006, ' + \
                             'key=key.example.com.>',
                         RequestContext(('2001:db8::1234', 53006,
                                         0, 0), tsig_record).__str__())

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
        self.assertRaises(TypeError, RequestContext, ('192.0.2.1', 53), 0, 1)
        # type error for TSIG
        self.assertRaises(TypeError, RequestContext, ('192.0.2.1', 53), tsig=1)
        # tuple is not in the form of sockaddr
        self.assertRaises(TypeError, RequestContext, (0, 53))
        self.assertRaises(TypeError, RequestContext, ('192.0.2.1', 'http'))
        self.assertRaises(TypeError, RequestContext, ('::', 0, 'flow', 0))
        # invalid address
        self.assertRaises(Error, RequestContext, ('example.com', 5300))
        self.assertRaises(Error, RequestContext, ('192.0.2.1.1', 5300))
        self.assertRaises(Error, RequestContext, ('2001:db8:::1', 5300))

class RequestACLTest(unittest.TestCase):

    def test_direct_construct(self):
        self.assertRaises(Error, RequestACL)

    def test_request_loader(self):
        # these shouldn't raise an exception
        REQUEST_LOADER.load('[{"action": "DROP"}]')
        REQUEST_LOADER.load([{"action": "DROP"}])
        REQUEST_LOADER.load('[{"action": "DROP", "from": "192.0.2.1"}]')
        REQUEST_LOADER.load([{"action": "DROP", "from": "192.0.2.1"}])

        # Invalid types (note that arguments like '1' or '[]' is of valid
        # 'type' (but syntax error at a higher level)).  So we need to use
        # something that is not really JSON nor string.
        self.assertRaises(TypeError, REQUEST_LOADER.load, b'')

        # Incorrect number of arguments
        self.assertRaises(TypeError, REQUEST_LOADER.load,
                          '[{"action": "DROP"}]', 0)

    def test_bad_acl_syntax(self):
        # the following are derived from loader_test.cc
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '{}');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, {});
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '42');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, 42);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, 'true');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, True);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, 'null');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, None);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '"hello"');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, "hello");
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '[42]');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, [42]);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '["hello"]');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, ["hello"]);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '[[]]');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, [[]]);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '[true]');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, [True]);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '[null]');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, [None]);
        self.assertRaises(LoaderError, REQUEST_LOADER.load, '[{}]');
        self.assertRaises(LoaderError, REQUEST_LOADER.load, [{}]);

        # the following are derived from dns_test.cc
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "ACCEPT", "bad": "192.0.2.1"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "bad": "192.0.2.1"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "ACCEPT", "from": 4}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "from": 4}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "ACCEPT", "key": 1}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "key": 1}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "ACCEPT", "key": {}}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "key": {}}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "ACCEPT", "from": "bad"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "from": "bad"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "key": "bad..name"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "key": "bad..name"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "ACCEPT", "from": null}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "ACCEPT", "from": None}])

    def test_bad_acl_ipsyntax(self):
        # this test is derived from ip_check_unittest.cc
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "192.0.2.43/-1"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "192.0.2.43/-1"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "192.0.2.43//1"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "192.0.2.43//1"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "192.0.2.43/1/"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "192.0.2.43/1/"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "/192.0.2.43/1"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "/192.0.2.43/1"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "2001:db8::/xxxx"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "2001:db8::/xxxx"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "2001:db8::/32/s"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "2001:db8::/32/s"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "1/"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "1/"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "/1"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "/1"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "192.0.2.0/33"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "192.0.2.0/33"}])
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          '[{"action": "DROP", "from": "::1/129"}]')
        self.assertRaises(LoaderError, REQUEST_LOADER.load,
                          [{"action": "DROP", "from": "::1/129"}])

    def test_execute(self):
        # tests derived from dns_test.cc.  We don't directly expose checks
        # in the python wrapper, so we test it via execute().
        self.assertEqual(ACCEPT, get_acl('192.0.2.1').execute(CONTEXT4))
        self.assertEqual(ACCEPT, get_acl_json('192.0.2.1').execute(CONTEXT4))
        self.assertEqual(REJECT, get_acl('192.0.2.53').execute(CONTEXT4))
        self.assertEqual(REJECT, get_acl_json('192.0.2.53').execute(CONTEXT4))
        self.assertEqual(ACCEPT, get_acl('192.0.2.0/24').execute(CONTEXT4))
        self.assertEqual(ACCEPT, get_acl_json('192.0.2.0/24').execute(CONTEXT4))
        self.assertEqual(REJECT, get_acl('192.0.1.0/24').execute(CONTEXT4))
        self.assertEqual(REJECT, get_acl_json('192.0.1.0/24').execute(CONTEXT4))
        self.assertEqual(REJECT, get_acl('192.0.1.0/24').execute(CONTEXT4))
        self.assertEqual(REJECT, get_acl_json('192.0.1.0/24').execute(CONTEXT4))

        self.assertEqual(ACCEPT, get_acl('2001:db8::1').execute(CONTEXT6))
        self.assertEqual(ACCEPT, get_acl_json('2001:db8::1').execute(CONTEXT6))
        self.assertEqual(REJECT, get_acl('2001:db8::53').execute(CONTEXT6))
        self.assertEqual(REJECT, get_acl_json('2001:db8::53').execute(CONTEXT6))
        self.assertEqual(ACCEPT, get_acl('2001:db8::/64').execute(CONTEXT6))
        self.assertEqual(ACCEPT,
                         get_acl_json('2001:db8::/64').execute(CONTEXT6))
        self.assertEqual(REJECT, get_acl('2001:db8:1::/64').execute(CONTEXT6))
        self.assertEqual(REJECT,
                         get_acl_json('2001:db8:1::/64').execute(CONTEXT6))
        self.assertEqual(REJECT, get_acl('32.1.13.184').execute(CONTEXT6))
        self.assertEqual(REJECT, get_acl_json('32.1.13.184').execute(CONTEXT6))

        # TSIG checks, derived from dns_test.cc
        self.assertEqual(ACCEPT, get_tsig_acl('key.example.com').\
                             execute(get_context('192.0.2.1',
                                                 'key.example.com')))
        self.assertEqual(REJECT, get_tsig_acl_json('key.example.com').\
                             execute(get_context('192.0.2.1',
                                                 'badkey.example.com')))
        self.assertEqual(ACCEPT, get_tsig_acl('key.example.com').\
                             execute(get_context('2001:db8::1',
                                                 'key.example.com')))
        self.assertEqual(REJECT, get_tsig_acl_json('key.example.com').\
                             execute(get_context('2001:db8::1',
                                                 'badkey.example.com')))
        self.assertEqual(REJECT, get_tsig_acl('key.example.com').\
                             execute(CONTEXT4))
        self.assertEqual(REJECT, get_tsig_acl_json('key.example.com').\
                             execute(CONTEXT4))
        self.assertEqual(REJECT, get_tsig_acl('key.example.com').\
                             execute(CONTEXT6))
        self.assertEqual(REJECT, get_tsig_acl_json('key.example.com').\
                             execute(CONTEXT6))

        # A bit more complicated example, derived from resolver_config_unittest
        acl = REQUEST_LOADER.load('[ {"action": "ACCEPT", ' +
                                  '     "from": "192.0.2.1"},' +
                                  '    {"action": "REJECT",' +
                                  '     "from": "192.0.2.0/24"},' +
                                  '    {"action": "DROP",' +
                                  '     "from": "2001:db8::1"},' +
                                  ']')
        self.assertEqual(ACCEPT, acl.execute(CONTEXT4))
        self.assertEqual(REJECT, acl.execute(get_context('192.0.2.2')))
        self.assertEqual(DROP, acl.execute(get_context('2001:db8::1')))
        self.assertEqual(REJECT, acl.execute(get_context('2001:db8::2')))

        # same test using the JSON representation
        acl = REQUEST_LOADER.load([{"action": "ACCEPT", "from": "192.0.2.1"},
                                   {"action": "REJECT",
                                    "from": "192.0.2.0/24"},
                                   {"action": "DROP", "from": "2001:db8::1"}])
        self.assertEqual(ACCEPT, acl.execute(CONTEXT4))
        self.assertEqual(REJECT, acl.execute(get_context('192.0.2.2')))
        self.assertEqual(DROP, acl.execute(get_context('2001:db8::1')))
        self.assertEqual(REJECT, acl.execute(get_context('2001:db8::2')))

    def test_bad_execute(self):
        acl = get_acl('192.0.2.1')
        # missing parameter
        self.assertRaises(TypeError, acl.execute)
        # too many parameters
        self.assertRaises(TypeError, acl.execute, get_context('192.0.2.2'), 0)
        # type mismatch
        self.assertRaises(TypeError, acl.execute, 'bad parameter')

class RequestLoaderTest(unittest.TestCase):
    # Note: loading ACLs is tested in other test cases.

    def test_construct(self):
        # at least for now, we don't allow direct construction.
        self.assertRaises(Error, RequestLoader)

if __name__ == '__main__':
    unittest.main()
