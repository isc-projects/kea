AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libutil_unittests.la
libutil_unittests_la_SOURCES = fork.h fork.cc
libutil_unittests_la_LIBADD = \
	$(top_builddir)/src/lib/util/io/libutil_io.la

CLEANFILES = *.gcno *.gcda
