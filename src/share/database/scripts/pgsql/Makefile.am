SUBDIRS = .

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql
sqlscripts_DATA = dhcpdb_create.pgsql
sqlscripts_DATA += dhcpdb_drop.pgsql
sqlscripts_DATA += upgrade_1.0_to_2.0.sh
sqlscripts_DATA += upgrade_2.0_to_3.0.sh
sqlscripts_DATA += upgrade_3.0_to_3.1.sh

DISTCLEANFILES = upgrade_1.0_to_2.0.sh
DISTCLEANFILES += upgrade_2.0_to_3.0.sh
DISTCLEANFILES += upgrade_3.0_to_3.1.s

EXTRA_DIST = ${sqlscripts_DATA}
