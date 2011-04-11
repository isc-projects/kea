AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/util -I$(top_srcdir)/src/util
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += io_address_unittest.cc
run_unittests_SOURCES += io_endpoint_unittest.cc
run_unittests_SOURCES += io_fetch_unittest.cc
run_unittests_SOURCES += io_socket_unittest.cc
run_unittests_SOURCES += io_service_unittest.cc
run_unittests_SOURCES += interval_timer_unittest.cc
run_unittests_SOURCES += tcp_endpoint_unittest.cc
run_unittests_SOURCES += tcp_socket_unittest.cc
run_unittests_SOURCES += udp_endpoint_unittest.cc
run_unittests_SOURCES += udp_socket_unittest.cc
run_unittests_SOURCES += dns_server_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

run_unittests_LDADD  = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libutil.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la

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
