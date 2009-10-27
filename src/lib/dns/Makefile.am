AM_CPPFLAGS = -I$(top_srcdir)/src/lib

lib_LIBRARIES = libdns.a
libdns_a_SOURCES = name.cc buffer.cc rrset.cc name.h buffer.h rrset.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc name_unittest.cc rrset_unittest.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = ./libdns.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
