SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(PGSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libpgsql_unittests

libpgsql_unittests_SOURCES  = pgsql_exchange_unittest.cc
libpgsql_unittests_SOURCES += run_unittests.cc

libpgsql_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libpgsql_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS) $(PGSQL_LIBS)

libpgsql_unittests_LDADD  = $(top_builddir)/src/lib/pgsql/libkea-pgsql.la
libpgsql_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libpgsql_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libpgsql_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libpgsql_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libpgsql_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libpgsql_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libpgsql_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
