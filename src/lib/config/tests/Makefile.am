AM_CPPFLAGS = -I$(top_srcdir)/src/lib

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libfake_session.la
libfake_session_la_SOURCES = fake_session.h fake_session.cc

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = ccsession_unittests.cc module_spec_unittests.cc config_data_unittests.cc run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD =  $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
run_unittests_LDADD += libfake_session.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/data.o

if HAVE_BOOST_SYSTEM
run_unittests_LDFLAGS += $(AM_LDFLAGS) $(BOOST_LDFLAGS)
run_unittests_LDADD += $(BOOST_SYSTEM_LIB)
endif

endif

noinst_PROGRAMS = $(TESTS)
