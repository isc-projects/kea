SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
SHTESTS += ctrl_agent_process_tests.sh

noinst_SCRIPTS = ctrl_agent_process_tests.sh

EXTRA_DIST  = ctrl_agent_process_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/agent/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/agent\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

DISTCLEANFILES = ctrl_agent_process_tests.sh

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += ctrl_agent_unittest

ctrl_agent_unittest_SOURCES  = ctrl_agent_cfg_mgr_unittest.cc
ctrl_agent_unittest_SOURCES += ctrl_agent_command_mgr_unittest.cc
ctrl_agent_unittest_SOURCES += ctrl_agent_controller_unittest.cc
ctrl_agent_unittest_SOURCES += ctrl_agent_process_unittest.cc
ctrl_agent_unittest_SOURCES += ctrl_agent_response_creator_unittest.cc
ctrl_agent_unittest_SOURCES += ctrl_agent_response_creator_factory_unittest.cc
ctrl_agent_unittest_SOURCES += ctrl_agent_unittest.cc
ctrl_agent_unittest_SOURCES += parser_unittest.cc

ctrl_agent_unittest_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
ctrl_agent_unittest_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

ctrl_agent_unittest_LDADD = $(top_builddir)/src/bin/agent/libagent.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/process/testutils/libprocesstest.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
ctrl_agent_unittest_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
ctrl_agent_unittest_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
ctrl_agent_unittest_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
