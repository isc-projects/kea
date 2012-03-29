# Copyright (C) 2011 Internet Systems Consortium.
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

from bind10_src import ProcessInfo, parse_args, dump_pid, unlink_pid_file, _BASETIME

import unittest
import sys
import os
import signal
import socket
from isc.net.addr import IPAddr
import time
import isc

class TestDhcpv6Daemon(unittest.TestCase):
    def setUp(self):
        # redirect stdout to a pipe so we can check that our
        # process spawning is doing the right thing with stdout
        self.old_stdout = os.dup(sys.stdout.fileno())
        self.pipes = os.pipe()
        os.dup2(self.pipes[1], sys.stdout.fileno())
        os.close(self.pipes[1])
        # note that we use dup2() to restore the original stdout
        # to the main program ASAP in each test... this prevents
        # hangs reading from the child process (as the pipe is only
        # open in the child), and also insures nice pretty output

    def tearDown(self):
        # clean up our stdout munging
        os.dup2(self.old_stdout, sys.stdout.fileno())
        os.close(self.pipes[0])

    def test_alive(self):
        """
        Simple test. Checks that b10-dhcp6 can be started and prints out info 
        about starting DHCPv6 operation.
        """
        pi = ProcessInfo('Test Process', [ '../b10-dhcp6' , '-v' ])
        pi.spawn()
        time.sleep(1)
        os.dup2(self.old_stdout, sys.stdout.fileno())
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)
        output = os.read(self.pipes[0], 4096)
        self.assertEqual( str(output).count("[b10-dhcp6] Initiating DHCPv6 operation."), 1)

        # kill this process
        # XXX: b10-dhcp6 is too dumb to understand 'shutdown' command for now,
        #      so let's just kill the bastard

        # TODO: Ignore errors for now. This test will be more thorough once ticket #1503
        # (passing port number to b10-dhcp6 daemon) is implemented.
        try:
            os.kill(pi.pid, signal.SIGTERM)
        except OSError:
            print("Ignoring failed kill attempt. Process is dead already.")

if __name__ == '__main__':
    unittest.main()
