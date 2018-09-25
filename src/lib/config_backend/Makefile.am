SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

EXTRA_DIST  = base_config_backend.h
EXTRA_DIST += base_config_backend_mgr.h
EXTRA_DIST += base_config_backend_pool.h

# The message file should be in the distribution.
#EXTRA_DIST += config_backend.dox

CLEANFILES = *.gcno *.gcda

# Specify the headers for copying into the installation directory tree.
libkea_cb_includedir = $(pkgincludedir)/config_backend
libkea_cb_include_HEADERS = \
	base_config_backend.h \
	base_config_backend_mgr.h \
	base_config_backend_pool.h

