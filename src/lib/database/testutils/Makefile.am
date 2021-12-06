SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
TEST_CA_DIR = $(abs_srcdir)/../../asiolink/testutils/ca
AM_CPPFLAGS += -DTEST_CA_DIR=\"$(TEST_CA_DIR)\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libdatabasetest.la

libdatabasetest_la_SOURCES = schema.cc schema.h

libdatabasetest_la_CXXFLAGS = $(AM_CXXFLAGS)
libdatabasetest_la_CPPFLAGS = $(AM_CPPFLAGS)
libdatabasetest_la_LDFLAGS  = $(AM_LDFLAGS)

endif
