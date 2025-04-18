SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/lease_cmds -I$(top_srcdir)/src/hooks/dhcp/lease_cmds
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

LOG_COMPILER = $(LIBTOOL)
AM_LOG_FLAGS = --mode=execute

TESTS =
if HAVE_GTEST
TESTS += lease_cmds_unittests

lease_cmds_unittests_SOURCES = run_unittests.cc
lease_cmds_unittests_SOURCES += binding_variables_unittest.cc
lease_cmds_unittests_SOURCES += lease_cmds_func_unittest.h
lease_cmds_unittests_SOURCES += lease_cmds_func4_unittest.cc
lease_cmds_unittests_SOURCES += lease_cmds_func6_unittest.cc

lease_cmds_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

lease_cmds_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

lease_cmds_unittests_CXXFLAGS = $(AM_CXXFLAGS)

lease_cmds_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/lease_cmds/liblease_cmds.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
lease_cmds_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
lease_cmds_unittests_LDADD += $(LOG4CPLUS_LIBS)
lease_cmds_unittests_LDADD += $(CRYPTO_LIBS)
lease_cmds_unittests_LDADD += $(BOOST_LIBS)
lease_cmds_unittests_LDADD += $(GTEST_LDADD)

endif
noinst_PROGRAMS = $(TESTS)
