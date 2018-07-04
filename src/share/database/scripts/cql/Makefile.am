SUBDIRS = .

sqlscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts/cql
sqlscripts_DATA  = dhcpdb_create.cql
sqlscripts_DATA += dhcpdb_drop.cql
sqlscripts_DATA += configdb_create.cql
sqlscripts_DATA += config_upgrade_0.0_to_1.0.cql
sqlscripts_DATA += config_upgrade_0.0_to_1.0.sh
sqlscripts_DATA += masterdb_create.cql
sqlscripts_DATA += master_upgrade_0.0_to_1.0.cql
sqlscripts_DATA += master_upgrade_0.0_to_1.0.sh
sqlscripts_DATA += upgrade_1.0_to_2.0.sh
sqlscripts_DATA += soft_wipe.cql

EXTRA_DIST = ${sqlscripts_DATA}
