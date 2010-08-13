AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib

AM_CXXFLAGS = $(B10_CXXFLAGS)
# see src/lib/cc/Makefile.am for -Wno-unused-parameter
if USE_GXX
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libfake_session.la
libfake_session_la_SOURCES = fake_session.h fake_session.cc

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = ccsession_unittests.cc module_spec_unittests.cc config_data_unittests.cc run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD =  $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
run_unittests_LDADD += libfake_session.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
# link *only* to data.o from lib/cc (more importantly, don't link in
# the session class provided there, since we use our own fake_session
# here)
run_unittests_LDADD += $(top_builddir)/src/lib/cc/data.o

endif

noinst_PROGRAMS = $(TESTS)
