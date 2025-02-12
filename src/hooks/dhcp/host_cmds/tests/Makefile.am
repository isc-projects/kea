SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/host_cmds -I$(top_srcdir)/src/hooks/dhcp/host_cmds
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

TESTS =
if HAVE_GTEST
TESTS += host_cmds_unittests

host_cmds_unittests_SOURCES = run_unittests.cc
host_cmds_unittests_SOURCES += host_cmds_unittest.cc
host_cmds_unittests_SOURCES += host_data_parser_unittest.cc

host_cmds_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

host_cmds_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

host_cmds_unittests_CXXFLAGS = $(AM_CXXFLAGS)

host_cmds_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/host_cmds/libhost_cmds.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
host_cmds_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
host_cmds_unittests_LDADD += $(LOG4CPLUS_LIBS)
host_cmds_unittests_LDADD += $(BOOST_LIBS)
host_cmds_unittests_LDADD += $(CRYPTO_LIBS)
host_cmds_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
