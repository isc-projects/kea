SUBDIRS = .

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/mysql
sqlscripts_DATA = dhcpdb_create.mysql
sqlscripts_DATA += dhcpdb_drop.mysql
sqlscripts_DATA += upgrade_1.0_to_2.0.sh
sqlscripts_DATA += upgrade_2.0_to_3.0.sh
sqlscripts_DATA += upgrade_3.0_to_4.0.sh
sqlscripts_DATA += upgrade_4.0_to_4.1.sh
sqlscripts_DATA += upgrade_4.1_to_5.0.sh
sqlscripts_DATA += upgrade_5.0_to_5.1.sh
sqlscripts_DATA += upgrade_5.1_to_5.2.sh
sqlscripts_DATA += upgrade_5.2_to_6.0.sh
sqlscripts_DATA += upgrade_6.0_to_7.0.sh
sqlscripts_DATA += upgrade_7.0_to_8.0.sh
sqlscripts_DATA += wipe_data.sh

DISTCLEANFILES = upgrade_1.0_to_2.0.sh
DISTCLEANFILES += upgrade_2.0_to_3.0.sh
DISTCLEANFILES += upgrade_3.0_to_4.0.sh
DISTCLEANFILES += upgrade_4.0_to_4.1.sh
DISTCLEANFILES += upgrade_4.1_to_5.0.sh
DISTCLEANFILES += upgrade_5.0_to_5.1.sh
DISTCLEANFILES += upgrade_5.1_to_5.2.sh
DISTCLEANFILES += upgrade_5.2_to_6.0.sh
DISTCLEANFILES += upgrade_6.0_to_7.0.sh
DISTCLEANFILES += upgrade_7.0_to_8.0.sh
DISTCLEANFILES += wipe_data.sh

EXTRA_DIST = ${sqlscripts_DATA}
