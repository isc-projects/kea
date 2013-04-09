# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

"""Utility for handling DNS transactions over TCP.

This module defines a few convenient utility classes for handling DNS
transactions via a TCP socket.

"""

import isc.log
from isc.server_common.logger import logger
from isc.log_messages.server_common_messages import *
from isc.ddns.logger import ClientFormatter
import errno
import socket
import struct

class DNSTCPSendBuffer:
    '''A composite buffer for a DNS message sent over TCP.

    This class encapsulates binary data supposed to be a complete DNS
    message, taking into account the 2-byte length field preceeding the
    actual data.

    An object of this class is constructed with a binary object for the
    DNS message data (in wire-format), conceptually "appended" to the
    2-byte length field.  The length is automatically calculated and
    converted to the wire-format data in the network byte order.

    Its get_data() method returns a binary object corresponding to the
    consecutive region of the conceptual buffer starting from the specified
    position.  The returned region may not necessarily contain all remaining
    data from the specified position; this class can internally hold multiple
    separate binary objects to represent the conceptual buffer, and,
    in that case, get_data() identifies the object that contains the
    specified position of data, and returns the longest consecutive region
    from that position.  So the caller must call get_data(), incrementing
    the position as it transmits the data, until it gets None.

    This class is primarily intended to be a private utility for the
    DNSTCPContext class, but can be used by other general applications
    that need to send DNS messages over TCP in their own way.

    '''
    def __init__(self, data):
        '''Consructor.

        Parameter:
          data (binary): A binary sequence that is supposed to be a
            complete DNS message in the wire format.  It must not
            exceed 65535 bytes in length; otherwise ValueError will be
            raised.  This class does not check any further validity on
            the data as a DNS message.

        '''
        self.__data_size = len(data)
        self.__len_size = 2     # fixed length
        if self.__data_size > 0xffff:
            raise ValueError('Too large data for DNS/TCP, size: ' +
                             str(self.__data_size))
        self.__lenbuf = struct.pack('H', socket.htons(self.__data_size))
        self.__databuf = data

    def get_total_len(self):
        '''Return the total length of the buffer, including the length field.

        '''
        return self.__data_size + self.__len_size

    def get_data(self, pos):
        '''Return a portion of data from a specified position.

        Parameter:
          pos (int): The position in the TCP DNS message data (including
          the 2-byte length field) from which the data are to be returned.

        Return:
          A Python binary object that corresponds to a part of the TCP
          DNS message data starting at the specified position.  It may
          or may not contain all remaining data from that position.
          If the given position is beyond the end of the entire data,
          None will be returned.

        '''
        if pos >= self.__len_size:
            pos -= self.__len_size
            if pos >= self.__data_size:
                return None
            return self.__databuf[pos:]
        return self.__lenbuf[pos:]

class DNSTCPContextError(Exception):
    '''An exception raised against logic errors in DNSTCPContext.

    This is raised only when the context class is used in an unexpected way,
    that is for a caller's bug.

    '''
    pass

