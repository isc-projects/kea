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

READ_ZONE_DB_FILE = TESTDATA_PATH + "example.com.sqlite3"
BROKEN_DB_FILE = TESTDATA_PATH + "brokendb.sqlite3"
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "example.com.out.sqlite3"
NEW_DB_FILE = TESTDATA_WRITE_PATH + "new_db.sqlite3"

def example_reader():
    my_zone = [
        ("example.com.",    "3600",    "IN",  "SOA", "ns.example.com. admin.example.com. 1234 3600 1800 2419200 7200"),
        ("example.com.",    "3600",    "IN",  "NS", "ns.example.com."),
        ("ns.example.com.", "3600",    "IN",  "A", "192.0.2.1")
    ]
    for rr in my_zone:
        yield rr

def example_reader_nested():
    # this iterator is used in the 'locked' test; it will cause
    # the load() method to try and write to the same database
    sqlite3_ds.load(WRITE_ZONE_DB_FILE,
                    ".",
                    example_reader)
    return example_reader()

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
                          BROKEN_DB_FILE)
        self.assertTrue(sqlite3_ds.zone_exist("example.com.",
                        READ_ZONE_DB_FILE))
        self.assertFalse(sqlite3_ds.zone_exist("example.org.",
                         READ_ZONE_DB_FILE))

    def test_load_db(self):
        sqlite3_ds.load(WRITE_ZONE_DB_FILE, ".", example_reader)

    def test_locked_db(self):
        # load it first to make sure it exists
        sqlite3_ds.load(WRITE_ZONE_DB_FILE, ".", example_reader)

        # and manually create a writing session as well
        con = sqlite3.connect(WRITE_ZONE_DB_FILE);
        cur = con.cursor()
        cur.execute("delete from records")

        self.assertRaises(sqlite3_ds.Sqlite3DSError,
                          sqlite3_ds.load, WRITE_ZONE_DB_FILE, ".",
                          example_reader)

        con.rollback()

        # and make sure lock does not stay
        sqlite3_ds.load(WRITE_ZONE_DB_FILE, ".", example_reader)

        # force locked db by nested loads
        self.assertRaises(sqlite3_ds.Sqlite3DSError,
                          sqlite3_ds.load, WRITE_ZONE_DB_FILE, ".",
                          example_reader_nested)

        # and make sure lock does not stay
        sqlite3_ds.load(WRITE_ZONE_DB_FILE, ".", example_reader)

class NewDBFile(unittest.TestCase):
    def tearDown(self):
        # remove the created database after every test
        if (os.path.exists(NEW_DB_FILE)):
            os.remove(NEW_DB_FILE)

    def setUp(self):
        # remove the created database before every test too, just
        # in case a test got aborted half-way, and cleanup didn't occur
        if (os.path.exists(NEW_DB_FILE)):
            os.remove(NEW_DB_FILE)

    def test_new_db(self):
        self.assertFalse(os.path.exists(NEW_DB_FILE))
        sqlite3_ds.open(NEW_DB_FILE)
        self.assertTrue(os.path.exists(NEW_DB_FILE))

    def test_new_db_locked(self):
        self.assertFalse(os.path.exists(NEW_DB_FILE))
        con = sqlite3.connect(NEW_DB_FILE);
        con.isolation_level = None
        cur = con.cursor()
        cur.execute("BEGIN IMMEDIATE TRANSACTION")

        # load should now fail, since the database is locked,
        # and the open() call needs an exclusive lock
        self.assertRaises(sqlite3.OperationalError,
                          sqlite3_ds.open, NEW_DB_FILE, 0.1)

        con.rollback()
        cur.close()
        con.close()
        self.assertTrue(os.path.exists(NEW_DB_FILE))

        # now that we closed our connection, load should work again
        sqlite3_ds.open(NEW_DB_FILE)

        # the database should now have been created, and a new load should
        # not require an exclusive lock anymore, so we lock it again
        con = sqlite3.connect(NEW_DB_FILE);
        cur = con.cursor()
        cur.execute("BEGIN IMMEDIATE TRANSACTION")
        sqlite3_ds.open(NEW_DB_FILE, 0.1)
        con.rollback()
        cur.close()
        con.close()

if __name__ == '__main__':
    unittest.main()
