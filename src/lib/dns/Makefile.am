AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_srcdir)/ext

lib_LIBRARIES = libdns.a
libdns_a_SOURCES = name.cc buffer.cc rrset.cc message.cc \
	name.h buffer.h rrset.h message.h data_source.cc data_source.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc name_unittest.cc rrset_unittest.cc
run_unittests_SOURCES += message_unittest.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = ./libdns.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
