#!/bin/sh

# Import common library.
. /home/thomson/devel/kea/src/bin/admin/admin-utils.sh

mysql_version "$@"
VERSION=$_RESULT

if [ "$VERSION" != "1.0" ]; then
    printf "This script upgrades 1.0 to 2.0. Reported version is $VERSION. Skipping upgrade.\n"
    exit 0
fi

mysql "$@" <<EOF
ALTER TABLE lease6
    ADD COLUMN hwaddr varbinary(2),
    ADD COLUMN hwtype smallint unsigned,
    ADD COLUMN hwaddr_source int unsigned;

CREATE TABLE lease6_hwaddr_source (
    hwaddr_source INT PRIMARY KEY NOT NULL,
    name VARCHAR(40)
);

-- See src/lib/dhcp/dhcp/pkt.h for detailed explanation
INSERT INTO lease6_hwaddr_source VALUES (1, "HWADDR_SOURCE_RAW");
INSERT INTO lease6_hwaddr_source VALUES (2, "HWADDR_SOURCE_IPV6_LINK_LOCAL");
INSERT INTO lease6_hwaddr_source VALUES (4, "HWADDR_SOURCE_DUID");
INSERT INTO lease6_hwaddr_source VALUES (8, "HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION");
INSERT INTO lease6_hwaddr_source VALUES (16, "HWADDR_SOURCE_REMOTE_ID");
INSERT INTO lease6_hwaddr_source VALUES (32, "HWADDR_SOURCE_SUBSCRIBER_ID");
INSERT INTO lease6_hwaddr_source VALUES (64, "HWADDR_SOURCE_DOCSIS");

UPDATE schema_version SET version="2", minor="0";
EOF

RESULT=$?

exit $?
