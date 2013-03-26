# Copyright (C) 2013  Internet Systems Consortium.
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
import unittest
from isc.util.address_formatter import AddressFormatter

class AddressFormatterTest(unittest.TestCase):
    def test_v4(self):
        self.assertEqual("127.0.0.1:123",
                         str(AddressFormatter(("127.0.0.1", 123))))
        self.assertEqual("127.0.0.1:123",
                         str(AddressFormatter(("127.0.0.1", 123), None)))
        self.assertEqual("192.0.2.1:1",
                         str(AddressFormatter(("192.0.2.1", 1))))

    def test_v6(self):
        self.assertEqual("[::1]:123",
                         str(AddressFormatter(("::1", 123))));
        self.assertEqual("[::1]:123",
                         str(AddressFormatter(("::1", 123), None)))
        self.assertEqual("[2001:db8::]:1",
                         str(AddressFormatter(("2001:db8::", 1))))

    def test_force_family_good(self):
        self.assertEqual("127.0.0.1:123",
                         str(AddressFormatter(("127.0.0.1", 123),
                                              socket.AF_INET)))
        self.assertEqual("[::1]:123",
                         str(AddressFormatter(("::1", 123),
                                              socket.AF_INET6)))

    def test_force_family_bad(self):
        """
        These results are 'bad' as in they don't return the value as
        specified by our guidelines, since the internal check is skipped if
        the family is given
        """
        self.assertEqual("[127.0.0.1]:123",
                         str(AddressFormatter(("127.0.0.1", 123),
                                              socket.AF_INET6)))
        self.assertEqual("::1:123",
                         str(AddressFormatter(("::1", 123),
                                              socket.AF_INET)))

    def test_bad_values(self):
        self.assertRaises(ValueError, str, AddressFormatter("string"))
        self.assertRaises(ValueError, str, AddressFormatter(None))
        self.assertRaises(ValueError, str, AddressFormatter(1))
        self.assertRaises(ValueError, str, AddressFormatter(("::1", 123), 1))
        self.assertRaises(ValueError, str, AddressFormatter(("::1", 123), 1))



if __name__ == "__main__":
    unittest.main()
