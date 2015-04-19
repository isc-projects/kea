SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -DLOCKFILE_DIR=\"${localstatedir}/run/${PACKAGE_NAME}\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS) $(SHLIB_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

noinst_LTLIBRARIES = libkea-log_interprocess.la

libkea_log_interprocess_la_SOURCES = api.h interprocess_sync.h
libkea_log_interprocess_la_SOURCES += interprocess_sync_file.h
libkea_log_interprocess_la_SOURCES += interprocess_sync_file.cc
libkea_log_interprocess_la_SOURCES += interprocess_sync_null.h
libkea_log_interprocess_la_SOURCES += interprocess_sync_null.cc

libkea_log_interprocess_la_LIBADD  = $(top_builddir)/src/lib/util/threads/libkea-threads.la

EXTRA_DIST  = README
