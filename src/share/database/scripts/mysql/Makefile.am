SUBDIRS = .

UPGRADE_SCRIPTS =
UPGRADE_SCRIPTS += upgrade_1.0_to_2.0.sh
UPGRADE_SCRIPTS += upgrade_2.0_to_3.0.sh
UPGRADE_SCRIPTS += upgrade_3.0_to_4.0.sh
UPGRADE_SCRIPTS += upgrade_4.0_to_4.1.sh
UPGRADE_SCRIPTS += upgrade_4.1_to_5.0.sh
UPGRADE_SCRIPTS += upgrade_5.0_to_5.1.sh
UPGRADE_SCRIPTS += upgrade_5.1_to_5.2.sh
UPGRADE_SCRIPTS += upgrade_5.2_to_6.0.sh
UPGRADE_SCRIPTS += upgrade_6.0_to_7.0.sh
UPGRADE_SCRIPTS += upgrade_7.0_to_8.0.sh
UPGRADE_SCRIPTS += upgrade_8.0_to_8.1.sh
UPGRADE_SCRIPTS += upgrade_8.1_to_8.2.sh
UPGRADE_SCRIPTS += upgrade_8.2_to_9.0.sh
UPGRADE_SCRIPTS += upgrade_9.0_to_9.1.sh
UPGRADE_SCRIPTS += upgrade_9.1_to_9.2.sh
UPGRADE_SCRIPTS += upgrade_9.2_to_9.3.sh
UPGRADE_SCRIPTS += upgrade_9.3_to_9.4.sh
UPGRADE_SCRIPTS += wipe_data.sh

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/mysql
sqlscripts_DATA = dhcpdb_create.mysql
sqlscripts_DATA += dhcpdb_drop.mysql
sqlscripts_DATA += ${UPGRADE_SCRIPTS}

DISTCLEANFILES = ${UPGRADE_SCRIPTS}

EXTRA_DIST = ${sqlscripts_DATA}
