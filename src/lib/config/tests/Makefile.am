SUBDIRS = testdata .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

noinst_LTLIBRARIES = libfake_session.la
libfake_session_la_SOURCES = fake_session.h fake_session.cc

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = ccsession_unittests.cc module_spec_unittests.cc config_data_unittests.cc run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD =  $(GTEST_LDADD)
run_unittests_LDADD += libfake_session.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la

endif

noinst_PROGRAMS = $(TESTS)
