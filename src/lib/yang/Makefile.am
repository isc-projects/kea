SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(SYSREPO_CPPFLAGS)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-yang.la
libkea_yang_la_SOURCES = sysrepo_error.h
libkea_yang_la_SOURCES += translator.cc translator.h
libkea_yang_la_SOURCES += translator_database.cc translator_database.h

libkea_yang_la_LIBADD =  $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_yang_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_yang_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(SYSREPO_LIBS)

libkea_yang_la_LDFLAGS = -no-undefined -version-info 0:0:0

# Specify the headers for copying into the installation directory tree.
libkea_yang_includedir = $(pkgincludedir)/yang
libkea_yang_include_HEADERS = \
	sysrepo_error.h \
	translator.h \
	translator_database.h

EXTRA_DIST = yang.dox

CLEANFILES = *.gcno *.gcda
