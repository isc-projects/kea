# Copyright (C) 2012 Internet Systems Consortium.
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
import fcntl

class TestDhcpv4Daemon(unittest.TestCase):
    def setUp(self):
        # don't redirect stdout/stderr here as we want to print out things
        # during the test
        pass

    def tearDown(self):
        pass

    def runDhcp4(self, params, wait=1):
        """
        This method runs dhcp4 and returns a touple: (returncode, stdout, stderr)
        """
        ## @todo: Convert this into generic method and reuse it in dhcp6

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
        time.sleep(wait)
        os.dup2(self.stdout_old, sys.stdout.fileno())
        os.dup2(self.stderr_old, sys.stderr.fileno())
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)

        # Set non-blocking read on pipes. Process may not print anything
        # on specific output and the we would hang without this.
        fd = self.stdout_pipes[0]
        fl = fcntl.fcntl(fd, fcntl.F_GETFL)
        fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

        fd = self.stderr_pipes[0]
        fl = fcntl.fcntl(fd, fcntl.F_GETFL)
        fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

        # There's potential problem if b10-dhcp4 prints out more
        # than 4k of text
        try:
            output = os.read(self.stdout_pipes[0], 4096)
        except OSError:
            print("No data available from stdout")
            output = ""

        # read can return None. Make sure we have a string
        if (output is None):
            output = ""

        try:
            error = os.read(self.stderr_pipes[0], 4096)
        except OSError:
            print("No data available on stderr")
            error = ""

        # read can return None. Make sure we have a string
        if (error is None):
            error = ""


        try:
            if (not pi.process.poll()):
                # let's be nice at first...
                pi.process.terminate()
        except OSError:
            print("Ignoring failed kill attempt. Process is dead already.")

        # call this to get returncode, process should be dead by now
        rc = pi.process.wait()

        # Clean up our stdout/stderr munging.
        os.dup2(self.stdout_old, sys.stdout.fileno())
        os.close(self.stdout_pipes[0])

        os.dup2(self.stderr_old, sys.stderr.fileno())
        os.close(self.stderr_pipes[0])

        print ("Process finished, return code=%d, stdout=%d bytes, stderr=%d bytes"
               % (rc, len(output), len(error)) )

        return (rc, output, error)

    def test_alive(self):
        print("Note: Purpose of some of the tests is to check if DHCPv4 server can be started,")
        print("      not that is can bind sockets correctly. Please ignore binding errors.")

        (returncode, output, error) = self.runDhcp4(["../b10-dhcp4", "-v"])

        self.assertEqual( str(output).count("[b10-dhcp4] Initiating DHCPv4 server operation."), 1)

    def test_portnumber_0(self):
        print("Check that specifying port number 0 is not allowed.")

        (returncode, output, error) = self.runDhcp4(['../b10-dhcp4', '-p', '0'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("Failed to parse port number"), 1)

    def test_portnumber_missing(self):
        print("Check that -p option requires a parameter.")

        (returncode, output, error) = self.runDhcp4(['../b10-dhcp4', '-p'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("option requires an argument"), 1)

    def test_portnumber_nonroot(self):
        print("Check that specifying unprivileged port number will work.")

        (returncode, output, error) = self.runDhcp4(['../b10-dhcp4', '-p', '10057'])

        # When invalid port number is specified, return code must not be success
        # TODO: Temporarily commented out as socket binding on systems that do not have
        #       interface detection implemented currently fails.
        # self.assertTrue(returncode == 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(output).count("opening sockets on port 10057"), 1)

if __name__ == '__main__':
    unittest.main()
