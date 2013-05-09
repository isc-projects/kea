SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -DLOCKFILE_DIR=\"${localstatedir}/${PACKAGE_NAME}\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

noinst_LTLIBRARIES = libb10-log_interprocess.la

libb10_log_interprocess_la_SOURCES = interprocess_sync.h
libb10_log_interprocess_la_SOURCES += interprocess_sync_file.h
libb10_log_interprocess_la_SOURCES += interprocess_sync_file.cc
libb10_log_interprocess_la_SOURCES += interprocess_sync_null.h
libb10_log_interprocess_la_SOURCES += interprocess_sync_null.cc

libb10_log_interprocess_la_LIBADD  = $(top_builddir)/src/lib/util/threads/libb10-threads.la

EXTRA_DIST  = README
