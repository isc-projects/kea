AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc
run_unittests_SOURCES += check_test.cc acl_test.cc loader_test.cc
run_unittests_SOURCES += logcheck.h
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/acl/libacl.la
endif

noinst_PROGRAMS = $(TESTS)
