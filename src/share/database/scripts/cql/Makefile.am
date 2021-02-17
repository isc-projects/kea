SUBDIRS = .

cqldir = ${datarootdir}/${PACKAGE_NAME}/scripts/cql

# non-executable
cql_DATA  =
cql_DATA += dhcpdb_create.cql
cql_DATA += dhcpdb_drop.cql

# executable
cql_SCRIPTS  =
cql_SCRIPTS += upgrade_1.0_to_2.0.sh
cql_SCRIPTS += upgrade_2.0_to_3.0.sh
cql_SCRIPTS += upgrade_3.0_to_4.0.sh
cql_SCRIPTS += upgrade_4.0_to_5.0.sh
cql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${cql_SCRIPTS}

EXTRA_DIST = ${cql_DATA}
