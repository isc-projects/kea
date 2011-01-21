SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/cache -I$(top_builddir)/src/lib/cache
AM_CPPFLAGS += -DTEST_DATA_SRCDIR=\"$(srcdir)/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/cache/tests/testdata\"
AM_CXXFLAGS = $(B10_CXXFLAGS)


AM_LDFLAGS = $(PTHREAD_LDFLAGS)
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.     
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_CLANGPP
# see ../Makefile.am
AM_CXXFLAGS += -Wno-unused-parameter
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES  += $(top_srcdir)/src/lib/dns/tests/unittest_util.cc
run_unittests_SOURCES  += rrset_entry_unittest.cc
run_unittests_SOURCES  += rrset_cache_unittest.cc
run_unittests_SOURCES  += message_cache_unittest.cc
run_unittests_SOURCES  += message_entry_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)

# NOTE: we may have to clean up this hack later (see the note in configure.ac)
if NEED_LIBBOOST_THREAD
run_unittests_LDADD += -lboost_thread
endif

run_unittests_LDADD += $(top_builddir)/src/lib/cache/libcache.la
run_unittests_LDADD += $(top_builddir)/src/lib/nsas/libnsas.la
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
endif

noinst_PROGRAMS = $(TESTS)
