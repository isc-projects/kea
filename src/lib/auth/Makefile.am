AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/ext $(SQLITE_CFLAGS)

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libauth.la
libauth_la_SOURCES = data_source.h data_source.cc
libauth_la_SOURCES += data_source_static.h data_source_static.cc
libauth_la_SOURCES += data_source_sqlite3.h data_source_sqlite3.cc
libauth_la_SOURCES += query.h query.cc

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc
run_unittests_SOURCES += unittest_util.h unittest_util.cc
run_unittests_SOURCES += unittest_ds.h unittest_ds.cc
run_unittests_SOURCES += datasrc_unittest.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += .libs/libauth.a
run_unittests_LDADD += $(top_builddir)/src/lib/dns/.libs/libdns.a 
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
endif

noinst_PROGRAMS = $(TESTS)
