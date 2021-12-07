SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libd2srvtest.la

libd2srvtest_la_SOURCES  = nc_test_utils.cc nc_test_utils.h
libd2srvtest_la_SOURCES += stats_test_utils.cc stats_test_utils.h

libd2srvtest_la_CXXFLAGS = $(AM_CXXFLAGS)
libd2srvtest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

libd2srvtest_la_LIBADD  = $(top_builddir)/src/lib/d2srv/libkea-d2srv.la
libd2srvtest_la_LIBADD += $(top_builddir)/src/lib/log/libkea-log.la

endif
