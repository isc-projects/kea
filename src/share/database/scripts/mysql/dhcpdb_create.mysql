# Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# This is the Kea schema specification for MySQL.
#
# The schema is reasonably portable (with the exception of the engine
# specification, which is MySQL-specific).  Minor changes might be needed for
# other databases.

# To create the schema, either type the command:
#
# mysql -u <user> -p <password> <database> < dhcpdb_create.mysql
#
# ... at the command prompt, or log in to the MySQL database and at the 'mysql>'
# prompt, issue the command:
#
# source dhcpdb_create.mysql
#
# This script is also called from kea-admin, see kea-admin lease-init mysql
#
# Over time, Kea database schema will evolve. Each version is marked with
# major.minor version. This file is organized sequentially, i.e. database
# is initialized to 1.0, then upgraded to 2.0 etc. This may be somewhat
# sub-optimal, but it ensues consistency with upgrade scripts. (It is much
# easier to maintain init and upgrade scripts if they look the same).
# Since initialization is done only once, it's performance is not an issue.

# This line starts database initialization to 1.0.

# Holds the IPv4 leases.
CREATE TABLE lease4 (
    address INT UNSIGNED PRIMARY KEY NOT NULL,  # IPv4 address
    hwaddr VARBINARY(20),                       # Hardware address
    client_id VARBINARY(128),                   # Client ID
    valid_lifetime INT UNSIGNED,                # Length of the lease (seconds)
    expire TIMESTAMP,                           # Expiration time of the lease
    subnet_id INT UNSIGNED,                     # Subnet identification
    fqdn_fwd BOOL,                              # Has forward DNS update been performed by a server
    fqdn_rev BOOL,                              # Has reverse DNS update been performed by a server
    hostname VARCHAR(255)                       # The FQDN of the client
    ) ENGINE = INNODB;


# Create search indexes for lease4 table
# index by hwaddr and subnet_id
CREATE INDEX lease4_by_hwaddr_subnet_id ON lease4 (hwaddr, subnet_id);

# index by client_id and subnet_id
CREATE INDEX lease4_by_client_id_subnet_id ON lease4 (client_id, subnet_id);

# Holds the IPv6 leases.
# N.B. The use of a VARCHAR for the address is temporary for development:
# it will eventually be replaced by BINARY(16).
CREATE TABLE lease6 (
    address VARCHAR(39) PRIMARY KEY NOT NULL,   # IPv6 address
    duid VARBINARY(128),                        # DUID
    valid_lifetime INT UNSIGNED,                # Length of the lease (seconds)
    expire TIMESTAMP,                           # Expiration time of the lease
    subnet_id INT UNSIGNED,                     # Subnet identification
    pref_lifetime INT UNSIGNED,                 # Preferred lifetime
    lease_type TINYINT,                         # Lease type (see lease6_types
                                                #    table for possible values)
    iaid INT UNSIGNED,                          # See Section 10 of RFC 3315
    prefix_len TINYINT UNSIGNED,                # For IA_PD only
    fqdn_fwd BOOL,                              # Has forward DNS update been performed by a server
    fqdn_rev BOOL,                              # Has reverse DNS update been performed by a server
    hostname VARCHAR(255)                       # The FQDN of the client

    ) ENGINE = INNODB;

# Create search indexes for lease4 table
# index by iaid, subnet_id, and duid
CREATE INDEX lease6_by_iaid_subnet_id_duid ON lease6 (iaid, subnet_id, duid);

# ... and a definition of lease6 types.  This table is a convenience for
# users of the database - if they want to view the lease table and use the
# type names, they can join this table with the lease6 table.
# Make sure those values match Lease6::LeaseType enum (see src/bin/dhcpsrv/
# lease_mgr.h)
CREATE TABLE lease6_types (
    lease_type TINYINT PRIMARY KEY NOT NULL,    # Lease type code.
    name VARCHAR(5)                             # Name of the lease type
    ) ENGINE = INNODB;

START TRANSACTION;
INSERT INTO lease6_types VALUES (0, 'IA_NA');   # Non-temporary v6 addresses
INSERT INTO lease6_types VALUES (1, 'IA_TA');   # Temporary v6 addresses
INSERT INTO lease6_types VALUES (2, 'IA_PD');   # Prefix delegations
COMMIT;

