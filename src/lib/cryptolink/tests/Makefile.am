SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_SRCDIR=\"$(abs_top_srcdir)/src/lib/cryptolink/tests/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/cryptolink/tests/testdata\"
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = run_unittests.cc
run_unittests_SOURCES += crypto_unittests.cc
run_unittests_SOURCES += hash_unittests.cc
run_unittests_SOURCES += hmac_unittests.cc
run_unittests_SOURCES += asym_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS =  $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS) $(AM_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD) $(CRYPTO_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
endif

noinst_PROGRAMS = $(TESTS)

#EXTRA_DIST += testdata/xxx
