-- Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")

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

-- Create v4 lease statistics table
CREATE TABLE lease4_stat (
    subnet_id BIGINT NOT NULL,
    state INT8 NOT NULL,
    leases BIGINT,
    PRIMARY KEY (subnet_id, state)
);

--
-- Create v4 insert trigger procedure
CREATE FUNCTION proc_stat_lease4_insert () RETURNS trigger AS $stat_lease4_insert$
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
CREATE FUNCTION proc_stat_lease4_update () RETURNS trigger AS $stat_lease4_update$
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
CREATE FUNCTION proc_stat_lease4_delete () RETURNS trigger AS $stat_lease4_delete$
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
CREATE FUNCTION proc_stat_lease6_insert () RETURNS trigger AS $stat_lease6_insert$
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
CREATE FUNCTION proc_stat_lease6_update () RETURNS trigger AS $stat_lease6_update$
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
CREATE FUNCTION proc_stat_lease6_delete() RETURNS trigger AS $stat_lease6_delete$
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

-- Set 4.0 schema version.
UPDATE schema_version
    SET version = '4', minor = '0';

-- Schema 4.0 specification ends here.

-- Upgrade to schema 5.0 begins here:

-- Add a column holding leases for user context.
ALTER TABLE lease4 ADD COLUMN user_context TEXT;
ALTER TABLE lease6 ADD COLUMN user_context TEXT;

--
DROP FUNCTION IF EXISTS lease4DumpHeader();
CREATE FUNCTION lease4DumpHeader() RETURNS text AS  $$
    select cast('address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context' as text) as result;
$$ LANGUAGE SQL;
--

--
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
CREATE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state,hwaddr,hwtype,hwaddr_source,user_context' as text) as result;
$$ LANGUAGE SQL;
--

--
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

-- Set schema 5.0 version
UPDATE schema_version
   SET version = '5', minor = '0';

-- Schema 5.0 specification ends here.

-- Upgrade to schema 5.1 begins here:

-- Put the auth key in hexadecimal (double size but far more user friendly).
ALTER TABLE hosts ALTER COLUMN auth_key TYPE VARCHAR(32);

-- Set schema 5.1 version
UPDATE schema_version
   SET version = '5', minor = '1';

-- Schema 5.1 specification ends here.

-- Upgrade to schema 6.0 begins here:

START TRANSACTION;

-- Create a lower case hostname index for hosts.
CREATE INDEX hosts_by_hostname ON hosts (lower(hostname))
WHERE hostname IS NOT NULL;

-- Create a hostname index for lease4.
CREATE INDEX lease4_by_hostname ON lease4 (lower(hostname))
WHERE hostname IS NOT NULL;

-- Create a hostname index for lease6.
CREATE INDEX lease6_by_hostname ON lease6 (lower(hostname))
WHERE hostname IS NOT NULL;

-- Set 6.0 schema version.
UPDATE schema_version
    SET version = '6', minor = '0';

-- Schema 6.0 specification ends here.

-- Commit the script transaction
COMMIT;

-- Upgrade to schema 6.1 begins here:

START TRANSACTION;

-- Fix v4 update trigger procedure
CREATE OR REPLACE FUNCTION proc_stat_lease4_update () RETURNS trigger AS $stat_lease4_update$
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
CREATE OR REPLACE FUNCTION proc_stat_lease4_delete () RETURNS trigger AS $stat_lease4_delete$
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
CREATE OR REPLACE FUNCTION proc_stat_lease6_update () RETURNS trigger AS $stat_lease6_update$
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

-- Set 6.1 schema version.
UPDATE schema_version
    SET version = '6', minor = '1';

-- Schema 6.1 specification ends here.

-- Commit the script transaction
COMMIT;

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

-- Update the schema version number
UPDATE schema_version
    SET version = '6', minor = '2';

-- Schema 6.2 specification ends here.

-- Commit the script transaction
COMMIT;

START TRANSACTION;

-- This starts schema update to 7.0. It adds a lot (20+) of tables for the config backend.


-- Adding on update trigger in MySQL is as easy as using this column definition in CREATE TABLE:
-- modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
-- Sadly, Postgres has its own convoluted way of doing this. Luckily, the update pattern is
-- the same in many tables, so we can define the trigger function once and the use it everywhere.

