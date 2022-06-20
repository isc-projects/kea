SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/config/tests\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += libcb_unittests

libcb_unittests_SOURCES  = config_backend_mgr_unittest.cc
libcb_unittests_SOURCES += run_unittests.cc

libcb_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libcb_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

libcb_unittests_LDADD  = $(top_builddir)/src/lib/database/libkea-database.la
libcb_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
libcb_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libcb_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
libcb_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
libcb_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libcb_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
