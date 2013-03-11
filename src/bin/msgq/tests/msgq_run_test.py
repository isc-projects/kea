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

SOCKET_PATH = os.path.abspath(os.environ['BIND10_TEST_SOCKET_FILE'])
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
        # Wait for it to become ready (up to the alarm-set timeout)
        while not os.path.exists(SOCKET_PATH):
            # Just a short wait, so we don't hog CPU, but don't wait too long
            time.sleep(0.01)

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
        if self.__msgq:
            self.__msgq.kill()
            self.__msgq = None
        if os.path.exists(SOCKET_PATH):
            os.unlink(SOCKET_PATH)
        for sig in self.__orig_signals:
            signal.signal(sig, self.__orig_signals[sig])
        # Cancel timeout (so someone else is not hit by it)
        signal.alarm(0)

    def test_empty_run(self):
        """
        Temporary empty test, to see if we can start and stop msgq.
        Testing the test harness.
        """
        pass

if __name__ == '__main__':
    isc.log.resetUnitTestRootLogger()
    unittest.main()
