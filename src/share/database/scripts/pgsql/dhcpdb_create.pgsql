-- Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")

-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

-- This is the Kea DHCP schema specification for PostgreSQL.

-- The schema is reasonably portable (with the exception of some field types
-- specification, which are PostgreSQL-specific).  Minor changes might be needed
-- for other databases.

-- To create the schema, either type the command:

-- psql -U <user> -W <password> <database> < dhcpdb_create.pgsql

-- ... at the command prompt, or log in to the PostgreSQL database and at the "postgres=#"
-- prompt, issue the command:

-- @dhcpdb_create.pgsql

-- Start a single transaction for the Entire script
START TRANSACTION;

-- Holds the IPv4 leases.
CREATE TABLE lease4 (
    address BIGINT PRIMARY KEY NOT NULL,        -- IPv4 address
    hwaddr BYTEA,                               -- Hardware address
    client_id BYTEA,                            -- Client ID
    valid_lifetime BIGINT,                      -- Length of the lease (seconds)
    expire TIMESTAMP WITH TIME ZONE,            -- Expiration time of the lease
    subnet_id BIGINT,                           -- Subnet identification
    fqdn_fwd BOOLEAN,                           -- Has forward DNS update been performed by a server
    fqdn_rev BOOLEAN,                           -- Has reverse DNS update been performed by a server
    hostname VARCHAR(255)                       -- The FQDN of the client
    );

-- Create search indexes for lease4 table
-- index by hwaddr and subnet_id
CREATE INDEX lease4_by_hwaddr_subnet_id ON lease4 (hwaddr, subnet_id);

-- index by client_id and subnet_id
CREATE INDEX lease4_by_client_id_subnet_id ON lease4 (client_id, subnet_id);

-- Holds the IPv6 leases.
-- N.B. The use of a VARCHAR for the address is temporary for development:
-- it will eventually be replaced by BINARY(16).
CREATE TABLE lease6 (
    address VARCHAR(39) PRIMARY KEY NOT NULL,   -- IPv6 address
    duid BYTEA,                                 -- DUID
    valid_lifetime BIGINT,                      -- Length of the lease (seconds)
    expire TIMESTAMP WITH TIME ZONE,            -- Expiration time of the lease
    subnet_id BIGINT,                           -- Subnet identification
    pref_lifetime BIGINT,                       -- Preferred lifetime
    lease_type SMALLINT,                        -- Lease type (see lease6_types
                                                --    table for possible values)
    iaid INT,                                   -- See Section 10 of RFC 3315
    prefix_len SMALLINT,                        -- For IA_PD only
    fqdn_fwd BOOLEAN,                           -- Has forward DNS update been performed by a server
    fqdn_rev BOOLEAN,                           -- Has reverse DNS update been performed by a server
    hostname VARCHAR(255)                       -- The FQDN of the client
    );

-- Create search indexes for lease6 table
-- index by iaid, subnet_id, and duid
CREATE INDEX lease6_by_iaid_subnet_id_duid ON lease6 (iaid, subnet_id, duid);

-- ... and a definition of lease6 types.  This table is a convenience for
-- users of the database - if they want to view the lease table and use the
-- type names, they can join this table with the lease6 table
CREATE TABLE lease6_types (
    lease_type SMALLINT PRIMARY KEY NOT NULL,   -- Lease type code.
    name VARCHAR(5)                             -- Name of the lease type
    );

INSERT INTO lease6_types VALUES (0, 'IA_NA');   -- Non-temporary v6 addresses
INSERT INTO lease6_types VALUES (1, 'IA_TA');   -- Temporary v6 addresses
INSERT INTO lease6_types VALUES (2, 'IA_PD');   -- Prefix delegations

-- Finally, the version of the schema.  We start at 0.1 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".
CREATE TABLE schema_version (
    version INT PRIMARY KEY NOT NULL,       -- Major version number
    minor INT                               -- Minor version number
    );

INSERT INTO schema_version VALUES (1, 0);

--
-- Schema 2.0 specification starts here.
--

