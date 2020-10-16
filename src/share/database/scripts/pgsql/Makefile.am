SUBDIRS = .

UPGRADE_SCRIPTS =
UPGRADE_SCRIPTS += upgrade_1.0_to_2.0.sh
UPGRADE_SCRIPTS += upgrade_2.0_to_3.0.sh
UPGRADE_SCRIPTS += upgrade_3.0_to_3.1.sh
UPGRADE_SCRIPTS += upgrade_3.1_to_3.2.sh
UPGRADE_SCRIPTS += upgrade_3.2_to_3.3.sh
UPGRADE_SCRIPTS += upgrade_3.3_to_4.0.sh
UPGRADE_SCRIPTS += upgrade_4.0_to_5.0.sh
UPGRADE_SCRIPTS += upgrade_5.0_to_5.1.sh
UPGRADE_SCRIPTS += upgrade_5.1_to_6.0.sh
UPGRADE_SCRIPTS += upgrade_6.0_to_6.1.sh
UPGRADE_SCRIPTS += upgrade_6.1_to_6.2.sh
UPGRADE_SCRIPTS += wipe_data.sh

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql
sqlscripts_DATA = dhcpdb_create.pgsql
sqlscripts_DATA += dhcpdb_drop.pgsql
sqlscripts_DATA += ${UPGRADE_SCRIPTS}

DISTCLEANFILES = ${UPGRADE_SCRIPTS}

EXTRA_DIST = ${sqlscripts_DATA}
