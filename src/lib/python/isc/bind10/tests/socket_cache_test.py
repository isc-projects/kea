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
import isc.bind10.sockcreator
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

        Also creates some more variables for testing.
        """
        Test.setUp(self)
        self.__cache = isc.bind10.socket_cache.Cache(self)
        self.__address = IPAddr("192.0.2.1")
        self.__socket = isc.bind10.socket_cache.Socket('Test', self.__address,
                                                       1024, 42)
        self.__get_socket_called = False

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

    def get_socket(self, address, port, socktype):
        """
        Pretend to be a socket creator.

        This expects to be called with the _address, port 1024 and 'UDP'.

        Returns 42 and notes down it was called.
        """
        self.assertEqual(self.__address, address)
        self.assertEqual(1024, port)
        self.assertEqual('UDP', socktype)
        self.__get_socket_called = True
        return 42

    def test_get_token_cached(self):
        """
        Check the behaviour of get_token when the requested socket is already
        cached inside.
        """
        self.__cache._sockets = {
            'UDP': {'192.0.2.1': {1024: self.__socket}}
        }
        token = self.__cache.get_token('UDP', self.__address, 1024, 'ANY',
                                       'test')
        # It didn't call get_socket
        self.assertFalse(self.__get_socket_called)
        # It returned something
        self.assertIsNotNone(token)
        # The token is both in the waiting sockets and the live tokens
        self.assertEqual({token: self.__socket}, self.__cache._waiting_tokens)
        self.assertEqual(set([token]), self.__cache._live_tokens)
        # The token got the new share to block any relevant queries
        self.assertEqual({token: ('ANY', 'test')}, self.__socket.shares)
        # The socket knows the token is waiting in it
        self.assertEqual(set([token]), self.__socket.waiting_tokens)

        # If we request one more, with incompatible share, it is rejected
        self.assertRaises(isc.bind10.socket_cache.ShareError,
                          self.__cache.get_token, 'UDP', self.__address, 1024,
                          'NO', 'test')
        # The internals are not changed, so the same checks
        self.assertEqual({token: self.__socket}, self.__cache._waiting_tokens)
        self.assertEqual(set([token]), self.__cache._live_tokens)
        self.assertEqual({token: ('ANY', 'test')}, self.__socket.shares)
        self.assertEqual(set([token]), self.__socket.waiting_tokens)

    def test_get_token_uncached(self):
        """
        Check a new socket is created when a corresponding one is missing.
        """
        token = self.__cache.get_token('UDP', self.__address, 1024, 'ANY',
                                       'test')
        # The get_socket was called
        self.assertTrue(self.__get_socket_called)
        # It returned something
        self.assertIsNotNone(token)
        # Get the socket and check it looks OK
        socket = self.__cache._waiting_tokens[token]
        self.assertEqual(self.__address, socket.address)
        self.assertEqual(1024, socket.port)
        self.assertEqual(42, socket.fileno)
        self.assertEqual('UDP', socket.protocol)
        # The socket is properly cached
        self.assertEqual({
            'UDP': {'192.0.2.1': {1024: socket}}
        }, self.__cache._sockets)
        # The token is both in the waiting sockets and the live tokens
        self.assertEqual({token: socket}, self.__cache._waiting_tokens)
        self.assertEqual(set([token]), self.__cache._live_tokens)
        # The token got the new share to block any relevant queries
        self.assertEqual({token: ('ANY', 'test')}, socket.shares)
        # The socket knows the token is waiting in it
        self.assertEqual(set([token]), socket.waiting_tokens)

    def test_get_token_excs(self):
        """
        Test that it is handled properly if the socket creator raises
        some exceptions.
        """
        def raiseCreatorError(fatal):
            raise isc.bind10.sockcreator.CreatorError('test error', fatal)
        # First, fatal socket creator errors are passed through
        self.get_socket = lambda addr, port, proto: raiseCreatorError(True)
        self.assertRaises(isc.bind10.sockcreator.CreatorError,
                          self.__cache.get_token, 'UDP', self.__address, 1024,
                          'NO', 'test')
        # And nonfatal are converted to SocketError
        self.get_socket = lambda addr, port, proto: raiseCreatorError(False)
        self.assertRaises(isc.bind10.socket_cache.SocketError,
                          self.__cache.get_token, 'UDP', self.__address, 1024,
                          'NO', 'test')

    def test_get_socket(self):
        """
        Test that we can pickup a socket if we know a token.
        """
        token = "token"
        app = 13
        # No socket prepared there
        self.assertRaises(ValueError, self.__cache.get_socket, token, app)
        # Not changed
        self.assertEqual({}, self.__cache._active_tokens)
        self.assertEqual({}, self.__cache._active_apps)
        self.assertEqual({}, self.__cache._sockets)
        self.assertEqual(set(), self.__cache._live_tokens)
        # Prepare a token there
        self.__socket.waiting_tokens = set([token])
        self.__socket.shares = {token: ('ANY', 'app')}
        self.__cache._waiting_tokens = {token: self.__socket}
        self.__cache._sockets = {'UDP': {'192.0.2.1': {1024: self.__socket}}}
        self.__cache._live_tokens = set([token])
        socket = self.__cache.get_socket(token, app)
        # Received the fileno
        self.assertEqual(42, socket)
        # It moved from waiting to active ones
        self.assertEqual({}, self.__cache._waiting_tokens)
        self.assertEqual({token: self.__socket}, self.__cache._active_tokens)
        self.assertEqual({13: set([token])}, self.__cache._active_apps)
        self.assertEqual(set([token]), self.__cache._live_tokens)
        self.assertEqual(set(), self.__socket.waiting_tokens)
        self.assertEqual({token: 13}, self.__socket.active_tokens)
        # Trying to get it again fails
        self.assertRaises(ValueError, self.__cache.get_socket, token, app)

if __name__ == '__main__':
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
