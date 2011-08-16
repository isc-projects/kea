# Copyright (C) 2011  Internet Systems Consortium.
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
A mock-up module of socket

*** NOTE ***
It is only for testing stats_httpd module and not reusable for
external module.
"""

import re

AF_INET = 'AF_INET'
AF_INET6 = 'AF_INET6'
_ADDRFAMILY = AF_INET
has_ipv6 = True
_CLOSED = False

class gaierror(Exception):
    pass

class error(Exception):
    pass

class socket:

    def __init__(self, family=None):
        if family is None:
            self.address_family = _ADDRFAMILY
        else:
            self.address_family = family
        self._closed = _CLOSED
        if self._closed:
            raise error('socket is already closed!')
        self._called = 0

    def close(self):
        self._closed = True

    def fileno(self):
        return id(self)

    def bind(self, server_class):
        (self.server_address, self.server_port) = server_class
        if self.address_family not in set([AF_INET, AF_INET6]):
            raise error("Address family not supported by protocol: %s" % self.address_family)
        if self.address_family == AF_INET6 and not has_ipv6:
            raise error("Address family not supported in this machine: %s has_ipv6: %s"
                        % (self.address_family, str(has_ipv6)))
        if self.address_family == AF_INET and re.search(':', self.server_address) is not None:
            raise gaierror("Address family for hostname not supported : %s %s" % (self.server_address, self.address_family))
        if self.address_family == AF_INET6 and re.search(':', self.server_address) is None:
            raise error("Cannot assign requested address : %s" % str(self.server_address))
        if type(self.server_port) is not int:
            raise TypeError("an integer is required: %s" % str(self.server_port))
        if self.server_port < 0 or self.server_port > 65535:
            raise OverflowError("port number must be 0-65535.: %s" % str(self.server_port))
