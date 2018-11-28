SUBDIRS = . testutils tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Define rule to build logging source files from message file
db_messages.h db_messages.cc: s-messages

s-messages: db_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/database/db_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = db_messages.h db_messages.cc

# Ensure that the message file is included in the distribution
EXTRA_DIST = db_messages.mes

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda db_messages.h db_messages.cc s-messages

lib_LTLIBRARIES = libkea-database.la
libkea_database_la_SOURCES  = backend_selector.cc backend_selector.h
libkea_database_la_SOURCES += database_connection.cc database_connection.h
libkea_database_la_SOURCES += dbaccess_parser.h dbaccess_parser.cc
libkea_database_la_SOURCES += db_exceptions.h
libkea_database_la_SOURCES += db_log.cc db_log.h
libkea_database_la_SOURCES += server_selector.h

nodist_libkea_database_la_SOURCES = db_messages.cc db_messages.h

libkea_database_la_LIBADD  = $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_database_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

libkea_database_la_LDFLAGS = -no-undefined -version-info 0:0:0

# Specify the headers for copying into the installation directory tree.
libkea_database_includedir = $(pkgincludedir)/database
libkea_database_include_HEADERS = \
	backend_selector.h \
	database_connection.h \
	dbaccess_parser.h \
	db_exceptions.h \
	db_log.h \
	db_messages.h \
	server_selector.h
