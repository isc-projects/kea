AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_builddir)/src/lib/util -I$(top_srcdir)/src/util
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += io_address_unittest.cc
run_unittests_SOURCES += io_endpoint_unittest.cc
run_unittests_SOURCES += io_socket_unittest.cc
run_unittests_SOURCES += interval_timer_unittest.cc
run_unittests_SOURCES += tcp_endpoint_unittest.cc
run_unittests_SOURCES += tcp_socket_unittest.cc
run_unittests_SOURCES += udp_endpoint_unittest.cc
run_unittests_SOURCES += udp_socket_unittest.cc
run_unittests_SOURCES += io_service_unittest.cc
run_unittests_SOURCES += dummy_io_callback_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

run_unittests_LDADD = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(GTEST_LDADD)

run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
run_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
run_unittests_CXXFLAGS += -Wno-unused-parameter
endif
endif

noinst_PROGRAMS = $(TESTS)
