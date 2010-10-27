# Copyright (C) 2010  Internet Systems Consortium.
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

"""Tests for the isc.net.addr module."""
import unittest
import socket
from isc.net.addr import IPAddr, InvalidAddress

class TestIPAddr(unittest.TestCase):
    """Test for the IPAddr class."""
    def test_v6ok(self):
        """Test if we can parse IPv6."""
        addr = IPAddr('2001:4f8::1')
        self.assertEqual(addr.family, socket.AF_INET6)
        self.assertEqual(addr.addr, socket.inet_pton(socket.AF_INET6, '2001:4f8::1'))

    def test_v4ok(self):
        """Test if we can parse IPv4."""
        addr = IPAddr('127.127.127.127')
        self.assertEqual(addr.family, socket.AF_INET)
        self.assertEqual(addr.addr, socket.inet_aton('127.127.127.127'))

    def test_badaddr(self):
        """Test if we raise on wrong address."""
        self.assertRaises(InvalidAddress, IPAddr, 'foobar')
        self.assertRaises(InvalidAddress, IPAddr, 'foo::bar')
        self.assertRaises(InvalidAddress, IPAddr, '123')
        self.assertRaises(InvalidAddress, IPAddr, '123.456.789.0')
        self.assertRaises(InvalidAddress, IPAddr, '127/8')
        self.assertRaises(InvalidAddress, IPAddr, '0/0')
        self.assertRaises(InvalidAddress, IPAddr, '1.2.3.4/32')
        self.assertRaises(InvalidAddress, IPAddr, '0')
        self.assertRaises(InvalidAddress, IPAddr, '')

if __name__ == '__main__':
    unittest.main()
