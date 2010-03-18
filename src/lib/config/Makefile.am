AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib -Wno-strict-aliasing
AM_CPPFLAGS += -I$(top_srcdir)/ext

lib_LTLIBRARIES = libcfgclient.la
libcfgclient_la_SOURCES = config_data.h config_data.cc module_spec.h module_spec.cc ccsession.cc ccsession.h

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
SUBDIRS = . tests
endif
