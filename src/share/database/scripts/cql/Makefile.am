SUBDIRS = .

UPGRADESCRIPTS =
UPGRADESCRIPTS += upgrade_1.0_to_2.0.sh
UPGRADESCRIPTS += upgrade_2.0_to_3.0.sh
UPGRADESCRIPTS += upgrade_3.0_to_4.0.sh
UPGRADESCRIPTS += upgrade_4.0_to_5.0.sh
UPGRADESCRIPTS += wipe_data.sh

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/cql
sqlscripts_DATA = dhcpdb_create.cql
sqlscripts_DATA += dhcpdb_drop.cql
sqlscripts_DATA += ${UPGRADESCRIPTS}
sqlscripts_SCRIPTS = ${UPGRADESCRIPTS}

DISTCLEANFILES = ${UPGRADESCRIPTS}

EXTRA_DIST = ${sqlscripts_DATA}
