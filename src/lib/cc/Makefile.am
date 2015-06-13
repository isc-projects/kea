SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-cc.la
libkea_cc_la_SOURCES = data.cc data.h
libkea_cc_la_SOURCES += command_interpreter.cc command_interpreter.h
libkea_cc_la_SOURCES += logger.cc logger.h
libkea_cc_la_LIBADD = $(top_builddir)/src/lib/log/libkea-log.la

CLEANFILES = *.gcno *.gcda
