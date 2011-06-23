SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libacl.la
libacl_la_SOURCES  = check.h
libacl_la_SOURCES += ip_check.h ip_check.cc

libacl_la_CXXFLAGS = $(AM_CXXFLAGS)
libacl_la_CPPFLAGS = $(AM_CPPFLAGS)
libacl_la_LIBADD = $(top_builddir)/src/lib/util/libutil.la
