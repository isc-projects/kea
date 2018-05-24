-- -----------------------------------------------------
-- Table `server_configuration4`
-- -----------------------------------------------------
CREATE TABLE server_configuration4 (
    config_id varchar,
    timestamp bigint,
    json_data varchar,
    generic_data varchar,
    PRIMARY KEY ((config_id))
);

-- -----------------------------------------------------
-- Table `server_configuration6`
-- -----------------------------------------------------
CREATE TABLE server_configuration6 (
    config_id varchar,
    timestamp bigint,
    json_data varchar,
    generic_data varchar,
    PRIMARY KEY ((config_id))
);

-- Finally, the version of the schema.  We start at 1.0 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".
CREATE TABLE config_schema_version (
    version int,
    minor int,
    PRIMARY KEY ((version))
);

INSERT INTO config_schema_version (version, minor) VALUES (1, 0);
