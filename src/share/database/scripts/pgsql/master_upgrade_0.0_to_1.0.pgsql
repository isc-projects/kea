-- All or nothing. Table creation should be atomic.
START TRANSACTION;

-- Table structure for DHCPv4 server configuration
DROP TABLE IF EXISTS server_configuration4;
CREATE TABLE server_configuration4 (
  instance_id VARCHAR(128) NOT NULL,
  timestamp TIMESTAMP WITH TIME ZONE NOT NULL,
  server_config BYTEA NOT NULL,
  config_database BYTEA NOT NULL,
  config_database_name VARCHAR(128) NOT NULL,
  PRIMARY KEY (instance_id)
);

-- Table structure for DHCPv6 server configuration
DROP TABLE IF EXISTS server_configuration6;
CREATE TABLE server_configuration6 (
  instance_id VARCHAR(128) NOT NULL,
  timestamp TIMESTAMP WITH TIME ZONE NOT NULL,
  server_config BYTEA NOT NULL,
  config_database BYTEA NOT NULL,
  config_database_name VARCHAR(128) NOT NULL,
  PRIMARY KEY (instance_id)
);

-- Finally, the version of the schema.  We start at 0.1 during development.
-- This table is only modified during schema upgrades.  For historical reasons
-- (related to the names of the columns in the BIND 10 DNS database file), the
-- first column is called "version" and not "major".
DROP TABLE IF EXISTS master_schema_version;;
CREATE TABLE master_schema_version (
  version INT PRIMARY KEY NOT NULL,
  minor INT
);

-- Set 1.0 schema version.
INSERT INTO master_schema_version VALUES (1, 0);
-- Schema 1.0 specification ends here.

-- Commit the script transaction
COMMIT;
