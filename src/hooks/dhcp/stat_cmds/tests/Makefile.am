SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/stat_cmds -I$(top_srcdir)/src/hooks/dhcp/stat_cmds
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DSTAT_CMDS_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/stat_cmds/.libs/libdhcp_stat_cmds.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif
if HAVE_CQL
AM_CPPFLAGS += $(CQL_CPPFLAGS)
endif


AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

# TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)
LOG_COMPILER = $(LIBTOOL)
AM_LOG_FLAGS = --mode=execute

TESTS =
if HAVE_GTEST
TESTS += stat_cmds_unittests

stat_cmds_unittests_SOURCES = run_unittests.cc
stat_cmds_unittests_SOURCES += stat_cmds_unittest.cc

stat_cmds_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

stat_cmds_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

stat_cmds_unittests_CXXFLAGS = $(AM_CXXFLAGS)

stat_cmds_unittests_LDADD = $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
stat_cmds_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
stat_cmds_unittests_LDADD += $(LOG4CPLUS_LIBS)
stat_cmds_unittests_LDADD += $(CRYPTO_LIBS)
stat_cmds_unittests_LDADD += $(BOOST_LIBS)
stat_cmds_unittests_LDADD += $(GTEST_LDADD)

if HAVE_MYSQL
stat_cmds_unittests_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
stat_cmds_unittests_LDFLAGS += $(PGSQL_LIBS)
endif
if HAVE_CQL
stat_cmds_unittests_LDFLAGS += $(CQL_LIBS)
endif

endif
noinst_PROGRAMS = $(TESTS)
