SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -DDATABASE_SCRIPTS_DIR=\"$(abs_top_srcdir)/src/share/database/scripts\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libprocesstest.la

libprocesstest_la_SOURCES  = d_test_stubs.cc d_test_stubs.h

libprocesstest_la_CXXFLAGS = $(AM_CXXFLAGS)
libprocesstest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libprocesstest_la_LDFLAGS  = $(AM_LDFLAGS)

libprocesstest_la_LIBADD  = $(top_builddir)/src/lib/process/libkea-process.la
libprocesstest_la_LIBADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libprocesstest_la_LIBADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libprocesstest_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la
libprocesstest_la_LIBADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)

endif
