# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

import socket
import struct
import os
import subprocess
from bind10_messages import *
from libutil_io_python import recv_fd

logger = isc.log.Logger("boss")

"""
Module that comunicates with the priviledget socket creator (b10-sockcreator).
"""

class CreatorError(Exception):
    """
    Exception for socket creator related errors.

    It has two members: fatal and errno and they are just holding the values
    passed to the __init__ function.
    """

    def __init__(self, message, fatal, errno=None):
        """
        Creates the exception. The message argument is the usual string.
        The fatal one tells if the error is fatal (eg. the creator crashed)
        and errno is the errno value returned from socket creator, if
        applicable.
        """
        Exception.__init__(self, message)
        self.fatal = fatal
        self.errno = errno

class Parser:
    """
    This class knows the sockcreator language. It creates commands, sends them
    and receives the answers and parses them.

    It does not start it, the communication channel must be provided.

    In theory, anything here can throw a fatal CreatorError exception, but it
    happens only in case something like the creator process crashes. Any other
    occations are mentioned explicitly.
    """

    def __init__(self, creator_socket):
        """
        Creates the parser. The creator_socket is socket to the socket creator
        process that will be used for communication. However, the object must
        have a read_fd() method to read the file descriptor. This slightly
        unusual trick with modifying an object is used to easy up testing.

        You can use WrappedSocket in production code to add the method to any
        ordinary socket.
        """
        self.__socket = creator_socket
        logger.info(BIND10_SOCKCREATOR_INIT)

    def terminate(self):
        """
        Asks the creator process to terminate and waits for it to close the
        socket. Does not return anything.
        """
        if self.__socket is None:
            raise CreatorError('Terminated already', True)
        logger.info(BIND10_SOCKCREATOR_TERMINATE)
        try:
            self.__socket.sendall(b'T')
            # Wait for an EOF - it will return empty data
            eof = self.__socket.recv(1)
            if len(eof) != 0:
                raise CreatorError('Protocol error - data after terminated',
                                   True)
            self.__socket = None
        except socket.error as se:
            self.__socket = None
            raise CreatorError(str(se), True)

    def get_socket(self, address, port, socktype):
        """
        Asks the socket creator process to create a socket. Pass an address
        (the isc.net.IPaddr object), port number and socket type (either
        string "UDP", "TCP" or constant socket.SOCK_DGRAM or
        socket.SOCK_STREAM.

        Blocks until it is provided by the socket creator process (which
        should be fast, as it is on localhost) and returns the file descriptor
        number. It raises a CreatorError exception if the creation fails.
        """
        if self.__socket is None:
            raise CreatorError('Socket requested on terminated creator', True)
        # First, assemble the request from parts
        logger.info(BIND10_SOCKET_GET, address, port, socktype)
        data = b'S'
        if socktype == 'UDP' or socktype == socket.SOCK_DGRAM:
            data += b'U'
        elif socktype == 'TCP' or socktype == socket.SOCK_STREAM:
            data += b'T'
        else:
            raise ValueError('Unknown socket type: ' + str(socktype))
        if address.family == socket.AF_INET:
            data += b'4'
        elif address.family == socket.AF_INET6:
            data += b'6'
        else:
            raise ValueError('Unknown address family in address')
        data += struct.pack('!H', port)
        data += address.addr
        try:
            # Send the request
            self.__socket.sendall(data)
            answer = self.__socket.recv(1)
            if answer == b'S':
                # Success!
                result = self.__socket.read_fd()
                logger.info(BIND10_SOCKET_CREATED, result)
                return result
            elif answer == b'E':
                # There was an error, read the error as well
                error = self.__socket.recv(1)
                errno = struct.unpack('i',
                                      self.__read_all(len(struct.pack('i',
                                                                      0))))
                if error == b'S':
                    cause = 'socket'
                elif error == b'B':
                    cause = 'bind'
                else:
                    self.__socket = None
                    logger.fatal(BIND10_SOCKCREATOR_BAD_CAUSE, error)
                    raise CreatorError('Unknown error cause' + str(answer), True)
                logger.error(BIND10_SOCKET_ERROR, cause, errno[0],
                             os.strerror(errno[0]))
                raise CreatorError('Error creating socket on ' + cause, False,
                                   errno[0])
            else:
                self.__socket = None
                logger.fatal(BIND10_SOCKCREATOR_BAD_RESPONSE, answer)
                raise CreatorError('Unknown response ' + str(answer), True)
        except socket.error as se:
            self.__socket = None
            logger.fatal(BIND10_SOCKCREATOR_TRANSPORT_ERROR, str(se))
            raise CreatorError(str(se), True)

    def __read_all(self, length):
        """
        Keeps reading until length data is read or EOF or error happens.

        EOF is considered error as well and throws.
        """
        result = b''
        while len(result) < length:
            data = self.__socket.recv(length - len(result))
            if len(data) == 0:
                self.__socket = None
                logger.fatal(BIND10_SOCKCREATOR_EOF)
                raise CreatorError('Unexpected EOF', True)
            result += data
        return result

class WrappedSocket:
    """
    This class wraps a socket and adds a read_fd method, so it can be used
    for the Parser class conveniently. It simply copies all it's guts into
    itself and implements the method.
    """
    def __init__(self, socket):
        # Copy whatever can be copied from the socket
        for name in dir(socket):
            if name not in ['__class__', '__weakref__']:
                setattr(self, name, getattr(socket, name))
        # Keep the socket, so we can prevent it from being garbage-collected
        # and closed before we are removed ourself
        self.__orig_socket = socket

    def read_fd(self):
        """
        Read the file descriptor from the socket.
        """
        return recv_fd(self.fileno())

# FIXME: Any idea how to test this? Starting an external process doesn't sound
# OK
class Creator(Parser):
    """
    This starts the socket creator and allows asking for the sockets.
    """
    def __init__(self, path):
        (local, remote) = socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM)
        # Popen does not like, for some reason, having the same socket for
        # stdin as well as stdout, so we dup it before passing it there.
        remote2 = socket.fromfd(remote.fileno(), socket.AF_UNIX,
                                socket.SOCK_STREAM)
        env = os.environ
        env['PATH'] = path
        self.__process = subprocess.Popen(['b10-sockcreator'], env=env,
                                          stdin=remote.fileno(),
                                          stdout=remote2.fileno())
        remote.close()
        remote2.close()
        Parser.__init__(self, WrappedSocket(local))

    def pid(self):
        return self.__process.pid

    def kill(self):
        logger.warn(BIND10_SOCKCREATOR_KILL)
        if self.__process is not None:
            self.__process.kill()
            self.__process = None
