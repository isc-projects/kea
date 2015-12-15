-- Copyright (C) 2012-2015  Internet Systems Consortium.

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

-- Create search indexes for lease4 table
-- index by iaid, subnet_id, and duid
CREATE INDEX lease6_by_iaid_subnet_id_duid ON lease6 (iaid, subnet_id, duid);

-- ... and a definition of lease6 types.  This table is a convenience for
-- users of the database - if they want to view the lease table and use the
-- type names, they can join this table with the lease6 table
CREATE TABLE lease6_types (
    lease_type SMALLINT PRIMARY KEY NOT NULL,   -- Lease type code.
    name VARCHAR(5)                             -- Name of the lease type
    );
START TRANSACTION;
INSERT INTO lease6_types VALUES (0, 'IA_NA');   -- Non-temporary v6 addresses
INSERT INTO lease6_types VALUES (1, 'IA_TA');   -- Temporary v6 addresses
INSERT INTO lease6_types VALUES (2, 'IA_PD');   -- Prefix delegations
COMMIT;

-- Finally, the version of the schema.  We start at 0.1 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".

-- NOTE: this MUST be kept in step with src/lib/dhcpsrv/tests/schema_copy.h,
--       which defines the schema for the unit tests.  If you are updating
--       the version number, the schema has changed: please ensure that
--       schema_copy.h has been updated as well.
CREATE TABLE schema_version (
    version INT PRIMARY KEY NOT NULL,       -- Major version number
    minor INT                               -- Minor version number
    );
START TRANSACTION;
INSERT INTO schema_version VALUES (1, 0);
COMMIT;

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
START TRANSACTION;
INSERT INTO lease_state VALUES (0, 'default');
INSERT INTO lease_state VALUES (1, 'declined');
INSERT INTO lease_state VALUES (2, 'expired-reclaimed');
COMMIT;

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
--  FUNCTION that returns a result set containing the column names for lease4 dumps
DROP FUNCTION IF EXISTS lease4DumpHeader();
CREATE FUNCTION lease4DumpHeader() RETURNS text AS  $$
    select cast('address,hwaddr,client_id,valid_lifetime,expire,subnet_id,fqdn_fwd,fqdn_rev,hostname,state' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease4 dumps
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
--  FUNCTION that returns a result set containing the column names for lease6 dumps
DROP FUNCTION IF EXISTS lease6DumpHeader();
CREATE FUNCTION lease6DumpHeader() RETURNS text AS  $$
    select cast('address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,state' as text) as result;
$$ LANGUAGE SQL;
--

--
--  FUNCTION that returns a result set containing the data for lease6 dumps
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
START TRANSACTION;
UPDATE schema_version
    SET version = '2', minor = '0';
COMMIT;

-- Schema 2.0 specification ends here.

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
