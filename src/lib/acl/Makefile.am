SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libacl.la
libacl_la_SOURCES = check.h acl.h
libacl_la_SOURCES += loader.h loader.cc

CLEANFILES = *.gcno *.gcda
