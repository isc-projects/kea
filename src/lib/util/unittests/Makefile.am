AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libutil_unittests.la
libutil_unittests_la_SOURCES = fork.h fork.cc resolver.h
libutil_unittests_la_SOURCES += newhook.h newhook.cc
libutil_unittests_la_SOURCES += run_all.h run_all.cc
libutil_unittests_la_SOURCES += testdata.h testdata.cc
libutil_unittests_la_SOURCES += textdata.h

libutil_unittests_la_LIBADD  = $(top_builddir)/src/lib/util/libutil.la
libutil_unittests_la_LIBADD  = $(top_builddir)/src/lib/exceptions/libexceptions.la

CLEANFILES = *.gcno *.gcda
