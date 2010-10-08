CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = ../sockcreator.cc ../sockcreator.h
run_unittests_SOURCES += sockcreator_tests.cc
run_unittests_SOURCES += run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
