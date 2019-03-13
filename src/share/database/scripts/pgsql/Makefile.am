SUBDIRS = .

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql
sqlscripts_DATA = dhcpdb_create.pgsql
sqlscripts_DATA += dhcpdb_drop.pgsql
sqlscripts_DATA += upgrade_1.0_to_2.0.sh
sqlscripts_DATA += upgrade_2.0_to_3.0.sh
sqlscripts_DATA += upgrade_3.0_to_3.1.sh
sqlscripts_DATA += upgrade_3.1_to_3.2.sh
sqlscripts_DATA += upgrade_3.2_to_3.3.sh
sqlscripts_DATA += upgrade_3.3_to_4.0.sh
sqlscripts_DATA += upgrade_4.0_to_5.0.sh
sqlscripts_DATA += wipe_data.sh

DISTCLEANFILES = upgrade_1.0_to_2.0.sh
DISTCLEANFILES += upgrade_2.0_to_3.0.sh
DISTCLEANFILES += upgrade_3.0_to_3.1.sh
DISTCLEANFILES += upgrade_3.1_to_3.2.sh
DISTCLEANFILES += upgrade_3.2_to_3.3.sh
DISTCLEANFILES += upgrade_3.3_to_4.0.sh
DISTCLEANFILES += upgrade_4.0_to_5.0.sh
DISTCLEANFILES += wipe_data.sh

EXTRA_DIST = ${sqlscripts_DATA}
