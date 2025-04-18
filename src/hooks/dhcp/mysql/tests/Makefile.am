SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/mysql -I$(top_srcdir)/src/hooks/dhcp/mysql
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
TEST_CA_DIR = $(top_srcdir)/src/lib/asiolink/testutils/ca
AM_CPPFLAGS += -DTEST_CA_DIR=\"$(TEST_CA_DIR)\"

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
TESTS += mysql_unittests

mysql_unittests_SOURCES  = mysql_cb_impl_unittest.cc
mysql_unittests_SOURCES += mysql_cb_dhcp4_unittest.cc
mysql_unittests_SOURCES += mysql_cb_dhcp4_mgr_unittest.cc
mysql_unittests_SOURCES += mysql_cb_dhcp6_unittest.cc
mysql_unittests_SOURCES += mysql_cb_dhcp6_mgr_unittest.cc
mysql_unittests_SOURCES += mysql_forensic_unittest.cc
mysql_unittests_SOURCES += mysql_host_data_source_unittest.cc
mysql_unittests_SOURCES += mysql_lease_mgr_unittest.cc
mysql_unittests_SOURCES += mysql_lease_extended_info_unittest.cc
mysql_unittests_SOURCES += mysql_bootp_unittest.cc
mysql_unittests_SOURCES += run_unittests.cc

mysql_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

mysql_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

mysql_unittests_CXXFLAGS = $(AM_CXXFLAGS)

mysql_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/mysql/libmysql.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
mysql_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
mysql_unittests_LDADD += $(LOG4CPLUS_LIBS)
mysql_unittests_LDADD += $(CRYPTO_LIBS)
mysql_unittests_LDADD += $(BOOST_LIBS)
mysql_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
