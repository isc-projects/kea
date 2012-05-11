SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(SQLITE_CFLAGS)

AM_CXXFLAGS = $(B10_CXXFLAGS)

# Define rule to build logging source files from message file
resolve_messages.h resolve_messages.cc: resolve_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/resolve/resolve_messages.mes

# Tell Automake that the nsasdef.{cc,h} source files are created in the build
# process, so it must create these before doing anything else.  Although they
# are a dependency of the library (so will be created from the message file
# anyway), there is no guarantee as to exactly _when_ in the build they will be
# created.  As the .h file is included in other sources file (so must be
# present when they are compiled), the safest option is to create it first.
BUILT_SOURCES = resolve_messages.h resolve_messages.cc

CLEANFILES = *.gcno *.gcda resolve_messages.cc resolve_messages.h

lib_LTLIBRARIES = libresolve.la
libresolve_la_SOURCES = resolve.h resolve.cc
libresolve_la_SOURCES += resolve_log.h resolve_log.cc
libresolve_la_SOURCES += resolver_interface.h
libresolve_la_SOURCES += resolver_callback.h resolver_callback.cc
libresolve_la_SOURCES += response_classifier.cc response_classifier.h
libresolve_la_SOURCES += recursive_query.cc recursive_query.h

nodist_libresolve_la_SOURCES = resolve_messages.h resolve_messages.cc

libresolve_la_LIBADD = $(top_builddir)/src/lib/dns/libdns++.la
libresolve_la_LIBADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
libresolve_la_LIBADD += $(top_builddir)/src/lib/log/liblog.la
libresolve_la_LIBADD += $(top_builddir)/src/lib/asiodns/libasiodns.la

# The message file should be in the distribution.
EXTRA_DIST = resolve_messages.mes

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# B10_CXXFLAGS)
libresolve_la_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# For clang++, we need to turn off -Werror completely.
libresolve_la_CXXFLAGS += -Wno-error
endif
libresolve_la_CPPFLAGS = $(AM_CPPFLAGS)

