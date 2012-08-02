SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

pkglibexecdir = $(libexecdir)/@PACKAGE@

CLEANFILES = *.gcno *.gcda

pkglibexec_PROGRAMS = b10-sockcreator

b10_sockcreator_SOURCES = sockcreator.cc sockcreator.h main.cc
b10_sockcreator_LDADD  = $(top_builddir)/src/lib/util/io/libb10-util-io.la
b10_sockcreator_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
