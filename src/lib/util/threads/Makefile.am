SUBDIRS = . tests
AM_CXXFLAGS = $(KEA_CXXFLAGS) $(SHLIB_CXXFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)

lib_LTLIBRARIES = libkea-threads.la
libkea_threads_la_SOURCES  = api.h
libkea_threads_la_SOURCES += sync.h sync.cc
libkea_threads_la_SOURCES += thread.h thread.cc
libkea_threads_la_LIBADD  = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_threads_la_LIBADD += $(PTHREAD_LDFLAGS)

CLEANFILES = *.gcno *.gcda
