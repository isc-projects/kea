AM_CPPFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/ext -Wall -Werror

lib_LIBRARIES = libcc.a
libcc_a_SOURCES = data.cc data.h session.cc session.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = data_unittests.cc run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = libcc.a $(GTEST_LDADD)
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/cpp/.libs/libdns.a
run_unittests_LDADD +=  $(top_builddir)/src/lib/exceptions/cpp/.libs/libexceptions.a
endif

noinst_PROGRAMS = $(TESTS)
