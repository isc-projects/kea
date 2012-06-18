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

'''Tests for isc.server_common.dns_tcp'''

import isc.log
from isc.server_common.dns_tcp import *
import socket
import errno
import unittest

def check_length_field(assert_eq, len_data, expected_len):
    # Examine the "length field" part of the data.  It should be 2-byte field,
    # and (in our implementation) always given as a separate chunk of data.
    # The 16-bit length value of the actual data should be stored in the
    # network byte order.
    len_high = (expected_len >> 8) & 0x00ff
    len_low = (expected_len & 0x00ff)
    assert_eq(2, len(len_data))
    assert_eq(len_high, len_data[0])
    assert_eq(len_low, len_data[1])

class BufferTest(unittest.TestCase):
    def check_length_field(self, buf, expected_len):
        '''Common subtest for the main tests that checks the length buffer.'''
        check_length_field(self.assertEqual, buf.get_data(0), expected_len)

        # Confirm the get_data(1) returns the latter half of the (partial)
        # buffer.
        self.assertEqual(1, len(buf.get_data(1)))
        self.assertEqual(expected_len & 0x00ff, buf.get_data(1)[0])

    def test_small_data(self):
        # The smallest size (in practice) of data: that of the header field.
        expected_data = b'x' * 12
        buf = DNSTCPSendBuffer(expected_data)
        self.check_length_field(buf, 12)

        self.assertEqual(expected_data, buf.get_data(2))
        self.assertEqual(b'x' * 11, buf.get_data(3))
        self.assertEqual(None, buf.get_data(14))

    def test_large_data(self):
        # Test with an arbitrarily large size of data.
        buf = DNSTCPSendBuffer(b'x' * 65534)
        self.check_length_field(buf, 65534)
        self.assertEqual(b'x' * 65534, buf.get_data(2))
        self.assertEqual(b'x' * 2, buf.get_data(65534))
        self.assertEqual(None, buf.get_data(65536))

    def test_largest_data(self):
        # This is the largest possible size of DNS message.
        buf = DNSTCPSendBuffer(b'y' * 65535)
        self.check_length_field(buf, 65535)
        self.assertEqual(b'y', buf.get_data(65536))
        self.assertEqual(None, buf.get_data(65537))

    def test_too_large_data(self):
        # The maximum possible size of a valid DNS message is 65535.
        # Beyond that, the buffer construction should result in an exception.
        self.assertRaises(ValueError, DNSTCPSendBuffer, b'0' * 65536)

    def test_empty_data(self):
        # Unusual, but it's not rejected
        buf = DNSTCPSendBuffer(b'')
        self.check_length_field(buf, 0)
        self.assertEqual(None, buf.get_data(2))

    def test_get_total_len(self):
        self.assertEqual(14, DNSTCPSendBuffer(b'x' * 12).get_total_len())
        self.assertEqual(2, DNSTCPSendBuffer(b'').get_total_len())
        self.assertEqual(65537, DNSTCPSendBuffer(b'X' * 65535).get_total_len())

class FakeSocket:
    '''Emulating python socket w/o involving IO while allowing inspection.'''
    def __init__(self, proto=socket.IPPROTO_TCP):
        self._setblocking_val = None # record the latest value of setblocking()
        self._closed = False         # set to True on close()
        self._sent_data = []         # record the transmitted data in send()
        self._send_buflen = None     # capacity of the faked "send buffer";
                                     # None means infinity, -1 means "closed"
        self._send_cc = 0            # waterline of the send buffer
        self.proto = proto # protocol (should be TCP, but can be faked)

    def setblocking(self, on):
        self._setblocking_val = on

    def close(self):
        self._closed = True

    def send(self, data):
        # Calculate the available space in the "send buffer"
        if self._send_buflen == -1:
            raise socket.error(errno.EPIPE, "Broken pipe")
        elif self._send_buflen is None:
            available_space = len(data)
        else:
            available_space = self._send_buflen - self._send_cc
        if available_space == 0:
            # if there's no space, (assuming it's nonblocking mode) raise
            # EAGAIN.
            raise socket.error(errno.EAGAIN,
                               "Resource temporarily unavailable")
        # determine the sendable part of the data, record it, update "buffer".
        cc = min(available_space, len(data))
        self._sent_data.append(data[:cc])
        self._send_cc += cc
        return cc

    def make_send_ready(self):
        # pretend that the accrued data has been cleared, making room in
        # the send buffer.
        self._send_cc = 0

    def getpeername(self):
        '''Return faked remote address'''
        return ('2001:db8::1', 53000, 0, 0)

