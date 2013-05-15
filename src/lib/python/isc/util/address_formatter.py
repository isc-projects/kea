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

class AddressFormatter:
    """
    A utility class to convert an IP address with a port number to a
    string.

    It takes a tuple (or list) containing and address string and a port
    number, and optionally a family.

    If the family is IPv4, the __str__ output will be
    <address>:<port>
    If the family is IPv6, the __str__ output will be
    [<address>]:<port>

    If family is not given, the __str__ method will try to figure it out
    itself, by checking for the ':' character in the address string.

    This class is designed to delay the conversion until it's explicitly
    requested, so the conversion doesn't happen if the corresponding log
    message is suppressed because of its log level (which is often the case
    for debug messages).

    Note: this optimization comes with the cost of instantiating the
    formatter object itself.  It's not really clear which overhead is
    heavier, and we may conclude it's actually better to just generate
    the strings unconditionally.  Alternatively, we can make the stored
    address of this object replaceable so that this object can be reused.
    Right now this is an open issue.

    See also ClientFormatter in the ddns.logger code, which does something
    similar but based on other criteria (and optional extra value).
    """
    def __init__(self, addr, family=None):
        self.__addr = addr
        self.__family = family

    def __addr_v4(self):
        return self.__addr[0] + ':' + str(self.__addr[1])

    def __addr_v6(self):
        return '[' + self.__addr[0] + ']:' + str(self.__addr[1])

    def __format_addr(self):
        # Some basic sanity checks, should we leave this out for efficiency?
        # (especially strings produce unexpected results)
        if isinstance(self.__addr, str) or\
           not hasattr(self.__addr, "__getitem__"):
            raise ValueError("Address must be a list or tuple")

        if self.__family is not None:
            if self.__family == socket.AF_INET6:
                return self.__addr_v6()
            elif self.__family == socket.AF_INET:
                return self.__addr_v4()
            else:
                raise ValueError("Unknown address family: " +
                                 str(self.__family))
        else:
            if self.__addr[0].find(':') >= 0:
                return self.__addr_v6()
            else:
                return self.__addr_v4()

    def __str__(self):
        return self.__format_addr()

