-- Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
-- Copyright (C) 2015-2018 Deutsche Telekom AG.

-- Author: Razvan Becheriu <razvan.becheriu@qualitance.com>

-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at

--           http://www.apache.org/licenses/LICENSE-2.0

-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

-- This is the Kea schema specification for Cassandra CQL.

-- The schema is reasonably portable (with the exception of the engine
-- specification, which is Cassandra CQL-specific).  Minor changes might be needed for
-- other databases.

-- To create the schema, either type the command:

-- cqlsh -u <user> -p <password> -k <database> -f dhcpdb_create.cql

-- ... at the command prompt, or log in to the CQL database and at the "cqlsh>"
-- prompt, issue the command:

-- SOURCE dhcpdb_create.cql

-- This script is also called from kea-admin, see kea-admin lease-init cql

-- Over time, Kea database schema will evolve. Each version is marked with
-- major.minor version. This file is organized sequentially, i.e. database
-- is initialized to 1.0, then upgraded to 2.0 etc. This may be somewhat
-- sub-optimal, but it ensues consistency with upgrade scripts. (It is much
-- easier to maintain init and upgrade scripts if they look the same).
-- Since initialization is done only once, it's performance is not an issue.

-- This line starts database initialization to 1.0.

-- Holds the IPv4 leases.
-- -----------------------------------------------------
-- Table `lease4`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lease4 (
    address INT,
    hwaddr BLOB,
    client_id BLOB,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id INT,
    fqdn_fwd BOOLEAN,
    fqdn_rev BOOLEAN,
    hostname VARCHAR,
    state INT,
    PRIMARY KEY ((address))
);

-- Create search indexes for lease4 table
CREATE INDEX IF NOT EXISTS lease4index1 ON lease4 (client_id);
CREATE INDEX IF NOT EXISTS lease4index2 ON lease4 (subnet_id);
CREATE INDEX IF NOT EXISTS lease4index3 ON lease4 (hwaddr);
CREATE INDEX IF NOT EXISTS lease4index4 ON lease4 (expire);
CREATE INDEX IF NOT EXISTS lease4index5 ON lease4 (state);

-- Holds the IPv6 leases.
-- N.B. The use of a VARCHAR for the address is temporary for development:
-- it will eventually be replaced by BINARY(16).
-- -----------------------------------------------------
-- Table `lease6`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lease6 (
    address VARCHAR,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id INT,
    pref_lifetime BIGINT,
    duid BLOB,
    iaid INT,
    lease_type INT,
    prefix_len INT,
    fqdn_fwd BOOLEAN,
    fqdn_rev BOOLEAN,
    hostname VARCHAR,
    hwaddr BLOB,
    hwtype INT,
    hwaddr_source INT,
    state INT,
    PRIMARY KEY ((address))
);

-- Create search indexes for lease6 table
CREATE INDEX IF NOT EXISTS lease6index1 ON lease6 (duid);
CREATE INDEX IF NOT EXISTS lease6index2 ON lease6 (iaid);
CREATE INDEX IF NOT EXISTS lease6index3 ON lease6 (lease_type);
CREATE INDEX IF NOT EXISTS lease6index4 ON lease6 (subnet_id);
CREATE INDEX IF NOT EXISTS lease6index5 ON lease6 (expire);
CREATE INDEX IF NOT EXISTS lease6index6 ON lease6 (state);

-- ... and a definition of lease6 types.  This table is a convenience for
-- users of the database - if they want to view the lease table and use the
-- type names, they can join this table with the lease6 table.
-- Make sure those values match Lease6::LeaseType enum (see src/bin/dhcpsrv/
-- lease_mgr.h)
-- -----------------------------------------------------
-- Table `lease6_types`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lease6_types (
    lease_type INT,                             -- Lease type code.
    name VARCHAR,                               -- Name of the lease type
    PRIMARY KEY ((lease_type))
);
INSERT INTO lease6_types (lease_type, name) VALUES (0, 'IA_NA');   -- Non-temporary v6 addresses
INSERT INTO lease6_types (lease_type, name) VALUES (1, 'IA_TA');   -- Temporary v6 addresses
INSERT INTO lease6_types (lease_type, name) VALUES (2, 'IA_PD');   -- Prefix delegations

-- Kea keeps track of the hardware/MAC address source, i.e. how the address
-- was obtained. Depending on the technique and your network topology, it may
-- be more or less trustworthy. This table is a convenience for
-- users of the database - if they want to view the lease table and use the
-- type names, they can join this table with the lease6 table. For details,
-- see constants defined in src/lib/dhcp/dhcp/pkt.h for detailed explanation.
-- -----------------------------------------------------
-- Table `lease_hwaddr_source`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lease_hwaddr_source (
    hwaddr_source INT,
    name VARCHAR,
    PRIMARY KEY ((hwaddr_source))
);

INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (0, 'HWADDR_SOURCE_UNKNOWN');

-- Hardware address obtained from raw sockets
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (1, 'HWADDR_SOURCE_RAW');

-- Hardware address converted from IPv6 link-local address with EUI-64
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (2, 'HWADDR_SOURCE_IPV6_LINK_LOCAL');

-- Hardware address extracted from client-id (duid)
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (4, 'HWADDR_SOURCE_DUID');

-- Hardware address extracted from client address relay option (RFC6939)
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (8, 'HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION');

-- Hardware address extracted from remote-id option (RFC4649)
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (16, 'HWADDR_SOURCE_REMOTE_ID');

-- Hardware address extracted from subscriber-id option (RFC4580)
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (32, 'HWADDR_SOURCE_SUBSCRIBER_ID');

-- Hardware address extracted from docsis options
INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (64, 'HWADDR_SOURCE_DOCSIS_CMTS');

INSERT INTO lease_hwaddr_source (hwaddr_source, name) VALUES (128, 'HWADDR_SOURCE_DOCSIS_MODEM');

-- Create table holding mapping of the lease states to their names.
-- This is not used in queries from the DHCP server but rather in
-- direct queries from the lease database management tools.
-- -----------------------------------------------------
-- Table `lease_state`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lease_state (
    state INT,
    name VARCHAR,
    PRIMARY KEY ((state))
);

-- Insert currently defined state names.
INSERT INTO lease_state (state, name) VALUES (0, 'default');
INSERT INTO lease_state (state, name) VALUES (1, 'declined');
INSERT INTO lease_state (state, name) VALUES (2, 'expired-reclaimed');

-- Finally, the version of the schema.  We start at 1.0 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".
-- -----------------------------------------------------
-- Table `schema_version`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS schema_version (
    version INT,
    minor INT,
    PRIMARY KEY ((version))
);

INSERT INTO schema_version (version, minor) VALUES (1, 0);

-- This line concludes database initialization to version 1.0.

-- This line starts database upgrade to version 2.0

-- -----------------------------------------------------
-- Table `host_reservations`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS host_reservations (
    id BIGINT,
    host_identifier BLOB,
    host_identifier_type INT,
    host_ipv4_subnet_id INT,
    host_ipv6_subnet_id INT,
    host_ipv4_address INT,
    host_ipv4_next_server INT,
    host_ipv4_server_hostname VARCHAR,
    host_ipv4_boot_file_name VARCHAR,
    hostname VARCHAR,
    user_context VARCHAR,
    host_ipv4_client_classes VARCHAR,
    host_ipv6_client_classes VARCHAR,
    -- reservation
    reserved_ipv6_prefix_address VARCHAR,
    reserved_ipv6_prefix_length INT,
    reserved_ipv6_prefix_address_type INT,
    iaid INT,
    -- option
    option_universe INT,
    option_code INT,
    option_value BLOB,
    option_formatted_value VARCHAR,
    option_space VARCHAR,
    option_is_persistent BOOLEAN,
    option_client_class VARCHAR,
    option_subnet_id INT,
    option_user_context VARCHAR,
    option_scope_id INT,
    PRIMARY KEY ((id))
);

CREATE INDEX IF NOT EXISTS host_reservationsindex1 ON host_reservations (host_identifier);
CREATE INDEX IF NOT EXISTS host_reservationsindex2 ON host_reservations (host_identifier_type);
CREATE INDEX IF NOT EXISTS host_reservationsindex3 ON host_reservations (host_ipv4_subnet_id);
CREATE INDEX IF NOT EXISTS host_reservationsindex4 ON host_reservations (host_ipv6_subnet_id);
CREATE INDEX IF NOT EXISTS host_reservationsindex5 ON host_reservations (host_ipv4_address);
CREATE INDEX IF NOT EXISTS host_reservationsindex6 ON host_reservations (reserved_ipv6_prefix_address);
CREATE INDEX IF NOT EXISTS host_reservationsindex7 ON host_reservations (reserved_ipv6_prefix_length);

-- -----------------------------------------------------
-- Table `host_identifier_type`
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS host_identifier_type (
    type INT,
    name VARCHAR,
    PRIMARY KEY ((type))
);

-- Insert currently defined type names.
INSERT INTO host_identifier_type (type, name) VALUES (0, 'hw-address');
INSERT INTO host_identifier_type (type, name) VALUES (1, 'duid');
INSERT INTO host_identifier_type (type, name) VALUES (2, 'circuit-id');
INSERT INTO host_identifier_type (type, name) VALUES (3, 'client-id');
INSERT INTO host_identifier_type (type, name) VALUES (4, 'flex-id');

