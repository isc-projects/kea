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

# This file is not installed. The log.so is installed into the right place.
# It is only to find it in the .libs directory when we run as a test or
# from the build directory.
# But as nobody gives us the builddir explicitly (and we can't use generation
# from .in file, as it would put us into the builddir and we wouldn't be found)
# we guess from current directory. Any idea for something better? This should
# be enough for the tests, but would it work for B10_FROM_SOURCE as well?
# Should we look there? Or define something in bind10_config?

import os
import sys

for base in sys.path[:]:
    loglibdir = os.path.join(base, 'isc/log/.libs')
    if os.path.exists(loglibdir):
        sys.path.insert(0, loglibdir)

from log import *
