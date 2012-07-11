DROP DATABASE kea;
CREATE DATABASE kea;

CONNECT kea;

CREATE TABLE lease4 (

    # Primary key (serial = BININT UNSIGNED NOT NULL AUTO_INCREMENT UNIQUE)
    lease_id SERIAL,
    addr INT UNSIGNED UNIQUE,

    # The largest hardware address is for Infiniband (20 bytes)
    hwaddr VARCHAR(20),

    # The largest client-id is DUID in DHCPv6 - up to 128 bytes
    client_id VARCHAR(128),

    # Expressed in seconds
    valid_lft INT,

    # Expressed in seconds,
    recycle_time INT DEFAULT 0,

    cltt TIMESTAMP,

    pool_id int,

    fixed BOOL,

    # DDNS stuff
    hostname VARCHAR(255),
    fqdn_fwd BOOL DEFAULT false,
    fqdn_rev BOOL DEFAULT false,

    options TEXT,
    comments TEXT
);

CREATE TABLE lease6 (

    # Primary key (serial = BININT UNSIGNED NOT NULL AUTO_INCREMENT UNIQUE)
    lease_id SERIAL,
    addr CHAR(16) BYTE UNIQUE,

    # The largest hardware address is for Infiniband (20 bytes)
    hwaddr VARCHAR(20),

    # The largest client-id is DUID in DHCPv6 - up to 128 bytes
    client_id VARCHAR(128),

    iaid int unsigned,

    # Used for IA_PD only (tinyint = 0..255)
    prefix_len TINYINT unsigned,

    # Expressed in seconds
    preferred_lft INT,

    # Expressed in seconds
    valid_lft INT,

    # Expressed in seconds,
    recycle_time INT DEFAULT 0,

    cltt TIMESTAMP,

    pool_id int,

    fixed BOOL DEFAULT false,

    hostname VARCHAR(255),
    fqdn_fwd BOOL DEFAULT false,
    fqdn_rev BOOL DEFAULT false,

    options TEXT,
    comments TEXT
);

CREATE TABLE host (
    address BIGINT NULL,
    address6 BIGINT NULL,
    prefix6 BIGINT NULL,
    hostname VARCHAR(255),
    options TEXT,
    comments TEXT
);