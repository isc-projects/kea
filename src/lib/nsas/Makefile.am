SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/nsas -I$(top_builddir)/src/lib/nsas
AM_CPPFLAGS += $(SQLITE_CFLAGS)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding missing
# initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# clang++ complains about unused function parameters in some boost header
# files.
if USE_CLANGPP
AM_CXXFLAGS += -Wno-unused-parameter
endif

# Define rule to build logging source files from message file
nsas_messages.h nsas_messages.cc: nsas_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/nsas/nsas_messages.mes

# What is being built.
lib_LTLIBRARIES = libb10-nsas.la

# Tell Automake that the nsas_messages.{cc,h} source files are created in the build
# process, so it must create these before doing anything else.  Although they
# are a dependency of the library (so will be created from the message file
# anyway), there is no guarantee as to exactly _when_ in the build they will be
# created.  As the .h file is included in other sources file (so must be
# present when they are compiled), the safest option is to create it first.
BUILT_SOURCES = nsas_messages.h nsas_messages.cc

# Library sources. The generated files will not be in the distribution.
libb10_nsas_la_SOURCES  = address_entry.h address_entry.cc
libb10_nsas_la_SOURCES += asiolink.h
libb10_nsas_la_SOURCES += hash.cc hash.h
libb10_nsas_la_SOURCES += hash_deleter.h
libb10_nsas_la_SOURCES += hash_key.cc hash_key.h
libb10_nsas_la_SOURCES += hash_table.h
libb10_nsas_la_SOURCES += nameserver_address_store.cc nameserver_address_store.h
libb10_nsas_la_SOURCES += nameserver_address.h nameserver_address.cc
libb10_nsas_la_SOURCES += nameserver_entry.cc nameserver_entry.h
libb10_nsas_la_SOURCES += nsas_entry_compare.h
libb10_nsas_la_SOURCES += nsas_entry.h nsas_types.h
libb10_nsas_la_SOURCES += nsas_log.cc nsas_log.h
libb10_nsas_la_SOURCES += zone_entry.cc zone_entry.h
libb10_nsas_la_SOURCES += fetchable.h
libb10_nsas_la_SOURCES += address_request_callback.h
libb10_nsas_la_SOURCES += glue_hints.h glue_hints.cc

nodist_libb10_nsas_la_SOURCES  = nsas_messages.h nsas_messages.cc

# The message file should be in the distribution.
EXTRA_DIST = nsas_messages.mes

# Make sure that the generated files are got rid of in a clean operation
CLEANFILES = *.gcno *.gcda nsas_messages.h nsas_messages.cc
