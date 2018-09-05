SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

lib_LTLIBRARIES = libkea-cb.la
libkea_cb_la_SOURCES  = base_config_backend.h
libkea_cb_la_SOURCES += base_config_backend_mgr.h
libkea_cb_la_SOURCES += base_config_backend_pool.cc base_config_backend_pool.h


libkea_cb_la_LIBADD  = $(top_builddir)/src/lib/database/libkea-database.la
libkea_cb_la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_cb_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_cb_la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_cb_la_LIBADD += $(BOOST_LIBS)

libkea_cb_la_LDFLAGS = -no-undefined -version-info 0:0:0

# The message file should be in the distribution.
#EXTRA_DIST = config_backend.dox

CLEANFILES = *.gcno *.gcda

# Specify the headers for copying into the installation directory tree.
libkea_cb_includedir = $(pkgincludedir)/config_backend
libkea_cb_include_HEADERS = \
	base_config_backend.h \
	base_config_backend_mgr.h \
	base_config_backend_pool.h

