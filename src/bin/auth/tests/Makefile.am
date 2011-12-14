AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST

TESTS += run_unittests
run_unittests_SOURCES = $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += ../auth_srv.h ../auth_srv.cc
run_unittests_SOURCES += ../auth_log.h ../auth_log.cc
run_unittests_SOURCES += ../query.h ../query.cc
run_unittests_SOURCES += ../change_user.h ../change_user.cc
run_unittests_SOURCES += ../auth_config.h ../auth_config.cc
run_unittests_SOURCES += ../command.h ../command.cc
run_unittests_SOURCES += ../common.h ../common.cc
run_unittests_SOURCES += ../statistics.h ../statistics.cc
run_unittests_SOURCES += auth_srv_unittest.cc
run_unittests_SOURCES += config_unittest.cc
run_unittests_SOURCES += command_unittest.cc
run_unittests_SOURCES += common_unittest.cc
run_unittests_SOURCES += query_unittest.cc
run_unittests_SOURCES += change_user_unittest.cc
run_unittests_SOURCES += statistics_unittest.cc
run_unittests_SOURCES += run_unittests.cc
# This is a temporary workaround for #1206, where the InMemoryClient has been
# moved to an ldopened library. We could add that library to LDADD, but that
# is nonportable. When #1207 is done this becomes moot anyway, and the
# specific workaround is not needed anymore, so we can then remove this
# line again.
run_unittests_SOURCES += ${top_srcdir}/src/lib/datasrc/memory_datasrc.cc


nodist_run_unittests_SOURCES = ../auth_messages.h ../auth_messages.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/testutils/libtestutils.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/datasrc/libdatasrc.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libutil.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libasiodns.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/xfr/libxfr.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
run_unittests_LDADD += $(top_builddir)/src/lib/server_common/libserver_common.la
run_unittests_LDADD += $(top_builddir)/src/lib/nsas/libnsas.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/statistics/libstatistics.la
endif

noinst_PROGRAMS = $(TESTS)
