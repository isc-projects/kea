-- -----------------------------------------------------
-- Table `server_configuration4`
-- -----------------------------------------------------
CREATE TABLE server_configuration4 (
    instance_id varchar,
    timestamp bigint,
    config_database varchar,
    config_database_name varchar,
    server_config varchar,
    PRIMARY KEY ((instance_id))
);

-- Create search indexes for server_configuration4 table
CREATE INDEX IF NOT EXISTS server_configuration4index1 ON server_configuration4 (config_database_name);

-- -----------------------------------------------------
-- Table `server_configuration6`
-- -----------------------------------------------------
CREATE TABLE server_configuration6 (
    instance_id varchar,
    timestamp bigint,
    config_database varchar,
    config_database_name varchar,
    server_config varchar,
    PRIMARY KEY ((instance_id))
);

-- Create search indexes for server_configuration6 table
CREATE INDEX IF NOT EXISTS server_configuration6index1 ON server_configuration6 (config_database_name);

-- Finally, the version of the schema.  We start at 1.0 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".
CREATE TABLE master_schema_version (
    version int,
    minor int,
    PRIMARY KEY ((version))
);

INSERT INTO master_schema_version (version, minor) VALUES (1, 0);
