SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
AM_LDFLAGS = $(PTHREAD_LDFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.     
AM_CXXFLAGS  = $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_CLANGPP
# see ../Makefile.am
AM_CXXFLAGS += -Wno-unused-parameter
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

# Build shared libraries for testing.
lib_LTLIBRARIES = libnvl.la libivl.la libbcl.la liblcl.la liblecl.la
 
# No version function
libnvl_la_SOURCES  = no_version_library.cc
libnvl_la_CXXFLAGS = $(AM_CXXFLAGS)
libnvl_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)
 
# Incorrect version function
libivl_la_SOURCES  = incorrect_version_library.cc
libivl_la_CXXFLAGS = $(AM_CXXFLAGS)
libilv_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)

# The basic callout library - contains standard callouts
libbcl_la_SOURCES  = basic_callout_library.cc
libbcl_la_CXXFLAGS = $(AM_CXXFLAGS)
libbcl_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)

# The load callout library - contains a load function
liblcl_la_SOURCES  = load_callout_library.cc
liblcl_la_CXXFLAGS = $(AM_CXXFLAGS)
liblcl_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)

# The load error callout library - contains a load function that returns
# an error.
liblecl_la_SOURCES  = load_error_callout_library.cc
liblecl_la_CXXFLAGS = $(AM_CXXFLAGS)
liblecl_la_CPPFLAGS = $(AM_CPPFLAGS) $(LOG4CPLUS_INCLUDES)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += callout_handle_unittest.cc
run_unittests_SOURCES += callout_manager_unittest.cc
run_unittests_SOURCES += handles_unittest.cc
run_unittests_SOURCES += library_manager_unittest.cc
run_unittests_SOURCES += server_hooks_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
run_unittests_LDADD    = $(AM_LDADD)    $(GTEST_LDADD)

run_unittests_LDADD += $(top_builddir)/src/lib/hooks/libb10-hooks.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
endif

noinst_PROGRAMS = $(TESTS)
