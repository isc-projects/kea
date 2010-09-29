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

class IPAddr:
    """Stores an IPv4 or IPv6 address."""
    family = None
    addr = None

    def __init__(self, addr):
        try:
            a = socket.inet_pton(socket.AF_INET, addr)
            self.family = socket.AF_INET
            self.addr = a
            return
        except:
            pass

        try:
            a = socket.inet_pton(socket.AF_INET6, addr)
            self.family = socket.AF_INET6
            self.addr = a
            return
        except Exception as e:
            raise e

    def __str__(self):
        return socket.inet_ntop(self.family, self.addr)
