AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc  -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"

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
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += dns_service_unittest.cc
run_unittests_SOURCES += dns_server_unittest.cc
run_unittests_SOURCES += io_fetch_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

run_unittests_LDADD  = $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libb10-asiodns.la

run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
run_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
run_unittests_CXXFLAGS += -Wno-unused-parameter
endif
if USE_CLANGPP
# Same for clang++, but we need to turn off -Werror completely.
run_unittests_CXXFLAGS += -Wno-error
endif
endif

noinst_PROGRAMS = $(TESTS)
