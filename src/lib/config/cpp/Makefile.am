AM_CPPFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/ext -Wall -Werror

lib_LIBRARIES = libcfgclient.a
libcfgclient_a_SOURCES = data_def.h data_def.cc ccsession.cc ccsession.h

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = data_def_unittests.cc run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = libcfgclient.a $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/dns/cpp/libdns.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/cpp/libcc.a
endif

noinst_PROGRAMS = $(TESTS)


