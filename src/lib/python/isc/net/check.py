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

"""
Checking and parsing of ports and IP addresses.
"""

def port_check(port):
    """
    Takes a port as an int or string and checks if it is valid. It returns
    the port as int. If it is not a valid port (the string doesn't contain
    number or it is not in the valid range), it raises ValueError.
    """
    pass

def addr_check(addr):
    """
    Checks and parses an IP address (either IPv4 or IPv6) and returns
    the IPAddr object. It raises ValueError if the passed string is not
    valid IP address.
    """
    pass
