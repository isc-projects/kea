SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/ext $(SQLITE_CFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libauth.la
libauth_la_SOURCES = data_source.h data_source.cc
libauth_la_SOURCES += static_datasrc.h static_datasrc.cc
libauth_la_SOURCES += sqlite3_datasrc.h sqlite3_datasrc.cc
libauth_la_SOURCES += query.h query.cc
