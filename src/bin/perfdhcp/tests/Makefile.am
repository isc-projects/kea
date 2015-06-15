SUBDIRS = . testdata

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(srcdir)/.. -I$(builddir)/..
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_srcdir)/testdata\"
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda
# The test[1-5].hex are created by the TestControl.PacketTemplates
# unit tests and have to be removed.
CLEANFILES += test1.hex test2.hex test3.hex test4.hex test5.hex

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += command_options_unittest.cc
run_unittests_SOURCES += perf_pkt6_unittest.cc
run_unittests_SOURCES += perf_pkt4_unittest.cc
run_unittests_SOURCES += localized_option_unittest.cc
run_unittests_SOURCES += packet_storage_unittest.cc
run_unittests_SOURCES += rate_control_unittest.cc
run_unittests_SOURCES += stats_mgr_unittest.cc
run_unittests_SOURCES += test_control_unittest.cc
run_unittests_SOURCES += command_options_helper.h

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
run_unittests_CXXFLAGS = -Wno-unused-parameter
endif

run_unittests_LDADD  = $(top_builddir)/src/bin/perfdhcp/libperfdhcp.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/bin/cfgrpt/libcfgrpt.la
run_unittests_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
