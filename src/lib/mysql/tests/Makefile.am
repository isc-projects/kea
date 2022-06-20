SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libmysql_unittests

libmysql_unittests_SOURCES  = mysql_binding_unittest.cc
libmysql_unittests_SOURCES += mysql_connection_unittest.cc
libmysql_unittests_SOURCES += run_unittests.cc

libmysql_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libmysql_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS) $(MYSQL_LIBS)

libmysql_unittests_LDADD  = $(top_builddir)/src/lib/mysql/testutils/libmysqltest.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/mysql/libkea-mysql.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/database/libkea-database.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libmysql_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
