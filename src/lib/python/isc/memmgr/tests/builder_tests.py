# Copyright (C) 2013  Internet Systems Consortium.
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
import select
import threading

import isc.log
from isc.memmgr.builder import *

class TestMemorySegmentBuilder(unittest.TestCase):
    def _create_builder_thread(self):
        (self._master_sock, self._builder_sock) = \
            socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM)

        self._builder_command_queue = []
        self._builder_response_queue = []

        self._builder_cv = threading.Condition()
        self._builder_lock = threading.Lock()

        self._builder = MemorySegmentBuilder(self._builder_sock,
                                             self._builder_cv,
                                             self._builder_lock,
                                             self._builder_command_queue,
                                             self._builder_response_queue)
        self._builder_thread = threading.Thread(target=self._builder.run)

    def setUp(self):
        self._create_builder_thread()

    def tearDown(self):
        # It's the tests' responsibility to stop and join the builder
        # thread if they start it.
        self.assertFalse(self._builder_thread.isAlive())

        self._master_sock.close()
        self._builder_sock.close()

    def test_bad_command(self):
        """Tests what happens when a bad command is passed to the
        MemorySegmentBuilder.
        """

        self._builder_thread.start()

        # Now that the builder thread is running, send it a bad
        # command. The thread should exit its main loop and be joinable.
        with self._builder_cv:
            with self._builder_lock:
                self._builder_command_queue.append('bad_command')
            self._builder_cv.notify_all()

        # Wait 5 seconds to receive a notification on the socket from
        # the builder.
        (reads, _, _) = select.select([self._master_sock], [], [], 5)
        self.assertTrue(self._master_sock in reads)

        # Reading 1 byte should not block us here, especially as the
        # socket is ready to read. It's a hack, but this is just a
        # testcase.
        got = self._master_sock.recv(1)
        self.assertEqual(got, b'x')

        # Wait 5 seconds at most for the main loop of the builder to
        # exit.
        self._builder_thread.join(5)
        self.assertFalse(self._builder_thread.isAlive())

        # The command queue must be cleared, and the response queue must
        # contain a response that a bad command was sent.
        with self._builder_lock:
            self.assertEqual(len(self._builder_command_queue), 0)
            self.assertEqual(len(self._builder_response_queue), 1)

            response = self._builder_response_queue[0]
            self.assertTrue(isinstance(response, tuple))
            self.assertTupleEqual(response, ('bad_command',))
            self._builder_response_queue.clear()

    def test_shutdown(self):
        """Tests that shutdown command exits the MemorySegmentBuilder
        loop.
        """

        self._builder_thread.start()

        # Now that the builder thread is running, send it the shutdown
        # command. The thread should exit its main loop and be joinable.
        with self._builder_cv:
            with self._builder_lock:
                self._builder_command_queue.append('shutdown')
                # Commands after 'shutdown' must be ignored.
                self._builder_command_queue.append('bad_command_1')
                self._builder_command_queue.append('bad_command_2')
            self._builder_cv.notify_all()

        # Wait 5 seconds at most for the main loop of the builder to
        # exit.
        self._builder_thread.join(5)
        self.assertFalse(self._builder_thread.isAlive())

        # The command queue must be cleared, and the response queue must
        # be untouched (we don't use it in this test).
        with self._builder_lock:
            self.assertEqual(len(self._builder_command_queue), 0)
            self.assertEqual(len(self._builder_response_queue), 0)

if __name__ == "__main__":
    isc.log.init("bind10-test")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
