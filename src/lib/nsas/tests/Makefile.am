SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/nsas -I$(top_builddir)/src/lib/nsas
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

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += address_entry_unittest.cc
run_unittests_SOURCES += hash_deleter_unittest.cc
run_unittests_SOURCES += hash_key_unittest.cc
run_unittests_SOURCES += hash_table_unittest.cc
run_unittests_SOURCES += hash_unittest.cc
run_unittests_SOURCES += nameserver_address_unittest.cc
run_unittests_SOURCES += nameserver_address_store_unittest.cc
run_unittests_SOURCES += nameserver_entry_unittest.cc
run_unittests_SOURCES += nsas_entry_compare_unittest.cc
run_unittests_SOURCES += nsas_test.h
run_unittests_SOURCES += zone_entry_unittest.cc
run_unittests_SOURCES += fetchable_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)
run_unittests_LDADD    = $(GTEST_LDADD)

run_unittests_LDADD += $(top_builddir)/src/lib/nsas/libb10-nsas.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libb10-dns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
endif

noinst_PROGRAMS = $(TESTS)
