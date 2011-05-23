SUBDIRS = testdata .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libfake_session.la
libfake_session_la_SOURCES = fake_session.h fake_session.cc

TESTS =
if HAVE_GTEST
# We build this file with disabled warnings because of asio
lib_LTLIBRARIES += libasiobased.la
libasiobased_la_SOURCES = ccsession_unittests.cc
libasiobased_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) -Wno-unused-parameter
libasiobased_la_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

TESTS += run_unittests
run_unittests_SOURCES = module_spec_unittests.cc config_data_unittests.cc run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD =  $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
run_unittests_LDADD += libfake_session.la
run_unittests_LDADD += libasiobased.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la

endif

noinst_PROGRAMS = $(TESTS)
