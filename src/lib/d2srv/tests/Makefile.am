SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libd2srv_unittests

libd2srv_unittests_SOURCES  = run_unittests.cc
libd2srv_unittests_SOURCES += d2_tsig_key_unittest.cc
libd2srv_unittests_SOURCES += d2_update_message_unittests.cc
libd2srv_unittests_SOURCES += d2_zone_unittests.cc
libd2srv_unittests_SOURCES += dns_client_unittests.cc
libd2srv_unittests_SOURCES += nc_trans_unittests.cc

libd2srv_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libd2srv_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

libd2srv_unittests_LDADD  = $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/d2srv/testutils/libd2srvtest.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libd2srv_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libd2srv_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
