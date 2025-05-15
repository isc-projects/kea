SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/host_cache -I$(top_srcdir)/src/hooks/dhcp/host_cache
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/hooks/dhcp/host_cache/tests\"
AM_CPPFLAGS += -DLIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/host_cache/.libs/libdhcp_host_cache.so\"
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
TESTS += host_cache_unittests

host_cache_unittests_SOURCES = run_unittests.cc
host_cache_unittests_SOURCES += host_data_source_unittests.cc
host_cache_unittests_SOURCES += cache_unittests.cc
host_cache_unittests_SOURCES += command_unittests.cc

host_cache_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

host_cache_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

host_cache_unittests_CXXFLAGS = $(AM_CXXFLAGS)

host_cache_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/host_cache/libhostcache.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/database/testutils/libdatabasetest.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
host_cache_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
host_cache_unittests_LDADD += $(LOG4CPLUS_LIBS)
host_cache_unittests_LDADD += $(CRYPTO_LIBS)
host_cache_unittests_LDADD += $(BOOST_LIBS)
host_cache_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
