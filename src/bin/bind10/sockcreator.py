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
        unusual modification of socket object is used to easy up testing.
        """
        self.__socket = creator_socket

    def terminate(self):
        """
        Asks the creator process to terminate and waits for it to close the
        socket. Does not return anything.
        """
        if self.__socket is None:
            raise CreatorError('Terminated already', True)
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
                return self.__socket.read_fd()
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
                    raise CreatorError('Unknown error cause' + str(answer), True)
                raise CreatorError('Error creating socket on ' + cause, False,
                                   errno[0])
            else:
                self.__socket = None
                raise CreatorError('Unknown response ' + str(answer), True)
        except socket.error as se:
            self.__socket = None
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
                raise CreatorError('Unexpected EOF', True)
            result += data
        return result