# Finally, the version of the schema.  We start at 1.0 during development.
# This table is only modified during schema upgrades.  For historical reasons
# (related to the names of the columns in the BIND 10 DNS database file), the
# first column is called 'version' and not 'major'.
CREATE TABLE schema_version (
    version INT PRIMARY KEY NOT NULL,       # Major version number
    minor INT                               # Minor version number
    ) ENGINE = INNODB;
START TRANSACTION;
INSERT INTO schema_version VALUES (1, 0);
COMMIT;

# This line concludes database initialization to version 1.0.

# This line starts database upgrade to version 2.0.
ALTER TABLE lease6
    ADD COLUMN hwaddr varbinary(20), # Hardware/MAC address, typically only 6
                                     # bytes is used, but some hardware (e.g.
                                     # Infiniband) use up to 20.
    ADD COLUMN hwtype smallint unsigned, # hardware type (16 bits)
    ADD COLUMN hwaddr_source int unsigned; # Hardware source. See description
                                     # of lease_hwaddr_source below.

# Kea keeps track of the hardware/MAC address source, i.e. how the address
# was obtained. Depending on the technique and your network topology, it may
# be more or less trustworthy. This table is a convenience for
# users of the database - if they want to view the lease table and use the
# type names, they can join this table with the lease6 table. For details,
# see constants defined in src/lib/dhcp/dhcp/pkt.h for detailed explanation.
CREATE TABLE lease_hwaddr_source (
    hwaddr_source INT PRIMARY KEY NOT NULL,
    name VARCHAR(40)
) ENGINE = INNODB;

# Hardware address obtained from raw sockets
INSERT INTO lease_hwaddr_source VALUES (1, 'HWADDR_SOURCE_RAW');

# Hardware address converted from IPv6 link-local address with EUI-64
INSERT INTO lease_hwaddr_source VALUES (2, 'HWADDR_SOURCE_IPV6_LINK_LOCAL');

# Hardware address extracted from client-id (duid)
INSERT INTO lease_hwaddr_source VALUES (4, 'HWADDR_SOURCE_DUID');

# Hardware address extracted from client address relay option (RFC6939)
INSERT INTO lease_hwaddr_source VALUES (8, 'HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION');

# Hardware address extracted from remote-id option (RFC4649)
INSERT INTO lease_hwaddr_source VALUES (16, 'HWADDR_SOURCE_REMOTE_ID');

# Hardware address extracted from subscriber-id option (RFC4580)
INSERT INTO lease_hwaddr_source VALUES (32, 'HWADDR_SOURCE_SUBSCRIBER_ID');

# Hardware address extracted from docsis options
INSERT INTO lease_hwaddr_source VALUES (64, 'HWADDR_SOURCE_DOCSIS');

UPDATE schema_version SET version='2', minor='0';

# This line concludes database upgrade to version 2.0.

# This line starts database upgrade to version 3.0.
# Upgrade extending MySQL schema with the ability to store hosts.

