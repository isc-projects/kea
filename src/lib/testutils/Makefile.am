SUBDIRS = . testdata

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS=$(B10_CXXFLAGS)

lib_LTLIBRARIES = libtestutils.la

libtestutils_la_SOURCES = srv_test.h srv_test.cc
libtestutils_la_SOURCES += srv_unittest.h
libtestutils_la_SOURCES += mockups.h
