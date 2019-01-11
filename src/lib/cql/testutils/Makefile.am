SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -DDATABASE_SCRIPTS_DIR=\"$(abs_top_srcdir)/src/share/database/scripts\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libcqltest.la

libcqltest_la_SOURCES = cql_schema.cc cql_schema.h

libcqltest_la_CXXFLAGS = $(AM_CXXFLAGS)
libcqltest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(CQL_CPPFLAGS)
libcqltest_la_LDFLAGS  = $(AM_LDFLAGS) $(CQL_LIBS)

libcqltest_la_LIBADD = $(top_builddir)/src/lib/database/testutils/libdatabasetest.la

endif
