SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/radius -I$(top_srcdir)/src/hooks/dhcp/radius
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/hooks/dhcp/radius/tests\"
AM_CPPFLAGS += -DLIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/radius/.libs/libdhcp_radius.so\"
TEST_DICTIONARY = $(abs_top_srcdir)/src/hooks/dhcp/radius/data/dictionary
AM_CPPFLAGS += -DTEST_DICTIONARY=\"$(TEST_DICTIONARY)\"
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
TESTS += libdhcp_radius_unittests

libdhcp_radius_unittests_SOURCES = run_unittests.cc
libdhcp_radius_unittests_SOURCES += load_unload_unittests.cc

libdhcp_radius_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libdhcp_radius_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libdhcp_radius_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libdhcp_radius_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_radius_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_radius_unittests_LDADD += $(LOG4CPLUS_LIBS)
libdhcp_radius_unittests_LDADD += $(CRYPTO_LIBS)
libdhcp_radius_unittests_LDADD += $(BOOST_LIBS)
libdhcp_radius_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
