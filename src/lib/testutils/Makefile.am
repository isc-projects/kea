SUBDIRS = . testdata valgrind

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS=$(B10_CXXFLAGS)

if HAVE_GTEST
noinst_LTLIBRARIES = libb10-testutils.la

libb10_testutils_la_SOURCES = srv_test.h srv_test.cc
libb10_testutils_la_SOURCES += dnsmessage_test.h dnsmessage_test.cc
libb10_testutils_la_SOURCES += mockups.h
libb10_testutils_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libb10_testutils_la_LIBADD = $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
endif

EXTRA_DIST = portconfig.h socket_request.h
