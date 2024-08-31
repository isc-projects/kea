SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/mysql_cb -I$(top_srcdir)/src/hooks/dhcp/mysql_cb
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS)
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
TESTS += mysql_cb_unittests

mysql_cb_unittests_SOURCES  = mysql_cb_dhcp4_unittest.cc
mysql_cb_unittests_SOURCES += mysql_cb_dhcp4_mgr_unittest.cc
mysql_cb_unittests_SOURCES += mysql_cb_dhcp6_unittest.cc
mysql_cb_unittests_SOURCES += mysql_cb_dhcp6_mgr_unittest.cc
mysql_cb_unittests_SOURCES += mysql_cb_impl_unittest.cc
mysql_cb_unittests_SOURCES += run_unittests.cc

mysql_cb_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

mysql_cb_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

mysql_cb_unittests_CXXFLAGS = $(AM_CXXFLAGS)

mysql_cb_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/mysql_cb/libmysqlcb.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
mysql_cb_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
mysql_cb_unittests_LDADD += $(LOG4CPLUS_LIBS)
mysql_cb_unittests_LDADD += $(CRYPTO_LIBS)
mysql_cb_unittests_LDADD += $(BOOST_LIBS)
mysql_cb_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
