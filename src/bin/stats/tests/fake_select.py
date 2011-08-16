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
A mock-up module of select

*** NOTE ***
It is only for testing stats_httpd module and not reusable for
external module.
"""

import fake_socket
import errno

class error(Exception):
    pass

def select(rlst, wlst, xlst, timeout):
    if type(timeout) != int and type(timeout) != float:
            raise TypeError("Error: %s must be integer or float"
                            % timeout.__class__.__name__)
    for s in rlst + wlst + xlst:
        if type(s) != fake_socket.socket:
            raise TypeError("Error: %s must be a dummy socket"
                            % s.__class__.__name__)
        s._called = s._called + 1
        if s._called > 3:
            raise error("Something is happened!")
        elif s._called > 2:
            raise error(errno.EINTR)
    return (rlst, wlst, xlst)
