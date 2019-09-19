SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/scripts -I$(top_srcdir)/src/hooks/dhcp/scripts
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_srcdir)/src/hooks/dhcp/scripts/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

SCRIPTS_LIB = $(top_builddir)/src/hooks/dhcp/scripts/libdhcp_scripts.la

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST = 

CLEANFILES = *.gcno *.gcda
DISTCLEANFILES = test_data_files_config.h

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdhcp_scripts_unittests

libdhcp_scripts_unittests_SOURCES  = 
libdhcp_scripts_unittests_SOURCES += run_unittests.cc
libdhcp_scripts_unittests_SOURCES += dhcp6_unittests.cc
libdhcp_scripts_unittests_SOURCES += scripts_unittests.cc


libdhcp_scripts_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

libdhcp_scripts_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libdhcp_scripts_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libdhcp_scripts_unittests_LDADD = $(top_builddir)/src/hooks/dhcp/scripts/libscripts.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/bin/dhcp6/libdhcp6.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/bin/dhcp6/tests/libdhcp6_tests.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/dhcp/tests/libdhcptest.la

libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_scripts_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_scripts_unittests_LDADD += $(LOG4CPLUS_LIBS)
libdhcp_scripts_unittests_LDADD += $(CRYPTO_LIBS)
libdhcp_scripts_unittests_LDADD += $(BOOST_LIBS)
libdhcp_scripts_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