CREATE TABLE IF NOT EXISTS hosts (
    host_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    dhcp_identifier VARBINARY(128) NOT NULL,
    dhcp_identifier_type TINYINT NOT NULL,
    dhcp4_subnet_id INT UNSIGNED NULL,
    dhcp6_subnet_id INT UNSIGNED NULL,
    ipv4_address INT UNSIGNED NULL,
    hostname VARCHAR(255) NULL,
    dhcp4_client_classes VARCHAR(255) NULL,
    dhcp6_client_classes VARCHAR(255) NULL,
    PRIMARY KEY (host_id),
    INDEX key_dhcp4_identifier_subnet_id (dhcp_identifier ASC , dhcp_identifier_type ASC),
    INDEX key_dhcp6_identifier_subnet_id (dhcp_identifier ASC , dhcp_identifier_type ASC , dhcp6_subnet_id ASC)
)  ENGINE=INNODB;
-- -----------------------------------------------------
-- Table `ipv6_reservations`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS ipv6_reservations (
    reservation_id INT NOT NULL AUTO_INCREMENT,
    address VARCHAR(39) NOT NULL,
    prefix_len TINYINT(3) UNSIGNED NOT NULL DEFAULT 128,
    type TINYINT(4) UNSIGNED NOT NULL DEFAULT 0,
    dhcp6_iaid INT UNSIGNED NULL,
    host_id INT UNSIGNED NOT NULL,
    PRIMARY KEY (reservation_id),
    INDEX fk_ipv6_reservations_host_idx (host_id ASC),
    CONSTRAINT fk_ipv6_reservations_Host FOREIGN KEY (host_id)
        REFERENCES hosts (host_id)
        ON DELETE NO ACTION ON UPDATE NO ACTION
)  ENGINE=INNODB;
-- -----------------------------------------------------
-- Table `dhcp4_options`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp4_options (
    option_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    code TINYINT UNSIGNED NOT NULL,
    value BLOB NULL,
    formatted_value TEXT NULL,
    space VARCHAR(128) NULL,
    persistent TINYINT(1) NOT NULL DEFAULT 0,
    dhcp_client_class VARCHAR(128) NULL,
    dhcp4_subnet_id INT NULL,
    host_id INT UNSIGNED NULL,
    PRIMARY KEY (option_id),
    UNIQUE INDEX option_id_UNIQUE (option_id ASC),
    INDEX fk_options_host1_idx (host_id ASC),
    CONSTRAINT fk_options_host1 FOREIGN KEY (host_id)
        REFERENCES hosts (host_id)
        ON DELETE NO ACTION ON UPDATE NO ACTION
)  ENGINE=INNODB;
-- -----------------------------------------------------
-- Table `dhcp6_options`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp6_options (
    option_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    code INT UNSIGNED NOT NULL,
    value BLOB NULL,
    formatted_value TEXT NULL,
    space VARCHAR(128) NULL,
    persistent TINYINT(1) NOT NULL DEFAULT 0,
    dhcp_client_class VARCHAR(128) NULL,
    dhcp6_subnet_id INT NULL,
    host_id INT UNSIGNED NULL,
    PRIMARY KEY (option_id),
    UNIQUE INDEX option_id_UNIQUE (option_id ASC),
    INDEX fk_options_host1_idx (host_id ASC),
    CONSTRAINT fk_options_host10 FOREIGN KEY (host_id)
        REFERENCES hosts (host_id)
        ON DELETE NO ACTION ON UPDATE NO ACTION
)  ENGINE=INNODB;

DELIMITER $$
CREATE TRIGGER host_BDEL BEFORE DELETE ON hosts FOR EACH ROW
-- Edit trigger body code below this line. Do not edit lines above this one
BEGIN
DELETE FROM ipv6_reservations WHERE ipv6_reservations.host_id = OLD.host_id;
END
$$
DELIMITER ;

UPDATE schema_version
SET version = '3', minor = '0';
# This line concludes database upgrade to version 3.0.

# This line starts database upgrade to version 4.0.
# Upgrade extending MySQL schema with the state columns for lease tables.

# Add state column to the lease4 table.
ALTER TABLE lease4
    ADD COLUMN state INT UNSIGNED DEFAULT 0;

# Add state column to the lease6 table.
ALTER TABLE lease6
    ADD COLUMN state INT UNSIGNED DEFAULT 0;

# Create indexes for querying leases in a given state and segregated
# by the expiration time. One of the applications is to retrieve all
# expired leases. However, these indexes can be also used to retrieve
# leases in a given state regardless of the expiration time.
CREATE INDEX lease4_by_state_expire ON lease4 (state ASC, expire ASC);
CREATE INDEX lease6_by_state_expire ON lease6 (state ASC, expire ASC);

# Create table holding mapping of the lease states to their names.
# This is not used in queries from the DHCP server but rather in
# direct queries from the lease database management tools.
CREATE TABLE IF NOT EXISTS lease_state (
  state INT UNSIGNED PRIMARY KEY NOT NULL,
  name VARCHAR(64) NOT NULL
) ENGINE=INNODB;

# Insert currently defined state names.
INSERT INTO lease_state VALUES (0, 'default');
INSERT INTO lease_state VALUES (1, 'declined');
INSERT INTO lease_state VALUES (2, 'expired-reclaimed');

# Add a constraint that any state value added to the lease4 must
# map to a value in the lease_state table.
ALTER TABLE lease4
    ADD CONSTRAINT fk_lease4_state FOREIGN KEY (state)
    REFERENCES lease_state (state);

# Add a constraint that any state value added to the lease6 must
# map to a value in the lease_state table.
ALTER TABLE lease6
    ADD CONSTRAINT fk_lease6_state FOREIGN KEY (state)
    REFERENCES lease_state (state);

