SUBDIRS = testdata .

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DAUTH_OBJ_DIR=\"$(abs_top_builddir)/src/bin/auth\"
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_OWN_DATA_DIR=\"$(abs_top_srcdir)/src/bin/auth/tests/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DDSRC_DIR=\"$(abs_top_builddir)/src/lib/datasrc\"
AM_CPPFLAGS += -DPLUGIN_DATA_PATH=\"$(abs_top_builddir)/src/bin/cfgmgr/plugins\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
# Some test cases cannot work with static link.  To selectively disable such
# tests we signal it via a definition.
AM_CPPFLAGS += -DUSE_STATIC_LINK=1
endif

CLEANFILES = *.gcno *.gcda
CLEANFILES += $(abs_top_builddir)/src/lib/testutils/testdata/does-not-exist.sqlite3

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

# Do not define global tests, use check-local so
# environment can be set (needed for dynamic loading)
TESTS =
if HAVE_GTEST

run_unittests_SOURCES = $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += ../auth_srv.h ../auth_srv.cc
run_unittests_SOURCES += ../auth_log.h ../auth_log.cc
run_unittests_SOURCES += ../query.h ../query.cc
run_unittests_SOURCES += ../auth_config.h ../auth_config.cc
run_unittests_SOURCES += ../command.h ../command.cc
run_unittests_SOURCES += ../common.h ../common.cc
run_unittests_SOURCES += ../statistics.h ../statistics.cc
run_unittests_SOURCES += ../datasrc_config.h ../datasrc_config.cc
run_unittests_SOURCES += datasrc_util.h datasrc_util.cc
run_unittests_SOURCES += auth_srv_unittest.cc
run_unittests_SOURCES += config_unittest.cc
run_unittests_SOURCES += config_syntax_unittest.cc
run_unittests_SOURCES += command_unittest.cc
run_unittests_SOURCES += common_unittest.cc
run_unittests_SOURCES += query_unittest.cc
run_unittests_SOURCES += statistics_unittest.cc
run_unittests_SOURCES += datasrc_config_unittest.cc
run_unittests_SOURCES += run_unittests.cc

nodist_run_unittests_SOURCES = ../auth_messages.h ../auth_messages.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(top_builddir)/src/lib/testutils/libb10-testutils.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/datasrc/libb10-datasrc.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/libb10-dns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/xfr/libb10-xfr.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/server_common/libb10-server-common.la
run_unittests_LDADD += $(top_builddir)/src/lib/nsas/libb10-nsas.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/statistics/libb10-statistics.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/tests/libfake_session.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libb10-threads.la
run_unittests_LDADD += $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)

check-local:
	B10_FROM_BUILD=${abs_top_builddir} ./run_unittests

noinst_PROGRAMS = run_unittests

endif
