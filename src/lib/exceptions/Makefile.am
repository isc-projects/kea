AM_CXXFLAGS=$(B10_CXXFLAGS)

lib_LTLIBRARIES = libexceptions.la
libexceptions_la_SOURCES = exceptions.h exceptions.cc

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc
run_unittests_SOURCES += exceptions_unittest.cc
run_unittests_CPPFLAGS = $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = .libs/libexceptions.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)

libexceptions_includedir = $(includedir)/exceptions
libexceptions_include_HEADERS = exceptions.h
