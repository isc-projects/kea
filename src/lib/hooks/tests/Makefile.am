SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)

AM_CXXFLAGS  = $(KEA_CXXFLAGS)
# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.     
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# Kea libraries against which the test user libraries are linked.
HOOKS_LIB      = $(top_builddir)/src/lib/hooks/libkea-hooks.la
LOG_LIB        = $(top_builddir)/src/lib/log/libkea-log.la
THREADS_LIB    = $(top_builddir)/src/lib/util/threads/libkea-threads.la
UTIL_LIB       = $(top_builddir)/src/lib/util/libkea-util.la
EXCEPTIONS_LIB = $(top_builddir)/src/lib/exceptions/libkea-exceptions.la

ALL_LIBS       = $(HOOKS_LIB) $(LOG_LIB) $(THREADS_LIB) $(UTIL_LIB) $(EXCEPTIONS_LIB) $(LOG4CPLUS_LIBS)

if USE_CLANGPP
# see ../Makefile.am
AM_CXXFLAGS += -Wno-unused-parameter
endif

# Files to clean include the file created by testing.
CLEANFILES = *.gcno *.gcda $(builddir)/marker_file.dat

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
# Build shared libraries for testing. The libtool way to create a shared library
# is to specify "-avoid-version -export-dynamic -module" in the library LDFLAGS
# (see http://www.gnu.org/software/libtool/manual/html_node/Link-mode.html).
# Use of these switches will guarantee that the .so files are created in the
# .libs folder and they can be dlopened.
#
# Note that the shared libraries with callouts should not be used together with
# the --enable-static-link option. With this option, the bind10 libraries are
# statically linked with the program and if the callout invokes the methods
# which belong to these libraries, the library with the callout will get its
# own copy of the static objects (e.g. logger, ServerHooks) and that will lead
# to unexpected errors. For this reason, the --enable-static-link option is
# ignored for unit tests built here.

noinst_LTLIBRARIES = libnvl.la  libivl.la libfxl.la libbcl.la liblcl.la \
                     liblecl.la libucl.la libfcl.la

# -rpath /nowhere is a hack to trigger libtool to not create a
# convenience archive, resulting in shared modules

# No version function
libnvl_la_SOURCES  = no_version_library.cc
libnvl_la_CXXFLAGS = $(AM_CXXFLAGS)
libnvl_la_CPPFLAGS = $(AM_CPPFLAGS)
libnvl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

# Incorrect version function
libivl_la_SOURCES  = incorrect_version_library.cc
libivl_la_CXXFLAGS = $(AM_CXXFLAGS)
libivl_la_CPPFLAGS = $(AM_CPPFLAGS)
libivl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

# All framework functions throw an exception
libfxl_la_SOURCES  = framework_exception_library.cc
libfxl_la_CXXFLAGS = $(AM_CXXFLAGS)
libfxl_la_CPPFLAGS = $(AM_CPPFLAGS)
libfxl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

# The basic callout library - contains standard callouts
libbcl_la_SOURCES  = basic_callout_library.cc
libbcl_la_CXXFLAGS = $(AM_CXXFLAGS)
libbcl_la_CPPFLAGS = $(AM_CPPFLAGS)
libbcl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere
libbcl_la_LIBADD   = $(ALL_LIBS)

# The load callout library - contains a load function
liblcl_la_SOURCES  = load_callout_library.cc
liblcl_la_CXXFLAGS = $(AM_CXXFLAGS)
liblcl_la_CPPFLAGS = $(AM_CPPFLAGS)
liblcl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere
liblcl_la_LIBADD   = $(ALL_LIBS)

# The load error callout library - contains a load function that returns
# an error.
liblecl_la_SOURCES  = load_error_callout_library.cc
liblecl_la_CXXFLAGS = $(AM_CXXFLAGS)
liblecl_la_CPPFLAGS = $(AM_CPPFLAGS)
liblecl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

# The unload callout library - contains an unload function that
# creates a marker file.
libucl_la_SOURCES  = unload_callout_library.cc
libucl_la_CXXFLAGS = $(AM_CXXFLAGS)
libucl_la_CPPFLAGS = $(AM_CPPFLAGS)
libucl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere

# The full callout library - contains all three framework functions.
libfcl_la_SOURCES  = full_callout_library.cc
libfcl_la_CXXFLAGS = $(AM_CXXFLAGS)
libfcl_la_CPPFLAGS = $(AM_CPPFLAGS)
libfcl_la_LDFLAGS  = -avoid-version -export-dynamic -module -rpath /nowhere
libfcl_la_LIBADD   = $(ALL_LIBS)

TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += callout_handle_unittest.cc
run_unittests_SOURCES += callout_manager_unittest.cc
run_unittests_SOURCES += common_test_class.h
run_unittests_SOURCES += handles_unittest.cc
run_unittests_SOURCES += hooks_manager_unittest.cc
run_unittests_SOURCES += library_manager_collection_unittest.cc
run_unittests_SOURCES += library_manager_unittest.cc
run_unittests_SOURCES += server_hooks_unittest.cc

nodist_run_unittests_SOURCES  = marker_file.h
nodist_run_unittests_SOURCES += test_libraries.h

run_unittests_CXXFLAGS  = $(AM_CXXFLAGS)
run_unittests_CPPFLAGS  = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS   = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
if USE_STATIC_LINK
run_unittests_LDFLAGS  += -static
endif

run_unittests_LDADD     = $(AM_LDADD)
run_unittests_LDADD    += $(ALL_LIBS)
run_unittests_LDADD    += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD    += $(GTEST_LDADD)
# As noted in configure.ac, libtool doesn't work perfectly with Darwin: it
# embeds the final install path in dynamic libraries and loadable modules refer
# to that path even if its loaded within the source tree, so preventing tests
# from working - but only when linking statically.  The solution used in other
# Makefiles (setting the path to the dynamic libraries via an environment
# variable) don't seem to work.  What does work is to run the unit test using
# libtool and specifying paths via -dlopen switches.  So... If running in an
# environment where we have to set the library path AND if linking statically,
# override the "check" target and run the unit tests ourselves.

if USE_STATIC_LINK
if SET_ENV_LIBRARY_PATH
check-TESTS:
	$(LIBTOOL) --mode=execute -dlopen $(HOOKS_LIB)  -dlopen $(LOG_LIB) -dlopen $(THREADS_LIB) -dlopen $(UTIL_LIB) -dlopen $(EXCEPTIONS_LIB) ./run_unittests
endif
endif

endif

noinst_PROGRAMS = $(TESTS)

EXTRA_DIST = marker_file.h.in test_libraries.h.in