# Add a constraint that lease type in the lease6 table must map
# to a lease type defined in the lease6_types table.
ALTER TABLE lease6
    ADD CONSTRAINT fk_lease6_type FOREIGN KEY (lease_type)
    REFERENCES lease6_types (lease_type);

# Modify the name of one of the HW address sources, and add a new one.
UPDATE lease_hwaddr_source
    SET name = 'HWADDR_SOURCE_DOCSIS_CMTS'
    WHERE hwaddr_source = 64;

INSERT INTO lease_hwaddr_source VALUES (128, 'HWADDR_SOURCE_DOCSIS_MODEM');

# Add UNSIGNED to match with the lease6.
ALTER TABLE lease_hwaddr_source
    MODIFY COLUMN hwaddr_source INT UNSIGNED NOT NULL;

# Add a constraint that non-null hwaddr_source in the lease6 table
# must map to an entry in the lease_hwaddr_source.
ALTER TABLE lease6
    ADD CONSTRAINT fk_lease6_hwaddr_source FOREIGN KEY (hwaddr_source)
    REFERENCES lease_hwaddr_source (hwaddr_source);

# FUNCTION that returns a result set containing the column names for lease4 dumps
DROP PROCEDURE IF EXISTS lease4DumpHeader;
DELIMITER $$
CREATE PROCEDURE lease4DumpHeader()
BEGIN
SELECT 'address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state';
END  $$
DELIMITER ;

# FUNCTION that returns a result set containing the data for lease4 dumps
DROP PROCEDURE IF EXISTS lease4DumpData;
DELIMITER $$
CREATE PROCEDURE lease4DumpData()
BEGIN
SELECT
    INET_NTOA(l.address),
    IFNULL(HEX(l.hwaddr), ''),
    IFNULL(HEX(l.client_id), ''),
    l.valid_lifetime,
    l.expire,
    l.subnet_id,
    l.fqdn_fwd,
    l.fqdn_rev,
    l.hostname,
    s.name
FROM
    lease4 l
    LEFT OUTER JOIN lease_state s on (l.state = s.state)
ORDER BY l.address;
END $$
DELIMITER ;

# FUNCTION that returns a result set containing the column names for lease6 dumps
DROP PROCEDURE IF EXISTS lease6DumpHeader;
DELIMITER $$
CREATE PROCEDURE lease6DumpHeader()
BEGIN
SELECT 'address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,hwtype,hwaddr_source,state';
END  $$
DELIMITER ;

# FUNCTION that returns a result set containing the data for lease6 dumps
DROP PROCEDURE IF EXISTS lease6DumpData;
DELIMITER $$
CREATE PROCEDURE lease6DumpData()
BEGIN
SELECT
    l.address,
    IFNULL(HEX(l.duid), ''),
    l.valid_lifetime,
    l.expire,
    l.subnet_id,
    l.pref_lifetime,
    IFNULL(t.name, ''),
    l.iaid,
    l.prefix_len,
    l.fqdn_fwd,
    l.fqdn_rev,
    l.hostname,
    IFNULL(HEX(l.hwaddr), ''),
    IFNULL(l.hwtype, ''),
    IFNULL(h.name, ''),
    IFNULL(s.name, '')
FROM lease6 l
    left outer join lease6_types t on (l.lease_type = t.lease_type)
    left outer join lease_state s on (l.state = s.state)
    left outer join lease_hwaddr_source h on (l.hwaddr_source = h.hwaddr_source)
ORDER BY l.address;
END $$
DELIMITER ;

# Update the schema version number
UPDATE schema_version
SET version = '4', minor = '0';

# This line concludes database upgrade to version 4.0.

# In the event hardware address cannot be determined, we need to satisfy
# foreign key constraint between lease6 and lease_hardware_source
INSERT INTO lease_hwaddr_source VALUES (0, 'HWADDR_SOURCE_UNKNOWN');

# Update the schema version number
UPDATE schema_version
SET version = '4', minor = '1';

# This line concludes database upgrade to version 4.1.

# Update index used for searching DHCPv4 reservations by identifier and subnet id.
# This index is now unique (to prevent duplicates) and includes DHCPv4 subnet
# identifier.
DROP INDEX key_dhcp4_identifier_subnet_id ON hosts;
CREATE UNIQUE INDEX key_dhcp4_identifier_subnet_id ON hosts (dhcp_identifier ASC , dhcp_identifier_type ASC , dhcp4_subnet_id ASC);

