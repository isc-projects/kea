// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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
// in the test database.  It is used by the MySQL unit test prior to each
// test.
//
// Each SQL statement is a single string.  The statements are not terminated
// by semicolons, and the strings must end with a comma.  The final line
// statement must be NULL (not in quotes)

// NOTE: This file mirrors the schema in src/lib/dhcpsrv/dhcpdb_create.mysql.
//       If this file is altered, please ensure that any change is compatible
//       with the schema in dhcpdb_create.mysql.

// Deletion of existing tables.

const char* destroy_statement[] = {
    "DROP TABLE lease4",
    "DROP TABLE lease6",
    "DROP TABLE lease6_types",
    "DROP TABLE lease_hwaddr_source",
    "DROP TABLE schema_version",

    // We need to drop ipv6_reservations before hosts, as it has constrains
    // that depend on hosts. Therefore hosts table cannot be deleted while
    // ipv6_reservations exists.
    "DROP TABLE ipv6_reservations",
    "DROP TABLE hosts",
    "DROP TABLE dhcp4_options",
    "DROP TABLE dhcp6_options",

    "DROP TRIGGER host_BDEL",
    NULL
};

// Creation of the new tables.

const char* create_statement[] = {

    // Schema initialization to 1.0 starts here.
    "START TRANSACTION",
    "CREATE TABLE lease4 ("
        "address INT UNSIGNED PRIMARY KEY NOT NULL,"
        "hwaddr VARBINARY(20),"
        "client_id VARBINARY(128),"
        "valid_lifetime INT UNSIGNED,"
        "expire TIMESTAMP,"
        "subnet_id INT UNSIGNED,"
        "fqdn_fwd BOOL,"
        "fqdn_rev BOOL,"
        "hostname VARCHAR(255)"
        ") ENGINE = INNODB",

    "CREATE INDEX lease4_by_hwaddr_subnet_id ON lease4 (hwaddr, subnet_id)",

    "CREATE INDEX lease4_by_client_id_subnet_id ON lease4 (client_id, subnet_id)",

    "CREATE TABLE lease6 ("
        "address VARCHAR(39) PRIMARY KEY NOT NULL,"
        "duid VARBINARY(128),"
        "valid_lifetime INT UNSIGNED,"
        "expire TIMESTAMP,"
        "subnet_id INT UNSIGNED,"
        "pref_lifetime INT UNSIGNED,"
        "lease_type TINYINT,"
        "iaid INT UNSIGNED,"
        "prefix_len TINYINT UNSIGNED,"
        "fqdn_fwd BOOL,"
        "fqdn_rev BOOL,"
        "hostname VARCHAR(255)"
        ") ENGINE = INNODB",

    "CREATE INDEX lease6_by_iaid_subnet_id_duid ON lease6 (iaid, subnet_id, duid)",

    "CREATE TABLE lease6_types ("
        "lease_type TINYINT PRIMARY KEY NOT NULL,"
        "name VARCHAR(5)"
        ")",

    "INSERT INTO lease6_types VALUES (0, \"IA_NA\")",
    "INSERT INTO lease6_types VALUES (1, \"IA_TA\")",
    "INSERT INTO lease6_types VALUES (2, \"IA_PD\")",

    "CREATE TABLE schema_version ("
        "version INT PRIMARY KEY NOT NULL,"
        "minor INT"
        ")",

    "INSERT INTO schema_version VALUES (1, 0)",
    "COMMIT",

    // Schema initialization to 1.0 ends here.

    // Schema upgrade to 2.0 starts here.
    "ALTER TABLE lease6 "
        "ADD COLUMN hwaddr varbinary(20),"
        "ADD COLUMN hwtype smallint unsigned,"
        "ADD COLUMN hwaddr_source int unsigned;",

    // Production schema has lease_hwaddr_source table. It is not used by
    // kea code and is simply useful for formulating more human readable
    // queries. Hence no need to create it in tests. The actual SQL
    // code remains here commented out to keep a trace that the omission
    // is intentional.

    /* "CREATE TABLE lease_hwaddr_source ("
    "hwaddr_source INT PRIMARY KEY NOT NULL,"
    "name VARCHAR(40) )",

    "INSERT INTO lease_hwaddr_source VALUES (1, \"HWADDR_SOURCE_RAW\");",
    "INSERT INTO lease_hwaddr_source VALUES (2, \"HWADDR_SOURCE_IPV6_LINK_LOCAL\");",
    "INSERT INTO lease_hwaddr_source VALUES (4, \"HWADDR_SOURCE_DUID\");",
    "INSERT INTO lease_hwaddr_source VALUES (8, \"HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION\");",
    "INSERT INTO lease_hwaddr_source VALUES (16, \"HWADDR_SOURCE_REMOTE_ID\");",
    "INSERT INTO lease_hwaddr_source VALUES (32, \"HWADDR_SOURCE_SUBSCRIBER_ID\");",
    "INSERT INTO lease_hwaddr_source VALUES (64, \"HWADDR_SOURCE_DOCSIS\");", */

    "UPDATE schema_version SET version=\"2\", minor=\"0\";",
    // Schema upgrade to 2.0 ends here.

    // Schema upgrade to 3.0 starts here.

    "CREATE TABLE IF NOT EXISTS hosts ("
        "host_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
        "dhcp_identifier VARBINARY(128) NOT NULL,"
        "dhcp_identifier_type TINYINT NOT NULL,"
        "dhcp4_subnet_id INT UNSIGNED NULL,"
        "dhcp6_subnet_id INT UNSIGNED NULL,"
        "ipv4_address INT UNSIGNED NULL,"
        "hostname VARCHAR(255) NULL,"
        "dhcp4_client_classes VARCHAR(255) NULL,"
        "dhcp6_client_classes VARCHAR(255) NULL,"
        "PRIMARY KEY (host_id),"
        "INDEX key_dhcp4_identifier_subnet_id (dhcp_identifier ASC , dhcp_identifier_type ASC),"
        "INDEX key_dhcp6_identifier_subnet_id (dhcp_identifier ASC , dhcp_identifier_type ASC , dhcp6_subnet_id ASC)"
    ")  ENGINE=INNODB",

    "CREATE TABLE IF NOT EXISTS ipv6_reservations ("
        "reservation_id INT NOT NULL AUTO_INCREMENT,"
        "address VARCHAR(39) NOT NULL,"
        "prefix_len TINYINT(3) UNSIGNED NOT NULL DEFAULT 128,"
        "type TINYINT(4) UNSIGNED NOT NULL DEFAULT 0,"
        "dhcp6_iaid INT UNSIGNED NULL,"
        "host_id INT UNSIGNED NOT NULL,"
        "PRIMARY KEY (reservation_id),"
        "INDEX fk_ipv6_reservations_host_idx (host_id ASC),"
        "CONSTRAINT fk_ipv6_reservations_Host FOREIGN KEY (host_id)"
            "REFERENCES hosts (host_id)"
            "ON DELETE NO ACTION ON UPDATE NO ACTION"
    ")  ENGINE=INNODB",

    "CREATE TABLE IF NOT EXISTS dhcp4_options ("
        "option_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
        "code TINYINT UNSIGNED NOT NULL,"
        "value BLOB NULL,"
        "formatted_value TEXT NULL,"
        "space VARCHAR(128) NULL,"
        "persistent TINYINT(1) NOT NULL DEFAULT 0,"
        "dhcp_client_class VARCHAR(128) NULL,"
        "dhcp4_subnet_id INT NULL,"
        "host_id INT UNSIGNED NULL,"
        "PRIMARY KEY (option_id),"
        "UNIQUE INDEX option_id_UNIQUE (option_id ASC),"
        "INDEX fk_options_host1_idx (host_id ASC),"
        "CONSTRAINT fk_options_host1 FOREIGN KEY (host_id)"
            "REFERENCES hosts (host_id)"
            "ON DELETE NO ACTION ON UPDATE NO ACTION"
    ")  ENGINE=INNODB",

    "CREATE TABLE IF NOT EXISTS dhcp6_options ("
        "option_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
        "code INT UNSIGNED NOT NULL,"
        "value BLOB NULL,"
        "formatted_value TEXT NULL,"
        "space VARCHAR(128) NULL,"
        "persistent TINYINT(1) NOT NULL DEFAULT 0,"
        "dhcp_client_class VARCHAR(128) NULL,"
        "dhcp6_subnet_id INT NULL,"
        "host_id INT UNSIGNED NULL,"
        "PRIMARY KEY (option_id),"
        "UNIQUE INDEX option_id_UNIQUE (option_id ASC),"
        "INDEX fk_options_host1_idx (host_id ASC),"
        "CONSTRAINT fk_options_host10 FOREIGN KEY (host_id)"
            "REFERENCES hosts (host_id)"
            "ON DELETE NO ACTION ON UPDATE NO ACTION"
    ")  ENGINE=INNODB",


    //"DELIMITER $$ ",
    "CREATE TRIGGER host_BDEL BEFORE DELETE ON hosts FOR EACH ROW "
    "BEGIN "
    "DELETE FROM ipv6_reservations WHERE ipv6_reservations.host_id = OLD.host_id; "
    "END ",
    //"$$ ",
    //"DELIMITER ;",

    "UPDATE schema_version SET version = '3', minor = '0';",

    // This line concludes database upgrade to version 3.0.

    // Schema upgrade to 4.0 starts here.
    "ALTER TABLE lease4 "
        "ADD COLUMN state INT UNSIGNED DEFAULT 0",

    "ALTER TABLE lease6 "
        "ADD COLUMN state INT UNSIGNED DEFAULT 0",

    "CREATE INDEX lease4_by_state_expire ON lease4 (state ASC, expire ASC)",
    "CREATE INDEX lease6_by_state_expire ON lease6 (state ASC, expire ASC)",

    // Production schema includes the lease_state table and
    // lease_hwaddr_source tables which map to the values in lease4
    // and lease6 tables. This is not used in the unit tests
    // so it is commented out.

    /*"CREATE TABLE IF NOT EXISTS lease_state (",
        "state INT UNSIGNED PRIMARY KEY NOT NULL,"
        "name VARCHAR(64) NOT NULL);",

    "INSERT INTO lease_state VALUES (0, \"default\");",
    "INSERT INTO lease_state VALUES (1, \"declined\");",
    "INSERT INTO lease_state VALUES (2, \"expired-reclaimed\");",

    "ALTER TABLE lease4 "
        "ADD CONSTRAINT fk_lease4_state FOREIGN KEY (state) "
        "REFERENCES lease_state (state)",

    "ALTER TABLE lease6 "
        "ADD CONSTRAINT fk_lease6_state FOREIGN KEY (state) "
        "REFERENCES lease_state (state)",

    "ALTER TABLE lease6 "
        "ADD CONSTRAINT fk_lease6_type FOREIGN KEY (lease_type) "
        "REFERENCES lease6_types (lease_type)",

    "UPDATE lease_hwaddr_source "
        "SET name = 'HWADDR_SOURCE_DOCSIS_CMTS' "
        "WHERE hwaddr_source = 64",

    "INSERT INTO lease_hwaddr_source VALUES (128, 'HWADDR_SOURCE_DOCSIS_MODEM')",

    "ALTER TABLE lease_hwaddr_source "
        "MODIFY COLUMN hwaddr_source INT UNSIGNED NOT NULL DEFAULT 0",

    "ALTER TABLE lease6 "
        "ADD CONSTRAINT fk_lease6_hwaddr_source FOREIGN KEY (hwaddr_source) "
        "REFERENCES lease_hwaddr_source (hwaddr_source)",*/

    // Schema upgrade to 4.0 ends here.

    NULL
};

};  // Anonymous namespace

#endif // SCHEMA_COPY_H
