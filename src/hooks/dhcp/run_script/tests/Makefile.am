SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/hooks/dhcp/run_script -I$(top_srcdir)/src/hooks/dhcp/run_script
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DRUN_SCRIPT_LIB_SO=\"$(abs_top_builddir)/src/hooks/dhcp/run_script/.libs/libdhcp_run_script.so\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

# Unit test data files need to get installed.
EXTRA_DIST =

CLEANFILES = *.gcno *.gcda

# TESTS_ENVIRONMENT = $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)
LOG_COMPILER = $(LIBTOOL)
AM_LOG_FLAGS = --mode=execute

TESTS =
if HAVE_GTEST
TESTS += run_script_unittests

run_script_unittests_SOURCES  = run_unittests.cc
run_script_unittests_SOURCES += run_script_unittests.cc

run_script_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)

run_script_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)

run_script_unittests_CXXFLAGS = $(AM_CXXFLAGS)

run_script_unittests_LDADD  = $(top_builddir)/src/hooks/dhcp/run_script/librun_script.la
run_script_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
run_script_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
run_script_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_script_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_script_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_script_unittests_LDADD += $(LOG4CPLUS_LIBS)
run_script_unittests_LDADD += $(CRYPTO_LIBS)
run_script_unittests_LDADD += $(BOOST_LIBS)
run_script_unittests_LDADD += $(GTEST_LDADD)
endif
noinst_PROGRAMS = $(TESTS)
