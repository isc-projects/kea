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

        It also creates other useful test variables.
        """
        Test.setUp(self)
        self.__address = IPAddr("192.0.2.1")
        self.__socket = isc.bind10.socket_cache.Socket('UDP', self.__address,
                                                       1024, 42)

    def test_init(self):
        """
        Checks the intrnals of the cache just after the creation.
        """
        self.assertEqual('UDP', self.__socket.protocol)
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
            self.assertTrue(self.__socket.share_compatible(mode, 'anything'))

        # There's an NO already, so it is incompatible with everything.
        self.__socket.shares = {'token': ('NO', 'anything')}
        for mode in modes:
            self.assertFalse(self.__socket.share_compatible(mode, 'anything'))

        # If there's SAMEAPP, it is compatible with ANY and SAMEAPP with the
        # same name.
        self.__socket.shares = {'token': ('SAMEAPP', 'app')}
        self.assertFalse(self.__socket.share_compatible('NO', 'app'))
        self.assertFalse(self.__socket.share_compatible('SAMEAPP',
                                                        'something'))
        self.assertTrue(self.__socket.share_compatible('SAMEAPP', 'app'))
        self.assertTrue(self.__socket.share_compatible('ANY', 'app'))
        self.assertFalse(self.__socket.share_compatible('ANY', 'something'))

        # If there's ANY, then ANY and SAMEAPP with the same name is compatible
        self.__socket.shares = {'token': ('ANY', 'app')}
        self.assertFalse(self.__socket.share_compatible('NO', 'app'))
        self.assertFalse(self.__socket.share_compatible('SAMEAPP',
                                                        'something'))
        self.assertTrue(self.__socket.share_compatible('SAMEAPP', 'app'))
        self.assertTrue(self.__socket.share_compatible('ANY', 'something'))

        # In case there are multiple already inside
        self.__socket.shares = {
            'token': ('ANY', 'app'),
            'another': ('SAMEAPP', 'app')
        }
        self.assertFalse(self.__socket.share_compatible('NO', 'app'))
        self.assertFalse(self.__socket.share_compatible('SAMEAPP',
                                                        'something'))
        self.assertTrue(self.__socket.share_compatible('SAMEAPP', 'app'))
        self.assertFalse(self.__socket.share_compatible('ANY', 'something'))
        self.assertTrue(self.__socket.share_compatible('ANY', 'app'))

        # Invalid inputs are rejected
        self.assertRaises(ValueError, self.__socket.share_compatible, 'bad',
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
        self.__socket = isc.bind10.socket_cache.Socket('UDP', self.__address,
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

    def test_drop_application(self):
        """
        Test that a drop_application calls drop_socket on all the sockets
        held by the application.
        """
        sockets = set()
        def drop_socket(token):
            sockets.add(token)
        # Mock the drop_socket so we know it is called
        self.__cache.drop_socket = drop_socket
        self.assertRaises(ValueError, self.__cache.drop_application,
                          13)
        self.assertEqual(set(), sockets)
        # Put the tokens into active_apps. Nothing else should be touched
        # by this call, so leave it alone.
        self.__cache._active_apps = {
            1: set(['t1', 't2']),
            2: set(['t3'])
        }
        self.__cache.drop_application(1)
        # We don't check the _active_apps, as it would be cleaned by
        # drop_socket and we removed it.
        self.assertEqual(set(['t1', 't2']), sockets)

    def test_drop_socket(self):
        """
        Test the drop_socket call. It tests:
        * That a socket that still has something to keep it alive is left alive
          (both waiting and active).
        * If not, it is deleted.
        * All bookkeeping data around are properly removed.
        * Of course the exception.
        """
        self.assertRaises(ValueError, self.__cache.drop_socket, "bad token")
        self.__socket.active_tokens = {'t1': 1}
        self.__socket.waiting_tokens = set(['t2'])
        self.__socket.shares = {'t1': ('ANY', 'app1'), 't2': ('ANY', 'app2')}
        self.__cache._waiting_tokens = {'t2': self.__socket}
        self.__cache._active_tokens = {'t1': self.__socket}
        self.__cache._sockets = {'UDP': {'192.0.2.1': {1024: self.__socket}}}
        self.__cache._live_tokens = set(['t1', 't2'])
        self.__cache._active_apps = {1: set(['t1'])}
        # We can't drop what wasn't picket up yet
        self.assertRaises(ValueError, self.__cache.drop_socket, 't2')
        self.assertEqual({'t1': 1}, self.__socket.active_tokens)
        self.assertEqual(set(['t2']), self.__socket.waiting_tokens)
        self.assertEqual({'t1': ('ANY', 'app1'), 't2': ('ANY', 'app2')},
                         self.__socket.shares)
        self.assertEqual({'t2': self.__socket}, self.__cache._waiting_tokens)
        self.assertEqual({'t1': self.__socket}, self.__cache._active_tokens)
        self.assertEqual({'UDP': {'192.0.2.1': {1024: self.__socket}}},
                         self.__cache._sockets)
        self.assertEqual(set(['t1', 't2']), self.__cache._live_tokens)
        self.assertEqual({1: set(['t1'])}, self.__cache._active_apps)
        self.assertEqual([], self._closes)
        # If we drop this, it survives because it waits for being picked up
        self.__cache.drop_socket('t1')
        self.assertEqual({}, self.__socket.active_tokens)
        self.assertEqual(set(['t2']), self.__socket.waiting_tokens)
        self.assertEqual({'t2': ('ANY', 'app2')}, self.__socket.shares)
        self.assertEqual({}, self.__cache._active_tokens)
        self.assertEqual({'UDP': {'192.0.2.1': {1024: self.__socket}}},
                         self.__cache._sockets)
        self.assertEqual(set(['t2']), self.__cache._live_tokens)
        self.assertEqual({}, self.__cache._active_apps)
        self.assertEqual([], self._closes)
        # Fill it again, now two applications having the same socket
        self.__socket.active_tokens = {'t1': 1, 't2': 2}
        self.__socket.waiting_tokens = set()
        self.__socket.shares = {'t1': ('ANY', 'app1'), 't2': ('ANY', 'app2')}
        self.__cache._waiting_tokens = {}
        self.__cache._active_tokens = {
            't1': self.__socket,
            't2': self.__socket
        }
        self.__cache._live_tokens = set(['t1', 't2', 't3'])
        self.assertEqual([], self._closes)
        # We cheat here little bit, the t3 doesn't exist enywhere else, but
        # we need to check the app isn't removed too soon and it shouldn't
        # matter anywhere else, so we just avoid the tiresome filling in
        self.__cache._active_apps = {1: set(['t1', 't3']), 2: set(['t2'])}
        # Drop it as t1. It should still live.
        self.__cache.drop_socket('t1')
        self.assertEqual({'t2': 2}, self.__socket.active_tokens)
        self.assertEqual(set(), self.__socket.waiting_tokens)
        self.assertEqual({'t2': ('ANY', 'app2')}, self.__socket.shares)
        self.assertEqual({}, self.__cache._waiting_tokens)
        self.assertEqual({'t2': self.__socket}, self.__cache._active_tokens)
        self.assertEqual({'UDP': {'192.0.2.1': {1024: self.__socket}}},
                         self.__cache._sockets)
        self.assertEqual(set(['t3', 't2']), self.__cache._live_tokens)
        self.assertEqual({1: set(['t3']), 2: set(['t2'])},
                         self.__cache._active_apps)
        self.assertEqual([], self._closes)
        # Drop it again, from the other application. It should get removed
        # and closed.
        self.__cache.drop_socket('t2')
        self.assertEqual({}, self.__socket.active_tokens)
        self.assertEqual(set(), self.__socket.waiting_tokens)
        self.assertEqual({}, self.__socket.shares)
        self.assertEqual({}, self.__cache._waiting_tokens)
        self.assertEqual({}, self.__cache._active_tokens)
        self.assertEqual({}, self.__cache._sockets)
        self.assertEqual(set(['t3']), self.__cache._live_tokens)
        self.assertEqual({1: set(['t3'])}, self.__cache._active_apps)
        # The cache doesn't hold the socket. So when we remove it ourself,
        # it should get closed.
        self.__socket = None
        self.assertEqual([42], self._closes)

if __name__ == '__main__':
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
