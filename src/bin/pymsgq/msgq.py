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
import struct
import errno
import time
import select
import pprint
from optparse import OptionParser, OptionValueError

import ISC.CC

class MsgQReceiveError(Exception): pass

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
        """Process an accept on the listening socket."""
        newsocket, ipaddr = self.listen_socket.accept()
        sys.stderr.write("Connection\n")
        self.sockets[newsocket.fileno()] = newsocket
        self.poller.register(newsocket, select.POLLIN)

    def process_socket(self, fd):
        """Process a read on a socket."""
        sock = self.sockets[fd]
        if sock == None:
            sys.stderr.write("Got read on Strange Socket fd %d\n" % fd)
            return
        sys.stderr.write("Got read on fd %d\n" %fd)
        self.process_packet(fd, sock)

    def kill_socket(self, fd, sock):
        """Fully close down the socket."""
        self.poller.unregister(sock)
        sock.close()
        self.sockets[fd] = None
        sys.stderr.write("Closing socket fd %d\n" % fd)

    def getbytes(self, fd, sock, length):
        """Get exactly the requested bytes, or raise an exception if
           EOF."""
        received = b''
        while len(received) < length:
            data = sock.recv(length - len(received))
            if len(data) == 0:
                raise MsgQReceiveError("EOF")
            received += data
        return received

    def read_packet(self, fd, sock):
        """Read a correctly formatted packet.  Will raise exceptions if
           something fails."""
        lengths = self.getbytes(fd, sock, 6)
        overall_length, routing_length = struct.unpack(">IH", lengths)
        if overall_length < 2:
            raise MsgQReceiveError("overall_length < 2")
        overall_length -= 2
        sys.stderr.write("overall length: %d, routing_length %d\n"
                         % (overall_length, routing_length))
        if routing_length > overall_length:
            raise MsgQReceiveError("routing_length > overall_length")
        if routing_length == 0:
            raise MsgQReceiveError("routing_length == 0")
        data_length = overall_length - routing_length
        # probably need to sanity check lengths here...
        routing = self.getbytes(fd, sock, routing_length)
        if data_length > 0:
            data = self.getbytes(fd, sock, data_length)
        else:
            data = None
        return (routing, data)

    def process_packet(self, fd, sock):
        """Process one packet."""
        try:
            routing, data = self.read_packet(fd, sock)
        except MsgQReceiveError as err:
            self.kill_socket(fd, sock)
            sys.stderr.write("Receive error: %s\n" % err)
            return

        try:
            routingmsg = ISC.CC.Message.from_wire(routing)
        except DecodeError as err:
            self.kill_socket(fd, sock)
            sys.stderr.write("Routing decode error: %s\n" % err)
            return

        sys.stdout.write("\t" + pprint.pformat(routingmsg) + "\n")
        sys.stdout.write("\t" + pprint.pformat(data) + "\n")

        self.process_command(fd, sock, routingmsg, data)

    def process_command(self, fd, sock, routing, data):
        """Process a single command.  This will split out into one of the
           other functions, above."""
        cmd = routing["type"]
        if cmd == 'getlname':
            self.process_command_getlname(sock, routing, data)
        elif cmd == 'send':
            self.process_command_send(sock, routing, data)
        else:
            sys.stderr.write("Invalid command: %s\n" % cmd)

    def sendmsg(self, sock, env, msg = None):
        if type(env) == dict:
            env = ISC.CC.Message.to_wire(env)
        if type(msg) == dict:
            msg = ISC.CC.Message.to_wire(msg)
        sock.setblocking(1)
        length = 2 + len(env);
        if msg:
            length += len(msg)
        sock.send(struct.pack("!IH", length, len(env)))
        sock.send(env)
        if msg:
            sock.send(msg)

    def process_command_getlname(self, sock, routing, data):
        self.sendmsg(sock, { "type" : "getlname" }, { "lname" : "staticlname" })

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
