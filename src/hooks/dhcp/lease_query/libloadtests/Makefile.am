SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/lease_query -I$(top_srcdir)/src/hooks/dhcp/lease_query
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/hooks/dhcp/lease_query/libloadtests\"
AM_CPPFLAGS += -DLIBDHCP_LEASE_QUERY_SO=\"$(abs_top_builddir)/src/hooks/dhcp/lease_query/.libs/libdhcp_lease_query.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdhcp_lease_query_unittests

libdhcp_lease_query_unittests_SOURCES = run_unittests.cc
libdhcp_lease_query_unittests_SOURCES += load_unload_unittests.cc

libdhcp_lease_query_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libdhcp_lease_query_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libdhcp_lease_query_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libdhcp_lease_query_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/tcp/libkea-tcp.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/database/testutils/libdatabasetest.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_lease_query_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_lease_query_unittests_LDADD += $(LOG4CPLUS_LIBS)
libdhcp_lease_query_unittests_LDADD += $(CRYPTO_LIBS)
libdhcp_lease_query_unittests_LDADD += $(BOOST_LIBS)
libdhcp_lease_query_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
