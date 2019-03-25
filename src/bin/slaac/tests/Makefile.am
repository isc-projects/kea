SHTESTS =


EXTRA_DIST  = testdata/get_config.json

# test using command-line arguments, so use check-local target instead of TESTS

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/bin -I$(top_builddir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/slaac/tests\"
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/slaac\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

DISTCLEANFILES =

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += slaac_unittests

slaac_unittests_SOURCES = process_unittests.cc
slaac_unittests_SOURCES += nd_unittests.cc
slaac_unittests_SOURCES += cfg_mgr_unittests.cc
slaac_unittests_SOURCES += slaac_unittests.cc

slaac_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
slaac_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

slaac_unittests_LDADD = $(top_builddir)/src/bin/slaac/libslaac.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/process/testutils/libprocesstest.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/eval/libkea-eval.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libkea-dhcp_ddns.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/stats/libkea-stats.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/http/libkea-http.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
#slaac_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
slaac_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
slaac_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
slaac_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
