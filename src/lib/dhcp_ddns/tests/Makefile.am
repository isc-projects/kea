SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/dhcp_ddns/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdhcp_ddns_unittests

libdhcp_ddns_unittests_SOURCES  = run_unittests.cc
libdhcp_ddns_unittests_SOURCES += ncr_unittests.cc
libdhcp_ddns_unittests_SOURCES += ncr_udp_unittests.cc
libdhcp_ddns_unittests_SOURCES += test_utils.cc test_utils.h

libdhcp_ddns_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

libdhcp_ddns_unittests_CXXFLAGS = $(AM_CXXFLAGS)

libdhcp_ddns_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

libdhcp_ddns_unittests_LDADD = $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdhcp_ddns_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdhcp_ddns_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
libdhcp_ddns_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
