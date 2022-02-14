SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/ddns_tuning -I$(top_srcdir)/src/hooks/dhcp/ddns_tuning
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DDDNS_TUNING_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/ddns_tuning/.libs/libdhcp_ddns_tuning.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

# TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)
LOG_COMPILER = $(LIBTOOL)
AM_LOG_FLAGS = --mode=execute

TESTS =
if HAVE_GTEST
TESTS += hook_unittests

hook_unittests_SOURCES = run_unittests.cc
hook_unittests_SOURCES += callout_unittests.cc
hook_unittests_SOURCES += load_unload_unittests.cc

ddns_tuning_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

ddns_tuning_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

ddns_tuning_unittests_CXXFLAGS = $(AM_CXXFLAGS)

ddns_tuning_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
ddns_tuning_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
ddns_tuning_unittests_LDADD += $(LOG4CPLUS_LIBS)
ddns_tuning_unittests_LDADD += $(CRYPTO_LIBS)
ddns_tuning_unittests_LDADD += $(BOOST_LIBS)
ddns_tuning_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
