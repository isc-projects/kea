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

"""
In this test file, we actually start msgq as a process and test it
as a whole. It may be considered a system test instead of unit test,
but apart from the terminology, we don't care much. We need to test
the message queue works as expected, together with the libraries.

In each test, we first start a timeout (because we do some waits
for messages and if they wouldn't come, the test could block indefinitely).
The timeout is long, because it is for the case the test fails.

We then start the msgq and wait for the socket file to appear
(that should indicate it is ready to receive connections). Then the
actual test starts. After the test, we kill it and remove the test file.

We also register signal handlers for many signals. Even in the case
the test is interrupted or crashes, we should ensure the message queue
itself is terminated.
"""

import unittest
import os
import signal
import sys
import subprocess
import time

import isc.log
import isc.cc.session
from isc.cc.proto_defs import *

# Due to problems with too long path on build bots, we place the socket
# into the top-level build directory. That is ugly, but works.
SOCKET_PATH = os.path.abspath(os.environ['B10_FROM_BUILD'] + '/msgq.sock')
MSGQ_PATH = os.environ['B10_FROM_BUILD'] + '/src/bin/msgq/run_msgq.sh'
TIMEOUT = 15 # Some long time (seconds), for single test.

class MsgqRunTest(unittest.TestCase):
    def setUp(self):
        """
        As described above - check the socket file does not exist.
        Then register signals and timeouts. Finally, launch msgq
        and wait for it to start.
        """
        self.__msgq = None
        self.__opened_connections = []
        # A precondition check
        self.assertFalse(os.path.exists(SOCKET_PATH))
        signal.alarm(TIMEOUT)
        self.__orig_signals = {}
        # Register handlers for many signals. Most of them probably
        # can't happen in python, but we register them anyway just to be
        # safe.
        for sig in [signal.SIGHUP, signal.SIGINT, signal.SIGQUIT,
            signal.SIGILL, signal.SIGTRAP, signal.SIGABRT, signal.SIGBUS,
            signal.SIGFPE, signal.SIGALRM, signal.SIGTERM]:
            self.__orig_signals[sig] = signal.signal(sig, self.__signal)
        # Start msgq
        self.__msgq = subprocess.Popen([MSGQ_PATH, '-s', SOCKET_PATH],
                                       close_fds=True)
        # Some testing data
        self.__no_recpt = {"result": [-1, "No such recipient"]}
        # Wait for it to become ready (up to the alarm-set timeout)
        connection = None
        while not connection:
            try:
                # If the msgq is ready, this'll succeed. If not, it'll throw
                # session error.
                connection = isc.cc.session.Session(SOCKET_PATH)
            except isc.cc.session.SessionError:
                time.sleep(0.1) # Retry after a short time
        # We have the connection now, that means it works. Close this
        # connection, we won't use it. Each test gets enough new connections
        # of its own.
        connection.close()

    def __message(self, data):
        """
        Provide some testing message. The data will be included in it, so
        several different messages can be created.
        """
        return {"Message": "Text", "Data": data}

    def tearDown(self):
        """
        Perform cleanup after the test.
        """
        self.__cleanup()

    def __signal(self, signal, frame):
        """
        Called from a signal handler. We perform some cleanup, output
        a complain and terminate with error.
        """
        self.__cleanup()
        sys.stderr.write("Test terminating from signal " + str(signal) +
                         " in " + str(frame) + "\n")
        sys.exit(1)

    def __cleanup(self):
        """
        Kill msgq (if running) and restore original signal handlers.
        """
        # Remove the socket (as we kill, msgq might not clean up)
        for conn in self.__opened_connections:
            conn.close()
        self.__opened_connections = []
        if self.__msgq:
            self.__msgq.kill()
            self.__msgq = None
        if os.path.exists(SOCKET_PATH):
            os.unlink(SOCKET_PATH)
        for sig in self.__orig_signals:
            signal.signal(sig, self.__orig_signals[sig])
        # Cancel timeout (so someone else is not hit by it)
        signal.alarm(0)

    def __get_connection(self):
        """
        Create a connection to the daemon and make sure it is properly closed
        at the end of the test.
        """
        connection = isc.cc.session.Session(SOCKET_PATH)
        self.__opened_connections.append(connection)
        return connection

    def test_send_direct(self):
        """
        Connect twice to msgq, send a message from one to another using direct
        l-name and see it comes.
        """
        # Create the connections
        conn1 = self.__get_connection()
        conn2 = self.__get_connection()
        # Send the message
        lname1 = conn1.lname
        conn2.group_sendmsg(self.__message(1), "*", to=lname1)
        # Receive the message and see it contains correct data
        (msg, env) = conn1.group_recvmsg(nonblock=False)
        self.assertEqual(self.__message(1), msg)
        # We don't check there are no extra headers, just that none are missing
        # or wrong.
        self.assertEqual(lname1, env[CC_HEADER_TO])
        self.assertEqual(conn2.lname, env[CC_HEADER_FROM])
        self.assertEqual("*", env[CC_HEADER_GROUP])
        self.assertEqual(CC_INSTANCE_WILDCARD, env[CC_HEADER_INSTANCE])
        self.assertEqual(CC_COMMAND_SEND, env[CC_HEADER_TYPE])
        self.assertFalse(env[CC_HEADER_WANT_ANSWER])

    def __barrier(self, connections):
        """
        Make sure all previous commands on all supplied connections are
        processed, by sending a ping and waiting for an answer.
        """
        for c in connections:
            c.sendmsg({"type": "ping"})
        for c in connections:
            pong = c.recvmsg(nonblock=False)
            self.assertEqual(({"type": "pong"}, None), pong)

    def test_send_group(self):
        """
        Create several connections. First, try to send a message to a (empty)
        group and see an error is bounced back. Then subscribe the others
        to the group and send it again. Send to a different group and see it
        bounced back. Unsubscribe and see it is bounced again.

        Then the other connections answer (after unsubscribing, strange, but
        legal). See both answers come.

        Then, look there are no more waiting messages.
        """
        conn_a = self.__get_connection()
        conn_b = []
        for i in range(0, 10):
            conn_b.append(self.__get_connection())
        # Send a message to empty group and get an error answer
        seq = conn_a.group_sendmsg(self.__message(1), "group",
                                   want_answer=True)
        (msg, env) = conn_a.group_recvmsg(nonblock=False, seq=seq)
        self.assertEqual(self.__no_recpt, msg)
        self.assertEqual(conn_a.lname, env[CC_HEADER_TO])
        # Subscribe the two connections
        for c in conn_b:
            c.group_subscribe("group")
        # The subscribe doesn't wait for answer, so make sure it is
        # all processed before continuing.
        self.__barrier(conn_b)
        # Send a message to the group (this time not empty)
        seq = conn_a.group_sendmsg(self.__message(2), "group",
                                   want_answer=True)
        envs = []
        for c in conn_b:
            (msg, env) = c.group_recvmsg(nonblock=False)
            self.assertEqual(self.__message(2), msg)
            self.assertEqual(conn_a.lname, env[CC_HEADER_FROM])
            # The daemon does not mangle the headers. Is it OK?
            self.assertEqual(CC_TO_WILDCARD, env[CC_HEADER_TO])
            self.assertEqual("group", env[CC_HEADER_GROUP])
            self.assertEqual(CC_INSTANCE_WILDCARD, env[CC_HEADER_INSTANCE])
            self.assertEqual(CC_COMMAND_SEND, env[CC_HEADER_TYPE])
            self.assertTrue(env[CC_HEADER_WANT_ANSWER])
            envs.append(env)
        # Send to non-existing group
        seq_ne = conn_a.group_sendmsg(self.__message(3), "no-group",
                                      want_answer=True)
        (msg, env) = conn_a.group_recvmsg(nonblock=False, seq=seq_ne)
        self.assertEqual(self.__no_recpt, msg)
        self.assertEqual(conn_a.lname, env[CC_HEADER_TO])
        # Unsubscribe the connections
        for c in conn_b:
            c.group_unsubscribe("group")
        # Synchronize the unsubscriptions
        self.__barrier(conn_b)
        seq_ne = conn_a.group_sendmsg(self.__message(4), "group",
                                      want_answer=True)
        (msg, env) = conn_a.group_recvmsg(nonblock=False, seq=seq_ne)
        self.assertEqual(self.__no_recpt, msg)
        self.assertEqual(conn_a.lname, env[CC_HEADER_TO])
        # Send answers for the original message that was delivered
        lnames = set()
        for (c, env) in zip(conn_b, envs):
            c.group_reply(env, self.__message("Reply"))
            lnames.add(c.lname)
        # Check the both answers come
        while lnames:
            # While there are still connections we didn't get the answer from
            # (the order is not guaranteed, therefore the juggling with set)
            (msg, env) = conn_a.group_recvmsg(nonblock=False, seq=seq)
            self.assertEqual(self.__message("Reply"), msg)
            lname = env[CC_HEADER_FROM]
            self.assertTrue(lname in lnames)
            lnames.remove(lname)

        # The barrier makes the msgq process everything we sent. As the
        # processing is single-threaded in it, any stray message would have
        # arrived before the barrier ends.
        self.__barrier(conn_b)
        self.__barrier([conn_a])
        for c in conn_b:
            self.assertEqual((None, None), c.group_recvmsg())
        self.assertEqual((None, None), conn_a.group_recvmsg())

    def test_conn_disconn(self):
        """
        Keep connecting and disconnecting, checking we can still send
        and receive messages.
        """
        conn = self.__get_connection()
        conn.group_subscribe("group")
        for i in range(0, 50):
            new = self.__get_connection()
            new.group_subscribe("group")
            self.__barrier([conn, new])
            new.group_sendmsg(self.__message(i), "group")
            (msg, env) = conn.group_recvmsg(nonblock=False)
            self.assertEqual(self.__message(i), msg)
            conn.close()
            conn = new

if __name__ == '__main__':
    isc.log.init("msgq-tests")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
