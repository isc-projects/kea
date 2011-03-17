# Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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
Module to manipulate the python processes.

It contains only function to rename the process, which is currently
wrapper around setproctitle library. Does not fail if the setproctitle
module is missing, but does nothing in that case.
"""
try:
    from setproctitle import setproctitle
except ImportError:
    def setproctitle(_): pass
import sys
import os.path

"""
Rename the current process to given name (so it can be found in ps).
If name is None, use zero'th command line argument.
"""
def rename(name=None):
    if name is None:
        name = os.path.basename(sys.argv[0])
    setproctitle(name)