# Update index used for searching DHCPv6 reservations by identifier and subnet id.
# This index is now unique to prevent duplicates.
DROP INDEX key_dhcp6_identifier_subnet_id ON hosts;
CREATE UNIQUE INDEX key_dhcp6_identifier_subnet_id ON hosts (dhcp_identifier ASC , dhcp_identifier_type ASC , dhcp6_subnet_id ASC);

# Create index to search for reservations using IP address and subnet id.
# This unique index guarantees that there is only one occurrence of the
# particular IPv4 address for a given subnet.
CREATE UNIQUE INDEX key_dhcp4_ipv4_address_subnet_id ON hosts (ipv4_address ASC , dhcp4_subnet_id ASC);

# Create index to search for reservations using address/prefix and prefix
# length.
CREATE UNIQUE INDEX key_dhcp6_address_prefix_len ON ipv6_reservations (address ASC , prefix_len ASC);

# Create a table mapping host identifiers to their names. Values in this
# table are used as a foreign key in hosts table to guarantee that only
# identifiers present in host_identifier_type table are used in hosts
# table.
CREATE TABLE IF NOT EXISTS host_identifier_type (
    type TINYINT PRIMARY KEY NOT NULL,   # Lease type code.
    name VARCHAR(32)                     # Name of the lease type
) ENGINE = INNODB;

START TRANSACTION;
INSERT INTO host_identifier_type VALUES (0, 'hw-address');
INSERT INTO host_identifier_type VALUES (1, 'duid');
INSERT INTO host_identifier_type VALUES (2, 'circuit-id');
COMMIT;

# Add a constraint that any identifier type value added to the hosts
# must map to a value in the host_identifier_type table.
ALTER TABLE hosts
    ADD CONSTRAINT fk_host_identifier_type FOREIGN KEY (dhcp_identifier_type)
    REFERENCES host_identifier_type (type);

# Store DHCPv6 option code as 16-bit unsigned integer.
ALTER TABLE dhcp6_options MODIFY code SMALLINT UNSIGNED NOT NULL;

# Subnet identifier is unsigned.
ALTER TABLE dhcp4_options MODIFY dhcp4_subnet_id INT UNSIGNED NULL;
ALTER TABLE dhcp6_options MODIFY dhcp6_subnet_id INT UNSIGNED NULL;

# Scopes associate DHCP options stored in dhcp4_options and
# dhcp6_options tables with hosts, subnets, classes or indicate
# that they are global options.
CREATE TABLE IF NOT EXISTS dhcp_option_scope (
    scope_id TINYINT UNSIGNED PRIMARY KEY NOT NULL,
    scope_name VARCHAR(32)
) ENGINE = INNODB;

START TRANSACTION;
INSERT INTO dhcp_option_scope VALUES (0, 'global');
INSERT INTO dhcp_option_scope VALUES (1, 'subnet');
INSERT INTO dhcp_option_scope VALUES (2, 'client-class');
INSERT INTO dhcp_option_scope VALUES (3, 'host');
COMMIT;

# Add scopes into table holding DHCPv4 options
ALTER TABLE dhcp4_options ADD COLUMN scope_id TINYINT UNSIGNED NOT NULL;
ALTER TABLE dhcp4_options
    ADD CONSTRAINT fk_dhcp4_option_scope FOREIGN KEY (scope_id)
    REFERENCES dhcp_option_scope (scope_id);

# Add scopes into table holding DHCPv6 options
ALTER TABLE dhcp6_options ADD COLUMN scope_id TINYINT UNSIGNED NOT NULL;
ALTER TABLE dhcp6_options
    ADD CONSTRAINT fk_dhcp6_option_scope FOREIGN KEY (scope_id)
    REFERENCES dhcp_option_scope (scope_id);

# Add UNSIGNED to reservation_id
ALTER TABLE ipv6_reservations
    MODIFY reservation_id INT UNSIGNED NOT NULL AUTO_INCREMENT;

# Add columns holding reservations for siaddr, sname and file fields
# carried within DHCPv4 message.
ALTER TABLE hosts ADD COLUMN dhcp4_next_server INT UNSIGNED NULL;
ALTER TABLE hosts ADD COLUMN dhcp4_server_hostname VARCHAR(64) NULL;
ALTER TABLE hosts ADD COLUMN dhcp4_boot_file_name VARCHAR(128) NULL;

