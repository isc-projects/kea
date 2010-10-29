SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/nsas -I$(top_builddir)/src/lib/nsas
AM_CPPFLAGS += $(SQLITE_CFLAGS)
AM_CXXFLAGS = $(B10_CXXFLAGS)

lib_LTLIBRARIES = libnsas.la
libnsas_la_SOURCES  = address_entry.h address_entry.cc
libnsas_la_SOURCES += hash.cc hash.h
libnsas_la_SOURCES += hash_deleter.h
libnsas_la_SOURCES += hash_key.cc hash_key.h
libnsas_la_SOURCES += hash_table.h
libnsas_la_SOURCES += lru_list.h
libnsas_la_SOURCES += nameserver_entry.cc nameserver_entry.h
libnsas_la_SOURCES += nsas_entry.h
libnsas_la_SOURCES += asiolink.h

CLEANFILES = *.gcno *.gcda
