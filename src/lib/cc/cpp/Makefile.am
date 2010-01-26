AM_CPPFLAGS = -I$(top_srcdir)/src/lib/cc/cpp -I$(top_srcdir)/ext -Wall -Werror

lib_LIBRARIES = libcc.a
libcc_a_SOURCES = data.cc data.h session.cc session.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = data_unittests.cc run_unittests.cc
run_unittests_CPPFLAGS = $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = libcc.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
