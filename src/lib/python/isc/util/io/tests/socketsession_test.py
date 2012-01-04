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

import os, signal, socket, unittest
from socket import AF_INET, AF_INET6, SOCK_STREAM, SOCK_DGRAM, IPPROTO_UDP, \
    IPPROTO_TCP
from isc.util.io.socketsession import *

TESTDATA_OBJDIR = os.getenv("TESTDATAOBJDIR")
TEST_UNIX_FILE = TESTDATA_OBJDIR + '/ssessiontest.unix'
TEST_DATA = b'BIND10 test'
TEST_PORT = 53535

class TestForwarder(unittest.TestCase):
    '''In general, this is a straightforward port of the C++ counterpart.

    In some cases test cases are simplified or have Python specific cases.

    '''

    def setUp(self):
        self.forwarder = SocketSessionForwarder(TEST_UNIX_FILE)
        if os.path.exists(TEST_UNIX_FILE):
            os.unlink(TEST_UNIX_FILE)
        self.large_text = b'a' * 65535

    def tearDown(self):
        if os.path.exists(TEST_UNIX_FILE):
            os.unlink(TEST_UNIX_FILE)

    def start_listen(self):
        self.listen_sock = socket.socket(socket.AF_UNIX, SOCK_STREAM, 0)
        self.listen_sock.bind(TEST_UNIX_FILE)
        self.listen_sock.listen(10)

    def accept_forwarder(self):
        self.listen_sock.setblocking(False)
        s, _ = self.listen_sock.accept()
        s.setblocking(True)
        return s

    def test_init(self):
        # check bad arguments.  valid cases will covered in other tests.
        self.assertRaises(TypeError, SocketSessionForwarder, 1)
        self.assertRaises(TypeError, SocketSessionForwarder,
                          'test.unix', 'test.unix')

    def test_badpush(self):
        # bad numbers of parameters
        self.assertRaises(TypeError, self.forwarder.push, 1)
        self.assertRaises(TypeError, self.forwarder.push, 0, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('127.0.0.1', 53),
                          ('192.0.2.1', 5300), TEST_DATA, 0)
        # contain a bad type of parameter
        self.assertRaises(TypeError, self.forwarder.push, 0, 'AF_INET',
                          SOCK_DGRAM, IPPROTO_UDP, ('127.0.0.1', 53),
                          ('192.0.2.1', 5300), TEST_DATA)
        # bad local address
        self.assertRaises(TypeError, self.forwarder.push, 0, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('127.0.0..1', 53),
                            ('192.0.2.1', 5300), TEST_DATA)
        self.assertRaises(TypeError, self.forwarder.push, 0, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, '127.0.0.1',
                            ('192.0.2.1', 5300), TEST_DATA)
        # bad remote address
        self.assertRaises(TypeError, self.forwarder.push, 0, AF_INET6,
                          SOCK_DGRAM, IPPROTO_UDP, ('2001:db8::1', 53),
                            ('2001:db8:::3', 5300), TEST_DATA)

        # push before connect
        self.assertRaises(TypeError, self.forwarder.push, 0, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('192.0.2.1', 53),
                          ('192.0.2.2', 53), TEST_DATA)

        # Now connect the forwarder for the rest of tests
        self.start_listen()
        self.forwarder.connect_to_receiver()

        # Inconsistent address family
        self.assertRaises(TypeError, self.forwarder.push, 1, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('2001:db8::1', 53, 0, 1),
                          ('192.0.2.2', 53), TEST_DATA)
        self.assertRaises(TypeError, self.forwarder.push, 1, AF_INET6,
                          SOCK_DGRAM, IPPROTO_UDP, ('2001:db8::1', 53, 0, 1),
                          ('192.0.2.2', 53), TEST_DATA)

        # Empty data: we reject them at least for now
        self.assertRaises(TypeError, self.forwarder.push, 1, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('192.0.2.1', 53),
                          ('192.0.2.2', 53), b'')

        # Too big data: we reject them at least for now
        self.assertRaises(TypeError, self.forwarder.push, 1, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('192.0.2.1', 53),
                          ('192.0.2.2', 53), b'd' * 65536)

        # Close the receptor before push.  It will result in SIGPIPE (should be
        # ignored) and EPIPE, which will be converted to SocketSessionError.
        self.listen_sock.close()
        self.assertRaises(SocketSessionError, self.forwarder.push, 1, AF_INET,
                          SOCK_DGRAM, IPPROTO_UDP, ('192.0.2.1', 53),
                          ('192.0.2.2', 53), TEST_DATA)

    def create_socket(self, family, type, protocol, addr, do_listen):
        s = socket.socket(family, type, protocol)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(addr)
        if do_listen and protocol == IPPROTO_TCP:
            s.listen(1)
        return s

    def check_push_and_pop(self, family, type, protocol, local, remote,
                           data, new_connection):
        sock = self.create_socket(family, type, protocol, local, True)
        fwd_fd = sock.fileno()
        if protocol == IPPROTO_TCP:
            client_addr = ('::1', 0, 0, 0) if family == AF_INET6 \
                else ('127.0.0.1', 0)
            client_sock = self.create_socket(family, type, protocol,
                                             client_addr, False)
            client_sock.setblocking(False)
            try:
                client_sock.connect(local)
            except socket.error:
                pass
            server_sock, _ = sock.accept()
            fwd_fd = server_sock.fileno()

        # If a new connection is required, start the "server", have the
        # internal forwarder connect to it, and then internally accept it.
        if new_connection:
            self.start_listen()
            self.forwarder.connect_to_receiver()
            self.accept_sock = self.accept_forwarder()

        # Then push one socket session via the forwarder.
        self.forwarder.push(fwd_fd, family, type, protocol, local, remote,
                            data)

        # Pop the socket session we just pushed from a local receiver, and
        # check the content.
        receiver = SocketSessionReceiver(self.accept_sock)
        signal.alarm(1)
        sock_session = receiver.pop()
        signal.alarm(0)
        passed_sock = sock_session[0]
        self.assertNotEqual(fwd_fd, passed_sock.fileno())
        self.assertEqual(family, passed_sock.family)
        self.assertEqual(type, passed_sock.type)
        self.assertEqual(protocol, passed_sock.proto)
        self.assertEqual(local, sock_session[1])
        self.assertEqual(remote, sock_session[2])
        self.assertEqual(data, sock_session[3])

        # Check if the passed FD is usable by sending some data from it.
        passed_sock.setblocking(True)
        if protocol == IPPROTO_UDP:
            self.assertEqual(len(TEST_DATA), passed_sock.sendto(TEST_DATA,
                                                                local))
            sock.settimeout(10)
            self.assertEqual(TEST_DATA, sock.recvfrom(len(TEST_DATA))[0])
        else:
            server_sock.close()
            self.assertEqual(len(TEST_DATA), passed_sock.send(TEST_DATA))
            client_sock.setblocking(True)
            client_sock.settimeout(10)
            self.assertEqual(TEST_DATA, client_sock.recv(len(TEST_DATA)))

    def test_push_and_pop(self):
        # This is a straightforward port of C++ pushAndPop test.
        local6 = ('::1', TEST_PORT, 0, 0)
        remote6 = ('2001:db8::1', 5300, 0, 0)
        self.check_push_and_pop(AF_INET6, SOCK_DGRAM, IPPROTO_UDP,
                                local6, remote6, TEST_DATA, True)
        self.check_push_and_pop(AF_INET6, SOCK_STREAM, IPPROTO_TCP,
                                local6, remote6, TEST_DATA, False)

        local4 = ('127.0.0.1', TEST_PORT)
        remote4 = ('192.0.2.2', 5300)
        self.check_push_and_pop(AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                local4, remote4, TEST_DATA, False)
        self.check_push_and_pop(AF_INET, SOCK_STREAM, IPPROTO_TCP,
                                local4, remote4, TEST_DATA, False)

        self.check_push_and_pop(AF_INET6, SOCK_DGRAM, IPPROTO_UDP,
                                local6, remote6, self.large_text, False)
        self.check_push_and_pop(AF_INET6, SOCK_STREAM, IPPROTO_TCP,
                                local6, remote6, self.large_text, False)
        self.check_push_and_pop(AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                local4, remote4, self.large_text, False)
        self.check_push_and_pop(AF_INET, SOCK_STREAM, IPPROTO_TCP,
                                local4, remote4, self.large_text, False)

        # Python specific: check for an IPv6 scoped address with non 0
        # scope (zone) ID
        scope6 = ('fe80::1', TEST_PORT, 0, 1)
        self.check_push_and_pop(AF_INET6, SOCK_DGRAM, IPPROTO_UDP,
                                local6, scope6, TEST_DATA, False)

    def test_push_too_fast(self):
        # A straightforward port of C++ pushTooFast test.
        def multi_push(forwarder, addr, data):
            for i in range(0, 10):
                forwarder.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP, addr,
                               addr, data)
        self.start_listen()
        self.forwarder.connect_to_receiver()
        self.assertRaises(SocketSessionError, multi_push, self.forwarder,
                          ('192.0.2.1', 53), self.large_text)

    def test_bad_pop(self):
        # This is a subset of C++ badPop test.  We only check pop() raises
        # SocketSessionError when it internally fails to get the FD.
        # Other cases would require passing a valid FD from the test,
        # which would make the test too complicated.  As a wrapper checking
        # one common failure case should be reasonably sufficient.

        self.start_listen()
        s = socket.socket(socket.AF_UNIX, SOCK_STREAM, 0)
        s.setblocking(False)
        s.connect(TEST_UNIX_FILE)
        accept_sock = self.accept_forwarder()
        receiver = SocketSessionReceiver(accept_sock)
        s.close()
        self.assertRaises(SocketSessionError, receiver.pop)

class TestReceiver(unittest.TestCase):
    # We only check a couple of failure cases on construction.  Valid cases
    # are covered in TestForwarder.

    def test_bad_init(self):
        class FakeSocket:
            # pretending to be th standard socket class, but its fileno() is
            # bogus.
            def fileno(self):
                return None
        self.assertRaises(TypeError, SocketSessionReceiver, 1)
        self.assertRaises(TypeError, SocketSessionReceiver, FakeSocket())

if __name__ == '__main__':
    unittest.main()
