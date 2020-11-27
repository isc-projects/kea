SUBDIRS = .

UPGRADESCRIPTS =
UPGRADESCRIPTS += upgrade_1.0_to_2.0.sh
UPGRADESCRIPTS += upgrade_2.0_to_3.0.sh
UPGRADESCRIPTS += upgrade_3.0_to_3.1.sh
UPGRADESCRIPTS += upgrade_3.1_to_3.2.sh
UPGRADESCRIPTS += upgrade_3.2_to_3.3.sh
UPGRADESCRIPTS += upgrade_3.3_to_4.0.sh
UPGRADESCRIPTS += upgrade_4.0_to_5.0.sh
UPGRADESCRIPTS += upgrade_5.0_to_5.1.sh
UPGRADESCRIPTS += upgrade_5.1_to_6.0.sh
UPGRADESCRIPTS += upgrade_6.0_to_6.1.sh
UPGRADESCRIPTS += wipe_data.sh

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql
sqlscripts_DATA = dhcpdb_create.pgsql
sqlscripts_DATA += dhcpdb_drop.pgsql
sqlscripts_DATA += ${UPGRADESCRIPTS}

DISTCLEANFILES = ${UPGRADESCRIPTS}

EXTRA_DIST = ${sqlscripts_DATA}
