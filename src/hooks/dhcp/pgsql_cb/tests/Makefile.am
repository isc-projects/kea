SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/pgsql_cb -I$(top_srcdir)/src/hooks/dhcp/pgsql_cb
AM_CPPFLAGS += $(BOOST_INCLUDES) $(PGSQL_CPPFLAGS)
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += pgsql_cb_unittests

pgsql_cb_unittests_SOURCES  = pgsql_cb_impl_unittest.cc
pgsql_cb_unittests_SOURCES  += pgsql_cb_dhcp4_unittest.cc
pgsql_cb_unittests_SOURCES += pgsql_cb_dhcp4_mgr_unittest.cc
pgsql_cb_unittests_SOURCES += pgsql_cb_dhcp6_unittest.cc
pgsql_cb_unittests_SOURCES += pgsql_cb_dhcp6_mgr_unittest.cc
pgsql_cb_unittests_SOURCES += run_unittests.cc

pgsql_cb_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

pgsql_cb_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

pgsql_cb_unittests_CXXFLAGS = $(AM_CXXFLAGS)

pgsql_cb_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/hooks/dhcp/pgsql_cb/libpgsqlcb.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/pgsql/testutils/libpgsqltest.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
pgsql_cb_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
pgsql_cb_unittests_LDADD += $(LOG4CPLUS_LIBS)
pgsql_cb_unittests_LDADD += $(CRYPTO_LIBS)
pgsql_cb_unittests_LDADD += $(BOOST_LIBS)
pgsql_cb_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
