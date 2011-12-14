SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)
AM_CXXFLAGS += -Wno-unused-parameter # see src/lib/cc/Makefile.am
if USE_CLANGPP
AM_CXXFLAGS += -Wno-error
endif

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libxfr.la
libxfr_la_SOURCES = xfrout_client.h xfrout_client.cc
libxfr_la_LIBADD = $(top_builddir)/src/lib/util/io/libutil_io.la
