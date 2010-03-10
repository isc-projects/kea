AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/ext

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc
run_unittests_SOURCES += unittest_util.h unittest_util.cc
run_unittests_SOURCES += datasrc_unittest.cc
run_unittests_SOURCES += sqlite3_ds_unittest.cc
run_unittests_SOURCES += static_ds_unittest.cc
run_unittests_SOURCES += test_ds.h test_ds.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/auth/.libs/libauth.a 
run_unittests_LDADD += $(top_builddir)/src/lib/dns/.libs/libdns.a 
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.a 
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
endif

noinst_PROGRAMS = $(TESTS)
