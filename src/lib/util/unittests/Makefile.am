AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(B10_CXXFLAGS)

noinst_LTLIBRARIES = libutil_unittests.la
libutil_unittests_la_SOURCES = fork.h fork.cc resolver.h
libutil_unittests_la_SOURCES += newhook.h newhook.cc
libutil_unittests_la_SOURCES += testdata.h testdata.cc
if HAVE_GTEST
libutil_unittests_la_SOURCES += resource.h resource.cc
libutil_unittests_la_SOURCES += run_all.h run_all.cc
libutil_unittests_la_SOURCES += textdata.h
libutil_unittests_la_SOURCES += wiredata.h wiredata.cc
endif

# For now, this isn't needed for libutil_unittests
EXTRA_DIST = mock_socketsession.h

libutil_unittests_la_CPPFLAGS = $(AM_CPPFLAGS)
if HAVE_GTEST
libutil_unittests_la_CPPFLAGS += $(GTEST_INCLUDES)
endif

libutil_unittests_la_LIBADD  = $(top_builddir)/src/lib/util/io/libb10-util-io.la
libutil_unittests_la_LIBADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la

CLEANFILES = *.gcno *.gcda
