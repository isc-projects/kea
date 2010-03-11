AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/ext

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = module_spec_unittests.cc config_data_unittests.cc run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD =  $(top_builddir)/src/lib/config/libcfgclient.la $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.a

if HAVE_BOOSTLIB
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(BOOST_LDFLAGS)
run_unittests_LDADD += $(BOOST_SYSTEM_LIB)
endif

endif

noinst_PROGRAMS = $(TESTS)
