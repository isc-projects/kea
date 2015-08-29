SUBDIRS = . tests

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS  = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)


# Define rule to build logging source files from message file
hooks_messages.h hooks_messages.cc: s-messages

s-messages: hooks_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/hooks/hooks_messages.mes
	touch $@

# Tell automake that the message files are built as part of the build process
# (so that they are built before the main library is built).
BUILT_SOURCES = hooks_messages.h hooks_messages.cc

# Ensure that the message file is included in the distribution
EXTRA_DIST = hooks_messages.mes

# Include developer's guide files
EXTRA_DIST += hooks_user.dox hooks_maintenance.dox hooks_component_developer.dox

# Include images used in Developer's guide
EXTRA_DIST += images/DataScopeArgument.dia images/DataScopeArgument.png
EXTRA_DIST += images/DataScopeContext.dia images/DataScopeContext.png
EXTRA_DIST += images/HooksUml.dia images/HooksUml.png

# Get rid of generated message files on a clean
CLEANFILES = *.gcno *.gcda hooks_messages.h hooks_messages.cc s-messages

lib_LTLIBRARIES = libkea-hooks.la
libkea_hooks_la_SOURCES  =
libkea_hooks_la_SOURCES += callout_handle.cc callout_handle.h
libkea_hooks_la_SOURCES += callout_manager.cc callout_manager.h
libkea_hooks_la_SOURCES += hooks.h hooks.cc
libkea_hooks_la_SOURCES += hooks_log.cc hooks_log.h
libkea_hooks_la_SOURCES += hooks_manager.cc hooks_manager.h
libkea_hooks_la_SOURCES += library_handle.cc library_handle.h
libkea_hooks_la_SOURCES += library_manager.cc library_manager.h
libkea_hooks_la_SOURCES += library_manager_collection.cc library_manager_collection.h
libkea_hooks_la_SOURCES += pointer_converter.h
libkea_hooks_la_SOURCES += server_hooks.cc server_hooks.h

nodist_libkea_hooks_la_SOURCES = hooks_messages.cc hooks_messages.h

libkea_hooks_la_CXXFLAGS = $(AM_CXXFLAGS)
libkea_hooks_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
libkea_hooks_la_LDFLAGS  = $(AM_LDFLAGS) -no-undefined -version-info 1:0:0
libkea_hooks_la_LIBADD  =
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_hooks_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_hooks_la_LIBADD += $(LOG4CPLUS_LIBS)

# Specify the headers for copying into the installation directory tree. User-
# written libraries only need the definitions from the headers for the
# CalloutHandle and LibraryHandle objects. CalloutManager may be required by
# users testing statically linked KEA binaries.
libkea_hooks_includedir = $(pkgincludedir)/hooks
libkea_hooks_include_HEADERS = \
    callout_handle.h \
    callout_manager.h \
    library_handle.h \
    hooks.h \
    server_hooks.h

if USE_CLANGPP
# Disable unused parameter warning caused by some of the
# Boost headers when compiling with clang.
libkea_hooks_la_CXXFLAGS += -Wno-unused-parameter
endif
