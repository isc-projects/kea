-- Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
--
-- Permission to use, copy, modify, and/or distribute this software for any
-- purpose with or without fee is hereby granted, provided that the above
-- copyright notice and this permission notice appear in all copies.
--
-- THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
-- REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
-- AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
-- INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
-- LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
-- OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
-- PERFORMANCE OF THIS SOFTWARE.

-- \brief Create Differences Table
--
-- This is a short-term solution to creating the differences table for testing
-- purposes.
--
-- It is assumed that the database used is a copy of the "example.org.sqlite3"
-- database in this test directory.  The diffs table is created and populated
-- with a set of RRs that purport to represent differences that end in the
-- zone as is.
--
-- The file can be executed by the command:
-- % sqlite3 -init <this-file> <database-file> ".quit"
--
-- The file gets executed as the set of SQL statements on the database file,
-- the ".quit" on the command line then  getting executed to exit SQLite3.

-- Create the diffs table
DROP TABLE diffs;
CREATE TABLE diffs (id INTEGER PRIMARY KEY,
                    zone_id INTEGER NOT NULL,
                    version INTEGER NOT NULL,
                    operation INTEGER NOT NULL,
                    name STRING NOT NULL COLLATE NOCASE,
                    rrtype STRING NOT NULL COLLATE NOCASE,
                    ttl INTEGER NOT NULL,
                    rdata STRING NOT NULL);

-- Populate it.  A dummy zone_id is used for now - this will be updated last of
-- all.

-- Change from 4294967280 (0xfffffff0) to 1230 to show serial rollover
-- Update one record in the zone.
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 4294967280,  1, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 4294967280 3600 1800 2419200 7200");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 4294967280, 1, "www.example.org.", "A", 3600, "192.0.2.31");

-- Records added in version 1230 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1230, 0, "example.org.", "SOA", 1800,
           "ns1.example.org. admin.example.org. 1230 3600 1800 2419200 7200");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1230, 0, "www.example.org.", "A", 3600, "192.0.2.21");

-- Change 1230 to 1231: Change change a parameter of the SOA record
-- Records removed from version 1230 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1230, 1, "example.org.", "SOA", 1800,
           "ns1.example.org. admin.example.org. 1230 3600 1800 2419200 7200");

-- Records added in version 1231 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1231, 0, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1231 3600 1800 2419200 7200");


-- Change 1231 to 1232: Remove one record, don't add anything.
-- Records removed from version 1231 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1231, 1, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1231 3600 1800 2419200 7200");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1231, 1, "unused.example.org.", "A", 3600, "192.0.2.102");

-- Records added in version 1232 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1232, 0, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1232 3600 1800 2419200 7200");

-- Change 1232 to 1233: Add two, don't remove anything.
-- Records removed from version 1232 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1232, 1, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1232 3600 1800 2419200 7200");

-- Records added in version 1233 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1233, 0, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1233 3600 1800 2419200 7200");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1233, 0, "sub.example.org.", "NS", 3600, "ns.sub.example.org.");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1233, 0, "ns.sub.example.org.", "A", 3600, "192.0.2.101");


-- Change 1233 to 1234: change addresses of two A records
-- Records removed from version 1233 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1233, 1, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1233 3600 1800 2419200 7200");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1233, 1, "www.example.org.", "A", 3600, "192.0.2.21");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1233, 1, "mail.example.org.", "A", 3600, "192.0.2.210");

-- Records added in version 1234 of the zone
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1234, 0, "example.org.", "SOA", 3600,
           "ns1.example.org. admin.example.org. 1234 3600 1800 2419200 7200");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1234, 0, "www.example.org.", "A", 3600, "192.0.2.1");
INSERT INTO diffs(zone_id, version, operation, name, rrtype, ttl, rdata)
    VALUES(1, 1234, 0, "mail.example.org.", "A", 3600, "192.0.2.10");

-- Finally, update the zone_id in the diffs table with what is actually
-- in the zone table.
UPDATE diffs SET zone_id =
   (SELECT id FROM ZONES LIMIT 1);
