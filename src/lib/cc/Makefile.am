SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-cc.la
libkea_cc_la_SOURCES = data.cc data.h
libkea_cc_la_SOURCES += command_interpreter.cc command_interpreter.h
libkea_cc_la_SOURCES += logger.cc logger.h
nodist_libkea_cc_la_SOURCES = cc_messages.cc cc_messages.h
libkea_cc_la_LIBADD = $(top_builddir)/src/lib/log/libkea-log.la

CLEANFILES = *.gcno *.gcda cc_messages.cc cc_messages.h s-messages

cc_messages.cc cc_messages.h: s-messages

s-messages: cc_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/cc/cc_messages.mes
	touch $@

BUILT_SOURCES = cc_messages.cc cc_messages.h

EXTRA_DIST = cc_messages.mes
