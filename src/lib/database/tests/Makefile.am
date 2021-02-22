SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/config/tests\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libdatabase_unittests

libdatabase_unittests_SOURCES  = audit_entry_unittest.cc
libdatabase_unittests_SOURCES += backend_selector_unittest.cc
libdatabase_unittests_SOURCES += database_connection_unittest.cc
libdatabase_unittests_SOURCES += database_log_unittest.cc
libdatabase_unittests_SOURCES += dbaccess_parser_unittest.cc
libdatabase_unittests_SOURCES += run_unittests.cc
libdatabase_unittests_SOURCES += server_unittest.cc
libdatabase_unittests_SOURCES += server_selector_unittest.cc

libdatabase_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libdatabase_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

libdatabase_unittests_LDADD  = $(top_builddir)/src/lib/database/libkea-database.la
libdatabase_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
libdatabase_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libdatabase_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libdatabase_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libdatabase_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libdatabase_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libdatabase_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
