AM_CPPFLAGS = -I$(top_srcdir)/src/lib

lib_LIBRARIES = libdns.a
libdns_a_SOURCES = name.cc buffer.cc name.h buffer.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = name_unittest.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = ./libdns.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
