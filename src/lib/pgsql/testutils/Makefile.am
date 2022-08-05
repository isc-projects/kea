SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -DDATABASE_SCRIPTS_DIR=\"$(abs_top_srcdir)/src/share/database/scripts\"
AM_CPPFLAGS += -DDATABASE_WIPE_DIR=\"$(abs_top_builddir)/src/share/database/scripts\"
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

if HAVE_GTEST

noinst_LTLIBRARIES = libpgsqltest.la

libpgsqltest_la_SOURCES = pgsql_schema.cc pgsql_schema.h

libpgsqltest_la_CXXFLAGS = $(AM_CXXFLAGS)
libpgsqltest_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(PGSQL_CPPFLAGS)
libpgsqltest_la_LDFLAGS  = $(AM_LDFLAGS) $(PGSQL_LIBS)

libpgsqltest_la_LIBADD = $(top_builddir)/src/lib/database/testutils/libdatabasetest.la

endif
