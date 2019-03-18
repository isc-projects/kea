SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-asiodns.la

libkea_asiodns_la_LDFLAGS = -no-undefined -version-info 0:2:0

libkea_asiodns_la_SOURCES = io_fetch.cc io_fetch.h
libkea_asiodns_la_SOURCES += logger.h logger.cc
libkea_asiodns_la_SOURCES += asiodns_messages.cc asiodns_messages.h

EXTRA_DIST = asiodns_messages.mes

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
libkea_asiodns_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_asiodns_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_asiodns_la_LIBADD  = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_asiodns_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_asiodns_la_LIBADD += $(BOOST_LIBS)
libkea_asiodns_la_LIBADD += $(LOG4CPLUS_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f asiodns_messages.h asiodns_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: asiodns_messages.h asiodns_messages.cc
	@echo Message files regenerated

asiodns_messages.h asiodns_messages.cc: asiodns_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/asiodns/asiodns_messages.mes

else

messages asiodns_messages.h asiodns_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_asiodns_includedir = $(pkgincludedir)/asiodns
libkea_asiodns_include_HEADERS = \
	asiodns_messages.h \
	io_fetch.h \
	logger.h

