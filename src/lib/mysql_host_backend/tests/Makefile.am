SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libmysql_host_backend_unittests

libmysql_host_backend_unittests_SOURCES  = run_unittests.cc
libmysql_host_backend_unittests_SOURCES += mysql_host_data_source_unittest.cc

libmysql_host_backend_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libmysql_host_backend_unittests_CPPFLAGS += $(MYSQL_CPPFLAGS)

libmysql_host_backend_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libmysql_host_backend_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
libmysql_host_backend_unittests_LDFLAGS += $(MYSQL_LIBS)

libmysql_host_backend_unittests_LDADD = $(top_builddir)/src/lib/mysql_host_backend/libkea-mysql-host-backend.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libmysql_host_backend_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libmysql_host_backend_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
