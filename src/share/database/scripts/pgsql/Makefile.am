SUBDIRS = .

pgsqldir = ${datarootdir}/${PACKAGE_NAME}/scripts/pgsql

# non-executable
pgsql_DATA  =
pgsql_DATA += dhcpdb_create.pgsql
pgsql_DATA += dhcpdb_drop.pgsql

# executable
pgsql_SCRIPTS  =
pgsql_SCRIPTS += upgrade_001.0_to_002.0.sh
pgsql_SCRIPTS += upgrade_002.0_to_003.0.sh
pgsql_SCRIPTS += upgrade_003.0_to_003.1.sh
pgsql_SCRIPTS += upgrade_003.1_to_003.2.sh
pgsql_SCRIPTS += upgrade_003.2_to_003.3.sh
pgsql_SCRIPTS += upgrade_003.3_to_004.0.sh
pgsql_SCRIPTS += upgrade_004.0_to_005.0.sh
pgsql_SCRIPTS += upgrade_005.0_to_005.1.sh
pgsql_SCRIPTS += upgrade_005.1_to_006.0.sh
pgsql_SCRIPTS += upgrade_006.0_to_006.1.sh
pgsql_SCRIPTS += upgrade_006.1_to_006.2.sh
pgsql_SCRIPTS += upgrade_006.2_to_007.0.sh
pgsql_SCRIPTS += upgrade_007_to_008.sh
pgsql_SCRIPTS += upgrade_008_to_009.sh
pgsql_SCRIPTS += upgrade_009_to_010.sh
pgsql_SCRIPTS += upgrade_010_to_011.sh
pgsql_SCRIPTS += upgrade_011_to_012.sh
pgsql_SCRIPTS += upgrade_012_to_013.sh
pgsql_SCRIPTS += upgrade_013_to_014.sh
pgsql_SCRIPTS += upgrade_014_to_015.sh
pgsql_SCRIPTS += upgrade_015_to_016.sh
pgsql_SCRIPTS += upgrade_016_to_017.sh
pgsql_SCRIPTS += upgrade_017_to_018.sh
pgsql_SCRIPTS += upgrade_018_to_019.sh
pgsql_SCRIPTS += upgrade_019_to_020.sh
pgsql_SCRIPTS += upgrade_020_to_021.sh
pgsql_SCRIPTS += upgrade_021_to_022.sh
pgsql_SCRIPTS += upgrade_022_to_023.sh
pgsql_SCRIPTS += upgrade_023_to_024.sh
pgsql_SCRIPTS += upgrade_024_to_025.sh
pgsql_SCRIPTS += upgrade_025_to_026.sh
pgsql_SCRIPTS += upgrade_026_to_027.sh
pgsql_SCRIPTS += upgrade_027_to_028.sh
pgsql_SCRIPTS += upgrade_028_to_029.sh
pgsql_SCRIPTS += wipe_data.sh

DISTCLEANFILES = ${pgsql_SCRIPTS}

EXTRA_DIST = ${pgsql_DATA}
