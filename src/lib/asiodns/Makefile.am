SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda asiodns_messages.h asiodns_messages.cc s-messages

# Define rule to build logging source files from message file
asiodns_messages.h asiodns_messages.cc: s-messages

s-messages: asiodns_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/asiodns/asiodns_messages.mes
	touch $@

BUILT_SOURCES = asiodns_messages.h asiodns_messages.cc

lib_LTLIBRARIES = libkea-asiodns.la
libkea_asiodns_la_SOURCES = io_fetch.cc io_fetch.h
libkea_asiodns_la_SOURCES += logger.h logger.cc

nodist_libkea_asiodns_la_SOURCES = asiodns_messages.cc asiodns_messages.h

EXTRA_DIST = asiodns_messages.mes

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
libkea_asiodns_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_asiodns_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_asiodns_la_LIBADD  = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_asiodns_la_LIBADD += $(LOG4CPLUS_LIBS)
