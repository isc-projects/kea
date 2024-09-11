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
TESTS += libpgsql_lease_backend_unittests

libpgsql_lease_backend_unittests_SOURCES  = run_unittests.cc
libpgsql_lease_backend_unittests_SOURCES += pgsql_lease_mgr_unittest.cc
libpgsql_lease_backend_unittests_SOURCES += pgsql_lease_extended_info_unittest.cc
libpgsql_lease_backend_unittests_SOURCES += pgsql_bootp_unittest.cc

libpgsql_lease_backend_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libpgsql_lease_backend_unittests_CPPFLAGS += $(PGSQL_CPPFLAGS)

libpgsql_lease_backend_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libpgsql_lease_backend_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
libpgsql_lease_backend_unittests_LDFLAGS += $(PGSQL_LIBS)

libpgsql_lease_backend_unittests_LDADD = $(top_builddir)/src/lib/pgsql_lease_backend/libkea-pgsql-lease-backend.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/pgsql/testutils/libpgsqltest.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libpgsql_lease_backend_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libpgsql_lease_backend_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
