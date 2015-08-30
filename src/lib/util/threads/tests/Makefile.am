SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
# XXX: we'll pollute the top builddir for creating a temporary test file
# # used to bind a UNIX domain socket so we can minimize the risk of exceeding
# # the limit of file name path size.
AM_CPPFLAGS += -DTEST_DATA_TOPBUILDDIR=\"$(abs_top_builddir)\"
AM_CXXFLAGS = $(KEA_CXXFLAGS)

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
run_unittests_SOURCES += thread_unittest.cc
run_unittests_SOURCES += lock_unittest.cc
run_unittests_SOURCES += condvar_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

run_unittests_LDADD = $(top_builddir)/src/lib/util/threads/libkea-threads.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