-- -----------------------------------------------------
-- Table `dhcp_option_scope`
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS dhcp_option_scope (
    scope_id INT,
    scope_name VARCHAR,
    PRIMARY KEY ((scope_id))
);

INSERT INTO dhcp_option_scope (scope_id, scope_name) VALUES (0, 'global');
INSERT INTO dhcp_option_scope (scope_id, scope_name) VALUES (1, 'subnet');
INSERT INTO dhcp_option_scope (scope_id, scope_name) VALUES (2, 'client-class');
INSERT INTO dhcp_option_scope (scope_id, scope_name) VALUES (3, 'host');

DELETE FROM schema_version WHERE version=1;
INSERT INTO schema_version (version, minor) VALUES(2, 0);

-- This line concludes database upgrade to version 2.0

-- This line starts database upgrade to version 3.0

-- Add a column holding leases for user context.
ALTER TABLE lease4 ADD user_context VARCHAR;
ALTER TABLE lease6 ADD user_context VARCHAR;

-- -----------------------------------------------------
-- Table `logs` (logs table is used by forensic logging hook library)
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS logs (
    timeuuid TIMEUUID,  -- creation timeuuid, use dateOf() to get timestamp
    address VARCHAR,    -- address or prefix
    log VARCHAR,        -- the log itself
    PRIMARY KEY ((timeuuid))
);

-- Create search index for logs table
CREATE INDEX IF NOT EXISTS logsindex ON logs (address);

-- This line adds auth_key column into host reservation table
ALTER TABLE host_reservations ADD auth_key VARCHAR;

-- Cql requires primary keys in the WHERE here.
DELETE FROM schema_version WHERE version=2;
INSERT INTO schema_version (version, minor) VALUES(3, 0);

-- This line concludes database upgrade to version 3.0

-- This line starts database upgrade to version 4.0

-- -----------------------------------------------------
-- Table `hosts`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS hosts (
    key BIGINT,
    id BIGINT,
    host_identifier BLOB,
    host_identifier_type INT,
    host_ipv4_subnet_id INT,
    host_ipv6_subnet_id INT,
    host_ipv4_address INT,
    host_ipv4_next_server INT,
    host_ipv4_server_hostname VARCHAR,
    host_ipv4_boot_file_name VARCHAR,
    hostname VARCHAR,
    auth_key VARCHAR,
    user_context VARCHAR,
    host_ipv4_client_classes VARCHAR,
    host_ipv6_client_classes VARCHAR,
    -- reservation
    reserved_ipv6_prefix_address VARCHAR,
    reserved_ipv6_prefix_length INT,
    reserved_ipv6_prefix_address_type INT,
    iaid INT,
    -- option
    option_universe INT,
    option_code INT,
    option_value BLOB,
    option_formatted_value VARCHAR,
    option_space VARCHAR,
    option_is_persistent BOOLEAN,
    option_client_class VARCHAR,
    option_subnet_id INT,
    option_user_context VARCHAR,
    option_scope_id INT,
    PRIMARY KEY ((key), id)
);

CREATE INDEX IF NOT EXISTS hostsindex1 ON hosts (host_identifier);
CREATE INDEX IF NOT EXISTS hostsindex2 ON hosts (host_identifier_type);
CREATE INDEX IF NOT EXISTS hostsindex3 ON hosts (host_ipv4_subnet_id);
CREATE INDEX IF NOT EXISTS hostsindex4 ON hosts (host_ipv6_subnet_id);
CREATE INDEX IF NOT EXISTS hostsindex5 ON hosts (host_ipv4_address);
CREATE INDEX IF NOT EXISTS hostsindex6 ON hosts (reserved_ipv6_prefix_address);
CREATE INDEX IF NOT EXISTS hostsindex7 ON hosts (reserved_ipv6_prefix_length);

DROP TABLE IF EXISTS host_reservations;

DROP INDEX IF EXISTS host_reservationsindex1;
DROP INDEX IF EXISTS host_reservationsindex2;
DROP INDEX IF EXISTS host_reservationsindex3;
DROP INDEX IF EXISTS host_reservationsindex4;
DROP INDEX IF EXISTS host_reservationsindex5;
DROP INDEX IF EXISTS host_reservationsindex6;
DROP INDEX IF EXISTS host_reservationsindex7;

-- Cql requires primary keys in the WHERE here.
DELETE FROM schema_version WHERE version=3;
INSERT INTO schema_version (version, minor) VALUES(4, 0);

-- This line concludes database upgrade to version 4.0
