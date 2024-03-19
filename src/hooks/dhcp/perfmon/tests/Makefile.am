SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/perfmon -I$(top_srcdir)/src/hooks/dhcp/perfmon
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DPERFMON_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/perfmon/.libs/libdhcp_perfmon.so\"
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
TESTS += perfmon_unittests

perfmon_unittests_SOURCES = run_unittests.cc
perfmon_unittests_SOURCES += monitored_duration_unittests.cc
perfmon_unittests_SOURCES += alarm_unittests.cc
perfmon_unittests_SOURCES += monitored_duration_store_unittests.cc
perfmon_unittests_SOURCES += alarm_store_unittests.cc
perfmon_unittests_SOURCES += perfmon_config_unittests.cc
perfmon_unittests_SOURCES += perfmon_mgr_unittests.cc
perfmon_unittests_SOURCES += duration_key_parser_unittests.cc
perfmon_unittests_SOURCES += alarm_parser_unittests.cc

perfmon_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

perfmon_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

perfmon_unittests_CXXFLAGS = $(AM_CXXFLAGS)

perfmon_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/perfmon/libperfmon.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
perfmon_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
perfmon_unittests_LDADD += $(LOG4CPLUS_LIBS)
perfmon_unittests_LDADD += $(CRYPTO_LIBS)
perfmon_unittests_LDADD += $(BOOST_LIBS)
perfmon_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
