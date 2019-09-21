SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/high_availability -I$(top_srcdir)/src/hooks/dhcp/high_availability
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DLIBDHCP_HA_SO=\"$(abs_top_builddir)/src/hooks/dhcp/high_availability/.libs/libdhcp_ha.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += ha_unittests

ha_unittests_SOURCES  = command_creator_unittest.cc
ha_unittests_SOURCES += communication_state_unittest.cc
ha_unittests_SOURCES += ha_config_unittest.cc
ha_unittests_SOURCES += ha_impl_unittest.cc
ha_unittests_SOURCES += ha_service_unittest.cc
ha_unittests_SOURCES += ha_test.cc ha_test.h
ha_unittests_SOURCES += query_filter_unittest.cc
ha_unittests_SOURCES += run_unittests.cc

ha_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

ha_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

ha_unittests_CXXFLAGS = $(AM_CXXFLAGS)

ha_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/high_availability/libha.la
ha_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
ha_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
ha_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
ha_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
ha_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
ha_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
ha_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
ha_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
ha_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
ha_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
ha_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
ha_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
ha_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
ha_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
ha_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
ha_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
ha_unittests_LDADD += $(LOG4CPLUS_LIBS)
ha_unittests_LDADD += $(CRYPTO_LIBS)
ha_unittests_LDADD += $(BOOST_LIBS)
ha_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
