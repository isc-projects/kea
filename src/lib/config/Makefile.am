SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS) -Wno-strict-aliasing

lib_LTLIBRARIES = libcfgclient.la
libcfgclient_la_SOURCES = config_data.h config_data.cc module_spec.h module_spec.cc ccsession.cc ccsession.h

CLEANFILES = *.gcno *.gcda
