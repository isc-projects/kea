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
        pass # TODO Implement

    def terminate(self):
        """
        Asks the creator process to terminate and waits for it to close the
        socket. Does not return anything.
        """
        pass # TODO Implement

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
        pass # TODO Implement
