SHTESTS =

SHTESTS += netconf_tests.sh

noinst_SCRIPTS = netconf_tests.sh

EXTRA_DIST = netconf_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)

CLEANFILES = *.json *.log

DISTCLEANFILES = netconf_tests.sh

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += netconf_unittests

netconf_unittests_SOURCES  = run_unittests.cc
netconf_unittests_SOURCES += netconf_env_unittest.cc

netconf_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
netconf_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)


netconf_unittests_LDADD = $(top_builddir)/src/bin/netconf/libnetconf.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
#netconf_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
netconf_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
netconf_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
netconf_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD) $(SYSREPO_LIBS)
endif

noinst_EXTRA_DIST = configs-list.txt

noinst_PROGRAMS = $(TESTS)