class ContextTest(unittest.TestCase):
    def setUp(self):
        self.__sock = FakeSocket()
        # there should be no setblocking value on the fake socket by default.
        self.assertEqual(None, self.__sock._setblocking_val)
        self.__ctx = DNSTCPContext(self.__sock)
        # dummy data that has the same length as the DNS header section:
        self.__test_data = b'x' * 12

    def test_initialization(self):
        # Creating a context (in setUp) should make the socket non-blocking.
        self.assertFalse(self.__sock._setblocking_val)

        # Only a TCP socket is accepted.
        self.assertRaises(DNSTCPContextError, DNSTCPContext,
                          FakeSocket(proto=socket.IPPROTO_UDP))

    def test_send_all(self):
        # By default, a single send() call will send out all data by 2
        # send() calls: one for the 2-byte length data and the other for the
        # actual data.
        self.assertEqual(DNSTCPContext.SEND_DONE,
                         self.__ctx.send(self.__test_data))
        self.assertEqual(2, len(self.__sock._sent_data))
        check_length_field(self.assertEqual, self.__sock._sent_data[0],
                           len(self.__test_data))
        self.assertEqual(self.__test_data, self.__sock._sent_data[1])

    def test_send_divided(self):
        # set the "send buffer" of the fake socket to 7 (half of the size of
        # len + data).
        self.__sock._send_buflen = 7

        # The initial send() can only send out the half of the data in
        # two calls to socket.send(): the first one for the length field,
        # and the other is for the first 5 bytes of the data
        self.assertEqual(DNSTCPContext.SENDING,
                         self.__ctx.send(self.__test_data))
        self.assertEqual(2, len(self.__sock._sent_data))
        check_length_field(self.assertEqual, self.__sock._sent_data[0],
                           len(self.__test_data))
        self.assertEqual(self.__test_data[:5], self.__sock._sent_data[1])

        # "flush" the send buffer of the fake socket
        self.__sock.make_send_ready()

        # send_ready() can now complete the send.  The remaining data should
        # have been passed.
        self.assertEqual(DNSTCPContext.SEND_DONE, self.__ctx.send_ready())
        self.assertEqual(3, len(self.__sock._sent_data))
        self.assertEqual(self.__test_data[5:], self.__sock._sent_data[2])

    def test_send_multi(self):
        # On a successful completion of send, another send can be done.
        for i in (0, 2):
            self.assertEqual(DNSTCPContext.SEND_DONE,
                             self.__ctx.send(self.__test_data))
            self.assertEqual(i + 2, len(self.__sock._sent_data))
            check_length_field(self.assertEqual, self.__sock._sent_data[i],
                               len(self.__test_data))
            self.assertEqual(self.__test_data, self.__sock._sent_data[i + 1])

    def test_send_reset(self):
        # the connection will be "reset" before the initial send.
        # send() should return CLOSED, and the underlying socket should be
        # closed.
        self.__sock._send_buflen = -1
        self.assertEqual(DNSTCPContext.CLOSED,
                         self.__ctx.send(self.__test_data))
        self.assertTrue(self.__sock._closed)

        # Once closed, send() cannot be called any more
        self.assertRaises(DNSTCPContextError, self.__ctx.send,
                          self.__test_data)
        # Calling close() is okay (it's NO-OP)
        self.__ctx.close()

    def test_send_divided_reset(self):
        # Similar to send_reset, but send() succeeds, and then the connection
        # will be "reset".
        self.__sock._send_buflen = 7
        self.assertEqual(DNSTCPContext.SENDING,
                         self.__ctx.send(self.__test_data))
        self.__sock._send_buflen = -1
        self.assertEqual(DNSTCPContext.CLOSED, self.__ctx.send_ready())
        self.assertTrue(self.__sock._closed)

        # Once closed, send_ready() cannot be called any more
        self.assertRaises(DNSTCPContextError, self.__ctx.send_ready)

    def test_duplicate_send(self):
        # send() cannot be called until it's completed
        self.__sock._send_buflen = 7
        self.assertEqual(DNSTCPContext.SENDING,
                         self.__ctx.send(self.__test_data))
        self.assertRaises(DNSTCPContextError, self.__ctx.send,
                          self.__test_data)

    def test_skip_send(self):
        # send_ready() cannot be called before send().
        self.assertRaises(DNSTCPContextError, self.__ctx.send_ready)

    def test_close(self):
        self.assertEqual(DNSTCPContext.SEND_DONE,
                         self.__ctx.send(self.__test_data))
        self.__ctx.close()
        self.assertTrue(self.__sock._closed)

        # Duplicate close is just ignored, and the socket is still closed.
        self.__ctx.close()
        self.assertTrue(self.__sock._closed)

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
