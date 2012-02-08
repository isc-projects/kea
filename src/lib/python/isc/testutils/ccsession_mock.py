# Copyright (C) 2012  Internet Systems Consortium.
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

class MockModuleCCSession():
    """Fake ModuleCCSession with a minimal implementation as needed by the
       tests. Currently this module only stores whether some methods have
       been called on it (send_stopping(), and close())"""
    def __init__(self):
        """Will be set to True when send_stopping() is called"""
        self.stopped = False
        """Will be set to True when close() is called"""
        self.closed = False

    def send_stopping(self):
        """Fake send_stopping() call. No message is sent, but only stores
           that this method has been called."""
        self.stopped = True

    def close(self):
        """Fake close() call. Nothing is closed, but only stores
           that this method has been called."""
        self.closed = True
