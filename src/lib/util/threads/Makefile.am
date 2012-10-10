SUBDIRS = . tests
AM_CXXFLAGS = $(B10_CXXFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)

lib_LTLIBRARIES = libb10-threads.la
libb10_threads_la_SOURCES  = lock.h lock.cc
libb10_threads_la_SOURCES += thread.h thread.cc
libb10_threads_la_SOURCES  += condvar.h condvar.cc
libb10_threads_la_LIBADD = $(top_builddir)/src/lib/exceptions/libb10-exceptions.la

CLEANFILES = *.gcno *.gcda
