SUBDIRS = .

pgsqldir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql

# non-executable
pgsql_DATA  =
pgsql_DATA += dhcpdb_create.pgsql
pgsql_DATA += dhcpdb_drop.pgsql

# executable
pgsql_SCRIPTS  =
pgsql_SCRIPTS += upgrade_1.0_to_2.0.sh
pgsql_SCRIPTS += upgrade_2.0_to_3.0.sh
pgsql_SCRIPTS += upgrade_3.0_to_3.1.sh
pgsql_SCRIPTS += upgrade_3.1_to_3.2.sh
pgsql_SCRIPTS += upgrade_3.2_to_3.3.sh
pgsql_SCRIPTS += upgrade_3.3_to_4.0.sh
pgsql_SCRIPTS += upgrade_4.0_to_5.0.sh
pgsql_SCRIPTS += upgrade_5.0_to_5.1.sh
pgsql_SCRIPTS += upgrade_5.1_to_6.0.sh
pgsql_SCRIPTS += upgrade_6.0_to_6.1.sh
pgsql_SCRIPTS += upgrade_6.1_to_6.2.sh
pgsql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${pgsql_SCRIPTS}

EXTRA_DIST = ${pgsql_DATA}
