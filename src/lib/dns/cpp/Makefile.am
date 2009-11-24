lib_LIBRARIES = libdns.a
libdns_a_SOURCES = name.cc name.h exceptions.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = exceptions_unittest.cc run_unittests.cc
run_unittests_CPPFLAGS = $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = ./libdns.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