-- First, we need to define a function that will do the actual job.
-- This is used in many, many tables.
CREATE OR REPLACE FUNCTION modification_ts_update()
  RETURNS trigger AS $modification_ts_update$
  BEGIN
    new.modification_ts = CURRENT_TIMESTAMP;
  END;

-- Second, we need to specify which language it was written in.
$modification_ts_update$ LANGUAGE plpgsql;


-- Create table modification and insert values for modification types.
CREATE TABLE modification (
  id smallint NOT NULL,
  modification_type varchar(32) NOT NULL,
  PRIMARY KEY (id)
);
INSERT INTO modification VALUES (0,'create'), (1,'update'), (2,'delete');



-- Now create the table that holds different parameter data types.
CREATE TABLE parameter_data_type (
  id smallint NOT NULL,
  name varchar(32) NOT NULL,
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
  tag varchar(256) NOT NULL,
  description text DEFAULT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE(tag)
);
CREATE INDEX dhcp6_server_idx1 ON dhcp6_server (modification_ts);
CREATE UNIQUE INDEX dhcp6_server_idx2 on dhcp6_server(tag);
CREATE TRIGGER dhcp6_server_modification_ts_update
  AFTER UPDATE ON dhcp6_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

INSERT INTO dhcp6_server VALUES (1,'all','special type: all servers');



-- Create a table for storing IPv6 shared networks
CREATE TABLE dhcp6_shared_network (
  id SERIAL PRIMARY KEY NOT NULL,
  name varchar(128) UNIQUE NOT NULL,
  client_class varchar(128) DEFAULT NULL,
  interface varchar(128) DEFAULT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
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
  ddns_generated_prefix varchar(255) DEFAULT NULL,
  ddns_qualifying_suffix varchar(255) DEFAULT NULL,
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
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
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
  subnet_id SERIAL PRIMARY KEY NOT NULL,
  subnet_prefix varchar(64) UNIQUE NOT NULL,
  client_class varchar(128) DEFAULT NULL,
  interface varchar(128) DEFAULT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  preferred_lifetime BIGINT DEFAULT NULL,
  rapid_commit BOOLEAN DEFAULT NULL,
  rebind_timer BIGINT DEFAULT NULL,
  relay TEXT DEFAULT NULL,
  renew_timer BIGINT DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  shared_network_name varchar(128) DEFAULT NULL,
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
  ddns_generated_prefix varchar(255) DEFAULT NULL,
  ddns_qualifying_suffix varchar(255) DEFAULT NULL,
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
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  client_class varchar(128) DEFAULT NULL,
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
  prefix varchar(45) NOT NULL,
  prefix_length SMALLINT NOT NULL,
  delegated_prefix_length SMALLINT NOT NULL,
  subnet_id BIGINT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  excluded_prefix varchar(45) DEFAULT NULL,
  excluded_prefix_length SMALLINT NOT NULL,
  client_class varchar(128) DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  CONSTRAINT fk_dhcp6_pd_pool_subnet_id FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet(subnet_id)
);

CREATE INDEX dhcp6_pd_pool_idx1 on dhcp6_pd_pool (modification_ts);
CREATE INDEX dhcp6_pd_pool_idx2 on dhcp6_pd_pool (subnet_id);
CREATE TRIGGER dhcp6_pd_pool_modification_ts_update
  AFTER UPDATE ON dhcp6_pd_pool
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();



CREATE TABLE dhcp6_subnet_server (
  subnet_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (subnet_id, server_id),
  CONSTRAINT fk_dhcp6_subnet_server_server_id FOREIGN KEY (server_id) REFERENCES dhcp6_server (id),
  CONSTRAINT fk_dhcp6_subnet_server_subnet_id FOREIGN KEY (subnet_id) REFERENCES dhcp6_subnet (subnet_id),
  UNIQUE (subnet_id, server_id)
);
CREATE INDEX dhcp6_subnet_server_idx1 on dhcp6_subnet_server(server_id);
CREATE INDEX dhcp6_subnet_server_idx2 on dhcp6_subnet_server(modification_ts);
CREATE TRIGGER dhcp6_subnet_server_modification_ts_update
  AFTER UPDATE ON dhcp6_subnet_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();



