SUBDIRS = .

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/cql
sqlscripts_DATA = dhcpdb_create.cql
sqlscripts_DATA += dhcpdb_drop.cql
sqlscripts_DATA += upgrade_1.0_to_2.0.sh
sqlscripts_DATA += upgrade_2.0_to_3.0.sh
sqlscripts_DATA += upgrade_3.0_to_4.0.sh
sqlscripts_DATA += wipe_data.sh

EXTRA_DIST = ${sqlscripts_DATA}
