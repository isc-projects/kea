SUBDIRS = .

mysqldir = ${datarootdir}/${PACKAGE_NAME}/scripts/mysql

# non-executable
mysql_DATA  =
mysql_DATA += dhcpdb_create.mysql
mysql_DATA += dhcpdb_drop.mysql

# executable
mysql_SCRIPTS  =
mysql_SCRIPTS += upgrade_1.0_to_2.0.sh
mysql_SCRIPTS += upgrade_2.0_to_3.0.sh
mysql_SCRIPTS += upgrade_3.0_to_4.0.sh
mysql_SCRIPTS += upgrade_4.0_to_4.1.sh
mysql_SCRIPTS += upgrade_4.1_to_5.0.sh
mysql_SCRIPTS += upgrade_5.0_to_5.1.sh
mysql_SCRIPTS += upgrade_5.1_to_5.2.sh
mysql_SCRIPTS += upgrade_5.2_to_6.0.sh
mysql_SCRIPTS += upgrade_6.0_to_7.0.sh
mysql_SCRIPTS += upgrade_7.0_to_8.0.sh
mysql_SCRIPTS += upgrade_8.0_to_8.1.sh
mysql_SCRIPTS += upgrade_8.1_to_8.2.sh
mysql_SCRIPTS += upgrade_8.2_to_9.0.sh
mysql_SCRIPTS += upgrade_9.0_to_9.1.sh
mysql_SCRIPTS += upgrade_9.1_to_9.2.sh
mysql_SCRIPTS += upgrade_9.2_to_9.3.sh
mysql_SCRIPTS += upgrade_9.3_to_9.4.sh
mysql_SCRIPTS += upgrade_9.4_to_9.5.sh
mysql_SCRIPTS += upgrade_9.5_to_9.6.sh
mysql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${mysql_SCRIPTS}

EXTRA_DIST = ${mysql_DATA}
