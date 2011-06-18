SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

EXTRA_DIST = check.h acl.h

lib_LTLIBRARIES = libacl.la

libacl_la_SOURCES = ip_check.h ip_check.cc
