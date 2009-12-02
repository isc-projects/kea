"""\
This code implements a Python version of the msgq daemon.

This replaces the C version, which relied upon the BIND 9 "libisc"
libraries.
"""

import subprocess
import signal
import os
import socket
import sys
import re
import errno
import time
import select
import pprint
from optparse import OptionParser, OptionValueError

import ISC.CC

# This is the version that gets displayed to the user.
__version__ = "v20091030 (Paving the DNS Parking Lot)"

class MsgQ:
    """Message Queue class."""
    def __init__(self, c_channel_port=9912, verbose=False):
        """Initialize the MsgQ master.
        
        The c_channel_port specifies the TCP/IP port that the msgq
        process listens on. If verbose is True, then the MsgQ reports
        what it is doing.
        """
        self.verbose = True
        self.c_channel_port = c_channel_port
        self.poller = None
        self.runnable = False
        self.listen_socket = False
        self.sockets = {}

    def setup_poller(self):
        """Set up the poll thing.  Internal function."""
        self.poller = select.poll()

    def setup_listener(self):
        """Set up the listener socket.  Internal function."""
        self.listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.listen_socket.bind(("127.0.0.1", self.c_channel_port))
        self.listen_socket.listen(1024)
        self.listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        self.poller.register(self.listen_socket, select.POLLIN)

    def setup(self):
        """Configure listener socket, polling, etc."""

        self.setup_poller()
        self.setup_listener()

        if self.verbose:
            sys.stdout.write("Listening\n")
        
        self.runnable = True

    def process_accept(self):
        newsocket, ipaddr = self.listen_socket.accept()
        sys.stderr.write("Connection\n")
        self.sockets[newsocket.fileno()] = newsocket
        self.poller.register(newsocket, select.POLLIN)

    def process_socket(self, fd):
        sock = self.sockets[fd]
        if sock == None:
            sys.stderr.write("Got read on Strange Socket fd %d\n" % fd)
            return
        sys.stderr.write("Got read on fd %d\n" %fd)
        self.process_packet(fd, sock)

    def process_packet(self, fd, sock):
        data = sock.recv(4)
        if len(data) == 0:
            self.poller.unregister(sock)
            sock.close()
            self.sockets[fd] = None
            sys.stderr.write("Closing socket fd %d\n" % fd)
            return
        sys.stderr.write("Got data: %s\n" % data)

    def run(self):
        """Process messages.  Forever.  Mostly."""

        while True:
            try:
                events = self.poller.poll()
            except select.error as err:
                if err.args[0] == errno.EINTR:
                    events = []
                else:
                    sys.stderr.write("Error with poll(): %s\n" % err)
                    break
            for (fd, event) in events:
                if fd == self.listen_socket.fileno():
                    self.process_accept()
                else:
                    self.process_socket(fd)

    def shutdown(self):
        """Stop the MsgQ master."""
        if self.verbose:
            sys.stdout.write("Stopping the server.\n")
        self.listen_socket.close()

if __name__ == "__main__":
    def check_port(option, opt_str, value, parser):
        """Function to insure that the port we are passed is actually 
        a valid port number. Used by OptionParser() on startup."""
        intval = int(value)
        if (intval < 0) or (intval > 65535):
            raise OptionValueError("%s requires a port number (0-65535)" % opt_str)
        parser.values.msgq_port = intval

    # Parse any command-line options.
    parser = OptionParser(version=__version__)
    parser.add_option("-v", "--verbose", dest="verbose", action="store_true",
                      help="display more about what is going on")
    parser.add_option("-m", "--msgq-port", dest="msgq_port", type="string",
                      action="callback", callback=check_port, default="9912",
                      help="port the msgq daemon will use")
    (options, args) = parser.parse_args()

    # Announce startup.
    if options.verbose:
        sys.stdout.write("MsgQ %s\n" % __version__)

    msgq = MsgQ(int(options.msgq_port), options.verbose)

    setup_result = msgq.setup()
    if setup_result:
        sys.stderr.write("Error on startup: %s\n" % setup_result)
        sys.exit(1)

    msgq.run()

    msgq.shutdown()
