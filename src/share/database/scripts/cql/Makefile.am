SUBDIRS = .

UPGRADE_SCRIPTS =
UPGRADE_SCRIPTS += upgrade_1.0_to_2.0.sh
UPGRADE_SCRIPTS += upgrade_2.0_to_3.0.sh
UPGRADE_SCRIPTS += upgrade_3.0_to_4.0.sh
UPGRADE_SCRIPTS += upgrade_4.0_to_5.0.sh
UPGRADE_SCRIPTS += wipe_data.sh

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/cql
sqlscripts_DATA = dhcpdb_create.cql
sqlscripts_DATA += dhcpdb_drop.cql
sqlscripts_DATA += ${UPGRADE_SCRIPTS}

DISTCLEANFILES = ${UPGRADE_SCRIPTS}

EXTRA_DIST = ${sqlscripts_DATA}
