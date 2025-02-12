SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/radius -I$(top_srcdir)/src/hooks/dhcp/radius
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/hooks/dhcp/radius/tests\"
AM_CPPFLAGS += -DLIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/radius/.libs/libdhcp_radius.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
DICTIONARY = $(sysconfdir)/@PACKAGE@/radius/dictionary
AM_CPPFLAGS += -DDICTIONARY=\"$(DICTIONARY)\"
TEST_DICTIONARY = $(abs_top_srcdir)/src/hooks/dhcp/radius/data/dictionary
AM_CPPFLAGS += -DDICTIONARY=\"$(DICTIONARY)\"
AM_CPPFLAGS += -DTEST_DICTIONARY=\"$(TEST_DICTIONARY)\"

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
TESTS += radius_unittests

# unit tests are in logical (vs alphabetic) order.
radius_unittests_SOURCES  = run_unittests.cc
radius_unittests_SOURCES += attribute_test.cc attribute_test.h
radius_unittests_SOURCES += dictionary_unittests.cc
radius_unittests_SOURCES += attribute_unittests.cc
radius_unittests_SOURCES += message_unittests.cc
radius_unittests_SOURCES += server_unittests.cc
radius_unittests_SOURCES += exchange_unittests.cc
radius_unittests_SOURCES += config_unittests.cc
radius_unittests_SOURCES += utils_unittests.cc
radius_unittests_SOURCES += request_unittests.h
radius_unittests_SOURCES += sync_request_unittests.cc
radius_unittests_SOURCES += async_request_unittests.cc
radius_unittests_SOURCES += backend_unittests.cc
radius_unittests_SOURCES += access_unittests.cc
radius_unittests_SOURCES += accounting_unittests.cc

radius_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

radius_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

radius_unittests_CXXFLAGS = $(AM_CXXFLAGS)

radius_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/radius/libradius.la
radius_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
radius_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
radius_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
radius_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
radius_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
radius_unittests_LDADD += $(top_builddir)/src/lib/dhcp/testutils/libdhcptest.la
radius_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
radius_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
radius_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
radius_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
radius_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
radius_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
radius_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
radius_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
radius_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
radius_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
radius_unittests_LDADD += $(LOG4CPLUS_LIBS)
radius_unittests_LDADD += $(CRYPTO_LIBS)
radius_unittests_LDADD += $(BOOST_LIBS)
radius_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
