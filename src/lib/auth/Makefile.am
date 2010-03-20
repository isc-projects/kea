SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(SQLITE_CFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libauth.la
libauth_la_SOURCES = data_source.h data_source.cc
libauth_la_SOURCES += static_datasrc.h static_datasrc.cc
libauth_la_SOURCES += sqlite3_datasrc.h sqlite3_datasrc.cc
libauth_la_SOURCES += query.h query.cc
