CLEANFILES = *.gcno *.gcda

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
# This is here because of juggling with sockaddr pointer.
# It is somehow required by the BSD socket interface, but it
# breaks C++ strict aliasing rules, so we need to ask the compiler
# not to use them.
AM_CPPFLAGS += -fno-strict-aliasing
AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = ../sockcreator.cc ../sockcreator.h
run_unittests_SOURCES += sockcreator_tests.cc
run_unittests_SOURCES += run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/util/io/libutil_io.la
run_unittests_LDADD += \
	$(top_builddir)/src/lib/util/unittests/libutil_unittests.la
endif

noinst_PROGRAMS = $(TESTS)
