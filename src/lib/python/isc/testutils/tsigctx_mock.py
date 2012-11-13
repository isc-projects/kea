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

from pydnspp import *

class MockTSIGContext(TSIGContext):
    """Tthis is a mock of TSIGContext class for testing.
    Via its "error" attribute, you can fake the result of verify(), thereby
    you can test many of TSIG related tests without requiring actual crypto
    setups.  "error" should be either a TSIGError type value or a callable
    object (typically a function).  In the latter case, the callable object
    will take the context as a parameter, and is expected to return a
    TSIGError object.
    """

    def __init__(self, tsig_key):
        super().__init__(tsig_key)
        self.error = None
        self.verify_called = 0  # number of verify() called

    def sign(self, qid, data):
        """Transparently delegate the processing to the super class.
        It doesn't matter much anyway because normal applications that would
        be implemented in Python normally won't call TSIGContext.sign()
        directly.
        """
        return super().sign(qid, data)

    def verify(self, tsig_record, data):
        self.verify_called += 1
        # call real "verify" so that we can notice any misue (which would
        # result in exception.
        super().verify(tsig_record, data)
        return self.get_error()

    def get_error(self):
        if self.error is None:
            return super().get_error()
        if hasattr(self.error, '__call__'):
            return self.error(self)
        return self.error

    def last_had_signature(self):
        return True
