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
            addrinfo = socket.getaddrinfo(addr, None, 0, 0, 0,
                socket.AI_NUMERICHOST)[0]
            self.family = addrinfo[0]
            if not self.family in [socket.AF_INET, socket.AF_INET6]:
                raise InvalidAddress(
                    'IPAddr can hold only IPv4 or IPv6 address')
            self.addr = socket.inet_pton(self.family, addr)
        except socket.error as e:
            raise InvalidAddress(str(e))

    def __str__(self):
        return socket.inet_ntop(self.family, self.addr)
