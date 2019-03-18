SUBDIRS = . testutils tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = db_messages.mes

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-database.la
libkea_database_la_SOURCES  = audit_entry.cc audit_entry.h
libkea_database_la_SOURCES += backend_selector.cc backend_selector.h
libkea_database_la_SOURCES += database_connection.cc database_connection.h
libkea_database_la_SOURCES += dbaccess_parser.h dbaccess_parser.cc
libkea_database_la_SOURCES += db_exceptions.h
libkea_database_la_SOURCES += db_log.cc db_log.h
libkea_database_la_SOURCES += db_messages.cc db_messages.h
libkea_database_la_SOURCES += server_selector.h

libkea_database_la_LIBADD  = $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_database_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_database_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

libkea_database_la_LDFLAGS = -no-undefined -version-info 1:0:0

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f db_messages.h db_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: db_messages.h db_messages.cc
	@echo Message files regenerated

db_messages.h db_messages.cc: db_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/database/db_messages.mes

else

messages db_messages.h db_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_database_includedir = $(pkgincludedir)/database
libkea_database_include_HEADERS = \
	audit_entry.h \
	backend_selector.h \
	database_connection.h \
	dbaccess_parser.h \
	db_exceptions.h \
	db_log.h \
	db_messages.h \
	server_selector.h
