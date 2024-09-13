SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/mysql_lb -I$(top_srcdir)/src/hooks/dhcp/mysql_lb
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += mysql_lb_unittests

mysql_lb_unittests_SOURCES  = run_unittests.cc
mysql_lb_unittests_SOURCES += mysql_lease_mgr_unittest.cc
mysql_lb_unittests_SOURCES += mysql_lease_extended_info_unittest.cc
mysql_lb_unittests_SOURCES += mysql_bootp_unittest.cc

mysql_lb_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
mysql_lb_unittests_CPPFLAGS += $(MYSQL_CPPFLAGS)

mysql_lb_unittests_CXXFLAGS = $(AM_CXXFLAGS)

mysql_lb_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
mysql_lb_unittests_LDFLAGS += $(MYSQL_LIBS)

mysql_lb_unittests_LDADD = $(top_builddir)/src/hooks/dhcp/mysql_lb/libmysqllb.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
mysql_lb_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
mysql_lb_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)