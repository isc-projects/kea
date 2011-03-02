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

from isc.datasrc import sqlite3_ds
import os
import socket
import unittest

TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep

class TestSqlite3_ds(unittest.TestCase):
    def test_zone_exist(self):
        # The following file must be non existent and must be non
        # "creatable"; the sqlite3 library will try to create a new
        # DB file if it doesn't exist, so to test a failure case the
        # create operation should also fail. The "nodir", a non
        # existent directory, is inserted for this purpose.
        nodir = "/nodir/notexist"
        self.assertRaises(sqlite3_ds.Sqlite3DSError,
                          sqlite3_ds.zone_exist, "example.com", nodir)
        # Open a broken database file
        self.assertRaises(sqlite3_ds.Sqlite3DSError,
                          sqlite3_ds.zone_exist, "example.com",
                          TESTDATA_PATH + "brokendb.sqlite3")
        self.assertTrue(sqlite3_ds.zone_exist("example.com.",
                            TESTDATA_PATH + "example.com.sqlite3"))
        self.assertFalse(sqlite3_ds.zone_exist("example.org.",
                            TESTDATA_PATH + "example.com.sqlite3"))

if __name__ == '__main__':
    unittest.main()
