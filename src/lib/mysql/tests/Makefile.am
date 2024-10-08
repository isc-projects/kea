SUBDIRS = .

TEST_CA_DIR = $(realpath $(abs_srcdir)/../../asiolink/testutils/ca)

AM_CPPFLAGS  =
AM_CPPFLAGS += -DTEST_CA_DIR=\"$(TEST_CA_DIR)\"
AM_CPPFLAGS += -DKEA_ADMIN=\"${abs_top_builddir}/src/bin/admin/kea-admin\"
AM_CPPFLAGS += -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MYSQL_CPPFLAGS) $(CRYPTO_CFLAGS) $(CRYPTO_INCLUDES)

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
libmysql_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libmysql_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libmysql_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD) $(CRYPTO_LIBS)

endif

noinst_PROGRAMS = $(TESTS)
