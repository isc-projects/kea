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


#define the index of different part of one record
RR_TYPE_INDEX = 5
RR_NAME_INDEX = 2
RR_TTL_INDEX = 4
RR_RDATA_INDEX = 7

# Current major and minor versions of schema
SCHEMA_MAJOR_VERSION = 2
SCHEMA_MINOR_VERSION = 1

class Sqlite3DSError(Exception):
    """ Define exceptions."""
    pass

def create(cur):
    """ Set up schema for a newly created zones/records database.

    Arguments:
        cur - sqlite3 cursor.
    """
    # We are creating the database because it apparently had not been at
    # the time we tried to read from it. However, another process may have
    # had the same idea, resulting in a potential race condition.
    # Therefore, we obtain an exclusive lock before we create anything
    # When we have it, we check *again* whether the database has been
    # initialized. If not, we do so.

    # If the database is perpetually locked, it'll time out automatically
    # and we just let it fail.
    cur.execute("BEGIN EXCLUSIVE TRANSACTION")
    try:
        cur.execute("SELECT version FROM schema_version")
        row = cur.fetchone()
    except sqlite3.OperationalError:
        cur.execute("""CREATE TABLE schema_version (version INTEGER NOT NULL,
                    minor INTEGER NOT NULL DEFAULT 0)""")
        cur.execute("INSERT INTO schema_version VALUES (" +
                    str(SCHEMA_MAJOR_VERSION) + ", " +
                    str(SCHEMA_MINOR_VERSION) + ")")
        cur.execute("""CREATE TABLE zones (id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL COLLATE NOCASE,
                    rdclass TEXT NOT NULL COLLATE NOCASE DEFAULT 'IN',
                    dnssec BOOLEAN NOT NULL DEFAULT 0)""")
        cur.execute("CREATE INDEX zones_byname ON zones (name)")
        cur.execute("""CREATE TABLE records (id INTEGER PRIMARY KEY,
                    zone_id INTEGER NOT NULL,
                    name TEXT NOT NULL COLLATE NOCASE,
                    rname TEXT NOT NULL COLLATE NOCASE,
                    ttl INTEGER NOT NULL,
                    rdtype TEXT NOT NULL COLLATE NOCASE,
                    sigtype TEXT COLLATE NOCASE,
                    rdata TEXT NOT NULL)""")
        cur.execute("CREATE INDEX records_byname ON records (name)")
        cur.execute("CREATE INDEX records_byrname ON records (rname)")
        cur.execute("""CREATE INDEX records_bytype_and_rname ON records
                       (rdtype, rname)""")
        cur.execute("""CREATE INDEX records_byrname_and_rdtype ON records
                       (rname, rdtype)""")
        cur.execute("""CREATE TABLE nsec3 (id INTEGER PRIMARY KEY,
                    zone_id INTEGER NOT NULL,
                    hash TEXT NOT NULL COLLATE NOCASE,
                    owner TEXT NOT NULL COLLATE NOCASE,
                    ttl INTEGER NOT NULL,
                    rdtype TEXT NOT NULL COLLATE NOCASE,
                    rdata TEXT NOT NULL)""")
        cur.execute("CREATE INDEX nsec3_byhash ON nsec3 (hash)")
        cur.execute("CREATE INDEX nsec3_byhash_and_rdtype ON nsec3 (hash, rdtype)")
        cur.execute("""CREATE TABLE diffs (id INTEGER PRIMARY KEY,
                    zone_id INTEGER NOT NULL,
                    version INTEGER NOT NULL,
                    operation INTEGER NOT NULL,
                    name TEXT NOT NULL COLLATE NOCASE,
                    rrtype TEXT NOT NULL COLLATE NOCASE,
                    ttl INTEGER NOT NULL,
                    rdata TEXT NOT NULL)""")
        cur.execute("SELECT version FROM schema_version")
        row = cur.fetchone()
    cur.execute("COMMIT TRANSACTION")
    return row

def open(dbfile, connect_timeout=5.0):
    """ Open a database, if the database is not yet set up, call create
    to do so. It may raise Sqlite3DSError if failed to open sqlite3
    database file or find bad database schema version in the database.

    Arguments:
        dbfile - the filename for the sqlite3 database.
        connect_timeout - timeout for opening the database or acquiring locks
                          defaults to sqlite3 module's default of 5.0 seconds

    Return sqlite3 connection, sqlite3 cursor.
    """
    try:
        conn = sqlite3.connect(dbfile, timeout=connect_timeout)
        cur = conn.cursor()
    except Exception as e:
        fail = "Failed to open " + dbfile + ": " + e.args[0]
        raise Sqlite3DSError(fail)

    # Does the database exist yet?  If not, create it.
    try:
        cur.execute("SELECT version FROM schema_version")
        row = cur.fetchone()
    except sqlite3.OperationalError:
        # temporarily disable automatic transactions so
        # we can do our own
        iso_lvl = conn.isolation_level
        conn.isolation_level = None
        row = create(cur)
        conn.isolation_level = iso_lvl

    if row == None or row[0] != SCHEMA_MAJOR_VERSION:
        bad_version = "(unknown)" if row is None else str(row[0])
        raise Sqlite3DSError("Bad database schema version: " + bad_version)

    return conn, cur


