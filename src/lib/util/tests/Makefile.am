SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_builddir)\"
# XXX: we'll pollute the top builddir for creating a temporary test file
# used to bind a UNIX domain socket so we can minimize the risk of exceeding
# the limit of file name path size.
AM_CPPFLAGS += -DTEST_DATA_TOPBUILDDIR=\"$(abs_top_builddir)\"
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
run_unittests_SOURCES += base32hex_unittest.cc
run_unittests_SOURCES += base64_unittest.cc
run_unittests_SOURCES += buffer_unittest.cc
run_unittests_SOURCES += fd_share_tests.cc
run_unittests_SOURCES += fd_tests.cc
run_unittests_SOURCES += filename_unittest.cc
run_unittests_SOURCES += hex_unittest.cc
run_unittests_SOURCES += io_utilities_unittest.cc
run_unittests_SOURCES += lru_list_unittest.cc
run_unittests_SOURCES += interprocess_sync_file_unittest.cc
run_unittests_SOURCES += interprocess_sync_null_unittest.cc
run_unittests_SOURCES += memory_segment_local_unittest.cc
run_unittests_SOURCES += qid_gen_unittest.cc
run_unittests_SOURCES += random_number_generator_unittest.cc
run_unittests_SOURCES += sha1_unittest.cc
run_unittests_SOURCES += socketsession_unittest.cc
run_unittests_SOURCES += strutil_unittest.cc
run_unittests_SOURCES += time_utilities_unittest.cc
run_unittests_SOURCES += range_utilities_unittest.cc
run_unittests_SOURCES += addr_utilities_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD = $(top_builddir)/src/lib/util/libb10-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/io/libb10-util-io.la
run_unittests_LDADD += \
	$(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
run_unittests_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
