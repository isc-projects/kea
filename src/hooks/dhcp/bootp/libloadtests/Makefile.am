SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/bootp -I$(top_srcdir)/src/hooks/dhcp/bootp
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DLIBDHCP_BOOTP_SO=\"$(abs_top_builddir)/src/hooks/dhcp/bootp/.libs/libdhcp_bootp.so\"
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

if HAVE_GTEST

TESTS = hook_load_unittests

hook_load_unittests_SOURCES  =
hook_load_unittests_SOURCES += load_unload_unittests.cc
hook_load_unittests_SOURCES += run_unittests.cc
hook_load_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
hook_load_unittests_CXXFLAGS = $(AM_CXXFLAGS)
hook_load_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

hook_load_unittests_LDADD  = $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
hook_load_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
hook_load_unittests_LDADD += $(LOG4CPLUS_LIBS)
hook_load_unittests_LDADD += $(CRYPTO_LIBS)
hook_load_unittests_LDADD += $(BOOST_LIBS)
hook_load_unittests_LDADD += $(GTEST_LDADD)

noinst_PROGRAMS = $(TESTS)

endif