-- Create table for storing global DHCPv6 parameters.
CREATE TABLE dhcp6_global_parameter (
  id SERIAL PRIMARY KEY NOT NULL,
  name varchar(128) NOT NULL,
  value TEXT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  parameter_type SMALLINT NOT NULL,
  CONSTRAINT fk_dhcp6_global_parameter_type FOREIGN KEY (parameter_type) REFERENCES parameter_data_type(id)
);

CREATE INDEX key_dhcp6_global_parameter_idx1 on dhcp6_global_parameter(modification_ts);
CREATE INDEX key_dhcp6_global_parameter_idx2 on dhcp6_global_parameter(name);

CREATE TRIGGER dhcp6_global_parameter_modification_ts_update
  AFTER UPDATE ON dhcp6_global_parameter
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


CREATE TABLE dhcp6_global_parameter_server (
  parameter_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (parameter_id, server_id),
  CONSTRAINT fk_dhcp6_global_parameter_server_parameter_id FOREIGN KEY (parameter_id)
    REFERENCES dhcp6_global_parameter(id) ON DELETE CASCADE  ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_global_parameter_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp6_server(id) ON DELETE CASCADE  ON UPDATE NO ACTION
);
CREATE INDEX key_dhcp6_global_parameter_server_idx1 on dhcp6_global_parameter_server(modification_ts);
CREATE TRIGGER dhcp6_global_parameter_server_modification_ts_update
  AFTER UPDATE ON dhcp6_global_parameter_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- Create a table for storing DHCPv6 options.
