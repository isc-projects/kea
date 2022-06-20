SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/flex_option -I$(top_srcdir)/src/hooks/dhcp/flex_option
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DFLEX_OPTION_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/flex_option/.libs/libdhcp_flex_option.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

LOG_COMPILER = $(LIBTOOL)
AM_LOG_FLAGS = --mode=execute

TESTS =
if HAVE_GTEST
TESTS += flex_option_unittests

flex_option_unittests_SOURCES = run_unittests.cc
flex_option_unittests_SOURCES += callout_unittests.cc
flex_option_unittests_SOURCES += load_unload_unittests.cc

flex_option_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

flex_option_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

flex_option_unittests_CXXFLAGS = $(AM_CXXFLAGS)

flex_option_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
flex_option_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
flex_option_unittests_LDADD += $(LOG4CPLUS_LIBS)
flex_option_unittests_LDADD += $(CRYPTO_LIBS)
flex_option_unittests_LDADD += $(BOOST_LIBS)
flex_option_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
