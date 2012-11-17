SUBDIRS = . memory testdata

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

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
noinst_PROGRAMS =
if HAVE_GTEST
TESTS += run_unittests

# We have two sets of tests: the general tests and factory tests (see below
# for the latter).  They are separate binary files sharing some program files
# and libraries.

# First define the parts shared by both
common_sources = run_unittests.cc
common_sources += $(top_srcdir)/src/lib/dns/tests/unittest_util.h
common_sources += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc

common_ldadd = $(top_builddir)/src/lib/datasrc/libb10-datasrc.la
common_ldadd += $(top_builddir)/src/lib/dns/libb10-dns++.la
common_ldadd += $(top_builddir)/src/lib/util/libb10-util.la
common_ldadd += $(top_builddir)/src/lib/log/libb10-log.la
common_ldadd += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
common_ldadd += $(top_builddir)/src/lib/cc/libb10-cc.la
common_ldadd += $(top_builddir)/src/lib/testutils/libb10-testutils.la
common_ldadd += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
common_ldadd += $(GTEST_LDADD) $(SQLITE_LIBS)

# The general tests
run_unittests_SOURCES = $(common_sources)

run_unittests_SOURCES += test_client.h test_client.cc
run_unittests_SOURCES += rbtree_unittest.cc
run_unittests_SOURCES += logger_unittest.cc
run_unittests_SOURCES += client_unittest.cc
run_unittests_SOURCES += database_unittest.cc
run_unittests_SOURCES += sqlite3_accessor_unittest.cc
run_unittests_SOURCES += memory_datasrc_unittest.cc
run_unittests_SOURCES += rbnode_rrset_unittest.cc
run_unittests_SOURCES += zonetable_unittest.cc
run_unittests_SOURCES += zone_finder_context_unittest.cc
run_unittests_SOURCES += faked_nsec3.h faked_nsec3.cc
run_unittests_SOURCES += client_list_unittest.cc
run_unittests_SOURCES += loader_callbacks_test.cc

# We need the actual module implementation in the tests (they are not part
# of libdatasrc)
run_unittests_SOURCES += $(top_srcdir)/src/lib/datasrc/sqlite3_accessor.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

run_unittests_LDADD = $(common_ldadd)

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
EXTRA_DIST += testdata/contexttest.zone
EXTRA_DIST += testdata/diffs.sqlite3
EXTRA_DIST += testdata/duplicate_rrset.zone
EXTRA_DIST += testdata/example2.com
EXTRA_DIST += testdata/example2.com.sqlite3
EXTRA_DIST += testdata/example.com.flattened
EXTRA_DIST += testdata/example.com.signed
EXTRA_DIST += testdata/example.org
EXTRA_DIST += testdata/example.org.nsec3-signed
EXTRA_DIST += testdata/example.org.nsec3-signed-noparam
EXTRA_DIST += testdata/example.org.sqlite3
EXTRA_DIST += testdata/mkbrokendb.c
EXTRA_DIST += testdata/root.zone
EXTRA_DIST += testdata/rrset_toWire1
EXTRA_DIST += testdata/rrset_toWire2
EXTRA_DIST += testdata/sql1.example.com.signed
EXTRA_DIST += testdata/sql2.example.com.signed
EXTRA_DIST += testdata/test-root.sqlite3
EXTRA_DIST += testdata/test.sqlite3
EXTRA_DIST += testdata/new_minor_schema.sqlite3
EXTRA_DIST += testdata/newschema.sqlite3
EXTRA_DIST += testdata/oldschema.sqlite3
EXTRA_DIST += testdata/static.zone
