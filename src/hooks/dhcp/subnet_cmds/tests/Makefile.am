SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/subnet_cmds -I$(top_srcdir)/src/hooks/dhcp/subnet_cmds
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DLIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/subnet_cmds/.libs/libdhcp_subnet_cmds.so\"
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
TESTS += subnet_cmds_unittests

subnet_cmds_unittests_SOURCES = run_unittests.cc
subnet_cmds_unittests_SOURCES += subnet_cmds_unittest.cc subnet_cmds_unittest.h
subnet_cmds_unittests_SOURCES += subnet4_cmds_unittest.cc
subnet_cmds_unittests_SOURCES += subnet6_cmds_unittest.cc

subnet_cmds_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

subnet_cmds_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

subnet_cmds_unittests_CXXFLAGS = $(AM_CXXFLAGS)

subnet_cmds_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
subnet_cmds_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
subnet_cmds_unittests_LDADD += $(LOG4CPLUS_LIBS)
subnet_cmds_unittests_LDADD += $(CRYPTO_LIBS)
subnet_cmds_unittests_LDADD += $(BOOST_LIBS)
subnet_cmds_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
