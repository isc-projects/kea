SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

EXTRA_DIST = libkea_tcp.dox

# Ensure that the message file is included in the distribution
EXTRA_DIST += tcp_messages.mes

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-tcp.la

libkea_tcp_la_SOURCES = tcp_connection.cc tcp_connection.h
libkea_tcp_la_SOURCES += tcp_connection_pool.cc tcp_connection_pool.h
libkea_tcp_la_SOURCES += tcp_listener.cc tcp_listener.h
libkea_tcp_la_SOURCES += mt_tcp_listener_mgr.cc mt_tcp_listener_mgr.h
libkea_tcp_la_SOURCES += tcp_log.cc tcp_log.h
libkea_tcp_la_SOURCES += tcp_messages.cc tcp_messages.h
libkea_tcp_la_SOURCES += tcp_stream_msg.cc tcp_stream_msg.h

libkea_tcp_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_tcp_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_tcp_la_LDFLAGS  = $(AM_LDFLAGS)
libkea_tcp_la_LDFLAGS += -no-undefined -version-info 4:0:0

libkea_tcp_la_LIBADD  = $(top_builddir)/src/lib/hooks/libkea-hooks.la
libkea_tcp_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_tcp_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_tcp_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_tcp_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_tcp_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_tcp_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(CRYPTO_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f tcp_messages.h tcp_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: tcp_messages.h tcp_messages.cc
	@echo Message files regenerated

tcp_messages.h tcp_messages.cc: tcp_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/tcp/tcp_messages.mes

else

messages tcp_messages.h tcp_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_tcp_includedir = $(pkgincludedir)/tcp
libkea_tcp_include_HEADERS = \
    mt_tcp_listener_mgr.h \
    tcp_connection_acceptor.h \
    tcp_connection.h \
    tcp_connection_pool.h \
    tcp_listener.h \
    tcp_log.h \
    tcp_messages.h \
    tcp_stream_msg.h
