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

class TestDhcpv4Daemon(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def runDhcp4(self, params):
        """
        This method runs dhcp4 and returns a touple: (returncode and stdout)
        """

        print("Running command: %s" % (" ".join(params)))

        # redirect stdout to a pipe so we can check that our
        # process spawning is doing the right thing with stdout
        self.stdout_old = os.dup(sys.stdout.fileno())
        self.stdout_pipes = os.pipe()
        os.dup2(self.stdout_pipes[1], sys.stdout.fileno())
        os.close(self.stdout_pipes[1])

        # do the same trick for stderr:
        self.stderr_old = os.dup(sys.stderr.fileno())
        self.stderr_pipes = os.pipe()
        os.dup2(self.stderr_pipes[1], sys.stderr.fileno())
        os.close(self.stderr_pipes[1])

        # note that we use dup2() to restore the original stdout
        # to the main program ASAP in each test... this prevents
        # hangs reading from the child process (as the pipe is only
        # open in the child), and also insures nice pretty output

        pi = ProcessInfo('Test Process', params)
        pi.spawn()
        time.sleep(1)
        os.dup2(self.stdout_old, sys.stdout.fileno())
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)

        output = os.read(self.stdout_pipes[0], 4096)
        error = os.read(self.stderr_pipes[0], 4096)

        try:
            if (not pi.process.poll()):
                # let's be nice at first...
                pi.process.send_signal(signal.SIGTERM)
                time.sleep(1)
                if (pi.process.returncode == None):
                    # if the suspect does not cooperate, use bigger hammer
                    os.kill(pi.pid, signal.SIGKILL)
        except OSError:
            print("Ignoring failed kill attempt. Process is dead already.")

        # clean up our stdout munging
        os.dup2(self.stdout_old, sys.stdout.fileno())
        os.close(self.stdout_pipes[0])

        os.dup2(self.stderr_old, sys.stderr.fileno())
        os.close(self.stderr_pipes[0])

        return (pi.process.returncode, output, error)

    def test_alive(self):
        print("Note: Purpose of some of the tests is to check if DHCPv4 server can be started,")
        print("      not that is can bind sockets correctly. Please ignore binding errors.")

        (returncode, output, error) = self.runDhcp4(["../b10-dhcp4", "-v"])
        # print("Return code=%d \nstdout=[%s]\nstderr=[%s]" % (returncode, output, error) )

        self.assertEqual( str(output).count("[b10-dhcp4] Initiating DHCPv4 server operation."), 1)

    def test_portnumber_0(self):
        print("Check that specifying port number 0 is not allowed.")
        (returncode, output, error) = self.runDhcp4(['../b10-dhcp4', '-p', '0'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("Failed to parse port number"), 1)



if __name__ == '__main__':
    unittest.main()
