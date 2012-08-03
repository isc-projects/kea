AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_builddir)/src/bin/resolver
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests

run_unittests_SOURCES = $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += ../resolver.h ../resolver.cc
run_unittests_SOURCES += ../resolver_log.h ../resolver_log.cc
run_unittests_SOURCES += ../response_scrubber.h ../response_scrubber.cc
run_unittests_SOURCES += resolver_unittest.cc
run_unittests_SOURCES += resolver_config_unittest.cc
run_unittests_SOURCES += response_scrubber_unittest.cc
run_unittests_SOURCES += run_unittests.cc

nodist_run_unittests_SOURCES = ../resolver_messages.h ../resolver_messages.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

run_unittests_LDADD  = $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/testutils/libb10-testutils.la
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/acl/libb10-dnsacl.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/xfr/libb10-xfr.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/server_common/libb10-server-common.la
run_unittests_LDADD += $(top_builddir)/src/lib/resolve/libb10-resolve.la
run_unittests_LDADD += $(top_builddir)/src/lib/cache/libb10-cache.la
run_unittests_LDADD += $(top_builddir)/src/lib/nsas/libb10-nsas.la
run_unittests_LDADD += $(top_builddir)/src/lib/acl/libb10-acl.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la

# Note the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS
run_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
run_unittests_CXXFLAGS += -Wno-unused-parameter
endif
endif

noinst_PROGRAMS = $(TESTS)
