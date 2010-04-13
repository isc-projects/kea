AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = $(top_srcdir)/src/lib/dns/tests/unittest_util.h
run_unittests_SOURCES += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES += ../auth_srv.h ../auth_srv.cc
run_unittests_SOURCES += auth_srv_unittest.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD +=  $(top_builddir)/src/lib/auth/.libs/libauth.a
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/.libs/libdns.a
run_unittests_LDADD += $(top_builddir)/src/lib/config/.libs/libcfgclient.a
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.a
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a
if HAVE_BOOST_SYSTEM
run_unittests_LDFLAGS += $(BOOST_LDFLAGS)
run_unittests_LDADD += $(BOOST_SYSTEM_LIB)
endif
endif

noinst_PROGRAMS = $(TESTS)

EXTRA_DIST =  testdata/badExampleQuery_fromWire
EXTRA_DIST += testdata/badExampleQuery_fromWire.spec
EXTRA_DIST += testdata/example.com
EXTRA_DIST += testdata/examplequery_fromWire
EXTRA_DIST += testdata/examplequery_fromWire.spec
EXTRA_DIST += testdata/example.sqlite3
EXTRA_DIST += testdata/iqueryresponse_fromWire
EXTRA_DIST += testdata/iqueryresponse_fromWire.spec
EXTRA_DIST += testdata/multiquestion_fromWire
EXTRA_DIST += testdata/multiquestion_fromWire.spec
EXTRA_DIST += testdata/queryBadEDNS_fromWire
EXTRA_DIST += testdata/queryBadEDNS_fromWire.spec
EXTRA_DIST += testdata/shortanswer_fromWire
EXTRA_DIST += testdata/shortanswer_fromWire.spec
EXTRA_DIST += testdata/shortmessage_fromWire
EXTRA_DIST += testdata/shortquestion_fromWire
EXTRA_DIST += testdata/shortresponse_fromWire
EXTRA_DIST += testdata/simplequery_fromWire
EXTRA_DIST += testdata/simplequery_fromWire.spec
EXTRA_DIST += testdata/simpleresponse_fromWire
EXTRA_DIST += testdata/simpleresponse_fromWire.spec
