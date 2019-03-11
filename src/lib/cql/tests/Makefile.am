SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libcql_unittests

libcql_unittests_SOURCES  = cql_connection_unittest.cc
libcql_unittests_SOURCES += run_unittests.cc

libcql_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(CQL_CPPFLAGS)
libcql_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(CQL_LIBS) $(GTEST_LDFLAGS)

libcql_unittests_LDADD  = $(top_builddir)/src/lib/cql/libkea-cql.la
libcql_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libcql_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS) $(CQL_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