class DNSTCPContext:
    '''Context of a TCP connection used for DNS transactions.

    This class offers the following services:
    - Handle the initial 2-byte length field internally.  The user of
      this class only has to deal with the bare DNS message (just like
      the one transmiited over UDP).
    - Asynchronous I/O.  It supports the non blocking operation mode,
      where method calls never block.  The caller is told whether it's
      ongoing and it should watch the socket or it's fully completed.
    - Socket error handling: it internally catches socket related exceptions
      and handle them in an appropriate way.  A fatal error will be reported
      to the caller in the form of a normal return value.  The application
      of this class can therefore assume it's basically exception free.

    Notes:
      - the initial implementation only supports non blocking mode, but
        it's intended to be extended so it can work in both blocking or
        non blocking mode as we see the need for it.
      - the initial implementation only supports send operations on an
        already connected socket, but the intent is to extend this class
        so it can handle receive or connect operations.

    '''

    # Result codes used in send()/send_ready() methods.
    SEND_DONE = 1
    SENDING = 2
    CLOSED = 3

    def __init__(self, sock):
        '''Constructor.

        Parameter:
          sock (Python socket): the socket to be used for the transaction.
            It must represent a TCP socket; otherwise DNSTCPContextError
            will be raised.  It's also expected to be connected, but it's
            not checked on construction; a subsequent send operation would
            fail.

        '''
        if sock.proto != socket.IPPROTO_TCP:
            raise DNSTCPContextError('not a TCP socket, proto: ' +
                                     str(sock.proto))
        sock.setblocking(False)
        self.__sock = sock
        self.__send_buffer = None
        self.__remote_addr = sock.getpeername() # record it for logging

    def send(self, data):
        '''Send a DNS message.

        In the non blocking mode, it sends as much data as possible via
        the underlying TCP socket until it would block or all data are sent
        out, and returns the corresponding result code.  This method
        therefore doesn't block in this mode.

          Note: the initial implementation only works in the non blocking
          mode.

        This method must not be called once an error is detected and
        CLOSED is returned or a prior send attempt is ongoing (with
        the result code of SENDING); otherwise DNSTCPContextError is
        raised.

        Parameter:
          data (binary): A binary sequence that is supposed to be a
            complete DNS message in the wire format.  It must meet
            the assumption that DNSTCPSendBuffer requires.

        Return:
          An integer constant representing the result:
          - SEND_DONE All data have been sent out successfully.
          - SENDING All writable data has been sent out, and further
              attempt would block at the moment.  The caller is expected
              to detect it when the underlying socket is writable again
              and call send_ready() to continue the send.
          - CLOSED A network error happened before the send operation is
              completed.  The underlying socket has been closed, and this
              context object will be unusable.

        '''
        if self.__sock is None:
            raise DNSTCPContextError('send() called after close')
        if self.__send_buffer is not None:
            raise DNSTCPContextError('duplicate send()')

        self.__send_buffer = DNSTCPSendBuffer(data)
        self.__send_marker = 0
        return self.__do_send()

    def send_ready(self):
        '''Resume sending a DNS message.

        This method is expected to be called followed by a send() call or
        another send_ready() call that resulted in SENDING, when the caller
        detects the underlying socket becomes writable.  It works as
        send() except that it continues the send operation from the suspended
        position of the data at the time of the previous call.

        This method must not be called once an error is detected and
        CLOSED is returned or a send() method hasn't been called to
        start the operation; otherwise DNSTCPContextError is raised.

        Return: see send().

        '''
        if self.__sock is None:
            raise DNSTCPContextError('send() called after close')
        if self.__send_buffer is None:
            raise DNSTCPContextError('send_ready() called before send')

        return self.__do_send()

    def __do_send(self):
        while True:
            data = self.__send_buffer.get_data(self.__send_marker)
            if data is None:
                # send complete; clear the internal buffer for next possible
                # send.
                logger.debug(logger.DBGLVL_TRACE_DETAIL,
                             PYSERVER_COMMON_DNS_TCP_SEND_DONE,
                             ClientFormatter(self.__remote_addr),
                             self.__send_marker)
                self.__send_buffer = None
                self.__send_marker = 0
                return self.SEND_DONE
            try:
                cc = self.__sock.send(data)
            except socket.error as ex:
                total_len = self.__send_buffer.get_total_len()
                if ex.errno == errno.EAGAIN:
                    logger.debug(logger.DBGLVL_TRACE_DETAIL,
                                 PYSERVER_COMMON_DNS_TCP_SEND_PENDING,
                                 ClientFormatter(self.__remote_addr),
                                 self.__send_marker, total_len)
                    return self.SENDING
                logger.warn(PYSERVER_COMMON_DNS_TCP_SEND_FAILED,
                            ClientFormatter(self.__remote_addr),
                            self.__send_marker, total_len, ex)
                self.__sock.close()
                self.__sock = None
                return self.CLOSED
            self.__send_marker += cc

    def close(self):
        '''Close the socket.

        This method closes the underlying socket.  Once called, the context
        object is effectively useless; any further method call would result
        in a DNSTCPContextError exception.

        The underlying socket will be automatically (and implicitly) closed
        when this object is deallocated, but Python seems to expect socket
        objects should be explicitly closed before deallocation.  So it's
        generally advisable for the user of this object to call this method
        explicitly when it doesn't need the context.

        This method can be called more than once or can be called after
        other I/O related methods have returned CLOSED; it's compatible
        with the close() method of the Python socket class.

        '''
        if self.__sock is None:
            return
        self.__sock.close()
        self.__sock = None      # prevent further operation
