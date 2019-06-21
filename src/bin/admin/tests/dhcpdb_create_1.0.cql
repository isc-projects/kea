-- Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
-- Copyright (C) 2015-2017 Deutsche Telekom AG.

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

-- This is the Kea schema 1.0 specification for Cassandra CQL.
-- Note: this is outdated version on purpose and it used to test upgrade
-- process. Do not update this file to 2.0 or any later.

-- The schema is reasonably portable (with the exception of the engine
-- specification, which is Cassandra CQL-specific).  Minor changes might be needed for
-- other databases.

-- To create the schema, either type the command:

-- cqlsh -u <user> -p <password> -k <database> -f dhcpdb_create.cql

-- ... at the command prompt, or log in to the CQL database and at the "cqlsh>"
-- prompt, issue the command:

-- SOURCE dhcpdb_create.cql

-- This script is also called from kea-admin, see kea-admin db-init cql

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
    address int,
    hwaddr blob,
    client_id blob,
    valid_lifetime bigint,
    expire bigint,
    subnet_id int,
    fqdn_fwd boolean,
    fqdn_rev boolean,
    hostname varchar,
    state int,
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
    address varchar,
    valid_lifetime bigint,
    expire bigint,
    subnet_id int,
    pref_lifetime bigint,
    duid blob,
    iaid int,
    lease_type int,
    prefix_len int,
    fqdn_fwd boolean,
    fqdn_rev boolean,
    hostname varchar,
    hwaddr blob,
    hwtype int,
    hwaddr_source int,
    state int,
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
    lease_type int,                             -- Lease type code.
    name varchar,                               -- Name of the lease type
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
    hwaddr_source int,
    name varchar,
    PRIMARY KEY ((hwaddr_source))
);

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

-- Create table holding mapping of the lease states to their names.
-- This is not used in queries from the DHCP server but rather in
-- direct queries from the lease database management tools.
-- -----------------------------------------------------
-- Table `lease_state`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lease_state (
    state int,
    name varchar,
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
-- Note: This MUST be kept in step with src/share/database/scripts/cassandra/dhcpdb_create.cql,
-- which defines the schema for the unit tests.
-- -----------------------------------------------------
-- Table `schema_version`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS schema_version (
    version int,
    minor int,
    PRIMARY KEY ((version))
);

INSERT INTO schema_version (version, minor) VALUES (1, 0);

-- This line concludes database initialization to version 1.0.

