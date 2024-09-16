SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/mysql_hb -I$(top_srcdir)/src/hooks/dhcp/mysql_hb
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += mysql_hb_unittests

mysql_hb_unittests_SOURCES  = run_unittests.cc
mysql_hb_unittests_SOURCES += mysql_host_data_source_unittest.cc

mysql_hb_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
mysql_hb_unittests_CPPFLAGS += $(MYSQL_CPPFLAGS)

mysql_hb_unittests_CXXFLAGS = $(AM_CXXFLAGS)

mysql_hb_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
mysql_hb_unittests_LDFLAGS += $(MYSQL_LIBS)

mysql_hb_unittests_LDADD = $(top_builddir)/src/hooks/dhcp/mysql_hb/libmysqlhb.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
mysql_hb_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
mysql_hb_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)

