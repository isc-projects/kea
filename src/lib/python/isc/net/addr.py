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

"""Module where address representations live."""
import socket
import re

# These regular expressions are not validating. They are supposed to
# guess which kind of address it is and throw away just obvious nonsense.
# It is expected that inet_pton will complain if it isn't an address, so
# they can have false positives.
isv4 = re.compile(r'^([0-9]{1,3}\.){3}[0-9]{1,3}$')
isv6 = re.compile(r'^([0-9a-f]{,4}:){,7}[0-9a-f]{,4}$', re.IGNORECASE)

class InvalidAddress(ValueError):
    """Exception for invalid addresses."""
    pass

class IPAddr:
    """Stores an IPv4 or IPv6 address."""
    family = None
    addr = None

    def __init__(self, addr):
        """
        Creates the address object from a string representation. It raises
        an InvalidAddr exception if the provided string isn't valid address.
        """
        try:
            if isv4.match(addr):
                a = socket.inet_pton(socket.AF_INET, addr)
                self.family = socket.AF_INET
                self.addr = a
            elif isv6.match(addr):
                a = socket.inet_pton(socket.AF_INET6, addr)
                self.family = socket.AF_INET6
                self.addr = a
            else:
                raise InvalidAddress(addr +
                    ' is not a valid IPv4 nor IPv6 address')
        except socket.error as e:
            raise InvalidAddress(str(e))

    def __str__(self):
        return socket.inet_ntop(self.family, self.addr)
