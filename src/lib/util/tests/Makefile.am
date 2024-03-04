SUBDIRS = .

AM_CPPFLAGS  =
AM_CPPFLAGS += -DABS_SRCDIR=\"$(abs_srcdir)\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_builddir)\"
AM_CPPFLAGS += -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda
# CSV files are created by unit tests for CSVFile class.
CLEANFILES += *.csv

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += bigint_unittest.cc
run_unittests_SOURCES += boost_time_utils_unittest.cc
run_unittests_SOURCES += buffer_unittest.cc
run_unittests_SOURCES += chrono_time_utils_unittest.cc
run_unittests_SOURCES += csv_file_unittest.cc
run_unittests_SOURCES += dhcp_space_unittest.cc
run_unittests_SOURCES += doubles_unittest.cc
run_unittests_SOURCES += encode_unittest.cc
run_unittests_SOURCES += fd_share_tests.cc
run_unittests_SOURCES += fd_tests.cc
run_unittests_SOURCES += filesystem_unittests.cc
run_unittests_SOURCES += hash_unittest.cc
run_unittests_SOURCES += io_unittests.cc
run_unittests_SOURCES += labeled_value_unittest.cc
run_unittests_SOURCES += memory_segment_common_unittest.cc
run_unittests_SOURCES += memory_segment_common_unittest.h
run_unittests_SOURCES += memory_segment_local_unittest.cc
run_unittests_SOURCES += multi_threading_mgr_unittest.cc
run_unittests_SOURCES += optional_unittest.cc
run_unittests_SOURCES += pid_file_unittest.cc
run_unittests_SOURCES += range_utilities_unittest.cc
run_unittests_SOURCES += readwrite_mutex_unittest.cc
run_unittests_SOURCES += staged_value_unittest.cc
run_unittests_SOURCES += state_model_unittest.cc
run_unittests_SOURCES += stopwatch_unittest.cc
run_unittests_SOURCES += str_unittests.cc
run_unittests_SOURCES += thread_pool_unittest.cc
run_unittests_SOURCES += triplet_unittest.cc
run_unittests_SOURCES += unlock_guard_unittests.cc
run_unittests_SOURCES += utf8_unittest.cc
run_unittests_SOURCES += versioned_csv_file_unittest.cc
run_unittests_SOURCES += watch_socket_unittests.cc
run_unittests_SOURCES += watched_thread_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD  = $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/io/libkea-util-io.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
