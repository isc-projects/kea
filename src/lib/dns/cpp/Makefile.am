lib_LIBRARIES = libdns.a
libdns_a_SOURCES = name.cc name.h

if HAVE_CPPUNIT
TEST_PROGRAM = run_unittests
else
TEST_PROGRAM =
endif

TESTS = $(TEST_PROGRAM)
noinst_PROGRAMS = $(TEST_PROGRAM)
run_unittests_SOURCES = name_unittest.cc name_unittest.h run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(CPPUNIT_INCLUDES)
run_unittests_LDFLAGS = $(CPPUNIT_LDFLAGS)
run_unittests_LDADD = ./libdns.a $(CPPUNIT_LDADD)
