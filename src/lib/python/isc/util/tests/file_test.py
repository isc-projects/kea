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

import isc.util.file
import unittest

class FileTest(unittest.TestCase):
    def test_search_path_find(self):
        """Test it returns the first occurence of the file"""
        self.assertEqual('./Makefile',
                         isc.util.file.path_search('Makefile',
                                                  ['/no/such/directory/', '.',
                                                  '../tests/']))

    def test_search_path_notfound(self):
        """Test it throws an exception when the file can't be found"""
        self.assertRaises(IOError, isc.util.file.path_search, 'no file', ['/no/such/directory'])

if __name__ == "__main__":
    unittest.main()
