AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/lib/dns
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += datasrc_unittest.cc
run_unittests_SOURCES += sqlite3_unittest.cc
run_unittests_SOURCES += static_unittest.cc
run_unittests_SOURCES += query_unittest.cc
run_unittests_SOURCES += cache_unittest.cc
run_unittests_SOURCES += test_datasrc.h test_datasrc.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/datasrc/libdatasrc.la 
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
endif

noinst_PROGRAMS = $(TESTS)

EXTRA_DIST =  testdata/brokendb.sqlite3
EXTRA_DIST += testdata/example.com.signed
EXTRA_DIST += testdata/example.org
EXTRA_DIST += testdata/example.org.sqlite3
EXTRA_DIST += testdata/example2.com
EXTRA_DIST += testdata/example2.com.sqlite3
EXTRA_DIST += testdata/mkbrokendb.c
EXTRA_DIST += testdata/root.zone
EXTRA_DIST += testdata/sql1.example.com.signed
EXTRA_DIST += testdata/sql2.example.com.signed
EXTRA_DIST += testdata/test-root.sqlite3
EXTRA_DIST += testdata/test.sqlite3
