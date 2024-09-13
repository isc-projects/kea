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
TESTS += libmysql_lease_backend_unittests

libmysql_lease_backend_unittests_SOURCES  = run_unittests.cc
libmysql_lease_backend_unittests_SOURCES += mysql_lease_mgr_unittest.cc
libmysql_lease_backend_unittests_SOURCES += mysql_lease_extended_info_unittest.cc
libmysql_lease_backend_unittests_SOURCES += mysql_bootp_unittest.cc

libmysql_lease_backend_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libmysql_lease_backend_unittests_CPPFLAGS += $(MYSQL_CPPFLAGS)

libmysql_lease_backend_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libmysql_lease_backend_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
libmysql_lease_backend_unittests_LDFLAGS += $(MYSQL_LIBS)

libmysql_lease_backend_unittests_LDADD = $(top_builddir)/src/lib/mysql_lease_backend/libkea-mysql-lease-backend.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libmysql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libmysql_lease_backend_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
