SUBDIRS = .

# Needed by shell_unittest.py to access python modules like kea_conn.
TESTS_ENVIRONMENT = PYTHONPATH="$(abs_top_srcdir)/src/bin/shell"

# Python tests
PYTESTS = shell_unittest.py

# Shell tests
SHTESTS  =
SHTESTS += ca_basic_auth_tests.sh
SHTESTS += d2_basic_auth_tests.sh
SHTESTS += dhcp4_basic_auth_tests.sh
SHTESTS += dhcp6_basic_auth_tests.sh
SHTESTS += shell_ca_process_tests.sh
SHTESTS += shell_d2_process_tests.sh
SHTESTS += shell_dhcp4_process_tests.sh
SHTESTS += shell_dhcp6_process_tests.sh
SHTESTS += tls_ca_process_tests.sh
SHTESTS += tls_d2_process_tests.sh
SHTESTS += tls_dhcp4_process_tests.sh
SHTESTS += tls_dhcp6_process_tests.sh

# As with every file generated by ./configure, clean them up when running
# "make distclean", but not on "make clean".
DISTCLEANFILES = $(PYTESTS) $(SHTESTS)

if HAVE_GTEST

# Run tests on "make check".
check_SCRIPTS = $(PYTESTS) $(SHTESTS)
TESTS = $(PYTESTS) $(SHTESTS)

endif

# Don't install tests.
noinst_SCRIPTS = $(PYTESTS) $(SHTESTS)
