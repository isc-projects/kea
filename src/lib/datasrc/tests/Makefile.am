SUBDIRS = testdata

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/lib/dns -I$(top_srcdir)/src/lib/dns
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(SQLITE_CFLAGS)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_srcdir)/testdata\"
AM_CPPFLAGS += -DTEST_DATA_COMMONDIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_builddir)/testdata\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
noinst_PROGRAMS =
if HAVE_GTEST
TESTS += run_unittests run_unittests_sqlite3 run_unittests_memory

#
# For each specific datasource, there is a separate binary that includes
# the code itself (we can't unittest through the public API). These need
# to be separate because the included code, by design, contains conflicting
# symbols.
# We also have a 'general' run_unittests with non-datasource-specific tests
#

# First define the parts shared by all
common_sources = run_unittests.cc
common_sources += $(top_srcdir)/src/lib/dns/tests/unittest_util.h
common_sources += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc

common_ldadd  = $(GTEST_LDADD)
common_ldadd += $(SQLITE_LIBS)
common_ldadd += $(top_builddir)/src/lib/datasrc/libdatasrc.la
common_ldadd += $(top_builddir)/src/lib/dns/libdns++.la
common_ldadd += $(top_builddir)/src/lib/util/libutil.la
common_ldadd += $(top_builddir)/src/lib/log/liblog.la
common_ldadd += $(top_builddir)/src/lib/exceptions/libexceptions.la
common_ldadd += $(top_builddir)/src/lib/cc/libcc.la
common_ldadd += $(top_builddir)/src/lib/testutils/libtestutils.la
common_ldadd += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la


# The general tests
run_unittests_SOURCES = $(common_sources)
run_unittests_SOURCES += datasrc_unittest.cc
run_unittests_SOURCES += static_unittest.cc
run_unittests_SOURCES += query_unittest.cc
run_unittests_SOURCES += cache_unittest.cc
run_unittests_SOURCES += test_datasrc.h test_datasrc.cc
run_unittests_SOURCES += rbtree_unittest.cc
run_unittests_SOURCES += logger_unittest.cc
run_unittests_SOURCES += client_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

run_unittests_LDADD = $(common_ldadd)


# SQlite3 datasource tests
run_unittests_sqlite3_SOURCES = $(common_sources)
run_unittests_sqlite3_SOURCES += database_unittest.cc
run_unittests_sqlite3_SOURCES += sqlite3_unittest.cc
run_unittests_sqlite3_SOURCES += sqlite3_accessor_unittest.cc
run_unittests_sqlite3_SOURCES += $(top_srcdir)/src/lib/datasrc/sqlite3_accessor.cc

run_unittests_sqlite3_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_sqlite3_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

run_unittests_sqlite3_LDADD = $(common_ldadd)

# In-memory datasource tests
run_unittests_memory_SOURCES = $(common_sources)
run_unittests_memory_SOURCES += memory_datasrc_unittest.cc
run_unittests_memory_SOURCES += $(top_srcdir)/src/lib/datasrc/memory_datasrc.cc

run_unittests_memory_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_memory_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

run_unittests_memory_LDADD = $(common_ldadd)

noinst_PROGRAMS+= $(TESTS)

# For the factory unit tests, we need to specify that we want
# the loadable backend libraries from the build tree, and not from 
# the installation directory. Therefore we build it into a separate
# binary, and call that from check-local with B10_FROM_BUILD set.
# Also, we only want to do this when static building is not used,
# since it will cause various troubles with static link such as
# "missing" symbols in the static object for the module.
if !USE_STATIC_LINK
noinst_PROGRAMS+=run_unittests_factory
run_unittests_factory_SOURCES = $(common_sources)
run_unittests_factory_SOURCES += factory_unittest.cc
run_unittests_factory_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_factory_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
run_unittests_factory_LDADD = $(common_ldadd)
check-local:
	B10_FROM_BUILD=${abs_top_builddir} ./run_unittests_factory
endif

endif

EXTRA_DIST =  testdata/brokendb.sqlite3
EXTRA_DIST += testdata/example.com.signed
EXTRA_DIST += testdata/example.org
EXTRA_DIST += testdata/example.org.nsec3-signed
EXTRA_DIST += testdata/example.org.nsec3-signed-noparam
EXTRA_DIST += testdata/example.org.sqlite3
EXTRA_DIST += testdata/example2.com
EXTRA_DIST += testdata/example2.com.sqlite3
EXTRA_DIST += testdata/mkbrokendb.c
EXTRA_DIST += testdata/root.zone
EXTRA_DIST += testdata/sql1.example.com.signed
EXTRA_DIST += testdata/sql2.example.com.signed
EXTRA_DIST += testdata/test-root.sqlite3
EXTRA_DIST += testdata/test.sqlite3
EXTRA_DIST += testdata/test.sqlite3.nodiffs
EXTRA_DIST += testdata/rwtest.sqlite3
EXTRA_DIST += testdata/diffs.sqlite3
