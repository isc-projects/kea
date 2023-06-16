-- Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")

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

-- Start a single transaction for the entire script.
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
    iaid INT,                                   -- See Section 12 of RFC 8415
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

-- This line starts the schema upgrade to version 2.0.

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
CREATE OR REPLACE FUNCTION lease4DumpHeader() RETURNS text AS  $$
    select cast('address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease4 dumps.
DROP FUNCTION IF EXISTS lease4DumpData();
CREATE OR REPLACE FUNCTION lease4DumpData() RETURNS
    table (address inet,
           hwaddr text,
           client_id text,
           valid_lifetime bigint,
           expire TIMESTAMP WITH TIME ZONE,
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
CREATE OR REPLACE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease6 dumps.
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE OR REPLACE FUNCTION lease6DumpData() RETURNS
    TABLE (
           address text,
           duid text,
           valid_lifetime bigint,
           expire TIMESTAMP WITH TIME ZONE,
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

-- Update the schema version number.
UPDATE schema_version
    SET version = '2', minor = '0';

-- This line concludes the schema upgrade to version 2.0.

-- This line starts the schema upgrade to version 3.0.

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
  scope_name VARCHAR(32) DEFAULT NULL
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
  dhcp4_subnet_id BIGINT DEFAULT NULL,
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
  dhcp6_subnet_id BIGINT DEFAULT NULL,
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
CREATE OR REPLACE FUNCTION lease4DumpData() RETURNS
    table (address inet,
           hwaddr text,
           client_id text,
           valid_lifetime bigint,
           expire TIMESTAMP WITH TIME ZONE,
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
CREATE OR REPLACE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state,hwaddr,hwtype,hwaddr_source' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease6 dumps.
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE OR REPLACE FUNCTION lease6DumpData() RETURNS
    TABLE (
           address text,
           duid text,
           valid_lifetime bigint,
           expire TIMESTAMP WITH TIME ZONE,
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

-- Update the schema version number.
UPDATE schema_version
    SET version = '3', minor = '0';

-- This line concludes the schema upgrade to version 3.0.

-- This line starts the schema upgrade to version 3.1.

-- This is a placeholder for the changes between 3.0 and 3.1. We have added a
-- missing 'client-id' host reservation type entry that had been accidentally
-- omitted when the 2.0 -> 3.0 upgrade script was created.
-- Also, new flexible identifier has been added.
INSERT INTO host_identifier_type VALUES (4, 'flex-id');

-- Update the schema version number.
UPDATE schema_version
    SET version = '3', minor = '1';

-- This line concludes the schema upgrade to version 3.1.

-- This line starts the schema upgrade to version 3.2.

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

-- Update the schema version number.
UPDATE schema_version
    SET version = '3', minor = '2';

-- This line concludes the schema upgrade to version 3.2.

-- This line starts the schema upgrade to version 3.3.

-- Change subnet ID columns type to BIGINT to match lease4/6 tables
ALTER TABLE hosts ALTER COLUMN dhcp4_subnet_id TYPE BIGINT;
ALTER TABLE hosts ALTER COLUMN dhcp6_subnet_id TYPE BIGINT;

ALTER TABLE dhcp4_options ALTER COLUMN dhcp4_subnet_id TYPE BIGINT;
ALTER TABLE dhcp6_options ALTER COLUMN dhcp6_subnet_id TYPE BIGINT;

-- Update the schema version number.
UPDATE schema_version
    SET version = '3', minor = '3';

-- This line concludes the schema upgrade to version 3.3.

-- This line starts the schema upgrade to version 4.0.

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

-- Create v4 lease statistics table
CREATE TABLE lease4_stat (
    subnet_id BIGINT NOT NULL,
    state INT8 NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, state)
);

--
-- Create v4 insert trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease4_insert() RETURNS trigger AS $stat_lease4_insert$
BEGIN
    IF NEW.state < 2 THEN
        UPDATE lease4_stat
            SET leases = leases + 1
            WHERE subnet_id = NEW.subnet_id AND state = NEW.state;

        IF NOT FOUND THEN
            INSERT INTO lease4_stat VALUES (new.subnet_id, new.state, 1);
        END IF;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease4_insert$ LANGUAGE plpgsql;

-- Create v4 insert trigger procedure
CREATE TRIGGER stat_lease4_insert
AFTER INSERT ON lease4
    FOR EACH ROW EXECUTE PROCEDURE proc_stat_lease4_insert();

--
-- Create v4 update trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease4_update() RETURNS trigger AS $stat_lease4_update$
BEGIN
    IF OLD.state != NEW.state THEN
        IF OLD.state < 2 THEN
            -- Decrement the old state count if record exists
            UPDATE lease4_stat SET leases = leases - 1
            WHERE subnet_id = OLD.subnet_id AND state = OLD.state;
        END IF;

        IF NEW.state < 2 THEN
            -- Increment the new state count if record exists
            UPDATE lease4_stat SET leases = leases + 1
            WHERE subnet_id = NEW.subnet_id AND state = NEW.state;

            -- Insert new state record if it does not exist
            IF NOT FOUND THEN
                INSERT INTO lease4_stat VALUES (NEW.subnet_id, NEW.state, 1);
            END IF;
        END IF;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease4_update$ LANGUAGE plpgsql;

-- Create v4 update trigger
CREATE TRIGGER stat_lease4_update
AFTER UPDATE ON lease4
    FOR EACH ROW EXECUTE PROCEDURE proc_stat_lease4_update();

--
-- Create the v4 delete trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease4_delete() RETURNS trigger AS $stat_lease4_delete$
BEGIN
    IF OLD.state < 2 THEN
        -- Decrement the state count if record exists
        UPDATE lease4_stat SET leases = leases - 1
        WHERE subnet_id = OLD.subnet_id AND OLD.state = state;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease4_delete$ LANGUAGE plpgsql;

-- Create the v4 delete trigger
CREATE TRIGGER stat_lease4_delete
AFTER DELETE ON lease4
    FOR EACH ROW EXECUTE PROCEDURE proc_stat_lease4_delete();

-- Create v6 lease statistics table
CREATE TABLE lease6_stat (
    subnet_id BIGINT NOT NULL,
    lease_type SMALLINT NOT NULL,
    state INT8 NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, lease_type, state)
);

--
-- Create v6 insert trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease6_insert() RETURNS trigger AS $stat_lease6_insert$
BEGIN
    IF NEW.state < 2 THEN
        UPDATE lease6_stat
        SET leases = leases + 1
        WHERE
        subnet_id = NEW.subnet_id AND lease_type = NEW.lease_type
        AND state = NEW.state;

        IF NOT FOUND THEN
            INSERT INTO lease6_stat
            VALUES (NEW.subnet_id, NEW.lease_type, NEW.state, 1);
        END IF;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease6_insert$ LANGUAGE plpgsql;

-- Create v6 insert trigger procedure
CREATE TRIGGER stat_lease6_insert
AFTER INSERT ON lease6
    FOR EACH ROW EXECUTE PROCEDURE proc_stat_lease6_insert();

--
-- Create v6 update trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease6_update() RETURNS trigger AS $stat_lease6_update$
BEGIN
    IF OLD.state != NEW.state THEN
        IF OLD.state < 2 THEN
            -- Decrement the old state count if record exists
            UPDATE lease6_stat SET leases = leases - 1
            WHERE subnet_id = OLD.subnet_id AND lease_type = OLD.lease_type
            AND state = OLD.state;
        END IF;

        IF NEW.state < 2 THEN
            -- Increment the new state count if record exists
            UPDATE lease6_stat SET leases = leases + 1
            WHERE subnet_id = NEW.subnet_id AND lease_type = NEW.lease_type
            AND state = NEW.state;

            -- Insert new state record if it does not exist
            IF NOT FOUND THEN
                INSERT INTO lease6_stat VALUES (NEW.subnet_id, NEW.lease_type, NEW.state, 1);
            END IF;
        END IF;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease6_update$ LANGUAGE plpgsql;

-- Create v6 update trigger
CREATE TRIGGER stat_lease6_update
AFTER UPDATE ON lease6
    FOR EACH ROW EXECUTE PROCEDURE proc_stat_lease6_update();

--
-- Create the v6 delete trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease6_delete() RETURNS trigger AS $stat_lease6_delete$
BEGIN
    IF OLD.state < 2 THEN
        -- Decrement the state count if record exists
        UPDATE lease6_stat SET leases = leases - 1
        WHERE subnet_id = OLD.subnet_id AND lease_type = OLD.lease_type
        AND OLD.state = state;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease6_delete$ LANGUAGE plpgsql;

-- Create the v6 delete trigger
CREATE TRIGGER stat_lease6_delete
AFTER DELETE ON lease6
    FOR EACH ROW EXECUTE PROCEDURE proc_stat_lease6_delete();

-- Update the schema version number.
UPDATE schema_version
    SET version = '4', minor = '0';

-- This line concludes the schema upgrade to version 4.0.

-- This line starts the schema upgrade to version 5.0.

-- Add a column holding leases for user context.
ALTER TABLE lease4 ADD COLUMN user_context TEXT;
ALTER TABLE lease6 ADD COLUMN user_context TEXT;

--
DROP FUNCTION IF EXISTS lease4DumpHeader();
CREATE OR REPLACE FUNCTION lease4DumpHeader() RETURNS text AS  $$
    select cast('address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context' as text) as result;
$$ LANGUAGE SQL;
--

--
DROP FUNCTION IF EXISTS lease4DumpData();
CREATE OR REPLACE FUNCTION lease4DumpData() RETURNS
    table (address inet,
           hwaddr text,
           client_id text,
           valid_lifetime bigint,
           expire TIMESTAMP WITH TIME ZONE,
           subnet_id bigint,
           fqdn_fwd int,
           fqdn_rev int,
           hostname text,
           state text,
           user_context text
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
            s.name,
            l.user_context
    FROM lease4 l
         left outer join lease_state s on (l.state = s.state)
    ORDER BY l.address;
$$ LANGUAGE SQL;
--

--
DROP FUNCTION IF EXISTS lease6DumpHeader();
CREATE OR REPLACE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state,hwaddr,hwtype,hwaddr_source,user_context' as text) as result;
$$ LANGUAGE SQL;
--

--
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE OR REPLACE FUNCTION lease6DumpData() RETURNS
    TABLE (
           address text,
           duid text,
           valid_lifetime bigint,
           expire TIMESTAMP WITH TIME ZONE,
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
           hwaddr_source text,
           user_context text
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
            h.name,
            l.user_context

     )
     FROM lease6 l
         left outer join lease6_types t on (l.lease_type = t.lease_type)
         left outer join lease_state s on (l.state = s.state)
         left outer join lease_hwaddr_source h on (l.hwaddr_source = h.hwaddr_source)
     ORDER BY l.address;
$$ LANGUAGE SQL;
--

-- Create logs table (logs table is used by forensic logging hook library)
CREATE TABLE logs (
    timestamp TIMESTAMP WITH TIME ZONE
    DEFAULT CURRENT_TIMESTAMP,          -- creation timestamp
    address VARCHAR(43) NULL,           -- address or prefix
    log TEXT NOT NULL                   -- the log itself
    );

-- Create search indexes
CREATE INDEX timestamp_id ON logs (timestamp);
CREATE INDEX address_id ON logs (address);

-- Create auth_key in hosts table for storing keys for DHCPv6 reconfigure.
ALTER TABLE hosts ADD COLUMN auth_key  VARCHAR(16) DEFAULT NULL;

-- Update the schema version number.
UPDATE schema_version
   SET version = '5', minor = '0';

-- This line concludes the schema upgrade to version 5.0.

-- This line starts the schema upgrade to version 5.1.

-- Put the auth key in hexadecimal (double size but far more user friendly).
ALTER TABLE hosts ALTER COLUMN auth_key TYPE VARCHAR(32);

-- Update the schema version number.
UPDATE schema_version
   SET version = '5', minor = '1';

-- This line concludes the schema upgrade to version 5.1.

-- This line starts the schema upgrade to version 6.0.

-- Create a lower case hostname index for hosts.
CREATE INDEX hosts_by_hostname ON hosts (lower(hostname))
WHERE hostname IS NOT NULL;

-- Create a hostname index for lease4.
CREATE INDEX lease4_by_hostname ON lease4 (lower(hostname))
WHERE hostname IS NOT NULL;

-- Create a hostname index for lease6.
CREATE INDEX lease6_by_hostname ON lease6 (lower(hostname))
WHERE hostname IS NOT NULL;

-- Update the schema version number.
UPDATE schema_version
    SET version = '6', minor = '0';

-- This line concludes the schema upgrade to version 6.0.

-- This line starts the schema upgrade to version 6.1.

-- Fix v4 update trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease4_update() RETURNS trigger AS $stat_lease4_update$
BEGIN
    IF OLD.subnet_id != NEW.subnet_id OR OLD.state != NEW.state THEN
        IF OLD.state < 2 THEN
            -- Decrement the old state count if record exists
            UPDATE lease4_stat SET leases = GREATEST(leases - 1, 0)
            WHERE subnet_id = OLD.subnet_id AND state = OLD.state;
        END IF;

        IF NEW.state < 2 THEN
            -- Increment the new state count if record exists
            UPDATE lease4_stat SET leases = leases + 1
            WHERE subnet_id = NEW.subnet_id AND state = NEW.state;

            -- Insert new state record if it does not exist
            IF NOT FOUND THEN
                INSERT INTO lease4_stat VALUES (NEW.subnet_id, NEW.state, 1);
            END IF;
        END IF;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease4_update$ LANGUAGE plpgsql;

--
-- Fix the v4 delete trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease4_delete() RETURNS trigger AS $stat_lease4_delete$
BEGIN
    IF OLD.state < 2 THEN
        -- Decrement the state count if record exists
        UPDATE lease4_stat SET leases = GREATEST(leases - 1, 0)
        WHERE subnet_id = OLD.subnet_id AND OLD.state = state;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease4_delete$ LANGUAGE plpgsql;

--
-- Fix v6 update trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease6_update() RETURNS trigger AS $stat_lease6_update$
BEGIN
    IF OLD.subnet_id != NEW.subnet_id OR
       OLD.lease_type != NEW.lease_type OR
       OLD.state != NEW.state THEN
        IF OLD.state < 2 THEN
            -- Decrement the old state count if record exists
            UPDATE lease6_stat SET leases = GREATEST(leases - 1, 0)
            WHERE subnet_id = OLD.subnet_id AND lease_type = OLD.lease_type
            AND state = OLD.state;
        END IF;

        IF NEW.state < 2 THEN
            -- Increment the new state count if record exists
            UPDATE lease6_stat SET leases = leases + 1
            WHERE subnet_id = NEW.subnet_id AND lease_type = NEW.lease_type
            AND state = NEW.state;

            -- Insert new state record if it does not exist
            IF NOT FOUND THEN
                INSERT INTO lease6_stat VALUES (NEW.subnet_id, NEW.lease_type, NEW.state, 1);
            END IF;
        END IF;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease6_update$ LANGUAGE plpgsql;

--
-- Fix the v6 delete trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease6_delete() RETURNS trigger AS $stat_lease6_delete$
BEGIN
    IF OLD.state < 2 THEN
        -- Decrement the state count if record exists
        UPDATE lease6_stat SET leases = GREATEST(leases - 1, 0)
        WHERE subnet_id = OLD.subnet_id AND lease_type = OLD.lease_type
        AND OLD.state = state;
    END IF;

    -- Return is ignored since this is an after insert
    RETURN NULL;
END;
$stat_lease6_delete$ LANGUAGE plpgsql;

-- Update the schema version number.
UPDATE schema_version
    SET version = '6', minor = '1';

-- This line concludes the schema upgrade to version 6.1.

-- This line starts the schema upgrade to version 6.2.

-- Starting from this version we allow specifying multiple IP reservations
-- for the same address in certain DHCP configurations. The server may check
-- uniqueness of the IP addresses on its own. This is no longer checked at
-- the database level to facilitate the use cases when a single host may
-- get the same reserved IP address via different interfaces.

-- Replace the unique index with non-unique index so the queries for
-- hosts by IPv4 address are still efficient.
DROP INDEX IF EXISTS key_dhcp4_ipv4_address_subnet_id;
CREATE INDEX key_dhcp4_ipv4_address_subnet_id
    ON hosts (ipv4_address ASC, dhcp4_subnet_id ASC);

-- Replace the unique index with non-unique index so the queries for
-- hosts by IPv6 address are still efficient.
ALTER TABLE ipv6_reservations DROP CONSTRAINT IF EXISTS key_dhcp6_address_prefix_len;
CREATE INDEX key_dhcp6_address_prefix_len
    ON ipv6_reservations (address ASC, prefix_len ASC);

-- Update the schema version number.
UPDATE schema_version
    SET version = '6', minor = '2';

-- This line concludes the schema upgrade to version 6.2.

-- This line starts the schema upgrade to version 7.0.

-- Add a lot (20+) of tables for the config backend.

-- Adding on update trigger in MySQL is as easy as using this column definition in CREATE TABLE:
-- modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
-- Sadly, Postgres has its own convoluted way of doing this. Luckily, the update pattern is
-- the same in many tables, so we can define the trigger function once and the use it everywhere.

-- First, we need to define a function that will do the actual job.
-- This is used in many, many tables.
CREATE OR REPLACE FUNCTION modification_ts_update()
  RETURNS trigger AS $modification_ts_update$
  BEGIN
    new.modification_ts = CURRENT_TIMESTAMP;
    RETURN NULL;
  END;

-- Second, we need to specify which language it was written in.
$modification_ts_update$ LANGUAGE plpgsql;

-- Create table modification and insert values for modification types.
CREATE TABLE modification (
  id smallint NOT NULL,
  modification_type VARCHAR(32) NOT NULL,
  PRIMARY KEY (id)
);
INSERT INTO modification VALUES (0,'create'), (1,'update'), (2,'delete');

-- Now create the table that holds different parameter data types.
CREATE TABLE parameter_data_type (
  id smallint NOT NULL,
  name VARCHAR(32) NOT NULL,
  PRIMARY KEY (id)
);
INSERT INTO parameter_data_type VALUES
    (0,'integer'),
    (1,'real'),
    (2,'boolean'),
    (4,'string');

-- This table doesn't exist in MySQL. However, it's nice to have an enum that explains what the values
-- in ddns_replace_client_name field in the dhcp{4,6}_shared_network table means.
CREATE TABLE ddns_replace_client_name_types (
  type INT8 PRIMARY KEY NOT NULL,
  name VARCHAR(32)
);
-- See enum ReplaceClientNameMode in src/lib/dhcpsrv/d2_client_cfg.h
INSERT INTO ddns_replace_client_name_types (type, name) VALUES
  (0, 'RCM_NEVER'),
  (1, 'RCM_ALWAYS'),
  (2, 'RCM_WHEN_PRESENT'),
  (3, 'RCM_WHEN_NOT_PRESENT');

-- Create table for DHCPv6 servers
CREATE TABLE dhcp6_server (
  id SERIAL PRIMARY KEY NOT NULL,
  tag VARCHAR(64) NOT NULL,
  description TEXT DEFAULT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE(tag)
);
CREATE INDEX dhcp6_server_idx1 ON dhcp6_server (modification_ts);
CREATE UNIQUE INDEX dhcp6_server_idx2 ON dhcp6_server(tag);
CREATE TRIGGER dhcp6_server_modification_ts_update
  AFTER UPDATE ON dhcp6_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

INSERT INTO dhcp6_server (tag, description) VALUES ('all','special type: all servers');

-- Create a table for storing IPv6 shared networks
CREATE TABLE dhcp6_shared_network (
  id SERIAL PRIMARY KEY NOT NULL,
  name VARCHAR(128) UNIQUE NOT NULL,
  client_class VARCHAR(128) DEFAULT NULL,
  interface VARCHAR(128) DEFAULT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  preferred_lifetime BIGINT DEFAULT NULL,
  rapid_commit BOOLEAN DEFAULT NULL,
  rebind_timer BIGINT DEFAULT NULL,
  relay TEXT DEFAULT NULL,
  renew_timer BIGINT DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  valid_lifetime BIGINT DEFAULT NULL,
  calculate_tee_times BOOLEAN DEFAULT NULL,
  t1_percent float DEFAULT NULL,
  t2_percent float DEFAULT NULL,
  interface_id BYTEA DEFAULT NULL, -- 128 bytes
  min_preferred_lifetime BIGINT DEFAULT NULL,
  max_preferred_lifetime BIGINT DEFAULT NULL,
  min_valid_lifetime BIGINT DEFAULT NULL,
  max_valid_lifetime BIGINT DEFAULT NULL,
  ddns_send_updates BOOLEAN DEFAULT NULL,
  ddns_override_no_update BOOLEAN DEFAULT NULL,
  ddns_override_client_update BOOLEAN DEFAULT NULL,
  ddns_replace_client_name INT8 DEFAULT NULL,
  ddns_generated_prefix VARCHAR(255) DEFAULT NULL,
  ddns_qualifying_suffix VARCHAR(255) DEFAULT NULL,
  reservations_global BOOLEAN DEFAULT NULL,
  reservations_in_subnet BOOLEAN DEFAULT NULL,
  reservations_out_of_pool BOOLEAN DEFAULT NULL,
  cache_threshold float DEFAULT NULL,
  cache_max_age BIGINT DEFAULT NULL,
  CONSTRAINT fk_ddns_replace_client_name FOREIGN KEY (ddns_replace_client_name)
    REFERENCES ddns_replace_client_name_types (type)
);
CREATE INDEX dhcp6_shared_network_idx1 ON dhcp6_shared_network (name);

CREATE TRIGGER dhcp6_shared_network_modification_ts_update
  AFTER UPDATE ON dhcp6_shared_network
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Now we need to create a relationship between defined shared networks and the servers
CREATE TABLE dhcp6_shared_network_server (
  shared_network_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (shared_network_id, server_id),
  CONSTRAINT fk_dhcp6_shared_network_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp6_server (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_shared_network_server_shared_network_id FOREIGN KEY (shared_network_id)
    REFERENCES dhcp6_shared_network (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX dhcp6_shared_network_server_idx1 ON dhcp6_shared_network_server (modification_ts);
CREATE INDEX dhcp6_shared_network_server_idx2 ON dhcp6_shared_network_server (server_id);

-- Create a list of IPv6 subnets
CREATE TABLE dhcp6_subnet (
  subnet_id BIGINT PRIMARY KEY NOT NULL,
  subnet_prefix VARCHAR(64) UNIQUE NOT NULL,
  client_class VARCHAR(128) DEFAULT NULL,
  interface VARCHAR(128) DEFAULT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  preferred_lifetime BIGINT DEFAULT NULL,
  rapid_commit BOOLEAN DEFAULT NULL,
  rebind_timer BIGINT DEFAULT NULL,
  relay TEXT DEFAULT NULL,
  renew_timer BIGINT DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  shared_network_name VARCHAR(128) DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  valid_lifetime BIGINT DEFAULT NULL,
  calculate_tee_times BOOLEAN DEFAULT NULL,
  t1_percent float DEFAULT NULL,
  t2_percent float DEFAULT NULL,
  interface_id BYTEA DEFAULT NULL,
  min_preferred_lifetime BIGINT DEFAULT NULL,
  max_preferred_lifetime BIGINT DEFAULT NULL,
  min_valid_lifetime BIGINT DEFAULT NULL,
  max_valid_lifetime BIGINT DEFAULT NULL,
  ddns_send_updates BOOLEAN DEFAULT NULL,
  ddns_override_no_update BOOLEAN DEFAULT NULL,
  ddns_override_client_update BOOLEAN DEFAULT NULL,
  ddns_replace_client_name INT8 DEFAULT NULL,
  ddns_generated_prefix VARCHAR(255) DEFAULT NULL,
  ddns_qualifying_suffix VARCHAR(255) DEFAULT NULL,
  reservations_global BOOLEAN DEFAULT NULL,
  reservations_in_subnet BOOLEAN DEFAULT NULL,
  reservations_out_of_pool BOOLEAN DEFAULT NULL,
  cache_threshold float DEFAULT NULL,
  cache_max_age BIGINT DEFAULT NULL,
  CONSTRAINT fk_dhcp6_subnet_shared_network FOREIGN KEY (shared_network_name)
    REFERENCES dhcp6_shared_network (name) ON DELETE SET NULL ON UPDATE NO ACTION,
  CONSTRAINT fk_ddns_replace_client_name FOREIGN KEY (ddns_replace_client_name)
    REFERENCES ddns_replace_client_name_types (type)
);

CREATE TRIGGER dhcp6_subnet_modification_ts_update
  AFTER UPDATE ON dhcp6_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

CREATE INDEX dhcp6_subnet_idx1 ON dhcp6_subnet (modification_ts);
CREATE INDEX dhcp6_subnet_idx2 ON dhcp6_subnet (shared_network_name);

-- Create a table that holds all address pools in IPv6.
CREATE TABLE dhcp6_pool (
  id SERIAL PRIMARY KEY NOT NULL,
  start_address inet NOT NULL,
  end_address inet NOT NULL,
  subnet_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  client_class VARCHAR(128) DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  CONSTRAINT fk_dhcp6_pool_subnet_id FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet (subnet_id)
);
CREATE INDEX dhcp6_pool_idx1 ON dhcp6_pool (modification_ts);
CREATE INDEX dhcp6_pool_idx2 ON dhcp6_pool (subnet_id);

CREATE TRIGGER dhcp6_pool_modification_ts_update
  AFTER UPDATE ON dhcp6_pool
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- And now the same, but for PD pools.
CREATE TABLE dhcp6_pd_pool (
  id SERIAL PRIMARY KEY NOT NULL,
  prefix VARCHAR(45) NOT NULL,
  prefix_length SMALLINT NOT NULL,
  delegated_prefix_length SMALLINT NOT NULL,
  subnet_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  excluded_prefix VARCHAR(45) DEFAULT NULL,
  excluded_prefix_length SMALLINT NOT NULL,
  client_class VARCHAR(128) DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  CONSTRAINT fk_dhcp6_pd_pool_subnet_id FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet(subnet_id)
);

CREATE INDEX dhcp6_pd_pool_idx1 ON dhcp6_pd_pool (modification_ts);
CREATE INDEX dhcp6_pd_pool_idx2 ON dhcp6_pd_pool (subnet_id);
CREATE TRIGGER dhcp6_pd_pool_modification_ts_update
  AFTER UPDATE ON dhcp6_pd_pool
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

CREATE TABLE dhcp6_subnet_server (
  subnet_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (subnet_id, server_id),
  CONSTRAINT fk_dhcp6_subnet_server_server_id
    FOREIGN KEY (server_id) REFERENCES dhcp6_server (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_subnet_server_subnet_id
    FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet (subnet_id) ON DELETE CASCADE ON UPDATE NO ACTION,
  UNIQUE (subnet_id, server_id)
);
CREATE INDEX dhcp6_subnet_server_idx1 ON dhcp6_subnet_server(server_id);
CREATE INDEX dhcp6_subnet_server_idx2 ON dhcp6_subnet_server(modification_ts);
CREATE TRIGGER dhcp6_subnet_server_modification_ts_update
  AFTER UPDATE ON dhcp6_subnet_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Create table for storing global DHCPv6 parameters.
CREATE TABLE dhcp6_global_parameter (
  id SERIAL PRIMARY KEY NOT NULL,
  name VARCHAR(128) NOT NULL,
  value TEXT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  parameter_type SMALLINT NOT NULL,
  CONSTRAINT fk_dhcp6_global_parameter_type FOREIGN KEY (parameter_type) REFERENCES parameter_data_type(id)
);

CREATE INDEX key_dhcp6_global_parameter_idx1 ON dhcp6_global_parameter(modification_ts);
CREATE INDEX key_dhcp6_global_parameter_idx2 ON dhcp6_global_parameter(name);

CREATE TRIGGER dhcp6_global_parameter_modification_ts_update
  AFTER UPDATE ON dhcp6_global_parameter
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

CREATE TABLE dhcp6_global_parameter_server (
  parameter_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (parameter_id, server_id),
  CONSTRAINT fk_dhcp6_global_parameter_server_parameter_id FOREIGN KEY (parameter_id)
    REFERENCES dhcp6_global_parameter(id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_global_parameter_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp6_server(id) ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE INDEX key_dhcp6_global_parameter_server_idx1 ON dhcp6_global_parameter_server(modification_ts);
CREATE TRIGGER dhcp6_global_parameter_server_modification_ts_update
  AFTER UPDATE ON dhcp6_global_parameter_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Alter table for storing DHCPv6 options.
ALTER TABLE dhcp6_options
  ADD COLUMN shared_network_name VARCHAR(128) DEFAULT NULL,
  ADD COLUMN pool_id BIGINT DEFAULT NULL,
  ADD COLUMN pd_pool_id BIGINT DEFAULT NULL,
  ADD COLUMN modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD CONSTRAINT fk_dhcp6_options_pd_pool FOREIGN KEY (pd_pool_id)
    REFERENCES dhcp6_pd_pool(id) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT fk_dhcp6_options_pool FOREIGN KEY (pool_id)
    REFERENCES dhcp6_pool (id) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT fk_dhcp6_options_shared_network FOREIGN KEY (shared_network_name)
    REFERENCES dhcp6_shared_network (name) ON DELETE CASCADE ON UPDATE CASCADE;

CREATE TRIGGER dhcp6_options_modification_ts_update
  AFTER UPDATE ON dhcp6_options
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Now create a table for associating defined options with servers.
CREATE TABLE dhcp6_options_server (
  option_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_id, server_id),
  CONSTRAINT fk_dhcp6_options_server_option_id FOREIGN KEY (option_id)
    REFERENCES dhcp6_options (option_id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_options_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp6_server (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX dhcp6_options_server_idx1 ON dhcp6_options_server(server_id);
CREATE INDEX dhcp6_options_server_idx2 ON dhcp6_options_server(modification_ts);
CREATE TRIGGER dhcp6_options_server_modification_ts_update
  AFTER UPDATE ON dhcp6_options_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- This table is for storing IPv6 option definitions
CREATE TABLE dhcp6_option_def (
  id SERIAL PRIMARY KEY UNIQUE NOT NULL,
  code SMALLINT NOT NULL,
  name VARCHAR(128) NOT NULL,
  space VARCHAR(128) NOT NULL,
  type SMALLINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  is_array BOOLEAN NOT NULL,
  encapsulate VARCHAR(128) NOT NULL,
  record_types VARCHAR DEFAULT NULL,
  user_context JSON DEFAULT NULL
);
CREATE INDEX dhcp6_option_def_idx1 ON dhcp6_option_def(modification_ts);
CREATE INDEX dhcp6_option_def_idx2 ON dhcp6_option_def(code, space);
CREATE TRIGGER dhcp6_option_def_modification_ts_update
  AFTER UPDATE ON dhcp6_option_def
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- and another table for storing relationship between option definitions and servers.
CREATE TABLE dhcp6_option_def_server (
  option_def_id BIGINT NOT NULL REFERENCES dhcp6_option_def (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  server_id BIGINT NOT NULL REFERENCES dhcp6_server (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_def_id, server_id)
);
CREATE TRIGGER dhcp6_option_def_server_modification_ts_update
  AFTER UPDATE ON dhcp6_option_def_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Now create two tables for audit revisions...
CREATE TABLE dhcp6_audit_revision (
  id SERIAL PRIMARY KEY NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  log_message TEXT DEFAULT NULL,
  server_id BIGINT DEFAULT NULL
);
CREATE TRIGGER dhcp6_audit_revision_modification_ts_update
  AFTER UPDATE ON dhcp6_audit_revision
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- ... and the DHCPv6 audit itself.
CREATE TABLE dhcp6_audit (
  id SERIAL UNIQUE NOT NULL,
  object_type VARCHAR(256) NOT NULL,
  object_id BIGINT NOT NULL,
  modification_type SMALLINT NOT NULL,
  revision_id BIGINT NOT NULL,
  CONSTRAINT fk_dhcp6_audit_modification_type FOREIGN KEY (modification_type)
    REFERENCES modification (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_audit_revision FOREIGN KEY (revision_id)
    REFERENCES dhcp6_audit_revision (id) ON DELETE NO ACTION ON UPDATE CASCADE
);
CREATE TRIGGER dhcp6_audit_modification_ts_update
  AFTER UPDATE ON dhcp6_audit
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();
CREATE INDEX dhcp6_audit_idx1 ON dhcp6_audit (modification_type);
CREATE INDEX dhcp6_audit_idx2 ON dhcp6_audit (revision_id);

-- Create table for DHCPv4 servers
CREATE TABLE dhcp4_server (
  id SERIAL PRIMARY KEY NOT NULL,
  tag VARCHAR(64) NOT NULL,
  description TEXT DEFAULT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE(tag)
);
CREATE INDEX dhcp4_server_modification_ts ON dhcp6_server (modification_ts);
CREATE TRIGGER dhcp4_server_modification_ts_update
  AFTER UPDATE ON dhcp4_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

INSERT INTO dhcp4_server (tag, description) VALUES ('all','special type: all servers');

-- Create table for storing global DHCPv4 parameters.
CREATE TABLE dhcp4_global_parameter (
  id SERIAL PRIMARY KEY NOT NULL,
  name VARCHAR(128) NOT NULL,
  value TEXT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  parameter_type SMALLINT NOT NULL,
  CONSTRAINT fk_dhcp6_global_parameter_type FOREIGN KEY (parameter_type) REFERENCES parameter_data_type(id)
);
CREATE INDEX dhcp4_global_parameter_idx1 ON dhcp4_global_parameter(modification_ts);
CREATE INDEX dhcp4_global_parameter_idx2 ON dhcp4_global_parameter(name);

CREATE TRIGGER dhcp4_global_parameter_modification_ts_update
  AFTER UPDATE ON dhcp4_global_parameter
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- and create mapping for the global DHCPv4 parameters mapping to servers
CREATE TABLE dhcp4_global_parameter_server (
  parameter_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (parameter_id, server_id),
  CONSTRAINT fk_dhcp4_global_parameter_server_parameter_id FOREIGN KEY (parameter_id)
    REFERENCES dhcp4_global_parameter(id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_global_parameter_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp4_server(id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX key_dhcp4_global_parameter_idx1 ON dhcp4_global_parameter_server(modification_ts);
CREATE TRIGGER dhcp4_global_parameter_server_modification_ts_update
  AFTER UPDATE ON dhcp4_global_parameter_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Create a table for storing IPv4 shared networks
CREATE TABLE dhcp4_shared_network (
  id SERIAL PRIMARY KEY NOT NULL,
  name VARCHAR(128) UNIQUE NOT NULL,
  client_class VARCHAR(128) DEFAULT NULL,
  interface VARCHAR(128) DEFAULT NULL,
  match_client_id BOOLEAN DEFAULT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  rebind_timer BIGINT DEFAULT NULL,
  relay TEXT DEFAULT NULL,
  renew_timer BIGINT DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  valid_lifetime BIGINT DEFAULT NULL,
  authoritative BOOLEAN DEFAULT NULL,
  calculate_tee_times BOOLEAN DEFAULT NULL,
  t1_percent float DEFAULT NULL,
  t2_percent float DEFAULT NULL,
  boot_file_name VARCHAR(128) DEFAULT NULL,
  next_server inet DEFAULT NULL,   -- let's use type inet
  server_hostname VARCHAR(64) DEFAULT NULL,
  min_valid_lifetime BIGINT DEFAULT NULL,
  max_valid_lifetime BIGINT DEFAULT NULL,
  ddns_send_updates BOOLEAN DEFAULT NULL,
  ddns_override_no_update BOOLEAN DEFAULT NULL,
  ddns_override_client_update BOOLEAN DEFAULT NULL,
  ddns_replace_client_name INT8 DEFAULT NULL,
  ddns_generated_prefix VARCHAR(255) DEFAULT NULL,
  ddns_qualifying_suffix VARCHAR(255) DEFAULT NULL,
  reservations_global BOOLEAN DEFAULT NULL,
  reservations_in_subnet BOOLEAN DEFAULT NULL,
  reservations_out_of_pool BOOLEAN DEFAULT NULL,
  cache_threshold float DEFAULT NULL,
  cache_max_age BIGINT DEFAULT NULL,
  CONSTRAINT fk_ddns_replace_client_name FOREIGN KEY (ddns_replace_client_name)
    REFERENCES ddns_replace_client_name_types (type)
);

CREATE UNIQUE INDEX dhcp4_shared_network_idx1 ON dhcp4_shared_network (name);
CREATE INDEX dhcp4_shared_network_idx2 ON dhcp4_shared_network (modification_ts);

CREATE TRIGGER dhcp4_shared_network_modification_ts_update
  AFTER UPDATE ON dhcp4_shared_network
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Now we need to create a relationship between defined shared networks and the servers
CREATE TABLE dhcp4_shared_network_server (
  shared_network_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (shared_network_id, server_id),
  CONSTRAINT fk_dhcp4_shared_network_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp4_server (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_shared_network_server_shared_network_id FOREIGN KEY (shared_network_id)
    REFERENCES dhcp4_shared_network (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX dhcp4_shared_network_server_idx1 ON dhcp4_shared_network_server (modification_ts);
CREATE INDEX dhcp4_shared_network_server_idx2 ON dhcp4_shared_network_server (server_id);

-- Create a list of IPv4 subnets
CREATE TABLE dhcp4_subnet (
  subnet_id BIGINT PRIMARY KEY NOT NULL,
  subnet_prefix VARCHAR(64) UNIQUE NOT NULL,
  interface_4o6 VARCHAR(128) DEFAULT NULL,
  interface_id_4o6 VARCHAR(128) DEFAULT NULL,
  subnet_4o6 VARCHAR(64) DEFAULT NULL,
  boot_file_name VARCHAR(128) DEFAULT NULL,
  client_class VARCHAR(128) DEFAULT NULL,
  interface VARCHAR(128) DEFAULT NULL,
  match_client_id BOOLEAN DEFAULT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  next_server inet DEFAULT NULL,
  rebind_timer BIGINT DEFAULT NULL,
  relay TEXT DEFAULT NULL,
  renew_timer BIGINT DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  server_hostname VARCHAR(64) DEFAULT NULL,
  shared_network_name VARCHAR(128) DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  valid_lifetime BIGINT DEFAULT NULL,
  authoritative BOOLEAN DEFAULT NULL,
  calculate_tee_times BOOLEAN DEFAULT NULL,
  t1_percent float DEFAULT NULL,
  t2_percent float DEFAULT NULL,
  min_valid_lifetime BIGINT DEFAULT NULL,
  max_valid_lifetime BIGINT DEFAULT NULL,
  ddns_send_updates BOOLEAN DEFAULT NULL,
  ddns_override_no_update BOOLEAN DEFAULT NULL,
  ddns_override_client_update BOOLEAN DEFAULT NULL,
  ddns_replace_client_name INT8 DEFAULT NULL,
  ddns_generated_prefix VARCHAR(255) DEFAULT NULL,
  ddns_qualifying_suffix VARCHAR(255) DEFAULT NULL,
  reservations_global BOOLEAN DEFAULT NULL,
  reservations_in_subnet BOOLEAN DEFAULT NULL,
  reservations_out_of_pool BOOLEAN DEFAULT NULL,
  cache_threshold float DEFAULT NULL,
  cache_max_age BIGINT DEFAULT NULL,
  CONSTRAINT fk_dhcp4_subnet_shared_network FOREIGN KEY (shared_network_name)
    REFERENCES dhcp4_shared_network (name) ON DELETE SET NULL ON UPDATE NO ACTION,
  CONSTRAINT fk_ddns_replace_client_name FOREIGN KEY (ddns_replace_client_name)
    REFERENCES ddns_replace_client_name_types (type)
);

CREATE TRIGGER dhcp4_subnet_modification_ts_update
  AFTER UPDATE ON dhcp4_subnet
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

CREATE INDEX dhcp4_subnet_idx1 ON dhcp4_subnet (modification_ts);
CREATE INDEX dhcp4_subnet_idx2 ON dhcp4_subnet (shared_network_name);

CREATE TABLE dhcp4_subnet_server (
  subnet_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (subnet_id, server_id),
  CONSTRAINT fk_dhcp6_subnet_server_server_id
    FOREIGN KEY (server_id) REFERENCES dhcp6_server (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_subnet_server_subnet_id
    FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet (subnet_id) ON DELETE CASCADE ON UPDATE NO ACTION,
  UNIQUE (subnet_id, server_id)
);
CREATE INDEX dhcp4_subnet_server_idx1 ON dhcp4_subnet_server(server_id);
CREATE INDEX dhcp4_subnet_server_idx2 ON dhcp4_subnet_server(modification_ts);
CREATE TRIGGER dhcp4_subnet_server_modification_ts_update
  AFTER UPDATE ON dhcp4_subnet_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Create a table that holds all address pools in IPv4.
CREATE TABLE dhcp4_pool (
  id SERIAL PRIMARY KEY NOT NULL,
  start_address inet NOT NULL,
  end_address inet NOT NULL,
  subnet_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  client_class VARCHAR(128) DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  CONSTRAINT fk_dhcp4_pool_subnet_id FOREIGN KEY (subnet_id) REFERENCES dhcp4_subnet (subnet_id)
);
CREATE INDEX dhcp4_pool_idx1 ON dhcp4_pool (modification_ts);
CREATE INDEX dhcp4_pool_idx2 ON dhcp4_pool (subnet_id);

CREATE TRIGGER dhcp4_pool_modification_ts_update
  AFTER UPDATE ON dhcp4_pool
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- ALTER table for storing DHCPv4 options.
ALTER TABLE dhcp4_options
  ADD COLUMN shared_network_name VARCHAR(128) DEFAULT NULL,
  ADD COLUMN pool_id BIGINT DEFAULT NULL,
  ADD COLUMN modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  ADD CONSTRAINT fk_dhcp4_options_pool FOREIGN KEY (pool_id)
    REFERENCES dhcp4_pool (id) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT fk_dhcp4_options_shared_network FOREIGN KEY (shared_network_name)
    REFERENCES dhcp4_shared_network (name) ON DELETE CASCADE ON UPDATE CASCADE;

CREATE TRIGGER dhcp4_options_modification_ts_update
  AFTER UPDATE ON dhcp4_options
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Now create a table for associating defined v4 options with servers.
CREATE TABLE dhcp4_options_server (
  option_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_id, server_id),
  CONSTRAINT fk_dhcp4_options_server_option_id FOREIGN KEY (option_id)
    REFERENCES dhcp4_options (option_id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_options_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp4_server (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX dhcp4_options_server_idx1 ON dhcp4_options_server(server_id);
CREATE INDEX dhcp4_options_server_idx2 ON dhcp4_options_server(modification_ts);
CREATE TRIGGER dhcp4_options_server_modification_ts_update
  AFTER UPDATE ON dhcp4_options_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- This table is for storing IPv4 option definitions
CREATE TABLE dhcp4_option_def (
  id SERIAL PRIMARY KEY UNIQUE NOT NULL,
  code SMALLINT NOT NULL,
  name VARCHAR(128) NOT NULL,
  space VARCHAR(128) NOT NULL,
  type SMALLINT NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  is_array BOOLEAN NOT NULL,
  encapsulate VARCHAR(128) NOT NULL,
  record_types VARCHAR DEFAULT NULL,
  user_context JSON DEFAULT NULL
);
CREATE INDEX dhcp4_option_def_idx1 ON dhcp4_option_def(modification_ts);
CREATE INDEX dhcp4_option_def_idx2 ON dhcp4_option_def(code, space);
CREATE TRIGGER dhcp4_option_def_modification_ts_update
  AFTER UPDATE ON dhcp4_option_def
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- and another table for storing relationship between option definitions and servers.
CREATE TABLE dhcp4_option_def_server (
  option_def_id BIGINT NOT NULL REFERENCES dhcp6_option_def (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  server_id BIGINT NOT NULL REFERENCES dhcp4_server (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_def_id, server_id)
);
CREATE TRIGGER dhcp4_option_def_server_modification_ts_update
  AFTER UPDATE ON dhcp4_option_def_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- Now create two tables for audit revisions...
CREATE TABLE dhcp4_audit_revision (
  id SERIAL PRIMARY KEY NOT NULL,
  modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
  log_message TEXT DEFAULT NULL,
  server_id BIGINT DEFAULT NULL
);
CREATE TRIGGER dhcp4_audit_revision_modification_ts_update
  AFTER UPDATE ON dhcp4_audit_revision
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- ... and the DHCPv4 audit itself.
CREATE TABLE dhcp4_audit (
  id SERIAL UNIQUE NOT NULL,
  object_type VARCHAR(256) NOT NULL,
  object_id BIGINT NOT NULL,
  modification_type SMALLINT NOT NULL,
  revision_id BIGINT NOT NULL,
  CONSTRAINT fk_dhcp4_audit_modification_type FOREIGN KEY (modification_type)
    REFERENCES modification (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_audit_revision FOREIGN KEY (revision_id)
    REFERENCES dhcp4_audit_revision (id) ON DELETE NO ACTION ON UPDATE CASCADE
);
CREATE TRIGGER dhcp4_audit_modification_ts_update
  AFTER UPDATE ON dhcp4_audit
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();
CREATE INDEX dhcp4_audit_idx1 ON dhcp4_audit (modification_type);
CREATE INDEX dhcp4_audit_idx2 ON dhcp4_audit (revision_id);

-- Stores a TEXT value to a session variable
-- name name of session variable to set
-- value TEXT value to store
CREATE OR REPLACE FUNCTION set_session_value(name text, value TEXT)
RETURNS VOID
AS $$
DECLARE
BEGIN
    PERFORM set_config(name, value, false);
    RETURN;

    EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'set_session_value(%) : value:[%] failed, sqlstate: %', name, value, sqlstate;
END;$$
LANGUAGE plpgsql;

-- Stores a BIGINT value to a session variable
-- Note the value converted to TEXT and then stored as Postgresql does
-- not support any other data type in session variables.
-- name name of session variable to set
-- value BIGINT value to store
CREATE OR REPLACE FUNCTION set_session_value(name text, value BIGINT)
RETURNS VOID
AS $$
BEGIN
    PERFORM set_config(name, cast(value as text), false);
    RETURN;

    EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'set_session_value(%) : value:[%] failed, sqlstate: %', name, value, sqlstate;
END;$$
LANGUAGE plpgsql;

-- Stores a BOOLEAN value to a session variable
-- Note the value converted to TEXT and then stored as Postgresql does
-- not support any other data type in session variables.
-- name name of session variable to set
-- value BOOLEAN value to store
CREATE OR REPLACE FUNCTION set_session_value(name text, value BOOLEAN)
RETURNS VOID
AS $$
BEGIN
    PERFORM set_config(name, cast(value as text), false);
    RETURN;

    EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'set_session_value(%) : value:[%] failed, sqlstate: %', name, value, sqlstate;
END;$$
LANGUAGE plpgsql;

-- Fetches a text value from the session configuration.
-- param name name of the session variable to fetch
-- If the name is not found it returns NULL.
-- Postgresql allows you to store custom session values
-- but throws an exception if they have not first been
-- set.  This allows us to be a bit more graceful.
CREATE OR REPLACE FUNCTION get_session_value(name TEXT)
RETURNS TEXT
AS $$
DECLARE
    text_value TEXT := '';
BEGIN
    text_value = current_setting(name);
    RETURN(text_value);

    EXCEPTION
    WHEN undefined_object THEN
        -- Variable has not been initialized so return NULL
        RETURN NULL;
    WHEN OTHERS THEN
        RAISE EXCEPTION 'get_session_value(%, TEXT) failed, sqlstate: %', name, sqlstate;
END;$$
LANGUAGE plpgsql;

-- Fetches an BIGINT value from the session configuration.
-- param name name of the session variable to fetch
-- If the name is not found it returns zero.
CREATE OR REPLACE FUNCTION get_session_big_int(name text)
RETURNS BIGINT
AS $$
DECLARE
    int_value BIGINT := 0;
    text_value TEXT := '';
BEGIN
    text_value = get_session_value(name);
    IF text_value is NULL or text_value = '' THEN
        RETURN(0);
    END IF;

    int_value = cast(text_value as BIGINT);
    RETURN(int_value);

    EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'get_session_big_int(%) failed - text:[%] , sqlstate: %', name, text_value, sqlstate;

END;$$
LANGUAGE plpgsql;

-- Fetches an BOOLEAN value from the session configuration.
-- param name name of the session variable to fetch
-- If the name is not found it returns zero.
CREATE OR REPLACE FUNCTION get_session_boolean(name text)
RETURNS BOOLEAN
AS $$
DECLARE
    bool_value BOOLEAN := false;
    text_value TEXT := '';
BEGIN
    text_value = get_session_value(name);
    IF text_value is NULL or text_value = '' THEN
        RETURN(false);
    END IF;

    bool_value = cast(text_value as BOOLEAN);
    RETURN(bool_value);

    EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'get_session_boolean(%) failed - text:[%] , sqlstate: %', name, text_value, sqlstate;

END;$$
LANGUAGE plpgsql;

-- -----------------------------------------------------
-- Stored procedure which creates a new entry in the
-- dhcp4_audit_revision table and sets appropriate session
-- variables to be used while creating the audit entries
-- by triggers. This procedure should be called at the
-- beginning of a transaction which modifies configuration
-- data in the database, e.g. when new subnet is added.
--
-- Parameters:
-- - audit_ts timestamp to be associated with the audit
--   revision.
-- - server_tag is used to retrieve the server_id which
--   associates the changes applied with the particular
--   server or all servers.
-- - audit_log_message is a log message associates with
--   the audit revision.
-- - cascade_transaction is assigned to a session
--   variable which is used in some triggers to determine
--   if the audit entry should be created for them or
--   not. Specifically, this is used when DHCP options
--   are inserted, updated or deleted. If such modification
--   is a part of the larger change (e.g. change in the
--   subnet the options belong to) the dedicated audit
--   entry for options must not be created. On the other
--   hand, if the global option is being added, the
--   audit entry for the option must be created because
--   it is the sole object modified in that case.
--   Session variable disable_audit is used to disable
--   the procedure when wiping the database during
--   unit tests.  This avoids issues with revision_id
--   being null.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createAuditRevisionDHCP4(audit_ts TIMESTAMP WITH TIME ZONE,
                                                    server_tag VARCHAR(64),
                                                    audit_log_message TEXT,
                                                    cascade_transaction BOOLEAN)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    disable_audit BOOLEAN := false;
    audit_revision_id BIGINT;
    srv_id BIGINT;
BEGIN
    -- Fetch session value for disable_audit.
    disable_audit := get_session_boolean('kea.disable_audit');
    IF disable_audit = false THEN
        SELECT id INTO srv_id FROM dhcp4_server WHERE tag = server_tag;
        INSERT INTO dhcp4_audit_revision (modification_ts, server_id, log_message)
            VALUES (audit_ts, srv_id, audit_log_message) returning id INTO audit_revision_id;

        -- Update pertinent session variables.
        PERFORM set_session_value('kea.audit_revision_id', audit_revision_id);
        PERFORM set_session_value('kea.cascade_transaction', cascade_transaction);
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------
-- Stored procedure which creates a new entry in the
-- dhcp4_audit table. It should be called from the
-- triggers of the tables where the config modifications
-- are applied. The audit_revision_id variable contains
-- the revision id to be placed in the audit entries.
--
-- The following parameters are passed to this procedure:
-- - object_type_val: name of the table to be associated
--   with the applied changes.
-- - object_id_val: identifier of the modified object in
--   that table.
-- - modification_type_val: string value indicating the
--   type of the change, i.e. 'create', 'update' or
--   'delete'.
--   Session variable disable_audit is used to disable
--   the procedure when wiping the database during
--   unit tests.  This avoids issues with revision_id
--   being null.
-- ----------------------------------------------------
CREATE OR REPLACE FUNCTION createAuditEntryDHCP4(object_type_val VARCHAR(256),
                                                 object_id_val BIGINT,
                                                 modification_type_val VARCHAR(32))
RETURNS VOID
LANGUAGE plpgsql
as $$
DECLARE
    audit_revision_id BIGINT;
    disable_audit BOOLEAN := false;
BEGIN
    -- Fetch session value for disable_audit.
    disable_audit := get_session_boolean('kea.disable_audit');

    IF disable_audit IS NULL OR disable_audit = false THEN
        -- Fetch session value most recently created audit_revision_id.
        audit_revision_id := get_session_big_int('kea.audit_revision_id');
        INSERT INTO dhcp4_audit (object_type, object_id, modification_type, revision_id)
            VALUES (object_type_val, object_id_val,
                (SELECT id FROM modification WHERE modification_type = modification_type_val),
                 audit_revision_id);
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Create a table holding the DHCPv4 client classes. Most table
-- columns map directly to respective client class properties in
-- Kea configuration. The depend_on_known_directly column is
-- explicitly set in an insert or update statement to indicate
-- if the client class directly depends on KNOWN or UNKNOWN
-- built-in classes. A caller should determine it by evaluating
-- a test expression before inserting or updating the client
-- class in the database. The nullable follow_class_name column
-- can be used for positioning the inserted or updated client
-- class within the class hierarchy. Set this column value to
-- an existing class name, after which this class should be
-- placed in the class hierarchy. See dhcp4_client_class_order
-- description for the details of how classes are ordered.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp4_client_class (
    id SERIAL PRIMARY KEY NOT NULL,
    name VARCHAR(128) UNIQUE NOT NULL,
    test TEXT,
    next_server INET DEFAULT NULL,
    server_hostname VARCHAR(128) DEFAULT NULL,
    boot_file_name VARCHAR(512) DEFAULT NULL,
    only_if_required BOOLEAN NOT NULL DEFAULT false,
    valid_lifetime BIGINT DEFAULT NULL,
    min_valid_lifetime BIGINT DEFAULT NULL,
    max_valid_lifetime BIGINT DEFAULT NULL,
    depend_on_known_directly BOOLEAN NOT NULL DEFAULT false,
    follow_class_name VARCHAR(128) DEFAULT NULL,
    modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX key_dhcp4_client_class_modification_ts on dhcp4_client_class (modification_ts);

-- -----------------------------------------------------------------------
-- Create a table for ordering client classes and holding information
-- about indirect dependencies on KNOWN/UKNOWN built-in client classes.
-- Each class in the dhcp4_client_class table has a corresponding row
-- in the dhcp4_client_class_order table. A caller should not modify
-- the contents of this table. Its entries are automatically created
-- upon inserting or updating client classes in the dhcp4_client_classes
-- using triggers. The order_index designates the position of the client
-- class within the class hierarchy. If the follow_class_name value of
-- the dhcp4_client_class table is set to NULL, the client class is
-- appended at the end of the hierarchy. The assigned order_index
-- value for that class is set to a maximum current value + 1.
-- If the follow_client_class specifies a name of an existing class,
-- the generated order_index is set to an id of that class + 1, and
-- the order_index values of the later classes are incremented by 1.
-- The depend_on_known_indirectly column holds a boolean value indicating
-- whether the given class depends on KNOWN/UKNOWN built-in classes
-- via other classes, i.e. it depends on classes that directly or
-- indirectly depend on these built-ins. This value is auto-generated
-- by a trigger on the dhcp4_client_class_dependency table.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp4_client_class_order (
    class_id BIGINT PRIMARY KEY NOT NULL,
    order_index BIGINT NOT NULL,
    depend_on_known_indirectly BOOLEAN NOT NULL DEFAULT false,
    CONSTRAINT fk_dhcp4_client_class_order_class_id FOREIGN KEY (class_id)
        REFERENCES dhcp4_client_class (id) ON DELETE CASCADE
);

CREATE INDEX key_dhcp4_client_class_order_index on dhcp4_client_class_order (order_index);

-- -----------------------------------------------------------------------
-- Stored procedure positioning an inserted or updated client class
-- within the class hierarchy, depending on the value of the
-- follow_class_name parameter.
--
-- Parameters:
-- - id id of the positioned class,
-- - follow_class_name name of the class after which this class should be
--   positioned within the class hierarchy.
-- - old_follow_class_name previous name of the class after which this
--   class was positioned within the class hierarchy.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION setClientClass4Order(id BIGINT,
                                                new_follow_class_name VARCHAR(128),
                                                old_follow_class_name VARCHAR(128))
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- Used to fetch class's current value for depend_on_known_indirectly
    l_depend_on_known_indirectly BIGINT := 0;

    -- Optionally set if the follow_class_name column value is specified.
    follow_class_index BIGINT;
BEGIN
    -- Fetch the class's current value of depend_on_known_indirectly.
    SELECT depend_on_known_indirectly INTO l_depend_on_known_indirectly
        FROM dhcp4_client_class_order WHERE id = class_id;

    -- Save it to the current session for use elsewhere during this transaction.
    -- Note this does not work prior to Postgres 9.2 unless the variables are
    -- defined in postgresql.conf. I think for now we put up with CB not supported
    -- prior to 9.2 or we tell people how to edit the conf file.
    PERFORM set_session_value('kea.depend_on_known_indirectly', l_depend_on_known_indirectly);

    -- Bail if the class is updated without re-positioning.
    IF(
       l_depend_on_known_indirectly IS NOT NULL AND
       ((new_follow_class_name IS NULL AND old_follow_class_name IS NULL) OR
        (new_follow_class_name = old_follow_class_name))
    ) THEN
        -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
        -- whenever the dhcp4_client_class record is updated. Such update may include
        -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
        -- This value will be later adjusted when dependencies are inserted.
        -- TKM should we update the session value also or is it moot?
        UPDATE dhcp4_client_class_order SET depend_on_known_indirectly = false
            WHERE class_id = id;
        RETURN;
    END IF;

    IF new_follow_class_name IS NOT NULL THEN
        -- Get the position of the class after which the new class should be added.
        SELECT o.order_index INTO follow_class_index
            FROM dhcp4_client_class AS c
            INNER JOIN dhcp4_client_class_order AS o
                ON c.id = o.class_id
            WHERE c.name = new_follow_class_name;

        IF follow_class_index IS NULL THEN
            -- The class with a name specified with new_follow_class_name does
            -- not exist.
            RAISE EXCEPTION 'Class %s does not exist.', new_follow_class_name
                USING ERRCODE = 'sql_routine_exception';
        END IF;

        -- We need to place the new class at the position of follow_class_index + 1.
        -- There may be a class at this position already.
        IF EXISTS(SELECT * FROM dhcp4_client_class_order WHERE order_index = follow_class_index + 1) THEN
            -- There is a class at this position already. Let's move all classes
            -- starting from this position by one to create a spot for the new
            -- class.
            UPDATE dhcp4_client_class_order
                SET order_index = order_index + 1
            WHERE order_index >= follow_class_index + 1;
            -- TKM postgresql doesn't like order by here, does it matter?
            -- ORDER BY order_index DESC;
        END IF;

    ELSE
        -- A caller did not specify the new_follow_class_name value. Let's append the
        -- new class at the end of the hierarchy.
        SELECT MAX(order_index) INTO follow_class_index FROM dhcp4_client_class_order;
        IF follow_class_index IS NULL THEN
            -- Apparently, there are no classes. Let's start from 0.
            follow_class_index = 0;
        END IF;
    END IF;

    -- Check if moving the class doesn't break dependent classes.
    IF EXISTS(
        SELECT 1 FROM dhcp4_client_class_dependency AS d
            INNER JOIN dhcp4_client_class_order AS o
                ON d.class_id = o.class_id
            WHERE d.dependency_id = id AND o.order_index < follow_class_index + 1
        LIMIT 1
    ) THEN
        RAISE EXCEPTION 'Unable to move class with id %s because it would break its dependencies', id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
    -- whenever the dhcp4_client_class record is updated. Such update may include
    -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
    -- This value will be later adjusted when dependencies are inserted.
    -- ON CONFLICT required 9.5 or later
    UPDATE dhcp4_client_class_order
        SET order_index = follow_class_index + 1,
            depend_on_known_indirectly = l_depend_on_known_indirectly
        WHERE class_id = id;
    IF FOUND THEN
        RETURN;
    END IF;

    INSERT INTO  dhcp4_client_class_order(class_id, order_index, depend_on_known_indirectly)
        VALUES (id, follow_class_index + 1, 0);
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Trigger procedure to position an inserted class within the class hierarchy
-- and create audit.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp4_client_class_AINS() RETURNS trigger AS $dhcp4_client_class_AINS$
BEGIN
    PERFORM setClientClass4Order(NEW.id, NEW.follow_class_name, NULL);
    PERFORM createAuditEntryDHCP4('dhcp4_client_class', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp4_client_class_AINS$
LANGUAGE plpgsql;

-- Create dhcp4_client_class insert trigger
CREATE TRIGGER dhcp4_client_class_AINS
    AFTER INSERT ON dhcp4_client_class
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_client_class_AINS();

-- -----------------------------------------------------------------------
-- Trigger to position an updated class within the class hierarchy,
-- create audit and remember the direct dependency on the
-- KNOWN/UNKNOWN built-in classes before the class update.
-- When updating a client class, it is very important to ensure that
-- its dependency on KNOWN or UNKNOWN built-in client classes is not
-- changed. It is because there may be other classes that depend on
-- these built-ins via this class. Changing the dependency would break
-- the chain of dependencies for other classes. Here, we store the
-- information about the dependency in the session variables. Their
-- values will be compared with the new dependencies after an update.
-- If they change, an error will be signaled.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp4_client_class_AUPD() RETURNS trigger AS $dhcp4_client_class_AUPD$
BEGIN
    PERFORM set_session_value('kea.depend_on_known_directly', OLD.depend_on_known_directly);
    PERFORM set_session_value('kea.client_class_id', NEW.id);
    PERFORM setClientClass4Order(NEW.id, NEW.follow_class_name, OLD.follow_class_name);
    PERFORM createAuditEntryDHCP4('dhcp4_client_class', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp4_client_class_AUPD$
LANGUAGE plpgsql;

-- Create dhcp4_client_class update insert trigger
CREATE TRIGGER dhcp4_client_class_AUPD
    AFTER UPDATE ON dhcp4_client_class
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_client_class_AUPD();

-- -----------------------------------------------------------------------
-- Trigger procedure to create the audit entry for client class delete.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp4_client_class_ADEL() RETURNS trigger AS $dhcp4_client_class_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_client_class', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp4_client_class_ADEL$
LANGUAGE plpgsql;

-- Create dhcp4_client_class delete trigger
CREATE TRIGGER dhcp4_client_class_ADEL
    AFTER DELETE ON dhcp4_client_class
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_client_class_ADEL();

-- -----------------------------------------------------------------------
-- Create a table associating client classes stored in the
-- dhcp4_client_class table with their dependencies. There is
-- an M:N relationship between these tables. Each class may have
-- many dependencies (created using member operator in test expression),
-- and each class may be a dependency for many other classes. A caller
-- is responsible for inserting dependencies for a class after inserting
-- or updating it in the dhcp4_client_class table. A caller should
-- delete all existing dependencies for an updated client class, evaluate
-- test expression to discover new dependencies (in case test expression
-- has changed), and insert new dependencies to this table.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp4_client_class_dependency (
    class_id BIGINT PRIMARY KEY NOT NULL,
    dependency_id BIGINT NOT NULL,

    CONSTRAINT dhcp4_client_class_class_id FOREIGN KEY (class_id)
        REFERENCES dhcp4_client_class (id) ON DELETE CASCADE,
    CONSTRAINT dhcp4_client_class_dependency_id FOREIGN KEY (dependency_id)
        REFERENCES dhcp4_client_class (id)
);

CREATE INDEX dhcp4_client_class_dependency_id_idx on dhcp4_client_class_dependency (dependency_id);

-- -----------------------------------------------------------------------
-- Stored procedure verifying if class dependency is met. It includes
-- checking if referenced classes exist, are associated with the same
-- server or all servers, and are defined before the class specified with
-- class_id.
--
-- Parameters:
-- - p_class_id id client class,
-- - p_dependency_id id of the dependency.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION checkDHCPv4ClientClassDependency(p_class_id BIGINT,
                                                            p_dependency_id BIGINT)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    class_index BIGINT;
    dependency_index BIGINT;
BEGIN
    -- We could check the same with a constraint but later in this
    -- trigger we use this value to verify if the dependencies are
    -- met.
    IF p_class_id IS NULL THEN
        RAISE EXCEPTION 'Client class id must not be NULL.'
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    IF p_dependency_id IS NULL THEN
        RAISE EXCEPTION 'Class dependency id must not be NULL.'
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Dependencies on self make no sense.
    IF p_class_id = p_dependency_id THEN
        RAISE EXCEPTION 'Client class must not have dependency on self.'
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Check position of our class in the hierarchy.
    SELECT o.order_index INTO class_index FROM dhcp4_client_class AS c
        INNER JOIN dhcp4_client_class_order AS o ON c.id = o.class_id
        WHERE c.id = p_class_id;

    IF class_index IS NULL THEN
        RAISE EXCEPTION 'Client class with id % does not exist.', p_class_id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Check position of the dependency.
    SELECT o.order_index INTO dependency_index FROM dhcp4_client_class AS c
        INNER JOIN dhcp4_client_class_order AS o ON c.id = o.class_id
        WHERE c.id = p_dependency_id;

    IF dependency_index IS NULL THEN
        RAISE EXCEPTION 'Dependency class with id % does not exist.', p_dependency_id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- The dependency must not be later than our class.
    IF dependency_index > class_index THEN
        RAISE EXCEPTION
            'Client class with id % must not depend on class defined later with id %',
            p_class_id, p_dependency_id USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Check if all servers associated with the new class have dependent
    -- classes configured. This catches the cases that class A belongs to
    -- server1 and depends on class B which belongs only to server 2.
    -- It is fine if the class B belongs to all servers in this case.
    -- Make a SELECT on the dhcp4_client_class_server table to gather
    -- all servers to which the class belongs. LEFT JOIN it with the
    -- same table, selecting all records matching the dependency class
    -- and the servers to which the new class belongs. If there are
    -- any NULL records joined it implies that some dependencies are
    -- not met (didn't find a dependency for at least one server).
    IF EXISTS(
        SELECT 1 FROM dhcp4_client_class_server AS t1
            LEFT JOIN dhcp4_client_class_server AS t2
                ON t2.class_id = p_dependency_id AND (t2.server_id = 1 OR t2.server_id = t1.server_id)
        WHERE t1.class_id = p_class_id AND t2.server_id IS NULL
        LIMIT 1
    ) THEN
        RAISE EXCEPTION 'Unmet dependencies for client class with id %', class_id
            USING ERRCODE = 'sql_routine_exception';
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Trigger verifying if class dependency is met. It includes checking
-- if referenced classes exist, are associated with the same server
-- or all servers, and are defined before the class specified with
-- class_id.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp4_client_class_check_dependency_BINS()
    RETURNS trigger AS $dhcp4_client_class_check_dependency_BINS$
BEGIN
    PERFORM checkDHCPv4ClientClassDependency(NEW.class_id, NEW.dependency_id);
    RETURN NULL;
END;
$dhcp4_client_class_check_dependency_BINS$
LANGUAGE plpgsql;

-- Create dhcp4_client_class_check_dependency_BINS before insert trigger.
CREATE TRIGGER dhcp4_client_class_check_dependency_BINS
    BEFORE INSERT ON dhcp4_client_class_dependency
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_client_class_check_dependency_BINS();

-- -----------------------------------------------------------------------
-- Stored procedure setting client class indirect dependency on KNOWN or
-- UNKNOWN built-in classes by checking this flag for the client classes
-- on which it depends.
--
-- Parameters:
-- - client_class_id id of the client class which dependency is set,
-- - dependency_id id of the client class on which the given class depends.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION updateDHCPv4ClientClassKnownDependency(client_class_id BIGINT,
                                                                  dependency_id BIGINT)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    dependency BOOLEAN;
BEGIN
    -- Check if the dependency class references KNOWN/UNKNOWN.
    SELECT depend_on_known_directly INTO dependency FROM dhcp4_client_class
        WHERE id = dependency_id;

    -- If it doesn't, check if the dependency references KNOWN/UNKNOWN
    -- indirectly (via other classes).
    IF dependency = false THEN
        SELECT depend_on_known_indirectly INTO dependency FROM dhcp4_client_class_order
            WHERE class_id = dependency_id;
    END IF;

    IF dependency = true THEN
        UPDATE dhcp4_client_class_order
            SET depend_on_known_indirectly = true
        WHERE class_id = client_class_id;
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Trigger setting client class indirect dependency on KNOWN or UNKNOWN
-- built-in classes by checking this flag for the client classes on which
-- it depends.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp4_client_class_dependency_AINS()
    RETURNS TRIGGER AS $dhcp4_client_class_dependency_AINS$
BEGIN
    PERFORM updateDHCPv4ClientClassKnownDependency(NEW.class_id, NEW.dependency_id);
    RETURN NULL;
END;
$dhcp4_client_class_dependency_AINS$
LANGUAGE plpgsql;

-- Create dhcp4_client_class_check_dependency_AINS after insert trigger.
CREATE TRIGGER dhcp4_client_class_dependency_AINS
    AFTER INSERT ON dhcp4_client_class_dependency
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_client_class_dependency_AINS();

-- -----------------------------------------------------------------------
-- Stored procedure to be executed before committing a transaction
-- updating a DHCPv4 client class. It verifies if the class dependency on
-- KNOWN or UNKNOWN built-in classes has changed as a result of the
-- update. It signals an error if it has changed and there is at least
-- one class depending on this class.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION checkDHCPv4ClientClassKnownDependencyChange()
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    depended BOOLEAN := false;
    depends BOOLEAN := false;
    client_class_id BIGINT;
    depend_on_known_directly BOOLEAN;
    depend_on_known_indirectly BOOLEAN;
BEGIN

    -- Session variables are set upon a client class update.
    client_class_id := get_session_big_int('kea.client_class_id');
    IF client_class_id IS NOT NULL THEN
        -- Check if any of the classes depend on this class. If not,
        -- it is ok to change the dependency on KNOWN/UNKNOWN.
        IF EXISTS(
            SELECT 1 FROM dhcp4_client_class_dependency
            WHERE dependency_id = client_class_id LIMIT 1
        ) THEN
            -- Using the session variables, determine whether the client class
            -- depended on KNOWN/UNKNOWN before the update.
            depend_on_known_directly := get_session_boolean('kea.depend_on_known_directly');
            depend_on_known_indirectly := get_session_boolean('kea.depend_on_known_indirectly');
            IF depend_on_known_directly = true OR depend_on_known_indirectly = true THEN
                SET depended = true;
            END IF;

            -- Check if the client class depends on KNOWN/UNKNOWN after the update.
            SELECT depend_on_known_directly INTO depends FROM dhcp4_client_class
                WHERE id = client_class_id;

            -- If it doesn't depend directly, check indirect dependencies.
            IF depends = false THEN
                SELECT depend_on_known_indirectly INTO depends FROM dhcp4_client_class_order
                    WHERE class_id = client_class_id;
            END IF;

            -- The resulting dependency on KNOWN/UNKNOWN must not change.
            IF depended <> depends THEN
                RAISE EXCEPTION 'Class dependency on KNOWN/UNKNOWN built-in classes must not change.'
                    USING ERRCODE = 'sql_routine_exception';
            END IF;
        END IF;
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Create table matching DHCPv4 classes with the servers.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp4_client_class_server (
    class_id BIGINT NOT NULL,
    server_id BIGINT NOT NULL,
    modification_ts  TIMESTAMP WITH TIME ZONE NULL DEFAULT NULL,
    PRIMARY KEY (class_id,server_id),
    CONSTRAINT fk_dhcp4_client_class_class_id FOREIGN KEY (class_id)
        REFERENCES dhcp4_client_class (id)
        ON DELETE CASCADE,
    CONSTRAINT fk_dhcp4_client_class_server_id FOREIGN KEY (server_id)
        REFERENCES dhcp4_server (id)
);

CREATE INDEX fk_dhcp4_client_class_server_id ON dhcp4_client_class_server (server_id);

-- -----------------------------------------------------
-- Stored procedure which creates a new entry in the
-- dhcp6_audit_revision table and sets appropriate session
-- variables to be used while creating the audit entries
-- by triggers. This procedure should be called at the
-- beginning of a transaction which modifies configuration
-- data in the database, e.g. when new subnet is added.
--
-- Parameters:
-- - audit_ts timestamp to be associated with the audit
--   revision.
-- - server_tag is used to retrieve the server_id which
--   associates the changes applied with the particular
--   server or all servers.
-- - audit_log_message is a log message associates with
--   the audit revision.
-- - cascade_transaction is assigned to a session
--   variable which is used in some triggers to determine
--   if the audit entry should be created for them or
--   not. Specifically, this is used when DHCP options
--   are inserted, updated or deleted. If such modification
--   is a part of the larger change (e.g. change in the
--   subnet the options belong to) the dedicated audit
--   entry for options must not be created. On the other
--   hand, if the global option is being added, the
--   audit entry for the option must be created because
--   it is the sole object modified in that case.
--   Session variable disable_audit is used to disable
--   the procedure when wiping the database during
--   unit tests.  This avoids issues with revision_id
--   being null.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createAuditRevisionDHCP6(audit_ts TIMESTAMP WITH TIME ZONE,
                                                    server_tag VARCHAR(64),
                                                    audit_log_message TEXT,
                                                    cascade_transaction BOOLEAN)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    disable_audit BOOLEAN := false;
    audit_revision_id BIGINT;
    srv_id BIGINT;
BEGIN
    -- Fetch session value for disable_audit.
    disable_audit := get_session_boolean('kea.disable_audit');
    IF disable_audit = false THEN
        SELECT id INTO srv_id FROM dhcp6_server WHERE tag = server_tag;
        INSERT INTO dhcp6_audit_revision (modification_ts, server_id, log_message)
            VALUES (audit_ts, srv_id, audit_log_message) returning id INTO audit_revision_id;

        -- Update pertinent session variables.
        PERFORM set_session_value('kea.audit_revision_id', audit_revision_id);
        PERFORM set_session_value('kea.cascade_transaction', cascade_transaction);
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------
-- Stored procedure which creates a new entry in the
-- dhcp6_audit table. It should be called from the
-- triggers of the tables where the config modifications
-- are applied. The audit_revision_id variable contains
-- the revision id to be placed in the audit entries.
--
-- The following parameters are passed to this procedure:
-- - object_type_val: name of the table to be associated
--   with the applied changes.
-- - object_id_val: identifier of the modified object in
--   that table.
-- - modification_type_val: string value indicating the
--   type of the change, i.e. 'create', 'update' or
--   'delete'.
--   Session variable disable_audit is used to disable
--   the procedure when wiping the database during
--   unit tests.  This avoids issues with revision_id
--   being null.
-- ----------------------------------------------------
CREATE OR REPLACE FUNCTION createAuditEntryDHCP6(object_type_val VARCHAR(256),
                                                 object_id_val BIGINT,
                                                 modification_type_val VARCHAR(32))
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    audit_revision_id BIGINT;
    disable_audit BOOLEAN := false;
BEGIN
    -- Fetch session value for disable_audit.
    disable_audit := get_session_boolean('kea.disable_audit');
    IF disable_audit = false THEN
        -- Fetch session value most recently created audit_revision_id.
        audit_revision_id := get_session_big_int('kea.audit_revision_id');
        INSERT INTO dhcp6_audit (object_type, object_id, modification_type, revision_id)
            VALUES (object_type_val, object_id_val,
                (SELECT id FROM modification WHERE modification_type = modification_type_val),
                 audit_revision_id);
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Create a table holding the DHCPv6 client classes. Most table
-- columns map directly to respective client class properties in
-- Kea configuration. The depend_on_known_directly column is
-- explicitly set in an insert or update statement to indicate
-- if the client class directly depends on KNOWN or UNKNOWN
-- built-in classes. A caller should determine it by evaluating
-- a test expression before inserting or updating the client
-- class in the database. The nullable follow_class_name column
-- can be used for positioning the inserted or updated client
-- class within the class hierarchy. Set this column value to
-- an existing class name, after which this class should be
-- placed in the class hierarchy. See dhcp6_client_class_order
-- description for the details of how classes are ordered.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp6_client_class (
    id SERIAL PRIMARY KEY NOT NULL,
    name VARCHAR(128) UNIQUE NOT NULL,
    test TEXT,
    only_if_required BOOLEAN NOT NULL DEFAULT false,
    valid_lifetime BIGINT DEFAULT NULL,
    min_valid_lifetime BIGINT DEFAULT NULL,
    max_valid_lifetime BIGINT DEFAULT NULL,
    depend_on_known_directly BOOLEAN NOT NULL DEFAULT false,
    follow_class_name VARCHAR(128) DEFAULT NULL,
    modification_ts TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX key_dhcp6_client_class_modification_ts on dhcp6_client_class (modification_ts);

-- -----------------------------------------------------------------------
-- Create a table for ordering client classes and holding information
-- about indirect dependencies on KNOWN/UKNOWN built-in client classes.
-- Each class in the dhcp6_client_class table has a corresponding row
-- in the dhcp6_client_class_order table. A caller should not modify
-- the contents of this table. Its entries are automatically created
-- upon inserting or updating client classes in the dhcp6_client_classes
-- using triggers. The order_index designates the position of the client
-- class within the class hierarchy. If the follow_class_name value of
-- the dhcp6_client_class table is set to NULL, the client class is
-- appended at the end of the hierarchy. The assigned order_index
-- value for that class is set to a maximum current value + 1.
-- If the follow_client_class specifies a name of an existing class,
-- the generated order_index is set to an id of that class + 1, and
-- the order_index values of the later classes are incremented by 1.
-- The depend_on_known_indirectly column holds a boolean value indicating
-- whether the given class depends on KNOWN/UKNOWN built-in classes
-- via other classes, i.e. it depends on classes that directly or
-- indirectly depend on these built-ins. This value is auto-generated
-- by a trigger on the dhcp6_client_class_dependency table.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp6_client_class_order (
    class_id BIGINT PRIMARY KEY NOT NULL,
    order_index BIGINT NOT NULL,
    depend_on_known_indirectly BOOLEAN NOT NULL DEFAULT false,
    CONSTRAINT fk_dhcp6_client_class_order_class_id FOREIGN KEY (class_id)
        REFERENCES dhcp6_client_class (id) ON DELETE CASCADE
);

CREATE INDEX key_dhcp6_client_class_order_index on dhcp6_client_class_order (order_index);

-- -----------------------------------------------------------------------
-- Stored procedure positioning an inserted or updated client class
-- within the class hierarchy, depending on the value of the
-- new_follow_class_name parameter.
--
-- Parameters:
-- - id id of the positioned class,
-- - new_follow_class_name name of the class after which this class should be
--   positioned within the class hierarchy.
-- - old_follow_class_name previous name of the class after which this
--   class was positioned within the class hierarchy.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION setClientClass6Order(id BIGINT,
                                                new_follow_class_name VARCHAR(128),
                                                old_follow_class_name VARCHAR(128))
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- Used to fetch class's current value for depend_on_known_indirectly
    l_depend_on_known_indirectly BIGINT := 0;

    -- Optionally set if the follow_class_name column value is specified.
    follow_class_index BIGINT;
BEGIN
    -- Fetch the class's current value of depend_on_known_indirectly.
    SELECT depend_on_known_indirectly INTO l_depend_on_known_indirectly
        FROM dhcp6_client_class_order WHERE id = class_id;

    -- Save it to the current session for use elsewhere during this transaction.
    -- Note this does not work prior to Postgres 9.2 unless the variables are
    -- defined in postgresql.conf. I think for now we put up with CB not supported
    -- prior to 9.2 or we tell people how to edit the conf file.
    PERFORM set_session_value('kea.depend_on_known_indirectly', l_depend_on_known_indirectly);

    -- Bail if the class is updated without re-positioning.
    IF(
       l_depend_on_known_indirectly IS NOT NULL AND
       ((new_follow_class_name IS NULL AND old_follow_class_name IS NULL) OR
        (new_follow_class_name = old_follow_class_name))
    ) THEN
        -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
        -- whenever the dhcp6_client_class record is updated. Such update may include
        -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
        -- This value will be later adjusted when dependencies are inserted.
        -- TKM should we update the session value also or is it moot?
        UPDATE dhcp6_client_class_order SET depend_on_known_indirectly = false
            WHERE class_id = id;
        RETURN;
    END IF;

    IF new_follow_class_name IS NOT NULL THEN
        -- Get the position of the class after which the new class should be added.
        SELECT o.order_index INTO follow_class_index
            FROM dhcp6_client_class AS c
            INNER JOIN dhcp6_client_class_order AS o
                ON c.id = o.class_id
            WHERE c.name = new_follow_class_name;

        IF follow_class_index IS NULL THEN
            -- The class with a name specified with new_follow_class_name does
            -- not exist.
            RAISE EXCEPTION 'Class %s does not exist.', new_follow_class_name
                USING ERRCODE = 'sql_routine_exception';
        END IF;

        -- We need to place the new class at the position of follow_class_index + 1.
        -- There may be a class at this position already.
        IF EXISTS(SELECT * FROM dhcp6_client_class_order WHERE order_index = follow_class_index + 1) THEN
            -- There is a class at this position already. Let's move all classes
            -- starting from this position by one to create a spot for the new
            -- class.
            UPDATE dhcp6_client_class_order
                SET order_index = order_index + 1
            WHERE order_index >= follow_class_index + 1;
            -- TKM postgresql doesn't like order by here, does it matter?
            -- ORDER BY order_index DESC;
        END IF;

    ELSE
        -- A caller did not specify the new_follow_class_name value. Let's append the
        -- new class at the end of the hierarchy.
        SELECT MAX(order_index) INTO follow_class_index FROM dhcp6_client_class_order;
        IF follow_class_index IS NULL THEN
            -- Apparently, there are no classes. Let's start from 0.
            follow_class_index = 0;
        END IF;
    END IF;

    -- Check if moving the class doesn't break dependent classes.
    IF EXISTS(
        SELECT 1 FROM dhcp6_client_class_dependency AS d
            INNER JOIN dhcp6_client_class_order AS o
                ON d.class_id = o.class_id
            WHERE d.dependency_id = id AND o.order_index < follow_class_index + 1
        LIMIT 1
    ) THEN
        RAISE EXCEPTION 'Unable to move class with id %s because it would break its dependencies', id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
    -- whenever the dhcp6_client_class record is updated. Such update may include
    -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
    -- This value will be later adjusted when dependencies are inserted.
    -- TKM - note that ON CONFLICT requires PostgreSQL 9.5 or later.
    UPDATE dhcp6_client_class_order
        SET order_index = follow_class_index + 1,
            depend_on_known_indirectly = l_depend_on_known_indirectly
        WHERE class_id = id;
    IF FOUND THEN
        RETURN;
    END IF;

    INSERT INTO  dhcp6_client_class_order(class_id, order_index, depend_on_known_indirectly)
        VALUES (id, follow_class_index + 1, 0);
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Trigger procedure to position an inserted class within the class hierarchy
-- and create audit.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp6_client_class_AINS() RETURNS trigger AS $dhcp6_client_class_AINS$
BEGIN
    PERFORM setClientClass6Order(NEW.id, NEW.follow_class_name, NULL);
    PERFORM createAuditEntryDHCP6('dhcp6_client_class', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp6_client_class_AINS$
LANGUAGE plpgsql;

-- Create dhcp6_client_class insert trigger
CREATE TRIGGER dhcp6_client_class_AINS
    AFTER INSERT ON dhcp6_client_class
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_client_class_AINS();

-- -----------------------------------------------------------------------
-- Trigger to position an updated class within the class hierarchy,
-- create audit and remember the direct dependency on the
-- KNOWN/UNKNOWN built-in classes before the class update.
-- When updating a client class, it is very important to ensure that
-- its dependency on KNOWN or UNKNOWN built-in client classes is not
-- changed. It is because there may be other classes that depend on
-- these built-ins via this class. Changing the dependency would break
-- the chain of dependencies for other classes. Here, we store the
-- information about the dependency in the session variables. Their
-- values will be compared with the new dependencies after an update.
-- If they change, an error will be signaled.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp6_client_class_AUPD() RETURNS trigger AS $dhcp6_client_class_AUPD$
BEGIN
    PERFORM set_session_value('kea.depend_on_known_directly', OLD.depend_on_known_directly);
    PERFORM set_session_value('kea.client_class_id', NEW.id);
    PERFORM setClientClass6Order(NEW.id, NEW.follow_class_name, OLD.follow_class_name);
    PERFORM createAuditEntryDHCP6('dhcp6_client_class', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp6_client_class_AUPD$
LANGUAGE plpgsql;

-- Create dhcp6_client_class update insert trigger
CREATE TRIGGER dhcp6_client_class_AUPD
    AFTER UPDATE ON dhcp6_client_class
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_client_class_AUPD();

-- -----------------------------------------------------------------------
-- Trigger procedure to create the audit entry for client class delete.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp6_client_class_ADEL() RETURNS trigger AS $dhcp6_client_class_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_client_class', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp6_client_class_ADEL$
LANGUAGE plpgsql;

-- Create dhcp6_client_class delete trigger
CREATE TRIGGER dhcp6_client_class_ADEL
    AFTER DELETE ON dhcp6_client_class
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_client_class_ADEL();

-- -----------------------------------------------------------------------
-- Create a table associating client classes stored in the
-- dhcp6_client_class table with their dependencies. There is
-- an M:N relationship between these tables. Each class may have
-- many dependencies (created using member operator in test expression),
-- and each class may be a dependency for many other classes. A caller
-- is responsible for inserting dependencies for a class after inserting
-- or updating it in the dhcp6_client_class table. A caller should
-- delete all existing dependencies for an updated client class, evaluate
-- test expression to discover new dependencies (in case test expression
-- has changed), and insert new dependencies to this table.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp6_client_class_dependency (
    class_id BIGINT PRIMARY KEY NOT NULL,
    dependency_id BIGINT NOT NULL,

    CONSTRAINT dhcp6_client_class_class_id FOREIGN KEY (class_id)
        REFERENCES dhcp6_client_class (id) ON DELETE CASCADE,
    CONSTRAINT dhcp6_client_class_dependency_id FOREIGN KEY (dependency_id)
        REFERENCES dhcp6_client_class (id)
);

CREATE INDEX dhcp6_client_class_dependency_id_idx on dhcp6_client_class_dependency (dependency_id);

-- -----------------------------------------------------------------------
-- Stored procedure verifying if class dependency is met. It includes
-- checking if referenced classes exist, are associated with the same
-- server or all servers, and are defined before the class specified with
-- class_id.
--
-- Parameters:
-- - p_class_id id client class,
-- - p_dependency_id id of the dependency.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION checkDHCPv6ClientClassDependency(p_class_id BIGINT,
                                                            p_dependency_id BIGINT)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    class_index BIGINT;
    dependency_index BIGINT;
BEGIN
    -- We could check the same with a constraint but later in this
    -- trigger we use this value to verify if the dependencies are
    -- met.
    IF p_class_id IS NULL THEN
        RAISE EXCEPTION 'Client class id must not be NULL.'
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    IF p_dependency_id IS NULL THEN
        RAISE EXCEPTION 'Class dependency id must not be NULL.'
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Dependencies on self make no sense.
    IF p_class_id = p_dependency_id THEN
        RAISE EXCEPTION 'Client class must not have dependency on self.'
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Check position of our class in the hierarchy.
    SELECT o.order_index INTO class_index FROM dhcp6_client_class AS c
        INNER JOIN dhcp6_client_class_order AS o ON c.id = o.class_id
        WHERE c.id = p_class_id;

    IF class_index IS NULL THEN
        RAISE EXCEPTION 'Client class with id % does not exist.', p_class_id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Check position of the dependency.
    SELECT o.order_index INTO dependency_index FROM dhcp6_client_class AS c
        INNER JOIN dhcp6_client_class_order AS o ON c.id = o.class_id
        WHERE c.id = p_dependency_id;

    IF dependency_index IS NULL THEN
        RAISE EXCEPTION 'Dependency class with id % does not exist.', p_dependency_id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- The dependency must not be later than our class.
    IF dependency_index > class_index THEN
        RAISE EXCEPTION
            'Client class with id % must not depend on class defined later with id %',
            p_class_id, p_dependency_id USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- Check if all servers associated with the new class have dependent
    -- classes configured. This catches the cases that class A belongs to
    -- server1 and depends on class B which belongs only to server 2.
    -- It is fine if the class B belongs to all servers in this case.
    -- Make a SELECT on the dhcp6_client_class_server table to gather
    -- all servers to which the class belongs. LEFT JOIN it with the
    -- same table, selecting all records matching the dependency class
    -- and the servers to which the new class belongs. If there are
    -- any NULL records joined it implies that some dependencies are
    -- not met (didn't find a dependency for at least one server).
    IF EXISTS(
        SELECT 1 FROM dhcp6_client_class_server AS t1
            LEFT JOIN dhcp6_client_class_server AS t2
                ON t2.class_id = p_dependency_id AND (t2.server_id = 1 OR t2.server_id = t1.server_id)
        WHERE t1.class_id = p_class_id AND t2.server_id IS NULL
        LIMIT 1
    ) THEN
        RAISE EXCEPTION 'Unmet dependencies for client class with id %', p_class_id
            USING ERRCODE = 'sql_routine_exception';
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Trigger verifying if class dependency is met. It includes checking
-- if referenced classes exist, are associated with the same server
-- or all servers, and are defined before the class specified with
-- class_id.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp6_client_class_check_dependency_BINS()
    RETURNS trigger AS $dhcp6_client_class_check_dependency_BINS$
BEGIN
    PERFORM checkDHCPv6ClientClassDependency(NEW.class_id, NEW.dependency_id);
    RETURN NULL;
END;
$dhcp6_client_class_check_dependency_BINS$
LANGUAGE plpgsql;

-- Create dhcp6_client_class_check_dependency_BINS before insert trigger.
CREATE TRIGGER dhcp6_client_class_check_dependency_BINS
    BEFORE INSERT ON dhcp6_client_class_dependency
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_client_class_check_dependency_BINS();

-- -----------------------------------------------------------------------
-- Stored procedure setting client class indirect dependency on KNOWN or
-- UNKNOWN built-in classes by checking this flag for the client classes
-- on which it depends.
--
-- Parameters:
-- - client_class_id id of the client class which dependency is set,
-- - dependency_id id of the client class on which the given class depends.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION updateDHCPv6ClientClassKnownDependency(client_class_id BIGINT,
                                                                  dependency_id BIGINT)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    dependency BOOLEAN;
BEGIN
    -- Check if the dependency class references KNOWN/UNKNOWN.
    SELECT depend_on_known_directly INTO dependency FROM dhcp6_client_class
        WHERE id = dependency_id;

    -- If it doesn't, check if the dependency references KNOWN/UNKNOWN
    -- indirectly (via other classes).
    IF dependency = false THEN
        SELECT depend_on_known_indirectly INTO dependency FROM dhcp6_client_class_order
            WHERE class_id = dependency_id;
    END IF;

    IF dependency = true THEN
        UPDATE dhcp6_client_class_order
            SET depend_on_known_indirectly = true
        WHERE class_id = client_class_id;
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Trigger setting client class indirect dependency on KNOWN or UNKNOWN
-- built-in classes by checking this flag for the client classes on which
-- it depends.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp6_client_class_dependency_AINS()
    RETURNS TRIGGER AS $dhcp6_client_class_dependency_AINS$
BEGIN
    PERFORM updateDHCPv6ClientClassKnownDependency(NEW.class_id, NEW.dependency_id);
    RETURN NULL;
END;
$dhcp6_client_class_dependency_AINS$
LANGUAGE plpgsql;

-- Create dhcp6_client_class_check_dependency_AINS after insert trigger.
CREATE TRIGGER dhcp6_client_class_dependency_AINS
    AFTER INSERT ON dhcp6_client_class_dependency
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_client_class_dependency_AINS();

-- -----------------------------------------------------------------------
-- Stored procedure to be executed before committing a transaction
-- updating a DHCPv6 client class. It verifies if the class dependency on
-- KNOWN or UNKNOWN built-in classes has changed as a result of the
-- update. It signals an error if it has changed and there is at least
-- one class depending on this class.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION checkDHCPv6ClientClassKnownDependencyChange()
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    depended BOOLEAN := false;
    depends BOOLEAN := false;
    client_class_id BIGINT;
    depend_on_known_directly BOOLEAN;
    depend_on_known_indirectly BOOLEAN;
BEGIN

    -- Session variables are set upon a client class update.
    client_class_id := get_session_big_int('kea.client_class_id');
    IF client_class_id IS NOT NULL THEN
        -- Check if any of the classes depend on this class. If not,
        -- it is ok to change the dependency on KNOWN/UNKNOWN.
        IF EXISTS(
            SELECT 1 FROM dhcp6_client_class_dependency
            WHERE dependency_id = client_class_id LIMIT 1
        ) THEN
            -- Using the session variables, determine whether the client class
            -- depended on KNOWN/UNKNOWN before the update.
            depend_on_known_directly := get_session_boolean('kea.depend_on_known_directly');
            depend_on_known_indirectly := get_session_boolean('kea.depend_on_known_indirectly');
            IF depend_on_known_directly = true OR depend_on_known_indirectly = true THEN
                SET depended = true;
            END IF;

            -- Check if the client class depends on KNOWN/UNKNOWN after the update.
            SELECT depend_on_known_directly INTO depends FROM dhcp6_client_class
                WHERE id = client_class_id;

            -- If it doesn't depend directly, check indirect dependencies.
            IF depends = false THEN
                SELECT depend_on_known_indirectly INTO depends FROM dhcp6_client_class_order
                    WHERE class_id = client_class_id;
            END IF;

            -- The resulting dependency on KNOWN/UNKNOWN must not change.
            IF depended <> depends THEN
                RAISE EXCEPTION 'Class dependency on KNOWN/UNKNOWN built-in classes must not change.'
                    USING ERRCODE = 'sql_routine_exception';
            END IF;
        END IF;
    END IF;
    RETURN;
END;$$;

-- -----------------------------------------------------------------------
-- Create table matching DHCPv6 classes with the servers.
-- -----------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS dhcp6_client_class_server (
    class_id BIGINT NOT NULL,
    server_id BIGINT NOT NULL,
    modification_ts  TIMESTAMP WITH TIME ZONE NULL DEFAULT NULL,
    PRIMARY KEY (class_id,server_id),
    CONSTRAINT fk_dhcp6_client_class_class_id FOREIGN KEY (class_id)
        REFERENCES dhcp6_client_class (id)
        ON DELETE CASCADE,
    CONSTRAINT fk_dhcp6_client_class_server_id FOREIGN KEY (server_id)
        REFERENCES dhcp6_server (id)
);

CREATE INDEX fk_dhcp6_client_class_server_id ON dhcp6_client_class_server (server_id);

-- Trigger function for dhcp4_pool_BDEL called BEFORE DELETE on dhcp4_pool
-- It removes pool specific options upon removal of the pool.
CREATE OR REPLACE FUNCTION func_dhcp4_pool_BDEL() RETURNS TRIGGER AS $dhcp4_pool_BDEL$
BEGIN
    DELETE FROM dhcp4_options WHERE scope_id = 5 AND pool_id = OLD.id;
    RETURN OLD;
END;
$dhcp4_pool_BDEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_pool_BDEL
    BEFORE DELETE ON dhcp4_pool
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_pool_BDEL();

-- Trigger function for dhcp6_pool_BDEL called BEFORE DELETE on dhcp6_pool
-- It removes pool specific options upon removal of the pool.
CREATE OR REPLACE FUNCTION func_dhcp6_pool_BDEL() RETURNS TRIGGER AS $dhcp6_pool_BDEL$
BEGIN
    DELETE FROM dhcp6_options WHERE scope_id = 5 AND pool_id = OLD.id;
    RETURN OLD;
END;
$dhcp6_pool_BDEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_pool_BDEL
    BEFORE DELETE ON dhcp6_pool
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_pool_BDEL();

-- Trigger function for dhcp4_global_parameter_AINS called AFTER INSERT on dhcp4_global_parameter
CREATE OR REPLACE FUNCTION func_dhcp4_global_parameter_AINS() RETURNS TRIGGER AS $dhcp4_global_parameter_AINS$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_global_parameter', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp4_global_parameter_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_global_parameter_AINS
    AFTER INSERT ON dhcp4_global_parameter
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_global_parameter_AINS();

-- Trigger function for dhcp4_global_parameter_AUPD called AFTER UPDATE on dhcp4_global_parameter
CREATE OR REPLACE FUNCTION func_dhcp4_global_parameter_AUPD() RETURNS TRIGGER AS $dhcp4_global_parameter_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_global_parameter', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp4_global_parameter_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_global_parameter_AUPD
    AFTER UPDATE ON dhcp4_global_parameter
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_global_parameter_AUPD();

-- Trigger function for dhcp4_global_parameter_ADEL called AFTER DELETE on dhcp4_global_parameter
CREATE OR REPLACE FUNCTION func_dhcp4_global_parameter_ADEL() RETURNS TRIGGER AS $dhcp4_global_parameter_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_global_parameter', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp4_global_parameter_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_global_parameter_ADEL
    AFTER DELETE ON dhcp4_global_parameter
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_global_parameter_ADEL();

-- Trigger function for dhcp4_subnet_AINS called AFTER INSERT on dhcp4_subnet
CREATE OR REPLACE FUNCTION func_dhcp4_subnet_AINS() RETURNS TRIGGER AS $dhcp4_subnet_AINS$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_subnet', NEW.subnet_id, 'create');
    RETURN NULL;
END;
$dhcp4_subnet_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_subnet_AINS
    AFTER INSERT ON dhcp4_subnet
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_subnet_AINS();

-- Trigger function for dhcp4_subnet_AUPD called AFTER UPDATE on dhcp4_subnet
CREATE OR REPLACE FUNCTION func_dhcp4_subnet_AUPD() RETURNS TRIGGER AS $dhcp4_subnet_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_subnet', NEW.subnet_id, 'update');
    RETURN NULL;
END;
$dhcp4_subnet_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_subnet_AUPD
    AFTER UPDATE ON dhcp4_subnet
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_subnet_AUPD();

-- Trigger function for dhcp4_shared_network_AINS called AFTER INSERT on dhcp4_shared_network
CREATE OR REPLACE FUNCTION func_dhcp4_shared_network_AINS() RETURNS TRIGGER AS $dhcp4_shared_network_AINS$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_shared_network', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp4_shared_network_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_shared_network_AINS
    AFTER INSERT ON dhcp4_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_shared_network_AINS();

-- Trigger function for dhcp4_shared_network_AUPD called AFTER UPDATE on dhcp4_shared_network
CREATE OR REPLACE FUNCTION func_dhcp4_shared_network_AUPD() RETURNS TRIGGER AS $dhcp4_shared_network_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_shared_network', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp4_shared_network_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_shared_network_AUPD
    AFTER UPDATE ON dhcp4_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_shared_network_AUPD();

-- Trigger function for dhcp4_shared_network_ADEL called AFTER DELETE on dhcp4_shared_network
CREATE OR REPLACE FUNCTION func_dhcp4_shared_network_ADEL() RETURNS TRIGGER AS $dhcp4_shared_network_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_shared_network', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp4_shared_network_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_shared_network_ADEL
    AFTER DELETE ON dhcp4_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_shared_network_ADEL();

-- Trigger function for dhcp4_option_def_AINS called AFTER INSERT on dhcp4_option_def
CREATE OR REPLACE FUNCTION func_dhcp4_option_def_AINS() RETURNS TRIGGER AS $dhcp4_option_def_AINS$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_option_def', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp4_option_def_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_option_def_AINS
    AFTER INSERT ON dhcp4_option_def
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_option_def_AINS();

-- Trigger function for dhcp4_option_def_AUPD called AFTER UPDATE on dhcp4_option_def
CREATE OR REPLACE FUNCTION func_dhcp4_option_def_AUPD() RETURNS TRIGGER AS $dhcp4_option_def_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_option_def', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp4_option_def_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_option_def_AUPD
    AFTER UPDATE ON dhcp4_option_def
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_option_def_AUPD();

-- Trigger function for dhcp4_option_def_ADEL called AFTER DELETE on dhcp4_option_def
CREATE OR REPLACE FUNCTION func_dhcp4_option_def_ADEL() RETURNS TRIGGER AS $dhcp4_option_def_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_option_def', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp4_option_def_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_option_def_ADEL
    AFTER DELETE ON dhcp4_option_def
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_option_def_ADEL();

-- -----------------------------------------------------
--
-- Stored procedure which updates modification timestamp of
-- a parent object when an option is modified.
--
-- The following parameters are passed to the procedure:
-- - modification_type: 'create', 'update' or 'delete'
-- - scope_id: identifier of the option scope, e.g.
--   global, subnet specific etc.
-- - option_id: identifier of the option.
-- - p_subnet_id: identifier of the subnet if the option
--   belongs to the subnet.
-- - host_id: identifier of the host if the option
-- - belongs to the host.
-- - network_name: shared network name if the option
--   belongs to the shared network.
-- - pool_id: identifier of the pool if the option
--   belongs to the pool.
-- - p_modification_ts: modification timestamp of the
--   option.
--   Some arguments are prefixed with "p_" to avoid ambiguity
--   with column names in SQL statements. PostgreSQL does not
--   allow table aliases to be used with column names in update
--   set expressions.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createOptionAuditDHCP4(modification_type VARCHAR,
                                                  scope_id SMALLINT,
                                                  option_id INT,
                                                  p_subnet_id BIGINT,
                                                  host_id INT,
                                                  network_name VARCHAR,
                                                  pool_id BIGINT,
                                                  p_modification_ts TIMESTAMP WITH TIME ZONE)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- These variables will hold shared network id and subnet id that
    -- we will select.
    snid VARCHAR(128);
    sid BIGINT;
    cascade_transaction BOOLEAN := true;
    ct TEXT;
BEGIN
    -- Cascade transaction flag is set to true to prevent creation of
    -- the audit entries for the options when the options are
    -- created as part of the parent object creation or update.
    -- For example: when the option is added as part of the subnet
    -- addition, the cascade transaction flag is equal to true. If
    -- the option is added into the existing subnet the cascade
    -- transaction is equal to false. Note that depending on the option
    -- scope the audit entry will contain the object_type value
    -- of the parent object to cause the server to replace the
    -- entire subnet. The only case when the object_type will be
    -- set to 'dhcp4_options' is when a global option is added.
    -- Global options do not have the owner.

    cascade_transaction := get_session_boolean('kea.cascade_transaction');
    IF cascade_transaction = false THEN
        -- todo: host manager hasn't been updated to use audit
        -- mechanisms so ignore host specific options for now.
        IF scope_id = 0 THEN
            -- If a global option is added or modified, create audit
            -- entry for the 'dhcp4_options' table.
            PERFORM createAuditEntryDHCP4('dhcp4_options', option_id, modification_type);
        ELSEIF scope_id = 1 THEN
            -- If subnet specific option is added or modified, update
            -- the modification timestamp of this subnet to allow the
            -- servers to refresh the subnet information. This will
            -- also result in creating an audit entry for this subnet.
            UPDATE dhcp4_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = p_subnet_id;
        ELSEIF scope_id = 4 THEN
            -- If shared network specific option is added or modified,
            -- update the modification timestamp of this shared network
            -- to allow the servers to refresh the shared network
            -- information. This will also result in creating an
            -- audit entry for this shared network.
           SELECT id INTO snid FROM dhcp4_shared_network WHERE name = network_name LIMIT 1;
           UPDATE dhcp4_shared_network SET modification_ts = p_modification_ts
                WHERE id = snid;
        ELSEIF scope_id = 5 THEN
            -- If pool specific option is added or modified, update
            -- the modification timestamp of the owning subnet.
            SELECT dhcp4_pool.subnet_id INTO sid FROM dhcp4_pool WHERE id = pool_id;
            UPDATE dhcp4_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        END IF;
    END IF;
    RETURN;
END;$$;

-- Trigger function for dhcp4_options_AINS called AFTER INSERT on dhcp4_options
CREATE OR REPLACE FUNCTION func_dhcp4_options_AINS() RETURNS TRIGGER AS $dhcp4_options_AINS$
BEGIN
    PERFORM createOptionAuditDHCP4('create', NEW.scope_id, NEW.option_id, NEW.dhcp4_subnet_id,
                                   NEW.host_id, NEW.shared_network_name, NEW.pool_id,
                                   NEW.modification_ts);
    RETURN NULL;
END;
$dhcp4_options_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_options_AINS
    AFTER INSERT ON dhcp4_options
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_options_AINS();

-- Trigger function for dhcp4_options_AUPD called AFTER UPDATE on dhcp4_options
CREATE OR REPLACE FUNCTION func_dhcp4_options_AUPD() RETURNS TRIGGER AS $dhcp4_options_AUPD$
BEGIN
    PERFORM createOptionAuditDHCP4('update', NEW.scope_id, NEW.option_id, NEW.dhcp4_subnet_id,
                                   NEW.host_id, NEW.shared_network_name, NEW.pool_id,
                                   NEW.modification_ts);
    RETURN NULL;
END;
$dhcp4_options_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_options_AUPD
    AFTER UPDATE ON dhcp4_options
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_options_AUPD();

-- Trigger function for dhcp4_options_ADEL called AFTER DELETE on dhcp4_options
CREATE OR REPLACE FUNCTION func_dhcp4_options_ADEL() RETURNS TRIGGER AS $dhcp4_options_ADEL$
BEGIN
    PERFORM createOptionAuditDHCP4('delete', OLD.scope_id, OLD.option_id, OLD.dhcp4_subnet_id,
                                   OLD.host_id, OLD.shared_network_name, OLD.pool_id,
                                   NOW());
    RETURN NULL;
END;
$dhcp4_options_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_options_ADEL
    AFTER DELETE ON dhcp4_options
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_options_ADEL();

-- Trigger function for dhcp6_global_parameter_AINS called AFTER INSERT on dhcp6_global_parameter
CREATE OR REPLACE FUNCTION func_dhcp6_global_parameter_AINS() RETURNS TRIGGER AS $dhcp6_global_parameter_AINS$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_global_parameter', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp6_global_parameter_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_global_parameter_AINS
    AFTER INSERT ON dhcp6_global_parameter
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_global_parameter_AINS();

-- Trigger function for dhcp6_global_parameter_AUPD called AFTER UPDATE on dhcp6_global_parameter
CREATE OR REPLACE FUNCTION func_dhcp6_global_parameter_AUPD() RETURNS TRIGGER AS $dhcp6_global_parameter_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_global_parameter', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp6_global_parameter_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_global_parameter_AUPD
    AFTER UPDATE ON dhcp6_global_parameter
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_global_parameter_AUPD();

-- Trigger function for dhcp6_global_parameter_ADEL called AFTER DELETE on dhcp6_global_parameter
CREATE OR REPLACE FUNCTION func_dhcp6_global_parameter_ADEL() RETURNS TRIGGER AS $dhcp6_global_parameter_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_global_parameter', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp6_global_parameter_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_global_parameter_ADEL
    AFTER DELETE ON dhcp6_global_parameter
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_global_parameter_ADEL();

-- Trigger function for dhcp6_subnet_AINS called AFTER INSERT on dhcp6_subnet
CREATE OR REPLACE FUNCTION func_dhcp6_subnet_AINS() RETURNS TRIGGER AS $dhcp6_subnet_AINS$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_subnet', NEW.subnet_id, 'create');
    RETURN NULL;
END;
$dhcp6_subnet_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_subnet_AINS
    AFTER INSERT ON dhcp6_subnet
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_subnet_AINS();

-- Trigger function for dhcp6_subnet_AUPD called AFTER UPDATE on dhcp6_subnet
CREATE OR REPLACE FUNCTION func_dhcp6_subnet_AUPD() RETURNS TRIGGER AS $dhcp6_subnet_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_subnet', NEW.subnet_id, 'update');
    RETURN NULL;
END;
$dhcp6_subnet_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_subnet_AUPD
    AFTER UPDATE ON dhcp6_subnet
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_subnet_AUPD();

-- Trigger function for dhcp6_shared_network_AINS called AFTER INSERT on dhcp6_shared_network
CREATE OR REPLACE FUNCTION func_dhcp6_shared_network_AINS() RETURNS TRIGGER AS $dhcp6_shared_network_AINS$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_shared_network', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp6_shared_network_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_shared_network_AINS
    AFTER INSERT ON dhcp6_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_shared_network_AINS();

-- Trigger function for dhcp6_shared_network_AUPD called AFTER UPDATE on dhcp6_shared_network
CREATE OR REPLACE FUNCTION func_dhcp6_shared_network_AUPD() RETURNS TRIGGER AS $dhcp6_shared_network_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_shared_network', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp6_shared_network_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_shared_network_AUPD
    AFTER UPDATE ON dhcp6_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_shared_network_AUPD();

-- Trigger function for dhcp6_shared_network_ADEL called AFTER DELETE on dhcp6_shared_network
CREATE OR REPLACE FUNCTION func_dhcp6_shared_network_ADEL() RETURNS TRIGGER AS $dhcp6_shared_network_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_shared_network', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp6_shared_network_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_shared_network_ADEL
    AFTER DELETE ON dhcp6_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_shared_network_ADEL();

-- Trigger function for dhcp6_option_def_AINS called AFTER INSERT on dhcp6_option_def
CREATE OR REPLACE FUNCTION func_dhcp6_option_def_AINS() RETURNS TRIGGER AS $dhcp6_option_def_AINS$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_option_def', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp6_option_def_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_option_def_AINS
    AFTER INSERT ON dhcp6_option_def
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_option_def_AINS();

-- Trigger function for dhcp6_option_def_AUPD called AFTER UPDATE on dhcp6_option_def
CREATE OR REPLACE FUNCTION func_dhcp6_option_def_AUPD() RETURNS TRIGGER AS $dhcp6_option_def_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_option_def', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp6_option_def_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_option_def_AUPD
    AFTER UPDATE ON dhcp6_option_def
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_option_def_AUPD();

-- Trigger function for dhcp6_option_def_ADEL called AFTER DELETE on dhcp6_option_def
CREATE OR REPLACE FUNCTION func_dhcp6_option_def_ADEL() RETURNS TRIGGER AS $dhcp6_option_def_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_option_def', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp6_option_def_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_option_def_ADEL
    AFTER DELETE ON dhcp6_option_def
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_option_def_ADEL();

-- - pool_id: identifier of the pool if the option
--   belongs to the pool.
-- - pd_pool_id: identifier of the pool if the option
--   belongs to the pd pool.
-- - modification_ts: modification timestamp of the
--   option.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createOptionAuditDHCP6(modification_type VARCHAR(32),
                                                  scope_id SMALLINT,
                                                  option_id INT,
                                                  subnet_id BIGINT,
                                                  host_id INT,
                                                  network_name VARCHAR(128),
                                                  pool_id BIGINT,
                                                  pd_pool_id BIGINT,
                                                  modification_ts TIMESTAMP WITH TIME ZONE)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- These variables will hold shared network id and subnet id that
    -- we will select.
    snid VARCHAR(128);
    sid BIGINT;
    cascade_transaction BOOLEAN := false;

BEGIN
    -- Cascade transaction flag is set to true to prevent creation of
    -- the audit entries for the options when the options are
    -- created as part of the parent object creation or update.
    -- For example: when the option is added as part of the subnet
    -- addition, the cascade transaction flag is equal to true. If
    -- the option is added into the existing subnet the cascade
    -- transaction is equal to false. Note that depending on the option
    -- scope the audit entry will contain the object_type value
    -- of the parent object to cause the server to replace the
    -- entire subnet. The only case when the object_type will be
    -- set to 'dhcp6_options' is when a global option is added.
    -- Global options do not have the owner.
    cascade_transaction := get_session_boolean('kea.cascade_transaction');
    IF cascade_transaction = false THEN
        -- todo: host manager hasn't been updated to use audit
        -- mechanisms so ignore host specific options for now.
        IF scope_id = 0 THEN
            -- If a global option is added or modified, create audit
            -- entry for the 'dhcp6_options' table.
            PERFORM createAuditEntryDHCP6('dhcp6_options', option_id, modification_type);
        ELSEIF scope_id = 1 THEN
            -- If subnet specific option is added or modified, create
            -- audit entry for the entire subnet, which indicates that
            -- it should be treated as the subnet update.
            PERFORM createAuditEntryDHCP6('dhcp6_subnet', subnet_id, 'update');
        ELSEIF scope_id = 4 THEN
            -- If shared network specific option is added or modified,
            -- create audit entry for the shared network which
            -- indicates that it should be treated as the shared
            -- network update.
           SELECT id INTO snid FROM dhcp6_shared_network
                WHERE name = network_name LIMIT 1;
           PERFORM createAuditEntryDHCP6('dhcp6_shared_network', snid, 'update');
        ELSEIF scope_id = 5 THEN
            -- If pool specific option is added or modified, create
            -- audit entry for the subnet which this pool belongs to.
            SELECT dhcp6_pool.subnet_id INTO sid FROM dhcp6_pool WHERE id = pool_id;
            PERFORM createAuditEntryDHCP6('dhcp6_subnet', sid, 'update');
        ELSEIF scope_id = 6 THEN
            -- If pd pool specific option is added or modified, create
            -- audit entry for the subnet which this pd pool belongs to.
            SELECT dhcp6_pd_pool.subnet_id INTO sid FROM dhcp6_pd_pool
                WHERE id = pd_pool_id;
            PERFORM createAuditEntryDHCP6('dhcp6_subnet', sid, 'update');
        END IF;
    END IF;
    RETURN;
END;$$;

-- Trigger function for dhcp6_options_AINS called AFTER INSERT on dhcp6_options
CREATE OR REPLACE FUNCTION func_dhcp6_options_AINS() RETURNS TRIGGER AS $dhcp6_options_AINS$
BEGIN
    PERFORM createOptionAuditDHCP6('create', NEW.scope_id, NEW.option_id, NEW.dhcp6_subnet_id,
                                   NEW.host_id, NEW.shared_network_name, NEW.pool_id,
                                   NEW.pd_pool_id, NEW.modification_ts);
    RETURN NULL;
END;
$dhcp6_options_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_options_AINS
    AFTER INSERT ON dhcp6_options
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_options_AINS();

-- Trigger function for dhcp6_options_AUPD called AFTER UPDATE on dhcp6_options
CREATE OR REPLACE FUNCTION func_dhcp6_options_AUPD() RETURNS TRIGGER AS $dhcp6_options_AUPD$
BEGIN
    PERFORM createOptionAuditDHCP6('update', NEW.scope_id, NEW.option_id, NEW.dhcp6_subnet_id,
                                   NEW.host_id, NEW.shared_network_name, NEW.pool_id,
                                   NEW.pd_pool_id, NEW.modification_ts);
    RETURN NULL;
END;
$dhcp6_options_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_options_AUPD
    AFTER UPDATE ON dhcp6_options
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_options_AUPD();

-- Trigger function for dhcp6_options_ADEL called AFTER DELETE on dhcp6_options
CREATE OR REPLACE FUNCTION func_dhcp6_options_ADEL() RETURNS TRIGGER AS $dhcp6_options_ADEL$
BEGIN
    PERFORM createOptionAuditDHCP6('delete', OLD.scope_id, OLD.option_id, OLD.dhcp6_subnet_id,
                                   OLD.host_id, OLD.shared_network_name, OLD.pool_id,
                                   OLD.pd_pool_id, NOW());
    RETURN NULL;
END;
$dhcp6_options_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_options_ADEL
    AFTER DELETE ON dhcp6_options
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_options_ADEL();

-- Trigger function for dhcp4_server_AINS called AFTER INSERT on dhcp4_server
CREATE OR REPLACE FUNCTION func_dhcp4_server_AINS() RETURNS TRIGGER AS $dhcp4_server_AINS$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_server', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp4_server_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_server_AINS
    AFTER INSERT ON dhcp4_server
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_server_AINS();

-- Trigger function for dhcp4_server_AUPD called AFTER UPDATE on dhcp4_server
CREATE OR REPLACE FUNCTION func_dhcp4_server_AUPD() RETURNS TRIGGER AS $dhcp4_server_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_server', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp4_server_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_server_AUPD
    AFTER UPDATE ON dhcp4_server
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_server_AUPD();

-- Trigger function for dhcp4_server_ADEL called AFTER DELETE on dhcp4_server
CREATE OR REPLACE FUNCTION func_dhcp4_server_ADEL() RETURNS TRIGGER AS $dhcp4_server_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_server', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp4_server_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_server_ADEL
    AFTER DELETE ON dhcp4_server
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_server_ADEL();

-- Trigger function for dhcp6_server_AINS called AFTER INSERT on dhcp6_server
CREATE OR REPLACE FUNCTION func_dhcp6_server_AINS() RETURNS TRIGGER AS $dhcp6_server_AINS$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_server', NEW.id, 'create');
    RETURN NULL;
END;
$dhcp6_server_AINS$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_server_AINS
    AFTER INSERT ON dhcp6_server
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_server_AINS();

-- Trigger function for dhcp6_server_AUPD called AFTER UPDATE on dhcp6_server
CREATE OR REPLACE FUNCTION func_dhcp6_server_AUPD() RETURNS TRIGGER AS $dhcp6_server_AUPD$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_server', NEW.id, 'update');
    RETURN NULL;
END;
$dhcp6_server_AUPD$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_server_AUPD
    AFTER UPDATE ON dhcp6_server
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_server_AUPD();

-- Trigger function for dhcp6_server_ADEL called AFTER DELETE on dhcp6_server
CREATE OR REPLACE FUNCTION func_dhcp6_server_ADEL() RETURNS TRIGGER AS $dhcp6_server_ADEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_server', OLD.id, 'delete');
    RETURN NULL;
END;
$dhcp6_server_ADEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_server_ADEL
    AFTER DELETE ON dhcp6_server
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_server_ADEL();

-- Trigger function for dhcp4_shared_network_BDEL called BEFORE DELETE on dhcp4_shared_network
CREATE OR REPLACE FUNCTION func_dhcp4_shared_network_BDEL() RETURNS TRIGGER AS $dhcp4_shared_network_BDEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_shared_network', OLD.id, 'delete');
    DELETE FROM dhcp4_options WHERE shared_network_name = OLD.name;
    RETURN OLD;
END;
$dhcp4_shared_network_BDEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_shared_network_BDEL
    BEFORE DELETE ON dhcp4_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_shared_network_BDEL();

-- Trigger function for dhcp4_subnet_BDEL called BEFORE DELETE on dhcp4_subnet
CREATE OR REPLACE FUNCTION func_dhcp4_subnet_BDEL() RETURNS TRIGGER AS $dhcp4_subnet_BDEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_subnet', OLD.subnet_id, 'delete');
    DELETE FROM dhcp4_pool WHERE subnet_id = OLD.subnet_id;
    DELETE FROM dhcp4_options WHERE dhcp4_subnet_id = OLD.subnet_id;
    RETURN OLD;
END;
$dhcp4_subnet_BDEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp4_subnet_BDEL
    BEFORE DELETE ON dhcp4_subnet
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp4_subnet_BDEL();

-- Trigger function for dhcp6_shared_network_BDEL called BEFORE DELETE on dhcp6_shared_network
CREATE OR REPLACE FUNCTION func_dhcp6_shared_network_BDEL() RETURNS TRIGGER AS $dhcp6_shared_network_BDEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_shared_network', OLD.id, 'delete');
    DELETE FROM dhcp6_options WHERE shared_network_name = OLD.name;
    RETURN OLD;
END;
$dhcp6_shared_network_BDEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_shared_network_BDEL
    BEFORE DELETE ON dhcp6_shared_network
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_shared_network_BDEL();

-- Trigger function for dhcp6_subnet_BDEL called BEFORE DELETE on dhcp6_subnet
CREATE OR REPLACE FUNCTION func_dhcp6_subnet_BDEL() RETURNS TRIGGER AS $dhcp6_subnet_BDEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_subnet', OLD.subnet_id, 'delete');
    DELETE FROM dhcp6_pool WHERE subnet_id = OLD.subnet_id;
    DELETE FROM dhcp6_pd_pool WHERE subnet_id = OLD.subnet_id;
    DELETE FROM dhcp6_options WHERE dhcp6_subnet_id = OLD.subnet_id;
    RETURN OLD;
END;
$dhcp6_subnet_BDEL$
LANGUAGE plpgsql;

CREATE TRIGGER dhcp6_subnet_BDEL
    BEFORE DELETE ON dhcp6_subnet
        FOR EACH ROW EXECUTE PROCEDURE func_dhcp6_subnet_BDEL();
-- Trigger function for dhcp6_pd_pool_BDEL called BEFORE DELETE on dhcp6_pd_pool
CREATE OR REPLACE FUNCTION func_dhcp6_pd_pool_BDEL() RETURNS TRIGGER AS $dhcp6_pd_pool_BDEL$
BEGIN
    DELETE FROM dhcp6_options WHERE scope_id = 6 AND pd_pool_id = OLD.id;
    RETURN OLD;
END;
$dhcp6_pd_pool_BDEL$
LANGUAGE plpgsql;

-- Update the schema version number.
UPDATE schema_version
    SET version = '7', minor = '0';

-- This line concludes the schema upgrade to version 7.0.

-- This line starts the schema upgrade to version 8.0.

-- Add a few missing elements for CB and functions for kea-admin's lease-dump
-- and lease-upload commands.

-- -----------------------------------------------------------------------
-- Extend the table holding DHCPv4 option definitions with a nullable
-- column matching option defintions with client classes.
-- -----------------------------------------------------------------------
ALTER TABLE dhcp4_option_def
    ADD COLUMN class_id BIGINT NULL DEFAULT NULL;

ALTER TABLE dhcp4_option_def
  ADD CONSTRAINT fk_dhcp4_option_def_client_class_id
    FOREIGN KEY (class_id)
    REFERENCES dhcp4_client_class (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

-- -----------------------------------------------------------------------
-- Extend the table holding DHCPv6 option definitions with a nullable
-- column matching option defintions with client classes.
-- -----------------------------------------------------------------------
ALTER TABLE dhcp6_option_def
    ADD COLUMN class_id BIGINT NULL DEFAULT NULL;

ALTER TABLE dhcp6_option_def
  ADD CONSTRAINT fk_dhcp6_option_def_client_class_id
    FOREIGN KEY (class_id)
    REFERENCES dhcp6_client_class (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

-- -----------------------------------------------------------------------
-- Add missing preferred_lifetime columns to dhcp6_client_class table.
-- -----------------------------------------------------------------------
ALTER TABLE dhcp6_client_class
    ADD COLUMN preferred_lifetime BIGINT DEFAULT NULL,
    ADD COLUMN min_preferred_lifetime BIGINT DEFAULT NULL,
    ADD COLUMN max_preferred_lifetime BIGINT DEFAULT NULL;

-- -----------------------------------------------------------------------
-- Add option scopes
-- -----------------------------------------------------------------------
-- Add scope for shared network specific options.
INSERT INTO dhcp_option_scope (scope_id, scope_name)
    VALUES(4, 'shared-network');

-- Add scope for pool specific options.
INSERT INTO dhcp_option_scope (scope_id, scope_name)
    VALUES(5, 'pool');

-- Add scope for PD pool specific options.
INSERT INTO dhcp_option_scope (scope_id, scope_name)
    VALUES(6, 'pd-pool');

-- Drop the existing function, createOptionAuditDHCP6 so we can replace it
-- with one that has slightly different arguments.
DROP FUNCTION IF EXISTS createOptionAuditDHCP6(modification_type VARCHAR(32),
                                               scope_id SMALLINT, option_id INT, subnet_id BIGINT,
                                               host_id INT, network_name VARCHAR(128),
                                               pool_id BIGINT, pd_pool_id BIGINT,
                                               modification_ts TIMESTAMP WITH TIME ZONE);

-- -----------------------------------------------------
--
-- New version of the createOptionAuditDHCP6 stored
-- procedure which updates modification timestamp of
-- a parent object when an option is modified.
--
-- The following parameters are passed to the procedure:
-- - modification_type: "create", "update" or "delete"
-- - scope_id: identifier of the option scope, e.g.
--   global, subnet specific etc. See dhcp_option_scope
--   for specific values.
-- - option_id: identifier of the option.
-- - subnet_id: identifier of the subnet if the option
--   belongs to the subnet.
-- - host_id: identifier of the host if the option
-- - belongs to the host.
-- - network_name: shared network name if the option
--   belongs to the shared network.
-- - pool_id: identifier of the pool if the option
--   belongs to the pool.
-- - pd_pool_id: identifier of the pool if the option
--   belongs to the pd pool.
-- - modification_ts: modification timestamp of the
--   option.
--   Some arguments are prefixed with "p_" to avoid ambiguity
--   with column names in SQL statements. PostgreSQL does not
--   allow table aliases to be used with column names in update
--   set expressions.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createOptionAuditDHCP6(modification_type VARCHAR(32),
                                                  scope_id SMALLINT,
                                                  option_id INT,
                                                  p_subnet_id BIGINT,
                                                  host_id INT,
                                                  network_name VARCHAR(128),
                                                  pool_id BIGINT,
                                                  pd_pool_id BIGINT,
                                                  p_modification_ts TIMESTAMP WITH TIME ZONE)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- These variables will hold shared network id and subnet id that
    -- we will select.
    snid VARCHAR(128);
    sid BIGINT;
    cascade_transaction BOOLEAN := false;

BEGIN
    -- Cascade transaction flag is set to true to prevent creation of
    -- the audit entries for the options when the options are
    -- created as part of the parent object creation or update.
    -- For example: when the option is added as part of the subnet
    -- addition, the cascade transaction flag is equal to true. If
    -- the option is added into the existing subnet the cascade
    -- transaction is equal to false. Note that depending on the option
    -- scope the audit entry will contain the object_type value
    -- of the parent object to cause the server to replace the
    -- entire subnet. The only case when the object_type will be
    -- set to 'dhcp6_options' is when a global option is added.
    -- Global options do not have the owner.
    cascade_transaction := get_session_boolean('kea.cascade_transaction');
    IF cascade_transaction = false THEN
        -- todo: host manager hasn't been updated to use audit
        -- mechanisms so ignore host specific options for now.
        IF scope_id = 0 THEN
            -- If a global option is added or modified, create audit
            -- entry for the 'dhcp6_options' table.
            PERFORM createAuditEntryDHCP6('dhcp6_options', option_id, modification_type);
        ELSEIF scope_id = 1 THEN
            -- If subnet specific option is added or modified, update
            -- the modification timestamp of this subnet to allow the
            -- servers to refresh the subnet information. This will
            -- also result in creating an audit entry for this subnet.
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = p_subnet_id;
        ELSEIF scope_id = 4 THEN
            -- If shared network specific option is added or modified,
            -- update the modification timestamp of this shared network
            -- to allow the servers to refresh the shared network
            -- information. This will also result in creating an
            -- audit entry for this shared network.
           SELECT id INTO snid FROM dhcp6_shared_network WHERE name = network_name LIMIT 1;
           UPDATE dhcp6_shared_network SET modification_ts = p_modification_ts
                WHERE id = snid;
        ELSEIF scope_id = 5 THEN
            -- If pool specific option is added or modified, update
            -- the modification timestamp of the owning subnet.
            SELECT dhcp6_pool.subnet_id INTO sid FROM dhcp6_pool WHERE id = pool_id;
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        ELSEIF scope_id = 6 THEN
            -- If pd pool specific option is added or modified, create
            -- audit entry for the subnet which this pool belongs to.
            SELECT dhcp6_pd_pool.subnet_id INTO sid FROM dhcp6_pd_pool WHERE id = pool_id;
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        END IF;
    END IF;
    RETURN;
END;$$;

-- Fix mangled constraints on dhcp4_subnet_server table.
ALTER TABLE dhcp4_subnet_server
    DROP CONSTRAINT fk_dhcp6_subnet_server_server_id,
    ADD CONSTRAINT fk_dhcp4_subnet_server_server_id
        FOREIGN KEY (server_id) REFERENCES dhcp4_server (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
    DROP CONSTRAINT fk_dhcp6_subnet_server_subnet_id,
    ADD CONSTRAINT fk_dhcp4_subnet_server_subnet_id
        FOREIGN KEY (subnet_id) REFERENCES dhcp4_subnet (subnet_id) ON DELETE CASCADE ON UPDATE NO ACTION;

-- Add missing foreign key indexes. PostgreSQL does not automatically create indexes for
-- foreign key constraints. These have been added using the basic guideline:
--
-- If the constraint does not reference a static table (e.g. parameter_data_type),
-- and the referencing column is not the primary key or the first
-- column in the primary key, and does not already have an index, then an index
-- should be added to the table for the referencing column.
--
-- dhcp6_global_parameter_server
CREATE INDEX  fk_dhcp6_global_parameter_server_server_id ON dhcp6_global_parameter_server (server_id);

-- dhcp6_options
-- Missing foreign key constraint and indexes
ALTER TABLE dhcp6_options ADD CONSTRAINT fk_dhcp6_options_subnet
    FOREIGN KEY (dhcp6_subnet_id)
        REFERENCES dhcp6_subnet(subnet_id)
        ON DELETE CASCADE ON UPDATE CASCADE;

CREATE INDEX fk_dhcp6_options_subnet ON dhcp6_options (dhcp6_subnet_id);
CREATE INDEX fk_dhcp6_options_pd_pool ON dhcp6_options (pd_pool_id);
CREATE INDEX fk_dhcp6_options_pool ON dhcp6_options (pool_id);
CREATE INDEX fk_dhcp6_options_shared_network ON dhcp6_options (shared_network_name);

-- dhcp6_option_def_server
-- Missing foreign key constraints and index
ALTER TABLE dhcp6_option_def_server
    ADD CONSTRAINT fk_dhcp6_option_def_server_option_def_id FOREIGN KEY (option_def_id)
        REFERENCES dhcp6_option_def (id) ON DELETE CASCADE ON UPDATE NO ACTION,
    ADD CONSTRAINT fk_dhcp6_option_def_server_server_id FOREIGN KEY (server_id)
        REFERENCES dhcp6_server (id) ON DELETE NO ACTION ON UPDATE NO ACTION;

CREATE INDEX fk_dhcp6_option_def_server_server_id ON dhcp6_option_def_server (server_id);

-- dhcp6_option_def
CREATE INDEX fk_dhcp6_option_def_client_class_id ON dhcp6_option_def (class_id);

-- dhcp4_global_parameter_server
CREATE INDEX  fk_dhcp4_global_parameter_server_server_id ON dhcp4_global_parameter_server (server_id);

-- dhcp4_options
-- Missing foreign key constraint and indexes
ALTER TABLE dhcp4_options ADD CONSTRAINT fk_dhcp4_options_subnet
    FOREIGN KEY (dhcp4_subnet_id)
        REFERENCES dhcp4_subnet(subnet_id)
        ON DELETE CASCADE ON UPDATE CASCADE;

CREATE INDEX fk_dhcp4_options_subnet ON dhcp4_options (dhcp4_subnet_id);
CREATE INDEX fk_dhcp4_options_pool ON dhcp4_options (pool_id);
CREATE INDEX fk_dhcp4_options_shared_network ON dhcp4_options (shared_network_name);

-- dhcp4_option_def_server
-- Missing foreign key constraints and index
ALTER TABLE dhcp4_option_def_server
    ADD CONSTRAINT fk_dhcp4_option_def_server_option_def_id FOREIGN KEY (option_def_id)
        REFERENCES dhcp4_option_def (id) ON DELETE CASCADE ON UPDATE NO ACTION,
    ADD CONSTRAINT fk_dhcp4_option_def_server_server_id FOREIGN KEY (server_id)
        REFERENCES dhcp4_server (id) ON DELETE NO ACTION ON UPDATE NO ACTION;

CREATE INDEX fk_dhcp4_option_def_server_server_id ON dhcp4_option_def_server (server_id);

-- dhcp4_option_def
CREATE INDEX fk_dhcp4_option_def_client_class_id ON dhcp4_option_def (class_id);

-- Create a function that separates groups of two hexadecimals
-- with colons.
CREATE OR REPLACE FUNCTION colonSeparatedHex(hex TEXT)
RETURNS TEXT
AS $$
DECLARE
    i INT := 3;
    length INT := LENGTH(hex);
    output TEXT;
BEGIN
    -- Add a leading zero if the first octet has a single hexadecimal character.
    IF MOD(length, 2) = 1 THEN
        hex := CONCAT('0', hex);
        length := length + 1;
    END IF;

    -- Start with the first octet.
    output := SUBSTR(hex, 1, 2);

    -- Add one octet at a time and a leading colon with each.
    WHILE i < length LOOP
        output := CONCAT(output, ':', SUBSTR(hex, i, 2));
        i := i + 2;
    END LOOP;

    -- Memfile uses lowercase hexadecimals.
    output := LOWER(output);

    RETURN output;
END
$$ LANGUAGE plpgsql;

-- Modify the function to output a memfile-ready CSV file.
-- Some columns that are SMALLINT in the lease4 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
DROP FUNCTION IF EXISTS lease4DumpData();
CREATE OR REPLACE FUNCTION lease4DumpData()
RETURNS TABLE (
    address INET,
    hwaddr VARCHAR,
    client_id VARCHAR,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id BIGINT,
    fqdn_fwd INT,
    fqdn_rev INT,
    hostname VARCHAR,
    state INT8,
    user_context VARCHAR
) AS $$
    SELECT
        ('0.0.0.0'::inet + address),
        colonSeparatedHex(encode(hwaddr, 'hex')),
        colonSeparatedHex(encode(client_id, 'hex')),
        valid_lifetime,
        extract(epoch from expire)::bigint,
        subnet_id,
        fqdn_fwd::int,
        fqdn_rev::int,
        replace(hostname, ',', '&#x2c'),
        state,
        replace(user_context, ',', '&#x2c')
    FROM lease4
    ORDER BY address;
$$ LANGUAGE SQL;

-- hwtype and hwaddr_source need to be last to match memfile format.
DROP FUNCTION IF EXISTS lease6DumpHeader();
CREATE OR REPLACE FUNCTION lease6DumpHeader()
RETURNS TEXT AS $$
    SELECT CAST('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,state,user_context,hwtype,hwaddr_source' AS TEXT) AS result;
$$ LANGUAGE SQL;

-- Modify the function to output a memfile-ready CSV file.
-- Some columns that are SMALLINT in the lease6 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE OR REPLACE FUNCTION lease6DumpData()
RETURNS TABLE (
    address VARCHAR,
    duid VARCHAR,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id BIGINT,
    pref_lifetime BIGINT,
    lease_type SMALLINT,
    iaid INT,
    prefix_len SMALLINT,
    fqdn_fwd INT,
    fqdn_rev INT,
    hostname VARCHAR,
    hwaddr VARCHAR,
    state INT8,
    user_context VARCHAR,
    hwtype SMALLINT,
    hwaddr_source SMALLINT
) AS $$
    SELECT
        address,
        colonSeparatedHex(encode(duid, 'hex')),
        valid_lifetime,
        extract(epoch from expire)::bigint,
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd::int,
        fqdn_rev::int,
        replace(hostname, ',', '&#x2c'),
        colonSeparatedHex(encode(hwaddr, 'hex')),
        state,
        replace(user_context, ',', '&#x2c'),
        hwtype,
        hwaddr_source
    FROM lease6
    ORDER BY address;
$$ LANGUAGE SQL;

-- Create a procedure that inserts a v4 lease from memfile data.
-- Some columns that are SMALLINT in the lease4 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
CREATE OR REPLACE FUNCTION lease4Upload(
    IN address VARCHAR,
    IN hwaddr VARCHAR,
    IN client_id VARCHAR,
    IN valid_lifetime BIGINT,
    IN expire BIGINT,
    IN subnet_id BIGINT,
    IN fqdn_fwd INT,
    IN fqdn_rev INT,
    IN hostname VARCHAR,
    IN state INT8,
    IN user_context VARCHAR
) RETURNS VOID AS $$
BEGIN
    INSERT INTO lease4 (
        address,
        hwaddr,
        client_id,
        valid_lifetime,
        expire,
        subnet_id,
        fqdn_fwd,
        fqdn_rev,
        hostname,
        state,
        user_context
    ) VALUES (
        address::inet - '0.0.0.0'::inet,
        decode(replace(hwaddr, ':', ''), 'hex'),
        decode(replace(client_id, ':', ''), 'hex'),
        valid_lifetime,
        to_timestamp(expire),
        subnet_id,
        fqdn_fwd::int::boolean,
        fqdn_rev::int::boolean,
        replace(hostname, '&#x2c', ','),
        state,
        replace(user_context, '&#x2c', ',')
    );
END
$$ LANGUAGE plpgsql;

-- Create a procedure that inserts a v6 lease from memfile data.
-- Some columns that are SMALLINT in the lease6 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
CREATE OR REPLACE FUNCTION lease6Upload(
    IN address VARCHAR,
    IN duid VARCHAR,
    IN valid_lifetime BIGINT,
    IN expire BIGINT,
    IN subnet_id BIGINT,
    IN pref_lifetime BIGINT,
    IN lease_type INT,
    IN iaid INT,
    IN prefix_len INT,
    IN fqdn_fwd INT,
    IN fqdn_rev INT,
    IN hostname VARCHAR,
    IN hwaddr VARCHAR,
    IN state INT8,
    IN user_context VARCHAR,
    IN hwtype INT,
    IN hwaddr_source INT
) RETURNS VOID AS $$
BEGIN
    INSERT INTO lease6 (
        address,
        duid,
        valid_lifetime,
        expire,
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd,
        fqdn_rev,
        hostname,
        hwaddr,
        state,
        user_context,
        hwtype,
        hwaddr_source
    ) VALUES (
        address,
        decode(replace(duid, ':', ''), 'hex'),
        valid_lifetime,
        to_timestamp(expire),
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd::int::boolean,
        fqdn_rev::int::boolean,
        replace(hostname, '&#x2c', ','),
        decode(replace(hwaddr, ':', ''), 'hex'),
        state,
        replace(user_context, '&#x2c', ','),
        hwtype,
        hwaddr_source
    );
END
$$ LANGUAGE plpgsql;

-- Update the schema version number.
UPDATE schema_version
    SET version = '8', minor = '0';

-- This line concludes the schema upgrade to version 8.0.

-- This line starts the schema upgrade to version 9.0.

-- Add missing cascade to constraint on dhcp4/6_subnet_server tables.
ALTER TABLE dhcp4_subnet_server
    DROP CONSTRAINT fk_dhcp4_subnet_server_server_id,
    ADD CONSTRAINT fk_dhcp4_subnet_server_server_id
        FOREIGN KEY (server_id) REFERENCES dhcp4_server (id) ON DELETE CASCADE ON UPDATE CASCADE,
    DROP CONSTRAINT fk_dhcp4_subnet_server_subnet_id,
    ADD CONSTRAINT fk_dhcp4_subnet_server_subnet_id
        FOREIGN KEY (subnet_id) REFERENCES dhcp4_subnet (subnet_id) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE dhcp6_subnet_server
    DROP CONSTRAINT fk_dhcp6_subnet_server_server_id,
    ADD CONSTRAINT fk_dhcp6_subnet_server_server_id
        FOREIGN KEY (server_id) REFERENCES dhcp6_server (id) ON DELETE CASCADE ON UPDATE CASCADE,
    DROP CONSTRAINT fk_dhcp6_subnet_server_subnet_id,
    ADD CONSTRAINT fk_dhcp6_subnet_server_subnet_id
        FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet (subnet_id) ON DELETE CASCADE ON UPDATE CASCADE;

-- Fix constraint typo on dhcp4_option_def_server
ALTER TABLE dhcp4_option_def_server
    DROP CONSTRAINT dhcp4_option_def_server_option_def_id_fkey,
    ADD CONSTRAINT dhcp4_option_def_server_option_def_id_fkey
        FOREIGN KEY (option_def_id) REFERENCES dhcp4_option_def(id) ON DELETE CASCADE;

-- DROP shared-network ADEL triggers that should not exist.
DROP TRIGGER IF EXISTS dhcp4_shared_network_ADEL on dhcp4_shared_network CASCADE;
DROP TRIGGER IF EXISTS dhcp6_shared_network_ADEL on dhcp6_shared_network CASCADE;

-- Replace createOptionAuditDHCP4() with a version that has local variable
-- snid correctly declared as a BIGINT.
--
-- -----------------------------------------------------
--
-- Stored procedure which updates modification timestamp of
-- a parent object when an option is modified.
--
-- The following parameters are passed to the procedure:
-- - modification_type: "create", "update" or "delete"
-- - scope_id: identifier of the option scope, e.g.
--   global, subnet specific etc. See dhcp_option_scope
--   for specific values.
-- - option_id: identifier of the option.
-- - p_subnet_id: identifier of the subnet if the option
--   belongs to the subnet.
-- - host_id: identifier of the host if the option
-- - belongs to the host.
-- - network_name: shared network name if the option
--   belongs to the shared network.
-- - pool_id: identifier of the pool if the option
--   belongs to the pool.
-- - p_modification_ts: modification timestamp of the
--   option.
--   Some arguments are prefixed with "p_" to avoid ambiguity
--   with column names in SQL statements. PostgreSQL does not
--   allow table aliases to be used with column names in update
--   set expressions.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createOptionAuditDHCP4(modification_type VARCHAR,
                                                  scope_id SMALLINT,
                                                  option_id INT,
                                                  p_subnet_id BIGINT,
                                                  host_id INT,
                                                  network_name VARCHAR,
                                                  pool_id BIGINT,
                                                  p_modification_ts TIMESTAMP WITH TIME ZONE)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- These variables will hold shared network id and subnet id that
    -- we will select.
    snid BIGINT;
    sid BIGINT;
    cascade_transaction BOOLEAN;
BEGIN
    -- Cascade transaction flag is set to true to prevent creation of
    -- the audit entries for the options when the options are
    -- created as part of the parent object creation or update.
    -- For example: when the option is added as part of the subnet
    -- addition, the cascade transaction flag is equal to true. If
    -- the option is added into the existing subnet the cascade
    -- transaction is equal to false. Note that depending on the option
    -- scope the audit entry will contain the object_type value
    -- of the parent object to cause the server to replace the
    -- entire subnet. The only case when the object_type will be
    -- set to 'dhcp4_options' is when a global option is added.
    -- Global options do not have the owner.

    cascade_transaction := get_session_boolean('kea.cascade_transaction');
    IF cascade_transaction = false THEN
        -- todo: host manager hasn't been updated to use audit
        -- mechanisms so ignore host specific options for now.
        IF scope_id = 0 THEN
            -- If a global option is added or modified, create audit
            -- entry for the 'dhcp4_options' table.
            PERFORM createAuditEntryDHCP4('dhcp4_options', option_id, modification_type);
        ELSEIF scope_id = 1 THEN
            -- If subnet specific option is added or modified, update
            -- the modification timestamp of this subnet to allow the
            -- servers to refresh the subnet information. This will
            -- also result in creating an audit entry for this subnet.
            UPDATE dhcp4_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = p_subnet_id;
        ELSEIF scope_id = 4 THEN
            -- If shared network specific option is added or modified,
            -- update the modification timestamp of this shared network
            -- to allow the servers to refresh the shared network
            -- information. This will also result in creating an
            -- audit entry for this shared network.
           SELECT id INTO snid FROM dhcp4_shared_network WHERE name = network_name LIMIT 1;
           UPDATE dhcp4_shared_network SET modification_ts = p_modification_ts
                WHERE id = snid;
        ELSEIF scope_id = 5 THEN
            -- If pool specific option is added or modified, update
            -- the modification timestamp of the owning subnet.
            SELECT dhcp4_pool.subnet_id INTO sid FROM dhcp4_pool WHERE id = pool_id;
            UPDATE dhcp4_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        END IF;
    END IF;
    RETURN;
END;$$;

-- Replace createOptionAuditDHCP6() with a version that has local variable
-- snid correctly declared as a BIGINT.
--
-- -----------------------------------------------------
--
-- Stored procedure which updates modification timestamp of
-- a parent object when an option is modified.
--
-- The following parameters are passed to the procedure:
-- - modification_type: "create", "update" or "delete"
-- - scope_id: identifier of the option scope, e.g.
--   global, subnet specific etc. See dhcp_option_scope
--   for specific values.
-- - option_id: identifier of the option.
-- - p_subnet_id: identifier of the subnet if the option
--   belongs to the subnet.
-- - host_id: identifier of the host if the option
-- - belongs to the host.
-- - network_name: shared network name if the option
--   belongs to the shared network.
-- - pool_id: identifier of the pool if the option
--   belongs to the pool.
-- - pd_pool_id: identifier of the pool if the option
--   belongs to the pd pool.
-- - p_modification_ts: modification timestamp of the
--   option.
--   Some arguments are prefixed with "p_" to avoid ambiguity
--   with column names in SQL statements. PostgreSQL does not
--   allow table aliases to be used with column names in update
--   set expressions.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createOptionAuditDHCP6(modification_type VARCHAR,
                                                  scope_id SMALLINT,
                                                  option_id INT,
                                                  p_subnet_id BIGINT,
                                                  host_id INT,
                                                  network_name VARCHAR,
                                                  pool_id BIGINT,
                                                  pd_pool_id BIGINT,
                                                  p_modification_ts TIMESTAMP WITH TIME ZONE)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- These variables will hold shared network id and subnet id that
    -- we will select.
    snid BIGINT;
    sid BIGINT;
    cascade_transaction BOOLEAN;
BEGIN
    -- Cascade transaction flag is set to true to prevent creation of
    -- the audit entries for the options when the options are
    -- created as part of the parent object creation or update.
    -- For example: when the option is added as part of the subnet
    -- addition, the cascade transaction flag is equal to true. If
    -- the option is added into the existing subnet the cascade
    -- transaction is equal to false. Note that depending on the option
    -- scope the audit entry will contain the object_type value
    -- of the parent object to cause the server to replace the
    -- entire subnet. The only case when the object_type will be
    -- set to 'dhcp6_options' is when a global option is added.
    -- Global options do not have the owner.

    cascade_transaction := get_session_boolean('kea.cascade_transaction');
    IF cascade_transaction = false THEN
        -- todo: host manager hasn't been updated to use audit
        -- mechanisms so ignore host specific options for now.
        IF scope_id = 0 THEN
            -- If a global option is added or modified, create audit
            -- entry for the 'dhcp6_options' table.
            PERFORM createAuditEntryDHCP6('dhcp6_options', option_id, modification_type);
        ELSEIF scope_id = 1 THEN
            -- If subnet specific option is added or modified, update
            -- the modification timestamp of this subnet to allow the
            -- servers to refresh the subnet information. This will
            -- also result in creating an audit entry for this subnet.
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = p_subnet_id;
        ELSEIF scope_id = 4 THEN
            -- If shared network specific option is added or modified,
            -- update the modification timestamp of this shared network
            -- to allow the servers to refresh the shared network
            -- information. This will also result in creating an
            -- audit entry for this shared network.
           SELECT id INTO snid FROM dhcp6_shared_network WHERE name = network_name LIMIT 1;
           UPDATE dhcp6_shared_network SET modification_ts = p_modification_ts
                WHERE id = snid;
        ELSEIF scope_id = 5 THEN
            -- If pool specific option is added or modified, update
            -- the modification timestamp of the owning subnet.
            SELECT dhcp6_pool.subnet_id INTO sid FROM dhcp6_pool WHERE id = pool_id;
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        ELSEIF scope_id = 6 THEN
            -- If pd pool specific option is added or modified, create
            -- audit entry for the subnet which this pool belongs to.
            SELECT dhcp6_pd_pool.subnet_id INTO sid FROM dhcp6_pd_pool WHERE id = pool_id;
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        END IF;
    END IF;
    RETURN;
END;$$;

-- Returns the epoch GMT time in second from a timestamp with time zone
--
-- param input_ts timestamp value to convert
-- return a BIGINT containing the number of seconds since the epoch in GMT.
CREATE OR REPLACE FUNCTION gmt_epoch(input_ts TIMESTAMP WITH TIME ZONE)
RETURNS BIGINT
AS $$
DECLARE
    gmt_epoch BIGINT;
BEGIN
    SELECT (extract(epoch from input_ts) + extract(timezone from input_ts))::BIGINT INTO gmt_epoch;
    RETURN gmt_epoch;
    EXCEPTION
    WHEN OTHERS THEN
        RAISE EXCEPTION 'gmt_epoch(%) : failed, sqlstate: %', input_ts, sqlstate;
END;$$
LANGUAGE plpgsql;

-- Update the schema version number.
UPDATE schema_version
    SET version = '9', minor = '0';

-- This line concludes the schema upgrade to version 9.0.

-- This line starts the schema upgrade to version 10.0.

-- It adds corrections for client classes for CB

-- Replace setClientClass4Order():
-- 1. l_depend_on_known_indirectly needs to be BOOL
-- 2. follow_class_index needs to be BIGINT

-- -----------------------------------------------------------------------
-- Stored procedure positioning an inserted or updated client class
-- within the class hierarchy, depending on the value of the
-- new_follow_class_name parameter.
--
-- Parameters:
-- - id id of the positioned class,
-- - new_follow_class_name name of the class after which this class should be
--   positioned within the class hierarchy.
-- - old_follow_class_name previous name of the class after which this
--   class was positioned within the class hierarchy.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION setClientClass4Order(id BIGINT,
                                                new_follow_class_name VARCHAR(128),
                                                old_follow_class_name VARCHAR(128))
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- Used to fetch class's current value for depend_on_known_indirectly
    l_depend_on_known_indirectly BOOL := false;

    -- Optionally set if the follow_class_name column value is specified.
    follow_class_index BIGINT;
BEGIN
    -- Fetch the class's current value of depend_on_known_indirectly.
    SELECT depend_on_known_indirectly INTO l_depend_on_known_indirectly
        FROM dhcp4_client_class_order WHERE id = class_id;

    -- Save it to the current session for use elsewhere during this transaction.
    -- Note this does not work prior to Postgres 9.2 unless the variables are
    -- defined in postgresql.conf. I think for now we put up with CB not supported
    -- prior to 9.2 or we tell people how to edit the conf file.
    PERFORM set_session_value('kea.depend_on_known_indirectly', l_depend_on_known_indirectly);

    -- Bail if the class is updated without re-positioning.
    IF(
       l_depend_on_known_indirectly IS NOT NULL AND
       ((new_follow_class_name IS NULL AND old_follow_class_name IS NULL) OR
        (new_follow_class_name = old_follow_class_name))
    ) THEN
        -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
        -- whenever the dhcp4_client_class record is updated. Such update may include
        -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
        -- This value will be later adjusted when dependencies are inserted.
        -- TKM should we update the session value also or is it moot?
        UPDATE dhcp4_client_class_order SET depend_on_known_indirectly = false
            WHERE class_id = id;
        RETURN;
    END IF;

    IF new_follow_class_name IS NOT NULL THEN
        -- Get the position of the class after which the new class should be added.
        SELECT o.order_index INTO follow_class_index
            FROM dhcp4_client_class AS c
            INNER JOIN dhcp4_client_class_order AS o
                ON c.id = o.class_id
            WHERE c.name = new_follow_class_name;

        IF follow_class_index IS NULL THEN
            -- The class with a name specified with new_follow_class_name does
            -- not exist.
            RAISE EXCEPTION 'Class %s does not exist.', new_follow_class_name
                USING ERRCODE = 'sql_routine_exception';
        END IF;

        -- We need to place the new class at the position of follow_class_index + 1.
        -- There may be a class at this position already.
        IF EXISTS(SELECT * FROM dhcp4_client_class_order WHERE order_index = follow_class_index + 1) THEN
            -- There is a class at this position already. Let's move all classes
            -- starting from this position by one to create a spot for the new
            -- class.
            UPDATE dhcp4_client_class_order
                SET order_index = order_index + 1
            WHERE order_index >= follow_class_index + 1;
            -- TKM postgresql doesn't like order by here, does it matter?
            -- ORDER BY order_index DESC;
        END IF;

    ELSE
        -- A caller did not specify the new_follow_class_name value. Let's append the
        -- new class at the end of the hierarchy.
        SELECT MAX(order_index) INTO follow_class_index FROM dhcp4_client_class_order;
        IF follow_class_index IS NULL THEN
            -- Apparently, there are no classes. Let's start from 0.
            follow_class_index = 0;
        END IF;
    END IF;

    -- Check if moving the class doesn't break dependent classes.
    IF EXISTS(
        SELECT 1 FROM dhcp4_client_class_dependency AS d
            INNER JOIN dhcp4_client_class_order AS o
                ON d.class_id = o.class_id
            WHERE d.dependency_id = id AND o.order_index < follow_class_index + 1
        LIMIT 1
    ) THEN
        RAISE EXCEPTION 'Unable to move class with id %s because it would break its dependencies', id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
    -- whenever the dhcp4_client_class record is updated. Such update may include
    -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
    -- This value will be later adjusted when dependencies are inserted.
    -- TKM - note that ON CONFLICT requires PostgreSQL 9.5 or later.
    UPDATE dhcp4_client_class_order
        SET order_index = follow_class_index + 1,
            depend_on_known_indirectly = l_depend_on_known_indirectly
        WHERE class_id = id;
    IF FOUND THEN
        RETURN;
    END IF;

    INSERT INTO  dhcp4_client_class_order(class_id, order_index, depend_on_known_indirectly)
        VALUES (id, follow_class_index + 1, false);
    RETURN;
END;$$;

-- Replace setClientClass6Order():
-- 1. l_depend_on_known_indirectly needs to be BOOL
-- 2. follow_class_index needs to be BIGINT

-- -----------------------------------------------------------------------
-- Stored procedure positioning an inserted or updated client class
-- within the class hierarchy, depending on the value of the
-- new_follow_class_name parameter.
--
-- Parameters:
-- - id id of the positioned class,
-- - new_follow_class_name name of the class after which this class should be
--   positioned within the class hierarchy.
-- - old_follow_class_name previous name of the class after which this
--   class was positioned within the class hierarchy.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION setClientClass6Order(id BIGINT,
                                                new_follow_class_name VARCHAR(128),
                                                old_follow_class_name VARCHAR(128))
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- Used to fetch class's current value for depend_on_known_indirectly
    l_depend_on_known_indirectly BOOL := false;

    -- Optionally set if the follow_class_name column value is specified.
    follow_class_index BIGINT;
BEGIN
    -- Fetch the class's current value of depend_on_known_indirectly.
    SELECT depend_on_known_indirectly INTO l_depend_on_known_indirectly
        FROM dhcp6_client_class_order WHERE id = class_id;

    -- Save it to the current session for use elsewhere during this transaction.
    -- Note this does not work prior to Postgres 9.2 unless the variables are
    -- defined in postgresql.conf. I think for now we put up with CB not supported
    -- prior to 9.2 or we tell people how to edit the conf file.
    PERFORM set_session_value('kea.depend_on_known_indirectly', l_depend_on_known_indirectly);

    -- Bail if the class is updated without re-positioning.
    IF(
       l_depend_on_known_indirectly IS NOT NULL AND
       ((new_follow_class_name IS NULL AND old_follow_class_name IS NULL) OR
        (new_follow_class_name = old_follow_class_name))
    ) THEN
        -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
        -- whenever the dhcp6_client_class record is updated. Such update may include
        -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
        -- This value will be later adjusted when dependencies are inserted.
        -- TKM should we update the session value also or is it moot?
        UPDATE dhcp6_client_class_order SET depend_on_known_indirectly = false
            WHERE class_id = id;
        RETURN;
    END IF;

    IF new_follow_class_name IS NOT NULL THEN
        -- Get the position of the class after which the new class should be added.
        SELECT o.order_index INTO follow_class_index
            FROM dhcp6_client_class AS c
            INNER JOIN dhcp6_client_class_order AS o
                ON c.id = o.class_id
            WHERE c.name = new_follow_class_name;

        IF follow_class_index IS NULL THEN
            -- The class with a name specified with new_follow_class_name does
            -- not exist.
            RAISE EXCEPTION 'Class %s does not exist.', new_follow_class_name
                USING ERRCODE = 'sql_routine_exception';
        END IF;

        -- We need to place the new class at the position of follow_class_index + 1.
        -- There may be a class at this position already.
        IF EXISTS(SELECT * FROM dhcp6_client_class_order WHERE order_index = follow_class_index + 1) THEN
            -- There is a class at this position already. Let's move all classes
            -- starting from this position by one to create a spot for the new
            -- class.
            UPDATE dhcp6_client_class_order
                SET order_index = order_index + 1
            WHERE order_index >= follow_class_index + 1;
            -- TKM postgresql doesn't like order by here, does it matter?
            -- ORDER BY order_index DESC;
        END IF;

    ELSE
        -- A caller did not specify the new_follow_class_name value. Let's append the
        -- new class at the end of the hierarchy.
        SELECT MAX(order_index) INTO follow_class_index FROM dhcp6_client_class_order;
        IF follow_class_index IS NULL THEN
            -- Apparently, there are no classes. Let's start from 0.
            follow_class_index = 0;
        END IF;
    END IF;

    -- Check if moving the class doesn't break dependent classes.
    IF EXISTS(
        SELECT 1 FROM dhcp6_client_class_dependency AS d
            INNER JOIN dhcp6_client_class_order AS o
                ON d.class_id = o.class_id
            WHERE d.dependency_id = id AND o.order_index < follow_class_index + 1
        LIMIT 1
    ) THEN
        RAISE EXCEPTION 'Unable to move class with id %s because it would break its dependencies', id
            USING ERRCODE = 'sql_routine_exception';
    END IF;

    -- The depend_on_known_indirectly is set to 0 because this procedure is invoked
    -- whenever the dhcp6_client_class record is updated. Such update may include
    -- test expression changes impacting the dependency on KNOWN/UNKNOWN classes.
    -- This value will be later adjusted when dependencies are inserted.
    -- TKM - note that ON CONFLICT requires PostgreSQL 9.5 or later.
    UPDATE dhcp6_client_class_order
        SET order_index = follow_class_index + 1,
            depend_on_known_indirectly = l_depend_on_known_indirectly
        WHERE class_id = id;
    IF FOUND THEN
        RETURN;
    END IF;

    INSERT INTO  dhcp6_client_class_order(class_id, order_index, depend_on_known_indirectly)
        VALUES (id, follow_class_index + 1, false);
    RETURN;
END;$$;

-- Change primary key to composite, dependency table can have multiple rows
-- per class id.
ALTER TABLE dhcp4_client_class_dependency DROP CONSTRAINT dhcp4_client_class_dependency_pkey;
ALTER TABLE dhcp4_client_class_dependency ADD PRIMARY KEY(class_id, dependency_id);

ALTER TABLE dhcp6_client_class_dependency DROP CONSTRAINT dhcp6_client_class_dependency_pkey;
ALTER TABLE dhcp6_client_class_dependency ADD PRIMARY KEY(class_id, dependency_id);

-- Replace triggers that verify class dependency.
-- Because they are BEFORE INSERT triggers they need to return NEW not NULL.
-- -----------------------------------------------------------------------
-- Trigger verifying if class dependency is met. It includes checking
-- if referenced classes exist, are associated with the same server
-- or all servers, and are defined before the class specified with
-- class_id.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp4_client_class_check_dependency_BINS()
    RETURNS trigger AS $dhcp4_client_class_check_dependency_BINS$
BEGIN
    PERFORM checkDHCPv4ClientClassDependency(NEW.class_id, NEW.dependency_id);
    RETURN NEW;
END;
$dhcp4_client_class_check_dependency_BINS$
LANGUAGE plpgsql;

-- -----------------------------------------------------------------------
-- Trigger verifying if class dependency is met. It includes checking
-- if referenced classes exist, are associated with the same server
-- or all servers, and are defined before the class specified with
-- class_id.
-- -----------------------------------------------------------------------
CREATE OR REPLACE FUNCTION func_dhcp6_client_class_check_dependency_BINS()
    RETURNS trigger AS $dhcp6_client_class_check_dependency_BINS$
BEGIN
    PERFORM checkDHCPv6ClientClassDependency(NEW.class_id, NEW.dependency_id);
    RETURN NEW;
END;
$dhcp6_client_class_check_dependency_BINS$
LANGUAGE plpgsql;

-- Update the schema version number.
UPDATE schema_version
    SET version = '10', minor = '0';

-- This line concludes the schema upgrade to version 10.0.

-- This line starts the schema upgrade to version 11.0.

-- Replace createOptionAuditDHCP6() with a version corrected
-- where clause when scope is 6 (i.e. PD pool)
--
-- -----------------------------------------------------
--
-- Stored procedure which updates modification timestamp of
-- a parent object when an option is modified.
--
-- The following parameters are passed to the procedure:
-- - modification_type: "create", "update" or "delete"
-- - scope_id: identifier of the option scope, e.g.
--   global, subnet specific etc. See dhcp_option_scope
--   for specific values.
-- - option_id: identifier of the option.
-- - p_subnet_id: identifier of the subnet if the option
--   belongs to the subnet.
-- - host_id: identifier of the host if the option
-- - belongs to the host.
-- - network_name: shared network name if the option
--   belongs to the shared network.
-- - pool_id: identifier of the pool if the option
--   belongs to the pool.
-- - pd_pool_id: identifier of the pool if the option
--   belongs to the pd pool.
-- - p_modification_ts: modification timestamp of the
--   option.
--   Some arguments are prefixed with "p_" to avoid ambiguity
--   with column names in SQL statements. PostgreSQL does not
--   allow table aliases to be used with column names in update
--   set expressions.
-- -----------------------------------------------------
CREATE OR REPLACE FUNCTION createOptionAuditDHCP6(modification_type VARCHAR,
                                                  scope_id SMALLINT,
                                                  option_id INT,
                                                  p_subnet_id BIGINT,
                                                  host_id INT,
                                                  network_name VARCHAR,
                                                  pool_id BIGINT,
                                                  pd_pool_id BIGINT,
                                                  p_modification_ts TIMESTAMP WITH TIME ZONE)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    -- These variables will hold shared network id and subnet id that
    -- we will select.
    snid BIGINT;
    sid BIGINT;
    cascade_transaction BOOLEAN;
BEGIN
    -- Cascade transaction flag is set to true to prevent creation of
    -- the audit entries for the options when the options are
    -- created as part of the parent object creation or update.
    -- For example: when the option is added as part of the subnet
    -- addition, the cascade transaction flag is equal to true. If
    -- the option is added into the existing subnet the cascade
    -- transaction is equal to false. Note that depending on the option
    -- scope the audit entry will contain the object_type value
    -- of the parent object to cause the server to replace the
    -- entire subnet. The only case when the object_type will be
    -- set to 'dhcp6_options' is when a global option is added.
    -- Global options do not have the owner.

    cascade_transaction := get_session_boolean('kea.cascade_transaction');
    IF cascade_transaction = false THEN
        -- todo: host manager hasn't been updated to use audit
        -- mechanisms so ignore host specific options for now.
        IF scope_id = 0 THEN
            -- If a global option is added or modified, create audit
            -- entry for the 'dhcp6_options' table.
            PERFORM createAuditEntryDHCP6('dhcp6_options', option_id, modification_type);
        ELSEIF scope_id = 1 THEN
            -- If subnet specific option is added or modified, update
            -- the modification timestamp of this subnet to allow the
            -- servers to refresh the subnet information. This will
            -- also result in creating an audit entry for this subnet.
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = p_subnet_id;
        ELSEIF scope_id = 4 THEN
            -- If shared network specific option is added or modified,
            -- update the modification timestamp of this shared network
            -- to allow the servers to refresh the shared network
            -- information. This will also result in creating an
            -- audit entry for this shared network.
           SELECT id INTO snid FROM dhcp6_shared_network WHERE name = network_name LIMIT 1;
           UPDATE dhcp6_shared_network SET modification_ts = p_modification_ts
                WHERE id = snid;
        ELSEIF scope_id = 5 THEN
            -- If pool specific option is added or modified, update
            -- the modification timestamp of the owning subnet.
            SELECT dhcp6_pool.subnet_id INTO sid FROM dhcp6_pool WHERE id = pool_id;
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        ELSEIF scope_id = 6 THEN
            -- If pd pool specific option is added or modified, create
            -- audit entry for the subnet which this pool belongs to.
            SELECT dhcp6_pd_pool.subnet_id INTO sid FROM dhcp6_pd_pool WHERE id = pd_pool_id;
            UPDATE dhcp6_subnet SET modification_ts = p_modification_ts
                WHERE subnet_id = sid;
        END IF;
    END IF;
    RETURN;
END;$$;

-- Update the schema version number.
UPDATE schema_version
    SET version = '11', minor = '0';

-- This line concludes the schema upgrade to version 11.0.

-- This line starts the schema upgrade to version 12.0.

-- Modify shared-network-name foreign key constraint on dhcp4_subnet to not perform
-- the update when the network is deleted the cascaded update will not execute
-- dhcp4_subnet update trigger leaving the updated subnets without audit_entries.
ALTER TABLE dhcp4_subnet
    DROP CONSTRAINT fk_dhcp4_subnet_shared_network,
    ADD CONSTRAINT fk_dhcp4_subnet_shared_network FOREIGN KEY (shared_network_name)
         REFERENCES dhcp4_shared_network (name)
         ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Modify BEFORE delete trigger function on dhcp4_shared_network to explicitly
-- update dhcp4_subnets. This ensures there are audit entries for updated
-- subnets.
-- Trigger function for dhcp4_shared_network_BDEL called BEFORE DELETE on dhcp4_shared_network
CREATE OR REPLACE FUNCTION func_dhcp4_shared_network_BDEL() RETURNS TRIGGER AS $dhcp4_shared_network_BDEL$
BEGIN
    PERFORM createAuditEntryDHCP4('dhcp4_shared_network', OLD.id, 'delete');
    -- Explicitly update subnets now rather than via foreign key constraint, this ensures the
    -- audit entries for subnets will preceded that of the shared-network, keeping the order
    -- of the entries the same as they are for MySQL.
    UPDATE dhcp4_subnet SET shared_network_name = NULL WHERE shared_network_name = OLD.name;
    DELETE FROM dhcp4_options WHERE shared_network_name = OLD.name;
    RETURN OLD;
END;
$dhcp4_shared_network_BDEL$
LANGUAGE plpgsql;

-- Modify shared-network-name foreign key constraint on dhcp6_subnet to not perform
-- the update when the network is deleted the cascaded update will not execute
-- dhcp6_subnet update trigger leaving the updated subnets without audit_entries.
ALTER TABLE dhcp6_subnet
    DROP CONSTRAINT fk_dhcp6_subnet_shared_network,
    ADD CONSTRAINT fk_dhcp6_subnet_shared_network FOREIGN KEY (shared_network_name)
         REFERENCES dhcp6_shared_network (name)
         ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Modify BEFORE delete trigger function on dhcp6_shared_network to explicitly
-- update dhcp6_subnets. This ensures there are audit entries for updated
-- subnets.
-- Trigger function for dhcp6_shared_network_BDEL called BEFORE DELETE on dhcp6_shared_network
CREATE OR REPLACE FUNCTION func_dhcp6_shared_network_BDEL() RETURNS TRIGGER AS $dhcp6_shared_network_BDEL$
BEGIN
    PERFORM createAuditEntryDHCP6('dhcp6_shared_network', OLD.id, 'delete');
    -- Explicitly update subnets now rather than via foreign key constraint, this ensures the
    -- audit entries for subnets will preceded that of the shared-network, keeping the order
    -- of the entries the same as they are for MySQL.
    UPDATE dhcp6_subnet SET shared_network_name = NULL WHERE shared_network_name = OLD.name;
    DELETE FROM dhcp6_options WHERE shared_network_name = OLD.name;
    RETURN OLD;
END;
$dhcp6_shared_network_BDEL$
LANGUAGE plpgsql;

-- Add user_context column to client class tables.
ALTER TABLE dhcp4_client_class ADD COLUMN user_context JSON DEFAULT NULL;
ALTER TABLE dhcp6_client_class ADD COLUMN user_context JSON DEFAULT NULL;

-- Update the schema version number.
UPDATE schema_version
    SET version = '12', minor = '0';

-- This line concludes the schema upgrade to version 12.0.

-- This line starts the schema upgrade to version 13.0.

-- JSON functions --

-- Helper function that avoids a casting error when the string
-- presumed to be in JSON format, is empty.
CREATE OR REPLACE FUNCTION json_cast(IN json_candidate TEXT)
RETURNS JSON
AS $$
BEGIN
    IF LENGTH(json_candidate) = 0 THEN
        RETURN '{}'::json;
    END IF;
    RETURN json_candidate::json;
END;
$$ LANGUAGE plpgsql;

-- Function that establishes whether JSON functions are supported.
-- They should be provided with PostgreSQL >= 9.4.
CREATE OR REPLACE FUNCTION isJsonSupported()
RETURNS BOOLEAN
AS $$
BEGIN
    IF get_session_value('json_supported') IS NULL THEN
        IF (SELECT proname FROM pg_proc WHERE proname = 'json_extract_path') = 'json_extract_path' THEN
            PERFORM set_session_value('kea.json_supported', true);
        ELSE
            PERFORM set_session_value('kea.json_supported', false);
        END IF;
    END IF;
    RETURN get_session_value('kea.json_supported');
END
$$ LANGUAGE plpgsql;

-- Schema changes related to lease limiting start here. --

-- Recreate the triggers that update the leaseX_stat tables as stored procedures. --

CREATE OR REPLACE FUNCTION lease4_AINS_lease4_stat(IN new_state BIGINT,
                                                   IN new_subnet_id BIGINT)
RETURNS VOID
AS $$
BEGIN
    IF new_state = 0 OR new_state = 1 THEN
        -- Update the state count if it exists.
        UPDATE lease4_stat SET leases = leases + 1
            WHERE subnet_id = new_subnet_id AND state = new_state;

        -- Insert the state count record if it does not exist.
        IF NOT FOUND THEN
            INSERT INTO lease4_stat VALUES (new_subnet_id, new_state, 1);
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease4_AUPD_lease4_stat(IN old_state BIGINT,
                                                   IN old_subnet_id BIGINT,
                                                   IN new_state BIGINT,
                                                   IN new_subnet_id BIGINT)
RETURNS VOID
AS $$
BEGIN
    IF old_subnet_id != new_subnet_id OR old_state != new_state THEN
        IF old_state = 0 OR old_state = 1 THEN
            -- Decrement the old state count if record exists.
            UPDATE lease4_stat
                SET leases = GREATEST(leases - 1, 0)
                WHERE subnet_id = old_subnet_id AND state = old_state;
        END IF;

        IF new_state = 0 OR new_state = 1 THEN
            -- Increment the new state count if record exists.
            UPDATE lease4_stat SET leases = leases + 1
                WHERE subnet_id = new_subnet_id AND state = new_state;

            -- Insert new state record if it does not exist.
            IF NOT FOUND THEN
                INSERT INTO lease4_stat VALUES (new_subnet_id, new_state, 1);
            END IF;
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease4_ADEL_lease4_stat(IN old_state BIGINT,
                                                   IN old_subnet_id BIGINT)
RETURNS VOID
AS $$
BEGIN
    IF old_state = 0 OR old_state = 1 THEN
        -- Decrement the state count if record exists.
        UPDATE lease4_stat
            SET leases = GREATEST(leases - 1, 0)
            WHERE subnet_id = old_subnet_id AND old_state = state;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_AINS_lease6_stat(IN new_state BIGINT,
                                                   IN new_subnet_id BIGINT,
                                                   IN new_lease_type SMALLINT)
RETURNS VOID
AS $$
BEGIN
    IF new_state = 0 OR new_state = 1 THEN
        -- Update the state count if it exists.
        UPDATE lease6_stat SET leases = leases + 1
            WHERE subnet_id = new_subnet_id AND lease_type = new_lease_type
            AND state = new_state;

        -- Insert the state count record if it does not exist.
        IF NOT FOUND THEN
            INSERT INTO lease6_stat VALUES (new_subnet_id, new_lease_type, new_state, 1);
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_AUPD_lease6_stat(IN old_state BIGINT,
                                                   IN old_subnet_id BIGINT,
                                                   IN old_lease_type SMALLINT,
                                                   IN new_state BIGINT,
                                                   IN new_subnet_id BIGINT,
                                                   IN new_lease_type SMALLINT)
RETURNS VOID
AS $$
BEGIN
    IF old_subnet_id != new_subnet_id OR
       old_lease_type != new_lease_type OR
       old_state != new_state THEN
        IF old_state = 0 OR old_state = 1 THEN
            -- Decrement the old state count if record exists.
            UPDATE lease6_stat
                SET leases = GREATEST(leases - 1, 0)
                WHERE subnet_id = old_subnet_id AND lease_type = old_lease_type
                AND state = old_state;
        END IF;

        IF new_state = 0 OR new_state = 1 THEN
            -- Increment the new state count if record exists
            UPDATE lease6_stat SET leases = leases + 1
                WHERE subnet_id = new_subnet_id AND lease_type = new_lease_type
                AND state = new_state;

            -- Insert new state record if it does not exist
            IF NOT FOUND THEN
                INSERT INTO lease6_stat
                VALUES (new_subnet_id, new_lease_type, new_state, 1);
            END IF;
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_ADEL_lease6_stat(IN old_state BIGINT,
                                                   IN old_subnet_id BIGINT,
                                                   IN old_lease_type SMALLINT)
RETURNS VOID
AS $$
BEGIN
    IF old_state = 0 OR old_state = 1 THEN
        -- Decrement the state count if record exists
        UPDATE lease6_stat
            SET leases = GREATEST(leases - 1, 0)
            WHERE subnet_id = old_subnet_id AND lease_type = old_lease_type
            AND state = old_state;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Create tables that contain the number of active leases. --

CREATE TABLE lease4_stat_by_client_class (
    client_class VARCHAR(128) NOT NULL PRIMARY KEY,
    leases BIGINT NOT NULL
);

CREATE TABLE lease6_stat_by_client_class (
    client_class VARCHAR(128) NOT NULL,
    lease_type SMALLINT NOT NULL,
    leases BIGINT NOT NULL,
    PRIMARY KEY (client_class, lease_type),
    CONSTRAINT fk_lease6_stat_by_client_class_lease_type FOREIGN KEY (lease_type)
        REFERENCES lease6_types (lease_type)
);

-- Create procedures to be called for each row in after-event triggers for
-- INSERT, UPDATE and DELETE on lease tables.

CREATE OR REPLACE FUNCTION lease4_AINS_lease4_stat_by_client_class(IN new_state BIGINT,
                                                                   IN new_user_context TEXT)
RETURNS VOID
AS $$
DECLARE
    class VARCHAR(128);
BEGIN
    -- Only state 0 is needed for lease limiting.
    IF new_state = 0 THEN
        -- Dive into client classes.
        FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(new_user_context)->'ISC'->'client-classes') LOOP
            SELECT TRIM('"' FROM class) INTO class;

            -- Upsert to increment the lease count.
            UPDATE lease4_stat_by_client_class SET leases = leases + 1
                WHERE client_class = class;
            IF NOT FOUND THEN
                INSERT INTO lease4_stat_by_client_class VALUES (class, 1);
            END IF;
        END LOOP;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease4_AUPD_lease4_stat_by_client_class(IN old_state BIGINT,
                                                                   IN old_user_context TEXT,
                                                                   IN new_state BIGINT,
                                                                   IN new_user_context TEXT)
RETURNS VOID
AS $$
DECLARE
    old_client_classes TEXT;
    new_client_classes TEXT;
    class VARCHAR(128);
    length INT;
    i INT;
BEGIN
    SELECT json_cast(old_user_context)->'ISC'->'client-classes' INTO old_client_classes;
    SELECT json_cast(new_user_context)->'ISC'->'client-classes' INTO new_client_classes;

    IF old_state != new_state OR old_client_classes != new_client_classes THEN
        -- Check if it's moving away from a counted state.
        IF old_state = 0 THEN
            -- Dive into client classes.
            FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(old_client_classes)) LOOP
                SELECT TRIM('"' FROM class) INTO class;

                -- Decrement the lease count if the record exists.
                UPDATE lease4_stat_by_client_class SET leases = GREATEST(leases - 1, 0)
                    WHERE client_class = class;
            END LOOP;
        END IF;

        -- Check if it's moving into a counted state.
        IF new_state = 0 THEN
            -- Dive into client classes.
            FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(new_client_classes)) LOOP
                SELECT TRIM('"' FROM class) INTO class;

                -- Upsert to increment the lease count.
                UPDATE lease4_stat_by_client_class SET leases = leases + 1
                    WHERE client_class = class;
                IF NOT FOUND THEN
                    INSERT INTO lease4_stat_by_client_class VALUES (class, 1);
                END IF;
            END LOOP;
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease4_ADEL_lease4_stat_by_client_class(IN old_state BIGINT,
                                                                   IN old_user_context TEXT)
RETURNS VOID
AS $$
DECLARE
    class VARCHAR(128);
BEGIN
    -- Only state 0 is accounted for in lease limiting.
    IF old_state = 0 THEN
        -- Dive into client classes.
        FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(old_user_context)->'ISC'->'client-classes') LOOP
            SELECT TRIM('"' FROM class) INTO class;

            -- Decrement the lease count if the record exists.
            UPDATE lease4_stat_by_client_class SET leases = GREATEST(leases - 1, 0)
                WHERE client_class = class;
        END LOOP;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_AINS_lease6_stat_by_client_class(IN new_state BIGINT,
                                                                   IN new_user_context TEXT,
                                                                   IN new_lease_type SMALLINT)
RETURNS VOID
AS $$
DECLARE
    client_classes TEXT;
    class VARCHAR(128);
    length INT;
    i INT;
BEGIN
    -- Only state 0 is needed for lease limiting.
    IF new_state = 0 THEN
        -- Dive into client classes.
        FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(new_user_context)->'ISC'->'client-classes') LOOP
            SELECT TRIM('"' FROM class) INTO class;

            -- Upsert to increment the lease count.
            UPDATE lease6_stat_by_client_class SET leases = leases + 1
                WHERE client_class = class AND lease_type = new_lease_type;
            IF NOT FOUND THEN
                INSERT INTO lease6_stat_by_client_class VALUES (class, new_lease_type, 1);
            END IF;
        END LOOP;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_AUPD_lease6_stat_by_client_class(IN old_state BIGINT,
                                                                   IN old_user_context TEXT,
                                                                   IN old_lease_type SMALLINT,
                                                                   IN new_state BIGINT,
                                                                   IN new_user_context TEXT,
                                                                   IN new_lease_type SMALLINT)
RETURNS VOID
AS $$
DECLARE
    old_client_classes TEXT;
    new_client_classes TEXT;
    class VARCHAR(128);
    length INT;
    i INT;
BEGIN
    SELECT json_cast(old_user_context)->'ISC'->'client-classes' INTO old_client_classes;
    SELECT json_cast(new_user_context)->'ISC'->'client-classes' INTO new_client_classes;

    IF old_state != new_state OR old_client_classes != new_client_classes OR old_lease_type != new_lease_type THEN
        -- Check if it's moving away from a counted state.
        IF old_state = 0 THEN
            -- Dive into client classes.
            FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(old_client_classes)) LOOP
                SELECT TRIM('"' FROM class) INTO class;

                -- Decrement the lease count if the record exists.
                UPDATE lease6_stat_by_client_class SET leases = GREATEST(leases - 1, 0)
                    WHERE client_class = class AND lease_type = old_lease_type;
            END LOOP;
        END IF;

        -- Check if it's moving into a counted state.
        IF new_state = 0 THEN
            -- Dive into client classes.
            FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(new_client_classes)) LOOP
                SELECT TRIM('"' FROM class) INTO class;

                -- Upsert to increment the lease count.
                UPDATE lease6_stat_by_client_class SET leases = leases + 1
                    WHERE client_class = class AND lease_type = new_lease_type;
                IF NOT FOUND THEN
                    INSERT INTO lease6_stat_by_client_class VALUES (class, new_lease_type, 1);
                END IF;
            END LOOP;
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_ADEL_lease6_stat_by_client_class(IN old_state BIGINT,
                                                                   IN old_user_context TEXT,
                                                                   IN old_lease_type SMALLINT)
RETURNS VOID
AS $$
DECLARE
    client_classes VARCHAR(1024);
    class VARCHAR(128);
    length INT;
    i INT;
BEGIN
    -- Only state 0 is accounted for in lease limiting. But check both states to be consistent with lease6_stat.
    IF old_state = 0 THEN
        -- Dive into client classes.
        FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(old_user_context)->'ISC'->'client-classes') LOOP
            SELECT TRIM('"' FROM class) INTO class;

            -- Decrement the lease count if the record exists.
            UPDATE lease6_stat_by_client_class SET leases = GREATEST(leases - 1, 0)
                WHERE client_class = class AND lease_type = old_lease_type;
        END LOOP;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Recreate the after-event triggers for INSERT, UPDATE and DELETE on lease tables to call the --
-- stored procedures above in pairs of two: for client classes and for subnets. --

DROP TRIGGER IF EXISTS stat_lease4_insert ON lease4;

CREATE OR REPLACE FUNCTION func_lease4_AINS()
RETURNS trigger AS $lease4_AINS$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease4_AINS_lease4_stat_by_client_class(NEW.state, NEW.user_context);
    END IF;
    PERFORM lease4_AINS_lease4_stat(NEW.state, NEW.subnet_id);
    RETURN NULL;
END;
$lease4_AINS$ LANGUAGE plpgsql;

CREATE TRIGGER lease4_AINS AFTER INSERT ON lease4
    FOR EACH ROW EXECUTE PROCEDURE func_lease4_AINS();

DROP TRIGGER IF EXISTS stat_lease4_update ON lease4;

CREATE OR REPLACE FUNCTION func_lease4_AUPD()
RETURNS trigger AS $lease4_AUPD$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease4_AUPD_lease4_stat_by_client_class(OLD.state, OLD.user_context, NEW.state, NEW.user_context);
    END IF;
    PERFORM lease4_AUPD_lease4_stat(OLD.state, OLD.subnet_id, NEW.state, NEW.subnet_id);
    RETURN NULL;
END;
$lease4_AUPD$ LANGUAGE plpgsql;

CREATE TRIGGER lease4_AUPD AFTER UPDATE ON lease4
    FOR EACH ROW EXECUTE PROCEDURE func_lease4_AUPD();

DROP TRIGGER IF EXISTS stat_lease4_delete ON lease4;

CREATE OR REPLACE FUNCTION func_lease4_ADEL()
RETURNS trigger AS $lease4_ADEL$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease4_ADEL_lease4_stat_by_client_class(OLD.state, OLD.user_context);
    END IF;
    PERFORM lease4_ADEL_lease4_stat(OLD.state, OLD.subnet_id);
    RETURN NULL;
END;
$lease4_ADEL$ LANGUAGE plpgsql;

CREATE TRIGGER lease4_ADEL AFTER DELETE ON lease4
    FOR EACH ROW EXECUTE PROCEDURE func_lease4_ADEL();

DROP TRIGGER IF EXISTS stat_lease6_insert ON lease6;

CREATE OR REPLACE FUNCTION func_lease6_AINS()
RETURNS trigger AS $lease6_AINS$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease6_AINS_lease6_stat_by_client_class(NEW.state, NEW.user_context, NEW.lease_type);
    END IF;
    PERFORM lease6_AINS_lease6_stat(NEW.state, NEW.subnet_id, NEW.lease_type);
    RETURN NULL;
END;
$lease6_AINS$ LANGUAGE plpgsql;

CREATE TRIGGER lease6_AINS AFTER INSERT ON lease6
    FOR EACH ROW EXECUTE PROCEDURE func_lease6_AINS();

DROP TRIGGER IF EXISTS stat_lease6_update ON lease6;

CREATE OR REPLACE FUNCTION func_lease6_AUPD()
RETURNS trigger AS $lease6_AUPD$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease6_AUPD_lease6_stat_by_client_class(OLD.state, OLD.user_context, OLD.lease_type, NEW.state, NEW.user_context, NEW.lease_type);
    END IF;
    PERFORM lease6_AUPD_lease6_stat(OLD.state, OLD.subnet_id, OLD.lease_type, NEW.state, NEW.subnet_id, NEW.lease_type);
    RETURN NULL;
END;
$lease6_AUPD$ LANGUAGE plpgsql;

CREATE TRIGGER lease6_AUPD AFTER UPDATE ON lease6
    FOR EACH ROW EXECUTE PROCEDURE func_lease6_AUPD();

DROP TRIGGER IF EXISTS stat_lease6_delete ON lease6;

CREATE OR REPLACE FUNCTION func_lease6_ADEL()
RETURNS trigger AS $lease6_ADEL$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease6_ADEL_lease6_stat_by_client_class(OLD.state, OLD.user_context, OLD.lease_type);
    END IF;
    PERFORM lease6_ADEL_lease6_stat(OLD.state, OLD.subnet_id, OLD.lease_type);
    RETURN NULL;
END;
$lease6_ADEL$ LANGUAGE plpgsql;

CREATE TRIGGER lease6_ADEL AFTER DELETE ON lease6
    FOR EACH ROW EXECUTE PROCEDURE func_lease6_ADEL();

-- Create functions that return an empty TEXT if all limits allow for more leases, or otherwise a
-- TEXT in one of the following JSON formats detailing the limit that was reached:
-- { "limit-type": "client-class", "name": foo, "lease-type": "address", "limit": 2, "count": 2 }
-- { "limit-type": "subnet", "id": 1, "lease-type": "IA_PD", "limit": 2, "count": 2 }
-- The following format for user_context is assumed:
-- { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2, "prefix-limit": 1 } ],
--                        "subnet": { "id": 1, "address-limit": 2, "prefix-limit": 1 } } } }

CREATE OR REPLACE FUNCTION checkLease4Limits(user_context TEXT)
RETURNS TEXT
AS $$
DECLARE
    class TEXT;
    name VARCHAR(255);
    sid INT;
    lease_limit INT;
    lease_count INT;
BEGIN
    -- Dive into client class limits.
    FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(user_context)->'ISC'->'limits'->'client-classes') LOOP
        SELECT TRIM('"' FROM (json_cast(class)->'name')::text) INTO name;
        SELECT json_cast(class)->'address-limit' INTO lease_limit;

        IF lease_limit IS NOT NULL THEN
            -- Get the lease count for this client class.
            SELECT leases FROM lease4_stat_by_client_class INTO lease_count WHERE client_class = name;
            IF lease_count IS NULL THEN
                lease_count := 0;
            END IF;

            -- Compare. Return immediately if the limit is surpassed.
            IF lease_limit <= lease_count THEN
                RETURN CONCAT('address limit ', lease_limit, ' for client class "', name, '", current lease count ', lease_count);
            END IF;
        END IF;
    END LOOP;

    -- Dive into subnet limits.
    SELECT json_cast(user_context)->'ISC'->'limits'->'subnet'->'id' INTO sid;
    SELECT json_cast(user_context)->'ISC'->'limits'->'subnet'->'address-limit' INTO lease_limit;

    IF lease_limit IS NOT NULL THEN
        -- Get the lease count for this client class.
        SELECT leases FROM lease4_stat WHERE subnet_id = sid AND state = 0 INTO lease_count;
        IF lease_count IS NULL THEN
            lease_count := 0;
        END IF;

        -- Compare. Return immediately if the limit is surpassed.
        IF lease_limit <= lease_count THEN
            RETURN CONCAT('address limit ', lease_limit, ' for subnet ID ', sid, ', current lease count ', lease_count);
        END IF;
    END IF;

    RETURN '';
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION checkLease6Limits(user_context TEXT)
RETURNS TEXT
AS $$
DECLARE
    class TEXT;
    name VARCHAR(255);
    sid INT;
    lease_limit INT;
    lease_count INT;
BEGIN
    -- Dive into client class limits.
    FOR class IN SELECT * FROM JSON_ARRAY_ELEMENTS(json_cast(user_context)->'ISC'->'limits'->'client-classes') LOOP
        SELECT TRIM('"' FROM (json_cast(class)->'name')::text) INTO name;
        SELECT json_cast(class)->'address-limit' INTO lease_limit;

        IF lease_limit IS NOT NULL THEN
            -- Get the address count for this client class.
            SELECT leases FROM lease6_stat_by_client_class WHERE client_class = name AND lease_type = 0 INTO lease_count;
            IF lease_count IS NULL THEN
                lease_count := 0;
            END IF;

            -- Compare. Return immediately if the limit is surpassed.
            IF lease_limit <= lease_count THEN
                RETURN CONCAT('address limit ', lease_limit, ' for client class "', name, '", current lease count ', lease_count);
            END IF;
        END IF;

        SELECT json_cast(class)->'prefix-limit' INTO lease_limit;
        IF lease_limit IS NOT NULL THEN
            -- Get the prefix count for this client class.
            SELECT leases FROM lease6_stat_by_client_class WHERE client_class = name AND lease_type = 2 INTO lease_count;
            IF lease_count IS NULL THEN
                lease_count := 0;
            END IF;

            -- Compare. Return immediately if the limit is surpassed.
            IF lease_limit <= lease_count THEN
                RETURN CONCAT('prefix limit ', lease_limit, ' for client class "', name, '", current lease count ', lease_count);
            END IF;
        END IF;
    END LOOP;

    -- Dive into subnet limits.
    SELECT json_cast(user_context)->'ISC'->'limits'->'subnet'->'id' INTO sid;
    SELECT json_cast(user_context)->'ISC'->'limits'->'subnet'->'address-limit' INTO lease_limit;
    IF lease_limit IS NOT NULL THEN
        -- Get the lease count for this subnet.
        SELECT leases FROM lease6_stat WHERE subnet_id = sid AND lease_type = 0 AND state = 0 INTO lease_count;
        IF lease_count IS NULL THEN
            lease_count := 0;
        END IF;

        -- Compare. Return immediately if the limit is surpassed.
        IF lease_limit <= lease_count THEN
            RETURN CONCAT('address limit ', lease_limit, ' for subnet ID ', sid, ', current lease count ', lease_count);
        END IF;
    END IF;
    SELECT json_cast(user_context)->'ISC'->'limits'->'subnet'->'prefix-limit' INTO lease_limit;
    IF lease_limit IS NOT NULL THEN
        -- Get the lease count for this client class.
        SELECT leases FROM lease6_stat WHERE subnet_id = sid AND lease_type = 2 AND state = 0 INTO lease_count;
        IF lease_count IS NULL THEN
            lease_count := 0;
        END IF;

        -- Compare. Return immediately if the limit is surpassed.
        IF lease_limit <= lease_count THEN
            RETURN CONCAT('prefix limit ', lease_limit, ' for subnet ID ', sid, ', current lease count ', lease_count);
        END IF;
    END IF;

    RETURN '';
END;
$$ LANGUAGE plpgsql;

-- Improve hosts indexes for better performance of global reservations
-- Create new index that uses only dhcp_identifier.
CREATE INDEX key_dhcp_identifier on hosts (dhcp_identifier, dhcp_identifier_type);

-- Modify existing indexes to include subnet_id values of 0, so index is also used
-- for global reservations.
DROP INDEX IF EXISTS key_dhcp4_identifier_subnet_id;
CREATE UNIQUE INDEX key_dhcp4_identifier_subnet_id ON hosts
        (dhcp_identifier ASC, dhcp_identifier_type ASC, dhcp4_subnet_id ASC)
    WHERE (dhcp4_subnet_id IS NOT NULL);

DROP INDEX IF EXISTS key_dhcp6_identifier_subnet_id;
CREATE UNIQUE INDEX key_dhcp6_identifier_subnet_id ON hosts
        (dhcp_identifier ASC, dhcp_identifier_type ASC, dhcp6_subnet_id ASC)
    WHERE (dhcp6_subnet_id IS NOT NULL);

-- Update the schema version number.
UPDATE schema_version
    SET version = '13', minor = '0';

-- This line concludes the schema upgrade to version 13.0.

-- This line starts the schema upgrade to version 14.0.

-- Add cancelled (aka never-send) column to option tables.

ALTER TABLE dhcp4_options ADD COLUMN cancelled BOOLEAN NOT NULL DEFAULT 'f';
ALTER TABLE dhcp6_options ADD COLUMN cancelled BOOLEAN NOT NULL DEFAULT 'f';

-- Add offer_lifetime column to v4 tables.
ALTER TABLE dhcp4_shared_network
    ADD COLUMN offer_lifetime BIGINT DEFAULT NULL;

ALTER TABLE dhcp4_subnet
    ADD COLUMN offer_lifetime BIGINT DEFAULT NULL;

ALTER TABLE dhcp4_client_class
    ADD COLUMN offer_lifetime BIGINT DEFAULT NULL;

-- Update the schema version number.
UPDATE schema_version
    SET version = '14', minor = '0';

-- This line concludes the schema upgrade to version 14.0.

-- This line starts the schema upgrade to version 15.0.

-- Add relay and remote id columns to DHCPv4 leases.
--
-- Note: these columns are only used for indexes, in particular they are
-- not exported by lease4 dump as values are also in the user context
ALTER TABLE lease4
    ADD COLUMN relay_id BYTEA DEFAULT NULL,
    ADD COLUMN remote_id BYTEA DEFAULT NULL;

-- Create relay and remote id indexes.
CREATE INDEX lease4_by_relay_id ON lease4 (relay_id);
CREATE INDEX lease4_by_remote_id ON lease4 (remote_id);

-- Update the schema version number.
UPDATE schema_version
    SET version = '15', minor = '0';

-- This line concludes the schema upgrade to version 15.0.

-- This line starts the schema upgrade to version 16.0.

-- Add the allocator column to the DHCPv4 tables.
ALTER TABLE dhcp4_subnet ADD COLUMN allocator TEXT DEFAULT NULL;
ALTER TABLE dhcp4_shared_network ADD COLUMN allocator TEXT DEFAULT NULL;

-- Add allocator and pd_allocator to the DHCPv6 subnet tables.
ALTER TABLE dhcp6_subnet ADD COLUMN allocator TEXT DEFAULT NULL;
ALTER TABLE dhcp6_subnet ADD COLUMN pd_allocator TEXT DEFAULT NULL;

-- Add allocator and pd_allocator to the DHCPv6 shared network tables.
ALTER TABLE dhcp6_shared_network ADD COLUMN allocator TEXT DEFAULT NULL;
ALTER TABLE dhcp6_shared_network ADD COLUMN pd_allocator TEXT DEFAULT NULL;

-- Update the schema version number.
UPDATE schema_version
    SET version = '16', minor = '0';

-- This line concludes the schema upgrade to version 16.0.

-- This line starts the schema upgrade to version 17.0.

UPDATE lease6 SET duid = E'\\x000000' WHERE duid = E'\\x00';

-- Add pool_id column to the lease4 table.
ALTER TABLE lease4
    ADD COLUMN pool_id BIGINT NOT NULL DEFAULT 0;

-- Add pool_id column to the lease6 table.
ALTER TABLE lease6
    ADD COLUMN pool_id BIGINT NOT NULL DEFAULT 0;

-- Create v4 lease statistics table
CREATE TABLE lease4_pool_stat (
    subnet_id BIGINT NOT NULL,
    pool_id BIGINT NOT NULL,
    state INT8 NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, pool_id, state)
);

-- Create v6 lease statistics table
CREATE TABLE lease6_pool_stat (
    subnet_id BIGINT NOT NULL,
    pool_id BIGINT NOT NULL,
    lease_type SMALLINT NOT NULL,
    state INT8 NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, pool_id, lease_type, state)
);

CREATE OR REPLACE FUNCTION lease4_AINS_lease4_pool_stat(IN new_state BIGINT,
                                                        IN new_subnet_id BIGINT,
                                                        IN new_pool_id BIGINT)
RETURNS VOID
AS $$
BEGIN
    IF new_state = 0 OR new_state = 1 THEN
        -- Update the state count if it exists.
        UPDATE lease4_pool_stat SET leases = leases + 1
            WHERE subnet_id = new_subnet_id AND pool_id = new_pool_id
            AND state = new_state;

        -- Insert the state count record if it does not exist.
        IF NOT FOUND THEN
            INSERT INTO lease4_pool_stat
            VALUES (new_subnet_id, new_pool_id, new_state, 1);
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease4_AUPD_lease4_pool_stat(IN old_state BIGINT,
                                                        IN old_subnet_id BIGINT,
                                                        IN old_pool_id BIGINT,
                                                        IN new_state BIGINT,
                                                        IN new_subnet_id BIGINT,
                                                        IN new_pool_id BIGINT)
RETURNS VOID
AS $$
BEGIN
    IF old_subnet_id != new_subnet_id OR
       old_pool_id != new_pool_id OR
       old_state != new_state THEN
        IF old_state = 0 OR old_state = 1 THEN
            -- Decrement the old state count if record exists.
            UPDATE lease4_pool_stat
                SET leases = GREATEST(leases - 1, 0)
                WHERE subnet_id = old_subnet_id AND pool_id = old_pool_id
                AND state = old_state;
        END IF;

        IF new_state = 0 OR new_state = 1 THEN
            -- Increment the new state count if record exists.
            UPDATE lease4_pool_stat SET leases = leases + 1
                WHERE subnet_id = new_subnet_id AND pool_id = new_pool_id
                AND state = new_state;

            -- Insert new state record if it does not exist.
            IF NOT FOUND THEN
                INSERT INTO lease4_pool_stat
                VALUES (new_subnet_id, new_pool_id, new_state, 1);
            END IF;
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease4_ADEL_lease4_pool_stat(IN old_state BIGINT,
                                                        IN old_subnet_id BIGINT,
                                                        IN old_pool_id BIGINT)
RETURNS VOID
AS $$
BEGIN
    IF old_state = 0 OR old_state = 1 THEN
        -- Decrement the state count if record exists.
        UPDATE lease4_pool_stat
            SET leases = GREATEST(leases - 1, 0)
            WHERE subnet_id = old_subnet_id AND pool_id = old_pool_id
            AND state = old_state;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_AINS_lease6_pool_stat(IN new_state BIGINT,
                                                        IN new_subnet_id BIGINT,
                                                        IN new_pool_id BIGINT,
                                                        IN new_lease_type SMALLINT)
RETURNS VOID
AS $$
BEGIN
    IF new_state = 0 OR new_state = 1 THEN
        -- Update the state count if it exists.
        UPDATE lease6_pool_stat SET leases = leases + 1
            WHERE subnet_id = new_subnet_id AND pool_id = new_pool_id
            AND lease_type = new_lease_type AND state = new_state;

        -- Insert the state count record if it does not exist.
        IF NOT FOUND THEN
            INSERT INTO lease6_pool_stat
            VALUES (new_subnet_id, new_pool_id, new_lease_type, new_state, 1);
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_AUPD_lease6_pool_stat(IN old_state BIGINT,
                                                        IN old_subnet_id BIGINT,
                                                        IN old_pool_id BIGINT,
                                                        IN old_lease_type SMALLINT,
                                                        IN new_state BIGINT,
                                                        IN new_subnet_id BIGINT,
                                                        IN new_pool_id BIGINT,
                                                        IN new_lease_type SMALLINT)
RETURNS VOID
AS $$
BEGIN
    IF old_subnet_id != new_subnet_id OR
       old_pool_id != new_pool_id OR
       old_lease_type != new_lease_type OR
       old_state != new_state THEN
        IF old_state = 0 OR old_state = 1 THEN
            -- Decrement the old state count if record exists.
            UPDATE lease6_pool_stat
                SET leases = GREATEST(leases - 1, 0)
                WHERE subnet_id = old_subnet_id AND pool_id = old_pool_id
                AND lease_type = old_lease_type AND state = old_state;
        END IF;

        IF new_state = 0 OR new_state = 1 THEN
            -- Increment the new state count if record exists
            UPDATE lease6_pool_stat SET leases = leases + 1
                WHERE subnet_id = new_subnet_id AND pool_id = new_pool_id
                AND lease_type = new_lease_type AND state = new_state;

            -- Insert new state record if it does not exist
            IF NOT FOUND THEN
                INSERT INTO lease6_pool_stat
                VALUES (new_subnet_id, new_pool_id, new_lease_type, new_state, 1);
            END IF;
        END IF;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION lease6_ADEL_lease6_pool_stat(IN old_state BIGINT,
                                                        IN old_subnet_id BIGINT,
                                                        IN old_pool_id BIGINT,
                                                        IN old_lease_type SMALLINT)
RETURNS VOID
AS $$
BEGIN
    IF old_state = 0 OR old_state = 1 THEN
        -- Decrement the state count if record exists
        UPDATE lease6_pool_stat
            SET leases = GREATEST(leases - 1, 0)
            WHERE subnet_id = old_subnet_id AND pool_id = old_pool_id
            AND lease_type = old_lease_type AND state = old_state;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_lease4_AINS()
RETURNS trigger AS $lease4_AINS$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease4_AINS_lease4_stat_by_client_class(NEW.state, NEW.user_context);
    END IF;
    PERFORM lease4_AINS_lease4_stat(NEW.state, NEW.subnet_id);
    PERFORM lease4_AINS_lease4_pool_stat(NEW.state, NEW.subnet_id, NEW.pool_id);
    RETURN NULL;
END;
$lease4_AINS$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_lease4_AUPD()
RETURNS trigger AS $lease4_AUPD$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease4_AUPD_lease4_stat_by_client_class(OLD.state, OLD.user_context, NEW.state, NEW.user_context);
    END IF;
    PERFORM lease4_AUPD_lease4_stat(OLD.state, OLD.subnet_id, NEW.state, NEW.subnet_id);
    PERFORM lease4_AUPD_lease4_pool_stat(OLD.state, OLD.subnet_id, OLD.pool_id, NEW.state, NEW.subnet_id, NEW.pool_id);
    RETURN NULL;
END;
$lease4_AUPD$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_lease4_ADEL()
RETURNS trigger AS $lease4_ADEL$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease4_ADEL_lease4_stat_by_client_class(OLD.state, OLD.user_context);
    END IF;
    PERFORM lease4_ADEL_lease4_stat(OLD.state, OLD.subnet_id);
    PERFORM lease4_ADEL_lease4_pool_stat(OLD.state, OLD.subnet_id, OLD.pool_id);
    RETURN NULL;
END;
$lease4_ADEL$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_lease6_AINS()
RETURNS trigger AS $lease6_AINS$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease6_AINS_lease6_stat_by_client_class(NEW.state, NEW.user_context, NEW.lease_type);
    END IF;
    PERFORM lease6_AINS_lease6_stat(NEW.state, NEW.subnet_id, NEW.lease_type);
    PERFORM lease6_AINS_lease6_pool_stat(NEW.state, NEW.subnet_id, NEW.pool_id, NEW.lease_type);
    RETURN NULL;
END;
$lease6_AINS$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_lease6_AUPD()
RETURNS trigger AS $lease6_AUPD$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease6_AUPD_lease6_stat_by_client_class(OLD.state, OLD.user_context, OLD.lease_type, NEW.state, NEW.user_context, NEW.lease_type);
    END IF;
    PERFORM lease6_AUPD_lease6_stat(OLD.state, OLD.subnet_id, OLD.lease_type, NEW.state, NEW.subnet_id, NEW.lease_type);
    PERFORM lease6_AUPD_lease6_pool_stat(OLD.state, OLD.subnet_id, OLD.pool_id, OLD.lease_type, NEW.state, NEW.subnet_id, NEW.pool_id, NEW.lease_type);
    RETURN NULL;
END;
$lease6_AUPD$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_lease6_ADEL()
RETURNS trigger AS $lease6_ADEL$
BEGIN
    IF isJsonSupported() = true THEN
        PERFORM lease6_ADEL_lease6_stat_by_client_class(OLD.state, OLD.user_context, OLD.lease_type);
    END IF;
    PERFORM lease6_ADEL_lease6_stat(OLD.state, OLD.subnet_id, OLD.lease_type);
    PERFORM lease6_ADEL_lease6_pool_stat(OLD.state, OLD.subnet_id, OLD.pool_id, OLD.lease_type);
    RETURN NULL;
END;
$lease6_ADEL$ LANGUAGE plpgsql;

DROP FUNCTION IF EXISTS lease4DumpHeader();
CREATE OR REPLACE FUNCTION lease4DumpHeader()
RETURNS text AS $$
    select cast('address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context,pool_id' as text) as result;
$$ LANGUAGE SQL;

-- Adding support for pool ID in function to output a memfile-ready CSV file.
-- Some columns that are SMALLINT in the lease4 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
DROP FUNCTION IF EXISTS lease4DumpData();
CREATE OR REPLACE FUNCTION lease4DumpData()
RETURNS TABLE (
    address INET,
    hwaddr VARCHAR,
    client_id VARCHAR,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id BIGINT,
    fqdn_fwd INT,
    fqdn_rev INT,
    hostname VARCHAR,
    state INT8,
    user_context VARCHAR,
    pool_id BIGINT
) AS $$
    SELECT
        ('0.0.0.0'::inet + address),
        colonSeparatedHex(encode(hwaddr, 'hex')),
        colonSeparatedHex(encode(client_id, 'hex')),
        valid_lifetime,
        extract(epoch from expire)::bigint,
        subnet_id,
        fqdn_fwd::int,
        fqdn_rev::int,
        replace(hostname, ',', '&#x2c'),
        state,
        replace(user_context, ',', '&#x2c'),
        pool_id
    FROM lease4
    ORDER BY address;
$$ LANGUAGE SQL;

DROP FUNCTION IF EXISTS lease6DumpHeader();
CREATE OR REPLACE FUNCTION lease6DumpHeader()
RETURNS TEXT AS $$
    SELECT CAST('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,state,user_context,hwtype,hwaddr_source,pool_id' AS TEXT) AS result;
$$ LANGUAGE SQL;

-- Adding support for pool ID in function to output a memfile-ready CSV file.
-- Some columns that are SMALLINT in the lease6 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
DROP FUNCTION IF EXISTS lease6DumpData();
CREATE OR REPLACE FUNCTION lease6DumpData()
RETURNS TABLE (
    address VARCHAR,
    duid VARCHAR,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id BIGINT,
    pref_lifetime BIGINT,
    lease_type SMALLINT,
    iaid INT,
    prefix_len SMALLINT,
    fqdn_fwd INT,
    fqdn_rev INT,
    hostname VARCHAR,
    hwaddr VARCHAR,
    state INT8,
    user_context VARCHAR,
    hwtype SMALLINT,
    hwaddr_source SMALLINT,
    pool_id BIGINT
) AS $$
    SELECT
        address,
        colonSeparatedHex(encode(duid, 'hex')),
        valid_lifetime,
        extract(epoch from expire)::bigint,
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd::int,
        fqdn_rev::int,
        replace(hostname, ',', '&#x2c'),
        colonSeparatedHex(encode(hwaddr, 'hex')),
        state,
        replace(user_context, ',', '&#x2c'),
        hwtype,
        hwaddr_source,
        pool_id
    FROM lease6
    ORDER BY address;
$$ LANGUAGE SQL;

-- Adding support for pool id in function that inserts a v4 lease from memfile data.
-- Some columns that are SMALLINT in the lease4 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
CREATE OR REPLACE FUNCTION lease4Upload(
    IN address VARCHAR,
    IN hwaddr VARCHAR,
    IN client_id VARCHAR,
    IN valid_lifetime BIGINT,
    IN expire BIGINT,
    IN subnet_id BIGINT,
    IN fqdn_fwd INT,
    IN fqdn_rev INT,
    IN hostname VARCHAR,
    IN state INT8,
    IN user_context VARCHAR,
    IN pool_id BIGINT
) RETURNS VOID AS $$
BEGIN
    INSERT INTO lease4 (
        address,
        hwaddr,
        client_id,
        valid_lifetime,
        expire,
        subnet_id,
        fqdn_fwd,
        fqdn_rev,
        hostname,
        state,
        user_context,
        pool_id
    ) VALUES (
        address::inet - '0.0.0.0'::inet,
        decode(replace(hwaddr, ':', ''), 'hex'),
        decode(replace(client_id, ':', ''), 'hex'),
        valid_lifetime,
        to_timestamp(expire),
        subnet_id,
        fqdn_fwd::int::boolean,
        fqdn_rev::int::boolean,
        replace(hostname, '&#x2c', ','),
        state,
        replace(user_context, '&#x2c', ','),
        pool_id
    );
END
$$ LANGUAGE plpgsql;

-- Adding support for pool id in function that inserts a v6 lease from memfile data.
-- Some columns that are SMALLINT in the lease6 table have their type promoted
-- to INT in the declaration of this function for backwards compatibility with
-- PostgreSQL versions.
CREATE OR REPLACE FUNCTION lease6Upload(
    IN address VARCHAR,
    IN duid VARCHAR,
    IN valid_lifetime BIGINT,
    IN expire BIGINT,
    IN subnet_id BIGINT,
    IN pref_lifetime BIGINT,
    IN lease_type INT,
    IN iaid INT,
    IN prefix_len INT,
    IN fqdn_fwd INT,
    IN fqdn_rev INT,
    IN hostname VARCHAR,
    IN hwaddr VARCHAR,
    IN state INT8,
    IN user_context VARCHAR,
    IN hwtype INT,
    IN hwaddr_source INT,
    IN pool_id BIGINT
) RETURNS VOID AS $$
BEGIN
    INSERT INTO lease6 (
        address,
        duid,
        valid_lifetime,
        expire,
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd,
        fqdn_rev,
        hostname,
        hwaddr,
        state,
        user_context,
        hwtype,
        hwaddr_source,
        pool_id
    ) VALUES (
        address,
        decode(replace(duid, ':', ''), 'hex'),
        valid_lifetime,
        to_timestamp(expire),
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd::int::boolean,
        fqdn_rev::int::boolean,
        replace(hostname, '&#x2c', ','),
        decode(replace(hwaddr, ':', ''), 'hex'),
        state,
        replace(user_context, '&#x2c', ','),
        hwtype,
        hwaddr_source,
        pool_id
    );
END
$$ LANGUAGE plpgsql;

INSERT INTO lease4_pool_stat (subnet_id, pool_id, state, leases)
    SELECT subnet_id, pool_id, state, count(*) FROM lease4
    WHERE state = 0 OR state = 1 GROUP BY subnet_id, pool_id, state;

INSERT INTO lease6_pool_stat (subnet_id, pool_id, lease_type, state, leases)
    SELECT subnet_id, pool_id, lease_type, state, count(*) FROM lease6
    WHERE state = 0 OR state = 1 GROUP BY subnet_id, pool_id, lease_type, state;

-- Add the binary version of the IPv6 address for v6 BLQ prefix filter.
ALTER TABLE lease6
    ADD COLUMN binaddr BYTEA DEFAULT NULL;
CREATE INDEX lease6_by_binaddr ON lease6 (binaddr ASC);

-- Create table for v6 BLQ by-relay-id.
CREATE TABLE lease6_relay_id (
    extended_info_id SERIAL PRIMARY KEY NOT NULL,
    relay_id BYTEA NOT NULL,
    lease_addr BYTEA NOT NULL);
CREATE INDEX lease6_relay_id_by_id ON lease6_relay_id (relay_id, lease_addr ASC);
CREATE INDEX lease6_relay_id_by_address ON lease6_relay_id (lease_addr);

-- Create table for v6 BLQ by-remote-id.
CREATE TABLE lease6_remote_id (
    extended_info_id SERIAL PRIMARY KEY NOT NULL,
    remote_id BYTEA NOT NULL,
    lease_addr BYTEA NOT NULL);
CREATE INDEX lease6_remote_id_by_id ON lease6_remote_id (remote_id, lease_addr ASC);
CREATE INDEX lease6_remote_id_by_address ON lease6_remote_id (lease_addr);

-- Update the schema version number.
UPDATE schema_version
    SET version = '17', minor = '0';

-- This line concludes the schema upgrade to version 17.0.

-- This line starts the schema upgrade to version 18.0.

-- Drop binaddr index and column from lease6.
DROP INDEX lease6_by_binaddr;
ALTER TABLE lease6
    DROP COLUMN binaddr;

-- Change lease6:address to INET.
ALTER TABLE lease6 ALTER COLUMN address TYPE INET USING address::INET;

-- Change ipv6_reservations:address to INET.
ALTER TABLE ipv6_reservations ALTER COLUMN address TYPE INET USING address::INET;

-- Invoke HOST() on address now that address type is inet
CREATE OR REPLACE FUNCTION lease6DumpData()
RETURNS TABLE (
    address VARCHAR,
    duid VARCHAR,
    valid_lifetime BIGINT,
    expire BIGINT,
    subnet_id BIGINT,
    pref_lifetime BIGINT,
    lease_type SMALLINT,
    iaid INT,
    prefix_len SMALLINT,
    fqdn_fwd INT,
    fqdn_rev INT,
    hostname VARCHAR,
    hwaddr VARCHAR,
    state INT8,
    user_context VARCHAR,
    hwtype SMALLINT,
    hwaddr_source SMALLINT,
    pool_id BIGINT
) AS $$
    SELECT
        HOST(address),
        colonSeparatedHex(encode(duid, 'hex')),
        valid_lifetime,
        extract(epoch from expire)::bigint,
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd::int,
        fqdn_rev::int,
        replace(hostname, ',', '&#x2c'),
        colonSeparatedHex(encode(hwaddr, 'hex')),
        state,
        replace(user_context, ',', '&#x2c'),
        hwtype,
        hwaddr_source,
        pool_id
    FROM lease6
    ORDER BY address;
$$ LANGUAGE SQL;

-- Invoke HOST() on address now that address type is inet
CREATE OR REPLACE FUNCTION lease6Upload(
    IN address VARCHAR,
    IN duid VARCHAR,
    IN valid_lifetime BIGINT,
    IN expire BIGINT,
    IN subnet_id BIGINT,
    IN pref_lifetime BIGINT,
    IN lease_type INT,
    IN iaid INT,
    IN prefix_len INT,
    IN fqdn_fwd INT,
    IN fqdn_rev INT,
    IN hostname VARCHAR,
    IN hwaddr VARCHAR,
    IN state INT8,
    IN user_context VARCHAR,
    IN hwtype INT,
    IN hwaddr_source INT,
    IN pool_id BIGINT
) RETURNS VOID AS $$
BEGIN
    INSERT INTO lease6 (
        address,
        duid,
        valid_lifetime,
        expire,
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd,
        fqdn_rev,
        hostname,
        hwaddr,
        state,
        user_context,
        hwtype,
        hwaddr_source,
        pool_id
    ) VALUES (
        cast(address as inet),
        decode(replace(duid, ':', ''), 'hex'),
        valid_lifetime,
        to_timestamp(expire),
        subnet_id,
        pref_lifetime,
        lease_type,
        iaid,
        prefix_len,
        fqdn_fwd::int::boolean,
        fqdn_rev::int::boolean,
        replace(hostname, '&#x2c', ','),
        decode(replace(hwaddr, ':', ''), 'hex'),
        state,
        replace(user_context, '&#x2c', ','),
        hwtype,
        hwaddr_source,
        pool_id
    );
END
$$ LANGUAGE plpgsql;

-- Update the schema version number.
UPDATE schema_version
    SET version = '18', minor = '0';

-- This line concludes the schema upgrade to version 18.0.

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
