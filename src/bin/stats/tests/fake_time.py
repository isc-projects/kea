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

# $Id$
__version__ = "$Revision$"

# This is a dummy time class against a Python standard time class.
# It is just testing use only.
# Other methods which time class has is not implemented.
# (This class isn't orderloaded for time class.)

# These variables are constant. These are example.
_TEST_TIME_SECS = 1283364938.229088
_TEST_TIME_STRF = '2010-09-01T18:15:38Z'

def time():
    """
    This is a dummy time() method against time.time()
    """
    # return float constant value
    return _TEST_TIME_SECS

def gmtime():
    """
    This is a dummy gmtime() method against time.gmtime()
    """
    # always return nothing
    return None

def strftime(*arg):
    """
    This is a dummy gmtime() method against time.gmtime()
    """
    return _TEST_TIME_STRF