ALTER TABLE dhcp6_options
  ADD COLUMN shared_network_name VARCHAR(128) DEFAULT NULL,
  ADD COLUMN pool_id BIGINT DEFAULT NULL,
  ADD COLUMN pd_pool_id BIGINT DEFAULT NULL,
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
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_id, server_id),
  CONSTRAINT fk_dhcp6_options_server_option_id FOREIGN KEY (option_id)
    REFERENCES dhcp6_options (option_id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp6_options_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp6_server (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX dhcp6_options_server_idx1 on dhcp6_options_server(server_id);
CREATE INDEX dhcp6_options_server_idx2 on dhcp6_options_server(modification_ts);
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
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  is_array BOOLEAN NOT NULL,
  encapsulate VARCHAR(128) NOT NULL,
  record_types VARCHAR DEFAULT NULL,
  user_context JSON DEFAULT NULL
);
CREATE INDEX dhcp6_option_def_idx1 on dhcp6_option_def(modification_ts);
CREATE INDEX dhcp6_option_def_idx2 on dhcp6_option_def(code, space);
CREATE TRIGGER dhcp6_option_def_modification_ts_update
  AFTER UPDATE ON dhcp6_option_def
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- and another table for storing relationship between option definitions and servers.
CREATE TABLE dhcp6_option_def_server (
  option_def_id BIGINT NOT NULL REFERENCES dhcp6_option_def (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  server_id BIGINT NOT NULL REFERENCES dhcp6_server (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_def_id, server_id)
);
CREATE TRIGGER dhcp6_option_def_server_modification_ts_update
  AFTER UPDATE ON dhcp6_option_def_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- Now create two tables for audit revisions...
CREATE TABLE dhcp6_audit_revision (
  id SERIAL PRIMARY KEY NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  log_message text DEFAULT NULL,
  server_id BIGINT DEFAULT NULL
);
CREATE TRIGGER dhcp6_audit_revision_modification_ts_update
  AFTER UPDATE ON dhcp6_audit_revision
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- ... and the DHCPv6 audit itself.
CREATE TABLE dhcp6_audit (
  id SERIAL UNIQUE NOT NULL,
  object_type varchar(256) NOT NULL,
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
CREATE INDEX dhcp6_audit_idx1 on dhcp6_audit (modification_type);
CREATE INDEX dhcp6_audit_idx2 on dhcp6_audit (revision_id);


-- Create table for DHCPv4 servers
CREATE TABLE dhcp4_server (
  id SERIAL PRIMARY KEY NOT NULL,
  tag varchar(256) NOT NULL,
  description text DEFAULT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE(tag)
);
CREATE INDEX dhcp4_server_modification_ts ON dhcp6_server (modification_ts);
CREATE TRIGGER dhcp4_server_modification_ts_update
  AFTER UPDATE ON dhcp4_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

INSERT INTO dhcp4_server VALUES (1,'all','special type: all servers');

-- Create table for storing global DHCPv4 parameters.
CREATE TABLE dhcp4_global_parameter (
  id SERIAL PRIMARY KEY NOT NULL,
  name varchar(128) NOT NULL,
  value TEXT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  parameter_type SMALLINT NOT NULL,
  CONSTRAINT fk_dhcp6_global_parameter_type FOREIGN KEY (parameter_type) REFERENCES parameter_data_type(id)
);
CREATE INDEX dhcp4_global_parameter_idx1 on dhcp4_global_parameter(modification_ts);
CREATE INDEX dhcp4_global_parameter_idx2 on dhcp4_global_parameter(name);

CREATE TRIGGER dhcp4_global_parameter_modification_ts_update
  AFTER UPDATE ON dhcp4_global_parameter
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();

-- and create mapping for the global DHCPv4 parameters mapping to servers
CREATE TABLE dhcp4_global_parameter_server (
  parameter_id BIGINT NOT NULL,
  server_id BIGINT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (parameter_id, server_id),
  CONSTRAINT fk_dhcp4_global_parameter_server_parameter_id FOREIGN KEY (parameter_id)
    REFERENCES dhcp4_global_parameter(id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_global_parameter_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp4_server(id) ON DELETE CASCADE  ON UPDATE NO ACTION
);
CREATE INDEX key_dhcp4_global_parameter_idx1 ON dhcp4_global_parameter_server(modification_ts);
CREATE TRIGGER dhcp4_global_parameter_server_modification_ts_update
  AFTER UPDATE ON dhcp4_global_parameter_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- Create a table for storing IPv4 shared networks
CREATE TABLE dhcp4_shared_network (
  id SERIAL PRIMARY KEY NOT NULL,
  name varchar(128) UNIQUE NOT NULL,
  client_class varchar(128) DEFAULT NULL,
  interface varchar(128) DEFAULT NULL,
  match_client_id BOOLEAN DEFAULT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
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
  boot_file_name VARCHAR(129) DEFAULT NULL, -- bootfile field is 128 bytes (plus \0 char)
  next_server inet DEFAULT NULL,   -- let's use type inet
  server_hostname varchar(65) DEFAULT NULL, -- sname is 64 bytes long (plus \0 char)
  min_valid_lifetime BIGINT DEFAULT NULL,
  max_valid_lifetime BIGINT DEFAULT NULL,
  ddns_send_updates BOOLEAN DEFAULT NULL,
  ddns_override_no_update BOOLEAN DEFAULT NULL,
  ddns_override_client_update BOOLEAN DEFAULT NULL,
  ddns_replace_client_name INT8 DEFAULT NULL,
  ddns_generated_prefix varchar(255) DEFAULT NULL,
  ddns_qualifying_suffix varchar(255) DEFAULT NULL,
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


-- Create a list of IPv4 subnets
CREATE TABLE dhcp4_subnet (
  subnet_id SERIAL PRIMARY KEY NOT NULL,
  subnet_prefix VARCHAR(64) UNIQUE NOT NULL,
  interface_4o6 VARCHAR(128) DEFAULT NULL,
  interface_id_4o6 VARCHAR(128) DEFAULT NULL,
  subnet_4o6 VARCHAR(64) DEFAULT NULL,
  boot_file_name varchar(129) DEFAULT NULL, -- note the field is 128 bytes long (plus extra \0 char to keep it in memory)
  client_class varchar(128) DEFAULT NULL,
  interface varchar(128) DEFAULT NULL,
  match_client_id BOOLEAN DEFAULT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  next_server inet DEFAULT NULL,
  rebind_timer BIGINT DEFAULT NULL,
  relay TEXT DEFAULT NULL,
  renew_timer BIGINT DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  server_hostname varchar(65) DEFAULT NULL, -- sname is 64 bytes long (plus \0 char)
  shared_network_name varchar(128) DEFAULT NULL,
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
  ddns_generated_prefix varchar(255) DEFAULT NULL,
  ddns_qualifying_suffix varchar(255) DEFAULT NULL,
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


-- Create a table that holds all address pools in IPv4.
CREATE TABLE dhcp4_pool (
  id SERIAL PRIMARY KEY NOT NULL,
  start_address inet NOT NULL,
  end_address inet NOT NULL,
  subnet_id BIGINT NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  client_class varchar(128) DEFAULT NULL,
  require_client_classes TEXT DEFAULT NULL,
  user_context JSON DEFAULT NULL,
  CONSTRAINT fk_dhcp4_pool_subnet_id FOREIGN KEY (subnet_id) REFERENCES dhcp4_subnet (subnet_id)
);
CREATE INDEX dhcp4_pool_idx1 ON dhcp4_pool (modification_ts);
CREATE INDEX dhcp4_pool_idx2 ON dhcp4_pool (subnet_id);

CREATE TRIGGER dhcp4_pool_modification_ts_update
  AFTER UPDATE ON dhcp4_pool
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- Create a table for storing DHCPv4 options.
ALTER TABLE dhcp4_options
  ADD COLUMN shared_network_name VARCHAR(128) DEFAULT NULL,
  ADD COLUMN pool_id BIGINT DEFAULT NULL,
  ADD COLUMN modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
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
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_id, server_id),
  CONSTRAINT fk_dhcp4_options_server_option_id FOREIGN KEY (option_id)
    REFERENCES dhcp4_options (option_id) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_options_server_server_id FOREIGN KEY (server_id)
    REFERENCES dhcp4_server (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE INDEX dhcp4_options_server_idx1 on dhcp4_options_server(server_id);
CREATE INDEX dhcp4_options_server_idx2 on dhcp4_options_server(modification_ts);
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
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  is_array BOOLEAN NOT NULL,
  encapsulate VARCHAR(128) NOT NULL,
  record_types VARCHAR DEFAULT NULL,
  user_context JSON DEFAULT NULL
);
CREATE INDEX dhcp4_option_def_idx1 on dhcp4_option_def(modification_ts);
CREATE INDEX dhcp4_option_def_idx2 on dhcp4_option_def(code, space);
CREATE TRIGGER dhcp4_option_def_modification_ts_update
  AFTER UPDATE ON dhcp4_option_def
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- and another table for storing relationship between option definitions and servers.
CREATE TABLE dhcp4_option_def_server (
  option_def_id BIGINT NOT NULL REFERENCES dhcp6_option_def (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  server_id BIGINT NOT NULL REFERENCES dhcp4_server (id) ON DELETE CASCADE ON UPDATE NO ACTION,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (option_def_id, server_id)
);
CREATE TRIGGER dhcp4_option_def_server_modification_ts_update
  AFTER UPDATE ON dhcp4_option_def_server
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();



-- Now create two tables for audit revisions...
CREATE TABLE dhcp4_audit_revision (
  id SERIAL PRIMARY KEY NOT NULL,
  modification_ts timestamp with time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
  log_message text DEFAULT NULL,
  server_id BIGINT DEFAULT NULL
);
CREATE TRIGGER dhcp4_audit_revision_modification_ts_update
  AFTER UPDATE ON dhcp4_audit_revision
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();


-- ... and the DHCPv4 audit itself.
CREATE TABLE dhcp4_audit (
  id SERIAL UNIQUE NOT NULL,
  object_type varchar(256) NOT NULL,
  object_id BIGINT NOT NULL,
  modification_type SMALLINT NOT NULL,
  revision_id BIGINT NOT NULL,
  CONSTRAINT fk_dhcp4_audit_modification_type FOREIGN KEY (modification_type)
    REFERENCES modification (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT fk_dhcp4_audit_revision FOREIGN KEY (revision_id)
    REFERENCES dhcp4_audit_revision (id) ON DELETE NO ACTION ON UPDATE CASCADE
);
CREATE TRIGGER dhcp4_audit_modification_ts_update
  AFTER UPDATE ON dhcp6_audit
  FOR EACH ROW EXECUTE PROCEDURE modification_ts_update();
CREATE INDEX dhcp4_audit_idx1 on dhcp4_audit (modification_type);
CREATE INDEX dhcp4_audit_idx2 on dhcp4_audit (revision_id);



-- Update the schema version number
UPDATE schema_version
    SET version = '7', minor = '0';

-- Schema 7.0 specification ends here.

-- Commit the script transaction
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
