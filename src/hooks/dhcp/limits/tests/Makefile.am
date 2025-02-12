SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp -I$(top_srcdir)/src/hooks/dhcp
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

if HAVE_GTEST

TESTS = limits_unit_tests

limits_unit_tests_SOURCES  =
limits_unit_tests_SOURCES += limits_unit_tests_lease_limiting.cc
limits_unit_tests_SOURCES += limits_unit_tests_limit_manager.cc
limits_unit_tests_SOURCES += limits_unit_tests_rate_limiting.cc
limits_unit_tests_SOURCES += limits_unit_tests_main.cc
limits_unit_tests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
limits_unit_tests_CXXFLAGS = $(AM_CXXFLAGS)
limits_unit_tests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

limits_unit_tests_LDADD  = $(top_builddir)/src/hooks/dhcp/limits/liblimits.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
limits_unit_tests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
limits_unit_tests_LDADD += $(LOG4CPLUS_LIBS)
limits_unit_tests_LDADD += $(CRYPTO_LIBS)
limits_unit_tests_LDADD += $(BOOST_LIBS)
limits_unit_tests_LDADD += $(GTEST_LDADD)

noinst_PROGRAMS = $(TESTS)

endif