# Update the schema version number
UPDATE schema_version
SET version = '5', minor = '0';
# This line concludes database upgrade to version 5.0.

# Add missing 'client-id' and new 'flex-id' host identifier types.
INSERT INTO host_identifier_type VALUES (3, 'client-id');
INSERT INTO host_identifier_type VALUES (4, 'flex-id');

# Recreate the trigger removing dependent host entries.
DROP TRIGGER host_BDEL;

DELIMITER $$
CREATE TRIGGER host_BDEL BEFORE DELETE ON hosts FOR EACH ROW
-- Edit trigger body code below this line. Do not edit lines above this one
BEGIN
DELETE FROM ipv6_reservations WHERE ipv6_reservations.host_id = OLD.host_id;
DELETE FROM dhcp4_options WHERE dhcp4_options.host_id = OLD.host_id;
DELETE FROM dhcp6_options WHERE dhcp6_options.host_id = OLD.host_id;
END
$$
DELIMITER ;

# Update the schema version number
UPDATE schema_version
SET version = '5', minor = '1';
# This line concludes database upgrade to version 5.1.

# Make subnet_id column types consistent with lease table columns
ALTER TABLE dhcp4_options MODIFY dhcp4_subnet_id INT UNSIGNED;
ALTER TABLE dhcp6_options MODIFY dhcp6_subnet_id INT UNSIGNED;

# Update the schema version number
UPDATE schema_version
SET version = '5', minor = '2';

# This line concludes database upgrade to version 5.2.

# Add user context into table holding hosts
ALTER TABLE hosts ADD COLUMN user_context TEXT NULL;

# Add user contexts into tables holding DHCP options
ALTER TABLE dhcp4_options ADD COLUMN user_context TEXT NULL;
ALTER TABLE dhcp6_options ADD COLUMN user_context TEXT NULL;

# Create index for searching leases by subnet identifier.
CREATE INDEX lease4_by_subnet_id ON lease4 (subnet_id);

# Create for searching leases by subnet identifier and lease type.
CREATE INDEX lease6_by_subnet_id_lease_type ON lease6 (subnet_id, lease_type);

# The index by iaid_subnet_id_duid is not the best choice because there are
# cases when we don't specify subnet identifier while searching leases. The
# index will be universal if the subnet_id is the right most column in the
# index.
DROP INDEX lease6_by_iaid_subnet_id_duid on lease6;
CREATE INDEX lease6_by_duid_iaid_subnet_id ON lease6 (duid, iaid, subnet_id);

# Create lease4_stat table
CREATE TABLE lease4_stat (
    subnet_id INT UNSIGNED NOT NULL,
    state INT UNSIGNED NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, state)
) ENGINE = INNODB;

# Create stat_lease4_insert trigger
DELIMITER $$
CREATE TRIGGER stat_lease4_insert AFTER INSERT ON lease4
    FOR EACH ROW
    BEGIN
        IF NEW.state = 0 OR NEW.state = 1 THEN
            # Update the state count if it exists
            UPDATE lease4_stat SET leases = leases + 1
            WHERE subnet_id = NEW.subnet_id AND state = NEW.state;

            # Insert the state count record if it does not exist
            IF ROW_COUNT() <= 0 THEN
                INSERT INTO lease4_stat VALUES (NEW.subnet_id, NEW.state, 1);
            END IF;
        END IF;
    END $$
DELIMITER ;

# Create stat_lease4_update trigger
DELIMITER $$
CREATE TRIGGER stat_lease4_update AFTER UPDATE ON lease4
    FOR EACH ROW
    BEGIN
        IF OLD.state != NEW.state THEN
            IF OLD.state = 0 OR OLD.state = 1 THEN
                # Decrement the old state count if record exists
                UPDATE lease4_stat SET leases = leases - 1
                WHERE subnet_id = OLD.subnet_id AND state = OLD.state;
            END IF;

            IF NEW.state = 0 OR NEW.state = 1 THEN
                # Increment the new state count if record exists
                UPDATE lease4_stat SET leases = leases + 1
                WHERE subnet_id = NEW.subnet_id AND state = NEW.state;

                # Insert new state record if it does not exist
                IF ROW_COUNT() <= 0 THEN
                    INSERT INTO lease4_stat VALUES (NEW.subnet_id, NEW.state, 1);
                END IF;
            END IF;
        END IF;
    END $$
