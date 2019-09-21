SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
SHTESTS += ca_process_tests.sh

noinst_SCRIPTS = ca_process_tests.sh

EXTRA_DIST  = ca_process_tests.sh.in
EXTRA_DIST += testdata/get_config.json

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
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/agent/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/agent\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

DISTCLEANFILES = ca_process_tests.sh test_data_files_config.h test_libraries.h

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

noinst_LTLIBRARIES = libbasic.la

TESTS += ca_unittests

ca_unittests_SOURCES  = ca_cfg_mgr_unittests.cc
ca_unittests_SOURCES += ca_command_mgr_unittests.cc
ca_unittests_SOURCES += ca_controller_unittests.cc
ca_unittests_SOURCES += ca_process_unittests.cc
ca_unittests_SOURCES += ca_response_creator_unittests.cc
ca_unittests_SOURCES += ca_response_creator_factory_unittests.cc
ca_unittests_SOURCES += ca_unittests.cc
ca_unittests_SOURCES += parser_unittests.cc
ca_unittests_SOURCES += get_config_unittest.cc

ca_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
ca_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

ca_unittests_LDADD = $(top_builddir)/src/bin/agent/libagent.la
ca_unittests_LDADD += $(top_builddir)/src/lib/process/testutils/libprocesstest.la
ca_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
ca_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
ca_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
ca_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
ca_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
ca_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
ca_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
ca_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
ca_unittests_LDADD += $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
ca_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
ca_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
ca_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
ca_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
ca_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
ca_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
ca_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
ca_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
ca_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
ca_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
ca_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)

# The basic callout library - contains standard callouts
libbasic_la_SOURCES  = basic_library.cc
libbasic_la_CXXFLAGS = $(AM_CXXFLAGS)
libbasic_la_CPPFLAGS = $(AM_CPPFLAGS)
libbasic_la_LIBADD   = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libbasic_la_LIBADD  += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libbasic_la_LIBADD  += $(top_builddir)/src/lib/log/libkea-log.la
libbasic_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

nodist_ca_unittests_SOURCES = test_data_files_config.h test_libraries.h

endif

noinst_PROGRAMS = $(TESTS)