def get_zone_datas(zonename, dbfile):
    """ A generator function producing an iterable set of
    the records in the zone with the given zone name.

    Arguments:
        zonename - the zone's origin name.
        dbfile - the filename for the sqlite3 database.
    """
    conn, cur = open(dbfile)
    zone_id = get_zoneid(zonename, cur)

    cur.execute("SELECT * FROM records WHERE zone_id = ?", [zone_id])
    record = cur.fetchone()
    while record:
        yield record
        record = cur.fetchone()

    cur.close()
    conn.close()


def get_zone_soa(zonename, dbfile):
    """Return the soa record of the zone with the given zone name.
    If the zone doesn't exist, return None.

    Arguments:
        zonename - the zone's origin name.
        dbfile - the filename for the sqlite3 database.
    """
    conn, cur = open(dbfile)
    id = get_zoneid(zonename, cur)
    cur.execute("SELECT * FROM records WHERE zone_id = ? and rdtype = ?", [id, 'SOA'])
    datas = cur.fetchone()
    cur.close()
    conn.close()

    return datas


def get_zone_rrset(zonename, rr_name, rdtype, dbfile):
    """Return the rrset of the zone with the given zone name, rrset
    name and given RR type. If the zone doesn't exist or RR type
    doesn't exist, return an empty list.

    Arguments:
        zonename - the zone's origin name.
        rr_name - rr name.
        rdtype - RR type.
        dbfile - the filename for the sqlite3 database.
    """
    conn, cur = open(dbfile)
    id = get_zoneid(zonename, cur)
    cur.execute("SELECT * FROM records WHERE name = ? and zone_id = ? and rdtype = ?",
                [rr_name, id, rdtype])
    datas = cur.fetchall()
    cur.close()
    conn.close()
    return datas


def get_zones_info(dbfile):
    """ Return all the zones' information in the database.

    Arguments:
        dbfile - the filename for the sqlite3 database.
    """
    conn, cur = open(dbfile)
    cur.execute("SELECT name, rdclass FROM zones")
    info = cur.fetchone()
    while info:
        yield info
        info = cur.fetchone()

    cur.close()
    conn.close()


def get_zoneid(zonename, cur):
    """ Get the zone_id for a given zone name.

    Arguments:
        zonename - the zone's origin name.
        cur - sqlite3 cursor.

    Return zone id for the given zone name, or an empty string if the
    zone is not found.
    """
    cur.execute("SELECT id FROM zones WHERE name = ?", [zonename])
    row = cur.fetchone()
    if row:
        return row[0]
    else:
        return ''


def zone_exist(zonename, dbfile):
    """ Search for the zone with the given zone name in databse. This
    method may throw a Sqlite3DSError exception because its underlying
    method open() can throw that exception.

    Arguments:
        zonename - the zone's origin name.
        dbfile - the filename for the sqlite3 database.

    Return True if the zone is found, otherwise False.
    """
    conn, cur = open(dbfile)
    zoneid = get_zoneid(zonename, cur)
    cur.close()
    conn.close()
    if zoneid:
        return True
    return False


def reverse_name(name):
    """Reverse the labels of a domain name; for example,
    given 'www.example.org.', return 'org.example.www.'  This is needed
    for DNSSEC sort order.

    Arguments:
        name - the DNS name will be reversed.
    """
    new = name.split('.')
    new.reverse()
    if new[0] == '':
        new.pop(0)
    return '.'.join(new)+'.'


def load(dbfile, zone, reader):
    """  Load a zone into the SQL database.

    Arguments:
        dbfile - the sqlite3 database filename
        zone - the zone origin
        reader - a generator function producing an iterable set of
        name/ttl/class/rrtype/rdata-text tuples.
    """
    # if the zone name doesn't contain the trailing dot, automatically add it.
    if zone[-1] != '.':
        zone += '.'

    conn, cur = open(dbfile)
    try:
        old_zone_id = get_zoneid(zone, cur)

        temp = str(random.randrange(100000))
        cur.execute("INSERT INTO zones (name, rdclass) VALUES (?, 'IN')", [temp])
        new_zone_id = cur.lastrowid

        for name, ttl, rdclass, rdtype, rdata in reader():
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
                               (zone_id, name, rname, ttl,
                                rdtype, sigtype, rdata)
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
    except Exception as e:
        fail = "Error while loading " + zone + ": " + e.args[0]
        raise Sqlite3DSError(fail)
    finally:
        cur.close()
        conn.close()
