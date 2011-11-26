# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
import isc.log
import isc.bind10.socket_cache
from isc.net.addr import IPAddr
import os

class Test(unittest.TestCase):
    """
    Base for the tests here. It replaces the os.close method.
    """
    def setUp(self):
        self._closes = []
        isc.bind10.socket_cache.os.close = self.__close

    def tearDown(self):
        # This is not very clean solution. But when the test stops
        # to exist, the method must not be used to destroy the
        # object any more. And we can't restore the os.close here
        # as we never work with real sockets here.
        isc.bind10.socket_cache.os.close = lambda fd: None

    def __close(self, fd):
        """
        Just log a close was called.
        """
        self._closes.append(fd)

class SocketTest(Test):
    """
    Test for the Socket class.
    """
    def setUp(self):
        """
        Creates the socket to be tested.

        It has 'Test' as the protocol , which means the
        fileno file descriptor will not be closed on deletion.

        It also creates other useful test variables.
        """
        Test.setUp(self)
        self.__address = IPAddr("192.0.2.1")
        self.__socket = isc.bind10.socket_cache.Socket('Test', self.__address,
                                                       1024, 42)

    def test_init(self):
        """
        Checks the intrnals of the cache just after the creation.
        """
        self.assertEqual('Test', self.__socket.protocol)
        self.assertEqual(self.__address, self.__socket.address)
        self.assertEqual(1024, self.__socket.port)
        self.assertEqual(42, self.__socket.fileno)
        self.assertEqual({}, self.__socket.active_tokens)
        self.assertEqual({}, self.__socket.shares)
        self.assertEqual(set(), self.__socket.waiting_tokens)

    def test_del(self):
        """
        Check it closes the socket when removed.
        """
        # This should make the refcount 0 and call the descructor
        # right away
        self.__socket = None
        self.assertEqual([42], self._closes)

    def test_share_modes(self):
        """
        Test the share mode compatibility check function.
        """
        modes = ['NO', 'SAMEAPP', 'ANY']
        # If there are no shares, it is compatible with everything.
        for mode in modes:
            self.assertTrue(self.__socket.shareCompatible(mode, 'anything'))

        # There's an NO already, so it is incompatible with everything.
        self.__socket.shares = {'token': ('NO', 'anything')}
        for mode in modes:
            self.assertFalse(self.__socket.shareCompatible(mode, 'anything'))

        # If there's SAMEAPP, it is compatible with ANY and SAMEAPP with the
        # same name.
        self.__socket.shares = {'token': ('SAMEAPP', 'app')}
        self.assertFalse(self.__socket.shareCompatible('NO', 'app'))
        self.assertFalse(self.__socket.shareCompatible('SAMEAPP', 'something'))
        self.assertTrue(self.__socket.shareCompatible('SAMEAPP', 'app'))
        self.assertTrue(self.__socket.shareCompatible('ANY', 'app'))
        self.assertFalse(self.__socket.shareCompatible('ANY', 'something'))

        # If there's ANY, then ANY and SAMEAPP with the same name is compatible
        self.__socket.shares = {'token': ('ANY', 'app')}
        self.assertFalse(self.__socket.shareCompatible('NO', 'app'))
        self.assertFalse(self.__socket.shareCompatible('SAMEAPP', 'something'))
        self.assertTrue(self.__socket.shareCompatible('SAMEAPP', 'app'))
        self.assertTrue(self.__socket.shareCompatible('ANY', 'something'))

        # In case there are multiple already inside
        self.__socket.shares = {
            'token': ('ANY', 'app'),
            'another': ('SAMEAPP', 'app')
        }
        self.assertFalse(self.__socket.shareCompatible('NO', 'app'))
        self.assertFalse(self.__socket.shareCompatible('SAMEAPP', 'something'))
        self.assertTrue(self.__socket.shareCompatible('SAMEAPP', 'app'))
        self.assertFalse(self.__socket.shareCompatible('ANY', 'something'))
        self.assertTrue(self.__socket.shareCompatible('ANY', 'app'))

        # Invalid inputs are rejected
        self.assertRaises(ValueError, self.__socket.shareCompatible, 'bad',
                          'bad')

class SocketCacheTest(Test):
    """
    Some tests for the isc.bind10.socket_cache.Cache.

    This class, as well as being the testcase, pretends to be the
    socket creator so it can hijack all the requests for sockets.
    """
    def setUp(self):
        """
        Creates the cache for tests with us being the socket creator.
        """
        Test.setUp(self)
        self.__cache = isc.bind10.socket_cache.Cache(self)

    def test_init(self):
        """
        Checks the internals of the cache just after the creation.
        """
        self.assertEqual(self, self.__cache._creator)
        self.assertEqual({}, self.__cache._waiting_tokens)
        self.assertEqual({}, self.__cache._active_tokens)
        self.assertEqual({}, self.__cache._active_apps)
        self.assertEqual({}, self.__cache._sockets)
        self.assertEqual(set(), self.__cache._live_tokens)

if __name__ == '__main__':
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
