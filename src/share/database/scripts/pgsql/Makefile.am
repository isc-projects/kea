SUBDIRS = .

pgsqldir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql

# non-executable
pgsql_DATA  =
pgsql_DATA += dhcpdb_create.pgsql
pgsql_DATA += dhcpdb_drop.pgsql

# executable
pgsql_SCRIPTS  =
pgsql_SCRIPTS += upgrade_001.0_to_002.0.sh
pgsql_SCRIPTS += upgrade_002.0_to_003.0.sh
pgsql_SCRIPTS += upgrade_003.0_to_003.1.sh
pgsql_SCRIPTS += upgrade_003.1_to_003.2.sh
pgsql_SCRIPTS += upgrade_003.2_to_003.3.sh
pgsql_SCRIPTS += upgrade_003.3_to_004.0.sh
pgsql_SCRIPTS += upgrade_004.0_to_005.0.sh
pgsql_SCRIPTS += upgrade_005.0_to_005.1.sh
pgsql_SCRIPTS += upgrade_005.1_to_006.0.sh
pgsql_SCRIPTS += upgrade_006.0_to_006.1.sh
pgsql_SCRIPTS += upgrade_006.1_to_006.2.sh
pgsql_SCRIPTS += upgrade_006.2_to_007.0.sh
pgsql_SCRIPTS += upgrade_007_to_008.sh
pgsql_SCRIPTS += upgrade_008_to_009.sh
pgsql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${pgsql_SCRIPTS}

EXTRA_DIST = ${pgsql_DATA}
