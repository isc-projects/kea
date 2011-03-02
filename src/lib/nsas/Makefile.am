SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/nsas -I$(top_builddir)/src/lib/nsas
AM_CPPFLAGS += $(SQLITE_CFLAGS)
AM_CXXFLAGS = $(B10_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_CLANGPP
# clang++ complains about unused function parameters in some boost header
# files.
AM_CXXFLAGS += -Wno-unused-parameter
endif

lib_LTLIBRARIES = libnsas.la
libnsas_la_SOURCES  = address_entry.h address_entry.cc
libnsas_la_SOURCES += asiolink.h
libnsas_la_SOURCES += hash.cc hash.h
libnsas_la_SOURCES += hash_deleter.h
libnsas_la_SOURCES += hash_key.cc hash_key.h
libnsas_la_SOURCES += locks.h
libnsas_la_SOURCES += hash_table.h
libnsas_la_SOURCES += lru_list.h
libnsas_la_SOURCES += nameserver_address_store.cc nameserver_address_store.h
libnsas_la_SOURCES += nameserver_address.h nameserver_address.cc
libnsas_la_SOURCES += nameserver_entry.cc nameserver_entry.h
libnsas_la_SOURCES += nsas_entry_compare.h
libnsas_la_SOURCES += nsas_entry.h nsas_types.h
libnsas_la_SOURCES += zone_entry.cc zone_entry.h
libnsas_la_SOURCES += fetchable.h
libnsas_la_SOURCES += address_request_callback.h
libnsas_la_SOURCES += random_number_generator.h

CLEANFILES = *.gcno *.gcda