-- Add state column to the lease4 table.
ALTER TABLE lease4
    ADD COLUMN state INT8 DEFAULT 0;

-- Add state column to the lease6 table.
ALTER TABLE lease6
    ADD COLUMN state INT8 DEFAULT 0;

-- Create indexes for querying leases in a given state and segregated
-- by the expiration time. One of the applications is to retrieve all
-- expired leases. However, these indexes can be also used to retrieve
-- leases in a given state regardless of the expiration time.
CREATE INDEX lease4_by_state_expire ON lease4 (state ASC, expire ASC);
CREATE INDEX lease6_by_state_expire ON lease6 (state ASC, expire ASC);

-- Create table holding mapping of the lease states to their names.
-- This is not used in queries from the DHCP server but rather in
-- direct queries from the lease database management tools.
CREATE TABLE lease_state (
    state INT8 PRIMARY KEY NOT NULL,
    name VARCHAR(64) NOT NULL);

-- Insert currently defined state names.
INSERT INTO lease_state VALUES (0, 'default');
INSERT INTO lease_state VALUES (1, 'declined');
INSERT INTO lease_state VALUES (2, 'expired-reclaimed');

-- Add a constraint that any state value added to the lease4 must
-- map to a value in the lease_state table.
ALTER TABLE lease4
    ADD CONSTRAINT fk_lease4_state FOREIGN KEY (state)
    REFERENCES lease_state (state);

-- Add a constraint that any state value added to the lease6 must
-- map to a value in the lease_state table.
ALTER TABLE lease6
    ADD CONSTRAINT fk_lease6_state FOREIGN KEY (state)
    REFERENCES lease_state (state);

-- Add a constraint that lease type in the lease6 table must map
-- to a lease type defined in the lease6_types table.
ALTER TABLE lease6
    ADD CONSTRAINT fk_lease6_type FOREIGN KEY (lease_type)
    REFERENCES lease6_types (lease_type);

