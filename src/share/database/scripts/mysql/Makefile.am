SUBDIRS = .

mysqldir = ${datarootdir}/${PACKAGE_NAME}/scripts/mysql

# non-executable
mysql_DATA  =
mysql_DATA += dhcpdb_create.mysql
mysql_DATA += dhcpdb_drop.mysql

# executable
mysql_SCRIPTS  =
mysql_SCRIPTS += upgrade_001.0_to_002.0.sh
mysql_SCRIPTS += upgrade_002.0_to_003.0.sh
mysql_SCRIPTS += upgrade_003.0_to_004.0.sh
mysql_SCRIPTS += upgrade_004.0_to_004.1.sh
mysql_SCRIPTS += upgrade_004.1_to_005.0.sh
mysql_SCRIPTS += upgrade_005.0_to_005.1.sh
mysql_SCRIPTS += upgrade_005.1_to_005.2.sh
mysql_SCRIPTS += upgrade_005.2_to_006.0.sh
mysql_SCRIPTS += upgrade_006.0_to_007.0.sh
mysql_SCRIPTS += upgrade_007.0_to_008.0.sh
mysql_SCRIPTS += upgrade_008.0_to_008.1.sh
mysql_SCRIPTS += upgrade_008.1_to_008.2.sh
mysql_SCRIPTS += upgrade_008.2_to_009.0.sh
mysql_SCRIPTS += upgrade_009.0_to_009.1.sh
mysql_SCRIPTS += upgrade_009.1_to_009.2.sh
mysql_SCRIPTS += upgrade_009.2_to_009.3.sh
mysql_SCRIPTS += upgrade_009.3_to_009.4.sh
mysql_SCRIPTS += upgrade_009.4_to_009.5.sh
mysql_SCRIPTS += upgrade_009.5_to_009.6.sh
mysql_SCRIPTS += upgrade_009.6_to_010.0.sh
mysql_SCRIPTS += upgrade_010_to_011.sh
mysql_SCRIPTS += upgrade_011_to_012.sh
mysql_SCRIPTS += upgrade_012_to_013.sh
mysql_SCRIPTS += upgrade_013_to_014.sh
mysql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${mysql_SCRIPTS}

EXTRA_DIST = ${mysql_DATA}
