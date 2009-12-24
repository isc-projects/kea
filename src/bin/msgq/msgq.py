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
import random
from optparse import OptionParser, OptionValueError

import ISC.CC

# This is the version that gets displayed to the user.
__version__ = "v20091030 (Paving the DNS Parking Lot)"

class MsgQReceiveError(Exception): pass

class SubscriptionManager:
    def __init__(self):
        self.subscriptions = {}

    def subscribe(self, group, instance, socket):
        """Add a subscription."""
        target = ( group, instance )
        if target in self.subscriptions:
            print("Appending to existing target")
            self.subscriptions[target].append(socket)
        else:
            print("Creating new target")
            self.subscriptions[target] = [ socket ]

    def unsubscribe(self, group, instance, socket):
        """Remove the socket from the one specific subscription."""
        target = ( group, instance )
        if target in self.subscriptions:
            while socket in self.subscriptions[target]:
                self.subscriptions[target].remove(socket)

    def unsubscribe_all(self, socket):
        """Remove the socket from all subscriptions."""
        for socklist in self.subscriptions.values():
            while socket in socklist:
                socklist.remove(socket)

    def find_sub(self, group, instance):
        """Return an array of sockets which want this specific group,
        instance."""
        target = (group, instance)
        if target in self.subscriptions:
            return self.subscriptions[target]
        else:
            return []

    def find(self, group, instance):
        """Return an array of sockets who should get something sent to
        this group, instance pair.  This includes wildcard subscriptions."""
        target = (group, instance)
        partone = self.find_sub(group, instance)
        parttwo = self.find_sub(group, "*")
        return list(set(partone + parttwo))

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
        self.connection_counter = random.random()
        self.hostname = socket.gethostname()
        self.subs = SubscriptionManager()
        self.lnames = {}

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
        lname = self.newlname()
        self.lnames[lname] = newsocket
        self.poller.register(newsocket, select.POLLIN)

    def process_socket(self, fd):
        """Process a read on a socket."""
        sock = self.sockets[fd]
        if sock == None:
            sys.stderr.write("Got read on Strange Socket fd %d\n" % fd)
            return
#        sys.stderr.write("Got read on fd %d\n" %fd)
        self.process_packet(fd, sock)

    def kill_socket(self, fd, sock):
        """Fully close down the socket."""
        self.poller.unregister(sock)
        self.subs.unsubscribe_all(sock)
        lname = [ k for k, v in self.lnames.items() if v == sock ][0]
        del self.lnames[lname]
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

#        sys.stdout.write("\t" + pprint.pformat(routingmsg) + "\n")
#        sys.stdout.write("\t" + pprint.pformat(data) + "\n")

        self.process_command(fd, sock, routingmsg, data)

    def process_command(self, fd, sock, routing, data):
        """Process a single command.  This will split out into one of the
           other functions, above."""
        print("[XX] got command: ")
        print(routing)
        cmd = routing["type"]
        if cmd == 'send':
            self.process_command_send(sock, routing, data)
        elif cmd == 'subscribe':
            self.process_command_subscribe(sock, routing, data)
        elif cmd == 'unsubscribe':
            self.process_command_unsubscribe(sock, routing, data)
        elif cmd == 'getlname':
            self.process_command_getlname(sock, routing, data)
        else:
            sys.stderr.write("Invalid command: %s\n" % cmd)

    def preparemsg(self, env, msg = None):
        if type(env) == dict:
            env = ISC.CC.Message.to_wire(env)
        if type(msg) == dict:
            msg = ISC.CC.Message.to_wire(msg)
        length = 2 + len(env);
        if msg:
            length += len(msg)
        ret = struct.pack("!IH", length, len(env))
        ret += env
        if msg:
            ret += msg
        return ret

    def sendmsg(self, sock, env, msg = None):
        sock.send(self.preparemsg(env, msg))

    def send_prepared_msg(self, sock, msg):
        sock.send(msg)

    def newlname(self):
        """Generate a unique conenction identifier for this socket.
        This is done by using an increasing counter and the current
        time."""
        self.connection_counter += 1
        return "%x_%x@%s" % (time.time(), self.connection_counter, self.hostname)

    def process_command_getlname(self, sock, routing, data):
        lname = [ k for k, v in self.lnames.items() if v == sock ][0]
        self.sendmsg(sock, { "type" : "getlname" }, { "lname" : lname })

    def process_command_send(self, sock, routing, data):
        group = routing["group"]
        instance = routing["instance"]
        to = routing["to"]
        if group == None or instance == None:
            return  # ignore invalid packets entirely

        if to == "*":
            sockets = self.subs.find(group, instance)
        else:
            if to in self.lnames:
                sockets = [ self.lnames[to] ]
            else:
                return # recipient doesn't exist

        msg = self.preparemsg(routing, data)

        if sock in sockets:
            sockets.remove(sock)
        for socket in sockets:
            self.send_prepared_msg(socket, msg)

    def process_command_subscribe(self, sock, routing, data):
        group = routing["group"]
        instance = routing["instance"]
        if group == None or instance == None:
            return  # ignore invalid packets entirely
        self.subs.subscribe(group, instance, sock)

    def process_command_unsubscribe(self, sock, routing, data):
        group = routing["group"]
        instance = routing["instance"]
        if group == None or instance == None:
            return  # ignore invalid packets entirely
        self.subs.unsubscribe(group, instance, sock)

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
