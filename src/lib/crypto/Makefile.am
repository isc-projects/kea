SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libb10crypto.la

libb10crypto_la_SOURCES = crypto.h crypto.cc
libb10crypto_la_SOURCES += crypto_hmac.h crypto_hmac.cc
