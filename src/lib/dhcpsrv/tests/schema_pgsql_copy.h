// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef SCHEMA_COPY_H
#define SCHEMA_COPY_H

namespace {

// What follows is a set of statements that creates a copy of the schema
// in the test database.  It is used by the PostgreSQL unit test prior to each
// test.
//
// Each SQL statement is a single string.  The statements are not terminated
// by semicolons, and the strings must end with a comma.  The final line
// statement must be NULL (not in quotes)

// NOTE: This file mirrors the schema in src/lib/dhcpsrv/dhcpdb_create.pgsql.
//       If this file is altered, please ensure that any change is compatible
//       with the schema in dhcpdb_create.pgsql.

// Deletion of existing tables.

const char* destroy_statement[] = {
    "DROP TABLE lease4",
    "DROP TABLE lease6",
    "DROP TABLE lease6_types",
    "DROP TABLE schema_version",
    NULL
};

// Creation of the new tables.

const char* create_statement[] = {
    "START TRANSACTION",
    "CREATE TABLE lease4 ("
    "address BIGINT PRIMARY KEY NOT NULL,"
    "hwaddr BYTEA,"
    "client_id BYTEA,"
    "valid_lifetime BIGINT,"
    "expire TIMESTAMP WITH TIME ZONE,"
    "subnet_id BIGINT,"
    "fqdn_fwd BOOLEAN,"
    "fqdn_rev BOOLEAN,"
    "hostname VARCHAR(255)"
    ")",

    "CREATE TABLE lease6 ("
    "address VARCHAR(39) PRIMARY KEY NOT NULL,"
    "duid BYTEA,"
    "valid_lifetime BIGINT,"
    "expire TIMESTAMP WITH TIME ZONE,"
    "subnet_id BIGINT,"
    "pref_lifetime BIGINT,"
    "lease_type SMALLINT,"
    "iaid BIGINT,"
    "prefix_len SMALLINT,"
    "fqdn_fwd BOOLEAN,"
    "fqdn_rev BOOLEAN,"
    "hostname VARCHAR(255)"
    ")",

    "CREATE TABLE lease6_types ("
    "lease_type SMALLINT PRIMARY KEY NOT NULL,"
    "name VARCHAR(5)"
    ")",

    "INSERT INTO lease6_types VALUES (0, 'IA_NA')",
    "INSERT INTO lease6_types VALUES (1, 'IA_TA')",
    "INSERT INTO lease6_types VALUES (2, 'IA_PD')",

    "CREATE TABLE schema_version ("
        "version INT PRIMARY KEY NOT NULL,"
        "minor INT"
        ")",

    "INSERT INTO schema_version VALUES (1, 0)",
    "COMMIT",

    // This line concludes creation of database version 1.0.

    // Schema upgrade to 2.0 starts here.

    "ALTER TABLE lease4 "
        "ADD COLUMN state INT8 DEFAULT 0",

    "ALTER TABLE lease6 "
        "ADD COLUMN state INT8 DEFAULT 0",

    "CREATE INDEX lease4_by_state_expire ON lease4 (state ASC, expire ASC)",
    "CREATE INDEX lease6_by_state_expire ON lease6 (state ASC, expire ASC)",

    // Production schema includes the lease_state table which maps
    // the lease states to their names. This is not used in the unit tests
    // so it is commented out.

    /*"CREATE TABLE lease_state (",
        "state INT8 PRIMARY KEY NOT NULL,"
        "name VARCHAR(64) NOT NULL);",

    "ALTER TABLE lease4 "
        "ADD CONSTRAINT fk_lease4_state FOREIGN KEY (state) "
        "REFERENCES lease_state (state)",

    "ALTER TABLE lease6 "
        "ADD CONSTRAINT fk_lease6_state FOREIGN KEY (state) "
        "REFERENCES lease_state (state)",

    "ALTER TABLE lease6 "
        "ADD CONSTRAINT fk_lease6_type FOREIGN KEY (lease_type) "
        "REFERENCES lease6_types (lease_type)",

    "INSERT INTO lease_state VALUES (0, \"default\");",
    "INSERT INTO lease_state VALUES (1, \"declined\");",
    "INSERT INTO lease_state VALUES (2, \"expired-reclaimed\");",*/

    "UPDATE schema_version SET version = '2', minor = '0';",
    "COMMIT",

    // Schema upgrade to 2.0 ends here.

    NULL
};

};  // Anonymous namespace

#endif // SCHEMA_COPY_H
