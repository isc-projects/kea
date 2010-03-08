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

import sqlite3, re, random
import isc

#########################################################################
# define exceptions
#########################################################################
class Sqlite3DSError(Exception):
    pass

#########################################################################
# create: set up schema for a newly created zones/records database
#########################################################################
def create(cur):
    """Create new zone database"""
    cur.execute("CREATE TABLE schema_version (version INTEGER NOT NULL)")
    cur.execute("INSERT INTO schema_version VALUES (1)")
    cur.execute("""CREATE TABLE zones (id INTEGER PRIMARY KEY, 
                   name STRING NOT NULL COLLATE NOCASE,
                   rdclass STRING NOT NULL COLLATE NOCASE DEFAULT 'IN', 
                   dnssec BOOLEAN NOT NULL DEFAULT 0)""")
    cur.execute("CREATE INDEX zones_byname ON zones (name)")
    cur.execute("""CREATE TABLE records (id INTEGER PRIMARY KEY, 
                   zone_id INTEGER NOT NULL,
                   name STRING NOT NULL COLLATE NOCASE,
                   rname STRING NOT NULL COLLATE NOCASE,
                   ttl INTEGER NOT NULL,
                   rdtype STRING NOT NULL COLLATE NOCASE,
                   sigtype STRING COLLATE NOCASE,
                   rdata STRING NOT NULL)""")
    cur.execute("CREATE INDEX records_byname ON records (name)")
    cur.execute("CREATE INDEX records_byrname ON records (rname)")
    cur.execute("""CREATE TABLE nsec3 (id INTEGER PRIMARY KEY, 
                   zone_id INTEGER NOT NULL,
                   hash STRING NOT NULL COLLATE NOCASE,
                   owner STRING NOT NULL COLLATE NOCASE,
                   ttl INTEGER NOT NULL,
                   rdtype STRING NOT NULL COLLATE NOCASE,
                   rdata STRING NOT NULL)""")
    cur.execute("CREATE INDEX nsec3_byhash ON nsec3 (hash)")

#########################################################################
# open: open a database.  if the database is not yet set up, 
# call create to do so.
# input:
#   dbfile - the filename for the sqlite3 database
# returns:
#   sqlite3 connection, sqlite3 cursor
#########################################################################
def open(dbfile):
    """Open the database file.  If necessary, set it up"""
    try: 
        conn = sqlite3.connect(dbfile)
        cur = conn.cursor()
    except Exception as e:
        fail = "Failed to open " + dbfile + ": " + e.args[0]
        raise Sqlite3DSError(fail)

    # Does the database exist yet?  If not, create it.
    try:
        cur.execute("SELECT version FROM schema_version")
        row = cur.fetchone()
    except:
        create(cur)
        conn.commit()
        row = [1]

    if row == None or row[0] != 1:
        raise Sqlite3DSError("Bad database schema version")

    return conn, cur

#########################################################################
# get_zoneid:
#   returns the zone_id for a given zone name, or an empty
#   string if the zone is not found
#########################################################################
def get_zoneid(zone, cur):
    cur.execute("SELECT id FROM zones WHERE name = ?", [zone])
    row = cur.fetchone()
    if row:
        return row[0]
    else:
        return ''

#########################################################################
# reverse_name:
#   reverse the labels of a DNS name.  (for example,
#   "bind10.isc.org." would become "org.isc.bind10.")
#########################################################################
def reverse_name(name):
    """Reverse the labels of a domain name; for example,
    given 'www.isc.org.', return 'org.isc.www.'  This is needed
    for DNSSEC sort order."""
    new = name.split('.')
    new.reverse()
    if new[0] == '':
        new.pop(0)
    return '.'.join(new)+'.'


#########################################################################
# load:
#   load a zone into the SQL database.
# input:
#   dbfile: the sqlite3 database fileanme
#   zone: the zone origin
#   zonedata: an iterable set of name/ttl/class/rrtype/rdata-text tuples
#########################################################################
def load(dbfile, zone, reader, file):
    conn, cur = open(dbfile)
    old_zone_id = get_zoneid(zone, cur)

    temp = str(random.randrange(100000))
    cur.execute("INSERT INTO zones (name, rdclass) VALUES (?, 'IN')", [temp])
    new_zone_id = cur.lastrowid

    for name, ttl, rdclass, rdtype, rdata in reader(file):
        sigtype = ''
        if rdtype.lower() == 'rrsig':
            sigtype = rdata.split()[0]

        if rdtype.lower() == 'nsec3' or sigtype.lower() == 'nsec3':
            hash = name.split('.')[0]
            cur.execute("""INSERT INTO nsec3
                           (zone_id, hash, owner, ttl, rdtype, rdata)
                           VALUES (?, ?, ?, ?, ?, ?)""",
                        [new_zone_id, hash, name, ttl, rdtype, rdata])
        elif rdtype.lower() == 'rrsig':
            cur.execute("""INSERT INTO records
                           (zone_id, name, rname, ttl, rdtype, sigtype, rdata)
                           VALUES (?, ?, ?, ?, ?, ?, ?)""",
                        [new_zone_id, name, reverse_name(name), ttl,
                        rdtype, sigtype, rdata])
        else:
            cur.execute("""INSERT INTO records
                           (zone_id, name, rname, ttl, rdtype, rdata)
                           VALUES (?, ?, ?, ?, ?, ?)""",
                        [new_zone_id, name, reverse_name(name), ttl,
                        rdtype, rdata])

    if old_zone_id:
        cur.execute("DELETE FROM zones WHERE id=?", [old_zone_id])
        cur.execute("UPDATE zones SET name=? WHERE id=?", [zone, new_zone_id])
        conn.commit()
        cur.execute("DELETE FROM records WHERE zone_id=?", [old_zone_id])
        cur.execute("DELETE FROM nsec3 WHERE zone_id=?", [old_zone_id])
        conn.commit()
    else:
        cur.execute("UPDATE zones SET name=? WHERE id=?", [zone, new_zone_id])
        conn.commit()

    cur.close()
    conn.close()
