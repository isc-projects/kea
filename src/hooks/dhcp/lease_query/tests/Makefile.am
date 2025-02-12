SUBDIRS = .

AM_CPPFLAGS  =
AM_CPPFLAGS += -I$(top_builddir)/src -I$(top_srcdir)/src
AM_CPPFLAGS += -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/lease_query -I$(top_srcdir)/src/hooks/dhcp/lease_query
if HAVE_MYSQL
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/mysql -I$(top_srcdir)/src/hooks/dhcp/mysql
endif
if HAVE_PGSQL
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/pgsql -I$(top_srcdir)/src/hooks/dhcp/pgsql
endif
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/hooks/dhcp/lease_query/tests\"
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
TESTS += lease_query_unittests

lease_query_unittests_SOURCES  = run_unittests.cc
lease_query_unittests_SOURCES += accept_filter4_unittest.cc
lease_query_unittests_SOURCES += accept_filter6_unittest.cc
lease_query_unittests_SOURCES += blq4_utils.h blq6_utils.h
lease_query_unittests_SOURCES += bulk_lease_query4_unittest.cc
lease_query_unittests_SOURCES += bulk_lease_query6_unittest.cc
lease_query_unittests_SOURCES += lease_query_impl4_unittest.cc
lease_query_unittests_SOURCES += lease_query_impl6_unittest.cc
lease_query_unittests_SOURCES += lease_query4_unittest.cc
lease_query_unittests_SOURCES += lease_query6_unittest.cc
lease_query_unittests_SOURCES += lease_query_connection_unittest.cc
lease_query_unittests_SOURCES += lease_query_listener4_unittest.cc
lease_query_unittests_SOURCES += lease_query_listener6_unittest.cc
lease_query_unittests_SOURCES += lease_query_test_client.h
lease_query_unittests_SOURCES += mt_lease_query_mgr4_unittest.cc
lease_query_unittests_SOURCES += mt_lease_query_mgr6_unittest.cc
lease_query_unittests_SOURCES += test_lease_mgr.h

lease_query_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

if HAVE_MYSQL
AM_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif
if HAVE_PGSQL
AM_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif

lease_query_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
if HAVE_MYSQL
lease_query_unittests_LDFLAGS += $(MYSQL_LIBS)
endif
if HAVE_PGSQL
lease_query_unittests_LDFLAGS += $(PGSQL_LIBS)
endif

lease_query_unittests_CXXFLAGS = $(AM_CXXFLAGS)

lease_query_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/lease_query/liblease_query.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/tcp/libkea-tcp.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la

if HAVE_PGSQL
lease_query_unittests_LDADD += $(top_builddir)/src/hooks/dhcp/pgsql/libpgsql.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/pgsql/testutils/libpgsqltest.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
endif
if HAVE_MYSQL
lease_query_unittests_LDADD += $(top_builddir)/src/hooks/dhcp/mysql/libmysql.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
endif

lease_query_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
lease_query_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
lease_query_unittests_LDADD += $(LOG4CPLUS_LIBS)
lease_query_unittests_LDADD += $(CRYPTO_LIBS)
lease_query_unittests_LDADD += $(BOOST_LIBS)
lease_query_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
