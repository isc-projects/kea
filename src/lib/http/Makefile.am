SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
http_messages.h http_messages.cc: s-messages

s-messages: http_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/http/http_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = http_messages.h http_messages.cc

# Ensure that the message file is included in the distribution
EXTRA_DIST = http_messages.mes

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda http_messages.h http_messages.cc s-messages

lib_LTLIBRARIES = libkea-http.la
libkea_http_la_SOURCES  = connection.cc connection.h
libkea_http_la_SOURCES += connection_pool.cc connection_pool.h
libkea_http_la_SOURCES += date_time.cc date_time.h
libkea_http_la_SOURCES += http_log.cc http_log.h
libkea_http_la_SOURCES += header_context.h
libkea_http_la_SOURCES += http_acceptor.h
libkea_http_la_SOURCES += http_types.h
libkea_http_la_SOURCES += listener.cc listener.h
libkea_http_la_SOURCES += post_request.cc post_request.h
libkea_http_la_SOURCES += post_request_json.cc post_request_json.h
libkea_http_la_SOURCES += request.cc request.h
libkea_http_la_SOURCES += request_context.h
libkea_http_la_SOURCES += request_parser.cc request_parser.h
libkea_http_la_SOURCES += response.cc response.h
libkea_http_la_SOURCES += response_creator.cc response_creator.h
libkea_http_la_SOURCES += response_creator_factory.h
libkea_http_la_SOURCES += response_json.cc response_json.h

nodist_libkea_http_la_SOURCES = http_messages.cc http_messages.h

libkea_http_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_http_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_http_la_LDFLAGS  = $(AM_LDFLAGS)
libkea_http_la_LDFLAGS += -no-undefined -version-info 0:0:0

libkea_http_la_LIBADD  =
libkea_http_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_http_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_http_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_http_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_http_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_http_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_http_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

# Specify the headers for copying into the installation directory tree.
libkea_process_includedir = $(pkgincludedir)/http
libkea_process_include_HEADERS = \
	http_log.h
