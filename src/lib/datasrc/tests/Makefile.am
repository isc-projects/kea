AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/lib/dns
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

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
run_unittests_SOURCES += test_datasrc.h test_datasrc.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/datasrc/.libs/libdatasrc.a 
run_unittests_LDADD += $(top_builddir)/src/lib/dns/.libs/libdns.a 
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.a 
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
endif

noinst_PROGRAMS = $(TESTS)

EXTRA_DIST =  testdata/brokendb.sqlite3
EXTRA_DIST += testdata/example.com.signed
EXTRA_DIST += testdata/example.org
EXTRA_DIST += testdata/example.org.sqlite3
EXTRA_DIST += testdata/example2.com
EXTRA_DIST += testdata/example2.com.sqlite3
EXTRA_DIST += testdata/mkbrokendb.c
EXTRA_DIST += testdata/q_cname
EXTRA_DIST += testdata/q_cname_ext
EXTRA_DIST += testdata/q_cname_int
EXTRA_DIST += testdata/q_dname
EXTRA_DIST += testdata/q_example_ns
EXTRA_DIST += testdata/q_example_ptr
EXTRA_DIST += testdata/q_glork
EXTRA_DIST += testdata/q_spork
EXTRA_DIST += testdata/q_sql1
EXTRA_DIST += testdata/q_subzone
EXTRA_DIST += testdata/q_subzone_any
EXTRA_DIST += testdata/q_subzone_dname
EXTRA_DIST += testdata/q_subzone_ds
EXTRA_DIST += testdata/q_subzone_ns
EXTRA_DIST += testdata/q_subzone_nsec
EXTRA_DIST += testdata/q_wild2_a
EXTRA_DIST += testdata/q_wild2_aaaa
EXTRA_DIST += testdata/q_wild3_a
EXTRA_DIST += testdata/q_wild_a
EXTRA_DIST += testdata/q_wild_aaaa
EXTRA_DIST += testdata/root.zone
EXTRA_DIST += testdata/sql1.example.com.signed
EXTRA_DIST += testdata/sql2.example.com.signed
EXTRA_DIST += testdata/test-root.sqlite3
EXTRA_DIST += testdata/test.sqlite3
