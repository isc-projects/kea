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
mysql_SCRIPTS += upgrade_014_to_015.sh
mysql_SCRIPTS += upgrade_015_to_016.sh
mysql_SCRIPTS += upgrade_016_to_017.sh
mysql_SCRIPTS += upgrade_017_to_018.sh
mysql_SCRIPTS += upgrade_018_to_019.sh
mysql_SCRIPTS += upgrade_019_to_020.sh
mysql_SCRIPTS += upgrade_020_to_021.sh
mysql_SCRIPTS += upgrade_021_to_022.sh
mysql_SCRIPTS += upgrade_022_to_023.sh
mysql_SCRIPTS += upgrade_023_to_024.sh
mysql_SCRIPTS += upgrade_024_to_025.sh
mysql_SCRIPTS += upgrade_025_to_026.sh
mysql_SCRIPTS += upgrade_026_to_027.sh
mysql_SCRIPTS += upgrade_027_to_028.sh
mysql_SCRIPTS += upgrade_028_to_029.sh
mysql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${mysql_SCRIPTS}

EXTRA_DIST = ${mysql_DATA}
