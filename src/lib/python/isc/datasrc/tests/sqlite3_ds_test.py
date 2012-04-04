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
import sqlite3

TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep

DBFILE_NEWSCHEMA = TESTDATA_PATH + "/newschema.sqlite3";
DBFILE_OLDSCHEMA = TESTDATA_PATH + "/oldschema.sqlite3";
DBFILE_NEW_MINOR_SCHEMA = TESTDATA_PATH + "/new_minor_schema.sqlite3";

class NewDBFile(unittest.TestCase):
    def test_different_version(self):
        self.assertTrue(os.path.exists(DBFILE_NEWSCHEMA))
        self.assertRaises(sqlite3_ds.Sqlite3DSError, sqlite3_ds.open,
                          DBFILE_NEWSCHEMA)
        self.assertRaises(sqlite3_ds.Sqlite3DSError, sqlite3_ds.open,
                          DBFILE_OLDSCHEMA)
        self.assertNotEqual(None, sqlite3_ds.open(DBFILE_NEW_MINOR_SCHEMA)[0])

if __name__ == '__main__':
    unittest.main()