--
--  FUNCTION that returns a result set containing the column names for lease4 dumps.
DROP FUNCTION IF EXISTS lease4DumpHeader();
CREATE FUNCTION lease4DumpHeader() RETURNS text AS  $$
    select cast('address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease4 dumps.
DROP FUNCTION IF EXISTS lease4DumpData();
CREATE FUNCTION lease4DumpData() RETURNS
    table (address inet,
           hwaddr text,
           client_id text,
           valid_lifetime bigint,
           expire timestamp with time zone,
           subnet_id bigint,
           fqdn_fwd int,
           fqdn_rev int,
           hostname text,
           state text
    ) as $$
    SELECT ('0.0.0.0'::inet + l.address),
            encode(l.hwaddr,'hex'),
            encode(l.client_id,'hex'),
            l.valid_lifetime,
            l.expire,
            l.subnet_id,
            l.fqdn_fwd::int,
            l.fqdn_rev::int,
            l.hostname,
            s.name
    FROM lease4 l
         left outer join lease_state s on (l.state = s.state);
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the column names for lease6 dumps.
DROP FUNCTION IF EXISTS lease6DumpHeader();
CREATE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease6 dumps.
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE FUNCTION lease6DumpData() RETURNS
    TABLE (
           address text,
           duid text,
           valid_lifetime bigint,
           expire timestamp with time zone,
           subnet_id bigint,
           pref_lifetime bigint,
           name text,
           iaid integer,
           prefix_len smallint,
           fqdn_fwd int,
           fqdn_rev int,
           hostname text,
           state text
    ) AS $$
    SELECT (l.address,
            encode(l.duid,'hex'),
            l.valid_lifetime,
            l.expire,
            l.subnet_id,
            l.pref_lifetime,
            t.name,
            l.iaid,
            l.prefix_len,
            l.fqdn_fwd::int,
            l.fqdn_rev::int,
            l.hostname,
            s.name)
     FROM lease6 l
         left outer join lease6_types t on (l.lease_type = t.lease_type)
         left outer join lease_state s on (l.state = s.state);
$$ LANGUAGE SQL;
--

-- Set 2.0 schema version.
UPDATE schema_version
    SET version = '2', minor = '0';

-- Schema 2.0 specification ends here.

-- Upgrade to schema 3.0 begins here:

--
-- Table structure for table host_identifier_type.
--

CREATE TABLE host_identifier_type (
  type SMALLINT PRIMARY KEY NOT NULL,
  name VARCHAR(32) DEFAULT NULL
);

INSERT INTO host_identifier_type VALUES (0, 'hw-address');
INSERT INTO host_identifier_type VALUES (1, 'duid');
INSERT INTO host_identifier_type VALUES (2, 'circuit-id');
INSERT INTO host_identifier_type VALUES (3, 'client-id');

--
-- Table structure for table dhcp_option_scope.
--

CREATE TABLE dhcp_option_scope (
  scope_id SMALLINT PRIMARY KEY NOT NULL,
  scope_name varchar(32) DEFAULT NULL
);

INSERT INTO dhcp_option_scope VALUES (0, 'global');
INSERT INTO dhcp_option_scope VALUES (1, 'subnet');
INSERT INTO dhcp_option_scope VALUES (2, 'client-class');
INSERT INTO dhcp_option_scope VALUES (3, 'host');

--
-- Table structure for table hosts.
--
-- Primary key and unique constraints automatically create indexes,
-- foreign key constraints do not.
CREATE TABLE hosts (
  host_id SERIAL PRIMARY KEY NOT NULL,
  dhcp_identifier BYTEA NOT NULL,
  dhcp_identifier_type SMALLINT NOT NULL,
  dhcp4_subnet_id INT DEFAULT NULL,
  dhcp6_subnet_id INT DEFAULT NULL,
  ipv4_address BIGINT DEFAULT NULL,
  hostname VARCHAR(255) DEFAULT NULL,
  dhcp4_client_classes VARCHAR(255) DEFAULT NULL,
  dhcp6_client_classes VARCHAR(255) DEFAULT NULL,
  CONSTRAINT key_dhcp4_ipv4_address_subnet_id UNIQUE (ipv4_address, dhcp4_subnet_id),
  CONSTRAINT key_dhcp4_identifier_subnet_id UNIQUE (dhcp_identifier, dhcp_identifier_type, dhcp4_subnet_id),
  CONSTRAINT key_dhcp6_identifier_subnet_id UNIQUE (dhcp_identifier, dhcp_identifier_type, dhcp6_subnet_id),
  CONSTRAINT fk_host_identifier_type FOREIGN KEY (dhcp_identifier_type) REFERENCES host_identifier_type (type)
  ON DELETE CASCADE
);

CREATE INDEX fk_host_identifier_type ON hosts (dhcp_identifier_type);

--
-- Table structure for table dhcp4_options.
--

CREATE TABLE dhcp4_options (
  option_id SERIAL PRIMARY KEY NOT NULL,
  code SMALLINT NOT NULL,
  value BYTEA,
  formatted_value TEXT,
  space VARCHAR(128) DEFAULT NULL,
  persistent BOOLEAN NOT NULL DEFAULT 'f',
  dhcp_client_class VARCHAR(128) DEFAULT NULL,
  dhcp4_subnet_id INT DEFAULT NULL,
  host_id INT DEFAULT NULL,
  scope_id SMALLINT NOT NULL,
  CONSTRAINT fk_options_host1 FOREIGN KEY (host_id) REFERENCES hosts (host_id) ON DELETE CASCADE,
  CONSTRAINT fk_dhcp4_option_scode FOREIGN KEY (scope_id) REFERENCES dhcp_option_scope (scope_id) ON DELETE CASCADE
);

CREATE INDEX fk_dhcp4_options_host1_idx ON dhcp4_options (host_id);
CREATE INDEX fk_dhcp4_options_scope_idx ON dhcp4_options (scope_id);

--
-- Table structure for table dhcp6_options.
--

CREATE TABLE dhcp6_options (
  option_id SERIAL PRIMARY KEY NOT NULL,
  code INT NOT NULL,
  value BYTEA,
  formatted_value TEXT,
  space VARCHAR(128) DEFAULT NULL,
  persistent BOOLEAN NOT NULL DEFAULT 'f',
  dhcp_client_class VARCHAR(128) DEFAULT NULL,
  dhcp6_subnet_id INT DEFAULT NULL,
  host_id INT DEFAULT NULL,
  scope_id SMALLINT NOT NULL,
  CONSTRAINT fk_options_host10 FOREIGN KEY (host_id) REFERENCES hosts (host_id) ON DELETE CASCADE,
  CONSTRAINT fk_dhcp6_option_scode FOREIGN KEY (scope_id) REFERENCES dhcp_option_scope (scope_id) ON DELETE CASCADE
);

CREATE INDEX fk_dhcp6_options_host1_idx ON dhcp6_options (host_id);
CREATE INDEX fk_dhcp6_options_scope_idx ON dhcp6_options (scope_id);

--
-- Table structure for table ipv6_reservations.
--

CREATE TABLE ipv6_reservations (
  reservation_id SERIAL PRIMARY KEY NOT NULL,
  address VARCHAR(39) NOT NULL,
  prefix_len SMALLINT NOT NULL DEFAULT '128',
  type SMALLINT NOT NULL DEFAULT '0',
  dhcp6_iaid INT DEFAULT NULL,
  host_id INT NOT NULL,
  CONSTRAINT key_dhcp6_address_prefix_len UNIQUE (address, prefix_len),
  CONSTRAINT fk_ipv6_reservations_host FOREIGN KEY (host_id) REFERENCES hosts (host_id) ON DELETE CASCADE
);

CREATE INDEX fk_ipv6_reservations_host_idx ON ipv6_reservations (host_id);

--
-- Table structure for table lease_hwaddr_source.
--

CREATE TABLE lease_hwaddr_source (
  hwaddr_source INT PRIMARY KEY NOT NULL,
  name VARCHAR(40) DEFAULT NULL
);

-- In the event hardware address cannot be determined, we need to satisfy
-- foreign key constraint between lease6 and lease_hardware_source.
INSERT INTO lease_hwaddr_source VALUES (0, 'HWADDR_SOURCE_UNKNOWN');

-- Hardware address obtained from raw sockets.
INSERT INTO lease_hwaddr_source VALUES (1, 'HWADDR_SOURCE_RAW');

-- Hardware address converted from IPv6 link-local address with EUI-64.
INSERT INTO lease_hwaddr_source VALUES (2, 'HWADDR_SOURCE_IPV6_LINK_LOCAL');

-- Hardware address extracted from client-id (duid).
INSERT INTO lease_hwaddr_source VALUES (4, 'HWADDR_SOURCE_DUID');

-- Hardware address extracted from client address relay option (RFC6939).
INSERT INTO lease_hwaddr_source VALUES (8, 'HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION');

-- Hardware address extracted from remote-id option (RFC4649).
INSERT INTO lease_hwaddr_source VALUES (16, 'HWADDR_SOURCE_REMOTE_ID');

-- Hardware address extracted from subscriber-id option (RFC4580).
INSERT INTO lease_hwaddr_source VALUES (32, 'HWADDR_SOURCE_SUBSCRIBER_ID');

-- Hardware address extracted from docsis options.
INSERT INTO lease_hwaddr_source VALUES (64, 'HWADDR_SOURCE_DOCSIS_CMTS');

INSERT INTO lease_hwaddr_source VALUES (128, 'HWADDR_SOURCE_DOCSIS_MODEM');

-- Adding ORDER BY clause to sort by lease address.
--
--  FUNCTION that returns a result set containing the data for lease4 dumps.
DROP FUNCTION IF EXISTS lease4DumpData();
CREATE FUNCTION lease4DumpData() RETURNS
    table (address inet,
           hwaddr text,
           client_id text,
           valid_lifetime bigint,
           expire timestamp with time zone,
           subnet_id bigint,
           fqdn_fwd int,
           fqdn_rev int,
           hostname text,
           state text
    ) as $$
    SELECT ('0.0.0.0'::inet + l.address),
            encode(l.hwaddr,'hex'),
            encode(l.client_id,'hex'),
            l.valid_lifetime,
            l.expire,
            l.subnet_id,
            l.fqdn_fwd::int,
            l.fqdn_rev::int,
            l.hostname,
            s.name
    FROM lease4 l
         left outer join lease_state s on (l.state = s.state)
    ORDER BY l.address;
$$ LANGUAGE SQL;
--

-- Add new columns to lease6.
ALTER TABLE lease6
  ADD COLUMN hwaddr BYTEA DEFAULT NULL,
  ADD COLUMN hwtype SMALLINT DEFAULT NULL,
  ADD COLUMN hwaddr_source SMALLINT DEFAULT NULL;

--
--  FUNCTION that returns a result set containing the column names for lease6 dumps.
DROP FUNCTION IF EXISTS lease6DumpHeader();
CREATE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state,hwaddr,hwtype,hwaddr_source' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease6 dumps.
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE FUNCTION lease6DumpData() RETURNS
    TABLE (
           address text,
           duid text,
           valid_lifetime bigint,
           expire timestamp with time zone,
           subnet_id bigint,
           pref_lifetime bigint,
           name text,
           iaid integer,
           prefix_len smallint,
           fqdn_fwd int,
           fqdn_rev int,
           hostname text,
           state text,
           hwaddr text,
           hwtype smallint,
           hwaddr_source text
    ) AS $$
    SELECT (l.address,
            encode(l.duid,'hex'),
            l.valid_lifetime,
            l.expire,
            l.subnet_id,
            l.pref_lifetime,
            t.name,
            l.iaid,
            l.prefix_len,
            l.fqdn_fwd::int,
            l.fqdn_rev::int,
            l.hostname,
            s.name,
            encode(l.hwaddr,'hex'),
            l.hwtype,
            h.name
     )
     FROM lease6 l
         left outer join lease6_types t on (l.lease_type = t.lease_type)
         left outer join lease_state s on (l.state = s.state)
         left outer join lease_hwaddr_source h on (l.hwaddr_source = h.hwaddr_source)
     ORDER BY l.address;
$$ LANGUAGE SQL;

-- Add columns holding reservations for siaddr, sname and file fields
-- carried within DHCPv4 message.
ALTER TABLE hosts ADD COLUMN dhcp4_next_server BIGINT DEFAULT NULL;
ALTER TABLE hosts ADD COLUMN dhcp4_server_hostname VARCHAR(64) DEFAULT NULL;
ALTER TABLE hosts ADD COLUMN dhcp4_boot_file_name VARCHAR(128) DEFAULT NULL;

-- Set 3.0 schema version.
UPDATE schema_version
    SET version = '3', minor = '0';

-- Schema 3.0 specification ends here.

-- Upgrade to schema 3.1 begins here:

-- This is a placeholder for the changes between 3.0 and 3.1. We have added a
-- missing 'client-id' host reservation type entry that had been accidentally
-- omitted when the 2.0 -> 3.0 upgrade script was created.
-- Also, new flexible identifier has been added.
INSERT INTO host_identifier_type VALUES (4, 'flex-id');

-- Set 3.1 schema version.
UPDATE schema_version
    SET version = '3', minor = '1';

-- Schema 3.1 specification ends here.

-- Upgrade to schema 3.2 begins here:

-- Remove constraints which perform too restrictive checks on the inserted
-- host reservations. We want to be able to insert host reservations which
-- include no specific IPv4 address or those that have repeating subnet
-- identifiers, e.g. IPv4 reservations would typically include 0 (or null)
-- IPv6 subnet identifiers.
ALTER TABLE hosts DROP CONSTRAINT key_dhcp4_ipv4_address_subnet_id;
ALTER TABLE hosts DROP CONSTRAINT key_dhcp4_identifier_subnet_id;
ALTER TABLE hosts DROP CONSTRAINT key_dhcp6_identifier_subnet_id;

-- Create partial indexes instead of the constraints that we have removed.

-- IPv4 address/IPv4 subnet identifier pair is unique if subnet identifier is
-- not null and not 0.
CREATE UNIQUE INDEX key_dhcp4_ipv4_address_subnet_id ON hosts
       (ipv4_address ASC, dhcp4_subnet_id ASC)
    WHERE ipv4_address IS NOT NULL AND ipv4_address <> 0;

-- Client identifier is unique within an IPv4 subnet when subnet identifier is
-- not null and not 0.
CREATE UNIQUE INDEX key_dhcp4_identifier_subnet_id ON hosts
        (dhcp_identifier ASC, dhcp_identifier_type ASC, dhcp4_subnet_id ASC)
    WHERE (dhcp4_subnet_id IS NOT NULL AND dhcp4_subnet_id <> 0);

-- Client identifier is unique within an IPv6 subnet when subnet identifier is
-- not null and not 0.
CREATE UNIQUE INDEX key_dhcp6_identifier_subnet_id ON hosts
        (dhcp_identifier ASC, dhcp_identifier_type ASC, dhcp6_subnet_id ASC)
    WHERE (dhcp6_subnet_id IS NOT NULL AND dhcp6_subnet_id <> 0);

-- Set 3.2 schema version.
UPDATE schema_version
    SET version = '3', minor = '2';

-- Schema 3.2 specification ends here.

-- Upgrade to schema 3.3 begins here:

-- Change subnet ID columns type to BIGINT to match lease4/6 tables
ALTER TABLE hosts ALTER COLUMN dhcp4_subnet_id TYPE BIGINT;
ALTER TABLE hosts ALTER COLUMN dhcp6_subnet_id TYPE BIGINT;

ALTER TABLE dhcp4_options ALTER COLUMN dhcp4_subnet_id TYPE BIGINT;
ALTER TABLE dhcp6_options ALTER COLUMN dhcp6_subnet_id TYPE BIGINT;

-- Set 3.3 schema version.
UPDATE schema_version
    SET version = '3', minor = '3';

-- Schema 3.3 specification ends here.

-- Upgrade to schema 4.0 begins here:

-- Add a column holding hosts for user context.
ALTER TABLE hosts ADD COLUMN user_context TEXT;

-- Add a column holding DHCP options for user context.
ALTER TABLE dhcp4_options ADD COLUMN user_context TEXT;
ALTER TABLE dhcp6_options ADD COLUMN user_context TEXT;

-- Create index for searching leases by subnet identifier.
CREATE INDEX lease4_by_subnet_id ON lease4 (subnet_id);

-- Create for searching leases by subnet identifier and lease type.
CREATE INDEX lease6_by_subnet_id_lease_type ON lease6 (subnet_id, lease_type);

-- The index by iaid_subnet_id_duid is not the best choice because there are
-- cases when we don't specify subnet identifier while searching leases. The
-- index will be universal if the subnet_id is the right most column in the
-- index.
DROP INDEX lease6_by_iaid_subnet_id_duid;
CREATE INDEX lease6_by_duid_iaid_subnet_id ON lease6 (duid, iaid, subnet_id);

-- Set 4.0 schema version.
UPDATE schema_version
    SET version = '4', minor = '0';

-- Schema 4.0 specification ends here.

-- Commit the script transaction.
COMMIT;

-- Notes:

-- Indexes
-- =======
-- It is likely that additional indexes will be needed.  However, the
-- increase in lookup performance from these will come at the expense
-- of a decrease in performance during insert operations due to the need
-- to update the indexes.  For this reason, the need for additional indexes
-- will be determined by experiment during performance tests.

-- The most likely additional indexes will cover the following columns:

-- hwaddr and client_id
-- For lease stability: if a client requests a new lease, try to find an
-- existing or recently expired lease for it so that it can keep using the
-- same IP address.

-- Field Sizes
-- ===========
-- If any of the VARxxx field sizes are altered, the lengths in the PgSQL
-- backend source file (pgsql_lease_mgr.cc) must be correspondingly changed.

-- Portability
-- ===========
-- Some columns contain binary data so are stored as BYTEA instead of
-- VARCHAR.  This may be non-portable between databases: in this case, the
-- definition should be changed to VARCHAR.
