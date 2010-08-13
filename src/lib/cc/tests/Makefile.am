AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(B10_CXXFLAGS)
if USE_GXX			#XXX: see ../Makefile.am
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
# (TODO: these need to be completed and moved to tests/)
run_unittests_SOURCES = data_unittests.cc session_unittests.cc run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
# TODO: remove PTHREAD_LDFLAGS (and from configure too)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD +=  $(top_builddir)/src/lib/cc/libcc.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/exceptions/libexceptions.la

endif

noinst_PROGRAMS = $(TESTS)
