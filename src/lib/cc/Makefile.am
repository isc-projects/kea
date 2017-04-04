SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-cc.la
libkea_cc_la_SOURCES = data.cc data.h
libkea_cc_la_SOURCES += cfg_to_element.h dhcp_config_error.h
libkea_cc_la_SOURCES += command_interpreter.cc command_interpreter.h
libkea_cc_la_SOURCES += simple_parser.cc simple_parser.h

libkea_cc_la_LIBADD  = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cc_la_LIBADD += $(BOOST_LIBS)

libkea_cc_la_LDFLAGS = -no-undefined -version-info 2:0:0

# Since data.h is now used in the hooks interface, it needs to be
# installed on target system.
libkea_cc_includedir = $(pkgincludedir)/cc
libkea_cc_include_HEADERS = cfg_to_element.h data.h dhcp_config_error.h

EXTRA_DIST = cc.dox

CLEANFILES = *.gcno *.gcda