DELIMITER ;

# Create stat_lease4_delete trigger
DELIMITER $$
CREATE TRIGGER stat_lease4_delete AFTER DELETE ON lease4
    FOR EACH ROW
    BEGIN
        IF OLD.state = 0 OR OLD.state = 1 THEN
            # Decrement the state count if record exists
            UPDATE lease4_stat SET leases = leases - 1
            WHERE subnet_id = OLD.subnet_id AND OLD.state = state;
        END IF;
    END $$
DELIMITER ;

# Create lease6_stat table
CREATE TABLE lease6_stat (
    subnet_id INT UNSIGNED NOT NULL,
    lease_type INT UNSIGNED NOT NULL,
    state INT UNSIGNED NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, lease_type, state)
) ENGINE = INNODB;

# Create stat_lease6_insert trigger
DELIMITER $$
CREATE TRIGGER stat_lease6_insert AFTER INSERT ON lease6
    FOR EACH ROW
    BEGIN
        IF NEW.state = 0 OR NEW.state = 1 THEN
            # Update the state count if it exists
            UPDATE lease6_stat SET leases = leases + 1
            WHERE
                subnet_id = NEW.subnet_id AND lease_type = NEW.lease_type
                AND state = NEW.state;

            # Insert the state count record if it does not exist
            IF ROW_COUNT() <= 0 THEN
                INSERT INTO lease6_stat
                VALUES (NEW.subnet_id, NEW.lease_type, NEW.state, 1);
            END IF;
        END IF;
    END $$
DELIMITER ;

# Create stat_lease6_update trigger
DELIMITER $$
CREATE TRIGGER stat_lease6_update AFTER UPDATE ON lease6
    FOR EACH ROW
    BEGIN
        IF OLD.state != NEW.state THEN
            IF OLD.state = 0 OR OLD.state = 1 THEN
                # Decrement the old state count if record exists
                UPDATE lease6_stat SET leases = leases - 1
                WHERE subnet_id = OLD.subnet_id AND lease_type = OLD.lease_type
                AND state = OLD.state;
            END IF;

            IF NEW.state = 0 OR NEW.state = 1 THEN
                # Increment the new state count if record exists
                UPDATE lease6_stat SET leases = leases + 1
                WHERE subnet_id = NEW.subnet_id AND lease_type = NEW.lease_type
                AND state = NEW.state;

                # Insert new state record if it does not exist
                IF ROW_COUNT() <= 0 THEN
                    INSERT INTO lease6_stat
                    VALUES (NEW.subnet_id, NEW.lease_type, NEW.state, 1);
                END IF;
            END IF;
        END IF;
    END $$
DELIMITER ;

# Create stat_lease6_delete trigger
DELIMITER $$
CREATE TRIGGER stat_lease6_delete AFTER DELETE ON lease6
    FOR EACH ROW
    BEGIN
        IF OLD.state = 0 OR OLD.state = 1 THEN
            # Decrement the state count if record exists
            UPDATE lease6_stat SET leases = leases - 1
            WHERE subnet_id = OLD.subnet_id AND lease_type = OLD.lease_type
            AND state = OLD.state;
        END IF;
    END $$
DELIMITER ;

# Update the schema version number
UPDATE schema_version
SET version = '6', minor = '0';

# This line concludes database upgrade to version 6.0.

# Notes:
#
# Indexes
# =======
# It is likely that additional indexes will be needed.  However, the
# increase in lookup performance from these will come at the expense
# of a decrease in performance during insert operations due to the need
# to update the indexes.  For this reason, the need for additional indexes
# will be determined by experiment during performance tests.
#
# The most likely additional indexes will cover the following columns:
#
# hwaddr and client_id
# For lease stability: if a client requests a new lease, try to find an
# existing or recently expired lease for it so that it can keep using the
# same IP address.
#
# Field Sizes
# ===========
# If any of the VARxxx field sizes are altered, the lengths in the MySQL
# backend source file (mysql_lease_mgr.cc) must be correspondingly changed.
#
# Portability
# ===========
# The 'ENGINE = INNODB' on some tables is not portable to another database
# and will need to be removed.
#
# Some columns contain binary data so are stored as VARBINARY instead of
# VARCHAR.  This may be non-portable between databases: in this case, the
# definition should be changed to VARCHAR.
