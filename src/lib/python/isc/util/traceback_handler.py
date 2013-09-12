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

from isc.log_messages.util_messages import *
import sys
import tempfile
import os
import traceback

logger = isc.log.Logger('util')

def traceback_handler(main):
    """
    Handle uncaught exception from the main callable.

    The function runs the callable passed as main (it is called
    without any provided parameters). If it raises any exception,
    the exception is logged and the application is terminated.
    """
    try:
        return main()
    except Exception as e:
        fd, name = tempfile.mkstemp(text=True)
        with os.fdopen(fd, 'w') as handle:
            traceback.print_exc(None, handle)
        logger.fatal(UNHANDLED_EXCEPTION, type(e).__name__, e, name)
        sys.exit(1)
