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
        # Don't redirect stdout/stderr here as we want to print out things
        # during the test
        #
        # However, we do want to set the logging lock directory to somewhere
        # to which we can write - use the current working directory.  We then
        # set the appropriate environment variable.  os.putenv() may be not
        # supported on some platforms as suggested in
        # http://docs.python.org/release/3.2/library/os.html?highlight=putenv#os.environ:
        # "If the platform supports the putenv() function...". It was checked
        # that it does not work on Ubuntu. To overcome this problem we access
        # os.environ directly.
        lockdir_envvar = "B10_LOCKFILE_DIR_FROM_BUILD"
        if lockdir_envvar not in os.environ:
            os.environ[lockdir_envvar] = os.getcwd()

    def tearDown(self):
        pass

    def readPipe(self, pipe_fd):
        """
        Reads bytes from a pipe and returns a character string.  If nothing is
        read, or if there is an error, an empty string is returned.

        pipe_fd - Pipe file descriptor to read
        """
        try:
            data = os.read(pipe_fd, 16384)
            # Make sure we have a string
            if (data is None):
                data = ""
            else:
                data = str(data)
        except OSError:
            data = ""

        return data

    def runCommand(self, params, wait=1):
        """
        This method runs a command and returns a tuple: (returncode, stdout, stderr)
        """
        ## @todo: Convert this into generic method and reuse it in dhcp4 and dhcp6

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

        # As we don't know how long the subprocess will take to start and
        # produce output, we'll loop and sleep for 250 ms between each
        # iteration.  To avoid an infinite loop, we'll loop for a maximum
        # of five seconds: that should be enough.
        for count in range(20):
            # Read something from stderr and stdout (these reads don't block).
            output = self.readPipe(self.stdout_pipes[0])
            error  = self.readPipe(self.stderr_pipes[0])

            # If the process has already exited, or if it has output something,
            # quit the loop now.
            if pi.process.poll() is not None or len(error) > 0 or len(output) > 0:
                break

            # Process still running, try again in 250 ms.
            time.sleep(0.25)

        # Exited loop, kill the process if it is still running
        if pi.process.poll() is None:
            try:
                pi.process.terminate()
            except OSError:
                print("Ignoring failed kill attempt. Process is dead already.")

        # call this to get returncode, process should be dead by now
        rc = pi.process.wait()

        # Clean up our stdout/stderr munging.
        os.dup2(self.stdout_old, sys.stdout.fileno())
        os.close(self.stdout_old)
        os.close(self.stdout_pipes[0])

        os.dup2(self.stderr_old, sys.stderr.fileno())
        os.close(self.stderr_old)
        os.close(self.stderr_pipes[0])

        # Free up resources (file descriptors) from the ProcessInfo object
        # TODO: For some reason, this gives an error if the process has ended,
        #       although it does cause all descriptors still allocated to the
        #       object to be freed.
        pi = None

        print ("Process finished, return code=%d, stdout=%d bytes, stderr=%d bytes"
               % (rc, len(output), len(error)) )

        return (rc, output, error)

    def test_alive(self):
        print("Note: Purpose of some of the tests is to check if DHCPv4 server can be started,")
        print("      not that is can bind sockets correctly. Please ignore binding errors.")

        (returncode, output, error) = self.runCommand(["../b10-dhcp4", "-v"])
        output_text = str(output) + str(error)
        self.assertEqual(output_text.count("DHCP4_STARTING"), 1)

    def test_portnumber_0(self):
        print("Check that specifying port number 0 is not allowed.")

        (returncode, output, error) = self.runCommand(['../b10-dhcp4', '-v', '-p', '0'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("Failed to parse port number"), 1)

    def test_portnumber_missing(self):
        print("Check that -p option requires a parameter.")

        (returncode, output, error) = self.runCommand(['../b10-dhcp4', '-p'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("option requires an argument"), 1)

    def test_portnumber_invalid1(self):
        print("Check that -p option is check against bogus port number (999999).")

        (returncode, output, error) = self.runCommand(['../b10-dhcp4', '-p','999999'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("Failed to parse port number"), 1)

    def test_portnumber_invalid2(self):
        print("Check that -p option is check against bogus port number (123garbage).")

        (returncode, output, error) = self.runCommand(['../b10-dhcp4', '-p','123garbage'])

        # When invalid port number is specified, return code must not be success
        self.assertTrue(returncode != 0)

        # Check that there is an error message about invalid port number printed on stderr
        self.assertEqual( str(error).count("Failed to parse port number"), 1)

    def test_portnumber_nonroot(self):
        print("Check that specifying unprivileged port number will work.")

        # Check that there is a message about running with an unprivileged port
        (returncode, output, error) = self.runCommand(['../b10-dhcp4', '-v', '-s', '-p', '10057'])
        output_text = str(output) + str(error)
        self.assertEqual(output_text.count("DHCP4_OPEN_SOCKET opening sockets on port 10057"), 1)

    def test_skip_msgq(self):
        print("Check that connection to BIND10 msgq can be disabled.")

        # Check that the system outputs a message on one of its streams about running
        # standalone.
        (returncode, output, error) = self.runCommand(['../b10-dhcp4', '-v', '-s', '-p', '10057'])
        output_text = str(output) + str(error)
        self.assertEqual(output_text.count("DHCP4_STANDALONE"), 1)

if __name__ == '__main__':
    unittest.main()
