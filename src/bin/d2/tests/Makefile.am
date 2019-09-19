SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
SHTESTS += d2_process_tests.sh

noinst_SCRIPTS = d2_process_tests.sh

EXTRA_DIST  = d2_process_tests.sh.in
EXTRA_DIST += testdata/d2_cfg_tests.json testdata/get_config.json

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/d2/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/ddns\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

DISTCLEANFILES = d2_process_tests.sh test_data_files_config.h

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += d2_unittests

d2_unittests_SOURCES  = d2_unittests.cc
d2_unittests_SOURCES += d2_process_unittests.cc
d2_unittests_SOURCES += d2_cfg_mgr_unittests.cc
d2_unittests_SOURCES += d2_queue_mgr_unittests.cc
d2_unittests_SOURCES += d2_update_message_unittests.cc
d2_unittests_SOURCES += d2_update_mgr_unittests.cc
d2_unittests_SOURCES += d2_zone_unittests.cc
d2_unittests_SOURCES += dns_client_unittests.cc
d2_unittests_SOURCES += nc_add_unittests.cc
d2_unittests_SOURCES += nc_remove_unittests.cc
d2_unittests_SOURCES += nc_test_utils.cc nc_test_utils.h
d2_unittests_SOURCES += nc_trans_unittests.cc
d2_unittests_SOURCES += d2_controller_unittests.cc
d2_unittests_SOURCES += d2_simple_parser_unittest.cc
d2_unittests_SOURCES += parser_unittest.cc parser_unittest.h
d2_unittests_SOURCES += get_config_unittest.cc
d2_unittests_SOURCES += d2_command_unittest.cc

d2_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
d2_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
if HAVE_MYSQL
d2_unittests_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
d2_unittests_LDFLAGS += $(PGSQL_LIBS)
endif
if HAVE_CQL
d2_unittests_LDFLAGS += $(CQL_LIBS)
endif
d2_unittests_LDFLAGS += $(GTEST_LDFLAGS)

d2_unittests_LDADD = $(top_builddir)/src/bin/d2/libd2.la
d2_unittests_LDADD += $(top_builddir)/src/lib/process/testutils/libprocesstest.la
d2_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
d2_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
d2_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
d2_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
d2_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
d2_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
d2_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
d2_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
d2_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
d2_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
d2_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
d2_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
d2_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
d2_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
d2_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
d2_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
