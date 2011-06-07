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

# This tests it can be loaded, nothing more yet
import isc.log
import unittest

class LogDict(unittest.TestCase):
    def setUp(self):
        # We work on a test dictionary now.
        isc.log.set_test_dictionary(True)
    def tearDown(self):
        # Return to the global dictionary
        isc.log.set_test_dictionary(False)

    def test_load_msgs(self):
        # Try loading a message and see it's there, but nothing more
        self.assertEqual(isc.log.create_message("ID", "Text"), "ID")
        self.assertEqual(isc.log.get_message("ID"), "Text")
        self.assertEqual(isc.log.get_message("no-ID"), None)

if __name__ == '__main__':
    unittest.main()
