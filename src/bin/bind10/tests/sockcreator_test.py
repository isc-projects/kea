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
Tests for the bind10.sockcreator module.
"""

import unittest
import struct
import socket
from bind10.sockcreator import Parser, CreatorError
from isc.net.addr import IPAddr

class FakeCreator:
    """
    Class emulating the socket to the socket creator. It can be given expected
    data to receive (and check) and responses to give to the Parser class
    during testing.
    """

    class InvalidPlan(Exception):
        """
        Raised when someone wants to recv when sending is planned or vice
        versa.
        """
        pass

    class InvalidData(Exception):
        """
        Raises when the data passed to sendall are not the same as expected.
        """
        pass

    def __init__(self, plan):
        """
        Create the object. The plan variable contains list of expected actions,
        in form:

        [('r', 'Data to return from recv'), ('s', 'Data expected on sendall'),
             , ('d', 'File descriptor number to return from read_sock'), ('e',
             None), ...]

        It modifies the array as it goes.
        """
        self.__plan = plan

    def __get_plan(self, expected):
        if len(self.__plan) == 0:
            raise InvalidPlan('Nothing more planned')
        (kind, data) = self.__plan[0]
        if kind == 'e':
            self.__plan.pop(0)
            raise socket.error('False socket error')
        if kind != expected:
            raise InvalidPlan('Planned ' + kind + ', but ' + expected +
                'requested')
        return data

    def recv(self, maxsize):
        """
        Emulate recv. Returs maxsize bytes from the current recv plan. If
        there are data left from previous recv call, it is used first.

        If no recv is planned, raises InvalidPlan.
        """
        data = self.__get_plan('r')
        result, rest = data[:maxsize], data[maxsize:]
        if len(rest) > 0:
            self.__plan[0] = ('r', rest)
        else:
            self.__plan.pop(0)
        return result

    def read_fd(self):
        """
        Emulate the reading of file descriptor. Returns one from a plan.

        It raises InvalidPlan if no socket is planned now.
        """
        fd = self.__get_plan('f')
        self.__plan.pop(0)
        return fd

    def sendall(self, data):
        """
        Checks that the data passed are correct according to plan. It raises
        InvalidData if the data differs or InvalidPlan when sendall is not
        expected.
        """
        planned = self.__get_plan('s')
        dlen = len(data)
        prefix, rest = planned[:dlen], planned[dlen:]
        if prefix != data:
            raise InvalidData('Expected "' + str(prefix)+ '", got "' +
                str(data) + '"')
        if len(rest) > 0:
            self.__plan[0] = ('s', rest)
        else:
            self.__plan.pop(0)

    def all_used(self):
        """
        Returns if the whole plan was consumed.
        """
        return len(self.__plan) == 0

class ParserTests(unittest.TestCase):
    """
    Testcases for the Parser class.
    """
    def __terminate(self):
        creator = FakeCreator([('s', b'T'), ('r', b'')])
        parser = Parser(creator)
        self.assertEqual(None, parser.terminate())
        self.assertTrue(creator.all_used())
        return parser

    def test_terminate(self):
        """
        Test if the command to terminate is correct and it waits for reading the
        EOF.
        """
        self.__terminate()

    def test_terminate_error1(self):
        """
        Test it reports an exception when there's error terminating the creator.
        This one raises an error when receiving the EOF.
        """
        creator = FakeCreator([('s', b'T'), ('e', None)])
        parser = Parser(creator)
        with self.assertRaises(CreatorError) as cm:
            parser.terminate()
        self.assertTrue(cm.exception.fatal)
        self.assertEqual(None, cm.exception.errno)

    def test_terminate_error2(self):
        """
        Test it reports an exception when there's error terminating the creator.
        This one raises an error when sending data.
        """
        creator = FakeCreator([('e', None)])
        parser = Parser(creator)
        with self.assertRaises(CreatorError) as cm:
            parser.terminate()
        self.assertTrue(cm.exception.fatal)
        self.assertEqual(None, cm.exception.errno)

    def test_terminate_twice(self):
        """
        Test we can't terminate twice.
        """
        parser = self.__terminate()
        with self.assertRaises(CreatorError) as cm:
            parser.terminate()
        self.assertTrue(cm.exception.fatal)
        self.assertEqual(None, cm.exception.errno)

    def test_terminate_error3(self):
        """
        Test it reports an exception when there's error terminating the creator.
        This one sends data when it should have terminated.
        """
        creator = FakeCreator([('s', b'T'), ('r', b'Extra data')])
        parser = Parser(creator)
        with self.assertRaises(CreatorError) as cm:
            parser.terminate()
        self.assertTrue(cm.exception.fatal)
        self.assertEqual(None, cm.exception.errno)

    def test_crash(self):
        """
        Tests that the parser correctly raises exception when it crashes
        unexpectedly.
        """
        creator = FakeCreator([('s', b'SU4\0\0\0\0\0\0'), ('r', b'')])
        parser = Parser(creator)
        with self.assertRaises(CreatorError) as cm:
            parser.get_socket(IPAddr('0.0.0.0'), 0, 'UDP')
        self.assertTrue(creator.all_used())
        # Is the exception correct?
        self.assertTrue(cm.exception.fatal)
        self.assertEqual(None, cm.exception.errno)

    def test_error(self):
        """
        Tests that the parser correctly raises non-fatal exception when
        the socket can not be created.
        """
        # We split the int to see if it can cope with data coming in
        # different packets
        intpart = struct.pack('@i', 42)
        creator = FakeCreator([('s', b'SU4\0\0\0\0\0\0'), ('r', b'ES' +
            intpart[:1]), ('r', intpart[1:])])
        parser = Parser(creator)
        with self.assertRaises(CreatorError) as cm:
            parser.get_socket(IPAddr('0.0.0.0'), 0, 'UDP')
        self.assertTrue(creator.all_used())
        # Is the exception correct?
        self.assertFalse(cm.exception.fatal)
        self.assertEqual(42, cm.exception.errno)

    def __error(self, plan):
        creator = FakeCreator(plan)
        parser = Parser(creator)
        with self.assertRaises(CreatorError) as cm:
            parser.get_socket(IPAddr('0.0.0.0'), 0, socket.SOCK_DGRAM)
        self.assertTrue(creator.all_used())
        self.assertTrue(cm.exception.fatal)

    def test_error_send(self):
        self.__error([('e', None)])

    def test_error_recv(self):
        self.__error([('s', b'SU4\0\0\0\0\0\0'), ('e', None)])

    def test_error_read_fd(self):
        self.__error([('s', b'SU4\0\0\0\0\0\0'), ('r', b'S'), ('e', None)])

    def __create(self, addr, socktype, encoded):
        creator = FakeCreator([('s', b'S' + encoded), ('r', b'S'), ('f', 42)])
        parser = Parser(creator)
        self.assertEqual(42, parser.get_socket(IPAddr(addr), 42, socktype))

    def test_create1(self):
        self.__create('192.0.2.0', 'UDP', b'U4\0\x2A\xC0\0\x02\0')

    def test_create2(self):
        self.__create('2001:db8::', socket.SOCK_STREAM,
            b'T6\0\x2A\x20\x01\x0d\xb8\0\0\0\0\0\0\0\0\0\0\0\0')

    def test_create_terminated(self):
        """
        Test we can't request sockets after it was terminated.
        """
        parser = self.__terminate()
        with self.assertRaises(CreatorError) as cm:
            parser.get_socket(IPAddr('0.0.0.0'), 0, 'UDP')
        self.assertTrue(cm.exception.fatal)
        self.assertEqual(None, cm.exception.errno)

    def test_invalid_socktype(self):
        """
        Test invalid socket type is rejected
        """
        self.assertRaises(ValueError, Parser(FakeCreator([])).get_socket,
                          IPAddr('0.0.0.0'), 42, 'RAW')

    def test_invalid_family(self):
        """
        Test it rejects invalid address family.
        """
        addr = IPAddr('0.0.0.0')
        addr.family = 'Nonsense'
        self.assertRaises(ValueError, Parser(FakeCreator([])).get_socket,
                          addr, 42, socket.SOCK_DGRAM)

if __name__ == '__main__':
    unittest.main()
