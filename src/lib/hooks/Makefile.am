SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Ensure that the message file is included in the distribution
EXTRA_DIST = hooks_messages.mes

# Include developer's guide files
EXTRA_DIST += hooks_user.dox hooks_maintenance.dox hooks_component_developer.dox

# Include images used in Developer's guide
EXTRA_DIST += images/DataScopeArgument.dia images/DataScopeArgument.png
EXTRA_DIST += images/DataScopeContext.dia images/DataScopeContext.png
EXTRA_DIST += images/HooksUml.dia images/HooksUml.png

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libkea-hooks.la
libkea_hooks_la_SOURCES  =
libkea_hooks_la_SOURCES += callout_handle.cc callout_handle.h
libkea_hooks_la_SOURCES += callout_handle_associate.cc callout_handle_associate.h
libkea_hooks_la_SOURCES += callout_manager.cc callout_manager.h
libkea_hooks_la_SOURCES += hooks.h
libkea_hooks_la_SOURCES += hooks_log.cc hooks_log.h
libkea_hooks_la_SOURCES += hooks_manager.cc hooks_manager.h
libkea_hooks_la_SOURCES += hooks_config.cc hooks_config.h
libkea_hooks_la_SOURCES += hooks_parser.cc hooks_parser.h
libkea_hooks_la_SOURCES += libinfo.cc libinfo.h
libkea_hooks_la_SOURCES += library_handle.cc library_handle.h
libkea_hooks_la_SOURCES += library_manager.cc library_manager.h
libkea_hooks_la_SOURCES += library_manager_collection.cc library_manager_collection.h
libkea_hooks_la_SOURCES += parking_lots.h
libkea_hooks_la_SOURCES += pointer_converter.h
libkea_hooks_la_SOURCES += server_hooks.cc server_hooks.h
libkea_hooks_la_SOURCES += hooks_messages.cc hooks_messages.h

libkea_hooks_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_hooks_la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_hooks_la_LDFLAGS  = $(AM_LDFLAGS) -no-undefined -version-info 7:2:0
libkea_hooks_la_LIBADD  =
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_hooks_la_LIBADD += $(BOOST_LIBS)
libkea_hooks_la_LIBADD += $(LOG4CPLUS_LIBS)

# If we want to get rid of all generated messages files, we need to use
# make maintainer-clean. The proper way to introduce custom commands for
# that operation is to define maintainer-clean-local target. However,
# make maintainer-clean also removes Makefile, so running configure script
# is required.  To make it easy to rebuild messages without going through
# reconfigure, a new target messages-clean has been added.
maintainer-clean-local:
	rm -f hooks_messages.h hooks_messages.cc

# To regenerate messages files, one can do:
#
# make messages-clean
# make messages
#
# This is needed only when a .mes file is modified.
messages-clean: maintainer-clean-local

if GENERATE_MESSAGES

# Define rule to build logging source files from message file
messages: hooks_messages.h hooks_messages.cc
	@echo Message files regenerated

hooks_messages.h hooks_messages.cc: hooks_messages.mes
	$(top_builddir)/src/lib/log/compiler/kea-msg-compiler $(top_srcdir)/src/lib/hooks/hooks_messages.mes

else

messages hooks_messages.h hooks_messages.cc:
	@echo Messages generation disabled. Configure with --enable-generate-messages to enable it.

endif

# Specify the headers for copying into the installation directory tree.
libkea_hooks_includedir = $(pkgincludedir)/hooks
libkea_hooks_include_HEADERS = \
	callout_handle.h \
	callout_handle_associate.h \
	callout_manager.h \
	hooks.h \
	hooks_config.h \
	hooks_log.h \
	hooks_manager.h \
	hooks_messages.h \
	hooks_parser.h \
	libinfo.h \
	library_handle.h \
	library_manager.h \
	library_manager_collection.h \
	parking_lots.h \
	pointer_converter.h \
	server_hooks.h


