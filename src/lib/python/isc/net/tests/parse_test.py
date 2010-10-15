# Copyright (C) 2010  CZ NIC
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

"""Tests for isc.net.parse."""
import unittest
from isc.net.parse import port_parse, addr_parse

class TestCheckPort(unittest.TestCase):
    """
    Testcases for the isc.net.port_parse function
    """
    def test_fail(self):
        """
        Test if it fails on invalid input in the correct way.
        """
        self.assertRaises(ValueError, port_parse, "not a number")
        self.assertRaises(ValueError, port_parse, -1)
        self.assertRaises(ValueError, port_parse, 65536)

    def test_success(self):
        """
        Test if it succeeds on valid inputs and returns the correct output
        """
        self.assertEqual(port_parse(0), 0)
        self.assertEqual(port_parse("65535"), 65535)
        self.assertEqual(port_parse(1234), 1234)

class TestCheckIP(unittest.TestCase):
    """
    Testcases for the isc.net.ip_par function
    """
    def test_fail(self):
        """
        Test if it fails on invalid input the correct way.
        """
        self.assertRaises(ValueError, addr_parse, "not an address")
        self.assertRaises(ValueError, addr_parse, "123.456.789.012")
        self.assertRaises(ValueError, addr_parse, "123.0.0.")
        # Address range not allowed
        self.assertRaises(ValueError, addr_parse, "192.0.2.0/24")
        self.assertRaises(ValueError, addr_parse, "0000.0.0.0")
        self.assertRaises(ValueError, addr_parse, "bada:ddr0::")
        self.assertRaises(ValueError, addr_parse, "2001:db8::/32")
        # This should be one part too long (eg. 9 segments)
        self.assertRaises(ValueError, addr_parse, "2001:db8:0:0:0:0:0:0:0")
        # Only one :: allowed
        self.assertRaises(ValueError, addr_parse, "2001::db8::c")

    def test_success(self):
        """
        Test if it succeeds on valid inputs and returns addresses that look
        the same.
        """
        self.assertEqual("192.0.2.0", str(addr_parse("192.0.2.0")))
        self.assertEqual("2001:bd8::", str(addr_parse("2001:bd8::")))
        # It should strip the unnecesarry parts
        self.assertEqual("2001:bd8::", str(addr_parse("2001:bd8:0:0:0:0:0:0")))
        self.assertEqual("::", str(addr_parse("::")))

if __name__ == "__main__":
    unittest.main()
