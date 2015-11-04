SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DLOGGING_SPEC_FILE=\"$(abs_top_srcdir)/src/lib/dhcpsrv/logging.spec\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += libeval_unittests

libeval_unittests_SOURCES  = evaluate_unittest.cc
libeval_unittests_SOURCES += token_unittest.cc
libeval_unittests_SOURCES += run_unittests.cc
libeval_unittests_CXXFLAGS = $(AM_CXXFLAGS)
libeval_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libeval_unittests_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
libeval_unittests_LDADD    = $(top_builddir)/src/lib/eval/libkea-eval.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/log/libkea-log.la
libeval_unittests_LDADD   += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libeval_unittests_LDADD   += $(CRYPTO_LIBS) $(LOG4CPLUS_LIBS)
libeval_unittests_LDADD   += $(BOOST_LIBS) $(GTEST_LDADD)

if USE_CLANGPP
# This is to workaround unused variables tcout and tcerr in
# log4cplus's streams.h and unused parameters from some of the
# Boost headers.
libeval_unittests_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter
endif

endif

noinst_PROGRAMS = $(TESTS)
