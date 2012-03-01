SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(SQLITE_CFLAGS)

AM_CXXFLAGS = $(B10_CXXFLAGS)

pkglibdir = $(libexecdir)/@PACKAGE@/backends

datasrc_config.h: datasrc_config.h.pre
	$(SED) -e "s|@@PKGLIBDIR@@|$(pkglibdir)|" datasrc_config.h.pre >$@

CLEANFILES = *.gcno *.gcda datasrc_messages.h datasrc_messages.cc
CLEANFILES += datasrc_config.h

lib_LTLIBRARIES = libdatasrc.la
libdatasrc_la_SOURCES = data_source.h data_source.cc
libdatasrc_la_SOURCES += static_datasrc.h static_datasrc.cc
libdatasrc_la_SOURCES += sqlite3_datasrc.h sqlite3_datasrc.cc
libdatasrc_la_SOURCES += query.h query.cc
libdatasrc_la_SOURCES += cache.h cache.cc
libdatasrc_la_SOURCES += rbtree.h
libdatasrc_la_SOURCES += zonetable.h zonetable.cc
libdatasrc_la_SOURCES += zone.h zone_finder_context.cc
libdatasrc_la_SOURCES += result.h
libdatasrc_la_SOURCES += logger.h logger.cc
libdatasrc_la_SOURCES += client.h iterator.h
libdatasrc_la_SOURCES += database.h database.cc
libdatasrc_la_SOURCES += factory.h factory.cc
nodist_libdatasrc_la_SOURCES = datasrc_messages.h datasrc_messages.cc

pkglib_LTLIBRARIES =  sqlite3_ds.la memory_ds.la

sqlite3_ds_la_SOURCES = sqlite3_accessor.h sqlite3_accessor.cc
sqlite3_ds_la_SOURCES += sqlite3_accessor_link.cc
sqlite3_ds_la_LDFLAGS = -module
sqlite3_ds_la_LDFLAGS += -no-undefined -version-info 1:0:0
sqlite3_ds_la_LIBADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
sqlite3_ds_la_LIBADD += libdatasrc.la
sqlite3_ds_la_LIBADD += $(SQLITE_LIBS)

memory_ds_la_SOURCES = memory_datasrc.h memory_datasrc.cc
memory_ds_la_SOURCES += memory_datasrc_link.cc
memory_ds_la_LDFLAGS = -module
memory_ds_la_LIBADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
memory_ds_la_LIBADD += libdatasrc.la

libdatasrc_la_LIBADD = $(top_builddir)/src/lib/exceptions/libexceptions.la
libdatasrc_la_LIBADD += $(top_builddir)/src/lib/dns/libdns++.la
libdatasrc_la_LIBADD += $(top_builddir)/src/lib/log/liblog.la
libdatasrc_la_LIBADD += $(top_builddir)/src/lib/cc/libcc.la
libdatasrc_la_LIBADD += $(SQLITE_LIBS)

BUILT_SOURCES = datasrc_config.h datasrc_messages.h datasrc_messages.cc
datasrc_messages.h datasrc_messages.cc: Makefile datasrc_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/datasrc/datasrc_messages.mes

EXTRA_DIST = datasrc_messages.mes
