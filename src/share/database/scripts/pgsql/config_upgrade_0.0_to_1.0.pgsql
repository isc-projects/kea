START TRANSACTION;

-- Upgrade to schema 0.0 begins here:

--
-- Table structure for DHCPv4 server configuration
--
CREATE TABLE IF NOT EXISTS server_configuration4 (
  config_id VARCHAR(36) NOT NULL,
  timestamp TIMESTAMP WITH TIME ZONE NOT NULL,
  json_data BYTEA NOT NULL,
  generic_data BYTEA NOT NULL,
  PRIMARY KEY (config_id)
);

--
-- Table structure for DHCPv6 server configuration
--
CREATE TABLE IF NOT EXISTS server_configuration6 (
  config_id VARCHAR(36) NOT NULL,
  timestamp TIMESTAMP WITH TIME ZONE NOT NULL,
  json_data BYTEA NOT NULL,
  generic_data BYTEA NOT NULL,
  PRIMARY KEY (config_id)
);

-- Finally, the version of the schema.  We start at 0.1 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".
CREATE TABLE IF NOT EXISTS config_schema_version (
    version INT PRIMARY KEY NOT NULL,       -- Major version number
    minor INT                               -- Minor version number
    );

-- Set 1.0 schema version.
INSERT INTO config_schema_version VALUES (1, 0);
-- Schema 1.0 specification ends here.

-- Commit the script transaction
COMMIT;
