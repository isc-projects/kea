SUBDIRS = .

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/cql
sqlscripts_DATA = dhcpdb_create.cql
sqlscripts_DATA += dhcpdb_drop.cql
sqlscripts_DATA += upgrade_1.0_to_2.0.sh

EXTRA_DIST = ${sqlscripts_DATA}

noinst_EXTRA_DIST = soft_wipe.cql
