AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(SYSREPO_CPPFLAGS)
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples\"
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

EXTRA_DIST = keatest-module.yang

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = adaptor_unittests.cc
run_unittests_SOURCES += sysrepo_setup.h
run_unittests_SOURCES += translator_unittests.cc
run_unittests_SOURCES += translator_option_data_unittests.cc
run_unittests_SOURCES += translator_option_def_unittests.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD  = $(top_builddir)/src/lib/yang/libkea-yang.la
run_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)
run_unittests_LDADD += $(SYSREPO_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
