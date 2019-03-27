SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-cc.la
libkea_cc_la_SOURCES = data.cc data.h
libkea_cc_la_SOURCES += element_value.h
libkea_cc_la_SOURCES += cfg_to_element.h dhcp_config_error.h
libkea_cc_la_SOURCES += command_interpreter.cc command_interpreter.h
libkea_cc_la_SOURCES += json_feed.cc json_feed.h
libkea_cc_la_SOURCES += simple_parser.cc simple_parser.h
libkea_cc_la_SOURCES += stamped_element.cc stamped_element.h
libkea_cc_la_SOURCES += stamped_value.cc stamped_value.h
libkea_cc_la_SOURCES += user_context.cc user_context.h

libkea_cc_la_LIBADD  = $(top_builddir)/src/lib/util/libkea-util.la
libkea_cc_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_cc_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cc_la_LIBADD += $(BOOST_LIBS)

libkea_cc_la_LDFLAGS = -no-undefined -version-info 7:0:0

# Specify the headers for copying into the installation directory tree.
libkea_cc_includedir = $(pkgincludedir)/cc
libkea_cc_include_HEADERS = \
	cfg_to_element.h \
	command_interpreter.h \
	data.h \
	dhcp_config_error.h \
	element_value.h \
	json_feed.h \
	simple_parser.h \
	stamped_element.h \
	stamped_value.h \
	user_context.h

EXTRA_DIST = cc.dox

CLEANFILES = *.gcno *.gcda
