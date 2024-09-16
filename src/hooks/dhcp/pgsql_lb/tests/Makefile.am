SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/pgsql_lb -I$(top_srcdir)/src/hooks/dhcp/pgsql_lb
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += pgsql_lb_unittests

pgsql_lb_unittests_SOURCES  = run_unittests.cc
pgsql_lb_unittests_SOURCES += pgsql_lease_mgr_unittest.cc
pgsql_lb_unittests_SOURCES += pgsql_lease_extended_info_unittest.cc
pgsql_lb_unittests_SOURCES += pgsql_bootp_unittest.cc

pgsql_lb_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
pgsql_lb_unittests_CPPFLAGS += $(PGSQL_CPPFLAGS)

pgsql_lb_unittests_CXXFLAGS = $(AM_CXXFLAGS)

pgsql_lb_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
pgsql_lb_unittests_LDFLAGS += $(PGSQL_LIBS)

pgsql_lb_unittests_LDADD = $(top_builddir)/src/hooks/dhcp/pgsql_lb/libpgsqllb.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/pgsql/testutils/libpgsqltest.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
pgsql_lb_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
pgsql_lb_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)

