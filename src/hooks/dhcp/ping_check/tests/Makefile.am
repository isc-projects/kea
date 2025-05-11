SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/ping_check -I$(top_srcdir)/src/hooks/dhcp/ping_check
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CPPFLAGS += -DPING_CHECK_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/ping_check/.libs/libdhcp_ping_check.so\"
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
TESTS += ping_check_unittests

ping_check_unittests_SOURCES = run_unittests.cc
ping_check_unittests_SOURCES += icmp_endpoint_unittests.cc
ping_check_unittests_SOURCES += icmp_socket_unittests.cc
ping_check_unittests_SOURCES += ping_context_unittests.cc
ping_check_unittests_SOURCES += ping_context_store_unittests.cc
ping_check_unittests_SOURCES += icmp_msg_unittests.cc
ping_check_unittests_SOURCES += ping_test_utils.h
ping_check_unittests_SOURCES += ping_channel_unittests.cc
ping_check_unittests_SOURCES += ping_check_mgr_unittests.cc
ping_check_unittests_SOURCES += ping_check_config_unittests.cc
ping_check_unittests_SOURCES += config_cache_unittests.cc

ping_check_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

ping_check_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

ping_check_unittests_CXXFLAGS = $(AM_CXXFLAGS)

ping_check_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/ping_check/libping_check.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
ping_check_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
ping_check_unittests_LDADD += $(LOG4CPLUS_LIBS)
ping_check_unittests_LDADD += $(CRYPTO_LIBS)
ping_check_unittests_LDADD += $(BOOST_LIBS)
ping_check_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
