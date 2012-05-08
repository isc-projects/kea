SUBDIRS = . testdata

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS=$(B10_CXXFLAGS)

if HAVE_GTEST
noinst_LTLIBRARIES = libtestutils.la

libtestutils_la_SOURCES = srv_test.h srv_test.cc
libtestutils_la_SOURCES += dnsmessage_test.h dnsmessage_test.cc
libtestutils_la_SOURCES += mockups.h
libtestutils_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libtestutils_la_LIBADD = $(top_builddir)/src/lib/asiolink/libasiolink.la
endif

EXTRA_DIST = portconfig.h socket_request.h
