AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(KEA_CXXFLAGS)

noinst_LTLIBRARIES = libutil_unittests.la
libutil_unittests_la_SOURCES = fork.h fork.cc resolver.h
libutil_unittests_la_SOURCES += newhook.h newhook.cc
libutil_unittests_la_SOURCES += testdata.h testdata.cc
if HAVE_GTEST
libutil_unittests_la_SOURCES += resource.h resource.cc
libutil_unittests_la_SOURCES += check_valgrind.h check_valgrind.cc
libutil_unittests_la_SOURCES += run_all.h run_all.cc
libutil_unittests_la_SOURCES += textdata.h
libutil_unittests_la_SOURCES += wiredata.h wiredata.cc
libutil_unittests_la_SOURCES += interprocess_util.h interprocess_util.cc
endif

# For now, this isn't needed for libutil_unittests
EXTRA_DIST = mock_socketsession.h

libutil_unittests_la_CPPFLAGS = $(AM_CPPFLAGS)
if HAVE_GTEST
libutil_unittests_la_CPPFLAGS += $(GTEST_INCLUDES)
endif

libutil_unittests_la_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
libutil_unittests_la_LIBADD  = # $(top_builddir)/src/lib/util/io/libkea-util-io.la
libutil_unittests_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libutil_unittests_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
if HAVE_GTEST
libutil_unittests_la_LIBADD += $(GTEST_LDADD)
endif

CLEANFILES = *.gcno *.gcda
